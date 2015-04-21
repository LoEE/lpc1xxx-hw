#lang at-exp racket
(require scribble/text
         "common.rkt")

(define output-dir "../system")

(define (main)
  (parameterize ([current-directory output-dir])
    (with-output-to-file "LPC15xx.h" #:exists 'replace
      (λ () (output (generate-15xx-system))))))

(define (decl name . args)
  @list{INLINE void @|name|_setup (@(add-newlines #:sep ", " args))})

(define (clksrc-switch arg var options)
  @list{switch (@arg) {
          @(for/nl ([opt (in-list options)])
             @list{case @(car opt): @var = @(cdr opt); break;})
          case KEEP_SRC: @var = -1; break;
          default: ERROR("Invalid clock source.");
        }})

(define (check-range min var max desc)
  @list{if (@var < @min || @var > @max) ERROR("@desc value out of range [@|min|-@|max|].");})

(define (set/mask reg mask val)
  @list{@reg = (@reg & ~(@mask)) | (@val);})

(define (set/bit reg bit val)
  (set/mask reg @list{1 << @bit} @list{@val ? 1 << @bit : 0}))

(define (assoc/if in out error pairs)
  @list{@(add-newlines #:sep "\nelse "
           (for/list ([p (in-list pairs)])
             @list{if (@in == @(car p)) @out = @(cdr p);}))
        else ERROR ("@error");})

(define (generate-15xx-system)
  @list{
@header[url]{System configuration functions for the LPC15xx processors.}
@cpp-wrap['SYSTEM]{
INLINE void system_set_power (int bit, int on)
{
  @(set/bit 'LPC_SYSCON->PDRUNCFG 'bit "!on")
}

INLINE void system_set_clock (int bit, int on)
{
  volatile uint32_t *reg = bit < 100 ? &LPC_SYSCON->SYSAHBCLKCTRL0 : &LPC_SYSCON->SYSAHBCLKCTRL1;
  if (bit >= 100) bit = bit - 100;
  @(set/bit "(*reg)" 'bit "on")
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

@(decl 'rom "int on") { system_set_clock (1, on); }

@(decl 'sram1 "int on") { system_set_clock (3, on); }

@(decl 'sram2 "int on") { system_set_clock (4, on); }

@(decl 'flash "int on") { system_periph_reset (7, !on); }

@(decl 'eeprom "int on") { system_set_clock (9, on); system_set_power(6, on); system_periph_reset (9, !on); }

@(decl 'mux "int on") { system_set_clock (11, on); system_periph_reset (11, !on); }

@(decl 'swm "int on") { system_set_clock (12, on); }

@(decl 'iocon "int on") { system_set_clock (13, on); system_periph_reset (13, !on); }

@(decl 'gpio0 "int on") { system_set_clock (14, on); }
@(decl 'gpio1 "int on") { system_set_clock (15, on); }
@(decl 'gpio2 "int on") { system_set_clock (16, on); }

@(decl 'pint "int on") { system_set_clock (18, on); system_periph_reset (18, !on); }

@(decl 'gint "int on") { system_set_clock (19, on); system_periph_reset (19, !on); }

@(decl 'dma "int on") { system_set_clock (20, on); system_periph_reset (20, !on); }

@(decl 'crc "int on") { system_set_clock (21, on); system_periph_reset (21, !on); }

@(decl 'wwdt "int on") { system_set_clock (22, on); }

@(decl 'rtc "int on") { system_set_clock (23, on); }

@(decl 'adc0 "int on") { system_set_clock (27, on); system_set_power(10, on); system_periph_reset (27, !on); }
@(decl 'adc1 "int on") { system_set_clock (28, on); system_set_power(11, on); system_periph_reset (28, !on); }

@(decl 'dac "int on") { system_set_clock (29, on); system_set_power(12, on); }

@(decl 'acmp_clock "int chn" "int on") {
  if (chn < 0 || chn > 3) ERROR("Invalid ACMP number.");
  int v = LPC_SYSCON->PDRUNCFG;
  if (on) v |= 1 << chn; else v &= ~(1 << chn);
  LPC_SYSCON->PDRUNCFG = v;
  system_set_clock (30, v & (0xf << 13));
  system_periph_reset (30, !on);
}

@(decl 'mrt "int on") { system_set_clock (100, on); system_periph_reset (100, !on); }
@(decl 'rit "int on") { system_set_clock (101, on); system_periph_reset (101, !on); }

@(decl 'sct0 "int on") { system_set_clock (102, on); system_periph_reset (102, !on); }
@(decl 'sct1 "int on") { system_set_clock (103, on); system_periph_reset (103, !on); }
@(decl 'sct2 "int on") { system_set_clock (104, on); system_periph_reset (104, !on); }
@(decl 'sct3 "int on") { system_set_clock (105, on); system_periph_reset (105, !on); }
@(decl 'sctipu "int on") { system_set_clock (106, on); system_periph_reset (106, !on); }

@(decl 'ccan_system "int on") { system_set_clock (107, on); system_periph_reset (107, !on); }

@(decl 'spi0 "int on") { system_set_clock (109, on); system_periph_reset (109, !on); }
@(decl 'spi1 "int on") { system_set_clock (110, on); system_periph_reset (110, !on); }

@(decl 'i2c0 "int on") { system_set_clock (113, on); system_periph_reset (113, !on); }

@(decl 'uart0 "int on") { system_set_clock (117, on); system_periph_reset (117, !on); }
@(decl 'uart1 "int on") { system_set_clock (118, on); system_periph_reset (118, !on); }
@(decl 'uart2 "int on") { system_set_clock (119, on); system_periph_reset (119, !on); }

@(decl 'qei_clock "int on") { system_set_clock (121, on); system_periph_reset (121, !on); }

@(decl 'uart_clock "int div") { LPC_SYSCON->UARTCLKDIV = div; }
@(decl 'glitch_filter_clock "int div") { LPC_SYSCON->IOCONCLKDIV = div; }
@(decl 'adc_clock "int div") { LPC_SYSCON->ADCASYNCCLKDIV = div; }

// frequency measure
// USB need_clock

@(decl 'flash "int clock")
{
  int ws = 0;
       if (clock > 72e6) ERROR("Clock frequency too high (> 72 Mhz).");
  else if (clock > 55e6) ws = 3;
  else if (clock > 25e6) ws = 2;
  else if (clock > 0) ws = 1;
  if (ws) {
    @(set/mask 'LPC_SYSCON->FLASHCFG "0x3 << 12" "ws - 1")
  }
  system_set_clock (7, ws > 0); system_set_power(5, ws > 0);
  @(set/bit 'LPC_SYSCON->PRESETCTRL0 7 "ws > 0")
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

@(decl 'bod "int on" "int reset" "float reset_level" "float int_level")
{
  system_set_power (3, on);
  int rlvl = 0, ilvl = 0;
  @(assoc/if 'reset_level 'rlvl "Invalid BOD reset level."
             `([0 . 0]
               [2.55f . 2]
               [2.83f . 3]))
  @(assoc/if 'int_level 'ilvl "Invalid BOD interrupt level."
             `([0 . 0]
               [2.34f . 2]
               [2.64f . 3]))
  LPC_SYSCON->BODCTRL = (rlvl << 0) | (ilvl << 2) | (reset ? 1 << 4 : 0);
}

enum {
  OSC_BYPASS,
};

@(decl 'sysosc "int freq")
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

@(decl 'clkout "enum clock_source src" "int div")
{
  @check-range[0 'div 255]{CLKOUT divider}
  LPC_SYSCON->CLKOUTDIV = 0;
  int s = 0;
  @(clksrc-switch 'src 's '([OSC_IRC 0]
                            [OSC_SYS 1]
                            [OSC_WDT 2]
                            [CLK_MAIN 3]
                            [PLL_USB "0x11"]
                            [PLL_SCT "0x12"]
                            [OSC_RTC "0x13"]))
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
  @check-range[1 'mul 64]{Required system PLL frequency multiplier}
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
  @(assoc/if 'div 'div "Invalid PLL post divider."
               `([1 . 0]
                 [2 . 1]
                 [4 . 2]
                 [8 . 3]))
  *reg = mul << 0 | div << 6;
}

@(decl 'syspll "int on" "enum clock_source src" "int in" "int out")
{
  system_set_power (22, 0);
  if (!on) return;
  pll_setup_shared (in, out, &LPC_SYSCON->SYSPLLCTRL);
  int s = 0;
  @(clksrc-switch 'src 's '([OSC_IRC 0]
                            [OSC_SYS 1]))
  if (s != -1) LPC_SYSCON->SYSPLLCLKSEL = s;
  system_set_power (22, 1);
  while (!LPC_SYSCON->SYSPLLSTAT);
}

@(decl 'usbpll "int on" "enum clock_source src" "int in" "int out")
{
  system_set_power (23, 0);
  if (!on) return;
  pll_setup_shared (in, out, &LPC_SYSCON->USBPLLCTRL);
  int s = 0;
  @(clksrc-switch 'src 's '([OSC_IRC 0]
                            [OSC_SYS 1]))
  if (s != -1) LPC_SYSCON->USBPLLCLKSEL = s;
  system_set_power (23, 1);
  while (!LPC_SYSCON->USBPLLSTAT);
}

@(decl 'sctpll "int on" "enum clock_source src" "int in" "int out")
{
  system_set_power (24, 0);
  if (!on) return;
  pll_setup_shared (in, out, &LPC_SYSCON->SCTPLLCTRL);
  int s = 0;
  @(clksrc-switch 'src 's '([OSC_IRC 0]
                            [OSC_SYS 1]))
  if (s != -1) LPC_SYSCON->SCTPLLCLKSEL = s;
  system_set_power (24, 1);
  while (!LPC_SYSCON->SCTPLLSTAT);
}

@(decl 'system_clock "enum clock_source src" "int div")
{
  @check-range[0 'div 255]{Main clock divider.}
  int s = 0;
  @(clksrc-switch 'src 's '([OSC_IRC 0]
                            [OSC_SYS 1]
                            [OSC_WDT 2]
                            [PLL_SYS_IN "0x11"]
                            [PLL_SYS    "0x12"]
                            [OSC_RTC    "0x13"]))
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

@(decl 'usb_system "enum clock_source src" "int div") {
  system_set_power(9, div != 0);
  system_set_clock (123, 0);
  if (!div) return;
  int s = 0;
  @(clksrc-switch 'src 's '([OSC_IRC 0]
                            [OSC_SYS 1]
                            [PLL_USB 2]
                            [CLK_MAIN 3]))
  if (s != -1) {
    LPC_SYSCON->USBCLKDIV = 255;
    LPC_SYSCON->USBCLKSEL = s;
  }
  system_set_clock (123, div != 0);
  system_periph_reset (123, on == 0);
  LPC_SYSCON->USBCLKDIV = div;
}

#if 0
@(decl 'wdtosc "int clk" "int div") {
  system_set_power (6, clk ? 1 : 0);
  int freq;
  @check-range[2 'div 64]{Watchdog clock divider}
  if (div % 2) ERROR("Watchdog clock divider must be even.");
  div = div / 2 - 1;
  if (clk) {
    @(assoc/if 'clk 'freq "Invalid watchdog oscillator frequency."
               `([0.5 . 1]
                 [0.8 . 2]
                 [1.1 . 3]
                 [1.4 . 4]
                 [1.6 . 5]
                 [1.8 . 6]
                 [2.0 . 7]
                 [2.2 . 8]
                 [2.4 . 9]
                 [2.6 . 10]
                 [2.7 . 11]
                 [2.9 . 12]
                 [3.1 . 13]
                 [3.2 . 14]
                 [3.4 . 15]))
  }
  LPC_SYSCON->WDTOSCCTRL = div << 0 | freq << 5;
}

@(decl 'rtc_clock "enum clock_source src" "int div")
{
  ERROR("Not implemented");
}

#if 0 // TODO
@(decl 'wdt "enum clock_source src" "int div")
{
  @check-range[0 'div 255]{Watchdog clock divider}
  system_set_clock (15, div ? 1 : 0);
  int s = 0;
  LPC_SYSCON->WDTCLKDIV = div;
  @(clksrc-switch 'src 's '([OSC_IRC 0]
                            [CLK_MAIN 1]
                            [OSC_WDT 2]))
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
  @(set/bit 'LPC_WWDT->MOD 0 'on)
  wdt_feed();
}

@(decl 'uart0_clock "int div")
{
  @check-range[0 'div 255]{UART0 clock divider}
  set_reset (2, 1);
  system_set_clock (12, div ? 1 : 0);
  LPC_SYSCON->UART0CLKDIV = div;
  set_reset (2, div ? 0 : 1);
}

@(decl 'uart1_clock "int div")
{
  @check-range[0 'div 255]{UART1 clock divider}
  set_reset (3, 1);
  system_set_clock (13, div ? 1 : 0);
  LPC_SYSCON->UART1CLKDIV = div;
  set_reset (3, div ? 0 : 1);
}

@(decl 'ssp_clock "int div")
{
  @check-range[0 'div 255]{SSP clock divider}
  set_reset (0, 1);
  system_set_clock (11, div ? 1 : 0);
  LPC_SYSCON->SSPCLKDIV = div;
  set_reset (0, div ? 0 : 1);
}

@(decl 'adc_system "int on") { system_set_power (4, on); system_set_clock (14, on); }

enum memory_map {
  MEMORY_MAP_BOOT  = 0,
  MEMORY_MAP_RAM   = 1,
  MEMORY_MAP_FLASH = 2,
};

@(decl 'memory_map "enum memory_map map")
{
  LPC_SYSCON->SYSMEMREMAP = map;
}
#endif
}})

(main)
