#include "OB38A08T2.h"
#include "I2C.h"

//SDA: P3.0  OPENDRAIN MODE
//SCL: P2.3  OPENDRAIN MODE
#define SDA_SET	P3_0 = 1
#define SDA_CLR	P3_0 = 0
#define SDA P3_0

#define SCL_SET	P2_3 = 1
#define SCL_CLR	P2_3 = 0

#define SDA_INIT	P3M1|=0x01;P3M0|=0x01
#define SCL_INIT	P2M1|=0x08;P2M0|=0x08

#define NACK    1
#define ACK     0

#define DELAY  delay_us()

void delay_us(void)
{
	unsigned char i;
	for(i=0;i<10;i++);
}

void I2C_Master_Init(void)
{
	SDA_INIT;
	SCL_INIT;

	SDA_SET;
	SCL_SET;
}

void iic_master_start(void)
{
	SDA_SET;
	SCL_SET;
	DELAY;
	SDA_CLR;
	DELAY;
	SCL_CLR;
}

void iic_master_stop(void)
{
	SCL_CLR;
	SDA_CLR;
	DELAY;
	SCL_SET;
	DELAY;
	SDA_SET;
}


unsigned char iic_master_read_byte(unsigned char ack)
{
	unsigned char i;
	unsigned char buffer = 0;
	SCL_CLR;
	SDA_SET;
	for(i=0;i<8;i++)
	{
		DELAY;
		SCL_SET;
		DELAY;
		buffer <<= 1;
		if(SDA)
			buffer |= 0x01;	
		SCL_CLR;
	}

	if(ack)
		SDA_SET;
	else
		SDA_CLR;	
	DELAY;
	SCL_SET;
	DELAY;
	SCL_CLR;

	return buffer;
}

unsigned char iic_master_write_byte(unsigned char send)
{
	unsigned char i;
	unsigned char ack;

	SCL_CLR;
	for(i=0;i<8;i++)
	{
		if(send & 0x80)
			SDA_SET;
		else
			SDA_CLR;
		send <<= 1;
		DELAY;
		SCL_SET;
		DELAY;
		SCL_CLR;
	}

	SDA_SET;
	DELAY;
	SCL_SET;
	DELAY;
	ack = SDA;
	SCL_CLR;

	return ack;
}

void I2C_Master_Read_Data(unsigned char addr, unsigned char * receivedata, unsigned char receivelen)
{
	unsigned char i;
	iic_master_start();
	iic_master_write_byte(addr|0x01);
	for(i=0;i<receivelen-1;i++)
	{
		receivedata[i] = iic_master_read_byte(ACK);
	}
	receivedata[i] = iic_master_read_byte(NACK);
	iic_master_stop();
}

void I2C_Master_Write_Data(unsigned char addr, unsigned char * senddata, unsigned char sendlen)
{
	unsigned char i;
	iic_master_start();
	iic_master_write_byte(addr);
	for(i=0;i<sendlen;i++)
	{
		iic_master_write_byte(senddata[i]);
	}
	iic_master_stop();
}

