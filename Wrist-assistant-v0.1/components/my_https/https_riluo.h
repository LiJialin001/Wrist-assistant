#ifndef __https_riluo__
#define __https_riluo__

#include "stdio.h"
#include "stdint.h"

#if 1
  #define riluo_debug(format, ...)  my_debug("[https日落]- ",format,##__VA_ARGS__);
#else
  #define riluo_debug(format, ...)  ;
#endif

typedef struct
{
	char date[20];         //日期
  char sunrise[10];      //日出时间
  char sunset[10];       //日落时间
}_RiLuo_Data;

int https_get_riluo(void);
int HTTP_Get_RiLuo(char * city_name_buf,_RiLuo_Data  read_buf[3]);

#endif
