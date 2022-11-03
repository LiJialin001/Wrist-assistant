#ifndef __LVGL_ShuaXin_H__
#define __LVGL_ShuaXin_H__

#include "lvgl.h"

#if 1
  #define ShuaXin_debug(format, args...) \
  ESP_LOGW("[刷新]- "," %s:%d\r\n",__FILE__, __LINE__);\
  printf(format, ## args );
#else
  #define ShuaXin_debug(format, args...) ;
#endif

#define lvgl_ShuaXin_GaoDu 61

#define lvgl_shuaxin_jieshu_event 100



enum {
	lvgl_ShuaXin_JieShu = 0,
	lvgl_ShuaXin_KaiShi,
	lvgl_ShuaXin_Zhong,


}lvgl_ShuaXin_Sta;


typedef struct
{
	lv_anim_t lv_XiaLa_anim;
	lv_anim_t lv_ShangLa_anim;
}_ShuaXin_ChuangKou;

extern _ShuaXin_ChuangKou ShuaXin_ChuangKou;
typedef struct
{
	char buf[20];
	int image_cnt;
	lv_obj_t *fu;
	int zuhangtai_flag;

	int *usr_flag;


}_lvgl_ShuaXin_GongNeng_Data;

extern _lvgl_ShuaXin_GongNeng_Data lvgl_ShuaXin_GongNeng_Data;


void lvgl_ShuaXin_create(lv_obj_t * Fu);
void lvgl_ShuaXin_close(void);
void lvgl_ShuaXin_Start(lv_obj_t * Fu,int * dat,int time);
void lvgl_ShuaXin_Stop(void);
void ShuaXin_anim_DongHua_Jin(void);
void ShuaXin_anim_DongHua_Chu(void);


int lvgl_shuaxin_get_sta(void);

#endif
