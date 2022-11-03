#include "https_riluo.h"
#include "main.h"
#include "https.h"


int https_get_riluo(void)
{
  int res = 0;
  char buf[50];

  res = HTTP_Get_RiLuo(system_data.City,system_data.RiLuo_Data);
  if(res)
  {
    riluo_debug("获取失败\r\n");
    return -1;
  }
  return 0;
}

int HTTP_Get_RiLuo(char * city_name_buf,_RiLuo_Data  read_buf[3])
{

  int res=0;
  int i=0;
  int return_dat=0;
  char *http_recv_buff=NULL;
  char buf[256];
  if(read_buf==NULL)
   return 1;

  http_recv_buff = (char*)os_malloc(1024*2);


  riluo_debug("开始获取日出日落\r\n");
  sprintf(buf,"%s%s",HTTPS_RiLuo,city_name_buf);
  res = HTTP_Read_Data(buf,NULL,http_recv_buff,GET_REQ);
  if(res==0)
  {

    char *str=strstr((char *)http_recv_buff, "\"}]}");
    if(str==NULL)
    {
      riluo_debug("日出日落数据错误\r\n");
      return_dat= -1;
    }else
    {
      riluo_debug("开始解析日出日落数据\r\n");
      char *json_data = http_recv_buff;
      cJSON *json_A = cJSON_Parse(os_strchr(json_data, '{'));//获取整个大的句柄
      cJSON *results = cJSON_GetObjectItem(json_A,"results");
      cJSON *location = cJSON_GetObjectItem(cJSON_GetArrayItem(results,0),"location");
      cJSON *sun = cJSON_GetObjectItem(cJSON_GetArrayItem(results,0),"sun");



      riluo_debug("city: %s\n%s\n%s\n%s\n",
                cJSON_Print(cJSON_GetObjectItem(location, "name")),
                cJSON_Print(cJSON_GetArrayItem(sun, 0)),
                cJSON_Print(cJSON_GetArrayItem(sun, 1)),
                cJSON_Print(cJSON_GetArrayItem(sun, 2))

                );

      cJSON *item;
      cJSON *data;
      for(i =0;i<3;i++)
      {
        riluo_debug("日出日落:%d\r\n",i);
        item = cJSON_GetArrayItem(sun, i);

        data = cJSON_GetObjectItem(item, "date");
        if(data->valueint!=NULL)
        {
          riluo_debug("日期:%s\r\n",data->valuestring);
          sprintf(read_buf[i].date,"%s",data->valuestring);
        }else
        {
          riluo_debug("日期:%s\r\n","NULL");
          sprintf(read_buf[i].date,"%s","NULL");
        }

        data = cJSON_GetObjectItem(item, "sunrise");
        if(data->valuestring!=NULL)
        {
          riluo_debug("日出:%s\r\n",data->valuestring);
          sprintf(read_buf[i].sunrise,"%s",data->valuestring);
        }else
        {
          riluo_debug("日出:%s\r\n","NULL");
          sprintf(read_buf[i].sunrise,"%s","NULL");
        }

        data = cJSON_GetObjectItem(item, "sunset");
        if(data->valuestring!=NULL)
        {
          riluo_debug("日落:%s\r\n",data->valuestring);
          sprintf(read_buf[i].sunset,"%s",data->valuestring);
        }else
        {
          riluo_debug("日落:%s\r\n","NULL");
          sprintf(read_buf[i].sunset,"%s","NULL");
        }
      }

      cJSON_Delete(json_A);
    }
  }else
  {
    riluo_debug("获取日出日落失败:%d\r\n", res);
    return_dat= -3;
  }
  os_free(http_recv_buff);
  return return_dat;
}
