#include "lvgl_heart.h"
#include "lvgl_Project.h"
#include "lvgl_heart_anim.h"
#include "lvgl_SheZhi.h"



_lvgl_heart_GongNeng_Data lvgl_heart_GongNeng_Data;
_heart_ChuangKou heart_ChuangKou;

lv_obj_t *lvgl_heart_main_cont = NULL;
lv_style_t lvgl_heart_style;

LV_IMG_DECLARE(walking_0)
LV_IMG_DECLARE(walking_2)
LV_IMG_DECLARE(walking_4)
LV_IMG_DECLARE(walking_6)

const char*heart_TEXT[][SYSTEM_LANGUAGE_NUM] =
{
	{ "health", "health", "health", NULL},
	{ "BPM:", "BPM:", "BPM:", NULL},
	{ "SaO2:", "SaO2:", "SaO2:", NULL},
	{ "steps:", "steps:", "steps:", NULL},
};


//设置心率
void lvgl_heart_Set_heart_rate(char *str)
{
	char buf[20];
	if (heart_ChuangKou.lvgl_cont_bpm == NULL)
	{
		//----创建容器----//
		heart_ChuangKou.lvgl_cont_bpm = lv_cont_create(lvgl_heart_main_cont, NULL);
		lv_obj_set_pos(heart_ChuangKou.lvgl_cont_bpm,16, 56);
		lv_obj_set_size(heart_ChuangKou.lvgl_cont_bpm, 214, 32);
		lv_obj_set_drag_parent(heart_ChuangKou.lvgl_cont_bpm, true); //启用 / 禁用父对象可拖动
		lv_obj_add_style(heart_ChuangKou.lvgl_cont_bpm, LV_OBJ_PART_MAIN, &lvgl_touming_cont_style);


		heart_ChuangKou.lvgl_Label_biaoti_bpm = lv_label_create(heart_ChuangKou.lvgl_cont_bpm, NULL);
		lv_label_set_long_mode(heart_ChuangKou.lvgl_Label_biaoti_bpm, LV_LABEL_LONG_SROLL_CIRC);//循环滚动
		lv_obj_set_pos(heart_ChuangKou.lvgl_Label_biaoti_bpm, 0, 0);
		lv_obj_set_width(heart_ChuangKou.lvgl_Label_biaoti_bpm, 102);
		lv_obj_set_height(heart_ChuangKou.lvgl_Label_biaoti_bpm, 32);
		lv_label_set_recolor(heart_ChuangKou.lvgl_Label_biaoti_bpm, true);
		lv_label_set_align(heart_ChuangKou.lvgl_Label_biaoti_bpm, LV_LABEL_ALIGN_RIGHT);
		lv_label_set_recolor(heart_ChuangKou.lvgl_Label_biaoti_bpm, true);
		lv_label_set_text(heart_ChuangKou.lvgl_Label_biaoti_bpm, heart_TEXT[1][system_get_Language()]);

		lv_obj_add_style(heart_ChuangKou.lvgl_Label_biaoti_bpm, LV_OBJ_PART_MAIN, &lvgl_font24_style);

		lv_label_set_anim_speed(heart_ChuangKou.lvgl_Label_biaoti_bpm, 20);


		heart_ChuangKou.lvgl_Label_bpm = lv_label_create(heart_ChuangKou.lvgl_cont_bpm, heart_ChuangKou.lvgl_Label_biaoti_bpm);
		lv_obj_set_pos(heart_ChuangKou.lvgl_Label_bpm, 104, 0);
		lv_obj_set_width(heart_ChuangKou.lvgl_Label_bpm, 110);
		lv_obj_set_height(heart_ChuangKou.lvgl_Label_bpm, 32);
		lv_label_set_align(heart_ChuangKou.lvgl_Label_bpm, LV_LABEL_ALIGN_LEFT);

	}
	if (str == NULL)
	{

		lv_label_set_text(heart_ChuangKou.lvgl_Label_bpm, "----");
		return;
	}

	lv_label_set_text(heart_ChuangKou.lvgl_Label_bpm, str);
}

