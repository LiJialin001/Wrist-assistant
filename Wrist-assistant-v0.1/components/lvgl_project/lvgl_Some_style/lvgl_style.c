#include "lvgl_style.h"
#include "string.h"
#include "stdio.h"

_lvgl_Style_Func_Data lvgl_Style_Func_Data;

lv_style_t lvgl_WuBianKuang_cont_style;

void lvgl_Style_create(void)
{
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

	
}