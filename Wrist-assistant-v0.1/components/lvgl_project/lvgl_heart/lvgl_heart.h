#ifndef __lvgl_heart_H__
#define __lvgl_heart_H__

#include "lvgl.h"
#include "lvgl_Project.h"
#include "my_system.h"

#if 1
#define heart_debug(format, ...) lvgl_project_debug("[heart_page]- ",format,##__VA_ARGS__);
#else
#define heart_debug(format, ...) ;
#endif

#define heart_Button_Num 3
#define heart_event_anXia 100

#define  heart_zuo_you_bmp_y 135



typedef struct
{


	lv_anim_t lv_anim_jin;


	lv_task_t * lvgl_task;

	lv_anim_t lv_anim_zuo_image_jin;
	lv_anim_t lv_anim_zuo_image_shangxia;


	lv_anim_t lv_anim_you_image_jin;
	lv_anim_t lv_anim_you_image_shangxia;


	lv_anim_t lv_anim_yezi_image;



	lv_obj_t *lvgl_tou_image;
	lv_obj_t *lvgl_tou_qian_image;
	lv_obj_t *lvgl_qian_image;
	lv_obj_t *lvgl_zuo_image;
	lv_obj_t *lvgl_you_image;
	lv_obj_t *lvgl_logo_image;
	lv_obj_t *lvgl_yezi_image;

	//粉丝
	lv_obj_t *lvgl_cont_fensi;
	lv_obj_t *lvgl_Label_biaoti_fensi;
	lv_obj_t *lvgl_Label_fensi;

	//播放
	lv_obj_t *lvgl_cont_bofang;
	lv_obj_t *lvgl_Label_biaoti_bofang;
	lv_obj_t *lvgl_Label_bofang;

	//关注
	lv_obj_t *lvgl_cont_guanzhu;
	lv_obj_t *lvgl_Label_biaoti_guanzhu;
	lv_obj_t *lvgl_Label_guanzhu;



} _heart_ChuangKou;

extern  _heart_ChuangKou heart_ChuangKou;
typedef struct
{
	char buf[20];

	int ShuaXin_Sta;
	int AnXia_Num;//按下的按钮编号
	lv_obj_t *AnXia_button;//按下的按钮句柄

	int DongHua_Flag;

	lv_point_t point;


}_lvgl_heart_GongNeng_Data;

extern _lvgl_heart_GongNeng_Data lvgl_heart_GongNeng_Data;


extern lv_obj_t *lvgl_heart_main_cont;

void lvgl_heart_create(lv_obj_t * Fu);
void lvgl_heart_close(int);
void lvgl_heart_closed(void);
void lvgl_heart_TaskCb(lv_task_t *t);
void lvgl_heart_shuaxin_kaishi(void);
void lvgl_heart_shuaxin_jieshu(void);


void lvgl_heart_Set_heart_rate(char *str);
void lvgl_heart_Set_blood_oxygen(char *str);
void lvgl_heart_Set_steps(char *str);



#endif


