#include "lvgl_bpm.h"
#include "lvgl_Project.h"

_lvgl_bpm_Func_Data lvgl_bpm_Func_Data;
_bpm_page bpm_page;

lv_style_t lvgl_WuBianKuang_cont_style;

lv_obj_t *lvgl_bpm_main_cont = NULL;
lv_style_t lvgl_bpm_style;
lv_task_t * lvgl_bpm_task = NULL;

lv_obj_t *lvgl_bpm_Label[2];

lv_area_t bpm_Label_area[] =
{
	{5,5,125,65},{135,5,100,65}
};

uint32_t bpm_Label_color[][2]=
{
	{0Xff00ff,0Xbc0cc1},{0X8cc63f,0X678931}
};

lv_style_t lvgl_bpm_Backgroud_style;

void lvgl_bpm_create(lv_obj_t * Fu)
{
	if (lvgl_bpm_main_cont == NULL)
	{
		lv_style_init(&lvgl_bpm_Backgroud_style);
		lv_style_copy(&lvgl_bpm_Backgroud_style, &lvgl_WuBianKuang_cont_style);

		/*渐变色*/
		lv_style_set_bg_opa(&lvgl_bpm_Backgroud_style, LV_STATE_DEFAULT, LV_OPA_COVER);//背景透明度
		lv_style_set_bg_color(&lvgl_bpm_Backgroud_style, LV_STATE_DEFAULT, LV_COLOR_BLACK);//背景上面颜色
		lv_style_set_bg_grad_color(&lvgl_bpm_Backgroud_style, LV_STATE_DEFAULT, LV_COLOR_BLACK);//背景上面颜色

		lv_obj_add_style(lv_scr_act(), LV_OBJ_PART_MAIN, &lvgl_bpm_Backgroud_style);//设置样式

		lv_style_init(&lvgl_bpm_style);
		lv_style_copy(&lvgl_bpm_style, &lvgl_WuBianKuang_cont_style);
		/*渐变色*/
		lv_style_set_bg_opa(&lvgl_bpm_style, LV_STATE_DEFAULT, LV_OPA_COVER);//背景透明度
		//lv_style_set_bg_color(&lvgl_bpm_style, LV_STATE_DEFAULT, lv_color_hex(0x1b1d5c));//背景上面颜色
		//lv_style_set_bg_grad_color(&lvgl_bpm_style, LV_STATE_DEFAULT, lv_color_hex(0x5c418d));//背景上面颜色
		lv_style_set_bg_color(&lvgl_bpm_style, LV_STATE_DEFAULT, LV_COLOR_BLACK);//背景上面颜色
		lv_style_set_bg_grad_color(&lvgl_bpm_style, LV_STATE_DEFAULT, LV_COLOR_BLACK);//背景上面颜色
		lv_style_set_bg_grad_dir(&lvgl_bpm_style, LV_STATE_DEFAULT, LV_GRAD_DIR_VER);//渐变方向

		/*调整渐变色位置*/
		lv_style_set_bg_main_stop(&lvgl_bpm_style, LV_STATE_DEFAULT, 10);
		lv_style_set_bg_main_stop(&lvgl_bpm_style, LV_STATE_DEFAULT, 100);

		//----创建容器----//
		lvgl_bpm_main_cont = lv_cont_create(Fu, NULL);
		lv_obj_set_pos(lvgl_bpm_main_cont, 0, 0);
		lv_obj_set_size(lvgl_bpm_main_cont, lv_obj_get_width(Fu), 600);
		//lv_obj_set_drag_parent(lvgl_bpm_main_cont, true); //启用 / 禁用父对象可拖动

		// lv_obj_set_click(lvgl_bpm_main_cont, true); //启用 / 禁用可点击
		// lv_obj_set_drag(lvgl_bpm_main_cont, true);//启用/禁用对象可拖动
		// lv_obj_set_drag_dir(lvgl_bpm_main_cont, LV_DRAG_DIR_ONE);//设置拖动方向
		// lv_obj_set_drag_throw(lvgl_bpm_main_cont, false);//启用/禁用拖动后是否有惯性移动

		//lv_obj_set_drag_parent(lvgl_bpm_main_cont, true); //启用 / 禁用父对象可拖动
		lv_obj_add_style(lvgl_bpm_main_cont, LV_OBJ_PART_MAIN, &lvgl_bpm_style);//设置样式
		// lv_obj_set_event_cb(lvgl_bpm_main_cont, lvgl_desktop_event_cb);//设置回调函数

#if 0
		for (int i = 0; i < desktop_Button_Num; i++)
		{
			lv_style_init(&lvgl_desktop_Button_style[i]);
			lv_style_copy(&lvgl_desktop_Button_style[i], &lvgl_WuBianKuang_cont_style);
			lv_style_set_radius(&lvgl_desktop_Button_style[i], LV_STATE_DEFAULT, 10);//圆角
			lv_style_set_shadow_width(&lvgl_desktop_Button_style[i], LV_STATE_DEFAULT, 0);//阴影宽度
			lv_style_set_shadow_opa(&lvgl_desktop_Button_style[i], LV_STATE_DEFAULT, LV_OPA_TRANSP);//阴影透明度
			lv_style_set_bg_opa(&lvgl_desktop_Button_style[i], LV_STATE_DEFAULT, LV_OPA_COVER);//背景透明度
			lv_style_set_bg_color(&lvgl_desktop_Button_style[i], LV_STATE_DEFAULT, lv_color_hex(desktop_BUTTON_color[i][0]));//背景上面颜色
			lv_style_set_bg_grad_color(&lvgl_desktop_Button_style[i], LV_STATE_DEFAULT, lv_color_hex(desktop_BUTTON_color[i][0]));//背景上面颜色

			lv_style_set_bg_color(&lvgl_desktop_Button_style[i], LV_STATE_PRESSED, lv_color_hex(desktop_BUTTON_color[i][1]));
			lv_style_set_bg_grad_color(&lvgl_desktop_Button_style[i], LV_STATE_PRESSED, lv_color_hex(desktop_BUTTON_color[i][1]));

			lv_style_set_border_color(&lvgl_desktop_Button_style[i], LV_STATE_FOCUSED, LV_COLOR_BLUE);
			lv_style_set_border_color(&lvgl_desktop_Button_style[i], LV_STATE_FOCUSED | LV_STATE_PRESSED, LV_COLOR_NAVY);

			lv_style_set_text_color(&lvgl_desktop_Button_style[i], LV_STATE_DEFAULT, LV_COLOR_WHITE);
			lv_style_set_text_font(&lvgl_desktop_Button_style[i], LV_STATE_DEFAULT, (const lv_font_t*)&font_ChangYongHanZi_24);

			lv_style_set_transform_height(&lvgl_desktop_Button_style[i], LV_STATE_PRESSED, -5);
			lv_style_set_transform_width(&lvgl_desktop_Button_style[i], LV_STATE_PRESSED, -10);
#if LV_USE_ANIMATION
			//Add a transition to the size change
			static lv_anim_path_t path;
			lv_anim_path_init(&path);
			lv_anim_path_set_cb(&path, lv_anim_path_overshoot);

			lv_style_set_transition_prop_1(&lvgl_desktop_Button_style[i], LV_STATE_DEFAULT, LV_STYLE_TRANSFORM_HEIGHT);
			lv_style_set_transition_prop_2(&lvgl_desktop_Button_style[i], LV_STATE_DEFAULT, LV_STYLE_TRANSFORM_WIDTH);
			lv_style_set_transition_time(&lvgl_desktop_Button_style[i], LV_STATE_DEFAULT, 200);
			lv_style_set_transition_path(&lvgl_desktop_Button_style[i], LV_STATE_DEFAULT, &path);
#endif

			lvgl_desktop_Button[i] = lv_btn_create(lvgl_bpm_main_cont,NULL);

			lv_obj_set_pos(lvgl_desktop_Button[i], desktop_BUTTON_area[i].x1, desktop_BUTTON_area[i].y1);
			lv_obj_set_size(lvgl_desktop_Button[i], desktop_BUTTON_area[i].x2, desktop_BUTTON_area[i].y2);

			lv_obj_set_drag_parent(lvgl_desktop_Button[i], true); //启用 / 禁用父对象可拖动

			lv_obj_reset_style_list(lvgl_desktop_Button[i], LV_BTN_PART_MAIN);         /*Remove the styles coming from the theme*/
			lv_obj_add_style(lvgl_desktop_Button[i], LV_BTN_PART_MAIN, &lvgl_desktop_Button_style[i]);//设置样式

			lvgl_desktop_Label[i] = lv_label_create(lvgl_desktop_Button[i], NULL);          /*Add a label to the button*/


			lv_obj_set_event_cb(lvgl_desktop_Button[i], lvgl_desktop_button_cb);//设置 btn3的事件回调
		}
#endif

		lvgl_task_create(&lvgl_bpm_task,lvgl_bpm_TaskCb, 200, LV_TASK_PRIO_LOWEST, NULL);
		bpm_debug("创建窗口\r\n");
	}
	else
	{
		bpm_debug("显示窗口\r\n");
	}
	for (int i = 0; i < 2; i++)
	{
		lv_label_set_text(lvgl_bpm_Label[i], lvgl_globa_text[i+2][0]);  /*Set the labels text*/  // ToDo: 语言切换
	}

	lv_obj_move_background(lvgl_bpm_main_cont);

	lv_obj_set_drag_throw(lvgl_bpm_main_cont, false);//启用/禁用拖动后是否有惯性移动
	lvgl_set_obj_show(lvgl_bpm_main_cont);

	//lvgl_task_create(&lvgl_desktop_task,lvgl_desktop_TaskCb, 200, LV_TASK_PRIO_LOWEST, NULL);
}

