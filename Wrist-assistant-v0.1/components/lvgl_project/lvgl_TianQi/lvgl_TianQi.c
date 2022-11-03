#include "lvgl_TianQi.h"
#include "lvgl_Project.h"


LV_IMG_DECLARE(bmp_BeiJing_BaiTian)
LV_IMG_DECLARE(bmp_BeiJIng_YeWan)
LV_IMG_DECLARE(bmp_DingWei)
LV_IMG_DECLARE(bmp_Du)
LV_IMG_DECLARE(bmp_RiChuRiLuo)
LV_IMG_DECLARE(bmp_BeiJing)


_lvgl_TianQi_GongNeng_Data lvgl_TianQi_GongNeng_Data;

lv_obj_t *lvgl_TianQi_ChengShiMing_text = NULL;
lv_obj_t *lvgl_TianQi_image = NULL;
lv_obj_t *lvgl_TianQi_image2 = NULL;
lv_obj_t *lvgl_TianQi_main_cont = NULL;
lv_obj_t *lvgl_TianQi_FengSu = NULL;
lv_obj_t *lvgl_TianQi_FengXiang = NULL;
lv_obj_t *lvgl_TianQi_JiangShui = NULL;
lv_obj_t *lvgl_TianQi_ShiDu = NULL;
lv_obj_t *lvgl_TianQi_DangTian = NULL;

lv_obj_t *lvgl_TianQi_JinTian_cont = NULL;
lv_obj_t *lvgl_TianQi_MingTian_cont = NULL;
lv_obj_t *lvgl_TianQi_HouTian_cont = NULL;
lv_obj_t *lvgl_TianQi_RiChuRiLuo_cont = NULL;
lv_obj_t *lvgl_TianQi_RiQi= NULL;
lv_obj_t *lvgl_TianQi_ShiJian = NULL;
lv_obj_t *lvgl_TianQi_XingQi = NULL;

static lv_style_t lv_style_src;

static lv_style_t lvgl_TianQi_main_cont_style;
static lv_style_t lvgl_TianQi_TianQi_cont_style;

lv_task_t * lvgl_TianQi_task = NULL;
void lvgl_TianQi_anim_FengSu_cb(void * arc, lv_anim_value_t v);
void lvgl_TianQi_anim_FengXiang_cb(void * arc, lv_anim_value_t v);
void lvgl_TianQi_anim_JiangShui_cb(void * arc, lv_anim_value_t v);
void lvgl_TianQi_anim_ShiDu_cb(void * arc, lv_anim_value_t v);

void lvgl_TianQi_anim_DangTian_cb(void * arc, lv_anim_value_t v);
void lvgl_TianQi_anim_JinTian_cb(void * arc, lv_anim_value_t v);
void lvgl_TianQi_anim_MingTian_cb(void * arc, lv_anim_value_t v);
void lvgl_TianQi_anim_HouTian_cb(void * arc, lv_anim_value_t v);

void lvgl_TianQi_anim_RiQi_cb(void * arc, lv_anim_value_t v);
void lvgl_TianQi_anim_XingQi_cb(void * arc, lv_anim_value_t v);
void lvgl_TianQi_anim_ShiJian_cb(void * arc, lv_anim_value_t v);

//设定位图标
void lvgl_TianQi_DingWei_TuBiao(uint8_t sta)
{

	static lv_obj_t *lvgl_DingWei_TuBiao_image=NULL;

	if (lvgl_DingWei_TuBiao_image == NULL)
	{
		lvgl_DingWei_TuBiao_image = lv_img_create(lvgl_TianQi_main_cont, NULL);
		lv_obj_set_pos(lvgl_DingWei_TuBiao_image, 0, 0);
		lv_img_set_src(lvgl_DingWei_TuBiao_image, &bmp_DingWei);
	}
	if (sta == 1)
	{


	}

}


//设定日出日落
void lvgl_TianQi_Set_RiChuRiLuo(int richu_shi, int richu_fen, int riluo_shi, int riluo_fen,char *richu_str,char *riluo_str)
{
	char buf[20];
	static lv_obj_t *lvgl_TuBiao_image = NULL;
	static lv_obj_t *lvgl_TianQi_RiQi = NULL;
	static lv_obj_t *lvgl_TianQi_RiQi1 = NULL;
	if (lvgl_TianQi_RiChuRiLuo_cont == NULL)
	{

		//----创建容器----//
		lvgl_TianQi_RiChuRiLuo_cont = lv_cont_create(lvgl_TianQi_main_cont,NULL);
		lv_obj_set_pos(lvgl_TianQi_RiChuRiLuo_cont, 0, 204+40);
		lv_obj_set_size(lvgl_TianQi_RiChuRiLuo_cont, 240, 52);
		lv_obj_set_drag_parent(lvgl_TianQi_RiChuRiLuo_cont, true); //启用 / 禁用父对象可拖动
		lv_obj_add_style(lvgl_TianQi_RiChuRiLuo_cont, LV_OBJ_PART_MAIN, &lvgl_TianQi_TianQi_cont_style);

		lvgl_TuBiao_image = lv_img_create(lvgl_TianQi_RiChuRiLuo_cont, NULL);
		lv_obj_set_pos(lvgl_TuBiao_image, 45, 2);
		lv_img_set_src(lvgl_TuBiao_image, &bmp_RiChuRiLuo);

		lvgl_TianQi_RiQi = lv_label_create(lvgl_TianQi_RiChuRiLuo_cont, NULL);
		lv_label_set_long_mode(lvgl_TianQi_RiQi, LV_LABEL_LONG_SROLL_CIRC);//循环滚动
		lv_obj_set_pos(lvgl_TianQi_RiQi, 3, 20);
		lv_obj_set_width(lvgl_TianQi_RiQi, 40);
		lv_obj_set_height(lvgl_TianQi_RiQi, 16);
		lv_label_set_recolor(lvgl_TianQi_RiQi, true);
		lv_label_set_align(lvgl_TianQi_RiQi, LV_LABEL_ALIGN_CENTER);
		lv_label_set_recolor(lvgl_TianQi_RiQi, true);

		lv_obj_add_style(lvgl_TianQi_RiQi, LV_OBJ_PART_MAIN, &lvgl_font_acsii_12_style);

		lv_label_set_anim_speed(lvgl_TianQi_RiQi, 20);

		lvgl_TianQi_RiQi1 = lv_label_create(lvgl_TianQi_RiChuRiLuo_cont, lvgl_TianQi_RiQi);
		lv_obj_set_pos(lvgl_TianQi_RiQi1, 199, 20);
		lv_obj_set_width(lvgl_TianQi_RiQi1, 40);
		lv_obj_set_height(lvgl_TianQi_RiQi1, 16);
		lv_obj_add_style(lvgl_TianQi_RiQi1, LV_OBJ_PART_MAIN, &lvgl_font_acsii_12_style);




	}


	if (richu_shi==0xffff)
	{

		lv_label_set_text(lvgl_TianQi_RiQi, "-:-");
		lv_label_set_text(lvgl_TianQi_RiQi1, "-:-");

		return;
	}
	if(richu_str!=NULL)
	{
		lv_label_set_text(lvgl_TianQi_RiQi, richu_str);

	}else
	{
		sprintf(buf, "%02d:%02d", richu_shi, richu_fen);
		lv_label_set_text(lvgl_TianQi_RiQi, buf);

	}
	if(riluo_str!=NULL)
	{
		lv_label_set_text(lvgl_TianQi_RiQi1, riluo_str);

	}else
	{
		sprintf(buf, "%02d:%02d", riluo_shi, riluo_fen);
		lv_label_set_text(lvgl_TianQi_RiQi1, buf);

	}


}

//设置风向
void lvgl_TianQi_Set_ShiDu(char *str)
{
	char buf[20];

	if (lvgl_TianQi_ShiDu == NULL)
	{
		lvgl_TianQi_ShiDu = lv_label_create(lvgl_TianQi_main_cont, NULL);
		lv_label_set_long_mode(lvgl_TianQi_ShiDu, LV_LABEL_LONG_SROLL_CIRC);//循环滚动
		lv_obj_set_pos(lvgl_TianQi_ShiDu, 175, 129+10);
		lv_obj_set_width(lvgl_TianQi_ShiDu, 60);
		lv_obj_set_height(lvgl_TianQi_ShiDu, 16);
		lv_label_set_recolor(lvgl_TianQi_ShiDu, true);
		lv_label_set_align(lvgl_TianQi_ShiDu, LV_LABEL_ALIGN_LEFT);
		lv_label_set_recolor(lvgl_TianQi_ShiDu, true);

		lv_obj_add_style(lvgl_TianQi_ShiDu, LV_OBJ_PART_MAIN, &lvgl_font12_style);

		lv_label_set_anim_speed(lvgl_TianQi_ShiDu, 20);
	}
	if (str == NULL)
	{
		lv_label_set_text(lvgl_TianQi_ShiDu, "湿度:--");
		return;
	}
	sprintf(buf, "湿度:%s%%", str);
	lv_label_set_text(lvgl_TianQi_ShiDu, buf);

}

