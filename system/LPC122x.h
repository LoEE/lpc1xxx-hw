/*
   System configuration functions for the LPC122x processors.

   This is an automatically generated file. For more details see:
       http://bitbucket.org/jpc/lpc1xxx-hw/

   Copyright (c) 2010-2011 LoEE - Jakub Piotr Cłapa
   This program is released under the new BSD license.
*/
#ifndef SYSTEM_H
#define SYSTEM_H

INLINE void set_power (int bit, int on)
{
  LPC_SYSCON->PDRUNCFG = (LPC_SYSCON->PDRUNCFG & ~(1 << bit)) | (!on ? 1 << bit : 0);
}

INLINE void set_clock (int bit, int on)
{
  LPC_SYSCON->SYSAHBCLKCTRL = (LPC_SYSCON->SYSAHBCLKCTRL & ~(1 << bit)) | (on ? 1 << bit : 0);
}

INLINE void set_reset (int bit, int reset)
{
  LPC_SYSCON->PRESETCTRL = (LPC_SYSCON->PRESETCTRL & ~(1 << bit)) | (!reset ? 1 << bit : 0);
}

INLINE void rom_setup (int on) { set_clock (1, on); }

INLINE void ram_setup (int on) { set_clock (2, on); }

INLINE void flash_timing_setup (int clock)
{
  int ws = 0;
  if (clock > 45e6) ERROR("Clock frequency too high (> 45 Mhz).");
  if (clock > 30e6) ws = 1;
  else ws = 0;
  if (ws) {
    LPC_FLASHCTRL->FLASHCFG = (LPC_FLASHCTRL->FLASHCFG & ~(3)) | (ws);
    LPC_SYSCON->PRESETCTRL = (LPC_SYSCON->PRESETCTRL & ~(1 << 15)) | (0 ? 1 << 15 : 0);
  } else {
    LPC_SYSCON->PRESETCTRL = (LPC_SYSCON->PRESETCTRL & ~(1 << 15)) | (1 ? 1 << 15 : 0);
  }
}

INLINE void flash_registers_setup (int on) { set_clock (3, on); }

INLINE void flash_array_setup (int on) { set_clock (4, on); }

INLINE void i2c_system_setup (int on)
{
  set_reset (1, 1);
  set_clock (5, on);
  set_reset (1, !on);
}

INLINE void crc_setup (int on) { set_reset (9, 1); set_clock (6, on); set_reset (9, !on); }

INLINE void ct16b0_setup (int on) { set_reset (4, 1); set_clock (7, on); set_reset (4, !on); }

INLINE void ct16b1_setup (int on) { set_reset (5, 1); set_clock (8, on); set_reset (5, !on); }

INLINE void ct32b0_setup (int on) { set_reset (6, 1); set_clock (9, on); set_reset (6, !on); }

INLINE void ct32b1_setup (int on) { set_reset (7, 1); set_clock (10, on); set_reset (7, !on); }

INLINE void iocon_setup (int on) { set_clock (16, on); }

INLINE void dma_setup (int on) { set_reset (10, 1); set_clock (17, on); set_reset (10, !on); }

INLINE void rtc_setup (int on) { set_clock (19, on); }

INLINE void cmp_setup (int on) { set_power (15, on); set_reset (8, 1); set_clock (20, on); set_reset (8, !on); }

INLINE void gpio0_setup (int on) { set_clock (29, on); }

INLINE void gpio1_setup (int on) { set_clock (30, on); }

INLINE void gpio2_setup (int on) { set_clock (31, on); }

INLINE void irc_setup (int on) { set_power (1, on); set_power (0, on); }

INLINE void flash_setup (int on) { set_power (2, on); }

INLINE void bod_setup (int on, int reset, float reset_level, float int_level)
{
  set_power (3, on);
  int rlvl = 0, ilvl = 0;
  if (reset_level == 0) rlvl = 0;
  else if (reset_level == 2.038f) rlvl = 1;
  else if (reset_level == 2.336f) rlvl = 2;
  else if (reset_level == 2.624f) rlvl = 3;
  else ERROR ("Invalid BOD reset level.");
  if (int_level == 0) ilvl = 0;
  else if (int_level == 2.248f) ilvl = 1;
  else if (int_level == 2.541f) ilvl = 2;
  else if (int_level == 2.828f) ilvl = 3;
  else ERROR ("Invalid BOD interrupt level.");
  LPC_SYSCON->BODCTRL = (rlvl << 0) | (ilvl << 2) | (reset ? 1 << 4 : 0);
}

