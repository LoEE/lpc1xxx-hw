/*
   IO functions for NXP LPC151x devices in LQFP64 package.

   This is an automatically generated file. For more details see:
       https://bitbucket.org/LoEE/lpc1xxx-hw/

   Copyright (c) 2010-2011 LoEE - Jakub Piotr Cłapa
   This program is released under the new BSD license.
*/
#ifndef IO_PIN_H
#define IO_PIN_H

enum pin_dir {
  PIN_IN = 0,
  PIN_OUT = 1,
};

enum io_mode {
  PULL_NONE = 0 << 3,
  PULL_DOWN = 1 << 3,
  PULL_UP = 2 << 3,
  PULL_REPEATER = 3 << 3,

  IN_HYSTERESIS = 1 << 5,
  IN_INVERT = 1 << 6,

  OUT_OPENDRAIN = 1 << 10,

  I2C_STD = 0 << 8,
  I2C_FAST = 0 << 8,
  I2C_GPIO = 1 << 8,
  I2C_FAST_PLUS = 2 << 8,
};

enum io_filter {
  IN_DEGLITCH = 1 << 8,
};

enum io_function {
  ADC0_10, SCT0_OUT3, ADC0_7, SCT0_OUT4, ADC0_6, SCT1_OUT3, ADC0_5, SCT1_OUT4, ADC0_4, ADC0_3, ADC0_2, SCT2_OUT3, ADC0_1, ADC0_0, TDO, ADC1_1, TDI, ADC1_2, ADC1_3, DAC_OUT, ADC1_6, ADC1_7, SCT1_OUT5, ADC1_8, ADC1_9, WAKEUP, nTRST, SCT0_OUT5, SWCLK, TCK, SWDIO, SCT1_OUT6, TMS, nRESET, I2C0_SCL, I2C0_SDA, SCT0_OUT6, ACMP0_I4, ACMP0_I3, SCT3_OUT3, ACMP_I1, ACMP1_I3, ACMP2_I3, SCT2_OUT4, ADC0_11, ADC0_9, ADC0_8, ADC1_0, ADC1_4, ADC1_5, ADC1_10, ADC1_11, ACMP_I2, ACMP3_I4, ACMP3_I3, SCT3_OUT4, ACMP2_I4, ACMP1_I4, MOVABLE = 0xff,
  U0_TXD, U0_RXD, U0_RTS, U0_CTS, U0_SCLK, U1_TXD, U1_RXD, U1_RTS, U1_CTS, U1_SCLK, U2_TXD, U2_RXD, U2_SCLK, SPI0_SCK, SPI0_MOSI, SPI0_MISO, SPI0_SSEL0, SPI0_SSEL1, SPI0_SSEL2, SPI0_SSEL3, SPI1_SCK, SPI1_MOSI, SPI1_MISO, SPI1_SSEL0, SPI1_SSEL1, CAN0_TD, CAN0_RD, CAN0_RESERVED, USB_VBUS, SCT0_OUT0, SCT0_OUT1, SCT0_OUT2, SCT1_OUT0, SCT1_OUT1, SCT1_OUT2, SCT2_OUT0, SCT2_OUT1, SCT2_OUT2, SCT3_OUT0, SCT3_OUT1, SCT3_OUT2, SCT_ABORT0, SCT_ABORT1, ADC0_PINTRIG0, ADC0_PINTRIG1, ADC1_PINTRIG0, ADC1_PINTRIG1, DAC_PINTRIG, DAC_SHUTOFF, ACMP0_O, ACMP1_O, ACMP2_O, ACMP3_O, CLKOUT, ROSC, ROSC_RESET, USB_FTOGGLE, QEI_PHA, QEI_PHB, QEI_IDX, GPIO_INT_BMAT, SWO, LPC15xx_MAX_FUNCTION
};

enum pio_pin {
  P0_0, P0_1, P0_2, P0_3, P0_4, P0_5, P0_6, P0_7, P0_8, P0_9, P0_10, P0_11, P0_12, P0_13, P0_14, P0_15, P0_16, P0_17, P0_18, P0_19, P0_20, P0_21, P0_22, P0_23, P0_24, P0_25, P0_26, P0_27, P0_28, P0_29, P0_30, P0_31, P1_0, P1_1, P1_2, P1_3, P1_4, P1_5, P1_6, P1_7, P1_8, P1_9, P1_10, P1_11, P2_12, P2_13, NOT_CONNECTED, LPC15xx_MAX_PIN
};