//设置血氧
void lvgl_heart_Set_blood_oxygen(char *str)
{
	char buf[20];
	if (heart_ChuangKou.lvgl_cont_SaO2 == NULL)
	{
		//----创建容器----//
		heart_ChuangKou.lvgl_cont_SaO2 = lv_cont_create(lvgl_heart_main_cont, NULL);
		lv_obj_set_pos(heart_ChuangKou.lvgl_cont_SaO2,16, 97);
		lv_obj_set_size(heart_ChuangKou.lvgl_cont_SaO2, 214, 32);
		lv_obj_set_drag_parent(heart_ChuangKou.lvgl_cont_SaO2, true); //启用 / 禁用父对象可拖动
		lv_obj_add_style(heart_ChuangKou.lvgl_cont_SaO2, LV_OBJ_PART_MAIN, &lvgl_touming_cont_style);


		heart_ChuangKou.lvgl_Label_biaoti_SaO2 = lv_label_create(heart_ChuangKou.lvgl_cont_SaO2, NULL);
		lv_label_set_long_mode(heart_ChuangKou.lvgl_Label_biaoti_SaO2, LV_LABEL_LONG_SROLL_CIRC);//循环滚动
		lv_obj_set_pos(heart_ChuangKou.lvgl_Label_biaoti_SaO2, 0, 0);
		lv_obj_set_width(heart_ChuangKou.lvgl_Label_biaoti_SaO2, 102);
		lv_obj_set_height(heart_ChuangKou.lvgl_Label_biaoti_SaO2, 32);
		lv_label_set_recolor(heart_ChuangKou.lvgl_Label_biaoti_SaO2, true);
		lv_label_set_align(heart_ChuangKou.lvgl_Label_biaoti_SaO2, LV_LABEL_ALIGN_RIGHT);
		lv_label_set_recolor(heart_ChuangKou.lvgl_Label_biaoti_SaO2, true);
		lv_label_set_text(heart_ChuangKou.lvgl_Label_biaoti_SaO2, heart_TEXT[2][system_get_Language()]);

		lv_obj_add_style(heart_ChuangKou.lvgl_Label_biaoti_SaO2, LV_OBJ_PART_MAIN, &lvgl_font24_style);

		lv_label_set_anim_speed(heart_ChuangKou.lvgl_Label_biaoti_SaO2, 20);


		heart_ChuangKou.lvgl_Label_bofang = lv_label_create(heart_ChuangKou.lvgl_cont_SaO2, heart_ChuangKou.lvgl_Label_biaoti_SaO2);
		lv_obj_set_pos(heart_ChuangKou.lvgl_Label_bofang, 104, 0);
		lv_obj_set_width(heart_ChuangKou.lvgl_Label_bofang, 110);
		lv_obj_set_height(heart_ChuangKou.lvgl_Label_bofang, 32);
		lv_label_set_align(heart_ChuangKou.lvgl_Label_bofang, LV_LABEL_ALIGN_LEFT);

	}
	if (str == NULL)
	{

		lv_label_set_text(heart_ChuangKou.lvgl_Label_bofang, "----");
		return;
	}

	lv_label_set_text(heart_ChuangKou.lvgl_Label_bofang, str);
}


