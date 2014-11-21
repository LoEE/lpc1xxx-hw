/*
   UART functions.

   For more details see:
       https://bitbucket.org/LoEE/lpc1xxx-hw/

   Copyright (c) 2008-2014 LoEE - Jakub Piotr Cłapa
   This program is released under the new BSD license.
 */
#ifndef UART_H
#define UART_H

#if defined(LPC12xx)
#define UART_Regs LPC_UART0_Type
#define UART0 ((UART_Regs *)LPC_UART0)
#define UART1 ((UART_Regs *)LPC_UART1)
#include "uart-16550.h"
#elif defined(LPC13xx)
#define UART_Regs LPC_UART_TypeDef
#define UART0 ((UART_Regs *)LPC_UART)
#include "uart-16550.h"
#elif defined(LPC15xx)
#define UART_Regs LPC_USART0_Type
#define UART0 ((UART_Regs *)LPC_USART0)
#define UART1 ((UART_Regs *)LPC_USART1)
#define UART2 ((UART_Regs *)LPC_USART2)
#include "uart-nxp.h"
#elif defined(LPC17xx)
#define UART_Regs LPC_UART_TypeDef
#define UART0 ((UART_Regs *)LPC_UART0)
#define UART1 ((UART_Regs *)LPC_UART1)
#define UART2 ((UART_Regs *)LPC_UART2)
#define UART3 ((UART_Regs *)LPC_UART3)
#include "uart-16550.h"
#else
#error Unknown processor family.
#endif

int uart_tx_finished (UART_Regs *UART);
int uart_tx_empty (UART_Regs *UART);
int uart_rx_ready (UART_Regs *UART);

int uart_tx_bytes_avail (UART_Regs *UART);

void uart_set9_nowait (UART_Regs *UART, const int c);
void uart_set9 (UART_Regs *UART, const int c);

void uart_putc_nowait (UART_Regs *UART, int c);
void uart_putc        (UART_Regs *UART, int c);
void uart_putc_hex    (UART_Regs *UART, int c);

void uart_put      (UART_Regs *UART, const void *x, int len);
void uart_put_hex  (UART_Regs *UART, const void *x, int len);
void uart_rput     (UART_Regs *UART, const void *x, int len);
void uart_rput_hex (UART_Regs *UART, const void *x, int len);

void uart_puts     (UART_Regs *UART, const char *x);

int uart_getc_nowait (UART_Regs *UART);
int uart_getc        (UART_Regs *UART);
int uart_getc_status (UART_Regs *UART);

void uart_get  (UART_Regs *UART, void *x, int len);

// int uart_dynamic_baud_setup (UART_Regs *UART, int clk, int baud,
//     int char_size, enum uart_parity parity, int stop_bits);

// inlined baudrate configuration procedures are in device-specific header files

#endif
