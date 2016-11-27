#ifndef UART_HW_H_
#define UART_HW_H_
#include "msp430g2553.h"
#include <stdint.h>
#include "ring_buffer.h"

#define RX BIT1
#define TX BIT2

#define ENABLE_RING_BUFF 1
#define DISABLE_RING_BUFF 0

static rbd_t _rbd;
static char _rbmem[8];
static uint8_t buff_state;

void config_uart(uint8_t _state);
void read_buff(void);

#endif
