#ifndef __LVGL_bpm_H__
#define __LVGL_bpm_H__

#include "lvgl.h"
#include "lvgl_Project.h"

#if 1
#define bpm_debug(format, ...) lvgl_project_debug("[bpm_page]-",format,##__VA_ARGS__);
#else
#define bpm_debug(format, ...) ;
#endif

#define bpm_event_anXia 100
#define bpm_lable_num 2

typedef struct
{
	lv_anim_t lv_DongHua_anim;
	lv_area_t lv_DongHua_area;

}_bpm_page;

extern _bpm_page bpm_page;

typedef struct
{
	char buf[20];
	int image_cnt; //图片数量

	int DongHua_KaiShiZhi;//动画开始时初始值
	int DongHua_Flag;//进入应用时动画是否结束标志位
	int AnXia_Num;//按下的按钮

	lv_obj_t *AnXia_button;
	lv_point_t point;
}_lvgl_bpm_Func_Data;

extern _lvgl_bpm_Func_Data lvgl_bpm_Func_Data;

void lvgl_bpm_create(lv_obj_t * Fu);
void lvgl_bpm_close(void);
void lvgl_bpm_event_cb(struct _lv_obj_t * obj, lv_event_t event);
void lvgl_bpm_hidden(void);
void lvgl_bpm_TaskCb(lv_task_t *t);

#endif