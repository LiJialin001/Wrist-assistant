idf_component_register(
                    SRCS
                    "."
                    "bsp_i2c.c"
                    "bsp_ledc.c"
                    "bsp_power.c"
                    "bsp_key.c"
                    SRC_DIRS
                    "."

                    INCLUDE_DIRS
                    "."
                    REQUIRES driver main
                    )

