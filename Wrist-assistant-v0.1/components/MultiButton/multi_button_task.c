#include "multi_button_task.h"
#include "multi_button.h"
#include "bsp_key.h"



esp_timer_handle_t multi_button_task_timer_id = NULL;


static void multi_button_task_time_handler(void * p_context)
{

	button_ticks();

}


esp_err_t multi_button_task_init(void)
{

	multi_button_task_debug("初始化...");
	//bsp_key_init();

	esp_timer_create_args_t multi_button_task_timer_conf = {
			.callback = multi_button_task_time_handler,
			.name     = "multi_button_task_timer"
	};

	esp_timer_create(&multi_button_task_timer_conf, &multi_button_task_timer_id);
	esp_timer_start_periodic(multi_button_task_timer_id, 5 * 1000U);




	multi_button_task_debug("初始化成功");
	return ESP_OK;
}
