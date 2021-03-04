#include "OB38A08T2.h"
#include "Bsp.h"
#include "Led.h"
#include "Audio.h"
#include "fps.h"


//1:enable, 0:disable
#define g_SleepCtrl     (*((unsigned char volatile xdata*)0x30D))

extern unsigned char TOUCH_Auto_Set_Counter_Limit_Range(void);


unsigned char bdata ucTkStatusPort0;
unsigned char bdata ucTkStatusPort1;

sbit bTk00Flag  = ucTkStatusPort0^0;
sbit bTk01Flag  = ucTkStatusPort0^1;
sbit bTk02Flag  = ucTkStatusPort0^2;
sbit bTk03Flag  = ucTkStatusPort0^3;
sbit bTk04Flag  = ucTkStatusPort0^4;
sbit bTk05Flag  = ucTkStatusPort0^5;
sbit bTk06Flag  = ucTkStatusPort0^6;
sbit bTk07Flag  = ucTkStatusPort0^7;

sbit bTk08Flag  = ucTkStatusPort1^0;
sbit bTk09Flag  = ucTkStatusPort1^1;
sbit bTk10Flag  = ucTkStatusPort1^2;
sbit bTk11Flag  = ucTkStatusPort1^3;
sbit bTk12Flag  = ucTkStatusPort1^4;
sbit bTk13Flag  = ucTkStatusPort1^5;
sbit bTk14Flag  = ucTkStatusPort1^6;
sbit bTk15Flag  = ucTkStatusPort1^7;


unsigned char g_ucTkNumber = 0xFF;

void TOUCH_ISR(void) interrupt d_TK_Vector using 1
{
    EA = 0;
    ((void(code*)(void))0x2011)();      //Touch ISR Function
    EA = 1;
}

void WDT_ISR(void) interrupt d_WDT_Vector
{
    ((void(code*)(void))0x200B)();      //WDT ISR Function
}

//According to practical application, user can change upper/lower limit by calliing this function
//0: AutoSet touch upper/lower limit data OK
//1: Online mode (Connecting with Touchlyzer)
//2: Number of programming is over the upper limit (Count>800)
//3: Error occurred
unsigned char TOUCH_Auto_Set_Counter_Limit_Range(void)
{
    return ((unsigned char(code*)(void))0x2014)();      		
}

void main(void)
{
    Led_Init();
    
    ((void(code*)(void))0x2005)();                   //Touch initial

    LVC=0x40;    // For Power down mode

    //g_SleepCtrl = 0;

    while(1)
    {
        ((unsigned char(code*)(void))0x2008)();  //Touch Normal Run

        ucTkStatusPort0 = TKSTATUS0;
        ucTkStatusPort1 = TKSTATUS1;

        if (ucTkStatusPort0 == 0 && ucTkStatusPort1 == 0)
        {
            g_ucTkNumber = 0xFF;
        }
        else if (g_ucTkNumber == 0xFF)
        {
            if (bTk00Flag == 1)              //Check TK0
                g_ucTkNumber = 0;
            else if (bTk01Flag == 1)         //Check TK1
                g_ucTkNumber = 1;
            else if (bTk02Flag == 1)         //Check TK2
                g_ucTkNumber = 2;
            else if (bTk03Flag == 1)         //Check TK3
                g_ucTkNumber = 3;
            else if (bTk04Flag == 1)         //Check TK4
                g_ucTkNumber = 4;
            else if (bTk05Flag == 1)         //Check TK5
                g_ucTkNumber = 5;
            else if (bTk06Flag == 1)         //Check TK6
                g_ucTkNumber = 6;
            else if (bTk07Flag == 1)         //Check TK7
                g_ucTkNumber = 7;
            else if (bTk08Flag == 1)         //Check TK8
                g_ucTkNumber = 8;
            else if (bTk09Flag == 1)         //Check TK9
                g_ucTkNumber = 9;
            else if (bTk10Flag == 1)         //Check TK10
                g_ucTkNumber = 10;
            else if (bTk11Flag == 1)         //Check TK11
                g_ucTkNumber = 11;
            else if (bTk12Flag == 1)         //Check TK12
                g_ucTkNumber = 12;
            else if (bTk13Flag == 1)         //Check TK13
                g_ucTkNumber = 13;
            else if (bTk14Flag == 1)         //Check TK14
                g_ucTkNumber = 14;
            else if (bTk15Flag == 1)         //Check TK15
                g_ucTkNumber = 15;
        }

        //if (TKSTATUS0 != 0 )
        // {
        //     g_SleepCtrl = 1;  //Entering power down mode immediately
        // }
    }
}
