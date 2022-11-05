#include "lvgl_SheZhi_anim.h"
#include "lvgl_Project.h"




void SheZhi_anim_01(void * arc, lv_anim_value_t v)
{
	lv_obj_set_x(arc, v);
}
void SheZhi_anim_02(void * arc, lv_anim_value_t v)
{
	lv_obj_set_x(arc, v);
}
void SheZhi_anim_03(void * arc, lv_anim_value_t v)
{
	lv_obj_set_x(arc, v);
}
void SheZhi_anim_04(void * arc, lv_anim_value_t v)
{
	lv_obj_set_x(arc, v);
}
void SheZhi_anim_05(void * arc, lv_anim_value_t v)
{
	lv_obj_set_x(arc, v);
}
void SheZhi_anim_06(void * arc, lv_anim_value_t v)
{
	lv_obj_set_x(arc, v);
}
void SheZhi_anim_07(void * arc, lv_anim_value_t v)
{
	lv_obj_set_x(arc, v);
}
void SheZhi_anim_08(void * arc, lv_anim_value_t v)
{
	lv_obj_set_x(arc, v);
}
void SheZhi_anim_09(void * arc, lv_anim_value_t v)
{
	lv_obj_set_x(arc, v);
}
void SheZhi_anim_10(void * arc, lv_anim_value_t v)
{
	lv_obj_set_x(arc, v);
}
void SheZhi_anim_11(void * arc, lv_anim_value_t v)
{
	lv_obj_set_x(arc, v);
}
void SheZhi_anim_12(void * arc, lv_anim_value_t v)
{
	lv_obj_set_x(arc, v);
}
void SheZhi_anim_13(void * arc, lv_anim_value_t v)
{
	lv_obj_set_x(arc, v);
}
void SheZhi_anim_Jin_ready_cb(lv_anim_t * anim)
{
	SheZhi_debug("Jin ok\r\n");

	lv_obj_set_drag_dir(lvgl_SheZhi_main_cont, LV_DRAG_DIR_ONE);//设置拖动方向
}
void SheZhi_anim_Chu_ready_cb(lv_anim_t * anim)
{
	SheZhi_debug("chu ok\r\n");

	lv_event_send(lvgl_SheZhi_GongNeng_Data.AnXia_button, SheZhi_event_anXia,NULL);
	//lvgl_SheZhi_DongHua_Jin();
}

void(*SheZhi_anim_cb_buf[])(void * arc, lv_anim_value_t v) =
{
	&SheZhi_anim_01,
	&SheZhi_anim_02,
	&SheZhi_anim_03,
	&SheZhi_anim_04,
	&SheZhi_anim_05,
	&SheZhi_anim_06,
	&SheZhi_anim_07,
	&SheZhi_anim_08,
	&SheZhi_anim_09,
	&SheZhi_anim_10,
	&SheZhi_anim_11,
	&SheZhi_anim_12,
	&SheZhi_anim_13,



};

//滑入动画
void lvgl_SheZhi_DongHua_Jin(void)
{
	int i = 0;
	int max = SheZhi_Button_Num;


	lv_anim_path_t path;
	lv_anim_path_init(&path);
	lv_anim_path_set_cb(&path, lv_anim_path_overshoot);
	//lv_anim_path_linear线性动画
	//lv_anim_path_step最后一步更改
	//lv_anim_path_ease_in开头很慢
	//lv_anim_path_ease_out最后慢
	//lv_anim_path_ease_in_out在开始和结束时也很慢
	//lv_anim_path_overshoot超出最终值
	//lv_anim_path_bounce从最终值反弹一点（就像撞墙一样）

	//lv_anim_path_set_user_data(&path, &foo); /*Optional for custom functions*/

	for (i = 0; i < max; i++)
	{
		lv_obj_set_x(lvgl_SheZhi_Button[i], 240);
		lv_obj_set_y(lvgl_SheZhi_Button[i], 40 + i * SheZhi_item_height);

		lv_anim_init(&SheZhi_ChuangKou.lv_anim_Jin[i]);

		if (i == max-1)
		{
			lv_anim_set_ready_cb(&SheZhi_ChuangKou.lv_anim_Jin[i], SheZhi_anim_Jin_ready_cb);
		}

		lv_anim_set_exec_cb(&SheZhi_ChuangKou.lv_anim_Jin[i], SheZhi_anim_cb_buf[i]);
		lv_anim_set_values(&SheZhi_ChuangKou.lv_anim_Jin[i], 240, 5);
		lv_anim_set_time(&SheZhi_ChuangKou.lv_anim_Jin[i], 200+i*30);
		lv_anim_set_var(&SheZhi_ChuangKou.lv_anim_Jin[i], lvgl_SheZhi_Button[i]);

		lv_anim_set_path(&SheZhi_ChuangKou.lv_anim_Jin[i], &path);
		lv_anim_start(&SheZhi_ChuangKou.lv_anim_Jin[i]);
	}

}



void SheZhi_anim_DongHua_cb(void * arc, lv_anim_value_t v)
{
	lv_obj_set_y(arc, v);
}
void SheZhi_anim_ready_DongHua_cb(lv_anim_t * anim)
{

	lv_event_send(lvgl_SheZhi_GongNeng_Data.AnXia_button, SheZhi_event_anXia, NULL);

	lv_anim_del(&SheZhi_ChuangKou.lv_DongHua_anim,NULL);
}

//滑出动画
void lvgl_SheZhi_DongHua_Chu(void)
{

	lv_obj_move_foreground(lvgl_SheZhi_GongNeng_Data.AnXia_button);//窗口放在前面

	lv_anim_init(&SheZhi_ChuangKou.lv_DongHua_anim);
	lv_anim_set_ready_cb(&SheZhi_ChuangKou.lv_DongHua_anim, SheZhi_anim_ready_DongHua_cb);
	lv_anim_set_exec_cb(&SheZhi_ChuangKou.lv_DongHua_anim, SheZhi_anim_DongHua_cb);
	lv_anim_set_values(
		&SheZhi_ChuangKou.lv_DongHua_anim,
		lv_obj_get_y(lvgl_SheZhi_GongNeng_Data.AnXia_button),
		(0 - lv_obj_get_y(lvgl_SheZhi_main_cont))-10
	);
	lv_anim_set_time(&SheZhi_ChuangKou.lv_DongHua_anim, 250);
	lv_anim_set_var(&SheZhi_ChuangKou.lv_DongHua_anim, lvgl_SheZhi_GongNeng_Data.AnXia_button);

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

	lv_anim_set_path(&SheZhi_ChuangKou.lv_DongHua_anim, &path);

	lv_anim_start(&SheZhi_ChuangKou.lv_DongHua_anim);

}

