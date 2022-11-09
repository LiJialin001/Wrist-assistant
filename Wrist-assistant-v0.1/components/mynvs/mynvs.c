#include "mynvs.h"
#include "main.h"
#include "nvs_flash.h"
#include "nvs.h"

#if 1
nvs_handle my_handle;

#define nvs_name "wrist_assistant"

#define nvs_wifi_name       "wifi_name"
#define nvs_wifi_password   "wifi_password"

esp_err_t nvs_init(void)
{
   // ESP_ERROR_CHECK(nvs_flash_erase());
    esp_err_t err = nvs_flash_init();
    if (err == ESP_ERR_NVS_NO_FREE_PAGES || err == ESP_ERR_NVS_NEW_VERSION_FOUND)
    {
        //擦除
        ESP_ERROR_CHECK(nvs_flash_erase());
        err = nvs_flash_init();
    }else
    {
        my_nvs_debug("my_nvs初始化成功\r\n");

    }

/*
    xTaskCreate(nvs_test_task,"nvs_test_task",1024*2,NULL,20,NULL);
*/
 	return 0;
}

void nvs_test_task(void *pvParameter)
{
	while (1)
    {
        vTaskDelay(1000 / portTICK_PERIOD_MS);
 	}
	vTaskDelete(NULL);
}

esp_err_t nvs_set_wifi(char *wifi_name,char *wifi_password)
{
    nvs_handle handle;

    //  wifi_config_t wifi_config_to_store = {
    //     .sta = {
    //         .ssid = "store_ssid:hello_kitty",
    //         .password = "store_password:1234567890",
    //     },
    // };
    // ESP_ERROR_CHECK( nvs_set_blob( handle, DATA3, &wifi_config_to_store, sizeof(wifi_config_to_store)) );


    ESP_ERROR_CHECK( nvs_open( nvs_name, NVS_READWRITE, &handle) );
    ESP_ERROR_CHECK( nvs_set_str( handle, nvs_wifi_name, wifi_name) );
    ESP_ERROR_CHECK( nvs_set_str( handle, nvs_wifi_password, wifi_password) );

    ESP_ERROR_CHECK( nvs_commit(handle) );
    nvs_close(handle);
    return ESP_OK;
}


esp_err_t nvs_get_wifi(char *wifi_name,char *wifi_password)
{
    nvs_handle handle;

    uint32_t str_length = 32;
    uint32_t str_length2 = 64;
    char str_data[32] = {0};
    char str_data2[64] = {0};

    my_nvs_debug("开始读取wifi\r\n");
    // wifi_config_t wifi_config_stored;
    // memset(&wifi_config_stored, 0x0, sizeof(wifi_config_stored));
    // uint32_t len = sizeof(wifi_config_stored);
    // ESP_ERROR_CHECK ( nvs_get_blob(handle, nvs_wifi_password, &wifi_config_stored, &len) );

    esp_err_t err=0;

    err = nvs_open(nvs_name, NVS_READWRITE, &handle);
    if(err!=ESP_OK)
    {
        ESP_ERROR_CHECK(err);
        my_nvs_debug("打开错误\r\n");
        goto nvs_close;
    }
    err = nvs_get_str(handle, nvs_wifi_name, str_data, &str_length);
    if(err!=ESP_OK)
    {
        ESP_ERROR_CHECK(err);
        my_nvs_debug("获取错误\r\n");
        goto nvs_close;
    }
    err = nvs_get_str(handle, nvs_wifi_password, str_data2, &str_length2);
    if(err!=ESP_OK)
    {
        ESP_ERROR_CHECK(err);
        my_nvs_debug("获取错误\r\n");
        goto nvs_close;
    }

    my_nvs_debug("[nvs_wifi_name]:%s len:%u\r\n", str_data, str_length);
    my_nvs_debug("[nvs_wifi_password]:%s len:%u\r\n", str_data2,str_length2);
    sprintf(wifi_name,"%s",str_data);
    sprintf(wifi_password,"%s",str_data2);

nvs_close:
    nvs_close(handle);
    return err;
}
#endif
