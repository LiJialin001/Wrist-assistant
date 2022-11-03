#include "webserver.h"

#include "string.h"


static const char *TAG="webserver";

int pre_start_mem=0, post_stop_mem=0, post_stop_min_mem=0;

httpd_handle_t gsm_httpd_handle=NULL;

static char * html_buf=NULL;
uint32_t g_html_fileSize=0;

#if 0
static esp_err_t test_header_duankai_handler(httpd_req_t *req)
{
    webserver_debug("断开连接\r\n");
    httpd_resp_set_hdr(req, "Access-Control-Allow-Origin", "*");
    return httpd_resp_send(req, NULL, 0);
}

static esp_err_t open_web_get_handler(httpd_req_t *req)
{

    // extern const unsigned char index_ov2640_html_gz_start[] asm("_binary_index_ov2640_html_gz_start");
    // extern const unsigned char index_ov2640_html_gz_end[] asm("_binary_index_ov2640_html_gz_end");
    // size_t index_ov2640_html_gz_len = index_ov2640_html_gz_end - index_ov2640_html_gz_start;

    // extern const unsigned char test_html_gz_start[] asm("_binary_test_html_gz_start");
    // extern const unsigned char test_html_gz_end[] asm("_binary_test_html_gz_end");
    // size_t test_html_gz_len = test_html_gz_end - test_html_gz_start;

    // extern const unsigned char test1_html_gz_start[] asm("_binary_test1_html_gz_start");
    // extern const unsigned char test1_html_gz_end[] asm("_binary_test1_html_gz_end");
    // size_t test1_html_gz_len = test1_html_gz_end - test1_html_gz_start;

    webserver_debug("打开网页\r\n");

     //httpd_resp_set_type(req, HTTPD_TYPE_TEXT);
     //httpd_resp_send(req, http_post, HTTPD_RESP_USE_STRLEN);
    httpd_resp_set_type(req, "text/html");
    httpd_resp_set_hdr(req, "Content-Encoding", "gzip");
    httpd_resp_send(req, (const char *)html_buf, g_html_fileSize);

    return ESP_OK;
}

esp_err_t echo_post_handler(httpd_req_t *req)
{
    webserver_debug( "/echo handler read content length %d", req->content_len);
    webserver_debug("post请求\r\n");
    char*  buf = malloc(req->content_len + 1);
    size_t off = 0;
    int    ret;

    if (!buf)
    {
        ESP_LOGE(TAG, "Failed to allocate memory of %d bytes!", req->content_len + 1);
        httpd_resp_send_500(req);
        return ESP_FAIL;
    }

    while (off < req->content_len) {
        /* Read data received in the request */
        ret = httpd_req_recv(req, buf + off, req->content_len - off);
        if (ret <= 0) {
            if (ret == HTTPD_SOCK_ERR_TIMEOUT) {
                httpd_resp_send_408(req);
            }
            free (buf);
            return ESP_FAIL;
        }
        off += ret;
        webserver_debug( "/echo handler 接收长度: %d", ret);
    }
    buf[off] = '\0';

    if (req->content_len < 128) {
        webserver_debug( "/echo handler 读取到数据: %s", buf);
    }

    httpd_resp_set_hdr(req, "Access-Control-Allow-Origin", "*");
    httpd_resp_send(req, NULL, 0);

    free (buf);
    return ESP_OK;
}
static esp_err_t parse_get(httpd_req_t *req, char **obuf)
{
    char *buf = NULL;
    size_t buf_len = 0;

    buf_len = httpd_req_get_url_query_len(req) + 1;
    if (buf_len > 1) {
        buf = (char *)malloc(buf_len);
        if (!buf) {
            httpd_resp_send_500(req);
            return ESP_FAIL;
        }
        if (httpd_req_get_url_query_str(req, buf, buf_len) == ESP_OK) {
            *obuf = buf;
            return ESP_OK;
        }
        free(buf);
    }
    httpd_resp_send_404(req);
    return ESP_FAIL;
}


static esp_err_t set_wifi_handler(httpd_req_t *req)
{
    char *buf = NULL;
    char wifi_name[30];
    char wifi_password[30];
    char res;
    webserver_debug("收到/set_wifi\r\n");
    if (parse_get(req, &buf) != ESP_OK) {
        return ESP_FAIL;
    }
    webserver_debug("解析成功\r\n");
    if (httpd_query_key_value(buf, "wifi_name", wifi_name, sizeof(wifi_name)) != ESP_OK ||
        httpd_query_key_value(buf, "wifi_password", wifi_password, sizeof(wifi_password)) != ESP_OK)
    {
        free(buf);
        webserver_debug("数据内容错误\r\n");
        httpd_resp_send_404(req);
        return ESP_FAIL;
    }
    free(buf);

    sprintf(system_data.wifi_name,"%s",wifi_name);
    sprintf(system_data.wifi_password,"%s",wifi_password);

    //nvs_set_wifi(wifi_name,wifi_password);



    webserver_debug( "wifi名字:%s wifi密码:%s", wifi_name, wifi_password);
    httpd_resp_set_hdr(req, "Access-Control-Allow-Origin", "*");
    return httpd_resp_send(req, NULL, 0);
}

