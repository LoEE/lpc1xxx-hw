#lang at-exp racket
(require scribble/text
         "common.rkt")

(define output-dir "../system")

(define (main)
  (parameterize ([current-directory output-dir])
    (with-output-to-file "LPC122x.h" #:exists 'replace
      (λ () (output (generate-122x-system))))))

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

(define (generate-122x-system)
  @list{
@header[url]{System configuration functions for the LPC122x processors.}
@cpp-wrap['SYSTEM]{
INLINE void set_power (int bit, int on)
{
  @(set/bit 'LPC_SYSCON->PDRUNCFG 'bit "!on")
}

INLINE void set_clock (int bit, int on)
{
  @(set/bit 'LPC_SYSCON->SYSAHBCLKCTRL 'bit "on")
}

INLINE void set_reset (int bit, int reset)
{
  @(set/bit 'LPC_SYSCON->PRESETCTRL 'bit '!reset)
}

@(decl 'rom "int on") { set_clock (1, on); }

@(decl 'ram "int on") { set_clock (2, on); }

@(decl 'flash_timing "int clock")
{
  int ws = 0;
  if (clock > 45e6) ERROR("Clock frequency too high (> 45 Mhz).");
  if (clock > 30e6) ws = 1;
  else ws = 0;
  if (ws) {
    @(set/mask 'LPC_FLASHCTRL->FLASHCFG #x3 'ws)
    @(set/bit 'LPC_SYSCON->PRESETCTRL 15 0)
  } else {
    @(set/bit 'LPC_SYSCON->PRESETCTRL 15 1)
  }
}

@(decl 'flash_registers "int on") { set_clock (3, on); }

@(decl 'flash_array "int on") { set_clock (4, on); }

@(decl 'i2c_system "int on")
{
  set_reset (1, 1);
  set_clock (5, on);
  set_reset (1, !on);
}

@(decl 'crc "int on") { set_reset (9, 1); set_clock (6, on); set_reset (9, !on); }

@(decl 'ct16b0 "int on") { set_reset (4, 1); set_clock (7, on); set_reset (4, !on); }

@(decl 'ct16b1 "int on") { set_reset (5, 1); set_clock (8, on); set_reset (5, !on); }

@(decl 'ct32b0 "int on") { set_reset (6, 1); set_clock (9, on); set_reset (6, !on); }

@(decl 'ct32b1 "int on") { set_reset (7, 1); set_clock (10, on); set_reset (7, !on); }

@(decl 'iocon "int on") { set_clock (16, on); }

@(decl 'dma "int on") { set_reset (10, 1); set_clock (17, on); set_reset (10, !on); }

@(decl 'rtc "int on") { set_clock (19, on); }

@(decl 'cmp "int on") { set_power (15, on); set_reset (8, 1); set_clock (20, on); set_reset (8, !on); }

@(decl 'gpio0 "int on") { set_clock (29, on); }

@(decl 'gpio1 "int on") { set_clock (30, on); }

@(decl 'gpio2 "int on") { set_clock (31, on); }

@(decl 'irc "int on") { set_power (1, on); set_power (0, on); }

@(decl 'flash "int on") { set_power (2, on); }

@(decl 'bod "int on" "int reset" "float reset_level" "float int_level")
{
  set_power (3, on);
  int rlvl = 0, ilvl = 0;
  @(assoc/if 'reset_level 'rlvl "Invalid BOD reset level."
             `([0 . 0]
               [2.038 . 1]
               [2.336 . 2]
               [2.624 . 3]))
  @(assoc/if 'int_level 'ilvl "Invalid BOD interrupt level."
             `([0 . 0]
               [2.248 . 1]
               [2.541 . 2]
               [2.828 . 3]))
  LPC_SYSCON->BODCTRL = (rlvl << 0) | (ilvl << 2) | (reset ? 1 << 4 : 0);
}

enum {
  OSC_BYPASS,
};

@(decl 'sysosc "int freq")
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

@(decl 'wdtosc "int clk" "int div") {
  set_power (6, clk ? 1 : 0);
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
  @check-range[1 'mul 32]{Required system PLL frequency multiplier}
  if (out > 100e6) ERROR("PLL output frequency too high [out > 100 MHz].");
  int div;
  if (out * 2 > 156e6) div = 2;
  else if (out * 4 > 156e6) div = 4;
  else if (out * 8 > 156e6) div = 8;
  else ERROR("Output frequency too low for the CCO [156 < F_CCO < 320].");
  if (out * div > 320e6) ERROR("CCO frequency too high [156 < F_CC0 < 320].");
  mul--;
  div = div / 2 - 1;
  *reg = mul << 0 | div << 5;
}

@(decl 'syspll "int on" "enum clock_source src" "int in" "int out")
{
  set_power (7, 0);
  if (!on) return;
  pll_setup_shared (in, out, &LPC_SYSCON->SYSPLLCTRL);
  int s = 0;
  @(clksrc-switch 'src 's '([OSC_IRC 0]
                            [OSC_SYS 1]))
  if (s != -1) {
    LPC_SYSCON->SYSPLLCLKSEL = s;
    LPC_SYSCON->SYSPLLCLKUEN = 0;
    LPC_SYSCON->SYSPLLCLKUEN = 1;
  }
  set_power (7, 1);
  while (!LPC_SYSCON->SYSPLLSTAT);
}

@(decl 'system_clock "enum clock_source src" "int div")
{
  @check-range[0 'div 255]{System (AHB) clock divider}
  int s = 0;
  @(clksrc-switch 'src 's '([OSC_IRC 0]
                            [PLL_SYS_IN 1]
                            [OSC_WDT 2]
                            [PLL_SYS 3]))
  if (s != -1) {
    LPC_SYSCON->SYSAHBCLKDIV = 255;
    LPC_SYSCON->MAINCLKSEL = s;
    LPC_SYSCON->MAINCLKUEN = 0;
    LPC_SYSCON->MAINCLKUEN = 1;
  }
  LPC_SYSCON->SYSAHBCLKDIV = div;
}

@(decl 'rtc_clock "enum clock_source src" "int div")
{
  ERROR("Not implemented");
}

@(decl 'clkout "enum clock_source src" "int div")
{
  @check-range[0 'div 255]{CLKOUT divider}
  int s = 0;
  LPC_SYSCON->CLKOUTDIV = div;
  @(clksrc-switch 'src 's '([OSC_IRC 0]
                            [OSC_SYS 1]
                            [OSC_WDT 2]
                            [CLK_MAIN 3]))
  if (s != -1) {
    LPC_SYSCON->CLKOUTCLKSEL = s;
    LPC_SYSCON->CLKOUTUEN = 0;
    LPC_SYSCON->CLKOUTUEN = 1;
  }
}

#if 0 // TODO
@(decl 'wdt "enum clock_source src" "int div")
{
  @check-range[0 'div 255]{Watchdog clock divider}
  set_clock (15, div ? 1 : 0);
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
  set_clock (12, div ? 1 : 0);
  LPC_SYSCON->UART0CLKDIV = div;
  set_reset (2, div ? 0 : 1);
}

@(decl 'uart1_clock "int div")
{
  @check-range[0 'div 255]{UART1 clock divider}
  set_reset (3, 1);
  set_clock (13, div ? 1 : 0);
  LPC_SYSCON->UART1CLKDIV = div;
  set_reset (3, div ? 0 : 1);
}

@(decl 'ssp_clock "int div")
{
  @check-range[0 'div 255]{SSP clock divider}
  set_reset (0, 1);
  set_clock (11, div ? 1 : 0);
  LPC_SYSCON->SSPCLKDIV = div;
  set_reset (0, div ? 0 : 1);
}

@(decl 'adc_system "int on") { set_power (4, on); set_clock (14, on); }

enum memory_map {
  MEMORY_MAP_BOOT  = 0,
  MEMORY_MAP_RAM   = 1,
  MEMORY_MAP_FLASH = 2,
};

@(decl 'memory_map "enum memory_map map")
{
  LPC_SYSCON->SYSMEMREMAP = map;
}
}})

(main)
