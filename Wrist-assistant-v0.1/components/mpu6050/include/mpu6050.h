#ifndef __mpu6050__h
#define __mpu6050__h

#include "main.h" 


typedef struct accel_out_tag
{
    int16_t accel_xout;
    int16_t accel_yout; 
    int16_t accel_zout; 
}accel_out_t;

typedef struct temp_out_tag
{
    int16_t temp_xout; 
}temp_out_t;

typedef struct gyro_out_tag
{
    int16_t gyro_xout; 
    int16_t gyro_yout; 
    int16_t gyro_zout; 
}gyro_out_t;

typedef struct measurement_out_tag
{
    accel_out_t accel_out;
    temp_out_t temp_out;
    gyro_out_t gyro_out;
}measurement_out_t;


/**
* @brief 初始化 mpu6050
*/
esp_err_t mpu6050_init();

/**
* @brief 读取加速度计、温度和陀螺仪数据
*/
measurement_out_t mpu6050_get_value();


#endif

