#ifndef __https_kongqi__
#define __https_kongqi__

#include "stdio.h"
#include "stdint.h"

#if 0
  #define kongqi_debug(format, ...)  my_debug("[https空气]- ",format,##__VA_ARGS__);
#else
  #define kongqi_debug(format, ...)  ;
#endif

typedef struct
{
    char aqi[10]; //空气质量指数(AQI)是描述空气质量状况的定量指数
    char pm25[10]; //PM2.5颗粒物（粒径小于等于2.5μm）1小时平均值。单位：μg/m³
    char pm10[10]; //PM10颗粒物（粒径小于等于10μm）1小时平均值。单位：μg/m³
    char so2[10]; //二氧化硫1小时平均值。单位：μg/m³
    char no2[10]; //二氧化氮1小时平均值。单位：μg/m³
    char co[10]; //一氧化碳1小时平均值。单位：mg/m³
    char o3[10]; //臭氧1小时平均值。单位：μg/m³
    char primary_pollutant[10]; //首要污染物
    char quality[10]; //空气质量类别，有“优、良、轻度污染、中度污染、重度污染、严重污染”6类
    char last_update[30]; //数据发布时间
}_kongqi_Data;

int https_get_kongqi(void);
int HTTP_Get_KongQi(char * city_name_buf,_kongqi_Data  *read_buf);

#endif
