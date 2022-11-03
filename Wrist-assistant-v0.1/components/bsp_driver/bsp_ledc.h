#ifndef __bsp_ledc_h__
#define __bsp_ledc_h__

#include "stdint.h"
#include "stdio.h"

void bsp_ledc_init(void);
void bsp_ledc_set_duty(uint8_t dat);
#endif
