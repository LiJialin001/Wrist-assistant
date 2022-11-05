#include "lvgl_bilibili_anim.h"
#include "lvgl_Project.h"
//#include "lvgl_SheZhi.h"



// void lvgl_bilibili_anim_ready_zuo_image_cb_Jin(lv_anim_t * anim)
// {
// 	// lv_anim_del(&bilibili_ChuangKou.lv_anim_zuo_image_jin, NULL);

// 	// lvgl_bilibili_anim_zuo_image_shangxia(lv_obj_get_y(bilibili_ChuangKou.lvgl_zuo_image), lv_obj_get_height(lv_scr_act())-120);
// 	// lv_obj_invalidate(lvgl_bilibili_main_cont);
// }

void lvgl_bilibili_anim_zuo_image_cb_Jin(void * arc, lv_anim_value_t v)
{
	lv_obj_set_x(arc, v);

	lv_obj_invalidate(lvgl_bilibili_main_cont);
}

//左测图片进入动效
void lvgl_bilibili_anim_zuo_image_jin(void)
{
	// lv_obj_set_x(bilibili_ChuangKou.lvgl_zuo_image, -(lv_obj_get_width(bilibili_ChuangKou.lvgl_zuo_image)));

	lv_anim_init(&bilibili_ChuangKou.lv_anim_zuo_image_jin);
	// lv_anim_set_ready_cb(&bilibili_ChuangKou.lv_anim_zuo_image_jin, lvgl_bilibili_anim_ready_zuo_image_cb_Jin);
	lv_anim_set_exec_cb(&bilibili_ChuangKou.lv_anim_zuo_image_jin, lvgl_bilibili_anim_zuo_image_cb_Jin);
	// lv_anim_set_values(
	// 	&bilibili_ChuangKou.lv_anim_zuo_image_jin,

	// 	-(lv_obj_get_width(bilibili_ChuangKou.lvgl_zuo_image)),
	// 	0

	// );
	lv_anim_set_time(&bilibili_ChuangKou.lv_anim_zuo_image_jin, 300);
	// lv_anim_set_var(&bilibili_ChuangKou.lv_anim_zuo_image_jin, bilibili_ChuangKou.lvgl_zuo_image);

	//lv_anim_set_playback_delay(&bilibili_ChuangKou.lv_anim_zuo_image_jin,1000);

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

	lv_anim_set_path(&bilibili_ChuangKou.lv_anim_zuo_image_jin, &path);

	lv_anim_start(&bilibili_ChuangKou.lv_anim_zuo_image_jin);
}


// void lvgl_bilibili_anim_ready_you_image_cb_Jin(lv_anim_t * anim)
// {
// 	lv_anim_del(&bilibili_ChuangKou.lv_anim_you_image_jin, NULL);
// 	lvgl_bilibili_anim_you_image_shangxia(lv_obj_get_y(bilibili_ChuangKou.lvgl_you_image),lv_obj_get_height(lv_scr_act())-120);
// }

void lvgl_bilibili_anim_you_image_cb_Jin(void * arc, lv_anim_value_t v)
{
	lv_obj_set_x(arc, v);

	lv_obj_invalidate(lvgl_bilibili_main_cont);
}

//右测图片进入动效
void lvgl_bilibili_anim_you_image_jin(void)
{
	// lv_obj_set_x(bilibili_ChuangKou.lvgl_you_image, lv_obj_get_width(lv_scr_act()));

	lv_anim_init(&bilibili_ChuangKou.lv_anim_you_image_jin);
	// lv_anim_set_ready_cb(&bilibili_ChuangKou.lv_anim_you_image_jin, lvgl_bilibili_anim_ready_you_image_cb_Jin);
	lv_anim_set_exec_cb(&bilibili_ChuangKou.lv_anim_you_image_jin, lvgl_bilibili_anim_you_image_cb_Jin);
	lv_anim_set_values(
		&bilibili_ChuangKou.lv_anim_you_image_jin,
		lv_obj_get_width(lv_scr_act()),
		162
	);

	lv_anim_set_time(&bilibili_ChuangKou.lv_anim_you_image_jin, 300);
	// lv_anim_set_var(&bilibili_ChuangKou.lv_anim_you_image_jin, bilibili_ChuangKou.lvgl_you_image);

	//lv_anim_set_playback_delay(&bilibili_ChuangKou.lv_anim_you_image_jin,1000);

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

	lv_anim_set_path(&bilibili_ChuangKou.lv_anim_you_image_jin, &path);

	lv_anim_start(&bilibili_ChuangKou.lv_anim_you_image_jin);
}



