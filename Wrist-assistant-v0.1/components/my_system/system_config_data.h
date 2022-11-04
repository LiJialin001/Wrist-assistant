#ifndef __system_config_data_H__
#define __system_config_data_H__


#include "main.h"
#include "lvgl_project.h"


#if 1
#define system_config_data_debug(format, ...) my_debug("[system config data]- ",format,##__VA_ARGS__);
#else
#define system_config_data_debug(format, ...) ;
#endif

typedef struct _system_wifi_data1
{

    char name[50];
    char password[20];
    char auto_connect[10];
    struct _system_wifi_data1 *next;

}_system_wifi_data;

extern _system_wifi_data *system_wifi_data;


uint8_t system_get_wifi_data(void);
_system_wifi_data* wifi_list_create(char * name,char *password,char *auto_connect);
void wifi_list_add_node_back(_system_wifi_data **pphead,char * name,char *password,char *auto_connect);
void wifi_list_add_node_front(_system_wifi_data **pphead,char * name,char *password,char *auto_connect);
void wifi_list_delete_node_back(_system_wifi_data **pphead);
void wifi_list_delete_node_front(_system_wifi_data **pphead);
void wifi_list_delete_node_name(_system_wifi_data **pphead,char * name);
_system_wifi_data * wifi_list_find_name(_system_wifi_data *phead, char * name);

#endif
