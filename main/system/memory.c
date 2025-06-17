#include "memory.h"
#include "logging.h"
#include "config.h"
#include "esp_spiffs.h"
#include "cJSON.h"
#include <string.h>
#include <sys/stat.h>
#include <errno.h>
#include <dirent.h>
#include <limits.h>

static const char *TAG = "MEMORY";

esp_err_t memory_init(void) {
    esp_err_t ret;


    esp_vfs_spiffs_unregister(NULL); // Unregister any previous SPIFFS instan
    
    esp_vfs_spiffs_conf_t conf = {
        .base_path = "/spiffs",
        .partition_label = NULL,
        .max_files = 5,
        .format_if_mount_failed = true
    };
    
    ret = esp_vfs_spiffs_register(&conf);
    if (ret != ESP_OK) {
        if (ret == ESP_FAIL) {
            LOG_ERROR(TAG, "Failed to mount or format filesystem");
        } else if (ret == ESP_ERR_NOT_FOUND) {
            LOG_ERROR(TAG, "Failed to find SPIFFS partition");
        } else {
            LOG_ERROR(TAG, "Failed to initialize SPIFFS (%s)", esp_err_to_name(ret));
        }
        return ret;
    }
    
    mkdir(TREATED_DATA_DIR, 0777);
    mkdir(SAMPLING_DATA_DIR, 0777);
    
    LOG_SUCCESS(TAG, "SPIFFS initialized successfully");
    return ESP_OK;
}

esp_err_t memory_cleanup(void) {
    return esp_vfs_spiffs_unregister(NULL);
}

esp_err_t memory_write(const char *filename, const float *data, size_t size) {
    char path[128];
    snprintf(path, sizeof(path), "%s/%s", SAMPLING_DATA_DIR, filename);
    
    FILE *f = fopen(path, "wb");
    if (f == NULL) {
        LOG_ERROR(TAG, "Failed to open file for writing: %s", path);
        return ESP_FAIL;
    }
    
    size_t written = fwrite(data, sizeof(float), size, f);
    fclose(f);
    
    if (written != size) {
        LOG_ERROR(TAG, "Write incomplete: %d/%d bytes", written, size);
        return ESP_FAIL;
    }
    
    LOG_INFO(TAG, "Wrote %d floats to %s", size, path);
    return ESP_OK;
}

esp_err_t memory_read(const char *filename) {
    char path[128];
    snprintf(path, sizeof(path), "%s/%s", SAMPLING_DATA_DIR, filename);
    
    FILE *f = fopen(path, "rb");
    if (f == NULL) {
        LOG_ERROR(TAG, "Failed to open file for reading: %s", path);
        return ESP_FAIL;
    }
    
    // Determine file size
    fseek(f, 0, SEEK_END);
    long fsize = ftell(f);
    fseek(f, 0, SEEK_SET);
    
    size_t num_values = fsize / sizeof(float);
    float *data = malloc(fsize);
    if (data == NULL) {
        fclose(f);
        LOG_ERROR(TAG, "Failed to allocate memory");
        return ESP_ERR_NO_MEM;
    }
    
    if (fread(data, sizeof(float), num_values, f) != num_values) {
        free(data);
        fclose(f);
        LOG_ERROR(TAG, "Failed to read float array");
        return ESP_FAIL;
    }
    
    fclose(f);
    
    // Process your data here or return it through a parameter
    // For now, just log that we read it
    LOG_INFO(TAG, "Read %d values from %s", num_values, path);
    
    free(data);
    return ESP_OK;
}

esp_err_t memory_delete(const char *filename) {
    char path[128];
    snprintf(path, sizeof(path), "%s/%s", SAMPLING_DATA_DIR, filename);
    
    if (remove(path) != 0) {
        LOG_ERROR(TAG, "Failed to delete file: %s", path);
        return ESP_FAIL;
    }
    
    LOG_INFO(TAG, "Deleted file: %s", path);
    return ESP_OK;
}

esp_err_t memory_read_buffer(const char *filename, void *buffer, size_t size) {
    char path[128];
    // If filename is already a full path, you can just use it directly
    snprintf(path, sizeof(path), "%s/%s", SAMPLING_DATA_DIR, filename);
    FILE *f = fopen(path, "rb");
    if (!f) return ESP_FAIL;
    size_t n = fread(buffer, 1, size, f);
    fclose(f);
    return (n == size) ? ESP_OK : ESP_FAIL;
}

esp_err_t memory_get_size(const char *filename, size_t *size) {
    char path[128];
    snprintf(path, sizeof(path), "%s/%s", SAMPLING_DATA_DIR, filename);
    FILE *f = fopen(path, "rb");
    if (!f) return ESP_FAIL;
    fseek(f, 0, SEEK_END);
    long sz = ftell(f);
    fclose(f);
    if (sz < 0) return ESP_FAIL;
    *size = (size_t)sz;
    return ESP_OK;
}

