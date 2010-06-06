/*
 * UART functions for NXP LPC17xx.
 *
 * Copyright (c) 2008-2010 Jakub Piotr Cłapa
 * This program is released under the new BSD license.
 */
#ifndef UART_H
#define UART_H

#include "common.h"
#include "LPC17xx.h"
#include "system.h"
#include "io-pin.h"

/*
 * API
 */

#define LPC_UART_BITS enum {                         \
  TEMT = 1<< 6, RDR = 1<< 0,    /* LPC_UART->LSR */ \
  DIVADDVAL = 0, MULVAL = 4,    /* LPC_UART->FDR */ \
  FIFO_EN = 1<< 0, RX_FIFO_RESET = 1<< 1, TX_FIFO_RESET = 1<< 2, /* LPC_UART->FCR */ \
  RX_TRIG_SELECT = 6,                                \
  CHAR_SIZE = 0, STOP_BITS = 1<< 2, PARITY = 3, BREAK = 1<< 6,   /* LPC_UART->LCR */ \
  DLAB = 1<< 7,                                      \
  TXEN = 1<< 7,                 /* LPC_UART->TER */ \
  RXFIFOLVL = 0, TXFIFOLVL = 8, /* LPC_UART->FIFOLVL */ \
  FIFOLVL_MAX = 16, FIFOLVL_MASK = 0x1f,              \
}

INLINE
int uart_tx_finished (LPC_UART_TypeDef *LPC_UART)
{ 
  LPC_UART_BITS;
  return (LPC_UART->LSR & TEMT) != 0;
}

INLINE
int uart_rx_ready (LPC_UART_TypeDef *LPC_UART)
{ 
  LPC_UART_BITS;
  return (LPC_UART->LSR & RDR) != 0;
}

INLINE
int uart_tx_bytes_avail (LPC_UART_TypeDef *LPC_UART)
{
  LPC_UART_BITS;
  return FIFOLVL_MAX - ((LPC_UART->FIFOLVL >> TXFIFOLVL) & FIFOLVL_MASK);
}

INLINE
int uart_rx_bytes_avail (LPC_UART_TypeDef *LPC_UART)
{
  LPC_UART_BITS;
  return (LPC_UART->FIFOLVL >> RXFIFOLVL) & FIFOLVL_MASK;
}

INLINE
void uart_putc_nowait (LPC_UART_TypeDef *LPC_UART, unsigned char x)
{
  LPC_UART->THR = x;
}

extern void uart_putc (LPC_UART_TypeDef *LPC_UART, const char c);
extern void uart_putc_hex (LPC_UART_TypeDef *LPC_UART, const char c);

extern void uart_put  (LPC_UART_TypeDef *LPC_UART, const void *x, int len);
extern void uart_put_hex (LPC_UART_TypeDef *LPC_UART, const void *x, int len);
extern void uart_rput_hex (LPC_UART_TypeDef *LPC_UART, const void *x, int len);

extern void uart_puts (LPC_UART_TypeDef *LPC_UART, const char *x);

INLINE
unsigned char uart_getc_nowait (LPC_UART_TypeDef *LPC_UART)
{
  return LPC_UART->RBR;
}

/*
 * Setup
 */

enum uart_parity {
  UART_PARITY_NONE = 0,
  UART_PARITY_ODD  = 1 | 0 <<1,
  UART_PARITY_EVEN = 1 | 1 <<1,
  UART_PARITY_ONE  = 1 | 2 <<1,
  UART_PARITY_ZERO = 1 | 3 <<1
};

