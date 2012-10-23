/*
   IO functions for NXP LPC122x devices in LQFP64 package.

   This is an automatically generated file. For more details see:
       http://bitbucket.org/jpc/lpc1xxx-hw/

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
  PULL_NONE = 0 << 4,
  PULL_UP = 1 << 4,
  IO_INVERT = 1 << 6,
  IO_HIGH_DRIVE = 1 << 9,
  IO_OPEN_DRAIN = 1 << 10,
};

enum io_function {
  PIO, nRTS0, RXD0, CT32B0_CAP0, CT32B0_MAT0, TXD0, CT32B0_CAP1, CT32B0_MAT1, nDTR0, CT32B0_CAP2, CT32B0_MAT2, nDSR0, CT32B0_CAP3, CT32B0_MAT3, nDCD0, nRI0, CT32B1_CAP0, CT32B1_MAT0, nCTS0, CT32B1_CAP1, CT32B1_MAT1, RXD1, CT32B1_CAP2, CT32B1_MAT2, TXD1, CT32B1_CAP3, CT32B1_MAT3, SCL, SDA, CT16B0_CAP0, CT16B0_MAT0, CLKOUT, CT16B0_CAP1, CT16B0_MAT1, nRESET, SCK, SSEL, CT16B1_CAP0, CT16B1_MAT0, MISO, CT16B1_CAP1, CT16B1_MAT1, MOSI, SWCLK, ACMP0_I0, ACMP0_I1, ACMP0_I2, ACMP0_I3, ACMP1_I0, ACMP1_I1, SWDIO, ACMP1_I2, ACMP1_I3, ACMP0_O, ACMP1_O, ROSC, AD0, AD1, AD2, AD3, AD4, AD5, WAKEUP, AD6, AD7
};

enum pio_pin {
  P0_0, P0_1, P0_2, P0_3, P0_4, P0_5, P0_6, P0_7, P0_8, P0_9, P0_10, P0_11, P0_12, P0_13, P0_14, P0_15, P0_16, P0_17, P0_18, P0_19, P0_20, P0_21, P0_22, P0_23, P0_24, P0_25, P0_26, P0_27, P0_28, P0_29, P0_30, P0_31, P1_0, P1_1, P1_2, P1_3, P1_4, P1_5, P1_6, P2_0, P2_1, P2_2, P2_3, P2_4, P2_5, P2_6, P2_7, P2_8, P2_9, P2_10, P2_11, P2_12, P2_13, P2_14, P2_15
};

INLINE
void pin_setup (enum pio_pin pin, enum io_function func, enum io_mode mode)
{
  int f = 0;
  int other = mode;
  switch (pin) {
    case P0_0:
      switch (func) {
        case PIO: f = 0; other |= 1 << 7; break;
        case nRTS0: f = 1; other |= 1 << 7; break;
        default:
          ERROR("PIO0_0 can only be used as nRTS0 or PIO.");
      }
      LPC_IOCON->PIO0_0 = f | other;
      break;
    case P0_1:
      switch (func) {
        case PIO: f = 0; other |= 1 << 7; break;
        case RXD0: f = 1; other |= 1 << 7; break;
        case CT32B0_CAP0: f = 2; other |= 1 << 7; break;
        case CT32B0_MAT0: f = 3; other |= 1 << 7; break;
        default:
          ERROR("PIO0_1 can only be used as RXD0, CT32B0_CAP0, CT32B0_MAT0 or PIO.");
      }
      LPC_IOCON->PIO0_1 = f | other;
      break;
    case P0_2:
      switch (func) {
        case PIO: f = 0; other |= 1 << 7; break;
        case TXD0: f = 1; other |= 1 << 7; break;
        case CT32B0_CAP1: f = 2; other |= 1 << 7; break;
        case CT32B0_MAT1: f = 3; other |= 1 << 7; break;
        default:
          ERROR("PIO0_2 can only be used as TXD0, CT32B0_CAP1, CT32B0_MAT1 or PIO.");
      }
      LPC_IOCON->PIO0_2 = f | other;
      break;
    case P0_3:
      switch (func) {
        case PIO: f = 0; other |= 1 << 7; break;
        case nDTR0: f = 1; other |= 1 << 7; break;
        case CT32B0_CAP2: f = 2; other |= 1 << 7; break;
        case CT32B0_MAT2: f = 3; other |= 1 << 7; break;
        default:
          ERROR("PIO0_3 can only be used as nDTR0, CT32B0_CAP2, CT32B0_MAT2 or PIO.");
      }
      LPC_IOCON->PIO0_3 = f | other;
      break;
    case P0_4:
      switch (func) {
        case PIO: f = 0; other |= 1 << 7; break;
        case nDSR0: f = 1; other |= 1 << 7; break;
        case CT32B0_CAP3: f = 2; other |= 1 << 7; break;
        case CT32B0_MAT3: f = 3; other |= 1 << 7; break;
        default:
          ERROR("PIO0_4 can only be used as nDSR0, CT32B0_CAP3, CT32B0_MAT3 or PIO.");
      }
      LPC_IOCON->PIO0_4 = f | other;
      break;
    case P0_5:
      switch (func) {
        case PIO: f = 0; other |= 1 << 7; break;
        case nDCD0: f = 1; other |= 1 << 7; break;
        default:
          ERROR("PIO0_5 can only be used as nDCD0 or PIO.");
      }
      LPC_IOCON->PIO0_5 = f | other;
      break;
    case P0_6:
      switch (func) {
        case PIO: f = 0; other |= 1 << 7; break;
        case nRI0: f = 1; other |= 1 << 7; break;
        case CT32B1_CAP0: f = 2; other |= 1 << 7; break;
        case CT32B1_MAT0: f = 3; other |= 1 << 7; break;
        default:
          ERROR("PIO0_6 can only be used as nRI0, CT32B1_CAP0, CT32B1_MAT0 or PIO.");
      }
      LPC_IOCON->PIO0_6 = f | other;
      break;
    case P0_7:
      switch (func) {
        case PIO: f = 0; other |= 1 << 7; break;
        case nCTS0: f = 1; other |= 1 << 7; break;
        case CT32B1_CAP1: f = 2; other |= 1 << 7; break;
        case CT32B1_MAT1: f = 3; other |= 1 << 7; break;
        default:
          ERROR("PIO0_7 can only be used as nCTS0, CT32B1_CAP1, CT32B1_MAT1 or PIO.");
      }
      LPC_IOCON->PIO0_7 = f | other;
      break;
    case P0_8:
      switch (func) {
        case PIO: f = 0; other |= 1 << 7; break;
        case RXD1: f = 1; other |= 1 << 7; break;
        case CT32B1_CAP2: f = 2; other |= 1 << 7; break;
        case CT32B1_MAT2: f = 3; other |= 1 << 7; break;
        default:
          ERROR("PIO0_8 can only be used as RXD1, CT32B1_CAP2, CT32B1_MAT2 or PIO.");
      }
      LPC_IOCON->PIO0_8 = f | other;
      break;
    case P0_9:
      switch (func) {
        case PIO: f = 0; other |= 1 << 7; break;
        case TXD1: f = 1; other |= 1 << 7; break;
        case CT32B1_CAP3: f = 2; other |= 1 << 7; break;
        case CT32B1_MAT3: f = 3; other |= 1 << 7; break;
        default:
          ERROR("PIO0_9 can only be used as TXD1, CT32B1_CAP3, CT32B1_MAT3 or PIO.");
      }
      LPC_IOCON->PIO0_9 = f | other;
      break;
    case P0_10:
      switch (func) {
        case PIO: f = 0; other |= 1 << 7;
          if (mode & PULL_UP)
            ERROR("Pull-up is not available on I2C pins.");
          if (mode & IO_HIGH_DRIVE)
            ERROR("High output drive is not available on I2C pins.");
          break;
        case SCL: f = 1; other |= 1 << 7;
          if (mode & PULL_UP)
            ERROR("Pull-up is not available on I2C pins.");
          if (mode & IO_HIGH_DRIVE)
            ERROR("High output drive is not available on I2C pins.");
          break;
        default:
          ERROR("PIO0_10 can only be used as SCL or PIO.");
      }
      LPC_IOCON->PIO0_10 = f | other;
      break;
    case P0_11:
      switch (func) {
        case PIO: f = 0; other |= 1 << 7;
          if (mode & PULL_UP)
            ERROR("Pull-up is not available on I2C pins.");
          if (mode & IO_HIGH_DRIVE)
            ERROR("High output drive is not available on I2C pins.");
          break;
        case SDA: f = 1; other |= 1 << 7;
          if (mode & PULL_UP)
            ERROR("Pull-up is not available on I2C pins.");
          if (mode & IO_HIGH_DRIVE)
            ERROR("High output drive is not available on I2C pins.");
          break;
        case CT16B0_CAP0: f = 2; other |= 1 << 7;
          if (mode & PULL_UP)
            ERROR("Pull-up is not available on I2C pins.");
          if (mode & IO_HIGH_DRIVE)
            ERROR("High output drive is not available on I2C pins.");
          break;
        case CT16B0_MAT0: f = 3; other |= 1 << 7;
          if (mode & PULL_UP)
            ERROR("Pull-up is not available on I2C pins.");
          if (mode & IO_HIGH_DRIVE)
            ERROR("High output drive is not available on I2C pins.");
          break;
        default:
          ERROR("PIO0_11 can only be used as SDA, CT16B0_CAP0, CT16B0_MAT0 or PIO.");
      }
      LPC_IOCON->PIO0_11 = f | other;
      break;
    case P0_12:
      switch (func) {
        case PIO: f = 0; other |= 1 << 7; break;
        case CLKOUT: f = 1; other |= 1 << 7; break;
        case CT16B0_CAP1: f = 2; other |= 1 << 7; break;
        case CT16B0_MAT1: f = 3; other |= 1 << 7; break;
        default:
          ERROR("PIO0_12 can only be used as CLKOUT, CT16B0_CAP1, CT16B0_MAT1 or PIO.");
      }
      LPC_IOCON->PIO0_12 = f | other;
      break;
    case P0_13:
      switch (func) {
        case nRESET: f = 0; other |= 1 << 7; break;
        case PIO: f = 1; other |= 1 << 7; break;
        default:
          ERROR("PIO0_13 can only be used as nRESET or PIO.");
      }
      LPC_IOCON->RESET_PIO0_13 = f | other;
      break;
    case P0_14:
      switch (func) {
        case PIO: f = 0; other |= 1 << 7; break;
        case SCK: f = 1; other |= 1 << 7; break;
        default:
          ERROR("PIO0_14 can only be used as SCK or PIO.");
      }
      LPC_IOCON->PIO0_14 = f | other;
      break;
    case P0_15:
      switch (func) {
        case PIO: f = 0; other |= 1 << 7; break;
        case SSEL: f = 1; other |= 1 << 7; break;
        case CT16B1_CAP0: f = 2; other |= 1 << 7; break;
        case CT16B1_MAT0: f = 3; other |= 1 << 7; break;
        default:
          ERROR("PIO0_15 can only be used as SSEL, CT16B1_CAP0, CT16B1_MAT0 or PIO.");
      }
      LPC_IOCON->PIO0_15 = f | other;
      break;
    case P0_16:
      switch (func) {
        case PIO: f = 0; other |= 1 << 7; break;
        case MISO: f = 1; other |= 1 << 7; break;
        case CT16B1_CAP1: f = 2; other |= 1 << 7; break;
        case CT16B1_MAT1: f = 3; other |= 1 << 7; break;
        default:
          ERROR("PIO0_16 can only be used as MISO, CT16B1_CAP1, CT16B1_MAT1 or PIO.");
      }
      LPC_IOCON->PIO0_16 = f | other;
      break;
    case P0_17:
      switch (func) {
        case PIO: f = 0; other |= 1 << 7; break;
        case MOSI: f = 1; other |= 1 << 7; break;
        default:
          ERROR("PIO0_17 can only be used as MOSI or PIO.");
      }
      LPC_IOCON->PIO0_17 = f | other;
      break;
    case P0_18:
      switch (func) {
        case PIO: f = 0; other |= 1 << 7; break;
        case SWCLK: f = 1; other |= 1 << 7; break;
        case CT32B0_CAP0: f = 2; other |= 1 << 7; break;
        case CT32B0_MAT0: f = 3; other |= 1 << 7; break;
        default:
          ERROR("PIO0_18 can only be used as SWCLK, CT32B0_CAP0, CT32B0_MAT0 or PIO.");
      }
      LPC_IOCON->PIO0_18 = f | other;
      break;
    case P0_19:
      switch (func) {
        case PIO: f = 0; other |= 1 << 7; break;
        case ACMP0_I0: f = 1; other |= 1 << 7; break;
        case CT32B0_CAP1: f = 2; other |= 1 << 7; break;
        case CT32B0_MAT1: f = 3; other |= 1 << 7; break;
        default:
          ERROR("PIO0_19 can only be used as ACMP0_I0, CT32B0_CAP1, CT32B0_MAT1 or PIO.");
      }
      LPC_IOCON->PIO0_19 = f | other;
      break;
    case P0_20:
      switch (func) {
        case PIO: f = 0; other |= 1 << 7; break;
        case ACMP0_I1: f = 1; other |= 1 << 7; break;
        case CT32B0_CAP2: f = 2; other |= 1 << 7; break;
        case CT32B0_MAT2: f = 3; other |= 1 << 7; break;
        default:
          ERROR("PIO0_20 can only be used as ACMP0_I1, CT32B0_CAP2, CT32B0_MAT2 or PIO.");
      }
      LPC_IOCON->PIO0_20 = f | other;
      break;
    case P0_21:
      switch (func) {
        case PIO: f = 0; other |= 1 << 7; break;
        case ACMP0_I2: f = 1; other |= 1 << 7; break;
        case CT32B0_CAP3: f = 2; other |= 1 << 7; break;
        case CT32B0_MAT3: f = 3; other |= 1 << 7; break;
        default:
          ERROR("PIO0_21 can only be used as ACMP0_I2, CT32B0_CAP3, CT32B0_MAT3 or PIO.");
      }
      LPC_IOCON->PIO0_21 = f | other;
      break;
    case P0_22:
      switch (func) {
        case PIO: f = 0; other |= 1 << 7; break;
        case ACMP0_I3: f = 1; other |= 1 << 7; break;
        default:
          ERROR("PIO0_22 can only be used as ACMP0_I3 or PIO.");
      }
      LPC_IOCON->PIO0_22 = f | other;
      break;
    case P0_23:
      switch (func) {
        case PIO: f = 0; other |= 1 << 7; break;
        case ACMP1_I0: f = 1; other |= 1 << 7; break;
        case CT32B1_CAP0: f = 2; other |= 1 << 7; break;
        case CT32B1_MAT0: f = 3; other |= 1 << 7; break;
        default:
          ERROR("PIO0_23 can only be used as ACMP1_I0, CT32B1_CAP0, CT32B1_MAT0 or PIO.");
      }
      LPC_IOCON->PIO0_23 = f | other;
      break;
    case P0_24:
      switch (func) {
        case PIO: f = 0; other |= 1 << 7; break;
        case ACMP1_I1: f = 1; other |= 1 << 7; break;
        case CT32B1_CAP1: f = 2; other |= 1 << 7; break;
        case CT32B1_MAT1: f = 3; other |= 1 << 7; break;
        default:
          ERROR("PIO0_24 can only be used as ACMP1_I1, CT32B1_CAP1, CT32B1_MAT1 or PIO.");
      }
      LPC_IOCON->PIO0_24 = f | other;
      break;
    case P0_25:
      switch (func) {
        case SWDIO: f = 0; other |= 1 << 7; break;
        case ACMP1_I2: f = 1; other |= 1 << 7; break;
        case CT32B1_CAP2: f = 2; other |= 1 << 7; break;
        case CT32B1_MAT2: f = 3; other |= 1 << 7; break;
        case PIO: f = 4; other |= 1 << 7; break;
        default:
          ERROR("PIO0_25 can only be used as SWDIO, ACMP1_I2, CT32B1_CAP2, CT32B1_MAT2 or PIO.");
      }
      LPC_IOCON->SWDIO_PIO0_25 = f | other;
      break;
    case P0_26:
      switch (func) {
        case SWCLK: f = 0; other |= 1 << 7; break;
        case ACMP1_I3: f = 1; other |= 1 << 7; break;
        case CT32B1_CAP3: f = 2; other |= 1 << 7; break;
        case CT32B1_MAT3: f = 3; other |= 1 << 7; break;
        case PIO: f = 4; other |= 1 << 7; break;
        default:
          ERROR("PIO0_26 can only be used as SWCLK, ACMP1_I3, CT32B1_CAP3, CT32B1_MAT3 or PIO.");
      }
      LPC_IOCON->SWCLK_PIO0_26 = f | other;
      break;
    case P0_27:
      switch (func) {
        case PIO: f = 0; other |= 1 << 7; break;
        case ACMP0_O: f = 1; other |= 1 << 7; break;
        default:
          ERROR("PIO0_27 can only be used as ACMP0_O or PIO.");
      }
      LPC_IOCON->PIO0_27 = f | other;
      break;
    case P0_28:
      switch (func) {
        case PIO: f = 0; other |= 1 << 7; break;
        case ACMP1_O: f = 1; other |= 1 << 7; break;
        case CT16B0_CAP0: f = 2; other |= 1 << 7; break;
        case CT16B0_MAT0: f = 3; other |= 1 << 7; break;
        default:
          ERROR("PIO0_28 can only be used as ACMP1_O, CT16B0_CAP0, CT16B0_MAT0 or PIO.");
      }
      LPC_IOCON->PIO0_28 = f | other;
      break;
    case P0_29:
      switch (func) {
        case PIO: f = 0; other |= 1 << 7; break;
        case ROSC: f = 1; other |= 1 << 7; break;
        case CT16B0_CAP1: f = 2; other |= 1 << 7; break;
        case CT16B0_MAT1: f = 3; other |= 1 << 7; break;
        default:
          ERROR("PIO0_29 can only be used as ROSC, CT16B0_CAP1, CT16B0_MAT1 or PIO.");
      }
      LPC_IOCON->PIO0_29 = f | other;
      break;
    case P0_30:
      switch (func) {
        case PIO: f = 1; other |= 1 << 7; break;
        case AD0: f = 2; break;
        default:
          ERROR("PIO0_30 can only be used as AD0 or PIO.");
      }
      LPC_IOCON->R_PIO0_30 = f | other;
      break;
    case P0_31:
      switch (func) {
        case PIO: f = 1; other |= 1 << 7; break;
        case AD1: f = 2; break;
        default:
          ERROR("PIO0_31 can only be used as AD1 or PIO.");
      }
      LPC_IOCON->R_PIO0_31 = f | other;
      break;
    case P1_0:
      switch (func) {
        case PIO: f = 1; other |= 1 << 7; break;
        case AD2: f = 2; break;
        default:
          ERROR("PIO1_0 can only be used as AD2 or PIO.");
      }
      LPC_IOCON->R_PIO1_0 = f | other;
      break;
    case P1_1:
      switch (func) {
        case PIO: f = 1; other |= 1 << 7; break;
        case AD3: f = 2; break;
        default:
          ERROR("PIO1_1 can only be used as AD3 or PIO.");
      }
      LPC_IOCON->R_PIO1_1 = f | other;
      break;
    case P1_2:
      switch (func) {
        case PIO: f = 0; other |= 1 << 7; break;
        case SWDIO: f = 1; other |= 1 << 7; break;
        case AD4: f = 2; break;
        default:
          ERROR("PIO1_2 can only be used as SWDIO, AD4 or PIO.");
      }
      LPC_IOCON->PIO1_2 = f | other;
      break;
    case P1_3:
      switch (func) {
        case PIO: f = 0; other |= 1 << 7; break;
        case AD5: f = 1; break;
        case WAKEUP: f = 2; other |= 1 << 7; break;
        default:
          ERROR("PIO1_3 can only be used as AD5, WAKEUP or PIO.");
      }
      LPC_IOCON->PIO1_3 = f | other;
      break;
    case P1_4:
      switch (func) {
        case PIO: f = 0; other |= 1 << 7; break;
        case AD6: f = 1; break;
        default:
          ERROR("PIO1_4 can only be used as AD6 or PIO.");
      }
      LPC_IOCON->PIO1_4 = f | other;
      break;
    case P1_5:
      switch (func) {
        case PIO: f = 0; other |= 1 << 7; break;
        case AD7: f = 1; break;
        case CT16B1_CAP0: f = 2; other |= 1 << 7; break;
        case CT16B1_MAT0: f = 3; other |= 1 << 7; break;
        default:
          ERROR("PIO1_5 can only be used as AD7, CT16B1_CAP0, CT16B1_MAT0 or PIO.");
      }
      LPC_IOCON->PIO1_5 = f | other;
      break;
    case P1_6:
      switch (func) {
        case PIO: f = 0; other |= 1 << 7; break;
        case CT16B1_CAP1: f = 1; other |= 1 << 7; break;
        case CT16B1_MAT1: f = 2; other |= 1 << 7; break;
        default:
          ERROR("PIO1_6 can only be used as CT16B1_CAP1, CT16B1_MAT1 or PIO.");
      }
      LPC_IOCON->PIO1_6 = f | other;
      break;
    case P2_0:
      switch (func) {
        case PIO: f = 0; other |= 1 << 7; break;
        case CT16B0_CAP0: f = 1; other |= 1 << 7; break;
        case CT16B0_MAT0: f = 2; other |= 1 << 7; break;
        case nRTS0: f = 3; other |= 1 << 7; break;
        default:
          ERROR("PIO2_0 can only be used as CT16B0_CAP0, CT16B0_MAT0, nRTS0 or PIO.");
      }
      LPC_IOCON->PIO2_0 = f | other;
      break;
    case P2_1:
      switch (func) {
        case PIO: f = 0; other |= 1 << 7; break;
        case CT16B0_CAP1: f = 1; other |= 1 << 7; break;
        case CT16B0_MAT1: f = 2; other |= 1 << 7; break;
        case RXD0: f = 3; other |= 1 << 7; break;
        default:
          ERROR("PIO2_1 can only be used as CT16B0_CAP1, CT16B0_MAT1, RXD0 or PIO.");
      }
      LPC_IOCON->PIO2_1 = f | other;
      break;
    case P2_2:
      switch (func) {
        case PIO: f = 0; other |= 1 << 7; break;
        case CT16B1_CAP0: f = 1; other |= 1 << 7; break;
        case CT16B1_MAT0: f = 2; other |= 1 << 7; break;
        case TXD0: f = 3; other |= 1 << 7; break;
        default:
          ERROR("PIO2_2 can only be used as CT16B1_CAP0, CT16B1_MAT0, TXD0 or PIO.");
      }
      LPC_IOCON->PIO2_2 = f | other;
      break;
    case P2_3:
      switch (func) {
        case PIO: f = 0; other |= 1 << 7; break;
        case CT16B1_CAP1: f = 1; other |= 1 << 7; break;
        case CT16B1_MAT1: f = 2; other |= 1 << 7; break;
        case nDTR0: f = 3; other |= 1 << 7; break;
        default:
          ERROR("PIO2_3 can only be used as CT16B1_CAP1, CT16B1_MAT1, nDTR0 or PIO.");
      }
      LPC_IOCON->PIO2_3 = f | other;
      break;
    case P2_4:
      switch (func) {
        case PIO: f = 0; other |= 1 << 7; break;
        case CT32B0_CAP0: f = 1; other |= 1 << 7; break;
        case CT32B0_MAT0: f = 2; other |= 1 << 7; break;
        case nCTS0: f = 3; other |= 1 << 7; break;
        default:
          ERROR("PIO2_4 can only be used as CT32B0_CAP0, CT32B0_MAT0, nCTS0 or PIO.");
      }
      LPC_IOCON->PIO2_4 = f | other;
      break;
    case P2_5:
      switch (func) {
        case PIO: f = 0; other |= 1 << 7; break;
        case CT32B0_CAP1: f = 1; other |= 1 << 7; break;
        case CT32B0_MAT1: f = 2; other |= 1 << 7; break;
        case nRI0: f = 3; other |= 1 << 7; break;
        default:
          ERROR("PIO2_5 can only be used as CT32B0_CAP1, CT32B0_MAT1, nRI0 or PIO.");
      }
      LPC_IOCON->PIO2_5 = f | other;
      break;
    case P2_6:
      switch (func) {
        case PIO: f = 0; other |= 1 << 7; break;
        case CT32B0_CAP2: f = 1; other |= 1 << 7; break;
        case CT32B0_MAT2: f = 2; other |= 1 << 7; break;
        case nDCD0: f = 3; other |= 1 << 7; break;
        default:
          ERROR("PIO2_6 can only be used as CT32B0_CAP2, CT32B0_MAT2, nDCD0 or PIO.");
      }
      LPC_IOCON->PIO2_6 = f | other;
      break;
    case P2_7:
      switch (func) {
        case PIO: f = 0; other |= 1 << 7; break;
        case CT32B0_CAP3: f = 1; other |= 1 << 7; break;
        case CT32B0_MAT3: f = 2; other |= 1 << 7; break;
        case nDSR0: f = 3; other |= 1 << 7; break;
        default:
          ERROR("PIO2_7 can only be used as CT32B0_CAP3, CT32B0_MAT3, nDSR0 or PIO.");
      }
      LPC_IOCON->PIO2_7 = f | other;
      break;
    case P2_8:
      switch (func) {
        case PIO: f = 0; other |= 1 << 7; break;
        case CT32B1_CAP0: f = 1; other |= 1 << 7; break;
        case CT32B1_MAT0: f = 2; other |= 1 << 7; break;
        default:
          ERROR("PIO2_8 can only be used as CT32B1_CAP0, CT32B1_MAT0 or PIO.");
      }
      LPC_IOCON->PIO2_8 = f | other;
      break;
    case P2_9:
      switch (func) {
        case PIO: f = 0; other |= 1 << 7; break;
        case CT32B1_CAP1: f = 1; other |= 1 << 7; break;
        case CT32B1_MAT1: f = 2; other |= 1 << 7; break;
        default:
          ERROR("PIO2_9 can only be used as CT32B1_CAP1, CT32B1_MAT1 or PIO.");
      }
      LPC_IOCON->PIO2_9 = f | other;
      break;
    case P2_10:
      switch (func) {
        case PIO: f = 0; other |= 1 << 7; break;
        case CT32B1_CAP2: f = 1; other |= 1 << 7; break;
        case CT32B1_MAT2: f = 2; other |= 1 << 7; break;
        case TXD1: f = 3; other |= 1 << 7; break;
        default:
          ERROR("PIO2_10 can only be used as CT32B1_CAP2, CT32B1_MAT2, TXD1 or PIO.");
      }
      LPC_IOCON->PIO2_10 = f | other;
      break;
    case P2_11:
      switch (func) {
        case PIO: f = 0; other |= 1 << 7; break;
        case CT32B1_CAP3: f = 1; other |= 1 << 7; break;
        case CT32B1_MAT3: f = 2; other |= 1 << 7; break;
        case RXD1: f = 3; other |= 1 << 7; break;
        default:
          ERROR("PIO2_11 can only be used as CT32B1_CAP3, CT32B1_MAT3, RXD1 or PIO.");
      }
      LPC_IOCON->PIO2_11 = f | other;
      break;
    case P2_12:
      switch (func) {
        case PIO: f = 0; other |= 1 << 7; break;
        case RXD1: f = 1; other |= 1 << 7; break;
        default:
          ERROR("PIO2_12 can only be used as RXD1 or PIO.");
      }
      LPC_IOCON->PIO2_12 = f | other;
      break;
    case P2_13:
      switch (func) {
        case PIO: f = 0; other |= 1 << 7; break;
        case TXD1: f = 1; other |= 1 << 7; break;
        default:
          ERROR("PIO2_13 can only be used as TXD1 or PIO.");
      }
      LPC_IOCON->PIO2_13 = f | other;
      break;
    case P2_14:
      if (func != PIO) ERROR("PIO2_14 can only be used as PIO.");
      f = 0;
      LPC_IOCON->PIO2_14 = f | other;
      break;
    case P2_15:
      if (func != PIO) ERROR("PIO2_15 can only be used as PIO.");
      f = 0;
      LPC_IOCON->PIO2_15 = f | other;
      break;
    default:
      ERROR("Invalid IO pin.");
  }
}

INLINE
void pin_write (enum pio_pin pin, int val)
{
  switch (pin) {
    case P0_0: if(val) LPC_GPIO0->SET = 1 << 0; else LPC_GPIO0->CLR =  1 << 0; break;
    case P0_1: if(val) LPC_GPIO0->SET = 1 << 1; else LPC_GPIO0->CLR =  1 << 1; break;
    case P0_2: if(val) LPC_GPIO0->SET = 1 << 2; else LPC_GPIO0->CLR =  1 << 2; break;
    case P0_3: if(val) LPC_GPIO0->SET = 1 << 3; else LPC_GPIO0->CLR =  1 << 3; break;
    case P0_4: if(val) LPC_GPIO0->SET = 1 << 4; else LPC_GPIO0->CLR =  1 << 4; break;
    case P0_5: if(val) LPC_GPIO0->SET = 1 << 5; else LPC_GPIO0->CLR =  1 << 5; break;
    case P0_6: if(val) LPC_GPIO0->SET = 1 << 6; else LPC_GPIO0->CLR =  1 << 6; break;
    case P0_7: if(val) LPC_GPIO0->SET = 1 << 7; else LPC_GPIO0->CLR =  1 << 7; break;
    case P0_8: if(val) LPC_GPIO0->SET = 1 << 8; else LPC_GPIO0->CLR =  1 << 8; break;
    case P0_9: if(val) LPC_GPIO0->SET = 1 << 9; else LPC_GPIO0->CLR =  1 << 9; break;
    case P0_10: if(val) LPC_GPIO0->SET = 1 << 10; else LPC_GPIO0->CLR =  1 << 10; break;
    case P0_11: if(val) LPC_GPIO0->SET = 1 << 11; else LPC_GPIO0->CLR =  1 << 11; break;
    case P0_12: if(val) LPC_GPIO0->SET = 1 << 12; else LPC_GPIO0->CLR =  1 << 12; break;
    case P0_13: if(val) LPC_GPIO0->SET = 1 << 13; else LPC_GPIO0->CLR =  1 << 13; break;
    case P0_14: if(val) LPC_GPIO0->SET = 1 << 14; else LPC_GPIO0->CLR =  1 << 14; break;
    case P0_15: if(val) LPC_GPIO0->SET = 1 << 15; else LPC_GPIO0->CLR =  1 << 15; break;
    case P0_16: if(val) LPC_GPIO0->SET = 1 << 16; else LPC_GPIO0->CLR =  1 << 16; break;
    case P0_17: if(val) LPC_GPIO0->SET = 1 << 17; else LPC_GPIO0->CLR =  1 << 17; break;
    case P0_18: if(val) LPC_GPIO0->SET = 1 << 18; else LPC_GPIO0->CLR =  1 << 18; break;
    case P0_19: if(val) LPC_GPIO0->SET = 1 << 19; else LPC_GPIO0->CLR =  1 << 19; break;
    case P0_20: if(val) LPC_GPIO0->SET = 1 << 20; else LPC_GPIO0->CLR =  1 << 20; break;
    case P0_21: if(val) LPC_GPIO0->SET = 1 << 21; else LPC_GPIO0->CLR =  1 << 21; break;
    case P0_22: if(val) LPC_GPIO0->SET = 1 << 22; else LPC_GPIO0->CLR =  1 << 22; break;
    case P0_23: if(val) LPC_GPIO0->SET = 1 << 23; else LPC_GPIO0->CLR =  1 << 23; break;
    case P0_24: if(val) LPC_GPIO0->SET = 1 << 24; else LPC_GPIO0->CLR =  1 << 24; break;
    case P0_25: if(val) LPC_GPIO0->SET = 1 << 25; else LPC_GPIO0->CLR =  1 << 25; break;
    case P0_26: if(val) LPC_GPIO0->SET = 1 << 26; else LPC_GPIO0->CLR =  1 << 26; break;
    case P0_27: if(val) LPC_GPIO0->SET = 1 << 27; else LPC_GPIO0->CLR =  1 << 27; break;
    case P0_28: if(val) LPC_GPIO0->SET = 1 << 28; else LPC_GPIO0->CLR =  1 << 28; break;
    case P0_29: if(val) LPC_GPIO0->SET = 1 << 29; else LPC_GPIO0->CLR =  1 << 29; break;
    case P0_30: if(val) LPC_GPIO0->SET = 1 << 30; else LPC_GPIO0->CLR =  1 << 30; break;
    case P0_31: if(val) LPC_GPIO0->SET = 1 << 31; else LPC_GPIO0->CLR =  1 << 31; break;
    case P1_0: if(val) LPC_GPIO1->SET = 1 << 0; else LPC_GPIO1->CLR =  1 << 0; break;
    case P1_1: if(val) LPC_GPIO1->SET = 1 << 1; else LPC_GPIO1->CLR =  1 << 1; break;
    case P1_2: if(val) LPC_GPIO1->SET = 1 << 2; else LPC_GPIO1->CLR =  1 << 2; break;
    case P1_3: if(val) LPC_GPIO1->SET = 1 << 3; else LPC_GPIO1->CLR =  1 << 3; break;
    case P1_4: if(val) LPC_GPIO1->SET = 1 << 4; else LPC_GPIO1->CLR =  1 << 4; break;
    case P1_5: if(val) LPC_GPIO1->SET = 1 << 5; else LPC_GPIO1->CLR =  1 << 5; break;
    case P1_6: if(val) LPC_GPIO1->SET = 1 << 6; else LPC_GPIO1->CLR =  1 << 6; break;
    case P2_0: if(val) LPC_GPIO2->SET = 1 << 0; else LPC_GPIO2->CLR =  1 << 0; break;
    case P2_1: if(val) LPC_GPIO2->SET = 1 << 1; else LPC_GPIO2->CLR =  1 << 1; break;
    case P2_2: if(val) LPC_GPIO2->SET = 1 << 2; else LPC_GPIO2->CLR =  1 << 2; break;
    case P2_3: if(val) LPC_GPIO2->SET = 1 << 3; else LPC_GPIO2->CLR =  1 << 3; break;
    case P2_4: if(val) LPC_GPIO2->SET = 1 << 4; else LPC_GPIO2->CLR =  1 << 4; break;
    case P2_5: if(val) LPC_GPIO2->SET = 1 << 5; else LPC_GPIO2->CLR =  1 << 5; break;
    case P2_6: if(val) LPC_GPIO2->SET = 1 << 6; else LPC_GPIO2->CLR =  1 << 6; break;
    case P2_7: if(val) LPC_GPIO2->SET = 1 << 7; else LPC_GPIO2->CLR =  1 << 7; break;
    case P2_8: if(val) LPC_GPIO2->SET = 1 << 8; else LPC_GPIO2->CLR =  1 << 8; break;
    case P2_9: if(val) LPC_GPIO2->SET = 1 << 9; else LPC_GPIO2->CLR =  1 << 9; break;
    case P2_10: if(val) LPC_GPIO2->SET = 1 << 10; else LPC_GPIO2->CLR =  1 << 10; break;
    case P2_11: if(val) LPC_GPIO2->SET = 1 << 11; else LPC_GPIO2->CLR =  1 << 11; break;
    case P2_12: if(val) LPC_GPIO2->SET = 1 << 12; else LPC_GPIO2->CLR =  1 << 12; break;
    case P2_13: if(val) LPC_GPIO2->SET = 1 << 13; else LPC_GPIO2->CLR =  1 << 13; break;
    case P2_14: if(val) LPC_GPIO2->SET = 1 << 14; else LPC_GPIO2->CLR =  1 << 14; break;
    case P2_15: if(val) LPC_GPIO2->SET = 1 << 15; else LPC_GPIO2->CLR =  1 << 15; break;
    default:
      ERROR("Invalid IO pin.");
  }
}

INLINE
int pin_read (enum pio_pin pin)
{
  switch (pin) {
    case P0_0: return LPC_GPIO0->PIN & (1 << 0) ? 1 : 0;
    case P0_1: return LPC_GPIO0->PIN & (1 << 1) ? 1 : 0;
    case P0_2: return LPC_GPIO0->PIN & (1 << 2) ? 1 : 0;
    case P0_3: return LPC_GPIO0->PIN & (1 << 3) ? 1 : 0;
    case P0_4: return LPC_GPIO0->PIN & (1 << 4) ? 1 : 0;
    case P0_5: return LPC_GPIO0->PIN & (1 << 5) ? 1 : 0;
    case P0_6: return LPC_GPIO0->PIN & (1 << 6) ? 1 : 0;
    case P0_7: return LPC_GPIO0->PIN & (1 << 7) ? 1 : 0;
    case P0_8: return LPC_GPIO0->PIN & (1 << 8) ? 1 : 0;
    case P0_9: return LPC_GPIO0->PIN & (1 << 9) ? 1 : 0;
    case P0_10: return LPC_GPIO0->PIN & (1 << 10) ? 1 : 0;
    case P0_11: return LPC_GPIO0->PIN & (1 << 11) ? 1 : 0;
    case P0_12: return LPC_GPIO0->PIN & (1 << 12) ? 1 : 0;
    case P0_13: return LPC_GPIO0->PIN & (1 << 13) ? 1 : 0;
    case P0_14: return LPC_GPIO0->PIN & (1 << 14) ? 1 : 0;
    case P0_15: return LPC_GPIO0->PIN & (1 << 15) ? 1 : 0;
    case P0_16: return LPC_GPIO0->PIN & (1 << 16) ? 1 : 0;
    case P0_17: return LPC_GPIO0->PIN & (1 << 17) ? 1 : 0;
    case P0_18: return LPC_GPIO0->PIN & (1 << 18) ? 1 : 0;
    case P0_19: return LPC_GPIO0->PIN & (1 << 19) ? 1 : 0;
    case P0_20: return LPC_GPIO0->PIN & (1 << 20) ? 1 : 0;
    case P0_21: return LPC_GPIO0->PIN & (1 << 21) ? 1 : 0;
    case P0_22: return LPC_GPIO0->PIN & (1 << 22) ? 1 : 0;
    case P0_23: return LPC_GPIO0->PIN & (1 << 23) ? 1 : 0;
    case P0_24: return LPC_GPIO0->PIN & (1 << 24) ? 1 : 0;
    case P0_25: return LPC_GPIO0->PIN & (1 << 25) ? 1 : 0;
    case P0_26: return LPC_GPIO0->PIN & (1 << 26) ? 1 : 0;
    case P0_27: return LPC_GPIO0->PIN & (1 << 27) ? 1 : 0;
    case P0_28: return LPC_GPIO0->PIN & (1 << 28) ? 1 : 0;
    case P0_29: return LPC_GPIO0->PIN & (1 << 29) ? 1 : 0;
    case P0_30: return LPC_GPIO0->PIN & (1 << 30) ? 1 : 0;
    case P0_31: return LPC_GPIO0->PIN & (1 << 31) ? 1 : 0;
    case P1_0: return LPC_GPIO1->PIN & (1 << 0) ? 1 : 0;
    case P1_1: return LPC_GPIO1->PIN & (1 << 1) ? 1 : 0;
    case P1_2: return LPC_GPIO1->PIN & (1 << 2) ? 1 : 0;
    case P1_3: return LPC_GPIO1->PIN & (1 << 3) ? 1 : 0;
    case P1_4: return LPC_GPIO1->PIN & (1 << 4) ? 1 : 0;
    case P1_5: return LPC_GPIO1->PIN & (1 << 5) ? 1 : 0;
    case P1_6: return LPC_GPIO1->PIN & (1 << 6) ? 1 : 0;
    case P2_0: return LPC_GPIO2->PIN & (1 << 0) ? 1 : 0;
    case P2_1: return LPC_GPIO2->PIN & (1 << 1) ? 1 : 0;
    case P2_2: return LPC_GPIO2->PIN & (1 << 2) ? 1 : 0;
    case P2_3: return LPC_GPIO2->PIN & (1 << 3) ? 1 : 0;
    case P2_4: return LPC_GPIO2->PIN & (1 << 4) ? 1 : 0;
    case P2_5: return LPC_GPIO2->PIN & (1 << 5) ? 1 : 0;
    case P2_6: return LPC_GPIO2->PIN & (1 << 6) ? 1 : 0;
    case P2_7: return LPC_GPIO2->PIN & (1 << 7) ? 1 : 0;
    case P2_8: return LPC_GPIO2->PIN & (1 << 8) ? 1 : 0;
    case P2_9: return LPC_GPIO2->PIN & (1 << 9) ? 1 : 0;
    case P2_10: return LPC_GPIO2->PIN & (1 << 10) ? 1 : 0;
    case P2_11: return LPC_GPIO2->PIN & (1 << 11) ? 1 : 0;
    case P2_12: return LPC_GPIO2->PIN & (1 << 12) ? 1 : 0;
    case P2_13: return LPC_GPIO2->PIN & (1 << 13) ? 1 : 0;
    case P2_14: return LPC_GPIO2->PIN & (1 << 14) ? 1 : 0;
    case P2_15: return LPC_GPIO2->PIN & (1 << 15) ? 1 : 0;
    default:
      ERROR("Invalid IO pin.");
  }
}

INLINE
void pin_dir (enum pio_pin pin, enum pin_dir dir)
{
  switch (pin) {
    case P0_0: LPC_GPIO0->DIR = (LPC_GPIO0->DIR & ~(1 << 0)) | (dir ? 1 << 0 : 0); break;
    case P0_1: LPC_GPIO0->DIR = (LPC_GPIO0->DIR & ~(1 << 1)) | (dir ? 1 << 1 : 0); break;
    case P0_2: LPC_GPIO0->DIR = (LPC_GPIO0->DIR & ~(1 << 2)) | (dir ? 1 << 2 : 0); break;
    case P0_3: LPC_GPIO0->DIR = (LPC_GPIO0->DIR & ~(1 << 3)) | (dir ? 1 << 3 : 0); break;
    case P0_4: LPC_GPIO0->DIR = (LPC_GPIO0->DIR & ~(1 << 4)) | (dir ? 1 << 4 : 0); break;
    case P0_5: LPC_GPIO0->DIR = (LPC_GPIO0->DIR & ~(1 << 5)) | (dir ? 1 << 5 : 0); break;
    case P0_6: LPC_GPIO0->DIR = (LPC_GPIO0->DIR & ~(1 << 6)) | (dir ? 1 << 6 : 0); break;
    case P0_7: LPC_GPIO0->DIR = (LPC_GPIO0->DIR & ~(1 << 7)) | (dir ? 1 << 7 : 0); break;
    case P0_8: LPC_GPIO0->DIR = (LPC_GPIO0->DIR & ~(1 << 8)) | (dir ? 1 << 8 : 0); break;
    case P0_9: LPC_GPIO0->DIR = (LPC_GPIO0->DIR & ~(1 << 9)) | (dir ? 1 << 9 : 0); break;
    case P0_10: LPC_GPIO0->DIR = (LPC_GPIO0->DIR & ~(1 << 10)) | (dir ? 1 << 10 : 0); break;
    case P0_11: LPC_GPIO0->DIR = (LPC_GPIO0->DIR & ~(1 << 11)) | (dir ? 1 << 11 : 0); break;
    case P0_12: LPC_GPIO0->DIR = (LPC_GPIO0->DIR & ~(1 << 12)) | (dir ? 1 << 12 : 0); break;
    case P0_13: LPC_GPIO0->DIR = (LPC_GPIO0->DIR & ~(1 << 13)) | (dir ? 1 << 13 : 0); break;
    case P0_14: LPC_GPIO0->DIR = (LPC_GPIO0->DIR & ~(1 << 14)) | (dir ? 1 << 14 : 0); break;
    case P0_15: LPC_GPIO0->DIR = (LPC_GPIO0->DIR & ~(1 << 15)) | (dir ? 1 << 15 : 0); break;
    case P0_16: LPC_GPIO0->DIR = (LPC_GPIO0->DIR & ~(1 << 16)) | (dir ? 1 << 16 : 0); break;
    case P0_17: LPC_GPIO0->DIR = (LPC_GPIO0->DIR & ~(1 << 17)) | (dir ? 1 << 17 : 0); break;
    case P0_18: LPC_GPIO0->DIR = (LPC_GPIO0->DIR & ~(1 << 18)) | (dir ? 1 << 18 : 0); break;
    case P0_19: LPC_GPIO0->DIR = (LPC_GPIO0->DIR & ~(1 << 19)) | (dir ? 1 << 19 : 0); break;
    case P0_20: LPC_GPIO0->DIR = (LPC_GPIO0->DIR & ~(1 << 20)) | (dir ? 1 << 20 : 0); break;
    case P0_21: LPC_GPIO0->DIR = (LPC_GPIO0->DIR & ~(1 << 21)) | (dir ? 1 << 21 : 0); break;
    case P0_22: LPC_GPIO0->DIR = (LPC_GPIO0->DIR & ~(1 << 22)) | (dir ? 1 << 22 : 0); break;
    case P0_23: LPC_GPIO0->DIR = (LPC_GPIO0->DIR & ~(1 << 23)) | (dir ? 1 << 23 : 0); break;
    case P0_24: LPC_GPIO0->DIR = (LPC_GPIO0->DIR & ~(1 << 24)) | (dir ? 1 << 24 : 0); break;
    case P0_25: LPC_GPIO0->DIR = (LPC_GPIO0->DIR & ~(1 << 25)) | (dir ? 1 << 25 : 0); break;
    case P0_26: LPC_GPIO0->DIR = (LPC_GPIO0->DIR & ~(1 << 26)) | (dir ? 1 << 26 : 0); break;
    case P0_27: LPC_GPIO0->DIR = (LPC_GPIO0->DIR & ~(1 << 27)) | (dir ? 1 << 27 : 0); break;
    case P0_28: LPC_GPIO0->DIR = (LPC_GPIO0->DIR & ~(1 << 28)) | (dir ? 1 << 28 : 0); break;
    case P0_29: LPC_GPIO0->DIR = (LPC_GPIO0->DIR & ~(1 << 29)) | (dir ? 1 << 29 : 0); break;
    case P0_30: LPC_GPIO0->DIR = (LPC_GPIO0->DIR & ~(1 << 30)) | (dir ? 1 << 30 : 0); break;
    case P0_31: LPC_GPIO0->DIR = (LPC_GPIO0->DIR & ~(1 << 31)) | (dir ? 1 << 31 : 0); break;
    case P1_0: LPC_GPIO1->DIR = (LPC_GPIO1->DIR & ~(1 << 0)) | (dir ? 1 << 0 : 0); break;
    case P1_1: LPC_GPIO1->DIR = (LPC_GPIO1->DIR & ~(1 << 1)) | (dir ? 1 << 1 : 0); break;
    case P1_2: LPC_GPIO1->DIR = (LPC_GPIO1->DIR & ~(1 << 2)) | (dir ? 1 << 2 : 0); break;
    case P1_3: LPC_GPIO1->DIR = (LPC_GPIO1->DIR & ~(1 << 3)) | (dir ? 1 << 3 : 0); break;
    case P1_4: LPC_GPIO1->DIR = (LPC_GPIO1->DIR & ~(1 << 4)) | (dir ? 1 << 4 : 0); break;
    case P1_5: LPC_GPIO1->DIR = (LPC_GPIO1->DIR & ~(1 << 5)) | (dir ? 1 << 5 : 0); break;
    case P1_6: LPC_GPIO1->DIR = (LPC_GPIO1->DIR & ~(1 << 6)) | (dir ? 1 << 6 : 0); break;
    case P2_0: LPC_GPIO2->DIR = (LPC_GPIO2->DIR & ~(1 << 0)) | (dir ? 1 << 0 : 0); break;
    case P2_1: LPC_GPIO2->DIR = (LPC_GPIO2->DIR & ~(1 << 1)) | (dir ? 1 << 1 : 0); break;
    case P2_2: LPC_GPIO2->DIR = (LPC_GPIO2->DIR & ~(1 << 2)) | (dir ? 1 << 2 : 0); break;
    case P2_3: LPC_GPIO2->DIR = (LPC_GPIO2->DIR & ~(1 << 3)) | (dir ? 1 << 3 : 0); break;
    case P2_4: LPC_GPIO2->DIR = (LPC_GPIO2->DIR & ~(1 << 4)) | (dir ? 1 << 4 : 0); break;
    case P2_5: LPC_GPIO2->DIR = (LPC_GPIO2->DIR & ~(1 << 5)) | (dir ? 1 << 5 : 0); break;
    case P2_6: LPC_GPIO2->DIR = (LPC_GPIO2->DIR & ~(1 << 6)) | (dir ? 1 << 6 : 0); break;
    case P2_7: LPC_GPIO2->DIR = (LPC_GPIO2->DIR & ~(1 << 7)) | (dir ? 1 << 7 : 0); break;
    case P2_8: LPC_GPIO2->DIR = (LPC_GPIO2->DIR & ~(1 << 8)) | (dir ? 1 << 8 : 0); break;
    case P2_9: LPC_GPIO2->DIR = (LPC_GPIO2->DIR & ~(1 << 9)) | (dir ? 1 << 9 : 0); break;
    case P2_10: LPC_GPIO2->DIR = (LPC_GPIO2->DIR & ~(1 << 10)) | (dir ? 1 << 10 : 0); break;
    case P2_11: LPC_GPIO2->DIR = (LPC_GPIO2->DIR & ~(1 << 11)) | (dir ? 1 << 11 : 0); break;
    case P2_12: LPC_GPIO2->DIR = (LPC_GPIO2->DIR & ~(1 << 12)) | (dir ? 1 << 12 : 0); break;
    case P2_13: LPC_GPIO2->DIR = (LPC_GPIO2->DIR & ~(1 << 13)) | (dir ? 1 << 13 : 0); break;
    case P2_14: LPC_GPIO2->DIR = (LPC_GPIO2->DIR & ~(1 << 14)) | (dir ? 1 << 14 : 0); break;
    case P2_15: LPC_GPIO2->DIR = (LPC_GPIO2->DIR & ~(1 << 15)) | (dir ? 1 << 15 : 0); break;
    default:
      ERROR("Invalid IO pin.");
  }
}

#endif // IO_PIN_H