//进入窗口的动效
void lvgl_bilibili_anim_Jin(void)
{

	// lvgl_bilibili_anim_zuo_image_jin();
	// lvgl_bilibili_anim_you_image_jin();
	// lvgl_bilibili_anim_yezi_image(lv_obj_get_width(lv_scr_act()), 100);

}


void lvgl_bilibili_anim_ready_zuo_image_cb_shang(lv_anim_t * anim)
{
	lv_anim_del(&bilibili_ChuangKou.lv_anim_zuo_image_shangxia, NULL);

	if (lv_obj_get_y(bilibili_ChuangKou.lvgl_zuo_image) == lv_obj_get_height(lv_scr_act())-100)
	{
		lvgl_bilibili_anim_zuo_image_shangxia(lv_obj_get_y(bilibili_ChuangKou.lvgl_zuo_image), lv_obj_get_height(lv_scr_act())-120);
	}
	else if (lv_obj_get_y(bilibili_ChuangKou.lvgl_zuo_image) == lv_obj_get_height(lv_scr_act())-120)
	{
		lvgl_bilibili_anim_zuo_image_shangxia(lv_obj_get_y(bilibili_ChuangKou.lvgl_zuo_image), lv_obj_get_height(lv_scr_act())-100);
	}
}

void lvgl_bilibili_anim_zuo_image_cb_shang(void * arc, lv_anim_value_t v)
{
	lv_obj_set_y(arc, v);

	lv_obj_invalidate(lvgl_bilibili_main_cont);
}

//右测图片上下动效
void lvgl_bilibili_anim_zuo_image_shangxia(int dat1, int dat2)
{

	lv_anim_init(&bilibili_ChuangKou.lv_anim_zuo_image_shangxia);
	lv_anim_set_ready_cb(&bilibili_ChuangKou.lv_anim_zuo_image_shangxia, lvgl_bilibili_anim_ready_zuo_image_cb_shang);
	lv_anim_set_exec_cb(&bilibili_ChuangKou.lv_anim_zuo_image_shangxia, lvgl_bilibili_anim_zuo_image_cb_shang);
	lv_anim_set_values(
		&bilibili_ChuangKou.lv_anim_zuo_image_shangxia,
		dat1,
		dat2
	);

	lv_anim_set_time(&bilibili_ChuangKou.lv_anim_zuo_image_shangxia, 1000);
	lv_anim_set_var(&bilibili_ChuangKou.lv_anim_zuo_image_shangxia, bilibili_ChuangKou.lvgl_zuo_image);

	//lv_anim_set_playback_delay(&bilibili_ChuangKou.lv_anim_zuo_image_shangxia,1000);

	lv_anim_path_t path;
	lv_anim_path_init(&path);
	lv_anim_path_set_cb(&path, lv_anim_path_linear);
	//lv_anim_path_linear线性动画
	//lv_anim_path_step最后一步更改
	//lv_anim_path_ease_in开头很慢
	//lv_anim_path_ease_out最后慢
	//lv_anim_path_ease_in_out在开始和结束时也很慢
	//lv_anim_path_overshoot超出最终值
	//lv_anim_path_bounce从最终值反弹一点（就像撞墙一样）

	//lv_anim_path_set_user_data(&path, &foo); /*Optional for custom functions*/

	lv_anim_set_path(&bilibili_ChuangKou.lv_anim_zuo_image_shangxia, &path);

	lv_anim_start(&bilibili_ChuangKou.lv_anim_zuo_image_shangxia);
}


void lvgl_bilibili_anim_ready_you_image_cb_shang(lv_anim_t * anim)
{
	lv_anim_del(&bilibili_ChuangKou.lv_anim_you_image_shangxia, NULL);

	if (lv_obj_get_y(bilibili_ChuangKou.lvgl_you_image) == lv_obj_get_height(lv_scr_act())-100)
	{
		lvgl_bilibili_anim_you_image_shangxia(lv_obj_get_y(bilibili_ChuangKou.lvgl_you_image), lv_obj_get_height(lv_scr_act())-120);
	}else if (lv_obj_get_y(bilibili_ChuangKou.lvgl_you_image) == lv_obj_get_height(lv_scr_act())-120)
	{
		lvgl_bilibili_anim_you_image_shangxia(lv_obj_get_y(bilibili_ChuangKou.lvgl_you_image), lv_obj_get_height(lv_scr_act())-100);
	}
}

void lvgl_bilibili_anim_you_image_cb_shang(void * arc, lv_anim_value_t v)
{
	lv_obj_set_y(arc, v);

	lv_obj_invalidate(lvgl_bilibili_main_cont);
}

