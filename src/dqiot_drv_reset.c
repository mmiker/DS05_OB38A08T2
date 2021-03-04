#ifndef __DQIOT_DRV_RESET_C__
#define __DQIOT_DRV_RESET_C__

#include "dqiot_drv.h"

#define KEY1_INIT P1M1|=0x80;P1M0&=0x7F
#define KEY2_ADC_INIT P1M1|=0x04;P1M0&=0xFB

#define KEY1 P1_7

/*
parameter: 
	none
return :
	none
*/
void dqiot_drv_reset_init(void)
{
	KEY1_INIT;
	KEY2_ADC_INIT;
	return;
}

/*
parameter: 
	none
return :
	none
*/
unsigned char dqiot_drv_get_reset_pin(void)
{
	return KEY1;//gpio_bit_get(RESET_PORT, RESET_PIN);
}

#endif


