/*
   System configuration functions for the LPC15xx processors.

   This is an automatically generated file. For more details see:
       https://bitbucket.org/LoEE/lpc1xxx-hw/

   Copyright (c) 2010-2011 LoEE - Jakub Piotr Cłapa
   This program is released under the new BSD license.
*/
#ifndef SYSTEM_H
#define SYSTEM_H

INLINE void system_set_power (int bit, int on)
{
  LPC_SYSCON->PDRUNCFG = (LPC_SYSCON->PDRUNCFG & ~(1 << bit)) | (!on ? 1 << bit : 0);
}

INLINE void system_set_clock (int bit, int on)
{
  volatile uint32_t *reg = bit < 100 ? &LPC_SYSCON->SYSAHBCLKCTRL0 : &LPC_SYSCON->SYSAHBCLKCTRL1;
  if (bit >= 100) bit = bit - 100;
  (*reg) = ((*reg) & ~(1 << bit)) | (on ? 1 << bit : 0);
}

INLINE void system_periph_reset (int bit, int reset)
{
  volatile uint32_t *reg = bit < 100 ? &LPC_SYSCON->PRESETCTRL0 : &LPC_SYSCON->PRESETCTRL1;
  if (bit >= 100) bit = bit - 100;
  int preset = *reg;
  *reg = preset | 1 << bit;
  if(!reset)
    *reg = preset;
}

INLINE void rom_setup (int on) { system_set_clock (1, on); }

INLINE void sram1_setup (int on) { system_set_clock (3, on); }

INLINE void sram2_setup (int on) { system_set_clock (4, on); }

INLINE void eeprom_setup (int on) { system_set_clock (9, on); system_set_power(6, on); }

INLINE void mux_setup (int on) { system_set_clock (11, on); }

INLINE void swm_setup (int on) { system_set_clock (12, on); }

INLINE void iocon_setup (int on) { system_set_clock (13, on); }

INLINE void gpio0_setup (int on) { system_set_clock (14, on); }
INLINE void gpio1_setup (int on) { system_set_clock (15, on); }
INLINE void gpio2_setup (int on) { system_set_clock (16, on); }

INLINE void pint_setup (int on) { system_set_clock (18, on); }

INLINE void gint_setup (int on) { system_set_clock (19, on); }

INLINE void dma_setup (int on) { system_set_clock (20, on); }

INLINE void crc_setup (int on) { system_set_clock (21, on); }

INLINE void wwdt_setup (int on) { system_set_clock (22, on); }

INLINE void rtc_setup (int on) { system_set_clock (23, on); }

INLINE void adc0_setup (int on) { system_set_clock (27, on); system_set_power(10, on); }
INLINE void adc1_setup (int on) { system_set_clock (28, on); system_set_power(11, on); }

INLINE void dac_setup (int on) { system_set_clock (29, on); system_set_power(12, on); }

INLINE void acmp_clock_setup (int chn, int on) {
  if (chn < 0 || chn > 3) ERROR("Invalid ACMP number.");
  int v = LPC_SYSCON->PDRUNCFG;
  if (on) v |= 1 << chn; else v &= ~(1 << chn);
  LPC_SYSCON->PDRUNCFG = v;
  system_set_clock (30, v & (0xf << 13));
}

INLINE void mrt_setup (int on) { system_set_clock (100, on); }
INLINE void rit_setup (int on) { system_set_clock (101, on); }

INLINE void sct0_setup (int on) { system_set_clock (102, on); }
INLINE void sct1_setup (int on) { system_set_clock (103, on); }
INLINE void sct2_setup (int on) { system_set_clock (104, on); }
INLINE void sct3_setup (int on) { system_set_clock (105, on); }
INLINE void sctipu_setup (int on) { system_set_clock (106, on); }

INLINE void ccan_system_setup (int on) { system_set_clock (107, on); }

INLINE void spi0_setup (int on) { system_set_clock (109, on); }
INLINE void spi1_setup (int on) { system_set_clock (110, on); }

INLINE void i2c0_setup (int on) { system_set_clock (113, on); }

INLINE void uart0_setup (int on) { system_set_clock (117, on); system_periph_reset (117, !on); }
INLINE void uart1_setup (int on) { system_set_clock (118, on); system_periph_reset (118, !on); }
INLINE void uart2_setup (int on) { system_set_clock (119, on); system_periph_reset (119, !on); }

INLINE void qei_clock_setup (int on) { system_set_clock (121, on); }

INLINE void uart_clock_setup (int div) { LPC_SYSCON->UARTCLKDIV = div; }
INLINE void glitch_filter_clock_setup (int div) { LPC_SYSCON->IOCONCLKDIV = div; }
INLINE void adc_clock_setup (int div) { LPC_SYSCON->ADCASYNCCLKDIV = div; }

// frequency measure
// USB need_clock

