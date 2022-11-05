#include "lvgl_chulizhong_anim.h"
#include "lvgl_Project.h"



void lvgl_chulizhong_anim_ready_cb_Jin(lv_anim_t * anim)
{
	lv_anim_del(&lvgl_chulizhong_ChuangKou.lv_anim_jin, NULL);

}

void lvgl_chulizhong_anim_cb_Jin(void * arc, lv_anim_value_t v)
{
	lv_obj_set_y(arc, v);

	lv_obj_invalidate(lvgl_chulizhong_main_cont);
}

//左测图片进入动效
void lvgl_chulizhong_anim_jin(void)
{

	lv_anim_init(&lvgl_chulizhong_ChuangKou.lv_anim_jin);
	lv_anim_set_ready_cb(&lvgl_chulizhong_ChuangKou.lv_anim_jin, lvgl_chulizhong_anim_ready_cb_Jin);
	lv_anim_set_exec_cb(&lvgl_chulizhong_ChuangKou.lv_anim_jin, lvgl_chulizhong_anim_cb_Jin);
	lv_anim_set_values(
		&lvgl_chulizhong_ChuangKou.lv_anim_jin,

		240,
		lvgl_chulizhong_y

	); 
	lv_anim_set_time(&lvgl_chulizhong_ChuangKou.lv_anim_jin, 300);
	lv_anim_set_var(&lvgl_chulizhong_ChuangKou.lv_anim_jin, lvgl_chulizhong_main_cont);

	//lv_anim_set_playback_delay(&lvgl_chulizhong_ChuangKou.lv_anim_jin,1000);

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

	lv_anim_set_path(&lvgl_chulizhong_ChuangKou.lv_anim_jin, &path);

	lv_anim_start(&lvgl_chulizhong_ChuangKou.lv_anim_jin);
}


//进入窗口的动效
void lvgl_chulizhong_anim_Jin(void)
{

	lvgl_chulizhong_anim_jin();


}



void lvgl_chulizhong_anim_ready_cb_chu(lv_anim_t * anim)
{
	lv_anim_del(&lvgl_chulizhong_ChuangKou.lv_anim_chu, NULL);
	lvgl_chulizhong_close();
}

void lvgl_chulizhong_anim_cb_chu(void * arc, lv_anim_value_t v)
{
	lv_obj_set_y(arc, v);

	lv_obj_invalidate(lvgl_chulizhong_main_cont);
}

//退出窗口动效
void lvgl_chulizhong_anim_chu(void)
{

	lv_anim_init(&lvgl_chulizhong_ChuangKou.lv_anim_chu);
	lv_anim_set_ready_cb(&lvgl_chulizhong_ChuangKou.lv_anim_chu, lvgl_chulizhong_anim_ready_cb_chu);
	lv_anim_set_exec_cb(&lvgl_chulizhong_ChuangKou.lv_anim_chu, lvgl_chulizhong_anim_cb_chu);
	lv_anim_set_values(
		&lvgl_chulizhong_ChuangKou.lv_anim_chu,
		lv_obj_get_y(lvgl_chulizhong_main_cont) ,
		240
	);
	lv_anim_set_time(&lvgl_chulizhong_ChuangKou.lv_anim_chu, 300);
	lv_anim_set_var(&lvgl_chulizhong_ChuangKou.lv_anim_chu, lvgl_chulizhong_main_cont);

	//lv_anim_set_playback_delay(&lvgl_chulizhong_ChuangKou.lv_anim_chu,1000);

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

	lv_anim_set_path(&lvgl_chulizhong_ChuangKou.lv_anim_chu, &path);

	lv_anim_start(&lvgl_chulizhong_ChuangKou.lv_anim_chu);
}
