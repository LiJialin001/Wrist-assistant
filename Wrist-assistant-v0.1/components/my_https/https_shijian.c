#include "https_shijian.h"
#include "main.h"
#include "https.h"

// 1月份 -- 全名：January           缩写：Jan.
// 2月份 -- 全名：February         缩写：Feb.
// 3月份 -- 全名：March             缩写：Mar.
// 4月份 -- 全名：April                缩写：Apr.
// 5月份 -- 全名：May                 缩写：May（无缩写）
// 6月份 -- 全名：June                 缩写：Jun.
// 7月份 -- 全名：July                   缩写：Jul.
// 8月份 -- 全名：August              缩写：Aug.
// 9月份 -- 全名：September        缩写：Sep.
// 10月份 -- 全名：October          缩写：Oct.
// 11月份 -- 全名：November       缩写：Nov.
// 12月份 -- 全名：December        缩写：Dec.

//Date: Tue, 26 Jul 2022 08:56:17 GMT
uint8_t https_get_date_fromhttpheard(char *dat,_RiQi_Data * read_buf)
{
  uint8_t i=0;
  char *str1 = strstr(dat,"Date:");
  char *str = NULL;
  char buf[10];
  if(str1 == NULL)
  {
    return -1;
  }else
  {

//Date: Tue, 26 Jul 2022 08:/*26*/56:17 GMT
    str = str1;
    str+=23;
    memset(buf,0x00,sizeof(buf));
    buf[0] = *str++;
    buf[1] = *str;
    read_buf->shi= atoi(buf)+8;
    shijiani_debug("时:%d\r\n",read_buf->shi);

    str = str1;
    str+=26;
    memset(buf,0x00,sizeof(buf));
    buf[0] = *str++;
    buf[1] = *str;
    read_buf->fen= atoi(buf);
    shijiani_debug("分:%d\r\n",read_buf->fen);

    str = str1;
    str+=29;
    memset(buf,0x00,sizeof(buf));
    buf[0] = *str++;
    buf[1] = *str;
    read_buf->miao= atoi(buf);
    shijiani_debug("秒:%d\r\n",read_buf->miao);


    str = str1;
    str+=18;
    memset(buf,0x00,sizeof(buf));
    buf[0] = *str++;
    buf[1] = *str++;
    buf[2] = *str++;
    buf[3] = *str;
    read_buf->nian= atoi(buf);
    shijiani_debug("年:%d\r\n",read_buf->nian);


    str = str1;
    str+=11;
    memset(buf,0x00,sizeof(buf));
    buf[0] = *str++;
    buf[1] = *str;
    read_buf->ri = atoi(buf);
    shijiani_debug("日:%d\r\n",read_buf->ri);

    str = str1;
    str+=14;
    memset(buf,0x00,sizeof(buf));
    buf[0] = *str++;
    buf[1] = *str++;
    buf[2] = *str;
    if(strstr(buf,"Jan"))
    {
      read_buf->yue = 1;
    }else if(strstr(buf,"Feb"))
    {
      read_buf->yue = 2;
    }else if(strstr(buf,"Mar"))
    {
      read_buf->yue = 3;
    }else if(strstr(buf,"Apr"))
    {
      read_buf->yue = 4;
    }else if(strstr(buf,"May"))
    {
      read_buf->yue = 5;
    }else if(strstr(buf,"Jun"))
    {
      read_buf->yue = 6;
    }else if(strstr(buf,"Jul"))
    {
      read_buf->yue = 7;
    }else if(strstr(buf,"Aug"))
    {
      read_buf->yue = 8;
    }else if(strstr(buf,"Sep"))
    {
      read_buf->yue = 9;
    }else if(strstr(buf,"Oct"))
    {
      read_buf->yue = 10;
    }else if(strstr(buf,"Nov"))
    {
      read_buf->yue = 11;
    }else if(strstr(buf,"Dec"))
    {
      read_buf->yue = 12;
    }else
    {
      read_buf->yue = 0;
      shijiani_debug("解析月失败");
      return -1;
    }
    shijiani_debug("月:%d\r\n",read_buf->yue);

  }

  sprintf(read_buf->riqi,"%d-%d-%d",read_buf->nian,read_buf->yue,read_buf->ri);

  shijiani_debug("日期:%s\r\n",read_buf->riqi);
  shijiani_debug("时间:%d:%d:%d\r\n",read_buf->shi,read_buf->fen,read_buf->miao);


  return 0;
}


int https_get_ShiJian(void)
{
  int res = 0;
  char buf[50];

  res = HTTP_Get_ShiJian(&system_data.RiQi_Data);
  if(res)
  {
    shijiani_debug("获取时间失败\r\n");
    return -1;
  }
  return 0;
}

