/*
 * Periprerial clocks & power control for LPC17xx.
 *
 * Copyright (c) 2010 LoEE - Jakub Piotr Cłapa
 * This program is released under the new BSD license.
 */
#ifndef SYSTEM_H
#define SYSTEM_H

#include "common.h"

/*
 * Main oscillator
 */
enum main_oscillator_speed {
  MAIN_OSCILLATOR_NORM = 0,
  MAIN_OSCILLATOR_FAST = 1,
  MAIN_OSCILLATOR_OFF  = 0xff,
};

#define SCS_BITS enum { OSCRANGE = 4, OSCEN = 5, OSCSTAT = 6 }

INLINE
int main_oscillator_ready ()
{
  SCS_BITS;
  return LPC_SC->SCS & (1 << OSCSTAT);
}

INLINE
void main_oscillator_setup (enum main_oscillator_speed speed)
{
  SCS_BITS;
  if (speed == MAIN_OSCILLATOR_OFF) {
    LPC_SC->SCS = 0;
  } else {
    LPC_SC->SCS = ((speed = MAIN_OSCILLATOR_FAST ? 1 : 0) << OSCRANGE) | \
                  (1 << OSCEN);
    while (!main_oscillator_ready ());
  }
}

/*
 * CPU clock divider.
 */
INLINE
void cpu_clock_divider_setup (int divider)
{
  if (divider < 1 || divider > 256) ERROR("CPU clock divider value out of range [1-256].");

  LPC_SC->CCLKCFG = divider - 1;
}

/*
 * PLL0
 */
#define PLL0_BITS enum {      \
  MSEL0 = 0, NSEL0 = 16,      \
  PLLE0 = 0, PLLE0_STAT = 24, \
  PLLC0 = 1, PLLC0_STAT = 25, \
  PLOCK0 = 26 }

enum pll0_clock_source {
  PLL0_SOURCE_RC = 0,
  PLL0_SOURCE_MAIN = 1,
  PLL0_SOURCE_RTC = 2,
};

INLINE
int pll0_enabled ()
{
  PLL0_BITS; return LPC_SC->PLL0STAT & PLLE0_STAT;
}

INLINE
int pll0_connected ()
{
  PLL0_BITS; return LPC_SC->PLL0STAT & PLLC0_STAT;
}

INLINE
uint32_t *bitband_address (void *reg_addr, int bit_no)
{
  uint32_t addr = (uint32_t)reg_addr;
  if (addr > 0x40000000 && addr < 0x400FFFFF) {
    return (uint32_t *)(0x42000000 + (addr - 0x40000000) * 32 + bit_no * 4);
  }
}

#define bit_read(reg, bit_no) (*reg & (1 << bit_no))
#define bit_read_alias(reg, bit_no) (*bitband_address (reg, bit_no))

INLINE
int pll0_locked ()
{
  PLL0_BITS;
  return bit_read (&LPC_SC->PLL0STAT, PLOCK0);
}

INLINE
void pll0_feed ()
{
  LPC_SC->PLL0FEED  = 0xAA;
  LPC_SC->PLL0FEED  = 0x55;
}

INLINE
void pll0_enable ()
{
  PLL0_BITS; LPC_SC->PLL0CON = (1 << PLLE0); // clear the PLLC0 flag as a bonus
  pll0_feed ();
}

INLINE
void pll0_connect ()
{
  PLL0_BITS; LPC_SC->PLL0CON = (1 << PLLE0) | (1 << PLLC0);
  pll0_feed ();
}

INLINE
void pll0_disable ()
{
  PLL0_BITS; LPC_SC->PLL0CON = 0;
  pll0_feed ();
}

