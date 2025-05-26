#include "system.h"

#include <string.h>
#include "esp_err.h"
#include "config.h"
#include "logging.h"
#include "memory.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#include "internet.h"
#include "dto-builder.h"


static const char *TAG = "SYSTEM";
esp_err_t wifi_init_sta(void);
void data_sender_task(void *pvParameters);


void system_init(void)
{
    LOG_INFO(TAG, "Booting up...");
    // Set log levels first
    esp_log_level_set("*", ESP_LOG_ERROR); 
    esp_log_level_set(TAG, ESP_LOG_INFO);  

    ESP_ERROR_CHECK(nvs_flash_init());
    connection_init();

    LOG_SUCCESS(TAG, "System Initializated.");

    if (xTaskCreate(data_sender_task, "data_sender_task", 8192, NULL, 5, NULL) != pdPASS) {
        LOG_ERROR(TAG, "Failed to create data sender task.");
    }

}

// Task to periodically send JSON data to the server
void data_sender_task(void *pvParameters)
{
    const TickType_t send_interval = pdMS_TO_TICKS(DATA_SEND_INTERVAL_MS);

    while (1) {
        LOG_INFO(TAG, "Preparing to send data...");
        cJSON *json = json_build_payload();
        esp_err_t ret = send_data(json);
        cJSON_Delete(json);

        if (ret != ESP_OK) { LOG_ERROR(TAG, "Failed to send data.");}
        vTaskDelay(send_interval);
    }
}
