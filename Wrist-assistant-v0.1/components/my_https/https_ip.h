#ifndef __https_ip__
#define __https_ip__

#include "stdio.h"
#include "stdint.h"

#if 1
  #define ip_debug(format, ...)  my_debug("[https ip]- ",format,##__VA_ARGS__);
#else
  #define ip_debug(format, ...)  ;
#endif


int https_get_ip(void);
int HTTP_Get_IP(char * read_buf);

#endif
