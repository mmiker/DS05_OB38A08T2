#ifndef __BASE_MMI_LED_C__
#define __BASE_MMI_LED_C__

#include "mmi_led.h"
#include "mmi_sys.h"
#include "mmi_key.h"
#include "dqiot_drv_control.h"
#include "dqiot_drv_led.h"

static unsigned char light_type[4] = {0};
static unsigned char led_flash_flag = 0;

void mmi_dq_led_init(void)
{
	dqiot_drv_signal_led_init();

}

void mmi_dq_signal_led_light(unsigned char light)
{
	light_type[light-1] = 0;
	dqiot_drv_signal_led_on(light);
}

void mmi_dq_signal_led_close(unsigned char light)
{
	light_type[light-1] = 0;
	dqiot_drv_signal_led_off(light);
}

static void mmi_dq_signal_led_toggle(unsigned char light)
{
	dqiot_drv_signal_led_toggle(light);
}

void mmi_dq_signal_led_shine_timer_start (unsigned char light, unsigned char times, unsigned char is_on)
{
	if(is_on)
		mmi_dq_signal_led_light(light);
	else
		mmi_dq_signal_led_close(light);
	light_type[light-1] = times;
	mmi_dq_sys_set_led_shine_timer();
}

static void mmi_dq_signal_led_shine_toggle (void)
{
	unsigned char i;
	unsigned char con = 0;
	for(i=0;i<4;i++)
	{
		if(light_type[i]!=0)
		{
			mmi_dq_signal_led_toggle(i+1);
			con = 1;
			if(light_type[i] != 255)
				light_type[i] --;
		}
	}
	if(con != 0)
		mmi_dq_sys_set_led_shine_timer();
	return;
}

void mmi_dq_key_light_light(unsigned char num)
{


}

void mmi_dq_key_light_close(unsigned char num)
{

}


void mmi_dq_key_light_flash_timer_start(void)
{
	led_flash_flag=1;
	mmi_dq_sys_set_led_flash_timer();
	mmi_dq_key_light_close(KEY_ALL);
}

static void mmi_dq_key_light_flash_toggle (void)
{
	if (led_flash_flag<13)
	{
		if(led_flash_flag%2==1)
			mmi_dq_key_light_light(KEY_ALL);
		else if(led_flash_flag%2==0)
			mmi_dq_key_light_close(KEY_ALL);
		mmi_dq_sys_set_led_flash_timer();
	}
	else 
	{
		mmi_dq_key_light_close(KEY_ALL);
	}
	led_flash_flag++;
	return;
}



void mmi_dq_inside_led_light(void)
{
	control_open_light();
}

void mmi_dq_inside_led_close(void)
{
	control_closed_light();
}

void mmi_dq_inside_led_timer_stop (void)
{
	if(mmi_dq_sys_get_inside_led_timer() > 0)
	{
		mmi_dq_inside_led_close();
		mmi_dq_sys_clear_inside_led_timer();
	}
}


void mmi_dq_inside_led_timer_start (void)
{
	mmi_dq_inside_led_light();
	mmi_dq_sys_set_inside_led_timer();
}


void mmi_dq_led_task_proc(void)
{
	unsigned char flag = mmi_dq_sys_get_led_timer_flag();
	if(flag & 0x01)
	{
		mmi_dq_inside_led_close();
	}
	if(flag & 0x02)
	{
		mmi_dq_signal_led_shine_toggle();
	}
	if(flag & 0x04)
	{
		mmi_dq_key_light_flash_toggle();
	}
}
#endif
