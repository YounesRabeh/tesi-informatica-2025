#include "system.h"
#include "multimeter.h"
#include "memory.h"
#include "data/data_manager.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "logging.h"
#include <dirent.h>
#include "time.h"
#include "sys/stat.h"
#include <limits.h>
#include "internet.h"
#include <math.h>

#define TAG "MAIN"
#define LOG_INTERVAL_MS 5000 
#define MAX_FILES 100          
#define SAMPLE_INTERVAL_MS 10000 


static void multimeter_task(void *pvParameters) {
    LOG_INFO(TAG, "Multimeter task started");
    
    // Initialize data structure
    MultimeterData data[NUM_REGISTERS];
    memset(data, 0, sizeof(data));
    size_t num_registers = 0;
    uint8_t consecutive_errors = 0;
    const uint8_t max_consecutive_errors = 3;

    while (1) {
        // Clear previous data
        memset(data, 0, sizeof(data));
        num_registers = 0;

        // Attempt to read with retry mechanism
        esp_err_t ret = ESP_FAIL;
        for (uint8_t attempt = 0; attempt < 3 && ret != ESP_OK; attempt++) {
            ret = multimeter_read_data(data, &num_registers);
            
            if (ret != ESP_OK) {
                vTaskDelay(pdMS_TO_TICKS(200)); // between retries
            }
        }

        if (ret == ESP_OK) {
            consecutive_errors = 0; // Reset error counter
            
            // Validate register count
            if (num_registers > 0 && num_registers <= NUM_REGISTERS) {
                
                // Process and log each register
                for (size_t i = 0; i < num_registers; i++) {
                    if (!isnan(data[i].value)) {
                        LOG_DEBUG(TAG, "Register %d: %.2f", i, data[i].value);
                    } else {
                        LOG_WARNING(TAG, "Register %d: Invalid reading (NaN)", i);
                        data[i].value = 0.0f; // Replace NaN with 0
                    }
                }
                
                // Send data for storage
                float scaled_values[NUM_REGISTERS];
                for (size_t i = 0; i < num_registers; i++) {
                    scaled_values[i] = data[i].value;
                }
                
                if (add_sample(scaled_values, num_registers) != ESP_OK) {
                    LOG_ERROR(TAG, "Failed to store sample");
                }
            } else {
                LOG_ERROR(TAG, "Invalid register count: %d", num_registers);
            }
        } else {
            consecutive_errors++;
            LOG_ERROR(TAG, "Read failed after 3 attempts (0x%x)", ret);
            
            if (consecutive_errors >= max_consecutive_errors) {
                LOG_ERROR(TAG, "Max consecutive errors reached, resetting Modbus");
                multimeter_cleanup();
                vTaskDelay(pdMS_TO_TICKS(1000));
                multimeter_init();
                consecutive_errors = 0;
            }
        }

        vTaskDelay(pdMS_TO_TICKS(SAMPLE_INTERVAL_MS));
    }

}


void data_sender_task(void *pvParameters)
{
    const TickType_t send_interval = pdMS_TO_TICKS(DATA_SEND_INTERVAL_MS);

    while (1) {
        LOG_INFO(TAG, "Preparing to send data...");
        cJSON *json = json_build_payload();

        cJSON *measurements = cJSON_GetObjectItem(json, "measurements");
        if (!measurements || !cJSON_IsArray(measurements) || cJSON_GetArraySize(measurements) == 0) {
            LOG_WARNING(TAG, "No measurements to send, skipping...");
            cJSON_Delete(json);
            vTaskDelay(send_interval);
            continue;
        }

        esp_err_t ret = send_data(json);
        cJSON_Delete(json);

        if (ret != ESP_OK) {
            LOG_ERROR(TAG, "Failed to send data.");
        }
        vTaskDelay(send_interval);
    }
}



void app_main(void) {
    system_init();
    
    if (multimeter_init() != ESP_OK) {
        memory_cleanup();
        return;
    }
    
    xTaskCreate(multimeter_task, "multimeter_task", 8192, NULL, 6, NULL);
    xTaskCreate(data_sender_task, "data_sender_task", 4096, NULL, 5, NULL);

    LOG_SUCCESS(TAG, "System started successfully");
}