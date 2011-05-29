#lang at-exp racket
(require scribble/text
         "common.rkt"
         "devices.rkt")

(define output-dir "hw/io")

(define (main)
  (make-directory/remove output-dir)
  (parameterize ([current-directory output-dir])
    (for* ([family '(LPC131x LPC134x)]
           [package '(LQFP48 HVQFN33)])
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
  I2C_STD = 0,
  I2C_FAST = 0,
  I2C_GPIO = 1,
  I2C_FAST_PLUS = 2,
  PULL_NONE = 0,
  PULL_DOWN = 1,
  PULL_UP = 2,
  PULL_REPEATER = 3,
};
 
enum io_function {
  @(add-newlines (pinout->enum-names po) #:sep ", ")
};
 
enum pio_pin {
  @(add-newlines (map pin-enum-name po) #:sep ", ")
};

@(pin-setup po)
 
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
  (define prefixes '([PIO0_0  . RESET_]
                     [PIO0_10 . JTAG_TCK_]
                     [PIO0_11 . JTAG_TDI_]
                     [PIO1_0  . JTAG_TMS_]
                     [PIO1_1  . JTAG_TDO_]
                     [PIO1_2  . JTAG_nTRST_]
                     [PIO1_3  . ARM_SWDIO_]))
  (format "LPC_IOCON->~a~a" (dict-ref prefixes (pin-name pin) "") (pin-name pin)))

(define (pin-has-functions? p)
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
  (remove-duplicates (append* (list (function-name->enum-name "PIO")) (map pin-enum-names po))))

(define (pio-f? f) (and (string? f) (regexp-match pio-rx f) f))
(define (adc-f? f) (and (string? f) (regexp-match #rx"^AD[0-9]$" f) f))
(define (i2c-f? f) (and (string? f) (regexp-match #rx"^SDA|SCL$" f) f))
(define (usb-f? f) (and (string? f) (regexp-match #rx"^n?USB_" f) f))

(define (pin-setup po)
  (define (do-pin i pin fun)
    (unless (equal? fun "R")
      (add-newlines
       (list
        (when (usb-f? fun) @list{@disable-prefix{#ifdef CPU_HAS_USB}})
        (cond
          [(ormap adc-f? (pin-functions pin))
           @list{case @(function-name->enum-name fun): f = @i;@(unless (adc-f? fun) " other |= 1 << 7;") break;}]
          [(ormap i2c-f? (pin-functions pin))
           @list{case @(function-name->enum-name fun): f = @i; other = mode << 8;
                   @(unless (i2c-f? fun)
                      @list{if (mode == I2C_FAST_PLUS)
                              ERROR("I2C_FAST_PLUS cannot be used with PIO function.");@"\n"})@;
                   if (hyst)
                     ERROR("Hysteresis is not available on I2C pins.");}]
          [(equal? fun "SCK")
           (define v (dict-ref '([PIO0_10 0]
                                 [PIO2_11 1]
                                 [PIO0_6  2])
                               (pin-name pin)))
           @list{case @(function-name->enum-name fun): f = @i; LPC_IOCON->SCKLOC = @v; break;}]
          [else
           @list{case @(function-name->enum-name fun): f = @i; break;}])
        (when (usb-f? fun) @list{@disable-prefix{#endif // CPU_HAS_USB}})))))
  @list{INLINE
        void pin_setup (enum pio_pin pin, enum io_function func, enum io_mode mode, int hyst)
        {
          int f = 0;
          int other = mode << 3 | hyst << 5 | 1 << 6;
          switch (pin) {
            @(for/nl ([p (in-list po)]
                      #:when (and (pin-name p)))
               @list{case @(pin-enum-name p):
                       @(if (pin-has-functions? p)
                            @list{switch (func) {
                                    @(for/nl ([i (in-naturals)] [f (in-list (pin-functions p))])
                                       (do-pin i p f))
                                    default:
                                      ERROR("@(pin-name p) can only be used as @(add-newlines
                                                                                 (remove "PIO" (pin-enum-names p))
                                                                                 #:sep ", ") or PIO.");
                                  }}
                            @list{if (func != PIO) ERROR("@(pin-name p) can only be used as PIO.");
                                  f = 0;})
                       @list{@(pin-iocon-name p) = f | other;}
                       break;})
            default:
              ERROR("Invalid IO pin.");
          }
        }})

(define (pin-write po)
  @list{INLINE
        void pin_write (enum pio_pin pin, int val)
        {
          switch (pin) {
            @(for/nl ([p (in-list po)] #:when (pin-name p))
               @list{case @(pin-enum-name p): LPC_GPIO@(pin-port p)->MASKED_ACCESS[1 << @(pin-no p)] = val ? 0xffff : 0x0000; break;})
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
               @list{case @(pin-enum-name p): return LPC_GPIO@(pin-port p)->MASKED_ACCESS[1 << @(pin-no p)] ? 1 : 0;})
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
               @list{case @(pin-enum-name p): LPC_GPIO@(pin-port p)->DIR = @;
                      (LPC_GPIO@(pin-port p)->DIR & ~(1 << @(pin-no p))) | (dir ? 1 << @(pin-no p) : 0); break;})
            default:
              ERROR("Invalid IO pin.");
          }
        }})


(define LPC13xx-LQFP48
  @parse-pinout{
!RESET/PIO0_0
PIO0_1/CLKOUT/CT32B0_MAT2/USB_FTOGGLE
PIO0_2/SSEL/CT16B0_CAP0
PIO0_3/USB_VBUS
PIO0_4/SCL
PIO0_5/SDA
PIO0_6/!USB_CONNECT/SCK
PIO0_7/CTS
PIO0_8/MISO/CT16B0_MAT0
PIO0_9/MOSI/CT16B0_MAT1/SWO

SWCLK/PIO0_10/SCK/CT16B0_MAT2
R/PIO0_11/AD0/CT32B0_MAT3
R/PIO1_0/AD1/CT32B1_CAP0
R/PIO1_1/AD2/CT32B1_MAT0
R/PIO1_2/AD3/CT32B1_MAT1
SWDIO/PIO1_3/AD4/CT32B1_MAT2
PIO1_4/AD5/CT32B1_MAT3/WAKEUP
PIO1_5/!RTS/CT32B0_CAP0
PIO1_6/RXD/CT32B0_MAT0

PIO1_7/TXD/CT32B0_MAT1
PIO1_8/CT16B1_CAP0
PIO1_9/CT16B1_MAT0
PIO1_10/AD6/CT16B1_MAT1
PIO1_11/AD7
PIO2_0/!DTR
PIO2_1/!DSR
PIO2_2/!DCD
PIO2_3/!RI
PIO2_4
PIO2_4
PIO2_5
PIO2_5
PIO2_6
PIO2_7
PIO2_8
PIO2_9
PIO2_10
PIO2_11/SCK
PIO3_0
PIO3_1
PIO3_2
PIO3_3
})

(define LPC13xx-HVQFN33
  @parse-pinout{
!RESET/PIO0_0
PIO0_1/CLKOUT/CT32B0_MAT2/USB_FTOGGLE
PIO0_2/SSEL/CT16B0_CAP0
PIO0_3/USB_VBUS
PIO0_4/SCL

PIO0_5/SDA
PIO0_6/!USB_CONNECT/SCK
PIO0_7/CTS
PIO0_8/MISO/CT16B0_MAT0
PIO0_9/MOSI/CT16B0_MAT1/SWO
SWCLK/PIO0_10/SCK/CT16B0_MAT2
R/PIO0_11/AD0/CT32B0_MAT3
R/PIO1_0/AD1/CT32B1_CAP0
R/PIO1_1/AD2/CT32B1_MAT0

R/PIO1_2/AD3/CT32B1_MAT1
SWDIO/PIO1_3/AD4/CT32B1_MAT2
PIO1_4/AD5/CT32B1_MAT3/WAKEUP
PIO1_5/!RTS/CT32B0_CAP0
PIO1_6/RXD/CT32B0_MAT0
PIO1_7/TXD/CT32B0_MAT1
PIO1_8/CT16B1_CAP0
PIO1_9/CT16B1_MAT0
PIO1_10/AD6/CT16B1_MAT1
PIO1_11/AD7
PIO2_0/!DTR
PIO3_2
})

(define pinouts
  `([(LPC131x HVQFN33) . ,(append LPC13xx-HVQFN33
                                  @parse-pinout{PIO3_4
                                                PIO3_5})]
    [(LPC134x HVQFN33) . ,LPC13xx-HVQFN33]
    [(LPC131x LQFP48)  . ,(append LPC13xx-LQFP48
                                  @parse-pinout{PIO3_4
                                                PIO3_5})]
    [(LPC134x LQFP48)  . ,LPC13xx-LQFP48]))

(main)