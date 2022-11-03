#ifndef __webserver__H__
#define __webserver__H__
#include "main.h"

#include "esp_http_server.h"

#if 1
#define webserver_debug(format, ...) my_debug("[webserver]-",format,##__VA_ARGS__);
#else
#define webserver_debug(format, ...) ;
#endif

httpd_handle_t  start_webserver(void);
void stop_webserver(void);

#endif