static esp_err_t status_handler(httpd_req_t *req)
{
    char *buf = NULL;
    static char json_response[1024];
    char *p = json_response;
    *p++ = '{';

    char res;
    webserver_debug("收到/status\r\n");

    p += sprintf(p, "\"wifi_name\":\"%s\"", system_data.wifi_name);
    p += sprintf(p, ",\"wifi_password\":\"%s\"", system_data.wifi_password);
    *p++ = '}';
    *p++ = 0;
    webserver_debug("返回:%s\r\n",json_response);
    httpd_resp_set_type(req, "application/json");
    httpd_resp_set_hdr(req, "Access-Control-Allow-Origin", "*");
    return httpd_resp_send(req, json_response, strlen(json_response));
}
static esp_err_t shuaxin_handler(httpd_req_t *req)
{
    char *buf = NULL;
    static char json_response[1024];
    char *p = json_response;
    *p++ = '{';

    char res;
    webserver_debug("收到/shuaxin\r\n");

    system_data.web_huoqu_tianqi_flag=true;
    httpd_resp_set_type(req, "application/json");
    httpd_resp_set_hdr(req, "Access-Control-Allow-Origin", "*");
    return httpd_resp_send(req, NULL, 0);
}
static esp_err_t reset_handler(httpd_req_t *req)
{
    char res;
    webserver_debug("收到/reset\r\n");

    httpd_resp_set_type(req, "application/json");
    httpd_resp_set_hdr(req, "Access-Control-Allow-Origin", "*");
    httpd_resp_send(req, NULL, 0);

    webserver_debug("开始重启...\r\n");
    esp_restart();
    return 0;
}

httpd_uri_t basic_handlers[] = {
    {
        .uri      = "/",
        .method   = HTTP_GET,
        .handler  = open_web_get_handler,
        .user_ctx = NULL,
    },
    {
        .uri      = "/status",
        .method   = HTTP_GET,
        .handler  = status_handler,
        .user_ctx = NULL,
    },
    { .uri      = "/favicon.ico",
      .method   = HTTP_GET,
      .handler  = test_header_duankai_handler,
      .user_ctx = NULL,
    },
    { .uri      = "/echo",
      .method   = HTTP_POST,
      .handler  = echo_post_handler,
      .user_ctx = NULL,
    },
    {
        .uri = "/set_wifi",
        .method = HTTP_GET,
        .handler =set_wifi_handler,
        .user_ctx = NULL,
    },
    {
        .uri = "/shuaxin",
        .method = HTTP_GET,
        .handler =shuaxin_handler,
        .user_ctx = NULL,
    },
    {
        .uri = "/reset",
        .method = HTTP_GET,
        .handler =reset_handler,
        .user_ctx = NULL,
    },

};

int basic_handlers_no = sizeof(basic_handlers)/sizeof(httpd_uri_t);
void register_basic_handlers(httpd_handle_t hd)
{
    int i;
    webserver_debug("注册基本处理程序\r\n");
    webserver_debug( "Registering basic handlers");
    webserver_debug("handlers数量:%d\r\n", basic_handlers_no);
    webserver_debug( "No of handlers = %d", basic_handlers_no);
    for (i = 0; i < basic_handlers_no; i++) {
        if (httpd_register_uri_handler(hd, &basic_handlers[i]) != ESP_OK) {
            ESP_LOGW(TAG, "register uri failed for %d", i);
            return;
        }
    }
    webserver_debug( "Success");
}

httpd_handle_t httpd_init()
{
    pre_start_mem = esp_get_free_heap_size();
    httpd_handle_t hd ;
    httpd_config_t config = HTTPD_DEFAULT_CONFIG();
    /* Modify this setting to match the number of test URI handlers */
    config.max_uri_handlers  = 9;
    config.server_port = 80;
    config.stack_size  = 4096*2;
    /* This check should be a part of http_server */
    config.max_open_sockets = (CONFIG_LWIP_MAX_SOCKETS - 3);

    if (httpd_start(&hd, &config) == ESP_OK)
    {
        webserver_debug( "Started HTTP server on port: '%d'", config.server_port);
        webserver_debug( "Max URI handlers: '%d'", config.max_uri_handlers);
        webserver_debug( "Max Open Sessions: '%d'", config.max_open_sockets);
        webserver_debug( "Max Header Length: '%d'", HTTPD_MAX_REQ_HDR_LEN);
        webserver_debug( "Max URI Length: '%d'", HTTPD_MAX_URI_LEN);
        webserver_debug( "Max Stack Size: '%d'", config.stack_size);
        return hd;
    }
    return NULL;
}

void test_httpd_stop(httpd_handle_t hd)
{
    httpd_stop(hd);
    post_stop_mem = esp_get_free_heap_size();
    gsm_httpd_handle=NULL;
    webserver_debug( "HTTPD Stop: Current free memory: %d", post_stop_mem);
}


httpd_handle_t start_webserver(void)
{
    const char * html_file_path = "/spiffs/test.html.gz";
    if(html_buf == NULL)
    {

        g_html_fileSize = system_get_file_size(html_file_path);
        FILE *pread = fopen(html_file_path,"rb");
        if (pread==NULL)
        {
            webserver_debug("无此文件");
            return;
        }

        html_buf = (char*)heap_caps_malloc(g_html_fileSize, MALLOC_CAP_SPIRAM);

        if(html_buf == NULL)
        {
            webserver_debug("内存申请失败");
        }

        fread(html_buf,1,g_html_fileSize,pread);
        fclose(pread);
    }

    if(gsm_httpd_handle==NULL)
    {
        webserver_debug("启动webserver\r\n");
        gsm_httpd_handle = httpd_init();
        if (gsm_httpd_handle) {

            register_basic_handlers(gsm_httpd_handle);
        }
    }else
    {
        webserver_debug("webserver已经在运行\r\n");
    }

    return gsm_httpd_handle;
}

void stop_webserver(void)
{
    if(gsm_httpd_handle)
    {
        webserver_debug("停止webserver\r\n");
        test_httpd_stop(gsm_httpd_handle);
    }else
    {
        webserver_debug("webserver未运行\r\n");
    }
}
#else


httpd_handle_t start_webserver(void)
{

    return gsm_httpd_handle;
}

void stop_webserver(void)
{

}
#endif
