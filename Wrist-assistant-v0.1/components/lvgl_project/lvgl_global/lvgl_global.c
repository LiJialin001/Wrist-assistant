#include "lvgl_global.h"
#include "lvgl_Project.h"



void lvgl_set_obj_hide(lv_obj_t * obj)
{
	if (obj == NULL)
		return;
	lv_obj_set_hidden(obj, true);

}

void lvgl_set_obj_show(lv_obj_t * obj)
{
	if (obj == NULL)
		return;
	lv_obj_set_hidden(obj, false);

}
uint8_t lvgl_task_create(lv_task_t **handel,lv_task_cb_t task_cb, uint32_t period, lv_task_prio_t prio, void * user_data)
{

	if(*handel != NULL)
	{

		return false;
	}

	*handel = lv_task_create(task_cb, period, prio, user_data);

	if (*handel == NULL)
	{
		return false;
	}

	return true;


}

void lvgl_task_delete(lv_task_t ** task)
{

	if (*task != NULL)
	{
		lv_task_del(*task);
		*task = NULL;
		//memset(task,0x00,sizeof(lv_task_t));
	}

}

void lvgl_set_motai(int sta)
{

	lv_obj_set_click(lv_layer_top(), sta);//开启后窗口将模态
}








