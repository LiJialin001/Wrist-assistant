#include "cst816t.h"
#include "bsp_i2c.h"

uint8_t cst816t_read_len(uint16_t reg_addr,uint8_t *data,uint8_t len)
{
    uint8_t res=0;
    res = i2c_master_write_read_device(I2C_PORT_NUM_TP, CST816T_ADDR, &reg_addr, 1, data, len, 1000 / portTICK_PERIOD_MS);

    return res;
}


uint8_t cst816t_register_write_byte(uint8_t reg_addr, uint8_t data)
{
    int ret;
    uint8_t write_buf[2] = {reg_addr, data};

    ret = i2c_master_write_to_device(I2C_PORT_NUM_TP, CST816T_ADDR, write_buf, sizeof(write_buf), 1000 / portTICK_PERIOD_MS);

    return ret;
}


uint8_t cst816t_chipId(void)
{

    return 0;
}
static esp_err_t  cst816t_get_touch_points_num(uint8_t *touch_points_num)
{
    uint8_t res=0;
    res = cst816t_read_len(0x02, touch_points_num,1);
    return res;
}

esp_err_t cst816t_read_pos(uint8_t *touch_points_num, uint16_t *x, uint16_t *y)
{
    uint8_t data[4];

    cst816t_get_touch_points_num(touch_points_num);
    if (0 == *touch_points_num)
    {
        *x=0;
        *y=0;
        return 1;
    }else
    {
        cst816t_read_len(0x03, data,4);

        *x = ((data[0] & 0x0f) << 8) | data[1];
        *y = ((data[2] & 0x0f) << 8) | data[3];


    }

    return ESP_OK;
}


void cst816t_test_task(void *pvParameter)
{

    uint8_t res=0;

    uint8_t touch_points_num=0;
    uint16_t x=0;
    uint16_t y=0;
    while(1)
    {

        res = cst816t_read_pos(&touch_points_num,&x,&y);
        if(res==ESP_OK)
        {
            cst816t_debug("成功 点数:%d X:%d Y:%d \r\n",touch_points_num,x,y);
        }else
        {
            //cst816t_debug("失败 点数:%d X:%d Y:%d \r\n",touch_points_num,x,y);
        }

        vTaskDelay(pdMS_TO_TICKS(100));
    }

	vTaskDelete(NULL);
}







uint8_t cst816t_init(void)
{
    uint8_t buf[10];
    cst816t_read_len(0x15, buf,1);
    vTaskDelay(pdMS_TO_TICKS(10));
    cst816t_read_len(0xa7, buf,1);
    vTaskDelay(pdMS_TO_TICKS(10));
    //xTaskCreate(cst816t_test_task,"cst816t_test_task",1024*5,NULL,10,NULL);

    return 0;
}
