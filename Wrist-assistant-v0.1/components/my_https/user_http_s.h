#ifndef USER_HTTP_S_
#define USER_HTTP_S_

//获取IP地址
#define HTTPS_HuoQuIP           "http://icanhazip.com/"
//高德定位
#define HTTPS_DingWei           "http://restapi.amap.com/v3/ip?key=e673da4f70707f787c7b00443211602b&ip="    //"http://ip.ws.126.net/ipquery?ip="
//高德静态地图
#define HTTPS_JingTaiDITu       "https://restapi.amap.com/v3/staticmap?location=116.481485,39.990464&zoom=17&size=240*240&markers=mid,,A:116.481485,39.990464&key=e673da4f70707f787c7b00443211602b"


int https_get_TianQi(void);
int https_get_ShiJian(void);
#endif
