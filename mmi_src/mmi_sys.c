#ifndef __MMI_SYS_C__
#define __MMI_SYS_C__

#include "mmi_feature.h"
#include "mmi_sys.h"
#include "mmi_audio.h"
#include "mmi_rst.h"
#include "mmi_queue.h"
#include "dqiot_drv.h"
#include "mmi_ms.h"
#include "mmi_fs.h"
#include "mmi_bsp.h"
#include "mmi_motor.h"
#include "mmi_wifi.h"
#include "mmi_led.h"
#include "ADC.h"
#include "mmi_alarm.h"

static unsigned char g_sys_door_open_flag = 0;

static unsigned int g_timer2_sleep_count = 0;
static unsigned int g_timer2_count = 0;
static unsigned int g_timer2_set_count = 0;
static unsigned char g_timer2_flag = 0;

static unsigned char g_wifi_check_flag = 0;
static unsigned char g_wifi_check_count = 0;
static unsigned char g_wifi_check_type = 0;

static unsigned char g_led_flag = 0;
static unsigned char g_inside_led_count = 0;
static unsigned char g_led_shine_count = 0;
static unsigned char g_led_flash_count = 0;

static unsigned char g_alarm_flag = 0;
static unsigned char g_alarm_count = 0;


#define LOCK_MAX_EEROR_TIMES 5
static unsigned char g_lock_error_flag = 0;
//static unsigned int g_lock_error_count = 0;

timer2_delay_pro g_timer2_delay_pro = 0;

#define MMI_TIMER_BASE_TIME		100
#define MMI_TIMER_ENTER_SLEEP	10000
#define MMI_TIMER_ENTER_SLEEP_COUNT	(MMI_TIMER_ENTER_SLEEP/MMI_TIMER_BASE_TIME)
#define MMI_TIMER_ENTER_SLEEP_DELAY	20000
#define MMI_TIMER_ENTER_SLEEP_DEALY_COUNT	(MMI_TIMER_ENTER_SLEEP_DELAY/MMI_TIMER_BASE_TIME)
#define MMI_TIMER_DOOR_OPEN 	6000
#define MMI_TIMER_DOOR_OPEN_COUNT	(MMI_TIMER_DOOR_OPEN/MMI_TIMER_BASE_TIME)
#define MMI_TIMER_MOTOR 	 	300
#define MMI_TIMER_MOTOR_COUNT	(MMI_TIMER_MOTOR/MMI_TIMER_BASE_TIME)


#define MMI_WIFI_SETTING_DELAY  60000
#define MMI_WIFI_SETTING_DELAY_COUNT (MMI_WIFI_SETTING_DELAY/MMI_TIMER_BASE_TIME)
#define MMI_INSIDE_LED_DEYLAY		30000
#define MMI_INSIDE_LED_DEYLAY_COUNT (MMI_INSIDE_LED_DEYLAY/MMI_TIMER_BASE_TIME)
#define MMI_LED_SHINE_DEYLAY		500    
#define MMI_LED_SHINE_DEYLAY_COUNT (MMI_LED_SHINE_DEYLAY/MMI_TIMER_BASE_TIME)
#define MMI_LED_FLASH_DEYLAY		400
#define MMI_LED_FLASH_DEYLAY_COUNT (MMI_LED_FLASH_DEYLAY/MMI_TIMER_BASE_TIME)
#define MMI_ALARM_DEYLAY		500    
#define MMI_ALARM_DEYLAY_COUNT (MMI_ALARM_DEYLAY/MMI_TIMER_BASE_TIME)
#define MMI_LOCK_ERROR_DELAY	60000
#define MMI_LOCK_ERROR_DELAY_COUNT (MMI_LOCK_ERROR_DELAY/MMI_TIMER_BASE_TIME)

/*
parameter: 
	none
return :
	none
*/
void mmi_dq_sys_init(void)
{
	mmi_InitQueue();
	mmi_ms_pwd_init_var();
	mmi_dq_fs_init();
}

