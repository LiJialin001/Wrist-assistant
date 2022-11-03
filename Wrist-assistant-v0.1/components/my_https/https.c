#include "mbedtls/platform.h"
//#include "mbedtls/net.h"
#include "mbedtls/debug.h"
#include "mbedtls/ssl.h"
#include "mbedtls/entropy.h"
#include "mbedtls/ctr_drbg.h"
#include "mbedtls/error.h"
//#include "mbedtls/certs.h"
#include "mbedtls/net_sockets.h"

#include "lwip/err.h"
#include "lwip/sockets.h"
#include "lwip/sys.h"
#include "lwip/netdb.h"
#include "lwip/dns.h"


#include "user_http_s.h"
#include "os.h"
#include <freertos/FreeRTOS.h>
#include "freertos/task.h"
#include "freertos/queue.h"
#include "cJSON.h"
#include "https.h"

#include "main.h"

/**
 * 从给定的网址中获取主机域名和域名后面的内容分别存放至HOST和Filename
 * @param[in]   URL     :需要解析的域名地址
 * @param[out]  host    :解析获取域名的主机地址
 * @param[out]  filename:解析获取从域名主机的内容地址
 * @retval
 *              0: 解析成功
 *             -1: URL为空
 *             -2: host为空
 *             -3: filename为空
 *             -4: 传进来的网址中没有https://和http://
 * @par         示例:
 *              1.如果URL是https://www.sojson.com/open/api/weather/json.shtml?city=深圳
 *              2.host是"www.sojson.com/"
 *              3.filename是"open/api/weather/json.shtml?city=深圳"
 *
 * @par         修改日志
 *               Ver0.0.1:
                     Helon_Chan, 2018/06/27, 初始化版本\n
 */
esp_err_t http_url_parse(char *URL, char *host, char *filename)
{
  char *PA;
  char *PB;
  /* 分别判断传来的实参是不是为空 */
  if (URL == NULL)
  {
    return -1;
  }
  else if (host == NULL)
  {
    return -2;
  }
  else if (filename == NULL)
  {
    return -3;
  }

  /* 初始化传进来的用于存放host和filename的内存空间 */
  //os_memset(host, 0, sizeof(host)/sizeof(char));
  //os_memset(filename, 0, sizeof(filename)/sizeof(char));

  PA = URL;
  /* 判断传进来的网址是否带有"http://以及https://"内容 */
  if (!os_strncmp(PA, "http://", os_strlen("http://")))
  {
    PA = URL + os_strlen("http://");
  }
  else if (!os_strncmp(PA, "https://", os_strlen("https://")))
  {
    PA = URL + os_strlen("https://");
  }
  else
  {
    return -4;
  }
  /* 获取主页地址后面内容的首地址 */
  PB = os_strchr(PA, '/');
  if (PB)
  {
    /* 获取传进来网址的主页以及主页后面跟着的地址内容 */
    os_memcpy(host, PA, os_strlen(PA) - os_strlen(PB));
    if (PB + 1)
    {
      os_memcpy(filename, PB + 1, os_strlen(PB - 1));
      filename[os_strlen(PB) - 1] = 0;
    }
    host[os_strlen(PA) - os_strlen(PB)] = 0;
  }
  /* 如果传进来的网址是主页则直接获取主页地址内容 */
  else
  {
    os_memcpy(host, PA, os_strlen(PA));
    host[os_strlen(PA)] = 0;
  }
  return ESP_OK;
}


static int recv_timeout_cb( void *ctx, unsigned char *buf, size_t len,
                            uint32_t timeout )
{
  int ret;
  printf("http超时\r\n");
  ret = mbedtls_net_recv_timeout(ctx, buf, len, timeout );
  return ret;
}


const struct addrinfo hints = {
    .ai_family = AF_INET,
    .ai_socktype = SOCK_STREAM,
};

int https_get_data_no_head(char *data)
{
  //char *buf=(char*)os_malloc(strlen(data));
  char *str=strstr(data,"\r\n\r\n");
  if(str!=NULL)
  {
    https_debug("找到get头开始去掉\r\n");
    //data = str+4;
    sprintf(data,"%s",str+4);
  }else
  {
    https_debug("未找到get头\r\n");

  }
  //os_free(buf);

  return 0;
}


struct addrinfo *addrinfo_res=NULL;
struct in_addr *inaddr=NULL;
int socket_s=0;