INLINE
void pin_setup (enum pio_pin pin, enum io_function func, enum io_mode mode)
{
  mode |= 1 << 7; // reserved
  void set_pinenable(int pin, int on) {
    int reg = pin / 32, shift = pin % 32, mask = 1 << shift;
    LPC_SWM->PINENABLE[reg] = (LPC_SWM->PINENABLE[reg] & ~mask) | (on ? 0 : 1 << shift);
  }
  switch (pin) {
    case P0_0:
      set_pinenable(10, func == ADC0_10);
      set_pinenable(37, func == SCT0_OUT3);
      LPC_IOCON->PIO0_0 = mode;
      break;
    case P0_1:
      set_pinenable(7, func == ADC0_7);
      set_pinenable(38, func == SCT0_OUT4);
      LPC_IOCON->PIO0_1 = mode;
      break;
    case P0_2:
      set_pinenable(6, func == ADC0_6);
      set_pinenable(42, func == SCT1_OUT3);
      LPC_IOCON->PIO0_2 = mode;
      break;
    case P0_3:
      set_pinenable(5, func == ADC0_5);
      set_pinenable(43, func == SCT1_OUT4);
      LPC_IOCON->PIO0_3 = mode;
      break;
    case P0_4:
      set_pinenable(4, func == ADC0_4);
      LPC_IOCON->PIO0_4 = mode;
      break;
    case P0_5:
      set_pinenable(3, func == ADC0_3);
      LPC_IOCON->PIO0_5 = mode;
      break;
    case P0_6:
      set_pinenable(2, func == ADC0_2);
      set_pinenable(47, func == SCT2_OUT3);
      LPC_IOCON->PIO0_6 = mode;
      break;
    case P0_7:
      set_pinenable(1, func == ADC0_1);
      LPC_IOCON->PIO0_7 = mode;
      break;
    case P0_8:
      set_pinenable(0, func == ADC0_0);
      LPC_IOCON->PIO0_8 = mode;
      break;
    case P0_9:
      set_pinenable(13, func == ADC1_1);
      LPC_IOCON->PIO0_9 = mode;
      break;
    case P0_10:
      set_pinenable(14, func == ADC1_2);
      LPC_IOCON->PIO0_10 = mode;
      break;
    case P0_11:
      set_pinenable(15, func == ADC1_3);
      LPC_IOCON->PIO0_11 = mode;
      break;
    case P0_12:
      set_pinenable(24, func == DAC_OUT);
      LPC_IOCON->PIO0_12 = mode;
      break;
    case P0_13:
      set_pinenable(18, func == ADC1_6);
      LPC_IOCON->PIO0_13 = mode;
      break;
    case P0_14:
      set_pinenable(19, func == ADC1_7);
      set_pinenable(44, func == SCT1_OUT5);
      LPC_IOCON->PIO0_14 = mode;
      break;
    case P0_15:
      set_pinenable(20, func == ADC1_8);
      LPC_IOCON->PIO0_15 = mode;
      break;
    case P0_16:
      set_pinenable(21, func == ADC1_9);
      LPC_IOCON->PIO0_16 = mode;
      break;
    case P0_17:
      LPC_IOCON->PIO0_17 = mode;
      break;
    case P0_18:
      set_pinenable(39, func == SCT0_OUT5);
      LPC_IOCON->PIO0_18 = mode;
      break;
    case P0_19:
      set_pinenable(54, func == SWCLK);
      LPC_IOCON->PIO0_19 = mode;
      break;
    case P0_20:
      set_pinenable(55, func == SWDIO);
      set_pinenable(45, func == SCT1_OUT6);
      LPC_IOCON->PIO0_20 = mode;
      break;
    case P0_21:
      LPC_IOCON->PIO0_21 = mode;
      break;
    case P0_22:
      set_pinenable(36, func == I2C0_SCL);
      if (mode & 0x3f)
        ERROR("Pull resistors and hysteresis are not available on I2C pins.");
      LPC_IOCON->PIO0_22 = mode;
      break;
    case P0_23:
      set_pinenable(35, func == I2C0_SDA);
      if (mode & 0x3f)
        ERROR("Pull resistors and hysteresis are not available on I2C pins.");
      LPC_IOCON->PIO0_23 = mode;
      break;
    case P0_24:
      set_pinenable(40, func == SCT0_OUT6);
      LPC_IOCON->PIO0_24 = mode;
      break;
    case P0_25:
      set_pinenable(28, func == ACMP0_I4);
      LPC_IOCON->PIO0_25 = mode;
      break;
    case P0_26:
      set_pinenable(27, func == ACMP0_I3);
      set_pinenable(50, func == SCT3_OUT3);
      LPC_IOCON->PIO0_26 = mode;
      break;
    case P0_27:
      set_pinenable(25, func == ACMP_I1);
      LPC_IOCON->PIO0_27 = mode;
      break;
    case P0_28:
      set_pinenable(29, func == ACMP1_I3);
      LPC_IOCON->PIO0_28 = mode;
      break;
    case P0_29:
      set_pinenable(31, func == ACMP2_I3);
      set_pinenable(48, func == SCT2_OUT4);
      LPC_IOCON->PIO0_29 = mode;
      break;
    case P0_30:
      set_pinenable(11, func == ADC0_11);
      LPC_IOCON->PIO0_30 = mode;
      break;
    case P0_31:
      set_pinenable(9, func == ADC0_9);
      LPC_IOCON->PIO0_31 = mode;
      break;
    case P1_0:
      set_pinenable(8, func == ADC0_8);
      LPC_IOCON->PIO1_0 = mode;
      break;
    case P1_1:
      set_pinenable(12, func == ADC1_0);
      LPC_IOCON->PIO1_1 = mode;
      break;
    case P1_2:
      set_pinenable(16, func == ADC1_4);
      LPC_IOCON->PIO1_2 = mode;
      break;
    case P1_3:
      set_pinenable(17, func == ADC1_5);
      LPC_IOCON->PIO1_3 = mode;
      break;
    case P1_4:
      set_pinenable(22, func == ADC1_10);
      LPC_IOCON->PIO1_4 = mode;
      break;
    case P1_5:
      set_pinenable(23, func == ADC1_11);
      LPC_IOCON->PIO1_5 = mode;
      break;
    case P1_6:
      set_pinenable(26, func == ACMP_I2);
      LPC_IOCON->PIO1_6 = mode;
      break;
    case P1_7:
      set_pinenable(34, func == ACMP3_I4);
      LPC_IOCON->PIO1_7 = mode;
      break;
    case P1_8:
      set_pinenable(33, func == ACMP3_I3);
      set_pinenable(51, func == SCT3_OUT4);
      LPC_IOCON->PIO1_8 = mode;
      break;
    case P1_9:
      set_pinenable(32, func == ACMP2_I4);
      LPC_IOCON->PIO1_9 = mode;
      break;
    case P1_10:
      set_pinenable(30, func == ACMP1_I4);
      LPC_IOCON->PIO1_10 = mode;
      break;
    default:
      ERROR("Invalid IO pin.");
  }
  if (func > MOVABLE)
    ERROR("Movable functions are set using pin_setup_function.");
}

