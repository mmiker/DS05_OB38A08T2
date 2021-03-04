#ifndef __MMI_AUD_C__
#define __MMI_AUD_C__

#include "mmi_audio.h"
#include "dqiot_drv_audio.h"
#include "mmi_com.h"

#ifdef __LOCK_AUDIO_SUPPORT__
unsigned char audio_play_state = 0;
/*
parameter: 
	none
return :
	none
*/
void mmi_dq_aud_init(void)
{
	dqiot_drv_audio_init();
}

/*
parameter: 
	none
return :
	none
*/
void mmi_dq_set_aud_state(unsigned char state)
{
	audio_play_state = state;
}

/*
parameter: 
	none
return :
	none
*/
void mmi_dq_aud_play_with_id(AUD_PLAY_ID aud_id)
{
	if(mmi_dq_fs_get_pro_sound()!=0 || audio_play_state != 0)
		dqiot_drv_audio_play(aud_id);
	
	return;
}

/*
parameter: 
	none
return :
	none
*/
void mmi_dq_aud_play_key_tone(void)
{
	mmi_dq_aud_stop();
	mmi_dq_aud_play_with_id(AUD_ID_PRO_AUDIO);
}
/*
parameter: 
	none
return :
	none
*/
void mmi_dq_aud_stop(void)
{
	dqiot_drv_audio_stop();
}

/*
parameter: 
	none
return :
	none
*/
unsigned char mmi_dq_aud_get_state(void)
{
	return dqiot_drv_audio_get_state();
}

/*
parameter: 
	none
return :
	none
*/
unsigned char mmi_dq_aud_get_end_flag(void)
{
	return dqiot_drv_audio_get_end_flag();
}
#endif
#endif//__MMI_AUD_C__
