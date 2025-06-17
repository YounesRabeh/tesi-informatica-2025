#include "config.h"
#include "internet.h"
#include "logging.h"

/**
 * @brief The Internet module Tag for logging.
 */
static const char *TAG = "INTERNET";


esp_err_t connection_init(void)
{
    esp_err_t ret = wifi_init_sta();
    if (ret == ESP_OK) {
        LOG_SUCCESS(TAG, "Wi-Fi connected successfully, no need for LTE.");
    } else {
        LOG_WARNING(TAG, "Wi-Fi failed (err=0x%x), falling back to LTE.", ret);
        ret = lte_init();
        if (ret != ESP_OK) {
            LOG_ERROR(TAG, "LTE initialization failed (err=0x%x)", ret);
            return ret;
        }
    }

    if (setup_ntp_time() != ESP_OK) {
        LOG_WARNING(TAG, "NTP time setup failed");
    }

    return ESP_OK;
}

esp_err_t send_data(cJSON *json)
{
    char *payload_str = cJSON_PrintUnformatted(json); // Using passed JSON

    esp_http_client_config_t config = {
        .url = API_URL,
        .method = HTTP_METHOD_POST,
        .transport_type = HTTP_TRANSPORT_OVER_SSL,
        .crt_bundle_attach = esp_crt_bundle_attach,
        .timeout_ms = DATA_SEND_INTERVAL_MS,
    };

    LOG_DEBUG(TAG, "Sending JSON: %s", payload_str);

    esp_http_client_handle_t client = esp_http_client_init(&config);
    esp_http_client_set_header(client, "Content-Type", "application/json");
    esp_http_client_set_post_field(client, payload_str, strlen(payload_str));

    esp_err_t err = ESP_FAIL;
    int retry_count = 0;
    int status_code = 0;

    while (retry_count < DATA_SENDING_MAX_RETRIES)
    {
        err = esp_http_client_perform(client);
        if (err == ESP_OK)
        {
            status_code = esp_http_client_get_status_code(client);
            if (status_code >= 200 && status_code < 300) {
                LOG_SUCCESS(TAG, "Data sent successfully (Status: %d)", status_code);
                break;
            } else {
                LOG_ERROR(TAG, "Server error (Status: %d), retry %d/%d",
                            status_code, retry_count + 1, DATA_SENDING_MAX_RETRIES);
            }
        } else {
            LOG_ERROR(TAG, "Connection error: %s, retry %d/%d",
                      esp_err_to_name(err), retry_count + 1, DATA_SENDING_MAX_RETRIES);
        }
        retry_count++;
        vTaskDelay(pdMS_TO_TICKS(DATA_SEND_RETRY_AFTER_MS));
    }

    esp_http_client_cleanup(client);
    free(payload_str);
    return err;
}

esp_err_t setup_ntp_time(void) {
    esp_sntp_setoperatingmode(SNTP_OPMODE_POLL);
    esp_sntp_setservername(0, NTP_SERVER);
    esp_sntp_init();

    time_t now = 0;
    struct tm timeinfo = { 0 };
    int retry_attempts = NTP_MAX_RETRY_ATTEMPTS;

    while (timeinfo.tm_year < (2020 - 1900) && retry_attempts > 0) {
        time(&now);
        localtime_r(&now, &timeinfo);
        vTaskDelay(pdMS_TO_TICKS(1000));  
        retry_attempts--;
    }
    if (retry_attempts == 0) {
        LOG_ERROR(TAG, "Failed to sync time after %d attempts", NTP_MAX_RETRY_ATTEMPTS);
        return ESP_FAIL;
    } else {
        localtime_r(&now, &timeinfo);
        LOG_SUCCESS(TAG, "Time synchronized: %s", asctime(&timeinfo));
        return ESP_OK;
    }
}

