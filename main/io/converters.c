#include "converters.h"
#include <string.h>


float bytes_to_float(uint16_t high, uint16_t low, float scale) {
    uint32_t combined = ((uint32_t)high << 16) | low;
    return combined * scale;
}


 double bytes_to_double(uint16_t b3, uint16_t b2, uint16_t b1, uint16_t b0, float scale) {
    uint64_t combined = ((uint64_t)b3 << 48) |
                        ((uint64_t)b2 << 32) |
                        ((uint64_t)b1 << 16) |
                        b0;
    return combined * scale;
}