/*
function: system enter sleep
parameter: 
	none
return :
	none
*/
void mmi_dq_sys_enter_sleep(void)
{
	mmi_dq_bsp_enter_sleep();
	
	g_timer2_flag = 0;
	g_sys_door_open_flag = 0;
	
	mmi_dq_ms_set_sys_state(SYS_STATUS_ENTER_SLEEP);
	
}

/*
function: system wake up
parameter: 
	none
return :
	none
*/
void mmi_dq_sys_wake_up(void)
{
	
	mmi_dq_bsp_wake_up();
	if(mmi_dq_sys_check_vbat() == 0) 
	{
	    mmi_dq_wifi_wakeup();
#ifdef __LOCK_FP_SUPPORT__
		mmi_dq_fp_init(); //握手、点灯
#endif
		mmi_dq_ms_set_sys_state(SYS_STATUS_IDLE);
	}
}

/*
function: 
parameter: 
	none
return :
	none
*/
void mmi_dq_sys_door_open_cb(void)
{
	//mmi_dq_motor_stop();
	mmi_dq_aud_play_with_id(AUD_ID_DOOR_OPEN);
	mmi_dq_sys_set_delay_event(MMI_TIMER_DOOR_OPEN_COUNT, mmi_dq_sys_door_close);
}


/*
function: 
parameter: 
	none
return :
	none
*/
void mmi_dq_sys_door_open(sys_open_type type)
{
	g_lock_error_flag = 0;
	if((mmi_dq_fs_get_open_mode() == SYS_OPEN_MODE_DBL) && (SYS_OPEN_BY_WIFI != type) && ((type&SYS_OPEN_BY_110) == 0))
	{
		if((g_sys_door_open_flag & (~ type)) != 0)
		{
			g_sys_door_open_flag = 0;
		}
		else
		{
			g_sys_door_open_flag |= type;
			mmi_dq_signal_led_light(LED_TYPE_ERROR);
			mmi_dq_signal_led_light(LED_TYPE_RIGHT);
			switch(type)
			{
				case SYS_OPEN_BY_PASSWORD:
				case SYS_OPEN_BY_ADMIN_PASSWORD:
				case SYS_OPEN_BY_USER_PASSWORD:
#ifdef __LOCK_FP_SUPPORT__
					mmi_dq_aud_play_with_id(AUD_ID_PRESS_FP);
					mmi_dq_ms_set_sys_state(SYS_STATUS_IDLE);
#else
					mmi_dq_aud_play_with_id(AUD_ID_SYS_DBL_OPEN_MODE);
#endif
					break;
#ifdef __LOCK_FP_SUPPORT__
				case SYS_OPEN_BY_FP:
					mmi_dq_aud_play_with_id(AUD_ID_INPUT_68_PWD);
					mmi_dq_ms_set_sys_state(SYS_STATUS_INPUT_PWD);
					break;
#endif
#ifdef	__LOCK_RFID_CARD_SUPPORT__
				case SYS_OPEN_BY_RFID:
					
					break;
#endif
			}
			return;
		}
	}

	mmi_dq_ms_set_sys_state(SYS_STATUS_DOOR_OPEN);
	mmi_dq_alarm_stop();
	mmi_dq_fs_set_alarm_flag(0);

	mmi_dq_signal_led_close(LED_TYPE_ERROR);
	mmi_dq_signal_led_light(LED_TYPE_RIGHT);

	mmi_dq_inside_led_timer_start();
	
	mmi_dq_motor_turn_right();
	mmi_dq_sys_door_open_cb();
	//mmi_dq_sys_set_delay_event(MMI_TIMER_MOTOR_COUNT, mmi_dq_sys_door_open_cb);


#ifdef __LOCK_WIFI_SUPPORT__	
	switch(type)
	{
#ifdef __LOCK_110_SUPPORT__
		case SYS_OPEN_BY_110_PASSWORD:
			mmi_dq_wifi_send_pwd_110();
			break;
		case SYS_OPEN_BY_110_FP:
			mmi_dq_wifi_send_fp_110();
			break;
#endif
		case SYS_OPEN_BY_PASSWORD:
		case SYS_OPEN_BY_ADMIN_PASSWORD:
		case SYS_OPEN_BY_USER_PASSWORD:
			mmi_dq_wifi_open_by_password();
			break;
#ifdef __LOCK_FP_SUPPORT__
		case SYS_OPEN_BY_FP:
			mmi_dq_wifi_open_by_fp();
			break;
#endif
#ifdef	__LOCK_RFID_CARD_SUPPORT__
		case SYS_OPEN_BY_RFID:
			mmi_dq_wifi_open_by_rfid();
			break;
#endif
		case SYS_OPEN_BY_WIFI:
			mmi_dq_wifi_open_by_wifi();
			break;
	}
#endif
	
}

