#ifndef __mpu6050__h
#define __mpu6050__h

#include "main.h" 


#define ABS(a) (0 - (a)) > 0 ? (-(a)) : (a)   //取a的绝对值
#define MAX(a, b) (a > b) ? (a) : (b)    //取a和b中的最大值
#define MIN(a, b) (a < b) ? (a) : (b)    //取a和b中的最小值
#define SAMPLE_NUM                10          //采样10次取平均值
#define MIN_RELIABLE_VARIATION    500         //最小可信赖变化量
#define MAX_RELIABLE_VARIATION    5000        //最大可信赖变化量

// 最活跃轴
#define ACTIVE_NUM          30            //最活跃轴更新周期
#define ACTIVE_NULL         0             //最活跃轴未知
#define ACTIVE_X            1             //最活跃轴是X
#define ACTIVE_Y            2             //最活跃轴是Y
#define ACTIVE_Z            3             //最活跃轴是Z


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


//极值数据
typedef struct
{
	gyro_out_t max;
	gyro_out_t min;
}peak_value_t;
peak_value_t peak_value;

typedef struct 
{
    gyro_out_t old_ave_GyroValue;
    gyro_out_t ave_GyroValue;
    peak_value_t peak_GyroValue;
}measurement_data_t;

measurement_data_t measurement_data;

/**
* @brief 初始化 mpu6050
*/
esp_err_t mpu6050_init();

/**
* @brief 读取加速度计、温度和陀螺仪数据
*/
measurement_out_t mpu6050_get_value();


void Gyro_sample_update(void);
void detect_step(void);

#endif

