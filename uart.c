/*
 * UART functions for NXP LPC17xx.
 *
 * Copyright (c) 2008-2010 Jakub Piotr Cłapa
 * This program is released under the new BSD license.
 */
#include "uart.h"

void __attribute__((__noinline__)) uart_putc (LPC_UART_TypeDef *LPC_UART, const char c)
{
  while (!uart_tx_bytes_avail (LPC_UART));
  uart_putc_nowait (LPC_UART, c);
}

void uart_putc_hex (LPC_UART_TypeDef *LPC_UART, const char c)
{
  static char *hex_digits = "0123456789abcdef";

  while (uart_tx_bytes_avail (LPC_UART) < 2);
  uart_putc_nowait (LPC_UART, hex_digits [c >> 4]);
  uart_putc_nowait (LPC_UART, hex_digits [c & 0xf]);
}

void uart_put (LPC_UART_TypeDef *LPC_UART, const void *x, int len)
{
  const char *s = x;
  while (len--)
    uart_putc (LPC_UART, *s++);
}

void uart_put_hex (LPC_UART_TypeDef *LPC_UART, const void *x, int len)
{
  const char *s = x;
  while (len--)
    uart_putc_hex (LPC_UART, *s++);
}

void uart_rput_hex (LPC_UART_TypeDef *LPC_UART, const void *x, int len)
{
  const char *s = x + len;
  while (len--)
    uart_putc_hex (LPC_UART, *--s);
}

void uart_puts (LPC_UART_TypeDef *LPC_UART, const char *s)
{
  while (*s != 0)
    uart_putc (LPC_UART, *s++);
}
