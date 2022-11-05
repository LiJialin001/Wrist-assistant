#include "lvgl_hint.h"
#include "lvgl_Project.h"
#include "lvgl_hint_anim.h"



_lvgl_tishi_GongNeng_Data lvgl_tishi_GongNeng_Data;
_tishi_ChuangKou tishi_ChuangKou;

lv_obj_t *lvgl_tishi_main_cont = NULL;
lv_style_t lvgl_tishi_style;


void lvgl_tishi_event_cb(struct _lv_obj_t * obj, lv_event_t event)
{
	//if (obj == lvgl_tishi_main_cont)
	{
		//tishi_debug("cb:%d\r\n", event);
		switch (event)
		{

		case LV_EVENT_DELETE:

			lvgl_tishi_main_cont = NULL;
			tishi_debug("删除窗口\r\n");
			break;

		case LV_EVENT_PRESSING://对象被持续按下


			break;
		case LV_EVENT_PRESSED://对象已被按下


			//lvgl_tishi_anim_chu();


			break;
		case LV_EVENT_DRAG_END://拖动结束后

			lvgl_tishi_close();
			break;

		case LV_EVENT_RELEASED://按钮释放

			//lvgl_tishi_anim_chu();

			break;

		case LV_EVENT_LONG_PRESSED://按钮长按

			break;

		default:
			break;

		}
	}
}


