#pragma once

#include <stdio.h>
#include <string.h>
#include "esp_log.h"


#define TAG_SIZE "%-10s"

#define COLOR_RESET    "\033[0m"
#define COLOR_WHITE    "\033[0;37m"
#define COLOR_GREEN    "\033[0;32m"
#define COLOR_YELLOW   "\033[0;33m"
#define COLOR_RED      "\033[0;31m"
#define COLOR_PURPLE   "\033[0;35m"

// padded tag t
#define PRINT_TAG(tag) do { \
    char tag_buf[32]; \
    snprintf(tag_buf, sizeof(tag_buf), "<%s>", tag); \
    printf(COLOR_WHITE TAG_SIZE, tag_buf); \
} while(0)

// Log an information (regular) 
#define LOG_INFO(tag, format, ...)    do { PRINT_TAG(tag); printf(COLOR_WHITE " [INFO]: " format COLOR_RESET "\n", ##__VA_ARGS__); } while(0)
// Log a debug message, for debugging purposes (purple)
#define LOG_DEBUG(tag, format, ...)   do { PRINT_TAG(tag); printf(COLOR_PURPLE " [DEBUG]: " format COLOR_RESET "\n", ##__VA_ARGS__); } while(0)
// Log a success message (green)
#define LOG_SUCCESS(tag, format, ...) do { PRINT_TAG(tag); printf(COLOR_GREEN " [OK]: " format COLOR_RESET "\n", ##__VA_ARGS__); } while(0)
// Log a warning message (yellow)
#define LOG_WARNING(tag, format, ...) do { PRINT_TAG(tag); printf(COLOR_YELLOW " [WARN]: " format COLOR_RESET "\n", ##__VA_ARGS__); } while(0)
// Log an error message (red)
#define LOG_ERROR(tag, format, ...)   do { PRINT_TAG(tag); printf(COLOR_RED " [ERROR]: " format COLOR_RESET "\n", ##__VA_ARGS__); } while(0)
