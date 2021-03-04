#include "OB38A08T2.h"
#include "Led.h"


void Led_Init(void)
{
	TKRUNTIME = 28;
	dCOM0 = 1;
	COMEN  = 0x01;
	SEGEN0 = 0x00;
	SEGEN1 = 0x00;
	LEDCLK = 35;
	LEDCON = 0x90;
}

void Led_On(unsigned char led)
{
	SEGEN0 |= led;
}

void Led_Off(unsigned char led)
{
	SEGEN0 &= ~led;
}

