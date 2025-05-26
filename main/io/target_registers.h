#pragma once
#include <stdint.h>
#include "esp_err.h"

#ifndef TARGET_REGISTERS_H
#define TARGET_REGISTERS_H

/** 
 * @brief Modbus communication information structure.
 */
typedef struct {
    const char *name;
    const char *unit;
    float value;
    esp_err_t error;
} MultimeterData;

/**
 * @brief register definition for the UMP209 multimeter.
 */
typedef struct {
    const char *name;
    const char *unit;
    uint16_t reg_start;
    uint8_t reg_size;
    uint8_t command;
    float scale;
} MultimeterRegister;

/**
 * @brief Set of registers for the UMP209 multimeter. 
 * This structure contains an array of registers and its size.
 */
typedef struct {
    const MultimeterRegister *registers;
    // switch to short for smaller memory footprint
    int size;
} MultimeterRegisterSet;

/**
 * @brief Multimeter data structure set.
 */
extern const MultimeterRegisterSet target_register_set;

#endif // TARGET_REGISTERS_H