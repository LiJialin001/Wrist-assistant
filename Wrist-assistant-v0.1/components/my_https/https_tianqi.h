#ifndef __https_tianqii__
#define __https_tianqii__

#include "stdio.h"
#include "stdint.h"

#if 0
  #define tianqii_debug(format, ...)  my_debug("[http天气]- ",format,##__VA_ARGS__);
#else
  #define tianqii_debug(format, ...)  ;
#endif

typedef struct
{
    char date[20];             		    //日期
    char text_day[20];                  //白天天气现象文字
    char code_day[20];                 //白天天气现象代码
    char text_night[20];                //晚间天气现象文字
    char code_night[20];                //晚间天气现象代码
    char high[20];                     //当天最高温度
    char low[20];                      //当天最低温度
    char precip[20];                    //降水概率，范围0~100，单位百分比（目前仅支持国外城市）
    char wind_direction[20];            //风向文字
    char wind_direction_degree[20];   //风向角度，范围0~360
    char wind_speed[20];             //风速，单位km/h（当unit=c时）、mph（当unit=f时）
    char wind_scale[20];                 //风力等级
    char rainfall[20];                //降水量，单位mm
    char humidity[20];                  //相对湿度，0~100，单位为百分比

}_Weather_Data;

int https_get_tianqi(void);
int HTTP_Get_TianQi(char * city_name_buf,_Weather_Data  read_buf[3]);

#endif
