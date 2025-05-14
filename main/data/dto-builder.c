#include "dto-builder.h"


static cJSON *build_device_info(void)
{
    // (Use real data later)
    cJSON *device = cJSON_CreateObject();
    cJSON_AddNumberToObject(device, "timestamp", 10044149);
    cJSON_AddStringToObject(device, "num_seriale", "paperino85");
    cJSON_AddStringToObject(device, "firmware", "pippeto");
    cJSON_AddStringToObject(device, "vers_hardware", "hhhh");
    cJSON_AddStringToObject(device, "modello", "ppp");
    cJSON_AddStringToObject(device, "caratt_comunicazione", "vredcs");
    cJSON_AddNumberToObject(device, "data_calibrazione", 3322123);
    cJSON_AddNumberToObject(device, "codice_err", 0);
    return device;
}

static cJSON *build_metrics(void)
{
    cJSON *metrics = cJSON_CreateArray();

    cJSON *m1 = cJSON_CreateObject();
    cJSON_AddNumberToObject(m1, "num_reg", 52);
    cJSON_AddNumberToObject(m1, "value", 180);
    cJSON_AddNumberToObject(m1, "word", 1);
    cJSON_AddItemToArray(metrics, m1);

    cJSON *m2 = cJSON_CreateObject();
    cJSON_AddNumberToObject(m2, "num_reg", 0);
    cJSON_AddNumberToObject(m2, "value", 10.34);
    cJSON_AddNumberToObject(m2, "word", 2);
    cJSON_AddItemToArray(metrics, m2);

    return metrics;
}

cJSON *json_build_payload(void)
{
    cJSON *payload = build_device_info();
    cJSON *metrics = build_metrics();
    cJSON_AddItemToObject(payload, "rilevazioni", metrics);
    return payload;
}