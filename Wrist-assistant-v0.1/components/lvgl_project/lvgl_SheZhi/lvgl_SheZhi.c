#include "lvgl_SheZhi.h"
#include "lvgl_Project.h"


_lvgl_SheZhi_GongNeng_Data lvgl_SheZhi_GongNeng_Data;
_SheZhi_ChuangKou SheZhi_ChuangKou;

lv_obj_t *lvgl_SheZhi_main_cont = NULL;
lv_style_t lvgl_SheZhi_style;


lv_obj_t *lvgl_SheZhi_Button[SheZhi_Button_Num];
lv_obj_t *lvgl_SheZhi_Label[SheZhi_Button_Num];
lv_style_t lvgl_SheZhi_Button_style[SheZhi_Button_Num];


lv_area_t SheZhi_BUTTON_area[] =
{
	{5,40,230,40},{5,85,230,40},
	{5,130,230,40},{5,175,230,40},
	{5,145,70,80},{80,145,155,80},
	{5,230,113,75},{123,230,112,75},
	{5,310,155,65},{165,310,70,65},
	{5,380,113,80},{123,380,113,80},

	{5,465,230,130},
};


uint32_t SheZhi_BUTTON_color[][2]=
{
	{0Xff00ff,0Xbc0cc1},{0X8cc63f,0X678931},
	{0X22b573,0X1a7047},{0X2e3192,0X1e2259},
	{0X998675,0X5b5148},{0X29abe2,0X1f7b9b},
	{0Xd4145a,0X991349},{0Xf7931e,0Xba6919},
	{0Xff00ff,0Xa809ad},{0X8cc63f,0X5c7c2a},
	{0Xa67c52,0X75583d},{0Xd9e021,0X999916},

	{0X333333,0X1c1c1c},
};



static void lvgl_SheZhi_switch_cb(lv_obj_t * obj, lv_event_t event)
{
	switch (event)
	{

	case LV_EVENT_VALUE_CHANGED:
		if (obj == SheZhi_ChuangKou.switch_wifi)
		{
			system_set_wifi_kaiguan(lv_switch_get_state(obj));


			if (system_get_wifi_kaiguan() == true)
			{
				if (system_data.WIFI_Sta == true)
				{
					lv_label_set_text(SheZhi_ChuangKou.label_wifi_zhuangtai, system_data.wifi_name);
				}
				else
				{
					lv_label_set_text(SheZhi_ChuangKou.label_wifi_zhuangtai, lvgl_globa_text[42+0][system_get_Language()]);
				}
			}
			else
			{
				lv_label_set_text(SheZhi_ChuangKou.label_wifi_zhuangtai, lvgl_globa_text[42+1][system_get_Language()]);
			}

		}


		break;
	}

}