/*
function: 
parameter: 
	none
return :
	none
*/
void mmi_dq_sys_door_open_fail(sys_open_type type)
{	
	//g_lock_error_count = 0;
	g_lock_error_flag++;
	switch(type)
	{
		case SYS_OPEN_BY_PASSWORD:
			mmi_dq_aud_play_with_id(AUD_ID_PWD_WRONG_TRY);
			mmi_dq_signal_led_shine_timer_start(LED_TYPE_ERROR, 2, 1);
			if(g_lock_error_flag >= LOCK_MAX_EEROR_TIMES)
				mmi_dq_wifi_pw_alarm();
			break;
#ifdef __LOCK_FP_SUPPORT__
		case SYS_OPEN_BY_FP:
			mmi_dq_aud_play_with_id(AUD_ID_FP_WRONG_TRY);
			mmi_dq_signal_led_light(LED_TYPE_RIGHT);
			mmi_dq_signal_led_shine_timer_start(LED_TYPE_ERROR, 2, 1);
			if(g_lock_error_flag >= LOCK_MAX_EEROR_TIMES)
				mmi_dq_wifi_fp_alarm();
			mmi_dq_ms_set_sys_state(SYS_STATUS_IDLE);
			break;
#endif
#ifdef __LOCK_RFID_CARD_SUPPORT__
		case SYS_OPEN_BY_RFID:
			mmi_dq_aud_play_with_id(AUD_ID_RFCARD_WRONG_TRY);
			if(g_lock_error_flag >= LOCK_MAX_EEROR_TIMES)
				mmi_dq_wifi_rfid_alarm();
			break;
#endif
	}
	if(g_lock_error_flag >= LOCK_MAX_EEROR_TIMES)
	{
		g_lock_error_flag = 0;
		mmi_dq_alarm_start();
	}
}

/*
function: 
parameter: 
	none
return :
	none
*/
void mmi_dq_sys_door_close_cb(void)
{
	//mmi_dq_motor_stop();
	mmi_dq_aud_play_with_id(AUD_ID_DOOR_CLOSE);
	mmi_dq_signal_led_close(LED_TYPE_RIGHT);
	mmi_dq_ms_set_sys_state(SYS_STATUS_IDLE);
}

/*
function: 
parameter: 
	none
return :
	none
*/
void mmi_dq_sys_door_close(void)
{
	mmi_dq_motor_turn_back();
	mmi_dq_sys_door_close_cb();
	//mmi_dq_sys_set_delay_event(MMI_TIMER_MOTOR_COUNT, mmi_dq_sys_door_close_cb);
}

/*
function: 
parameter: 
	none
return :
	none
*/
//unsigned char mmi_dq_sys_door_state_check(void)
//{
//	if(g_lock_error_flag >= LOCK_MAX_EEROR_TIMES)
//		return 1;
//	return 0;
//}

/*
function: 
parameter: 
	none
return :
	none
*/
void mmi_dq_sys_aud_end(void)
{
	mmi_dq_ms_set_msg_que(QUE_EVENT_AUDIO_END,QUE_PRO_LOW,0);
}

/*
function: 
parameter: 
	none
return :
	none
*/
void mmi_dq_sys_time_out_handle(void)
{
	SYS_BASE_STATUS state = mmi_dq_ms_get_sys_state();

	if(state >= SYS_STATUS_ADD_PWD && state <= SYS_STATUS_ADD_ADMIN_PWD || state == SYS_STATUS_SYS_MENU || state == SYS_STATUS_SET_OPEN_MODE)
	{
		mmi_dq_aud_play_with_id(AUD_ID_TIMEOUT);
		mmi_dq_ms_set_sys_state(SYS_STATUS_WAIT_FOR_ENTER_SLEEP);
	}
	else
		mmi_dq_ms_set_sys_state(SYS_STATUS_WAIT_FOR_ENTER_SLEEP);
}

