#include "lvgl_style.h"
#include "string.h"
#include "stdio.h"
#include "font.h"

_lvgl_Style_Func_Data lvgl_Style_Func_Data;

lv_style_t lvgl_font12_style;
lv_style_t lvgl_font16_style;
lv_style_t lvgl_font24_style;
lv_style_t lvgl_font_acsii_48_style;
lv_style_t lvgl_font_acsii_12_style;
lv_style_t lvgl_font_acsii_16_style;
lv_style_t lvgl_font_acsii_32_style;

lv_style_t lvgl_WuBianKuang_cont_style;
lv_style_t lvgl_ta_moren_style;		//文本输入默认样式
lv_style_t lvgl_touming_cont_style;//透明cont样式

lv_style_t lvgl_preload_SPINNING_style;		//preload底部圆形默认样式
lv_style_t lvgl_preload_FILLSPIN_style;		//preload旋转的弧形默认样式


lv_style_t lvgl_switch_on_style;			//switch的开状态默认样式
lv_style_t lvgl_switch_background_style;	//switch的背景默认样式
lv_style_t lvgl_switch_knob_style;			//switch的指示器默认样式


void lvgl_Style_create(void)
{

		lv_style_init(&lvgl_font_acsii_12_style);
	lv_style_set_text_color(&lvgl_font_acsii_12_style, LV_STATE_DEFAULT, LV_COLOR_MAKE(0xff, 0xff, 0xff));
	lv_style_set_text_font(&lvgl_font_acsii_12_style, LV_STATE_DEFAULT, (const lv_font_t*)&font_acsii_12);

	lv_style_init(&lvgl_font_acsii_16_style);
	lv_style_set_text_color(&lvgl_font_acsii_16_style, LV_STATE_DEFAULT, LV_COLOR_MAKE(0xff, 0xff, 0xff));
	lv_style_set_text_font(&lvgl_font_acsii_16_style, LV_STATE_DEFAULT, (const lv_font_t*)&font_acsii_16);



	lv_style_init(&lvgl_font_acsii_32_style);
	lv_style_set_text_color(&lvgl_font_acsii_32_style, LV_STATE_DEFAULT, LV_COLOR_MAKE(0xff, 0xff, 0xff));
	lv_style_set_text_font(&lvgl_font_acsii_32_style, LV_STATE_DEFAULT, (const lv_font_t*)&font_acsii_32);


	lv_style_init(&lvgl_font12_style);
	lv_style_set_text_color(&lvgl_font12_style, LV_STATE_DEFAULT, LV_COLOR_MAKE(0xff, 0xff, 0xff));
	lv_style_set_text_font(&lvgl_font12_style, LV_STATE_DEFAULT, (const lv_font_t*)&font_ChangYongHanZi_12);

	lv_style_init(&lvgl_font16_style);
	lv_style_set_text_color(&lvgl_font16_style, LV_STATE_DEFAULT, LV_COLOR_MAKE(0xff, 0xff, 0xff));
	lv_style_set_text_font(&lvgl_font16_style, LV_STATE_DEFAULT, (const lv_font_t*)&lv_font_montserrat_16);


	lv_style_init(&lvgl_font24_style);
	lv_style_set_text_color(&lvgl_font24_style, LV_STATE_DEFAULT, LV_COLOR_MAKE(0xff, 0xff, 0xff));
	lv_style_set_text_font(&lvgl_font24_style, LV_STATE_DEFAULT, (const lv_font_t*)&font_ChangYongHanZi_24);

	lv_style_init(&lvgl_font_acsii_48_style);
	lv_style_set_text_color(&lvgl_font_acsii_48_style, LV_STATE_DEFAULT, LV_COLOR_MAKE(0xff, 0xff, 0xff));
	lv_style_set_text_font(&lvgl_font_acsii_48_style, LV_STATE_DEFAULT, (const lv_font_t*)&font_acsii_48);

    lv_style_init(&lvgl_WuBianKuang_cont_style);
	lv_style_set_radius(&lvgl_WuBianKuang_cont_style, LV_STATE_DEFAULT, 0);//圆角
	lv_style_set_border_opa(&lvgl_WuBianKuang_cont_style, LV_STATE_DEFAULT, 255);//边框透明度
	lv_style_set_border_width(&lvgl_WuBianKuang_cont_style, LV_STATE_DEFAULT, 0);//边框宽度
	lv_style_set_border_side(&lvgl_WuBianKuang_cont_style, LV_STATE_DEFAULT, LV_BORDER_SIDE_NONE);
	lv_style_set_border_blend_mode(&lvgl_WuBianKuang_cont_style, LV_STATE_DEFAULT, LV_BLEND_MODE_NORMAL);
	lv_style_set_pad_top(&lvgl_WuBianKuang_cont_style, LV_STATE_DEFAULT, 0);//内边距上侧尺寸
	lv_style_set_pad_bottom(&lvgl_WuBianKuang_cont_style, LV_STATE_DEFAULT, 0);//内边距下侧尺寸
	lv_style_set_pad_left(&lvgl_WuBianKuang_cont_style, LV_STATE_DEFAULT, 0);//内边距左侧尺寸
	lv_style_set_pad_right(&lvgl_WuBianKuang_cont_style, LV_STATE_DEFAULT, 0);//内边距右侧尺寸

	/*背景色*/
	lv_style_set_bg_opa(&lvgl_WuBianKuang_cont_style, LV_STATE_DEFAULT, LV_OPA_COVER);//背景透明度
	lv_style_set_bg_color(&lvgl_WuBianKuang_cont_style, LV_STATE_DEFAULT, style_moren_bg);//背景上面颜色
	lv_style_set_bg_grad_color(&lvgl_WuBianKuang_cont_style, LV_STATE_DEFAULT, style_moren_bg);//背景上面颜色
	lv_style_set_bg_grad_dir(&lvgl_WuBianKuang_cont_style, LV_STATE_DEFAULT, LV_GRAD_DIR_VER);//渐变方向

	/*调整渐变色位置*/
	lv_style_set_bg_main_stop(&lvgl_WuBianKuang_cont_style, LV_STATE_DEFAULT, 10);
	lv_style_set_bg_main_stop(&lvgl_WuBianKuang_cont_style, LV_STATE_DEFAULT, 100);

	//----输入框默认样式----//
	lv_style_init(&lvgl_ta_moren_style);
	lv_style_set_text_color(&lvgl_ta_moren_style, LV_STATE_DEFAULT, LV_COLOR_MAKE(0xff, 0xff, 0xff));
	lv_style_set_text_font(&lvgl_ta_moren_style, LV_STATE_DEFAULT, (const lv_font_t*)&font_ZiDing_K8_16);
	lv_style_set_radius(&lvgl_ta_moren_style, LV_STATE_DEFAULT, 6);//圆角

	lv_style_set_pad_top(&lvgl_ta_moren_style, LV_STATE_DEFAULT, 2);//内边距上侧尺寸
	lv_style_set_pad_bottom(&lvgl_ta_moren_style, LV_STATE_DEFAULT, 2);//内边距下侧尺寸
	lv_style_set_pad_left(&lvgl_ta_moren_style, LV_STATE_DEFAULT, 2);//内边距左侧尺寸
	lv_style_set_pad_right(&lvgl_ta_moren_style, LV_STATE_DEFAULT, 2);//内边距右侧尺寸

		//默认样式
	lv_style_set_border_opa(&lvgl_ta_moren_style, LV_STATE_DEFAULT, 255);//边框透明度
	lv_style_set_border_width(&lvgl_ta_moren_style, LV_STATE_DEFAULT, 1);//边框宽度
	lv_style_set_border_color(&lvgl_ta_moren_style, LV_STATE_DEFAULT, LV_COLOR_MAKE(0x00, 0x71, 0xbc));//边框颜色
	lv_style_set_border_side(&lvgl_ta_moren_style, LV_STATE_DEFAULT, LV_BORDER_SIDE_FULL);
	lv_style_set_border_blend_mode(&lvgl_ta_moren_style, LV_STATE_DEFAULT, LV_BLEND_MODE_NORMAL);

	lv_style_set_bg_opa(&lvgl_ta_moren_style, LV_STATE_DEFAULT, LV_OPA_COVER);//背景透明度
	lv_style_set_bg_color(&lvgl_ta_moren_style, LV_STATE_DEFAULT, style_moren_bg);//背景上面颜色
	lv_style_set_bg_grad_color(&lvgl_ta_moren_style, LV_STATE_DEFAULT, style_moren_bg);//背景上面颜色


	//按下时
	lv_style_set_border_opa(&lvgl_ta_moren_style, LV_STATE_FOCUSED, 255);//边框透明度
	lv_style_set_border_width(&lvgl_ta_moren_style, LV_STATE_FOCUSED, 1);//边框宽度
	lv_style_set_border_color(&lvgl_ta_moren_style, LV_STATE_FOCUSED, LV_COLOR_MAKE(0x00, 0x71, 0xbc));//边框颜色
	lv_style_set_border_side(&lvgl_ta_moren_style, LV_STATE_FOCUSED, LV_BORDER_SIDE_FULL);
	lv_style_set_border_blend_mode(&lvgl_ta_moren_style, LV_STATE_FOCUSED, LV_BLEND_MODE_NORMAL);

	lv_style_set_bg_opa(&lvgl_ta_moren_style, LV_STATE_FOCUSED, LV_OPA_COVER);//背景透明度
	lv_style_set_bg_color(&lvgl_ta_moren_style, LV_STATE_FOCUSED, style_moren_bg);//背景上面颜色
	lv_style_set_bg_grad_color(&lvgl_ta_moren_style, LV_STATE_FOCUSED, style_moren_bg);//背景上面颜色

	
		//----透明背景容器样式----//
	lv_style_init(&lvgl_touming_cont_style);
	lv_style_set_radius(&lvgl_touming_cont_style, LV_STATE_DEFAULT, 0);
	lv_style_set_border_opa(&lvgl_touming_cont_style, LV_STATE_DEFAULT, 255);//边框透明度
	lv_style_set_border_width(&lvgl_touming_cont_style, LV_STATE_DEFAULT, 0);//边框宽度
	lv_style_set_border_side(&lvgl_touming_cont_style, LV_STATE_DEFAULT, LV_BORDER_SIDE_NONE);
	lv_style_set_border_blend_mode(&lvgl_touming_cont_style, LV_STATE_DEFAULT, LV_BLEND_MODE_NORMAL);
	lv_style_set_pad_top(&lvgl_touming_cont_style, LV_STATE_DEFAULT, 0);//内边距上侧尺寸
	lv_style_set_pad_bottom(&lvgl_touming_cont_style, LV_STATE_DEFAULT, 0);//内边距下侧尺寸
	lv_style_set_pad_left(&lvgl_touming_cont_style, LV_STATE_DEFAULT, 0);//内边距左侧尺寸
	lv_style_set_pad_right(&lvgl_touming_cont_style, LV_STATE_DEFAULT, 0);//内边距右侧尺寸
	//背景
	lv_style_set_bg_opa(&lvgl_touming_cont_style, LV_STATE_DEFAULT, LV_OPA_0);//背景透明度
	lv_style_set_bg_color(&lvgl_touming_cont_style, LV_STATE_DEFAULT, LV_COLOR_MAKE(0x00, 0x5B, 0x97));//背景上面颜色
	lv_style_set_bg_grad_color(&lvgl_touming_cont_style, LV_STATE_DEFAULT, LV_COLOR_MAKE(0x93, 0x93, 0x93));//背景下面颜色

	//----透明背景容器样式----//


		//switch的背景默认样式
	lv_style_init(&lvgl_switch_background_style);
	lv_style_copy(&lvgl_switch_background_style, &lvgl_WuBianKuang_cont_style);
	lv_style_set_bg_opa(&lvgl_switch_background_style, LV_STATE_DEFAULT, LV_OPA_COVER);//背景透明度
	lv_style_set_bg_color(&lvgl_switch_background_style, LV_STATE_DEFAULT, LV_COLOR_MAKE(0xCC, 0xCC, 0xCC));//背景上面颜色
	lv_style_set_bg_grad_color(&lvgl_switch_background_style, LV_STATE_DEFAULT, LV_COLOR_MAKE(0xCC, 0xCC, 0xCC));//背景上面颜色
	lv_style_set_radius(&lvgl_switch_background_style, LV_STATE_DEFAULT, 15);//圆角


	lv_style_set_border_opa(&lvgl_switch_background_style, LV_STATE_FOCUSED, LV_OPA_80);//边框透明度
	lv_style_set_border_color(&lvgl_switch_background_style, LV_STATE_FOCUSED, LV_COLOR_MAKE(0x00, 0x00, 0xff));//边框颜色
	lv_style_set_border_width(&lvgl_switch_background_style, LV_STATE_FOCUSED, 5);//边框宽度


	lv_style_set_shadow_opa(&lvgl_switch_background_style, LV_STATE_FOCUSED, LV_OPA_80);//阴影透明度
	lv_style_set_shadow_color(&lvgl_switch_background_style, LV_STATE_FOCUSED, LV_COLOR_MAKE(0x00, 0x00, 0xff));//阴影颜色
	lv_style_set_shadow_width(&lvgl_switch_background_style, LV_STATE_FOCUSED, 5);//阴影宽度


	//switch的开状态默认样式
	lv_style_init(&lvgl_switch_on_style);
	lv_style_copy(&lvgl_switch_on_style, &lvgl_WuBianKuang_cont_style);
	lv_style_set_bg_opa(&lvgl_switch_on_style, LV_STATE_DEFAULT, LV_OPA_COVER);//背景透明度
	lv_style_set_bg_color(&lvgl_switch_on_style, LV_STATE_DEFAULT, LV_COLOR_MAKE(0x41, 0x97, 0xfe));//背景上面颜色
	lv_style_set_bg_grad_color(&lvgl_switch_on_style, LV_STATE_DEFAULT, LV_COLOR_MAKE(0x41, 0x97, 0xfe));//背景上面颜色
	lv_style_set_radius(&lvgl_switch_on_style, LV_STATE_DEFAULT, 15);//圆角


	//switch的指示器默认样式
	lv_style_init(&lvgl_switch_knob_style);
	lv_style_copy(&lvgl_switch_knob_style, &lvgl_WuBianKuang_cont_style);
	lv_style_set_bg_opa(&lvgl_switch_knob_style, LV_STATE_DEFAULT, LV_OPA_COVER);//背景透明度
	lv_style_set_bg_color(&lvgl_switch_knob_style, LV_STATE_DEFAULT, LV_COLOR_MAKE(0xff, 0xff, 0xff));//背景上面颜色
	lv_style_set_bg_grad_color(&lvgl_switch_knob_style, LV_STATE_DEFAULT, LV_COLOR_MAKE(0xff, 0xff, 0xff));//背景上面颜色
	lv_style_set_radius(&lvgl_switch_knob_style, LV_STATE_DEFAULT, 15);//圆角
	lv_style_set_pad_top(&lvgl_switch_knob_style, LV_STATE_DEFAULT, -3);//内边距上侧尺寸
	lv_style_set_pad_bottom(&lvgl_switch_knob_style, LV_STATE_DEFAULT, -3);//内边距下侧尺寸
	lv_style_set_pad_left(&lvgl_switch_knob_style, LV_STATE_DEFAULT, -3);//内边距左侧尺寸
	lv_style_set_pad_right(&lvgl_switch_knob_style, LV_STATE_DEFAULT, -3);//内边距右侧尺寸

	lv_style_set_shadow_opa(&lvgl_switch_knob_style, LV_STATE_DEFAULT, LV_OPA_80);//阴影透明度
	lv_style_set_shadow_color(&lvgl_switch_knob_style, LV_STATE_DEFAULT, LV_COLOR_MAKE(0x00, 0x00, 0x00));//阴影颜色
	lv_style_set_shadow_width(&lvgl_switch_knob_style, LV_STATE_DEFAULT, 5);//阴影宽度


	lvgl_kb_yangshi_init();
	lvgl_yangshi_preload();
}

