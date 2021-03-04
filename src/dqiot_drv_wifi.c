#ifndef __DQIOT_DRV_WIFI_H__
#define __DQIOT_DRV_WIFI_H__
#include "dqiot_drv_wifi.h"
#include "mmi_feature.h"
#include "I2C.h"
#include "delay.h"

/*
parameter: 
	none
return :
	none
*/
uint8_t UH010_ReadDatas(uint8_t *send,uint8_t send_len,uint8_t *Buf,uint8_t len) 
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
	return 0;
}

/*
parameter: 
	none
return :
	none
*/
unsigned char UH010_Write_Byte(uint8_t *send,uint8_t send_len)
{
	I2C_Master_Write_Data(CONTROL_ADDR, send, send_len, 1);
	return 0;
}

/*
parameter: 
	none
return :
	none
*/
uint8_t wifi_net_connect_send(void)
{
	uint8_t wifi_data[2];
	wifi_data[0] = WIFI_CMD_NET_CON;
	wifi_data[1] = 100;
	if(UH010_Write_Byte(wifi_data,2) == 0)
		return 1;
	else
		return 0;
}

/*
parameter: 
	none
return :
	none
*/
uint8_t wifi_net_connect_state(void)
{
	uint8_t wifi_data[2];
	uint8_t data_2[2] = {0};
	wifi_data[0] = WIFI_CMD_NET_STATE;
	wifi_data[1] = 100;
	UH010_Write_Byte(wifi_data,2);
	delay_ms(10);
	UH010_ReadDatas(wifi_data,0,data_2,2);
	if(data_2[0]=='I'&&data_2[1]=='O')
		return 1;
	else
		return 0;
	
}

/*
parameter: 
	none
return :
	none
*/
uint8_t wifi_open_ask(void)
{
	uint8_t wifi_data[2];
	wifi_data[0] = WIFI_CMD_WF_OPEN_ASK;
	wifi_data[1] = 100;
	if(UH010_Write_Byte(wifi_data,2) == 0)
		return 1;
	else
		return 0;
}

/*
parameter: 
	none
return :
	none
*/
uint8_t wifi_open_reply_get(void)
{
	uint8_t wifi_data[2];
	uint8_t data_2[2] = {0};
	wifi_data[0] = WIFI_CMD_WF_OPEN_REPLY;
	wifi_data[1] = 100;
	UH010_Write_Byte(wifi_data,2);
	delay_ms(10);
	UH010_ReadDatas(wifi_data,0,data_2,2);
	if(data_2[0]=='K'&&data_2[1]=='O')
		return 1;
	else if(data_2[0]=='K'&&data_2[1]=='E')
		return 2;
	else if(data_2[0]=='K'&&data_2[1]=='K')
		return 3;
	else
		return 0;


}

/*
parameter: 
	none
return :
	none
*/
void wifi_wake_up(void)
{

	uint8_t wifi_data[2];
	wifi_data[0] = WIFI_CMD_WAKEUP;
	wifi_data[1] = 100;
	UH010_Write_Byte(wifi_data,2);
}

/*
parameter: 
	none
return :
	none
*/
void wifi_sleep_mode(void)
{
	uint8_t wifi_data[2];
	wifi_data[0] = WIFI_CMD_SLEEP;
	wifi_data[1] = 100;
	UH010_Write_Byte(wifi_data,2);
}

/*
parameter: 
	none
return :
	none
*/
void wifi_add_password(void)
{
	uint8_t wifi_data[2];
	wifi_data[0] = WIFI_CMD_ADD_PW;
	wifi_data[1] = 100;
	UH010_Write_Byte(wifi_data,2);
}

/*
parameter: 
	none
return :
	none
*/
void wifi_del_password(void)
{
	uint8_t wifi_data[2];
	wifi_data[0] = WIFI_CMD_DEL_PW;
	wifi_data[1] = 100;
	UH010_Write_Byte(wifi_data,2);
}

/*
parameter: 
	none
return :
	none
*/
void wifi_add_fp(void)
{
	uint8_t wifi_data[2];
	wifi_data[0] = WIFI_CMD_ADD_FP;
	wifi_data[1] = 100;
	UH010_Write_Byte(wifi_data,2);
}

