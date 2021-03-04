/*--------------------------------------------------------------------------
Header file for Timer0.
Modify on 2012/04/12.
--------------------------------------------------------------------------*/

#ifndef __TIMER_H__
#define __TIMER_H__

// Example Code
/*
void main(void)
{ 
    TIMER0_initialize();
    TR0  = 1;
    TR1  = 1;
    EA   = 1;
    while(1);
}
*/

void TIMER_Init(void);

void TIMER0_Start(void);
void TIMER0_Stop(void);

void TIMER1_Delay(unsigned int delay_ms);

 #endif