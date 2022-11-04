#include "my_system.h"


_system_data system_data;

static void system_shijian_timercb(void *timer)
{
    static int time=0;

	system_data.RiQi_Data.miao += 1;
	if (system_data.RiQi_Data.miao >= 600)
	{
		system_data.RiQi_Data.miao = 0;

		system_data.RiQi_Data.fen += 1;
		if (system_data.RiQi_Data.fen >= 60)
		{
			system_data.RiQi_Data.fen = 0;
			system_data.RiQi_Data.shi += 1;
			if (system_data.RiQi_Data.shi >= 12)
				system_data.RiQi_Data.shi = 0;
		}
	}

    clock_Data.Miao = system_data.RiQi_Data.miao;
    clock_Data.Fen = system_data.RiQi_Data.fen;
    clock_Data.Shi = system_data.RiQi_Data.shi;

    if(++time>60*10*1)
    {
        time=0;
		if(system_data.WIFI_Sta == wifi_qingqiuduankai || system_data.WIFI_Sta == wifi_lianjiehzong)
		{

		}else
		{
			system_data.HuoQu_ShiJian_Flag=true;//同步一次时间
			xSemaphoreGive(system_data.https_request_Semaphore);//释放信号量
		}

    }
}

int system_init(void)
{
	system_data.Language = JianTiZhongWen;

	system_data.https_request_Semaphore = xSemaphoreCreateCounting(10,0);//动态创建一个计数型信号量

//----时间更新定时器----//
    esp_timer_create_args_t timer_conf =
    {
        .callback = system_shijian_timercb,
        .name     = "system_shijian_timer"
    };
    esp_timer_handle_t g_wifi_connect_timer = NULL;
    esp_timer_create(&timer_conf, &g_wifi_connect_timer);
    esp_timer_start_periodic(g_wifi_connect_timer, 100 * 1000U);
//----时间更新定时器----//

	system_data.RiQi_Data.nian=2021;
	system_data.RiQi_Data.yue=1;
	system_data.RiQi_Data.ri=14;
	system_set_wifi_kaiguan(true);

	system_wifi_data = wifi_list_create("NULL","NULL","NULL");
	// if(system_wifi_data)
	// {
	// 	system_debug("wifi链表创建成功");
	// } else {
	// 	system_debug("wifi链表创建失败");
	// }
	// system_get_wifi_data();
    return 0;
}

int system_save_config(void)
{
	const char *config_fime_path = "/spiffs/system/config.json";
	uint32_t file_size=0;

	cJSON* root = NULL;

	root = cJSON_CreateObject();
	cJSON_AddNumberToObject(root, "wifi switch", system_get_wifi_kaiguan());
	cJSON_AddNumberToObject(root , "language", system_get_Language());

	cJSON* curriculum_arr = cJSON_CreateArray();
	cJSON* curriculum_wifi1 = cJSON_CreateObject();
	cJSON_AddStringToObject(curriculum_wifi1, "name",system_data.wifi_name);
	cJSON_AddStringToObject(curriculum_wifi1, "password",system_data.wifi_password);
	cJSON_AddStringToObject(curriculum_wifi1, "auto connect","true");
	cJSON_AddItemToArray(curriculum_arr, curriculum_wifi1);

	cJSON* curriculum_wifi2 = cJSON_CreateObject();
	cJSON_AddStringToObject(curriculum_wifi2, "name","test");
	cJSON_AddStringToObject(curriculum_wifi2, "password","17625349864");
	cJSON_AddStringToObject(curriculum_wifi2, "auto connect","true");
	cJSON_AddItemToArray(curriculum_arr, curriculum_wifi2);

	cJSON_AddItemToObject(root, "wifi", curriculum_arr);


	char* str = cJSON_PrintUnformatted(root);
	int len = strlen(str);
	system_debug("len:%d %s\n",len, cJSON_Print(root));
	system_debug("保存文件");
	file_size = system_get_file_size(config_fime_path);
    FILE* file = fopen(config_fime_path, "w+");
    if (file == NULL)
	{
        system_debug("打开文件失败");
        return 1;
    }
	system_debug("打开文件成功");
	fwrite(str, 1, len, file);

    fclose(file);

	cJSON_Delete(root);
	return 0;
}

int system_set_Language(int dat)
{
	int Language = system_data.Language;
	system_data.Language = dat;
	system_data.uart_rx_flag=0;

	return Language;
}

int system_get_Language(void)
{
	return system_data.Language;
}

int system_set_wifi_kaiguan(int dat)
{
	int dat1 = system_data.wifi_kaiguan;
	system_data.wifi_kaiguan = dat;
	return dat1;
}

int system_get_wifi_kaiguan(void)
{
	return system_data.wifi_kaiguan;
}

void system_power_off(void)
{
	//bsp_power_off();
}


uint32_t system_get_file_size(char * path)
{
	uint32_t fileSize=0;
	FILE *pread = fopen(path,"rb");
	if (pread==NULL)
	{
		system_debug("文件打开失败");
		return;
	}

	fseek(pread, 0, SEEK_END);
	fileSize = ftell(pread);
	fseek(pread,0,SEEK_SET);
	fclose(pread);
	system_debug("文件:%s 大小:%d",path,fileSize);
	return fileSize;
}
