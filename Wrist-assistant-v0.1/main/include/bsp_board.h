
#define sd_file 0


#define GPIO_LCD_BL     (GPIO_NUM_45)
#define GPIO_LCD_DC     (GPIO_NUM_38)
#define GPIO_LCD_RST    (GPIO_NUM_0)
#define GPIO_LCD_CS     (GPIO_NUM_39)
#define GPIO_LCD_DIN    (GPIO_NUM_41)
#define GPIO_LCD_DOUT   (GPIO_NUM_NC)
#define GPIO_LCD_CLK    (GPIO_NUM_40)


#define GPIO_SD_SPI_CS      (GPIO_NUM_34)
#define GPIO_SD_SPI_MISO    (GPIO_NUM_37)
#define GPIO_SD_SPI_MOSI    (GPIO_NUM_35)
#define GPIO_SD_SPI_SCLK    (GPIO_NUM_36)


#define I2C_PORT_NUM_TP     (0)
#define GPIO_TP_I2C_SCL     (GPIO_NUM_48)
#define GPIO_TP_I2C_SDA     (GPIO_NUM_47)

#define I2C_PORT_NUM_BPM     (1)
#define GPIO_BPM_I2C_SCL     (GPIO_NUM_12)
#define GPIO_BPM_I2C_SDA     (GPIO_NUM_13)
#define I2C_FRQ 100000


#define GPIO_LED_R      (GPIO_NUM_5)
#define GPIO_LED_G      (GPIO_NUM_6)

// MPU6050
#define MPU6050_I2C_PORT_NUM (1)
#define MPU6050_I2C_SDA    (GPIO_NUM_19)
#define MPU6050_I2C_SCL   (GPIO_NUM_18)
#define MPU6050_I2C_FREQ 400000
#define MPU6050_ADDR 0x68  //器件地址： b110100(AD0) 

#define WRITE_BIT I2C_MASTER_WRITE  //I2C master write 
#define READ_BIT I2C_MASTER_READ    //I2C master read 
#define ACK_CHECK_EN 0x1            //I2C master will check ack from slave
#define ACK_CHECK_DIS 0x0           //I2C master will not check ack from slave 
#define ACK_VAL 0x0                 //I2C ack value 
#define NACK_VAL 0x1                //I2C nack value    
