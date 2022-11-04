#ifndef __lvgl_Project_H__
#define __lvgl_Project_H__

#include "stdio.h"
#include "string.h"
#include "main.h"
#include "math.h"
#include "font.h"

#include "lvgl.h"
#include "lvgl_port.h"
#include "lv_gif.h"
#include "lv_png.h"
#include "my_system.h"

#include "bmp_tianqi_40x40.h"
#include "bmp_tianqi_80x80.h"
#include "bmp_ShuaXin.h"

#include "lvgl_bpm.h"
#include "lvgl_hint.h"
#include "lvgl_style.h"
#include "lvgl_global.h"
#include "lvgl_clock.h"
#include "lvgl_ShuaXin.h"
#include "lvgl_TianQi.h"


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
