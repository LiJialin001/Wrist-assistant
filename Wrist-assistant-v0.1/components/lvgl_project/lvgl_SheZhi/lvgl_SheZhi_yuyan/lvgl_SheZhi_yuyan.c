#include "lvgl_SheZhi_yuyan.h"
#include "lvgl_Project.h"
#include "lvgl_SheZhi.h"



_lvgl_SheZhi_yuyan_GongNeng_Data lvgl_SheZhi_yuyan_GongNeng_Data;
_SheZhi_yuyan_ChuangKou SheZhi_yuyan_ChuangKou;

lv_obj_t *lvgl_SheZhi_yuyan_main_cont = NULL;
lv_style_t lvgl_SheZhi_yuyan_style;
lv_task_t * lvgl_SheZhi_yuyan_task = NULL;

lv_obj_t *lvgl_SheZhi_yuyan_Button[SheZhi_yuyan_Button_Num];
lv_style_t lvgl_SheZhi_yuyan_Button_style[SheZhi_yuyan_Button_Num];
lv_obj_t *lvgl_SheZhi_yuyan_Label[SheZhi_yuyan_Button_Num];
lv_style_t lvgl_SheZhi_yuyan_Label_style[SheZhi_yuyan_Button_Num];


void lvgl_SheZhi_yuyan_button_cb(struct _lv_obj_t * obj, lv_event_t event)
{
	int i = 0;
	//printf("cb:%d\r\n", event);
	switch (event)
	{

	case LV_EVENT_PRESSING://对象被连续按下

		break;
	case LV_EVENT_PRESSED://对象已被按下


		break;


	case LV_EVENT_CLICKED://非拖动下释放
		if (lvgl_SheZhi_yuyan_GongNeng_Data.DongHua_Flag == false)
		{
			lvgl_SheZhi_yuyan_GongNeng_Data.DongHua_Flag = true;
		}
		else
		{
			break;
		}

		for (i = 0; i < SheZhi_yuyan_Button_Num; i++)
		{
			if (lvgl_SheZhi_yuyan_Button[i] == obj)
			{

				lvgl_SheZhi_yuyan_GongNeng_Data.AnXia_Num = i;
				printf("AnXia_Num:%d\r\n", lvgl_SheZhi_yuyan_GongNeng_Data.AnXia_Num);
				break;
			}
		}
		system_set_Language(lvgl_SheZhi_yuyan_GongNeng_Data.AnXia_Num);

		lvgl_SheZhi_yuyan_GongNeng_Data.AnXia_button = obj;
		lvgl_SheZhi_yuyan_anim_XuanZhong(lvgl_SheZhi_yuyan_GongNeng_Data.AnXia_button);
	break;





	case LV_EVENT_RELEASED://按钮释放


		break;


	case SheZhi_yuyan_event_anXia:

		if (0)//obj == lvgl_SheZhi_yuyan_Button[0])
		{
			lvgl_set_obj_hide(lvgl_SheZhi_yuyan_main_cont);
			lvgl_TianQi_create(lv_scr_act());
		}
		else
		{
			//lvgl_SheZhi_yuyan_anim_btn_item_jin();

		}
		lvgl_SheZhi_yuyan_GongNeng_Data.DongHua_Flag = false;
	break;

	case LV_EVENT_LONG_PRESSED://按钮长按



		break;
	default:
		break;

	}



}

void lvgl_SheZhi_yuyan_event_cb(struct _lv_obj_t * obj, lv_event_t event)
{
	if (obj == lvgl_SheZhi_yuyan_main_cont)
	{
		//SheZhi_yuyan_debug("cb:%d\r\n", event);
		switch (event)
		{

		case LV_EVENT_DELETE:

			lvgl_SheZhi_yuyan_main_cont = NULL;
			SheZhi_yuyan_debug("删除窗口\r\n");
			break;

		case LV_EVENT_PRESSING://对象被持续按下


			break;
		case LV_EVENT_PRESSED://对象已被按下


			break;
		case LV_EVENT_DRAG_END://拖动结束后

			lv_btn_set_state(SheZhi_yuyan_ChuangKou.btn_BiaoTi, LV_BTN_STATE_RELEASED);


			if (lv_obj_get_y(lvgl_SheZhi_yuyan_main_cont) != 0)
			{

				lv_obj_set_y(lvgl_SheZhi_yuyan_main_cont, 0);
			}

			if (lv_obj_get_x(lvgl_SheZhi_yuyan_main_cont) != 0)
			{
				if (lv_obj_get_x(lvgl_SheZhi_yuyan_main_cont) > 100)
				{


					lvgl_SheZhi_yuyan_close();


				}
				else
				{
					lv_obj_set_x(lvgl_SheZhi_yuyan_main_cont, 0);
				}
			}
			break;
			break;

		case LV_EVENT_RELEASED://按钮释放

		case LV_EVENT_LONG_PRESSED://按钮长按

			break;

		default:
			break;

		}

	}
}


