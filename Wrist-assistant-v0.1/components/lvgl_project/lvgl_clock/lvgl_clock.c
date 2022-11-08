#include "lvgl_clock.h"
#include "lvgl_Project.h"


_clock_ChuangKou clock_ChuangKou;

lv_obj_t *lvgl_clock_main_cont = NULL;
lv_style_t lvgl_clock_main_cont_style;
lv_style_t lvgl_clock_Line_BiaoPan_style;

lv_style_t lvgl_clock_Line_Shi_style;
lv_point_t line_points_Shi[2];
lv_obj_t * line_Shi = NULL;

lv_style_t lvgl_clock_Line_Fen_style;
lv_point_t line_points_Fen[2];
lv_obj_t * line_Fen = NULL;

lv_style_t lvgl_clock_Line_Miao_style;
lv_point_t line_points_Miao[2];
lv_obj_t * line_Miao = NULL;

lv_style_t lvgl_clock_Arc_style;
lv_obj_t * lvgl_clock_Arc = NULL;

lv_task_t * lvgl_clock_task = NULL;


_clock_Data clock_Data;

void lvgl_clock_event_cb(struct _lv_obj_t * obj, lv_event_t event)
{
	 if (obj == lvgl_clock_main_cont)
	{
		 //clock_debug("cb:%d\r\n", event);
		switch (event)
		{

		case LV_EVENT_DELETE:

			lvgl_clock_main_cont = NULL;
			clock_debug("删除窗口\r\n");
			break;

		case LV_EVENT_PRESSING://对象被持续按下
			//if (lv_obj_get_y(lvgl_clock_main_cont) < 0)
			//{
			//	lv_obj_set_y(lvgl_clock_main_cont, 0);
			//}

			break;
		case LV_EVENT_PRESSED://对象已被按下


			break;
		case LV_EVENT_DRAG_END://拖动结束后


			if (lv_obj_get_y(lvgl_clock_main_cont) !=0)
			{
				if(lv_obj_get_y(lvgl_clock_main_cont) > lvgl_ShuaXin_GaoDu)
				{
					lvgl_hint_create(lv_scr_act(),lvgl_globa_text[1][system_get_Language()],100,3);
					system_data.HuoQu_ShiJian_Flag=true;
					xSemaphoreGive(system_data.https_request_Semaphore);//释放信号量
					lv_obj_set_y(lvgl_clock_main_cont, 0);
				}
				// else 
				// if (lv_obj_get_y(lvgl_clock_main_cont) < -50)
				// {
				// 	lvgl_clock_hidden();
				// 	lvgl_SheZhi_create(lv_scr_act());
				// }
				else {
					lv_obj_set_y(lvgl_clock_main_cont, 0);
				}
				
			}

			if (lv_obj_get_x(lvgl_clock_main_cont) != 0)
			{
				if (lv_obj_get_x(lvgl_clock_main_cont) < -100)
				{
					lvgl_clock_close(0);
				}
				else
				if (lv_obj_get_x(lvgl_clock_main_cont) > 100)
				{
					lvgl_clock_close(1);
				}
				else
				{
					lv_obj_set_x(lvgl_clock_main_cont, 0);
				}
			}



			break;

		case LV_EVENT_RELEASED://按钮释放

		case LV_EVENT_LONG_PRESSED://按钮长按

			break;
		default:
			break;

		}
	}
}

