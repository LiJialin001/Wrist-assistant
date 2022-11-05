#ifndef __lvgl_chulizhong_anim_H__
#define __lvgl_chulizhong_anim_H__

#include "lvgl.h"
#include "lvgl_Project.h"


#if 1
  #define lvgl_chulizhong_anim_debug(format, ...) \
  ESP_LOGW("[加载中-动效]]- "," %s:%d",__FILE__, __LINE__);\
  printf(format,##__VA_ARGS__);
#else
#define lvgl_chulizhong_anim_debug(format, ...) ;
#endif


void lvgl_chulizhong_anim_Jin(void);
void lvgl_chulizhong_anim_chu(void);


#endif


