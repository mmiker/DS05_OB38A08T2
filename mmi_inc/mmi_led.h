#ifndef __MMI_LED_H__
#define __MMI_LED_H__


#define LED_TYPE_SET 1//0x10
#define LED_TYPE_LOWPOER 2//0x20
#define LED_TYPE_ERROR 3//0x40
#define LED_TYPE_RIGHT 4//0x80
#define LED_TYPE_ALL 5//0xf0

void mmi_dq_led_init(void);

void mmi_dq_signal_led_light(unsigned char light);

void mmi_dq_signal_led_close(unsigned char light);

void mmi_dq_signal_led_shine_timer_start (unsigned char light, unsigned char times, unsigned char is_on);

void mmi_dq_key_light_light(unsigned char num);

void mmi_dq_key_light_close(unsigned char num);

void mmi_dq_key_light_flash_timer_start(void);

void mmi_dq_inside_led_light(void);

void mmi_dq_inside_led_close(void);

void mmi_dq_inside_led_timer_start(void);

void mmi_dq_inside_led_timer_stop(void);

void mmi_dq_led_task_proc(void);

#endif
