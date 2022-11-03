#include "lvgl_ShuaXin.h"
#include "lvgl_Project.h"



_ShuaXin_ChuangKou ShuaXin_ChuangKou;
_lvgl_ShuaXin_GongNeng_Data lvgl_ShuaXin_GongNeng_Data;

lv_obj_t *lvgl_ShuaXin = NULL;
lv_task_t *lvgl_ShuaXin_task = NULL;

void lvgl_ShuaXin_TaskCb(lv_task_t *t);

void lvgl_ShuaXin_create(lv_obj_t * Fu)
{
	// lvgl_ShuaXin_GongNeng_Data.fu = Fu;

	// ShuaXin_debug("创建刷新窗口\r\n");
	// lv_obj_set_drag(lvgl_ShuaXin_GongNeng_Data.fu, false);//启用/禁用对象可拖动
	// if (lvgl_ShuaXin == NULL)
	// {
	// 	lvgl_ShuaXin = lv_img_create(lv_scr_act(), NULL);
	// 	lv_obj_set_pos(lvgl_ShuaXin, 95, 0);
	// 	lv_img_set_src(lvgl_ShuaXin, bmp_ShuaXin_buf[0]);

	// 	lv_obj_move_background(lvgl_ShuaXin);//窗口放在后面
	// }

	// ShuaXin_anim_DongHua_Jin();

}
void lvgl_ShuaXin_close(void)
{
	if (lvgl_ShuaXin == NULL)
		return;

	ShuaXin_anim_DongHua_Chu();
}

void lvgl_ShuaXin_Start(lv_obj_t * Fu,int * dat,int time)
{
	lvgl_ShuaXin_GongNeng_Data.usr_flag=dat;
	lvgl_ShuaXin_GongNeng_Data.fu = Fu;

	ShuaXin_debug("创建刷新窗口\r\n");
	lv_obj_set_drag(lvgl_ShuaXin_GongNeng_Data.fu, false);//启用/禁用对象可拖动
	if (lvgl_ShuaXin == NULL)
	{
		lvgl_ShuaXin = lv_img_create(lv_scr_act(), NULL);
		lv_obj_set_pos(lvgl_ShuaXin, 95, 0);
		lv_img_set_src(lvgl_ShuaXin, bmp_ShuaXin_buf[0]);
		lv_obj_move_background(lvgl_ShuaXin);//窗口放在后面
	}
	ShuaXin_anim_DongHua_Jin();

	if (lvgl_ShuaXin_task == NULL)
	{
		ShuaXin_debug("开始执行刷新动画\r\n");
		lvgl_ShuaXin_task = lv_task_create(lvgl_ShuaXin_TaskCb, time, LV_TASK_PRIO_LOWEST, NULL);
		lvgl_ShuaXin_GongNeng_Data.image_cnt = 0;
	}

	lvgl_ShuaXin_GongNeng_Data.zuhangtai_flag=lvgl_ShuaXin_Zhong;
	*lvgl_ShuaXin_GongNeng_Data.usr_flag=true;

	xSemaphoreGive(system_data.https_request_Semaphore);//释放信号量

}
void lvgl_ShuaXin_Stop(void)
{
	if (lvgl_ShuaXin_task != NULL)
	{
		lv_obj_set_hidden(lvgl_ShuaXin_task,true);
		lvgl_ShuaXin_task = NULL;

	}

}
void lvgl_ShuaXin_TaskCb(lv_task_t *t)
{
	static int cnt=0;
	if (++lvgl_ShuaXin_GongNeng_Data.image_cnt > 15)
	{
		lvgl_ShuaXin_GongNeng_Data.image_cnt = 0;
	}
	lv_img_set_src(lvgl_ShuaXin, bmp_ShuaXin_buf[lvgl_ShuaXin_GongNeng_Data.image_cnt]);
}

void ShuaXin_anim_Jin_ready_cb(lv_anim_t * anim)
{

	lv_anim_del(&ShuaXin_ChuangKou.lv_XiaLa_anim,NULL);
}