/*
function: 
parameter: 
	none
return :
	none
*/
void System_timer_event_handler(void)
{
	SYS_BASE_STATUS state = mmi_dq_ms_get_sys_state();

	if(g_timer2_flag == 1)
	{
		g_timer2_count++;
		if(g_timer2_count >= g_timer2_set_count)
		{
			g_timer2_flag = 2;
			g_timer2_count = 0;
			//mmi_dq_ms_set_msg_que(QUE_EVENT_TIMER_END,QUE_PRO_LOW,0);
		}
	}

	if(g_wifi_check_flag == 1)
	{
		g_wifi_check_count++;
		if(g_wifi_check_count >= 4)
		{
			g_wifi_check_flag = 2;
			g_wifi_check_count = 0;
		}
	}

	//if(g_lock_error_flag>0)
	//{
	//	g_lock_error_count++;
	//	if(g_lock_error_count>=MMI_LOCK_ERROR_DELAY_COUNT)
	//		g_lock_error_flag = 0;
	//}

	if(g_inside_led_count > 0)
	{
		g_inside_led_count--;
		if(g_inside_led_count == 0)
			g_led_flag &= 0x01;
	}

	if(g_led_shine_count > 0)
	{
		g_led_shine_count--;
		if(g_led_shine_count == 0)
			g_led_flag &= 0x02;
	}
	
	if(g_led_flash_count > 0)
	{
		g_led_flash_count--;
		if(g_led_flash_count == 0)
			g_led_flag &= 0x04;
	}

	if(g_alarm_flag == 1)
	{
		g_alarm_count ++;
		if(g_alarm_count >= MMI_ALARM_DEYLAY_COUNT)
			g_alarm_flag = 2;
	}
	
	if((mmi_dq_rst_timer_event() != 0) && (SYS_STATUS_ENTER_SLEEP != state && SYS_STATUS_WAIT_FOR_ENTER_SLEEP != state) && (g_timer2_flag != 1) && (mmi_dq_ms_get_run_flag() == 1)&&(mmi_dq_wifi_get_running_flag() == 0))
	{
		unsigned char flag = 0;
		g_timer2_sleep_count++;
		if(state == SYS_STATUS_ADD_PWD ||state ==SYS_STATUS_ADD_ADMIN_PWD 
#ifdef __LOCK_FP_SUPPORT__
			|| state == SYS_STATUS_ADD_FP|| state == SYS_STATUS_DEL_FP 
#endif
#ifdef __LOCK_RFID_CARD_SUPPORT__
			|| state == SYS_STATUS_ADD_RFID|| state == SYS_STATUS_DEL_RFID
#endif
			)
		{
			if(g_timer2_sleep_count > MMI_TIMER_ENTER_SLEEP_DEALY_COUNT)
			{
				flag = 1;
			}
		}
		else if(g_timer2_sleep_count > MMI_TIMER_ENTER_SLEEP)
		{
			flag = 1;
		}


		if(flag)
		{
			mmi_dq_sys_time_out_handle();
		}
	}
	else
		g_timer2_sleep_count = 0;
}

/*
function: 
parameter: 
	none
return :
	none
*/
unsigned char mmi_dq_sys_get_wifi_check_flag(void)
{
	if(g_wifi_check_flag == 2)
	{
		g_wifi_check_flag = 0;
		return 1;
	}
	return 0;
}

/*
function: 
parameter: 
	none
return :
	none
*/
void mmi_dq_sys_set_wifi_check(unsigned char type)
{
	g_wifi_check_count = 0;
	g_wifi_check_flag = 1;
	g_wifi_check_type = type;
}

/*
function: 
parameter: 
	none
return :
	none
*/
unsigned char mmi_dq_sys_get_wifi_check_type(void)
{
	return g_wifi_check_type;
}

