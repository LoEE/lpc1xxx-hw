/*
   System configuration functions for the LPC17xx processors.

   This is an automatically generated file. For more details see:
       https://bitbucket.org/LoEE/lpc1xxx-hw/

   Copyright (c) 2010-2011 LoEE - Jakub Piotr Cłapa
   This program is released under the new BSD license.
*/
#ifndef SYSTEM_H
#define SYSTEM_H


enum sysosc_mode {
  SYSOSC_OFF,
  SYSOSC_SLOW,
  SYSOSC_FAST,
};

INLINE void sysosc_setup (enum sysosc_mode range)
{
  if (range == SYSOSC_OFF) {
    LPC_SC->SCS = (LPC_SC->SCS & ~(1 << 5)) | (0 ? 1 << 5 : 0);
  } else {
    int t = 1 << 5;
    if (range == SYSOSC_FAST) {
      t |= 1 << 4;
    }
    LPC_SC->SCS = t;
    while (!(LPC_SC->SCS & (1 << 6)));
  }
}

enum clock_source {
  CLK_OFF = -2,
  KEEP_SRC = -1,
  OSC_IRC,
  OSC_SYS,
  OSC_RTC,
};

INLINE void system_clock_source_setup (enum clock_source src)
{
  int s = 0;
  switch (src) {
    case OSC_IRC: s = 0; break;
    case OSC_SYS: s = 1; break;
    case OSC_RTC: s = 2; break;
    case KEEP_SRC: s = -1; break;
    default: ERROR("Invalid clock source.");
  }
  if (s != -1) {
    LPC_SC->CLKSRCSEL = s;
  }
}

INLINE void cpu_clock_divider_setup (int div)
{
  if (div < 1 || div > 256) ERROR("CPU clock divider value out of range [1-256].");
  LPC_SC->CCLKCFG = div - 1;
}

INLINE void usb_clock_divider_setup (int div)
{
  switch(div) {
    case 6:
    case 8:
    case 10:
      LPC_SC->USBCLKCFG = div - 1; break;
    default:
      ERROR("Invalid USB clock divider (not 6, 8 or 10)."); break;
  }
}

INLINE void pll_setup_shared (int in, int out, int evenpost, volatile uint32_t *reg, volatile uint32_t *postdivreg)
{
  int mul = 0, prediv = 0, postdiv = 0, ok = 0;
#define PLL_SETUP_PREDIV_CHECK(p) ({                                   \
    prediv = p;                                                        \
    mul = out * prediv / in / 2;                                       \
    double freq = in * mul * 2 / prediv;                               \
    postdiv = (275000000 + freq - 1) / freq;                           \
    if (evenpost) postdiv = (postdiv + 1) / 2 * 2;                     \
    mul *= postdiv;                                                    \
    if (in * mul * 2 / prediv < 550000000)                             \
      if (in * mul * 2 / prediv / postdiv == out) { ok = 1; goto ok; } \
  })
  PLL_SETUP_PREDIV_CHECK(1);
  PLL_SETUP_PREDIV_CHECK(2);
  PLL_SETUP_PREDIV_CHECK(3);
  PLL_SETUP_PREDIV_CHECK(4);
  PLL_SETUP_PREDIV_CHECK(5);
  PLL_SETUP_PREDIV_CHECK(6);
  PLL_SETUP_PREDIV_CHECK(7);
  PLL_SETUP_PREDIV_CHECK(8);
  PLL_SETUP_PREDIV_CHECK(9);
  PLL_SETUP_PREDIV_CHECK(10);
  PLL_SETUP_PREDIV_CHECK(11);
  PLL_SETUP_PREDIV_CHECK(12);
  PLL_SETUP_PREDIV_CHECK(13);
  PLL_SETUP_PREDIV_CHECK(14);
  PLL_SETUP_PREDIV_CHECK(15);
  PLL_SETUP_PREDIV_CHECK(16);
  PLL_SETUP_PREDIV_CHECK(17);
  PLL_SETUP_PREDIV_CHECK(18);
  PLL_SETUP_PREDIV_CHECK(19);
  PLL_SETUP_PREDIV_CHECK(20);
  PLL_SETUP_PREDIV_CHECK(21);
  PLL_SETUP_PREDIV_CHECK(22);
  PLL_SETUP_PREDIV_CHECK(23);
  PLL_SETUP_PREDIV_CHECK(24);
  PLL_SETUP_PREDIV_CHECK(25);
  PLL_SETUP_PREDIV_CHECK(26);
  PLL_SETUP_PREDIV_CHECK(27);
  PLL_SETUP_PREDIV_CHECK(28);
  PLL_SETUP_PREDIV_CHECK(29);
  PLL_SETUP_PREDIV_CHECK(30);
  PLL_SETUP_PREDIV_CHECK(31);
  PLL_SETUP_PREDIV_CHECK(32);
#undef PLL_SETUP_PREDIV_CHECK
  if(!ok) ERROR("The PLL cannot synthesize the desired output frequency.");
ok:
  if (mul < 6 || mul > 512) ERROR("Required PLL frequency multiplier value out of range [6-512].");
  if (postdiv < 1 || postdiv > 256) ERROR("Required PLL post divider value out of range [1-256].");
  mul--; prediv--; postdiv--;
  *reg = mul << 0 | prediv << 16;
  *postdivreg = postdiv;
}

INLINE void syspll_feed (void)
{
  LPC_SC->PLL0FEED = 0xAA;
  LPC_SC->PLL0FEED = 0x55;
}

INLINE void syspll_connect (int on)
{
  LPC_SC->PLL0CON = (LPC_SC->PLL0CON & ~(1 << 1)) | (on ? 1 << 1 : 0);
  syspll_feed();
}

