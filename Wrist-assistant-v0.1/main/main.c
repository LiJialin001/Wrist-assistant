#include "main.h"

static void init_task_handler(void *pvParameters)
{
	main_debug("-------------开始初始化----------------\r\n");
	main_debug("编译时间:%s %s\r\n", __DATE__, __TIME__);
	main_debug("esp32 sdk version :%s\r\n", esp_get_idf_version());

	// bsp_key_init();

#if 0 //测试用
	gpio_set_direction(IO_POWER_PIN, GPIO_MODE_OUTPUT);
	gpio_set_direction(IO_LCD_BL_PIN, GPIO_MODE_OUTPUT);
	gpio_set_level(IO_LCD_BL_PIN, 0);

	uint32_t key_press_count=0;
	while(1)
	{
		main_debug("开机计数:%d",key_press_count);
		bsp_power_off();
		if(bsp_key_read_power_gpio())
		{
			if(++key_press_count > 5)
			{
				main_debug("按键开机");
				break;
			}
		}else
		{
			main_debug("进入休眠");
			gpio_set_level(IO_POWER_PIN, 1);
			bsp_power_sleep();
			key_press_count = 0;
		}

		vTaskDelay(pdMS_TO_TICKS(100));
	}
#endif

	main_debug("初始化结束\r\n");

	while(1)
	{
		vTaskDelay(100 / portTICK_PERIOD_MS);
	}

	vTaskDelete(NULL);

}
void app_main()
{

  xTaskCreate(init_task_handler,
              "init_task_handler",
              1024 * 10,
              NULL,
              configMAX_PRIORITIES-1,
              NULL);
}

void ptintf_memory(char *file,int len)
{
    int free_size;

    ESP_LOGW("内存监控", "%s:%d",file,len);
    free_size = heap_caps_get_free_size(MALLOC_CAP_INTERNAL);
    printf("内部RAM剩余%d.%dKB  ", free_size/1024,free_size%1024);
    free_size = heap_caps_get_free_size(MALLOC_CAP_SPIRAM);
    printf("外部PSRAM剩余%d.%dkB\r\n",free_size/1024,free_size%1024);
}