/*
function: 
parameter: 
	none
return :
	none
*/
void mmi_dq_sys_set_inside_led_timer(void)
{
	g_inside_led_count = MMI_INSIDE_LED_DEYLAY_COUNT;
	g_led_flag &= 0xFE;
}

/*
function: 
parameter: 
	none
return :
	none
*/
void mmi_dq_sys_clear_inside_led_timer(void)
{
	g_inside_led_count = 0;
	g_led_flag &= 0xFE;
}

/*
function: 
parameter: 
	none
return :
	none
*/
unsigned char mmi_dq_sys_get_inside_led_timer(void)
{
	if(g_inside_led_count > 0)
		return 1;
	else 
		return 0;
}


/*
function: 
parameter: 
	none
return :
	none
*/
void mmi_dq_sys_set_led_shine_timer(void)
{
	g_led_shine_count = MMI_LED_SHINE_DEYLAY_COUNT;
	g_led_flag &= 0xFD;
}

/*
function: 
parameter: 
	none
return :
	none
*/
void mmi_dq_sys_set_led_flash_timer(void)
{
	g_led_flash_count = MMI_LED_FLASH_DEYLAY_COUNT;
	g_led_flag &= 0xFB;
}

/*
function: 
parameter: 
	none
return :
	none
*/
unsigned char mmi_dq_sys_get_led_timer_flag(void)
{
	unsigned char flag = g_led_flag;
	g_led_flag = 0;
	return flag;
}

/*
function: 
parameter: 
	none
return :
	none
*/
void mmi_dq_sys_alarm_timer_start(void)
{
	g_alarm_count = MMI_ALARM_DEYLAY_COUNT;
	g_alarm_flag = 1;
}

/*
function: 
parameter: 
	none
return :
	none
*/
void mmi_dq_sys_alarm_timer_stop(void)
{
	g_alarm_flag = 0;
	g_alarm_count = 0;
}


/*
function: 
parameter: 
	none
return :
	none
*/
unsigned char mmi_dq_sys_get_alarm_timer_flag(void)
{
	if(g_alarm_flag == 2)
	{
		g_alarm_flag = 0;
		return 1;
	}
	return 0;
}

/*
function: 
parameter: 
	none
return :
	none
*/
void mmi_dq_sys_sleep_timer_reset(void)
{
	g_timer2_sleep_count = 0;
	return;
}


/*
function: 
parameter: 
	none
return :
	none
*/
unsigned char mmi_dq_sys_get_timer2_flag(void)
{
	if(g_timer2_flag == 2)
	{
		g_timer2_flag = 0;
		return 1;
	}
	return 0;
}

/*
function: 
parameter: 
	none
return :
	none
*/
//慎用，最好确保无其他输入情况下使用
void mmi_dq_sys_set_delay_event(unsigned int count, timer2_delay_pro pro)
{
	if(count != 0)
	{
		g_timer2_count = 0;
		g_timer2_set_count = count;
		g_timer2_delay_pro = pro;
		g_timer2_flag = 1;
	}
	else
		pro();
}

/*
function: 
parameter: 
	none
return :
	none
*/
void mmi_dq_sys_delay_event_pro(void)
{
	g_timer2_delay_pro();
}

/*
function: 
parameter: 
	none
return :
	none
*/
unsigned char mmi_dq_sys_check_vbat(void)
{
	unsigned char state = adc_VolT();
	if(state > 0) 
	{
		mmi_dq_aud_play_with_id(AUD_ID_LOW_BATTERY);
		mmi_dq_wifi_lowpower_alarm();
		if(state == 2)
		{
			mmi_dq_ms_set_sys_state(SYS_STATUS_LOW_POWER);
			return 1;
		}
	}

	return 0;
}

/*
function: 
parameter: 
	none
return :
	none
*/
void mmi_dq_sys_wifi_open(void)
{
	if((mmi_dq_fs_get_wifi_setting()== 0)||(mmi_dq_wifi_open_ask() == 0))
		mmi_dq_aud_play_with_id(AUD_ID_WIFI_UNFINDE);
	else
	{
		mmi_dq_signal_led_close(LED_TYPE_RIGHT);
		mmi_dq_signal_led_close(LED_TYPE_ERROR);
		mmi_dq_ms_set_sys_state(SYS_STATUS_IDLE);
	}
}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//*******************************************************************************************************************************************************************************************
//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//
//				menu part
//
//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//*******************************************************************************************************************************************************************************************
//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

