idf_component_register(
                    SRCS
                    "."
                    "multi_button_task.c"
                    "multi_button.c"
                    "multi_button_callback.c"

                    INCLUDE_DIRS
                    "."
                    REQUIRES driver bsp_driver
                    )

