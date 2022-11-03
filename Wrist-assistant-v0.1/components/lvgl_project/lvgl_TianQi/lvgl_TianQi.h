#ifndef __LVGL_TianQi_H__
#define __LVGL_TianQi_H__

#include "lvgl_Project.h"

#define lvgl_TianQi_ShuaXin_GaoDu 61

#if 1
#define TianQi_debug(format, ...) lvgl_project_debug("[天气]- ",format,##__VA_ARGS__);
#else
#define TianQi_debug(format, ...) ;
#endif

enum {
	lvgl_TianQi_ShuaXin_JieShu=0,
	lvgl_TianQi_ShuaXin_KaiShi,
	lvgl_TianQi_ShuaXin_Zhong,


}lvgl_TianQi_ShuaXin_Sta;

typedef struct
{
	int ShuaXin_Sta;
	int DongHua_Sta;
	lv_anim_t lv_anim_JinTian;
	int JinTian_y;
	lv_anim_t lv_anim_MingTian;
	int MingTian_y;
	lv_anim_t lv_anim_HouTian;
	int HouTian_y;

	lv_anim_t lv_anim_FengSu;
	lv_anim_t lv_anim_FengXiang;
	lv_anim_t lv_anim_JiangShui;
	lv_anim_t lv_anim_ShiDu;


	lv_anim_t lv_anim_DangTian;


	lv_anim_t lv_anim_RiQi;
	lv_anim_t lv_anim_ShiJian;
	lv_anim_t lv_anim_XingQi;


}_lvgl_TianQi_GongNeng_Data;

extern _lvgl_TianQi_GongNeng_Data lvgl_TianQi_GongNeng_Data;


void lvgl_TianQi_create(lv_obj_t * Fu);
void lvgl_TianQi_close(void);
void lvgl_TianQi_TaskCb(lv_task_t *t);
void lvgl_TianQi_Set_ChengShi(char *str);
void lvgl_TianQi_Set_ChengShi(char *str);
void lvgl_TianQi_Set_ShiJian(int shi, int fen, char *str);
void lvgl_TianQi_Set_RiQi(int nian,int yue,int ri, char *str);
void lvgl_TianQi_Set_XingQi(int dat);
void lvgl_TianQi_Set_WenDu(int dat);
void lvgl_TianQi_Set_DangTianQi(int sta,int num,int wendu,char *str,int min, int max);
void lvgl_TianQi_Set_TianQi_JinTian(int sta, int num,char *str,int min,int max);
void lvgl_TianQi_Set_TianQi_MingTian(int sta, int num, char *str, int min, int max);
void lvgl_TianQi_Set_TianQi_HouTian(int sta, int num, char *str, int min, int max);
void lvgl_TianQi_Set_FengSu(char *str);
void lvgl_TianQi_Set_FengXiang(char *str);
void lvgl_TianQi_Set_JiangShui(char *str);
void lvgl_TianQi_Set_ShiDu(char *str);
void lvgl_TianQi_Set_RiChuRiLuo(int richu_shi, int richu_fen, int riluo_shi, int riluo_fen,char *richu_str,char *riluo_str);

void lvgl_TianQi_shuaxin_kaishi(void);
void lvgl_TianQi_ShuaXin_jieshu(void);
void lvgl_TianQi_DongHua_Jin(void);
void lvgl_TianQi_DongHua_Chu(void);


#endif
