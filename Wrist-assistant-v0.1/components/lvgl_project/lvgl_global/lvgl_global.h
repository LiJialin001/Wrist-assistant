#ifndef __lvgl_global_H__
#define __lvgl_global_H__

#include "lvgl.h"

void lvgl_set_obj_hide(lv_obj_t * obj);
void lvgl_set_obj_show(lv_obj_t * obj);
uint8_t lvgl_task_create(lv_task_t **handel,lv_task_cb_t task_cb, uint32_t period, lv_task_prio_t prio, void * user_data);
void lvgl_task_delete(lv_task_t ** task);
void lvgl_set_motai(int sta);


#endif
