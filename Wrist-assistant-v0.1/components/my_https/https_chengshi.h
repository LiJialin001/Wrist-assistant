#ifndef __https_chengshi__
#define __https_chengshi__

#include "stdio.h"
#include "stdint.h"

#if 1
  #define chengshi_debug(format, ...)  my_debug("[https城市]- ",format,##__VA_ARGS__);
#else
  #define chengshi_debug(format, ...)  ;
#endif


int https_get_chengshi(void);
int HTTP_Get_ChengShi(char * ip_buf,char * read_buf);

#endif
