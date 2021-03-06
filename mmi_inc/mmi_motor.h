#ifndef __MMI_MOTOR_H__
#define __MMI_MOTOR_H__

#include "mmi_feature.h"
#if defined (__LOCK_MOTOR_SUPPORT__) || defined(__LOCK_CONTROL_SUPPORT__)

/*
parameter: 
	none
return :
	none
*/
void mmi_dq_motor_turn_right(void);

/*
parameter: 
	none
return :
	none
*/
void mmi_dq_motor_turn_back(void);

/*
parameter: 
	none
return :
	none
*/
void mmi_dq_motor_stop(void);
#endif
#endif
