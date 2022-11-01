#include "main.h"
#include "lvgl_project.h"

max30102_config_t max30102 = {};

// void get_bpm(void* param) {
//     printf("MAX30102 Test\n");
//     max30102_data_t result = {};
//     /*ESP_ERROR_CHECK(max30102_print_registers(&max30102));*/
//     while(true) {
//         //Update sensor, saving to "result"
//         ESP_ERROR_CHECK(max30102_update(&max30102, &result));
//         if(result.pulse_detected) {
//             printf("BEAT\n");
//             printf("BPM: %f | SpO2: %f%%\n", result.heart_bpm, result.spO2);
//         }
//         //Update rate: 100Hz
//         vTaskDelay(10/portTICK_PERIOD_MS);
//     }
// }

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

    i2c2_init();
	cst816t_init();
    lcd_init(SPI3_HOST, 80000000);
    lv_init();
    lvgl_Style_create();
    lvgl_bpm_create(lv_scr_act());

    //Init I2C_NUM_0
    i2c_bpm_init();
    //Init sensor at I2C_NUM_0
    if (max30102_init( &max30102, I2C_PORT_NUM_BPM,
                   MAX30102_DEFAULT_OPERATING_MODE,
                   MAX30102_DEFAULT_SAMPLING_RATE,
                   MAX30102_DEFAULT_LED_PULSE_WIDTH,
                   MAX30102_DEFAULT_IR_LED_CURRENT,
                   MAX30102_DEFAULT_START_RED_LED_CURRENT,
                   MAX30102_DEFAULT_MEAN_FILTER_SIZE,
                   MAX30102_DEFAULT_PULSE_BPM_SAMPLE_SIZE,
                   MAX30102_DEFAULT_ADC_RANGE, 
                   MAX30102_DEFAULT_SAMPLE_AVERAGING,
                   MAX30102_DEFAULT_ROLL_OVER,
                   MAX30102_DEFAULT_ALMOST_FULL,
                   false )==ESP_OK) {
                        main_debug("MAX30102 Init OK\r\n");
                   } else {
                        main_debug("MAX30102 not found\r\n");
                   }
	main_debug("初始化结束\r\n");

    printf("MAX30102 Test\n");
    max30102_data_t result = {};

	while(1)
	{
        //Update sensor, saving to "result"
        if(max30102_update(&max30102, &result)==ESP_OK) {
            if(result.pulse_detected) {
                printf("BEAT\n");
                printf("BPM: %f | SpO2: %f%%\n", result.heart_bpm, result.spO2);
            }
        } else {
            main_debug("MAX30102 not found\r\n");
        }
		vTaskDelay(10 / portTICK_PERIOD_MS);
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
