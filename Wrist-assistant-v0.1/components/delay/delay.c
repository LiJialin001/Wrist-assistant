#include "delay.h"

void delay_us(int us)
{
	 long time=40*us;
	 while(--time);
	//ets_delay_us(200000);
	//vTaskDelay(10 / portTICK_RATE_MS);
	//ets_delay_us(us);
}

void delay_ms(int ms)
{
	//ets_delay_us(ms*1000);
	delay_us(ms*1000);
	//vTaskDelay(ms / portTICK_RATE_MS);
}