int http_get_task(char * send_buf,char * send_host,char *read_data)
{

  int return_dat=0;
  int rx_len=0;
  int time=0;
  char buf1[20];
  int len=0;
  char *str=NULL;
  char *str1=NULL;
  char *recv_buf = NULL;



  //while(1)
  {
      http_get_task_debug("开始域名解析:%s\r\n",send_host);
      //DNS域名解析
      int err = getaddrinfo(send_host, WEB_PORT, &hints, &addrinfo_res);
      if(err != 0 || addrinfo_res == NULL)
      {
        http_get_task_debug("域名解析失败\r\n");
        return_dat=-1;
        goto exit;
      }
      //打印获取的IP
      inaddr = &((struct sockaddr_in *)addrinfo_res->ai_addr)->sin_addr;
      http_get_task_debug("域名解析成功:%s\r\n",inet_ntoa(*inaddr));

      http_get_task_debug("新建socket\r\n");

      //新建socket
      socket_s = socket(addrinfo_res->ai_family, addrinfo_res->ai_socktype, 0);
      if(socket_s < 0)
      {
        http_get_task_debug("新建socket失败:%d\r\n",socket_s);
        return_dat=-2;

        goto exit;
      }
      http_get_task_debug("新建socket成功\r\n");

      http_get_task_debug("连接ip\r\n");
      //连接ip
      if(connect(socket_s, addrinfo_res->ai_addr, addrinfo_res->ai_addrlen) != 0)
      {
        http_get_task_debug("连接ip失败:%d\r\n",errno);
        return_dat=-3;
        goto exit;
      }
      http_get_task_debug("连接ip成功\r\n");

      http_get_task_debug("发送http包\r\n");
      //发送http包
      if (write(socket_s, send_buf, strlen(send_buf)) < 0)
        {
        http_get_task_debug("发送http包l失败\r\n");
        return_dat=-4;
        goto exit;
      }
      http_get_task_debug("发送http包成功:%s\r\n",send_buf);

      http_get_task_debug("获取http应答包\r\n");

      int sta=0;
      rx_len=0;
#define recv_buf_size 1024*20

      printf_memory();
      recv_buf = (char*)heap_caps_malloc(recv_buf_size, MALLOC_CAP_SPIRAM);
      memset(recv_buf,0,recv_buf_size);
      printf_memory();


      while(1)
      {
          http_get_task_debug("开始获取\r\n");
          rx_len += read(socket_s, &recv_buf[rx_len], recv_buf_size-1);
          if(rx_len>0)
          {
            //http_get_task_debug("获取http应答成功,数据长度:%d\r\n数据内容:----%s----\r\n",rx_len,recv_buf);

            // if(strstr(recv_buf,"请求异常页面"))
            // {
            //   http_get_task_debug("请求异常页面\r\n");
            //   sprintf(read_data,"failed");
            //   break;
            // }

#if 0
            str1 = recv_buf;
            memcpy(read_data,str1,rx_len);
            http_get_task_debug("复制成功 长度:%d\r\n----%s----\r\n",rx_len,read_data);
            return_dat=0;
            break;
#else
            time=0;

            str=strstr(recv_buf,"Content-Length: ");
            if(str==NULL||sta==1)
            {
              sta=1;
              http_get_task_debug("数据包中无Content-Length\r\n");

              if(rx_len<6)
              {
                http_get_task_debug("已接收完毕\r\n");
                break;
              }
              strcat(read_data,recv_buf);
              rx_len=0;
              bzero(recv_buf,recv_buf_size);

            }else
            {
              str+=16;
              memset(buf1,0,sizeof(buf1));
              for(int i=0;*str!='\r';i++)
              {
                buf1[i]=*str;
                str++;
              }
              len = atoi(buf1);
              http_get_task_debug("报头实体长度:%s %d 接收长度:%d\r\n",buf1,len,rx_len);
              if(rx_len<len)//GET到的数据过长需分多次获取
              {
                http_get_task_debug("获取http长度不够继续接收\r\n");
                continue;
              }else
              {
                //http_get_task_debug("接收成功 长度:%d\r\n----%s----\r\n",rx_len,recv_buf);

                str1 = recv_buf;
                sprintf(read_data,"%s\r\n",str1);
                //http_get_task_debug("复制成功 长度:%d\r\n----%s----\r\n",strlen(read_data),read_data);
              }
              break;
            }
#endif
          }else
          {
            http_get_task_debug("接收完毕\r\n");
            break;
          }
          if(++time>10)
          {
            http_get_task_debug("获取http应答包失败\r\n");
            return_dat=-5;
            break;
          }
          http_get_task_debug("正在获取获取http应答包:%d\r\n",time);
          vTaskDelay(100 / portTICK_RATE_MS);
      }
  }

exit:

  http_get_task_debug("获取数据结束 长度:%d\r\n----%s----\r\n",strlen(read_data),read_data);
  close(socket_s);
  freeaddrinfo(addrinfo_res);
  if(recv_buf!=NULL)
    heap_caps_free(recv_buf);
  printf_memory();
  return return_dat;
}

int HTTP_Read_Data(char *URL,char *origin_data,char *read_data,uint8_t method)
{
  int return_dat=0;

  char *https_get_buffer = (char*)heap_caps_malloc(1024*2, MALLOC_CAP_SPIRAM);
  char *http_host = (char*)heap_caps_malloc(1024, MALLOC_CAP_SPIRAM);
  char *http_filename = (char*)heap_caps_malloc(1024, MALLOC_CAP_SPIRAM);

  if (http_url_parse(URL, http_host, http_filename))
  {
    HTTP_Read_Data_debug("从URL中提取数据错误\r\n");
    return -1;
  }
  HTTP_Read_Data_debug("从URL中提取数据成功\r\n");
  HTTP_Read_Data_debug("http_host:%s\r\n",http_host);
  HTTP_Read_Data_debug("http_filename:%s\r\n",http_filename);

  sprintf((char*)https_get_buffer, GET, http_filename, http_host);
  return_dat = http_get_task((char*)https_get_buffer,http_host,read_data);
  if(origin_data!=NULL)
    memcpy(origin_data,read_data,strlen(read_data));
  https_get_data_no_head(read_data);

  heap_caps_free(https_get_buffer);
  heap_caps_free(http_host);
  heap_caps_free(http_filename);


  return return_dat;

}
