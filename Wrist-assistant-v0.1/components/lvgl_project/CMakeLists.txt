#添加头文件目录
idf_component_register(
    SRC_DIRS
    "."
    "lvgl_bpm"
    "lvgl_Some_style"
    "lvgl_global"


    INCLUDE_DIRS
    "."
    "lvgl_bpm"
    "lvgl_Some_style"
    "lvgl_global"

    REQUIRES lvgl main)
