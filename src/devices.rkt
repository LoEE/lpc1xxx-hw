#lang racket
(provide (struct-out device)
         (struct-out memory-block) memory-block-end memory-subblock
         device-ram-map device-ram-block
         find-device-by-part-id find-device-by-model find-device-by-model-and-package
         devices)

;;
;; Utility functions
;;
(define (find lst value #:key [key car] #:cmp [cmp equal?])
  (for/first ([item (in-list lst)]
              #:when (cmp value (key item)))
    item))

;;
;; Memory map block datatype
;;
(struct memory-block (name addr size) #:transparent)
(define (memory-map #:size-unit [size-unit 'B] . blocks)
  (define size-mult (expt 1024 (case size-unit [(B) 0] [(k) 1] [(M) 2] [(G) 3] [(T) 4])))
  (define (parse-block bl)
    (match bl [(list name addr size)
               (memory-block name addr (* size size-mult))]))
  (map parse-block blocks))
(define (memory-block-end  block) (+ (memory-block-addr block) (memory-block-size block)))

(define (memory-subblock block name start [size (- (memory-block-size block) start)])
  (memory-block name (+ (memory-block-addr block) start) size))

;;
;; Device datatype and operations
;;
(struct device (part-id family model package total-flash total-ram)
        #:transparent)

(define-syntax-rule (unknown-device-family-error device)
  (error (format "unknown device family: ~a" (device-family device))))

(define (device-bootloader-ram-block device)
  (define-values (start size)
    (case (device-family device)
      [(lpc17xx) (values 0 #x200)] ;; FIXME: wrong start
      [(lpc13xx lpc12xx) (values 0 #x260)]
      [else (unknown-device-family-error device)]))
  (memory-subblock (device-ram-block device) 'boot-ram start size))

(define (device-ram-map device)
  (case (device-family device)
    [(lpc17xx)
     (case (/ (device-total-ram device) 1024)
       [(8 16) (memory-map
                `[SRAM  #x10000000 ,(device-total-ram device)])]
       [(32)   (memory-map #:size-unit 'k
                           `[SRAM  #x10000000 16]
                           `[SRAM0 #x2007C000 16])]
       [(64)   (memory-map #:size-unit 'k
                           `[SRAM  #x10000000 32]
                           `[SRAM0 #x2007C000 16]
                           `[SRAM1 #x20080000 16])]
       [else
        (error 'device-ram-map "device RAM map unknown for device: ~a" (device-model device))])]
    [(lpc13xx lpc12xx)
     (memory-map
      `[SRAM #x10000000 ,(device-total-ram device)])]
    [else
     (unknown-device-family-error device)]))

(define (device-ram-block device [name 'SRAM])
  (find (device-ram-map device) name #:key memory-block-name))

(define (find-device-by-part-id part-id)
  (find devices part-id #:key device-part-id))

(define (find-device-by-model model)
  (find devices model #:key device-model))

(define (find-device-by-model-and-package model package)
  (find devices (cons model package) #:key (λ (v) (cons (device-model v) (device-package v)))))

;;
;; NXP Cortex-M3 device list
;;
(define-syntax-rule (define-table (name constructor) [args ...] ...)
  (define name
    (list [constructor `args ...]
          ...)))

(define (device* part-id family model package total-flash total-ram)
  (device part-id family model package (* total-flash 1024) (* total-ram 1024)))

(define-table (devices device*)
  ;; LPC13xx
  [#x2C42502B lpc13xx LPC1311 HVQFN33    8  4]
  [#x2C40102B lpc13xx LPC1313 HVQFN33   32  8]
  [#x2C40102B lpc13xx LPC1313 LQFP48    32  8]
  [#x3D01402B lpc13xx LPC1342 HVQFN33   16  4]
  [#x3D00002B lpc13xx LPC1343 HVQFN33   32  8]
  [#x3D00002B lpc13xx LPC1343 LQFP48    32  8]
  ;; LPC17xx
  [#x26113F37 lpc17xx LPC1769 LQFP100  512 64]
  [#x26013F37 lpc17xx LPC1768 LQFP100  512 64]
  [#x26013F37 lpc17xx LPC1768 TFBGA100 512 64]
  [#x26012837 lpc17xx LPC1767 LQFP100  512 64]
  [#x26013F33 lpc17xx LPC1766 LQFP100  256 64]
  [#x26013733 lpc17xx LPC1765 LQFP100  256 64]
  [#x26011922 lpc17xx LPC1764 LQFP100  128 32]
  [#x25113737 lpc17xx LPC1759 LQFP80   512 64]
  [#x25013F37 lpc17xx LPC1758 LQFP80   512 64]
  [#x25011723 lpc17xx LPC1756 LQFP80   256 32]
  [#x25011722 lpc17xx LPC1754 LQFP80   128 32]
  [#x25001121 lpc17xx LPC1752 LQFP80    64 16]
  [#x25001118 lpc17xx LPC1751 LQFP80    32  8]
  [#x25001110 lpc17xx LPC1751 LQFP80    32  8]
  ;; LPC12xx
  [#x3670002B lpc12xx LPC12D27_301 LQFP100 128 8]
  [#x3670002B lpc12xx LPC1227_301  LQFP64  128 8]
  [#x3670002B lpc12xx LPC1227_301  LQFP48  128 8]
  [#x3660002B lpc12xx LPC1226_301  LQFP64  96  8]
  [#x3660002B lpc12xx LPC1226_301  LQFP48  96  8]
  [#x3652002B lpc12xx LPC1225_321  LQFP64  80  8]
  [#x3650002B lpc12xx LPC1225_301  LQFP64  64  8]
  [#x3652002B lpc12xx LPC1225_321  LQFP48  80  8]
  [#x3650002B lpc12xx LPC1225_301  LQFP48  64  8]
  [#x3642C02B lpc12xx LPC1224_121  LQFP64  48  4]
  [#x3640C02B lpc12xx LPC1224_101  LQFP64  32  4]
  [#x3642C02B lpc12xx LPC1224_121  LQFP48  48  4]
  [#x3640C02B lpc12xx LPC1224_101  LQFP48  32  4]
  )