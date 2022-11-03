#include "user_http_s.h"
#include "main.h"

#define TAG                     "HTTP连接"


int https_get_TianQi(void)
{
  int res = 0;
  char buf[100];

  uint8_t method = GET_REQ;

  if(system_data.IP_ADDR[0]==0)
  {
    lvgl_TianQi_Set_ChengShi("正在获取IP...");
    res = HTTP_Get_IP(system_data.IP_ADDR);
    if(res)
    {
      printf("获取IP失败\r\n");
      lvgl_TianQi_Set_ChengShi("获取IP失败");
      return -1;
    }
  }

  if(system_data.City[0]==0)
  {
    lvgl_TianQi_Set_ChengShi("正在定位城市...");
    res = HTTP_Get_ChengShi(system_data.IP_ADDR,system_data.City);
    if(res)
    {
      printf("定位城市失败\r\n");
      lvgl_TianQi_Set_ChengShi("定位城市失败");
      return -2;
    }
  }

  sprintf(buf,"当前IP:%s 城市:%s",system_data.IP_ADDR,system_data.City);
  //lvgl_TianQi_Set_ChengShi(system_data.City);

  res = HTTP_Get_TianQi(system_data.City,system_data.Weather_Data);
  if(res)
  {
    printf("获取天气失败\r\n");
    lvgl_TianQi_Set_ChengShi("获取天气失败");
    return -3;
  }

  lvgl_TianQi_Set_ChengShi("正在获取空气质量...");
  res = HTTP_Get_KongQi(system_data.City,&system_data.kongqi_Data);
  if(res)
  {
    lvgl_TianQi_Set_ChengShi("获取空气质量失败");
    printf("获取空气质量失败\r\n");
    return -4;
  }
  lvgl_TianQi_Set_ChengShi("正在获取日出日落...");
  res = HTTP_Get_RiLuo(system_data.City,system_data.RiLuo_Data);
  if(res)
  {
    lvgl_TianQi_Set_ChengShi("获取日出日落失败");
    printf("获取日出日落失败\r\n");
    return -5;
  }
  return 0;
}


