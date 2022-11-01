#ifndef __bsp_i2c_h__
#define __bsp_i2c_h__

#include "driver/i2c.h"
#include "bsp_board.h"
#include "main.h"

#if 1
#define bsp_i2c_debug(format, ...) my_debug("[bsp-i2c]- ",format,##__VA_ARGS__);
#else
#define bsp_i2c_debug(format, ...) ;
#endif

#define I2C_MASTER_FREQ_HZ          400000                     /*!< I2C master clock frequency */
#define I2C_MASTER_TX_BUF_DISABLE   0                          /*!< I2C master doesn't need buffer */
#define I2C_MASTER_RX_BUF_DISABLE   0                          /*!< I2C master doesn't need buffer */
#define I2C_MASTER_TIMEOUT_MS       1000




void i2c2_init(void);
void i2c2_uninit(void);


#endif
