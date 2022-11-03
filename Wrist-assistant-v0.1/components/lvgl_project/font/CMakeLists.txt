#添加头文件目录
idf_component_register(
    SRC_DIRS
    "."
    SRCS
    "font_acsii_12.c"
    "font_acsii_16.c"
    "font_acsii_32.c"
    "font_acsii_48.c"
    "font_ChangYongHanZi_12.c"
    "font_ChangYongHanZi_16.c"
    "font_ChangYongHanZi_24.c"
    "font_ZiDing_K8_12.c"
    "font_ZiDing_K8_16.c"
    "font_ZiDing_K8_24.c"

    INCLUDE_DIRS
    "."

    REQUIRES lvgl my_system main)
