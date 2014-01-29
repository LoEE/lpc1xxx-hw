#lang at-exp racket
(require scribble/text
         "common.rkt")

(define output-dir "../system")

(define (main)
  (parameterize ([current-directory output-dir])
    (with-output-to-file "LPC13xx.h" #:exists 'replace
      (λ () (output (generate-13xx-system))))))

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

(define (generate-13xx-system)
  @list{
@header[url]{System configuration functions for the LPC13xx processors.}
@cpp-wrap['SYSTEM]{
INLINE void set_power (int bit, int on)
{
  @(set/bit 'LPC_SYSCON->PDRUNCFG 'bit "!on")
}

INLINE void set_clock (int bit, int on)
{
  @(set/bit 'LPC_SYSCON->SYSAHBCLKCTRL 'bit "on")
}

@(decl 'rom "int on") { set_clock (1, on); }

@(decl 'ram "int on") { set_clock (2, on); }

#define FLASHCFG (*(volatile uint32_t *)(0x4003C010))

@(decl 'flash_timing "int clock")
{
  int t = 0;
  if (clock > 72e6) ERROR("Clock frequency too high (> 72 Mhz).");
  if (clock > 40e6) t = 2;
  else if (clock > 20e6) t = 1;
  else t = 0;
  @(set/mask 'FLASHCFG #x3 't)
}

@(decl 'flash_registers "int on") { set_clock (3, on); }

@(decl 'flash_array "int on") { set_clock (4, on); }

@(decl 'i2c_system "int on")
{
  set_clock (5, on);
  @(set/bit 'LPC_SYSCON->PRESETCTRL 1 'on)
}

@(decl 'gpio "int on") { set_clock (6, on); }

@(decl 'ct16b0 "int on") { set_clock (7, on); }

@(decl 'ct16b1 "int on") { set_clock (8, on); }

@(decl 'ct32b0 "int on") { set_clock (9, on); }

@(decl 'ct32b1 "int on") { set_clock (10, on); }

@(decl 'iocon "int on") { set_clock (16, on); }

@(decl 'irc "int on") { set_power (1, on); set_power (0, on); }

@(decl 'flash "int on") { set_power (2, on); }

@(decl 'bod "int on" "int reset" "float int_level")
{
  set_power (3, on);
  int lvl = 0;
  @(assoc/if 'int_level 'lvl "Invalid BOD interrupt level."
             `([1.69f . 0]
               [2.29f . 1]
               [2.59f . 2]
               [2.87f . 3]))
  LPC_SYSCON->BODCTRL = (lvl << 2) | (reset ? 1 << 4 : 0);
}

enum sysosc_mode {
  SYSOSC_OFF,
  SYSOSC_BYPASS,
  SYSOSC_SLOW,
  SYSOSC_FAST,
};

@(decl 'sysosc "enum sysosc_mode range")
{
  if (range == SYSOSC_OFF) {
    set_power (5, 0);
  } else {
    set_power (5, 1);
    @(assoc/if 'range 'LPC_SYSCON->SYSOSCCTRL "Invalid system oscillator mode."
               `([SYSOSC_BYPASS . "1"]
                 [SYSOSC_SLOW   . "0"]
                 [SYSOSC_FAST   . "1 << 1"]))
  }
}

@(decl 'wdtosc "int clk" "int div") {
  set_power (6, clk ? 1 : 0);
  if (clk) {
    int freq;
    @check-range[2 'div 64]{Watchdog clock divider}
    if (div % 2) ERROR("Watchdog clock divider must be even.");
    div = div / 2 - 1;
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
    LPC_SYSCON->WDTOSCCTRL = div << 0 | freq << 5;
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
  OSC_WDT,
  OSC_SYS,
};

INLINE void pll_setup_shared (int in, int out, volatile uint32_t *reg)
{
  int mul = out / in;
  if (mul * in != out) ERROR("PLL output frequency is not divisible by input frequency.");
  @check-range[1 'mul 32]{Required system PLL frequency multiplier}
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
  *reg = mul << 0 | div << 5;
}

@(decl 'syspll_clock_source "enum clock_source src")
{
  int s = 0;
  @(clksrc-switch 'src 's '([OSC_IRC 0]
                            [OSC_SYS 1]))
  if (s != -1) {
    LPC_SYSCON->SYSPLLCLKSEL = s;
    LPC_SYSCON->SYSPLLCLKUEN = 0;
    LPC_SYSCON->SYSPLLCLKUEN = 1;
  }
}

@(decl 'syspll "int on" "enum clock_source src" "int in" "int out")
{
  set_power (7, 0);
  if (!on) return;
  pll_setup_shared (in, out, &LPC_SYSCON->SYSPLLCTRL);
  syspll_clock_source_setup(src);
  set_power (7, 1);
  while (!LPC_SYSCON->SYSPLLSTAT);
}

#ifdef CPU_HAS_USB
@(decl 'usbpll "int on" "enum clock_source src" "int in" "int out")
{
  set_power (8, 0);
  if (!on) return;
  pll_setup_shared (in, out, &LPC_SYSCON->USBPLLCTRL);
  int s = 0;
  @(clksrc-switch 'src 's '([OSC_IRC 0]
                            [OSC_SYS 1]))
  if (s != -1) {
    LPC_SYSCON->USBPLLCLKSEL = s;
    LPC_SYSCON->USBPLLCLKUEN = 0;
    LPC_SYSCON->USBPLLCLKUEN = 1;
  }
  set_power (8, 1);
  while (!LPC_SYSCON->USBPLLSTAT);
}
#endif // CPU_HAS_USB

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

@(decl 'wdt "enum clock_source src" "int div")
{
  @check-range[0 'div (* 255 4)]{Watchdog clock divider}
  if (div % 4) ERROR("Watchdog clock divider must be a multiple of 4.");
  set_clock (15, div ? 1 : 0);
  int s = 0;
  LPC_SYSCON->WDTCLKDIV = div / 4;
  @(clksrc-switch 'src 's '([OSC_IRC 0]
                            [CLK_MAIN 1]
                            [OSC_WDT 2]))
  if (s != -1) {
    LPC_SYSCON->WDTCLKSEL = s;
    LPC_SYSCON->WDTCLKUEN = 0;
    LPC_SYSCON->WDTCLKUEN = 1;
  }
}

#ifdef CPU_HAS_USB
@(decl 'usb_clock "enum clock_source src" "int div")
{
  @check-range[0 'div 255]{USB clock divider}
  set_power (10, div ? 1 : 0); set_clock (14, div ? 1 : 0);
  int s = 0;
  LPC_SYSCON->USBCLKDIV = div;
  @(clksrc-switch 'src 's '([PLL_USB 0]
                            [CLK_MAIN 1]))
  if (s != -1) {
    LPC_SYSCON->USBCLKSEL = s;
    LPC_SYSCON->USBCLKUEN = 0;
    LPC_SYSCON->USBCLKUEN = 1;
  }
}
#endif // CPU_HAS_USB

@(decl 'systick_clock "int div")
{
  @check-range[0 'div 255]{SYSTICK timer clock divider}
  LPC_SYSCON->SYSTICKCLKDIV = div;
}

@(decl 'trace_clock "int div")
{
  @check-range[0 'div 255]{ARM trace clock divider}
  LPC_SYSCON->TRACECLKDIV = div;
}

@(decl 'uart_clock "int div")
{
  @check-range[0 'div 255]{UART clock divider}
  set_clock (12, div ? 1 : 0);
  LPC_SYSCON->UARTCLKDIV = div;
}

#define ssp_clock_setup ssp0_clock_setup
@(decl 'ssp0_clock "int div")
{
  @check-range[0 'div 255]{SSP clock divider}
  set_clock (11, div ? 1 : 0);
  LPC_SYSCON->SSP0CLKDIV = div;
  @(set/bit 'LPC_SYSCON->PRESETCTRL 0 'div)
}

@(decl 'ssp1_clock "int div")
{
  @check-range[0 'div 255]{SSP clock divider}
  set_clock (18, div ? 1 : 0);
  LPC_SYSCON->SSP1CLKDIV = div;
  @(set/bit 'LPC_SYSCON->PRESETCTRL 2 'div)
}

@(decl 'adc_system "int on") { set_power (4, on); set_clock (13, on); }

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
