#include "bsp_power.h"

#include "driver/gpio.h"
#include "main.h"


void bsp_power_on(void)
{
	gpio_set_level(IO_POWER_PIN, 1);
	gpio_set_level(IO_POWER_PIN, 1);

}
void bsp_power_off(void)
{
	gpio_set_level(IO_POWER_PIN, 0);
}

xSemaphoreHandle  bsp_power_Semaphore;

void bsp_power_send_off(void)
{
	xSemaphoreGive(bsp_power_Semaphore);//释放信号量
}


static portMUX_TYPE lock = portMUX_INITIALIZER_UNLOCKED;
// #define ENTER_CRITICAL()   portENTER_CRITICAL(&cdc_acm_lock)
// #define EXIT_CRITICAL()    portEXIT_CRITICAL(&cdc_acm_lock)
static uint8_t power_flag=0;

// void bsp_power_handler(void* params)
// {
// 	uint32_t count=0;
// 	uint32_t count1=0;
// 	while (1)
// 	{

// 		// xSemaphoreTake(bsp_power_Semaphore, portMAX_DELAY);//等待信号量

// 		// count = uxSemaphoreGetCount(bsp_power_Semaphore);//获取信号的值
// 		// bap_power_debug("计数信号量的值:%d\r\n",count);
// 		// bap_power_debug("开始关机\r\n");
// 		bsp_power_on();

// 		if(power_flag==0)
// 		{
// 			if(bsp_key_read_power_gpio()==1)
// 			{
// 				if(++count>2)
// 				{
// 					power_flag=1;
// 					bap_power_debug("进入1");
// 				}
// 			}
// 		}else if(power_flag==1)
// 		{
// 			if(bsp_key_read_power_gpio()==0)
// 			{
// 				if(++count>2)
// 				{
// 					power_flag=2;
// 					bap_power_debug("进入2");
// 				}
// 			}
// 		}else if(power_flag==2)
// 		{
// 			if(bsp_key_read_power_gpio()==1)
// 			{
// 				bap_power_debug("关机计数:%d",count);
// 				if(++count>20)
// 				{
// 					lvgl_hint_create(lv_scr_act(),"松手关机",200,20);

// 					while(bsp_key_read_power_gpio())
// 					{
// 						vTaskDelay(pdMS_TO_TICKS(10));
// 					}

// 					bsp_ledc_set_duty(0);
// 					system_save_config();
// 					vTaskDelay(pdMS_TO_TICKS(1000));
// 					bsp_power_off();

// 					//bsp_power_sleep();
// 					wifi_lianjie(0,system_data.wifi_name,system_data.wifi_password,NULL);
// 					vTaskDelay(pdMS_TO_TICKS(1000));
// 					vTaskDelay(pdMS_TO_TICKS(1000));
// 					esp_restart();
// 					while(1)
// 					{
// 						bsp_power_off();
// 						vTaskDelay(pdMS_TO_TICKS(100));
// 					}
// 				}
// 			}else
// 			{
// 				count=0;
// 			}
// 		}

// 		vTaskDelay(pdMS_TO_TICKS(100));
// 	}

//   vTaskDelete(NULL);
// }
#define sleep_time (1000*1000*3600*24)*30//30天
void bsp_power_sleep(void)
{
	esp_sleep_enable_ext1_wakeup((1ULL << KEY_POWER_PIN),ESP_EXT1_WAKEUP_ANY_HIGH);
	esp_sleep_enable_timer_wakeup(sleep_time);
	esp_deep_sleep_start();
}
void bsp_power_init(void)
{
	bap_power_debug("开始初始化");
	//gpio_reset_pin(IO_POWER_PIN);
	gpio_set_direction(IO_POWER_PIN, GPIO_MODE_OUTPUT);
	gpio_set_direction(IO_LCD_BL_PIN, GPIO_MODE_OUTPUT);
	gpio_set_level(IO_LCD_BL_PIN, 0);

	// gpio_pullup_dis(IO_POWER_PIN);
	// gpio_pulldown_dis(IO_POWER_PIN);
	gpio_set_pull_mode(IO_POWER_PIN,GPIO_PULLUP_ONLY);

	bsp_power_on();

	// if(bsp_key_read_power_gpio()==0)
	// {
	// 	power_flag=2;
	// 	bap_power_debug("USB供电开机");
	// }else
	// {
	// 	power_flag=0;
	// 	bap_power_debug("按键电池开机");
	// }

	// bsp_power_Semaphore = xSemaphoreCreateCounting(10,0);//动态创建一个计数型信号量
	// xTaskCreate(bsp_power_handler, "bsp_power_handler", 1024*10, NULL, 4, NULL);

	// bap_power_debug("初始化结束");
}
// void bsp_power_off_task_start(void)
// {
// 	// bsp_power_Semaphore = xSemaphoreCreateCounting(10,0);//动态创建一个计数型信号量
// 	// xTaskCreate(bsp_power_handler, "bsp_power_handler", 1024*4, NULL, 4, NULL);
//  }
