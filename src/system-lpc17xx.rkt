#lang at-exp racket
(require scribble/text
         "common.rkt")

(define output-dir "../system")

(define (main)
  (parameterize ([current-directory output-dir])
    (with-output-to-file "LPC17xx.h" #:exists 'replace
      (λ () (output (generate-17xx-system))))))

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

(define (generate-17xx-system)
  @list{
@header[url]{System configuration functions for the LPC17xx processors.}
@cpp-wrap['SYSTEM]{
                   
enum sysosc_mode {
  SYSOSC_OFF,
  @;SYSOSC_BYPASS,
  SYSOSC_SLOW,
  SYSOSC_FAST,
};

@(decl 'sysosc "enum sysosc_mode range")
{
  if (range == SYSOSC_OFF) {
    @(set/bit 'LPC_SC->SCS 5 0)
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

@(decl 'system_clock_source "enum clock_source src")
{
  int s = 0;
  @(clksrc-switch 'src 's '([OSC_IRC 0]
                            [OSC_SYS 1]
                            [OSC_RTC 2]))
  if (s != -1) {
    LPC_SC->CLKSRCSEL = s;
  }
}

@(decl 'cpu_clock_divider "int div")
{
  @check-range[1 'div 256]{CPU clock divider}
  LPC_SC->CCLKCFG = div - 1;
}

@(decl 'usb_clock_divider "int div")
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
  @(for/nl ([i (in-range 1 33)])
     @list{PLL_SETUP_PREDIV_CHECK(@i);})
#undef PLL_SETUP_PREDIV_CHECK
  if(!ok) ERROR("The PLL cannot synthesize the desired output frequency.");
ok:
  @check-range[6 'mul 512]{Required PLL frequency multiplier}
  @check-range[1 'postdiv 256]{Required PLL post divider}
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
  @(set/bit 'LPC_SC->PLL0CON 1 'on)
  syspll_feed();
}

INLINE void syspll_power (int on)
{
  syspll_connect(0);
  @(set/bit 'LPC_SC->PLL0CON 0 'on)
  syspll_feed();
}

INLINE int syspll_locked (void)
{
  return LPC_SC->PLL0STAT & (1 << 26);
}

@(decl 'syspll "int in" "int out")
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
  @(set/bit 'LPC_SC->PCONP 'bit 'on)
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
    @(set/mask 'LPC_SC->PCLKSEL0 "3 << shift" "div << shift")
  else {
    shift -= 32;
    @(set/mask 'LPC_SC->PCLKSEL1 "3 << shift" "div << shift")
  }
}

@(decl 'wdt_pclk "int div") { set_pclk (1, div); }
@(decl 'timer0_pclk "int div") { set_power (1, div != 0); set_pclk (2, div); }
@(decl 'timer1_pclk "int div") { set_power (2, div != 0); set_pclk (4, div); }
@(decl 'uart0_pclk "int div") { set_power (3, div != 0); set_pclk (6, div); }
@(decl 'uart1_pclk "int div") { set_power (4, div != 0); set_pclk (8, div); }
@(decl 'pwm1_pclk "int div") { set_power (6, div != 0); set_pclk (12, div); }
@(decl 'i2c0_pclk "int div") { set_power (7, div != 0); set_pclk (14, div); }
@(decl 'spi_pclk "int div") { set_power (8, div != 0); set_pclk (16, div); }
@(decl 'rtc_pclk "int div") { set_power (9, div != 0); set_pclk (18, div); }
@(decl 'ssp1_pclk "int div") { set_power (10, div != 0); set_pclk (20, div); }
@(decl 'dac_pclk "int div") { set_pclk (22, div); }
@(decl 'adc_pclk "int div") { set_power (12, div != 0); set_pclk (24, div); }
@(decl 'can1_pclk "int div") { set_power (13, div != 0); set_pclk (26, div); }
@(decl 'can2_pclk "int div") { set_power (14, div != 0); set_pclk (28, div); }
@(decl 'can_acf_pclk "int div") { set_pclk (30, div); }
@(decl 'gpio_pclk "int div") { set_power (15, div != 0); set_pclk (34, div); set_pclk (36, div); }
@(decl 'rit_pclk "int div") { set_power (16, div != 0); set_pclk (58, div); }
@(decl 'mcpwm_pclk "int div") { set_power (17, div != 0); set_pclk (62, div); }
@(decl 'qei_pclk "int div") { set_power (18, div != 0); set_pclk (32, div); }
@(decl 'i2c1_pclk "int div") { set_power (19, div != 0); set_pclk (38, div); }
@(decl 'ssp0_pclk "int div") { set_power (21, div != 0); set_pclk (42, div); }
@(decl 'timer2_pclk "int div") { set_power (22, div != 0); set_pclk (44, div); }
@(decl 'timer3_pclk "int div") { set_power (23, div != 0); set_pclk (46, div); }
@(decl 'uart2_pclk "int div") { set_power (24, div != 0); set_pclk (48, div); }
@(decl 'uart3_pclk "int div") { set_power (25, div != 0); set_pclk (50, div); }
@(decl 'i2c2_pclk "int div") { set_power (26, div != 0); set_pclk (52, div); }
@(decl 'i2s_pclk "int div") { set_power (27, div != 0); set_pclk (54, div); }
@(decl 'dma_pclk "int div") { set_power (29, div != 0); }
@(decl 'enet_pclk "int div") { if(div != 0 && div != 1) ERROR("Ethernet clock cannot be divided, only disabled."); set_power (30, div != 0); }
@(decl 'usb_pclk "int div") { set_power (31, div != 0); }
@(decl 'syscon_pclk "int div") { if(div == 0) ERROR("SYSCON PCLK cannot be disabled."); set_pclk (60, div); }
}
@;{
   
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


INLINE void set_power (int bit, int on)
{
  @(set/bit 'LPC_SYSCON->PDRUNCFG 'bit "!on")
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
}
})

(main)