#define HD_PI 0.0174f //3.1415926/18
lv_point_t line_points[12][2];
lv_obj_t * line[12];
void lvgl_clock_ShiZhong_Init(lv_obj_t * par,int x, int y)
{
	// int x1 = 0, y1 = 0,x2 = 0, y2 = 0;

	// int line_cnt = 0;


	lv_style_set_line_width(&lvgl_clock_Line_BiaoPan_style, LV_STATE_DEFAULT, 2);
	lv_style_set_line_color(&lvgl_clock_Line_BiaoPan_style, LV_STATE_DEFAULT, LV_COLOR_WHITE);
	lv_style_set_line_rounded(&lvgl_clock_Line_BiaoPan_style, LV_STATE_DEFAULT, true);


	for (int i = 0; i < 12; i ++)
	{
		line[i] = lv_line_create(par, NULL);//创建线条对象
		lv_obj_set_pos(line[i], 0, 0);//设置坐标
		lv_line_set_auto_size(line[i], true); //使能大小自适应
		//lv_line_set_points(line[i], line_points[i], 2);//设置坐标点集合
		lv_obj_add_style(line[i], LV_LINE_PART_MAIN, &lvgl_clock_Line_BiaoPan_style);//设置样式
	}

	lv_style_init(&lvgl_clock_Line_Miao_style);
	lv_style_set_line_width(&lvgl_clock_Line_Miao_style, LV_STATE_DEFAULT, 4);
	lv_style_set_line_color(&lvgl_clock_Line_Miao_style, LV_STATE_DEFAULT, LV_COLOR_RED);
	lv_style_set_line_rounded(&lvgl_clock_Line_Miao_style, LV_STATE_DEFAULT, true);//圆角

	lv_style_init(&lvgl_clock_Line_Fen_style);
	lv_style_set_line_width(&lvgl_clock_Line_Fen_style, LV_STATE_DEFAULT, 6);
	lv_style_set_line_color(&lvgl_clock_Line_Fen_style, LV_STATE_DEFAULT, LV_COLOR_WHITE);
	lv_style_set_line_rounded(&lvgl_clock_Line_Fen_style, LV_STATE_DEFAULT, true);//圆角

	lv_style_init(&lvgl_clock_Line_Shi_style);
	lv_style_set_line_width(&lvgl_clock_Line_Shi_style, LV_STATE_DEFAULT, 8);
	lv_style_set_line_color(&lvgl_clock_Line_Shi_style, LV_STATE_DEFAULT, LV_COLOR_WHITE);
	lv_style_set_line_rounded(&lvgl_clock_Line_Shi_style, LV_STATE_DEFAULT, true);//圆角

	line_Shi = lv_line_create(par, NULL);//创建线条对象
	lv_obj_set_pos(line_Shi, 0, 0);//设置坐标
	lv_line_set_auto_size(line_Shi, true); //使能大小自适应
	//lv_line_set_points(line_Shi, line_points_Miao, 2);//设置坐标点集合
	lv_obj_add_style(line_Shi, LV_LINE_PART_MAIN, &lvgl_clock_Line_Shi_style);//设置样式

	line_Fen = lv_line_create(par, NULL);//创建线条对象
	lv_obj_set_pos(line_Fen, 0, 0);//设置坐标
	lv_line_set_auto_size(line_Fen, true); //使能大小自适应
	//lv_line_set_points(line_Miao, line_points_Miao, 2);//设置坐标点集合
	lv_obj_add_style(line_Fen, LV_LINE_PART_MAIN, &lvgl_clock_Line_Fen_style);//设置样式

	line_Miao = lv_line_create(par, NULL);//创建线条对象
	lv_obj_set_pos(line_Miao, 0, 0);//设置坐标
	lv_line_set_auto_size(line_Miao, true); //使能大小自适应
	//lv_line_set_points(line_Miao, line_points_Miao, 2);//设置坐标点集合
	lv_obj_add_style(line_Miao, LV_LINE_PART_MAIN, &lvgl_clock_Line_Miao_style);//设置样式

	lv_style_init(&lvgl_clock_Arc_style);
	lv_style_copy(&lvgl_clock_Arc_style, &lvgl_WuBianKuang_cont_style);
	//lv_style_set_bg_opa(&lvgl_clock_Arc_style, LV_STATE_DEFAULT,);

	lv_style_set_line_width(&lvgl_clock_Arc_style, LV_STATE_DEFAULT, 10);
	lv_style_set_line_color(&lvgl_clock_Arc_style, LV_STATE_DEFAULT, LV_COLOR_BLUE);
	lv_style_set_line_opa(&lvgl_clock_Arc_style, LV_STATE_DEFAULT, 255);//线透明度
	lv_style_set_line_rounded(&lvgl_clock_Arc_style, LV_STATE_DEFAULT, true);//圆角
	lv_style_set_bg_opa(&lvgl_clock_Arc_style, LV_STATE_DEFAULT, 0);//背景透明度

	lvgl_clock_Arc = lv_arc_create(par, NULL);
	lv_obj_set_size(lvgl_clock_Arc,12,12);
	lv_obj_set_pos(lvgl_clock_Arc, x - 12 / 2, y-12/2);
	lv_arc_set_angles(lvgl_clock_Arc,0,360);
	lv_obj_add_style(lvgl_clock_Arc, LV_LINE_PART_MAIN, &lvgl_clock_Arc_style);//设置样式

}

