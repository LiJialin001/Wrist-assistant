#ifndef __lvgl_chulizhong_H__
#define __lvgl_chulizhong_H__

#include "lvgl.h"
#include "lvgl_Project.h"


#if 1
  #define chulizhong_debug(format, args...) \
  ESP_LOGW("[加载中]]- "," %s:%d",__FILE__, __LINE__);\
  printf(format, ## args );
#else
#define chulizhong_debug(format, args...) ;
#endif


#define lvgl_chulizhong_x 70
#define lvgl_chulizhong_y 70
#define lvgl_chulizhong_xsize 100
#define lvgl_chulizhong_ysize 100

typedef struct
{

	lv_anim_t lv_anim_jin;
	lv_anim_t lv_anim_chu;
	lv_task_t * lvgl_task;
	lv_task_t * lv_lable_tishi;

	lv_task_t * lv_preload;


	lv_style_t lv_preload_SPINNING_style;
	lv_style_t lv_preload_FILLSPIN_style;
	lv_style_t lv_kb_style;


}_lvgl_chulizhong_ChuangKou;

extern _lvgl_chulizhong_ChuangKou lvgl_chulizhong_ChuangKou;
typedef struct
{
	char buf[20];

	int ShuaXin_Sta;
	int AnXia_Num;//按下的按钮编号
	lv_obj_t *AnXia_button;//按下的按钮句柄

	int DongHua_Flag;

	lv_point_t point;

	char shuru_text[52];
	char shuchu_text[52];

	void(*cb)(char * text, void *dat);

	int guanbi_flag;


}_lvgl_chulizhong_GongNeng_Data;

extern _lvgl_chulizhong_GongNeng_Data lvgl_chulizhong_GongNeng_Data;


extern lv_obj_t *lvgl_chulizhong_main_cont;

void lvgl_chulizhong_create(lv_obj_t * Fu, char *tishi, uint32_t color, uint32_t anxia_color, void(*cb)(char * text, void *dat));
void lvgl_chulizhong_close(void);
void lvgl_chulizhong_closed(void);
void lvgl_chulizhong_TaskCb(lv_task_t *t);


#endif