INLINE void syspll_power (int on)
{
  syspll_connect(0);
  LPC_SC->PLL0CON = (LPC_SC->PLL0CON & ~(1 << 0)) | (on ? 1 << 0 : 0);
  syspll_feed();
}

INLINE int syspll_locked (void)
{
  return LPC_SC->PLL0STAT & (1 << 26);
}

INLINE void syspll_setup (int in, int out)
{
  syspll_power(0);
  if (out == 0) return;
  pll_setup_shared (in, out, 0, &LPC_SC->PLL0CFG, &LPC_SC->CCLKCFG);
  syspll_feed();
  syspll_power(1);
  while (!syspll_locked());
  syspll_connect(1);
}

INLINE void set_power (int bit, int on)
{
  LPC_SC->PCONP = (LPC_SC->PCONP & ~(1 << bit)) | (on ? 1 << bit : 0);
}

INLINE void set_pclk (int shift, int div)
{
  if(div == 0) return;
  if(shift & 1 || shift == 10 || shift == 18 || shift == 40)
    ERROR("Invalid PCLK divider register shift.");
  if(shift == 18 && div != 4)
    ERROR("RTC PCLK can only be divided by 4.");
  int is_can = (shift == 26 || shift == 28 || shift == 30);
  switch (div) {
    case 1: break;
    case 2: break;
    case 4: div = 0; break;
    case 6:
      if(!is_can)
        ERROR("PCLK division by 6 is only possible for CAN");
      div = 3;
      break;
    case 8:
      if(is_can)
        ERROR("PCLK division by 8 is not possible for CAN");
      div = 3;
      break;
    default:
      if(is_can)
        ERROR("Invalid PCLK divider value for CAN (not 1, 2, 4 or 6)");
      else
        ERROR("Invalid PCLK divider value (not 1, 2, 4 or 8)");
  }
  if (shift < 32)
    LPC_SC->PCLKSEL0 = (LPC_SC->PCLKSEL0 & ~(3 << shift)) | (div << shift);
  else {
    shift -= 32;
    LPC_SC->PCLKSEL1 = (LPC_SC->PCLKSEL1 & ~(3 << shift)) | (div << shift);
  }
}

INLINE void wdt_pclk_setup (int div) { set_pclk (1, div); }
INLINE void timer0_pclk_setup (int div) { set_power (1, div != 0); set_pclk (2, div); }
INLINE void timer1_pclk_setup (int div) { set_power (2, div != 0); set_pclk (4, div); }
INLINE void uart0_pclk_setup (int div) { set_power (3, div != 0); set_pclk (6, div); }
INLINE void uart1_pclk_setup (int div) { set_power (4, div != 0); set_pclk (8, div); }
INLINE void pwm1_pclk_setup (int div) { set_power (6, div != 0); set_pclk (12, div); }
INLINE void i2c0_pclk_setup (int div) { set_power (7, div != 0); set_pclk (14, div); }
INLINE void spi_pclk_setup (int div) { set_power (8, div != 0); set_pclk (16, div); }
INLINE void rtc_pclk_setup (int div) { set_power (9, div != 0); set_pclk (18, div); }
INLINE void ssp1_pclk_setup (int div) { set_power (10, div != 0); set_pclk (20, div); }
INLINE void dac_pclk_setup (int div) { set_pclk (22, div); }
INLINE void adc_pclk_setup (int div) { set_power (12, div != 0); set_pclk (24, div); }
INLINE void can1_pclk_setup (int div) { set_power (13, div != 0); set_pclk (26, div); }
INLINE void can2_pclk_setup (int div) { set_power (14, div != 0); set_pclk (28, div); }
INLINE void can_acf_pclk_setup (int div) { set_pclk (30, div); }
INLINE void gpio_pclk_setup (int div) { set_power (15, div != 0); set_pclk (34, div); set_pclk (36, div); }
INLINE void rit_pclk_setup (int div) { set_power (16, div != 0); set_pclk (58, div); }
INLINE void mcpwm_pclk_setup (int div) { set_power (17, div != 0); set_pclk (62, div); }
INLINE void qei_pclk_setup (int div) { set_power (18, div != 0); set_pclk (32, div); }
INLINE void i2c1_pclk_setup (int div) { set_power (19, div != 0); set_pclk (38, div); }
INLINE void ssp0_pclk_setup (int div) { set_power (21, div != 0); set_pclk (42, div); }
INLINE void timer2_pclk_setup (int div) { set_power (22, div != 0); set_pclk (44, div); }
INLINE void timer3_pclk_setup (int div) { set_power (23, div != 0); set_pclk (46, div); }
INLINE void uart2_pclk_setup (int div) { set_power (24, div != 0); set_pclk (48, div); }
INLINE void uart3_pclk_setup (int div) { set_power (25, div != 0); set_pclk (50, div); }
INLINE void i2c2_pclk_setup (int div) { set_power (26, div != 0); set_pclk (52, div); }
INLINE void i2s_pclk_setup (int div) { set_power (27, div != 0); set_pclk (54, div); }
INLINE void dma_pclk_setup (int div) { set_power (29, div != 0); }
INLINE void enet_pclk_setup (int div) { if(div != 0 && div != 1) ERROR("Ethernet clock cannot be divided, only disabled."); set_power (30, div != 0); }
INLINE void usb_pclk_setup (int div) { set_power (31, div != 0); }
INLINE void syscon_pclk_setup (int div) { if(div == 0) ERROR("SYSCON PCLK cannot be disabled."); set_pclk (60, div); }

#endif // SYSTEM_H
