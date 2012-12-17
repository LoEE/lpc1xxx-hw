#lang at-exp racket
(require scribble/text
         "common.rkt"
         "devices.rkt")

(define output-dir "../io")

(define (main)
  (parameterize ([current-directory output-dir])
    (for* ([family '(LPC122x)]
           [package '(LQFP48 LQFP64)])
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
  PULL_NONE = 0 << 4,
  PULL_UP = 1 << 4,
  IO_INVERT = 1 << 6,
  IO_HIGH_DRIVE = 1 << 9,
  IO_OPEN_DRAIN = 1 << 10,
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
  (define prefixes '([PIO0_25 . SWDIO_]
                     [PIO0_26 . SWCLK_]
                     [PIO0_13 . RESET_]
                     [PIO0_30 . R_]
                     [PIO0_31 . R_]
                     [PIO1_0  . R_]
                     [PIO1_1  . R_]))
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
    [(list main ... (? pio-f? pio) other ...)
     (let* ([pio (string->symbol pio)]
            [functions (append main (list pio) other)])
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

(define (pin-setup po)
  (define (do-pin i pin fun)
    (unless (equal? fun "R")
      (add-newlines
       (list
        (cond
          [(ormap adc-f? (pin-functions pin))
           @list{case @(function-name->enum-name fun): f = @i;@(unless (adc-f? fun) " other |= 1 << 7;") break;}]
          [(ormap i2c-f? (pin-functions pin))
           @list{case @(function-name->enum-name fun): f = @i; other |= 1 << 7;
                   if (mode & PULL_UP)
                     ERROR("Pull-up is not available on I2C pins.");
                   if (mode & IO_HIGH_DRIVE)
                     ERROR("High output drive is not available on I2C pins.");
                   break;}]
          [else
           @list{case @(function-name->enum-name fun): f = @i; other |= 1 << 7; break;}])))))
  @list{INLINE
        void pin_setup (enum pio_pin pin, enum io_function func, enum io_mode mode)
        {
          int f = 0;
          int other = mode;
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
               @list{case @(pin-enum-name p): if(val) LPC_GPIO@(pin-port p)->SET = 1 << @(pin-no p); else LPC_GPIO@(pin-port p)->CLR =  1 << @(pin-no p); break;})
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
               @list{case @(pin-enum-name p): return LPC_GPIO@(pin-port p)->PIN & (1 << @(pin-no p)) ? 1 : 0;})
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


(define LPC122x-LQFP48
  @parse-pinout{
PIO0_0/R/!RTS0
PIO0_1/R/RXD0/CT32B0_CAP0/CT32B0_MAT0
PIO0_2/R/TXD0/CT32B0_CAP1/CT32B0_MAT1
PIO0_3/R/!DTR0/CT32B0_CAP2/CT32B0_MAT2
PIO0_4/R/!DSR0/CT32B0_CAP3/CT32B0_MAT3
PIO0_5/R/!DCD0
PIO0_6/R/!RI0/CT32B1_CAP0/CT32B1_MAT0

PIO0_7/R/!CTS0/CT32B1_CAP1/CT32B1_MAT1
PIO0_8/R/RXD1/CT32B1_CAP2/CT32B1_MAT2
PIO0_9/R/TXD1/CT32B1_CAP3/CT32B1_MAT3
PIO0_10/R/SCL
PIO0_11/R/SDA/CT16B0_CAP0/CT16B0_MAT0
PIO0_12/R/CLKOUT/CT16B0_CAP1/CT16B0_MAT1
!RESET/PIO0_13
PIO0_14/R/SCK
PIO0_15/R/SSEL/CT16B1_CAP0/CT16B1_MAT0
PIO0_16/R/MISO/CT16B1_CAP1/CT16B1_MAT1

PIO0_17/R/MOSI
PIO0_18/SWCLK/R/CT32B0_CAP0/CT32B0_MAT0
PIO0_19/R/ACMP0_I0/CT32B0_CAP1/CT32B0_MAT1
PIO0_20/R/ACMP0_I1/CT32B0_CAP2/CT32B0_MAT2
PIO0_21/R/ACMP0_I2/CT32B0_CAP3/CT32B0_MAT3
PIO0_22/R/ACMP0_I3
PIO0_23/R/ACMP1_I0/CT32B1_CAP0/CT32B1_MAT0
PIO0_24/R/ACMP1_I1/CT32B1_CAP1/CT32B1_MAT1
SWDIO/R/ACMP1_I2/CT32B1_CAP2/CT32B1_MAT2/R/PIO0_25
SWCLK/R/ACMP1_I3/CT32B1_CAP3/CT32B1_MAT3/R/PIO0_26

PIO0_27/R/ACMP0_O
PIO0_28/R/ACMP1_O/CT16B0_CAP0/CT16B0_MAT0
PIO0_29/R/ROSC/CT16B0_CAP1/CT16B0_MAT1
R/PIO0_30/R/AD0
R/PIO0_31/R/AD1
R/PIO1_0/AD2
R/PIO1_1/AD3
PIO1_2/SWDIO/AD4
PIO1_3/AD5
PIO1_4/AD6

PIO1_5/AD7/CT16B1_CAP0/CT16B1_MAT0
PIO1_6/CT16B1_CAP1/CT16B1_MAT1
})

(define LPC122x-LQFP64
  @parse-pinout{
PIO0_0/R/!RTS0
PIO0_1/R/RXD0/CT32B0_CAP0/CT32B0_MAT0
PIO0_2/R/TXD0/CT32B0_CAP1/CT32B0_MAT1
PIO0_3/R/!DTR0/CT32B0_CAP2/CT32B0_MAT2
PIO0_4/R/!DSR0/CT32B0_CAP3/CT32B0_MAT3
PIO0_5/R/!DCD0
PIO0_6/R/!RI0/CT32B1_CAP0/CT32B1_MAT0

PIO0_7/R/!CTS0/CT32B1_CAP1/CT32B1_MAT1
PIO0_8/R/RXD1/CT32B1_CAP2/CT32B1_MAT2
PIO0_9/R/TXD1/CT32B1_CAP3/CT32B1_MAT3
PIO0_10/R/SCL
PIO0_11/R/SDA/CT16B0_CAP0/CT16B0_MAT0
PIO0_12/R/CLKOUT/CT16B0_CAP1/CT16B0_MAT1
!RESET/PIO0_13
PIO0_14/R/SCK
PIO0_15/R/SSEL/CT16B1_CAP0/CT16B1_MAT0
PIO0_16/R/MISO/CT16B1_CAP1/CT16B1_MAT1

PIO0_17/R/MOSI
PIO0_18/SWCLK/R/CT32B0_CAP0/CT32B0_MAT0
PIO0_19/R/ACMP0_I0/CT32B0_CAP1/CT32B0_MAT1
PIO0_20/R/ACMP0_I1/CT32B0_CAP2/CT32B0_MAT2
PIO0_21/R/ACMP0_I2/CT32B0_CAP3/CT32B0_MAT3
PIO0_22/R/ACMP0_I3
PIO0_23/R/ACMP1_I0/CT32B1_CAP0/CT32B1_MAT0
PIO0_24/R/ACMP1_I1/CT32B1_CAP1/CT32B1_MAT1
SWDIO/R/ACMP1_I2/CT32B1_CAP2/CT32B1_MAT2/PIO0_25
SWCLK/R/ACMP1_I3/CT32B1_CAP3/CT32B1_MAT3/PIO0_26

PIO0_27/R/ACMP0_O
PIO0_28/R/ACMP1_O/CT16B0_CAP0/CT16B0_MAT0
PIO0_29/R/ROSC/CT16B0_CAP1/CT16B0_MAT1
R/PIO0_30/R/AD0
R/PIO0_31/R/AD1
R/PIO1_0/AD2
R/PIO1_1/AD3
PIO1_2/SWDIO/AD4
PIO1_3/AD5
PIO1_4/AD6

PIO1_5/AD7/CT16B1_CAP0/CT16B1_MAT0
PIO1_6/CT16B1_CAP1/CT16B1_MAT1

PIO2_0/R/CT16B0_CAP0/CT16B0_MAT0/!RTS0
PIO2_1/R/CT16B0_CAP1/CT16B0_MAT1/RXD0
PIO2_2/R/CT16B1_CAP0/CT16B1_MAT0/TXD0
PIO2_3/R/CT16B1_CAP1/CT16B1_MAT1/!DTR0
PIO2_4/R/CT32B0_CAP0/CT32B0_MAT0/!CTS0
PIO2_5/R/CT32B0_CAP1/CT32B0_MAT1/!RI0

PIO2_6/R/CT32B0_CAP2/CT32B0_MAT2/!DCD0
PIO2_7/R/CT32B0_CAP3/CT32B0_MAT3/!DSR0
PIO2_8/R/CT32B1_CAP0/CT32B1_MAT0
PIO2_9/R/CT32B1_CAP1/CT32B1_MAT1
PIO2_10/R/CT32B1_CAP2/CT32B1_MAT2/R/TXD1
PIO2_11/R/CT32B1_CAP3/CT32B1_MAT3/R/RXD1
PIO2_12/R/R/RXD1
PIO2_13/R/R/TXD1
PIO2_14
PIO2_15
})

(define pinouts
  `([(LPC122x LQFP48) . ,LPC122x-LQFP48]
    [(LPC122x LQFP64) . ,LPC122x-LQFP64]))

(main)
