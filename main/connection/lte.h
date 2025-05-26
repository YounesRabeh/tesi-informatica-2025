#pragma once

#include "config.h"
#include "logging.h"

/**
 * @brief Initializes LTE modem (SIM card) and connects to the internet.
 * @return ESP_OK on success, or an error code on failure.
 */
esp_err_t lte_init(void);
