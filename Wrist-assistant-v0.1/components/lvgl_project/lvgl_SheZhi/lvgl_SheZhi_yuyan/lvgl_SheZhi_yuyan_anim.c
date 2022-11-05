#include "lvgl_SheZhi_yuyan.h"
#include "lvgl_Project.h"



void SheZhi_yuyan_anim_ready_XiaLa_Jin_cb(lv_anim_t * anim)
{
	lv_anim_del(&SheZhi_yuyan_ChuangKou.btn_BiaoTi, NULL);
	lvgl_SheZhi_yuyan_anim_XuanZhong(lvgl_SheZhi_yuyan_GongNeng_Data.AnXia_button);
}

void SheZhi_yuyan_anim_XiaLa_Jin_cb(void * arc, lv_anim_value_t v)
{
	lv_obj_set_height(arc, v);
}

//标题下拉进动画
void lvgl_SheZhi_yuyan_anim_XiaLa_Jin(void)
{
	lv_obj_set_height(SheZhi_yuyan_ChuangKou.btn_BiaoTi, SheZhi_yuyan_item_height);

	lv_anim_init(&SheZhi_yuyan_ChuangKou.lv_XiaLa_anim);
	lv_anim_set_ready_cb(&SheZhi_yuyan_ChuangKou.lv_XiaLa_anim, SheZhi_yuyan_anim_ready_XiaLa_Jin_cb);
	lv_anim_set_exec_cb(&SheZhi_yuyan_ChuangKou.lv_XiaLa_anim, SheZhi_yuyan_anim_XiaLa_Jin_cb);
	lv_anim_set_values(
		&SheZhi_yuyan_ChuangKou.lv_XiaLa_anim,
		lv_obj_get_height(SheZhi_yuyan_ChuangKou.btn_BiaoTi),
		lv_obj_get_height(lvgl_SheZhi_yuyan_main_cont)-10
	);
	lv_anim_set_time(&SheZhi_yuyan_ChuangKou.lv_XiaLa_anim, 300);
	lv_anim_set_var(&SheZhi_yuyan_ChuangKou.lv_XiaLa_anim, SheZhi_yuyan_ChuangKou.btn_BiaoTi);

	//lv_anim_set_playback_delay(&SheZhi_yuyan_ChuangKou.lv_XiaLa_anim,1000);

	lv_anim_path_t path;
	lv_anim_path_init(&path);
	lv_anim_path_set_cb(&path, lv_anim_path_bounce);
	//lv_anim_path_linear线性动画
	//lv_anim_path_step最后一步更改
	//lv_anim_path_ease_in开头很慢
	//lv_anim_path_ease_out最后慢
	//lv_anim_path_ease_in_out在开始和结束时也很慢
	//lv_anim_path_overshoot超出最终值
	//lv_anim_path_bounce从最终值反弹一点（就像撞墙一样）

	//lv_anim_path_set_user_data(&path, &foo); /*Optional for custom functions*/

	lv_anim_set_path(&SheZhi_yuyan_ChuangKou.lv_XiaLa_anim, &path);


	lv_anim_start(&SheZhi_yuyan_ChuangKou.lv_XiaLa_anim);
}


void SheZhi_yuyan_anim_ready_XuanZhong_cb(lv_anim_t * anim)
{
	lv_anim_del(&SheZhi_yuyan_ChuangKou.lv_XuanZhong_anim, NULL);
	lvgl_SheZhi_yuyan_GongNeng_Data.DongHua_Flag = false;
}

void SheZhi_yuyan_anim_XuanZhong_cb(void * arc, lv_anim_value_t v)
{

	lv_obj_set_y(arc, v);

}
//切换选中时的动画
void lvgl_SheZhi_yuyan_anim_XuanZhong(lv_obj_t *btn_XuanZhong)
{

	lv_anim_init(&SheZhi_yuyan_ChuangKou.lv_XuanZhong_anim);
	lv_anim_set_ready_cb(&SheZhi_yuyan_ChuangKou.lv_XuanZhong_anim, SheZhi_yuyan_anim_ready_XuanZhong_cb);
	lv_anim_set_exec_cb(&SheZhi_yuyan_ChuangKou.lv_XuanZhong_anim, SheZhi_yuyan_anim_XuanZhong_cb);
	lv_anim_set_values(
		&SheZhi_yuyan_ChuangKou.lv_XuanZhong_anim,
		lv_obj_get_y(SheZhi_yuyan_ChuangKou.btn_XuanZhong),
		lv_obj_get_y(btn_XuanZhong)
	);
	lv_anim_set_time(&SheZhi_yuyan_ChuangKou.lv_XuanZhong_anim, 300);
	lv_anim_set_var(&SheZhi_yuyan_ChuangKou.lv_XuanZhong_anim, SheZhi_yuyan_ChuangKou.btn_XuanZhong);

	lv_anim_path_t path;
	lv_anim_path_init(&path);
	lv_anim_path_set_cb(&path, lv_anim_path_bounce);

	lv_anim_set_path(&SheZhi_yuyan_ChuangKou.lv_XuanZhong_anim, &path);


	lv_anim_start(&SheZhi_yuyan_ChuangKou.lv_XuanZhong_anim);
}






