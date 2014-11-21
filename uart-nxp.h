/*
   UART functions for NXP LPC1xxx processors.

   For more details see:
       https://bitbucket.org/LoEE/lpc1xxx-hw/

   Copyright (c) 2008-2011 LoEE - Jakub Piotr Cłapa
   This program is released under the new BSD license.

   TODO: improve TX buffering
 */
#ifndef UART_NXP_H
#define UART_NXP_H

enum uart_parity {
  UART_PARITY_NONE = 0,
  UART_PARITY_EVEN = 0x2,
  UART_PARITY_ODD  = 0x3,
  UART_PARITY_MASK = 0x3,
};

#define UART_ERRORS enum {                                                         \
  OVERRUN = 0, PARITY = 1<< 14, FRAMING = 1<< 13, BREAK = 0, RXNOISE = 1<< 15,     \
}

#define UART_BITS enum {                                                           \
  RXRDY = 1<< 0, RXIDLE = 1<< 1, TXRDY = 1<< 2, TXIDLE = 1<< 3, TXDISABLED = 1<< 6,\
  RXOVERRRUN = 1 << 8, RXBRK = 1<< 10, dRXBRK = 1<< 11, RXSTART = 1<< 12,          \
  RXFRAMEerr = 1<< 13, RXPARITYerr = 1<< 14, RXNOISEerr = 1<< 15, /* STAT */       \
  ENABLE = 1<< 0, CHAR_SIZEs = 2, PARITYs = 4, STOP_BITS_2 = 1<< 6, /* CFG */      \
}

#if !defined(UART_MULVAL)
// determined to be a good overall choice for clocks derived from a 12MHz oscillator:
#define UART_MULVAL 64
#endif

INLINE
void uart_setup_raw (UART_Regs *UART, int divisor, int oversampling,
                     int char_size, enum uart_parity parity, int stop_bits)
{
  UART_BITS;

  UART->CFG = 0;

  UART->OSR = oversampling - 1;
  UART->BRG = divisor - 1;

  LPC_SYSCON->FRGCTRL = UART_MULVAL << 8 | (256 - 1);

  UART->CTRL = 0;
  UART->CFG = ENABLE | (char_size - 7) << CHAR_SIZEs \
    | ((stop_bits == 2) ? STOP_BITS_2 : 0)           \
    | parity << PARITYs;
}

INLINE
void uart_setup (UART_Regs *UART, int divisor, int oversampling,
                 int char_size, enum uart_parity parity, int stop_bits)
{
  if (divisor < 0 || divisor > 0xffff)  { ERROR("Divisor value out of range [0-0xffff]."); }
  if (oversampling < 5 || oversampling > 16) { ERROR("Oversampling value out of range [5-16]."); }

  if (char_size < 7 && char_size > 9)   { ERROR("Character size out of range [7-9]."); }
  if (stop_bits != 1 && stop_bits != 2) { ERROR("Stop bits out of range [1-2]."); }

  uart_setup_raw (UART, divisor, oversampling, char_size, parity, stop_bits);
}

#ifndef UART_BAUD_ALLOWED_ERROR
#define UART_BAUD_ALLOWED_ERROR (1./100)
#endif

INLINE
void uart_baud_setup (UART_Regs *UART, int clk, int baud,
                      int char_size, enum uart_parity parity, int stop_bits)
{
  extern double fmax (double, double);
  extern double fabs (double);

  int boversampling = 16, bdivider = 0; double berror = 1;
#define UART_SETUP_W_BAUD_CHECK_OVERSAMPLING(oversampling) ({           \
    double scaled_clk = clk / (1. + UART_MULVAL / 256.) / oversampling; \
    int real_divisor = fmax (1, (double)scaled_clk / baud + 0.5);       \
    double real_baud = scaled_clk / real_divisor;                       \
    double error = (real_baud / baud - 1);                              \
    if (fabs(error) < fabs(berror)) {                                   \
      bdivider = real_divisor;                                          \
      boversampling = oversampling;                                     \
      berror = error;                                                   \
    }                                                                   \
  })
  UART_SETUP_W_BAUD_CHECK_OVERSAMPLING(10);
  UART_SETUP_W_BAUD_CHECK_OVERSAMPLING(11);
  UART_SETUP_W_BAUD_CHECK_OVERSAMPLING(12);
  UART_SETUP_W_BAUD_CHECK_OVERSAMPLING(13);
  UART_SETUP_W_BAUD_CHECK_OVERSAMPLING(14);
  UART_SETUP_W_BAUD_CHECK_OVERSAMPLING(15);
  UART_SETUP_W_BAUD_CHECK_OVERSAMPLING(16);
#undef UART_SETUP_W_BAUD_CHECK_OVERSAMPLING
  if (fabs (berror) > UART_BAUD_ALLOWED_ERROR) {
    ERROR("Failed to calculate good enough divider parameters for the given baud rate and clock.");
  }
  uart_setup (UART, bdivider, boversampling, char_size, parity, stop_bits);
}

int uart_dynamic_baud_setup (UART_Regs *UART, int clk, int baud,
    int char_size, enum uart_parity parity, int stop_bits);

#endif
