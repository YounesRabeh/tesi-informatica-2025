#pragma once
#include <stdint.h>
#include "esp_err.h"
#include "cJSON.h"

// Modbus configuration
#define MB_PORT_NUM         1
#define MB_DEV_SPEED        19200
#define MB_PARITY_MODE      UART_PARITY_DISABLE
#define MB_SLAVE_ADDR       1
#define MB_UART_TXD         7
#define MB_UART_RXD         8
#define MB_UART_RTS         4

// Structure for multimeter data
typedef struct {
    const char *name;
    const char *unit;
    float value;
    esp_err_t error;
} MultimeterData;

// Structure for register configuration
typedef struct {
    const char *name;
    const char *unit;
    uint16_t reg_start;
    uint8_t reg_size;
    uint8_t command;
    float scale;
} MultimeterRegister;

// Modbus initialization
esp_err_t multimeter_init(void);

// Read all registers
esp_err_t multimeter_read_data(MultimeterData *data, size_t *num_registers);

// Convert data to JSON string (caller must free memory)
char* multimeter_to_json(const MultimeterData *data, size_t num_registers);

// Cleanup resources
void multimeter_cleanup(void);

// Add this prototype
esp_err_t multimeter_check_slave(uint8_t slave_addr, uint32_t timeout_ms);