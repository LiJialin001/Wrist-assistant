#include "mpu6050.h"  

uint8_t most_active_axis = ACTIVE_NULL;   //记录最活跃轴

static const uint8_t mpu6050_init_cmd[11][2] = {
    {0x6B, 0x80}, // PWR_MGMT_1, DEVICE_RESET  
    // need wait 
    {0x6B, 0x00}, // cleat SLEEP
    {0x1B, 0x18}, // Gyroscope Full Scale Range = ± 2000 °/s
    {0x1C, 0x00}, // Accelerometer Full Scale Range = ± 2g 
    {0x38, 0x00}, // Interrupt Enable.disenable 
    {0x6A, 0x00}, // User Control.auxiliary I2C are logically driven by the primary I2C bus
    {0x23, 0x00}, // FIFO Enable.disenable  
    {0x19, 0x63}, // Sample Rate Divider.Sample Rate = 1KHz / (1 + 99)  
    {0x1A, 0x13}, // EXT_SYNC_SET = GYRO_XOUT_L[0]; Bandwidth = 3
    {0x6B, 0x01}, // Power Management 1.PLL with X axis gyroscope reference
    {0x6C, 0x00}  // Power Management 2
};

static esp_err_t  i2c_master_read_slave(i2c_port_t i2c_num, uint8_t *reg_addr, uint8_t *data_rd, size_t size)
{
    if (size == 0) {
        return ESP_OK;
    }
    i2c_cmd_handle_t cmd = i2c_cmd_link_create();
    i2c_master_start(cmd);
    i2c_master_write_byte(cmd, (MPU6050_ADDR << 1) | WRITE_BIT, ACK_CHECK_EN);
    i2c_master_write_byte(cmd, reg_addr, ACK_CHECK_EN);
    i2c_master_start(cmd);
    i2c_master_write_byte(cmd, (MPU6050_ADDR << 1) | READ_BIT, ACK_CHECK_EN);
    if (size > 1) {
        i2c_master_read(cmd, data_rd, size - 1, ACK_VAL);
    }
    i2c_master_read_byte(cmd, data_rd + size - 1, NACK_VAL);
    i2c_master_stop(cmd);
    esp_err_t ret = i2c_master_cmd_begin(i2c_num, cmd, 1000 / portTICK_RATE_MS);
    i2c_cmd_link_delete(cmd);
    return ret;
}

static esp_err_t i2c_master_write_slave(i2c_port_t i2c_num, uint8_t *data_wr, size_t size)
{
    i2c_cmd_handle_t cmd = i2c_cmd_link_create();
    i2c_master_start(cmd);
    i2c_master_write_byte(cmd, (MPU6050_ADDR << 1) | WRITE_BIT, ACK_CHECK_EN);
    i2c_master_write(cmd, data_wr, size, ACK_CHECK_EN);
    i2c_master_stop(cmd);
    esp_err_t ret = i2c_master_cmd_begin(i2c_num, cmd, 1000 / portTICK_RATE_MS);
    i2c_cmd_link_delete(cmd);
    return ret;
}

/**
* @brief 初始化 mpu6050
*/
esp_err_t mpu6050_init()
{
    esp_err_t esp_err;

    for (size_t i = 0; i < 11; i++)
    {
        esp_err = i2c_master_write_slave(MPU6050_I2C_PORT_NUM, mpu6050_init_cmd[i], 2);
        if (i == 0)
            vTaskDelay(500 / portTICK_RATE_MS);
    }
    return esp_err;
}

/**
* @brief 读取加速度计、温度和陀螺仪数据
*/
measurement_out_t mpu6050_get_value()
{
    uint8_t *measurement_bytes_out = (uint8_t *)malloc(14);
    i2c_master_read_slave(MPU6050_I2C_PORT_NUM, 0x3B, measurement_bytes_out, 14);
    measurement_out_t measurement_out = {
        .accel_out.accel_xout = (int16_t)(measurement_bytes_out[0]<<8 | measurement_bytes_out[1]),
        .accel_out.accel_yout = (int16_t)(measurement_bytes_out[2]<<8 | measurement_bytes_out[3]),
        .accel_out.accel_zout = (int16_t)(measurement_bytes_out[4]<<8 | measurement_bytes_out[5]),
        .temp_out.temp_xout = (int16_t)(measurement_bytes_out[6]<<8 | measurement_bytes_out[7]),
        .gyro_out.gyro_xout = (int16_t)(measurement_bytes_out[8]<<8 | measurement_bytes_out[9]),
        .gyro_out.gyro_yout = (int16_t)(measurement_bytes_out[10]<<8 | measurement_bytes_out[11]),
        .gyro_out.gyro_zout = (int16_t)(measurement_bytes_out[12]<<8 | measurement_bytes_out[13]),
    };
    return measurement_out;
}

