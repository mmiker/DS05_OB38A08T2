#ifndef __MMI_FEATURE_H__
#define __MMI_FEATURE_H__

#include "dq_project.h"

#ifdef __DQ_PROJECT_DS06__
	//#define __LOCK_RFID_CARD_SUPPORT__
	#define __LOCK_AUDIO_SUPPORT__
	#define __LOCK_KEY_SUPPORT__
	//ָ�Ƶ�ǰʹ��֧�ָ��ǣ���ָ�Ʋ�֧�ָ��Ǽǵ���110�͹���Աָ�����ʱ���ɾ����ָ��
	#define __LOCK_FP_SUPPORT__
	#define __PREIPHERAL_FP_SY_SUPPORT__
	#define __LOCK_WIFI_SUPPORT__
	#define __LOCK_ALARM_SUPPORT__

	#define __LOCK_BUS_SUPPORT__
	#define __LOCK_110_SUPPORT__
#endif

#endif //__MMI_FEATURE_H__

