/**
 * @file lvgl_port.h
 * @brief LVGL basic functions header file
 * @version 0.1
 * @date 2021-01-22
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
#pragma once

#include <stdio.h>

#include "freertos/FreeRTOS.h"
#include "freertos/semphr.h"
#include "freertos/task.h"

#include "lvgl/lvgl.h"

#include "cst816t.h"
#include "lcd.h"
#include "my_system.h"


#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Initialize LVGL, includes buffer allocation, semaphore and task creating.
 *
 * @return esp_err_t Initialize status. Always return ESP_OK for now
 */
esp_err_t lvgl_init(void);

/**
 * @brief Take GUI semaphore
 *
 * @return esp_err_t If tick_to_wait is not portMAX_DELAY, return semaphore taking result.
 */
esp_err_t lv_port_sem_take(void);

/**
 * @brief Give GUI semaphore
 *
 * @return esp_err_t Semaphore giving result.
 */
esp_err_t lv_port_sem_give(void);

#ifdef __cplusplus
}   /*!< extern "C" { */
#endif

