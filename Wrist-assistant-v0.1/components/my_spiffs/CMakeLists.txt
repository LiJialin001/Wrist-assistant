idf_component_register(
                    SRCS
                    .
                    "my_spiffs.c"
                    INCLUDE_DIRS
                    .
                    REQUIRES spiffs mbedtls
                    )


#spiffs_create_partition_image(storage ../../spiffs_image FLASH_IN_PROJECT)

