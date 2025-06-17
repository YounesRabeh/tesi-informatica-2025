#pragma once

#define CONFIG_FILE "/spiffs/mb_config.json"

#define WIFI_SSID      CONFIG_WIFI_SSID
#define WIFI_PASS      CONFIG_WIFI_PASS
#define API_URL        "https://api.blackboxchain.cloud/saveData"


#define DATA_SEND_INTERVAL_MS    10000
#define DATA_SEND_RETRY_AFTER_MS 2000 


#define WIFI_AUTH_MODE WIFI_AUTH_WPA2_PSK
#define DATA_SENDING_MAX_RETRIES 3



#define MODEM_TYPE           ESP_MODEM_DCE_SIM7600 
#define MODEM_TXD_PIN        17
#define MODEM_RXD_PIN        16
#define MODEM_BAUD_RATE      115200
#define ESP_MODEM_DTE_DEFAULT_CONFIG() { \
    .uart_config = { \
        .tx_io_num = 17, \
        .rx_io_num = 16, \
        .baud_rate = 115200, \
        .data_bits = UART_DATA_8_BITS, \
        .parity = UART_PARITY_DISABLE, \
        .stop_bits = UART_STOP_BITS_1 \
    } \
}


#define MULTIMETER_DATA_INTERVAL_MS 5000 



