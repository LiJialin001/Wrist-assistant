#include "lvgl_shurufa.h"
#include "lvgl_Project.h"
#include "lvgl_shurufa_anim.h"



_lvgl_shurufa_GongNeng_Data lvgl_shurufa_GongNeng_Data;
_lvgl_shurufa_ChuangKou lvgl_shurufa_ChuangKou;

lv_obj_t *lvgl_shurufa_main_cont = NULL;
lv_style_t lvgl_shurufa_style;



const char*shurufa_TEXT[][SYSTEM_LANGUAGE_NUM] =
{
	{ "输入法", "输入法", "shurufa", NULL},
};

//无重复按下功能,选择松手触发
#define MKC (LV_BTNMATRIX_CTRL_NO_REPEAT | LV_BTNMATRIX_CTRL_CLICK_TRIG)

static const char * const my_kb_map_lc[] = { "123", "q", "w", "e", "r", "t", "y", "u", "i", "o", "p", LV_SYMBOL_BACKSPACE, "\n",
								   "ABC", "a", "s", "d", "f", "g", "h", "j", "k", "l", LV_SYMBOL_NEW_LINE, "\n",
								   ".", "z", "x", "c", "v", "b", "n", "m", "Clear", "\n",
								   LV_SYMBOL_CLOSE, LV_SYMBOL_LEFT, " ", LV_SYMBOL_RIGHT, LV_SYMBOL_OK, "" };

static const lv_btnmatrix_ctrl_t my_kb_ctrl_lc_map[] = {
	MKC | 5, MKC | 4, MKC | 4, MKC | 4, MKC | 4, MKC | 4, MKC | 4, MKC | 4, MKC | 4, MKC | 4, MKC | 4, MKC | 7,
	MKC | 7, MKC | 3, MKC | 3, MKC | 3, MKC | 3, MKC | 3, MKC | 3, MKC | 3, MKC | 3, MKC | 3, MKC | 7,
	MKC | 1, MKC | 1, MKC | 1, MKC | 1, MKC | 1, MKC | 1, MKC | 1, MKC | 1, MKC | 3,
	MKC | 2, MKC | 2, MKC | 6, MKC | 2, MKC | 2
};

static const char * const my_kb_map_uc[] = { "123", "Q", "W", "E", "R", "T", "Y", "U", "I", "O", "P", LV_SYMBOL_BACKSPACE, "\n",
								   "abc", "A", "S", "D", "F", "G", "H", "J", "K", "L", LV_SYMBOL_NEW_LINE, "\n",
								   ".", "Z", "X", "C", "V", "B", "N", "M", "Clear", "\n",
								   LV_SYMBOL_CLOSE, LV_SYMBOL_LEFT, " ", LV_SYMBOL_RIGHT, LV_SYMBOL_OK, "" };

static const lv_btnmatrix_ctrl_t my_kb_ctrl_uc_map[] = {
	MKC | 5, MKC | 4, MKC | 4, MKC | 4, MKC | 4, MKC | 4, MKC | 4, MKC | 4, MKC | 4, MKC | 4, MKC | 4, MKC | 7,
	MKC | 7, MKC | 3, MKC | 3, MKC | 3, MKC | 3, MKC | 3, MKC | 3, MKC | 3, MKC | 3, MKC | 3, MKC | 7,
	MKC | 1, MKC | 1, MKC | 1, MKC | 1, MKC | 1, MKC | 1, MKC | 1, MKC | 1, MKC | 3,
	MKC | 2, MKC | 2, MKC | 6, MKC | 2, MKC | 2
};


static const char * const my_kb_map_num[] = {
	".,?","1", "2", "3", LV_SYMBOL_BACKSPACE, "\n",
	"abc","4", "5", "6","/",  "\n",
	".","7", "8", "9", "_", "\n",
	LV_SYMBOL_CLOSE, LV_SYMBOL_LEFT, " ", LV_SYMBOL_RIGHT, LV_SYMBOL_OK, ""
};

