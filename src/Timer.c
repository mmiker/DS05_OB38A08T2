#include "OB38A08T2.h"
#include "Timer.h"

#define TIMER0_VECTOR   d_T0_Vector       //TIMER0 Interrupt Vevtor
#define TIMER1_VECTOR   d_T1_Vector       //TIMER1 Interrupt Vevtor
#define TIMER3_VECTOR   d_T3_Vector       //TIMER3 Interrupt Vevtor
#define d_T0MOD         0x02    //TMOD[3:0] TIMER0 Mode setting
#define d_T1MOD         0x02    //TMOD[7:4] TIMER1 Mode setting
#define d_T3MOD         0x02    //T3MOD[3:0] TIMER3 Mode setting
#define ET3             0x01    //TIMER3 overflow Interrupt Enable (Default 0 Disable)
#define ET2             0x00    //TIMER2 overflow Interrupt Enable (Default 0 Disable)
#define ET1             0x01    //TIMER1 overflow Interrupt Enable (Default 0 Disable)
#define ET0             0x01    //TIMER0 overflow Interrupt Enable (Default 0 Disable)

#define d_MODEVALUE_T0      256    //MODE2 8bit 256(Auto Reload)
#define d_RELOADVALUE_T0    200    //User Define Reload Value

#define d_MODEVALUE_T1      256    //MODE2 8bit 256(Auto Reload)
#define d_RELOADVALUE_T1    167    //User Define Reload Value

#define d_MODEVALUE_T3      65536     //MODE1 16bit 65536
#define d_RELOADVALUE_T3    48870      //User Define Reload Value

unsigned int timer1_delay_count;
void TIMER_Init(void)  //Initialize TIMER0
{
    IEN0 |= (ET3<<6)|(ET2<<5)|(ET1<<3)|(ET0<<1); //IE=IEN0
    TMOD  = (d_T1MOD<<4)|(d_T0MOD);
	T3MOD = d_T3MOD;
    TH0   = (d_MODEVALUE_T0-d_RELOADVALUE_T0);  //MODE2 8bit 256(Auto Reload)
    TL0   = (d_MODEVALUE_T0-d_RELOADVALUE_T0);
    TH1   = (d_MODEVALUE_T1-d_RELOADVALUE_T1);  //MODE2 8bit 256(Auto Reload)
    TL1   = (d_MODEVALUE_T1-d_RELOADVALUE_T1);
    TH3   = (d_MODEVALUE_T3-d_RELOADVALUE_T3)/256;    //MODE1 16bit 65536
    TL3   = (d_MODEVALUE_T3-d_RELOADVALUE_T3)%256;
	
    PFCON |= (0x02<<2)|(0x02<<4);
}

void TIMER0_Start(void)
{
    TR0   = 1; //Timer0 Start bit 
}

void TIMER0_Stop(void)
{
    TR0   = 0; //Timer0 Start bit 
}


void TIMER1_Delay(unsigned int delay_ms)
{
	timer1_delay_count = delay_ms;
    TR1 = 1; 
    while(timer1_delay_count > 0);
	TR1 = 0;
}

void TIMER3_Start(void)
{
    TR3   = 1; //Timer0 Start bit 
}



void TIMER0_ISR(void) interrupt TIMER0_VECTOR
{
    // To do something by using timer interrupt. 
	extern void Audio_timer_event_handler(void);
	Audio_timer_event_handler();
}

void TIMER1_ISR(void) interrupt TIMER1_VECTOR
{
    // To do something by using timer interrupt.
    if(timer1_delay_count>0)
		timer1_delay_count--;
}

void TIMER3_ISR(void) interrupt TIMER3_VECTOR
{
		extern void System_timer_event_handler(void);    
    TH3 = (d_MODEVALUE_T0-d_RELOADVALUE_T0)/256;    //MODE1 16bit 65536
    TL3 = (d_MODEVALUE_T0-d_RELOADVALUE_T0)%256;
    
    // To do something by using timer interrupt.
    System_timer_event_handler();
}


