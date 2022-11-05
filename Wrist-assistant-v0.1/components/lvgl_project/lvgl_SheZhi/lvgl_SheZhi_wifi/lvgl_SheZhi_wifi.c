#include "lvgl_SheZhi_wifi.h"
#include "lvgl_Project.h"
#include "lvgl_SheZhi.h"



_lvgl_SheZhi_wifi_GongNeng_Data lvgl_SheZhi_wifi_GongNeng_Data;
_SheZhi_wifi_ChuangKou SheZhi_wifi_ChuangKou;

lv_obj_t *lvgl_SheZhi_wifi_main_cont = NULL;
lv_style_t lvgl_SheZhi_wifi_style;
lv_task_t * lvgl_SheZhi_wifi_task = NULL;

lv_obj_t *lvgl_SheZhi_wifi_Button[SheZhi_wifi_Button_Num];
lv_style_t lvgl_SheZhi_wifi_Button_style[SheZhi_wifi_Button_Num];
lv_obj_t *lvgl_SheZhi_wifi_Label[SheZhi_wifi_Button_Num];
lv_style_t lvgl_SheZhi_wifi_Label_style[SheZhi_wifi_Button_Num];



const char*SheZhi_wifi_TEXT[][SYSTEM_LANGUAGE_NUM] =
{
	{ "WIFI", "WIFI", "WIFI", NULL},
	{ "Refreshing", "Refreshing", "Refreshing", NULL},
	{ "Input password", "Input password", "Input password", NULL},
	{ "Connecting...", "Connecting...", "Connecting...", NULL},
	{ "Please input.", "Please input.", "Please input.", NULL},
	{ "WiFi Connected", "WiFi Connected", "WiFi Connected", NULL},
};


void lvgl_shezhi_wifi_lianjie_cb(char * text, void *dat)
{
	lvgl_chulizhong_close();
}


//输入退出时执行的回调函数
void lvgl_SheZhi_wifi_shuru_cb(char * text,void *dat)
{
	int flag = *((int*)dat);

	printf("flag:%d\r\n",flag);
	printf("str:%s\r\n", text);
	if (flag == true)
	{
		if (strlen(text) > 0)
		{

			lvgl_SheZhi_wifi_GongNeng_Data.wifi_lianjie_flag = true;

			// lvgl_chulizhong_create
			// (
			// 	lv_layer_top(),
			// 	SheZhi_wifi_TEXT[3][system_get_Language()],
			// 	lvgl_SheZhi_wifi_GongNeng_Data.color,
			// 	lvgl_SheZhi_wifi_GongNeng_Data.anxia_color,
			// 	NULL
			// );



			// wifi_lianjie(1,
			// 	lv_label_get_text(lvgl_SheZhi_wifi_Label[lvgl_SheZhi_wifi_GongNeng_Data.AnXia_Num]),
			// 	text,
			// 	NULL//lvgl_shezhi_wifi_lianjie_cb
			// );

			memset(system_data.wifi_name,0x00,sizeof(system_data.wifi_name));
			memset(system_data.wifi_password,0x00,sizeof(system_data.wifi_password));

			memcpy(system_data.wifi_name,lv_label_get_text(lvgl_SheZhi_wifi_Label[lvgl_SheZhi_wifi_GongNeng_Data.AnXia_Num]),strlen(lv_label_get_text(lvgl_SheZhi_wifi_Label[lvgl_SheZhi_wifi_GongNeng_Data.AnXia_Num])));
			memcpy(system_data.wifi_password,text,strlen(text));


			system_save_config();

			system_data.set_connect_wifi_flag = true;
			//lvgl_hint_create(lv_scr_act(),"请重启连接新的wifi",200,20);
			xSemaphoreGive(system_data.https_request_Semaphore);//释放信号量
		}
		else
		{
			lvgl_hint_create(lv_scr_act(), SheZhi_wifi_TEXT[4][system_get_Language()], 120,3);
		}
	}
}



void lvgl_SheZhi_wifi_button_cb(struct _lv_obj_t * obj, lv_event_t event)
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
		if (lvgl_SheZhi_wifi_GongNeng_Data.DongHua_Flag == false)
		{
			lvgl_SheZhi_wifi_GongNeng_Data.DongHua_Flag = true;
		}
		else
		{
			break;
		}

		for (i = 0; i < SheZhi_wifi_Button_Num; i++)
		{
			if (lvgl_SheZhi_wifi_Button[i] == obj)
			{

				lvgl_SheZhi_wifi_GongNeng_Data.AnXia_Num = i;
				printf("AnXia_Num:%d\r\n", lvgl_SheZhi_wifi_GongNeng_Data.AnXia_Num);
				break;
			}
		}

		lvgl_SheZhi_wifi_GongNeng_Data.AnXia_button = obj;

		if(lvgl_SheZhi_wifi_GongNeng_Data.wifi_dangqian_num == lvgl_SheZhi_wifi_GongNeng_Data.AnXia_Num)
		{
			lvgl_SheZhi_wifi_GongNeng_Data.DongHua_Flag = false;
			lvgl_SheZhi_wifi_GongNeng_Data.wifi_lianjie_flag = true;
			lvgl_hint_create(lv_scr_act(), SheZhi_wifi_TEXT[5][system_get_Language()], 120,3);

		}else
		if (1)//obj == lvgl_SheZhi_wifi_Button[0])
		{
			lvgl_SheZhi_wifi_GongNeng_Data.DongHua_Flag = false;

			sprintf(lvgl_SheZhi_wifi_GongNeng_Data.buf,"%s:%s",
				SheZhi_wifi_TEXT[2][system_get_Language()],
				lv_label_get_text(lvgl_SheZhi_wifi_Label[lvgl_SheZhi_wifi_GongNeng_Data.AnXia_Num])
				);
			lvgl_shurufa_create
			(
				lv_scr_act(),
				lvgl_SheZhi_wifi_Label[lvgl_SheZhi_wifi_GongNeng_Data.AnXia_Num],
				lvgl_SheZhi_wifi_GongNeng_Data.buf,
				type_lable,
				lvgl_SheZhi_wifi_GongNeng_Data.color,
				lvgl_SheZhi_wifi_GongNeng_Data.anxia_color,
				lvgl_SheZhi_wifi_shuru_cb
			);
		}
		else
		{
			lvgl_SheZhi_wifi_DongHua_Chu();
		}
	break;


	case LV_EVENT_RELEASED://按钮释放


	break;


	case SheZhi_wifi_event_anXia:


		lvgl_SheZhi_wifi_anim_btn_item_jin();

		lvgl_SheZhi_wifi_GongNeng_Data.DongHua_Flag = false;
	break;

	case LV_EVENT_LONG_PRESSED://按钮长按



		break;
	default:
		break;

	}
}

