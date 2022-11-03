idf_component_register(
    SRC_DIRS
    "."
    SRCS
    .
    "https_chengshi.c"
    "https_ip.c"
    "https_kongqi.c"
    "https_riluo.c"
    "https_shijian.c"
    "https_tianqi.c"
    "https.c"
    "user_http_s.c"

    INCLUDE_DIRS
    "."

    REQUIRES lvgl my_system main openthread mbedtls lwip)