enum {
  OSC_BYPASS,
};

INLINE void sysosc_setup (int freq)
{
  if (freq == 0) {
    set_power (5, 0);
  } else {
    set_power (5, 1);
    if (freq == OSC_BYPASS) {
      LPC_SYSCON->SYSOSCCTRL = (1 << 0);
    } else if (freq < 1e6) {
      ERROR("System oscillator frequency too high [> 25 MHz].");
    } else if (freq < 17e6) {
      LPC_SYSCON->SYSOSCCTRL = (0 << 1);
    } else if (freq <= 25e6) {
      LPC_SYSCON->SYSOSCCTRL = (1 << 1);
    } else {
      ERROR("System oscillator frequency too high [> 25 MHz].");
    }
  }
}

INLINE void wdtosc_setup (int clk, int div) {
  set_power (6, clk ? 1 : 0);
  int freq;
  if (div < 2 || div > 64) ERROR("Watchdog clock divider value out of range [2-64].");
  if (div % 2) ERROR("Watchdog clock divider must be even.");
  div = div / 2 - 1;
  if (clk) {
    if (clk == 0.5) freq = 1;
    else if (clk == 0.8) freq = 2;
    else if (clk == 1.1) freq = 3;
    else if (clk == 1.4) freq = 4;
    else if (clk == 1.6) freq = 5;
    else if (clk == 1.8) freq = 6;
    else if (clk == 2.0) freq = 7;
    else if (clk == 2.2) freq = 8;
    else if (clk == 2.4) freq = 9;
    else if (clk == 2.6) freq = 10;
    else if (clk == 2.7) freq = 11;
    else if (clk == 2.9) freq = 12;
    else if (clk == 3.1) freq = 13;
    else if (clk == 3.2) freq = 14;
    else if (clk == 3.4) freq = 15;
    else ERROR ("Invalid watchdog oscillator frequency.");
  }
  LPC_SYSCON->WDTOSCCTRL = div << 0 | freq << 5;
}

enum clock_source {
  CLK_OFF = -2,
  KEEP_SRC = -1,
  OSC_IRC,
  CLK_MAIN,
  PLL_SYS,
  PLL_SYS_IN,
  PLL_USB,
  OSC_WDT,
  OSC_SYS,
};

INLINE void pll_setup_shared (int in, int out, volatile uint32_t *reg)
{
  int mul = out / in;
  if (mul * in != out) ERROR("PLL output frequency is not divisible by input frequency.");
  if (mul < 1 || mul > 32) ERROR("Required system PLL frequency multiplier value out of range [1-32].");
  if (out > 100e6) ERROR("PLL output frequency too high [out > 100 MHz].");
  int div;
  if (out * 2 > 156e6) div = 2;
  else if (out * 4 > 156e6) div = 4;
  else if (out * 8 > 156e6) div = 8;
  else if (out * 16 > 156e6) div = 16;
  else ERROR("Output frequency too low for the CCO [156 < F_CCO < 320].");
  if (out * div > 320e6) ERROR("CCO frequency too high [156 < F_CC0 < 320].");
  mul--;
  div = div / 2;
  if (div == 1) div = 0;
  else if (div == 2) div = 1;
  else if (div == 4) div = 2;
  else if (div == 8) div = 3;
  else ERROR ("Invalid PLL post divider.");
  *reg = mul << 0 | div << 5;
}

INLINE void syspll_setup (int on, enum clock_source src, int in, int out)
{
  set_power (7, 0);
  if (!on) return;
  pll_setup_shared (in, out, &LPC_SYSCON->SYSPLLCTRL);
  int s = 0;
  switch (src) {
    case OSC_IRC: s = 0; break;
    case OSC_SYS: s = 1; break;
    case KEEP_SRC: s = -1; break;
    default: ERROR("Invalid clock source.");
  }
  if (s != -1) {
    LPC_SYSCON->SYSPLLCLKSEL = s;
    LPC_SYSCON->SYSPLLCLKUEN = 0;
    LPC_SYSCON->SYSPLLCLKUEN = 1;
  }
  set_power (7, 1);
  while (!LPC_SYSCON->SYSPLLSTAT);
}

