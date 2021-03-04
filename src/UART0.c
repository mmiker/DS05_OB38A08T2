#include "OB38A08T2.h"
#include "UART0.h"

//===============================================================
//DEFINITIONs
//===============================================================
#define d_S0RELH        0x03
#define d_S0RELL        0xF7

#define UART0_BUFFLEN 20
//===============================================================
//GLOBAL VARIABLE
//===============================================================
bit bU0TX = 0;
unsigned char UART0_RXBUF[UART0_BUFFLEN];
unsigned char UART0_RXLEN = 0;
//=========================================================================
void UART0_init(void)
{
	unsigned char i;
    S0RELH   = d_S0RELH;
    S0RELL   = d_S0RELL;
    AUX     |= 0x90;            // BRS = 1,SICS = 01
    PCON    |= 0x80;            // SMOD =1
    IEN0    |= 0x90;            // EA=1, ES0=1, interrupt enable
    S0CON    = 0x50;            // mode 1, SM20=0, Revice enable
    TI       = 0;

	for(i=0;i<UART0_BUFFLEN;i++)
		UART0_RXBUF[i] = 0;
	UART0_RXLEN = 0;
}

void UART0_ISR(void) interrupt d_UART0_Vector
{
    if (RI)                     // INT_RX
    {
        RI = 0;                 // RI clear
        if(UART0_RXLEN<UART0_BUFFLEN)
        	UART0_RXBUF[UART0_RXLEN++] = S0BUF;         // Read BUF, user code...
    }
    else                        // INT_TX
    {
        bU0TX  = 0;
        TI     = 0;             // TI clear
    }
}

void UART0_TX(unsigned char n_temp0)
{
    bU0TX = 1;
    S0BUF = n_temp0;
    while(bU0TX);
}
//=========================================================================
