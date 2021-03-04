#include "mmi_alarm.h"
#if defined (__LOCK_ALARM_SUPPORT__) || defined (__LOCK_CONTROL_SUPPORT__)
#include "dqiot_drv_alarm.h"
#include "dqiot_drv_control.h"
#include "mmi_ms.h"
#include "mmi_sys.h"
#include "mmi_led.h"

static unsigned char alarm_state = 0;
/*
parameter: 
	none
return :
	none
*/
void mmi_dq_alarm_start(void)
{
#ifdef __LOCK_CONTROL_SUPPORT__
	control_open_alarm();
#endif
#ifdef __LOCK_ALARM_SUPPORT__
	Alarm_start();
#endif

	alarm_state = 1;
	mmi_dq_sys_alarm_timer_start();
	mmi_dq_signal_led_shine_timer_start(LED_TYPE_SET,255,1);
}

/*
parameter: 
	none
return :
	none
*/
void mmi_dq_alarm_stop(void)
{
#ifdef __LOCK_CONTROL_SUPPORT__
	control_closed_alarm();
#endif
#ifdef __LOCK_ALARM_SUPPORT__
	Alarm_stop();
#endif
	alarm_state = 0;
	mmi_dq_sys_alarm_timer_stop();
	mmi_dq_signal_led_close(LED_TYPE_SET);
}

/*
parameter: 
	none
return :
	none
*/
void mmi_dq_alarm_task_pro(void)
{
	if(alarm_state != 0 && mmi_dq_sys_get_alarm_timer_flag() == 1)
	{
		SYS_BASE_STATUS state = mmi_dq_ms_get_sys_state();
#ifdef __LOCK_CONTROL_SUPPORT__
		control_closed_alarm();
#endif
#ifdef __LOCK_ALARM_SUPPORT__
		Alarm_stop();
#endif
		alarm_state = 0;

		if(state == SYS_STATUS_INPUT_ADMIN_PWD)
			mmi_dq_signal_led_light(LED_TYPE_SET);
		else
			mmi_dq_signal_led_close(LED_TYPE_SET);
	}
}

/*
parameter: 
	none
return :
	none
*/
void mmi_dq_alarm_init(void)
{
#ifdef __LOCK_ALARM_SUPPORT__
	Alarm_init();
#endif
}

/*
parameter: 
	none
return :
	none
*/
unsigned char mmi_dq_get_alarm_state(void)
{
	return alarm_state;
}

#endif
