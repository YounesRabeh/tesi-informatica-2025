#pragma once

#include "esp_err.h"

esp_err_t add_sample(const float *data, size_t data_size);
esp_err_t treat_data(void);
esp_err_t clear_sampling_space(void);
esp_err_t pop_sample(float **data, size_t *data_size);
