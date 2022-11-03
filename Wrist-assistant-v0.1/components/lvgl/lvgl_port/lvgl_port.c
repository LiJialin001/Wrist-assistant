/**
 * @file lvgl_port.c
 * @brief
 * @version 0.1
 * @date 2021-01-14
 *
 * @copyright Copyright 2021 Espressif Systems (Shanghai) Co. Ltd.
 *
 *      Licensed under the Apache License, Version 2.0 (the "License");
 *      you may not use this file except in compliance with the License.
 *      You may obtain a copy of the License at
 *
 *               http://www.apache.org/licenses/LICENSE-2.0
 *
 *      Unless required by applicable law or agreed to in writing, software
 *      distributed under the License is distributed on an "AS IS" BASIS,
 *      WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *      See the License for the specific language governing permissions and
 *      limitations under the License.
 */

#include "lvgl_port.h"

#define LVGL_BUFFER_SIZE  (sizeof(lv_color_t) * (LV_HOR_RES_MAX * LV_VER_RES_MAX))
#define LVGL_INIT_PIXCNT  (LV_HOR_RES_MAX * LV_VER_RES_MAX)

static const char *TAG = "lvgl_port";

#define LOG_TRACE(...)	ESP_LOGD(TAG, ##__VA_ARGS__)

static SemaphoreHandle_t lvgl_mutex = NULL;

esp_err_t lv_port_sem_take(void)
{
    return !xSemaphoreTake(lvgl_mutex, portMAX_DELAY);
}

esp_err_t lv_port_sem_give(void)
{
    return !xSemaphoreGive(lvgl_mutex);
}

static void lvgl_tick_task(void *data)
{
    static TickType_t tick = 0;
    static const uint32_t task_period = 10;

    tick = xTaskGetTickCount();

    while (1) {
        lv_tick_inc(task_period);
        vTaskDelayUntil(&tick, pdMS_TO_TICKS(task_period));
    }
}

static void lv_handler_task(void *pvparam)
{
    static TickType_t tick;

    tick = xTaskGetTickCount();

    while (1) {
        lv_task_handler();
        vTaskDelayUntil(&tick, pdMS_TO_TICKS(20));
    }
}

static IRAM_ATTR void lvgl_flush_cb(lv_disp_drv_t * disp_drv, const lv_area_t * area, lv_color_t * color_p)
{
    lv_port_sem_take();

    lv_disp_flush_ready(disp_drv);

    lcd_flush_area(area->x1, area->y1, area->x2, area->y2, (uint8_t *)color_p);

    lv_port_sem_give();
}

static IRAM_ATTR bool lvgl_read_cb(lv_indev_drv_t * indev_drv, lv_indev_data_t * data)
{
    static uint8_t tp_num = 0;
    static uint16_t x = 0, y = 0;

    cst816t_read_pos(&tp_num, &x, &y);

    if (0 == tp_num) {
        data->state = LV_INDEV_STATE_REL;
    } else {
        /* Swap xy order and invert y direction */
        data->point.x = x;
        data->point.y = y;//LV_VER_RES_MAX - x - 1;
        data->state = LV_INDEV_STATE_PR;
    }

    //LOG_TRACE("[%d] - [%3d][%3d]", tp_num, data->point.x, data->point.y);

    return false;
}

esp_err_t lvgl_init(void)
{
    lv_init();

    lvgl_mutex = xSemaphoreCreateMutex();

    /*!< Create a display buffer */
    static lv_disp_buf_t disp_buf;

#if 0
    static DRAM_ATTR lv_color_t *lv_buf;
    /*!< Use DRAM as sigle none screen size buffer */
    lv_buf = (lv_color_t *)heap_caps_malloc(LVGL_BUFFER_SIZE, MALLOC_CAP_INTERNAL | MALLOC_CAP_8BIT);
#else
    static lv_color_t lv_buf[LV_HOR_RES_MAX*50];
    lv_disp_buf_init(&disp_buf, lv_buf, NULL, LV_HOR_RES_MAX*50);
#endif

    /*!< Create a display */
    lv_disp_drv_t disp_drv;
    lv_disp_drv_init(&disp_drv);
    disp_drv.buffer = &disp_buf;
    disp_drv.flush_cb = lvgl_flush_cb;
    lv_disp_drv_register(&disp_drv);

    /*!< Register input devcie and callback */
    lv_indev_drv_t indev_drv;
    lv_indev_drv_init(&indev_drv);
    indev_drv.type = LV_INDEV_TYPE_POINTER;
    indev_drv.read_cb = lvgl_read_cb;
    lv_indev_drv_register(&indev_drv);

    lv_obj_set_style_local_bg_color(lv_scr_act(), LV_OBJ_PART_MAIN, LV_STATE_DEFAULT, LV_COLOR_BLACK);

    xTaskCreate(
		(TaskFunction_t)        lvgl_tick_task,
		(const char * const)    "LVGL Tick Task",
		(const uint32_t)        1024,
		(void * const)          NULL,
		(UBaseType_t)           configMAX_PRIORITIES,
		(TaskHandle_t * const)  NULL);

    /*!< Task for lvgl event handler and screen flush */
    xTaskCreate(
        (TaskFunction_t)        lv_handler_task,
        (const char * const)    "LVGL Handler Task",
        (const uint32_t)        4 * 1024,
        (void * const)          NULL,
        (UBaseType_t)           configMAX_PRIORITIES - 1,
        (TaskHandle_t * const)  NULL);

    return ESP_OK;
}
