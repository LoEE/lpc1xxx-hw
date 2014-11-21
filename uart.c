/*
   UART functions for NXP LPC1xxx processors.

   For more details see:
       https://bitbucket.org/LoEE/lpc1xxx-hw/

   Copyright (c) 2008-2011 LoEE - Jakub Piotr Cłapa
   This program is released under the new BSD license.

   TODO: improve TX buffering
 */

#include "hw.h"

#if defined(LPC12xx) || defined(LPC13xx) || defined(LPC17xx)
#include "uart-16550.c"
#elif defined(LPC15xx)
#include "uart-nxp.c"
#else
#error Unknown processor family.
#endif

NOINLINE void uart_putc (UART_Regs *UART, int c)
{
  while (!uart_tx_empty (UART));
  uart_putc_nowait (UART, c);
}

NOINLINE void uart_set9 (UART_Regs *UART, int c)
{
  while (!uart_tx_finished (UART));
  uart_set9_nowait (UART, c);
}

NOINLINE int uart_getc (UART_Regs *UART)
{
  while (!uart_rx_ready (UART));
  return uart_getc_nowait (UART);
}

void uart_putc_hex (UART_Regs *UART, int c)
{
  static const char hex_digits[] = "0123456789abcdef";

  while (!uart_tx_empty (UART));
  uart_putc_nowait (UART, hex_digits [c >> 4]);
  uart_putc_nowait (UART, hex_digits [c & 0xf]);
}

void uart_put (UART_Regs *UART, const void *x, int len)
{
  const char *s = x;
  while (len--)
    uart_putc (UART, *s++);
}

void uart_rput (UART_Regs *UART, const void *x, int len)
{
  const char *s = x + len;
  while (len--)
    uart_putc (UART, *--s);
}

void uart_get (UART_Regs *UART, void *x, int len)
{
  char *s = x;
  while (len--)
    *s++ = uart_getc (UART);
}

void uart_put_hex (UART_Regs *UART, const void *x, int len)
{
  const char *s = x;
  while (len--)
    uart_putc_hex (UART, *s++);
}

void uart_rput_hex (UART_Regs *UART, const void *x, int len)
{
  const char *s = x + len;
  while (len--)
    uart_putc_hex (UART, *--s);
}

void uart_puts (UART_Regs *UART, const char *s)
{
  while (*s != 0)
    uart_putc (UART, *s++);
}