void lvgl_SheZhi_yuyan_create(lv_obj_t * Fu,lv_obj_t *btn, lv_style_t*style,char *str,void *usr)
{

	static char flag = 0;
	if (flag == 0)
	{
		flag = 0;
	}

	if (lvgl_SheZhi_yuyan_main_cont == NULL)
	{

		lv_style_init(&lvgl_SheZhi_yuyan_style);
		lv_style_copy(&lvgl_SheZhi_yuyan_style, &lvgl_WuBianKuang_cont_style);
		/*渐变色*/
		lv_style_set_bg_opa(&lvgl_SheZhi_yuyan_style, LV_STATE_DEFAULT, LV_OPA_COVER);//背景透明度
		//lv_style_set_bg_color(&lvgl_SheZhi_yuyan_style, LV_STATE_DEFAULT, lv_color_hex(0x1b1d5c));//背景上面颜色
		//lv_style_set_bg_grad_color(&lvgl_SheZhi_yuyan_style, LV_STATE_DEFAULT, lv_color_hex(0x5c418d));//背景上面颜色
		lv_style_set_bg_color(&lvgl_SheZhi_yuyan_style, LV_STATE_DEFAULT, LV_COLOR_BLACK);//背景上面颜色
		lv_style_set_bg_grad_color(&lvgl_SheZhi_yuyan_style, LV_STATE_DEFAULT, LV_COLOR_BLACK);//背景上面颜色
		lv_style_set_bg_grad_dir(&lvgl_SheZhi_yuyan_style, LV_STATE_DEFAULT, LV_GRAD_DIR_VER);//渐变方向

		/*调整渐变色位置*/
		lv_style_set_bg_main_stop(&lvgl_SheZhi_yuyan_style, LV_STATE_DEFAULT, 10);
		lv_style_set_bg_main_stop(&lvgl_SheZhi_yuyan_style, LV_STATE_DEFAULT, 100);

		//----创建容器----//
		lvgl_SheZhi_yuyan_main_cont = lv_cont_create(Fu, NULL);
		lv_obj_set_pos(lvgl_SheZhi_yuyan_main_cont, 0, 0);
		lv_obj_set_size(lvgl_SheZhi_yuyan_main_cont, lv_obj_get_width(lv_scr_act()), lv_obj_get_height(lv_scr_act()));
		//lv_obj_set_drag_parent(lvgl_SheZhi_yuyan_main_cont, true); //启用 / 禁用父对象可拖动

		lv_obj_set_click(lvgl_SheZhi_yuyan_main_cont, true); //启用 / 禁用可点击
		lv_obj_set_drag(lvgl_SheZhi_yuyan_main_cont, true);//启用/禁用对象可拖动
		lv_obj_set_drag_dir(lvgl_SheZhi_yuyan_main_cont, LV_DRAG_DIR_ONE);//设置拖动方向
		lv_obj_set_drag_throw(lvgl_SheZhi_yuyan_main_cont, false);//启用/禁用拖动后是否有惯性移动

		//lv_obj_set_drag_parent(lvgl_SheZhi_yuyan_main_cont, true); //启用 / 禁用父对象可拖动
		lv_obj_add_style(lvgl_SheZhi_yuyan_main_cont, LV_OBJ_PART_MAIN, &lvgl_SheZhi_yuyan_style);//设置样式
		lv_obj_set_event_cb(lvgl_SheZhi_yuyan_main_cont, lvgl_SheZhi_yuyan_event_cb);//设置回调函数


//----标题----//
		lv_style_init(&SheZhi_yuyan_ChuangKou.label_BiaoTi_style);
		lv_style_copy(&SheZhi_yuyan_ChuangKou.label_BiaoTi_style, &lvgl_font24_style);

		SheZhi_yuyan_ChuangKou.btn_BiaoTi = lv_btn_create(lvgl_SheZhi_yuyan_main_cont, btn);

		lv_obj_set_pos(SheZhi_yuyan_ChuangKou.btn_BiaoTi, 5, 5);
		lv_obj_set_event_cb(SheZhi_yuyan_ChuangKou.btn_BiaoTi, NULL);

		SheZhi_yuyan_ChuangKou.label_BiaoTi = lv_label_create(lvgl_SheZhi_yuyan_main_cont, NULL);
		lv_label_set_text(SheZhi_yuyan_ChuangKou.label_BiaoTi, str);

		lv_label_set_long_mode(SheZhi_yuyan_ChuangKou.label_BiaoTi, LV_LABEL_LONG_SROLL_CIRC);//循环滚动
		lv_obj_set_pos(SheZhi_yuyan_ChuangKou.label_BiaoTi, 0, 8);
		lv_obj_set_width(SheZhi_yuyan_ChuangKou.label_BiaoTi, 240);
		lv_obj_set_height(SheZhi_yuyan_ChuangKou.label_BiaoTi, 40);
		lv_label_set_recolor(SheZhi_yuyan_ChuangKou.label_BiaoTi, true);
		lv_label_set_align(SheZhi_yuyan_ChuangKou.label_BiaoTi, LV_LABEL_ALIGN_CENTER);

		lv_label_set_anim_speed(SheZhi_yuyan_ChuangKou.label_BiaoTi, 20);

		lv_style_set_bg_color(&SheZhi_yuyan_ChuangKou.label_BiaoTi_style, LV_STATE_DEFAULT, lv_color_hex(SheZhi_yuyan_Color_weianxia));//背景上面颜色
		lv_style_set_bg_grad_color(&SheZhi_yuyan_ChuangKou.label_BiaoTi_style, LV_STATE_DEFAULT, lv_color_hex(SheZhi_yuyan_Color_weianxia));//背景上面颜色

		lv_obj_add_style(SheZhi_yuyan_ChuangKou.label_BiaoTi, LV_OBJ_PART_MAIN, &SheZhi_yuyan_ChuangKou.label_BiaoTi_style);
//----标题----//


//----选中时的背景----//

		lv_style_t *btn_XuanZhong_style;
		lv_obj_t *btn_XuanZhong;
		lv_style_init(&SheZhi_yuyan_ChuangKou.btn_XuanZhong_style);
		lv_style_copy(&SheZhi_yuyan_ChuangKou.btn_XuanZhong_style, &lvgl_WuBianKuang_cont_style);


		lv_style_set_radius(&SheZhi_yuyan_ChuangKou.btn_XuanZhong_style, LV_STATE_DEFAULT, 10);//圆角
		lv_style_set_bg_opa(&SheZhi_yuyan_ChuangKou.btn_XuanZhong_style, LV_STATE_DEFAULT, LV_OPA_50);//背景透明度

		lv_style_set_bg_color(&SheZhi_yuyan_ChuangKou.btn_XuanZhong_style, LV_STATE_DEFAULT, lv_color_hex(SheZhi_yuyan_Color_weianxia));//默认背景上面颜色
		lv_style_set_bg_grad_color(&SheZhi_yuyan_ChuangKou.btn_XuanZhong_style, LV_STATE_DEFAULT, lv_color_hex(SheZhi_yuyan_Color_weianxia));//默认背景上面颜色
		lv_style_set_bg_color(&SheZhi_yuyan_ChuangKou.btn_XuanZhong_style, LV_STATE_PRESSED, lv_color_hex(SheZhi_yuyan_Color_anxia));//按下时背景颜色
		lv_style_set_bg_grad_color(&SheZhi_yuyan_ChuangKou.btn_XuanZhong_style, LV_STATE_PRESSED, lv_color_hex(SheZhi_yuyan_Color_anxia));//按下时背景颜色


#if LV_USE_ANIMATION
			//Add a transition to the size change
		static lv_anim_path_t path;
		lv_anim_path_init(&path);
		lv_anim_path_set_cb(&path, lv_anim_path_overshoot);

		lv_style_set_transition_prop_1(&SheZhi_yuyan_ChuangKou.btn_XuanZhong_style, LV_STATE_DEFAULT, LV_STYLE_TRANSFORM_HEIGHT);
		lv_style_set_transition_prop_2(&SheZhi_yuyan_ChuangKou.btn_XuanZhong_style, LV_STATE_DEFAULT, LV_STYLE_TRANSFORM_WIDTH);
		lv_style_set_transition_time(&SheZhi_yuyan_ChuangKou.btn_XuanZhong_style, LV_STATE_DEFAULT, 200);
		lv_style_set_transition_path(&SheZhi_yuyan_ChuangKou.btn_XuanZhong_style, LV_STATE_DEFAULT, &path);
#endif
		SheZhi_yuyan_ChuangKou.btn_XuanZhong = lv_btn_create(lvgl_SheZhi_yuyan_main_cont, NULL);

		//lv_obj_move_foreground(SheZhi_yuyan_ChuangKou.btn_XuanZhong);//置顶

		lv_obj_set_pos(SheZhi_yuyan_ChuangKou.btn_XuanZhong, 5, -50);
		lv_obj_set_size(SheZhi_yuyan_ChuangKou.btn_XuanZhong, 230, 40);
		lv_obj_set_drag_parent(SheZhi_yuyan_ChuangKou.btn_XuanZhong, true); //启用 / 禁用父对象可拖动
		lv_obj_reset_style_list(SheZhi_yuyan_ChuangKou.btn_XuanZhong, LV_BTN_PART_MAIN);         //Remove the styles coming from the theme
		lv_obj_add_style(SheZhi_yuyan_ChuangKou.btn_XuanZhong, LV_BTN_PART_MAIN, &SheZhi_yuyan_ChuangKou.btn_XuanZhong_style);//设置样式

//----选中时的背景----//



		int i = 0;
		for (i = 0; i < SheZhi_yuyan_Button_Num; i++)
		{
			lv_style_init(&lvgl_SheZhi_yuyan_Button_style[i]);
			lv_style_copy(&lvgl_SheZhi_yuyan_Button_style[i], &lvgl_WuBianKuang_cont_style);

			lv_style_set_border_opa(&lvgl_SheZhi_yuyan_Button_style[i], LV_STATE_DEFAULT, LV_OPA_COVER);//边框透明度
			lv_style_set_border_width(&lvgl_SheZhi_yuyan_Button_style[i], LV_STATE_DEFAULT, 1);//边框宽度
			lv_style_set_border_color(&lvgl_SheZhi_yuyan_Button_style[i], LV_STATE_DEFAULT, LV_COLOR_BLACK);//边框颜色
			//lv_style_set_border_side(&lvgl_WuBianKuang_cont_style, LV_STATE_DEFAULT, LV_BORDER_SIDE_FULL);//边框模式

			lv_style_set_shadow_width(&lvgl_SheZhi_yuyan_Button_style[i], LV_STATE_DEFAULT, 0);//阴影宽度
			lv_style_set_shadow_opa(&lvgl_SheZhi_yuyan_Button_style[i], LV_STATE_DEFAULT, LV_OPA_80);//阴影透明度
			lv_style_set_shadow_color(&lvgl_SheZhi_yuyan_Button_style[i], LV_STATE_DEFAULT, LV_COLOR_BLACK);//阴影颜色

			lv_style_set_radius(&lvgl_SheZhi_yuyan_Button_style[i], LV_STATE_DEFAULT, 10);//圆角
			lv_style_set_bg_opa(&lvgl_SheZhi_yuyan_Button_style[i], LV_STATE_DEFAULT, LV_OPA_TRANSP);//背景透明度

			lv_style_set_bg_color(&lvgl_SheZhi_yuyan_Button_style[i], LV_STATE_DEFAULT, lv_color_hex(SheZhi_yuyan_Color_weianxia));//默认背景上面颜色
			lv_style_set_bg_grad_color(&lvgl_SheZhi_yuyan_Button_style[i], LV_STATE_DEFAULT, lv_color_hex(SheZhi_yuyan_Color_weianxia));//默认背景上面颜色
			lv_style_set_bg_color(&lvgl_SheZhi_yuyan_Button_style[i], LV_STATE_PRESSED, lv_color_hex(SheZhi_yuyan_Color_anxia));//按下时背景颜色
			lv_style_set_bg_grad_color(&lvgl_SheZhi_yuyan_Button_style[i], LV_STATE_PRESSED, lv_color_hex(SheZhi_yuyan_Color_anxia));//按下时背景颜色


			lv_style_set_border_color(&lvgl_SheZhi_yuyan_Button_style[i], LV_STATE_FOCUSED, LV_COLOR_BLUE);
			lv_style_set_border_color(&lvgl_SheZhi_yuyan_Button_style[i], LV_STATE_FOCUSED | LV_STATE_PRESSED, LV_COLOR_NAVY);


			lv_style_set_text_color(&lvgl_SheZhi_yuyan_Button_style[i], LV_STATE_DEFAULT, LV_COLOR_WHITE);
			lv_style_set_text_font(&lvgl_SheZhi_yuyan_Button_style[i], LV_STATE_DEFAULT, (const lv_font_t*)&lvgl_font24_style);

			lv_style_set_transform_height(&lvgl_SheZhi_yuyan_Button_style[i], LV_STATE_PRESSED, -5);
			lv_style_set_transform_width(&lvgl_SheZhi_yuyan_Button_style[i], LV_STATE_PRESSED, -10);
#if LV_USE_ANIMATION
			//Add a transition to the size change
			static lv_anim_path_t path;
			lv_anim_path_init(&path);
			lv_anim_path_set_cb(&path, lv_anim_path_overshoot);

			lv_style_set_transition_prop_1(&lvgl_SheZhi_yuyan_Button_style[i], LV_STATE_DEFAULT, LV_STYLE_TRANSFORM_HEIGHT);
			lv_style_set_transition_prop_2(&lvgl_SheZhi_yuyan_Button_style[i], LV_STATE_DEFAULT, LV_STYLE_TRANSFORM_WIDTH);
			lv_style_set_transition_time(&lvgl_SheZhi_yuyan_Button_style[i], LV_STATE_DEFAULT, 200);
			lv_style_set_transition_path(&lvgl_SheZhi_yuyan_Button_style[i], LV_STATE_DEFAULT, &path);
#endif
			lvgl_SheZhi_yuyan_Button[i] = lv_btn_create(lvgl_SheZhi_yuyan_main_cont, NULL);

			lv_obj_move_foreground(lvgl_SheZhi_yuyan_Button[i]);//置顶

			lv_obj_set_pos(lvgl_SheZhi_yuyan_Button[i], 5, 40 + i * SheZhi_yuyan_item_height);
			lv_obj_set_size(lvgl_SheZhi_yuyan_Button[i], 230, 40);
			lv_obj_set_drag_parent(lvgl_SheZhi_yuyan_Button[i], true); //启用 / 禁用父对象可拖动
			lv_obj_reset_style_list(lvgl_SheZhi_yuyan_Button[i], LV_BTN_PART_MAIN);         //Remove the styles coming from the theme
			lv_obj_add_style(lvgl_SheZhi_yuyan_Button[i], LV_BTN_PART_MAIN, &lvgl_SheZhi_yuyan_Button_style[i]);//设置样式

			lv_btn_set_layout(lvgl_SheZhi_yuyan_Button[i], LV_LAYOUT_OFF);//关闭对子对象布局

			//lv_btn_set_fit4(lvgl_SheZhi_yuyan_Button[i], LV_FIT_NONE, LV_FIT_TIGHT, LV_FIT_NONE, LV_FIT_NONE); ////设置宽度只在右边自适 应

			lv_obj_set_event_cb(lvgl_SheZhi_yuyan_Button[i], lvgl_SheZhi_yuyan_button_cb);//设置 btn3的事件回调
			lvgl_set_obj_show(lvgl_SheZhi_yuyan_Button[i]);

			lv_style_init(&lvgl_SheZhi_yuyan_Label_style[i]);
			lv_style_copy(&lvgl_SheZhi_yuyan_Label_style[i], &lvgl_font24_style);

			//----按钮上的文字----//
			lvgl_SheZhi_yuyan_Label[i] = lv_label_create(lvgl_SheZhi_yuyan_Button[i], NULL);   //Add a label to the button

			lv_label_set_long_mode(lvgl_SheZhi_yuyan_Label[i], LV_LABEL_LONG_SROLL_CIRC);//循环滚动
			lv_obj_set_pos(lvgl_SheZhi_yuyan_Label[i], 0, 0);
			lv_obj_set_width(lvgl_SheZhi_yuyan_Label[i], 190);
			lv_obj_set_height(lvgl_SheZhi_yuyan_Label[i], SheZhi_yuyan_item_height);
			lv_label_set_text(lvgl_SheZhi_yuyan_Label[i], (const char*)lvgl_globa_text[48+i][system_get_Language()]);
			lv_label_set_align(lvgl_SheZhi_yuyan_Label[i], LV_LABEL_ALIGN_CENTER);
			lv_label_set_recolor(lvgl_SheZhi_yuyan_Label[i], true);

			lv_obj_add_style(lvgl_SheZhi_yuyan_Label[i], LV_BTN_PART_MAIN, &lvgl_SheZhi_yuyan_Label_style[i]);

			lv_obj_align(lvgl_SheZhi_yuyan_Label[i], lvgl_SheZhi_yuyan_Button[i], LV_ALIGN_IN_BOTTOM_LEFT, 5, 12);

			//----按钮上的文字----//

		}

		SheZhi_yuyan_debug("创建窗口\r\n");
	}
	else
	{

		SheZhi_yuyan_debug("显示窗口\r\n");
	}

	lv_obj_move_background(lvgl_SheZhi_yuyan_main_cont);

	lv_obj_set_drag_throw(lvgl_SheZhi_yuyan_main_cont, false);//启用/禁用拖动后是否有惯性移动
	lv_obj_set_pos(lvgl_SheZhi_yuyan_main_cont, 0, 0);
	lvgl_set_obj_show(lvgl_SheZhi_yuyan_main_cont);

	lvgl_SheZhi_yuyan_GongNeng_Data.AnXia_button = lvgl_SheZhi_yuyan_Button[system_get_Language()];
	lvgl_SheZhi_yuyan_anim_XiaLa_Jin();

	lvgl_task_create(&lvgl_SheZhi_yuyan_task,lvgl_SheZhi_yuyan_TaskCb, 100, LV_TASK_PRIO_LOWEST, NULL);

}

