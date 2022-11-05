#include "lvgl_chulizhong.h"
#include "lvgl_Project.h"
#include "lvgl_chulizhong_anim.h"



_lvgl_chulizhong_GongNeng_Data lvgl_chulizhong_GongNeng_Data;
_lvgl_chulizhong_ChuangKou lvgl_chulizhong_ChuangKou;

lv_obj_t *lvgl_chulizhong_main_cont = NULL;
lv_style_t lvgl_chulizhong_style;


const char*chulizhong_TEXT[][SYSTEM_LANGUAGE_NUM] =
{
	{ "处理中", "处理中", "chulizhong", NULL},
};


void lvgl_chulizhong_button_cb(struct _lv_obj_t * obj, lv_event_t event)
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


	break;





	case LV_EVENT_RELEASED://按钮释放


		break;


	case lvgl_event_anXia:

	break;

	case LV_EVENT_LONG_PRESSED://按钮长按

		break;
	default:
		break;

	}



}

void lvgl_chulizhong_event_cb(struct _lv_obj_t * obj, lv_event_t event)
{
	if (obj == lvgl_chulizhong_main_cont)
	{
		//chulizhong_debug("cb:%d\r\n", event);
		switch (event)
		{

		case LV_EVENT_DELETE:


			lvgl_chulizhong_closed();

			break;

		case LV_EVENT_PRESSING://对象被持续按下


			break;
		case LV_EVENT_PRESSED://对象已被按下


			break;
		case LV_EVENT_DRAG_END://拖动结束后


			if (lv_obj_get_y(lvgl_chulizhong_main_cont) > lvgl_chulizhong_y +20)
			{
				//lvgl_chulizhong_shuaxin_kaishi();//刷新开始
				lvgl_chulizhong_close();
			}else
			if (lv_obj_get_y(lvgl_chulizhong_main_cont) != lvgl_chulizhong_y)
			{
				lv_obj_set_y(lvgl_chulizhong_main_cont, lvgl_chulizhong_y);
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


void lvgl_chulizhong_create(lv_obj_t * Fu,char *tishi,uint32_t color, uint32_t anxia_color,void(*cb)(char * text, void *dat))
{

	if (lvgl_chulizhong_main_cont == NULL)
	{

		lv_style_init(&lvgl_chulizhong_style);
		lv_style_copy(&lvgl_chulizhong_style, &lvgl_WuBianKuang_cont_style);

		lv_style_set_radius(&lvgl_chulizhong_style, LV_STATE_DEFAULT, 10);//圆角

		lv_style_set_bg_opa(&lvgl_chulizhong_style, LV_STATE_DEFAULT, LV_OPA_70);//背景透明度
		lv_style_set_bg_color(&lvgl_chulizhong_style, LV_STATE_DEFAULT, style_moren_bg);//背景上面颜色
		lv_style_set_bg_grad_color(&lvgl_chulizhong_style, LV_STATE_DEFAULT, style_moren_bg);//背景上面颜色

		//----创建容器----//
		lvgl_chulizhong_main_cont = lv_cont_create(Fu, NULL);
		lv_obj_set_pos(lvgl_chulizhong_main_cont, lvgl_chulizhong_x, lvgl_chulizhong_y);
		lv_obj_set_size(lvgl_chulizhong_main_cont, lvgl_chulizhong_xsize, lvgl_chulizhong_ysize);

		lvgl_set_motai(true);//开启后窗口将模态
		lv_obj_set_click(lvgl_chulizhong_main_cont, true); //启用 / 禁用可点击
		lv_obj_set_drag(lvgl_chulizhong_main_cont, false);//启用/禁用对象可拖动
		lv_obj_set_drag_dir(lvgl_chulizhong_main_cont, LV_DRAG_DIR_VER);//设置拖动方向
		lv_obj_set_drag_throw(lvgl_chulizhong_main_cont, false);//启用/禁用拖动后是否有惯性移动

		//lv_obj_set_drag_parent(lvgl_chulizhong_main_cont, false); //启用 / 禁用父对象可拖动

		lv_obj_add_style(lvgl_chulizhong_main_cont, LV_OBJ_PART_MAIN, &lvgl_chulizhong_style);//设置样式
		lv_obj_set_event_cb(lvgl_chulizhong_main_cont, lvgl_chulizhong_event_cb);//设置回调函数


		//提示文本框
		lvgl_chulizhong_ChuangKou.lv_lable_tishi = lv_label_create(lvgl_chulizhong_main_cont, NULL);
		lv_label_set_long_mode(lvgl_chulizhong_ChuangKou.lv_lable_tishi, LV_LABEL_LONG_SROLL_CIRC);//循环滚动
		lv_obj_set_pos(lvgl_chulizhong_ChuangKou.lv_lable_tishi, 0, 0);
		lv_obj_set_width(lvgl_chulizhong_ChuangKou.lv_lable_tishi, 80);
		lv_obj_set_height(lvgl_chulizhong_ChuangKou.lv_lable_tishi, 24);
		lv_label_set_align(lvgl_chulizhong_ChuangKou.lv_lable_tishi, LV_LABEL_ALIGN_CENTER);
		lv_label_set_recolor(lvgl_chulizhong_ChuangKou.lv_lable_tishi, true);

		lv_obj_add_style(lvgl_chulizhong_ChuangKou.lv_lable_tishi, LV_BTN_PART_MAIN, &lvgl_font16_style);

		lv_obj_align(lvgl_chulizhong_ChuangKou.lv_lable_tishi, lvgl_chulizhong_main_cont, LV_ALIGN_CENTER, 0, 0);

		//预加载器
		lvgl_chulizhong_ChuangKou.lv_preload = lv_spinner_create(lvgl_chulizhong_main_cont, NULL);
		lv_obj_set_size(lvgl_chulizhong_ChuangKou.lv_preload, 100, 100);//设置大小
		lv_obj_align(lvgl_chulizhong_ChuangKou.lv_preload, NULL, LV_ALIGN_CENTER, 0, 0);//与屏幕居中对齐
		//设置样式
		lv_spinner_set_arc_length(lvgl_chulizhong_ChuangKou.lv_preload, 45);//设置小圆弧对应的角度
		lv_spinner_set_dir(lvgl_chulizhong_ChuangKou.lv_preload, LV_SPINNER_DIR_FORWARD);//设置为逆时针旋转
		//设置旋转动画的方式
		lv_spinner_set_type(lvgl_chulizhong_ChuangKou.lv_preload, LV_SPINNER_TYPE_SPINNING_ARC);
		lv_spinner_set_spin_time(lvgl_chulizhong_ChuangKou.lv_preload, 1000);//设置旋转的速度 ,转一圈所需要的时间

		lv_style_init(&lvgl_chulizhong_ChuangKou.lv_preload_SPINNING_style);
		lv_style_copy(&lvgl_chulizhong_ChuangKou.lv_preload_SPINNING_style, &lvgl_preload_SPINNING_style);

		lv_style_init(&lvgl_chulizhong_ChuangKou.lv_preload_FILLSPIN_style);
		lv_style_copy(&lvgl_chulizhong_ChuangKou.lv_preload_FILLSPIN_style, &lvgl_preload_FILLSPIN_style);

		lv_style_set_line_color(&lvgl_chulizhong_ChuangKou.lv_preload_FILLSPIN_style, LV_STATE_DEFAULT, lv_color_hex(color));

		//底部园样式
		lv_obj_add_style(lvgl_chulizhong_ChuangKou.lv_preload, LV_SPINNER_TYPE_SPINNING_ARC, &lvgl_chulizhong_ChuangKou.lv_preload_SPINNING_style);
		//旋转的弧样式
		lv_obj_add_style(lvgl_chulizhong_ChuangKou.lv_preload, LV_SPINNER_TYPE_FILLSPIN_ARC, &lvgl_chulizhong_ChuangKou.lv_preload_FILLSPIN_style);

		//lvgl_task_create(&lvgl_chulizhong_ChuangKou.lvgl_task,lvgl_chulizhong_TaskCb, 20, LV_TASK_PRIO_LOWEST, NULL);
		chulizhong_debug("创建窗口1\r\n");
	}
	else
	{
		chulizhong_debug("显示窗口2\r\n");
	}

	lv_label_set_text(lvgl_chulizhong_ChuangKou.lv_lable_tishi, tishi);//文本
	lvgl_chulizhong_GongNeng_Data.cb = cb;
	lv_obj_set_drag_throw(lvgl_chulizhong_main_cont, false);//启用/禁用拖动后是否有惯性移动
	lv_obj_set_pos(lvgl_chulizhong_main_cont, lvgl_chulizhong_x, 240);
	lvgl_set_obj_show(lvgl_chulizhong_main_cont);

	lvgl_chulizhong_anim_Jin();
}

void lvgl_chulizhong_close(void)
{
	uint16_t count = 0;

	lvgl_task_delete(&lvgl_chulizhong_ChuangKou.lvgl_task);

	lvgl_chulizhong_GongNeng_Data.point.y = lv_obj_get_y(lvgl_chulizhong_main_cont);
	lvgl_chulizhong_GongNeng_Data.point.x = lv_obj_get_x(lvgl_chulizhong_main_cont);

	lv_obj_clean(lvgl_chulizhong_main_cont);

	count = lv_obj_count_children(lvgl_chulizhong_main_cont);
	chulizhong_debug("count:%d\r\n", count);

	lv_obj_del(lvgl_chulizhong_main_cont);
}


void lvgl_chulizhong_closed(void)
{
	chulizhong_debug("删除窗口\r\n");
	chulizhong_debug("closed\r\n");

	lvgl_chulizhong_main_cont = NULL;
	memset(&lvgl_chulizhong_ChuangKou, 0x00, sizeof(_lvgl_chulizhong_ChuangKou));
	lvgl_set_motai(false);//开启后窗口将模态

	if (lvgl_chulizhong_GongNeng_Data.cb != NULL)
	{
		lvgl_chulizhong_GongNeng_Data.cb(lvgl_chulizhong_GongNeng_Data.shuchu_text, &lvgl_chulizhong_GongNeng_Data.guanbi_flag);
	}

}

void lvgl_chulizhong_TaskCb(lv_task_t *t)
{
	static int time = 0, bmp_qian_time = 0, bmp_qian_x = 0, bmp_qian_flag = 0,bmp_time = 0, bmp_cnt = 0, bmp_flag = 0;
}