void lvgl_hint_create(lv_obj_t * Fu,char *text,uint8_t touming,uint8_t shijian)
{

	lvgl_tishi_GongNeng_Data.delete_flag=false;
	if (lvgl_tishi_main_cont == NULL)
	{

		lv_style_init(&lvgl_tishi_style);
		lv_style_copy(&lvgl_tishi_style, &lvgl_WuBianKuang_cont_style);

		lv_style_set_radius(&lvgl_tishi_style, LV_STATE_DEFAULT, 5);//圆角
		/*背景色*/
		lv_style_set_bg_opa(&lvgl_tishi_style, LV_STATE_DEFAULT, touming);//背景透明度
		lv_style_set_bg_color(&lvgl_tishi_style, LV_STATE_DEFAULT, LV_COLOR_MAKE(0x00, 0x00, 0x00));//背景上面颜色
		lv_style_set_bg_grad_color(&lvgl_tishi_style, LV_STATE_DEFAULT, LV_COLOR_MAKE(0x00, 0x00, 0x00));//背景上面颜色
		lv_style_set_bg_grad_dir(&lvgl_tishi_style, LV_STATE_DEFAULT, LV_GRAD_DIR_VER);//渐变方向

		//----创建容器----//
		lvgl_tishi_main_cont = lv_cont_create(Fu, NULL);
		lv_obj_set_pos(lvgl_tishi_main_cont, 0, 240);
		lv_obj_set_size(lvgl_tishi_main_cont, 140, 30);

		lv_obj_set_click(lvgl_tishi_main_cont, true); //启用 / 禁用可点击
		lv_obj_set_drag(lvgl_tishi_main_cont, true);//启用/禁用对象可拖动
		lv_obj_set_drag_dir(lvgl_tishi_main_cont, LV_DRAG_DIR_BOTH);//设置拖动方向
		lv_obj_set_drag_throw(lvgl_tishi_main_cont, true);//启用/禁用拖动后是否有惯性移动

		lv_obj_set_drag_parent(lvgl_tishi_main_cont, false); //启用 / 禁用父对象可拖动
		lv_obj_add_style(lvgl_tishi_main_cont, LV_OBJ_PART_MAIN, &lvgl_tishi_style);//设置样式
		lv_obj_set_event_cb(lvgl_tishi_main_cont, lvgl_tishi_event_cb);//设置回调函数


		tishi_ChuangKou.lvgl_Label_text = lv_label_create(lvgl_tishi_main_cont, NULL);
		lv_label_set_long_mode(tishi_ChuangKou.lvgl_Label_text, LV_LABEL_LONG_SROLL_CIRC);//循环滚动
		lv_obj_set_pos(tishi_ChuangKou.lvgl_Label_text, 0, 2);
		lv_obj_set_width(tishi_ChuangKou.lvgl_Label_text, lv_obj_get_width(lvgl_tishi_main_cont));
		lv_obj_set_height(tishi_ChuangKou.lvgl_Label_text, 20);
		lv_label_set_align(tishi_ChuangKou.lvgl_Label_text, LV_LABEL_ALIGN_CENTER);
		lv_label_set_recolor(tishi_ChuangKou.lvgl_Label_text, true);

		lv_obj_add_style(tishi_ChuangKou.lvgl_Label_text, LV_OBJ_PART_MAIN, &lvgl_font16_style);

		lv_label_set_anim_speed(tishi_ChuangKou.lvgl_Label_text, 20);

		lv_obj_align(tishi_ChuangKou.lvgl_Label_text,lvgl_tishi_main_cont,LV_ALIGN_CENTER,0,-2);


		tishi_ChuangKou.lvgl_btn_tuichu = lv_btn_create(lvgl_tishi_main_cont, NULL);
		lv_obj_set_pos(tishi_ChuangKou.lvgl_btn_tuichu, 0, 0);
		lv_obj_set_size(tishi_ChuangKou.lvgl_btn_tuichu, lv_obj_get_width(lvgl_tishi_main_cont), lv_obj_get_height(lvgl_tishi_main_cont));

		lv_obj_set_click(tishi_ChuangKou.lvgl_btn_tuichu, true); //启用 / 禁用可点击

		lv_obj_add_style(tishi_ChuangKou.lvgl_btn_tuichu, LV_OBJ_PART_MAIN, &lvgl_touming_cont_style);
		lv_obj_set_drag_parent(tishi_ChuangKou.lvgl_btn_tuichu, true); //启用 / 禁用父对象可拖动

		lv_obj_set_event_cb(tishi_ChuangKou.lvgl_btn_tuichu, lvgl_tishi_event_cb);//设置回调函数

		lvgl_task_create(&tishi_ChuangKou.lvgl_task,lvgl_tishi_TaskCb, 1000, LV_TASK_PRIO_LOWEST, NULL);
		tishi_debug("创建窗口\r\n");
	}
	else
	{
		tishi_debug("显示窗口\r\n");
	}

	lv_label_set_text(tishi_ChuangKou.lvgl_Label_text, text);

	lv_obj_set_pos(
		lvgl_tishi_main_cont,
		(lv_obj_get_width(lv_scr_act()) - lv_obj_get_width(lvgl_tishi_main_cont))/2,
		lv_obj_get_height(lv_scr_act())
	);

	lvgl_tishi_GongNeng_Data.shijian = shijian;

	lvgl_set_obj_show(lvgl_tishi_main_cont);
	lv_obj_set_top(lvgl_tishi_main_cont, true);
	lv_obj_move_foreground(lvgl_tishi_main_cont);//置顶

	lvgl_tishi_anim_Jin();
}

void lvgl_tishi_close(void)
{
	tishi_debug("关闭窗口\r\n");
	lvgl_task_delete(&tishi_ChuangKou.lvgl_task);
	tishi_ChuangKou.lvgl_task = NULL;
	lvgl_tishi_GongNeng_Data.point.y = lv_obj_get_y(lvgl_tishi_main_cont);
	lvgl_tishi_GongNeng_Data.point.x = lv_obj_get_x(lvgl_tishi_main_cont);

	memset(&tishi_ChuangKou,0x00,sizeof(_tishi_ChuangKou));

	lv_obj_del(lvgl_tishi_main_cont);
	//lvgl_set_obj_hide(lvgl_tishi_main_cont);

}

void lvgl_tishi_TaskCb(lv_task_t *t)
{
	if(lvgl_tishi_GongNeng_Data.delete_flag==false)
	{
		if (--lvgl_tishi_GongNeng_Data.shijian <= 0)
		{
			lvgl_tishi_GongNeng_Data.delete_flag=true;
			lvgl_tishi_anim_chu();
		}
	}
}

