#pragma once
#include "cJSON.h"

/**
 * @brief Builds the collected information JSON object.
 * @return A cJSON object containing the multimeter information.
 */
cJSON *json_build_payload(void); // Returns full payload: device + rilevazioni