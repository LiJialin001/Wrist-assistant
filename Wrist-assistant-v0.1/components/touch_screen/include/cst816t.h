#ifndef __cst816t__h
#define __cst816t__h

#include "main.h"

#if 1
#define cst816t_debug(format, ...) my_debug("[ cst816t]- ",format,##__VA_ARGS__);
#else
#define cst816t_debug(format, ...) ;
#endif

#define CST816T_ADDR 0X15

uint8_t cst816t_init(void);

#endif