void lvgl_clock_Draw_Miao(void)
{
	int x1 = 0, y1 = 0, x2 = 0, y2 = 0;

	int x = lv_obj_get_width(lvgl_clock_main_cont)/2;
	int y = lv_obj_get_height(lvgl_clock_main_cont)/2;

	clock_Data.Angle_Miao = (clock_Data.Miao * 0.6)-90;

	x1 = x + 105 * cos((clock_Data.Angle_Miao * HD_PI));
	y1 = y + 105 * sin((clock_Data.Angle_Miao * HD_PI));

	x2 = x + 0 * cos((clock_Data.Angle_Miao * HD_PI));
	y2 = y + 0 * sin((clock_Data.Angle_Miao * HD_PI));

	line_points_Miao[0].x = x1;
	line_points_Miao[0].y = y1;

	line_points_Miao[1].x = x2;
	line_points_Miao[1].y = y2;

	lv_line_set_points(line_Miao, line_points_Miao, 2);//设置坐标点集合
}

void lvgl_clock_Draw_Fen(void)
{
	int x1 = 0, y1 = 0, x2 = 0, y2 = 0;

	int x = lv_obj_get_width(lvgl_clock_main_cont)/2;
	int y = lv_obj_get_height(lvgl_clock_main_cont)/2;


	clock_Data.Angle_Fen = clock_Data.Fen * 6 +(clock_Data.Miao*0.01) - 90;

	x1 = x + 80 * cos((clock_Data.Angle_Fen * HD_PI));
	y1 = y + 80 * sin((clock_Data.Angle_Fen * HD_PI));

	x2 = x + 0 * cos((clock_Data.Angle_Fen * HD_PI));
	y2 = y + 0 * sin((clock_Data.Angle_Fen * HD_PI));

	line_points_Fen[0].x = x1;
	line_points_Fen[0].y = y1;

	line_points_Fen[1].x = x2;
	line_points_Fen[1].y = y2;

	lv_line_set_points(line_Fen, line_points_Fen, 2);//设置坐标点集合
}

