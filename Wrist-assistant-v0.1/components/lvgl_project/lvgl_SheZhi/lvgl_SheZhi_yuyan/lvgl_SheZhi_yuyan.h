#ifndef __LVGL_SheZhi_yuyan_H__
#define __LVGL_SheZhi_yuyan_H__

#include "lvgl.h"
#include "lvgl_Project.h"
#include "my_system.h"

#if 1
  #define SheZhi_yuyan_debug(format, ...) lvgl_project_debug("[设置-语言]- ",format,##__VA_ARGS__);

#else
#define SheZhi_yuyan_debug(format, ...) ;
#endif

#define SheZhi_yuyan_Button_Num 3
#define SheZhi_yuyan_event_anXia 100

#define SheZhi_yuyan_Color_weianxia	0X282828
#define SheZhi_yuyan_Color_anxia	0X161616
#define SheZhi_yuyan_item_height 45



typedef struct
{


	lv_anim_t lv_XiaLa_anim;
	lv_anim_t lv_XuanZhong_anim;

	lv_style_t *btn_XuanZhong_style;
	lv_obj_t *btn_XuanZhong;

	lv_style_t *btn_BiaoTi_style;
	lv_obj_t *btn_BiaoTi;
	lv_obj_t *label_BiaoTi;
	lv_style_t label_BiaoTi_style;


}_SheZhi_yuyan_ChuangKou;

extern _SheZhi_yuyan_ChuangKou SheZhi_yuyan_ChuangKou;
typedef struct
{
	char buf[20];


	int AnXia_Num;//按下的按钮编号
	lv_obj_t *AnXia_button;//按下的按钮句柄

	int DongHua_Flag;

	lv_point_t point;


}_lvgl_SheZhi_yuyan_GongNeng_Data;

extern _lvgl_SheZhi_yuyan_GongNeng_Data lvgl_SheZhi_yuyan_GongNeng_Data;
extern lv_obj_t *lvgl_SheZhi_yuyan_main_cont;

void lvgl_SheZhi_yuyan_create(lv_obj_t * Fu, lv_obj_t *btn, lv_style_t*style, char *str, void *usr);
void lvgl_SheZhi_yuyan_close(void);
void lvgl_SheZhi_yuyan_TaskCb(lv_task_t *t);
const char * lvgl_SheZhi_yuyan_get_zhuangtai_str(void);


void lvgl_SheZhi_yuyan_XiaLa_Jin(void);
void lvgl_SheZhi_yuyan_XuanZhong(lv_obj_t *btn_XuanZhong);
#endif