//右测图片上下动效
void lvgl_bilibili_anim_you_image_shangxia(int dat1,int dat2)
{

	lv_anim_init(&bilibili_ChuangKou.lv_anim_you_image_shangxia);
	lv_anim_set_ready_cb(&bilibili_ChuangKou.lv_anim_you_image_shangxia, lvgl_bilibili_anim_ready_you_image_cb_shang);
	lv_anim_set_exec_cb(&bilibili_ChuangKou.lv_anim_you_image_shangxia, lvgl_bilibili_anim_you_image_cb_shang);
	lv_anim_set_values(
		&bilibili_ChuangKou.lv_anim_you_image_shangxia,
		dat1,
		dat2
	);

	lv_anim_set_time(&bilibili_ChuangKou.lv_anim_you_image_shangxia, 1500);
	lv_anim_set_var(&bilibili_ChuangKou.lv_anim_you_image_shangxia, bilibili_ChuangKou.lvgl_you_image);

	//lv_anim_set_playback_delay(&bilibili_ChuangKou.lv_anim_you_image_shangxia,1000);

	lv_anim_path_t path;
	lv_anim_path_init(&path);
	lv_anim_path_set_cb(&path, lv_anim_path_linear);
	//lv_anim_path_linear线性动画
	//lv_anim_path_step最后一步更改
	//lv_anim_path_ease_in开头很慢
	//lv_anim_path_ease_out最后慢
	//lv_anim_path_ease_in_out在开始和结束时也很慢
	//lv_anim_path_overshoot超出最终值
	//lv_anim_path_bounce从最终值反弹一点（就像撞墙一样）

	//lv_anim_path_set_user_data(&path, &foo); /*Optional for custom functions*/

	lv_anim_set_path(&bilibili_ChuangKou.lv_anim_you_image_shangxia, &path);

	lv_anim_start(&bilibili_ChuangKou.lv_anim_you_image_shangxia);
}







//叶子图片左右动效
void lvgl_bilibili_anim_ready_yezi_image_cb(lv_anim_t * anim)
{
	lv_anim_del(&bilibili_ChuangKou.lv_anim_yezi_image, NULL);

	if (lv_obj_get_x(bilibili_ChuangKou.lvgl_yezi_image) == 100)
	{
		lvgl_bilibili_anim_yezi_image(lv_obj_get_x(bilibili_ChuangKou.lvgl_yezi_image), 160);
	}
	else if (lv_obj_get_x(bilibili_ChuangKou.lvgl_yezi_image) == 160)
	{
		lvgl_bilibili_anim_yezi_image(lv_obj_get_x(bilibili_ChuangKou.lvgl_yezi_image), 100);
	}
}

void lvgl_bilibili_anim_yezi_image_cb(void * arc, lv_anim_value_t v)
{
	lv_obj_set_x(arc, v);

	lv_obj_invalidate(lvgl_bilibili_main_cont);
}


void lvgl_bilibili_anim_yezi_image(int dat1, int dat2)
{

	lv_anim_init(&bilibili_ChuangKou.lv_anim_yezi_image);
	lv_anim_set_ready_cb(&bilibili_ChuangKou.lv_anim_yezi_image, lvgl_bilibili_anim_ready_yezi_image_cb);
	lv_anim_set_exec_cb(&bilibili_ChuangKou.lv_anim_yezi_image, lvgl_bilibili_anim_yezi_image_cb);
	lv_anim_set_values(
		&bilibili_ChuangKou.lv_anim_yezi_image,
		dat1,
		dat2
	);

	lv_anim_set_time(&bilibili_ChuangKou.lv_anim_yezi_image, 2000);
	lv_anim_set_var(&bilibili_ChuangKou.lv_anim_yezi_image, bilibili_ChuangKou.lvgl_yezi_image);

	//lv_anim_set_playback_delay(&bilibili_ChuangKou.lv_anim_yezi_image,1000);

	lv_anim_path_t path;
	lv_anim_path_init(&path);
	lv_anim_path_set_cb(&path, lv_anim_path_ease_in_out);
	//lv_anim_path_linear线性动画
	//lv_anim_path_step最后一步更改
	//lv_anim_path_ease_in开头很慢
	//lv_anim_path_ease_out最后慢
	//lv_anim_path_ease_in_out在开始和结束时也很慢
	//lv_anim_path_overshoot超出最终值
	//lv_anim_path_bounce从最终值反弹一点（就像撞墙一样）

	//lv_anim_path_set_user_data(&path, &foo); /*Optional for custom functions*/

	lv_anim_set_path(&bilibili_ChuangKou.lv_anim_yezi_image, &path);

	lv_anim_start(&bilibili_ChuangKou.lv_anim_yezi_image);
}



