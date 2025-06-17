// memory.h
#ifndef MEMORY_H
#define MEMORY_H

#include "esp_err.h"
#include "mbcontroller.h"
#include "nvs_flash.h"


#define TREATED_DATA_DIR  "/spiffs/treated"
#define SAMPLING_DATA_DIR "/spiffs/sampling"

esp_err_t memory_init(void);
esp_err_t memory_cleanup(void);

esp_err_t memory_write(const char *filename, const float *data, size_t size);
esp_err_t memory_read(const char *filename);
esp_err_t memory_delete(const char *filename);
esp_err_t memory_get_size(const char *filename, size_t *size);
esp_err_t memory_read_buffer(const char *filename, void *buffer, size_t size);

esp_err_t memory_get_size(const char *filename, size_t *size);



#endif // MEMORY_H