//设置步数
void lvgl_heart_Set_steps(char *str)
{
	char buf[20];
	if (heart_ChuangKou.lvgl_cont_step == NULL)
	{
		//----创建容器----//
		heart_ChuangKou.lvgl_cont_step = lv_cont_create(lvgl_heart_main_cont, NULL);
		lv_obj_set_pos(heart_ChuangKou.lvgl_cont_step,16, 138);
		lv_obj_set_size(heart_ChuangKou.lvgl_cont_step, 214, 32);
		lv_obj_set_drag_parent(heart_ChuangKou.lvgl_cont_step, true); //启用 / 禁用父对象可拖动
		lv_obj_add_style(heart_ChuangKou.lvgl_cont_step, LV_OBJ_PART_MAIN, &lvgl_touming_cont_style);


		heart_ChuangKou.lvgl_Label_biaoti_step = lv_label_create(heart_ChuangKou.lvgl_cont_step, NULL);
		lv_label_set_long_mode(heart_ChuangKou.lvgl_Label_biaoti_step, LV_LABEL_LONG_SROLL_CIRC);//循环滚动
		lv_obj_set_pos(heart_ChuangKou.lvgl_Label_biaoti_step, 0, 0);
		lv_obj_set_width(heart_ChuangKou.lvgl_Label_biaoti_step, 102);
		lv_obj_set_height(heart_ChuangKou.lvgl_Label_biaoti_step, 32);
		lv_label_set_recolor(heart_ChuangKou.lvgl_Label_biaoti_step, true);
		lv_label_set_align(heart_ChuangKou.lvgl_Label_biaoti_step, LV_LABEL_ALIGN_RIGHT);
		lv_label_set_recolor(heart_ChuangKou.lvgl_Label_biaoti_step, true);
		lv_label_set_text(heart_ChuangKou.lvgl_Label_biaoti_step, heart_TEXT[3][system_get_Language()]);

		lv_obj_add_style(heart_ChuangKou.lvgl_Label_biaoti_step, LV_OBJ_PART_MAIN, &lvgl_font24_style);

		lv_label_set_anim_speed(heart_ChuangKou.lvgl_Label_biaoti_step, 20);


		heart_ChuangKou.lvgl_Label_step = lv_label_create(heart_ChuangKou.lvgl_cont_step, heart_ChuangKou.lvgl_Label_biaoti_step);
		lv_obj_set_pos(heart_ChuangKou.lvgl_Label_step, 104, 0);
		lv_obj_set_width(heart_ChuangKou.lvgl_Label_step, 110);
		lv_obj_set_height(heart_ChuangKou.lvgl_Label_step, 32);
		lv_label_set_align(heart_ChuangKou.lvgl_Label_step, LV_LABEL_ALIGN_LEFT);

	}
	if (str == NULL)
	{

		lv_label_set_text(heart_ChuangKou.lvgl_Label_step, "----");
		return;
	}

	lv_label_set_text(heart_ChuangKou.lvgl_Label_step, str);
}


void lvgl_heart_event_cb(struct _lv_obj_t * obj, lv_event_t event)
{
	if (obj == lvgl_heart_main_cont)
	{
		//heart_debug("cb:%d\r\n", event);
		switch (event)
		{

		case LV_EVENT_DELETE:

			lvgl_heart_closed();

			break;

		case LV_EVENT_PRESSING://对象被持续按下


			break;
		case LV_EVENT_PRESSED://对象已被按下


			break;
		case LV_EVENT_DRAG_END://拖动结束后

			if (lv_obj_get_y(lvgl_heart_main_cont) != 0)
			{

				lv_obj_set_y(lvgl_heart_main_cont, 0);
			}

			if (lv_obj_get_x(lvgl_heart_main_cont) != 0)
			{
				if (lv_obj_get_x(lvgl_heart_main_cont) < -100)
				{
					lvgl_heart_close(0);

				}
				else
				if (lv_obj_get_x(lvgl_heart_main_cont) > 100)
				{
					lvgl_heart_close(0);

				}
				else
				{
					lv_obj_set_x(lvgl_heart_main_cont, 0);
				}
			}
			break;

		case LV_EVENT_RELEASED://按钮释放

		break;
		case LV_EVENT_LONG_PRESSED://按钮长按

			break;

		default:
			break;

		}

	}
}


