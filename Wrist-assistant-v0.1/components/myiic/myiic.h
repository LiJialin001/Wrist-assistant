#ifndef __my_iic_H__
#define __my_iic_H__
#include "main.h"

#define SDA_IN  gpio_set_direction(GPIO_BPM_I2C_SDA,GPIO_MODE_INPUT)
#define SDA_OUT  gpio_set_direction(GPIO_BPM_I2C_SDA,GPIO_MODE_OUTPUT)

#define SDA_H gpio_set_level(GPIO_BPM_I2C_SDA,1)
#define SDA_L gpio_set_level(GPIO_BPM_I2C_SDA,0)

#define SCL_H gpio_set_level(GPIO_BPM_I2C_SCL,1)
#define SCL_L gpio_set_level(GPIO_BPM_I2C_SCL,0)

#define SDAX gpio_get_level(GPIO_BPM_I2C_SDA)
#define SCLX gpio_get_level(GPIO_BPM_I2C_SCL)

#define I2C_ADDRESS     0x00
#define I2C_ADDRESS_R     0x00


void myiic_start(void);
void myiic_stop(void);
void waitack(void);
void noack(void);
void ack(void);
void write8bit(uint8_t data);
uint8_t read8bit(void);
void writebyte(uint8_t addr, uint8_t dat);
uint8_t readbyte(uint8_t addr);
void write_register(uint8_t addr, uint8_t dat);


#endif