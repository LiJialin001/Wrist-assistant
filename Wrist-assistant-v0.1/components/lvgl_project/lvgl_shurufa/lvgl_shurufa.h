#ifndef __lvgl_shurufa_H__
#define __lvgl_shurufa_H__

#include "lvgl.h"
#include "lvgl_Project.h"
#include "my_system.h"

#if 1
#define shurufa_debug(format, ...) lvgl_project_debug("[输入法]- ",format,##__VA_ARGS__);
#else
#define shurufa_debug(format, ...) ;
#endif

#define shurufa_Button_Num 3

#define lvgl_shuaxin_y lv_obj_get_height(lv_scr_act())-130

typedef struct
{

	lv_anim_t lv_anim_jin;
	lv_anim_t lv_anim_chu;
	lv_task_t * lvgl_task;
	lv_task_t * lv_ta_shuru;
	lv_task_t * lv_kb;

	lv_style_t lv_ta_shuru_style;
	lv_style_t lv_kb_style;




}_lvgl_shurufa_ChuangKou;

extern _lvgl_shurufa_ChuangKou lvgl_shurufa_ChuangKou;
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


}_lvgl_shurufa_GongNeng_Data;

extern _lvgl_shurufa_GongNeng_Data lvgl_shurufa_GongNeng_Data;


extern lv_obj_t *lvgl_shurufa_main_cont;

void lvgl_shurufa_create(lv_obj_t * Fu, lv_obj_t * source, char *tishi, int type, uint32_t color, uint32_t anxia_color, void(*cb)(char * text, void *dat));
void lvgl_shurufa_close(void);
void lvgl_shurufa_closed(void);
void lvgl_shurufa_TaskCb(lv_task_t *t);


#endif

