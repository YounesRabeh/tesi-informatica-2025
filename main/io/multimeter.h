#pragma once
#include <stdint.h>
#include "esp_err.h"
#include "cJSON.h"
#include "target_registers.h"

// Modbus configuration
// Modbus port number
#define MB_PORT_NUM         1
// Modbus communication speed
#define MB_DEV_SPEED        19200
// Modbus communication mode
#define MB_PARITY_MODE      UART_PARITY_DISABLE
// Modbus slave address (multimeter address)
#define MB_SLAVE_ADDR       1
// Modbus UART Transmit
#define MB_UART_TXD         7
// Modbus UART Receive
#define MB_UART_RXD         8
// Modbus UART (Request to Send)
#define MB_UART_RTS         4
// Modbus Init Delay (in milliseconds)
#define MB_INIT_DELAY_MS    300

// 
#define NUM_REGISTERS ((int)(target_register_set.size))

#define MB_SLAVE_DELAY_BETWEEN_REQUESTS 50 // Delay between requests in milliseconds



/**
 * @brief Multimeter initialization. 
 * This function initializes the Modbus master communication
 */
esp_err_t multimeter_init(void);

/** 
 * @brief Reads data from the multimeter.
 */
esp_err_t multimeter_read_data(MultimeterData *data, size_t *num_registers);

/** 
 * @brief Converts multimeter data to JSON format.
 */
char* multimeter_to_json(const MultimeterData *data, size_t num_registers);

/**
 * @brief Cleans up the multimeter resources.
 * This function stops the Modbus master communication and frees resources.
 */
void multimeter_cleanup(void);
