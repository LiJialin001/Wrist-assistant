#ifndef __multi_button_callback_H__
#define __multi_button_callback_H__

#include "main.h"


#if 1
#define multi_button_callback_debug(format, ... ) my_debug("[multi_button_callback]:",format,##__VA_ARGS__);
#else
#define multi_button_callback_debug(format, ...) ;
#endif

esp_err_t multi_button_callback_init(void);

void BTN_LONG_PRESS_HOLD_Handler(void* btn);
void BTN_LONG_PRESS_Handler(void* btn);
void BTN_PRESS_UP_Handler(void* btn);
void BTN_PRESS_DOWN_Handler(void* btn);

#endif
