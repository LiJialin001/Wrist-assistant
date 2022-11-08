#include "myiic.h"

void myiic_start(void)
{
    SDA_H;
    delay_us(5);
    SCL_H;
    delay_us(5);
    SDA_L;
    delay_us(5);
}

void myiic_stop(void)
{
    SDA_L;
    delay_us(5);
    SCL_H;
    delay_us(5);
    SDA_H;
    delay_us(5);
}

void waitack(void)
{
    int j;
    uint8_t a;
    SDA_IN;    
    for (j=0; j<1000; j++) {
        a = SDAX;
        if (a == 0)
            break;
    }
    
    if (j >= 1000) {
        //TODO: What's the meaning of waitSta
        //waitSta = 0x0a;
    }
    
    SCL_H;
    delay_us(5);
    SCL_L;
    delay_us(5);
    SDA_OUT;   
}

void noack(void)
{
    SDA_H;
    delay_us(5);
    SCL_H;
    delay_us(5);
    SCL_L;
    delay_us(5);
    SDA_L;
    delay_us(5);
}

void ack(void)
{
    SDA_L;
    delay_us(5);
    SCL_H;
    delay_us(5);
    SCL_L;
    delay_us(5);
    SDA_H;
    delay_us(5);
}

void write8bit(uint8_t data)
{
    int i;
    SCL_L;
    delay_us(5);

    for (i = 0; i < 8; i++)
    {
        if ((data<<i) & 0x80)
            SDA_H;
        else
            SDA_L;
        delay_us(5);

        SCL_H;
        delay_us(5);
        
        SCL_L;
        delay_us(5);
    }
    SCL_L;
    delay_us(5);

    SDA_H;  
    delay_us(5);
}

uint8_t read8bit(void)
{
    int temp ;
    uint8_t rbyte = 0x00;

    SDA_IN;    
    for (temp=0; temp<8; temp++) {
        rbyte = rbyte <<1;
        SCL_H;
        delay_us(5);
        if (SDAX)
            rbyte = rbyte | 0x01;
        SCL_L;
        delay_us(5);
    }
    SDA_OUT;   
    SCL_L;
    SDA_H;
    delay_us(5);
    
    return rbyte;
}

void writebyte(uint8_t addr, uint8_t dat)
{
    myiic_start();

    write8bit(I2C_ADDRESS);
    delay_us(50);
    waitack();
    delay_us(50);
    write8bit(addr);
    delay_us(50);
    waitack();
    delay_us(50);

    write8bit(dat);
    delay_us(50);
    waitack();
    delay_us(50);

    myiic_stop();
}

uint8_t readbyte(uint8_t addr)
{
    uint8_t byte;

    myiic_start();

    write8bit(I2C_ADDRESS);
    delay_us(50);
    waitack();
    delay_us(50);
    write8bit(addr);
    delay_us(50);
    waitack();
    delay_us(50);

    myiic_start();
    write8bit(I2C_ADDRESS_R);
    delay_us(50);
    waitack();
    delay_us(50);
    
    byte = read8bit();
    delay_us(50);
    noack();
    delay_us(50);
    
    myiic_stop();

    return byte;
}

void write_register(uint8_t addr, uint8_t dat)
{
    do {
        writebyte(addr, dat);
        delay_us(50);
    }while(dat != readbyte(addr));
}