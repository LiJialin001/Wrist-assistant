
#include <stdio.h>
#include "esp_log.h"
#include "driver/i2c.h"

#include "bsp_i2c.h"



// static esp_err_t i2c2_read_bytes(uint8_t device_addr,uint8_t reg_addr, uint8_t *data, size_t len)
// {
//     return i2c_master_write_read_device(I2C_PORT_NUM_TP, device_addr, &reg_addr, 1, data, len, I2C_MASTER_TIMEOUT_MS / portTICK_PERIOD_MS);
// }


// static esp_err_t i2c2_write_bytes(uint8_t device_addr,uint8_t reg_addr, uint8_t data)
// {
//     // int ret;
//     // uint8_t write_buf[2] = {reg_addr, data};

//     // ret = i2c_master_write_to_device(I2C_PORT_NUM_TP, device_addr, write_buf, sizeof(write_buf), I2C_MASTER_TIMEOUT_MS / portTICK_PERIOD_MS);

//     // return ret;

//     return i2c_master_write_read_device(I2C_PORT_NUM_TP, device_addr, &reg_addr, 1, data, len, I2C_MASTER_TIMEOUT_MS / portTICK_PERIOD_MS);


// }


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
    uint8_t buf[]={0xA7,0X00};
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




