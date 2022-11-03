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

extern lv_style_t lvgl_font12_style;
extern lv_style_t lvgl_font16_style;
extern lv_style_t lvgl_font24_style;
extern lv_style_t lvgl_font_acsii_48_style;
extern lv_style_t lvgl_font_acsii_12_style;
extern lv_style_t lvgl_font_acsii_16_style;
extern lv_style_t lvgl_font_acsii_32_style;

extern lv_style_t lvgl_WuBianKuang_cont_style;
extern lv_style_t lvgl_ta_moren_style;		//文本输入默认样式
extern lv_style_t lvgl_touming_cont_style;//透明cont样式

void lvgl_Style_create(void);

#endif