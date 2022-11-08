idf_component_register(
                    SRCS
                    "."
                    "delay.c"
                    INCLUDE_DIRS
                    "."
                    REQUIRES main
                    )


#spiffs_create_partition_image(storage ../../spiffs_image FLASH_IN_PROJECT)