void lvgl_clock_Draw_Shi(void)
{
	int x1 = 0, y1 = 0, x2 = 0, y2 = 0;

	int x = lv_obj_get_width(lvgl_clock_main_cont)/2;
	int y = lv_obj_get_height(lvgl_clock_main_cont)/2;

	clock_Data.Angle_Shi = clock_Data.Shi * 30 + (clock_Data.Fen*0.5) - 90;

	x1 = x + 60 * cos((clock_Data.Angle_Shi * HD_PI));
	y1 = y + 60 * sin((clock_Data.Angle_Shi * HD_PI));

	x2 = x + 0 * cos((clock_Data.Angle_Shi * HD_PI));
	y2 = y + 0 * sin((clock_Data.Angle_Shi * HD_PI));

	line_points_Shi[0].x = x1;
	line_points_Shi[0].y = y1;

	line_points_Shi[1].x = x2;
	line_points_Shi[1].y = y2;

	lv_line_set_points(line_Shi, line_points_Shi, 2);//设置坐标点集合
}
void lvgl_clock_create(lv_obj_t * Fu)
{

	if (lvgl_clock_main_cont == NULL)
	{

		lv_style_init(&lvgl_clock_Line_BiaoPan_style);

		lv_style_init(&lvgl_clock_main_cont_style);
		lv_style_copy(&lvgl_clock_main_cont_style, &lvgl_WuBianKuang_cont_style);
		/*渐变色*/
		lv_style_set_bg_opa(&lvgl_clock_main_cont_style, LV_STATE_DEFAULT, LV_OPA_COVER);//背景透明度
		lv_style_set_bg_color(&lvgl_clock_main_cont_style, LV_STATE_DEFAULT, lv_color_hex(0xBA55D3));//背景上面颜色
		lv_style_set_bg_grad_color(&lvgl_clock_main_cont_style, LV_STATE_DEFAULT, lv_color_hex(0xBA55D3));//背景上面颜色
		// lv_style_set_bg_color(&lvgl_clock_main_cont_style, LV_STATE_DEFAULT, LV_COLOR_BLACK);//背景上面颜色
		// lv_style_set_bg_grad_color(&lvgl_clock_main_cont_style, LV_STATE_DEFAULT, LV_COLOR_BLACK);//背景上面颜色
		lv_style_set_bg_grad_dir(&lvgl_clock_main_cont_style, LV_STATE_DEFAULT, LV_GRAD_DIR_VER);//渐变方向

		/*调整渐变色位置*/
		lv_style_set_bg_main_stop(&lvgl_clock_main_cont_style, LV_STATE_DEFAULT, 10);
		lv_style_set_bg_main_stop(&lvgl_clock_main_cont_style, LV_STATE_DEFAULT, 100);

		//----创建容器----//
		lvgl_clock_main_cont = lv_cont_create(Fu, NULL);
		lv_obj_set_pos(lvgl_clock_main_cont, 0, 0);
		lv_obj_set_size(lvgl_clock_main_cont, lv_obj_get_width(Fu), lv_obj_get_height(Fu));

		//lv_obj_set_click(lvgl_clock_main_cont, false); //启用 / 禁用可点击
		// lv_obj_set_drag(lvgl_clock_main_cont, true);//启用/禁用对象可拖动
		// lv_obj_set_drag_dir(lvgl_clock_main_cont, LV_DRAG_DIR_HOR);//设置拖动方向
		// lv_obj_set_drag_throw(lvgl_clock_main_cont, false);//启用/禁用拖动后是否有惯性移动
		//lv_obj_set_drag_parent(lvgl_clock_main_cont, false); //启用 / 禁用父对象可拖动

		lv_obj_add_style(lvgl_clock_main_cont, LV_OBJ_PART_MAIN, &lvgl_clock_main_cont_style);//设置样式
		lv_obj_set_event_cb(lvgl_clock_main_cont, lvgl_clock_event_cb);//设置回调函数

		// clock_Data.Miao = 0;
		// clock_Data.Fen = 15;
		// clock_Data.Shi = 0;

		lvgl_clock_ShiZhong_Init(lvgl_clock_main_cont, lv_obj_get_width(lvgl_clock_main_cont)/2, lv_obj_get_height(lvgl_clock_main_cont)/2);

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




		lv_anim_init(&clock_ChuangKou.lv_anim_Shi);
		//lv_anim_set_ready_cb(&clock_ChuangKou.lv_anim_Shi, clock_anim_Jin_ready_cb);
		lv_anim_set_exec_cb(&clock_ChuangKou.lv_anim_Shi, clock_anim_Shi_cb);
		lv_anim_set_values(&clock_ChuangKou.lv_anim_Shi, 0, 60);
		lv_anim_set_time(&clock_ChuangKou.lv_anim_Shi, 100);
		lv_anim_set_var(&clock_ChuangKou.lv_anim_Shi, NULL);
		lv_anim_set_path(&clock_ChuangKou.lv_anim_Shi, &path);


		lv_anim_init(&clock_ChuangKou.lv_anim_Fen);
		//lv_anim_set_ready_cb(&clock_ChuangKou.lv_anim_Fen, clock_anim_Jin_ready_cb);
		lv_anim_set_exec_cb(&clock_ChuangKou.lv_anim_Fen, clock_anim_Fen_cb);
		lv_anim_set_values(&clock_ChuangKou.lv_anim_Fen, 0, 80);
		lv_anim_set_time(&clock_ChuangKou.lv_anim_Fen, 150);
		lv_anim_set_var(&clock_ChuangKou.lv_anim_Fen, NULL);
		lv_anim_set_path(&clock_ChuangKou.lv_anim_Fen, &path);



		lv_anim_init(&clock_ChuangKou.lv_anim_Miao);
		lv_anim_set_ready_cb(&clock_ChuangKou.lv_anim_Miao, clock_anim_Miao_ready_cb);
		lv_anim_set_exec_cb(&clock_ChuangKou.lv_anim_Miao, clock_anim_Miao_cb);
		lv_anim_set_values(&clock_ChuangKou.lv_anim_Miao, 0, 105);
		lv_anim_set_time(&clock_ChuangKou.lv_anim_Miao, 200);
		lv_anim_set_var(&clock_ChuangKou.lv_anim_Miao, NULL);
		lv_anim_set_path(&clock_ChuangKou.lv_anim_Miao, &path);

		clock_anim_ShiJian_Zou_Init();

		system_data.HuoQu_ShiJian_Flag = true;//同步时间
		clock_debug("创建窗口create\r\n");
	}
	else
	{

		clock_debug("显示窗口show\r\n");
	}

	lv_obj_move_background(lvgl_clock_main_cont);  

	lv_obj_set_pos(lvgl_clock_main_cont, 0, 0);
	lvgl_set_obj_show(lvgl_clock_main_cont);

	clock_anim_DongHua_Jin();
}

