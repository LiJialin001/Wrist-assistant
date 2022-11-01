#ifndef __LVGL_style_H__
#define __LVGL_style_H__

#include "lvgl.h"

#define style_moren_bg LV_COLOR_MAKE(0x00, 0x00, 0x00)

typedef struct
{
	char buf[20];
	int image_cnt;
}_lvgl_Style_Func_Data;

extern _lvgl_Style_Func_Data lvgl_Style_Func_Data;

extern lv_style_t lvgl_WuBianKuang_cont_style;

void lvgl_Style_create(void);

#endif