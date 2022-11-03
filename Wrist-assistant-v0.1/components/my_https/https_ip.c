#include "https_ip.h"
#include "main.h"
#include "https.h"


int https_get_ip(void)
{
  int res = 0;
  char buf[50];

  res = HTTP_Get_IP(system_data.IP_ADDR);
  if(res)
  {
    ip_debug("获取失败\r\n");
    return -1;
  }
  return 0;
}

int HTTP_Get_IP(char * read_buf)
{
  int return_dat=0;
  uint8_t res=0;
  char *str=NULL;
  char buf[30];
  //char buf1[30];
  int i=0;
  char *http_recv_buff=NULL;

  if(read_buf==NULL)
    return 1;


  http_recv_buff = (char*)os_malloc(1024*3);

  ip_debug("开始获取IP地址\r\n");

  res = HTTP_Read_Data(HTTPS_HuoQuIP,NULL,http_recv_buff,GET_REQ);


  if(res==0)
  {
    memset(buf,0,sizeof(buf));
    str=strstr((char *)http_recv_buff, ".");
    if(str!=NULL)
    {
      // for(i=0;i<strlen(buf1);i++)
      // {
      //   printf("buf1[%d]:0x%x\r\n",i,buf1[i]);
      // }

      for(i=0;i<strlen(http_recv_buff);i++)
      {
        if(http_recv_buff[+i]==0x0a)
          break;
        else
          buf[i] = http_recv_buff[i];
      }
       ip_debug("获取到的IP地址:%s 长度:%d\r\n",buf,strlen(buf));
      if(read_buf!=NULL)
      {
          sprintf(read_buf,"%s",buf);
      }
    }else
    {
      ip_debug("解析IP失败\r\n");
      return_dat= -1;
    }
  }else
  {
    ip_debug("获取IP地址失败:%d\r\n", res);
    return_dat= -2;
  }
  os_free(http_recv_buff);
  return return_dat;
}
