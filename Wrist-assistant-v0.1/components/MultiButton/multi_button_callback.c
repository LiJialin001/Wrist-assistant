#include "multi_button_callback.h"
#include "multi_button.h"
#include "bsp_key.h"
#include "bsp_power.h"

Button btn_power;

uint8_t power_off_flag=false;


esp_err_t multi_button_callback_init(void)
{

	//multi_button_callback_debug("初始化...");

	button_init(&btn_power, bsp_key_read_power_gpio, 1);
	button_start(&btn_power);

	button_attach(&btn_power, PRESS_DOWN, BTN_PRESS_DOWN_Handler);
	button_attach(&btn_power, PRESS_UP, BTN_PRESS_UP_Handler);
	button_attach(&btn_power, LONG_PRESS_START, BTN_LONG_PRESS_Handler);


	//multi_button_callback_debug("初始化成功");
	return ESP_OK;
}


void BTN_LONG_PRESS_HOLD_Handler(void* btn)
{
	//multi_button_callback_debug("----进入:长按保持回调函数----");
	if(btn==&btn_power)
	{
		multi_button_callback_debug("power长按保持");
	}
	//multi_button_callback_debug("----退出:长按保持回调函数----");

}

void BTN_LONG_PRESS_Handler(void* btn)
{
	//multi_button_callback_debug("----进入:长按回调函数----");
	static uint8_t flag=0;

	if(btn==&btn_power)
	{
		multi_button_callback_debug("power长按");
		if(0)//flag==0)
		{
			flag=1;

		}else
		{
			//bsp_power_off();
			bsp_power_send_off();
			power_off_flag=true;
		}


	}
	//multi_button_callback_debug("----退出:长按回调函数----");
}

void BTN_PRESS_UP_Handler(void* btn)
{
	//multi_button_callback_debug("----进入:抬起回调函数----");
	if(btn==&btn_power)
	{
		multi_button_callback_debug("power抬起");

		if(power_off_flag==true)
		{

			//bsp_power_off();
		}



	}
	//multi_button_callback_debug("----退出:抬起回调函数----");
}

void BTN_PRESS_DOWN_Handler(void* btn)
{
	//multi_button_callback_debug("----进入:按下回调函数----");
	if(btn==&btn_power)
	{
		multi_button_callback_debug("power按下");


	}
	//multi_button_callback_debug("----退出:按下回调函数----");
}