void lvgl_clock_hidden(void)
{
	lvgl_set_obj_hide(lvgl_clock_main_cont);
	lv_obj_set_click(lvgl_clock_main_cont, false); //启用 / 禁用可点击
	lv_obj_set_drag(lvgl_clock_main_cont, false);//启用/禁用对象可拖动
	lv_obj_set_drag_dir(lvgl_clock_main_cont, LV_DRAG_DIR_ONE);//设置拖动方向
}

void lvgl_clock_close(int dire)
{

	lvgl_task_delete(&lvgl_clock_task);
	lvgl_clock_task=NULL;

	lv_obj_del(lvgl_clock_main_cont);
	if (dire == 0)
	{
		lvgl_TianQi_create(lv_scr_act());
	}
	else if (dire == 1)
	{
		lvgl_heart_create(lv_scr_act());
	}else {
		lvgl_SheZhi_create(lv_scr_act());
	}

	//lvgl_set_obj_hide(lvgl_clock_main_cont);
	// lvgl_set_obj_hide(line_Shi);
	// lvgl_set_obj_hide(line_Fen);
	// lvgl_set_obj_hide(line_Miao);
}
void clock_TaskCb(lv_task_t *t)
{
#if lvgl_win
	clock_Data.Miao += 10;
	if (clock_Data.Miao >= 600-1)
	{
		clock_Data.Miao = 0;

		clock_Data.Fen += 1;
		if (clock_Data.Fen >= 60-1)
		{
			clock_Data.Fen = 0;
			clock_Data.Shi += 1;
			if (clock_Data.Shi >= 12)
				clock_Data.Shi = 0;
		}
	}
#endif

	clock_anim_Miao_Zou(clock_Data.Miao);

	//clock_debug("S:%d F:%d M:%d\r\n", clock_Data.Shi, clock_Data.Fen, clock_Data.Miao);
	//lvgl_clock_Draw_Miao();
	lvgl_clock_Draw_Fen();
	lvgl_clock_Draw_Shi();
}

void clock_anim_Jin_ready_cb(lv_anim_t * anim)
{

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

	lv_anim_set_ready_cb(&clock_ChuangKou.lv_anim, clock_anim_Chu_ready_cb);
	lv_anim_set_exec_cb(&clock_ChuangKou.lv_anim, clock_anim_Chu_cb);
	lv_anim_set_values(&clock_ChuangKou.lv_anim, 0, 100);
	lv_anim_set_time(&clock_ChuangKou.lv_anim, 300);
	lv_anim_set_var(&clock_ChuangKou.lv_anim, NULL);

	lv_anim_set_path(&clock_ChuangKou.lv_anim, &path);
	lv_anim_start(&clock_ChuangKou.lv_anim);
}

void clock_anim_Chu_ready_cb(lv_anim_t * anim)
{

	lv_anim_del(&clock_ChuangKou.lv_anim, NULL);

	lvgl_set_obj_show(line_Shi);
	lvgl_set_obj_show(line_Fen);
	lvgl_set_obj_show(line_Miao);


	lv_anim_start(&clock_ChuangKou.lv_anim_Shi);
	lv_anim_start(&clock_ChuangKou.lv_anim_Fen);
	lv_anim_start(&clock_ChuangKou.lv_anim_Miao);




}


