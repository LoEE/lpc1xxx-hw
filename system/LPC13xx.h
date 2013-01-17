/*
   System configuration functions for the LPC13xx processors.

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

INLINE void rom_setup (int on) { set_clock (1, on); }

INLINE void ram_setup (int on) { set_clock (2, on); }

#define FLASHCFG (*(volatile uint32_t *)(0x4003C010))

INLINE void flash_timing_setup (int clock)
{
  int t = 0;
  if (clock > 72e6) ERROR("Clock frequency too high (> 72 Mhz).");
  if (clock > 40e6) t = 2;
  else if (clock > 20e6) t = 1;
  else t = 0;
  FLASHCFG = (FLASHCFG & ~(3)) | (t);
}

INLINE void flash_registers_setup (int on) { set_clock (3, on); }

INLINE void flash_array_setup (int on) { set_clock (4, on); }

INLINE void i2c_system_setup (int on)
{
  set_clock (5, on);
  LPC_SYSCON->PRESETCTRL = (LPC_SYSCON->PRESETCTRL & ~(1 << 1)) | (on ? 1 << 1 : 0);
}

INLINE void gpio_setup (int on) { set_clock (6, on); }

INLINE void ct16b0_setup (int on) { set_clock (7, on); }

INLINE void ct16b1_setup (int on) { set_clock (8, on); }

INLINE void ct32b0_setup (int on) { set_clock (9, on); }

INLINE void ct32b1_setup (int on) { set_clock (10, on); }

INLINE void iocon_setup (int on) { set_clock (16, on); }

INLINE void irc_setup (int on) { set_power (1, on); set_power (0, on); }

INLINE void flash_setup (int on) { set_power (2, on); }

INLINE void bod_setup (int on, int reset, float int_level)
{
  set_power (3, on);
  int lvl = 0;
  if (int_level == 1.69f) lvl = 0;
  else if (int_level == 2.29f) lvl = 1;
  else if (int_level == 2.59f) lvl = 2;
  else if (int_level == 2.87f) lvl = 3;
  else ERROR ("Invalid BOD interrupt level.");
  LPC_SYSCON->BODCTRL = (lvl << 2) | (reset ? 1 << 4 : 0);
}

enum sysosc_mode {
  SYSOSC_OFF,
  SYSOSC_BYPASS,
  SYSOSC_SLOW,
  SYSOSC_FAST,
};

INLINE void sysosc_setup (enum sysosc_mode range)
{
  if (range == SYSOSC_OFF) {
    set_power (5, 0);
  } else {
    set_power (5, 1);
    if (range == SYSOSC_BYPASS) LPC_SYSCON->SYSOSCCTRL = 1;
    else if (range == SYSOSC_SLOW) LPC_SYSCON->SYSOSCCTRL = 0;
    else if (range == SYSOSC_FAST) LPC_SYSCON->SYSOSCCTRL = 1 << 1;
    else ERROR ("Invalid system oscillator mode.");
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
  int div;
  if (out * 2 > 156e6) div = 2;
  else if (out * 4 > 156e6) div = 4;
  else if (out * 8 > 156e6) div = 8;
  else if (out * 16 > 156e6) div = 16;
  else ERROR("Output frequency too low for the CCO [156 < F_CCO < 320].");
  if (out * div > 320e6) ERROR("CCO frequency too high [156 < F_CC0 < 320].");
  mul--;
  div = div / 2 - 1;
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

#ifdef CPU_HAS_USB
INLINE void usbpll_setup (int on, enum clock_source src, int in, int out)
{
  set_power (8, 0);
  if (!on) return;
  pll_setup_shared (in, out, &LPC_SYSCON->USBPLLCTRL);
  int s = 0;
  switch (src) {
    case OSC_IRC: s = 0; break;
    case OSC_SYS: s = 1; break;
    case KEEP_SRC: s = -1; break;
    default: ERROR("Invalid clock source.");
  }
  if (s != -1) {
    LPC_SYSCON->USBPLLCLKSEL = s;
    LPC_SYSCON->USBPLLCLKUEN = 0;
    LPC_SYSCON->USBPLLCLKUEN = 1;
  }
  set_power (8, 1);
  while (!LPC_SYSCON->USBPLLSTAT);
}
#endif // CPU_HAS_USB

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

#ifdef CPU_HAS_USB
INLINE void usb_clock_setup (enum clock_source src, int div)
{
  if (div < 0 || div > 255) ERROR("USB clock divider value out of range [0-255].");
  set_power (10, div ? 1 : 0); set_clock (14, div ? 1 : 0);
  int s = 0;
  LPC_SYSCON->USBCLKDIV = div;
  switch (src) {
    case PLL_USB: s = 0; break;
    case CLK_MAIN: s = 1; break;
    case KEEP_SRC: s = -1; break;
    default: ERROR("Invalid clock source.");
  }
  if (s != -1) {
    LPC_SYSCON->USBCLKSEL = s;
    LPC_SYSCON->USBCLKUEN = 0;
    LPC_SYSCON->USBCLKUEN = 1;
  }
}
#endif // CPU_HAS_USB

INLINE void systick_clock_setup (int div)
{
  if (div < 0 || div > 255) ERROR("SYSTICK timer clock divider value out of range [0-255].");
  LPC_SYSCON->SYSTICKCLKDIV = div;
}

INLINE void trace_clock_setup (int div)
{
  if (div < 0 || div > 255) ERROR("ARM trace clock divider value out of range [0-255].");
  LPC_SYSCON->TRACECLKDIV = div;
}

INLINE void uart_clock_setup (int div)
{
  if (div < 0 || div > 255) ERROR("UART clock divider value out of range [0-255].");
  set_clock (12, div ? 1 : 0);
  LPC_SYSCON->UARTCLKDIV = div;
}

INLINE void ssp_clock_setup (int div)
{
  if (div < 0 || div > 255) ERROR("SSP clock divider value out of range [0-255].");
  set_clock (11, div ? 1 : 0);
  LPC_SYSCON->SSPCLKDIV = div;
  LPC_SYSCON->PRESETCTRL = (LPC_SYSCON->PRESETCTRL & ~(1 << 0)) | (div ? 1 << 0 : 0);
}

INLINE void adc_system_setup (int on) { set_power (4, on); set_clock (13, on); }

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