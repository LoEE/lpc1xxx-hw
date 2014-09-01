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
  I2C_STD = 0 << 8,
  I2C_FAST = 0 << 8,
  I2C_GPIO = 1 << 8,
  I2C_FAST_PLUS = 2 << 8,
  PULL_NONE = 0 << 3,
  PULL_DOWN = 1 << 3,
  PULL_UP = 2 << 3,
  PULL_REPEATER = 3 << 3,
  IN_HYSTERESIS = 1 << 5,
};

enum io_function {
  PIO, ADC0_10, SCT0_OUT3, ADC0_7, SCT0_OUT4, ADC0_6, SCT1_OUT3, ADC0_5, SCT1_OUT4, ADC0_4, ADC0_3, ADC0_2, SCT2_OUT3, ADC0_1, ADC0_0, TDO, ADC1_1, TDI, ADC1_2, ADC1_3, DAC_OUT, ADC1_6, ADC1_7, SCT1_OUT5, ADC1_8, ADC1_9, WAKEUP, nTRST, SCT0_OUT5, SWCLK, TCK, SWDIO, SCT1_OUT6, TMS, nRESET, I2C0_SCL, I2C0_SDA, SCT0_OUT6, ACMP0_I4, ACMP0_I3, SCT3_OUT3, ACMP_I1, ACMP1_I3, ACMP2_I3, SCT2_OUT4, ADC0_11, ADC0_9, ADC0_8, ADC1_0, ADC1_4, ADC1_5, ADC1_10, ADC1_11, ACMP_I2, ACMP3_I4, ACMP3_I3, SCT3_OUT4, ACMP2_I4, ACMP1_I4
};

enum pio_pin {
  P0_0, P0_1, P0_2, P0_3, P0_4, P0_5, P0_6, P0_7, P0_8, P0_9, P0_10, P0_11, P0_12, P0_13, P0_14, P0_15, P0_16, P0_17, P0_18, P0_19, P0_20, P0_21, P0_22, P0_23, P0_24, P0_25, P0_26, P0_27, P0_28, P0_29, P0_30, P0_31, P1_0, P1_1, P1_2, P1_3, P1_4, P1_5, P1_6, P1_7, P1_8, P1_9, P1_10, P1_11, P2_12, P2_13
};

