#ifndef __LVGL_SheZhi_yuyan_anim_H__
#define __LVGL_SheZhi_yuyan_anim_H__

#include "lvgl.h"
#include "lvgl_Project.h"


#if 1
  #define SheZhi_yuyan_anim_debug(format, ...) lvgl_project_debug("[设置-语言-动效]- ",format,##__VA_ARGS__);

#else
#define SheZhi_yuyan_anim_debug(format, ...) ;
#endif

void lvgl_SheZhi_yuyan_anim_XiaLa_Jin(void);
void lvgl_SheZhi_yuyan_anim_XuanZhong(lv_obj_t *btn_XuanZhong);

#endif


