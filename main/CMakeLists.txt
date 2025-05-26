idf_component_register(
    SRCS 
        "system/system.c"
        "connection/wifi.c" 
        "connection/lte.c" 
        "connection/internet.c"
        "data/dto-builder.c"
        "io/target_registers.c"
        "io/multimeter.c"
        "main.c"
    INCLUDE_DIRS "." "system" "connection" "data" "io" 
    REQUIRES 
        esp_http_client
        esp-tls
        json
        nvs_flash
        esp_netif
        esp_wifi
        esp-modbus
        freertos
        esp_event
)

# Check if the environment variables are set
if(NOT DEFINED ENV{WIFI_SSID})
    message(FATAL_ERROR "WIFI_SSID environment variable not set.")
else()
    set(WIFI_SSID $ENV{WIFI_SSID})
    message(STATUS "Using SSID: ${WIFI_SSID}")
endif()

if(NOT DEFINED ENV{WIFI_PASS})
    message(FATAL_ERROR "WIFI_PASS environment variable not set.")
else()
    set(WIFI_PASS $ENV{WIFI_PASS})
    message(STATUS "Using Password: ${WIFI_PASS}")
endif()

# Passing to compile definitions
target_compile_definitions(${COMPONENT_LIB} PRIVATE
    CONFIG_WIFI_SSID="${WIFI_SSID}"
    CONFIG_WIFI_PASS="${WIFI_PASS}"
)
