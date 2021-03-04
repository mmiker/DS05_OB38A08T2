//#include "dqiot_project.h"
//#ifdef __PREIPHERAL_CONTROL_SUPPORT__
#include "mmi_feature.h"
#include "I2C.h"
#include "dqiot_control.h"
#include "Timer.h"

unsigned char CONTROL_Write_Byte(unsigned char *send,unsigned char send_len)
{   
	I2C_Master_Write_Data(CONTROL_ADDR, send, send_len, 1);
	return 1;
}


unsigned char CONTROL_ReadDatas(unsigned char *send,unsigned char send_len,unsigned char *Buf,unsigned char len) 
{
	int i;
	for (i = 0; i < len; i++) 
	{
		Buf[i] = 0;
	}
	if(send_len>0)
	{
		// Write: register address we want to start reading from
		I2C_Master_Write_Data(CONTROL_ADDR, send, send_len, 0);
		// Read: the number of bytes requested.
		I2C_Master_Read_Data(CONTROL_ADDR, Buf, len);
	}
	else
	{
	  	I2C_Master_Read_Data(CONTROL_ADDR, Buf, len);
	}
	return 1;
}


unsigned char control_open_light(void)
{
	unsigned char data[2];
	data[0] = CONTROL_LIGHT;
	data[1] = CONTROL_OPEN;
	if(CONTROL_Write_Byte(data,2) == 0)
		return 1;
	else
		return 0;
}

unsigned char control_closed_light(void)
{
	unsigned char data[2];
	data[0] = CONTROL_LIGHT;
	data[1] = CONTROL_CLOSED;
	if(CONTROL_Write_Byte(data,2) == 0)
		return 1;
	else
		return 0;
}


unsigned char control_open_motor(void)
{	
	unsigned char data[2];
	data[0] = CONTROL_MOTOR;
	data[1] = CONTROL_OPEN;
	if(CONTROL_Write_Byte(data,2) == 0)
		return 1;
	else
		return 0;
}

unsigned char control_closed_motor(void)
{	
	unsigned char data[2];
	data[0] = CONTROL_MOTOR;
	data[1] = CONTROL_CLOSED;
	if(CONTROL_Write_Byte(data,2) == 0)
		return 1;
	else
		return 0;
}


unsigned char control_open_solenoid(void)
{	
	unsigned char data[2];
	data[0] = CONTROL_SOLENOID;
	data[1] = CONTROL_OPEN;
	if(CONTROL_Write_Byte(data,2) == 0)
		return 1;
	else
		return 0;
}

unsigned char control_closed_solenoid(void)
{	
	unsigned char data[2];
	data[0] = CONTROL_SOLENOID;
	data[1] = CONTROL_CLOSED;
	if(CONTROL_Write_Byte(data,2) == 0)
		return 1;
	else
		return 0;
}


unsigned char control_open_alarm(void)
{	
	unsigned char data[2];
	data[0] = CONTROL_ALARM;
	data[1] = CONTROL_OPEN;
	if(CONTROL_Write_Byte(data,2) == 0)
		return 1;
	else
		return 0;
}

unsigned char control_closed_alarm(void)
{	
	unsigned char data[2];
	data[0] = CONTROL_ALARM;
	data[1] = CONTROL_CLOSED;
	if(CONTROL_Write_Byte(data,2) == 0)
		return 1;
	else
		return 0;
}

unsigned char control_get_close_state(void)
{
	unsigned char data[2];
	unsigned char data_2[2] = {0};
	data[0] = CONTROL_SEARCH;
	data[1] = CONTROL_OPEN;
	CONTROL_Write_Byte(data,2);
	TIMER1_Delay(10);
	CONTROL_ReadDatas(data,0,data_2,2);
	if(data_2[0]=='M'&&data_2[1]=='O')
		return 1;
	else
		return 0;
}

unsigned char control_set_close(void)
{
	unsigned char data[2];
	data[0] = CONTROL_SEARCH;
	data[1] = CONTROL_CLOSED;
	if(CONTROL_Write_Byte(data,2) == 0)
		return 1;
	else
		return 0;
}

void control_wake_up(void)
{	
	unsigned char data[2];
	data[0] = CONTROL_WAKEUP;
	data[1] = CONTROL_OPEN;
	CONTROL_Write_Byte(data,2);
 }


//#endif