void ShuaXin_anim_Jin_cb(void * arc, lv_anim_value_t v)
{
	lv_obj_set_y(arc, v);

}


//滑入动画
void ShuaXin_anim_DongHua_Jin(void)
{

	ShuaXin_debug("执行刷新进入动效\r\n");

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

	lv_anim_init(&ShuaXin_ChuangKou.lv_XiaLa_anim);
	lv_anim_set_ready_cb(&ShuaXin_ChuangKou.lv_XiaLa_anim, ShuaXin_anim_Jin_ready_cb);
	lv_anim_set_exec_cb(&ShuaXin_ChuangKou.lv_XiaLa_anim, ShuaXin_anim_Jin_cb);
	lv_anim_set_values(&ShuaXin_ChuangKou.lv_XiaLa_anim, 0, bmp_ShuaXin_buf[0]->header.h);
	lv_anim_set_time(&ShuaXin_ChuangKou.lv_XiaLa_anim, 200);
	lv_anim_set_var(&ShuaXin_ChuangKou.lv_XiaLa_anim, lvgl_ShuaXin_GongNeng_Data.fu);

	lv_anim_set_path(&ShuaXin_ChuangKou.lv_XiaLa_anim, &path);
	lv_anim_start(&ShuaXin_ChuangKou.lv_XiaLa_anim);

}



void ShuaXin_anim_Chu_ready_cb(lv_anim_t * anim)
{

	lv_anim_del(&ShuaXin_ChuangKou.lv_ShangLa_anim, NULL);

	if (lvgl_ShuaXin != NULL)
	{
		lv_obj_del(lvgl_ShuaXin);
		lvgl_ShuaXin = NULL;
	}
	if (lvgl_ShuaXin_task != NULL)
	{
		lv_task_del(lvgl_ShuaXin_task);
		lvgl_ShuaXin_task = NULL;
	}
	lv_obj_set_y(lvgl_ShuaXin_GongNeng_Data.fu, 0);
	lv_obj_set_drag(lvgl_ShuaXin_GongNeng_Data.fu, true);//启用/禁用对象可拖动

	lvgl_ShuaXin_GongNeng_Data.zuhangtai_flag=lvgl_ShuaXin_JieShu;
	*lvgl_ShuaXin_GongNeng_Data.usr_flag=false;
	lv_event_send(lvgl_ShuaXin_GongNeng_Data.fu, lvgl_shuaxin_jieshu_event,NULL);

	ShuaXin_debug("已关闭刷新窗口\r\n");

	lvgl_ShuaXin=NULL;
}

void ShuaXin_anim_Chu_cb(void * arc, lv_anim_value_t v)
{
	lv_obj_set_y(arc, v);

}


//滑出动画
void ShuaXin_anim_DongHua_Chu(void)
{

	ShuaXin_debug("执行刷新退出动效\r\n");

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

	lv_anim_init(&ShuaXin_ChuangKou.lv_ShangLa_anim);
	lv_anim_set_ready_cb(&ShuaXin_ChuangKou.lv_ShangLa_anim, ShuaXin_anim_Chu_ready_cb);
	lv_anim_set_exec_cb(&ShuaXin_ChuangKou.lv_ShangLa_anim, ShuaXin_anim_Chu_cb);
	lv_anim_set_values(&ShuaXin_ChuangKou.lv_ShangLa_anim, bmp_ShuaXin_buf[0]->header.h,0 );
	lv_anim_set_time(&ShuaXin_ChuangKou.lv_ShangLa_anim, 200);
	lv_anim_set_var(&ShuaXin_ChuangKou.lv_ShangLa_anim, lvgl_ShuaXin_GongNeng_Data.fu);

	lv_anim_set_path(&ShuaXin_ChuangKou.lv_ShangLa_anim, &path);
	lv_anim_start(&ShuaXin_ChuangKou.lv_ShangLa_anim);

}



int lvgl_shuaxin_get_sta(void)
{
	return lvgl_ShuaXin_GongNeng_Data.zuhangtai_flag;
}

