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

/**
 * @brief Checks if a Modbus slave is responsive.
 * 
 * @param slave_addr The address of the Modbus slave to check.
 * @param timeout_ms Timeout in milliseconds for the check.
 * @return ESP_OK if the slave is responsive, otherwise an error code.
 */
esp_err_t multimeter_check_slave(uint8_t slave_addr, uint32_t timeout_ms);