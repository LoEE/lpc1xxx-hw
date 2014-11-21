#lang at-exp racket
(require scribble/text
         "common.rkt"
         "devices.rkt")

(define output-dir "../io")

(define (main)
  (parameterize ([current-directory output-dir])
    (for* ([family '(LPC151x LPC154x)]
           [package '(LQFP48 LQFP64 LQFP100)])
      (with-output-to-file (format "~a-~a.h" family package) #:exists 'replace
        (λ () (output (generate-io-pin family package)))))))

(define (generate-io-pin family package)
  (define po (dict-ref pinouts (list family package)))
  @list{
@header[url]{IO functions for NXP @family devices in @package package.}
@cpp-wrap['IO_PIN]{
enum pin_dir {
  PIN_IN = 0,
  PIN_OUT = 1,
};

enum io_mode {
  PULL_NONE = 0 << 3,
  PULL_DOWN = 1 << 3,
  PULL_UP = 2 << 3,
  PULL_REPEATER = 3 << 3,
  
  IN_HYSTERESIS = 1 << 5,
  IN_INVERT = 1 << 6,
  
  OUT_OPENDRAIN = 1 << 10,

  I2C_STD = 0 << 8,
  I2C_FAST = 0 << 8,
  I2C_GPIO = 1 << 8,
  I2C_FAST_PLUS = 2 << 8,
};
 
enum io_filter {
  IN_DEGLITCH = 1 << 8,
};
 
enum io_function {
  @(add-newlines (pinout->enum-names po) #:sep ", "), PIO = 0xff,
  @(add-newlines (map car LPC15xx-movable-functions) #:sep ", "), LPC15xx_MAX_FUNCTION
};

enum pio_pin {
  @(add-newlines (map pin-enum-name po) #:sep ", "), NOT_CONNECTED, LPC15xx_MAX_PIN
}; 

@(pin-setup po)

INLINE
void pin_setup_function(enum io_function func, enum pio_pin pin)
{
  if(func <= PIO) ERROR("pin_setup_function only deals with movable functions.");
  if(pin >= LPC15xx_MAX_PIN) ERROR("Invalid IO pin.");
  if(pin == NOT_CONNECTED) pin = 0xff;
  func -= PIO + 1;
  int reg = func / 4, shift = (func % 4) * 8, mask = 0xff << shift;
  LPC_SWM->PINASSIGN[reg] = (LPC_SWM->PINASSIGN[reg] & ~mask) | (pin << shift);
}

INLINE
void pin_setup_filter(enum pio_pin pin, int samples, int clocks, enum io_filter flags) {
  enum { FILTER_MASK = IN_DEGLITCH | 0xF800 };
  // FIXME: not implemented
}

@(pin-write po)

@(pin-read po)

@(pin-dir po)
}})

(struct pin (name functions) #:transparent)

(define pio-rx #rx"^PIO([0-9])_([0-9]+)$")

(define (pin-port p)
  (and (symbol? (pin-name p))
       (second (regexp-match pio-rx (symbol->string (pin-name p))))))

(define (pin-no p)
  (and (symbol? (pin-name p))
       (third (regexp-match pio-rx (symbol->string (pin-name p))))))

(define (pin-enum-name p)
  (format "P~a_~a" (pin-port p) (pin-no p)))

(define (pin-iocon-name pin)
  (format "LPC_IOCON->~a" (pin-name pin)))

(define (pin-has-fixfuns? p)
  (pair? (cdr (pin-functions p))))

(define (parse-pinout . text)
  (for/list ([line (in-list (split-lines text))]
             #:when (pair? line))
    (decode-pin (regexp-split #rx"/" (car line)))))

(define (decode-pin functions)
  (match functions
    [(list-rest (? pio-f? pio) other)
     (let* ([pio (string->symbol pio)]
            [functions (list* pio other)])
       (pin pio functions))]
    [(list-rest main (? pio-f? pio) other)
     (let* ([pio (string->symbol pio)]
            [functions (list* main pio other)])
       (pin pio functions))]
    [other
     (pin #f other)]))

(define (function-name->enum-name f)
  (cond
    [(symbol? f)                   "PIO"]
    [(string=? f "R")              #f]
    [(char=? (string-ref f 0) #\!) (string-append "n" (substring f 1))]
    [else                          f]))

(define (pin-enum-names p)
    (if (pin-name p)
        (map function-name->enum-name (pin-functions p))
        '()))

(define (pinout->enum-names po)
  (remove "PIO" (remove-duplicates (append* (map pin-enum-names po)))))

(define (pio-f? f) (and (string? f) (regexp-match pio-rx f) f))
(define (adc-f? f) (and (string? f) (regexp-match #rx"^AD[0-9]$" f) f))
(define (i2c-f? f) (and (string? f) (regexp-match #rx"^I2C" f) f))

(define (pin-setup po)
  (define (setup-fixfun p f)
    @(for/nl ([f2 (in-list (pin-functions p))] #:when (not (symbol? f2)))
       (define fixfun (assq (string->symbol f2) LPC15xx-fixed-functions))
       (when fixfun
         (eprintf "~s ~s~n" f2 fixfun)
         @list{fixfun(@(cdr fixfun), @(if (eq? f f2) 1 0)); // @f2})))
  @list{INLINE
        void pin_setup (enum pio_pin pin, enum io_function func, enum io_mode mode)
        {
          mode |= 1 << 7; // reserved
          void set_pinenable(int pin, int on) {
            int reg = pin / 32, shift = pin % 32, mask = 1 << shift;
            LPC_SWM->PINENABLE[reg] = (LPC_SWM->PINENABLE[reg] & ~mask) | (on ? 0 : 1 << shift);
          }
          switch (pin) {
            @(for/nl ([p (in-list po)]
                      #:when (pin-name p)
                      #:when (pin-has-fixfuns? p))
               @list{case @(pin-enum-name p):
                       @(for/list ([f (in-list (pin-functions p))]
                                   #:when (not (symbol? f)))
                          (define fixfun (assq (string->symbol f) LPC15xx-fixed-functions))
                          (when fixfun
                            @list{set_pinenable(@(cdr fixfun), func == @(function-name->enum-name f));@"\n"}))@;
                       @(when (ormap i2c-f? (pin-functions p))
                         @list{if (mode & 0x3f)
                                 ERROR("Pull resistors and hysteresis are not available on I2C pins.");@"\n"})@;
                       @(pin-iocon-name p) = mode;
                       break;})
            default:
              ERROR("Invalid IO pin.");
          }          
          if (func > PIO)
            ERROR("Movable functions are set using pin_setup_function.");
        }})

(define (pin-write po)
  @list{INLINE
        void pin_write (enum pio_pin pin, int val)
        {
          switch (pin) {
            @(for/nl ([p (in-list po)] #:when (pin-name p))
               @list{case @(pin-enum-name p): LPC_GPIO_PORT->B[@(pin-enum-name p)] = val ? 1 : 0; break;})
            default:
              ERROR("Invalid IO pin.");
          }
        }})

(define (pin-read po)
  @list{INLINE
        int pin_read (enum pio_pin pin)
        {
          switch (pin) {
            @(for/nl ([p (in-list po)] #:when (pin-name p))
               @list{case @(pin-enum-name p): return LPC_GPIO_PORT->B[@(pin-enum-name p)];})
            default:
              ERROR("Invalid IO pin.");
          }
        }})

(define (pin-dir po)
  @list{INLINE
        void pin_dir (enum pio_pin pin, enum pin_dir dir)
        {
          switch (pin) {
            @(for/nl ([p (in-list po)] #:when (pin-name p))
               @list{case @(pin-enum-name p): LPC_GPIO_PORT->DIR[@(pin-port p)] = @;
                      (LPC_GPIO_PORT->DIR[@(pin-port p)] & ~(1 << @(pin-no p))) | (dir ? 1 << @(pin-no p) : 0); break;})
            default:
              ERROR("Invalid IO pin.");
          }
        }})


(define LPC15xx-LQFP48
  @parse-pinout{
PIO0_0/ADC0_10/SCT0_OUT3
PIO0_1/ADC0_7/SCT0_OUT4
PIO0_2/ADC0_6/SCT1_OUT3
PIO0_3/ADC0_5/SCT1_OUT4
PIO0_4/ADC0_4
PIO0_5/ADC0_3
PIO0_6/ADC0_2/SCT2_OUT3
PIO0_7/ADC0_1

PIO0_8/ADC0_0/TDO
PIO0_9/ADC1_1/TDI
PIO0_10/ADC1_2
PIO0_11/ADC1_3
PIO0_12/DAC_OUT
PIO0_13/ADC1_6
PIO0_14/ADC1_7/SCT1_OUT5
PIO0_15/ADC1_8
PIO0_16/ADC1_9
PIO0_17/WAKEUP/!TRST

PIO0_18/SCT0_OUT5
SWCLK/PIO0_19/TCK
SWDIO/PIO0_20/SCT1_OUT6/TMS
!RESET/PIO0_21
PIO0_22/I2C0_SCL
PIO0_23/I2C0_SDA
PIO0_24/SCT0_OUT6
PIO0_25/ACMP0_I4
PIO0_26/ACMP0_I3/SCT3_OUT3
PIO0_27/ACMP_I1

PIO0_28/ACMP1_I3
PIO0_29/ACMP2_I3/SCT2_OUT4})

(define +LPC15xx-LQFP64
  @parse-pinout{
PIO0_30/ADC0_11
PIO0_31/ADC0_9
PIO1_0/ADC0_8
PIO1_1/ADC1_0
PIO1_2/ADC1_4
PIO1_3/ADC1_5
PIO1_4/ADC1_10
PIO1_5/ADC1_11
PIO1_6/ACMP_I2
PIO1_7/ACMP3_I4
PIO1_8/ACMP3_I3/SCT3_OUT4
PIO1_9/ACMP2_I4
PIO1_10/ACMP1_I4
PIO1_11})

(define +LPC15xx-LQFP100
  @parse-pinout{
PIO1_12
PIO1_13

PIO1_14/SCT0_OUT7
PIO1_15
PIO1_16
PIO1_17/SCT1_OUT7
PIO1_18
PIO1_19
PIO1_20/SCT2_OUT5
PIO1_21
PIO1_22
PIO1_23
PIO1_24/SCT3_OUT5
PIO1_25
PIO1_26
PIO1_27
PIO1_28
PIO1_29
PIO1_30
PIO1_31
PIO2_0
PIO2_1
PIO2_2
PIO2_3
PIO2_4
PIO2_5
PIO2_6
PIO2_7
PIO2_8

PIO2_9
PIO2_10
PIO2_11})

(define LPC15xx-noUSB @parse-pinout{PIO2_12
                                    PIO2_13})

(define-syntax-rule (enum names ...)
  (for/list ([i (in-naturals)]
             [name (in-list '(names ...))])
    (cons name i)))

(define LPC15xx-movable-functions
  (enum U0_TXD U0_RXD U0_RTS U0_CTS U0_SCLK
        U1_TXD U1_RXD U1_RTS U1_CTS U1_SCLK
        U2_TXD U2_RXD U2_SCLK
        SPI0_SCK SPI0_MOSI SPI0_MISO SPI0_SSEL0 SPI0_SSEL1 SPI0_SSEL2 SPI0_SSEL3
        SPI1_SCK SPI1_MOSI SPI1_MISO SPI1_SSEL0 SPI1_SSEL1
        CAN0_TD CAN0_RD CAN0_RESERVED
        USB_VBUS
        SCT0_OUT0 SCT0_OUT1 SCT0_OUT2
        SCT1_OUT0 SCT1_OUT1 SCT1_OUT2
        SCT2_OUT0 SCT2_OUT1 SCT2_OUT2
        SCT3_OUT0 SCT3_OUT1 SCT3_OUT2
        SCT_ABORT0 SCT_ABORT1
        ADC0_PINTRIG0 ADC0_PINTRIG1
        ADC1_PINTRIG0 ADC1_PINTRIG1
        DAC_PINTRIG DAC_SHUTOFF
        ACMP0_O ACMP1_O ACMP2_O ACMP3_O
        CLKOUT ROSC ROSC_RESET
        USB_FTOGGLE
        QEI_PHA QEI_PHB QEI_IDX
        GPIO_INT_BMAT SWO))

(define LPC15xx-movable-function-max (length LPC15xx-movable-functions))

(define LPC15xx-fixed-functions
  (enum ADC0_0 ADC0_1 ADC0_2 ADC0_3 ADC0_4 ADC0_5 ADC0_6 ADC0_7 ADC0_8 ADC0_9 ADC0_10 ADC0_11
        ADC1_0 ADC1_1 ADC1_2 ADC1_3 ADC1_4 ADC1_5 ADC1_6 ADC1_7 ADC1_8 ADC1_9 ADC1_10 ADC1_11
        DAC_OUT
        ACMP_I1 ACMP_I2 ACMP0_I3 ACMP0_I4 ACMP1_I3 ACMP1_I4 ACMP2_I3 ACMP2_I4 ACMP3_I3 ACMP3_I4
        I2C0_SDA I2C0_SCL
        SCT0_OUT3 SCT0_OUT4 SCT0_OUT5 SCT0_OUT6 SCT0_OUT7
        SCT1_OUT3 SCT1_OUT4 SCT1_OUT5 SCT1_OUT6 SCT1_OUT7
        SCT2_OUT3 SCT2_OUT4 SCT2_OUT5
        SCT3_OUT3 SCT3_OUT4 SCT3_OUT5
        RESETN SWCLK SWDIO))

(define LPC15xx-fixed-function-max (length LPC15xx-fixed-functions))

(define pinouts
  `([(LPC151x LQFP48)  . ,(append LPC15xx-LQFP48 LPC15xx-noUSB)]
    [(LPC151x LQFP64)  . ,(append LPC15xx-LQFP48 +LPC15xx-LQFP64 LPC15xx-noUSB)]
    [(LPC151x LQFP100) . ,(append LPC15xx-LQFP48 +LPC15xx-LQFP64 +LPC15xx-LQFP100 LPC15xx-noUSB)]
    [(LPC154x LQFP48)  . ,(append LPC15xx-LQFP48)]
    [(LPC154x LQFP64)  . ,(append LPC15xx-LQFP48 +LPC15xx-LQFP64)]
    [(LPC154x LQFP100) . ,(append LPC15xx-LQFP48 +LPC15xx-LQFP64 +LPC15xx-LQFP100)]))

(main)