#include "OB38A08T2.h"
#include "Bsp.h"

//LDO_EN:P1.3 PUSHPULL
//VIB_INT:P1.4 INPUT
//KEY1:P1.7 INPUT
//KEY_2/ADC:P1.2 INPUT
#define LDO_EN_INIT \
	P1M1 &= 0xF7;   \
	P1M0 |= 0x08
#define VIB_INT_INIT \
	P1M1 |= 0x10;    \
	P1M0 &= 0xEF
#define KEY1_INIT \
	P1M1 |= 0x80; \
	P1M0 &= 0x7F
#define KEY2_ADC_INIT \
	P1M1 |= 0x04;     \
	P1M0 &= 0xFB

#define LDO_EN_ON P1_3 = 1
#define LDO_EN_OFF P1_3 = 0
void Bsp_Init(void)
{
	LDO_EN_INIT;
	VIB_INT_INIT;
	KEY1_INIT;
	KEY2_ADC_INIT;

	LDO_EN_ON;
}

void Bsp_Sleep(void)
{
	LDO_EN_OFF;

	S0CON &= 0xEF;
	P2M1 |= 0x40;
	P2M0 &= 0xBF;
	P2M1 |= 0x20;
	P2M0 &= 0xDF;
	P2_6 = 0;
	P2_5 = 0;

	P0M1 |= 0x01;
	P0M0 &= 0xFE;
	P1M1 |= 0x40;
	P1M0 &= 0xBF;
	P0_0 = 0;
	P1_6 = 0;

	//P3M1|=0x02;P3M0&=0xFD;
	//P3_0 = 0;
}

void Bsp_Wakeup(void)
{
	LDO_EN_ON;
}

void INT1_Init(void)
{
	P2M1 |= 0x40;
	P2M0 &= 0xBF;
	P2_6 = 0;

	IT1 = 1;
	ENHIT |= 0x08;
	INTDEG |= 0x04;
	EX1 = 1;
}
