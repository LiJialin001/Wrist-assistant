#ifndef __wifi_h_
#define __wifi_h_

#include "main.h"
#include "esp_event.h"

#if 1
#define WIFI_debug(format, ...) my_debug("[wifi]-",format,##__VA_ARGS__);
#else
#define WIFI_debug(format, ...) ;
#endif


typedef struct
{
  char buf[100];
  wifi_config_t wifi_config;
  void(*cb)(char * text, void *dat);


}_wifi_data;

extern _wifi_data wifi_data;

enum wifi_sta {
	wifi_weilianjie = 0,
	wifi_yilianjie,
	wifi_lianjiehzong,
	wifi_lianjieshibai,
  wifi_qingqiuduankai,
  wifi_yiduankai,
};


void wifi_init(void);
int wifi_scan_list_start(void);
int wifi_scan_list_get(void);
void wifi_lianjie(uint8_t mode,char *name, char *password, void(*cb)(char * text, void *dat));




#endif
