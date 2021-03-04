#ifndef __MMI_LED_H__
#define __MMI_LED_H__


#define LED_TYPE_1 0x10
#define LED_TYPE_2 0x20
#define LED_TYPE_3 0x40
#define LED_TYPE_4 0x80
#define LED_TYPE_ALL 0xf0

#define LED_TYPE_KEY 0x01

void mmi_dq_led_light(unsigned char num);

void mmi_dq_led_close(unsigned char num);

void mmi_dq_inside_led_light(void);

void mmi_dq_inside_led_close(void);


#endif
