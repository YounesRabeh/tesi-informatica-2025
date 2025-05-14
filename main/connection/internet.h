#pragma once

#include "wifi.h"
#include "lte.h" 

#include "esp_sntp.h"
#include "esp_crt_bundle.h"
#include "dto-builder.h"

#define NTP_SERVER "pool.ntp.org"
#define NTP_RETRY_ATTEMPTS 20


/**
 * @brief Initializes the available network interfaces.
 *
 * This will initialize Wi-Fi, LTE, or both based on configuration.
 */
void connection_init(void);

/**
 * @brief Sets up NTP time synchronization.
 *
 * This function configures the SNTP client to synchronize time with the specified NTP server.
 * It will retry for a specified number of attempts until the time is synchronized.
 */
void setup_ntp_time(void);

/**
 * @brief Sends JSON data to the server.
 *
 * This function sends the provided JSON data to the server using HTTPS POST.
 * It will retry sending the data for a specified number of attempts if it fails.
 *
 * @param json The JSON object to send.
 * @return ESP_OK on success, or an error code on failure.
 */
esp_err_t send_data(cJSON *json);