INLINE void flash_setup (int clock)
{
  int ws = 0;
       if (clock > 72e6) ERROR("Clock frequency too high (> 72 Mhz).");
  else if (clock > 55e6) ws = 3;
  else if (clock > 25e6) ws = 2;
  else if (clock > 0) ws = 1;
  if (ws) {
    LPC_SYSCON->FLASHCFG = (LPC_SYSCON->FLASHCFG & ~(0x3 << 12)) | (ws - 1);
  }
  system_set_clock (7, ws > 0); system_set_power(5, ws > 0);
  LPC_SYSCON->PRESETCTRL0 = (LPC_SYSCON->PRESETCTRL0 & ~(1 << 7)) | (ws > 0 ? 1 << 7 : 0);
}

struct reset_reason {
  int power_on:1;
  int external:1;
  int watchdog:1;
  int brownout:1;
  int software:1;
};

INLINE
struct reset_reason clear_reset_reason (void) {
  int v = LPC_SYSCON->SYSRSTSTAT;
  LPC_SYSCON->SYSRSTSTAT = v;
  return (struct reset_reason) {
    .power_on = v & (1 << 0),
    .external = v & (1 << 1),
    .watchdog = v & (1 << 2),
    .brownout = v & (1 << 3),
    .software = v & (1 << 4),
  };
}

INLINE void bod_setup (int on, int reset, float reset_level, float int_level)
{
  system_set_power (3, on);
  int rlvl = 0, ilvl = 0;
  if (reset_level == 0) rlvl = 0;
  else if (reset_level == 2.55f) rlvl = 2;
  else if (reset_level == 2.83f) rlvl = 3;
  else ERROR ("Invalid BOD reset level.");
  if (int_level == 0) ilvl = 0;
  else if (int_level == 2.34f) ilvl = 2;
  else if (int_level == 2.64f) ilvl = 3;
  else ERROR ("Invalid BOD interrupt level.");
  LPC_SYSCON->BODCTRL = (rlvl << 0) | (ilvl << 2) | (reset ? 1 << 4 : 0);
}

enum {
  OSC_BYPASS,
};

INLINE void sysosc_setup (int freq)
{
  if (freq == 0) {
    system_set_power (21, 0);
  } else {
    system_set_power (21, 1);
    if (freq == OSC_BYPASS) {
      LPC_SYSCON->SYSOSCCTRL = (1 << 0);
    } else if (freq < 1e6) {
      ERROR("System oscillator frequency too low [< 1 MHz].");
    } else if (freq < 17e6) {
      LPC_SYSCON->SYSOSCCTRL = (0 << 1);
    } else if (freq <= 25e6) {
      LPC_SYSCON->SYSOSCCTRL = (1 << 1);
    } else {
      ERROR("System oscillator frequency too high [> 25 MHz].");
    }
  }
}

enum clock_source {
  CLK_OFF = -2,
  KEEP_SRC = -1,
  OSC_IRC,
  CLK_MAIN,
  PLL_SYS,
  PLL_SYS_IN,
  PLL_USB,
  PLL_SCT,
  OSC_WDT,
  OSC_SYS,
  OSC_RTC,
};

INLINE void clkout_setup (enum clock_source src, int div)
{
  if (div < 0 || div > 255) ERROR("CLKOUT divider value out of range [0-255].");
  LPC_SYSCON->CLKOUTDIV = 0;
  int s = 0;
  switch (src) {
    case OSC_IRC: s = 0; break;
    case OSC_SYS: s = 1; break;
    case OSC_WDT: s = 2; break;
    case CLK_MAIN: s = 3; break;
    case PLL_USB: s = 0x11; break;
    case PLL_SCT: s = 0x12; break;
    case OSC_RTC: s = 0x13; break;
    case KEEP_SRC: s = -1; break;
    default: ERROR("Invalid clock source.");
  }
  if (s != -1) {
    if (s < 0x10) {
      LPC_SYSCON->CLKOUTSELA = s;
      LPC_SYSCON->CLKOUTSELB = 0;
    } else {
      LPC_SYSCON->CLKOUTSELB = s - 0x10;
    }
  }
  LPC_SYSCON->CLKOUTDIV = div;
}

INLINE void pll_setup_shared (int in, int out, volatile uint32_t *reg)
{
  int mul = out / in;
  if (mul * in != out) ERROR("PLL output frequency is not divisible by input frequency.");
  if (mul < 1 || mul > 64) ERROR("Required system PLL frequency multiplier value out of range [1-64].");
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
  *reg = mul << 0 | div << 6;
}

INLINE void syspll_setup (int on, enum clock_source src, int in, int out)
{
  system_set_power (22, 0);
  if (!on) return;
  pll_setup_shared (in, out, &LPC_SYSCON->SYSPLLCTRL);
  int s = 0;
  switch (src) {
    case OSC_IRC: s = 0; break;
    case OSC_SYS: s = 1; break;
    case KEEP_SRC: s = -1; break;
    default: ERROR("Invalid clock source.");
  }
  if (s != -1) LPC_SYSCON->SYSPLLCLKSEL = s;
  system_set_power (22, 1);
  while (!LPC_SYSCON->SYSPLLSTAT);
}

