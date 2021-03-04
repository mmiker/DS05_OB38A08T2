#include "mmi_feature.h"
#if defined (__LOCK_MOTOR_SUPPORT__) || defined(__LOCK_CONTROL_SUPPORT__)
#include "mmi_motor.h"
#include "dqiot_drv_motor.h"
#include "dqiot_drv_control.h"
#include "delay.h"

/*
parameter: 
	none
return :
	none
*/
void mmi_dq_motor_turn_right(void)
{
#ifdef __LOCK_CONTROL_SUPPORT__
  	control_open_light();
	delay_ms(200);
  	control_open_solenoid();
	delay_ms(200);
  	control_open_motor();
#endif
#ifdef __LOCK_MOTOR_SUPPORT__
	dqiot_drv_motor_turn_right();
#endif
	return;
}

/*
parameter: 
	none
return :
	none
*/
void mmi_dq_motor_turn_back(void)
{
#ifdef __LOCK_CONTROL_SUPPORT__
	control_closed_solenoid();
	delay_ms(200);
	control_closed_motor();
#endif
#ifdef __LOCK_MOTOR_SUPPORT__
	dqiot_drv_motor_turn_back();
#endif
	return;
}


/*
parameter: 
	none
return :
	none
*/
void mmi_dq_motor_stop(void)
{
#ifdef __LOCK_MOTOR_SUPPORT__
	dqiot_drv_motor_stop();
#endif
	return;
}


#endif



