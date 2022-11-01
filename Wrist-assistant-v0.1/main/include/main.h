#ifndef __main__h
#define __main__h

#include "stdint.h"
#include <stdio.h>
#include <math.h>
#include <os.h>
#include "nvs_flash.h"
#include "esp_spi_flash.h"
#include "esp_wifi.h"
#include "esp_event_loop.h"
#include "esp_log.h"
#include "esp_err.h"
#include <esp_log.h>
#include <arpa/inet.h>
#include "esp_wifi.h"
#include "driver/gpio.h"
#include "sdkconfig.h"
#include "freertos/task.h"
#include "driver/i2s.h"
#include "esp_system.h"
#include "cJSON.h"
#include "esp_timer.h"
#include "esp_event.h"
#include "driver/ledc.h"
#include "esp_spiffs.h"
#include "esp_sleep.h"

#include "freertos/FreeRTOS.h"
#include "freertos/event_groups.h"
#include "freertos/semphr.h"


#if 1
#define my_debug( tag, format, ... ) \
ESP_LOGW(tag," %s:%d",__FILE__, __LINE__); \
printf(format,##__VA_ARGS__);
#elif 1
#define my_debug( tag, format, ... ) \
ESP_LOGW(tag,""); \
printf(format,##__VA_ARGS__);
#else
#define my_debug( tag, format, ... ) ;
#endif


#if 1
#define main_debug(format, ...) my_debug("[main]- ",format,##__VA_ARGS__);
#else
#define main_debug(format, ...) ;
#endif

void ptintf_memory(char *file,int len);

#define printf_memory() ptintf_memory( __FILE__, __LINE__);

#endif