//设置风向
void lvgl_TianQi_Set_JiangShui(char *str)
{
	char buf[20];

	if (lvgl_TianQi_JiangShui == NULL)
	{
		lvgl_TianQi_JiangShui = lv_label_create(lvgl_TianQi_main_cont, NULL);
		lv_label_set_long_mode(lvgl_TianQi_JiangShui, LV_LABEL_LONG_SROLL_CIRC);//循环滚动
		lv_obj_set_pos(lvgl_TianQi_JiangShui, 175, 112+10);
		lv_obj_set_width(lvgl_TianQi_JiangShui, 60);
		lv_obj_set_height(lvgl_TianQi_JiangShui, 16);
		lv_label_set_recolor(lvgl_TianQi_JiangShui, true);
		lv_label_set_align(lvgl_TianQi_JiangShui, LV_LABEL_ALIGN_LEFT);
		lv_label_set_recolor(lvgl_TianQi_JiangShui, true);

		lv_obj_add_style(lvgl_TianQi_JiangShui, LV_OBJ_PART_MAIN, &lvgl_font12_style);

		lv_label_set_anim_speed(lvgl_TianQi_JiangShui, 20);
	}
	if (str == NULL)
	{
		lv_label_set_text(lvgl_TianQi_JiangShui, "降水:--");
		return;
	}
	sprintf(buf, "降水:%s%%", str);
	lv_label_set_text(lvgl_TianQi_JiangShui, buf);

}

//设置风向
void lvgl_TianQi_Set_FengXiang(char *str)
{
	char buf[20];

	if (lvgl_TianQi_FengXiang == NULL)
	{
		lvgl_TianQi_FengXiang = lv_label_create(lvgl_TianQi_main_cont, NULL);
		lv_label_set_long_mode(lvgl_TianQi_FengXiang, LV_LABEL_LONG_SROLL_CIRC);//循环滚动
		lv_obj_set_pos(lvgl_TianQi_FengXiang, 175, 96+10);
		lv_obj_set_width(lvgl_TianQi_FengXiang, 60);
		lv_obj_set_height(lvgl_TianQi_FengXiang, 16);
		lv_label_set_recolor(lvgl_TianQi_FengXiang, true);
		lv_label_set_align(lvgl_TianQi_FengXiang, LV_LABEL_ALIGN_LEFT);
		lv_label_set_recolor(lvgl_TianQi_FengXiang, true);

		lv_obj_add_style(lvgl_TianQi_FengXiang, LV_OBJ_PART_MAIN, &lvgl_font12_style);

		lv_label_set_anim_speed(lvgl_TianQi_FengXiang, 20);
	}
	if (str == NULL)
	{
		lv_label_set_text(lvgl_TianQi_FengXiang, "风向:--");
		return;
	}
	sprintf(buf, "风向:%s", str);
	lv_label_set_text(lvgl_TianQi_FengXiang, buf);

}

//设置风速
void lvgl_TianQi_Set_FengSu(char *str)
{
	char buf[20];

	if (lvgl_TianQi_FengSu == NULL)
	{
		lvgl_TianQi_FengSu = lv_label_create(lvgl_TianQi_main_cont, NULL);
		lv_label_set_long_mode(lvgl_TianQi_FengSu, LV_LABEL_LONG_SROLL_CIRC);//循环滚动
		lv_obj_set_pos(lvgl_TianQi_FengSu, 175, 80+10);
		lv_obj_set_width(lvgl_TianQi_FengSu, 60);
		lv_obj_set_height(lvgl_TianQi_FengSu, 16);
		lv_label_set_recolor(lvgl_TianQi_FengSu, true);
		lv_label_set_align(lvgl_TianQi_FengSu, LV_LABEL_ALIGN_LEFT);
		lv_label_set_recolor(lvgl_TianQi_FengSu, true);

		lv_obj_add_style(lvgl_TianQi_FengSu, LV_OBJ_PART_MAIN, &lvgl_font12_style);

		lv_label_set_anim_speed(lvgl_TianQi_FengSu, 20);
	}
	if (str ==NULL)
	{
		lv_label_set_text(lvgl_TianQi_FengSu, "风力:--");
		return;
	}
	sprintf(buf,"风力:%s级", str);
	lv_label_set_text(lvgl_TianQi_FengSu, buf);

}



//设定后天天气
void lvgl_TianQi_Set_TianQi_HouTian(int sta, int num, char *str, int min, int max)
{
	char buf[20];
	static lv_obj_t *lvgl_TuBiao_image = NULL;
	static lv_obj_t *lvgl_TianQi_RiQi = NULL;
	static lv_obj_t *lvgl_TianQi_RiQi1 = NULL;
	if (lvgl_TianQi_HouTian_cont == NULL)
	{
		//----创建容器----//
		lvgl_TianQi_HouTian_cont = lv_cont_create(lvgl_TianQi_main_cont,NULL);
		lv_obj_set_pos(lvgl_TianQi_HouTian_cont, 160, 163);
		lv_obj_set_size(lvgl_TianQi_HouTian_cont, 80, 40);
		lv_obj_set_drag_parent(lvgl_TianQi_HouTian_cont, true); //启用 / 禁用父对象可拖动
		lv_obj_add_style(lvgl_TianQi_HouTian_cont, LV_OBJ_PART_MAIN, &lvgl_TianQi_TianQi_cont_style);

		lvgl_TuBiao_image = lv_img_create(lvgl_TianQi_HouTian_cont, NULL);
		lv_obj_set_pos(lvgl_TuBiao_image, 0, 0);


		lvgl_TianQi_RiQi = lv_label_create(lvgl_TianQi_HouTian_cont, NULL);
		lv_label_set_long_mode(lvgl_TianQi_RiQi, LV_LABEL_LONG_SROLL_CIRC);//循环滚动
		lv_obj_set_pos(lvgl_TianQi_RiQi, 44, 3);
		lv_obj_set_width(lvgl_TianQi_RiQi, 24);
		lv_obj_set_height(lvgl_TianQi_RiQi, 16);
		lv_label_set_recolor(lvgl_TianQi_RiQi, true);
		lv_label_set_align(lvgl_TianQi_RiQi, LV_LABEL_ALIGN_CENTER);
		lv_label_set_recolor(lvgl_TianQi_RiQi, true);
		lv_label_set_text(lvgl_TianQi_RiQi, str);

		lv_obj_add_style(lvgl_TianQi_RiQi, LV_OBJ_PART_MAIN, &lvgl_font12_style);

		lv_label_set_anim_speed(lvgl_TianQi_RiQi, 20);

		lvgl_TianQi_RiQi1 = lv_label_create(lvgl_TianQi_HouTian_cont, lvgl_TianQi_RiQi);
		lv_obj_set_pos(lvgl_TianQi_RiQi1, 40, 20);
		lv_obj_set_width(lvgl_TianQi_RiQi1, 34);
		lv_obj_set_height(lvgl_TianQi_RiQi1, 16);
		lv_obj_add_style(lvgl_TianQi_RiQi1, LV_OBJ_PART_MAIN, &lvgl_font_acsii_12_style);




	}
	if (num > 39 || sta == 0xffff)
	{
		lv_img_set_src(lvgl_TuBiao_image, &bmp_tianqi_40x40_99);
		lv_label_set_text(lvgl_TianQi_RiQi1, "-~-");
		return;
	}
	lv_img_set_src(lvgl_TuBiao_image, bmp_tianqi_40x40_buf[num]);

	sprintf(buf, "%d~%d", min, max);
	lv_label_set_text(lvgl_TianQi_RiQi1, buf);
}
//设定明天天气
void lvgl_TianQi_Set_TianQi_MingTian(int sta, int num, char *str, int min, int max)
{
	char buf[20];
	static lv_obj_t *lvgl_TuBiao_image = NULL;
	static lv_obj_t *lvgl_TianQi_RiQi = NULL;
	static lv_obj_t *lvgl_TianQi_RiQi1 = NULL;
	if (lvgl_TianQi_MingTian_cont == NULL)
	{
		//----创建容器----//
		lvgl_TianQi_MingTian_cont = lv_cont_create(lvgl_TianQi_main_cont,NULL);
		lv_obj_set_pos(lvgl_TianQi_MingTian_cont, 80, 163);
		lv_obj_set_size(lvgl_TianQi_MingTian_cont, 80, 40);
		lv_obj_set_drag_parent(lvgl_TianQi_MingTian_cont, true); //启用 / 禁用父对象可拖动
		lv_obj_add_style(lvgl_TianQi_MingTian_cont, LV_OBJ_PART_MAIN, &lvgl_TianQi_TianQi_cont_style);

		lvgl_TuBiao_image = lv_img_create(lvgl_TianQi_MingTian_cont, NULL);
		lv_obj_set_pos(lvgl_TuBiao_image, 0, 0);


		lvgl_TianQi_RiQi = lv_label_create(lvgl_TianQi_MingTian_cont, NULL);
		lv_label_set_long_mode(lvgl_TianQi_RiQi, LV_LABEL_LONG_SROLL_CIRC);//循环滚动
		lv_obj_set_pos(lvgl_TianQi_RiQi, 44, 3);
		lv_obj_set_width(lvgl_TianQi_RiQi, 24);
		lv_obj_set_height(lvgl_TianQi_RiQi, 16);
		lv_label_set_recolor(lvgl_TianQi_RiQi, true);
		lv_label_set_align(lvgl_TianQi_RiQi, LV_LABEL_ALIGN_CENTER);
		lv_label_set_recolor(lvgl_TianQi_RiQi, true);
		lv_label_set_text(lvgl_TianQi_RiQi, str);

		lv_obj_add_style(lvgl_TianQi_RiQi, LV_OBJ_PART_MAIN, &lvgl_font12_style);

		lv_label_set_anim_speed(lvgl_TianQi_RiQi, 20);

		lvgl_TianQi_RiQi1 = lv_label_create(lvgl_TianQi_MingTian_cont, lvgl_TianQi_RiQi);
		lv_obj_set_pos(lvgl_TianQi_RiQi1, 40, 20);
		lv_obj_set_width(lvgl_TianQi_RiQi1, 34);
		lv_obj_set_height(lvgl_TianQi_RiQi1, 16);
		lv_obj_add_style(lvgl_TianQi_RiQi1, LV_OBJ_PART_MAIN, &lvgl_font_acsii_12_style);
	}
	if (num > 39 || sta == 0xffff)
	{
		lv_img_set_src(lvgl_TuBiao_image, &bmp_tianqi_40x40_99);
		lv_label_set_text(lvgl_TianQi_RiQi1, "-~-");
		return;
	}
	lv_img_set_src(lvgl_TuBiao_image, bmp_tianqi_40x40_buf[num]);

	sprintf(buf, "%d~%d", min, max);
	lv_label_set_text(lvgl_TianQi_RiQi1, buf);
}
//设定今天天气
void lvgl_TianQi_Set_TianQi_JinTian(int sta, int num,char *str,int min,int max)
{
	char buf[20];
	static lv_obj_t *lvgl_TuBiao_image = NULL;
	static lv_obj_t *lvgl_TianQi_RiQi = NULL;
	static lv_obj_t *lvgl_TianQi_RiQi1 = NULL;
	if (lvgl_TianQi_JinTian_cont == NULL)
	{
			//----创建容器----//
		lvgl_TianQi_JinTian_cont = lv_cont_create(lvgl_TianQi_main_cont,NULL);
		//lv_obj_set_pos(lvgl_TianQi_JinTian_cont, 0, 163);
		lv_obj_set_pos(lvgl_TianQi_JinTian_cont, 0, lv_obj_get_height(lv_scr_act())+5);
		lv_obj_set_size(lvgl_TianQi_JinTian_cont, 80, 40);
		lv_obj_set_drag_parent(lvgl_TianQi_JinTian_cont, true); //启用 / 禁用父对象可拖动
		lv_obj_add_style(lvgl_TianQi_JinTian_cont, LV_OBJ_PART_MAIN, &lvgl_TianQi_TianQi_cont_style);

		lvgl_TuBiao_image = lv_img_create(lvgl_TianQi_JinTian_cont, NULL);
		lv_obj_set_pos(lvgl_TuBiao_image, 0, 0);


		lvgl_TianQi_RiQi = lv_label_create(lvgl_TianQi_JinTian_cont, NULL);
		lv_label_set_long_mode(lvgl_TianQi_RiQi, LV_LABEL_LONG_SROLL_CIRC);//循环滚动
		lv_obj_set_pos(lvgl_TianQi_RiQi, 44, 3);
		lv_obj_set_width(lvgl_TianQi_RiQi, 24);
		lv_obj_set_height(lvgl_TianQi_RiQi, 16);
		lv_label_set_recolor(lvgl_TianQi_RiQi, true);
		lv_label_set_align(lvgl_TianQi_RiQi, LV_LABEL_ALIGN_CENTER);
		lv_label_set_recolor(lvgl_TianQi_RiQi, true);
		lv_label_set_text(lvgl_TianQi_RiQi, str);

		lv_obj_add_style(lvgl_TianQi_RiQi, LV_OBJ_PART_MAIN, &lvgl_font12_style);

		lv_label_set_anim_speed(lvgl_TianQi_RiQi, 20);

		lvgl_TianQi_RiQi1 = lv_label_create(lvgl_TianQi_JinTian_cont, lvgl_TianQi_RiQi);
		lv_obj_set_pos(lvgl_TianQi_RiQi1, 40, 20);
		lv_obj_set_width(lvgl_TianQi_RiQi1, 34);
		lv_obj_set_height(lvgl_TianQi_RiQi1, 16);
		lv_obj_add_style(lvgl_TianQi_RiQi1, LV_OBJ_PART_MAIN, &lvgl_font_acsii_12_style);
	}
	if (num > 39 || sta == 0xffff)
	{
		lv_img_set_src(lvgl_TuBiao_image, &bmp_tianqi_40x40_99);
		lv_label_set_text(lvgl_TianQi_RiQi1, "-~-");
		return;
	}
	lv_img_set_src(lvgl_TuBiao_image, bmp_tianqi_40x40_buf[num]);

	sprintf(buf,"%d~%d",min,max);
	lv_label_set_text(lvgl_TianQi_RiQi1, buf);
}

