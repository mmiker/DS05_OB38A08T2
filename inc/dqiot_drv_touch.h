#ifndef __DQIOT_DRV_TOUCH_H__
#define __DQIOT_DRV_TOUCH_H__


/*
parameter: 
	none
return :
	none
*/
void dqiot_drv_touch_init(void);

/*
parameter: 
	none
return :
	none
*/
uint8_t dqiot_drv_touch_check(void);

/*
parameter: 
	none
return :
	none
*/
uint8_t dqiot_drv_touch_work(void);

/*
parameter: 
	none
return :
	none
*/
uint8_t dqiot_drv_get_touch_flag(void);

/*
parameter: 
	none
return :
	none
*/
uint8_t dqiot_drv_get_touch_value(void);


#endif