static const lv_btnmatrix_ctrl_t my_kb_ctrl_num_map[] = {
	MKC | 3, MKC | 4, MKC | 4,MKC | 4, MKC | 5,
	MKC | 3, MKC | 4, MKC | 4,MKC | 4, MKC | 5,
	MKC | 3, MKC | 4, MKC | 4,MKC | 4, MKC | 5,
	MKC | 2, MKC | 2, MKC | 6,MKC | 2, MKC | 2
};

static const char * const my_kb_map_fuhao[] = {
	"123", "+", "-", "/", "*", "=", "%", "!", LV_SYMBOL_BACKSPACE, "\n",
	"abc","?", "#", "<", ">", "\\", "@", "$","'", "\n",
	".", "(", ")", "{", "}", "[", "]", ";", "\"",  "\n",
	LV_SYMBOL_CLOSE, LV_SYMBOL_LEFT, " ", LV_SYMBOL_RIGHT, LV_SYMBOL_OK, ""
};

static const lv_btnmatrix_ctrl_t my_kb_ctrl_fuhao_map[] = {
	MKC | 5, MKC | 4, MKC | 4,MKC | 4, MKC | 4,MKC | 4,MKC | 4,MKC | 4, MKC | 5,
	MKC | 5, MKC | 4, MKC | 4,MKC | 4, MKC | 4,MKC | 4,MKC | 4,MKC | 4, MKC | 5,
	MKC | 3, MKC | 4, MKC | 4,MKC | 4, MKC | 4,MKC | 4,MKC | 4,MKC | 4, MKC | 5,
	MKC | 2, MKC | 2, MKC | 6,MKC | 2, MKC | 2
};

void lvgl_shurufa_button_cb(struct _lv_obj_t * obj, lv_event_t event)
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

