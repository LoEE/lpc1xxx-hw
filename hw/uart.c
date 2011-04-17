/*
   UART functions for NXP LPC1xxx processors.

   For more details see:
       http://bitbucket.org/jpc/lpc1xxx-hw/
 
   Copyright (c) 2008-2011 LoEE - Jakub Piotr Cłapa
   This program is released under the new BSD license.
 */

#include "hw.h"

int tx_fifo_lvl = 0;

void __attribute__((__noinline__)) uart_putc (UART_TypeDef *UART, const char c)
{
  UART_BITS;
  if (tx_fifo_lvl == FIFOLVL_MAX) {
    while (!uart_tx_empty (UART));
    tx_fifo_lvl = 0;
  }
  tx_fifo_lvl++;
  uart_putc_nowait (UART, c);
}

int uart_tx_bytes_avail (UART_TypeDef *UART)
{
  UART_BITS;
  UART = UART;
  return FIFOLVL_MAX - tx_fifo_lvl;
}

char __attribute__((__noinline__)) uart_getc (UART_TypeDef *UART)
{
  while (!uart_rx_ready (UART));
  return uart_getc_nowait (UART);
}

void uart_putc_hex (UART_TypeDef *UART, const char c)
{
  static char hex_digits[] = "0123456789abcdef";

  while (uart_tx_bytes_avail (UART) < 2);
  uart_putc_nowait (UART, hex_digits [c >> 4]);
  uart_putc_nowait (UART, hex_digits [c & 0xf]);
}

void uart_put (UART_TypeDef *UART, const void *x, int len)
{
  const char *s = x;
  while (len--)
    uart_putc (UART, *s++);
}

void uart_get (UART_TypeDef *UART, void *x, int len)
{
  char *s = x;
  while (len--)
    *s++ = uart_getc (UART);
}

void uart_put_hex (UART_TypeDef *UART, const void *x, int len)
{
  const char *s = x;
  while (len--)
    uart_putc_hex (UART, *s++);
}

void uart_rput_hex (UART_TypeDef *UART, const void *x, int len)
{
  const char *s = x + len;
  while (len--)
    uart_putc_hex (UART, *--s);
}

void uart_puts (UART_TypeDef *UART, const char *s)
{
  while (*s != 0)
    uart_putc (UART, *s++);
}