INLINE
void pin_setup_function(enum io_function func, enum pio_pin pin)
{
  if(func <= MOVABLE) ERROR("pin_setup_function only deals with movable functions.");
  if(pin >= LPC15xx_MAX_PIN) ERROR("Invalid IO pin.");
  if(pin == NOT_CONNECTED) pin = 0xff;
  func -= MOVABLE + 1;
  int reg = func / 4, shift = (func % 4) * 8, mask = 0xff << shift;
  LPC_SWM->PINASSIGN[reg] = (LPC_SWM->PINASSIGN[reg] & ~mask) | (pin << shift);
}

INLINE
void pin_setup_filter(enum pio_pin pin, int samples, int clocks, enum io_filter flags) {
  enum { FILTER_MASK = IN_DEGLITCH | 0xF800 };
  // FIXME: not implemented
}

INLINE
void pin_write (enum pio_pin pin, int val)
{
  switch (pin) {
    case P0_0: LPC_GPIO_PORT->B[P0_0] = val ? 1 : 0; break;
    case P0_1: LPC_GPIO_PORT->B[P0_1] = val ? 1 : 0; break;
    case P0_2: LPC_GPIO_PORT->B[P0_2] = val ? 1 : 0; break;
    case P0_3: LPC_GPIO_PORT->B[P0_3] = val ? 1 : 0; break;
    case P0_4: LPC_GPIO_PORT->B[P0_4] = val ? 1 : 0; break;
    case P0_5: LPC_GPIO_PORT->B[P0_5] = val ? 1 : 0; break;
    case P0_6: LPC_GPIO_PORT->B[P0_6] = val ? 1 : 0; break;
    case P0_7: LPC_GPIO_PORT->B[P0_7] = val ? 1 : 0; break;
    case P0_8: LPC_GPIO_PORT->B[P0_8] = val ? 1 : 0; break;
    case P0_9: LPC_GPIO_PORT->B[P0_9] = val ? 1 : 0; break;
    case P0_10: LPC_GPIO_PORT->B[P0_10] = val ? 1 : 0; break;
    case P0_11: LPC_GPIO_PORT->B[P0_11] = val ? 1 : 0; break;
    case P0_12: LPC_GPIO_PORT->B[P0_12] = val ? 1 : 0; break;
    case P0_13: LPC_GPIO_PORT->B[P0_13] = val ? 1 : 0; break;
    case P0_14: LPC_GPIO_PORT->B[P0_14] = val ? 1 : 0; break;
    case P0_15: LPC_GPIO_PORT->B[P0_15] = val ? 1 : 0; break;
    case P0_16: LPC_GPIO_PORT->B[P0_16] = val ? 1 : 0; break;
    case P0_17: LPC_GPIO_PORT->B[P0_17] = val ? 1 : 0; break;
    case P0_18: LPC_GPIO_PORT->B[P0_18] = val ? 1 : 0; break;
    case P0_19: LPC_GPIO_PORT->B[P0_19] = val ? 1 : 0; break;
    case P0_20: LPC_GPIO_PORT->B[P0_20] = val ? 1 : 0; break;
    case P0_21: LPC_GPIO_PORT->B[P0_21] = val ? 1 : 0; break;
    case P0_22: LPC_GPIO_PORT->B[P0_22] = val ? 1 : 0; break;
    case P0_23: LPC_GPIO_PORT->B[P0_23] = val ? 1 : 0; break;
    case P0_24: LPC_GPIO_PORT->B[P0_24] = val ? 1 : 0; break;
    case P0_25: LPC_GPIO_PORT->B[P0_25] = val ? 1 : 0; break;
    case P0_26: LPC_GPIO_PORT->B[P0_26] = val ? 1 : 0; break;
    case P0_27: LPC_GPIO_PORT->B[P0_27] = val ? 1 : 0; break;
    case P0_28: LPC_GPIO_PORT->B[P0_28] = val ? 1 : 0; break;
    case P0_29: LPC_GPIO_PORT->B[P0_29] = val ? 1 : 0; break;
    case P0_30: LPC_GPIO_PORT->B[P0_30] = val ? 1 : 0; break;
    case P0_31: LPC_GPIO_PORT->B[P0_31] = val ? 1 : 0; break;
    case P1_0: LPC_GPIO_PORT->B[P1_0] = val ? 1 : 0; break;
    case P1_1: LPC_GPIO_PORT->B[P1_1] = val ? 1 : 0; break;
    case P1_2: LPC_GPIO_PORT->B[P1_2] = val ? 1 : 0; break;
    case P1_3: LPC_GPIO_PORT->B[P1_3] = val ? 1 : 0; break;
    case P1_4: LPC_GPIO_PORT->B[P1_4] = val ? 1 : 0; break;
    case P1_5: LPC_GPIO_PORT->B[P1_5] = val ? 1 : 0; break;
    case P1_6: LPC_GPIO_PORT->B[P1_6] = val ? 1 : 0; break;
    case P1_7: LPC_GPIO_PORT->B[P1_7] = val ? 1 : 0; break;
    case P1_8: LPC_GPIO_PORT->B[P1_8] = val ? 1 : 0; break;
    case P1_9: LPC_GPIO_PORT->B[P1_9] = val ? 1 : 0; break;
    case P1_10: LPC_GPIO_PORT->B[P1_10] = val ? 1 : 0; break;
    case P1_11: LPC_GPIO_PORT->B[P1_11] = val ? 1 : 0; break;
    case P2_12: LPC_GPIO_PORT->B[P2_12] = val ? 1 : 0; break;
    case P2_13: LPC_GPIO_PORT->B[P2_13] = val ? 1 : 0; break;
    default:
      ERROR("Invalid IO pin.");
  }
}

