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
    uint32_t realbaud, mul, divadd, divider, error;
  } c, best = { .error = -1 };

  for (c.mul = 1; c.mul < 16; c.mul++) {
    for (c.divadd = 0; c.divadd < c.mul; c.divadd++) {
      c.divider = rdiv (clk * c.mul, 16 * baud * (c.mul + c.divadd));
      if (!c.divider) c.divider = 1;

      c.realbaud = rdiv (clk * c.mul, 16 * c.divider * (c.mul + c.divadd));

      /* error resolution: 0.001% */
      uint32_t abserr = absdiff (baud, c.realbaud);
      c.error = rdiv (abserr * 100000, baud);
      if (c.error < best.error) best = c;
    }
  }

  uart_setup_raw (UART,
      best.divider, best.mul, best.divadd,
      char_size, parity, stop_bits);
  return best.realbaud;
}

int uart_tx_finished (UART_Regs *UART)
{
  return UART->LSR & TEMT;
}

int uart_tx_empty (UART_Regs *UART)
{
  return UART->LSR & THRE;
}

int uart_rx_ready (UART_Regs *UART)
{
  return (UART->IIR & 0xf) == 4;
}

void uart_putc_nowait (UART_Regs *UART, int x)
{
  UART->THR = x;
}

int uart_getc_nowait (UART_Regs *UART)
{
  return UART->RBR;
}

static void uart_parity_setup (UART_Regs *UART, const int p)
{
  UART->LCR = (UART->LCR & ~(UART_PARITY_MASK<<PARITY)) | (p<<PARITY);
}

void uart_set9_nowait (UART_Regs *UART, const int c)
{
  uart_parity_setup (UART, c ? UART_PARITY_ONE : UART_PARITY_ZERO);
}

int uart_getc_status (UART_Regs *UART)
{
  int c = (UART->LSR & (0xf << 1)) << 8;
  c |= uart_getc_nowait (UART);
  return c;
}
