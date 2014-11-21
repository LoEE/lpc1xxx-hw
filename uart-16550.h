/*
   UART functions for NXP LPC1xxx processors.

   For more details see:
       https://bitbucket.org/LoEE/lpc1xxx-hw/

   Copyright (c) 2008-2011 LoEE - Jakub Piotr Cłapa
   This program is released under the new BSD license.

   TODO: improve TX buffering
 */
#ifndef UART_16550_H
#define UART_16550_H

enum uart_parity {
  UART_PARITY_NONE = 0,
  UART_PARITY_ODD  = 1 | 0 <<1,
  UART_PARITY_EVEN = 1 | 1 <<1,
  UART_PARITY_ONE  = 1 | 2 <<1,
  UART_PARITY_ZERO = 1 | 3 <<1,
  UART_PARITY_MASK = 7,
};

#define UART_ERRORS enum {                                                         \
  OVERRUN = 1<< (1+8), PARITY = 1<< (2+8), FRAMING = 1<< (3+8), BREAK = 1<< (4+8), \
}

#define UART_BITS enum {                                                         \
  RXFE = 1<< 7, TEMT = 1<< 6, THRE = 1<< 5, FE = 1<< 3,                          \
  PE = 1<< 2, OE = 1<< 1, RDR = 1<< 0,                           /* UART->LSR */ \
  DIVADDVAL = 0, MULVAL = 4,                                     /* UART->FDR */ \
  FIFO_EN = 1<< 0, RX_FIFO_RESET = 1<< 1, TX_FIFO_RESET = 1<< 2, /* UART->FCR */ \
  RX_TRIG_SELECT = 6,                                                            \
  CHAR_SIZE = 0, STOP_BITS = 1<< 2, PARITY = 3, BREAK = 1<< 6,   /* UART->LCR */ \
  DLAB = 1<< 7,                                                                  \
  TXEN = 1<< 7,                                                  /* UART->TER */ \
  RX_INT = 1<< 0, TX_INT = 1<< 1, RXERR_INT = 1<< 2,             /* UART->IER */ \
  FIFOLVL_MAX = 16,                                              /* misc      */ \
}

INLINE
void uart_setup_raw (UART_Regs *UART, int divisor, int mulval, int divaddval,
                     int char_size, enum uart_parity parity, int stop_bits)
{
  UART_BITS;

  UART->LCR = DLAB;
  UART->DLM = (divisor & 0xff00) >> 8;
  UART->DLL = (divisor & 0x00ff);

  UART->FDR = divaddval <<DIVADDVAL | mulval <<MULVAL;

  UART->LCR = (char_size - 5) <<CHAR_SIZE \
    | ((stop_bits == 2) ? STOP_BITS : 0)  \
    | parity <<PARITY;

  UART->TER = TXEN;

  UART->FCR = FIFO_EN | RX_FIFO_RESET | TX_FIFO_RESET;
  UART->IER = RX_INT;
}

INLINE
void uart_setup (UART_Regs *UART, int divisor, int mulval, int divaddval,
                 int char_size, enum uart_parity parity, int stop_bits)
{
  if (divisor > 0xffff)                 { ERROR("Divisor value out of range [0-0xffff]."); }
  if (mulval <= 0 || mulval > 15)       { ERROR("Multiplier value out of range [1-15]."); }
  if (divaddval < 0)                    { ERROR("Divider-Add value must not be less then 0."); }
  if (divaddval >= mulval)              { ERROR("Divider-Add value must be less then Multiplier."); }

  if (char_size < 5 && char_size > 8)   { ERROR("Character size out of range [5-8]."); }
  if (stop_bits != 1 && stop_bits != 2) { ERROR("Stop bits out of range [1-2]."); }

  uart_setup_raw (UART, divisor, mulval, divaddval, char_size, parity, stop_bits);
}

#ifndef UART_BAUD_ALLOWED_ERROR
#define UART_BAUD_ALLOWED_ERROR (0.2/100)
#endif

INLINE
void uart_baud_setup (UART_Regs *UART, int clk, int baud,
                      int char_size, enum uart_parity parity, int stop_bits)
{
  extern double fmax (double, double);
  extern double fabs (double);

  int bmulval = 1, bdivaddval = 0, bdivider = 0; double berror = 1;
#define UART_SETUP_W_BAUD_CHECK_FRAC(mulval, divaddval) ({              \
    if (mulval > divaddval) {                                           \
      double scaled_clk = clk / 16. / ((double)divaddval / mulval + 1); \
      int real_divisor = fmax (1, (double)scaled_clk / baud + 0.5);     \
      double real_baud = scaled_clk / real_divisor;                     \
      double error = (real_baud / baud - 1);                            \
      if (fabs(error) < fabs(berror)) {                                 \
        bdivider = real_divisor;                                        \
        bmulval = mulval;                                               \
        bdivaddval = divaddval;                                         \
        berror = error;                                                 \
      }                                                                 \
    }                                                                   \
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
  uart_setup (UART, bdivider, bmulval, bdivaddval, char_size, parity, stop_bits);
}

#endif