//设定天气
void lvgl_TianQi_Set_DangTianQi(int sta,int num,int wendu,char *str,int min, int max)
{

	char buf[20];
	static lv_obj_t *lvgl_TuBiao_image = NULL;
	static lv_obj_t *lvgl_TuBiao_image1 = NULL;
	static lv_obj_t *lvgl_TianQi_RiQi = NULL;
	static lv_obj_t *lvgl_TianQi_RiQi1 = NULL;
	static lv_obj_t *lvgl_TianQi_RiQi2 = NULL;
	if (lvgl_TianQi_DangTian == NULL)
	{
		//----创建容器----//
		lvgl_TianQi_DangTian = lv_cont_create(lvgl_TianQi_main_cont,NULL);
		lv_obj_set_pos(lvgl_TianQi_DangTian, 0, 76);
		lv_obj_set_size(lvgl_TianQi_DangTian, 160, 80+10);
		lv_obj_set_drag_parent(lvgl_TianQi_DangTian, true); //启用 / 禁用父对象可拖动
		lv_obj_add_style(lvgl_TianQi_DangTian, LV_OBJ_PART_MAIN, &lvgl_TianQi_TianQi_cont_style);

		//--天气图标--//
		lvgl_TuBiao_image = lv_img_create(lvgl_TianQi_DangTian, NULL);
		lv_obj_set_pos(lvgl_TuBiao_image, 80, 0);

		//--°图标--//
		lvgl_TuBiao_image1 = lv_img_create(lvgl_TianQi_DangTian, NULL);
		lv_obj_set_pos(lvgl_TuBiao_image1, 70, 2);
		lv_img_set_src(lvgl_TuBiao_image1, &bmp_Du);

		//--温度--//
		lvgl_TianQi_RiQi = lv_label_create(lvgl_TianQi_DangTian, NULL);
		lv_label_set_long_mode(lvgl_TianQi_RiQi, LV_LABEL_LONG_EXPAND);//循环滚动
		lv_obj_set_pos(lvgl_TianQi_RiQi, 4, -5);
		lv_obj_set_width(lvgl_TianQi_RiQi, 70);
		lv_obj_set_height(lvgl_TianQi_RiQi, 48);
		lv_label_set_align(lvgl_TianQi_RiQi, LV_LABEL_ALIGN_CENTER);
		lv_label_set_recolor(lvgl_TianQi_RiQi, true);

		lv_obj_add_style(lvgl_TianQi_RiQi, LV_OBJ_PART_MAIN, &lvgl_font_acsii_48_style);

		lv_label_set_anim_speed(lvgl_TianQi_RiQi, 20);


		//--天气 （晴 阴）--//
		lvgl_TianQi_RiQi1 = lv_label_create(lvgl_TianQi_DangTian, NULL);
		lv_label_set_long_mode(lvgl_TianQi_RiQi1, LV_LABEL_LONG_SROLL_CIRC);//循环滚动
		lv_obj_set_pos(lvgl_TianQi_RiQi1, 42, 56);
		lv_obj_set_width(lvgl_TianQi_RiQi1, 55);
		lv_obj_set_height(lvgl_TianQi_RiQi1, 20);
		lv_label_set_recolor(lvgl_TianQi_RiQi1, true);
		lv_label_set_align(lvgl_TianQi_RiQi1, LV_LABEL_ALIGN_CENTER);
		lv_label_set_recolor(lvgl_TianQi_RiQi1, true);
		lv_label_set_text(lvgl_TianQi_RiQi1, str);

		lv_obj_add_style(lvgl_TianQi_RiQi1, LV_OBJ_PART_MAIN, &lvgl_font12_style);

		lv_label_set_anim_speed(lvgl_TianQi_RiQi1, 20);

		//----温度范围---//
		lvgl_TianQi_RiQi2 = lv_label_create(lvgl_TianQi_DangTian, lvgl_TianQi_RiQi1);
		lv_obj_set_pos(lvgl_TianQi_RiQi2, 10, 56);
		lv_obj_set_width(lvgl_TianQi_RiQi2, 34);
		lv_obj_set_height(lvgl_TianQi_RiQi2, 16);
		lv_obj_add_style(lvgl_TianQi_RiQi2, LV_OBJ_PART_MAIN, &lvgl_font_acsii_12_style);
	}
	if (num > 39 || sta == 0xffff)
	{
		lv_img_set_src(lvgl_TuBiao_image, &bmp_tianqi_80x80_99);

		lv_label_set_text(lvgl_TianQi_RiQi, "--");
		lv_label_set_text(lvgl_TianQi_RiQi1, "--");
		lv_label_set_text(lvgl_TianQi_RiQi2, "-~-");

		return;
	}
	lv_img_set_src(lvgl_TuBiao_image, bmp_tianqi_80x80_buf[num]);

	sprintf(buf, "%d~%d", min, max);
	lv_label_set_text(lvgl_TianQi_RiQi2, buf);
	sprintf(buf, "%d", wendu);
	lv_label_set_text(lvgl_TianQi_RiQi, buf);
	lv_label_set_text(lvgl_TianQi_RiQi1, str);
}