INLINE
int pin_read (enum pio_pin pin)
{
  switch (pin) {
    case P0_0: return LPC_GPIO_PORT->B[P0_0];
    case P0_1: return LPC_GPIO_PORT->B[P0_1];
    case P0_2: return LPC_GPIO_PORT->B[P0_2];
    case P0_3: return LPC_GPIO_PORT->B[P0_3];
    case P0_4: return LPC_GPIO_PORT->B[P0_4];
    case P0_5: return LPC_GPIO_PORT->B[P0_5];
    case P0_6: return LPC_GPIO_PORT->B[P0_6];
    case P0_7: return LPC_GPIO_PORT->B[P0_7];
    case P0_8: return LPC_GPIO_PORT->B[P0_8];
    case P0_9: return LPC_GPIO_PORT->B[P0_9];
    case P0_10: return LPC_GPIO_PORT->B[P0_10];
    case P0_11: return LPC_GPIO_PORT->B[P0_11];
    case P0_12: return LPC_GPIO_PORT->B[P0_12];
    case P0_13: return LPC_GPIO_PORT->B[P0_13];
    case P0_14: return LPC_GPIO_PORT->B[P0_14];
    case P0_15: return LPC_GPIO_PORT->B[P0_15];
    case P0_16: return LPC_GPIO_PORT->B[P0_16];
    case P0_17: return LPC_GPIO_PORT->B[P0_17];
    case P0_18: return LPC_GPIO_PORT->B[P0_18];
    case P0_19: return LPC_GPIO_PORT->B[P0_19];
    case P0_20: return LPC_GPIO_PORT->B[P0_20];
    case P0_21: return LPC_GPIO_PORT->B[P0_21];
    case P0_22: return LPC_GPIO_PORT->B[P0_22];
    case P0_23: return LPC_GPIO_PORT->B[P0_23];
    case P0_24: return LPC_GPIO_PORT->B[P0_24];
    case P0_25: return LPC_GPIO_PORT->B[P0_25];
    case P0_26: return LPC_GPIO_PORT->B[P0_26];
    case P0_27: return LPC_GPIO_PORT->B[P0_27];
    case P0_28: return LPC_GPIO_PORT->B[P0_28];
    case P0_29: return LPC_GPIO_PORT->B[P0_29];
    case P0_30: return LPC_GPIO_PORT->B[P0_30];
    case P0_31: return LPC_GPIO_PORT->B[P0_31];
    case P1_0: return LPC_GPIO_PORT->B[P1_0];
    case P1_1: return LPC_GPIO_PORT->B[P1_1];
    case P1_2: return LPC_GPIO_PORT->B[P1_2];
    case P1_3: return LPC_GPIO_PORT->B[P1_3];
    case P1_4: return LPC_GPIO_PORT->B[P1_4];
    case P1_5: return LPC_GPIO_PORT->B[P1_5];
    case P1_6: return LPC_GPIO_PORT->B[P1_6];
    case P1_7: return LPC_GPIO_PORT->B[P1_7];
    case P1_8: return LPC_GPIO_PORT->B[P1_8];
    case P1_9: return LPC_GPIO_PORT->B[P1_9];
    case P1_10: return LPC_GPIO_PORT->B[P1_10];
    case P1_11: return LPC_GPIO_PORT->B[P1_11];
    case P2_12: return LPC_GPIO_PORT->B[P2_12];
    case P2_13: return LPC_GPIO_PORT->B[P2_13];
    default:
      ERROR("Invalid IO pin.");
  }
}

