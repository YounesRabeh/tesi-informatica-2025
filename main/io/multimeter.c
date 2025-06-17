#include "multimeter.h"
#include "memory.h"
#include "mbcontroller.h"
#include "esp_log.h"
#include "logging.h"
#include "converters.h"
#include "driver/uart.h"
#include "cJSON.h"
#include <math.h>


#define TAG "MULTIMETER"


static void* master_handler = NULL;

esp_err_t multimeter_init(void) {
    mb_communication_info_t comm = {
        .port = MB_PORT_NUM,
        .mode = MB_MODE_RTU,
        .baudrate = MB_DEV_SPEED,
        .parity = MB_PARITY_MODE
    };


    esp_err_t err = mbc_master_init(MB_PORT_SERIAL_MASTER, &master_handler);
    if (err != ESP_OK || !master_handler) return err;

    if ((err = mbc_master_setup((void*)&comm))) return err;
    if ((err = uart_set_pin(MB_PORT_NUM, MB_UART_TXD, MB_UART_RXD, MB_UART_RTS, UART_PIN_NO_CHANGE))) return err;
    if ((err = mbc_master_start())) return err;

    
    vTaskDelay(pdMS_TO_TICKS(1000));

    LOG_SUCCESS(TAG, "Port %d is Modbus Active", MB_PORT_NUM);
    return ESP_OK;
}

esp_err_t multimeter_read_data(MultimeterData *data, size_t *num_registers) {
    if (!data || !num_registers) return ESP_ERR_INVALID_ARG;

    // Always use the correct number of registers
    size_t reg_count = target_register_set.size;
    *num_registers = reg_count;

    
    for (size_t i = 0; i < *num_registers; i++) {
        const MultimeterRegister *reg = &target_register_set.registers[i];
        uint16_t raw_data[4] = {0};
        
        mb_param_request_t request = {
            .slave_addr = MB_SLAVE_ADDR,
            .command = reg->command,
            .reg_start = reg->reg_start,
            .reg_size = reg->reg_size
        };

        data[i].name = reg->name;
        data[i].unit = reg->unit;
        data[i].error = mbc_master_send_request(&request, raw_data);

        if (data[i].error == ESP_OK) {
            switch (reg->reg_size) {
                case 4:
                    data[i].value = bytes_to_double(
                        raw_data[0], raw_data[1],
                        raw_data[2], raw_data[3],
                        reg->scale
                    );
                    break;
                case 2:
                    data[i].value = bytes_to_float(
                        raw_data[0], raw_data[1],
                        reg->scale
                    );
                    break;
                default:
                    data[i].value = raw_data[0] * reg->scale;
                    break;
            }
        } else {
            LOG_ERROR(TAG, "Error reading %s: %s", 
                   reg->name, esp_err_to_name(data[i].error));
            data[i].value = NAN;
        }
         vTaskDelay(pdMS_TO_TICKS(MB_SLAVE_DELAY_BETWEEN_REQUESTS));
    }
    
    return ESP_OK;
}

char* multimeter_to_json(const MultimeterData *data, size_t num_registers) {
    
    cJSON *root = cJSON_CreateObject();
    
    for (size_t i = 0; i < num_registers; i++) {
        cJSON *item = cJSON_CreateObject();
        cJSON_AddStringToObject(item, "unit", data[i].unit);
        
        if (data[i].error == ESP_OK) {
            cJSON_AddNumberToObject(item, "value", data[i].value);
        } else {
            cJSON_AddStringToObject(item, "[!!!] -error", 
                esp_err_to_name(data[i].error));
        }
        
        cJSON_AddItemToObject(root, data[i].name, item);
    }
    
    char *json = cJSON_PrintUnformatted(root);
    cJSON_Delete(root);
    return json;
}



void multimeter_cleanup(void) {
    if (master_handler) {
        mbc_master_destroy();
        master_handler = NULL;
    }
}
