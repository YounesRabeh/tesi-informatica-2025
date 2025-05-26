#include "target_registers.h"
 
/**
 * @brief Array of registers for the UMP209 multimeter (hardcoded).
 */
static const MultimeterRegister targetRegister[] = {
    // Instant values
    { "Voltage_L1", "V", 0x0000, 2, 0x04, 0.001 },
    { "Current_L1", "A", 0x000E, 2, 0x04, 0.001 },
    // Add other registers...
};

const MultimeterRegisterSet target_register_set = {
    .registers = targetRegister,
    .size = sizeof(targetRegister) / sizeof(targetRegister[0])
};