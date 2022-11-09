
#include <stdio.h>
#include "esp_log.h"
#include "driver/i2c.h"

#include "bsp_i2c.h"



static esp_err_t i2c_mpu6050_master_init(void)
{
    i2c_config_t conf = {
        .mode = I2C_MODE_MASTER,
        .sda_io_num = MPU6050_I2C_SDA,         // select GPIO specific to your project
        .scl_io_num = MPU6050_I2C_SCL,         // select GPIO specific to your project
        .sda_pullup_en = GPIO_PULLUP_ENABLE,
        .scl_pullup_en = GPIO_PULLUP_ENABLE,
        .master.clk_speed = MPU6050_I2C_FREQ,  // select frequency specific to your project
        // .clk_flags = 0,          /*!< Optional, you can use I2C_SCLK_SRC_FLAG_* flags to choose i2c source clock here. */
    };
    
    i2c_param_config(MPU6050_I2C_PORT_NUM, &conf);

    return i2c_driver_install(MPU6050_I2C_PORT_NUM, I2C_MODE_MASTER, 0, 0, 0);
}

void i2c_mpu_bpm_uninit(void)
{
    ESP_ERROR_CHECK(i2c_driver_delete(MPU6050_I2C_PORT_NUM));
    bsp_i2c_debug("I2C mup bpm de-initialized successfully");
}


static esp_err_t i2c_bpm_master_init(void)
{
    int i2c_port = I2C_PORT_NUM_BPM;
    i2c_config_t conf = {};
    conf.mode = I2C_MODE_MASTER;
    conf.sda_io_num = GPIO_BPM_I2C_SDA;
    conf.scl_io_num = GPIO_BPM_I2C_SCL;
    conf.sda_pullup_en = GPIO_PULLUP_ENABLE;
    conf.scl_pullup_en = GPIO_PULLUP_ENABLE;
    conf.master.clk_speed = I2C_FRQ;
    i2c_param_config(i2c_port, &conf);
    return i2c_driver_install(i2c_port, I2C_MODE_MASTER, 0, 0, 0);
}


static esp_err_t i2c2_master_init(void)
{
    int i2c_master_port = I2C_PORT_NUM_TP;

    i2c_config_t conf = {
        .mode = I2C_MODE_MASTER,
        .sda_io_num = GPIO_TP_I2C_SDA,
        .scl_io_num = GPIO_TP_I2C_SCL,
        .sda_pullup_en = GPIO_PULLUP_DISABLE,
        .scl_pullup_en = GPIO_PULLUP_DISABLE,
        .master.clk_speed = I2C_MASTER_FREQ_HZ,
    };

    i2c_param_config(i2c_master_port, &conf);

    return i2c_driver_install(i2c_master_port, conf.mode, I2C_MASTER_RX_BUF_DISABLE, I2C_MASTER_TX_BUF_DISABLE, 0);
}

void bsp_i2c_test_task(void *pvParameter)
{


    uint8_t dummy;
    uint8_t data=0XA7;
    // uint8_t buf[]={0xA7,0X00};
    uint8_t i=0;

    // i2c_read(twiAddress, 0x15, &dummy, 1);
    // vTaskDelay(5);
    // i2c_read(twiAddress, 0xa7, &dummy, 1);
    // vTaskDelay(5);
    //for(int i=0;i<0xff;i++)
    i=0x15;
    while(1)
    {
        //for(i=0;i<0xff;i++])
        {
            if(i2c_master_write_read_device(I2C_PORT_NUM_TP, i, &data, 1, &dummy, 1, I2C_MASTER_TIMEOUT_MS / portTICK_PERIOD_MS)==ESP_OK)
            {
                bsp_i2c_debug("成功 地址:0x%02x 数据:0x%02x \r\n",i,dummy);
            }else
            {
                bsp_i2c_debug("失败 地址:0x%02x 数据:0x%02x \r\n",i,dummy);
            }
            vTaskDelay(1000 / portTICK_PERIOD_MS);
        }

    }

	vTaskDelete(NULL);
}

void i2c_bpm_init(void)
{
    if(i2c_bpm_master_init()==ESP_OK)
    {
        bsp_i2c_debug("i2c_bpm初始化成功\r\n");
        //xTaskCreate(bsp_i2c_test_task,"bsp_i2c_test_task",1024*5,NULL,12,NULL);
    }else
    {
        bsp_i2c_debug("i2c_bpm初始化失败\r\n");
    }

}

void i2c_mpu6050_init(void)
{
    if(i2c_mpu6050_master_init()==ESP_OK)
    {
        bsp_i2c_debug("i2c_mpu6050初始化成功\r\n");
        //xTaskCreate(bsp_i2c_test_task,"bsp_i2c_test_task",1024*5,NULL,12,NULL);
    }else
    {
        bsp_i2c_debug("i2c_mpu6050初始化失败\r\n");
    }

}

void i2c2_init(void)
{
    if(i2c2_master_init()==ESP_OK)
    {
        bsp_i2c_debug("i2c2初始化成功\r\n");
        //xTaskCreate(bsp_i2c_test_task,"bsp_i2c_test_task",1024*5,NULL,12,NULL);
    }else
    {
        bsp_i2c_debug("i2c2初始化失败\r\n");
    }

}
void i2c2_uninit(void)
{
    ESP_ERROR_CHECK(i2c_driver_delete(I2C_PORT_NUM_TP));
    bsp_i2c_debug("I2C de-initialized successfully");
}




