#ifndef __BASE_MMI_AUD_C__
#define __BASE_MMI_AUD_C__

#include "mmi_sys.h"
#include "mmi_aud.h"
#include "nrf_log.h"
#include "mmi_feature.h"
#include "dqiot_project.h"
#include "mmi_fs.h"
#include "dqiot_audio.h"


#ifdef __LOCK_AUDIO_SUPPORT__
uint8 audio_play_state = 0;
#ifdef __AUD_PLAY_BY_ARR__

const unsigned char aud_play_arr[] = 
{
	AUD_BASE_ID_INPUT_68_PWD,AUD_BASE_ID_INPUT_END,0,		//AUD_ID_INPUT_68_PWD = 0,//璇疯緭鍏?-8浣嶅瘑鐮侊紝鎸?閿