INLINE
void pin_dir (enum pio_pin pin, enum pin_dir dir)
{
  switch (pin) {
    case P0_0: LPC_GPIO_PORT->DIR[0] = (LPC_GPIO_PORT->DIR[0] & ~(1 << 0)) | (dir ? 1 << 0 : 0); break;
    case P0_1: LPC_GPIO_PORT->DIR[0] = (LPC_GPIO_PORT->DIR[0] & ~(1 << 1)) | (dir ? 1 << 1 : 0); break;
    case P0_2: LPC_GPIO_PORT->DIR[0] = (LPC_GPIO_PORT->DIR[0] & ~(1 << 2)) | (dir ? 1 << 2 : 0); break;
    case P0_3: LPC_GPIO_PORT->DIR[0] = (LPC_GPIO_PORT->DIR[0] & ~(1 << 3)) | (dir ? 1 << 3 : 0); break;
    case P0_4: LPC_GPIO_PORT->DIR[0] = (LPC_GPIO_PORT->DIR[0] & ~(1 << 4)) | (dir ? 1 << 4 : 0); break;
    case P0_5: LPC_GPIO_PORT->DIR[0] = (LPC_GPIO_PORT->DIR[0] & ~(1 << 5)) | (dir ? 1 << 5 : 0); break;
    case P0_6: LPC_GPIO_PORT->DIR[0] = (LPC_GPIO_PORT->DIR[0] & ~(1 << 6)) | (dir ? 1 << 6 : 0); break;
    case P0_7: LPC_GPIO_PORT->DIR[0] = (LPC_GPIO_PORT->DIR[0] & ~(1 << 7)) | (dir ? 1 << 7 : 0); break;
    case P0_8: LPC_GPIO_PORT->DIR[0] = (LPC_GPIO_PORT->DIR[0] & ~(1 << 8)) | (dir ? 1 << 8 : 0); break;
    case P0_9: LPC_GPIO_PORT->DIR[0] = (LPC_GPIO_PORT->DIR[0] & ~(1 << 9)) | (dir ? 1 << 9 : 0); break;
    case P0_10: LPC_GPIO_PORT->DIR[0] = (LPC_GPIO_PORT->DIR[0] & ~(1 << 10)) | (dir ? 1 << 10 : 0); break;
    case P0_11: LPC_GPIO_PORT->DIR[0] = (LPC_GPIO_PORT->DIR[0] & ~(1 << 11)) | (dir ? 1 << 11 : 0); break;
    case P0_12: LPC_GPIO_PORT->DIR[0] = (LPC_GPIO_PORT->DIR[0] & ~(1 << 12)) | (dir ? 1 << 12 : 0); break;
    case P0_13: LPC_GPIO_PORT->DIR[0] = (LPC_GPIO_PORT->DIR[0] & ~(1 << 13)) | (dir ? 1 << 13 : 0); break;
    case P0_14: LPC_GPIO_PORT->DIR[0] = (LPC_GPIO_PORT->DIR[0] & ~(1 << 14)) | (dir ? 1 << 14 : 0); break;
    case P0_15: LPC_GPIO_PORT->DIR[0] = (LPC_GPIO_PORT->DIR[0] & ~(1 << 15)) | (dir ? 1 << 15 : 0); break;
    case P0_16: LPC_GPIO_PORT->DIR[0] = (LPC_GPIO_PORT->DIR[0] & ~(1 << 16)) | (dir ? 1 << 16 : 0); break;
    case P0_17: LPC_GPIO_PORT->DIR[0] = (LPC_GPIO_PORT->DIR[0] & ~(1 << 17)) | (dir ? 1 << 17 : 0); break;
    case P0_18: LPC_GPIO_PORT->DIR[0] = (LPC_GPIO_PORT->DIR[0] & ~(1 << 18)) | (dir ? 1 << 18 : 0); break;
    case P0_19: LPC_GPIO_PORT->DIR[0] = (LPC_GPIO_PORT->DIR[0] & ~(1 << 19)) | (dir ? 1 << 19 : 0); break;
    case P0_20: LPC_GPIO_PORT->DIR[0] = (LPC_GPIO_PORT->DIR[0] & ~(1 << 20)) | (dir ? 1 << 20 : 0); break;
    case P0_21: LPC_GPIO_PORT->DIR[0] = (LPC_GPIO_PORT->DIR[0] & ~(1 << 21)) | (dir ? 1 << 21 : 0); break;
    case P0_22: LPC_GPIO_PORT->DIR[0] = (LPC_GPIO_PORT->DIR[0] & ~(1 << 22)) | (dir ? 1 << 22 : 0); break;
    case P0_23: LPC_GPIO_PORT->DIR[0] = (LPC_GPIO_PORT->DIR[0] & ~(1 << 23)) | (dir ? 1 << 23 : 0); break;
    case P0_24: LPC_GPIO_PORT->DIR[0] = (LPC_GPIO_PORT->DIR[0] & ~(1 << 24)) | (dir ? 1 << 24 : 0); break;
    case P0_25: LPC_GPIO_PORT->DIR[0] = (LPC_GPIO_PORT->DIR[0] & ~(1 << 25)) | (dir ? 1 << 25 : 0); break;
    case P0_26: LPC_GPIO_PORT->DIR[0] = (LPC_GPIO_PORT->DIR[0] & ~(1 << 26)) | (dir ? 1 << 26 : 0); break;
    case P0_27: LPC_GPIO_PORT->DIR[0] = (LPC_GPIO_PORT->DIR[0] & ~(1 << 27)) | (dir ? 1 << 27 : 0); break;
    case P0_28: LPC_GPIO_PORT->DIR[0] = (LPC_GPIO_PORT->DIR[0] & ~(1 << 28)) | (dir ? 1 << 28 : 0); break;
    case P0_29: LPC_GPIO_PORT->DIR[0] = (LPC_GPIO_PORT->DIR[0] & ~(1 << 29)) | (dir ? 1 << 29 : 0); break;
    case P0_30: LPC_GPIO_PORT->DIR[0] = (LPC_GPIO_PORT->DIR[0] & ~(1 << 30)) | (dir ? 1 << 30 : 0); break;
    case P0_31: LPC_GPIO_PORT->DIR[0] = (LPC_GPIO_PORT->DIR[0] & ~(1 << 31)) | (dir ? 1 << 31 : 0); break;
    case P1_0: LPC_GPIO_PORT->DIR[1] = (LPC_GPIO_PORT->DIR[1] & ~(1 << 0)) | (dir ? 1 << 0 : 0); break;
    case P1_1: LPC_GPIO_PORT->DIR[1] = (LPC_GPIO_PORT->DIR[1] & ~(1 << 1)) | (dir ? 1 << 1 : 0); break;
    case P1_2: LPC_GPIO_PORT->DIR[1] = (LPC_GPIO_PORT->DIR[1] & ~(1 << 2)) | (dir ? 1 << 2 : 0); break;
    case P1_3: LPC_GPIO_PORT->DIR[1] = (LPC_GPIO_PORT->DIR[1] & ~(1 << 3)) | (dir ? 1 << 3 : 0); break;
    case P1_4: LPC_GPIO_PORT->DIR[1] = (LPC_GPIO_PORT->DIR[1] & ~(1 << 4)) | (dir ? 1 << 4 : 0); break;
    case P1_5: LPC_GPIO_PORT->DIR[1] = (LPC_GPIO_PORT->DIR[1] & ~(1 << 5)) | (dir ? 1 << 5 : 0); break;
    case P1_6: LPC_GPIO_PORT->DIR[1] = (LPC_GPIO_PORT->DIR[1] & ~(1 << 6)) | (dir ? 1 << 6 : 0); break;
    case P1_7: LPC_GPIO_PORT->DIR[1] = (LPC_GPIO_PORT->DIR[1] & ~(1 << 7)) | (dir ? 1 << 7 : 0); break;
    case P1_8: LPC_GPIO_PORT->DIR[1] = (LPC_GPIO_PORT->DIR[1] & ~(1 << 8)) | (dir ? 1 << 8 : 0); break;
    case P1_9: LPC_GPIO_PORT->DIR[1] = (LPC_GPIO_PORT->DIR[1] & ~(1 << 9)) | (dir ? 1 << 9 : 0); break;
    case P1_10: LPC_GPIO_PORT->DIR[1] = (LPC_GPIO_PORT->DIR[1] & ~(1 << 10)) | (dir ? 1 << 10 : 0); break;
    case P1_11: LPC_GPIO_PORT->DIR[1] = (LPC_GPIO_PORT->DIR[1] & ~(1 << 11)) | (dir ? 1 << 11 : 0); break;
    case P2_12: LPC_GPIO_PORT->DIR[2] = (LPC_GPIO_PORT->DIR[2] & ~(1 << 12)) | (dir ? 1 << 12 : 0); break;
    case P2_13: LPC_GPIO_PORT->DIR[2] = (LPC_GPIO_PORT->DIR[2] & ~(1 << 13)) | (dir ? 1 << 13 : 0); break;
    default:
      ERROR("Invalid IO pin.");
  }
}

#endif // IO_PIN_H