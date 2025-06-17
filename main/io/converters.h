#pragma once

#include <stdint.h>

/**
 * @brief Convert two 16-bit Modbus registers (MSB first) to a 32-bit IEEE-754 float.
 *
 * @param high Most significant 16-bit word.
 * @param low  Least significant 16-bit word.
 * @param scale Scale multiplier to apply to the final value.
 * @return The resulting float value.
 */
float bytes_to_float(uint16_t high, uint16_t low, float scale);

/**
 * @brief Convert four 16-bit Modbus registers (MSB first) to a 64-bit IEEE-754 double.
 *
 * @param b3 Most significant word.
 * @param b2 Next word.
 * @param b1 Next word.
 * @param b0 Least significant word.
 * @param scale Scale multiplier to apply to the final value.
 * @return The resulting double value.
 */
double bytes_to_double(uint16_t b3, uint16_t b2, uint16_t b1, uint16_t b0, float scale);
