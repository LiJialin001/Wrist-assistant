#include "lvgl_hint_anim.h"
#include "lvgl_Project.h"






void lvgl_tishi_anim_ready_cb_Jin(lv_anim_t * anim)
{
	//lv_anim_del(&tishi_ChuangKou.lv_anim_jin, NULL);
}

void lvgl_tishi_anim_cb_Jin(void * arc, lv_anim_value_t v)
{
	lv_obj_set_y(arc, v);

	//lv_obj_invalidate(lvgl_tishi_main_cont);
}

//右测图片进入动效
void lvgl_tishi_anim_Jin(void)
{

	lv_anim_init(&tishi_ChuangKou.lv_anim_jin);
	lv_anim_set_ready_cb(&tishi_ChuangKou.lv_anim_jin, lvgl_tishi_anim_ready_cb_Jin);
	lv_anim_set_exec_cb(&tishi_ChuangKou.lv_anim_jin, lvgl_tishi_anim_cb_Jin);
	lv_anim_set_values(
		&tishi_ChuangKou.lv_anim_jin,
		lv_obj_get_height(lv_scr_act()),
		lv_obj_get_height(lv_scr_act())-50
	);

	lv_anim_set_time(&tishi_ChuangKou.lv_anim_jin, 300);
	lv_anim_set_var(&tishi_ChuangKou.lv_anim_jin, lvgl_tishi_main_cont);

	//lv_anim_set_playback_delay(&tishi_ChuangKou.lv_anim_jin,1000);

	lv_anim_path_t path;
	lv_anim_path_init(&path);
	lv_anim_path_set_cb(&path, lv_anim_path_ease_out);
	//lv_anim_path_linear线性动画
	//lv_anim_path_step最后一步更改
	//lv_anim_path_ease_in开头很慢
	//lv_anim_path_ease_out最后慢
	//lv_anim_path_ease_in_out在开始和结束时也很慢
	//lv_anim_path_overshoot超出最终值
	//lv_anim_path_bounce从最终值反弹一点（就像撞墙一样）

	//lv_anim_path_set_user_data(&path, &foo); /*Optional for custom functions*/

	lv_anim_set_path(&tishi_ChuangKou.lv_anim_jin, &path);

	lv_anim_start(&tishi_ChuangKou.lv_anim_jin);
}


void lvgl_tishi_anim_ready_cb_chu(lv_anim_t * anim)
{
	//lv_anim_del(&tishi_ChuangKou.lv_anim_chu, NULL);

	lvgl_tishi_close();
}

void lvgl_tishi_anim_cb_chu(void * arc, lv_anim_value_t v)
{
	lv_obj_set_y(arc, v);

	//lv_obj_invalidate(lvgl_tishi_main_cont);
}

//右测图片进入动效
void lvgl_tishi_anim_chu(void)
{

	lv_anim_init(&tishi_ChuangKou.lv_anim_chu);
	lv_anim_set_ready_cb(&tishi_ChuangKou.lv_anim_chu, lvgl_tishi_anim_ready_cb_chu);
	lv_anim_set_exec_cb(&tishi_ChuangKou.lv_anim_chu, lvgl_tishi_anim_cb_chu);
	lv_anim_set_values(
		&tishi_ChuangKou.lv_anim_chu,
		lv_obj_get_y(lvgl_tishi_main_cont),
		lv_obj_get_height(lv_scr_act())
	);

	lv_anim_set_time(&tishi_ChuangKou.lv_anim_chu, 300);
	lv_anim_set_var(&tishi_ChuangKou.lv_anim_chu, lvgl_tishi_main_cont);

	//lv_anim_set_playback_delay(&tishi_ChuangKou.lv_anim_chu,1000);

	lv_anim_path_t path;
	lv_anim_path_init(&path);
	lv_anim_path_set_cb(&path, lv_anim_path_ease_out);
	//lv_anim_path_linear线性动画
	//lv_anim_path_step最后一步更改
	//lv_anim_path_ease_in开头很慢
	//lv_anim_path_ease_out最后慢
	//lv_anim_path_ease_in_out在开始和结束时也很慢
	//lv_anim_path_overshoot超出最终值
	//lv_anim_path_bounce从最终值反弹一点（就像撞墙一样）

	//lv_anim_path_set_user_data(&path, &foo); /*Optional for custom functions*/

	lv_anim_set_path(&tishi_ChuangKou.lv_anim_chu, &path);

	lv_anim_start(&tishi_ChuangKou.lv_anim_chu);
}