void clock_anim_Chu_cb(void * arc, lv_anim_value_t v)
{
	int x1 = 0, y1 = 0, x2 = 0, y2 = 0;

	int x = lv_obj_get_width(lvgl_clock_main_cont)/2;
	int y = lv_obj_get_height(lvgl_clock_main_cont)/2;

	int line_cnt = 0;
	//clock_debug("time %d:\r\n", v);
	for (int i = 0; i < 360; i += 30)
	{
		//x1 = x + (v+10) * cos((i * HD_PI));
		//y1 = y + (v+10) * sin((i * HD_PI));
		x1 = x + 110 * cos((i * HD_PI));
		y1 = y + 110 * sin((i * HD_PI));
		x2 = x + v * cos((i * HD_PI));
		y2 = y + v * sin((i * HD_PI));

		line_points[line_cnt][0].x = x1;
		line_points[line_cnt][0].y = y1;

		line_points[line_cnt][1].x = x2;
		line_points[line_cnt][1].y = y2;

		lv_obj_set_pos(line[line_cnt], 0, 0);//设置坐标
		lv_line_set_points(line[line_cnt], line_points[line_cnt], 2);//设置坐标点集合
		line_cnt++;
	}
}

void clock_anim_Jin_cb(void * arc, lv_anim_value_t v)
{
	int x1 = 0, y1 = 0, x2 = 0, y2 = 0;

	int x = lv_obj_get_width(lvgl_clock_main_cont)/2;
	int y = lv_obj_get_height(lvgl_clock_main_cont)/2;

	int line_cnt = 0;
	//clock_debug("time %d:\r\n", v);
	for (int i = 0; i < 360; i += 30)
	{
		x1 = x + 110 * cos((i * HD_PI));
		y1 = y + 110 * sin((i * HD_PI));

		x2 = x + v * cos((i * HD_PI));
		y2 = y + v * sin((i * HD_PI));

		line_points[line_cnt][0].x = x1;
		line_points[line_cnt][0].y = y1;

		line_points[line_cnt][1].x = x2;
		line_points[line_cnt][1].y = y2;

		lv_obj_set_pos(line[line_cnt], 0, 0);//设置坐标
		lv_line_set_points(line[line_cnt], line_points[line_cnt], 2);//设置坐标点集合
		line_cnt++;
	}

}


//滑入动画
void clock_anim_DongHua_Jin(void)
{

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

	lv_anim_init(&clock_ChuangKou.lv_anim);
	lv_anim_set_ready_cb(&clock_ChuangKou.lv_anim, clock_anim_Jin_ready_cb);
	lv_anim_set_exec_cb(&clock_ChuangKou.lv_anim, clock_anim_Jin_cb);
	lv_anim_set_values(&clock_ChuangKou.lv_anim, 100, 5);
	lv_anim_set_time(&clock_ChuangKou.lv_anim, 150);
	lv_anim_set_var(&clock_ChuangKou.lv_anim, NULL);

	lv_anim_set_path(&clock_ChuangKou.lv_anim, &path);
	lv_anim_start(&clock_ChuangKou.lv_anim);

}

void clock_anim_Shi_cb(void * arc, lv_anim_value_t v)
{
	int x1 = 0, y1 = 0, x2 = 0, y2 = 0;

	int x = lv_obj_get_width(lvgl_clock_main_cont)/2;
	int y = lv_obj_get_height(lvgl_clock_main_cont)/2;

	clock_Data.Angle_Shi = clock_Data.Shi * 30 + (clock_Data.Fen*0.5) - 90;

	x1 = x + v * cos((clock_Data.Angle_Shi * HD_PI));
	y1 = y + v * sin((clock_Data.Angle_Shi * HD_PI));

	x2 = x + 0 * cos((clock_Data.Angle_Shi * HD_PI));
	y2 = y + 0 * sin((clock_Data.Angle_Shi * HD_PI));

	line_points_Shi[0].x = x1;
	line_points_Shi[0].y = y1;

	line_points_Shi[1].x = x2;
	line_points_Shi[1].y = y2;

	lv_line_set_points(line_Shi, line_points_Shi, 2);//设置坐标点集合

}

void clock_anim_Fen_cb(void * arc, lv_anim_value_t v)
{
	int x1 = 0, y1 = 0, x2 = 0, y2 = 0;

	int x = lv_obj_get_width(lvgl_clock_main_cont)/2;
	int y = lv_obj_get_height(lvgl_clock_main_cont)/2;

	clock_Data.Angle_Fen = clock_Data.Fen * 6 + (clock_Data.Miao*0.01) - 90;

	x1 = x + v * cos((clock_Data.Angle_Fen * HD_PI));
	y1 = y + v * sin((clock_Data.Angle_Fen * HD_PI));

	x2 = x + 0 * cos((clock_Data.Angle_Fen * HD_PI));
	y2 = y + 0 * sin((clock_Data.Angle_Fen * HD_PI));

	line_points_Fen[0].x = x1;
	line_points_Fen[0].y = y1;

	line_points_Fen[1].x = x2;
	line_points_Fen[1].y = y2;

	lv_line_set_points(line_Fen, line_points_Fen, 2);//设置坐标点集合

}

