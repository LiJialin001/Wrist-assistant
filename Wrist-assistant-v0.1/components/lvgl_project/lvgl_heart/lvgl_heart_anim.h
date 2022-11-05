#ifndef __lvgl_heart_anim_H__
#define __lvgl_heart_anim_H__

#include "lvgl.h"
#include "lvgl_Project.h"
#include "my_system.h"

#if 1
#define lvgl_heart_anim_debug(format, ...) lvgl_project_debug("[哔哩哔哩-动效]- ",format,##__VA_ARGS__);
#else
#define lvgl_heart_anim_debug(format, ...) ;
#endif


void lvgl_heart_anim_Jin(void);
void lvgl_heart_anim_zuo_image_shangxia(int dat1, int dat2);
void lvgl_heart_anim_you_image_shangxia(int dat1, int dat2);
void lvgl_heart_anim_yezi_image(int dat1, int dat2);


#endif