//获取时间与日期
int HTTP_Get_ShiJian(_RiQi_Data * read_buf)
{
  int return_dat=0;
  uint8_t res=0;
  char buf[50];
  char *str=NULL;
  int i=0,j=0;

  if(read_buf==NULL)
    return 1;

  char * http_recv_buff = (char*)heap_caps_malloc(1024*20, MALLOC_CAP_SPIRAM);
  char * http_recv_origin_buff = (char*)heap_caps_malloc(1024*20, MALLOC_CAP_SPIRAM);

  shijiani_debug("开始获取时间\r\n");

  res = HTTP_Read_Data(HTTPS_SuNing_ShiJian,http_recv_origin_buff,http_recv_buff,GET_REQ);

  if(res==0)
  {
    //shijiani_debug("获取到的数据:%s\r\n",http_recv_buff);

    str=strstr((char *)http_recv_buff, ":\"");
    if(str!=NULL)
    {

      str+=2;
      for(i=0;;i++)
      {
        if(str[i]==' ')
        {
          read_buf->riqi[i]='\0';
          break;
        }
        read_buf->riqi[i]=str[i];
      }
      shijiani_debug("解析到的日期:%s\r\n",read_buf->riqi);
      str+=i+1;
      for(i=0;;i++)
      {
        if(str[i]=='"')
        {
          read_buf->shijian[i]='\0';
          break;
        }
        read_buf->shijian[i]=str[i];
      }

      shijiani_debug("解析到的时间:%s\r\n",read_buf->shijian);


      str = read_buf->riqi;

      j=0;
      for(i=0;str[i]!='\0';i++)
      {
        if(str[i]=='-')
        {

          break;
        }
        buf[i]=str[i];
      }
      buf[i]='\0';
      read_buf->nian=atoi(buf);
      //shijiani_debug("年:%d\r\n",read_buf->nian);
      j+=i+1;
      str+=i+1;
      for(i=0;str[i]!='\0';i++)
      {
        if(str[i]=='-')
        {

          break;
        }
        buf[i]=str[i];
      }
      buf[i]='\0';
      read_buf->yue=atoi(buf);
      //shijiani_debug("月:%d\r\n",read_buf->yue);
      //shijiani_debug("str1:%s j:%d\r\n",str,j);

      str+=i+1;
      //shijiani_debug("str2:%s j:%d\r\n",str,j);
      for(i=0;str[i]!='\0';i++)
      {
        if(str[i]=='\0')
        {

          break;
        }
        buf[i]=str[i];
      }
      buf[i]='\0';
      read_buf->ri=atoi(buf);
      //shijiani_debug("日:%d\r\n",read_buf->ri);

      str = read_buf->shijian;
      j=0;
      for(i=0;str[i]!='\0';i++)
      {
        if(str[i]==':')
        {

          break;
        }
        buf[i]=str[i];
      }
      buf[i]='\0';
      read_buf->shi=atoi(buf);
      //shijiani_debug("时:%d\r\n",read_buf->shi);

      j+=i+1;
      str+=i+1;
      for(i=0;str[i]!='\0';i++)
      {
        if(str[i]==':')
        {

          break;
        }
        buf[i]=str[i];
      }
      buf[i]='\0';
      read_buf->fen=atoi(buf);
      //shijiani_debug("分:%d\r\n",read_buf->fen);
      //shijiani_debug("str1:%s j:%d\r\n",str,j);
      j+=i+1;
      str+=i+1;
      //shijiani_debug("str2:%s j:%d\r\n",str,j);
      for(i=0;str[i]!='\0';i++)
      {
        if(str[i]=='\0')
        {

          break;
        }
        buf[i]=str[i];
      }
      buf[i]='\0';
      read_buf->miao=atoi(buf);
      //shijiani_debug("秒:%d\r\n",read_buf->miao);
    }else
    {
      shijiani_debug("解析时间失败\r\n");
      return_dat= -1;
    }
  }else
  {
      return_dat= -2;
    shijiani_debug("获取时间失败:%d\r\n", res);
  }
  if(return_dat!=0)
  {
    res = https_get_date_fromhttpheard(http_recv_origin_buff,read_buf);
    if(res == 0)
    {
      return_dat = 0;
      shijiani_debug("从http头获取时间成功\r\n");
    }else
    {
      shijiani_debug("从http头获取时间失败\r\n");
    }

  }

  heap_caps_free(http_recv_buff);
  heap_caps_free(http_recv_origin_buff);


  return return_dat;
}


