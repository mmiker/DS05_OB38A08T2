#ifndef __DQIOT_DRV_LED_H__
#define __DQIOT_DRV_LED_H__


/*
parameter: 
	none
return :
	none
*/
void dqiot_drv_signal_led_init(void);

/*
parameter: 
	none
return :
	none
*/
void dqiot_drv_signal_led_on(unsigned char led);

/*
parameter: 
	none
return :
	none
*/
void dqiot_drv_signal_led_off(unsigned char led);

/*
parameter: 
	none
return :
	none
*/
void dqiot_drv_signal_led_toggle(unsigned char led);

#endif
