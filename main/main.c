#include "system.h"
#include "multimeter.h"
#include "freertos/FreeRTOS.h" 
#include "freertos/task.h"
#include "esp_log.h"       
#include "logging.h"  

static const char *TAG = "MAIN";



void app_main(void)
{
    // Initialize components
    system_init();
    //print vals
    esp_err_t ret = multimeter_init();
    if (ret != ESP_OK) {
        LOG_ERROR(TAG, "Multimeter initialization failed!");
        return;
    }

     // Check slave presence
    if (multimeter_check_slave(MB_SLAVE_ADDR, 1000) != ESP_OK) {
        LOG_ERROR(TAG, "Slave device not found!");
        multimeter_cleanup();
        return;
    }

    // Data storage
    MultimeterData data[10];
    size_t num_regs = 0;

    while (1) {
        // Read data
        if (multimeter_read_data(data, &num_regs) == ESP_OK) {
            // Convert to JSON
            char *json = multimeter_to_json(data, num_regs);
            if (json) {
                LOG_DEBUG(TAG, "Multimeter Data:\n%s\n", json);
                free(json);
            }
        }
        
        vTaskDelay(pdMS_TO_TICKS(5000));
    }

    // Cleanup
    multimeter_cleanup();

}