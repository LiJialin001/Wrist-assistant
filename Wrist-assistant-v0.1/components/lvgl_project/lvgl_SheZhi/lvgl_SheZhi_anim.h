#ifndef __LVGL_SheZhi_anim_H__
#define __LVGL_SheZhi_anim_H__

#include "lvgl.h"
#include "lvgl_Project.h"

#if 1
#define SheZhi_anim_debug(format, ...) lvgl_project_debug("[设置-动效]- ",format,##__VA_ARGS__);
#else
#define SheZhi_anim_debug(format, ...) ;
#endif


void lvgl_SheZhi_DongHua_Jin(void);
void lvgl_SheZhi_DongHua_Chu(void);


#endif