void lvgl_SheZhi_button_cb(struct _lv_obj_t * obj, lv_event_t event)
{
	int i = 0;
	//printf("cb:%d\r\n", event);
	switch (event)
	{


	case LV_EVENT_DELETE:

		//*obj = NULL;
		//SheZhi_debug("删除窗口 DELETE2\r\n");
		break;

	case LV_EVENT_PRESSING://对象被连续按下

		break;
	case LV_EVENT_PRESSED://对象已被按下

		break;

	case LV_EVENT_CLICKED://非拖动下释放
		if (lvgl_SheZhi_GongNeng_Data.DongHua_Flag == false)
		{
			lvgl_SheZhi_GongNeng_Data.DongHua_Flag = true;
		}
		else
		{
			break;
		}

		for (i = 0; i < SheZhi_Button_Num; i++)
		{
			if (lvgl_SheZhi_Button[i] == obj)
			{

				lvgl_SheZhi_GongNeng_Data.AnXia_Num = i;
				printf("AnXia_Num:%d\r\n", lvgl_SheZhi_GongNeng_Data.AnXia_Num);
				break;
			}
		}


		if (lvgl_SheZhi_GongNeng_Data.AnXia_Num==0)
		{
			if (system_get_wifi_kaiguan() == false)
			{
				lvgl_SheZhi_GongNeng_Data.DongHua_Flag = false;
				lvgl_hint_create(lv_scr_act(), lvgl_globa_text[42+1][system_get_Language()], 200, 3);
				break;
			}

		}


		lvgl_SheZhi_GongNeng_Data.AnXia_button = obj;
		lvgl_SheZhi_DongHua_Chu();

		//if (obj == lvgl_SheZhi_Button[0])
		//{
		//	lvgl_SheZhi_GongNeng_Data.AnXia_Num = 0;
		//	lvgl_SheZhi_DongHua_Chu();
		//}
		//else
		//if (obj == lvgl_SheZhi_Button[1])
		//{
		//	lvgl_SheZhi_GongNeng_Data.AnXia_Num = 1;
		//	lvgl_SheZhi_DongHua_Chu();
		//}
	break;





	case LV_EVENT_RELEASED://按钮释放


		break;


	case SheZhi_event_anXia:

		if (obj == lvgl_SheZhi_Button[0])
		{

			lvgl_set_obj_hide(lvgl_SheZhi_main_cont);

			lvgl_SheZhi_wifi_create(
				lv_scr_act(),
				lvgl_SheZhi_GongNeng_Data.AnXia_button,
				SheZhi_BUTTON_color[lvgl_SheZhi_GongNeng_Data.AnXia_Num][0],
				SheZhi_BUTTON_color[lvgl_SheZhi_GongNeng_Data.AnXia_Num][1],
				lvgl_globa_text[27+lvgl_SheZhi_GongNeng_Data.AnXia_Num + 1][system_get_Language()],
				NULL
			);

		}
		if (obj == lvgl_SheZhi_Button[1])
		{
			lvgl_set_obj_hide(lvgl_SheZhi_main_cont);

			lvgl_SheZhi_yuyan_create(
				lv_scr_act(),
				lvgl_SheZhi_GongNeng_Data.AnXia_button,
				&lvgl_SheZhi_Button_style[lvgl_SheZhi_GongNeng_Data.AnXia_Num],
				lvgl_globa_text[27+lvgl_SheZhi_GongNeng_Data.AnXia_Num + 1][system_get_Language()],
				NULL
			);
		}else
		{
			lvgl_SheZhi_DongHua_Jin();

		}

		lvgl_SheZhi_GongNeng_Data.DongHua_Flag = false;
	break;

	case LV_EVENT_LONG_PRESSED://按钮长按



		break;
	default:
		break;

	}



}