//设置温度
void lvgl_TianQi_Set_WenDu(int dat)
{
	char buf[20];
	static lv_obj_t *lvgl_text = NULL;
	if (lvgl_text == NULL)
	{
		lvgl_text = lv_label_create(lvgl_TianQi_main_cont, NULL);
		lv_label_set_long_mode(lvgl_text, LV_LABEL_LONG_SROLL_CIRC);//循环滚动
		lv_obj_set_pos(lvgl_text, 10, 83);
		lv_obj_set_width(lvgl_text, 60);
		lv_obj_set_height(lvgl_text, 60);
		lv_label_set_recolor(lvgl_text, true);
		lv_label_set_align(lvgl_text, LV_LABEL_ALIGN_CENTER);
		lv_label_set_recolor(lvgl_text, true);

		lv_obj_add_style(lvgl_text, LV_OBJ_PART_MAIN, &lvgl_font_acsii_48_style);

		lv_label_set_anim_speed(lvgl_text, 20);
	}
	if (dat == 0xffff)
	{
		lv_label_set_text(lvgl_text, "--");
		return;
	}
	sprintf(buf,"%d", dat);
	lv_label_set_text(lvgl_text, buf);

}

//设置星期
void lvgl_TianQi_Set_XingQi(int dat)
{
	char buf[20];
	if (lvgl_TianQi_XingQi == NULL)
	{
		lvgl_TianQi_XingQi = lv_label_create(lvgl_TianQi_main_cont, NULL);
		lv_label_set_long_mode(lvgl_TianQi_XingQi, LV_LABEL_LONG_SROLL_CIRC);//循环滚动
		lv_obj_set_pos(lvgl_TianQi_XingQi, 90, 47+10);
		lv_obj_set_width(lvgl_TianQi_XingQi, 49);
		lv_obj_set_height(lvgl_TianQi_XingQi, 16);
		lv_label_set_recolor(lvgl_TianQi_XingQi, true);
		lv_label_set_align(lvgl_TianQi_XingQi, LV_LABEL_ALIGN_CENTER);
		lv_label_set_recolor(lvgl_TianQi_XingQi, true);

		lv_obj_add_style(lvgl_TianQi_XingQi, LV_OBJ_PART_MAIN, &lvgl_font12_style);

		lv_label_set_anim_speed(lvgl_TianQi_XingQi, 20);
	}
	if (dat == 0xffff)
	{
		lv_label_set_text(lvgl_TianQi_XingQi, "---");
		return;
	}
	if (dat == 1)
	{
		sprintf(buf, "星期一");
	}else if (dat == 2)
	{
		sprintf(buf, "星期二");
	}
	else if (dat == 3)
	{
		sprintf(buf, "星期三");
	}
	else if (dat == 4)
	{
		sprintf(buf, "星期四");
	}
	else if (dat == 5)
	{
		sprintf(buf, "星期五");
	}
	else if (dat == 6)
	{
		sprintf(buf, "星期六");
	}
	else if (dat == 7)
	{
		sprintf(buf, "星期日");
	}

	lv_label_set_text(lvgl_TianQi_XingQi, buf);
}

//设置日期
void lvgl_TianQi_Set_RiQi(int nian,int yue,int ri, char *str)
{
	char buf[20];

	if (lvgl_TianQi_RiQi == NULL)
	{
		lvgl_TianQi_RiQi = lv_label_create(lvgl_TianQi_main_cont, NULL);
		lv_label_set_long_mode(lvgl_TianQi_RiQi, LV_LABEL_LONG_SROLL_CIRC);//循环滚动
		lv_obj_set_pos(lvgl_TianQi_RiQi, 5, 48);
		lv_obj_set_width(lvgl_TianQi_RiQi, 93);
		lv_obj_set_height(lvgl_TianQi_RiQi, 16);
		lv_label_set_align(lvgl_TianQi_RiQi, LV_LABEL_ALIGN_CENTER);
		lv_label_set_recolor(lvgl_TianQi_RiQi, true);

		lv_obj_add_style(lvgl_TianQi_RiQi, LV_OBJ_PART_MAIN, &lvgl_font12_style);

		lv_label_set_anim_speed(lvgl_TianQi_RiQi, 20);
	}
	if (nian == 0xffff)
	{
		lv_label_set_text(lvgl_TianQi_RiQi, "--/--/--");
		return;
	}
	if (str!=NULL)
	{
		lv_label_set_text(lvgl_TianQi_RiQi, str);
		return;
	}
	sprintf(buf, "%d/%02d/%02d", nian,yue,ri);
	lv_label_set_text(lvgl_TianQi_RiQi, buf);

}

//设置日期
void lvgl_TianQi_Set_ShiJian(int shi, int fen, char *str)
{
	char buf[20];
	if (lvgl_TianQi_ShiJian == NULL)
	{
		lvgl_TianQi_ShiJian = lv_label_create(lvgl_TianQi_main_cont, NULL);
		lv_label_set_long_mode(lvgl_TianQi_ShiJian, LV_LABEL_LONG_EXPAND);//循环滚动
	lv_obj_set_pos(lvgl_TianQi_ShiJian, 135, 30);
	lv_obj_set_width(lvgl_TianQi_ShiJian, 90);
	lv_obj_set_height(lvgl_TianQi_ShiJian, 32);
		lv_label_set_align(lvgl_TianQi_ShiJian, LV_LABEL_ALIGN_CENTER);
		lv_label_set_recolor(lvgl_TianQi_ShiJian, true);

		lv_obj_add_style(lvgl_TianQi_ShiJian, LV_OBJ_PART_MAIN, &lvgl_font_acsii_32_style);

		lv_label_set_anim_speed(lvgl_TianQi_ShiJian, 20);
	}
	if (shi == 0xffff)
	{
		lv_label_set_text(lvgl_TianQi_ShiJian, "--:--");
		return;
	}
	if (str != NULL)
	{
		lv_label_set_text(lvgl_TianQi_ShiJian, str);
		return;
	}
	sprintf(buf, "%02d:%02d", shi, fen);
	lv_label_set_text(lvgl_TianQi_ShiJian, buf);




}
//设置城市名
void lvgl_TianQi_Set_ChengShi(char *str)
{

	if (lvgl_TianQi_ChengShiMing_text == NULL)
	{
		lvgl_TianQi_ChengShiMing_text = lv_label_create(lvgl_TianQi_main_cont,NULL);
		lv_label_set_long_mode(lvgl_TianQi_ChengShiMing_text, LV_LABEL_LONG_SROLL_CIRC);//循环滚动
		lv_obj_set_pos(lvgl_TianQi_ChengShiMing_text, 0, 8);
		lv_obj_set_width(lvgl_TianQi_ChengShiMing_text, 240);
		lv_obj_set_height(lvgl_TianQi_ChengShiMing_text, 30);
		lv_label_set_recolor(lvgl_TianQi_ChengShiMing_text, true);
		lv_label_set_align(lvgl_TianQi_ChengShiMing_text, LV_LABEL_ALIGN_CENTER);
		lv_label_set_recolor(lvgl_TianQi_ChengShiMing_text, true);

		lv_obj_add_style(lvgl_TianQi_ChengShiMing_text, LV_OBJ_PART_MAIN, &lvgl_font24_style);

		lv_label_set_anim_speed(lvgl_TianQi_ChengShiMing_text, 20);
	}
	lv_label_set_text(lvgl_TianQi_ChengShiMing_text, str);
}