void lvgl_bpm_hidden(void)
{
	lvgl_set_obj_hide(lvgl_bpm_main_cont);
	lv_obj_set_click(lvgl_bpm_main_cont, false); //启用 / 禁用可点击
	lv_obj_set_drag(lvgl_bpm_main_cont, false);//启用/禁用对象可拖动
	lv_obj_set_drag_dir(lvgl_bpm_main_cont, LV_DRAG_DIR_ONE);//设置拖动方向
}

void lvgl_bpm_close(void)
{
	lvgl_set_obj_hide(lvgl_bpm_main_cont);
	lv_obj_set_x(lvgl_bpm_main_cont,0);
	lvgl_bpm_Func_Data.point.y = lv_obj_get_y(lvgl_bpm_main_cont);
	lvgl_bpm_Func_Data.point.x = lv_obj_get_x(lvgl_bpm_main_cont);

	// lvgl_clock_create(lv_scr_act());
}

void lvgl_bpm_TaskCb(lv_task_t *t)
{
	if (lv_obj_get_y(lvgl_bpm_main_cont) != 0)
	{
		lv_obj_set_drag_throw(lvgl_bpm_main_cont, true);//启用/禁用拖动后是否有惯性移动
	}

	if (lv_obj_get_x(lvgl_bpm_main_cont) != 0)
	{
		lv_obj_set_drag_throw(lvgl_bpm_main_cont, false);//启用/禁用拖动后是否有惯性移动
	}
}

