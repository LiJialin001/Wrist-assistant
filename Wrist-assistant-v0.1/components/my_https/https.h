#ifndef _https_h_
#define _https_h_

#include "main.h"


#if 1
  #define https_debug(format, ...)  my_debug("[https]- ",format,##__VA_ARGS__);
#else
  #define https_debug(format, ...)  ;
#endif

#if 1
  #define http_get_task_debug(format, ...)  my_debug("[http_get_task]- ",format,##__VA_ARGS__);
#else
  #define http_get_task_debug(format, ...)  ;
#endif
#if 1
  #define HTTP_Read_Data_debug(format, ...)  my_debug("[HTTP_Read_Data]- ",format,##__VA_ARGS__);
#else
  #define HTTP_Read_Data_debug(format, ...)  ;
#endif

enum
{
  GET_REQ,
  POST_REQ,
};
#define WEB_PORT            "80"
#define errno		(*__errno())

//心知天气key
#define HTTPS_XinZHi_Key "S2eHdKLoI6wioz6se"//"Spomv8m-PvaAm5XCA"
//https://api.seniverse.com/v3/air/now.json?key=2skpfx3xpxr1qqe9&language=zh-Hans&scope=city&location=苏州
//心知天气
#define HTTPS_XinZHi            "https://api.seniverse.com/v3/weather/daily.json?key="HTTPS_XinZHi_Key"&language=zh-Hans&unit=c&start=0&days=5&location="
//心知空气质量
#define HTTPS_KongQi            "https://api.seniverse.com/v3/air/now.json?key="HTTPS_XinZHi_Key"&language=zh-Hans&scope=city&location="
//心知日出日落
#define HTTPS_RiLuo             "https://api.seniverse.com/v3/geo/sun.json?key="HTTPS_XinZHi_Key"&language=zh-Hans&start=0&days=7&location="



/* 远程服务器的端口 */
#define REMOTE_PORT             "443"
/* GET请求 */
#define GET                     "GET /%s HTTP/1.1\r\nAccept:*/*\r\nHost:%s\r\n\r\n"
//#define GET                     "GET /%s HTTP/1.1\r\nAccept: text/html, application/xhtml+xml, image/jxr, */*\r\nAccept-Language: zh-CN,zh;q=0.8\r\nAccept-Charset: GBK,utf-8;q=0.7,*;q=0.3\r\nHost: %s\r\n\r\n"
/* POST请求,此章节暂时不讲 */
#define POST                    "POST /%s HTTP/1.1\r\nAccept: */*\r\nContent-Length: %d\r\nContent-Type: application/x-www-form-urlencoded; charset=utf-8\r\nHost: %s\r\nConnection: Keep-Alive\r\n\r\n%s"
/* 这里的内容由用户自己填充,具体内容用户自己填充 */
#define POST_CONTENT            "example_content"



esp_err_t http_url_parse(char *URL, char *host, char *filename);
int HTTP_Read_Data(char *URL,char *origin_data,char *read_data,uint8_t method);
int https_get_data_no_head(char *data);
#endif
