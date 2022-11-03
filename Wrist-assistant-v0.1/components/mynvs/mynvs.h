#ifndef __my_nvs_H__
#define __my_nvs_H__
#include "main.h"


#if 1
#define my_nvs_debug(format, ...) my_debug("[my nvs]- ",format,##__VA_ARGS__);
#else
#define my_nvs_debug(format, ...) ;
#endif


esp_err_t nvs_init(void);
void  nvs_test_task(void *pvParameter);
esp_err_t nvs_set_wifi(char *wifi_name,char *wifi_password);
esp_err_t nvs_get_wifi(char *wifi_name,char *wifi_password);
#endif
