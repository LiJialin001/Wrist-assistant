#ifndef __lvgl_Project_H__
#define __lvgl_Project_H__

#include "stdio.h"
#include "string.h"
#include "main.h"
#include "math.h"



#include "lvgl.h"
#include "lv_gif.h"
#include "lv_png.h"

#include "lvgl_global.h"

#include "lvgl_bpm.h"
#include "lvgl_style.h"


#define win32 0

#if 1
#define lvgl_project_debug( tag, format, ... ) \
ESP_LOGW(tag," %s:%d",__FILE__, __LINE__); \
printf(format,##__VA_ARGS__);
#else
#define lvgl_project_debug( tag, format, ... ) ;
#endif

#define lvgl_event_anXia 100 //自定义回调函数中的事件

typedef enum {
	type_btn = 0,
	type_lable,
	type_sw,
}lvgl_obj_type;

extern const char * lvgl_globa_text[][10];

#endif