INLINE void system_clock_setup (enum clock_source src, int div)
{
  if (div < 0 || div > 255) ERROR("System (AHB) clock divider value out of range [0-255].");
  int s = 0;
  switch (src) {
    case OSC_IRC: s = 0; break;
    case PLL_SYS_IN: s = 1; break;
    case OSC_WDT: s = 2; break;
    case PLL_SYS: s = 3; break;
    case KEEP_SRC: s = -1; break;
    default: ERROR("Invalid clock source.");
  }
  if (s != -1) {
    LPC_SYSCON->SYSAHBCLKDIV = 255;
    LPC_SYSCON->MAINCLKSEL = s;
    LPC_SYSCON->MAINCLKUEN = 0;
    LPC_SYSCON->MAINCLKUEN = 1;
  }
  LPC_SYSCON->SYSAHBCLKDIV = div;
}

INLINE void rtc_clock_setup (enum clock_source src, int div)
{
  ERROR("Not implemented");
}

INLINE void clkout_setup (enum clock_source src, int div)
{
  if (div < 0 || div > 255) ERROR("CLKOUT divider value out of range [0-255].");
  int s = 0;
  LPC_SYSCON->CLKOUTDIV = div;
  switch (src) {
    case OSC_IRC: s = 0; break;
    case OSC_SYS: s = 1; break;
    case OSC_WDT: s = 2; break;
    case CLK_MAIN: s = 3; break;
    case KEEP_SRC: s = -1; break;
    default: ERROR("Invalid clock source.");
  }
  if (s != -1) {
    LPC_SYSCON->CLKOUTCLKSEL = s;
    LPC_SYSCON->CLKOUTUEN = 0;
    LPC_SYSCON->CLKOUTUEN = 1;
  }
}

#if 0 // TODO
INLINE void wdt_setup (enum clock_source src, int div)
{
  if (div < 0 || div > 255) ERROR("Watchdog clock divider value out of range [0-255].");
  set_clock (15, div ? 1 : 0);
  int s = 0;
  LPC_SYSCON->WDTCLKDIV = div;
  switch (src) {
    case OSC_IRC: s = 0; break;
    case CLK_MAIN: s = 1; break;
    case OSC_WDT: s = 2; break;
    case KEEP_SRC: s = -1; break;
    default: ERROR("Invalid clock source.");
  }
  if (s != -1) {
    LPC_SYSCON->WDTCLKSEL = s;
    LPC_SYSCON->WDTCLKUEN = 0;
    LPC_SYSCON->WDTCLKUEN = 1;
  }
}
#endif

INLINE void wdt_feed (void)
{
  LPC_WWDT->FEED = 0xAA;
  LPC_WWDT->FEED = 0x55;
}

INLINE void wdt_setup (int on)
{
  wdt_feed();
  LPC_WWDT->MOD = (LPC_WWDT->MOD & ~(1 << 0)) | (on ? 1 << 0 : 0);
  wdt_feed();
}

INLINE void uart0_clock_setup (int div)
{
  if (div < 0 || div > 255) ERROR("UART0 clock divider value out of range [0-255].");
  set_reset (2, 1);
  set_clock (12, div ? 1 : 0);
  LPC_SYSCON->UART0CLKDIV = div;
  set_reset (2, div ? 0 : 1);
}

INLINE void uart1_clock_setup (int div)
{
  if (div < 0 || div > 255) ERROR("UART1 clock divider value out of range [0-255].");
  set_reset (3, 1);
  set_clock (13, div ? 1 : 0);
  LPC_SYSCON->UART1CLKDIV = div;
  set_reset (3, div ? 0 : 1);
}

INLINE void ssp_clock_setup (int div)
{
  if (div < 0 || div > 255) ERROR("SSP clock divider value out of range [0-255].");
  set_reset (0, 1);
  set_clock (11, div ? 1 : 0);
  LPC_SYSCON->SSPCLKDIV = div;
  set_reset (0, div ? 0 : 1);
}

INLINE void adc_system_setup (int on) { set_power (4, on); set_clock (14, on); }

enum memory_map {
  MEMORY_MAP_BOOT  = 0,
  MEMORY_MAP_RAM   = 1,
  MEMORY_MAP_FLASH = 2,
};

INLINE void memory_map_setup (enum memory_map map)
{
  LPC_SYSCON->SYSMEMREMAP = map;
}

#endif // SYSTEM_H