INLINE
void pin_setup (enum pio_pin pin, enum io_function func, enum io_mode mode)
{
  int f = 0;
  int other = mode | 3 << 6;
  switch (pin) {
    case P0_0:
      switch (func) {
        case PIO: f = 0; break;
        case ADC0_10: f = 1; break;
        case SCT0_OUT3: f = 2; break;
        default:
          ERROR("PIO0_0 can only be used as ADC0_10, SCT0_OUT3 or PIO.");
      }
      LPC_IOCON->PIO0_0 = f | other;
      break;
    case P0_1:
      switch (func) {
        case PIO: f = 0; break;
        case ADC0_7: f = 1; break;
        case SCT0_OUT4: f = 2; break;
        default:
          ERROR("PIO0_1 can only be used as ADC0_7, SCT0_OUT4 or PIO.");
      }
      LPC_IOCON->PIO0_1 = f | other;
      break;
    case P0_2:
      switch (func) {
        case PIO: f = 0; break;
        case ADC0_6: f = 1; break;
        case SCT1_OUT3: f = 2; break;
        default:
          ERROR("PIO0_2 can only be used as ADC0_6, SCT1_OUT3 or PIO.");
      }
      LPC_IOCON->PIO0_2 = f | other;
      break;
    case P0_3:
      switch (func) {
        case PIO: f = 0; break;
        case ADC0_5: f = 1; break;
        case SCT1_OUT4: f = 2; break;
        default:
          ERROR("PIO0_3 can only be used as ADC0_5, SCT1_OUT4 or PIO.");
      }
      LPC_IOCON->PIO0_3 = f | other;
      break;
    case P0_4:
      switch (func) {
        case PIO: f = 0; break;
        case ADC0_4: f = 1; break;
        default:
          ERROR("PIO0_4 can only be used as ADC0_4 or PIO.");
      }
      LPC_IOCON->PIO0_4 = f | other;
      break;
    case P0_5:
      switch (func) {
        case PIO: f = 0; break;
        case ADC0_3: f = 1; break;
        default:
          ERROR("PIO0_5 can only be used as ADC0_3 or PIO.");
      }
      LPC_IOCON->PIO0_5 = f | other;
      break;
    case P0_6:
      switch (func) {
        case PIO: f = 0; break;
        case ADC0_2: f = 1; break;
        case SCT2_OUT3: f = 2; break;
        default:
          ERROR("PIO0_6 can only be used as ADC0_2, SCT2_OUT3 or PIO.");
      }
      LPC_IOCON->PIO0_6 = f | other;
      break;
    case P0_7:
      switch (func) {
        case PIO: f = 0; break;
        case ADC0_1: f = 1; break;
        default:
          ERROR("PIO0_7 can only be used as ADC0_1 or PIO.");
      }
      LPC_IOCON->PIO0_7 = f | other;
      break;
    case P0_8:
      switch (func) {
        case PIO: f = 0; break;
        case ADC0_0: f = 1; break;
        case TDO: f = 2; break;
        default:
          ERROR("PIO0_8 can only be used as ADC0_0, TDO or PIO.");
      }
      LPC_IOCON->PIO0_8 = f | other;
      break;
    case P0_9:
      switch (func) {
        case PIO: f = 0; break;
        case ADC1_1: f = 1; break;
        case TDI: f = 2; break;
        default:
          ERROR("PIO0_9 can only be used as ADC1_1, TDI or PIO.");
      }
      LPC_IOCON->PIO0_9 = f | other;
      break;
    case P0_10:
      switch (func) {
        case PIO: f = 0; break;
        case ADC1_2: f = 1; break;
        default:
          ERROR("PIO0_10 can only be used as ADC1_2 or PIO.");
      }
      LPC_IOCON->PIO0_10 = f | other;
      break;
    case P0_11:
      switch (func) {
        case PIO: f = 0; break;
        case ADC1_3: f = 1; break;
        default:
          ERROR("PIO0_11 can only be used as ADC1_3 or PIO.");
      }
      LPC_IOCON->PIO0_11 = f | other;
      break;
    case P0_12:
      switch (func) {
        case PIO: f = 0; break;
        case DAC_OUT: f = 1; break;
        default:
          ERROR("PIO0_12 can only be used as DAC_OUT or PIO.");
      }
      LPC_IOCON->PIO0_12 = f | other;
      break;
    case P0_13:
      switch (func) {
        case PIO: f = 0; break;
        case ADC1_6: f = 1; break;
        default:
          ERROR("PIO0_13 can only be used as ADC1_6 or PIO.");
      }
      LPC_IOCON->PIO0_13 = f | other;
      break;
    case P0_14:
      switch (func) {
        case PIO: f = 0; break;
        case ADC1_7: f = 1; break;
        case SCT1_OUT5: f = 2; break;
        default:
          ERROR("PIO0_14 can only be used as ADC1_7, SCT1_OUT5 or PIO.");
      }
      LPC_IOCON->PIO0_14 = f | other;
      break;
    case P0_15:
      switch (func) {
        case PIO: f = 0; break;
        case ADC1_8: f = 1; break;
        default:
          ERROR("PIO0_15 can only be used as ADC1_8 or PIO.");
      }
      LPC_IOCON->PIO0_15 = f | other;
      break;
    case P0_16:
      switch (func) {
        case PIO: f = 0; break;
        case ADC1_9: f = 1; break;
        default:
          ERROR("PIO0_16 can only be used as ADC1_9 or PIO.");
      }
      LPC_IOCON->PIO0_16 = f | other;
      break;
    case P0_17:
      switch (func) {
        case PIO: f = 0; break;
        case WAKEUP: f = 1; break;
        case nTRST: f = 2; break;
        default:
          ERROR("PIO0_17 can only be used as WAKEUP, nTRST or PIO.");
      }
      LPC_IOCON->PIO0_17 = f | other;
      break;
    case P0_18:
      switch (func) {
        case PIO: f = 0; break;
        case SCT0_OUT5: f = 1; break;
        default:
          ERROR("PIO0_18 can only be used as SCT0_OUT5 or PIO.");
      }
      LPC_IOCON->PIO0_18 = f | other;
      break;
    case P0_19:
      switch (func) {
        case SWCLK: f = 0; break;
        case PIO: f = 1; break;
        case TCK: f = 2; break;
        default:
          ERROR("PIO0_19 can only be used as SWCLK, TCK or PIO.");
      }
      LPC_IOCON->PIO0_19 = f | other;
      break;
    case P0_20:
      switch (func) {
        case SWDIO: f = 0; break;
        case PIO: f = 1; break;
        case SCT1_OUT6: f = 2; break;
        case TMS: f = 3; break;
        default:
          ERROR("PIO0_20 can only be used as SWDIO, SCT1_OUT6, TMS or PIO.");
      }
      LPC_IOCON->PIO0_20 = f | other;
      break;
    case P0_21:
      switch (func) {
        case nRESET: f = 0; break;
        case PIO: f = 1; break;
        default:
          ERROR("PIO0_21 can only be used as nRESET or PIO.");
      }
      LPC_IOCON->PIO0_21 = f | other;
      break;
    case P0_22:
      switch (func) {
        case PIO: f = 0; other = mode;
          if (mode == I2C_FAST_PLUS)
            ERROR("I2C_FAST_PLUS cannot be used with PIO function.");
          if (mode & 0x7f)
            ERROR("Pull resistors and hysteresis are not available on I2C pins.");
          break;
        case I2C0_SCL: f = 1; other = mode;
          if (mode & 0x7f)
            ERROR("Pull resistors and hysteresis are not available on I2C pins.");
          break;
        default:
          ERROR("PIO0_22 can only be used as I2C0_SCL or PIO.");
      }
      LPC_IOCON->PIO0_22 = f | other;
      break;
    case P0_23:
      switch (func) {
        case PIO: f = 0; break;
        case I2C0_SDA: f = 1; break;
        default:
          ERROR("PIO0_23 can only be used as I2C0_SDA or PIO.");
      }
      LPC_IOCON->PIO0_23 = f | other;
      break;
    case P0_24:
      switch (func) {
        case PIO: f = 0; break;
        case SCT0_OUT6: f = 1; break;
        default:
          ERROR("PIO0_24 can only be used as SCT0_OUT6 or PIO.");
      }
      LPC_IOCON->PIO0_24 = f | other;
      break;
    case P0_25:
      switch (func) {
        case PIO: f = 0; break;
        case ACMP0_I4: f = 1; break;
        default:
          ERROR("PIO0_25 can only be used as ACMP0_I4 or PIO.");
      }
      LPC_IOCON->PIO0_25 = f | other;
      break;
    case P0_26:
      switch (func) {
        case PIO: f = 0; break;
        case ACMP0_I3: f = 1; break;
        case SCT3_OUT3: f = 2; break;
        default:
          ERROR("PIO0_26 can only be used as ACMP0_I3, SCT3_OUT3 or PIO.");
      }
      LPC_IOCON->PIO0_26 = f | other;
      break;
    case P0_27:
      switch (func) {
        case PIO: f = 0; break;
        case ACMP_I1: f = 1; break;
        default:
          ERROR("PIO0_27 can only be used as ACMP_I1 or PIO.");
      }
      LPC_IOCON->PIO0_27 = f | other;
      break;
    case P0_28:
      switch (func) {
        case PIO: f = 0; break;
        case ACMP1_I3: f = 1; break;
        default:
          ERROR("PIO0_28 can only be used as ACMP1_I3 or PIO.");
      }
      LPC_IOCON->PIO0_28 = f | other;
      break;
    case P0_29:
      switch (func) {
        case PIO: f = 0; break;
        case ACMP2_I3: f = 1; break;
        case SCT2_OUT4: f = 2; break;
        default:
          ERROR("PIO0_29 can only be used as ACMP2_I3, SCT2_OUT4 or PIO.");
      }
      LPC_IOCON->PIO0_29 = f | other;
      break;
    case P0_30:
      switch (func) {
        case PIO: f = 0; break;
        case ADC0_11: f = 1; break;
        default:
          ERROR("PIO0_30 can only be used as ADC0_11 or PIO.");
      }
      LPC_IOCON->PIO0_30 = f | other;
      break;
    case P0_31:
      switch (func) {
        case PIO: f = 0; break;
        case ADC0_9: f = 1; break;
        default:
          ERROR("PIO0_31 can only be used as ADC0_9 or PIO.");
      }
      LPC_IOCON->PIO0_31 = f | other;
      break;
    case P1_0:
      switch (func) {
        case PIO: f = 0; break;
        case ADC0_8: f = 1; break;
        default:
          ERROR("PIO1_0 can only be used as ADC0_8 or PIO.");
      }
      LPC_IOCON->PIO1_0 = f | other;
      break;
    case P1_1:
      switch (func) {
        case PIO: f = 0; break;
        case ADC1_0: f = 1; break;
        default:
          ERROR("PIO1_1 can only be used as ADC1_0 or PIO.");
      }
      LPC_IOCON->PIO1_1 = f | other;
      break;
    case P1_2:
      switch (func) {
        case PIO: f = 0; break;
        case ADC1_4: f = 1; break;
        default:
          ERROR("PIO1_2 can only be used as ADC1_4 or PIO.");
      }
      LPC_IOCON->PIO1_2 = f | other;
      break;
    case P1_3:
      switch (func) {
        case PIO: f = 0; break;
        case ADC1_5: f = 1; break;
        default:
          ERROR("PIO1_3 can only be used as ADC1_5 or PIO.");
      }
      LPC_IOCON->PIO1_3 = f | other;
      break;
    case P1_4:
      switch (func) {
        case PIO: f = 0; break;
        case ADC1_10: f = 1; break;
        default:
          ERROR("PIO1_4 can only be used as ADC1_10 or PIO.");
      }
      LPC_IOCON->PIO1_4 = f | other;
      break;
    case P1_5:
      switch (func) {
        case PIO: f = 0; break;
        case ADC1_11: f = 1; break;
        default:
          ERROR("PIO1_5 can only be used as ADC1_11 or PIO.");
      }
      LPC_IOCON->PIO1_5 = f | other;
      break;
    case P1_6:
      switch (func) {
        case PIO: f = 0; break;
        case ACMP_I2: f = 1; break;
        default:
          ERROR("PIO1_6 can only be used as ACMP_I2 or PIO.");
      }
      LPC_IOCON->PIO1_6 = f | other;
      break;
    case P1_7:
      switch (func) {
        case PIO: f = 0; break;
        case ACMP3_I4: f = 1; break;
        default:
          ERROR("PIO1_7 can only be used as ACMP3_I4 or PIO.");
      }
      LPC_IOCON->PIO1_7 = f | other;
      break;
    case P1_8:
      switch (func) {
        case PIO: f = 0; break;
        case ACMP3_I3: f = 1; break;
        case SCT3_OUT4: f = 2; break;
        default:
          ERROR("PIO1_8 can only be used as ACMP3_I3, SCT3_OUT4 or PIO.");
      }
      LPC_IOCON->PIO1_8 = f | other;
      break;
    case P1_9:
      switch (func) {
        case PIO: f = 0; break;
        case ACMP2_I4: f = 1; break;
        default:
          ERROR("PIO1_9 can only be used as ACMP2_I4 or PIO.");
      }
      LPC_IOCON->PIO1_9 = f | other;
      break;
    case P1_10:
      switch (func) {
        case PIO: f = 0; break;
        case ACMP1_I4: f = 1; break;
        default:
          ERROR("PIO1_10 can only be used as ACMP1_I4 or PIO.");
      }
      LPC_IOCON->PIO1_10 = f | other;
      break;
    case P1_11:
      if (func != PIO) ERROR("PIO1_11 can only be used as PIO.");
      f = 0;
      LPC_IOCON->PIO1_11 = f | other;
      break;
    case P2_12:
      if (func != PIO) ERROR("PIO2_12 can only be used as PIO.");
      f = 0;
      LPC_IOCON->PIO2_12 = f | other;
      break;
    case P2_13:
      if (func != PIO) ERROR("PIO2_13 can only be used as PIO.");
      f = 0;
      LPC_IOCON->PIO2_13 = f | other;
      break;
    default:
      ERROR("Invalid IO pin.");
  }
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