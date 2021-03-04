#include "OB38A08T2.h"
#include "Bsp.h"
#include "Led.h"
#include "Audio.h"
#include "fps.h"
#include "Touch.h"
#include "Timer.h"
#include "UART0.h"
#include "I2C.h"
#include "mmi_fps.h"
#include "ADC.h"

//1:enable, 0:disable
#define g_SleepCtrl (*((unsigned char volatile xdata *)0x30D))
unsigned char touch_t = 0xff;

void WDT_ISR(void) interrupt d_WDT_Vector
{
	((void(code *)(void))0x200B)(); //WDT ISR Function
}

void INT1_ISR(void) interrupt d_INT1_Vector
{
	if (P2_6 == 0)
	{
		Led_Off(LED_TYPE_2);
	}
	else
	{
		Led_On(LED_TYPE_2);
	}
}

unsigned char c_data[3] = {'L', 'o', 0};
void main(void)
{
	unsigned int num = 0;
	unsigned char state = 0;
	u16 ID = 0;

	Bsp_Init();
	Led_Init();
	Touch_Init();
	TIMER_Init();
	Audio_Init();
	Fps_Init();
	ADC_Init();

	LVC = 0x40; // For Power down mode

	//g_SleepCtrl = 0;
#if 0
	TIMER1_Delay(5000);

	Fps_Test();
	TIMER1_Delay(2000);
	if (UART0_RXLEN > 4)
	{
		unsigned char i;
		for (i = 0; i < UART0_RXLEN - 1; i++)
		{
			if (UART0_RXBUF[i] == 0xEF && UART0_RXBUF[i + 1] == 0x01)
			{
				Led_On(LED_TYPE_ALL);
				break;
			}
		}
	}
#else
	//INT1_Init();

	//EA =1;

	TIMER1_Delay(1000);
	I2C_Master_Write_Data(0x60, c_data, 2);

	TIMER1_Delay(1000);
	I2C_Master_Write_Data(0x60, c_data, 2);
#endif
	Led_On(LED_TYPE_3);

	state = adc_VolT();
	if (state > 0)
	{
		//提示电量低
		Audio_Play(AUD_ID_LOW_BATTERY);
		if (state == 2)
		{
			Audio_Play(AUD_ID_LOW_BATTERY);
		}
	}

	while (1)
	{
		Touch_Normal();

		if (0xFF == Touch_Getinput())
		{
			FP_Light(FP_BLUE);
			touch_t = 0xff;
			Led_Off(LED_TYPE_1);
			num++;
		}
		else if (touch_t != Touch_Getinput())
		{
			touch_t = Touch_Getinput();
			Led_On(LED_TYPE_1);

			if (touch_t == 1)
				Add_FR(ID);
			if (touch_t == 2)
				Del_FR(1);
			if (touch_t == 3)
				Del_FR(0);

			//Audio_Stop();
			//Audio_Play(AUD_BASE_ID_SYS_NUM_0 + touch_t);
			num = 0;
		}

		if (mmi_dq_fp_work() != 0)
			press_FR();

		// if (num > 60000) //TKSTATUS0 != 0 )
		// {
		// 	g_SleepCtrl = 1; //Entering power down mode immediately
		// 	num = 0;
		// 	Led_Off(LED_TYPE_3);
		// 	Bsp_Sleep();
		// 	//LEDCON &= 0x7F;
		// 	dCOM0 = 0;
		// 	PCON |= 0x02;
		// 	dCOM0 = 1;
		// 	Led_On(LED_TYPE_3);
		// 	Bsp_Wakeup();
		// }
	}
}
