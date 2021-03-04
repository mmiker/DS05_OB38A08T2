#ifndef __DQIOT_DRV_FP_C__
#define __DQIOT_DRV_FP_C__

#include "OB38A08T2.h"
#include "dqiot_drv_fp.h"
#include "UART0.h"
#include "Timer.h"
	
//FP_INT:P0.3 INPUT
#define FP_INT P0_3
	
#define FP_INT_INIT P0M1|=0x08;P0M0&=0xF7

/*
parameter: 
	none
return :
	none
*/
void dqiot_drv_fp_init(void)
{
	FP_INT_INIT;		
	return;
}

/*
parameter: 
	none
return :
	none
*/
void dqiot_drv_fp_wake_up(void)
{
    //gpio_bit_reset(FP_PWR_PORT,FP_PWR_PIN);  
	P2M1|=0x40;P2M0|=0x40;
	P2M1|=0x20;P2M0|=0x20;
	return;
}

/*
parameter: 
	none
return :
	none
*/
void dqiot_drv_fp_enter_sleep(void)
{
   // gpio_bit_set(FP_PWR_PORT,FP_PWR_PIN);
	P2M1|=0x40;P2M0&=0xBF;
	P2M1|=0x20;P2M0&=0xDF;
	P2_6 = 0;
	P2_5 = 0;
	return;
}

/*
parameter: 
	none
return :
	none
*/
unsigned char dqiot_drv_fp_get_int_state(void)
{
	return FP_INT;
}

#endif//__DQIOT_DRV_FP_C__

