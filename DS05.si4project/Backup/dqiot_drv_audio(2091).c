#ifndef __DQIOT_DRV_AUDIO_C__
#define __DQIOT_DRV_AUDIO_C__

#include "OB38A08T2.h"
#include "dqiot_drv_audio.h"
#include "dqiot_drv_timer.h"

//AU_RESET:P1.6 PUSHPULL
//AU_DATA:P0.0 PUSHPULL
//AU_BUSY:P0.1 INPUT

#define AUD_RST_SET	P1_6 = 1
#define AUD_RST_CLR	P1_6 = 0

#define AUD_DATA_SET	P0_0 = 1
#define AUD_DATA_CLR	P0_0 = 0
#define AUD_DATA_TOGGLE	P0_0 = ~P0_0

#define AUD_BUSY	P0_1

#define AUD_RST_INIT	P1M1&=0xBF;P1M0|=0x40
#define AUD_DATA_INIT	P0M1&=0xFE;P0M0|=0x01
#define AUD_BUSY_INIT	P0M1|=0x02;P0M0&=0xFD

#define AUD_RST_DEINIT	P1M1|=0x40;P1M0&=0xBF
#define AUD_DATA_DEINIT	P0M1|=0x01;P0M0&=0xFE


static uint8_t audio_flag=0; // 
static uint8_t audio_section=0,audio_time_count=0;
#define AUDIO_MAX_CACHE_NUM  	20
static uint8_t audio_cache[AUDIO_MAX_CACHE_NUM] = {0};

//static uint8_t audio_play_end_flag = 0;

/*
parameter: 
	none
return :
	none
*/
void dqiot_drv_audio_init(void)
{
	AUD_RST_INIT;
	AUD_DATA_INIT;
	AUD_BUSY_INIT;

	AUD_RST_CLR;
	AUD_DATA_CLR;
	return;
}

/*
parameter: 
	none
return :
	none
*/
void dqiot_drv_audio_deinit(void)
{
	AUD_RST_DEINIT;
	AUD_DATA_DEINIT;

	AUD_RST_CLR;
	AUD_DATA_CLR;
	return;
}


/*
parameter: 
	none
return :
	none
*/
uint8_t dqiot_drv_audio_play(AUD_PLAY_ID aud_id)
{
	unsigned char i = 0;
	if(audio_flag == 0 && AUD_BUSY == 1)
	{	
		audio_flag = 1;
		audio_section = aud_id;
		audio_time_count = 0;
		TIMER0_Start();
	}
	else
	{
		for(i=0;i<AUDIO_MAX_CACHE_NUM;i++)
		{
			if(audio_cache[i]==0)
				break;
		}
		if(i<AUDIO_MAX_CACHE_NUM)
			audio_cache[i]=aud_id;
	}
		
	return 1;
}

/*
parameter: 
	none
return :
	none
*/
void dqiot_drv_audio_stop(void)
{
	unsigned char i = 0;

	if( audio_flag == 0&&AUD_BUSY == 1)
		return;

	TIMER0_Stop();

	for(i=0;i<AUDIO_MAX_CACHE_NUM;i++)
	{
		audio_cache[i]=0;
	}

	if(audio_time_count>=4)
	{
		audio_section = 0;
		audio_flag = 3;
		audio_time_count = 0;
	}
	else
	{
		audio_section = 0;
		audio_flag = 3;
	}
		
    TIMER0_Start();
	return;
}

/*
parameter: 
	none
return :
	none
*/
uint8_t dqiot_drv_audio_check_busy(void)
{
	return AUD_BUSY;
}

/*
parameter: 
	none
return :
	none
*/
uint8_t dqiot_drv_audio_get_state(void)
{
	return audio_flag;
}

/*
parameter: 
	none
return :
	none
*/
uint8_t dqiot_drv_audio_get_section(void)
{
	return audio_section;
}

/*
parameter: 
	none
return :
	none
*/
//uint8_t dqiot_drv_audio_get_end_flag(void)
//{
//	if(audio_play_end_flag == 1)
//	{
//		audio_play_end_flag = 0;
//		return 1;
//	}
//	return 0;
//}	


/*
parameter: 
	none
return :
	none
*/
void Audio_Select_Handle_in_Timer(void)
{
	if(audio_flag == 1)
	{
		if(audio_time_count == 0)
		{
			AUD_RST_SET;
			AUD_DATA_CLR;
		}
		else if(audio_time_count == 2)
		{
			AUD_RST_CLR;
		}
		else if(audio_time_count >= 4)
		{
			AUD_DATA_TOGGLE;
		}
		audio_time_count ++;

		if(audio_time_count >= (audio_section + 1) * 2 + 4)
		{
			audio_time_count = 0;
			AUD_RST_CLR;
			AUD_DATA_CLR;
			audio_flag = 2;
		}
	}
	else if(audio_flag == 3)
	{
		if(audio_time_count == 0)
		{
			AUD_DATA_CLR;
		}	
		else if(audio_time_count == 1)
		{
			AUD_RST_SET;
		}
		else if(audio_time_count == 3)
		{
			AUD_RST_CLR;
		}
		audio_time_count ++;
		if(audio_time_count >= 4)
		{
			audio_time_count = 0;
			AUD_RST_CLR;
			AUD_DATA_CLR;
 			audio_flag = 2;
		}
		
	}

}

/*
parameter: 
	none
return :
	none
*/
void Audio_timer_event_handler(void)
{
	if((audio_flag == 2)&&(AUD_BUSY == 1))
	{
		//extern void mmi_dq_sys_aud_end(void);
		if(audio_cache[0]==0)
		{
			audio_section = 0;
			TIMER0_Stop();
			//mmi_dq_sys_aud_end();
			//audio_play_end_flag = 1;
			audio_flag = 0;
		}
		else
		{
			char i = 0;
			audio_flag = 1;
			audio_section = audio_cache[0];
			for(i=0;i<AUDIO_MAX_CACHE_NUM-1;i++)
			{
				if(audio_cache[i+1]!=0)
				{
					audio_cache[i]=audio_cache[i+1];
				}
				else
					break;
			}
			audio_cache[i]=0;
			audio_time_count = 0;
		}
	}
	else
		Audio_Select_Handle_in_Timer();
}


#endif//__DQIOT_DRV_AUDIO_C__

