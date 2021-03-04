#ifndef __DQIOT_DRV_H__
#define __DQIOT_DRV_H__

#include "OB38A08T2.h"

#include "I2C.h"
#include "EEPROM.h"
#include "Timer.h"
#include "UART0.h"

#include "dqiot_drv_audio.h"
#include "dqiot_drv_control.h"
#include "dqiot_drv_fp.h"
#include "dqiot_fp_sy.h"
#include "dqiot_drv_led.h"
#include "dqiot_drv_touch.h"
#include "dqiot_drv_wifi.h"
#include "dqiot_drv_reset.h"

/*
parameter: 
	none
return :
	none
*/
void dqiot_drv_init(void);

/*
parameter: 
	none
return :
	none
*/
void dqiot_drv_enter_sleep(void);

/*
parameter: 
	none
return :
	none
*/
void dqiot_drv_wake_up(void);

#endif