INLINE
void pll0_setup (enum pll0_clock_source source, int mult, int div)
{
  if ( div < 1  ||  div > 32 ) ERROR("PLL0 divider value out of range [1-32].");
  // FIXME: support large values for 32kHz input
  if (mult % 2) ERROR("PLL0 multiplier value must be even.");
  if (mult < 12 || mult > 1024) ERROR("PLL0 multiplier value out of range [12-1024].");
  mult = mult / 2 - 1;
  div -= 1;

  pll0_enable ();
  PLL0_BITS;
  LPC_SC->CLKSRCSEL = source;
  LPC_SC->PLL0CFG = mult << MSEL0 | div << NSEL0;
  pll0_feed ();
  while (!pll0_locked ());
  pll0_connect ();
}

/*
 * Peripheral clock control.
 */
enum peripheral_clock_id {
  PCLK_WDT = 0, PCLK_TIMER0 = 1, PCLK_TIMER1 = 2, PCLK_UART0 = 3,
  PCLK_UART1 = 4, PCLK_PWM1 = 6, PCLK_I2C0 = 7, PCLK_SPI = 8, PCLK_SSP1 = 10,
  PCLK_DAC = 11, PCLK_ADC = 12, PCLK_CAN1 = 13, PCLK_CAN2 = 14, PCLK_ACF = 15,
  PCLK_QEI = 16, PCLK_GPIOINT = 17, PCLK_PCB = 18, PCLK_I2C1 = 19, 
  PCLK_SSP0 = 21, PCLK_TIMER2 = 22, PCLK_TIMER3 = 23, PCLK_UART2 = 24,
  PCLK_UART3 = 25, PCLK_I2C2 = 26, PCLK_I2S = 27, PCLK_RIT = 29, 
  PCLK_SYSCON = 30, PCLK_MC = 31
};

INLINE
void pclk_set_divider (enum peripheral_clock_id clk, int div)
{
  switch(div) {
    case 4: div = 0; break;
    case 1: div = 1; break;
    case 2: div = 2; break;
    case 8: if (clk == PCLK_CAN1 || clk == PCLK_CAN2 || clk == PCLK_ACF)
              ERROR ("Dividing clock by 8 is not possible for CAN.");
            else
              div = 3;
            break;
    case 6: if (clk == PCLK_CAN1 || clk == PCLK_CAN2 || clk == PCLK_ACF)
              div = 3;
            else
              ERROR ("Dividing clock by 6 is only possible for CAN.");
            break;
    default:
            ERROR ("Valid PCLK dividers are 1, 2, 4, 6 and 8."); break;
  }
 
  int pin_off = (clk * 2) % 32;

  switch (clk) {
    case 0 ... 15:
      LPC_SC->PCLKSEL0 = (LPC_SC->PCLKSEL0 & ~(3 << pin_off)) | (div << pin_off); break;
    case 16 ... 31:
      LPC_SC->PCLKSEL1 = (LPC_SC->PCLKSEL0 & ~(3 << pin_off)) | (div << pin_off); break;
  }
}

/*
 * Peripheral power control.
 */
enum peripheral_power_id {
  POWER_TIM0 = 1, POWER_TIM1 = 2, POWER_UART0 = 3, POWER_UART1 = 4,
  POWER_PWM1 = 6, POWER_I2C0 = 7, POWER_SPI = 8, POWER_RTC = 9,
  POWER_SSP1 = 10, POWER_ADC = 12, POWER_CAN1 = 13, POWER_CAN2 = 14,
  POWER_RIT = 16, POWER_MCPWM = 17, POWER_QEI = 18, POWER_I2C1 = 19,
  POWER_SSP0 = 21, POWER_TIM2 = 22, POWER_TIM3 = 23, POWER_UART2 = 24,
  POWER_UART3 = 25, POWER_I2C2 = 26, POWER_I2S = 27, POWER_GPDMA = 29,
  POWER_ENET = 30, POWER_USB = 31
};

INLINE
void power_control (enum peripheral_power_id id, int on)
{
  if (on) {
    LPC_SC->PCONP |= 1<< id;
  } else {
    LPC_SC->PCONP &= ~(1 << id);
  }
}
#endif
