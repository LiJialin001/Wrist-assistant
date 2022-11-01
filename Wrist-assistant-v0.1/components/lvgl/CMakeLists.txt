idf_component_register(SRC_DIRS "."
                                "lvgl/src/lv_core"
                                "lvgl/src/lv_draw"
                                "lvgl/src/lv_font"
                                "lvgl/src/lv_gpu"
                                "lvgl/src/lv_hal"
                                "lvgl/src/lv_misc"
                                "lvgl/src/lv_themes"
                                "lvgl/src/lv_widgets"
                                "lv_gif"
                                "lv_lib_png"
                        INCLUDE_DIRS "."
                                "lvgl"
                                "lvgl/src/lv_core"
                                "lvgl/src/lv_draw"
                                "lvgl/src/lv_font"
                                "lvgl/src/lv_gpu"
                                "lvgl/src/lv_hal"
                                "lvgl/src/lv_misc"
                                "lvgl/src/lv_themes"
                                "lvgl/src/lv_widgets"
                                "lv_gif"
                                "lv_lib_png"
                        REQUIRES touch_screen main)

# Some warning might appear when complile master branch.
# Disable all warning output and set optimize level
target_compile_options(${COMPONENT_LIB} PRIVATE -w -O2)