lv_style_t lvgl_kb_TEXT_LOWER_moren_style;		//键盘背景默认样式
lv_style_t lvgl_kb_TEXT_UPPER_moren_style;		//键盘按钮默认样式

void lvgl_kb_yangshi_init(void)
{
	//---键盘按钮默认样式----//
	lv_style_init(&lvgl_kb_TEXT_LOWER_moren_style);
	lv_style_set_text_color(&lvgl_kb_TEXT_LOWER_moren_style, LV_STATE_DEFAULT, LV_COLOR_MAKE(0xff, 0xff, 0xff));
	//lv_style_set_text_font(&lvgl_kb_TEXT_LOWER_moren_style, LV_STATE_DEFAULT, (const lv_font_t*)&font_ZiDing_K8_16);
	lv_style_set_radius(&lvgl_kb_TEXT_LOWER_moren_style, LV_STATE_DEFAULT, 6);//圆角

	lv_style_set_pad_top(&lvgl_kb_TEXT_LOWER_moren_style, LV_STATE_DEFAULT, 0);//内边距上侧尺寸
	lv_style_set_pad_bottom(&lvgl_kb_TEXT_LOWER_moren_style, LV_STATE_DEFAULT, 4);//内边距下侧尺寸
	lv_style_set_pad_left(&lvgl_kb_TEXT_LOWER_moren_style, LV_STATE_DEFAULT, 0);//内边距左侧尺寸
	lv_style_set_pad_right(&lvgl_kb_TEXT_LOWER_moren_style, LV_STATE_DEFAULT, 0);//内边距右侧尺寸

	//默认样式
	lv_style_set_border_opa(&lvgl_kb_TEXT_LOWER_moren_style, LV_STATE_DEFAULT, 255);//边框透明度
	lv_style_set_border_width(&lvgl_kb_TEXT_LOWER_moren_style, LV_STATE_DEFAULT, 0);//边框宽度
	lv_style_set_border_color(&lvgl_kb_TEXT_LOWER_moren_style, LV_STATE_DEFAULT, LV_COLOR_MAKE(0x00, 0x71, 0xbc));//边框颜色
	lv_style_set_border_side(&lvgl_kb_TEXT_LOWER_moren_style, LV_STATE_DEFAULT, LV_BORDER_SIDE_NONE);
	lv_style_set_border_blend_mode(&lvgl_kb_TEXT_LOWER_moren_style, LV_STATE_DEFAULT, LV_BLEND_MODE_NORMAL);

	lv_style_set_bg_opa(&lvgl_kb_TEXT_LOWER_moren_style, LV_STATE_DEFAULT, LV_OPA_COVER);//背景透明度
	lv_style_set_bg_color(&lvgl_kb_TEXT_LOWER_moren_style, LV_STATE_DEFAULT, style_moren_bg);//背景上面颜色
	lv_style_set_bg_grad_color(&lvgl_kb_TEXT_LOWER_moren_style, LV_STATE_DEFAULT, style_moren_bg);//背景上面颜色


	//按下时
	lv_style_set_border_opa(&lvgl_kb_TEXT_LOWER_moren_style, LV_STATE_FOCUSED, 255);//边框透明度
	lv_style_set_border_width(&lvgl_kb_TEXT_LOWER_moren_style, LV_STATE_FOCUSED, 0);//边框宽度
	lv_style_set_border_color(&lvgl_kb_TEXT_LOWER_moren_style, LV_STATE_FOCUSED, LV_COLOR_MAKE(0x00, 0x71, 0xbc));//边框颜色
	lv_style_set_border_side(&lvgl_kb_TEXT_LOWER_moren_style, LV_STATE_FOCUSED, LV_BORDER_SIDE_NONE);
	lv_style_set_border_blend_mode(&lvgl_kb_TEXT_LOWER_moren_style, LV_STATE_FOCUSED, LV_BLEND_MODE_NORMAL);

	lv_style_set_bg_opa(&lvgl_kb_TEXT_LOWER_moren_style, LV_STATE_FOCUSED, LV_OPA_COVER);//背景透明度
	lv_style_set_bg_color(&lvgl_kb_TEXT_LOWER_moren_style, LV_STATE_FOCUSED, style_moren_bg);//背景上面颜色
	lv_style_set_bg_grad_color(&lvgl_kb_TEXT_LOWER_moren_style, LV_STATE_FOCUSED, style_moren_bg);//背景上面颜色

//----键盘按钮默认样式----//


//---键盘按钮默认样式----//
	lv_style_init(&lvgl_kb_TEXT_UPPER_moren_style);
	lv_style_set_text_color(&lvgl_kb_TEXT_UPPER_moren_style, LV_STATE_DEFAULT, LV_COLOR_MAKE(0xff, 0xff, 0xff));
	//lv_style_set_text_font(&lvgl_kb_TEXT_UPPER_moren_style, LV_STATE_DEFAULT, (const lv_font_t*)&font_ZiDing_K8_16);
	lv_style_set_radius(&lvgl_kb_TEXT_UPPER_moren_style, LV_STATE_DEFAULT, 6);//圆角

	lv_style_set_pad_top(&lvgl_kb_TEXT_UPPER_moren_style, LV_STATE_DEFAULT, 0);//内边距上侧尺寸
	lv_style_set_pad_bottom(&lvgl_kb_TEXT_UPPER_moren_style, LV_STATE_DEFAULT, 0);//内边距下侧尺寸
	lv_style_set_pad_left(&lvgl_kb_TEXT_UPPER_moren_style, LV_STATE_DEFAULT, 0);//内边距左侧尺寸
	lv_style_set_pad_right(&lvgl_kb_TEXT_UPPER_moren_style, LV_STATE_DEFAULT, 0);//内边距右侧尺寸


	//默认样式
	lv_style_set_border_opa(&lvgl_kb_TEXT_UPPER_moren_style, LV_STATE_DEFAULT, 255);//边框透明度
	lv_style_set_border_width(&lvgl_kb_TEXT_UPPER_moren_style, LV_STATE_DEFAULT, 1);//边框宽度
	lv_style_set_border_color(&lvgl_kb_TEXT_UPPER_moren_style, LV_STATE_DEFAULT, LV_COLOR_MAKE(0x00, 0x71, 0xbc));//边框颜色
	lv_style_set_border_side(&lvgl_kb_TEXT_UPPER_moren_style, LV_STATE_DEFAULT, LV_BORDER_SIDE_FULL);
	lv_style_set_border_blend_mode(&lvgl_kb_TEXT_UPPER_moren_style, LV_STATE_DEFAULT, LV_BLEND_MODE_NORMAL);

	lv_style_set_bg_opa(&lvgl_kb_TEXT_UPPER_moren_style, LV_STATE_DEFAULT, LV_OPA_COVER);//背景透明度
	lv_style_set_bg_color(&lvgl_kb_TEXT_UPPER_moren_style, LV_STATE_DEFAULT, style_moren_bg);//背景上面颜色
	lv_style_set_bg_grad_color(&lvgl_kb_TEXT_UPPER_moren_style, LV_STATE_DEFAULT, style_moren_bg);//背景上面颜色


	//按下时
	lv_style_set_border_opa(&lvgl_kb_TEXT_UPPER_moren_style, LV_STATE_FOCUSED, 255);//边框透明度
	lv_style_set_border_width(&lvgl_kb_TEXT_UPPER_moren_style, LV_STATE_FOCUSED, 1);//边框宽度
	lv_style_set_border_color(&lvgl_kb_TEXT_UPPER_moren_style, LV_STATE_FOCUSED, LV_COLOR_MAKE(0x00, 0x71, 0xbc));//边框颜色
	lv_style_set_border_side(&lvgl_kb_TEXT_UPPER_moren_style, LV_STATE_FOCUSED, LV_BORDER_SIDE_FULL);
	lv_style_set_border_blend_mode(&lvgl_kb_TEXT_UPPER_moren_style, LV_STATE_FOCUSED, LV_BLEND_MODE_NORMAL);

	lv_style_set_bg_opa(&lvgl_kb_TEXT_UPPER_moren_style, LV_STATE_FOCUSED, LV_OPA_COVER);//背景透明度
	lv_style_set_bg_color(&lvgl_kb_TEXT_UPPER_moren_style, LV_STATE_FOCUSED, style_moren_bg);//背景上面颜色
	lv_style_set_bg_grad_color(&lvgl_kb_TEXT_UPPER_moren_style, LV_STATE_FOCUSED, style_moren_bg);//背景上面颜色

//----键盘按钮默认样式----//


}