INLINE
void uart_setup (LPC_UART_TypeDef *LPC_UART, int divisor, int mulval, int divaddval,
                 int char_size, enum uart_parity parity, int stop_bits)
{
  LPC_UART_BITS;

  if (divisor > 0xffff) { ERROR("Divisor value out of range [0-0xffff]."); }
  if (mulval <= 0 || mulval > 15) { ERROR("Multiplier value out of range [1-15]."); }
  if (divaddval < 0) { ERROR("Divider-Add value must not be less then 0."); }
  if (divaddval >= mulval) { ERROR("Divider-Add value must be less then Multiplier."); }

  if (char_size < 5 && char_size > 8) { ERROR("Character size out of range [5-8]."); }
  if (stop_bits != 1 && stop_bits != 2) { ERROR("Stop bits out of range [1-2]."); }

  LPC_UART->LCR = DLAB;
  LPC_UART->DLM = (divisor & 0xff00) >> 8;
  LPC_UART->DLL = (divisor & 0x00ff);

  LPC_UART->FDR = divaddval <<DIVADDVAL | mulval <<MULVAL;

  LPC_UART->LCR = (char_size - 5) <<CHAR_SIZE           \
    | ((stop_bits == 2) ? STOP_BITS : 0)        \
    | parity <<PARITY;

  LPC_UART->TER = TXEN;

  LPC_UART->FCR = FIFO_EN | RX_FIFO_RESET | TX_FIFO_RESET;
}

#ifndef UART_BAUD_ALLOWED_ERROR
#define UART_BAUD_ALLOWED_ERROR (0.1/100)
#endif

INLINE
void uart_baud_setup (LPC_UART_TypeDef *LPC_UART, int clk, int baud,
                      int char_size, enum uart_parity parity, int stop_bits)
{
  extern double fmax (double, double);
  extern double fabs (double);

  int bmulval = 1, bdivaddval = 0, bdivider = 0; double berror = 1;
#define UART_SETUP_W_BAUD_CHECK_FRAC(mulval, divaddval) ({                 \
    if (mulval > divaddval) {                                             \
      double scaled_clk = clk / 16. / ((double)divaddval / mulval + 1);   \
      int real_divisor = fmax (1, (double)scaled_clk / baud + 0.5);        \
      double real_baud = scaled_clk / real_divisor;                       \
      double error = (real_baud / baud - 1);                              \
      if (fabs(error) < fabs(berror)) {                                     \
        bdivider = real_divisor;                                          \
        bmulval = mulval;                                                 \
        bdivaddval = divaddval;                                           \
        berror = error;                                                   \
      }                                                                   \
    }                                                                     \
  })
#define UART_SETUP_W_BAUD_CHECK_MULVAL(mulval) ({ \
    UART_SETUP_W_BAUD_CHECK_FRAC(mulval,  0);     \
    UART_SETUP_W_BAUD_CHECK_FRAC(mulval,  1);     \
    UART_SETUP_W_BAUD_CHECK_FRAC(mulval,  2);     \
    UART_SETUP_W_BAUD_CHECK_FRAC(mulval,  3);     \
    UART_SETUP_W_BAUD_CHECK_FRAC(mulval,  4);     \
    UART_SETUP_W_BAUD_CHECK_FRAC(mulval,  5);     \
    UART_SETUP_W_BAUD_CHECK_FRAC(mulval,  6);     \
    UART_SETUP_W_BAUD_CHECK_FRAC(mulval,  7);     \
    UART_SETUP_W_BAUD_CHECK_FRAC(mulval,  8);     \
    UART_SETUP_W_BAUD_CHECK_FRAC(mulval,  9);     \
    UART_SETUP_W_BAUD_CHECK_FRAC(mulval, 10);     \
    UART_SETUP_W_BAUD_CHECK_FRAC(mulval, 11);     \
    UART_SETUP_W_BAUD_CHECK_FRAC(mulval, 12);     \
    UART_SETUP_W_BAUD_CHECK_FRAC(mulval, 13);     \
    UART_SETUP_W_BAUD_CHECK_FRAC(mulval, 14);     \
  })
  UART_SETUP_W_BAUD_CHECK_MULVAL( 1);
  UART_SETUP_W_BAUD_CHECK_MULVAL( 2);
  UART_SETUP_W_BAUD_CHECK_MULVAL( 3);
  UART_SETUP_W_BAUD_CHECK_MULVAL( 4);
  UART_SETUP_W_BAUD_CHECK_MULVAL( 5);
  UART_SETUP_W_BAUD_CHECK_MULVAL( 6);
  UART_SETUP_W_BAUD_CHECK_MULVAL( 7);
  UART_SETUP_W_BAUD_CHECK_MULVAL( 8);
  UART_SETUP_W_BAUD_CHECK_MULVAL( 9);
  UART_SETUP_W_BAUD_CHECK_MULVAL(10);
  UART_SETUP_W_BAUD_CHECK_MULVAL(11);
  UART_SETUP_W_BAUD_CHECK_MULVAL(12);
  UART_SETUP_W_BAUD_CHECK_MULVAL(13);
  UART_SETUP_W_BAUD_CHECK_MULVAL(14);
  UART_SETUP_W_BAUD_CHECK_MULVAL(15);
