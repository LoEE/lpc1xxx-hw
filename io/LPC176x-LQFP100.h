/*
   IO functions for NXP LPC176x devices in LQFP100 package.

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
  PULL_NONE = 0,
  PULL_DOWN = 1,
  PULL_UP = 2,
  PULL_REPEATER = 3,
  IO_OPEN_DRAIN = 1 << 8,
};

enum io_function {
  PIO, RD1, TXD3, SDA1, TD1, RXD3, SCL1, TXD0, AD0_7, RXD0, AD0_6, I2SRX_CLK, RD2, CAP2_0, I2SRX_WS, TD2, CAP2_1, I2SRX_SDA, SSEL1, MAT2_0, I2STX_CLK, SCK1, MAT2_1, I2STX_WS, MISO1, MAT2_2, I2STX_SDA, MOSI1, MAT2_3, TXD2, SDA2, MAT3_0, RXD2, SCL2, MAT3_1, TXD1, SCK0, SCK, RXD1, SSEL0, SSEL, CTS1, MISO0, MISO, DCD1, MOSI0, MOSI, DSR1, DTR1, RI1, RTS1, AD0_0, CAP3_0, AD0_1, CAP3_1, AD0_2, AD0_3, AOUT, SDA0, USB_SDA, SCL0, USB_SCL, USB_Dp, USB_Dm, ENET_TXD0, ENET_TXD1, ENET_TX_EN, ENET_CRS, ENET_RXD0, ENET_RXD1, ENET_RX_ER, ENET_REF_CLK, ENET_MDC, ENET_MDIO, USB_UP_LED, PWM1_1, CAP1_0, MCOA0, nUSB_PPWR, CAP1_1, MCI0, PWM1_2, nMCABORT, PWM1_3, MCOB0, USB_PWRD, MAT1_0, MCI1, PWM1_4, MCI2, PWM1_5, MCOA1, MAT1_1, MCOB1, PWM1_6, CAP0_0, CLKOUT, nUSB_OVRCR, CAP0_1, MCOA2, PCAP1_0, MAT0_0, MCOB2, PCAP1_1, MAT0_1, VBUS, AD0_4, AD0_5, TRACEDATA_3, TRACEDATA_2, TRACEDATA_1, TRACEDATA_0, TRACECLK, USB_CONNECT, nEINT0, NMI, nEINT1, nEINT2, nEINT3, STCLK, RX_MCLK, TX_MCLK
};

enum pio_pin {
  P0_0, P0_1, P0_2, P0_3, P0_4, P0_5, P0_6, P0_7, P0_8, P0_9, P0_10, P0_11, P0_15, P0_16, P0_17, P0_18, P0_19, P0_20, P0_21, P0_22, P0_23, P0_24, P0_25, P0_26, P0_27, P0_28, P0_29, P0_30, P1_0, P1_1, P1_4, P1_8, P1_9, P1_10, P1_14, P1_15, P1_16, P1_17, P1_18, P1_19, P1_20, P1_21, P1_22, P1_23, P1_24, P1_25, P1_26, P1_27, P1_28, P1_29, P1_30, P1_31, P2_0, P2_1, P2_2, P2_3, P2_4, P2_5, P2_6, P2_7, P2_8, P2_9, P2_10, P2_11, P2_12, P2_13, P3_25, P3_26, P4_28, P4_29
};

INLINE
void pin_setup (enum pio_pin pin, enum io_function func, enum io_mode mode)
{
  int pull;
  switch (mode & 3) {
    case PULL_NONE: pull = 2; break;
    case PULL_DOWN: pull = 3; break;
    case PULL_UP:   pull = 0; break;
    case PULL_REPEATER: pull = 1; break;
  }
  switch (pin) {
    case P0_0:
      switch (func) {
        case PIO:
          LPC_PINCON->PINSEL0 = (LPC_PINCON->PINSEL0 & ~(3 << 0)) | (0 << 0);
          break;
        case RD1:
          LPC_PINCON->PINSEL0 = (LPC_PINCON->PINSEL0 & ~(3 << 0)) | (1 << 0);
          break;
        case TXD3:
          LPC_PINCON->PINSEL0 = (LPC_PINCON->PINSEL0 & ~(3 << 0)) | (2 << 0);
          break;
        case SDA1:
          LPC_PINCON->PINSEL0 = (LPC_PINCON->PINSEL0 & ~(3 << 0)) | (3 << 0);
          if (!(mode & IO_OPEN_DRAIN))
            ERROR("You must set IO_OPEN_DRAIN since pin P0_0 is not dedicated to I2C.");
          break;
        default:
          ERROR("P0_0 can only be used as RD1, TXD3, SDA1 or PIO.");
      }
      LPC_PINCON->PINMODE_OD0 = (LPC_PINCON->PINMODE_OD0 & ~(1 << 0)) | ((mode & IO_OPEN_DRAIN ? 1 : 0) << 0);
      LPC_PINCON->PINMODE0 = (LPC_PINCON->PINMODE0 & ~(3 << 0)) | (pull << 0);
      break;
    case P0_1:
      switch (func) {
        case PIO:
          LPC_PINCON->PINSEL0 = (LPC_PINCON->PINSEL0 & ~(3 << 2)) | (0 << 2);
          break;
        case TD1:
          LPC_PINCON->PINSEL0 = (LPC_PINCON->PINSEL0 & ~(3 << 2)) | (1 << 2);
          break;
        case RXD3:
          LPC_PINCON->PINSEL0 = (LPC_PINCON->PINSEL0 & ~(3 << 2)) | (2 << 2);
          break;
        case SCL1:
          LPC_PINCON->PINSEL0 = (LPC_PINCON->PINSEL0 & ~(3 << 2)) | (3 << 2);
          if (!(mode & IO_OPEN_DRAIN))
            ERROR("You must set IO_OPEN_DRAIN since pin P0_1 is not dedicated to I2C.");
          break;
        default:
          ERROR("P0_1 can only be used as TD1, RXD3, SCL1 or PIO.");
      }
      LPC_PINCON->PINMODE_OD0 = (LPC_PINCON->PINMODE_OD0 & ~(1 << 1)) | ((mode & IO_OPEN_DRAIN ? 1 : 0) << 1);
      LPC_PINCON->PINMODE0 = (LPC_PINCON->PINMODE0 & ~(3 << 2)) | (pull << 2);
      break;
    case P0_2:
      switch (func) {
        case PIO:
          LPC_PINCON->PINSEL0 = (LPC_PINCON->PINSEL0 & ~(3 << 4)) | (0 << 4);
          break;
        case TXD0:
          LPC_PINCON->PINSEL0 = (LPC_PINCON->PINSEL0 & ~(3 << 4)) | (1 << 4);
          break;
        case AD0_7:
          LPC_PINCON->PINSEL0 = (LPC_PINCON->PINSEL0 & ~(3 << 4)) | (2 << 4);
          break;
        default:
          ERROR("P0_2 can only be used as TXD0, AD0_7 or PIO.");
      }
      LPC_PINCON->PINMODE_OD0 = (LPC_PINCON->PINMODE_OD0 & ~(1 << 2)) | ((mode & IO_OPEN_DRAIN ? 1 : 0) << 2);
      LPC_PINCON->PINMODE0 = (LPC_PINCON->PINMODE0 & ~(3 << 4)) | (pull << 4);
      break;
    case P0_3:
      switch (func) {
        case PIO:
          LPC_PINCON->PINSEL0 = (LPC_PINCON->PINSEL0 & ~(3 << 6)) | (0 << 6);
          break;
        case RXD0:
          LPC_PINCON->PINSEL0 = (LPC_PINCON->PINSEL0 & ~(3 << 6)) | (1 << 6);
          break;
        case AD0_6:
          LPC_PINCON->PINSEL0 = (LPC_PINCON->PINSEL0 & ~(3 << 6)) | (2 << 6);
          break;
        default:
          ERROR("P0_3 can only be used as RXD0, AD0_6 or PIO.");
      }
      LPC_PINCON->PINMODE_OD0 = (LPC_PINCON->PINMODE_OD0 & ~(1 << 3)) | ((mode & IO_OPEN_DRAIN ? 1 : 0) << 3);
      LPC_PINCON->PINMODE0 = (LPC_PINCON->PINMODE0 & ~(3 << 6)) | (pull << 6);
      break;
    case P0_4:
      switch (func) {
        case PIO:
          LPC_PINCON->PINSEL0 = (LPC_PINCON->PINSEL0 & ~(3 << 8)) | (0 << 8);
          break;
        case I2SRX_CLK:
          LPC_PINCON->PINSEL0 = (LPC_PINCON->PINSEL0 & ~(3 << 8)) | (1 << 8);
          break;
        case RD2:
          LPC_PINCON->PINSEL0 = (LPC_PINCON->PINSEL0 & ~(3 << 8)) | (2 << 8);
          break;
        case CAP2_0:
          LPC_PINCON->PINSEL0 = (LPC_PINCON->PINSEL0 & ~(3 << 8)) | (3 << 8);
          break;
        default:
          ERROR("P0_4 can only be used as I2SRX_CLK, RD2, CAP2_0 or PIO.");
      }
      LPC_PINCON->PINMODE_OD0 = (LPC_PINCON->PINMODE_OD0 & ~(1 << 4)) | ((mode & IO_OPEN_DRAIN ? 1 : 0) << 4);
      LPC_PINCON->PINMODE0 = (LPC_PINCON->PINMODE0 & ~(3 << 8)) | (pull << 8);
      break;
    case P0_5:
      switch (func) {
        case PIO:
          LPC_PINCON->PINSEL0 = (LPC_PINCON->PINSEL0 & ~(3 << 10)) | (0 << 10);
          break;
        case I2SRX_WS:
          LPC_PINCON->PINSEL0 = (LPC_PINCON->PINSEL0 & ~(3 << 10)) | (1 << 10);
          break;
        case TD2:
          LPC_PINCON->PINSEL0 = (LPC_PINCON->PINSEL0 & ~(3 << 10)) | (2 << 10);
          break;
        case CAP2_1:
          LPC_PINCON->PINSEL0 = (LPC_PINCON->PINSEL0 & ~(3 << 10)) | (3 << 10);
          break;
        default:
          ERROR("P0_5 can only be used as I2SRX_WS, TD2, CAP2_1 or PIO.");
      }
      LPC_PINCON->PINMODE_OD0 = (LPC_PINCON->PINMODE_OD0 & ~(1 << 5)) | ((mode & IO_OPEN_DRAIN ? 1 : 0) << 5);
      LPC_PINCON->PINMODE0 = (LPC_PINCON->PINMODE0 & ~(3 << 10)) | (pull << 10);
      break;
    case P0_6:
      switch (func) {
        case PIO:
          LPC_PINCON->PINSEL0 = (LPC_PINCON->PINSEL0 & ~(3 << 12)) | (0 << 12);
          break;
        case I2SRX_SDA:
          LPC_PINCON->PINSEL0 = (LPC_PINCON->PINSEL0 & ~(3 << 12)) | (1 << 12);
          break;
        case SSEL1:
          LPC_PINCON->PINSEL0 = (LPC_PINCON->PINSEL0 & ~(3 << 12)) | (2 << 12);
          break;
        case MAT2_0:
          LPC_PINCON->PINSEL0 = (LPC_PINCON->PINSEL0 & ~(3 << 12)) | (3 << 12);
          break;
        default:
          ERROR("P0_6 can only be used as I2SRX_SDA, SSEL1, MAT2_0 or PIO.");
      }
      LPC_PINCON->PINMODE_OD0 = (LPC_PINCON->PINMODE_OD0 & ~(1 << 6)) | ((mode & IO_OPEN_DRAIN ? 1 : 0) << 6);
      LPC_PINCON->PINMODE0 = (LPC_PINCON->PINMODE0 & ~(3 << 12)) | (pull << 12);
      break;
    case P0_7:
      switch (func) {
        case PIO:
          LPC_PINCON->PINSEL0 = (LPC_PINCON->PINSEL0 & ~(3 << 14)) | (0 << 14);
          break;
        case I2STX_CLK:
          LPC_PINCON->PINSEL0 = (LPC_PINCON->PINSEL0 & ~(3 << 14)) | (1 << 14);
          break;
        case SCK1:
          LPC_PINCON->PINSEL0 = (LPC_PINCON->PINSEL0 & ~(3 << 14)) | (2 << 14);
          break;
        case MAT2_1:
          LPC_PINCON->PINSEL0 = (LPC_PINCON->PINSEL0 & ~(3 << 14)) | (3 << 14);
          break;
        default:
          ERROR("P0_7 can only be used as I2STX_CLK, SCK1, MAT2_1 or PIO.");
      }
      LPC_PINCON->PINMODE_OD0 = (LPC_PINCON->PINMODE_OD0 & ~(1 << 7)) | ((mode & IO_OPEN_DRAIN ? 1 : 0) << 7);
      LPC_PINCON->PINMODE0 = (LPC_PINCON->PINMODE0 & ~(3 << 14)) | (pull << 14);
      break;
    case P0_8:
      switch (func) {
        case PIO:
          LPC_PINCON->PINSEL0 = (LPC_PINCON->PINSEL0 & ~(3 << 16)) | (0 << 16);
          break;
        case I2STX_WS:
          LPC_PINCON->PINSEL0 = (LPC_PINCON->PINSEL0 & ~(3 << 16)) | (1 << 16);
          break;
        case MISO1:
          LPC_PINCON->PINSEL0 = (LPC_PINCON->PINSEL0 & ~(3 << 16)) | (2 << 16);
          break;
        case MAT2_2:
          LPC_PINCON->PINSEL0 = (LPC_PINCON->PINSEL0 & ~(3 << 16)) | (3 << 16);
          break;
        default:
          ERROR("P0_8 can only be used as I2STX_WS, MISO1, MAT2_2 or PIO.");
      }
      LPC_PINCON->PINMODE_OD0 = (LPC_PINCON->PINMODE_OD0 & ~(1 << 8)) | ((mode & IO_OPEN_DRAIN ? 1 : 0) << 8);
      LPC_PINCON->PINMODE0 = (LPC_PINCON->PINMODE0 & ~(3 << 16)) | (pull << 16);
      break;
    case P0_9:
      switch (func) {
        case PIO:
          LPC_PINCON->PINSEL0 = (LPC_PINCON->PINSEL0 & ~(3 << 18)) | (0 << 18);
          break;
        case I2STX_SDA:
          LPC_PINCON->PINSEL0 = (LPC_PINCON->PINSEL0 & ~(3 << 18)) | (1 << 18);
          break;
        case MOSI1:
          LPC_PINCON->PINSEL0 = (LPC_PINCON->PINSEL0 & ~(3 << 18)) | (2 << 18);
          break;
        case MAT2_3:
          LPC_PINCON->PINSEL0 = (LPC_PINCON->PINSEL0 & ~(3 << 18)) | (3 << 18);
          break;
        default:
          ERROR("P0_9 can only be used as I2STX_SDA, MOSI1, MAT2_3 or PIO.");
      }
      LPC_PINCON->PINMODE_OD0 = (LPC_PINCON->PINMODE_OD0 & ~(1 << 9)) | ((mode & IO_OPEN_DRAIN ? 1 : 0) << 9);
      LPC_PINCON->PINMODE0 = (LPC_PINCON->PINMODE0 & ~(3 << 18)) | (pull << 18);
      break;
    case P0_10:
      switch (func) {
        case PIO:
          LPC_PINCON->PINSEL0 = (LPC_PINCON->PINSEL0 & ~(3 << 20)) | (0 << 20);
          break;
        case TXD2:
          LPC_PINCON->PINSEL0 = (LPC_PINCON->PINSEL0 & ~(3 << 20)) | (1 << 20);
          break;
        case SDA2:
          LPC_PINCON->PINSEL0 = (LPC_PINCON->PINSEL0 & ~(3 << 20)) | (2 << 20);
          if (!(mode & IO_OPEN_DRAIN))
            ERROR("You must set IO_OPEN_DRAIN since pin P0_10 is not dedicated to I2C.");
          break;
        case MAT3_0:
          LPC_PINCON->PINSEL0 = (LPC_PINCON->PINSEL0 & ~(3 << 20)) | (3 << 20);
          break;
        default:
          ERROR("P0_10 can only be used as TXD2, SDA2, MAT3_0 or PIO.");
      }
      LPC_PINCON->PINMODE_OD0 = (LPC_PINCON->PINMODE_OD0 & ~(1 << 10)) | ((mode & IO_OPEN_DRAIN ? 1 : 0) << 10);
      LPC_PINCON->PINMODE0 = (LPC_PINCON->PINMODE0 & ~(3 << 20)) | (pull << 20);
      break;
    case P0_11:
      switch (func) {
        case PIO:
          LPC_PINCON->PINSEL0 = (LPC_PINCON->PINSEL0 & ~(3 << 22)) | (0 << 22);
          break;
        case RXD2:
          LPC_PINCON->PINSEL0 = (LPC_PINCON->PINSEL0 & ~(3 << 22)) | (1 << 22);
          break;
        case SCL2:
          LPC_PINCON->PINSEL0 = (LPC_PINCON->PINSEL0 & ~(3 << 22)) | (2 << 22);
          if (!(mode & IO_OPEN_DRAIN))
            ERROR("You must set IO_OPEN_DRAIN since pin P0_11 is not dedicated to I2C.");
          break;
        case MAT3_1:
          LPC_PINCON->PINSEL0 = (LPC_PINCON->PINSEL0 & ~(3 << 22)) | (3 << 22);
          break;
        default:
          ERROR("P0_11 can only be used as RXD2, SCL2, MAT3_1 or PIO.");
      }
      LPC_PINCON->PINMODE_OD0 = (LPC_PINCON->PINMODE_OD0 & ~(1 << 11)) | ((mode & IO_OPEN_DRAIN ? 1 : 0) << 11);
      LPC_PINCON->PINMODE0 = (LPC_PINCON->PINMODE0 & ~(3 << 22)) | (pull << 22);
      break;
    case P0_15:
      switch (func) {
        case PIO:
          LPC_PINCON->PINSEL0 = (LPC_PINCON->PINSEL0 & ~(3 << 30)) | (0 << 30);
          break;
        case TXD1:
          LPC_PINCON->PINSEL0 = (LPC_PINCON->PINSEL0 & ~(3 << 30)) | (1 << 30);
          break;
        case SCK0:
          LPC_PINCON->PINSEL0 = (LPC_PINCON->PINSEL0 & ~(3 << 30)) | (2 << 30);
          break;
        case SCK:
          LPC_PINCON->PINSEL0 = (LPC_PINCON->PINSEL0 & ~(3 << 30)) | (3 << 30);
          break;
        default:
          ERROR("P0_15 can only be used as TXD1, SCK0, SCK or PIO.");
      }
      LPC_PINCON->PINMODE_OD0 = (LPC_PINCON->PINMODE_OD0 & ~(1 << 15)) | ((mode & IO_OPEN_DRAIN ? 1 : 0) << 15);
      LPC_PINCON->PINMODE0 = (LPC_PINCON->PINMODE0 & ~(3 << 30)) | (pull << 30);
      break;
    case P0_16:
      switch (func) {
        case PIO:
          LPC_PINCON->PINSEL1 = (LPC_PINCON->PINSEL1 & ~(3 << 0)) | (0 << 0);
          break;
        case RXD1:
          LPC_PINCON->PINSEL1 = (LPC_PINCON->PINSEL1 & ~(3 << 0)) | (1 << 0);
          break;
        case SSEL0:
          LPC_PINCON->PINSEL1 = (LPC_PINCON->PINSEL1 & ~(3 << 0)) | (2 << 0);
          break;
        case SSEL:
          LPC_PINCON->PINSEL1 = (LPC_PINCON->PINSEL1 & ~(3 << 0)) | (3 << 0);
          break;
        default:
          ERROR("P0_16 can only be used as RXD1, SSEL0, SSEL or PIO.");
      }
      LPC_PINCON->PINMODE_OD0 = (LPC_PINCON->PINMODE_OD0 & ~(1 << 16)) | ((mode & IO_OPEN_DRAIN ? 1 : 0) << 16);
      LPC_PINCON->PINMODE1 = (LPC_PINCON->PINMODE1 & ~(3 << 0)) | (pull << 0);
      break;
    case P0_17:
      switch (func) {
        case PIO:
          LPC_PINCON->PINSEL1 = (LPC_PINCON->PINSEL1 & ~(3 << 2)) | (0 << 2);
          break;
        case CTS1:
          LPC_PINCON->PINSEL1 = (LPC_PINCON->PINSEL1 & ~(3 << 2)) | (1 << 2);
          break;
        case MISO0:
          LPC_PINCON->PINSEL1 = (LPC_PINCON->PINSEL1 & ~(3 << 2)) | (2 << 2);
          break;
        case MISO:
          LPC_PINCON->PINSEL1 = (LPC_PINCON->PINSEL1 & ~(3 << 2)) | (3 << 2);
          break;
        default:
          ERROR("P0_17 can only be used as CTS1, MISO0, MISO or PIO.");
      }
      LPC_PINCON->PINMODE_OD0 = (LPC_PINCON->PINMODE_OD0 & ~(1 << 17)) | ((mode & IO_OPEN_DRAIN ? 1 : 0) << 17);
      LPC_PINCON->PINMODE1 = (LPC_PINCON->PINMODE1 & ~(3 << 2)) | (pull << 2);
      break;
    case P0_18:
      switch (func) {
        case PIO:
          LPC_PINCON->PINSEL1 = (LPC_PINCON->PINSEL1 & ~(3 << 4)) | (0 << 4);
          break;
        case DCD1:
          LPC_PINCON->PINSEL1 = (LPC_PINCON->PINSEL1 & ~(3 << 4)) | (1 << 4);
          break;
        case MOSI0:
          LPC_PINCON->PINSEL1 = (LPC_PINCON->PINSEL1 & ~(3 << 4)) | (2 << 4);
          break;
        case MOSI:
          LPC_PINCON->PINSEL1 = (LPC_PINCON->PINSEL1 & ~(3 << 4)) | (3 << 4);
          break;
        default:
          ERROR("P0_18 can only be used as DCD1, MOSI0, MOSI or PIO.");
      }
      LPC_PINCON->PINMODE_OD0 = (LPC_PINCON->PINMODE_OD0 & ~(1 << 18)) | ((mode & IO_OPEN_DRAIN ? 1 : 0) << 18);
      LPC_PINCON->PINMODE1 = (LPC_PINCON->PINMODE1 & ~(3 << 4)) | (pull << 4);
      break;
    case P0_19:
      switch (func) {
        case PIO:
          LPC_PINCON->PINSEL1 = (LPC_PINCON->PINSEL1 & ~(3 << 6)) | (0 << 6);
          break;
        case DSR1:
          LPC_PINCON->PINSEL1 = (LPC_PINCON->PINSEL1 & ~(3 << 6)) | (1 << 6);
          break;
        case SDA1:
          LPC_PINCON->PINSEL1 = (LPC_PINCON->PINSEL1 & ~(3 << 6)) | (3 << 6);
          if (!(mode & IO_OPEN_DRAIN))
            ERROR("You must set IO_OPEN_DRAIN since pin P0_19 is not dedicated to I2C.");
          break;
        default:
          ERROR("P0_19 can only be used as DSR1, SDA1 or PIO.");
      }
      LPC_PINCON->PINMODE_OD0 = (LPC_PINCON->PINMODE_OD0 & ~(1 << 19)) | ((mode & IO_OPEN_DRAIN ? 1 : 0) << 19);
      LPC_PINCON->PINMODE1 = (LPC_PINCON->PINMODE1 & ~(3 << 6)) | (pull << 6);
      break;
    case P0_20:
      switch (func) {
        case PIO:
          LPC_PINCON->PINSEL1 = (LPC_PINCON->PINSEL1 & ~(3 << 8)) | (0 << 8);
          break;
        case DTR1:
          LPC_PINCON->PINSEL1 = (LPC_PINCON->PINSEL1 & ~(3 << 8)) | (1 << 8);
          break;
        case SCL1:
          LPC_PINCON->PINSEL1 = (LPC_PINCON->PINSEL1 & ~(3 << 8)) | (3 << 8);
          if (!(mode & IO_OPEN_DRAIN))
            ERROR("You must set IO_OPEN_DRAIN since pin P0_20 is not dedicated to I2C.");
          break;
        default:
          ERROR("P0_20 can only be used as DTR1, SCL1 or PIO.");
      }
      LPC_PINCON->PINMODE_OD0 = (LPC_PINCON->PINMODE_OD0 & ~(1 << 20)) | ((mode & IO_OPEN_DRAIN ? 1 : 0) << 20);
      LPC_PINCON->PINMODE1 = (LPC_PINCON->PINMODE1 & ~(3 << 8)) | (pull << 8);
      break;
    case P0_21:
      switch (func) {
        case PIO:
          LPC_PINCON->PINSEL1 = (LPC_PINCON->PINSEL1 & ~(3 << 10)) | (0 << 10);
          break;
        case RI1:
          LPC_PINCON->PINSEL1 = (LPC_PINCON->PINSEL1 & ~(3 << 10)) | (1 << 10);
          break;
        case RD1:
          LPC_PINCON->PINSEL1 = (LPC_PINCON->PINSEL1 & ~(3 << 10)) | (3 << 10);
          break;
        default:
          ERROR("P0_21 can only be used as RI1, RD1 or PIO.");
      }
      LPC_PINCON->PINMODE_OD0 = (LPC_PINCON->PINMODE_OD0 & ~(1 << 21)) | ((mode & IO_OPEN_DRAIN ? 1 : 0) << 21);
      LPC_PINCON->PINMODE1 = (LPC_PINCON->PINMODE1 & ~(3 << 10)) | (pull << 10);
      break;
    case P0_22:
      switch (func) {
        case PIO:
          LPC_PINCON->PINSEL1 = (LPC_PINCON->PINSEL1 & ~(3 << 12)) | (0 << 12);
          break;
        case RTS1:
          LPC_PINCON->PINSEL1 = (LPC_PINCON->PINSEL1 & ~(3 << 12)) | (1 << 12);
          break;
        case TD1:
          LPC_PINCON->PINSEL1 = (LPC_PINCON->PINSEL1 & ~(3 << 12)) | (3 << 12);
          break;
        default:
          ERROR("P0_22 can only be used as RTS1, TD1 or PIO.");
      }
      LPC_PINCON->PINMODE_OD0 = (LPC_PINCON->PINMODE_OD0 & ~(1 << 22)) | ((mode & IO_OPEN_DRAIN ? 1 : 0) << 22);
      LPC_PINCON->PINMODE1 = (LPC_PINCON->PINMODE1 & ~(3 << 12)) | (pull << 12);
      break;
    case P0_23:
      switch (func) {
        case PIO:
          LPC_PINCON->PINSEL1 = (LPC_PINCON->PINSEL1 & ~(3 << 14)) | (0 << 14);
          break;
        case AD0_0:
          LPC_PINCON->PINSEL1 = (LPC_PINCON->PINSEL1 & ~(3 << 14)) | (1 << 14);
          break;
        case I2SRX_CLK:
          LPC_PINCON->PINSEL1 = (LPC_PINCON->PINSEL1 & ~(3 << 14)) | (2 << 14);
          break;
        case CAP3_0:
          LPC_PINCON->PINSEL1 = (LPC_PINCON->PINSEL1 & ~(3 << 14)) | (3 << 14);
          break;
        default:
          ERROR("P0_23 can only be used as AD0_0, I2SRX_CLK, CAP3_0 or PIO.");
      }
      LPC_PINCON->PINMODE_OD0 = (LPC_PINCON->PINMODE_OD0 & ~(1 << 23)) | ((mode & IO_OPEN_DRAIN ? 1 : 0) << 23);
      LPC_PINCON->PINMODE1 = (LPC_PINCON->PINMODE1 & ~(3 << 14)) | (pull << 14);
      break;
    case P0_24:
      switch (func) {
        case PIO:
          LPC_PINCON->PINSEL1 = (LPC_PINCON->PINSEL1 & ~(3 << 16)) | (0 << 16);
          break;
        case AD0_1:
          LPC_PINCON->PINSEL1 = (LPC_PINCON->PINSEL1 & ~(3 << 16)) | (1 << 16);
          break;
        case I2SRX_WS:
          LPC_PINCON->PINSEL1 = (LPC_PINCON->PINSEL1 & ~(3 << 16)) | (2 << 16);
          break;
        case CAP3_1:
          LPC_PINCON->PINSEL1 = (LPC_PINCON->PINSEL1 & ~(3 << 16)) | (3 << 16);
          break;
        default:
          ERROR("P0_24 can only be used as AD0_1, I2SRX_WS, CAP3_1 or PIO.");
      }
      LPC_PINCON->PINMODE_OD0 = (LPC_PINCON->PINMODE_OD0 & ~(1 << 24)) | ((mode & IO_OPEN_DRAIN ? 1 : 0) << 24);
      LPC_PINCON->PINMODE1 = (LPC_PINCON->PINMODE1 & ~(3 << 16)) | (pull << 16);
      break;
    case P0_25:
      switch (func) {
        case PIO:
          LPC_PINCON->PINSEL1 = (LPC_PINCON->PINSEL1 & ~(3 << 18)) | (0 << 18);
          break;
        case AD0_2:
          LPC_PINCON->PINSEL1 = (LPC_PINCON->PINSEL1 & ~(3 << 18)) | (1 << 18);
          break;
        case I2SRX_SDA:
          LPC_PINCON->PINSEL1 = (LPC_PINCON->PINSEL1 & ~(3 << 18)) | (2 << 18);
          break;
        case TXD3:
          LPC_PINCON->PINSEL1 = (LPC_PINCON->PINSEL1 & ~(3 << 18)) | (3 << 18);
          break;
        default:
          ERROR("P0_25 can only be used as AD0_2, I2SRX_SDA, TXD3 or PIO.");
      }
      LPC_PINCON->PINMODE_OD0 = (LPC_PINCON->PINMODE_OD0 & ~(1 << 25)) | ((mode & IO_OPEN_DRAIN ? 1 : 0) << 25);
      LPC_PINCON->PINMODE1 = (LPC_PINCON->PINMODE1 & ~(3 << 18)) | (pull << 18);
      break;
    case P0_26:
      switch (func) {
        case PIO:
          LPC_PINCON->PINSEL1 = (LPC_PINCON->PINSEL1 & ~(3 << 20)) | (0 << 20);
          break;
        case AD0_3:
          LPC_PINCON->PINSEL1 = (LPC_PINCON->PINSEL1 & ~(3 << 20)) | (1 << 20);
          break;
        case AOUT:
          LPC_PINCON->PINSEL1 = (LPC_PINCON->PINSEL1 & ~(3 << 20)) | (2 << 20);
          break;
        case RXD3:
          LPC_PINCON->PINSEL1 = (LPC_PINCON->PINSEL1 & ~(3 << 20)) | (3 << 20);
          break;
        default:
          ERROR("P0_26 can only be used as AD0_3, AOUT, RXD3 or PIO.");
      }
      LPC_PINCON->PINMODE_OD0 = (LPC_PINCON->PINMODE_OD0 & ~(1 << 26)) | ((mode & IO_OPEN_DRAIN ? 1 : 0) << 26);
      LPC_PINCON->PINMODE1 = (LPC_PINCON->PINMODE1 & ~(3 << 20)) | (pull << 20);
      break;
    case P0_27:
      switch (func) {
        case PIO:
          LPC_PINCON->PINSEL1 = (LPC_PINCON->PINSEL1 & ~(3 << 22)) | (0 << 22);
          break;
        case SDA0:
          LPC_PINCON->PINSEL1 = (LPC_PINCON->PINSEL1 & ~(3 << 22)) | (1 << 22);
          break;
        case USB_SDA:
          LPC_PINCON->PINSEL1 = (LPC_PINCON->PINSEL1 & ~(3 << 22)) | (2 << 22);
          break;
        default:
          ERROR("P0_27 can only be used as SDA0, USB_SDA or PIO.");
      }
      if ((mode & 3) != PULL_NONE)
        ERROR("P0_27 does not have and pull-up and pull-down resistors.");
      LPC_PINCON->PINMODE_OD0 = (LPC_PINCON->PINMODE_OD0 & ~(1 << 27)) | ((mode & IO_OPEN_DRAIN ? 1 : 0) << 27);
      LPC_PINCON->PINMODE1 = (LPC_PINCON->PINMODE1 & ~(3 << 22)) | (pull << 22);
      break;
    case P0_28:
      switch (func) {
        case PIO:
          LPC_PINCON->PINSEL1 = (LPC_PINCON->PINSEL1 & ~(3 << 24)) | (0 << 24);
          break;
        case SCL0:
          LPC_PINCON->PINSEL1 = (LPC_PINCON->PINSEL1 & ~(3 << 24)) | (1 << 24);
          break;
        case USB_SCL:
          LPC_PINCON->PINSEL1 = (LPC_PINCON->PINSEL1 & ~(3 << 24)) | (2 << 24);
          break;
        default:
          ERROR("P0_28 can only be used as SCL0, USB_SCL or PIO.");
      }
      if ((mode & 3) != PULL_NONE)
        ERROR("P0_28 does not have and pull-up and pull-down resistors.");
      LPC_PINCON->PINMODE_OD0 = (LPC_PINCON->PINMODE_OD0 & ~(1 << 28)) | ((mode & IO_OPEN_DRAIN ? 1 : 0) << 28);
      LPC_PINCON->PINMODE1 = (LPC_PINCON->PINMODE1 & ~(3 << 24)) | (pull << 24);
      break;
    case P0_29:
      switch (func) {
        case PIO:
          LPC_PINCON->PINSEL1 = (LPC_PINCON->PINSEL1 & ~(3 << 26)) | (0 << 26);
          break;
        case USB_Dp:
          LPC_PINCON->PINSEL1 = (LPC_PINCON->PINSEL1 & ~(3 << 26)) | (1 << 26);
          break;
        default:
          ERROR("P0_29 can only be used as USB_Dp or PIO.");
      }
      if ((mode & 3) != PULL_NONE)
        ERROR("P0_29 does not have and pull-up and pull-down resistors.");
      LPC_PINCON->PINMODE_OD0 = (LPC_PINCON->PINMODE_OD0 & ~(1 << 29)) | ((mode & IO_OPEN_DRAIN ? 1 : 0) << 29);
      LPC_PINCON->PINMODE1 = (LPC_PINCON->PINMODE1 & ~(3 << 26)) | (pull << 26);
      break;
    case P0_30:
      switch (func) {
        case PIO:
          LPC_PINCON->PINSEL1 = (LPC_PINCON->PINSEL1 & ~(3 << 28)) | (0 << 28);
          break;
        case USB_Dm:
          LPC_PINCON->PINSEL1 = (LPC_PINCON->PINSEL1 & ~(3 << 28)) | (1 << 28);
          break;
        default:
          ERROR("P0_30 can only be used as USB_Dm or PIO.");
      }
      if ((mode & 3) != PULL_NONE)
        ERROR("P0_30 does not have and pull-up and pull-down resistors.");
      LPC_PINCON->PINMODE_OD0 = (LPC_PINCON->PINMODE_OD0 & ~(1 << 30)) | ((mode & IO_OPEN_DRAIN ? 1 : 0) << 30);
      LPC_PINCON->PINMODE1 = (LPC_PINCON->PINMODE1 & ~(3 << 28)) | (pull << 28);
      break;
    case P1_0:
      switch (func) {
        case PIO:
          LPC_PINCON->PINSEL2 = (LPC_PINCON->PINSEL2 & ~(3 << 0)) | (0 << 0);
          break;
        case ENET_TXD0:
          LPC_PINCON->PINSEL2 = (LPC_PINCON->PINSEL2 & ~(3 << 0)) | (1 << 0);
          break;
        default:
          ERROR("P1_0 can only be used as ENET_TXD0 or PIO.");
      }
      LPC_PINCON->PINMODE_OD1 = (LPC_PINCON->PINMODE_OD1 & ~(1 << 0)) | ((mode & IO_OPEN_DRAIN ? 1 : 0) << 0);
      LPC_PINCON->PINMODE2 = (LPC_PINCON->PINMODE2 & ~(3 << 0)) | (pull << 0);
      break;
    case P1_1:
      switch (func) {
        case PIO:
          LPC_PINCON->PINSEL2 = (LPC_PINCON->PINSEL2 & ~(3 << 2)) | (0 << 2);
          break;
        case ENET_TXD1:
          LPC_PINCON->PINSEL2 = (LPC_PINCON->PINSEL2 & ~(3 << 2)) | (1 << 2);
          break;
        default:
          ERROR("P1_1 can only be used as ENET_TXD1 or PIO.");
      }
      LPC_PINCON->PINMODE_OD1 = (LPC_PINCON->PINMODE_OD1 & ~(1 << 1)) | ((mode & IO_OPEN_DRAIN ? 1 : 0) << 1);
      LPC_PINCON->PINMODE2 = (LPC_PINCON->PINMODE2 & ~(3 << 2)) | (pull << 2);
      break;
    case P1_4:
      switch (func) {
        case PIO:
          LPC_PINCON->PINSEL2 = (LPC_PINCON->PINSEL2 & ~(3 << 8)) | (0 << 8);
          break;
        case ENET_TX_EN:
          LPC_PINCON->PINSEL2 = (LPC_PINCON->PINSEL2 & ~(3 << 8)) | (1 << 8);
          break;
        default:
          ERROR("P1_4 can only be used as ENET_TX_EN or PIO.");
      }
      LPC_PINCON->PINMODE_OD1 = (LPC_PINCON->PINMODE_OD1 & ~(1 << 4)) | ((mode & IO_OPEN_DRAIN ? 1 : 0) << 4);
      LPC_PINCON->PINMODE2 = (LPC_PINCON->PINMODE2 & ~(3 << 8)) | (pull << 8);
      break;
    case P1_8:
      switch (func) {
        case PIO:
          LPC_PINCON->PINSEL2 = (LPC_PINCON->PINSEL2 & ~(3 << 16)) | (0 << 16);
          break;
        case ENET_CRS:
          LPC_PINCON->PINSEL2 = (LPC_PINCON->PINSEL2 & ~(3 << 16)) | (1 << 16);
          break;
        default:
          ERROR("P1_8 can only be used as ENET_CRS or PIO.");
      }
      LPC_PINCON->PINMODE_OD1 = (LPC_PINCON->PINMODE_OD1 & ~(1 << 8)) | ((mode & IO_OPEN_DRAIN ? 1 : 0) << 8);
      LPC_PINCON->PINMODE2 = (LPC_PINCON->PINMODE2 & ~(3 << 16)) | (pull << 16);
      break;
    case P1_9:
      switch (func) {
        case PIO:
          LPC_PINCON->PINSEL2 = (LPC_PINCON->PINSEL2 & ~(3 << 18)) | (0 << 18);
          break;
        case ENET_RXD0:
          LPC_PINCON->PINSEL2 = (LPC_PINCON->PINSEL2 & ~(3 << 18)) | (1 << 18);
          break;
        default:
          ERROR("P1_9 can only be used as ENET_RXD0 or PIO.");
      }
      LPC_PINCON->PINMODE_OD1 = (LPC_PINCON->PINMODE_OD1 & ~(1 << 9)) | ((mode & IO_OPEN_DRAIN ? 1 : 0) << 9);
      LPC_PINCON->PINMODE2 = (LPC_PINCON->PINMODE2 & ~(3 << 18)) | (pull << 18);
      break;
    case P1_10:
      switch (func) {
        case PIO:
          LPC_PINCON->PINSEL2 = (LPC_PINCON->PINSEL2 & ~(3 << 20)) | (0 << 20);
          break;
        case ENET_RXD1:
          LPC_PINCON->PINSEL2 = (LPC_PINCON->PINSEL2 & ~(3 << 20)) | (1 << 20);
          break;
        default:
          ERROR("P1_10 can only be used as ENET_RXD1 or PIO.");
      }
      LPC_PINCON->PINMODE_OD1 = (LPC_PINCON->PINMODE_OD1 & ~(1 << 10)) | ((mode & IO_OPEN_DRAIN ? 1 : 0) << 10);
      LPC_PINCON->PINMODE2 = (LPC_PINCON->PINMODE2 & ~(3 << 20)) | (pull << 20);
      break;
    case P1_14:
      switch (func) {
        case PIO:
          LPC_PINCON->PINSEL2 = (LPC_PINCON->PINSEL2 & ~(3 << 28)) | (0 << 28);
          break;
        case ENET_RX_ER:
          LPC_PINCON->PINSEL2 = (LPC_PINCON->PINSEL2 & ~(3 << 28)) | (1 << 28);
          break;
        default:
          ERROR("P1_14 can only be used as ENET_RX_ER or PIO.");
      }
      LPC_PINCON->PINMODE_OD1 = (LPC_PINCON->PINMODE_OD1 & ~(1 << 14)) | ((mode & IO_OPEN_DRAIN ? 1 : 0) << 14);
      LPC_PINCON->PINMODE2 = (LPC_PINCON->PINMODE2 & ~(3 << 28)) | (pull << 28);
      break;
    case P1_15:
      switch (func) {
        case PIO:
          LPC_PINCON->PINSEL2 = (LPC_PINCON->PINSEL2 & ~(3 << 30)) | (0 << 30);
          break;
        case ENET_REF_CLK:
          LPC_PINCON->PINSEL2 = (LPC_PINCON->PINSEL2 & ~(3 << 30)) | (1 << 30);
          break;
        default:
          ERROR("P1_15 can only be used as ENET_REF_CLK or PIO.");
      }
      LPC_PINCON->PINMODE_OD1 = (LPC_PINCON->PINMODE_OD1 & ~(1 << 15)) | ((mode & IO_OPEN_DRAIN ? 1 : 0) << 15);
      LPC_PINCON->PINMODE2 = (LPC_PINCON->PINMODE2 & ~(3 << 30)) | (pull << 30);
      break;
    case P1_16:
      switch (func) {
        case PIO:
          LPC_PINCON->PINSEL3 = (LPC_PINCON->PINSEL3 & ~(3 << 0)) | (0 << 0);
          break;
        case ENET_MDC:
          LPC_PINCON->PINSEL3 = (LPC_PINCON->PINSEL3 & ~(3 << 0)) | (1 << 0);
          break;
        default:
          ERROR("P1_16 can only be used as ENET_MDC or PIO.");
      }
      LPC_PINCON->PINMODE_OD1 = (LPC_PINCON->PINMODE_OD1 & ~(1 << 16)) | ((mode & IO_OPEN_DRAIN ? 1 : 0) << 16);
      LPC_PINCON->PINMODE3 = (LPC_PINCON->PINMODE3 & ~(3 << 0)) | (pull << 0);
      break;
    case P1_17:
      switch (func) {
        case PIO:
          LPC_PINCON->PINSEL3 = (LPC_PINCON->PINSEL3 & ~(3 << 2)) | (0 << 2);
          break;
        case ENET_MDIO:
          LPC_PINCON->PINSEL3 = (LPC_PINCON->PINSEL3 & ~(3 << 2)) | (1 << 2);
          break;
        default:
          ERROR("P1_17 can only be used as ENET_MDIO or PIO.");
      }
      LPC_PINCON->PINMODE_OD1 = (LPC_PINCON->PINMODE_OD1 & ~(1 << 17)) | ((mode & IO_OPEN_DRAIN ? 1 : 0) << 17);
      LPC_PINCON->PINMODE3 = (LPC_PINCON->PINMODE3 & ~(3 << 2)) | (pull << 2);
      break;
    case P1_18:
      switch (func) {
        case PIO:
          LPC_PINCON->PINSEL3 = (LPC_PINCON->PINSEL3 & ~(3 << 4)) | (0 << 4);
          break;
        case USB_UP_LED:
          LPC_PINCON->PINSEL3 = (LPC_PINCON->PINSEL3 & ~(3 << 4)) | (1 << 4);
          break;
        case PWM1_1:
          LPC_PINCON->PINSEL3 = (LPC_PINCON->PINSEL3 & ~(3 << 4)) | (2 << 4);
          break;
        case CAP1_0:
          LPC_PINCON->PINSEL3 = (LPC_PINCON->PINSEL3 & ~(3 << 4)) | (3 << 4);
          break;
        default:
          ERROR("P1_18 can only be used as USB_UP_LED, PWM1_1, CAP1_0 or PIO.");
      }
      LPC_PINCON->PINMODE_OD1 = (LPC_PINCON->PINMODE_OD1 & ~(1 << 18)) | ((mode & IO_OPEN_DRAIN ? 1 : 0) << 18);
      LPC_PINCON->PINMODE3 = (LPC_PINCON->PINMODE3 & ~(3 << 4)) | (pull << 4);
      break;
    case P1_19:
      switch (func) {
        case PIO:
          LPC_PINCON->PINSEL3 = (LPC_PINCON->PINSEL3 & ~(3 << 6)) | (0 << 6);
          break;
        case MCOA0:
          LPC_PINCON->PINSEL3 = (LPC_PINCON->PINSEL3 & ~(3 << 6)) | (1 << 6);
          break;
        case nUSB_PPWR:
          LPC_PINCON->PINSEL3 = (LPC_PINCON->PINSEL3 & ~(3 << 6)) | (2 << 6);
          break;
        case CAP1_1:
          LPC_PINCON->PINSEL3 = (LPC_PINCON->PINSEL3 & ~(3 << 6)) | (3 << 6);
          break;
        default:
          ERROR("P1_19 can only be used as MCOA0, nUSB_PPWR, CAP1_1 or PIO.");
      }
      LPC_PINCON->PINMODE_OD1 = (LPC_PINCON->PINMODE_OD1 & ~(1 << 19)) | ((mode & IO_OPEN_DRAIN ? 1 : 0) << 19);
      LPC_PINCON->PINMODE3 = (LPC_PINCON->PINMODE3 & ~(3 << 6)) | (pull << 6);
      break;
    case P1_20:
      switch (func) {
        case PIO:
          LPC_PINCON->PINSEL3 = (LPC_PINCON->PINSEL3 & ~(3 << 8)) | (0 << 8);
          break;
        case MCI0:
          LPC_PINCON->PINSEL3 = (LPC_PINCON->PINSEL3 & ~(3 << 8)) | (1 << 8);
          break;
        case PWM1_2:
          LPC_PINCON->PINSEL3 = (LPC_PINCON->PINSEL3 & ~(3 << 8)) | (2 << 8);
          break;
        case SCK0:
          LPC_PINCON->PINSEL3 = (LPC_PINCON->PINSEL3 & ~(3 << 8)) | (3 << 8);
          break;
        default:
          ERROR("P1_20 can only be used as MCI0, PWM1_2, SCK0 or PIO.");
      }
      LPC_PINCON->PINMODE_OD1 = (LPC_PINCON->PINMODE_OD1 & ~(1 << 20)) | ((mode & IO_OPEN_DRAIN ? 1 : 0) << 20);
      LPC_PINCON->PINMODE3 = (LPC_PINCON->PINMODE3 & ~(3 << 8)) | (pull << 8);
      break;
    case P1_21:
      switch (func) {
        case PIO:
          LPC_PINCON->PINSEL3 = (LPC_PINCON->PINSEL3 & ~(3 << 10)) | (0 << 10);
          break;
        case nMCABORT:
          LPC_PINCON->PINSEL3 = (LPC_PINCON->PINSEL3 & ~(3 << 10)) | (1 << 10);
          break;
        case PWM1_3:
          LPC_PINCON->PINSEL3 = (LPC_PINCON->PINSEL3 & ~(3 << 10)) | (2 << 10);
          break;
        case SSEL0:
          LPC_PINCON->PINSEL3 = (LPC_PINCON->PINSEL3 & ~(3 << 10)) | (3 << 10);
          break;
        default:
          ERROR("P1_21 can only be used as nMCABORT, PWM1_3, SSEL0 or PIO.");
      }
      LPC_PINCON->PINMODE_OD1 = (LPC_PINCON->PINMODE_OD1 & ~(1 << 21)) | ((mode & IO_OPEN_DRAIN ? 1 : 0) << 21);
      LPC_PINCON->PINMODE3 = (LPC_PINCON->PINMODE3 & ~(3 << 10)) | (pull << 10);
      break;
    case P1_22:
      switch (func) {
        case PIO:
          LPC_PINCON->PINSEL3 = (LPC_PINCON->PINSEL3 & ~(3 << 12)) | (0 << 12);
          break;
        case MCOB0:
          LPC_PINCON->PINSEL3 = (LPC_PINCON->PINSEL3 & ~(3 << 12)) | (1 << 12);
          break;
        case USB_PWRD:
          LPC_PINCON->PINSEL3 = (LPC_PINCON->PINSEL3 & ~(3 << 12)) | (2 << 12);
          break;
        case MAT1_0:
          LPC_PINCON->PINSEL3 = (LPC_PINCON->PINSEL3 & ~(3 << 12)) | (3 << 12);
          break;
        default:
          ERROR("P1_22 can only be used as MCOB0, USB_PWRD, MAT1_0 or PIO.");
      }
      LPC_PINCON->PINMODE_OD1 = (LPC_PINCON->PINMODE_OD1 & ~(1 << 22)) | ((mode & IO_OPEN_DRAIN ? 1 : 0) << 22);
      LPC_PINCON->PINMODE3 = (LPC_PINCON->PINMODE3 & ~(3 << 12)) | (pull << 12);
      break;
    case P1_23:
      switch (func) {
        case PIO:
          LPC_PINCON->PINSEL3 = (LPC_PINCON->PINSEL3 & ~(3 << 14)) | (0 << 14);
          break;
        case MCI1:
          LPC_PINCON->PINSEL3 = (LPC_PINCON->PINSEL3 & ~(3 << 14)) | (1 << 14);
          break;
        case PWM1_4:
          LPC_PINCON->PINSEL3 = (LPC_PINCON->PINSEL3 & ~(3 << 14)) | (2 << 14);
          break;
        case MISO0:
          LPC_PINCON->PINSEL3 = (LPC_PINCON->PINSEL3 & ~(3 << 14)) | (3 << 14);
          break;
        default:
          ERROR("P1_23 can only be used as MCI1, PWM1_4, MISO0 or PIO.");
      }
      LPC_PINCON->PINMODE_OD1 = (LPC_PINCON->PINMODE_OD1 & ~(1 << 23)) | ((mode & IO_OPEN_DRAIN ? 1 : 0) << 23);
      LPC_PINCON->PINMODE3 = (LPC_PINCON->PINMODE3 & ~(3 << 14)) | (pull << 14);
      break;
    case P1_24:
      switch (func) {
        case PIO:
          LPC_PINCON->PINSEL3 = (LPC_PINCON->PINSEL3 & ~(3 << 16)) | (0 << 16);
          break;
        case MCI2:
          LPC_PINCON->PINSEL3 = (LPC_PINCON->PINSEL3 & ~(3 << 16)) | (1 << 16);
          break;
        case PWM1_5:
          LPC_PINCON->PINSEL3 = (LPC_PINCON->PINSEL3 & ~(3 << 16)) | (2 << 16);
          break;
        case MOSI0:
          LPC_PINCON->PINSEL3 = (LPC_PINCON->PINSEL3 & ~(3 << 16)) | (3 << 16);
          break;
        default:
          ERROR("P1_24 can only be used as MCI2, PWM1_5, MOSI0 or PIO.");
      }
      LPC_PINCON->PINMODE_OD1 = (LPC_PINCON->PINMODE_OD1 & ~(1 << 24)) | ((mode & IO_OPEN_DRAIN ? 1 : 0) << 24);
      LPC_PINCON->PINMODE3 = (LPC_PINCON->PINMODE3 & ~(3 << 16)) | (pull << 16);
      break;
    case P1_25:
      switch (func) {
        case PIO:
          LPC_PINCON->PINSEL3 = (LPC_PINCON->PINSEL3 & ~(3 << 18)) | (0 << 18);
          break;
        case MCOA1:
          LPC_PINCON->PINSEL3 = (LPC_PINCON->PINSEL3 & ~(3 << 18)) | (1 << 18);
          break;
        case MAT1_1:
          LPC_PINCON->PINSEL3 = (LPC_PINCON->PINSEL3 & ~(3 << 18)) | (3 << 18);
          break;
        default:
          ERROR("P1_25 can only be used as MCOA1, MAT1_1 or PIO.");
      }
      LPC_PINCON->PINMODE_OD1 = (LPC_PINCON->PINMODE_OD1 & ~(1 << 25)) | ((mode & IO_OPEN_DRAIN ? 1 : 0) << 25);
      LPC_PINCON->PINMODE3 = (LPC_PINCON->PINMODE3 & ~(3 << 18)) | (pull << 18);
      break;
    case P1_26:
      switch (func) {
        case PIO:
          LPC_PINCON->PINSEL3 = (LPC_PINCON->PINSEL3 & ~(3 << 20)) | (0 << 20);
          break;
        case MCOB1:
          LPC_PINCON->PINSEL3 = (LPC_PINCON->PINSEL3 & ~(3 << 20)) | (1 << 20);
          break;
        case PWM1_6:
          LPC_PINCON->PINSEL3 = (LPC_PINCON->PINSEL3 & ~(3 << 20)) | (2 << 20);
          break;
        case CAP0_0:
          LPC_PINCON->PINSEL3 = (LPC_PINCON->PINSEL3 & ~(3 << 20)) | (3 << 20);
          break;
        default:
          ERROR("P1_26 can only be used as MCOB1, PWM1_6, CAP0_0 or PIO.");
      }
      LPC_PINCON->PINMODE_OD1 = (LPC_PINCON->PINMODE_OD1 & ~(1 << 26)) | ((mode & IO_OPEN_DRAIN ? 1 : 0) << 26);
      LPC_PINCON->PINMODE3 = (LPC_PINCON->PINMODE3 & ~(3 << 20)) | (pull << 20);
      break;
    case P1_27:
      switch (func) {
        case PIO:
          LPC_PINCON->PINSEL3 = (LPC_PINCON->PINSEL3 & ~(3 << 22)) | (0 << 22);
          break;
        case CLKOUT:
          LPC_PINCON->PINSEL3 = (LPC_PINCON->PINSEL3 & ~(3 << 22)) | (1 << 22);
          break;
        case nUSB_OVRCR:
          LPC_PINCON->PINSEL3 = (LPC_PINCON->PINSEL3 & ~(3 << 22)) | (2 << 22);
          break;
        case CAP0_1:
          LPC_PINCON->PINSEL3 = (LPC_PINCON->PINSEL3 & ~(3 << 22)) | (3 << 22);
          break;
        default:
          ERROR("P1_27 can only be used as CLKOUT, nUSB_OVRCR, CAP0_1 or PIO.");
      }
      LPC_PINCON->PINMODE_OD1 = (LPC_PINCON->PINMODE_OD1 & ~(1 << 27)) | ((mode & IO_OPEN_DRAIN ? 1 : 0) << 27);
      LPC_PINCON->PINMODE3 = (LPC_PINCON->PINMODE3 & ~(3 << 22)) | (pull << 22);
      break;
    case P1_28:
      switch (func) {
        case PIO:
          LPC_PINCON->PINSEL3 = (LPC_PINCON->PINSEL3 & ~(3 << 24)) | (0 << 24);
          break;
        case MCOA2:
          LPC_PINCON->PINSEL3 = (LPC_PINCON->PINSEL3 & ~(3 << 24)) | (1 << 24);
          break;
        case PCAP1_0:
          LPC_PINCON->PINSEL3 = (LPC_PINCON->PINSEL3 & ~(3 << 24)) | (2 << 24);
          break;
        case MAT0_0:
          LPC_PINCON->PINSEL3 = (LPC_PINCON->PINSEL3 & ~(3 << 24)) | (3 << 24);
          break;
        default:
          ERROR("P1_28 can only be used as MCOA2, PCAP1_0, MAT0_0 or PIO.");
      }
      LPC_PINCON->PINMODE_OD1 = (LPC_PINCON->PINMODE_OD1 & ~(1 << 28)) | ((mode & IO_OPEN_DRAIN ? 1 : 0) << 28);
      LPC_PINCON->PINMODE3 = (LPC_PINCON->PINMODE3 & ~(3 << 24)) | (pull << 24);
      break;
    case P1_29:
      switch (func) {
        case PIO:
          LPC_PINCON->PINSEL3 = (LPC_PINCON->PINSEL3 & ~(3 << 26)) | (0 << 26);
          break;
        case MCOB2:
          LPC_PINCON->PINSEL3 = (LPC_PINCON->PINSEL3 & ~(3 << 26)) | (1 << 26);
          break;
        case PCAP1_1:
          LPC_PINCON->PINSEL3 = (LPC_PINCON->PINSEL3 & ~(3 << 26)) | (2 << 26);
          break;
        case MAT0_1:
          LPC_PINCON->PINSEL3 = (LPC_PINCON->PINSEL3 & ~(3 << 26)) | (3 << 26);
          break;
        default:
          ERROR("P1_29 can only be used as MCOB2, PCAP1_1, MAT0_1 or PIO.");
      }
      LPC_PINCON->PINMODE_OD1 = (LPC_PINCON->PINMODE_OD1 & ~(1 << 29)) | ((mode & IO_OPEN_DRAIN ? 1 : 0) << 29);
      LPC_PINCON->PINMODE3 = (LPC_PINCON->PINMODE3 & ~(3 << 26)) | (pull << 26);
      break;
    case P1_30:
      switch (func) {
        case PIO:
          LPC_PINCON->PINSEL3 = (LPC_PINCON->PINSEL3 & ~(3 << 28)) | (0 << 28);
          break;
        case VBUS:
          LPC_PINCON->PINSEL3 = (LPC_PINCON->PINSEL3 & ~(3 << 28)) | (2 << 28);
          break;
        case AD0_4:
          LPC_PINCON->PINSEL3 = (LPC_PINCON->PINSEL3 & ~(3 << 28)) | (3 << 28);
          break;
        default:
          ERROR("P1_30 can only be used as VBUS, AD0_4 or PIO.");
      }
      LPC_PINCON->PINMODE_OD1 = (LPC_PINCON->PINMODE_OD1 & ~(1 << 30)) | ((mode & IO_OPEN_DRAIN ? 1 : 0) << 30);
      LPC_PINCON->PINMODE3 = (LPC_PINCON->PINMODE3 & ~(3 << 28)) | (pull << 28);
      break;
    case P1_31:
      switch (func) {
        case PIO:
          LPC_PINCON->PINSEL3 = (LPC_PINCON->PINSEL3 & ~(3 << 30)) | (0 << 30);
          break;
        case SCK1:
          LPC_PINCON->PINSEL3 = (LPC_PINCON->PINSEL3 & ~(3 << 30)) | (2 << 30);
          break;
        case AD0_5:
          LPC_PINCON->PINSEL3 = (LPC_PINCON->PINSEL3 & ~(3 << 30)) | (3 << 30);
          break;
        default:
          ERROR("P1_31 can only be used as SCK1, AD0_5 or PIO.");
      }
      LPC_PINCON->PINMODE_OD1 = (LPC_PINCON->PINMODE_OD1 & ~(1 << 31)) | ((mode & IO_OPEN_DRAIN ? 1 : 0) << 31);
      LPC_PINCON->PINMODE3 = (LPC_PINCON->PINMODE3 & ~(3 << 30)) | (pull << 30);
      break;
    case P2_0:
      switch (func) {
        case PIO:
          LPC_PINCON->PINSEL4 = (LPC_PINCON->PINSEL4 & ~(3 << 0)) | (0 << 0);
          break;
        case PWM1_1:
          LPC_PINCON->PINSEL4 = (LPC_PINCON->PINSEL4 & ~(3 << 0)) | (1 << 0);
          break;
        case TXD1:
          LPC_PINCON->PINSEL4 = (LPC_PINCON->PINSEL4 & ~(3 << 0)) | (2 << 0);
          break;
        default:
          ERROR("P2_0 can only be used as PWM1_1, TXD1 or PIO.");
      }
      LPC_PINCON->PINMODE_OD2 = (LPC_PINCON->PINMODE_OD2 & ~(1 << 0)) | ((mode & IO_OPEN_DRAIN ? 1 : 0) << 0);
      LPC_PINCON->PINMODE4 = (LPC_PINCON->PINMODE4 & ~(3 << 0)) | (pull << 0);
      break;
    case P2_1:
      switch (func) {
        case PIO:
          LPC_PINCON->PINSEL4 = (LPC_PINCON->PINSEL4 & ~(3 << 2)) | (0 << 2);
          break;
        case PWM1_2:
          LPC_PINCON->PINSEL4 = (LPC_PINCON->PINSEL4 & ~(3 << 2)) | (1 << 2);
          break;
        case RXD1:
          LPC_PINCON->PINSEL4 = (LPC_PINCON->PINSEL4 & ~(3 << 2)) | (2 << 2);
          break;
        default:
          ERROR("P2_1 can only be used as PWM1_2, RXD1 or PIO.");
      }
      LPC_PINCON->PINMODE_OD2 = (LPC_PINCON->PINMODE_OD2 & ~(1 << 1)) | ((mode & IO_OPEN_DRAIN ? 1 : 0) << 1);
      LPC_PINCON->PINMODE4 = (LPC_PINCON->PINMODE4 & ~(3 << 2)) | (pull << 2);
      break;
    case P2_2:
      switch (func) {
        case PIO:
          LPC_PINCON->PINSEL4 = (LPC_PINCON->PINSEL4 & ~(3 << 4)) | (0 << 4);
          break;
        case PWM1_3:
          LPC_PINCON->PINSEL4 = (LPC_PINCON->PINSEL4 & ~(3 << 4)) | (1 << 4);
          break;
        case CTS1:
          LPC_PINCON->PINSEL4 = (LPC_PINCON->PINSEL4 & ~(3 << 4)) | (2 << 4);
          break;
        case TRACEDATA_3:
          LPC_PINCON->PINSEL4 = (LPC_PINCON->PINSEL4 & ~(3 << 4)) | (3 << 4);
          break;
        default:
          ERROR("P2_2 can only be used as PWM1_3, CTS1, TRACEDATA_3 or PIO.");
      }
      LPC_PINCON->PINMODE_OD2 = (LPC_PINCON->PINMODE_OD2 & ~(1 << 2)) | ((mode & IO_OPEN_DRAIN ? 1 : 0) << 2);
      LPC_PINCON->PINMODE4 = (LPC_PINCON->PINMODE4 & ~(3 << 4)) | (pull << 4);
      break;
    case P2_3:
      switch (func) {
        case PIO:
          LPC_PINCON->PINSEL4 = (LPC_PINCON->PINSEL4 & ~(3 << 6)) | (0 << 6);
          break;
        case PWM1_4:
          LPC_PINCON->PINSEL4 = (LPC_PINCON->PINSEL4 & ~(3 << 6)) | (1 << 6);
          break;
        case DCD1:
          LPC_PINCON->PINSEL4 = (LPC_PINCON->PINSEL4 & ~(3 << 6)) | (2 << 6);
          break;
        case TRACEDATA_2:
          LPC_PINCON->PINSEL4 = (LPC_PINCON->PINSEL4 & ~(3 << 6)) | (3 << 6);
          break;
        default:
          ERROR("P2_3 can only be used as PWM1_4, DCD1, TRACEDATA_2 or PIO.");
      }
      LPC_PINCON->PINMODE_OD2 = (LPC_PINCON->PINMODE_OD2 & ~(1 << 3)) | ((mode & IO_OPEN_DRAIN ? 1 : 0) << 3);
      LPC_PINCON->PINMODE4 = (LPC_PINCON->PINMODE4 & ~(3 << 6)) | (pull << 6);
      break;
    case P2_4:
      switch (func) {
        case PIO:
          LPC_PINCON->PINSEL4 = (LPC_PINCON->PINSEL4 & ~(3 << 8)) | (0 << 8);
          break;
        case PWM1_5:
          LPC_PINCON->PINSEL4 = (LPC_PINCON->PINSEL4 & ~(3 << 8)) | (1 << 8);
          break;
        case DSR1:
          LPC_PINCON->PINSEL4 = (LPC_PINCON->PINSEL4 & ~(3 << 8)) | (2 << 8);
          break;
        case TRACEDATA_1:
          LPC_PINCON->PINSEL4 = (LPC_PINCON->PINSEL4 & ~(3 << 8)) | (3 << 8);
          break;
        default:
          ERROR("P2_4 can only be used as PWM1_5, DSR1, TRACEDATA_1 or PIO.");
      }
      LPC_PINCON->PINMODE_OD2 = (LPC_PINCON->PINMODE_OD2 & ~(1 << 4)) | ((mode & IO_OPEN_DRAIN ? 1 : 0) << 4);
      LPC_PINCON->PINMODE4 = (LPC_PINCON->PINMODE4 & ~(3 << 8)) | (pull << 8);
      break;
    case P2_5:
      switch (func) {
        case PIO:
          LPC_PINCON->PINSEL4 = (LPC_PINCON->PINSEL4 & ~(3 << 10)) | (0 << 10);
          break;
        case PWM1_6:
          LPC_PINCON->PINSEL4 = (LPC_PINCON->PINSEL4 & ~(3 << 10)) | (1 << 10);
          break;
        case DTR1:
          LPC_PINCON->PINSEL4 = (LPC_PINCON->PINSEL4 & ~(3 << 10)) | (2 << 10);
          break;
        case TRACEDATA_0:
          LPC_PINCON->PINSEL4 = (LPC_PINCON->PINSEL4 & ~(3 << 10)) | (3 << 10);
          break;
        default:
          ERROR("P2_5 can only be used as PWM1_6, DTR1, TRACEDATA_0 or PIO.");
      }
      LPC_PINCON->PINMODE_OD2 = (LPC_PINCON->PINMODE_OD2 & ~(1 << 5)) | ((mode & IO_OPEN_DRAIN ? 1 : 0) << 5);
      LPC_PINCON->PINMODE4 = (LPC_PINCON->PINMODE4 & ~(3 << 10)) | (pull << 10);
      break;
    case P2_6:
      switch (func) {
        case PIO:
          LPC_PINCON->PINSEL4 = (LPC_PINCON->PINSEL4 & ~(3 << 12)) | (0 << 12);
          break;
        case PCAP1_0:
          LPC_PINCON->PINSEL4 = (LPC_PINCON->PINSEL4 & ~(3 << 12)) | (1 << 12);
          break;
        case RI1:
          LPC_PINCON->PINSEL4 = (LPC_PINCON->PINSEL4 & ~(3 << 12)) | (2 << 12);
          break;
        case TRACECLK:
          LPC_PINCON->PINSEL4 = (LPC_PINCON->PINSEL4 & ~(3 << 12)) | (3 << 12);
          break;
        default:
          ERROR("P2_6 can only be used as PCAP1_0, RI1, TRACECLK or PIO.");
      }
      LPC_PINCON->PINMODE_OD2 = (LPC_PINCON->PINMODE_OD2 & ~(1 << 6)) | ((mode & IO_OPEN_DRAIN ? 1 : 0) << 6);
      LPC_PINCON->PINMODE4 = (LPC_PINCON->PINMODE4 & ~(3 << 12)) | (pull << 12);
      break;
    case P2_7:
      switch (func) {
        case PIO:
          LPC_PINCON->PINSEL4 = (LPC_PINCON->PINSEL4 & ~(3 << 14)) | (0 << 14);
          break;
        case RD2:
          LPC_PINCON->PINSEL4 = (LPC_PINCON->PINSEL4 & ~(3 << 14)) | (1 << 14);
          break;
        case RTS1:
          LPC_PINCON->PINSEL4 = (LPC_PINCON->PINSEL4 & ~(3 << 14)) | (2 << 14);
          break;
        default:
          ERROR("P2_7 can only be used as RD2, RTS1 or PIO.");
      }
      LPC_PINCON->PINMODE_OD2 = (LPC_PINCON->PINMODE_OD2 & ~(1 << 7)) | ((mode & IO_OPEN_DRAIN ? 1 : 0) << 7);
      LPC_PINCON->PINMODE4 = (LPC_PINCON->PINMODE4 & ~(3 << 14)) | (pull << 14);
      break;
    case P2_8:
      switch (func) {
        case PIO:
          LPC_PINCON->PINSEL4 = (LPC_PINCON->PINSEL4 & ~(3 << 16)) | (0 << 16);
          break;
        case TD2:
          LPC_PINCON->PINSEL4 = (LPC_PINCON->PINSEL4 & ~(3 << 16)) | (1 << 16);
          break;
        case TXD2:
          LPC_PINCON->PINSEL4 = (LPC_PINCON->PINSEL4 & ~(3 << 16)) | (2 << 16);
          break;
        case ENET_MDC:
          LPC_PINCON->PINSEL4 = (LPC_PINCON->PINSEL4 & ~(3 << 16)) | (3 << 16);
          break;
        default:
          ERROR("P2_8 can only be used as TD2, TXD2, ENET_MDC or PIO.");
      }
      LPC_PINCON->PINMODE_OD2 = (LPC_PINCON->PINMODE_OD2 & ~(1 << 8)) | ((mode & IO_OPEN_DRAIN ? 1 : 0) << 8);
      LPC_PINCON->PINMODE4 = (LPC_PINCON->PINMODE4 & ~(3 << 16)) | (pull << 16);
      break;
    case P2_9:
      switch (func) {
        case PIO:
          LPC_PINCON->PINSEL4 = (LPC_PINCON->PINSEL4 & ~(3 << 18)) | (0 << 18);
          break;
        case USB_CONNECT:
          LPC_PINCON->PINSEL4 = (LPC_PINCON->PINSEL4 & ~(3 << 18)) | (1 << 18);
          break;
        case RXD2:
          LPC_PINCON->PINSEL4 = (LPC_PINCON->PINSEL4 & ~(3 << 18)) | (2 << 18);
          break;
        case ENET_MDIO:
          LPC_PINCON->PINSEL4 = (LPC_PINCON->PINSEL4 & ~(3 << 18)) | (3 << 18);
          break;
        default:
          ERROR("P2_9 can only be used as USB_CONNECT, RXD2, ENET_MDIO or PIO.");
      }
      LPC_PINCON->PINMODE_OD2 = (LPC_PINCON->PINMODE_OD2 & ~(1 << 9)) | ((mode & IO_OPEN_DRAIN ? 1 : 0) << 9);
      LPC_PINCON->PINMODE4 = (LPC_PINCON->PINMODE4 & ~(3 << 18)) | (pull << 18);
      break;
    case P2_10:
      switch (func) {
        case PIO:
          LPC_PINCON->PINSEL4 = (LPC_PINCON->PINSEL4 & ~(3 << 20)) | (0 << 20);
          break;
        case nEINT0:
          LPC_PINCON->PINSEL4 = (LPC_PINCON->PINSEL4 & ~(3 << 20)) | (1 << 20);
          break;
        case NMI:
          LPC_PINCON->PINSEL4 = (LPC_PINCON->PINSEL4 & ~(3 << 20)) | (2 << 20);
          break;
        default:
          ERROR("P2_10 can only be used as nEINT0, NMI or PIO.");
      }
      LPC_PINCON->PINMODE_OD2 = (LPC_PINCON->PINMODE_OD2 & ~(1 << 10)) | ((mode & IO_OPEN_DRAIN ? 1 : 0) << 10);
      LPC_PINCON->PINMODE4 = (LPC_PINCON->PINMODE4 & ~(3 << 20)) | (pull << 20);
      break;
    case P2_11:
      switch (func) {
        case PIO:
          LPC_PINCON->PINSEL4 = (LPC_PINCON->PINSEL4 & ~(3 << 22)) | (0 << 22);
          break;
        case nEINT1:
          LPC_PINCON->PINSEL4 = (LPC_PINCON->PINSEL4 & ~(3 << 22)) | (1 << 22);
          break;
        case I2STX_CLK:
          LPC_PINCON->PINSEL4 = (LPC_PINCON->PINSEL4 & ~(3 << 22)) | (3 << 22);
          break;
        default:
          ERROR("P2_11 can only be used as nEINT1, I2STX_CLK or PIO.");
      }
      LPC_PINCON->PINMODE_OD2 = (LPC_PINCON->PINMODE_OD2 & ~(1 << 11)) | ((mode & IO_OPEN_DRAIN ? 1 : 0) << 11);
      LPC_PINCON->PINMODE4 = (LPC_PINCON->PINMODE4 & ~(3 << 22)) | (pull << 22);
      break;
    case P2_12:
      switch (func) {
        case PIO:
          LPC_PINCON->PINSEL4 = (LPC_PINCON->PINSEL4 & ~(3 << 24)) | (0 << 24);
          break;
        case nEINT2:
          LPC_PINCON->PINSEL4 = (LPC_PINCON->PINSEL4 & ~(3 << 24)) | (1 << 24);
          break;
        case I2STX_WS:
          LPC_PINCON->PINSEL4 = (LPC_PINCON->PINSEL4 & ~(3 << 24)) | (3 << 24);
          break;
        default:
          ERROR("P2_12 can only be used as nEINT2, I2STX_WS or PIO.");
      }
      LPC_PINCON->PINMODE_OD2 = (LPC_PINCON->PINMODE_OD2 & ~(1 << 12)) | ((mode & IO_OPEN_DRAIN ? 1 : 0) << 12);
      LPC_PINCON->PINMODE4 = (LPC_PINCON->PINMODE4 & ~(3 << 24)) | (pull << 24);
      break;
    case P2_13:
      switch (func) {
        case PIO:
          LPC_PINCON->PINSEL4 = (LPC_PINCON->PINSEL4 & ~(3 << 26)) | (0 << 26);
          break;
        case nEINT3:
          LPC_PINCON->PINSEL4 = (LPC_PINCON->PINSEL4 & ~(3 << 26)) | (1 << 26);
          break;
        case I2STX_SDA:
          LPC_PINCON->PINSEL4 = (LPC_PINCON->PINSEL4 & ~(3 << 26)) | (3 << 26);
          break;
        default:
          ERROR("P2_13 can only be used as nEINT3, I2STX_SDA or PIO.");
      }
      LPC_PINCON->PINMODE_OD2 = (LPC_PINCON->PINMODE_OD2 & ~(1 << 13)) | ((mode & IO_OPEN_DRAIN ? 1 : 0) << 13);
      LPC_PINCON->PINMODE4 = (LPC_PINCON->PINMODE4 & ~(3 << 26)) | (pull << 26);
      break;
    case P3_25:
      switch (func) {
        case PIO:
          LPC_PINCON->PINSEL7 = (LPC_PINCON->PINSEL7 & ~(3 << 18)) | (0 << 18);
          break;
        case MAT0_0:
          LPC_PINCON->PINSEL7 = (LPC_PINCON->PINSEL7 & ~(3 << 18)) | (2 << 18);
          break;
        case PWM1_2:
          LPC_PINCON->PINSEL7 = (LPC_PINCON->PINSEL7 & ~(3 << 18)) | (3 << 18);
          break;
        default:
          ERROR("P3_25 can only be used as MAT0_0, PWM1_2 or PIO.");
      }
      LPC_PINCON->PINMODE_OD3 = (LPC_PINCON->PINMODE_OD3 & ~(1 << 25)) | ((mode & IO_OPEN_DRAIN ? 1 : 0) << 25);
      LPC_PINCON->PINMODE7 = (LPC_PINCON->PINMODE7 & ~(3 << 18)) | (pull << 18);
      break;
    case P3_26:
      switch (func) {
        case PIO:
          LPC_PINCON->PINSEL7 = (LPC_PINCON->PINSEL7 & ~(3 << 20)) | (0 << 20);
          break;
        case STCLK:
          LPC_PINCON->PINSEL7 = (LPC_PINCON->PINSEL7 & ~(3 << 20)) | (1 << 20);
          break;
        case MAT0_1:
          LPC_PINCON->PINSEL7 = (LPC_PINCON->PINSEL7 & ~(3 << 20)) | (2 << 20);
          break;
        case PWM1_3:
          LPC_PINCON->PINSEL7 = (LPC_PINCON->PINSEL7 & ~(3 << 20)) | (3 << 20);
          break;
        default:
          ERROR("P3_26 can only be used as STCLK, MAT0_1, PWM1_3 or PIO.");
      }
      LPC_PINCON->PINMODE_OD3 = (LPC_PINCON->PINMODE_OD3 & ~(1 << 26)) | ((mode & IO_OPEN_DRAIN ? 1 : 0) << 26);
      LPC_PINCON->PINMODE7 = (LPC_PINCON->PINMODE7 & ~(3 << 20)) | (pull << 20);
      break;
    case P4_28:
      switch (func) {
        case PIO:
          LPC_PINCON->PINSEL9 = (LPC_PINCON->PINSEL9 & ~(3 << 24)) | (0 << 24);
          break;
        case RX_MCLK:
          LPC_PINCON->PINSEL9 = (LPC_PINCON->PINSEL9 & ~(3 << 24)) | (1 << 24);
          break;
        case MAT2_0:
          LPC_PINCON->PINSEL9 = (LPC_PINCON->PINSEL9 & ~(3 << 24)) | (2 << 24);
          break;
        case TXD3:
          LPC_PINCON->PINSEL9 = (LPC_PINCON->PINSEL9 & ~(3 << 24)) | (3 << 24);
          break;
        default:
          ERROR("P4_28 can only be used as RX_MCLK, MAT2_0, TXD3 or PIO.");
      }
      LPC_PINCON->PINMODE_OD4 = (LPC_PINCON->PINMODE_OD4 & ~(1 << 28)) | ((mode & IO_OPEN_DRAIN ? 1 : 0) << 28);
      LPC_PINCON->PINMODE9 = (LPC_PINCON->PINMODE9 & ~(3 << 24)) | (pull << 24);
      break;
    case P4_29:
      switch (func) {
        case PIO:
          LPC_PINCON->PINSEL9 = (LPC_PINCON->PINSEL9 & ~(3 << 26)) | (0 << 26);
          break;
        case TX_MCLK:
          LPC_PINCON->PINSEL9 = (LPC_PINCON->PINSEL9 & ~(3 << 26)) | (1 << 26);
          break;
        case MAT2_1:
          LPC_PINCON->PINSEL9 = (LPC_PINCON->PINSEL9 & ~(3 << 26)) | (2 << 26);
          break;
        case RXD3:
          LPC_PINCON->PINSEL9 = (LPC_PINCON->PINSEL9 & ~(3 << 26)) | (3 << 26);
          break;
        default:
          ERROR("P4_29 can only be used as TX_MCLK, MAT2_1, RXD3 or PIO.");
      }
      LPC_PINCON->PINMODE_OD4 = (LPC_PINCON->PINMODE_OD4 & ~(1 << 29)) | ((mode & IO_OPEN_DRAIN ? 1 : 0) << 29);
      LPC_PINCON->PINMODE9 = (LPC_PINCON->PINMODE9 & ~(3 << 26)) | (pull << 26);
      break;
    default:
      ERROR("Invalid IO pin.");
  }
}

INLINE
void pin_write (enum pio_pin pin, int val)
{
  switch (pin) {
    case P0_0: if(val) LPC_GPIO0->FIOSET = 1 << 0; else LPC_GPIO0->FIOCLR = 1 << 0; break;
    case P0_1: if(val) LPC_GPIO0->FIOSET = 1 << 1; else LPC_GPIO0->FIOCLR = 1 << 1; break;
    case P0_2: if(val) LPC_GPIO0->FIOSET = 1 << 2; else LPC_GPIO0->FIOCLR = 1 << 2; break;
    case P0_3: if(val) LPC_GPIO0->FIOSET = 1 << 3; else LPC_GPIO0->FIOCLR = 1 << 3; break;
    case P0_4: if(val) LPC_GPIO0->FIOSET = 1 << 4; else LPC_GPIO0->FIOCLR = 1 << 4; break;
    case P0_5: if(val) LPC_GPIO0->FIOSET = 1 << 5; else LPC_GPIO0->FIOCLR = 1 << 5; break;
    case P0_6: if(val) LPC_GPIO0->FIOSET = 1 << 6; else LPC_GPIO0->FIOCLR = 1 << 6; break;
    case P0_7: if(val) LPC_GPIO0->FIOSET = 1 << 7; else LPC_GPIO0->FIOCLR = 1 << 7; break;
    case P0_8: if(val) LPC_GPIO0->FIOSET = 1 << 8; else LPC_GPIO0->FIOCLR = 1 << 8; break;
    case P0_9: if(val) LPC_GPIO0->FIOSET = 1 << 9; else LPC_GPIO0->FIOCLR = 1 << 9; break;
    case P0_10: if(val) LPC_GPIO0->FIOSET = 1 << 10; else LPC_GPIO0->FIOCLR = 1 << 10; break;
    case P0_11: if(val) LPC_GPIO0->FIOSET = 1 << 11; else LPC_GPIO0->FIOCLR = 1 << 11; break;
    case P0_15: if(val) LPC_GPIO0->FIOSET = 1 << 15; else LPC_GPIO0->FIOCLR = 1 << 15; break;
    case P0_16: if(val) LPC_GPIO0->FIOSET = 1 << 16; else LPC_GPIO0->FIOCLR = 1 << 16; break;
    case P0_17: if(val) LPC_GPIO0->FIOSET = 1 << 17; else LPC_GPIO0->FIOCLR = 1 << 17; break;
    case P0_18: if(val) LPC_GPIO0->FIOSET = 1 << 18; else LPC_GPIO0->FIOCLR = 1 << 18; break;
    case P0_19: if(val) LPC_GPIO0->FIOSET = 1 << 19; else LPC_GPIO0->FIOCLR = 1 << 19; break;
    case P0_20: if(val) LPC_GPIO0->FIOSET = 1 << 20; else LPC_GPIO0->FIOCLR = 1 << 20; break;
    case P0_21: if(val) LPC_GPIO0->FIOSET = 1 << 21; else LPC_GPIO0->FIOCLR = 1 << 21; break;
    case P0_22: if(val) LPC_GPIO0->FIOSET = 1 << 22; else LPC_GPIO0->FIOCLR = 1 << 22; break;
    case P0_23: if(val) LPC_GPIO0->FIOSET = 1 << 23; else LPC_GPIO0->FIOCLR = 1 << 23; break;
    case P0_24: if(val) LPC_GPIO0->FIOSET = 1 << 24; else LPC_GPIO0->FIOCLR = 1 << 24; break;
    case P0_25: if(val) LPC_GPIO0->FIOSET = 1 << 25; else LPC_GPIO0->FIOCLR = 1 << 25; break;
    case P0_26: if(val) LPC_GPIO0->FIOSET = 1 << 26; else LPC_GPIO0->FIOCLR = 1 << 26; break;
    case P0_27: if(val) LPC_GPIO0->FIOSET = 1 << 27; else LPC_GPIO0->FIOCLR = 1 << 27; break;
    case P0_28: if(val) LPC_GPIO0->FIOSET = 1 << 28; else LPC_GPIO0->FIOCLR = 1 << 28; break;
    case P0_29: if(val) LPC_GPIO0->FIOSET = 1 << 29; else LPC_GPIO0->FIOCLR = 1 << 29; break;
    case P0_30: if(val) LPC_GPIO0->FIOSET = 1 << 30; else LPC_GPIO0->FIOCLR = 1 << 30; break;
    case P1_0: if(val) LPC_GPIO1->FIOSET = 1 << 0; else LPC_GPIO1->FIOCLR = 1 << 0; break;
    case P1_1: if(val) LPC_GPIO1->FIOSET = 1 << 1; else LPC_GPIO1->FIOCLR = 1 << 1; break;
    case P1_4: if(val) LPC_GPIO1->FIOSET = 1 << 4; else LPC_GPIO1->FIOCLR = 1 << 4; break;
    case P1_8: if(val) LPC_GPIO1->FIOSET = 1 << 8; else LPC_GPIO1->FIOCLR = 1 << 8; break;
    case P1_9: if(val) LPC_GPIO1->FIOSET = 1 << 9; else LPC_GPIO1->FIOCLR = 1 << 9; break;
    case P1_10: if(val) LPC_GPIO1->FIOSET = 1 << 10; else LPC_GPIO1->FIOCLR = 1 << 10; break;
    case P1_14: if(val) LPC_GPIO1->FIOSET = 1 << 14; else LPC_GPIO1->FIOCLR = 1 << 14; break;
    case P1_15: if(val) LPC_GPIO1->FIOSET = 1 << 15; else LPC_GPIO1->FIOCLR = 1 << 15; break;
    case P1_16: if(val) LPC_GPIO1->FIOSET = 1 << 16; else LPC_GPIO1->FIOCLR = 1 << 16; break;
    case P1_17: if(val) LPC_GPIO1->FIOSET = 1 << 17; else LPC_GPIO1->FIOCLR = 1 << 17; break;
    case P1_18: if(val) LPC_GPIO1->FIOSET = 1 << 18; else LPC_GPIO1->FIOCLR = 1 << 18; break;
    case P1_19: if(val) LPC_GPIO1->FIOSET = 1 << 19; else LPC_GPIO1->FIOCLR = 1 << 19; break;
    case P1_20: if(val) LPC_GPIO1->FIOSET = 1 << 20; else LPC_GPIO1->FIOCLR = 1 << 20; break;
    case P1_21: if(val) LPC_GPIO1->FIOSET = 1 << 21; else LPC_GPIO1->FIOCLR = 1 << 21; break;
    case P1_22: if(val) LPC_GPIO1->FIOSET = 1 << 22; else LPC_GPIO1->FIOCLR = 1 << 22; break;
    case P1_23: if(val) LPC_GPIO1->FIOSET = 1 << 23; else LPC_GPIO1->FIOCLR = 1 << 23; break;
    case P1_24: if(val) LPC_GPIO1->FIOSET = 1 << 24; else LPC_GPIO1->FIOCLR = 1 << 24; break;
    case P1_25: if(val) LPC_GPIO1->FIOSET = 1 << 25; else LPC_GPIO1->FIOCLR = 1 << 25; break;
    case P1_26: if(val) LPC_GPIO1->FIOSET = 1 << 26; else LPC_GPIO1->FIOCLR = 1 << 26; break;
    case P1_27: if(val) LPC_GPIO1->FIOSET = 1 << 27; else LPC_GPIO1->FIOCLR = 1 << 27; break;
    case P1_28: if(val) LPC_GPIO1->FIOSET = 1 << 28; else LPC_GPIO1->FIOCLR = 1 << 28; break;
    case P1_29: if(val) LPC_GPIO1->FIOSET = 1 << 29; else LPC_GPIO1->FIOCLR = 1 << 29; break;
    case P1_30: if(val) LPC_GPIO1->FIOSET = 1 << 30; else LPC_GPIO1->FIOCLR = 1 << 30; break;
    case P1_31: if(val) LPC_GPIO1->FIOSET = 1 << 31; else LPC_GPIO1->FIOCLR = 1 << 31; break;
    case P2_0: if(val) LPC_GPIO2->FIOSET = 1 << 0; else LPC_GPIO2->FIOCLR = 1 << 0; break;
    case P2_1: if(val) LPC_GPIO2->FIOSET = 1 << 1; else LPC_GPIO2->FIOCLR = 1 << 1; break;
    case P2_2: if(val) LPC_GPIO2->FIOSET = 1 << 2; else LPC_GPIO2->FIOCLR = 1 << 2; break;
    case P2_3: if(val) LPC_GPIO2->FIOSET = 1 << 3; else LPC_GPIO2->FIOCLR = 1 << 3; break;
    case P2_4: if(val) LPC_GPIO2->FIOSET = 1 << 4; else LPC_GPIO2->FIOCLR = 1 << 4; break;
    case P2_5: if(val) LPC_GPIO2->FIOSET = 1 << 5; else LPC_GPIO2->FIOCLR = 1 << 5; break;
    case P2_6: if(val) LPC_GPIO2->FIOSET = 1 << 6; else LPC_GPIO2->FIOCLR = 1 << 6; break;
    case P2_7: if(val) LPC_GPIO2->FIOSET = 1 << 7; else LPC_GPIO2->FIOCLR = 1 << 7; break;
    case P2_8: if(val) LPC_GPIO2->FIOSET = 1 << 8; else LPC_GPIO2->FIOCLR = 1 << 8; break;
    case P2_9: if(val) LPC_GPIO2->FIOSET = 1 << 9; else LPC_GPIO2->FIOCLR = 1 << 9; break;
    case P2_10: if(val) LPC_GPIO2->FIOSET = 1 << 10; else LPC_GPIO2->FIOCLR = 1 << 10; break;
    case P2_11: if(val) LPC_GPIO2->FIOSET = 1 << 11; else LPC_GPIO2->FIOCLR = 1 << 11; break;
    case P2_12: if(val) LPC_GPIO2->FIOSET = 1 << 12; else LPC_GPIO2->FIOCLR = 1 << 12; break;
    case P2_13: if(val) LPC_GPIO2->FIOSET = 1 << 13; else LPC_GPIO2->FIOCLR = 1 << 13; break;
    case P3_25: if(val) LPC_GPIO3->FIOSET = 1 << 25; else LPC_GPIO3->FIOCLR = 1 << 25; break;
    case P3_26: if(val) LPC_GPIO3->FIOSET = 1 << 26; else LPC_GPIO3->FIOCLR = 1 << 26; break;
    case P4_28: if(val) LPC_GPIO4->FIOSET = 1 << 28; else LPC_GPIO4->FIOCLR = 1 << 28; break;
    case P4_29: if(val) LPC_GPIO4->FIOSET = 1 << 29; else LPC_GPIO4->FIOCLR = 1 << 29; break;
    default:
      ERROR("Invalid IO pin.");
  }
}

INLINE
int pin_read (enum pio_pin pin)
{
  switch (pin) {
    case P0_0: return LPC_GPIO0->FIOPIN & (1 << 0) ? 1 : 0;
    case P0_1: return LPC_GPIO0->FIOPIN & (1 << 1) ? 1 : 0;
    case P0_2: return LPC_GPIO0->FIOPIN & (1 << 2) ? 1 : 0;
    case P0_3: return LPC_GPIO0->FIOPIN & (1 << 3) ? 1 : 0;
    case P0_4: return LPC_GPIO0->FIOPIN & (1 << 4) ? 1 : 0;
    case P0_5: return LPC_GPIO0->FIOPIN & (1 << 5) ? 1 : 0;
    case P0_6: return LPC_GPIO0->FIOPIN & (1 << 6) ? 1 : 0;
    case P0_7: return LPC_GPIO0->FIOPIN & (1 << 7) ? 1 : 0;
    case P0_8: return LPC_GPIO0->FIOPIN & (1 << 8) ? 1 : 0;
    case P0_9: return LPC_GPIO0->FIOPIN & (1 << 9) ? 1 : 0;
    case P0_10: return LPC_GPIO0->FIOPIN & (1 << 10) ? 1 : 0;
    case P0_11: return LPC_GPIO0->FIOPIN & (1 << 11) ? 1 : 0;
    case P0_15: return LPC_GPIO0->FIOPIN & (1 << 15) ? 1 : 0;
    case P0_16: return LPC_GPIO0->FIOPIN & (1 << 16) ? 1 : 0;
    case P0_17: return LPC_GPIO0->FIOPIN & (1 << 17) ? 1 : 0;
    case P0_18: return LPC_GPIO0->FIOPIN & (1 << 18) ? 1 : 0;
    case P0_19: return LPC_GPIO0->FIOPIN & (1 << 19) ? 1 : 0;
    case P0_20: return LPC_GPIO0->FIOPIN & (1 << 20) ? 1 : 0;
    case P0_21: return LPC_GPIO0->FIOPIN & (1 << 21) ? 1 : 0;
    case P0_22: return LPC_GPIO0->FIOPIN & (1 << 22) ? 1 : 0;
    case P0_23: return LPC_GPIO0->FIOPIN & (1 << 23) ? 1 : 0;
    case P0_24: return LPC_GPIO0->FIOPIN & (1 << 24) ? 1 : 0;
    case P0_25: return LPC_GPIO0->FIOPIN & (1 << 25) ? 1 : 0;
    case P0_26: return LPC_GPIO0->FIOPIN & (1 << 26) ? 1 : 0;
    case P0_27: return LPC_GPIO0->FIOPIN & (1 << 27) ? 1 : 0;
    case P0_28: return LPC_GPIO0->FIOPIN & (1 << 28) ? 1 : 0;
    case P0_29: return LPC_GPIO0->FIOPIN & (1 << 29) ? 1 : 0;
    case P0_30: return LPC_GPIO0->FIOPIN & (1 << 30) ? 1 : 0;
    case P1_0: return LPC_GPIO1->FIOPIN & (1 << 0) ? 1 : 0;
    case P1_1: return LPC_GPIO1->FIOPIN & (1 << 1) ? 1 : 0;
    case P1_4: return LPC_GPIO1->FIOPIN & (1 << 4) ? 1 : 0;
    case P1_8: return LPC_GPIO1->FIOPIN & (1 << 8) ? 1 : 0;
    case P1_9: return LPC_GPIO1->FIOPIN & (1 << 9) ? 1 : 0;
    case P1_10: return LPC_GPIO1->FIOPIN & (1 << 10) ? 1 : 0;
    case P1_14: return LPC_GPIO1->FIOPIN & (1 << 14) ? 1 : 0;
    case P1_15: return LPC_GPIO1->FIOPIN & (1 << 15) ? 1 : 0;
    case P1_16: return LPC_GPIO1->FIOPIN & (1 << 16) ? 1 : 0;
    case P1_17: return LPC_GPIO1->FIOPIN & (1 << 17) ? 1 : 0;
    case P1_18: return LPC_GPIO1->FIOPIN & (1 << 18) ? 1 : 0;
    case P1_19: return LPC_GPIO1->FIOPIN & (1 << 19) ? 1 : 0;
    case P1_20: return LPC_GPIO1->FIOPIN & (1 << 20) ? 1 : 0;
    case P1_21: return LPC_GPIO1->FIOPIN & (1 << 21) ? 1 : 0;
    case P1_22: return LPC_GPIO1->FIOPIN & (1 << 22) ? 1 : 0;
    case P1_23: return LPC_GPIO1->FIOPIN & (1 << 23) ? 1 : 0;
    case P1_24: return LPC_GPIO1->FIOPIN & (1 << 24) ? 1 : 0;
    case P1_25: return LPC_GPIO1->FIOPIN & (1 << 25) ? 1 : 0;
    case P1_26: return LPC_GPIO1->FIOPIN & (1 << 26) ? 1 : 0;
    case P1_27: return LPC_GPIO1->FIOPIN & (1 << 27) ? 1 : 0;
    case P1_28: return LPC_GPIO1->FIOPIN & (1 << 28) ? 1 : 0;
    case P1_29: return LPC_GPIO1->FIOPIN & (1 << 29) ? 1 : 0;
    case P1_30: return LPC_GPIO1->FIOPIN & (1 << 30) ? 1 : 0;
    case P1_31: return LPC_GPIO1->FIOPIN & (1 << 31) ? 1 : 0;
    case P2_0: return LPC_GPIO2->FIOPIN & (1 << 0) ? 1 : 0;
    case P2_1: return LPC_GPIO2->FIOPIN & (1 << 1) ? 1 : 0;
    case P2_2: return LPC_GPIO2->FIOPIN & (1 << 2) ? 1 : 0;
    case P2_3: return LPC_GPIO2->FIOPIN & (1 << 3) ? 1 : 0;
    case P2_4: return LPC_GPIO2->FIOPIN & (1 << 4) ? 1 : 0;
    case P2_5: return LPC_GPIO2->FIOPIN & (1 << 5) ? 1 : 0;
    case P2_6: return LPC_GPIO2->FIOPIN & (1 << 6) ? 1 : 0;
    case P2_7: return LPC_GPIO2->FIOPIN & (1 << 7) ? 1 : 0;
    case P2_8: return LPC_GPIO2->FIOPIN & (1 << 8) ? 1 : 0;
    case P2_9: return LPC_GPIO2->FIOPIN & (1 << 9) ? 1 : 0;
    case P2_10: return LPC_GPIO2->FIOPIN & (1 << 10) ? 1 : 0;
    case P2_11: return LPC_GPIO2->FIOPIN & (1 << 11) ? 1 : 0;
    case P2_12: return LPC_GPIO2->FIOPIN & (1 << 12) ? 1 : 0;
    case P2_13: return LPC_GPIO2->FIOPIN & (1 << 13) ? 1 : 0;
    case P3_25: return LPC_GPIO3->FIOPIN & (1 << 25) ? 1 : 0;
    case P3_26: return LPC_GPIO3->FIOPIN & (1 << 26) ? 1 : 0;
    case P4_28: return LPC_GPIO4->FIOPIN & (1 << 28) ? 1 : 0;
    case P4_29: return LPC_GPIO4->FIOPIN & (1 << 29) ? 1 : 0;
    default:
      ERROR("Invalid IO pin.");
  }
}

INLINE
void pin_dir (enum pio_pin pin, enum pin_dir dir)
{
  switch (pin) {
    case P0_0: LPC_GPIO0->FIODIR = (LPC_GPIO0->FIODIR & ~(1 << 0)) | (dir ? 1 << 0 : 0); break;
    case P0_1: LPC_GPIO0->FIODIR = (LPC_GPIO0->FIODIR & ~(1 << 1)) | (dir ? 1 << 1 : 0); break;
    case P0_2: LPC_GPIO0->FIODIR = (LPC_GPIO0->FIODIR & ~(1 << 2)) | (dir ? 1 << 2 : 0); break;
    case P0_3: LPC_GPIO0->FIODIR = (LPC_GPIO0->FIODIR & ~(1 << 3)) | (dir ? 1 << 3 : 0); break;
    case P0_4: LPC_GPIO0->FIODIR = (LPC_GPIO0->FIODIR & ~(1 << 4)) | (dir ? 1 << 4 : 0); break;
    case P0_5: LPC_GPIO0->FIODIR = (LPC_GPIO0->FIODIR & ~(1 << 5)) | (dir ? 1 << 5 : 0); break;
    case P0_6: LPC_GPIO0->FIODIR = (LPC_GPIO0->FIODIR & ~(1 << 6)) | (dir ? 1 << 6 : 0); break;
    case P0_7: LPC_GPIO0->FIODIR = (LPC_GPIO0->FIODIR & ~(1 << 7)) | (dir ? 1 << 7 : 0); break;
    case P0_8: LPC_GPIO0->FIODIR = (LPC_GPIO0->FIODIR & ~(1 << 8)) | (dir ? 1 << 8 : 0); break;
    case P0_9: LPC_GPIO0->FIODIR = (LPC_GPIO0->FIODIR & ~(1 << 9)) | (dir ? 1 << 9 : 0); break;
    case P0_10: LPC_GPIO0->FIODIR = (LPC_GPIO0->FIODIR & ~(1 << 10)) | (dir ? 1 << 10 : 0); break;
    case P0_11: LPC_GPIO0->FIODIR = (LPC_GPIO0->FIODIR & ~(1 << 11)) | (dir ? 1 << 11 : 0); break;
    case P0_15: LPC_GPIO0->FIODIR = (LPC_GPIO0->FIODIR & ~(1 << 15)) | (dir ? 1 << 15 : 0); break;
    case P0_16: LPC_GPIO0->FIODIR = (LPC_GPIO0->FIODIR & ~(1 << 16)) | (dir ? 1 << 16 : 0); break;
    case P0_17: LPC_GPIO0->FIODIR = (LPC_GPIO0->FIODIR & ~(1 << 17)) | (dir ? 1 << 17 : 0); break;
    case P0_18: LPC_GPIO0->FIODIR = (LPC_GPIO0->FIODIR & ~(1 << 18)) | (dir ? 1 << 18 : 0); break;
    case P0_19: LPC_GPIO0->FIODIR = (LPC_GPIO0->FIODIR & ~(1 << 19)) | (dir ? 1 << 19 : 0); break;
    case P0_20: LPC_GPIO0->FIODIR = (LPC_GPIO0->FIODIR & ~(1 << 20)) | (dir ? 1 << 20 : 0); break;
    case P0_21: LPC_GPIO0->FIODIR = (LPC_GPIO0->FIODIR & ~(1 << 21)) | (dir ? 1 << 21 : 0); break;
    case P0_22: LPC_GPIO0->FIODIR = (LPC_GPIO0->FIODIR & ~(1 << 22)) | (dir ? 1 << 22 : 0); break;
    case P0_23: LPC_GPIO0->FIODIR = (LPC_GPIO0->FIODIR & ~(1 << 23)) | (dir ? 1 << 23 : 0); break;
    case P0_24: LPC_GPIO0->FIODIR = (LPC_GPIO0->FIODIR & ~(1 << 24)) | (dir ? 1 << 24 : 0); break;
    case P0_25: LPC_GPIO0->FIODIR = (LPC_GPIO0->FIODIR & ~(1 << 25)) | (dir ? 1 << 25 : 0); break;
    case P0_26: LPC_GPIO0->FIODIR = (LPC_GPIO0->FIODIR & ~(1 << 26)) | (dir ? 1 << 26 : 0); break;
    case P0_27: LPC_GPIO0->FIODIR = (LPC_GPIO0->FIODIR & ~(1 << 27)) | (dir ? 1 << 27 : 0); break;
    case P0_28: LPC_GPIO0->FIODIR = (LPC_GPIO0->FIODIR & ~(1 << 28)) | (dir ? 1 << 28 : 0); break;
    case P0_29: LPC_GPIO0->FIODIR = (LPC_GPIO0->FIODIR & ~(1 << 29)) | (dir ? 1 << 29 : 0); break;
    case P0_30: LPC_GPIO0->FIODIR = (LPC_GPIO0->FIODIR & ~(1 << 30)) | (dir ? 1 << 30 : 0); break;
    case P1_0: LPC_GPIO1->FIODIR = (LPC_GPIO1->FIODIR & ~(1 << 0)) | (dir ? 1 << 0 : 0); break;
    case P1_1: LPC_GPIO1->FIODIR = (LPC_GPIO1->FIODIR & ~(1 << 1)) | (dir ? 1 << 1 : 0); break;
    case P1_4: LPC_GPIO1->FIODIR = (LPC_GPIO1->FIODIR & ~(1 << 4)) | (dir ? 1 << 4 : 0); break;
    case P1_8: LPC_GPIO1->FIODIR = (LPC_GPIO1->FIODIR & ~(1 << 8)) | (dir ? 1 << 8 : 0); break;
    case P1_9: LPC_GPIO1->FIODIR = (LPC_GPIO1->FIODIR & ~(1 << 9)) | (dir ? 1 << 9 : 0); break;
    case P1_10: LPC_GPIO1->FIODIR = (LPC_GPIO1->FIODIR & ~(1 << 10)) | (dir ? 1 << 10 : 0); break;
    case P1_14: LPC_GPIO1->FIODIR = (LPC_GPIO1->FIODIR & ~(1 << 14)) | (dir ? 1 << 14 : 0); break;
    case P1_15: LPC_GPIO1->FIODIR = (LPC_GPIO1->FIODIR & ~(1 << 15)) | (dir ? 1 << 15 : 0); break;
    case P1_16: LPC_GPIO1->FIODIR = (LPC_GPIO1->FIODIR & ~(1 << 16)) | (dir ? 1 << 16 : 0); break;
    case P1_17: LPC_GPIO1->FIODIR = (LPC_GPIO1->FIODIR & ~(1 << 17)) | (dir ? 1 << 17 : 0); break;
    case P1_18: LPC_GPIO1->FIODIR = (LPC_GPIO1->FIODIR & ~(1 << 18)) | (dir ? 1 << 18 : 0); break;
    case P1_19: LPC_GPIO1->FIODIR = (LPC_GPIO1->FIODIR & ~(1 << 19)) | (dir ? 1 << 19 : 0); break;
    case P1_20: LPC_GPIO1->FIODIR = (LPC_GPIO1->FIODIR & ~(1 << 20)) | (dir ? 1 << 20 : 0); break;
    case P1_21: LPC_GPIO1->FIODIR = (LPC_GPIO1->FIODIR & ~(1 << 21)) | (dir ? 1 << 21 : 0); break;
    case P1_22: LPC_GPIO1->FIODIR = (LPC_GPIO1->FIODIR & ~(1 << 22)) | (dir ? 1 << 22 : 0); break;
    case P1_23: LPC_GPIO1->FIODIR = (LPC_GPIO1->FIODIR & ~(1 << 23)) | (dir ? 1 << 23 : 0); break;
    case P1_24: LPC_GPIO1->FIODIR = (LPC_GPIO1->FIODIR & ~(1 << 24)) | (dir ? 1 << 24 : 0); break;
    case P1_25: LPC_GPIO1->FIODIR = (LPC_GPIO1->FIODIR & ~(1 << 25)) | (dir ? 1 << 25 : 0); break;
    case P1_26: LPC_GPIO1->FIODIR = (LPC_GPIO1->FIODIR & ~(1 << 26)) | (dir ? 1 << 26 : 0); break;
    case P1_27: LPC_GPIO1->FIODIR = (LPC_GPIO1->FIODIR & ~(1 << 27)) | (dir ? 1 << 27 : 0); break;
    case P1_28: LPC_GPIO1->FIODIR = (LPC_GPIO1->FIODIR & ~(1 << 28)) | (dir ? 1 << 28 : 0); break;
    case P1_29: LPC_GPIO1->FIODIR = (LPC_GPIO1->FIODIR & ~(1 << 29)) | (dir ? 1 << 29 : 0); break;
    case P1_30: LPC_GPIO1->FIODIR = (LPC_GPIO1->FIODIR & ~(1 << 30)) | (dir ? 1 << 30 : 0); break;
    case P1_31: LPC_GPIO1->FIODIR = (LPC_GPIO1->FIODIR & ~(1 << 31)) | (dir ? 1 << 31 : 0); break;
    case P2_0: LPC_GPIO2->FIODIR = (LPC_GPIO2->FIODIR & ~(1 << 0)) | (dir ? 1 << 0 : 0); break;
    case P2_1: LPC_GPIO2->FIODIR = (LPC_GPIO2->FIODIR & ~(1 << 1)) | (dir ? 1 << 1 : 0); break;
    case P2_2: LPC_GPIO2->FIODIR = (LPC_GPIO2->FIODIR & ~(1 << 2)) | (dir ? 1 << 2 : 0); break;
    case P2_3: LPC_GPIO2->FIODIR = (LPC_GPIO2->FIODIR & ~(1 << 3)) | (dir ? 1 << 3 : 0); break;
    case P2_4: LPC_GPIO2->FIODIR = (LPC_GPIO2->FIODIR & ~(1 << 4)) | (dir ? 1 << 4 : 0); break;
    case P2_5: LPC_GPIO2->FIODIR = (LPC_GPIO2->FIODIR & ~(1 << 5)) | (dir ? 1 << 5 : 0); break;
    case P2_6: LPC_GPIO2->FIODIR = (LPC_GPIO2->FIODIR & ~(1 << 6)) | (dir ? 1 << 6 : 0); break;
    case P2_7: LPC_GPIO2->FIODIR = (LPC_GPIO2->FIODIR & ~(1 << 7)) | (dir ? 1 << 7 : 0); break;
    case P2_8: LPC_GPIO2->FIODIR = (LPC_GPIO2->FIODIR & ~(1 << 8)) | (dir ? 1 << 8 : 0); break;
    case P2_9: LPC_GPIO2->FIODIR = (LPC_GPIO2->FIODIR & ~(1 << 9)) | (dir ? 1 << 9 : 0); break;
    case P2_10: LPC_GPIO2->FIODIR = (LPC_GPIO2->FIODIR & ~(1 << 10)) | (dir ? 1 << 10 : 0); break;
    case P2_11: LPC_GPIO2->FIODIR = (LPC_GPIO2->FIODIR & ~(1 << 11)) | (dir ? 1 << 11 : 0); break;
    case P2_12: LPC_GPIO2->FIODIR = (LPC_GPIO2->FIODIR & ~(1 << 12)) | (dir ? 1 << 12 : 0); break;
    case P2_13: LPC_GPIO2->FIODIR = (LPC_GPIO2->FIODIR & ~(1 << 13)) | (dir ? 1 << 13 : 0); break;
    case P3_25: LPC_GPIO3->FIODIR = (LPC_GPIO3->FIODIR & ~(1 << 25)) | (dir ? 1 << 25 : 0); break;
    case P3_26: LPC_GPIO3->FIODIR = (LPC_GPIO3->FIODIR & ~(1 << 26)) | (dir ? 1 << 26 : 0); break;
    case P4_28: LPC_GPIO4->FIODIR = (LPC_GPIO4->FIODIR & ~(1 << 28)) | (dir ? 1 << 28 : 0); break;
    case P4_29: LPC_GPIO4->FIODIR = (LPC_GPIO4->FIODIR & ~(1 << 29)) | (dir ? 1 << 29 : 0); break;
    default:
      ERROR("Invalid IO pin.");
  }
}

#endif // IO_PIN_H