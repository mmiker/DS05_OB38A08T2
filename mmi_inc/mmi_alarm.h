#ifndef __BASE_MMI_ALARM_H__
#define __BASE_MMI_ALARM_H__
#include "mmi_feature.h"
#if defined (__LOCK_ALARM_SUPPORT__) || defined (__LOCK_CONTROL_SUPPORT__)

/*
parameter: 
	none
return :
	none
*/
void mmi_dq_alarm_start(void);

/*
parameter: 
	none
return :
	none
*/
void mmi_dq_alarm_stop(void);

/*
parameter: 
	none
return :
	none
*/

void mmi_dq_alarm_task_pro(void);

/*
parameter: 
	none
return :
	none
*/
void mmi_dq_alarm_init(void);

/*
parameter: 
	none
return :
	none
*/
unsigned char mmi_dq_get_alarm_state(void);
#endif
#endif

