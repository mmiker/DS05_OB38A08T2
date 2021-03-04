#ifndef __LED_H__
#define __LED_H__

#define LED_TYPE_1 0x10
#define LED_TYPE_2 0x20
#define LED_TYPE_3 0x40
#define LED_TYPE_4 0x80
#define LED_TYPE_ALL 0xf0


void Led_Init(void);

void Led_On(unsigned char led);

void Led_Off(unsigned char led);

#endif
