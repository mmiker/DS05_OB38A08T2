

#include "dqiot_drv.h"


//LDO_EN:P1.3 PUSHPULL
//VIB_INT:P1.4 INPUT
//KEY1:P1.7 INPUT
//KEY_2/ADC:P1.2 INPUT
#define LDO_EN_INIT P1M1&=0xF7;P1M0|=0x08
#define VIB_INT_INIT P1M1|=0x10;P1M0&=0xEF
#define KEY1_INIT P1M1|=0x80;P1M0&=0x7F
#define KEY2_ADC_INIT P1M1|=0x04;P1M0&=0xFB

#define LDO_EN_ON P1_3 = 1
#define LDO_EN_OFF P1_3 = 0


//1:enable, 0:disable
#define g_SleepCtrl     (*((unsigned char volatile xdata*)0x30D))

/*
parameter: 
	none
return :
	none
*/
void dqiot_drv_init(void)
{
	TIMER_Init();
	UART0_init();
	I2C_Master_Init();

	LDO_EN_INIT;
	VIB_INT_INIT;
	KEY1_INIT;
	KEY2_ADC_INIT;

	LDO_EN_ON;

	g_SleepCtrl = 0;
}

/*
parameter: 
	none
return :
	none
*/
void dqiot_drv_enter_sleep(void)
{
	LDO_EN_OFF;

	UART0_deinit();
	
	dqiot_drv_fp_enter_sleep();
	dqiot_drv_audio_deinit();
	g_SleepCtrl = 1;
}

/*
parameter: 
	none
return :
	none
*/
void dqiot_drv_wake_up(void)
{
	g_SleepCtrl = 0;
	dqiot_drv_fp_wake_up();
	dqiot_drv_audio_init();

	UART0_init();
	
	LDO_EN_ON;

}


void INT1_ISR(void) interrupt d_INT1_Vector
{
    if(P2_6 == 0)
    {
	//	Led_Off(LED_TYPE_2);
    }
	else
	{
	//	Led_On(LED_TYPE_2);
	}
}

void INT1_Init(void)
{
	P2M1|=0x40;P2M0&=0xBF;
	P2_6 = 0;

	IT1 = 1;
	ENHIT |= 0x08;
	INTDEG |= 0x04;
	EX1 = 1;
}
