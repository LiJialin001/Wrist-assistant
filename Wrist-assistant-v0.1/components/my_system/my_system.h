#ifndef __my_system_H__
#define __my_system_H__


#include "main.h"
#include "lvgl_project.h"
#include "system_config_data.h"

#include "https_shijian.h"
#include "https_tianqi.h"
#include "https_riluo.h"
#include "https_kongqi.h"
#include "https_chengshi.h"
#include "https_ip.h"
#include "https.h"
#include "user_http_s.h"

#if 1
#define system_debug(format, ...) my_debug("[system]- ",format,##__VA_ARGS__);
#else
#define system_debug(format, ...) ;
#endif

#define WIFI_SCAN_LIST_SIZE 40





typedef struct
{
    int sht20_sta;
    int ft5206_sta;
    int spiffs_sta;
    int nvs_sta;
    int mpu6050_sta;

	int Language;


    char IP_ADDR[30];
    char City[30];

    uint8_t MAC[6];
    char ip[30];
    char ziwangyanma[30];
    char wangguan[30];
    char wifi_name[32];
    char wifi_password[64];
    int Temp;
    int Humi;
    int HuoQu_TianQi_Flag;
    int HuoQu_ShiJian_Flag;
    int WIFI_Sta;//WIFI连接状态
    bool set_connect_wifi_flag;

    int web_huoqu_tianqi_flag;
    int wifi_scan_flag;

    int wifi_scan_list_cnt;
    wifi_ap_record_t wifi_ap_info[WIFI_SCAN_LIST_SIZE];	// AP信息结构体大小

    int wifi_kaiguan;

    // lv_indev_data_t mouse;
    // lv_indev_data_t huadong_mouse_0;
    // lv_indev_data_t huadong_mouse_1;


    int uart_rx_home;
    int uart_rx_flag;

    //wifi链接成功事件
    EventGroupHandle_t wifi_event_group;
    EventGroupHandle_t Wav_event_group;
    EventGroupHandle_t TianQi_event_group;

    xSemaphoreHandle  https_request_Semaphore;

    _Weather_Data   Weather_Data[3];
    _kongqi_Data    kongqi_Data;
    _RiLuo_Data     RiLuo_Data[3];
    _RiQi_Data      RiQi_Data;


}_system_data;

extern _system_data system_data;

#define SYSTEM_LANGUAGE_NUM 4

enum Language_Num {
	JianTiZhongWen = 0,
	FanTiZhongWen,
	YingWen,
	QiTa,
};


//extern wavctrl WaveCtrlData;
//extern FILE* Wave_File;


int system_init(void);
int system_set_Language(int dat);
int system_get_Language(void);

int system_set_wifi_kaiguan(int dat);
int system_get_wifi_kaiguan(void);
int system_set_wifi_kaiguan(int dat);
int system_get_wifi_kaiguan(void);
void system_power_off(void);
uint8_t system_get_wifi_data(void);
uint32_t system_get_file_size(char * path);
int system_save_config(void);
#endif
