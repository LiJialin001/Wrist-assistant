#include "https_kongqi.h"
#include "main.h"
#include "https.h"


int https_get_kongqi(void)
{
  int res = 0;
  char buf[50];

  res = HTTP_Get_KongQi(system_data.IP_ADDR,&system_data.kongqi_Data);
  if(res)
  {
    kongqi_debug("获取失败\r\n");
    return -1;
  }
  return 0;
}

int HTTP_Get_KongQi(char * city_name_buf,_kongqi_Data  *read_buf)
{
 int res=0;
  int i=0;
  int return_dat=0;
  char *http_recv_buff=NULL;
  char buf[256];
  if(read_buf==NULL)
   return 1;

  http_recv_buff = (char*)os_malloc(1024*2);


  kongqi_debug("开始获取空气质量\r\n");
  sprintf(buf,"%s%s",HTTPS_KongQi,city_name_buf);
  res = HTTP_Read_Data(buf,NULL,http_recv_buff,GET_REQ);
  if(res==0)
  {

    char *str=strstr((char *)http_recv_buff, "\"}]}");
    if(str==NULL||strstr((char *)http_recv_buff, "The API key is invalid")!=NULL)
    {
      kongqi_debug("空气质量数据错误\r\n");
      return_dat= -1;
    }else
    {

      kongqi_debug("开始解析空气质量数据\r\n");
      char *json_data = http_recv_buff;
      cJSON *json_A = cJSON_Parse(os_strchr(json_data, '{'));//获取整个大的句柄
      cJSON *results = cJSON_GetObjectItem(json_A,"results");
      cJSON *location = cJSON_GetObjectItem(cJSON_GetArrayItem(results,0),"location");
      cJSON *air = cJSON_GetObjectItem(cJSON_GetArrayItem(results,0),"air");
      cJSON *city = cJSON_GetObjectItem(air,"city");


      kongqi_debug("city: %s\n%s\n",
                cJSON_Print(cJSON_GetObjectItem(location, "name")),
                cJSON_Print(city)
                );

      cJSON *data;
      data = cJSON_GetObjectItem(city, "aqi");
      kongqi_debug("空气质量指数:%s\r\n",data->valuestring);
      sprintf(read_buf->aqi,"%s",data->valuestring);

      data = cJSON_GetObjectItem(city, "pm25");
      kongqi_debug("PM2.5颗粒物:%s\r\n",data->valuestring);
      sprintf(read_buf->pm25,"%s",data->valuestring);

      data = cJSON_GetObjectItem(city, "pm10");
      kongqi_debug("PM10颗粒物:%s\r\n",data->valuestring);
      sprintf(read_buf->pm10,"%s",data->valuestring);

      data = cJSON_GetObjectItem(city, "so2");
      kongqi_debug("二氧化硫1小时平均值:%s\r\n",data->valuestring);
      sprintf(read_buf->so2,"%s",data->valuestring);

      data = cJSON_GetObjectItem(city, "no2");
      kongqi_debug("二氧化氮1小时平均值:%s\r\n",data->valuestring);
      sprintf(read_buf->no2,"%s",data->valuestring);

      data = cJSON_GetObjectItem(city, "co");
      kongqi_debug("一氧化碳1小时平均值:%s\r\n",data->valuestring);
      sprintf(read_buf->co,"%s",data->valuestring);

      data = cJSON_GetObjectItem(city, "o3");
      kongqi_debug("臭氧1小时平均值:%s\r\n",data->valuestring);
      sprintf(read_buf->o3,"%s",data->valuestring);

      data = cJSON_GetObjectItem(city, "primary_pollutant");
      if(data->valuestring!=NULL)
      {
        kongqi_debug("首要污染物:%s\r\n",data->valuestring);
        sprintf(read_buf->primary_pollutant,"%s",data->valuestring);
      }else
      {
        kongqi_debug("首要污染物:%s\r\n","NULL");
        sprintf(read_buf->primary_pollutant,"%s","NULL");
      }

      data = cJSON_GetObjectItem(city, "quality");
      kongqi_debug("空气质量类别:%s\r\n",data->valuestring);
      sprintf(read_buf->quality,"%s",data->valuestring);

      data = cJSON_GetObjectItem(city, "last_update");
      kongqi_debug("数据发布时间:%s\r\n",data->valuestring);
      sprintf(read_buf->last_update,"%s",data->valuestring);

      cJSON_Delete(json_A);
    }
  }else
  {
    kongqi_debug("获取天气失败:%d\r\n", res);
    return_dat= -3;
  }


  os_free(http_recv_buff);
  return return_dat;
}
