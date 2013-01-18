/*
   IO functions for NXP LPC131x devices in LQFP48 package.

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
  I2C_STD = 0,
  I2C_FAST = 0,
  I2C_GPIO = 1,
  I2C_FAST_PLUS = 2,
  PULL_NONE = 0,
  PULL_DOWN = 1,
  PULL_UP = 2,
  PULL_REPEATER = 3,
};

enum io_function {
  PIO, nRESET, CLKOUT, CT32B0_MAT2, USB_FTOGGLE, SSEL0, CT16B0_CAP0, USB_VBUS, SCL, SDA, nUSB_CONNECT, SCK0, CTS, MISO0, CT16B0_MAT0, MOSI0, CT16B0_MAT1, SWO, SWCLK, CT16B0_MAT2, AD0, CT32B0_MAT3, AD1, CT32B1_CAP0, AD2, CT32B1_MAT0, AD3, CT32B1_MAT1, SWDIO, AD4, CT32B1_MAT2, AD5, CT32B1_MAT3, WAKEUP, nRTS, CT32B0_CAP0, RXD, CT32B0_MAT0, TXD, CT32B0_MAT1, CT16B1_CAP0, CT16B1_MAT0, AD6, CT16B1_MAT1, AD7, nDTR, SSEL1, nDSR, SCK1, nDCD, MISO1, nRI, MOSI1
};

enum pio_pin {
  P0_0, P0_1, P0_2, P0_3, P0_4, P0_5, P0_6, P0_7, P0_8, P0_9, P0_10, P0_11, P1_0, P1_1, P1_2, P1_3, P1_4, P1_5, P1_6, P1_7, P1_8, P1_9, P1_10, P1_11, P2_0, P2_1, P2_2, P2_3, P2_4, P2_5, P2_6, P2_7, P2_8, P2_9, P2_10, P2_11, P3_0, P3_1, P3_2, P3_3, P3_4, P3_5
};

INLINE
void pin_setup (enum pio_pin pin, enum io_function func, enum io_mode mode, int hyst)
{
  int f = 0;
  int other = mode << 3 | hyst << 5 | 1 << 6;
  switch (pin) {
    case P0_0:
      switch (func) {
        case nRESET: f = 0; break;
        case PIO: f = 1; break;
        default:
          ERROR("PIO0_0 can only be used as nRESET or PIO.");
      }
      LPC_IOCON->RESET_PIO0_0 = f | other;
      break;
    case P0_1:
      switch (func) {
        case PIO: f = 0; break;
        case CLKOUT: f = 1; break;
        case CT32B0_MAT2: f = 2; break;
#ifdef CPU_HAS_USB
        case USB_FTOGGLE: f = 3; break;
#endif // CPU_HAS_USB
        default:
          ERROR("PIO0_1 can only be used as CLKOUT, CT32B0_MAT2, USB_FTOGGLE or PIO.");
      }
      LPC_IOCON->PIO0_1 = f | other;
      break;
    case P0_2:
      switch (func) {
        case PIO: f = 0; break;
        case SSEL0: f = 1; break;
        case CT16B0_CAP0: f = 2; break;
        default:
          ERROR("PIO0_2 can only be used as SSEL0, CT16B0_CAP0 or PIO.");
      }
      LPC_IOCON->PIO0_2 = f | other;
      break;
    case P0_3:
      switch (func) {
        case PIO: f = 0; break;
#ifdef CPU_HAS_USB
        case USB_VBUS: f = 1; break;
#endif // CPU_HAS_USB
        default:
          ERROR("PIO0_3 can only be used as USB_VBUS or PIO.");
      }
      LPC_IOCON->PIO0_3 = f | other;
      break;
    case P0_4:
      switch (func) {
        case PIO: f = 0; other = mode << 8;
          if (mode == I2C_FAST_PLUS)
            ERROR("I2C_FAST_PLUS cannot be used with PIO function.");
          if (hyst)
            ERROR("Hysteresis is not available on I2C pins.");
          break;
        case SCL: f = 1; other = mode << 8;
          if (hyst)
            ERROR("Hysteresis is not available on I2C pins.");
          break;
        default:
          ERROR("PIO0_4 can only be used as SCL or PIO.");
      }
      LPC_IOCON->PIO0_4 = f | other;
      break;
    case P0_5:
      switch (func) {
        case PIO: f = 0; other = mode << 8;
          if (mode == I2C_FAST_PLUS)
            ERROR("I2C_FAST_PLUS cannot be used with PIO function.");
          if (hyst)
            ERROR("Hysteresis is not available on I2C pins.");
          break;
        case SDA: f = 1; other = mode << 8;
          if (hyst)
            ERROR("Hysteresis is not available on I2C pins.");
          break;
        default:
          ERROR("PIO0_5 can only be used as SDA or PIO.");
      }
      LPC_IOCON->PIO0_5 = f | other;
      break;
    case P0_6:
      switch (func) {
        case PIO: f = 0; break;
        case nUSB_CONNECT: f = 1; break;
        case SCK0: f = 2; break;
        default:
          ERROR("PIO0_6 can only be used as nUSB_CONNECT, SCK0 or PIO.");
      }
      LPC_IOCON->PIO0_6 = f | other;
      break;
    case P0_7:
      switch (func) {
        case PIO: f = 0; break;
        case CTS: f = 1; break;
        default:
          ERROR("PIO0_7 can only be used as CTS or PIO.");
      }
      LPC_IOCON->PIO0_7 = f | other;
      break;
    case P0_8:
      switch (func) {
        case PIO: f = 0; break;
        case MISO0: f = 1; break;
        case CT16B0_MAT0: f = 2; break;
        default:
          ERROR("PIO0_8 can only be used as MISO0, CT16B0_MAT0 or PIO.");
      }
      LPC_IOCON->PIO0_8 = f | other;
      break;
    case P0_9:
      switch (func) {
        case PIO: f = 0; break;
        case MOSI0: f = 1; break;
        case CT16B0_MAT1: f = 2; break;
        case SWO: f = 3; break;
        default:
          ERROR("PIO0_9 can only be used as MOSI0, CT16B0_MAT1, SWO or PIO.");
      }
      LPC_IOCON->PIO0_9 = f | other;
      break;
    case P0_10:
      switch (func) {
        case SWCLK: f = 0; break;
        case PIO: f = 1; break;
        case SCK0: f = 2; break;
        case CT16B0_MAT2: f = 3; break;
        default:
          ERROR("PIO0_10 can only be used as SWCLK, SCK0, CT16B0_MAT2 or PIO.");
      }
      LPC_IOCON->JTAG_TCK_PIO0_10 = f | other;
      break;
    case P0_11:
      switch (func) {
        case PIO: f = 1; other |= 1 << 7; break;
        case AD0: f = 2; break;
        case CT32B0_MAT3: f = 3; other |= 1 << 7; break;
        default:
          ERROR("PIO0_11 can only be used as AD0, CT32B0_MAT3 or PIO.");
      }
      LPC_IOCON->JTAG_TDI_PIO0_11 = f | other;
      break;
    case P1_0:
      switch (func) {
        case PIO: f = 1; other |= 1 << 7; break;
        case AD1: f = 2; break;
        case CT32B1_CAP0: f = 3; other |= 1 << 7; break;
        default:
          ERROR("PIO1_0 can only be used as AD1, CT32B1_CAP0 or PIO.");
      }
      LPC_IOCON->JTAG_TMS_PIO1_0 = f | other;
      break;
    case P1_1:
      switch (func) {
        case PIO: f = 1; other |= 1 << 7; break;
        case AD2: f = 2; break;
        case CT32B1_MAT0: f = 3; other |= 1 << 7; break;
        default:
          ERROR("PIO1_1 can only be used as AD2, CT32B1_MAT0 or PIO.");
      }
      LPC_IOCON->JTAG_TDO_PIO1_1 = f | other;
      break;
    case P1_2:
      switch (func) {
        case PIO: f = 1; other |= 1 << 7; break;
        case AD3: f = 2; break;
        case CT32B1_MAT1: f = 3; other |= 1 << 7; break;
        default:
          ERROR("PIO1_2 can only be used as AD3, CT32B1_MAT1 or PIO.");
      }
      LPC_IOCON->JTAG_nTRST_PIO1_2 = f | other;
      break;
    case P1_3:
      switch (func) {
        case SWDIO: f = 0; other |= 1 << 7; break;
        case PIO: f = 1; other |= 1 << 7; break;
        case AD4: f = 2; break;
        case CT32B1_MAT2: f = 3; other |= 1 << 7; break;
        default:
          ERROR("PIO1_3 can only be used as SWDIO, AD4, CT32B1_MAT2 or PIO.");
      }
      LPC_IOCON->ARM_SWDIO_PIO1_3 = f | other;
      break;
    case P1_4:
      switch (func) {
        case PIO: f = 0; other |= 1 << 7; break;
        case AD5: f = 1; break;
        case CT32B1_MAT3: f = 2; other |= 1 << 7; break;
        case WAKEUP: f = 3; other |= 1 << 7; break;
        default:
          ERROR("PIO1_4 can only be used as AD5, CT32B1_MAT3, WAKEUP or PIO.");
      }
      LPC_IOCON->PIO1_4 = f | other;
      break;
    case P1_5:
      switch (func) {
        case PIO: f = 0; break;
        case nRTS: f = 1; break;
        case CT32B0_CAP0: f = 2; break;
        default:
          ERROR("PIO1_5 can only be used as nRTS, CT32B0_CAP0 or PIO.");
      }
      LPC_IOCON->PIO1_5 = f | other;
      break;
    case P1_6:
      switch (func) {
        case PIO: f = 0; break;
        case RXD: f = 1; break;
        case CT32B0_MAT0: f = 2; break;
        default:
          ERROR("PIO1_6 can only be used as RXD, CT32B0_MAT0 or PIO.");
      }
      LPC_IOCON->PIO1_6 = f | other;
      break;
    case P1_7:
      switch (func) {
        case PIO: f = 0; break;
        case TXD: f = 1; break;
        case CT32B0_MAT1: f = 2; break;
        default:
          ERROR("PIO1_7 can only be used as TXD, CT32B0_MAT1 or PIO.");
      }
      LPC_IOCON->PIO1_7 = f | other;
      break;
    case P1_8:
      switch (func) {
        case PIO: f = 0; break;
        case CT16B1_CAP0: f = 1; break;
        default:
          ERROR("PIO1_8 can only be used as CT16B1_CAP0 or PIO.");
      }
      LPC_IOCON->PIO1_8 = f | other;
      break;
    case P1_9:
      switch (func) {
        case PIO: f = 0; break;
        case CT16B1_MAT0: f = 1; break;
        default:
          ERROR("PIO1_9 can only be used as CT16B1_MAT0 or PIO.");
      }
      LPC_IOCON->PIO1_9 = f | other;
      break;
    case P1_10:
      switch (func) {
        case PIO: f = 0; other |= 1 << 7; break;
        case AD6: f = 1; break;
        case CT16B1_MAT1: f = 2; other |= 1 << 7; break;
        default:
          ERROR("PIO1_10 can only be used as AD6, CT16B1_MAT1 or PIO.");
      }
      LPC_IOCON->PIO1_10 = f | other;
      break;
    case P1_11:
      switch (func) {
        case PIO: f = 0; other |= 1 << 7; break;
        case AD7: f = 1; break;
        default:
          ERROR("PIO1_11 can only be used as AD7 or PIO.");
      }
      LPC_IOCON->PIO1_11 = f | other;
      break;
    case P2_0:
      switch (func) {
        case PIO: f = 0; break;
        case nDTR: f = 1; break;
        case SSEL1: f = 2; break;
        default:
          ERROR("PIO2_0 can only be used as nDTR, SSEL1 or PIO.");
      }
      LPC_IOCON->PIO2_0 = f | other;
      break;
    case P2_1:
      switch (func) {
        case PIO: f = 0; break;
        case nDSR: f = 1; break;
        case SCK1: f = 2; break;
        default:
          ERROR("PIO2_1 can only be used as nDSR, SCK1 or PIO.");
      }
      LPC_IOCON->PIO2_1 = f | other;
      break;
    case P2_2:
      switch (func) {
        case PIO: f = 0; break;
        case nDCD: f = 1; break;
        case MISO1: f = 2; break;
        default:
          ERROR("PIO2_2 can only be used as nDCD, MISO1 or PIO.");
      }
      LPC_IOCON->PIO2_2 = f | other;
      break;
    case P2_3:
      switch (func) {
        case PIO: f = 0; break;
        case nRI: f = 1; break;
        case MOSI1: f = 2; break;
        default:
          ERROR("PIO2_3 can only be used as nRI, MOSI1 or PIO.");
      }
      LPC_IOCON->PIO2_3 = f | other;
      break;
    case P2_4:
      if (func != PIO) ERROR("PIO2_4 can only be used as PIO.");
      f = 0;
      LPC_IOCON->PIO2_4 = f | other;
      break;
    case P2_5:
      if (func != PIO) ERROR("PIO2_5 can only be used as PIO.");
      f = 0;
      LPC_IOCON->PIO2_5 = f | other;
      break;
    case P2_6:
      if (func != PIO) ERROR("PIO2_6 can only be used as PIO.");
      f = 0;
      LPC_IOCON->PIO2_6 = f | other;
      break;
    case P2_7:
      if (func != PIO) ERROR("PIO2_7 can only be used as PIO.");
      f = 0;
      LPC_IOCON->PIO2_7 = f | other;
      break;
    case P2_8:
      if (func != PIO) ERROR("PIO2_8 can only be used as PIO.");
      f = 0;
      LPC_IOCON->PIO2_8 = f | other;
      break;
    case P2_9:
      if (func != PIO) ERROR("PIO2_9 can only be used as PIO.");
      f = 0;
      LPC_IOCON->PIO2_9 = f | other;
      break;
    case P2_10:
      if (func != PIO) ERROR("PIO2_10 can only be used as PIO.");
      f = 0;
      LPC_IOCON->PIO2_10 = f | other;
      break;
    case P2_11:
      switch (func) {
        case PIO: f = 0; break;
        case SCK0: f = 1; break;
        default:
          ERROR("PIO2_11 can only be used as SCK0 or PIO.");
      }
      LPC_IOCON->PIO2_11 = f | other;
      break;
    case P3_0:
      switch (func) {
        case PIO: f = 0; break;
        case nDTR: f = 1; break;
        default:
          ERROR("PIO3_0 can only be used as nDTR or PIO.");
      }
      LPC_IOCON->PIO3_0 = f | other;
      break;
    case P3_1:
      switch (func) {
        case PIO: f = 0; break;
        case nDSR: f = 1; break;
        default:
          ERROR("PIO3_1 can only be used as nDSR or PIO.");
      }
      LPC_IOCON->PIO3_1 = f | other;
      break;
    case P3_2:
      switch (func) {
        case PIO: f = 0; break;
        case nDCD: f = 1; break;
        default:
          ERROR("PIO3_2 can only be used as nDCD or PIO.");
      }
      LPC_IOCON->PIO3_2 = f | other;
      break;
    case P3_3:
      switch (func) {
        case PIO: f = 0; break;
        case nRI: f = 1; break;
        default:
          ERROR("PIO3_3 can only be used as nRI or PIO.");
      }
      LPC_IOCON->PIO3_3 = f | other;
      break;
    case P3_4:
      if (func != PIO) ERROR("PIO3_4 can only be used as PIO.");
      f = 0;
      LPC_IOCON->PIO3_4 = f | other;
      break;
    case P3_5:
      if (func != PIO) ERROR("PIO3_5 can only be used as PIO.");
      f = 0;
      LPC_IOCON->PIO3_5 = f | other;
      break;
    default:
      ERROR("Invalid IO pin.");
  }
}

INLINE
void pin_write (enum pio_pin pin, int val)
{
  switch (pin) {
    case P0_0: LPC_GPIO0->MASKED_ACCESS[1 << 0] = val ? 0xffff : 0x0000; break;
    case P0_1: LPC_GPIO0->MASKED_ACCESS[1 << 1] = val ? 0xffff : 0x0000; break;
    case P0_2: LPC_GPIO0->MASKED_ACCESS[1 << 2] = val ? 0xffff : 0x0000; break;
    case P0_3: LPC_GPIO0->MASKED_ACCESS[1 << 3] = val ? 0xffff : 0x0000; break;
    case P0_4: LPC_GPIO0->MASKED_ACCESS[1 << 4] = val ? 0xffff : 0x0000; break;
    case P0_5: LPC_GPIO0->MASKED_ACCESS[1 << 5] = val ? 0xffff : 0x0000; break;
    case P0_6: LPC_GPIO0->MASKED_ACCESS[1 << 6] = val ? 0xffff : 0x0000; break;
    case P0_7: LPC_GPIO0->MASKED_ACCESS[1 << 7] = val ? 0xffff : 0x0000; break;
    case P0_8: LPC_GPIO0->MASKED_ACCESS[1 << 8] = val ? 0xffff : 0x0000; break;
    case P0_9: LPC_GPIO0->MASKED_ACCESS[1 << 9] = val ? 0xffff : 0x0000; break;
    case P0_10: LPC_GPIO0->MASKED_ACCESS[1 << 10] = val ? 0xffff : 0x0000; break;
    case P0_11: LPC_GPIO0->MASKED_ACCESS[1 << 11] = val ? 0xffff : 0x0000; break;
    case P1_0: LPC_GPIO1->MASKED_ACCESS[1 << 0] = val ? 0xffff : 0x0000; break;
    case P1_1: LPC_GPIO1->MASKED_ACCESS[1 << 1] = val ? 0xffff : 0x0000; break;
    case P1_2: LPC_GPIO1->MASKED_ACCESS[1 << 2] = val ? 0xffff : 0x0000; break;
    case P1_3: LPC_GPIO1->MASKED_ACCESS[1 << 3] = val ? 0xffff : 0x0000; break;
    case P1_4: LPC_GPIO1->MASKED_ACCESS[1 << 4] = val ? 0xffff : 0x0000; break;
    case P1_5: LPC_GPIO1->MASKED_ACCESS[1 << 5] = val ? 0xffff : 0x0000; break;
    case P1_6: LPC_GPIO1->MASKED_ACCESS[1 << 6] = val ? 0xffff : 0x0000; break;
    case P1_7: LPC_GPIO1->MASKED_ACCESS[1 << 7] = val ? 0xffff : 0x0000; break;
    case P1_8: LPC_GPIO1->MASKED_ACCESS[1 << 8] = val ? 0xffff : 0x0000; break;
    case P1_9: LPC_GPIO1->MASKED_ACCESS[1 << 9] = val ? 0xffff : 0x0000; break;
    case P1_10: LPC_GPIO1->MASKED_ACCESS[1 << 10] = val ? 0xffff : 0x0000; break;
    case P1_11: LPC_GPIO1->MASKED_ACCESS[1 << 11] = val ? 0xffff : 0x0000; break;
    case P2_0: LPC_GPIO2->MASKED_ACCESS[1 << 0] = val ? 0xffff : 0x0000; break;
    case P2_1: LPC_GPIO2->MASKED_ACCESS[1 << 1] = val ? 0xffff : 0x0000; break;
    case P2_2: LPC_GPIO2->MASKED_ACCESS[1 << 2] = val ? 0xffff : 0x0000; break;
    case P2_3: LPC_GPIO2->MASKED_ACCESS[1 << 3] = val ? 0xffff : 0x0000; break;
    case P2_4: LPC_GPIO2->MASKED_ACCESS[1 << 4] = val ? 0xffff : 0x0000; break;
    case P2_5: LPC_GPIO2->MASKED_ACCESS[1 << 5] = val ? 0xffff : 0x0000; break;
    case P2_6: LPC_GPIO2->MASKED_ACCESS[1 << 6] = val ? 0xffff : 0x0000; break;
    case P2_7: LPC_GPIO2->MASKED_ACCESS[1 << 7] = val ? 0xffff : 0x0000; break;
    case P2_8: LPC_GPIO2->MASKED_ACCESS[1 << 8] = val ? 0xffff : 0x0000; break;
    case P2_9: LPC_GPIO2->MASKED_ACCESS[1 << 9] = val ? 0xffff : 0x0000; break;
    case P2_10: LPC_GPIO2->MASKED_ACCESS[1 << 10] = val ? 0xffff : 0x0000; break;
    case P2_11: LPC_GPIO2->MASKED_ACCESS[1 << 11] = val ? 0xffff : 0x0000; break;
    case P3_0: LPC_GPIO3->MASKED_ACCESS[1 << 0] = val ? 0xffff : 0x0000; break;
    case P3_1: LPC_GPIO3->MASKED_ACCESS[1 << 1] = val ? 0xffff : 0x0000; break;
    case P3_2: LPC_GPIO3->MASKED_ACCESS[1 << 2] = val ? 0xffff : 0x0000; break;
    case P3_3: LPC_GPIO3->MASKED_ACCESS[1 << 3] = val ? 0xffff : 0x0000; break;
    case P3_4: LPC_GPIO3->MASKED_ACCESS[1 << 4] = val ? 0xffff : 0x0000; break;
    case P3_5: LPC_GPIO3->MASKED_ACCESS[1 << 5] = val ? 0xffff : 0x0000; break;
    default:
      ERROR("Invalid IO pin.");
  }
}

INLINE
int pin_read (enum pio_pin pin)
{
  switch (pin) {
    case P0_0: return LPC_GPIO0->MASKED_ACCESS[1 << 0] ? 1 : 0;
    case P0_1: return LPC_GPIO0->MASKED_ACCESS[1 << 1] ? 1 : 0;
    case P0_2: return LPC_GPIO0->MASKED_ACCESS[1 << 2] ? 1 : 0;
    case P0_3: return LPC_GPIO0->MASKED_ACCESS[1 << 3] ? 1 : 0;
    case P0_4: return LPC_GPIO0->MASKED_ACCESS[1 << 4] ? 1 : 0;
    case P0_5: return LPC_GPIO0->MASKED_ACCESS[1 << 5] ? 1 : 0;
    case P0_6: return LPC_GPIO0->MASKED_ACCESS[1 << 6] ? 1 : 0;
    case P0_7: return LPC_GPIO0->MASKED_ACCESS[1 << 7] ? 1 : 0;
    case P0_8: return LPC_GPIO0->MASKED_ACCESS[1 << 8] ? 1 : 0;
    case P0_9: return LPC_GPIO0->MASKED_ACCESS[1 << 9] ? 1 : 0;
    case P0_10: return LPC_GPIO0->MASKED_ACCESS[1 << 10] ? 1 : 0;
    case P0_11: return LPC_GPIO0->MASKED_ACCESS[1 << 11] ? 1 : 0;
    case P1_0: return LPC_GPIO1->MASKED_ACCESS[1 << 0] ? 1 : 0;
    case P1_1: return LPC_GPIO1->MASKED_ACCESS[1 << 1] ? 1 : 0;
    case P1_2: return LPC_GPIO1->MASKED_ACCESS[1 << 2] ? 1 : 0;
    case P1_3: return LPC_GPIO1->MASKED_ACCESS[1 << 3] ? 1 : 0;
    case P1_4: return LPC_GPIO1->MASKED_ACCESS[1 << 4] ? 1 : 0;
    case P1_5: return LPC_GPIO1->MASKED_ACCESS[1 << 5] ? 1 : 0;
    case P1_6: return LPC_GPIO1->MASKED_ACCESS[1 << 6] ? 1 : 0;
    case P1_7: return LPC_GPIO1->MASKED_ACCESS[1 << 7] ? 1 : 0;
    case P1_8: return LPC_GPIO1->MASKED_ACCESS[1 << 8] ? 1 : 0;
    case P1_9: return LPC_GPIO1->MASKED_ACCESS[1 << 9] ? 1 : 0;
    case P1_10: return LPC_GPIO1->MASKED_ACCESS[1 << 10] ? 1 : 0;
    case P1_11: return LPC_GPIO1->MASKED_ACCESS[1 << 11] ? 1 : 0;
    case P2_0: return LPC_GPIO2->MASKED_ACCESS[1 << 0] ? 1 : 0;
    case P2_1: return LPC_GPIO2->MASKED_ACCESS[1 << 1] ? 1 : 0;
    case P2_2: return LPC_GPIO2->MASKED_ACCESS[1 << 2] ? 1 : 0;
    case P2_3: return LPC_GPIO2->MASKED_ACCESS[1 << 3] ? 1 : 0;
    case P2_4: return LPC_GPIO2->MASKED_ACCESS[1 << 4] ? 1 : 0;
    case P2_5: return LPC_GPIO2->MASKED_ACCESS[1 << 5] ? 1 : 0;
    case P2_6: return LPC_GPIO2->MASKED_ACCESS[1 << 6] ? 1 : 0;
    case P2_7: return LPC_GPIO2->MASKED_ACCESS[1 << 7] ? 1 : 0;
    case P2_8: return LPC_GPIO2->MASKED_ACCESS[1 << 8] ? 1 : 0;
    case P2_9: return LPC_GPIO2->MASKED_ACCESS[1 << 9] ? 1 : 0;
    case P2_10: return LPC_GPIO2->MASKED_ACCESS[1 << 10] ? 1 : 0;
    case P2_11: return LPC_GPIO2->MASKED_ACCESS[1 << 11] ? 1 : 0;
    case P3_0: return LPC_GPIO3->MASKED_ACCESS[1 << 0] ? 1 : 0;
    case P3_1: return LPC_GPIO3->MASKED_ACCESS[1 << 1] ? 1 : 0;
    case P3_2: return LPC_GPIO3->MASKED_ACCESS[1 << 2] ? 1 : 0;
    case P3_3: return LPC_GPIO3->MASKED_ACCESS[1 << 3] ? 1 : 0;
    case P3_4: return LPC_GPIO3->MASKED_ACCESS[1 << 4] ? 1 : 0;
    case P3_5: return LPC_GPIO3->MASKED_ACCESS[1 << 5] ? 1 : 0;
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
    case P1_0: LPC_GPIO1->DIR = (LPC_GPIO1->DIR & ~(1 << 0)) | (dir ? 1 << 0 : 0); break;
    case P1_1: LPC_GPIO1->DIR = (LPC_GPIO1->DIR & ~(1 << 1)) | (dir ? 1 << 1 : 0); break;
    case P1_2: LPC_GPIO1->DIR = (LPC_GPIO1->DIR & ~(1 << 2)) | (dir ? 1 << 2 : 0); break;
    case P1_3: LPC_GPIO1->DIR = (LPC_GPIO1->DIR & ~(1 << 3)) | (dir ? 1 << 3 : 0); break;
    case P1_4: LPC_GPIO1->DIR = (LPC_GPIO1->DIR & ~(1 << 4)) | (dir ? 1 << 4 : 0); break;
    case P1_5: LPC_GPIO1->DIR = (LPC_GPIO1->DIR & ~(1 << 5)) | (dir ? 1 << 5 : 0); break;
    case P1_6: LPC_GPIO1->DIR = (LPC_GPIO1->DIR & ~(1 << 6)) | (dir ? 1 << 6 : 0); break;
    case P1_7: LPC_GPIO1->DIR = (LPC_GPIO1->DIR & ~(1 << 7)) | (dir ? 1 << 7 : 0); break;
    case P1_8: LPC_GPIO1->DIR = (LPC_GPIO1->DIR & ~(1 << 8)) | (dir ? 1 << 8 : 0); break;
    case P1_9: LPC_GPIO1->DIR = (LPC_GPIO1->DIR & ~(1 << 9)) | (dir ? 1 << 9 : 0); break;
    case P1_10: LPC_GPIO1->DIR = (LPC_GPIO1->DIR & ~(1 << 10)) | (dir ? 1 << 10 : 0); break;
    case P1_11: LPC_GPIO1->DIR = (LPC_GPIO1->DIR & ~(1 << 11)) | (dir ? 1 << 11 : 0); break;
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
    case P3_0: LPC_GPIO3->DIR = (LPC_GPIO3->DIR & ~(1 << 0)) | (dir ? 1 << 0 : 0); break;
    case P3_1: LPC_GPIO3->DIR = (LPC_GPIO3->DIR & ~(1 << 1)) | (dir ? 1 << 1 : 0); break;
    case P3_2: LPC_GPIO3->DIR = (LPC_GPIO3->DIR & ~(1 << 2)) | (dir ? 1 << 2 : 0); break;
    case P3_3: LPC_GPIO3->DIR = (LPC_GPIO3->DIR & ~(1 << 3)) | (dir ? 1 << 3 : 0); break;
    case P3_4: LPC_GPIO3->DIR = (LPC_GPIO3->DIR & ~(1 << 4)) | (dir ? 1 << 4 : 0); break;
    case P3_5: LPC_GPIO3->DIR = (LPC_GPIO3->DIR & ~(1 << 5)) | (dir ? 1 << 5 : 0); break;
    default:
      ERROR("Invalid IO pin.");
  }
}

#endif // IO_PIN_H