#undef UART_SETUP_W_BAUD_CHECK_FRAC
#undef UART_SETUP_W_BAUD_CHECK_MULVAL
  if (fabs (berror) > UART_BAUD_ALLOWED_ERROR) {
    ERROR("Failed to calculate good enough divider parameters for the given baud rate and clock.");
  }
  uart_setup (LPC_UART, bdivider, bmulval, bdivaddval, char_size, parity, stop_bits);
}

INLINE
void uart_system_setup (LPC_UART_TypeDef *LPC_UART, int clk_divider, int tx_pin, int rx_pin)
{
  switch ((uint32_t)LPC_UART) {
    case (uint32_t)LPC_UART0:
      power_control (POWER_UART0, 1); pclk_set_divider (PCLK_UART0, clk_divider);
      if (tx_pin == P0+2) pin_setup (tx_pin, 1);
      else ERROR("UART0 TxD can only be on P0.2.");
      if (rx_pin == P0+3) pin_setup (rx_pin, 1);
      else ERROR("UART0 RxD can only be on P0.3.");
      break;
    case (uint32_t)LPC_UART1:
      power_control (POWER_UART1, 1); pclk_set_divider (PCLK_UART1, clk_divider);
      if (tx_pin == P0+15) pin_setup (tx_pin, 1);
      else if (tx_pin == P2+0) pin_setup (tx_pin, 2);
      else ERROR("UART1 TxD can only be on P0.15 or P2.0.");
      if (rx_pin == P0+16) pin_setup (rx_pin, 1);
      else if (rx_pin == P2+1) pin_setup (rx_pin, 2);
      else ERROR("UART1 RxD can only be on P0.16 or P2.1.");
      break;
    case (uint32_t)LPC_UART2:
      power_control (POWER_UART2, 1); pclk_set_divider (PCLK_UART2, clk_divider);
      if (tx_pin == P0+10) pin_setup (tx_pin, 1); else
      if (tx_pin == P2+ 8) pin_setup (tx_pin, 2);
      else ERROR("UART2 TxD can only be on P0.10 or P2.8.");
      if (rx_pin == P0+11) pin_setup (rx_pin, 1); else
      if (rx_pin == P2+ 9) pin_setup (rx_pin, 2);
      else ERROR("UART2 RxD can only be on P0.11 or P2.9.");
      break;
    case (uint32_t)LPC_UART3:
      power_control (POWER_UART3, 1); pclk_set_divider (PCLK_UART3, clk_divider);
      if (tx_pin == P0+ 0) pin_setup (tx_pin, 2); else
      if (tx_pin == P0+25) pin_setup (tx_pin, 3); else
      if (tx_pin == P4+28) pin_setup (tx_pin, 3);
      else ERROR("UART3 TxD can only be on P0.0, P0.25 or P4.28.");
      if (rx_pin == P0+ 1) pin_setup (rx_pin, 2); else
      if (rx_pin == P0+26) pin_setup (rx_pin, 3); else
      if (rx_pin == P4+29) pin_setup (rx_pin, 3);
      else ERROR("UART3 RxD can only be on P0.1, P0.26 or P4.29.");
      break;
    default:
      ERROR("Invalid UART register address."); break;
  }
}

#endif
