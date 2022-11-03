#ifndef __lvgl_tishi_H__
#define __lvgl_tishi_H__

#include "lvgl.h"
#include "lvgl_Project.h"
#include "my_system.h"

#if 0
#define tishi_debug(format, ...) lvgl_project_debug("[提示]- ",format,##__VA_ARGS__);
#else
#define tishi_debug(format, ...) ;
#endif

#define tishi_Button_Num 3
#define tishi_event_anXia 100
#define  tishi_zuo_you_bmp_y 135



typedef struct
{


	lv_anim_t lv_anim_jin;
	lv_anim_t lv_anim_chu;

	lv_task_t * lvgl_task;

	lv_obj_t * lvgl_Label_text;
	lv_obj_t * lvgl_btn_tuichu;


}_tishi_ChuangKou;

extern _tishi_ChuangKou tishi_ChuangKou;
typedef struct
{
	char buf[20];

	int shijian;
	int DongHua_Flag;

	lv_point_t point;
	uint8_t delete_flag;

}_lvgl_tishi_GongNeng_Data;

extern _lvgl_tishi_GongNeng_Data lvgl_tishi_GongNeng_Data;


extern lv_obj_t *lvgl_tishi_main_cont;

void lvgl_hint_create(lv_obj_t * Fu, char *text, uint8_t touming, uint8_t shijian);
void lvgl_tishi_close(void);
void lvgl_tishi_TaskCb(lv_task_t *t);


#endif


