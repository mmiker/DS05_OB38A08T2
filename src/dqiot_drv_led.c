#ifndef __DQIOT_DRV_LED_C__
#define __DQIOT_DRV_LED_C__

#include "dqiot_drv.h"
#include "dqiot_drv_led.h"

/*
parameter: 
	none
return :
	none
*/
void dqiot_drv_signal_led_init(void)
{
	TKRUNTIME = 28;
	dCOM0 = 1;
	COMEN  = 0x01;
	SEGEN0 = 0x00;
	SEGEN1 = 0x00;
	LEDCLK = 35;
	LEDCON = 0x90;
}

/*
parameter: 
	none
return :
	none
*/
void dqiot_drv_signal_led_on(unsigned char led)
{
	SEGEN0 |= led;
}

/*
parameter: 
	none
return :
	none
*/
void dqiot_drv_signal_led_off(unsigned char led)
{
	SEGEN0 &= ~led;
}

/*
parameter: 
	none
return :
	none
*/
void dqiot_drv_signal_led_toggle(unsigned char led)
{
	if(SEGEN0&led)
		SEGEN0 &= ~led;
	else
		SEGEN0 |= led;
}

#endif
