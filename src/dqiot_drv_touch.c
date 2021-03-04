#ifndef __DQIOT_DRV_TOUCH_C__
#define __DQIOT_DRV_TOUCH_C__

#include "OB38A08T2.h"
#include "dqiot_drv_touch.h"


unsigned char bdata ucTkStatusPort0;
unsigned char bdata ucTkStatusPort1;

sbit bTk00Flag  = ucTkStatusPort0^0;
sbit bTk01Flag  = ucTkStatusPort0^1;
sbit bTk02Flag  = ucTkStatusPort0^2;
sbit bTk03Flag  = ucTkStatusPort0^3;
sbit bTk04Flag  = ucTkStatusPort0^4;
sbit bTk05Flag  = ucTkStatusPort0^5;
sbit bTk06Flag  = ucTkStatusPort0^6;
sbit bTk07Flag  = ucTkStatusPort0^7;

sbit bTk08Flag  = ucTkStatusPort1^0;
sbit bTk09Flag  = ucTkStatusPort1^1;
sbit bTk10Flag  = ucTkStatusPort1^2;
sbit bTk11Flag  = ucTkStatusPort1^3;
sbit bTk12Flag  = ucTkStatusPort1^4;
sbit bTk13Flag  = ucTkStatusPort1^5;
sbit bTk14Flag  = ucTkStatusPort1^6;
sbit bTk15Flag  = ucTkStatusPort1^7;

unsigned char g_ucTkNumber = 0xFF;


void TOUCH_ISR(void) interrupt d_TK_Vector using 1
{
    EA = 0;
    ((void(code*)(void))0x2011)();      //Touch ISR Function
    EA = 1;
}


/*
parameter: 
	none
return :
	none
*/
static void dqiot_drv_touch_normal(void)
{
	((unsigned char(code*)(void))0x2008)();  //Touch Normal Run
	ucTkStatusPort0 = TKSTATUS0;
	ucTkStatusPort1 = TKSTATUS1;
	
	if (ucTkStatusPort0 == 0 && ucTkStatusPort1 == 0)
	{
		g_ucTkNumber = 0xFF;
	}
	else if (g_ucTkNumber == 0xFF)
	{
		if (bTk00Flag == 1) 			 //Check TK0
			g_ucTkNumber = 0;
		//else if (bTk01Flag == 1)		 //Check TK1
		//	g_ucTkNumber = 1;
		else if (bTk02Flag == 1)		 //Check TK2
			g_ucTkNumber = 1;
		else if (bTk03Flag == 1)		 //Check TK3
			g_ucTkNumber = 2;
		else if (bTk04Flag == 1)		 //Check TK4
			g_ucTkNumber = 3;
		else if (bTk05Flag == 1)		 //Check TK5
			g_ucTkNumber = 4;
		else if (bTk06Flag == 1)		 //Check TK6
			g_ucTkNumber = 5;
		else if (bTk07Flag == 1)		 //Check TK7
			g_ucTkNumber = 6;
		//else if (bTk08Flag == 1)		 //Check TK8
		//	g_ucTkNumber = 8;
		//else if (bTk09Flag == 1)		 //Check TK9
		//	g_ucTkNumber = 9;
		//else if (bTk10Flag == 1)		 //Check TK10
		//	g_ucTkNumber = 10;
		else if (bTk11Flag == 1)		 //Check TK11
			g_ucTkNumber = 7;
		else if (bTk12Flag == 1)		 //Check TK12
			g_ucTkNumber = 8;
		else if (bTk13Flag == 1)		 //Check TK13
			g_ucTkNumber = 9;
		else if (bTk14Flag == 1)		 //Check TK14
			g_ucTkNumber = 10;
		else if (bTk15Flag == 1)		 //Check TK15
			g_ucTkNumber = 11;
	}
}

/*
parameter: 
	none
return :
	none
*/
void dqiot_drv_touch_init(void)
{
    ((void(code*)(void))0x2005)();                   //Touch initial
}

/*
parameter: 
	none
return :
	none
*/
uint8_t dqiot_drv_touch_check(void)
{
	dqiot_drv_touch_normal();
	if (g_ucTkNumber == 0xFF)
		return 0;
	else
		return 1;
}

/*
parameter: 
	none
return :
	none
*/
uint8_t dqiot_drv_touch_work(void)
{
	dqiot_drv_touch_normal();
	
	return g_ucTkNumber;
}

/*
parameter: 
	none
return :
	none
*/
uint8_t dqiot_drv_get_touch_flag(void)
{
	return (g_ucTkNumber == 0xFF)?0:1;
}

/*
parameter: 
	none
return :
	none
*/
uint8_t dqiot_drv_get_touch_value(void)
{
	return g_ucTkNumber;
}

#endif
