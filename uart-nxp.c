/*
   UART functions for NXP LPC1xxx processors.

   For more details see:
       https://bitbucket.org/LoEE/lpc1xxx-hw/

   Copyright (c) 2008-2011 LoEE - Jakub Piotr Cłapa
   This program is released under the new BSD license.

   TODO: improve TX buffering
 */

#include "hw.h"

UART_BITS;

#define rdiv(num, denom) ({ \
    typeof(num) __num__ = (num); \
    typeof(denom) __denom__ = (denom); \
    (__num__ + __denom__ / 2) / __denom__; \
  })

#define absdiff(x, y) ({ \
    int __x__ = (int)(x - y); \
    (unsigned) (__x__ < 0 ? - __x__ : __x__); \
  })

int uart_dynamic_baud_setup (UART_Regs *UART, int clk, int baud,
                      int char_size, enum uart_parity parity, int stop_bits)
{
  struct setup {
    uint32_t realbaud, oversampling, divider, error;
  } c, best = { .error = -1 };

  for (c.oversampling = 5; c.oversampling <= 16; c.oversampling++) {
    c.divider = rdiv (clk * 256, c.oversampling * baud * (256 + UART_MULVAL));
    if (c.divider > 0xffff) c.divider = 0xffff;
    if (!c.divider) c.divider = 1;

    c.realbaud = rdiv (clk * 256, c.oversampling * c.divider * (256 + UART_MULVAL));

    /* error resolution: 0.001% */
    uint32_t abserr = absdiff (baud, c.realbaud);
    c.error = rdiv (abserr * 100000, baud);
    if (c.error < best.error) best = c;
  }

  uart_setup_raw (UART,
      best.divider, best.oversampling,
      char_size, parity, stop_bits);
  return best.realbaud;
}

int uart_tx_finished (UART_Regs *UART)
{
  return UART->STAT & TXIDLE;
}

int uart_tx_empty (UART_Regs *UART)
{
  return UART->STAT & TXRDY;
}

int uart_rx_ready (UART_Regs *UART)
{
  return UART->STAT & RXRDY;
}

void uart_putc_nowait (UART_Regs *UART, int c)
{
  UART->TXDATA = c;
}

int uart_getc_nowait (UART_Regs *UART)
{
  return UART->RXDATA;
}

int uart_getc_status (UART_Regs *UART)
{
  return UART->RXDATASTAT;
}
