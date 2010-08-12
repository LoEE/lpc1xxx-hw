/*
 * IO functions for NXP LPC1768. (generated file, check io-pin.ss)
 *
 * See also: http://bitbucket.org/jpc/lpc1768/
 *
 * Copyright (c) 2010 LoEE - Jakub Piotr Cłapa
 * This program is released under the new BSD license.
 */
#ifndef IO_PIN_H
#define IO_PIN_H

#include "LPC17xx.h"

enum pin_port {
P0 = 0,
P1 = 32,
P2 = 64,
P3 = 96,
P4 = 128,
};

enum pin_dir {
  PIN_IN = 0,
  PIN_OUT = 1,
};

extern void invalid_pin_error () __attribute__((error ("Invalid IO pin number.")));

extern __inline__ __attribute__((always_inline,gnu_inline))
int pin_read (int pin_no)
{
  switch(pin_no) {
    case 0 ... 31:
      return LPC_GPIO0->FIOPIN & (1 << (pin_no - 0));
    case 32 ... 63:
      return LPC_GPIO1->FIOPIN & (1 << (pin_no - 32));
    case 64 ... 95:
      return LPC_GPIO2->FIOPIN & (1 << (pin_no - 64));
    case 96 ... 127:
      return LPC_GPIO3->FIOPIN & (1 << (pin_no - 96));
    case 128 ... 159:
      return LPC_GPIO4->FIOPIN & (1 << (pin_no - 128));
    default:
      invalid_pin_error ();
      break;
  }
  return 0;
}

extern __inline__ __attribute__((always_inline,gnu_inline))
void pin_write (int pin_no, int value)
{
  switch(pin_no) {
    case 0 ... 31:
      if (value) {
        LPC_GPIO0->FIOSET = (1 << (pin_no - 0));
      } else {
        LPC_GPIO0->FIOCLR = (1 << (pin_no - 0));
      }
      break;
    case 32 ... 63:
      if (value) {
        LPC_GPIO1->FIOSET = (1 << (pin_no - 32));
      } else {
        LPC_GPIO1->FIOCLR = (1 << (pin_no - 32));
      }
      break;
    case 64 ... 95:
      if (value) {
        LPC_GPIO2->FIOSET = (1 << (pin_no - 64));
      } else {
        LPC_GPIO2->FIOCLR = (1 << (pin_no - 64));
      }
      break;
    case 96 ... 127:
      if (value) {
        LPC_GPIO3->FIOSET = (1 << (pin_no - 96));
      } else {
        LPC_GPIO3->FIOCLR = (1 << (pin_no - 96));
      }
      break;
    case 128 ... 159:
      if (value) {
        LPC_GPIO4->FIOSET = (1 << (pin_no - 128));
      } else {
        LPC_GPIO4->FIOCLR = (1 << (pin_no - 128));
      }
      break;
    default:
      invalid_pin_error ();
      break;
  }
}

extern __inline__ __attribute__((always_inline,gnu_inline))
void pin_dir (int pin_no, enum pin_dir dir)
{
  switch(pin_no) {
    case 0 ... 31:
      if (dir == PIN_OUT) {
        LPC_GPIO0->FIODIR |= (1 << (pin_no - 0));
      } else {
        LPC_GPIO0->FIODIR &= (1 << (pin_no - 0));
      }
      break;
    case 32 ... 63:
      if (dir == PIN_OUT) {
        LPC_GPIO1->FIODIR |= (1 << (pin_no - 32));
      } else {
        LPC_GPIO1->FIODIR &= (1 << (pin_no - 32));
      }
      break;
    case 64 ... 95:
      if (dir == PIN_OUT) {
        LPC_GPIO2->FIODIR |= (1 << (pin_no - 64));
      } else {
        LPC_GPIO2->FIODIR &= (1 << (pin_no - 64));
      }
      break;
    case 96 ... 127:
      if (dir == PIN_OUT) {
        LPC_GPIO3->FIODIR |= (1 << (pin_no - 96));
      } else {
        LPC_GPIO3->FIODIR &= (1 << (pin_no - 96));
      }
      break;
    case 128 ... 159:
      if (dir == PIN_OUT) {
        LPC_GPIO4->FIODIR |= (1 << (pin_no - 128));
      } else {
        LPC_GPIO4->FIODIR &= (1 << (pin_no - 128));
      }
      break;
    default:
      invalid_pin_error ();
      break;
  }
}

extern __inline__ __attribute__((always_inline,gnu_inline))
void pin_setup (int pin_no, int pinsel)
{
  switch(pin_no) {
    case 0 ... 15:
      LPC_PINCON->PINSEL0 = (LPC_PINCON->PINSEL0 & ~(3 << ((pin_no - 0) * 2 % 32))) | (pinsel << ((pin_no - 0) * 2 % 32));
      break;
    case 16 ... 31:
      LPC_PINCON->PINSEL1 = (LPC_PINCON->PINSEL1 & ~(3 << ((pin_no - 0) * 2 % 32))) | (pinsel << ((pin_no - 0) * 2 % 32));
      break;
    case 32 ... 47:
      LPC_PINCON->PINSEL2 = (LPC_PINCON->PINSEL2 & ~(3 << ((pin_no - 32) * 2 % 32))) | (pinsel << ((pin_no - 32) * 2 % 32));
      break;
    case 48 ... 63:
      LPC_PINCON->PINSEL3 = (LPC_PINCON->PINSEL3 & ~(3 << ((pin_no - 32) * 2 % 32))) | (pinsel << ((pin_no - 32) * 2 % 32));
      break;
    case 64 ... 79:
      LPC_PINCON->PINSEL4 = (LPC_PINCON->PINSEL4 & ~(3 << ((pin_no - 64) * 2 % 32))) | (pinsel << ((pin_no - 64) * 2 % 32));
      break;
    case 80 ... 95:
      LPC_PINCON->PINSEL5 = (LPC_PINCON->PINSEL5 & ~(3 << ((pin_no - 64) * 2 % 32))) | (pinsel << ((pin_no - 64) * 2 % 32));
      break;
    case 96 ... 111:
      LPC_PINCON->PINSEL6 = (LPC_PINCON->PINSEL6 & ~(3 << ((pin_no - 96) * 2 % 32))) | (pinsel << ((pin_no - 96) * 2 % 32));
      break;
    case 112 ... 127:
      LPC_PINCON->PINSEL7 = (LPC_PINCON->PINSEL7 & ~(3 << ((pin_no - 96) * 2 % 32))) | (pinsel << ((pin_no - 96) * 2 % 32));
      break;
    case 128 ... 143:
      LPC_PINCON->PINSEL8 = (LPC_PINCON->PINSEL8 & ~(3 << ((pin_no - 128) * 2 % 32))) | (pinsel << ((pin_no - 128) * 2 % 32));
      break;
    case 144 ... 159:
      LPC_PINCON->PINSEL9 = (LPC_PINCON->PINSEL9 & ~(3 << ((pin_no - 128) * 2 % 32))) | (pinsel << ((pin_no - 128) * 2 % 32));
      break;
    default:
      invalid_pin_error ();
      break;
  }
}

#endif