void lvgl_shurufa_event_cb(struct _lv_obj_t * obj, lv_event_t event)
{
	if (obj == lvgl_shurufa_main_cont)
	{
		//shurufa_debug("cb:%d\r\n", event);
		switch (event)
		{

		case LV_EVENT_DELETE:


			lvgl_shurufa_closed();

			break;

		case LV_EVENT_PRESSING://对象被持续按下


			break;
		case LV_EVENT_PRESSED://对象已被按下


			break;
		case LV_EVENT_DRAG_END://拖动结束后


			if (lv_obj_get_y(lvgl_shurufa_main_cont) > lvgl_shuaxin_y+20)
			{
				lvgl_shurufa_GongNeng_Data.guanbi_flag = false;
				lvgl_shurufa_close();

			}else
			if (lv_obj_get_y(lvgl_shurufa_main_cont) != lvgl_shuaxin_y)
			{
				lv_obj_set_y(lvgl_shurufa_main_cont, lvgl_shuaxin_y);
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

static void lvgl_shurufa_kb_event_cb(lv_obj_t * obj, lv_event_t event)
{

	if (obj == lvgl_shurufa_ChuangKou.lv_kb)
	{
		const char * key_txt = lv_btnmatrix_get_active_btn_text(obj);//获取按下键的文本标题,放到lv_kb_def_event_cb的前面调用


		//添加自己的功能代码
		if (event == LV_EVENT_VALUE_CHANGED)
		{
			//uint16_t key_id = *(uint16_t*)lv_event_get_data();//获取按下键的id,第一个按键的id为0,后面的按键依次增1
			if (key_txt == NULL)
				return;
			if (strcmp(key_txt, "Clear") == 0)//按下的是清空键
			{
				lv_obj_t * bind_ta = lv_keyboard_get_textarea(obj);//获取当前绑定的文本域对象
				lv_textarea_set_text(bind_ta, "");//将输入内容清空
			}
			else
			if (strcmp(key_txt, "123") == 0)//切换到数字按键
			{

				lv_keyboard_set_mode(lvgl_shurufa_ChuangKou.lv_kb, LV_KEYBOARD_MODE_SPECIAL);
				lv_keyboard_set_map(lvgl_shurufa_ChuangKou.lv_kb, LV_KEYBOARD_MODE_SPECIAL, (const char **)my_kb_map_num);//设置自定义按键的映射表
				lv_keyboard_set_ctrl_map(lvgl_shurufa_ChuangKou.lv_kb, LV_KEYBOARD_MODE_SPECIAL, my_kb_ctrl_num_map);//设置自定义按键的属性控制映射表
			}
			else
			if (strcmp(key_txt, ".,?") == 0)//切换到符号键盘
			{

				lv_keyboard_set_mode(lvgl_shurufa_ChuangKou.lv_kb, LV_KEYBOARD_MODE_SPECIAL);
				lv_keyboard_set_map(lvgl_shurufa_ChuangKou.lv_kb, LV_KEYBOARD_MODE_SPECIAL, (const char **)my_kb_map_fuhao);//设置自定义按键的映射表
				lv_keyboard_set_ctrl_map(lvgl_shurufa_ChuangKou.lv_kb, LV_KEYBOARD_MODE_SPECIAL, my_kb_ctrl_fuhao_map);//设置自定义按键的属性控制映射表
			}
			else
			{
				lv_keyboard_def_event_cb(lvgl_shurufa_ChuangKou.lv_kb, event);//默认的按键处理函数
			}


		}else
		if (event == LV_EVENT_CANCEL)
		{
			lvgl_shurufa_GongNeng_Data.guanbi_flag = false;
			sprintf(lvgl_shurufa_GongNeng_Data.shuchu_text, "%s", lv_textarea_get_text(lvgl_shurufa_ChuangKou.lv_ta_shuru));
			lvgl_shurufa_anim_chu();


		}
		else if (event == LV_EVENT_APPLY)
		{
			lvgl_shurufa_GongNeng_Data.guanbi_flag = true;
			sprintf(lvgl_shurufa_GongNeng_Data.shuchu_text, "%s", lv_textarea_get_text(lvgl_shurufa_ChuangKou.lv_ta_shuru));
			lvgl_shurufa_anim_chu();

		}

	}
}


void lvgl_shurufa_create(lv_obj_t * Fu, lv_obj_t * source,char *tishi, int type, uint32_t color, uint32_t anxia_color,void(*cb)(char * text, void *dat))
{

	lvgl_set_motai(true);//开启后窗口将模态
	if (lvgl_shurufa_main_cont == NULL)
	{

		lv_style_init(&lvgl_shurufa_style);
		lv_style_copy(&lvgl_shurufa_style, &lvgl_WuBianKuang_cont_style);

		lv_style_set_radius(&lvgl_shurufa_style, LV_STATE_DEFAULT, 2);//圆角

		//----创建容器----//
		lvgl_shurufa_main_cont = lv_cont_create(lv_layer_top(), NULL);
		lv_obj_set_pos(lvgl_shurufa_main_cont, 0, lv_obj_get_height(lv_scr_act()));
		lv_obj_set_size(lvgl_shurufa_main_cont, 240, 130);
		//lv_obj_set_drag_parent(lvgl_shurufa_main_cont, true); //启用 / 禁用父对象可拖动

		lv_obj_set_click(lvgl_shurufa_main_cont, true); //启用 / 禁用可点击
		lv_obj_set_drag(lvgl_shurufa_main_cont, false);//启用/禁用对象可拖动
		lv_obj_set_drag_dir(lvgl_shurufa_main_cont, LV_DRAG_DIR_VER);//设置拖动方向
		lv_obj_set_drag_throw(lvgl_shurufa_main_cont, false);//启用/禁用拖动后是否有惯性移动

		//lv_obj_set_drag_parent(lvgl_shurufa_main_cont, true); //启用 / 禁用父对象可拖动
		lv_obj_add_style(lvgl_shurufa_main_cont, LV_OBJ_PART_MAIN, &lvgl_shurufa_style);//设置样式
		lv_obj_set_event_cb(lvgl_shurufa_main_cont, lvgl_shurufa_event_cb);//设置回调函数

		lvgl_task_create(&lvgl_shurufa_ChuangKou.lvgl_task,lvgl_shurufa_TaskCb, 20, LV_TASK_PRIO_LOWEST, NULL);


		if (type == type_lable)
		{
			sprintf(lvgl_shurufa_GongNeng_Data.shuru_text,"%s", lv_label_get_text(source));

		}



		//----输入框----//
		lv_style_init(&lvgl_shurufa_ChuangKou.lv_ta_shuru_style);
		lv_style_copy(&lvgl_shurufa_ChuangKou.lv_ta_shuru_style, &lvgl_ta_moren_style);

		lv_style_set_border_color(&lvgl_shurufa_ChuangKou.lv_ta_shuru_style, LV_STATE_DEFAULT, lv_color_hex(color));//边框颜色
		lv_style_set_border_color(&lvgl_shurufa_ChuangKou.lv_ta_shuru_style, LV_STATE_FOCUSED, lv_color_hex(color));//边框颜色


		lvgl_shurufa_ChuangKou.lv_ta_shuru = lv_textarea_create(lvgl_shurufa_main_cont, NULL);
		lv_obj_set_pos(lvgl_shurufa_ChuangKou.lv_ta_shuru,0,0);
		lv_obj_set_size(lvgl_shurufa_ChuangKou.lv_ta_shuru,240,24);
		lv_textarea_set_text(lvgl_shurufa_ChuangKou.lv_ta_shuru, "");//文本
		lv_textarea_set_placeholder_text(lvgl_shurufa_ChuangKou.lv_ta_shuru, tishi);//提示文本
		lv_textarea_set_cursor_hidden(lvgl_shurufa_ChuangKou.lv_ta_shuru, false);//光标
		lv_textarea_set_pwd_mode(lvgl_shurufa_ChuangKou.lv_ta_shuru, false);//密码模式
		lv_textarea_set_one_line(lvgl_shurufa_ChuangKou.lv_ta_shuru, true);//单行模式
		lv_obj_align(lvgl_shurufa_ChuangKou.lv_ta_shuru, NULL, LV_ALIGN_IN_TOP_MID, 0, 0);
		lv_obj_add_style(lvgl_shurufa_ChuangKou.lv_ta_shuru, LV_OBJ_PART_MAIN, &lvgl_shurufa_ChuangKou.lv_ta_shuru_style);
		lv_obj_set_drag_parent(lvgl_shurufa_ChuangKou.lv_ta_shuru, true); //启用 / 禁用父对象可拖动
		//----输入框----//

		//----键盘----//


		lvgl_shurufa_ChuangKou.lv_kb = lv_keyboard_create(lvgl_shurufa_main_cont, NULL);
		lv_obj_set_pos(lvgl_shurufa_ChuangKou.lv_kb,0,24);
		lv_obj_set_height(lvgl_shurufa_ChuangKou.lv_kb,108);
		lv_keyboard_set_textarea(lvgl_shurufa_ChuangKou.lv_kb, lvgl_shurufa_ChuangKou.lv_ta_shuru);//绑定文本域
		lv_obj_set_drag_parent(lvgl_shurufa_ChuangKou.lv_kb, true); //启用 / 禁用父对象可拖动

		lv_keyboard_set_map(lvgl_shurufa_ChuangKou.lv_kb, LV_KEYBOARD_MODE_TEXT_LOWER,(const char **)my_kb_map_lc);//设置自定义按键的映射表
		lv_keyboard_set_ctrl_map(lvgl_shurufa_ChuangKou.lv_kb, LV_KEYBOARD_MODE_TEXT_LOWER, my_kb_ctrl_lc_map);//设置自定义按键的属性控制映射表

		lv_keyboard_set_map(lvgl_shurufa_ChuangKou.lv_kb, LV_KEYBOARD_MODE_TEXT_UPPER, (const char **)my_kb_map_uc);//设置自定义按键的映射表
		lv_keyboard_set_ctrl_map(lvgl_shurufa_ChuangKou.lv_kb, LV_KEYBOARD_MODE_TEXT_UPPER, my_kb_ctrl_uc_map);//设置自定义按键的属性控制映射表

		//lv_keyboard_set_map(lvgl_shurufa_ChuangKou.lv_kb, LV_KEYBOARD_MODE_SPECIAL, (const char **)my_kb_map_num);//设置自定义按键的映射表
		//lv_keyboard_set_ctrl_map(lvgl_shurufa_ChuangKou.lv_kb, LV_KEYBOARD_MODE_SPECIAL, my_kb_ctrl_num_map);//设置自定义按键的属性控制映射表

		//按钮样式
		lv_style_set_border_color(&lvgl_kb_TEXT_UPPER_moren_style, LV_STATE_DEFAULT, lv_color_hex(color));//边框颜色
		lv_style_set_border_color(&lvgl_kb_TEXT_UPPER_moren_style, LV_STATE_FOCUSED, lv_color_hex(color));//边框颜色

		//lv_style_set_bg_color(&lvgl_kb_TEXT_UPPER_moren_style, LV_STATE_DEFAULT, lv_color_hex(color));//背景上面颜色
		lv_style_set_bg_grad_color(&lvgl_kb_TEXT_UPPER_moren_style, LV_STATE_PRESSED, lv_color_hex(anxia_color));//背景上面颜色
//LV_KEYBOARD_MODE_TEXT_LOWER,
//LV_KEYBOARD_MODE_TEXT_UPPER,
//LV_KEYBOARD_MODE_SPECIAL,
//LV_KEYBOARD_MODE_NUM,
		lv_obj_add_style(lvgl_shurufa_ChuangKou.lv_kb, LV_KEYBOARD_MODE_TEXT_LOWER, &lvgl_kb_TEXT_LOWER_moren_style);//键盘背景
		lv_obj_add_style(lvgl_shurufa_ChuangKou.lv_kb, LV_KEYBOARD_MODE_TEXT_UPPER, &lvgl_kb_TEXT_UPPER_moren_style);//键盘按钮

		lv_obj_set_event_cb(lvgl_shurufa_ChuangKou.lv_kb, lvgl_shurufa_kb_event_cb);//事件回调函数
		//----键盘----//


		shurufa_debug("创建窗口1\r\n");
	}
	else
	{

		shurufa_debug("显示窗口2\r\n");
	}

	memset(lvgl_shurufa_GongNeng_Data.shuchu_text,0x00,sizeof(lvgl_shurufa_GongNeng_Data.shuchu_text));
	lv_textarea_set_text(lvgl_shurufa_ChuangKou.lv_ta_shuru, "");//文本
	lv_textarea_set_placeholder_text(lvgl_shurufa_ChuangKou.lv_ta_shuru, tishi);//提示文本

	lvgl_shurufa_GongNeng_Data.cb = cb;

	lv_obj_set_drag_throw(lvgl_shurufa_main_cont, false);//启用/禁用拖动后是否有惯性移动
	lv_obj_set_pos(lvgl_shurufa_main_cont, 0, 0);
	lvgl_set_obj_show(lvgl_shurufa_main_cont);


	lvgl_shurufa_anim_Jin();
}

void lvgl_shurufa_close(void)
{

	uint16_t count = 0;

	lvgl_task_delete(&lvgl_shurufa_ChuangKou.lvgl_task);

	lvgl_shurufa_GongNeng_Data.point.y = lv_obj_get_y(lvgl_shurufa_main_cont);
	lvgl_shurufa_GongNeng_Data.point.x = lv_obj_get_x(lvgl_shurufa_main_cont);

	lv_obj_clean(lvgl_shurufa_main_cont);

	count = lv_obj_count_children(lvgl_shurufa_main_cont);
	printf("count:%d\r\n", count);

	lv_obj_del(lvgl_shurufa_main_cont);

}


void lvgl_shurufa_closed(void)
{
	shurufa_debug("删除窗口\r\n");
	shurufa_debug("closed\r\n");

	lvgl_shurufa_main_cont = NULL;
	memset(&lvgl_shurufa_ChuangKou, 0x00, sizeof(_lvgl_shurufa_ChuangKou));

	lvgl_set_motai(false);//开启后窗口将模态
	if (lvgl_shurufa_GongNeng_Data.cb != NULL)
	{
		lvgl_shurufa_GongNeng_Data.cb(lvgl_shurufa_GongNeng_Data.shuchu_text, &lvgl_shurufa_GongNeng_Data.guanbi_flag);

	}
}

void lvgl_shurufa_TaskCb(lv_task_t *t)
{
	static int time = 0, bmp_qian_time = 0, bmp_qian_x = 0, bmp_qian_flag = 0,bmp_time = 0, bmp_cnt = 0, bmp_flag = 0;

}

