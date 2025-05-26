#include <string.h> 
#include "wifi.h"

static const char *TAG = "WIFI";


EventGroupHandle_t wifi_event_group;
esp_netif_ip_info_t ip_info;

int retry_count = 0;

/**
 * @brief WiFi event handler callback.
 *
 * This function is called when WiFi events occur, such as connection and disconnection.
 * - On disconnection, it attempts to reconnect.
 * - On getting IP, it stores the IP info and sets the event bit to signal connectivity.
 *
 * @param arg         Unused.
 * @param event_base  Event base type (e.g., WIFI_EVENT, IP_EVENT).
 * @param event_id    Specific event ID (e.g., WIFI_EVENT_STA_DISCONNECTED).
 * @param event_data  Event-specific data (e.g., IP info).
 */
static void wifi_event_handler(void *arg, esp_event_base_t event_base,
                               int32_t event_id, void *event_data)
{
    if (event_base == WIFI_EVENT && event_id == WIFI_EVENT_STA_DISCONNECTED) {
        if (retry_count < MAX_RETRY_ATTEMPTS) {
            retry_count++;
            LOG_WARNING(TAG, "Disconnected. Retrying (%d/%d)...", retry_count, MAX_RETRY_ATTEMPTS);
            esp_wifi_connect();
        } else {
            LOG_ERROR(TAG, "Wi-Fi connection failed after %d attempts.", MAX_RETRY_ATTEMPTS);
            xEventGroupSetBits(wifi_event_group, WIFI_FAIL_BIT);
        }
    } else if (event_base == IP_EVENT && event_id == IP_EVENT_STA_GOT_IP) {
        ip_event_got_ip_t *event = (ip_event_got_ip_t *)event_data;
        memcpy(&ip_info, &event->ip_info, sizeof(ip_info));
        LOG_SUCCESS(TAG, "Connected | IP: " IPSTR, IP2STR(&ip_info.ip));
        retry_count = 0;  // Reset retry count on successful connection
        xEventGroupSetBits(wifi_event_group, WIFI_CONNECTED_BIT);
    }
}

esp_err_t wifi_init_sta(void)
{
    LOG_INFO(TAG, "Initializing WIFI...");
    //LOG_INFO(TAG, "PASS: '%s'", WIFI_PASS);
    wifi_event_group = xEventGroupCreate();

    ESP_ERROR_CHECK(esp_netif_init());
    ESP_ERROR_CHECK(esp_event_loop_create_default());
    esp_netif_create_default_wifi_sta();

    wifi_init_config_t cfg = WIFI_INIT_CONFIG_DEFAULT();
    ESP_ERROR_CHECK(esp_wifi_init(&cfg));

    ESP_ERROR_CHECK(esp_event_handler_instance_register(WIFI_EVENT, WIFI_EVENT_STA_DISCONNECTED, &wifi_event_handler, NULL, NULL));
    ESP_ERROR_CHECK(esp_event_handler_instance_register(IP_EVENT, IP_EVENT_STA_GOT_IP, &wifi_event_handler, NULL, NULL));

    wifi_config_t wifi_config = {
        .sta = {
            .ssid = WIFI_SSID,
            .password = WIFI_PASS,
            .threshold.authmode = WIFI_AUTH_MODE,
        },
    };
    ESP_ERROR_CHECK(esp_wifi_set_mode(WIFI_MODE_STA));
    ESP_ERROR_CHECK(esp_wifi_set_config(WIFI_IF_STA, &wifi_config));
    ESP_ERROR_CHECK(esp_wifi_start());
    ESP_ERROR_CHECK(esp_wifi_connect());
    LOG_INFO(TAG, "WIFI initialized Correctly. Triying to connect to %s...", WIFI_SSID);
    // Wait for the connection result with a timeout
    EventBits_t bits = xEventGroupWaitBits(wifi_event_group,
        WIFI_CONNECTED_BIT | WIFI_FAIL_BIT,
        pdTRUE,
        pdFALSE,
        pdMS_TO_TICKS(WIFI_CONNECT_TIMEOUT_MS)
    );
    if (bits & WIFI_CONNECTED_BIT) {
        return ESP_OK;
    } else if (bits & WIFI_FAIL_BIT) {
        LOG_ERROR(TAG, "failed to connect.");   
        return ESP_FAIL;
    } else {
        LOG_ERROR(TAG, "connection timed out.");
        return ESP_FAIL;
    }

}