void lvgl_TianQi_event_cb(struct _lv_obj_t * obj, lv_event_t event)
{
	if (obj == lvgl_TianQi_main_cont)
	{
		//TianQi_debug("cb:%d\r\n", event);
		switch (event)
		{

		case lvgl_shuaxin_jieshu_event:

			lvgl_TianQi_ShuaXin_jieshu();
		break;


		case LV_EVENT_DELETE:

			lvgl_TianQi_main_cont = NULL;
			TianQi_debug("删除窗口\r\n");
			break;

		case LV_EVENT_PRESSING://对象被持续按下
			//if (lv_obj_get_y(lvgl_TianQi_main_cont) < 0)
			//{
			//	lv_obj_set_y(lvgl_TianQi_main_cont, 0);
			//}

			break;
		case LV_EVENT_PRESSED://对象已被按下


			break;
		case LV_EVENT_DRAG_END://拖动结束后

			if (lv_obj_get_x(lvgl_TianQi_main_cont) != 0)
			{
				if (lv_obj_get_x(lvgl_TianQi_main_cont) > 50)
				{
					lvgl_TianQi_close();
				}
				else
				{
					lv_obj_set_x(lvgl_TianQi_main_cont, 0);
				}
			}

			if (lv_obj_get_y(lvgl_TianQi_main_cont) > lvgl_ShuaXin_GaoDu)
			{
				lvgl_TianQi_shuaxin_kaishi();
			}
			else if (lv_obj_get_y(lvgl_TianQi_main_cont) > 0 && lv_obj_get_y(lvgl_TianQi_main_cont) < lvgl_ShuaXin_GaoDu)
			{
				lvgl_TianQi_GongNeng_Data.ShuaXin_Sta = lvgl_ShuaXin_JieShu;

				lv_obj_set_y(lvgl_TianQi_main_cont, 0);
			}

			if (lv_obj_get_y(lvgl_TianQi_main_cont) < 0)
			{
				lvgl_TianQi_GongNeng_Data.ShuaXin_Sta = lvgl_ShuaXin_JieShu;

				lv_obj_set_y(lvgl_TianQi_main_cont, 0);
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
void lvgl_TianQi_ShuaXin_event_cb(struct _lv_obj_t * obj, lv_event_t event)
{
	if (obj == lvgl_TianQi_ChengShiMing_text)
	{
		TianQi_debug("刷新天气:%d\r\n", event);
	}
	TianQi_debug("天气回调消息:%d\r\n", event);
}

void lvgl_TianQi_create(lv_obj_t * Fu)
{

	if (lvgl_TianQi_main_cont == NULL)
	{
		lv_style_init(&lvgl_TianQi_main_cont_style);
		lv_style_copy(&lvgl_TianQi_main_cont_style, &lvgl_WuBianKuang_cont_style);


		//----天气40x40图标cont容器样式----//
		lv_style_init(&lvgl_TianQi_TianQi_cont_style);
		lv_style_set_radius(&lvgl_TianQi_TianQi_cont_style, LV_STATE_DEFAULT, 0);
		lv_style_set_border_opa(&lvgl_TianQi_TianQi_cont_style, LV_STATE_DEFAULT, 255);//边框透明度
		lv_style_set_border_width(&lvgl_TianQi_TianQi_cont_style, LV_STATE_DEFAULT, 0);//边框宽度
		lv_style_set_border_side(&lvgl_TianQi_TianQi_cont_style, LV_STATE_DEFAULT, LV_BORDER_SIDE_NONE);
		lv_style_set_border_blend_mode(&lvgl_TianQi_TianQi_cont_style, LV_STATE_DEFAULT, LV_BLEND_MODE_NORMAL);
		lv_style_set_pad_top(&lvgl_TianQi_TianQi_cont_style, LV_STATE_DEFAULT, 0);//内边距上侧尺寸
		lv_style_set_pad_bottom(&lvgl_TianQi_TianQi_cont_style, LV_STATE_DEFAULT, 0);//内边距下侧尺寸
		lv_style_set_pad_left(&lvgl_TianQi_TianQi_cont_style, LV_STATE_DEFAULT, 0);//内边距左侧尺寸
		lv_style_set_pad_right(&lvgl_TianQi_TianQi_cont_style, LV_STATE_DEFAULT, 0);//内边距右侧尺寸
		//背景
		lv_style_set_bg_opa(&lvgl_TianQi_TianQi_cont_style, LV_STATE_DEFAULT, LV_OPA_0);//背景透明度
		lv_style_set_bg_color(&lvgl_TianQi_TianQi_cont_style, LV_STATE_DEFAULT, LV_COLOR_MAKE(0x00, 0x5B, 0x97));//背景上面颜色
		lv_style_set_bg_grad_color(&lvgl_TianQi_TianQi_cont_style, LV_STATE_DEFAULT, LV_COLOR_MAKE(0x93, 0x93, 0x93));//背景下面颜色


		//----天气40x40图标cont容器样式----//
		lv_style_init(&lv_style_src);

		lv_style_set_line_color(&lv_style_src, LV_STATE_DEFAULT, LV_COLOR_MAKE(0x49, 0x4A, 0x4C));
		lv_style_set_line_width(&lv_style_src, LV_STATE_DEFAULT, 0);
		lv_style_set_line_rounded(&lv_style_src, LV_STATE_DEFAULT, false);//取消端点圆弧
		lv_style_set_line_opa(&lv_style_src, LV_STATE_DEFAULT, 100);//线透明度
		lv_style_set_border_opa(&lv_style_src, LV_STATE_DEFAULT, 100);//透明度

		lv_style_set_bg_opa(&lv_style_src, LV_STATE_DEFAULT, LV_OPA_COVER);//背景透明度
		lv_style_set_bg_color(&lv_style_src, LV_STATE_DEFAULT, LV_COLOR_RED);//背景色
		lv_style_set_bg_grad_color(&lv_style_src, LV_STATE_DEFAULT, LV_COLOR_BLUE);

		//----创建容器----//
		lvgl_TianQi_main_cont = lv_cont_create(Fu, NULL);
		lv_obj_set_pos(lvgl_TianQi_main_cont, 0, 0);
		lv_obj_set_size(lvgl_TianQi_main_cont, lv_obj_get_width(Fu), lv_obj_get_height(Fu));
		//lv_obj_set_drag_parent(lvgl_TianQi_main_cont, true); //启用 / 禁用父对象可拖动

		lv_obj_set_click(lvgl_TianQi_main_cont, true); //启用 / 禁用可点击
		lv_obj_set_drag(lvgl_TianQi_main_cont, true);//启用/禁用对象可拖动
		lv_obj_set_drag_dir(lvgl_TianQi_main_cont, LV_DRAG_DIR_ONE);//设置拖动方向
		//lv_obj_set_drag_throw(lvgl_TianQi_main_cont, true);//启用/禁用拖动后是否有惯性移动
		//lv_obj_set_drag_parent(lvgl_TianQi_main_cont, true); //启用 / 禁用父对象可拖动
		lv_obj_add_style(lvgl_TianQi_main_cont, LV_OBJ_PART_MAIN, &lvgl_TianQi_main_cont_style);//设置样式
		lv_obj_set_event_cb(lvgl_TianQi_main_cont, lvgl_TianQi_event_cb);//设置回调函数



		//lvgl_TianQi_image = lv_img_create(lvgl_TianQi_main_cont, NULL);
		//lv_obj_set_pos(lvgl_TianQi_image,0, 0);
		//lv_img_set_src(lvgl_TianQi_image, &bmp_BeiJing_BaiTian);

		lvgl_TianQi_Set_ChengShi("下拉刷新");
		lvgl_TianQi_Set_RiQi(0xffff, 10, 30, NULL);
		lvgl_TianQi_Set_XingQi(0XFFFF);
		//lvgl_TianQi_Set_WenDu(0XFFFF);
		lvgl_TianQi_Set_ShiJian(0XFFFF, 0XFFFF, NULL);
		lvgl_TianQi_Set_DangTianQi(0XFFFF, 0, 35, "晴", 10, 28);
		lvgl_TianQi_Set_TianQi_JinTian(0XFFFF, 0, "今天", 10, 30);
		lvgl_TianQi_Set_TianQi_MingTian(0XFFFF, 0, "明天", 10, 30);
		lvgl_TianQi_Set_TianQi_HouTian(0XFFFF, 0, "后天", 10, 30);
		lvgl_TianQi_Set_FengSu(NULL);
		lvgl_TianQi_Set_FengXiang(NULL);
		lvgl_TianQi_Set_JiangShui(NULL);
		lvgl_TianQi_Set_ShiDu(NULL);
		lvgl_TianQi_Set_RiChuRiLuo(0XFFFF, 20, 17, 30, NULL, NULL);


		//lv_obj_set_event_cb(lvgl_TianQi_ChengShiMing_text, lvgl_TianQi_event_cb);//设置回调函数
		//lv_obj_set_click(lvgl_TianQi_ChengShiMing_text, true); //启用 / 禁用可点击


		//lvgl_ShuaXin_create(lv_scr_act());


		lvgl_TianQi_GongNeng_Data.JinTian_y = lv_obj_get_height(lv_scr_act());
		lvgl_TianQi_GongNeng_Data.MingTian_y = 280;
		lvgl_TianQi_GongNeng_Data.HouTian_y = 310;
		lvgl_TianQi_GongNeng_Data.DongHua_Sta = 1;
		lvgl_TianQi_GongNeng_Data.ShuaXin_Sta = lvgl_ShuaXin_JieShu;

		system_data.HuoQu_TianQi_Flag = true;//刷新一次天气



		TianQi_debug("创建窗口\r\n");
	}
	else
	{

		TianQi_debug("显示窗口\r\n");
	}

	lv_obj_move_background(lvgl_TianQi_main_cont);
	lv_obj_set_pos(lvgl_TianQi_main_cont, 0, 0);
	lvgl_set_obj_show(lvgl_TianQi_main_cont);
	lvgl_TianQi_DongHua_Jin();

	lvgl_task_create(&lvgl_TianQi_task,lvgl_TianQi_TaskCb, 1000, LV_TASK_PRIO_LOWEST, NULL);

}
void lvgl_TianQi_close(void)
{

	//lv_obj_del_async(lvgl_LaoHuangLi_main_cont);

	lvgl_task_delete(&lvgl_TianQi_task);

	lvgl_set_obj_hide(lvgl_TianQi_main_cont);

	lvgl_clock_create(lv_scr_act());

}

//滑入动画
void lvgl_TianQi_DongHua_Jin(void)
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


	lv_obj_set_x(lvgl_TianQi_FengSu, lv_obj_get_height(lv_scr_act())+5);
	lv_obj_set_x(lvgl_TianQi_FengXiang, lv_obj_get_height(lv_scr_act())+5);
	lv_obj_set_x(lvgl_TianQi_JiangShui, lv_obj_get_height(lv_scr_act())+5);
	lv_obj_set_x(lvgl_TianQi_ShiDu, lv_obj_get_height(lv_scr_act())+5);

	lv_obj_set_y(lvgl_TianQi_JinTian_cont, lv_obj_get_height(lv_scr_act())+5);
	lv_obj_set_y(lvgl_TianQi_MingTian_cont, lv_obj_get_height(lv_scr_act())+5);
	lv_obj_set_y(lvgl_TianQi_HouTian_cont, lv_obj_get_height(lv_scr_act())+5);

	lv_obj_set_x(lvgl_TianQi_DangTian, -160);

	lv_obj_set_y(lvgl_TianQi_RiQi, -100);
	lv_obj_set_y(lvgl_TianQi_XingQi, -100);
	lv_obj_set_y(lvgl_TianQi_ShiJian, -100);


	lv_anim_init(&lvgl_TianQi_GongNeng_Data.lv_anim_ShiJian);
	lv_anim_set_exec_cb(&lvgl_TianQi_GongNeng_Data.lv_anim_ShiJian, lvgl_TianQi_anim_ShiJian_cb);
	//lv_anim_set_ready_cb(&lvgl_TianQi_GongNeng_Data.lv_anim_ShiJian, arc_lvgl_TianQi_GongNeng_Data.lv_anim_ShiJian_jia);
	lv_anim_set_values(&lvgl_TianQi_GongNeng_Data.lv_anim_ShiJian, -100, 30);
	lv_anim_set_time(&lvgl_TianQi_GongNeng_Data.lv_anim_ShiJian, 100);
	lv_anim_set_var(&lvgl_TianQi_GongNeng_Data.lv_anim_ShiJian, lvgl_TianQi_ShiJian);
	lv_anim_set_path(&lvgl_TianQi_GongNeng_Data.lv_anim_ShiJian, &path);
	lv_anim_start(&lvgl_TianQi_GongNeng_Data.lv_anim_ShiJian);


	lv_anim_init(&lvgl_TianQi_GongNeng_Data.lv_anim_XingQi);
	lv_anim_set_exec_cb(&lvgl_TianQi_GongNeng_Data.lv_anim_XingQi, lvgl_TianQi_anim_XingQi_cb);
	//lv_anim_set_ready_cb(&lvgl_TianQi_GongNeng_Data.lv_anim_XingQi, arc_lvgl_TianQi_GongNeng_Data.lv_anim_XingQi_jia);
	lv_anim_set_values(&lvgl_TianQi_GongNeng_Data.lv_anim_XingQi, -100, 47);
	lv_anim_set_time(&lvgl_TianQi_GongNeng_Data.lv_anim_XingQi, 200);
	lv_anim_set_var(&lvgl_TianQi_GongNeng_Data.lv_anim_XingQi, lvgl_TianQi_XingQi);
	lv_anim_set_path(&lvgl_TianQi_GongNeng_Data.lv_anim_XingQi, &path);
	lv_anim_start(&lvgl_TianQi_GongNeng_Data.lv_anim_XingQi);

	lv_anim_init(&lvgl_TianQi_GongNeng_Data.lv_anim_RiQi);
	lv_anim_set_exec_cb(&lvgl_TianQi_GongNeng_Data.lv_anim_RiQi, lvgl_TianQi_anim_RiQi_cb);
	//lv_anim_set_ready_cb(&lvgl_TianQi_GongNeng_Data.lv_anim_RiQi, arc_lvgl_TianQi_GongNeng_Data.lv_anim_RiQi_jia);
	lv_anim_set_values(&lvgl_TianQi_GongNeng_Data.lv_anim_RiQi, -100, 48);
	lv_anim_set_time(&lvgl_TianQi_GongNeng_Data.lv_anim_RiQi, 300);
	lv_anim_set_var(&lvgl_TianQi_GongNeng_Data.lv_anim_RiQi, lvgl_TianQi_RiQi);
	lv_anim_set_path(&lvgl_TianQi_GongNeng_Data.lv_anim_RiQi, &path);
	lv_anim_start(&lvgl_TianQi_GongNeng_Data.lv_anim_RiQi);

	lv_anim_init(&lvgl_TianQi_GongNeng_Data.lv_anim_DangTian);
	lv_anim_set_exec_cb(&lvgl_TianQi_GongNeng_Data.lv_anim_DangTian, lvgl_TianQi_anim_DangTian_cb);
	//lv_anim_set_ready_cb(&lvgl_TianQi_GongNeng_Data.lv_anim_DangTian, arc_lvgl_TianQi_GongNeng_Data.lv_anim_DangTian_jia);
	lv_anim_set_values(&lvgl_TianQi_GongNeng_Data.lv_anim_DangTian, -160, 0);
	lv_anim_set_time(&lvgl_TianQi_GongNeng_Data.lv_anim_DangTian, 100);
	lv_anim_set_var(&lvgl_TianQi_GongNeng_Data.lv_anim_DangTian, lvgl_TianQi_DangTian);
	lv_anim_set_path(&lvgl_TianQi_GongNeng_Data.lv_anim_DangTian, &path);
	lv_anim_start(&lvgl_TianQi_GongNeng_Data.lv_anim_DangTian);

	lv_anim_init(&lvgl_TianQi_GongNeng_Data.lv_anim_FengSu);
	lv_anim_set_exec_cb(&lvgl_TianQi_GongNeng_Data.lv_anim_FengSu, lvgl_TianQi_anim_FengSu_cb);
	//lv_anim_set_ready_cb(&lvgl_TianQi_GongNeng_Data.lv_anim_FengSu, arc_lvgl_TianQi_GongNeng_Data.lv_anim_FengSu_jia);
	lv_anim_set_values(&lvgl_TianQi_GongNeng_Data.lv_anim_FengSu, lv_obj_get_height(lv_scr_act()), 175);
	lv_anim_set_time(&lvgl_TianQi_GongNeng_Data.lv_anim_FengSu, 100);
	lv_anim_set_var(&lvgl_TianQi_GongNeng_Data.lv_anim_FengSu, lvgl_TianQi_FengSu);
	lv_anim_set_path(&lvgl_TianQi_GongNeng_Data.lv_anim_FengSu, &path);
	lv_anim_start(&lvgl_TianQi_GongNeng_Data.lv_anim_FengSu);


	lv_anim_init(&lvgl_TianQi_GongNeng_Data.lv_anim_FengXiang);
	lv_anim_set_exec_cb(&lvgl_TianQi_GongNeng_Data.lv_anim_FengXiang, lvgl_TianQi_anim_FengXiang_cb);
	//lv_anim_set_ready_cb(&lvgl_TianQi_GongNeng_Data.lv_anim_FengXiang, arc_lvgl_TianQi_GongNeng_Data.lv_anim_FengXiang_jia);
	lv_anim_set_values(&lvgl_TianQi_GongNeng_Data.lv_anim_FengXiang, lv_obj_get_height(lv_scr_act()), 175);
	lv_anim_set_time(&lvgl_TianQi_GongNeng_Data.lv_anim_FengXiang, 200);
	lv_anim_set_var(&lvgl_TianQi_GongNeng_Data.lv_anim_FengXiang, lvgl_TianQi_FengXiang);
	lv_anim_set_path(&lvgl_TianQi_GongNeng_Data.lv_anim_FengXiang, &path);
	lv_anim_start(&lvgl_TianQi_GongNeng_Data.lv_anim_FengXiang);



	lv_anim_init(&lvgl_TianQi_GongNeng_Data.lv_anim_JiangShui);
	lv_anim_set_exec_cb(&lvgl_TianQi_GongNeng_Data.lv_anim_JiangShui, lvgl_TianQi_anim_JiangShui_cb);
	//lv_anim_set_ready_cb(&lvgl_TianQi_GongNeng_Data.lv_anim_JiangShui, arc_lvgl_TianQi_GongNeng_Data.lv_anim_JiangShui_jia);
	lv_anim_set_values(&lvgl_TianQi_GongNeng_Data.lv_anim_JiangShui, lv_obj_get_height(lv_scr_act()), 175);
	lv_anim_set_time(&lvgl_TianQi_GongNeng_Data.lv_anim_JiangShui, 300);
	lv_anim_set_var(&lvgl_TianQi_GongNeng_Data.lv_anim_JiangShui, lvgl_TianQi_JiangShui);
	lv_anim_set_path(&lvgl_TianQi_GongNeng_Data.lv_anim_JiangShui, &path);
	lv_anim_start(&lvgl_TianQi_GongNeng_Data.lv_anim_JiangShui);


	lv_anim_init(&lvgl_TianQi_GongNeng_Data.lv_anim_ShiDu);
	lv_anim_set_exec_cb(&lvgl_TianQi_GongNeng_Data.lv_anim_ShiDu, lvgl_TianQi_anim_ShiDu_cb);
	//lv_anim_set_ready_cb(&lvgl_TianQi_GongNeng_Data.lv_anim_ShiDu, arc_lvgl_TianQi_GongNeng_Data.lv_anim_ShiDu_jia);
	lv_anim_set_values(&lvgl_TianQi_GongNeng_Data.lv_anim_ShiDu, lv_obj_get_height(lv_scr_act()), 175);
	lv_anim_set_time(&lvgl_TianQi_GongNeng_Data.lv_anim_ShiDu, 400);
	lv_anim_set_var(&lvgl_TianQi_GongNeng_Data.lv_anim_ShiDu, lvgl_TianQi_ShiDu);
	lv_anim_set_path(&lvgl_TianQi_GongNeng_Data.lv_anim_ShiDu, &path);
	lv_anim_start(&lvgl_TianQi_GongNeng_Data.lv_anim_ShiDu);






	lv_anim_init(&lvgl_TianQi_GongNeng_Data.lv_anim_JinTian);
	lv_anim_set_exec_cb(&lvgl_TianQi_GongNeng_Data.lv_anim_JinTian, lvgl_TianQi_anim_JinTian_cb);
	//lv_anim_set_ready_cb(&lvgl_TianQi_GongNeng_Data.lv_anim_JinTian, arc_lvgl_TianQi_GongNeng_Data.lv_anim_JinTian_jia);
	lv_anim_set_values(&lvgl_TianQi_GongNeng_Data.lv_anim_JinTian, lv_obj_get_height(lv_scr_act()), lv_obj_get_height(lv_scr_act())-95);
	lv_anim_set_time(&lvgl_TianQi_GongNeng_Data.lv_anim_JinTian, 100);
	lv_anim_set_var(&lvgl_TianQi_GongNeng_Data.lv_anim_JinTian, lvgl_TianQi_JinTian_cont);
	lv_anim_set_path(&lvgl_TianQi_GongNeng_Data.lv_anim_JinTian, &path);
	lv_anim_start(&lvgl_TianQi_GongNeng_Data.lv_anim_JinTian);


	lv_anim_init(&lvgl_TianQi_GongNeng_Data.lv_anim_MingTian);
	lv_anim_set_exec_cb(&lvgl_TianQi_GongNeng_Data.lv_anim_MingTian, lvgl_TianQi_anim_MingTian_cb);
	//lv_anim_set_ready_cb(&lvgl_TianQi_GongNeng_Data.lv_anim_JinTian, arc_lvgl_TianQi_GongNeng_Data.lv_anim_JinTian_jia);
	lv_anim_set_values(&lvgl_TianQi_GongNeng_Data.lv_anim_MingTian, lv_obj_get_height(lv_scr_act()), lv_obj_get_height(lv_scr_act())-95);
	lv_anim_set_time(&lvgl_TianQi_GongNeng_Data.lv_anim_MingTian, 200);
	lv_anim_set_var(&lvgl_TianQi_GongNeng_Data.lv_anim_MingTian, lvgl_TianQi_MingTian_cont);
	lv_anim_set_path(&lvgl_TianQi_GongNeng_Data.lv_anim_MingTian, &path);
	lv_anim_start(&lvgl_TianQi_GongNeng_Data.lv_anim_MingTian);


	lv_anim_init(&lvgl_TianQi_GongNeng_Data.lv_anim_HouTian);
	lv_anim_set_exec_cb(&lvgl_TianQi_GongNeng_Data.lv_anim_HouTian, lvgl_TianQi_anim_HouTian_cb);
	//lv_anim_set_ready_cb(&lvgl_TianQi_GongNeng_Data.lv_anim_JinTian, arc_lvgl_TianQi_GongNeng_Data.lv_anim_JinTian_jia);
	lv_anim_set_values(&lvgl_TianQi_GongNeng_Data.lv_anim_HouTian, lv_obj_get_height(lv_scr_act()), lv_obj_get_height(lv_scr_act())-95);
	lv_anim_set_time(&lvgl_TianQi_GongNeng_Data.lv_anim_HouTian, 300);
	lv_anim_set_var(&lvgl_TianQi_GongNeng_Data.lv_anim_HouTian, lvgl_TianQi_HouTian_cont);
	lv_anim_set_path(&lvgl_TianQi_GongNeng_Data.lv_anim_HouTian, &path);
	lv_anim_start(&lvgl_TianQi_GongNeng_Data.lv_anim_HouTian);

}
//滑出动画
void lvgl_TianQi_DongHua_Chu(void)
{


	lv_anim_init(&lvgl_TianQi_GongNeng_Data.lv_anim_ShiJian);
	lv_anim_set_exec_cb(&lvgl_TianQi_GongNeng_Data.lv_anim_ShiJian, lvgl_TianQi_anim_ShiJian_cb);
	//lv_anim_set_ready_cb(&lvgl_TianQi_GongNeng_Data.lv_anim_ShiJian, arc_lvgl_TianQi_GongNeng_Data.lv_anim_ShiJian_jia);
	lv_anim_set_values(&lvgl_TianQi_GongNeng_Data.lv_anim_ShiJian, 38, -100);
	lv_anim_set_time(&lvgl_TianQi_GongNeng_Data.lv_anim_ShiJian, 100);
	lv_anim_set_var(&lvgl_TianQi_GongNeng_Data.lv_anim_ShiJian, lvgl_TianQi_ShiJian);
	lv_anim_start(&lvgl_TianQi_GongNeng_Data.lv_anim_ShiJian);


	lv_anim_init(&lvgl_TianQi_GongNeng_Data.lv_anim_XingQi);
	lv_anim_set_exec_cb(&lvgl_TianQi_GongNeng_Data.lv_anim_XingQi, lvgl_TianQi_anim_XingQi_cb);
	//lv_anim_set_ready_cb(&lvgl_TianQi_GongNeng_Data.lv_anim_XingQi, arc_lvgl_TianQi_GongNeng_Data.lv_anim_XingQi_jia);
	lv_anim_set_values(&lvgl_TianQi_GongNeng_Data.lv_anim_XingQi, 47, -100);
	lv_anim_set_time(&lvgl_TianQi_GongNeng_Data.lv_anim_XingQi, 200);
	lv_anim_set_var(&lvgl_TianQi_GongNeng_Data.lv_anim_XingQi, lvgl_TianQi_XingQi);
	lv_anim_start(&lvgl_TianQi_GongNeng_Data.lv_anim_XingQi);

	lv_anim_init(&lvgl_TianQi_GongNeng_Data.lv_anim_RiQi);
	lv_anim_set_exec_cb(&lvgl_TianQi_GongNeng_Data.lv_anim_RiQi, lvgl_TianQi_anim_RiQi_cb);
	//lv_anim_set_ready_cb(&lvgl_TianQi_GongNeng_Data.lv_anim_RiQi, arc_lvgl_TianQi_GongNeng_Data.lv_anim_RiQi_jia);
	lv_anim_set_values(&lvgl_TianQi_GongNeng_Data.lv_anim_RiQi, 47, -100);
	lv_anim_set_time(&lvgl_TianQi_GongNeng_Data.lv_anim_RiQi, 300);
	lv_anim_set_var(&lvgl_TianQi_GongNeng_Data.lv_anim_RiQi, lvgl_TianQi_RiQi);
	lv_anim_start(&lvgl_TianQi_GongNeng_Data.lv_anim_RiQi);


	lv_anim_init(&lvgl_TianQi_GongNeng_Data.lv_anim_DangTian);
	lv_anim_set_exec_cb(&lvgl_TianQi_GongNeng_Data.lv_anim_DangTian, lvgl_TianQi_anim_DangTian_cb);
	//lv_anim_set_ready_cb(&lvgl_TianQi_GongNeng_Data.lv_anim_DangTian, arc_lvgl_TianQi_GongNeng_Data.lv_anim_DangTian_jia);
	lv_anim_set_values(&lvgl_TianQi_GongNeng_Data.lv_anim_DangTian, 0, -160);
	lv_anim_set_time(&lvgl_TianQi_GongNeng_Data.lv_anim_DangTian, 100);
	lv_anim_set_var(&lvgl_TianQi_GongNeng_Data.lv_anim_DangTian, lvgl_TianQi_DangTian);
	lv_anim_start(&lvgl_TianQi_GongNeng_Data.lv_anim_DangTian);



	lv_anim_init(&lvgl_TianQi_GongNeng_Data.lv_anim_FengSu);
	lv_anim_set_exec_cb(&lvgl_TianQi_GongNeng_Data.lv_anim_FengSu, lvgl_TianQi_anim_FengSu_cb);
	//lv_anim_set_ready_cb(&lvgl_TianQi_GongNeng_Data.lv_anim_FengSu, arc_lvgl_TianQi_GongNeng_Data.lv_anim_FengSu_jia);
	lv_anim_set_values(&lvgl_TianQi_GongNeng_Data.lv_anim_FengSu, 175, lv_obj_get_height(lv_scr_act()));
	lv_anim_set_time(&lvgl_TianQi_GongNeng_Data.lv_anim_FengSu, 100);
	lv_anim_set_var(&lvgl_TianQi_GongNeng_Data.lv_anim_FengSu, lvgl_TianQi_FengSu);
	lv_anim_start(&lvgl_TianQi_GongNeng_Data.lv_anim_FengSu);


	lv_anim_init(&lvgl_TianQi_GongNeng_Data.lv_anim_FengXiang);
	lv_anim_set_exec_cb(&lvgl_TianQi_GongNeng_Data.lv_anim_FengXiang, lvgl_TianQi_anim_FengXiang_cb);
	//lv_anim_set_ready_cb(&lvgl_TianQi_GongNeng_Data.lv_anim_FengXiang, arc_lvgl_TianQi_GongNeng_Data.lv_anim_FengXiang_jia);
	lv_anim_set_values(&lvgl_TianQi_GongNeng_Data.lv_anim_FengXiang, 175, lv_obj_get_height(lv_scr_act()));
	lv_anim_set_time(&lvgl_TianQi_GongNeng_Data.lv_anim_FengXiang, 200);
	lv_anim_set_var(&lvgl_TianQi_GongNeng_Data.lv_anim_FengXiang, lvgl_TianQi_FengXiang);
	lv_anim_start(&lvgl_TianQi_GongNeng_Data.lv_anim_FengXiang);


	lv_anim_init(&lvgl_TianQi_GongNeng_Data.lv_anim_JiangShui);
	lv_anim_set_exec_cb(&lvgl_TianQi_GongNeng_Data.lv_anim_JiangShui, lvgl_TianQi_anim_JiangShui_cb);
	//lv_anim_set_ready_cb(&lvgl_TianQi_GongNeng_Data.lv_anim_JiangShui, arc_lvgl_TianQi_GongNeng_Data.lv_anim_JiangShui_jia);
	lv_anim_set_values(&lvgl_TianQi_GongNeng_Data.lv_anim_JiangShui, 175 ,lv_obj_get_height(lv_scr_act()));
	lv_anim_set_time(&lvgl_TianQi_GongNeng_Data.lv_anim_JiangShui, 300);
	lv_anim_set_var(&lvgl_TianQi_GongNeng_Data.lv_anim_JiangShui, lvgl_TianQi_JiangShui);
	lv_anim_start(&lvgl_TianQi_GongNeng_Data.lv_anim_JiangShui);


	lv_anim_init(&lvgl_TianQi_GongNeng_Data.lv_anim_ShiDu);
	lv_anim_set_exec_cb(&lvgl_TianQi_GongNeng_Data.lv_anim_ShiDu, lvgl_TianQi_anim_ShiDu_cb);
	//lv_anim_set_ready_cb(&lvgl_TianQi_GongNeng_Data.lv_anim_ShiDu, arc_lvgl_TianQi_GongNeng_Data.lv_anim_ShiDu_jia);
	lv_anim_set_values(&lvgl_TianQi_GongNeng_Data.lv_anim_ShiDu, 175, 400);
	lv_anim_set_time(&lvgl_TianQi_GongNeng_Data.lv_anim_ShiDu, 200);
	lv_anim_set_var(&lvgl_TianQi_GongNeng_Data.lv_anim_ShiDu, lvgl_TianQi_ShiDu);
	lv_anim_start(&lvgl_TianQi_GongNeng_Data.lv_anim_ShiDu);




	lv_anim_init(&lvgl_TianQi_GongNeng_Data.lv_anim_JinTian);
	lv_anim_set_exec_cb(&lvgl_TianQi_GongNeng_Data.lv_anim_JinTian, lvgl_TianQi_anim_JinTian_cb);
	//lv_anim_set_ready_cb(&lvgl_TianQi_GongNeng_Data.lv_anim_JinTian, arc_lvgl_TianQi_GongNeng_Data.lv_anim_JinTian_jia);
	lv_anim_set_values(&lvgl_TianQi_GongNeng_Data.lv_anim_JinTian, 163, lv_obj_get_height(lv_scr_act()));
	lv_anim_set_time(&lvgl_TianQi_GongNeng_Data.lv_anim_JinTian, 100);
	lv_anim_set_var(&lvgl_TianQi_GongNeng_Data.lv_anim_JinTian, lvgl_TianQi_JinTian_cont);
	lv_anim_start(&lvgl_TianQi_GongNeng_Data.lv_anim_JinTian);


	lv_anim_init(&lvgl_TianQi_GongNeng_Data.lv_anim_MingTian);
	lv_anim_set_exec_cb(&lvgl_TianQi_GongNeng_Data.lv_anim_MingTian, lvgl_TianQi_anim_MingTian_cb);
	//lv_anim_set_ready_cb(&lvgl_TianQi_GongNeng_Data.lv_anim_JinTian, arc_lvgl_TianQi_GongNeng_Data.lv_anim_JinTian_jia);
	lv_anim_set_values(&lvgl_TianQi_GongNeng_Data.lv_anim_MingTian, 163, lv_obj_get_height(lv_scr_act()));
	lv_anim_set_time(&lvgl_TianQi_GongNeng_Data.lv_anim_MingTian, 200);
	lv_anim_set_var(&lvgl_TianQi_GongNeng_Data.lv_anim_MingTian, lvgl_TianQi_MingTian_cont);
	lv_anim_start(&lvgl_TianQi_GongNeng_Data.lv_anim_MingTian);


	lv_anim_init(&lvgl_TianQi_GongNeng_Data.lv_anim_HouTian);
	lv_anim_set_exec_cb(&lvgl_TianQi_GongNeng_Data.lv_anim_HouTian, lvgl_TianQi_anim_HouTian_cb);
	//lv_anim_set_ready_cb(&lvgl_TianQi_GongNeng_Data.lv_anim_JinTian, arc_lvgl_TianQi_GongNeng_Data.lv_anim_JinTian_jia);
	lv_anim_set_values(&lvgl_TianQi_GongNeng_Data.lv_anim_HouTian, 163, lv_obj_get_height(lv_scr_act()));
	lv_anim_set_time(&lvgl_TianQi_GongNeng_Data.lv_anim_HouTian, 300);
	lv_anim_set_var(&lvgl_TianQi_GongNeng_Data.lv_anim_HouTian, lvgl_TianQi_HouTian_cont);
	lv_anim_start(&lvgl_TianQi_GongNeng_Data.lv_anim_HouTian);

}

void lvgl_TianQi_TaskCb(lv_task_t *t)
{
	static int time = 0,time1=0;

	if (++time1 > 2)
	{
		time1 = 0;

		lvgl_TianQi_Set_RiQi(
			system_data.RiQi_Data.nian,
			system_data.RiQi_Data.yue,
			system_data.RiQi_Data.ri,
			NULL
		);
		lvgl_TianQi_Set_ShiJian(
			system_data.RiQi_Data.shi,
			system_data.RiQi_Data.fen,
			NULL
		);
	}


#if lvgl_win
	if (system_data.HuoQu_TianQi_Flag == true&&lvgl_shuaxin_get_sta() == lvgl_ShuaXin_Zhong)
	{
		if (++time > 2)
		{
			time = 0;
			lvgl_ShuaXin_close();
		}
	}
#endif
}

//刷新开始
void lvgl_TianQi_shuaxin_kaishi(void)
{
	TianQi_debug("刷新开始\r\n");

	lvgl_TianQi_GongNeng_Data.ShuaXin_Sta = lvgl_ShuaXin_Zhong;

	lvgl_TianQi_DongHua_Chu();

	lvgl_ShuaXin_Start(lvgl_TianQi_main_cont, &system_data.HuoQu_TianQi_Flag, 30);

}


void lvgl_TianQi_ShuaXin_jieshu(void)
{

	TianQi_debug("刷新 结束\r\n");

	lvgl_TianQi_GongNeng_Data.ShuaXin_Sta = lvgl_ShuaXin_JieShu;
	lvgl_TianQi_DongHua_Jin();

}



void lvgl_TianQi_anim_ShiJian_cb(void * arc, lv_anim_value_t v)
{
	lv_obj_set_y(arc, v);
}
void lvgl_TianQi_anim_XingQi_cb(void * arc, lv_anim_value_t v)
{
	lv_obj_set_y(arc, v);
}
void lvgl_TianQi_anim_RiQi_cb(void * arc, lv_anim_value_t v)
{
	lv_obj_set_y(arc, v);
}
void lvgl_TianQi_anim_DangTian_cb(void * arc, lv_anim_value_t v)
{
	lv_obj_set_x(arc, v);
}
void lvgl_TianQi_anim_FengSu_cb(void * arc, lv_anim_value_t v)
{
	lv_obj_set_x(arc, v);
}
void lvgl_TianQi_anim_FengXiang_cb(void * arc, lv_anim_value_t v)
{
	lv_obj_set_x(arc, v);
}
void lvgl_TianQi_anim_JiangShui_cb(void * arc, lv_anim_value_t v)
{
	lv_obj_set_x(arc, v);
}
void lvgl_TianQi_anim_ShiDu_cb(void * arc, lv_anim_value_t v)
{
	lv_obj_set_x(arc, v);
}

void lvgl_TianQi_anim_JinTian_cb(void * arc, lv_anim_value_t v)
{
	lv_obj_set_y(arc, v);
}

void lvgl_TianQi_anim_MingTian_cb(void * arc, lv_anim_value_t v)
{
	lv_obj_set_y(arc, v);
}
void lvgl_TianQi_anim_HouTian_cb(void * arc, lv_anim_value_t v)
{
	lv_obj_set_y(arc, v);
}