/**
* @brief 读取陀螺仪数据
*/
gyro_out_t mpu6050_get_Gyro_value()
{
    uint8_t *measurement_bytes_out = (uint8_t *)malloc(14);
    i2c_master_read_slave(MPU6050_I2C_PORT_NUM, 0x3B, measurement_bytes_out, 14);
    gyro_out_t gyro_out = {
        .gyro_xout = (int16_t)(measurement_bytes_out[8]<<8 | measurement_bytes_out[9]),
        .gyro_yout = (int16_t)(measurement_bytes_out[10]<<8 | measurement_bytes_out[11]),
        .gyro_zout = (int16_t)(measurement_bytes_out[12]<<8 | measurement_bytes_out[13]),
    };
    printf("gyro_xout: %d, gyro_yout: %d, gyro_zout: %d\r\n", gyro_out.gyro_xout, gyro_out.gyro_yout, gyro_out.gyro_zout);
    return gyro_out;
}

/**
 * @brief 保存上一次采样数据 → 均值采样本次数据 → 计算本次和上次的差值 → 检验差值大小(若超限则将本次数据回退到上一次的大小) → 保存最大值和最小值
 * 
 */
void Gyro_sample_update(void)
{
	gyro_out_t GyroValue;
	gyro_out_t change;
	int sum[3] = {0};
	uint8_t success_num = 0;

    // 保存上一次数据
    measurement_data.old_ave_GyroValue = measurement_data.ave_GyroValue;


	//多次测量取平均值
	for(uint8_t i = 0; i < SAMPLE_NUM; i++)
	{
		GyroValue = mpu6050_get_Gyro_value();
        sum[0] += GyroValue.gyro_xout;
        sum[1] += GyroValue.gyro_yout;
        sum[2] += GyroValue.gyro_zout;
        success_num ++;
	}

    measurement_data.ave_GyroValue.gyro_xout = sum[0] / success_num;
	measurement_data.ave_GyroValue.gyro_yout = sum[1] / success_num;
	measurement_data.ave_GyroValue.gyro_zout = sum[2] / success_num;

    //原始数据变化量
	change.gyro_xout = ABS(measurement_data.ave_GyroValue.gyro_xout - measurement_data.old_ave_GyroValue.gyro_xout);
	change.gyro_yout = ABS(measurement_data.ave_GyroValue.gyro_yout - measurement_data.old_ave_GyroValue.gyro_yout);
	change.gyro_zout = ABS(measurement_data.ave_GyroValue.gyro_zout - measurement_data.old_ave_GyroValue.gyro_zout);

    //如果变化量超出可接受的变化值，则将原始数据退回到上一次的大小
	if(change.gyro_xout < MIN_RELIABLE_VARIATION || change.gyro_xout > MAX_RELIABLE_VARIATION)
	{
		measurement_data.ave_GyroValue.gyro_xout = measurement_data.old_ave_GyroValue.gyro_xout;
	}
	if(change.gyro_yout < MIN_RELIABLE_VARIATION || change.gyro_yout > MAX_RELIABLE_VARIATION)
	{
		measurement_data.ave_GyroValue.gyro_yout = measurement_data.old_ave_GyroValue.gyro_yout;
	}	
	if(change.gyro_zout < MIN_RELIABLE_VARIATION || change.gyro_zout > MAX_RELIABLE_VARIATION)
	{
		measurement_data.ave_GyroValue.gyro_zout = measurement_data.old_ave_GyroValue.gyro_zout;
	}

    //分别保存三轴角速度原始数据的最大值和最小值
	peak_value.max.gyro_xout = MAX(peak_value.max.gyro_xout , measurement_data.ave_GyroValue.gyro_xout);
	peak_value.min.gyro_xout = MIN(peak_value.min.gyro_xout , measurement_data.ave_GyroValue.gyro_xout);
	peak_value.max.gyro_yout = MAX(peak_value.max.gyro_yout , measurement_data.ave_GyroValue.gyro_yout);
	peak_value.min.gyro_yout = MIN(peak_value.min.gyro_yout , measurement_data.ave_GyroValue.gyro_yout);
	peak_value.max.gyro_zout = MAX(peak_value.max.gyro_zout , measurement_data.ave_GyroValue.gyro_zout);
	peak_value.min.gyro_zout = MIN(peak_value.min.gyro_zout , measurement_data.ave_GyroValue.gyro_zout);

    printf("peak_value.max.gyro_xout: %d, peak_value.min.gyro_xout: %d \n peak_value.max.gyro_yout: %d, peak_value.min.gyro_yout: %d \n peak_value.max.gyro_zout: %d, peak_value.min.gyro_zout: %d\r\n", peak_value.max.gyro_xout, peak_value.min.gyro_xout, peak_value.max.gyro_yout, peak_value.min.gyro_yout, peak_value.max.gyro_zout, peak_value.min.gyro_zout);

}