const char * lvgl_SheZhi_yuyan_get_zhuangtai_str(void)
{

	return (const char*)lvgl_globa_text[48+system_get_Language()][system_get_Language()];
}


void lvgl_SheZhi_yuyan_close(void)
{

	lvgl_task_delete(&lvgl_SheZhi_yuyan_task);
	//lvgl_set_obj_hide(lvgl_SheZhi_yuyan_main_cont);

	lvgl_SheZhi_yuyan_GongNeng_Data.point.y = lv_obj_get_y(lvgl_SheZhi_yuyan_main_cont);
	lvgl_SheZhi_yuyan_GongNeng_Data.point.x = lv_obj_get_x(lvgl_SheZhi_yuyan_main_cont);

	//lv_obj_clean(lvgl_SheZhi_yuyan_main_cont);
	lv_obj_del(lvgl_SheZhi_yuyan_main_cont);

	lvgl_SheZhi_create(lv_scr_act());

}

void lvgl_SheZhi_yuyan_TaskCb(lv_task_t *t)
{
	static int time=0;

	if (lv_obj_get_y(lvgl_SheZhi_yuyan_main_cont) != 0)
	{
		lv_obj_set_drag_throw(lvgl_SheZhi_yuyan_main_cont, true);//启用/禁用拖动后是否有惯性移动

	}

	if (lv_obj_get_x(lvgl_SheZhi_yuyan_main_cont) != 0)
	{
		lv_obj_set_drag_throw(lvgl_SheZhi_yuyan_main_cont, false);//启用/禁用拖动后是否有惯性移动
		lv_btn_set_state(SheZhi_yuyan_ChuangKou.btn_BiaoTi, LV_BTN_STATE_PRESSED);
	}

}