INLINE void usbpll_setup (int on, enum clock_source src, int in, int out)
{
  system_set_power (23, 0);
  if (!on) return;
  pll_setup_shared (in, out, &LPC_SYSCON->USBPLLCTRL);
  int s = 0;
  switch (src) {
    case OSC_IRC: s = 0; break;
    case OSC_SYS: s = 1; break;
    case KEEP_SRC: s = -1; break;
    default: ERROR("Invalid clock source.");
  }
  if (s != -1) LPC_SYSCON->USBPLLCLKSEL = s;
  system_set_power (23, 1);
  while (!LPC_SYSCON->USBPLLSTAT);
}

INLINE void sctpll_setup (int on, enum clock_source src, int in, int out)
{
  system_set_power (24, 0);
  if (!on) return;
  pll_setup_shared (in, out, &LPC_SYSCON->SCTPLLCTRL);
  int s = 0;
  switch (src) {
    case OSC_IRC: s = 0; break;
    case OSC_SYS: s = 1; break;
    case KEEP_SRC: s = -1; break;
    default: ERROR("Invalid clock source.");
  }
  if (s != -1) LPC_SYSCON->SCTPLLCLKSEL = s;
  system_set_power (24, 1);
  while (!LPC_SYSCON->SCTPLLSTAT);
}

INLINE void system_clock_setup (enum clock_source src, int div)
{
  if (div < 0 || div > 255) ERROR("Main clock divider. value out of range [0-255].");
  int s = 0;
  switch (src) {
    case OSC_IRC: s = 0; break;
    case OSC_SYS: s = 1; break;
    case OSC_WDT: s = 2; break;
    case PLL_SYS_IN: s = 0x11; break;
    case PLL_SYS: s = 0x12; break;
    case OSC_RTC: s = 0x13; break;
    case KEEP_SRC: s = -1; break;
    default: ERROR("Invalid clock source.");
  }
  if (s != -1) {
    LPC_SYSCON->SYSAHBCLKDIV = 255;
    if (s < 0x10) {
      LPC_SYSCON->MAINCLKSELA = s;
      LPC_SYSCON->MAINCLKSELB = 0;
    } else {
      LPC_SYSCON->MAINCLKSELB = s - 0x10;
    }
  }
  LPC_SYSCON->SYSAHBCLKDIV = div;
}

INLINE void usb_system_setup (enum clock_source src, int div) {
  system_set_power(9, div != 0);
  system_set_clock (123, 0);
  if (!div) return;
  int s = 0;
  switch (src) {
    case OSC_IRC: s = 0; break;
    case OSC_SYS: s = 1; break;
    case PLL_USB: s = 2; break;
    case CLK_MAIN: s = 3; break;
    case KEEP_SRC: s = -1; break;
    default: ERROR("Invalid clock source.");
  }
  if (s != -1) {
    LPC_SYSCON->USBCLKDIV = 255;
    LPC_SYSCON->USBCLKSEL = s;
  }
  system_set_clock (123, div != 0);
  LPC_SYSCON->USBCLKDIV = div;
}

#if 0
INLINE void wdtosc_setup (int clk, int div) {
  system_set_power (6, clk ? 1 : 0);
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

INLINE void rtc_clock_setup (enum clock_source src, int div)
{
  ERROR("Not implemented");
}

#if 0 // TODO
INLINE void wdt_setup (enum clock_source src, int div)
{
  if (div < 0 || div > 255) ERROR("Watchdog clock divider value out of range [0-255].");
  system_set_clock (15, div ? 1 : 0);
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
  system_set_clock (12, div ? 1 : 0);
  LPC_SYSCON->UART0CLKDIV = div;
  set_reset (2, div ? 0 : 1);
}

INLINE void uart1_clock_setup (int div)
{
  if (div < 0 || div > 255) ERROR("UART1 clock divider value out of range [0-255].");
  set_reset (3, 1);
  system_set_clock (13, div ? 1 : 0);
  LPC_SYSCON->UART1CLKDIV = div;
  set_reset (3, div ? 0 : 1);
}

INLINE void ssp_clock_setup (int div)
{
  if (div < 0 || div > 255) ERROR("SSP clock divider value out of range [0-255].");
  set_reset (0, 1);
  system_set_clock (11, div ? 1 : 0);
  LPC_SYSCON->SSPCLKDIV = div;
  set_reset (0, div ? 0 : 1);
}

INLINE void adc_system_setup (int on) { system_set_power (4, on); system_set_clock (14, on); }

enum memory_map {
  MEMORY_MAP_BOOT  = 0,
  MEMORY_MAP_RAM   = 1,
  MEMORY_MAP_FLASH = 2,
};

INLINE void memory_map_setup (enum memory_map map)
{
  LPC_SYSCON->SYSMEMREMAP = map;
}
#endif

#endif // SYSTEM_H