lv_style_t lvgl_preload_SPINNING_style;		//preload底部圆形默认样式
lv_style_t lvgl_preload_FILLSPIN_style;		//preload旋转的弧形默认样式

void lvgl_yangshi_preload(void)
{

	//----preload底部园默认样式----//
	lv_style_init(&lvgl_preload_SPINNING_style);
	lv_style_set_text_color(&lvgl_preload_SPINNING_style, LV_STATE_DEFAULT, LV_COLOR_MAKE(0xff, 0xff, 0xff));
	lv_style_set_text_font(&lvgl_preload_SPINNING_style, LV_STATE_DEFAULT, (const lv_font_t*)&font_ZiDing_K8_16);
	lv_style_set_radius(&lvgl_preload_SPINNING_style, LV_STATE_DEFAULT, 6);//圆角

	lv_style_set_pad_top(&lvgl_preload_SPINNING_style, LV_STATE_DEFAULT, 0);//内边距上侧尺寸
	lv_style_set_pad_bottom(&lvgl_preload_SPINNING_style, LV_STATE_DEFAULT, 0);//内边距下侧尺寸
	lv_style_set_pad_left(&lvgl_preload_SPINNING_style, LV_STATE_DEFAULT, 0);//内边距左侧尺寸
	lv_style_set_pad_right(&lvgl_preload_SPINNING_style, LV_STATE_DEFAULT, 0);//内边距右侧尺寸

	//线条样式
	lv_style_set_line_color(&lvgl_preload_SPINNING_style, LV_STATE_DEFAULT, LV_COLOR_MAKE(0xff, 0xff, 0xff));
	lv_style_set_line_width(&lvgl_preload_SPINNING_style, LV_STATE_DEFAULT, 10);

	//默认样式
	lv_style_set_border_opa(&lvgl_preload_SPINNING_style, LV_STATE_DEFAULT, LV_OPA_TRANSP);//边框透明度
	lv_style_set_border_width(&lvgl_preload_SPINNING_style, LV_STATE_DEFAULT, 1);//边框宽度
	lv_style_set_border_color(&lvgl_preload_SPINNING_style, LV_STATE_DEFAULT, LV_COLOR_MAKE(0x00, 0x71, 0xbc));//边框颜色
	lv_style_set_border_side(&lvgl_preload_SPINNING_style, LV_STATE_DEFAULT, LV_BORDER_SIDE_NONE);
	lv_style_set_border_blend_mode(&lvgl_preload_SPINNING_style, LV_STATE_DEFAULT, LV_BLEND_MODE_NORMAL);

	lv_style_set_bg_opa(&lvgl_preload_SPINNING_style, LV_STATE_DEFAULT, LV_OPA_TRANSP);//背景透明度
	lv_style_set_bg_color(&lvgl_preload_SPINNING_style, LV_STATE_DEFAULT, style_moren_bg);//背景上面颜色
	lv_style_set_bg_grad_color(&lvgl_preload_SPINNING_style, LV_STATE_DEFAULT, style_moren_bg);//背景上面颜色

//----preload底部园默认样式----//

	//----preload旋转的弧形默认样式----//
	lv_style_init(&lvgl_preload_FILLSPIN_style);
	lv_style_set_text_color(&lvgl_preload_FILLSPIN_style, LV_STATE_DEFAULT, LV_COLOR_MAKE(0xff, 0xff, 0xff));
	lv_style_set_text_font(&lvgl_preload_FILLSPIN_style, LV_STATE_DEFAULT, (const lv_font_t*)&font_ZiDing_K8_16);
	lv_style_set_radius(&lvgl_preload_FILLSPIN_style, LV_STATE_DEFAULT, 6);//圆角

	lv_style_set_pad_top(&lvgl_preload_FILLSPIN_style, LV_STATE_DEFAULT, 2);//内边距上侧尺寸
	lv_style_set_pad_bottom(&lvgl_preload_FILLSPIN_style, LV_STATE_DEFAULT, 2);//内边距下侧尺寸
	lv_style_set_pad_left(&lvgl_preload_FILLSPIN_style, LV_STATE_DEFAULT, 2);//内边距左侧尺寸
	lv_style_set_pad_right(&lvgl_preload_FILLSPIN_style, LV_STATE_DEFAULT, 2);//内边距右侧尺寸

	//线条样式
	lv_style_set_line_color(&lvgl_preload_FILLSPIN_style, LV_STATE_DEFAULT, LV_COLOR_MAKE(0xff, 0xff, 0xff));
	lv_style_set_line_width(&lvgl_preload_FILLSPIN_style, LV_STATE_DEFAULT, 7);

	//默认样式
	lv_style_set_border_opa(&lvgl_preload_FILLSPIN_style, LV_STATE_DEFAULT, LV_OPA_TRANSP);//边框透明度
	lv_style_set_border_width(&lvgl_preload_FILLSPIN_style, LV_STATE_DEFAULT, 1);//边框宽度
	lv_style_set_border_color(&lvgl_preload_FILLSPIN_style, LV_STATE_DEFAULT, LV_COLOR_MAKE(0x00, 0x71, 0xbc));//边框颜色
	lv_style_set_border_side(&lvgl_preload_FILLSPIN_style, LV_STATE_DEFAULT, LV_BORDER_SIDE_NONE);
	lv_style_set_border_blend_mode(&lvgl_preload_FILLSPIN_style, LV_STATE_DEFAULT, LV_BLEND_MODE_NORMAL);

	lv_style_set_bg_opa(&lvgl_preload_FILLSPIN_style, LV_STATE_DEFAULT, LV_OPA_TRANSP);//背景透明度
	lv_style_set_bg_color(&lvgl_preload_FILLSPIN_style, LV_STATE_DEFAULT, style_moren_bg);//背景上面颜色
	lv_style_set_bg_grad_color(&lvgl_preload_FILLSPIN_style, LV_STATE_DEFAULT, style_moren_bg);//背景上面颜色

	//----preload旋转的弧形默认样式----//
}