/*
parameter: 
	none
return :
	none
*/
void wifi_del_fp(void)
{
	uint8_t wifi_data[2];
	wifi_data[0] = WIFI_CMD_DEL_FP;
	wifi_data[1] = 100;
	UH010_Write_Byte(wifi_data,2);
}

/*
parameter: 
	none
return :
	none
*/
void wifi_open_by_wifi(void)
{
	uint8_t wifi_data[2];
	wifi_data[0] = WIFI_CMD_WF_OPEN;
	wifi_data[1] = 100;
	UH010_Write_Byte(wifi_data,2);
}


/*
parameter: 
	none
return :
	none
*/
void wifi_open_by_password(void)
{
	uint8_t wifi_data[2];
	wifi_data[0] = WIFI_CMD_PW_OPEN;
	wifi_data[1] = 100;
	UH010_Write_Byte(wifi_data,2);
}

/*
parameter: 
	none
return :
	none
*/
void wifi_open_by_rfid(void)
{
	uint8_t wifi_data[2];
	wifi_data[0] = WIFI_CMD_RF_OPEN;
	wifi_data[1] = 100;
	UH010_Write_Byte(wifi_data,2);
}


/*
parameter: 
	none
return :
	none
*/
void wifi_open_by_fp(void)
{
	uint8_t wifi_data[2];
	wifi_data[0] = WIFI_CMD_FP_OPEN;
	wifi_data[1] = 100;
	UH010_Write_Byte(wifi_data,2);
}

/*
parameter: 
	none
return :
	none
*/
void wifi_open_by_key(void)
{
	uint8_t wifi_data[2];
	wifi_data[0] = WIFI_CMD_KEY_OPEN;
	wifi_data[1] = 100;
	UH010_Write_Byte(wifi_data,2);
}

/*
parameter: 
	none
return :
	none
*/
void wifi_door_close(void)
{
	uint8_t wifi_data[2];
	wifi_data[0] = WIFI_CMD_CLOSE;
	wifi_data[1] = 100;
	UH010_Write_Byte(wifi_data,2);
}

/*
parameter: 
	none
return :
	none
*/
void wifi_via_alarm(void)
{
	uint8_t wifi_data[2];
	wifi_data[0] = WIFI_CMD_VIA_ALARM;
	wifi_data[1] = 100;
	UH010_Write_Byte(wifi_data,2);
}

/*
parameter: 
	none
return :
	none
*/
void wifi_pw_alarm(void)
{
	uint8_t wifi_data[2];
	wifi_data[0] = WIFI_CMD_PW_ALARM;
	wifi_data[1] = 100;
	UH010_Write_Byte(wifi_data,2);
}

/*
parameter: 
	none
return :
	none
*/
void wifi_fp_alarm(void)
{
	uint8_t wifi_data[2];
	wifi_data[0] = WIFI_CMD_FP_ALARM;
	wifi_data[1] = 100;
	UH010_Write_Byte(wifi_data,2);
}

/*
parameter: 
	none
return :
	none
*/
void wifi_rf_alarm(void)
{
	uint8_t wifi_data[2];
	wifi_data[0] = WIFI_CMD_RF_ALARM;
	wifi_data[1] = 100;
	UH010_Write_Byte(wifi_data,2);
}


/*
parameter: 
	none
return :
	none
*/
void wifi_lowpower_alarm(void)
{
	uint8_t wifi_data[2];
	wifi_data[0] = WIFI_CMD_LOWPOWER_ALARM;
	wifi_data[1] = 100;
	UH010_Write_Byte(wifi_data,2);
}


void wifi_send_fp_110(void){
	uint8_t wifi_data[2];
	wifi_data[0] = WIFI_CMD_WF_OPEN_FP_110;
	wifi_data[1] = 100;
	UH010_Write_Byte(wifi_data,2);

}

void wifi_send_pwd_110(void){
	uint8_t wifi_data[2];
	wifi_data[0] = WIFI_CMD_WF_OPEN_PSW_110;
	wifi_data[1] = 100;
	UH010_Write_Byte(wifi_data,2);

}

void wifi_set_110(void){
	uint8_t wifi_data[2];
	wifi_data[0] = WIFI_CMD_WF_SET_110;
	wifi_data[1] = 100;
	UH010_Write_Byte(wifi_data,2);
}


#endif