void clock_anim_Miao_cb(void * arc, lv_anim_value_t v)
{
	int x1 = 0, y1 = 0, x2 = 0, y2 = 0;

	int x = lv_obj_get_width(lvgl_clock_main_cont)/2;
	int y = lv_obj_get_height(lvgl_clock_main_cont)/2;

	clock_Data.Angle_Miao = (clock_Data.Miao * 0.6) - 90;

	x1 = x + v * cos((clock_Data.Angle_Miao * HD_PI));
	y1 = y + v * sin((clock_Data.Angle_Miao * HD_PI));

	x2 = x + 0 * cos((clock_Data.Angle_Miao * HD_PI));
	y2 = y + 0 * sin((clock_Data.Angle_Miao * HD_PI));

	line_points_Miao[0].x = x1;
	line_points_Miao[0].y = y1;

	line_points_Miao[1].x = x2;
	line_points_Miao[1].y = y2;

	lv_line_set_points(line_Miao, line_points_Miao, 2);//设置坐标点集合

}

void clock_anim_Miao_ready_cb(lv_anim_t * anim)
{

	lvgl_task_create(&lvgl_clock_task,clock_TaskCb, 1000, LV_TASK_PRIO_LOWEST, NULL);

	lv_obj_set_drag_dir(lvgl_clock_main_cont, LV_DRAG_DIR_ONE);//设置拖动方向
}

void clock_anim_Miao_Zou_cb(void * arc, lv_anim_value_t v)
{
	int x1 = 0, y1 = 0, x2 = 0, y2 = 0;

	int x = lv_obj_get_width(lvgl_clock_main_cont)/2;
	int y = lv_obj_get_height(lvgl_clock_main_cont)/2;

	clock_Data.Angle_Miao = (v * 0.6) - 90;

	x1 = x + 105 * cos((clock_Data.Angle_Miao * HD_PI));
	y1 = y + 105 * sin((clock_Data.Angle_Miao * HD_PI));

	x2 = x + 0 * cos((clock_Data.Angle_Miao * HD_PI));
	y2 = y + 0 * sin((clock_Data.Angle_Miao * HD_PI));

	line_points_Miao[0].x = x1;
	line_points_Miao[0].y = y1;

	line_points_Miao[1].x = x2;
	line_points_Miao[1].y = y2;

	lv_line_set_points(line_Miao, line_points_Miao, 2);//设置坐标点集合
}

void clock_anim_ShiJian_Zou_Init(void)
{
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

	lv_anim_init(&clock_ChuangKou.lv_anim_Miao_Zou);
	lv_anim_set_ready_cb(&clock_ChuangKou.lv_anim_Miao_Zou, NULL);
	lv_anim_set_exec_cb(&clock_ChuangKou.lv_anim_Miao_Zou, clock_anim_Miao_Zou_cb);
	lv_anim_set_values(&clock_ChuangKou.lv_anim_Miao_Zou, 100, 5);
	lv_anim_set_time(&clock_ChuangKou.lv_anim_Miao_Zou, 200);
	lv_anim_set_var(&clock_ChuangKou.lv_anim_Miao_Zou, NULL);

	lv_anim_set_path(&clock_ChuangKou.lv_anim_Miao_Zou, &path);


}
void clock_anim_Miao_Zou(int dat)
{
	static int old = 0;

	if (dat == 0)
	{
		dat = 600;
		old = 590;
	}
	//if (dat - old > 10)
	old = dat - 10;

	//clock_debug("old:%d dat:%d\r\n",old,dat);

	lv_anim_set_values(&clock_ChuangKou.lv_anim_Miao_Zou, old, dat);
	lv_anim_set_time(&clock_ChuangKou.lv_anim_Miao_Zou, 150);
	lv_anim_start(&clock_ChuangKou.lv_anim_Miao_Zou);
	//old = dat;

	// if (dat == 600)
	// {
	// 	old = 0;
	// }


}



