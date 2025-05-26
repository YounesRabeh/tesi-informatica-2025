#pragma once


#include "esp_wifi.h"
#include "esp_event.h"
#include "esp_netif.h"
#include "esp_netif_ip_addr.h"
#include "esp_http_client.h"
#include "config.h"
#include "logging.h"

/** 
 * @brief The connection timeout in milliseconds.
 */
#define WIFI_CONNECT_TIMEOUT_MS 10000
/**
 * @brief The maximum number of retry attempts for WiFi connection.
 */
#define MAX_RETRY_ATTEMPTS      5
/**
 * @brief Bit set in wifi_event_group when connected to WiFi.
 */
#define WIFI_CONNECTED_BIT BIT0 
/**
 * @brief Bit set in wifi_event_group when WiFi connection fails.
 */
#define WIFI_FAIL_BIT      BIT1

/**
 * @brief Event group used to signal when WiFi is connected.
 */
extern EventGroupHandle_t wifi_event_group;

/**
 * @brief IP information structure to hold the IP address, netmask, and gateway.
 */
extern esp_netif_ip_info_t ip_info;

/**
 * @brief Initializes WiFi in Station (STA) mode.
 *
 * - Initializes the network interface and default event loop.
 * - Registers the event handler for WiFi and IP events.
 * - Sets WiFi configuration using SSID, password, and auth mode.
 * - Starts WiFi and attempts to connect.
 */
esp_err_t wifi_init_sta(void);


