idf_component_register(
        SRC_DIRS
        .
        SRCS
        .
        "wifi.c"        
        INCLUDE_DIRS
        .   
        REQUIRES main nvs_flash freertos webserver
        )
