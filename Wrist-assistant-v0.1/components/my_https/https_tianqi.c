#include "https_tianqi.h"
#include "main.h"
#include "https.h"


int https_get_tianqi(void)
{
  int res = 0;
  char buf[50];

  res = HTTP_Get_TianQi(system_data.City,system_data.Weather_Data);
  if(res)
  {
    tianqii_debug("获取失败\r\n");
    return -1;
  }
  return 0;
}

int HTTP_Get_TianQi(char * city_name_buf,_Weather_Data  read_buf[3])
{

  int res=0;
  int i=0;
  int return_dat=0;
  if(read_buf==NULL)
   return 1;

 char *http_recv_buff = (char*)heap_caps_malloc(1024*5, MALLOC_CAP_SPIRAM);
 char *buf = (char*)heap_caps_malloc(1024, MALLOC_CAP_SPIRAM);


  tianqii_debug("开始获取天气\r\n");
  sprintf(buf,"%s%s",HTTPS_XinZHi,city_name_buf);
  res = HTTP_Read_Data(buf,NULL,http_recv_buff,GET_REQ);
  if(res==0)
  {

    char *str=strstr((char *)http_recv_buff, "\"}]}");
    if(str==NULL)
    {
      tianqii_debug("天气数据错误\r\n");
      return_dat= -1;
    }else
    {
      tianqii_debug("开始解析天气数据\r\n");
      char *json_data = http_recv_buff;
      cJSON *json_A = cJSON_Parse(os_strchr(json_data, '{'));//获取整个大的句柄
      cJSON *results = cJSON_GetObjectItem(json_A,"results");
      cJSON *location = cJSON_GetObjectItem(cJSON_GetArrayItem(results,0),"location");
      cJSON *daily = cJSON_GetObjectItem(cJSON_GetArrayItem(results,0),"daily");
      cJSON *date = cJSON_GetObjectItem(cJSON_GetArrayItem(daily,0),"date");

      tianqii_debug("city: %s\n%s\n%s\n%s\n",
                cJSON_Print(cJSON_GetObjectItem(location, "name")),
                cJSON_Print(cJSON_GetArrayItem(daily, 0)),
                cJSON_Print(cJSON_GetArrayItem(daily, 1)),
                cJSON_Print(cJSON_GetArrayItem(daily, 2))

                );

      cJSON *item;
      cJSON *data;
      for(i =0;i<3;i++)
      {
        tianqii_debug("天气:%d\r\n",i);
        item = cJSON_GetArrayItem(daily, i);

        data = cJSON_GetObjectItem(item, "date");
        tianqii_debug("日期:%s\r\n",data->valuestring);
        sprintf(read_buf[i].date,"%s",data->valuestring);

      data = cJSON_GetObjectItem(item, "text_day");
        tianqii_debug("白天天气现象:%s\r\n",data->valuestring);
        sprintf(read_buf[i].text_day,"%s",data->valuestring);


      data = cJSON_GetObjectItem(item, "code_day");
        tianqii_debug("白天天气现象代码:%s\r\n",data->valuestring);
        sprintf(read_buf[i].code_day,"%s",data->valuestring);

        data = cJSON_GetObjectItem(item, "text_night");
        tianqii_debug("晚间天气现象:%s\r\n",data->valuestring);
        sprintf(read_buf[i].text_night,"%s",data->valuestring);

      data = cJSON_GetObjectItem(item, "code_night");
        tianqii_debug("晚间天气现象代码:%s\r\n",data->valuestring);
        sprintf(read_buf[i].code_night,"%s",data->valuestring);

        data = cJSON_GetObjectItem(item, "high");
        tianqii_debug("当天最高温度:%s\r\n",data->valuestring);
        sprintf(read_buf[i].high,"%s",data->valuestring);

        data = cJSON_GetObjectItem(item, "low");
        tianqii_debug("当天最低温度:%s\r\n",data->valuestring);
        sprintf(read_buf[i].low,"%s",data->valuestring);

          data = cJSON_GetObjectItem(item, "precip");
        tianqii_debug("降水概率:%s\r\n",data->valuestring);
        sprintf(read_buf[i].precip,"%s",data->valuestring);

        data = cJSON_GetObjectItem(item, "wind_direction");
        tianqii_debug("风向:%s\r\n",data->valuestring);
        sprintf(read_buf[i].wind_direction,"%s",data->valuestring);

        data = cJSON_GetObjectItem(item, "wind_direction_degree");
        tianqii_debug("风向角度:%s\r\n",data->valuestring);
        sprintf(read_buf[i].wind_direction_degree,"%s",data->valuestring);

        data = cJSON_GetObjectItem(item, "wind_speed");
        printf("风速:%s\r\n",data->valuestring);
        sprintf(read_buf[i].wind_speed,"%s",data->valuestring);

        data = cJSON_GetObjectItem(item, "wind_scale");
        tianqii_debug("风力等级:%s\r\n",data->valuestring);
        sprintf(read_buf[i].wind_scale,"%s",data->valuestring);

        data = cJSON_GetObjectItem(item, "rainfall");
        tianqii_debug("降水量:%s\r\n",data->valuestring);
        sprintf(read_buf[i].rainfall,"%s",data->valuestring);

        data = cJSON_GetObjectItem(item, "humidity");
        tianqii_debug("相对湿度:%s\r\n",data->valuestring);
        sprintf(read_buf[i].humidity,"%s",data->valuestring);

      }

      // printf("日期:%s\r\n",cJSON_Print(cJSON_GetObjectItem(cJSON_GetArrayItem(daily, 0), "date")));
      // printf("日期:%s\r\n",cJSON_Print(cJSON_GetObjectItem(cJSON_GetArrayItem(daily, 1), "date")));
      // printf("日期:%s\r\n",cJSON_Print(cJSON_GetObjectItem(cJSON_GetArrayItem(daily, 2), "date")));
      // printf("日期:%s\r\n",cJSON_Print(cJSON_GetObjectItem(cJSON_GetArrayItem(daily, 3), "date")));

      cJSON_Delete(json_A);
    }
  }else
  {
    tianqii_debug("获取天气失败:%d\r\n", res);
    return_dat= -3;
  }
  heap_caps_free(http_recv_buff);
  heap_caps_free(buf);
  return return_dat;
}
