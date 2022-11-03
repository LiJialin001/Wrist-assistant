#include "https_chengshi.h"
#include "main.h"
#include "https.h"


int https_get_chengshi(void)
{
  int res = 0;
  char buf[50];

  res = HTTP_Get_ChengShi(system_data.IP_ADDR,system_data.City);
  if(res)
  {
    chengshi_debug("获取失败\r\n");
    return -1;
  }
  return 0;
}

int HTTP_Get_ChengShi(char * ip_buf,char * read_buf)
{
  int res=0;
  int return_dat=0;
  char *http_recv_buff=NULL;
  char buf[128];
  if(read_buf==NULL)
    return 1;

  http_recv_buff = (char*)os_malloc(1024*2);

  chengshi_debug("开始获取城市\r\n");
  sprintf(buf,"%s%s",HTTPS_DingWei,ip_buf);
  res = HTTP_Read_Data(buf,NULL,http_recv_buff,GET_REQ);
  if(res==0)
  {
      char *json_data = http_recv_buff;
      cJSON *json_A = cJSON_Parse(os_strchr(json_data, '{'));//获取整个大的句柄
      cJSON *json_item = cJSON_GetObjectItem(json_A,"status"); //获取这个对象成员
      chengshi_debug("status:%s\r\n",json_item->valuestring);

      if(strstr(json_item->valuestring,"1")==NULL)
      {
        chengshi_debug("定位失败\r\n");
        return_dat=-1;
      }else
      {
        json_item = cJSON_GetObjectItem(json_A,"city"); //获取这个对象成员
        sprintf(read_buf,"%s",json_item->valuestring);
        chengshi_debug("city:%s\r\n",read_buf);

      }
      cJSON_Delete(json_A);
  }else
  {
    chengshi_debug("获取城市失败:%d\r\n", res);
    return_dat=-2;
  }

  os_free(http_recv_buff);
  return return_dat;
}
