#include "dto_builder.h"
#include "data_manager.h"
#include "target_registers.h"
#include <string.h>
#include <stdlib.h>
#include "logging.h"
#include "cJSON.h"

const char *TAG = "DTO-BUILDER";

static cJSON *build_device_info(void) {
    cJSON *device = cJSON_CreateObject();
    cJSON_AddStringToObject(device, "device_id", "UMP209-001 via ESP32s3");
    cJSON_AddStringToObject(device, "firmware_version", "0.8");
    cJSON_AddStringToObject(device, "device_type", "Multimeter");
    cJSON_AddStringToObject(device, "status", "____UNDER DEVELOPMENT____");
    return device;
}

static cJSON *build_metrics_from_samples(void) {
    cJSON *metrics = cJSON_CreateArray();
    size_t sample_count = 0;
    float *samples = NULL;
    if (pop_sample(&samples, &sample_count) != ESP_OK || !samples || sample_count == 0) {
        return metrics; // Return empty array if no samples
    }

    // Each value corresponds to the register at the same index
    for (size_t i = 0; i < sample_count && i < target_register_set.size; i++) {
        const MultimeterRegister *reg = &target_register_set.registers[i];
        cJSON *metric = cJSON_CreateObject();
        cJSON_AddStringToObject(metric, "name", reg->name);
        cJSON_AddNumberToObject(metric, "register", reg->reg_start);
        cJSON_AddNumberToObject(metric, "value", samples[i]);
        cJSON_AddStringToObject(metric, "unit", reg->unit);
        cJSON_AddItemToArray(metrics, metric);
    }

    free(samples);
    return metrics;
}

cJSON *json_build_payload(void) {
    cJSON *payload = build_device_info();
    cJSON *metrics = build_metrics_from_samples();
    cJSON_AddItemToObject(payload, "measurements", metrics);
    return payload;
}