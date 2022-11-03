#ifndef __font_h_
#define __font_h_
#include "lvgl/lvgl.h"
#include "main.h"


#if 1
#define font_debug(format, ...) my_debug("[font]- ",format,##__VA_ARGS__);
#else
#define font_debug(format, ...) ;
#endif

#if 0
#define font_12_path "/spiffs/font_ChangYongHanZi_12.bin"
#define font_16_path "/spiffs/font_ChangYongHanZi_16.bin"
#define font_24_path "/spiffs/font_ChangYongHanZi_24.bin"
#else
#define font_12_path "/sdcard/system/font/font_ChangYongHanZi_12.bin"
#define font_16_path "/sdcard/system/font/font_ChangYongHanZi_16.bin"
#define font_24_path "/sdcard/system/font/font_ChangYongHanZi_24.bin"

#endif

typedef struct
{
    FILE *file_font_12;
    FILE *file_font_16;
    FILE *file_font_24;


}_font_data;


lv_font_t font_acsii_12;
lv_font_t font_acsii_16;
lv_font_t font_acsii_32;
lv_font_t font_acsii_48;
lv_font_t font_ChangYongHanZi_12;
lv_font_t font_ChangYongHanZi_16;
lv_font_t font_ChangYongHanZi_24;
lv_font_t font_ZiDing_K8_24;
lv_font_t font_ZiDing_K8_12;
lv_font_t font_ZiDing_K8_16;


uint8_t font_init(void);
uint8_t font_12_get_data(uint8_t * buf,int offset, int size);
uint8_t font_16_get_data(uint8_t * buf,int offset, int size);
uint8_t font_24_get_data(uint8_t * buf,int offset, int size);



#endif
