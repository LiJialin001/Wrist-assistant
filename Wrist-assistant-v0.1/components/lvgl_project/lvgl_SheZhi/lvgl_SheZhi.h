#ifndef __LVGL_SheZhi_H__
#define __LVGL_SheZhi_H__

#include "lvgl.h"
#include "lvgl_Project.h"


#if 1
#define SheZhi_debug(format, ...) lvgl_project_debug("[设置]- ",format,##__VA_ARGS__);
#else
#define SheZhi_debug(format, ...) ;
#endif



#define SheZhi_Button_Num 7

#define SheZhi_event_anXia 100

#define SheZhi_Color_weianxia	0X282828
#define SheZhi_Color_anxia		0X161616
#define SheZhi_item_height 45


typedef struct
{

	lv_anim_t lv_DongHua_anim;


	lv_anim_t lv_anim_Jin[SheZhi_Button_Num];
	lv_anim_t lv_anim_Chu[SheZhi_Button_Num];



	lv_obj_t *label_BiaoTi;
	lv_style_t label_BiaoTi_style;

	lv_obj_t * switch_wifi;
	lv_obj_t *label_wifi_zhuangtai;


	lv_obj_t *label_yuyan_zhuangtai;
	lv_obj_t *label_ip;

	lv_task_t * lvgl_task;


}_SheZhi_ChuangKou;

extern _SheZhi_ChuangKou SheZhi_ChuangKou;
typedef struct
{
	char buf[20];
	int image_cnt;

	int DongHua_KaiShiZhi;//动画开始时初始值
	int DongHua_Flag;//进入应用时动画是否结束标志位
	int AnXia_Num;//按下的按钮

	lv_obj_t *AnXia_button;


	lv_point_t point;


}_lvgl_SheZhi_GongNeng_Data;

extern _lvgl_SheZhi_GongNeng_Data lvgl_SheZhi_GongNeng_Data;

extern lv_obj_t *lvgl_SheZhi_main_cont;
extern lv_style_t lvgl_SheZhi_style;


extern lv_obj_t *lvgl_SheZhi_Button[SheZhi_Button_Num];
extern lv_obj_t *lvgl_SheZhi_Label[SheZhi_Button_Num];
extern lv_style_t lvgl_SheZhi_Button_style[SheZhi_Button_Num];


void lvgl_SheZhi_create(lv_obj_t * Fu);
void lvgl_SheZhi_close(void);
void lvgl_SheZhi_closed(void);
void lvgl_SheZhi_TaskCb(lv_task_t *t);
void lvgl_SheZhi_DongHua_Jin(void);
void lvgl_SheZhi_DongHua_Chu(void);




#endif
