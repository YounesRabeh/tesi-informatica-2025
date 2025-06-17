#include "data_manager.h"
#include "memory.h"
#include "logging.h"
#include <string.h>
#include <dirent.h>
#include "stdlib.h"

static const char *TAG = "DATA";

esp_err_t add_sample(const float *data, size_t data_size) {
    static int sample_count = 0;
    char filename[32];
    
    // Generate filename with incrementing counter
    snprintf(filename, sizeof(filename), "sample_%d.bin", sample_count++);
    
    // Use existing memory_write function
    // Note: You might need to modify memory_write to accept size parameter
    // or implement a new function if needed
    esp_err_t ret = memory_write(filename, data, data_size);
    if (ret != ESP_OK) {
        LOG_INFO(TAG, "Failed to add sample");
        return ret;
    }
    
    LOG_INFO(TAG, "Added new sample %s with %d values", filename, data_size);
    return ESP_OK;
}

esp_err_t treat_data(void) {
    // Placeholder implementation - just returns true for now
    LOG_INFO(TAG, "Data treatment placeholder - returning true");
    return ESP_OK;
    
    // Future implementation might:
    // 1. Read all samples
    // 2. Process them (average, filter, etc.)
    // 3. Store results in treated data
    // 4. Return success status
}

esp_err_t clear_sampling_space(void) {
    DIR *dir;
    struct dirent *entry;
    
    dir = opendir(SAMPLING_DATA_DIR);
    if (dir == NULL) {
        LOG_ERROR(TAG, "Failed to open sampling directory");
        return ESP_FAIL;
    }
    
    while ((entry = readdir(dir)) != NULL) {
        // Skip current and parent directory entries
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) {
            continue;
        }
        
        // Safer path construction with buffer size checking
        char filepath[128]; 
        int needed = snprintf(filepath, sizeof(filepath), "%s/%s", SAMPLING_DATA_DIR, entry->d_name);
        
        // Validate path length before using
        if (needed < 0 || (size_t)needed >= sizeof(filepath)) {
            LOG_ERROR(TAG, "Path too long for: %s", entry->d_name);
            continue;  // Skip this file but continue with others
        }
        
        // Use existing memory_delete function
        esp_err_t ret = memory_delete(entry->d_name);
        if (ret != ESP_OK) {
            closedir(dir);
            return ret;
        }
        
        LOG_INFO(TAG, "Deleted file %s", filepath);
    }
    
    closedir(dir);
    LOG_INFO(TAG, "Cleared all sampling data");
    return ESP_OK;
}

esp_err_t pop_sample(float **data, size_t *data_size) {
    DIR *dir;
    struct dirent *entry;
    char oldest_filename[32] = "";
    int min_sample_num = INT_MAX;
    
    *data = NULL;
    *data_size = 0;

    // 1. Find the oldest sample (smallest number)
    dir = opendir(SAMPLING_DATA_DIR);
    if (dir == NULL) {
        LOG_ERROR(TAG, "Failed to open sampling directory");
        return ESP_FAIL;
    }

    while ((entry = readdir(dir)) != NULL) {
        // Skip non-sample files and directories
        if (strncmp(entry->d_name, "sample_", 7) != 0 || 
            strstr(entry->d_name, ".bin") == NULL) {
            continue;
        }

        // Extract sample number
        int sample_num;
        if (sscanf(entry->d_name, "sample_%d.bin", &sample_num) != 1) {
            continue;
        }

        // Track oldest sample
        if (sample_num < min_sample_num) {
            min_sample_num = sample_num;
            strncpy(oldest_filename, entry->d_name, sizeof(oldest_filename));
        }
    }
    closedir(dir);

    if (oldest_filename[0] == '\0') {
        LOG_INFO(TAG, "No samples found to pop");
        return ESP_ERR_NOT_FOUND;
    }

    // 2. Read the file data
    size_t file_size;
    esp_err_t ret = memory_get_size(oldest_filename, &file_size);
    if (ret != ESP_OK) {
        LOG_ERROR(TAG, "Failed to get size of %s", oldest_filename);
        return ret;
    }

    // Allocate buffer (file_size should be multiple of sizeof(float))
    *data = malloc(file_size);
    if (*data == NULL) {
        LOG_ERROR(TAG, "Memory allocation failed");
        return ESP_ERR_NO_MEM;
    }

    ret = memory_read_buffer(oldest_filename, *data, file_size);
    if (ret != ESP_OK) {
        LOG_ERROR(TAG, "Failed to read sample %s", oldest_filename);
        free(*data);
        *data = NULL;
        return ret;
    }

    // 3. Delete the file
    ret = memory_delete(oldest_filename);
    if (ret != ESP_OK) {
        LOG_WARNING(TAG, "Read sample but failed to delete %s", oldest_filename);
        // We still return the data despite delete failure
    }

    *data_size = file_size / sizeof(float);
    LOG_INFO(TAG, "Popped sample %s (%d floats)", oldest_filename, *data_size);
    return ESP_OK;
}