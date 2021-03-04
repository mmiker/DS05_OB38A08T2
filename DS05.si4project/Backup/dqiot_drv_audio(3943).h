#ifndef __DQIOT_DRV_AUDIO_H__
#define __DQIOT_DRV_AUDIO_H__

#include "dqiot_gpio.h"

/*
parameter: 
	none
return :
	none
*/
void dqiot_drv_audio_init(void);

/*
parameter: 
	none
return :
	none
*/
uint8_t dqiot_drv_audio_play(AUD_PLAY_ID aud_id);

/*
parameter: 
	none
return :
	none
*/
void dqiot_drv_audio_stop(void);

/*
parameter: 
	none
return :
	none
*/
uint8_t dqiot_drv_audio_check_busy(void);

/*
parameter: 
	none
return :
	none
*/
uint8_t dqiot_drv_audio_get_state(void);

/*
parameter: 
	none
return :
	none
*/
uint8_t dqiot_drv_audio_get_section(void);

/*
parameter: 
	none
return :
	none
*/
//uint8_t dqiot_drv_audio_get_end_flag(void);

#endif//__DQIOT_DRV_AUDIO_H__

