#lang at-exp racket
(require scribble/text
         "common.rkt"
         "devices.rkt")

(define output-dir "../io")

(define (main)
  (parameterize ([current-directory output-dir])
    (for ([family-package '((LPC175x LQFP80) (LPC176x LQFP100))])
      (with-output-to-file (apply format "~a-~a.h" family-package) #:exists 'replace
        (λ () (output (apply generate-io-pin family-package)))))))

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
  PULL_NONE = 0,
  PULL_DOWN = 1,
  PULL_UP = 2,
  PULL_REPEATER = 3,
  IO_OPEN_DRAIN = 1 << 8,
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

(define pio-rx #rx"^P([0-9])_([0-9]+)$")

(define (pin-port p)
  (and (symbol? (pin-name p))
       (second (regexp-match pio-rx (symbol->string (pin-name p))))))

(define (pin-no p)
  (and (symbol? (pin-name p))
       (third (regexp-match pio-rx (symbol->string (pin-name p))))))

(define (pin-enum-name p)
  (format "P~a_~a" (pin-port p) (pin-no p)))

(define (pin-halfreg-no p)
  (+ (* (string->number (pin-port p)) 2) (quotient (string->number (pin-no p)) 16)))

(define (pin-halfreg-shift p)
  (* (remainder (string->number (pin-no p)) 16) 2))

(define (pin-sel-reg p)
  (format "LPC_PINCON->PINSEL~a" (pin-halfreg-no p)))

(define (pin-mode-reg p)
  (format "LPC_PINCON->PINMODE~a" (pin-halfreg-no p)))

(define (pin-od-reg p)
  (format "LPC_PINCON->PINMODE_OD~a" (pin-port p)))

(define (pin-has-functions? p)
  (pair? (cdr (pin-functions p))))

(define (fix-brackets s)
  (regexp-replace* #rx"\\[([0-9]+)\\]" s "_\\1"))

(define (parse-pinout . text)
  (for/list ([line (in-list (split-lines text))]
             #:when (pair? line))
    (decode-pin (map fix-brackets (regexp-split #rx"[ ]*/[ ]*" (car line))))))

(define (decode-pin functions)
  (let* ([pio (string->symbol (car functions))])
    (pin pio (cons pio (cdr functions))))
  #;(match functions
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

(define (i2c-pin? p) (memq (pin-name p) '(P0_27 P0_28)))
(define (i2c-f? f) (and (string? f) (regexp-match #rx"^SDA|SCL" f) f))
(define (usb-pin? p) (memq (pin-name p) '(P0_29 P0_30)))

(define (pin-setup po)
  (define (do-fun i pin fun)
    (unless (equal? fun "R")
      @list{case @(function-name->enum-name fun):
              @(add-newlines
                (list
                 @list{@(pin-sel-reg pin) = (@(pin-sel-reg pin) & ~(3 << @(pin-halfreg-shift pin))) | (@i << @(pin-halfreg-shift pin));}
                 @(when (and (i2c-f? fun) (not (i2c-pin? pin)))
                    @list{if (!(mode & IO_OPEN_DRAIN))
                            ERROR("You must set IO_OPEN_DRAIN since pin @(pin-name pin) is not dedicated to I2C.");})))
              break;}))
  @list{INLINE
        void pin_setup (enum pio_pin pin, enum io_function func, enum io_mode mode)
        {
          int pull;
          switch (mode & 3) {
            case PULL_NONE: pull = 2; break;
            case PULL_DOWN: pull = 3; break;
            case PULL_UP:   pull = 0; break;
            case PULL_REPEATER: pull = 1; break;
          }
          switch (pin) {
            @(for/nl ([p (in-list po)]
                      #:when (and (pin-name p)))
               @list{case @(pin-enum-name p):
                       @(add-newlines
                         (list
                          (if (pin-has-functions? p)
                              @list{switch (func) {
                                      @(for/nl ([i (in-naturals)] [f (in-list (pin-functions p))])
                                         (do-fun i p f))
                                      default:
                                        ERROR("@(pin-name p) can only be used as @(add-newlines
                                                                                   (remove "PIO" (pin-enum-names p))
                                                                                   #:sep ", ") or PIO.");
                                    }}
                              @list{if (func != PIO) ERROR("@(pin-name p) can only be used as PIO.");
                                    f = 0;})
                          (when (or (i2c-pin? p) (usb-pin? p))
                             @list{if ((mode & 3) != PULL_NONE)
                                     ERROR("@(pin-name p) does not have and pull-up and pull-down resistors.");})
                          @list{@(pin-od-reg p) = (@(pin-od-reg p) & ~(1 << @(pin-no p))) | ((mode & IO_OPEN_DRAIN ? 1 : 0) << @(pin-no p));
                         @(pin-mode-reg p) = (@(pin-mode-reg p) & ~(3 << @(pin-halfreg-shift p))) | (pull << @(pin-halfreg-shift p));
                         break;}))})
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
               @list{case @(pin-enum-name p): if(val) LPC_GPIO@(pin-port p)->FIOSET = 1 << @(pin-no p); else LPC_GPIO@(pin-port p)->FIOCLR = 1 << @(pin-no p); break;})
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
               @list{case @(pin-enum-name p): return LPC_GPIO@(pin-port p)->FIOPIN & (1 << @(pin-no p)) ? 1 : 0;})
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
               @list{case @(pin-enum-name p): LPC_GPIO@(pin-port p)->FIODIR = @;
                      (LPC_GPIO@(pin-port p)->FIODIR & ~(1 << @(pin-no p))) | (dir ? 1 << @(pin-no p) : 0); break;})
            default:
              ERROR("Invalid IO pin.");
          }
        }})


(define LPC176x-LQFP100
  @parse-pinout{
P0[0] / RD1 / TXD3 / SDA1
P0[1] / TD1 / RXD3 / SCL1
P0[2] / TXD0 / AD0[7]
P0[3] / RXD0 / AD0[6]
P0[4] / I2SRX_CLK / RD2 / CAP2[0]
P0[5] / I2SRX_WS / TD2 / CAP2[1]
P0[6] / I2SRX_SDA / SSEL1 / MAT2[0]
P0[7] / I2STX_CLK / SCK1 / MAT2[1]

P0[8] / I2STX_WS / MISO1 / MAT2[2]
P0[9] / I2STX_SDA / MOSI1 / MAT2[3]
P0[10] / TXD2 / SDA2 / MAT3[0]
P0[11] / RXD2 / SCL2 / MAT3[1]
P0[15] / TXD1 / SCK0 / SCK
P0[16] / RXD1 / SSEL0 / SSEL
P0[17] / CTS1 / MISO0 / MISO
P0[18] / DCD1 / MOSI0 / MOSI
P0[19] / DSR1 / R / SDA1

P0[20] / DTR1 / R / SCL1
P0[21] / RI1 / R / RD1
P0[22] / RTS1 / R / TD1
P0[23] / AD0[0] / I2SRX_CLK / CAP3[0]
P0[24] / AD0[1] / I2SRX_WS / CAP3[1]
P0[25] / AD0[2] / I2SRX_SDA / TXD3
P0[26] / AD0[3] / AOUT / RXD3
P0[27] / SDA0 / USB_SDA

P0[28] / SCL0 / USB_SCL
P0[29] / USB_Dm
P0[30] / USB_Dp
P1[0] / ENET_TXD0
P1[1] / ENET_TXD1
P1[4] / ENET_TX_EN
P1[8] / ENET_CRS
P1[9] / ENET_RXD0
P1[10] / ENET_RXD1
P1[14] / ENET_RX_ER
P1[15] / ENET_REF_CLK
P1[16] / ENET_MDC
P1[17] / ENET_MDIO

P1[18] / USB_UP_LED / PWM1[1] / CAP1[0]
P1[19] / MCOA0 / !USB_PPWR / CAP1[1]
P1[20] / MCI0 / PWM1[2] / SCK0
P1[21] / !MCABORT / PWM1[3] / SSEL0
P1[22] / MCOB0 / USB_PWRD / MAT1[0]
P1[23] / MCI1 / PWM1[4] / MISO0
P1[24] / MCI2 / PWM1[5] / MOSI0
P1[25] / MCOA1 / R / MAT1[1]
P1[26] / MCOB1 / PWM1[6] / CAP0[0]

P1[27] / CLKOUT / !USB_OVRCR / CAP0[1]
P1[28] / MCOA2 / PCAP1[0] / MAT0[0]
P1[29] / MCOB2 / PCAP1[1] / MAT0[1]
P1[30] / R / VBUS / AD0[4]
P1[31] / R / SCK1 / AD0[5]
P2[0] / PWM1[1] / TXD1
P2[1] / PWM1[2] / RXD1
P2[2] / PWM1[3] / CTS1 / TRACEDATA[3]
P2[3] / PWM1[4] / DCD1 / TRACEDATA[2]

P2[4] / PWM1[5] / DSR1 / TRACEDATA[1]
P2[5] / PWM1[6] / DTR1 / TRACEDATA[0]
P2[6] / PCAP1[0] / RI1 / TRACECLK
P2[7] / RD2 / RTS1
P2[8] / TD2 / TXD2 / ENET_MDC
P2[9] / USB_CONNECT / RXD2 / ENET_MDIO
P2[10] / !EINT0 / NMI
P2[11] / !EINT1 / R / I2STX_CLK

P2[12] / !EINT2 / R / I2STX_WS
P2[13] / !EINT3 / R / I2STX_SDA
P3[25] / R / MAT0[0] / PWM1[2]
P3[26] / STCLK / MAT0[1] / PWM1[3]
P4[28] / RX_MCLK / MAT2[0] / TXD3
P4[29] / TX_MCLK / MAT2[1] / RXD3
})

(define LQFP80-missing-pins
  '("P0_4" "P0_5" "P0_19" "P0_20" "P0_21" "P0_23" "P0_24" "P0_27" "P0_28"
    "P1_16" "P1_17" "P1_21" "P1_27"
    "P2_11" "P2_12" "P2_13"
    "P3_25" "P3_26"))

(define LPC175x-LQFP80 (remove* LQFP80-missing-pins LPC176x-LQFP100
                                (λ (name pin) (string=? name (symbol->string (pin-name pin))))))

(define pinouts
  `([(LPC175x LQFP80)  . ,LPC175x-LQFP80]
    [(LPC176x LQFP100) . ,LPC176x-LQFP100]))

(main)