/*
parameter: 
	none
return :
	none
*/
void mmi_dq_sys_add_pwd(void)
{
	mmi_dq_aud_play_with_id(AUD_ID_INPUT_68_PWD);
	mmi_ms_pwd_init_var();
	mmi_dq_ms_set_sys_state(SYS_STATUS_ADD_PWD);
	return;
}

#ifdef __LOCK_110_SUPPORT__
/*
parameter: 
	none
return :
	none
*/
void mmi_dq_sys_add_110_pwd(void)
{
	mmi_dq_aud_play_with_id(AUD_ID_INPUT_68_PWD);
	mmi_ms_pwd_init_var();
	mmi_dq_ms_set_sys_state(SYS_STATUS_ADD_110_PWD);
	return;
}
#endif


#if defined(__LOCK_FP_SUPPORT__)
/*
parameter: 
	none
return :
	none
*/
void mmi_dq_sys_add_fp(void)
{
	if(mmi_dq_fs_get_fp_unuse_index()==0xFF)
	{
		mmi_dq_aud_play_with_id(AUD_ID_FP_FULL);
		mmi_dq_sys_show_cur_menu_list();
	}
	else
	{
		mmi_dq_aud_play_with_id(AUD_ID_PRESS_FP);
		mmi_dq_fp_light(FP_BLUE);
		mmi_ms_opt_time_init();
		mmi_dq_ms_set_sys_state(SYS_STATUS_ADD_FP);
	}
	return;
}

#ifdef __LOCK_110_SUPPORT__
/*
parameter: 
	none
return :
	none
*/
void mmi_dq_sys_add_110_fp(void)
{
	mmi_dq_aud_play_with_id(AUD_ID_PRESS_FP);
	mmi_dq_fp_light(FP_BLUE);
	mmi_ms_opt_time_init();
	mmi_dq_ms_set_sys_state(SYS_STATUS_ADD_110_FP);
	return;
}

#endif

/*
parameter: 
	none
return :
	none
*/
void mmi_dq_sys_del_fp(void)
{
	mmi_dq_aud_play_with_id(AUD_ID_INPUT_DEL_FP_NUM);
	mmi_dq_fp_light(FP_BLUE);
	mmi_ms_opt_time_init();
	mmi_dq_ms_set_sys_state(SYS_STATUS_DEL_FP);
	return;
}

#endif
#ifdef __LOCK_RFID_CARD_SUPPORT__
/*
parameter: 
	none
return :
	none
*/
void mmi_dq_sys_add_rf(void)
{
	
	if(mmi_dq_fs_get_rfid_unuse_index()==0xFF)
	{
		mmi_dq_aud_play_with_id(AUD_ID_RFCARD_FULL);
		mmi_dq_sys_show_cur_menu_list();
	}
	else
	{
		mmi_dq_aud_play_with_id(AUD_ID_PRESS_RFCARD);
		mmi_ms_opt_time_init();
		mmi_dq_ms_set_sys_state(SYS_STATUS_ADD_RFID);
	}
	return;
}

void mmi_dq_sys_add_rf_con(void)
{
	mmi_dq_aud_play_with_id(AUD_ID_CONTINUE_ADD_PWD);
	mmi_dq_ms_set_sys_state(SYS_STATUS_ADD_RFID_CON);
	return;
}

/*
parameter: 
	none
return :
	none
*/
static void mmi_dq_sys_chg_rf(void)
{
	//mmi_dq_ms_set_sys_state(SYS_STATUS_CHG_RFID);
	return;
}

/*
parameter: 
	none
return :
	none
*/
void mmi_dq_sys_del_rf(void)
{
	mmi_dq_aud_play_with_id(AUD_ID_INPUT_DEL_RFCARD_NUM);
	mmi_ms_opt_time_init();
	mmi_dq_ms_set_sys_state(SYS_STATUS_DEL_RFID);
	return;
}

