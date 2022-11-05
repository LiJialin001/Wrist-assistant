#ifndef __lvgl_shurufa_anim_H__
#define __lvgl_shurufa_anim_H__

#include "lvgl.h"
#include "lvgl_Project.h"
#include "my_system.h"

#if 1
#define lvgl_shurufa_anim_debug(format, ...) lvgl_project_debug("[输入法-动效]- ",format,##__VA_ARGS__);
#else
#define lvgl_shurufa_anim_debug(format, ...) ;
#endif


void lvgl_shurufa_anim_Jin(void);
void lvgl_shurufa_anim_chu(void);


#endif


