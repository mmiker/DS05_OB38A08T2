/*--------------------------------------------------------------------------
Header file for UART0.
Modify on 2010/07/1.
--------------------------------------------------------------------------*/

#ifndef __UART0_H__
#define __UART0_H__

extern unsigned char UART0_RXBUF[];
extern unsigned char UART0_RXLEN;


void UART0_TX(unsigned char n_temp0);
void UART0_init(void);
void UART0_deinit(void);

#endif
