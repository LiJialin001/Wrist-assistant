#include "font.h"
#include "main.h"

_font_data font_data;
static uint8_t font_12_init(uint8_t mode);
static uint8_t font_16_init(uint8_t mode);
static uint8_t font_24_init(uint8_t mode);


uint8_t font_init(void)
{
    font_12_init(0);
    font_16_init(0);
    font_24_init(0);

    return 0;
}

static uint8_t font_12_init(uint8_t mode)
{
    uint8_t r_dat=0;
    font_data.file_font_12 = fopen(font_12_path, "r");
    if (font_data.file_font_12 == NULL)
    {
        font_debug( "font12打开失败");
        r_dat=1;
        goto exit;
    }
    font_debug( "font12打开成功");

exit:
    return r_dat;
}

uint8_t font_12_get_data(uint8_t * buf,int offset, int size)
{
    if(font_data.file_font_12==NULL)
        return;
    memset(buf, 0, size);
    fseek(font_data.file_font_12,offset,SEEK_SET);
    fread(buf, 1, size, font_data.file_font_12);
    return 0;
}


static uint8_t font_16_init(uint8_t mode)
{
    uint8_t r_dat=0;
    font_data.file_font_16 = fopen(font_16_path, "r");
    if (font_data.file_font_16 == NULL)
    {
        font_debug( "font16打开失败");
        r_dat=1;
        goto exit;
    }
    font_debug( "font16打开成功");

exit:
    return r_dat;
}

uint8_t font_16_get_data(uint8_t * buf,int offset, int size)
{
    if(font_data.file_font_16==NULL)
        return;
    memset(buf, 0, size);
    fseek(font_data.file_font_16,offset,SEEK_SET);
    fread(buf, 1, size, font_data.file_font_16);
    return 0;
}

static uint8_t font_24_init(uint8_t mode)
{
    uint8_t r_dat=0;
    font_data.file_font_24 = fopen(font_24_path, "r");
    if (font_data.file_font_24 == NULL)
    {
        font_debug( "font24打开失败");
        r_dat=1;
        goto exit;
    }
    font_debug( "font24打开成功");

exit:
    return r_dat;
}

uint8_t font_24_get_data(uint8_t * buf,int offset, int size)
{
    if(font_data.file_font_24==NULL)
        return;
    memset(buf, 0, size);
    fseek(font_data.file_font_24,offset,SEEK_SET);
    fread(buf, 1, size, font_data.file_font_24);
    return 0;
}
