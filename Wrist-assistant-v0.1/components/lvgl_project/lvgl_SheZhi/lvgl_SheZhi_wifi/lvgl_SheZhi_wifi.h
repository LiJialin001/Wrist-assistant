#ifndef __LVGL_SheZhi_wifi_H__
#define __LVGL_SheZhi_wifi_H__


#include "lvgl_Project.h"
#include "main.h"
#include "my_system.h"


#if 1
  #define SheZhi_wifi_debug(format, ...) lvgl_project_debug("[设置-wifi]- ",format,##__VA_ARGS__);


#else
	#define SheZhi_wifi_debug(format, ...) ;
#endif

#define SheZhi_wifi_Button_Num 20//WIFI_SCAN_LIST_SIZE

#define SheZhi_wifi_event_anXia 100

#define SheZhi_wifi_Color_weianxia	0X282828
#define SheZhi_wifi_Color_anxia		0X161616
#define SheZhi_wifi_item_height 45







typedef struct
{


	lv_obj_t *lvgl_btn_DongHua;
	lv_style_t lvgl_btn_DongHua_style;
	lv_anim_t lv_DongHua_anim;
	lv_area_t lv_DongHua_area;

	lv_anim_t lv_XiaLa_anim;
	lv_anim_t lv_ShangLa_anim;

	lv_anim_t lv_anim_btn_item_jin[SheZhi_wifi_Button_Num];
	lv_anim_t lv_anim_btn_item_chu[SheZhi_wifi_Button_Num];

	lv_obj_t *btn_BiaoTi_style;
	lv_obj_t *btn_BiaoTi;
	lv_obj_t *label_BiaoTi;
	lv_style_t label_BiaoTi_style;


}_SheZhi_wifi_ChuangKou;

extern _SheZhi_wifi_ChuangKou SheZhi_wifi_ChuangKou;
typedef struct
{
	char buf[100];

	int ShuaXin_Sta;

	int DongHua_KaiShiZhi;//动画开始时初始值
	int DongHua_Flag;//进入应用时动画是否结束标志位
	int AnXia_Num;//按下的按钮

	lv_obj_t *AnXia_button;

	lv_point_t point;

	uint32_t color;
	uint32_t anxia_color;

	int wifi_lianjie_flag;
	int wifi_dangqian_num;

}_lvgl_SheZhi_wifi_GongNeng_Data;

extern _lvgl_SheZhi_wifi_GongNeng_Data lvgl_SheZhi_wifi_GongNeng_Data;


void lvgl_SheZhi_wifi_create(lv_obj_t * Fu, lv_obj_t *btn, uint32_t color, uint32_t anxia_color, char *str, void *usr);

void lvgl_SheZhi_wifi_close(void);
void lvgl_SheZhi_wifi_TaskCb(lv_task_t *t);
void lvgl_SheZhi_wifi_anim_btn_item_jin(void);
void lvgl_SheZhi_wifi_anim_btn_item_chu(void);
void lvgl_SheZhi_wifi_DongHua_Chu(void);
void lvgl_SheZhi_wifi_XiaLa_Jin(void);
void lvgl_SheZhi_wifi_ShuaXin_KaiShi(void);
void lvgl_SheZhi_wifi_ShuaXin_jieshu(void);


#endif
