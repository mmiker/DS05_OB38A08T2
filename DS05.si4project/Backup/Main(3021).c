#include "OB38A08T2.h"
#include "Bsp.h"
#include "Led.h"
#include "Audio.h"
#include "fps.h"
#include "Touch.h"
#include "Timer.h"
#include "UART0.h"
#include "I2C.h"

//1:enable, 0:disable
#define g_SleepCtrl     (*((unsigned char volatile xdata*)0x30D))
unsigned char touch_t = 0xff;

void WDT_ISR(void) interrupt d_WDT_Vector
{
    ((void(code*)(void))0x200B)();      //WDT ISR Function
}


void INT1_ISR(void) interrupt d_INT1_Vector
{
    if(P2_6 == 0)
    {
		Led_Off(LED_TYPE_2);
    }
	else
	{
		Led_On(LED_TYPE_2);
	}
}


unsigned char c_data[3] = {'L','o',0};
void main(void)
{
	unsigned int num = 0;
	Bsp_Init();
    Led_Init();
    Touch_Init();
	TIMER_Init();
	Audio_Init();
	Fps_Init();
	

    LVC=0x40;    // For Power down mode

    g_SleepCtrl = 0;
	Led_On(LED_TYPE_3);

    while(1)
    {
		Touch_Normal();

		if(0xFF == Touch_Getinput())
		{
			touch_t = 0xff;
			Led_Off(LED_TYPE_1);
			num ++;
		}
		else if(touch_t != Touch_Getinput())
		{
			touch_t = Touch_Getinput();
			Led_On(LED_TYPE_1);
			//Audio_Stop();
			//Audio_Play(AUD_BASE_ID_SYS_NUM_0 + touch_t);
			num = 0;
		}
		if(P2_6 != 0)
			num = 0;
		
        if (num > 60000)//TKSTATUS0 != 0 )
        {
             g_SleepCtrl = 1;  //Entering power down mode immediately
             num = 0;
			 Led_Off(LED_TYPE_3);
			 Bsp_Sleep();
			 //LEDCON &= 0x7F;
			 PCON |= 0x02;
			 Led_On(LED_TYPE_3);
        }

    }
}