void mmi_dq_sys_del_rf_con(void)
{
	mmi_dq_aud_play_with_id(AUD_ID_DEL_CONFIRM);
	mmi_dq_ms_set_sys_state(SYS_STATUS_DEL_RFID_CON);
	return;
}

/*
parameter: 
	none
return :
	none
*/
static void mmi_dq_sys_clear_rf(void)
{
	mmi_dq_aud_play_with_id(AUD_ID_CLR_RFCARD_CONFIRM);
	mmi_dq_ms_set_sys_state(SYS_STATUS_CLR_RFID);
	return;
}
#endif

/*
parameter: 
	none
return :
	none
*/
void mmi_dq_sys_chg_admin_pwd(void)
{
	mmi_dq_aud_play_with_id(AUD_ID_INPUT_NEW_ADMIN_PWD);
	mmi_ms_pwd_init_var();
	mmi_dq_ms_set_sys_state(SYS_STATUS_ADD_ADMIN_PWD);
	return;
}

/*
parameter: 
	none
return :
	none
*/
static void mmi_dq_sys_set_open_mode(void)
{
	mmi_dq_aud_play_with_id(AUD_ID_SYS_OPEN_MODE);
	mmi_dq_ms_set_sys_state(SYS_STATUS_SET_OPEN_MODE);
	return;
}

/*
parameter: 
	none
return :
	none
*/
static void mmi_dq_sys_wifi_setting(void)
{
	if(0 == mmi_dq_wifi_setting())
	{
		mmi_dq_aud_play_with_id(AUD_ID_SET_FAILED);
		mmi_dq_sys_show_cur_menu_list();
	}
	else
	{
		mmi_dq_ms_set_sys_state(SYS_STATUS_WIFI_MODE);
		mmi_dq_aud_play_with_id(AUD_ID_WIFI_CONNECTING);
		mmi_dq_signal_led_shine_timer_start(LED_TYPE_SET, 255, 1);
	}
}

typedef struct sys_menu_t
{
	void (*sys_menu_node_function)(void);
}sys_menu_t;

const sys_menu_t sys_menu_tree[] = 
{
#ifdef __LOCK_FP_SUPPORT__
		mmi_dq_sys_add_pwd,
		mmi_dq_sys_add_fp,
		mmi_dq_sys_del_fp,
		mmi_dq_sys_chg_admin_pwd,
		mmi_dq_sys_set_open_mode,
	#ifdef __LOCK_WIFI_SUPPORT__
		mmi_dq_sys_wifi_setting,
	#endif
	#ifdef __LOCK_110_SUPPORT__
		mmi_dq_sys_add_110_pwd,	
		mmi_dq_sys_add_110_fp,
	#endif
#else
		mmi_dq_sys_add_pwd,
		mmi_dq_sys_chg_admin_pwd,
		mmi_dq_sys_set_open_mode,
	#ifdef __LOCK_WIFI_SUPPORT__
		mmi_dq_sys_wifi_setting,
	#endif
	#ifdef __LOCK_110_SUPPORT__
		mmi_dq_sys_add_110_pwd,	
	#endif
#endif
};

/*
parameter: 
	none
return :
	none
*/
unsigned char mmi_dq_sys_get_menu_count(void)
{
	return sizeof(sys_menu_tree)/sizeof(sys_menu_t);
}


/*
parameter: 
	none
return :
	none
*/
void mmi_dq_sys_show_cur_menu_list(void)
{	
#ifdef __LOCK_AUDIO_SUPPORT__
	mmi_dq_aud_play_with_id(AUD_ID_SYSTEM);
#endif
#ifdef __LOCK_FP_SUPPORT__
  	mmi_dq_fp_light(FP_NONE_COLOR);
#endif

	mmi_dq_ms_set_sys_state(SYS_STATUS_SYS_MENU);
	return;
}

/*
parameter: 
	none
return :
	none
*/
RET_VAL mmi_dq_sys_exe_menu_fun(unsigned char menu_id)
{
	sys_menu_tree[menu_id].sys_menu_node_function();
	return RET_SUCESS;
}

#endif//__MMI_SYS_C__
