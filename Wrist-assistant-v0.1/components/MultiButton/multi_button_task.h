#ifndef __multi_button_task_H__
#define __multi_button_task_H__

#include "main.h"


#if 1
#define multi_button_task_debug(format, ... ) my_debug("[multi_button_task]:",format,##__VA_ARGS__);
#else
#define multi_button_task_debug(format, ...) ;
#endif

esp_err_t multi_button_task_init(void);

#endif
