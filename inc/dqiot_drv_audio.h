#ifndef __DQIOT_DRV_AUDIO_H__
#define __DQIOT_DRV_AUDIO_H__


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
void dqiot_drv_audio_deinit(void);

/*
parameter: 
	none
return :
	none
*/
unsigned char dqiot_drv_audio_play(unsigned char aud_id);

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
unsigned char dqiot_drv_audio_check_busy(void);

/*
parameter: 
	none
return :
	none
*/
unsigned char dqiot_drv_audio_get_state(void);

/*
parameter: 
	none
return :
	none
*/
unsigned char dqiot_drv_audio_get_section(void);

/*
parameter: 
	none
return :
	none
*/
//unsigned char dqiot_drv_audio_get_end_flag(void);

#endif//__DQIOT_DRV_AUDIO_H__

