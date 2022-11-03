#ifndef __lvgl_tishi_anim_H__
#define __lvgl_tishi_anim_H__

#include "lvgl.h"
#include "lvgl_Project.h"
#include "my_system.h"

#if 1
#define lvgl_tishi_anim_debug(format, ...) lvgl_project_debug("[提示-动效]- ",format,##__VA_ARGS__);
#else
#define lvgl_tishi_anim_debug(format, ...) ;
#endif


void lvgl_tishi_anim_Jin(void);
void lvgl_tishi_anim_chu(void);


#endif