void lvgl_heart_create(lv_obj_t * Fu)
{

	if (lvgl_heart_main_cont == NULL)
	{

		lv_style_init(&lvgl_heart_style);
		lv_style_copy(&lvgl_heart_style, &lvgl_WuBianKuang_cont_style);

		//----创建容器----//
		lvgl_heart_main_cont = lv_cont_create(lv_scr_act(), NULL);
		lv_obj_set_pos(lvgl_heart_main_cont, 0, 0);
		lv_obj_set_size(lvgl_heart_main_cont, lv_obj_get_width(Fu), lv_obj_get_height(Fu));

		//lv_obj_set_drag_parent(lvgl_heart_main_cont, true); //启用 / 禁用父对象可拖动
		// lv_obj_set_click(lvgl_heart_main_cont, true); //启用 / 禁用可点击
		// lv_obj_set_drag(lvgl_heart_main_cont, true);//启用/禁用对象可拖动
		// lv_obj_set_drag_dir(lvgl_heart_main_cont, LV_DRAG_DIR_ONE);//设置拖动方向
		// lv_obj_set_drag_throw(lvgl_heart_main_cont, false);//启用/禁用拖动后是否有惯性移动

		lv_obj_add_style(lvgl_heart_main_cont, LV_OBJ_PART_MAIN, &lvgl_heart_style);//设置样式
		lv_obj_set_event_cb(lvgl_heart_main_cont, lvgl_heart_event_cb);//设置回调函数


		//----文字显示----//
#if 1
		lvgl_heart_Set_heart_rate("66666");
		lvgl_heart_Set_blood_oxygen("66666");
		lvgl_heart_Set_steps("888888");
#else
          lvgl_heart_Set_heart_rate(system_data.bpm_Data.heart_rate);
          lvgl_heart_Set_blood_oxygen(system_data.bpm_Data.blood_oxygen);
          lvgl_heart_Set_steps(system_data.bpm_Data.steps);
#endif
		// ----文字显示----//


		// ----walk图片----//
		if (heart_ChuangKou.lvgl_walk_image == NULL)
		{
			heart_ChuangKou.lvgl_walk_image = lv_img_create(lvgl_heart_main_cont, NULL);
			lv_obj_set_pos(heart_ChuangKou.lvgl_walk_image, 30, -50);
			lv_img_set_zoom(heart_ChuangKou.lvgl_walk_image, 50);
			lv_img_set_src(heart_ChuangKou.lvgl_walk_image, &walking_0);
		}
		// ----walk图片----//

		// ----heart图片----//
		if (heart_ChuangKou.lvgl_heart_image == NULL)
		{
			heart_ChuangKou.lvgl_heart_image = lv_img_create(lvgl_heart_main_cont, NULL);
			lv_obj_set_pos(heart_ChuangKou.lvgl_heart_image, -10, 0);
			lv_img_set_zoom(heart_ChuangKou.lvgl_heart_image, 50);
			lv_img_set_src(heart_ChuangKou.lvgl_heart_image, &walking_2);
		}
		// ----heart图片----//

		// ----sao2图片----//
		if (heart_ChuangKou.lvgl_Sao2_image == NULL)
		{
			heart_ChuangKou.lvgl_Sao2_image = lv_img_create(lvgl_heart_main_cont, NULL);
			lv_obj_set_pos(heart_ChuangKou.lvgl_Sao2_image, 0, 50);
			lv_img_set_zoom(heart_ChuangKou.lvgl_Sao2_image, 50);
			lv_img_set_src(heart_ChuangKou.lvgl_Sao2_image, &walking_4);
		}
		// ----sao2图片----//


		// // ----logo图片----//
		// if (heart_ChuangKou.lvgl_logo_image == NULL)
		// {
		// 	heart_ChuangKou.lvgl_logo_image = lv_img_create(lvgl_heart_main_cont, NULL);
		// 	lv_obj_set_pos(heart_ChuangKou.lvgl_logo_image,30, lv_obj_get_height(Fu)-44);
		// 	lv_img_set_src(heart_ChuangKou.lvgl_logo_image, NULL);
		// }
		// // ----logo图片----//

		// // ----左侧图片----//
		// if (heart_ChuangKou.lvgl_zuo_image == NULL)
		// {
		// 	heart_ChuangKou.lvgl_zuo_image = lv_img_create(lvgl_heart_main_cont, NULL);
		// 	lv_obj_set_pos(heart_ChuangKou.lvgl_zuo_image, 0, lv_obj_get_height(Fu)-100);
		// 	lv_img_set_src(heart_ChuangKou.lvgl_zuo_image, NULL);
		// }
		// // ----左侧图片----//

		// // ----右侧图片----//
		// if (heart_ChuangKou.lvgl_you_image == NULL)
		// {
		// 	heart_ChuangKou.lvgl_you_image = lv_img_create(lvgl_heart_main_cont, NULL);
		// 	lv_obj_set_pos(heart_ChuangKou.lvgl_you_image, 162, lv_obj_get_height(Fu)-100);
		// 	lv_img_set_src(heart_ChuangKou.lvgl_you_image, NULL);
		// }
		// // ----右侧图片----//


		// // ----叶子图片----//
		// if (heart_ChuangKou.lvgl_yezi_image == NULL)
		// {
		// 	heart_ChuangKou.lvgl_yezi_image = lv_img_create(lvgl_heart_main_cont, NULL);
		// 	lv_obj_set_pos(heart_ChuangKou.lvgl_yezi_image, 146, 10);
		// 	lv_img_set_src(heart_ChuangKou.lvgl_yezi_image, NULL);
		// }
		// // ----叶子图片----//


		// // ----头 前图层图片----//
		// if (heart_ChuangKou.lvgl_tou_qian_image == NULL)
		// {
		// 	heart_ChuangKou.lvgl_tou_qian_image = lv_img_create(lvgl_heart_main_cont, NULL);
		// 	lv_obj_set_pos(heart_ChuangKou.lvgl_tou_qian_image, 0, 1);
		// 	lv_img_set_src(heart_ChuangKou.lvgl_tou_qian_image, NULL);
		// }
		// // ----头 前图层图片----//


		// // ----前图层图片----//
		// if (heart_ChuangKou.lvgl_qian_image == NULL)
		// {
		// 	heart_ChuangKou.lvgl_qian_image = lv_img_create(lvgl_heart_main_cont, NULL);
		// 	lv_obj_set_pos(heart_ChuangKou.lvgl_qian_image, 0,lv_obj_get_height(Fu)-36);
		// 	lv_img_set_src(heart_ChuangKou.lvgl_qian_image, NULL);
		// }
		// // ----前图层图片----//



		lvgl_task_create(&heart_ChuangKou.lvgl_task,lvgl_heart_TaskCb, 20, LV_TASK_PRIO_LOWEST, NULL);

		heart_debug("创建窗口1\r\n");
	}
	else
	{

		heart_debug("显示窗口2\r\n");
	}

	lv_obj_move_background(lvgl_heart_main_cont);

	lv_obj_set_pos(lvgl_heart_main_cont, 0, 0);
	lvgl_set_obj_show(lvgl_heart_main_cont);

	lvgl_heart_anim_Jin();

}