void lvgl_SheZhi_event_cb(struct _lv_obj_t * obj, lv_event_t event)
{
	if (obj == lvgl_SheZhi_main_cont)
	{
		//printf("cb:%d\r\n", event);
		switch (event)
		{

		case LV_EVENT_DELETE:
			lvgl_SheZhi_closed();


			break;

		case LV_EVENT_PRESSING://对象被持续按下


			break;
		case LV_EVENT_PRESSED://对象已被按下


			break;
		case LV_EVENT_DRAG_END://拖动结束后


			if (lv_obj_get_y(lvgl_SheZhi_main_cont) > 0)
			{

				lv_obj_set_y(lvgl_SheZhi_main_cont, 0);

			}else if (lv_obj_get_y(lvgl_SheZhi_main_cont) < -(lv_obj_get_height(lvgl_SheZhi_main_cont)-240))
			{

				lv_obj_set_y(lvgl_SheZhi_main_cont, -(lv_obj_get_height(lvgl_SheZhi_main_cont) - 240));

			}

			if (lv_obj_get_x(lvgl_SheZhi_main_cont) != 0)
			{
				if (lv_obj_get_x(lvgl_SheZhi_main_cont) > 100)
				{
					lvgl_SheZhi_close();
				}
				else
				{
					lv_obj_set_x(lvgl_SheZhi_main_cont, 0);
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



void lvgl_SheZhi_create(lv_obj_t * Fu)
{
	int i = 0;

	if (lvgl_SheZhi_main_cont == NULL)
	{

		lv_style_init(&lvgl_SheZhi_style);
		lv_style_copy(&lvgl_SheZhi_style, &lvgl_WuBianKuang_cont_style);

		//----创建容器----//
		lvgl_SheZhi_main_cont = lv_cont_create(Fu, NULL);
		lv_obj_set_pos(lvgl_SheZhi_main_cont, 0, 0);
		lv_obj_set_size(lvgl_SheZhi_main_cont, lv_obj_get_width(lv_scr_act()), lv_obj_get_height(lv_scr_act()));

		// lv_obj_set_click(lvgl_SheZhi_main_cont, true); //启用 / 禁用可点击
		// lv_obj_set_drag(lvgl_SheZhi_main_cont, true);//启用/禁用对象可拖动
		// lv_obj_set_drag_dir(lvgl_SheZhi_main_cont, LV_DRAG_DIR_ONE);//设置拖动方向
		// lv_obj_set_drag_throw(lvgl_SheZhi_main_cont, false);//启用/禁用拖动后是否有惯性移动

		//lv_obj_set_drag_parent(lvgl_SheZhi_main_cont, true); //启用 / 禁用父对象可拖动
		lv_obj_add_style(lvgl_SheZhi_main_cont, LV_OBJ_PART_MAIN, &lvgl_SheZhi_style);//设置样式
		lv_obj_set_event_cb(lvgl_SheZhi_main_cont, lvgl_SheZhi_event_cb);//设置回调函数


//----标题----//

		lv_style_init(&SheZhi_ChuangKou.label_BiaoTi_style);
		lv_style_copy(&SheZhi_ChuangKou.label_BiaoTi_style, &lvgl_font24_style);

		SheZhi_ChuangKou.label_BiaoTi = lv_label_create(lvgl_SheZhi_main_cont, NULL);

		lv_label_set_long_mode(SheZhi_ChuangKou.label_BiaoTi, LV_LABEL_LONG_SROLL_CIRC);//循环滚动
		lv_obj_set_pos(SheZhi_ChuangKou.label_BiaoTi, 0, 8);
		lv_obj_set_width(SheZhi_ChuangKou.label_BiaoTi, 240);
		lv_obj_set_height(SheZhi_ChuangKou.label_BiaoTi, 40);
		lv_label_set_recolor(SheZhi_ChuangKou.label_BiaoTi, true);
		lv_label_set_align(SheZhi_ChuangKou.label_BiaoTi, LV_LABEL_ALIGN_CENTER);

		lv_label_set_anim_speed(SheZhi_ChuangKou.label_BiaoTi, 20);
		lv_label_set_text(SheZhi_ChuangKou.label_BiaoTi, lvgl_globa_text[27+0][system_get_Language()]);

		lv_style_set_bg_color(&SheZhi_ChuangKou.label_BiaoTi_style, LV_STATE_DEFAULT, lv_color_hex(SheZhi_Color_weianxia));//背景上面颜色
		lv_style_set_bg_grad_color(&SheZhi_ChuangKou.label_BiaoTi_style, LV_STATE_DEFAULT, lv_color_hex(SheZhi_Color_weianxia));//背景上面颜色

		lv_obj_add_style(SheZhi_ChuangKou.label_BiaoTi, LV_OBJ_PART_MAIN, &SheZhi_ChuangKou.label_BiaoTi_style);
//----标题----//


		for (i = 0; i < SheZhi_Button_Num; i++)
		{
			lv_style_init(&lvgl_SheZhi_Button_style[i]);
			lv_style_copy(&lvgl_SheZhi_Button_style[i], &lvgl_WuBianKuang_cont_style);
			lv_style_set_radius(&lvgl_SheZhi_Button_style[i], LV_STATE_DEFAULT, 10);//圆角
			lv_style_set_shadow_width(&lvgl_SheZhi_Button_style[i], LV_STATE_DEFAULT, 0);//阴影宽度
			lv_style_set_shadow_opa(&lvgl_SheZhi_Button_style[i], LV_STATE_DEFAULT, LV_OPA_TRANSP);//阴影透明度
			lv_style_set_bg_opa(&lvgl_SheZhi_Button_style[i], LV_STATE_DEFAULT, LV_OPA_COVER);//背景透明度
#if 0
			lv_style_set_bg_color(&lvgl_SheZhi_Button_style[i], LV_STATE_DEFAULT, lv_color_hex(SheZhi_Color_weianxia));//背景上面颜色
			lv_style_set_bg_grad_color(&lvgl_SheZhi_Button_style[i], LV_STATE_DEFAULT, lv_color_hex(SheZhi_Color_weianxia));//背景上面颜色
			lv_style_set_bg_color(&lvgl_SheZhi_Button_style[i], LV_STATE_PRESSED, lv_color_hex(SheZhi_Color_anxia));
			lv_style_set_bg_grad_color(&lvgl_SheZhi_Button_style[i], LV_STATE_PRESSED, lv_color_hex(SheZhi_Color_anxia));
#else
			lv_style_set_bg_color(&lvgl_SheZhi_Button_style[i], LV_STATE_DEFAULT, lv_color_hex(SheZhi_BUTTON_color[i][0]));//背景上面颜色
			lv_style_set_bg_grad_color(&lvgl_SheZhi_Button_style[i], LV_STATE_DEFAULT, lv_color_hex(SheZhi_BUTTON_color[i][0]));//背景上面颜色

			lv_style_set_bg_color(&lvgl_SheZhi_Button_style[i], LV_STATE_PRESSED, lv_color_hex(SheZhi_BUTTON_color[i][1]));
			lv_style_set_bg_grad_color(&lvgl_SheZhi_Button_style[i], LV_STATE_PRESSED, lv_color_hex(SheZhi_BUTTON_color[i][1]));

#endif

			lv_style_set_border_color(&lvgl_SheZhi_Button_style[i], LV_STATE_FOCUSED, LV_COLOR_BLUE);
			lv_style_set_border_color(&lvgl_SheZhi_Button_style[i], LV_STATE_FOCUSED | LV_STATE_PRESSED, LV_COLOR_NAVY);


			lv_style_set_text_color(&lvgl_SheZhi_Button_style[i], LV_STATE_DEFAULT, LV_COLOR_WHITE);
			lv_style_set_text_font(&lvgl_SheZhi_Button_style[i], LV_STATE_DEFAULT, (const lv_font_t*)&lvgl_font24_style);

			lv_style_set_transform_height(&lvgl_SheZhi_Button_style[i], LV_STATE_PRESSED, -5);
			lv_style_set_transform_width(&lvgl_SheZhi_Button_style[i], LV_STATE_PRESSED, -10);
#if LV_USE_ANIMATION
			//Add a transition to the size change
			static lv_anim_path_t path;
			lv_anim_path_init(&path);
			lv_anim_path_set_cb(&path, lv_anim_path_overshoot);

			lv_style_set_transition_prop_1(&lvgl_SheZhi_Button_style[i], LV_STATE_DEFAULT, LV_STYLE_TRANSFORM_HEIGHT);
			lv_style_set_transition_prop_2(&lvgl_SheZhi_Button_style[i], LV_STATE_DEFAULT, LV_STYLE_TRANSFORM_WIDTH);
			lv_style_set_transition_time(&lvgl_SheZhi_Button_style[i], LV_STATE_DEFAULT, 200);
			lv_style_set_transition_path(&lvgl_SheZhi_Button_style[i], LV_STATE_DEFAULT, &path);
#endif


			lvgl_SheZhi_Button[i] = lv_btn_create(lvgl_SheZhi_main_cont,NULL);

			lv_btn_set_layout(lvgl_SheZhi_Button[i], LV_LAYOUT_OFF);//关闭对子对象布局


			lv_obj_set_pos(lvgl_SheZhi_Button[i], 5, 40+i* SheZhi_item_height);
			lv_obj_set_size(lvgl_SheZhi_Button[i], 230, 40);
			lv_obj_set_drag_parent(lvgl_SheZhi_Button[i], true); //启用 / 禁用父对象可拖动
			lv_obj_reset_style_list(lvgl_SheZhi_Button[i], LV_BTN_PART_MAIN);
			lv_obj_add_style(lvgl_SheZhi_Button[i], LV_BTN_PART_MAIN, &lvgl_SheZhi_Button_style[i]);//设置样式

			//添加文字
			lvgl_SheZhi_Label[i] = lv_label_create(lvgl_SheZhi_Button[i], NULL);
			lv_label_set_text(lvgl_SheZhi_Label[i], lvgl_globa_text[27+i+1][system_get_Language()]);
			lv_obj_align(lvgl_SheZhi_Label[i], lvgl_SheZhi_Button[i], LV_ALIGN_IN_LEFT_MID, 5, 0);//设置对齐方式
			lv_obj_set_event_cb(lvgl_SheZhi_Button[i], lvgl_SheZhi_button_cb);//设置 btn的事件回调
		}


		//----创建wifi上的开关按钮与文字----//
		lv_btn_set_layout(lvgl_SheZhi_Button[0], LV_LAYOUT_OFF);//关闭对子对象布局
		SheZhi_ChuangKou .switch_wifi = lv_switch_create(lvgl_SheZhi_Button[0], NULL);
		lv_obj_set_size(SheZhi_ChuangKou.switch_wifi,40,24);//设置大小
		lv_obj_reset_style_list(SheZhi_ChuangKou.switch_wifi, LV_SWITCH_PART_BG);//清除背景样式
		lv_obj_add_style(SheZhi_ChuangKou.switch_wifi, LV_SWITCH_PART_BG,&lvgl_switch_background_style);//添加背景样式
		lv_obj_add_style(SheZhi_ChuangKou.switch_wifi, LV_SWITCH_PART_INDIC, &lvgl_switch_on_style);//开的区域
		lv_obj_add_style(SheZhi_ChuangKou.switch_wifi, LV_SWITCH_PART_KNOB, &lvgl_switch_knob_style);//指示器

		lv_obj_align(SheZhi_ChuangKou.switch_wifi, NULL, LV_ALIGN_IN_RIGHT_MID, -10, 0);//设置对齐方式
		lv_obj_set_event_cb(SheZhi_ChuangKou.switch_wifi, lvgl_SheZhi_switch_cb);//设置 btn的事件回调

		SheZhi_ChuangKou.label_wifi_zhuangtai = lv_label_create(lvgl_SheZhi_Button[0], NULL);
		lv_label_set_long_mode(SheZhi_ChuangKou.label_wifi_zhuangtai, LV_LABEL_LONG_SROLL_CIRC);//循环滚动
		lv_obj_set_pos(SheZhi_ChuangKou.label_wifi_zhuangtai, 62, 7);
		lv_obj_set_width(SheZhi_ChuangKou.label_wifi_zhuangtai, 120);
		lv_obj_set_height(SheZhi_ChuangKou.label_wifi_zhuangtai, lv_obj_get_height(lvgl_SheZhi_Button[0]));
		lv_label_set_align(SheZhi_ChuangKou.label_wifi_zhuangtai, LV_LABEL_ALIGN_CENTER);
		lv_label_set_recolor(SheZhi_ChuangKou.label_wifi_zhuangtai, true);
		lv_obj_add_style(SheZhi_ChuangKou.label_wifi_zhuangtai, LV_OBJ_PART_MAIN, &lvgl_font24_style);
		lv_label_set_anim_speed(SheZhi_ChuangKou.label_wifi_zhuangtai, 20);
		//----创建wifi上的开关按钮与文字----//

		//----创建语言状态显示文字----//
		SheZhi_ChuangKou.label_yuyan_zhuangtai = lv_label_create(lvgl_SheZhi_Button[1], NULL);
		lv_label_set_long_mode(SheZhi_ChuangKou.label_yuyan_zhuangtai, LV_LABEL_LONG_SROLL_CIRC);//循环滚动
		lv_obj_set_pos(SheZhi_ChuangKou.label_yuyan_zhuangtai, 85, 7);
		lv_obj_set_width(SheZhi_ChuangKou.label_yuyan_zhuangtai, 120);
		lv_obj_set_height(SheZhi_ChuangKou.label_yuyan_zhuangtai, lv_obj_get_height(lvgl_SheZhi_Button[0]));
		lv_label_set_align(SheZhi_ChuangKou.label_yuyan_zhuangtai, LV_LABEL_ALIGN_CENTER);
		lv_label_set_recolor(SheZhi_ChuangKou.label_yuyan_zhuangtai, true);
		lv_obj_add_style(SheZhi_ChuangKou.label_yuyan_zhuangtai, LV_OBJ_PART_MAIN, &lvgl_font24_style);
		lv_label_set_anim_speed(SheZhi_ChuangKou.label_yuyan_zhuangtai, 20);
		//----创建语言状态显示文字----//



		lv_obj_set_size(lvgl_SheZhi_main_cont, 240, 40+i* SheZhi_item_height);

		if(lv_obj_get_height(lvgl_SheZhi_main_cont)<lv_obj_get_height(lv_scr_act()))
		{
			lv_obj_set_size(lvgl_SheZhi_main_cont, lv_obj_get_width(lv_scr_act()), lv_obj_get_height(lv_scr_act()));
		}

		lvgl_task_create(&SheZhi_ChuangKou.lvgl_task,lvgl_SheZhi_TaskCb, 200, LV_TASK_PRIO_LOWEST, NULL);

		SheZhi_debug("创建窗口\r\n");
	}
	else
	{

		SheZhi_debug("显示窗口\r\n");
	}

	lv_obj_move_background(lvgl_SheZhi_main_cont);


	lv_obj_set_drag_throw(lvgl_SheZhi_main_cont, false);//启用/禁用拖动后是否有惯性移动
	lv_obj_set_x(lvgl_SheZhi_main_cont, 0);
	lvgl_set_obj_show(lvgl_SheZhi_main_cont);

	//----设置条目中的文字----//
	for (i = 0; i < SheZhi_Button_Num; i++)
	{

		lv_label_set_text(lvgl_SheZhi_Label[i], lvgl_globa_text[27+i + 1][system_get_Language()]);
	}
	//----设置条目中的文字----//


	//----显示语言上面的状态文字----//
	lv_label_set_text(SheZhi_ChuangKou.label_yuyan_zhuangtai, lvgl_SheZhi_yuyan_get_zhuangtai_str());
	//----显示语言上面的状态文字----//

	//----设置wifi开关按钮与文字----//
	//system_set_wifi_kaiguan(false);
	if (system_get_wifi_kaiguan() == true)
	{
		lv_switch_on(SheZhi_ChuangKou.switch_wifi, LV_ANIM_ON);//设置状态 ,并带有动画效果
		if (system_data.WIFI_Sta==true)
		{
			lv_label_set_text(SheZhi_ChuangKou.label_wifi_zhuangtai, system_data.wifi_name);
		}
		else
		{
			lv_label_set_text(SheZhi_ChuangKou.label_wifi_zhuangtai, lvgl_globa_text[42+0][system_get_Language()]);
		}
	}
	else
	{
		lv_switch_off(SheZhi_ChuangKou.switch_wifi, LV_ANIM_ON);//设置状态 ,并带有动画效果
		lv_label_set_text(SheZhi_ChuangKou.label_wifi_zhuangtai, lvgl_globa_text[42+1][system_get_Language()]);
	}
	//----设置wifi开关按钮与文字----//



	lvgl_SheZhi_DongHua_Jin();
}


void lvgl_SheZhi_TaskCb(lv_task_t *t)
{

	if (lv_obj_get_y(lvgl_SheZhi_main_cont) != 0)
	{
		lv_obj_set_drag_throw(lvgl_SheZhi_main_cont, true);//启用/禁用拖动后是否有惯性移动
	}

	if (lv_obj_get_x(lvgl_SheZhi_main_cont) != 0)
	{
		lv_obj_set_drag_throw(lvgl_SheZhi_main_cont, false);//启用/禁用拖动后是否有惯性移动
	}
}


void lvgl_SheZhi_close(void)
{
	SheZhi_debug("开始关闭窗口 close\r\n");

	lvgl_clock_create(lv_scr_act());

	lvgl_task_delete(&SheZhi_ChuangKou.lvgl_task);

	lv_obj_clean(lvgl_SheZhi_main_cont);

	lvgl_SheZhi_GongNeng_Data.point.y = lv_obj_get_y(lvgl_SheZhi_main_cont);
	lvgl_SheZhi_GongNeng_Data.point.x = lv_obj_get_x(lvgl_SheZhi_main_cont);

	//uint16_t count = lv_obj_count_children(lvgl_SheZhi_main_cont);

	//printf("count:%d\r\n", count);

	lv_obj_del(lvgl_SheZhi_main_cont);
}

void lvgl_SheZhi_closed(void)
{

	SheZhi_debug("closed\r\n");
	SheZhi_debug("删除窗口\r\n");

	memset(&SheZhi_ChuangKou, 0x00, sizeof(SheZhi_ChuangKou));

	lvgl_SheZhi_main_cont = NULL;
}

