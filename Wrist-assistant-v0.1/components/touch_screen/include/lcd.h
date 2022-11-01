
//#pragma once

#ifndef __lcd_h__
#define __lcd_h__


#include <stdio.h>
#include <string.h>

#include "driver/spi_master.h"
#include "driver/gpio.h"

#include "esp_err.h"
#include "esp_log.h"
#include "esp_system.h"

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#include "bsp_board.h"

#ifdef __cplusplus
extern "C" {
#endif

/*!< SPI host DMA Channel */
#define DMA_CHAN	    SPI_DMA_CH_AUTO
#define USE_HORIZONTAL  0  //设置横屏或者竖屏显示 0或1为竖屏 2或3为横屏

typedef struct {
    uint8_t cmd;        /*!< Command */
    uint8_t data_len;   /*!< Length of data */
    uint8_t data[16];   /*!< Data array */
} lcd_init_cmd_t;

esp_err_t lcd_init(spi_host_device_t spi_host_device, int clock_speed);

esp_err_t lcd_flush_area(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint8_t *data);

#ifdef __cplusplus
}   /*!< extern "C" { */
#endif


#endif