void lvgl_heart_close(int dire)
{

	lvgl_task_delete(&heart_ChuangKou.lvgl_task);
	heart_ChuangKou.lvgl_task = NULL;

	// lvgl_heart_GongNeng_Data.point.y = lv_obj_get_y(lvgl_heart_main_cont);
	// lvgl_heart_GongNeng_Data.point.x = lv_obj_get_x(lvgl_heart_main_cont);

    if (dire == 0)
	{
		lvgl_clock_create(lv_scr_act());
	} else {
		lvgl_clock_create(lv_scr_act());
	}

}


void lvgl_heart_closed(void)
{
	heart_debug("删除窗口\r\n");
	heart_debug("closed\r\n");

	lvgl_heart_main_cont = NULL;
	// memset(&heart_ChuangKou, 0x00, sizeof(_heart_ChuangKou));
}


void lvgl_heart_TaskCb(lv_task_t *t)
{
	static int time = 0, bmp_qian_time = 0, bmp_qian_x = 0, bmp_qian_flag = 0,bmp_time = 0, bmp_cnt = 0, bmp_flag = 0;

	if (++bmp_cnt > 5)
	{
		bmp_cnt = 0;
	}
	// lvgl_walk_icon(bmp_cnt);



	// if (++bmp_qian_time > 2)
	// {
	// 	bmp_qian_time = 0;
	// 	if (bmp_qian_flag == 0)
	// 	{
	// 		if (--bmp_qian_x < -100)
	// 		{
	// 			bmp_qian_flag = 1;
	// 		}
	// 	}
	// 	else
	// 	{
	// 		if (++bmp_qian_x > -10)
	// 		{
	// 			bmp_qian_flag = 0;
	// 		}
	// 	}
	// 	lv_obj_set_x(heart_ChuangKou.lvgl_qian_image, bmp_qian_x);
	// 	lv_obj_invalidate(lvgl_heart_main_cont);
	// }
}

