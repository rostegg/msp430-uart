#include "uart_hw.h"

void config_uart(uint8_t _state)
{
	buff_state = _state;
	WDTCTL = WDTPW + WDTHOLD;
    P1DIR = BIT0;
	P1OUT = ~BIT0;
	DCOCTL = 0;
	BCSCTL1 = CALBC1_1MHZ;
	DCOCTL = CALDCO_1MHZ;
	P1SEL = BIT1 | BIT2 ;
	P1SEL2 = BIT1 | BIT2;
	if (buff_state == ENABLE_RING_BUFF)
	{
		rb_attr_t attr = {sizeof(_rbmem[0]), ARRAY_SIZE(_rbmem), _rbmem};
		if (ring_buffer_init(&_rbd, &attr) != 0)
			exit(-1);
	}
	UCA0CTL1 = UCSWRST;
	UCA0CTL1 |= UCSSEL_2;
	UCA0BR0 = 104;
	UCA0BR1 = 0;
	UCA0MCTL = UCBRS0;
	UCA0CTL1 &= ~UCSWRST;
	IE2 |= UCA0RXIE;
	__bis_SR_register(LPM0_bits + GIE);
}

void read_buff(void)
{
    if (IFG2 & UCA0RXIFG) {
        const char c = UCA0RXBUF;
        IFG2 &= ~UCA0RXIFG;
        ring_buffer_put(_rbd, &c);
    }
}
