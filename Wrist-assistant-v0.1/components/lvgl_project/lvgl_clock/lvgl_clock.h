#ifndef __LVGL_clock_H__
#define __LVGL_clock_H__

#include "lvgl.h"

#if 1
#define clock_debug(format, ...) lvgl_project_debug("[主界面]- ",format,##__VA_ARGS__);
#else
#define clock_debug(format, ...) ;
#endif


typedef struct
{
	lv_obj_t *lvgl_Lucy;

	lv_anim_t lv_anim;

	lv_anim_t lv_anim_Shi;
	lv_anim_t lv_anim_Fen;
	lv_anim_t lv_anim_Miao;

	lv_anim_t lv_anim_Shi_Zou;
	lv_anim_t lv_anim_Fen_Zou;
	lv_anim_t lv_anim_Miao_Zou;


}_clock_ChuangKou;

_clock_ChuangKou clock_ChuangKou;

typedef struct
{
	int Shi;
	int Fen;
	int Miao;
	int Nian;
	int Yue;
	int Ri;
	float Angle_Shi;
	float Angle_Fen;
	float Angle_Miao;


}_clock_Data;

extern _clock_Data clock_Data;


void lvgl_clock_create(lv_obj_t * Fu);
void lvgl_clock_close(int dire);   // dire 0:左 1:右 2:向上 
void lvgl_clock_hidden(void);
void clock_TaskCb(lv_task_t *t);
void clock_anim_DongHua_Jin(void);
void clock_anim_Jin_cb(void * arc, lv_anim_value_t v);
void clock_anim_Chu_cb(void * arc, lv_anim_value_t v);
void clock_anim_Jin_ready_cb(lv_anim_t * anim);
void clock_anim_Chu_ready_cb(lv_anim_t * anim);

void clock_anim_Shi_cb(void * arc, lv_anim_value_t v);
void clock_anim_Fen_cb(void * arc, lv_anim_value_t v);
void clock_anim_Miao_cb(void * arc, lv_anim_value_t v);
void clock_anim_Miao_ready_cb(lv_anim_t * anim);

void clock_anim_Miao_Zou_cb(void * arc, lv_anim_value_t v);
void clock_anim_ShiJian_Zou_Init(void);
void clock_anim_Miao_Zou(int dat);
#endif
