#include "OB38A08T2.h"
#include "fps.h"
#include "UART0.h"
#include "Timer.h"

//FP_INT:P0.3 INPUT
#define FP_INT P0_3

#define FP_INT_INIT P0M1|=0x08;P0M0&=0xF7

void Fps_Init(void)
{
	FP_INT_INIT;
	
	UART0_init();
}

unsigned char test_data[] ={0xEF,0x01,0xFF,0xFF,0xFF,0xFF,0x01,0x00,0x07,0x41,0x01,0x01,0x00,0x50,0x00,0x9B};
void Fps_Test(void)
{
	unsigned char i;
	for(i =0;i<16;i++)
		UART0_TX(test_data[i]);
}