void lvgl_SheZhi_wifi_event_cb(struct _lv_obj_t * obj, lv_event_t event)
{
	if (obj == lvgl_SheZhi_wifi_main_cont)
	{
		//SheZhi_wifi_debug("cb:%d\r\n", event);
		switch (event)
		{

		case lvgl_shuaxin_jieshu_event:

			lvgl_SheZhi_wifi_ShuaXin_jieshu();
			break;

		case LV_EVENT_DELETE:

			lvgl_SheZhi_wifi_main_cont = NULL;
			SheZhi_wifi_debug("删除窗口\r\n");
			break;

		case LV_EVENT_PRESSING://对象被持续按下


			break;
		case LV_EVENT_PRESSED://对象已被按下


			break;
		case LV_EVENT_DRAG_END://拖动结束后

			lv_btn_set_state(SheZhi_wifi_ChuangKou.btn_BiaoTi, LV_BTN_STATE_RELEASED);


			if (lv_obj_get_y(lvgl_SheZhi_wifi_main_cont) > lvgl_ShuaXin_GaoDu)
			{

				lvgl_SheZhi_wifi_ShuaXin_KaiShi();


			}
			else if (lv_obj_get_y(lvgl_SheZhi_wifi_main_cont) > 0 && lv_obj_get_y(lvgl_SheZhi_wifi_main_cont) < lvgl_ShuaXin_GaoDu)
			{
				lvgl_SheZhi_wifi_GongNeng_Data.ShuaXin_Sta = lvgl_ShuaXin_JieShu;

				lv_obj_set_y(lvgl_SheZhi_wifi_main_cont, 0);
			}
			else if (lv_obj_get_y(lvgl_SheZhi_wifi_main_cont) < -(lv_obj_get_height(lvgl_SheZhi_wifi_main_cont) - 240))
			{

				lv_obj_set_y(lvgl_SheZhi_wifi_main_cont, -(lv_obj_get_height(lvgl_SheZhi_wifi_main_cont) - 240));

			}


			if (lv_obj_get_x(lvgl_SheZhi_wifi_main_cont) != 0)
			{
				if (lv_obj_get_x(lvgl_SheZhi_wifi_main_cont) > 100)
				{


					lvgl_SheZhi_wifi_close();


				}
				else
				{
					lv_obj_set_x(lvgl_SheZhi_wifi_main_cont, 0);
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


void lvgl_SheZhi_wifi_create(lv_obj_t * Fu,lv_obj_t *btn, uint32_t color, uint32_t anxia_color, char *str,void *usr)
{
	lvgl_SheZhi_wifi_GongNeng_Data.color = color;
	lvgl_SheZhi_wifi_GongNeng_Data.anxia_color = anxia_color;

	if (lvgl_SheZhi_wifi_main_cont == NULL)
	{

		lv_style_init(&lvgl_SheZhi_wifi_style);
		lv_style_copy(&lvgl_SheZhi_wifi_style, &lvgl_WuBianKuang_cont_style);
		/*渐变色*/
		lv_style_set_bg_opa(&lvgl_SheZhi_wifi_style, LV_STATE_DEFAULT, LV_OPA_COVER);//背景透明度
		//lv_style_set_bg_color(&lvgl_SheZhi_wifi_style, LV_STATE_DEFAULT, lv_color_hex(0x1b1d5c));//背景上面颜色
		//lv_style_set_bg_grad_color(&lvgl_SheZhi_wifi_style, LV_STATE_DEFAULT, lv_color_hex(0x5c418d));//背景上面颜色
		lv_style_set_bg_color(&lvgl_SheZhi_wifi_style, LV_STATE_DEFAULT, LV_COLOR_BLACK);//背景上面颜色
		lv_style_set_bg_grad_color(&lvgl_SheZhi_wifi_style, LV_STATE_DEFAULT, LV_COLOR_BLACK);//背景上面颜色
		lv_style_set_bg_grad_dir(&lvgl_SheZhi_wifi_style, LV_STATE_DEFAULT, LV_GRAD_DIR_VER);//渐变方向

		/*调整渐变色位置*/
		lv_style_set_bg_main_stop(&lvgl_SheZhi_wifi_style, LV_STATE_DEFAULT, 10);
		lv_style_set_bg_main_stop(&lvgl_SheZhi_wifi_style, LV_STATE_DEFAULT, 100);

		//----创建容器----//
		lvgl_SheZhi_wifi_main_cont = lv_cont_create(Fu, NULL);
		lv_obj_set_pos(lvgl_SheZhi_wifi_main_cont, 0, 0);
		lv_obj_set_size(lvgl_SheZhi_wifi_main_cont,lv_obj_get_width(lv_scr_act()), lv_obj_get_height(lv_scr_act()));
		//lv_obj_set_drag_parent(lvgl_SheZhi_wifi_main_cont, true); //启用 / 禁用父对象可拖动

		lv_obj_set_click(lvgl_SheZhi_wifi_main_cont, true); //启用 / 禁用可点击
		lv_obj_set_drag(lvgl_SheZhi_wifi_main_cont, true);//启用/禁用对象可拖动
		lv_obj_set_drag_dir(lvgl_SheZhi_wifi_main_cont, LV_DRAG_DIR_ONE);//设置拖动方向
		lv_obj_set_drag_throw(lvgl_SheZhi_wifi_main_cont, false);//启用/禁用拖动后是否有惯性移动

		//lv_obj_set_drag_parent(lvgl_SheZhi_wifi_main_cont, true); //启用 / 禁用父对象可拖动
		lv_obj_add_style(lvgl_SheZhi_wifi_main_cont, LV_OBJ_PART_MAIN, &lvgl_SheZhi_wifi_style);//设置样式
		lv_obj_set_event_cb(lvgl_SheZhi_wifi_main_cont, lvgl_SheZhi_wifi_event_cb);//设置回调函数


//----标题----//
		lv_style_init(&SheZhi_wifi_ChuangKou.label_BiaoTi_style);
		lv_style_copy(&SheZhi_wifi_ChuangKou.label_BiaoTi_style, &lvgl_font24_style);

		SheZhi_wifi_ChuangKou.btn_BiaoTi = lv_btn_create(lvgl_SheZhi_wifi_main_cont, btn);

		lv_obj_set_pos(SheZhi_wifi_ChuangKou.btn_BiaoTi, 5, 5);
		lv_obj_set_event_cb(SheZhi_wifi_ChuangKou.btn_BiaoTi, NULL);

		SheZhi_wifi_ChuangKou.label_BiaoTi = lv_label_create(lvgl_SheZhi_wifi_main_cont, NULL);
		lv_label_set_text(SheZhi_wifi_ChuangKou.label_BiaoTi, str);

		lv_label_set_long_mode(SheZhi_wifi_ChuangKou.label_BiaoTi, LV_LABEL_LONG_SROLL_CIRC);//循环滚动
		lv_obj_set_pos(SheZhi_wifi_ChuangKou.label_BiaoTi, 0, 8);
		lv_obj_set_width(SheZhi_wifi_ChuangKou.label_BiaoTi, 240);
		lv_obj_set_height(SheZhi_wifi_ChuangKou.label_BiaoTi, 40);
		lv_label_set_recolor(SheZhi_wifi_ChuangKou.label_BiaoTi, true);
		lv_label_set_align(SheZhi_wifi_ChuangKou.label_BiaoTi, LV_LABEL_ALIGN_CENTER);

		lv_label_set_anim_speed(SheZhi_wifi_ChuangKou.label_BiaoTi, 20);

		lv_style_set_bg_color(&SheZhi_wifi_ChuangKou.label_BiaoTi_style, LV_STATE_DEFAULT, lv_color_hex(lvgl_SheZhi_wifi_GongNeng_Data.color));//背景上面颜色
		lv_style_set_bg_grad_color(&SheZhi_wifi_ChuangKou.label_BiaoTi_style, LV_STATE_DEFAULT, lv_color_hex(lvgl_SheZhi_wifi_GongNeng_Data.anxia_color));//背景上面颜色

		lv_obj_add_style(SheZhi_wifi_ChuangKou.label_BiaoTi, LV_OBJ_PART_MAIN, &SheZhi_wifi_ChuangKou.label_BiaoTi_style);
//----标题----//
		int i = 0;
		for (i = 0; i < SheZhi_wifi_Button_Num; i++)
		{
			lv_style_init(&lvgl_SheZhi_wifi_Button_style[i]);
			lv_style_copy(&lvgl_SheZhi_wifi_Button_style[i], &lvgl_WuBianKuang_cont_style);
			lv_style_set_border_opa(&lvgl_SheZhi_wifi_Button_style[i], LV_STATE_DEFAULT, LV_OPA_80);//边框透明度
			lv_style_set_border_width(&lvgl_SheZhi_wifi_Button_style[i], LV_STATE_DEFAULT, 1);//边框宽度
			lv_style_set_border_color(&lvgl_SheZhi_wifi_Button_style[i], LV_STATE_DEFAULT, LV_COLOR_BLACK);//边框颜色
			//lv_style_set_border_side(&lvgl_WuBianKuang_cont_style, LV_STATE_DEFAULT, LV_BORDER_SIDE_FULL);//边框模式

			lv_style_set_shadow_width(&lvgl_SheZhi_wifi_Button_style[i], LV_STATE_DEFAULT, 0);//阴影宽度
			lv_style_set_shadow_opa(&lvgl_SheZhi_wifi_Button_style[i], LV_STATE_DEFAULT, LV_OPA_80);//阴影透明度
			lv_style_set_shadow_color(&lvgl_SheZhi_wifi_Button_style[i], LV_STATE_DEFAULT, LV_COLOR_BLACK);//阴影颜色

			lv_style_set_radius(&lvgl_SheZhi_wifi_Button_style[i], LV_STATE_DEFAULT, 10);//圆角
			lv_style_set_bg_opa(&lvgl_SheZhi_wifi_Button_style[i], LV_STATE_DEFAULT, LV_OPA_50);//背景透明度
#if 1
			lv_style_set_bg_color(&lvgl_SheZhi_wifi_Button_style[i], LV_STATE_DEFAULT, lv_color_hex(SheZhi_wifi_Color_weianxia));//背景上面颜色
			lv_style_set_bg_grad_color(&lvgl_SheZhi_wifi_Button_style[i], LV_STATE_DEFAULT, lv_color_hex(SheZhi_wifi_Color_weianxia));//背景上面颜色
			lv_style_set_bg_color(&lvgl_SheZhi_wifi_Button_style[i], LV_STATE_PRESSED, lv_color_hex(SheZhi_wifi_Color_anxia));
			lv_style_set_bg_grad_color(&lvgl_SheZhi_wifi_Button_style[i], LV_STATE_PRESSED, lv_color_hex(SheZhi_wifi_Color_anxia));
#else
			lv_style_set_bg_color(&lvgl_SheZhi_wifi_Button_style[i], LV_STATE_DEFAULT, lv_color_hex(SheZhi_wifi_BUTTON_color[i][0]));//背景上面颜色
			lv_style_set_bg_grad_color(&lvgl_SheZhi_wifi_Button_style[i], LV_STATE_DEFAULT, lv_color_hex(SheZhi_wifi_BUTTON_color[i][0]));//背景上面颜色

			lv_style_set_bg_color(&lvgl_SheZhi_wifi_Button_style[i], LV_STATE_PRESSED, lv_color_hex(SheZhi_wifi_BUTTON_color[i][1]));
			lv_style_set_bg_grad_color(&lvgl_SheZhi_wifi_Button_style[i], LV_STATE_PRESSED, lv_color_hex(SheZhi_wifi_BUTTON_color[i][1]));

#endif

			lv_style_set_border_color(&lvgl_SheZhi_wifi_Button_style[i], LV_STATE_FOCUSED, LV_COLOR_BLUE);
			lv_style_set_border_color(&lvgl_SheZhi_wifi_Button_style[i], LV_STATE_FOCUSED | LV_STATE_PRESSED, LV_COLOR_NAVY);


			lv_style_set_text_color(&lvgl_SheZhi_wifi_Button_style[i], LV_STATE_DEFAULT, LV_COLOR_WHITE);
			lv_style_set_text_font(&lvgl_SheZhi_wifi_Button_style[i], LV_STATE_DEFAULT, (const lv_font_t*)&lvgl_font24_style);

			lv_style_set_transform_height(&lvgl_SheZhi_wifi_Button_style[i], LV_STATE_PRESSED, -5);
			lv_style_set_transform_width(&lvgl_SheZhi_wifi_Button_style[i], LV_STATE_PRESSED, -10);
#if LV_USE_ANIMATION
			//Add a transition to the size change
			static lv_anim_path_t path;
			lv_anim_path_init(&path);
			lv_anim_path_set_cb(&path, lv_anim_path_overshoot);

			lv_style_set_transition_prop_1(&lvgl_SheZhi_wifi_Button_style[i], LV_STATE_DEFAULT, LV_STYLE_TRANSFORM_HEIGHT);
			lv_style_set_transition_prop_2(&lvgl_SheZhi_wifi_Button_style[i], LV_STATE_DEFAULT, LV_STYLE_TRANSFORM_WIDTH);
			lv_style_set_transition_time(&lvgl_SheZhi_wifi_Button_style[i], LV_STATE_DEFAULT, 200);
			lv_style_set_transition_path(&lvgl_SheZhi_wifi_Button_style[i], LV_STATE_DEFAULT, &path);
#endif
			lvgl_SheZhi_wifi_Button[i] = lv_btn_create(lvgl_SheZhi_wifi_main_cont, NULL);

			lv_obj_set_pos(lvgl_SheZhi_wifi_Button[i], 240, 40 + i * SheZhi_wifi_item_height);
			lv_obj_set_size(lvgl_SheZhi_wifi_Button[i], 230, 40);
			lv_obj_set_drag_parent(lvgl_SheZhi_wifi_Button[i], true); //启用 / 禁用父对象可拖动
			lv_obj_reset_style_list(lvgl_SheZhi_wifi_Button[i], LV_BTN_PART_MAIN);         //Remove the styles coming from the theme
			lv_obj_add_style(lvgl_SheZhi_wifi_Button[i], LV_BTN_PART_MAIN, &lvgl_SheZhi_wifi_Button_style[i]);//设置样式

			lv_btn_set_layout(lvgl_SheZhi_wifi_Button[i], LV_LAYOUT_OFF);//关闭对子对象布局

			//lv_btn_set_fit4(lvgl_SheZhi_wifi_Button[i], LV_FIT_NONE, LV_FIT_TIGHT, LV_FIT_NONE, LV_FIT_NONE); ////设置宽度只在右边自适 应

			lv_obj_set_event_cb(lvgl_SheZhi_wifi_Button[i], lvgl_SheZhi_wifi_button_cb);//设置 btn3的事件回调
			lvgl_set_obj_hide(lvgl_SheZhi_wifi_Button[i]);

			lv_style_init(&lvgl_SheZhi_wifi_Label_style[i]);
			lv_style_copy(&lvgl_SheZhi_wifi_Label_style[i], &lvgl_font24_style);

			lvgl_SheZhi_wifi_Label[i] = lv_label_create(lvgl_SheZhi_wifi_Button[i], NULL);   //Add a label to the button

			//sprintf(system_data.wifi_ap_info[i].ssid, "这里是wifi测试列表:%02d", i);

			lv_label_set_long_mode(lvgl_SheZhi_wifi_Label[i], LV_LABEL_LONG_SROLL_CIRC);//循环滚动
			lv_obj_set_pos(lvgl_SheZhi_wifi_Label[i], 0, 0);
			lv_obj_set_width(lvgl_SheZhi_wifi_Label[i], 190);
			lv_obj_set_height(lvgl_SheZhi_wifi_Label[i], SheZhi_wifi_item_height);
			lv_label_set_text(lvgl_SheZhi_wifi_Label[i], (const char*)system_data.wifi_ap_info[i].ssid);
			lv_label_set_align(lvgl_SheZhi_wifi_Label[i], LV_LABEL_ALIGN_LEFT);
			lv_label_set_recolor(lvgl_SheZhi_wifi_Label[i], true);

			lv_obj_add_style(lvgl_SheZhi_wifi_Label[i], LV_BTN_PART_MAIN, &lvgl_SheZhi_wifi_Label_style[i]);

			lv_obj_align(lvgl_SheZhi_wifi_Label[i], lvgl_SheZhi_wifi_Button[i], LV_ALIGN_IN_BOTTOM_LEFT, 5, 12);
		}

		SheZhi_wifi_debug("创建窗口\r\n");
	}
	else
	{

		SheZhi_wifi_debug("显示窗口\r\n");
	}

	lv_obj_move_background(lvgl_SheZhi_wifi_main_cont);

	lv_obj_set_drag_throw(lvgl_SheZhi_wifi_main_cont, false);//启用/禁用拖动后是否有惯性移动
	lv_obj_set_pos(lvgl_SheZhi_wifi_main_cont, 0, 0);
	lvgl_set_obj_show(lvgl_SheZhi_wifi_main_cont);

	//lvgl_SheZhi_wifi_anim_btn_item_jin();
	lvgl_SheZhi_wifi_XiaLa_Jin();

	lvgl_task_create(&lvgl_SheZhi_wifi_task,lvgl_SheZhi_wifi_TaskCb, 1000, LV_TASK_PRIO_LOWEST, NULL);

}

void lvgl_SheZhi_wifi_close(void)
{

	lv_style_reset(&SheZhi_wifi_ChuangKou.btn_BiaoTi_style);
	lv_style_reset(&SheZhi_wifi_ChuangKou.label_BiaoTi_style);
	lv_style_reset(&lvgl_SheZhi_wifi_style);

	for (int i = 0; i < SheZhi_wifi_Button_Num; i++)
	{
		lv_style_reset(&lvgl_SheZhi_wifi_Button_style[i]);
		lv_style_reset(&lvgl_SheZhi_wifi_Label_style[i]);

	}


	lvgl_task_delete(&lvgl_SheZhi_wifi_task);
	//lvgl_set_obj_hide(lvgl_SheZhi_wifi_main_cont);

	lvgl_SheZhi_wifi_GongNeng_Data.point.y = lv_obj_get_y(lvgl_SheZhi_wifi_main_cont);
	lvgl_SheZhi_wifi_GongNeng_Data.point.x = lv_obj_get_x(lvgl_SheZhi_wifi_main_cont);

	lv_obj_del_async(lvgl_SheZhi_wifi_main_cont);

	lvgl_SheZhi_create(lv_scr_act());

}

void lvgl_SheZhi_wifi_TaskCb(lv_task_t *t)
{
	static int time=0,time1=0;

	if (lv_obj_get_y(lvgl_SheZhi_wifi_main_cont) != 0)
	{
		lv_obj_set_drag_throw(lvgl_SheZhi_wifi_main_cont, false);//启用/禁用拖动后是否有惯性移动

	}

	if (lv_obj_get_x(lvgl_SheZhi_wifi_main_cont) != 0)
	{
		lv_obj_set_drag_throw(lvgl_SheZhi_wifi_main_cont, false);//启用/禁用拖动后是否有惯性移动
		lv_btn_set_state(SheZhi_wifi_ChuangKou.btn_BiaoTi, LV_BTN_STATE_PRESSED);
	}

#if lvgl_win
	if (system_data.wifi_scan_flag == true && lvgl_shuaxin_get_sta() == lvgl_ShuaXin_Zhong)
	{
		if (++time > 1)
		{
			time = 0;
			lvgl_ShuaXin_close();
		}
	}
	if (lvgl_SheZhi_wifi_GongNeng_Data.wifi_lianjie_flag == true)
	{
		if (++time1 > 2)
		{
			time1 = 0;
			lvgl_SheZhi_wifi_GongNeng_Data.wifi_lianjie_flag = false;
			lvgl_chulizhong_close();
		}
	}
#endif
}


void lvgl_SheZhi_wifi_ShuaXin_KaiShi(void)
{
	SheZhi_wifi_debug("刷新 开始\r\n");


	lvgl_SheZhi_wifi_GongNeng_Data.ShuaXin_Sta = lvgl_ShuaXin_Zhong;
	system_data.wifi_scan_flag = true;
	//xSemaphoreGive(system_data.https_request_Semaphore);//释放信号量

	//lvgl_TianQi_DongHua_Chu();
	//lvgl_ShuaXin_create(lvgl_SheZhi_wifi_main_cont);
	lvgl_ShuaXin_Start(lvgl_SheZhi_wifi_main_cont,&system_data.wifi_scan_flag,30);
	lv_btn_set_state(SheZhi_wifi_ChuangKou.btn_BiaoTi, LV_BTN_STATE_PRESSED);

	lv_obj_set_pos(SheZhi_wifi_ChuangKou.label_BiaoTi, 0, 2);
	lv_label_set_text(SheZhi_wifi_ChuangKou.label_BiaoTi, SheZhi_wifi_TEXT[1][system_get_Language()]);

	if (system_data.wifi_scan_list_cnt > 0)
	{
		lvgl_SheZhi_wifi_anim_btn_item_chu();
	}


}
void lvgl_SheZhi_wifi_ShuaXin_jieshu(void)
{

	SheZhi_wifi_debug("刷新 结束\r\n");

	lvgl_SheZhi_wifi_GongNeng_Data.ShuaXin_Sta = lvgl_ShuaXin_JieShu;
	//lvgl_ShuaXin_close();
	//lv_obj_set_drag(lvgl_SheZhi_wifi_main_cont, true);//启用/禁用对象可拖动

	lv_btn_set_state(SheZhi_wifi_ChuangKou.btn_BiaoTi, LV_BTN_STATE_RELEASED);
	lv_obj_set_pos(SheZhi_wifi_ChuangKou.label_BiaoTi, 0, 8);
	lv_label_set_text(SheZhi_wifi_ChuangKou.label_BiaoTi, SheZhi_wifi_TEXT[0][system_get_Language()]);


	lvgl_SheZhi_wifi_anim_btn_item_jin();

}






void SheZhi_wifi_anim_01(void * arc, lv_anim_value_t v)
{
	lv_obj_set_x(arc, v);
}
void SheZhi_wifi_anim_02(void * arc, lv_anim_value_t v)
{
	lv_obj_set_x(arc, v);
}
void SheZhi_wifi_anim_03(void * arc, lv_anim_value_t v)
{
	lv_obj_set_x(arc, v);
}
void SheZhi_wifi_anim_04(void * arc, lv_anim_value_t v)
{
	lv_obj_set_x(arc, v);
}
void SheZhi_wifi_anim_05(void * arc, lv_anim_value_t v)
{
	lv_obj_set_x(arc, v);
}
void SheZhi_wifi_anim_06(void * arc, lv_anim_value_t v)
{
	lv_obj_set_x(arc, v);
}
void SheZhi_wifi_anim_07(void * arc, lv_anim_value_t v)
{
	lv_obj_set_x(arc, v);
}
void SheZhi_wifi_anim_08(void * arc, lv_anim_value_t v)
{
	lv_obj_set_x(arc, v);
}
void SheZhi_wifi_anim_09(void * arc, lv_anim_value_t v)
{
	lv_obj_set_x(arc, v);
}
void SheZhi_wifi_anim_10(void * arc, lv_anim_value_t v)
{
	lv_obj_set_x(arc, v);
}
void SheZhi_wifi_anim_11(void * arc, lv_anim_value_t v)
{
	lv_obj_set_x(arc, v);
}
void SheZhi_wifi_anim_12(void * arc, lv_anim_value_t v)
{
	lv_obj_set_x(arc, v);
}
void SheZhi_wifi_anim_13(void * arc, lv_anim_value_t v)
{
	lv_obj_set_x(arc, v);
}
void SheZhi_wifi_anim_btn_item_jin_ready_cb(lv_anim_t * anim)
{
	//SheZhi_wifi_debug("Jin ok\r\n");
}
void SheZhi_wifi_anim_btn_item_chu_ready_cb(lv_anim_t * anim)
{
	//SheZhi_wifi_debug("chu ok\r\n");
}
void SheZhi_wifi_anim_Chu_ready_cb(lv_anim_t * anim)
{
	//SheZhi_wifi_debug("chu ok\r\n");

	lv_event_send(lvgl_SheZhi_wifi_GongNeng_Data.AnXia_button, SheZhi_wifi_event_anXia,NULL);
	//lvgl_SheZhi_wifi_anim_btn_item_jin();
}

void(*SheZhi_wifi_anim_cb_buf[])(void * arc, lv_anim_value_t v) =
{
	&SheZhi_wifi_anim_01,
	&SheZhi_wifi_anim_02,
	&SheZhi_wifi_anim_03,
	&SheZhi_wifi_anim_04,
	&SheZhi_wifi_anim_05,
	&SheZhi_wifi_anim_06,
	&SheZhi_wifi_anim_07,
	&SheZhi_wifi_anim_08,
	&SheZhi_wifi_anim_09,
	&SheZhi_wifi_anim_10,
	&SheZhi_wifi_anim_11,
	&SheZhi_wifi_anim_12,
	&SheZhi_wifi_anim_13,



};

//按钮条目滑入动画
void lvgl_SheZhi_wifi_anim_btn_item_jin(void)
{
	int i = 0;
	int max = 0;


#if lvgl_win

	for (i = 0; i < WIFI_SCAN_LIST_SIZE; i++)
	{
		sprintf(system_data.wifi_ap_info[i].ssid,"wifi test list:%02d",i);
	}
	system_data.wifi_scan_list_cnt = i;

#endif


	max = system_data.wifi_scan_list_cnt;
	SheZhi_wifi_debug("wifi数量:%d\r\n", system_data.wifi_scan_list_cnt);
	for (i = 0; i < SheZhi_wifi_Button_Num; i++)
	{
		lvgl_set_obj_hide(lvgl_SheZhi_wifi_Button[i]);

		lv_style_set_text_color(&lvgl_SheZhi_wifi_Label_style[i], LV_STATE_DEFAULT, LV_COLOR_WHITE);


	}
	lvgl_SheZhi_wifi_GongNeng_Data.wifi_dangqian_num = 0xff;
	for (i = 0; i < max; i++)
	{

		if (
			system_data.WIFI_Sta==wifi_yilianjie
			&&
			strstr((const char*)system_data.wifi_ap_info[i].ssid, (const char*)system_data.wifi_name) != NULL
		)
		{
			lvgl_SheZhi_wifi_GongNeng_Data.wifi_dangqian_num = i;//标记为当前连接
			lv_style_set_text_color(&lvgl_SheZhi_wifi_Label_style[i], LV_STATE_DEFAULT, LV_COLOR_GREEN);
		}

		lv_label_set_text(lvgl_SheZhi_wifi_Label[i], (const char*)system_data.wifi_ap_info[i].ssid);

		lvgl_set_obj_show(lvgl_SheZhi_wifi_Button[i]);

	}

	lv_obj_set_height(SheZhi_wifi_ChuangKou.btn_BiaoTi, lv_obj_get_height(lv_scr_act())-10);


	if (40 + i * SheZhi_wifi_item_height > lv_obj_get_height(SheZhi_wifi_ChuangKou.btn_BiaoTi))
	{
		lv_obj_set_height(lvgl_SheZhi_wifi_main_cont, 40 + i * SheZhi_wifi_item_height);
		lv_obj_set_height(SheZhi_wifi_ChuangKou.btn_BiaoTi, lv_obj_get_height(lvgl_SheZhi_wifi_main_cont) - 10);
		SheZhi_wifi_debug("设置wifi窗口高度1");
	}

	// if(lv_obj_get_height(lvgl_SheZhi_wifi_main_cont) < lv_obj_get_height(lv_scr_act()))
	// {
	// 	lv_obj_set_height(lvgl_SheZhi_wifi_main_cont,lv_obj_get_height(lv_scr_act())-10);
	// 	SheZhi_wifi_debug("设置wifi窗口高度2");
	// }


	//lv_obj_set_height(lvgl_SheZhi_wifi_main_cont,500);

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



	for (i = 0; i < max; i++)
	{
		lv_obj_set_x(lvgl_SheZhi_wifi_Button[i], 240);


		lv_anim_init(&SheZhi_wifi_ChuangKou.lv_anim_btn_item_jin[i]);

		if (i == max-1)
		{
			lv_anim_set_ready_cb(&SheZhi_wifi_ChuangKou.lv_anim_btn_item_jin[i], SheZhi_wifi_anim_btn_item_jin_ready_cb);
		}

		lv_anim_set_exec_cb(&SheZhi_wifi_ChuangKou.lv_anim_btn_item_jin[i], SheZhi_wifi_anim_cb_buf[i]);
		lv_anim_set_values(&SheZhi_wifi_ChuangKou.lv_anim_btn_item_jin[i], 240, 5);
		lv_anim_set_time(&SheZhi_wifi_ChuangKou.lv_anim_btn_item_jin[i], 200+i*30);
		lv_anim_set_var(&SheZhi_wifi_ChuangKou.lv_anim_btn_item_jin[i], lvgl_SheZhi_wifi_Button[i]);


		lv_anim_set_path(&SheZhi_wifi_ChuangKou.lv_anim_btn_item_jin[i], &path);

		lv_anim_start(&SheZhi_wifi_ChuangKou.lv_anim_btn_item_jin[i]);
	}

}

//按钮条目滑出动画
void lvgl_SheZhi_wifi_anim_btn_item_chu(void)
{
	int i = 0;
	int max = 0;

	max = system_data.wifi_scan_list_cnt;

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



	for (i = 0; i < max; i++)
	{
		lv_obj_set_x(lvgl_SheZhi_wifi_Button[i], 240);


		lv_anim_init(&SheZhi_wifi_ChuangKou.lv_anim_btn_item_chu[i]);

		if (i == max - 1)
		{
			lv_anim_set_ready_cb(&SheZhi_wifi_ChuangKou.lv_anim_btn_item_chu[i], SheZhi_wifi_anim_btn_item_chu_ready_cb);
		}

		lv_anim_set_exec_cb(&SheZhi_wifi_ChuangKou.lv_anim_btn_item_chu[i], SheZhi_wifi_anim_cb_buf[i]);
		lv_anim_set_values(&SheZhi_wifi_ChuangKou.lv_anim_btn_item_chu[i], 5, 240);
		lv_anim_set_time(&SheZhi_wifi_ChuangKou.lv_anim_btn_item_chu[i], 200 + i * 30);
		lv_anim_set_var(&SheZhi_wifi_ChuangKou.lv_anim_btn_item_chu[i], lvgl_SheZhi_wifi_Button[i]);


		lv_anim_set_path(&SheZhi_wifi_ChuangKou.lv_anim_btn_item_chu[i], &path);

		lv_anim_start(&SheZhi_wifi_ChuangKou.lv_anim_btn_item_chu[i]);
	}

}

void SheZhi_wifi_anim_cb_DongHua(void * arc, lv_anim_value_t v)
{
	lv_obj_set_pos(arc, SheZhi_wifi_ChuangKou.lv_DongHua_area.x1-v/2, SheZhi_wifi_ChuangKou.lv_DongHua_area.y1-v/2);
	lv_obj_set_size(arc, SheZhi_wifi_ChuangKou.lv_DongHua_area.x2+v, SheZhi_wifi_ChuangKou.lv_DongHua_area.y2 + v);

}
void SheZhi_wifi_anim_ready_DongHua_cb(lv_anim_t * anim)
{
	lv_event_send(lvgl_SheZhi_wifi_GongNeng_Data.AnXia_button, SheZhi_wifi_event_anXia, NULL);

	lv_obj_del(SheZhi_wifi_ChuangKou.lvgl_btn_DongHua);
	lv_style_reset(&SheZhi_wifi_ChuangKou.lvgl_btn_DongHua_style);

}
//滑出动画
void lvgl_SheZhi_wifi_DongHua_Chu(void)
{
	int x = 0, y = 0;

	lv_style_init(&SheZhi_wifi_ChuangKou.lvgl_btn_DongHua_style);
	lv_style_copy(&SheZhi_wifi_ChuangKou.lvgl_btn_DongHua_style, &lvgl_SheZhi_wifi_Button_style[lvgl_SheZhi_wifi_GongNeng_Data.AnXia_Num]);
	lv_style_set_radius(&SheZhi_wifi_ChuangKou.lvgl_btn_DongHua_style, LV_STATE_DEFAULT, 30);//圆角

	SheZhi_wifi_ChuangKou.lvgl_btn_DongHua = lv_btn_create(lv_scr_act(), lvgl_SheZhi_wifi_GongNeng_Data.AnXia_button);

	SheZhi_wifi_ChuangKou.lv_DongHua_area.x1 = lv_obj_get_x(lvgl_SheZhi_wifi_GongNeng_Data.AnXia_button);
	SheZhi_wifi_ChuangKou.lv_DongHua_area.y1 = lv_obj_get_y(lvgl_SheZhi_wifi_GongNeng_Data.AnXia_button);
	SheZhi_wifi_ChuangKou.lv_DongHua_area.x2 = lv_obj_get_width(lvgl_SheZhi_wifi_GongNeng_Data.AnXia_button);
	SheZhi_wifi_ChuangKou.lv_DongHua_area.y2 = lv_obj_get_height(lvgl_SheZhi_wifi_GongNeng_Data.AnXia_button);

	y= lv_obj_get_y(lvgl_SheZhi_wifi_main_cont);
	SheZhi_wifi_ChuangKou.lv_DongHua_area.y1 += lv_obj_get_y(lvgl_SheZhi_wifi_main_cont);

	lv_obj_set_y(SheZhi_wifi_ChuangKou.lvgl_btn_DongHua, SheZhi_wifi_ChuangKou.lv_DongHua_area.y1);

	lvgl_SheZhi_wifi_GongNeng_Data.DongHua_KaiShiZhi = fmin(SheZhi_wifi_ChuangKou.lv_DongHua_area.x2, SheZhi_wifi_ChuangKou.lv_DongHua_area.y2);

	lv_anim_init(&SheZhi_wifi_ChuangKou.lv_DongHua_anim);
	lv_anim_set_ready_cb(&SheZhi_wifi_ChuangKou.lv_DongHua_anim, SheZhi_wifi_anim_ready_DongHua_cb);
	lv_anim_set_exec_cb(&SheZhi_wifi_ChuangKou.lv_DongHua_anim, SheZhi_wifi_anim_cb_DongHua);
	lv_anim_set_values(
		&SheZhi_wifi_ChuangKou.lv_DongHua_anim,
		lvgl_SheZhi_wifi_GongNeng_Data.DongHua_KaiShiZhi,
		400
	);
	lv_anim_set_time(&SheZhi_wifi_ChuangKou.lv_DongHua_anim, 200);
	lv_anim_set_var(&SheZhi_wifi_ChuangKou.lv_DongHua_anim, SheZhi_wifi_ChuangKou.lvgl_btn_DongHua);
	lv_anim_start(&SheZhi_wifi_ChuangKou.lv_DongHua_anim);
}




void SheZhi_anim_ready_XiaLa_HuiTan_Jin_cb(lv_anim_t * anim)
{
	//lv_event_send(lvgl_SheZhi_GongNeng_Data.AnXia_button, SheZhi_event_anXia, NULL);

	lvgl_SheZhi_wifi_anim_btn_item_jin();
	lv_anim_del(&SheZhi_ChuangKou.lv_DongHua_anim, NULL);

}
void SheZhi_anim_wifi_XiaLa_HuiTan_Jin_cb(void * arc, lv_anim_value_t v)
{

	lv_obj_set_height(arc, v);

}

void SheZhi_anim_ready_XiaLa_Jin_cb(lv_anim_t * anim)
{
	//lv_event_send(lvgl_SheZhi_GongNeng_Data.AnXia_button, SheZhi_event_anXia, NULL);

	//lvgl_SheZhi_wifi_anim_btn_item_jin();
	lv_anim_del(&SheZhi_wifi_ChuangKou.lv_XiaLa_anim, NULL);

	if (system_data.wifi_scan_list_cnt <= 0)
	{
		lvgl_SheZhi_wifi_ShuaXin_KaiShi();
	}
	else
	{
		lvgl_SheZhi_wifi_anim_btn_item_jin();
	}


}
void SheZhi_anim_wifi_XiaLa_Jin_cb(void * arc, lv_anim_value_t v)
{

	lv_obj_set_height(arc, v);

}
void lvgl_SheZhi_wifi_XiaLa_Jin(void)
{
	lv_obj_set_height(SheZhi_wifi_ChuangKou.btn_BiaoTi, SheZhi_wifi_item_height);

	lv_anim_init(&SheZhi_wifi_ChuangKou.lv_XiaLa_anim);
	lv_anim_set_ready_cb(&SheZhi_wifi_ChuangKou.lv_XiaLa_anim, SheZhi_anim_ready_XiaLa_Jin_cb);
	lv_anim_set_exec_cb(&SheZhi_wifi_ChuangKou.lv_XiaLa_anim, SheZhi_anim_wifi_XiaLa_Jin_cb);
	lv_anim_set_values(
		&SheZhi_wifi_ChuangKou.lv_XiaLa_anim,
		lv_obj_get_height(SheZhi_wifi_ChuangKou.btn_BiaoTi),
		lv_obj_get_height(lvgl_SheZhi_wifi_main_cont)-10
	);
	lv_anim_set_time(&SheZhi_wifi_ChuangKou.lv_XiaLa_anim, 300);
	lv_anim_set_var(&SheZhi_wifi_ChuangKou.lv_XiaLa_anim, SheZhi_wifi_ChuangKou.btn_BiaoTi);

	//lv_anim_set_playback_delay(&SheZhi_wifi_ChuangKou.lv_XiaLa_anim,1000);

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

	lv_anim_set_path(&SheZhi_wifi_ChuangKou.lv_XiaLa_anim, &path);


	lv_anim_start(&SheZhi_wifi_ChuangKou.lv_XiaLa_anim);
}

void SheZhi_anim_ready_ShangLa_Jin_cb(lv_anim_t * anim)
{
	//lv_event_send(lvgl_SheZhi_GongNeng_Data.AnXia_button, SheZhi_event_anXia, NULL);

	lvgl_SheZhi_wifi_anim_btn_item_jin();
	lv_anim_del(&SheZhi_ChuangKou.lv_DongHua_anim, NULL);

}
void SheZhi_anim_wifi_ShangLa_Jin_cb(void * arc, lv_anim_value_t v)
{

	lv_obj_set_height(arc, v);

}
void lvgl_SheZhi_wifi_ShangLa_Jin(void)
{
	lv_obj_set_height(SheZhi_wifi_ChuangKou.btn_BiaoTi, SheZhi_wifi_item_height);

	lv_anim_init(&SheZhi_wifi_ChuangKou.lv_ShangLa_anim);
	lv_anim_set_ready_cb(&SheZhi_wifi_ChuangKou.lv_ShangLa_anim, SheZhi_anim_ready_ShangLa_Jin_cb);
	lv_anim_set_exec_cb(&SheZhi_wifi_ChuangKou.lv_ShangLa_anim, SheZhi_anim_wifi_ShangLa_Jin_cb);
	lv_anim_set_values(
		&SheZhi_wifi_ChuangKou.lv_ShangLa_anim,
		lv_obj_get_height(SheZhi_wifi_ChuangKou.btn_BiaoTi),
		lv_obj_get_height(lvgl_SheZhi_wifi_main_cont) - 10
	);
	lv_anim_set_time(&SheZhi_wifi_ChuangKou.lv_ShangLa_anim, 300);
	lv_anim_set_var(&SheZhi_wifi_ChuangKou.lv_ShangLa_anim, SheZhi_wifi_ChuangKou.btn_BiaoTi);
	lv_anim_start(&SheZhi_wifi_ChuangKou.lv_ShangLa_anim);

}
