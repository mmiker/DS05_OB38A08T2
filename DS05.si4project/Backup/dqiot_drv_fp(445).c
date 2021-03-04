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
	UART0_init();
	return;
}

/*
parameter: 
	none
return :
	none
*/
void dqiot_drv_fp_poweron(void)
{
    //gpio_bit_reset(FP_PWR_PORT,FP_PWR_PIN);
	return;
}

/*
parameter: 
	none
return :
	none
*/
void dqiot_drv_fp_poweroff(void)
{
   // gpio_bit_set(FP_PWR_PORT,FP_PWR_PIN);
	return;
}


#endif//__DQIOT_DRV_FP_C__

