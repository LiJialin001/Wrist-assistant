#添加头文件目录
idf_component_register(
    SRC_DIRS
        .
        SRCS
        .
        "my_system.c"
        "system_config_data.c"                 
    INCLUDE_DIRS
        .
        REQUIRES  lvgl_project esp_timer
        )