void which_is_active(void)
{
	gyro_out_t change;
	static gyro_out_t active;        //三个轴的活跃度权重
	static uint8_t active_sample_num; 
 
	Gyro_sample_update();
	active_sample_num ++;
 
	//每隔一段时间，比较一次权重大小，判断最活跃轴
	if(active_sample_num >= ACTIVE_NUM)
	{
		if(active.gyro_xout > active.gyro_yout && active.gyro_xout > active.gyro_zout)
		{
			most_active_axis = ACTIVE_X;
		}
		else if(active.gyro_yout > active.gyro_xout && active.gyro_yout > active.gyro_zout)
		{
			most_active_axis = ACTIVE_Y;
		}
		else if(active.gyro_zout > active.gyro_xout && active.gyro_zout > active.gyro_yout)
		{
			most_active_axis = ACTIVE_Z;
		}
		else
		{
			most_active_axis = ACTIVE_NULL;
		}
        printf("最大轴：%d\r\n", most_active_axis);
		active_sample_num = 0;
		active.gyro_xout = 0;
		active.gyro_yout = 0;
		active.gyro_zout = 0;
	}
 
    //原始数据变化量
	change.gyro_xout = ABS(measurement_data.ave_GyroValue.gyro_xout - measurement_data.old_ave_GyroValue.gyro_xout);
	change.gyro_yout = ABS(measurement_data.ave_GyroValue.gyro_yout - measurement_data.old_ave_GyroValue.gyro_yout);
	change.gyro_zout = ABS(measurement_data.ave_GyroValue.gyro_zout - measurement_data.old_ave_GyroValue.gyro_zout);

 
	//增加三轴活跃度权重
	if(change.gyro_xout > change.gyro_yout && change.gyro_xout > change.gyro_zout)
	{
		active.gyro_xout ++;
	}
	else if(change.gyro_yout > change.gyro_xout && change.gyro_yout > change.gyro_zout)
	{
		active.gyro_yout ++;
	}
	else if(change.gyro_zout > change.gyro_xout && change.gyro_zout > change.gyro_yout)
	{
		active.gyro_zout ++;
	}
}


void detect_step(void)
{
	int16_t mid;
	which_is_active();
	switch(most_active_axis)
	{
		case ACTIVE_NULL:
			break;
		//捕捉原始数据骤增和骤减现象
		case ACTIVE_X:
			mid = (peak_value.max.gyro_xout + peak_value.min.gyro_xout) / 2;
			if(measurement_data.old_ave_GyroValue.gyro_xout < mid && measurement_data.ave_GyroValue.gyro_xout > mid)
			{
				system_data.bpm_Data.steps ++;
			}
			else if(measurement_data.old_ave_GyroValue.gyro_xout > mid && measurement_data.ave_GyroValue.gyro_xout < mid)
			{
				system_data.bpm_Data.steps ++;
			}
			break;
		case ACTIVE_Y:
			mid = (peak_value.max.gyro_yout + peak_value.min.gyro_yout) / 2;
			if(measurement_data.old_ave_GyroValue.gyro_yout < mid && measurement_data.ave_GyroValue.gyro_yout > mid)
			{
				system_data.bpm_Data.steps ++;
			}
			else if(measurement_data.old_ave_GyroValue.gyro_yout > mid && measurement_data.ave_GyroValue.gyro_yout < mid)
			{
				system_data.bpm_Data.steps ++;
			}
			break;	
		case ACTIVE_Z:
			mid = (peak_value.max.gyro_zout + peak_value.min.gyro_zout) / 2;
			if(measurement_data.old_ave_GyroValue.gyro_zout < mid && measurement_data.ave_GyroValue.gyro_zout > mid)
			{
				system_data.bpm_Data.steps ++;
			}
			else if(measurement_data.old_ave_GyroValue.gyro_zout > mid && measurement_data.ave_GyroValue.gyro_zout < mid)
			{
				system_data.bpm_Data.steps ++;
			}
			break;
		default:
			break;
	}
    printf("步数未处理：%d\r\n", system_data.bpm_Data.steps);
}
