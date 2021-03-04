#ifndef __BASE_MMI_LED_C__
#define __BASE_MMI_LED_C__

#include "mmi_led.h"
#include "mmi_sys.h"

static unsigned char light_type[4] = {0};
static unsigned char led_flash_flag = 0;

void mmi_dq_led_light(unsigned char num)
{


}

void mmi_dq_led_close(unsigned char num)
{

}

static void mmi_dq_led_toggle(unsigned char num)
{

}


void mmi_dq_led_shine_timer_stop (unsigned char light, unsigned char is_on)
{
	unsigned char i;
	if(light_type[light-1]!=0)
	{
		light_type[light-1] = 0;
		for(i=0;i<4;i++)
		{
			if(light_type[i]!=0)
				break;
		}
	}
	if(is_on)
		mmi_dq_led_light(light);
	else
		mmi_dq_led_close(light);
	
	return;

}

void mmi_dq_led_shine_timer_start (unsigned char light, unsigned char times, unsigned char is_on)
{
	if(is_on)
		mmi_dq_led_light(light);
	else
		mmi_dq_led_close(light);
	light_type[light-1] = times;
	mmi_dq_sys_set_led_shine_timer();
}

static void mmi_dq_led_shine_toggle (void)
{
	unsigned char i;
	unsigned char con = 0;
	for(i=0;i<4;i++)
	{
		if(light_type[i]!=0)
		{
			mmi_dq_led_toggle(i+1);
			con = 1;
			if(light_type[i] != 255)
				light_type[i] --;
		}
	}
	if(con != 0)
		mmi_dq_sys_set_led_shine_timer();
	return;
}



void mmi_dq_led_flash_timer_start (unsigned char light, unsigned char times, unsigned char is_on)
{
	led_flash_flag=1;
	mmi_dq_sys_set_led_flash_timer();
}

static void mmi_dq_led_flash_toggle (void)
{
	if (led_flash_flag<13)
	{
		if(led_flash_flag%2==1){
		touch_gt316_key_light_with_out_finger();
		Auaraled_BLN_Light(RGB_G);
		}else if(led_flash_flag%2==0){
		touch_gt316_keyboard_close();
		//Auaraled_BLN_Close(); 
		}
	}
	else 
	{
		touch_gt316_keyboard_close();
		Auaraled_BLN_Close();	
	}
	led_flash_flag++;
	return;
}



void mmi_dq_inside_led_light(void)
{
	touch_gt316_inside_light();
}

void mmi_dq_inside_led_close(void)
{
	touch_gt316_inside_close();
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
		mmi_dq_led_shine_toggle();
		mmi_dq_sys_set_led_shine_timer();
	}
	if(flag & 0x04)
	{

	}
}
#endif
