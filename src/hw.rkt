#lang at-exp racket
(require scribble/text
         "common.rkt"
         "devices.rkt")

(define output-dir "../")

(define (main)
  (make-directory/ignore output-dir)
  (parameterize ([current-directory output-dir])
    (with-output-to-file "cpu.h" #:exists 'replace
      (λ () (output (generate-cpu))))
    (with-output-to-file "hw.h" #:exists 'replace
      (λ () (output (generate-hw))))))

(define (generate-cpu)
  @list{
@header[url]{CPU type and features.}
@cpp-wrap['CPU]{

#if defined(LPC1311) || defined(LPC1313)
#  define LPC13xx
#  define LPC131x
#elif defined(LPC1342) || defined(LPC1343)
#  define LPC13xx
#  define LPC134x
#  define CPU_HAS_USB
#elif defined(LPC12D27_301) || defined(LPC1227_301) || defined(LPC1227_301) || defined(LPC1226_301) || defined(LPC1226_301) \
   || defined(LPC1225_321) || defined(LPC1225_301) || defined(LPC1225_321) || defined(LPC1225_301) || defined(LPC1224_121) \
   || defined(LPC1224_101) || defined(LPC1224_121) || defined(LPC1224_101)
#  define LPC12xx
#  define LPC122x
#elif defined(LPC1769) || defined(LPC1768) || defined(LPC1767) || defined(LPC1766) || defined(LPC1765) || defined(LPC1764) \
   || defined(LPC1763)
#  define LPC17xx
#  define LPC176x
#elif defined(LPC1759) || defined(LPC1758) || defined(LPC1756) || defined(LPC1754) || defined(LPC1752) || defined(LPC1751)
#  define LPC17xx
#  define LPC175x
#elif defined(LPC1549) || defined(LPC1548) || defined(LPC1547)
#  define LPC15xx
#  define LPC154x
#  define CPU_HAS_USB
#elif defined(LPC1519) || defined(LPC1518) || defined(LPC1517)
#  define LPC15xx
#  define LPC151x
#else
#  error "No supported CPU type defined."
#endif
}})

(define (generate-hw)
  @list{
@header[url]{Main include file for the LPC1xxx processor support package.}
@cpp-wrap['HW]{

#include "stdint.h"
#include "common.h"

#include "cpu.h"

#if defined(LPC13xx)
#  if !defined(LQFP48) && !defined(HVQFN33)
#    error "No supported CPU package types defined."
#  endif
#  include "CMSIS/LPC13xx.h"
#  include "system/LPC13xx.h"

#  define _WakeUp_Handler_FOR(pin_name) WakeUp##pin_name##_Handler
#  define WakeUp_Handler_FOR(pin_name) _WakeUp_Handler_FOR(pin_name)
#elif defined(LPC122x)
#  if !defined(LQFP48) && !defined(LQFP64)
#    error "No supported CPU package types defined."
#  endif
#  include "CMSIS/LPC122x.h"
#  include "system/LPC122x.h"
#elif defined(LPC176x)
#  if !defined(LQFP100) && !defined(TFBGA100)
#    error "No supported CPU package types defined."
#  endif
#  include "CMSIS/LPC17xx.h"
#  include "system/LPC17xx.h"
#elif defined(LPC175x)
#  if !defined(LQFP80)
#    error "No supported CPU package types defined."
#  endif
#  include "CMSIS/LPC17xx.h"
#  include "system/LPC17xx.h"
#elif defined(LPC15xx)
#  if !defined(LQFP48) && !defined(LQFP64) && !defined(LQFP100)
#    error "No supported CPU package types defined."
#  endif
#  include "CMSIS/LPC15xx.h"
#  include "system/LPC15xx.h"
#endif

#if@;
@(disable-prefix (add-newlines #:sep "\n#elif"
   (for*/list ([family '(LPC131x LPC134x)]
               [package '(LQFP48 HVQFN33)])
     @list{
 defined(@family) && defined(@package)
#  include "io/@|family|-@|package|.h"})))
#elif@;
@(disable-prefix (add-newlines #:sep "\n#elif"
   (for*/list ([family '(LPC122x)]
               [package '(LQFP48 LQFP64)])
     @list{
 defined(@family) && defined(@package)
#  include "io/@|family|-@|package|.h"})))
#elif@;
@(disable-prefix (add-newlines #:sep "\n#elif"
   (for*/list ([family '(LPC151x LPC154x)]
               [package '(LQFP48 LQFP64 LQFP100)])
     @list{
 defined(@family) && defined(@package)
#  include "io/@|family|-@|package|.h"})))
#elif defined(LPC175x) && defined(LQFP80)
#  include "io/LPC175x-LQFP80.h"
#elif defined(LPC1768) && defined(TFBGA100)
#  include "io/LPC176x-TFBGA100.h"
#elif defined(LPC176x) && defined(LQFP100)
#  include "io/LPC176x-LQFP100.h"
#else
#  error "The given CPU type and package combination is invalid."
#endif

#include "time.h"

#if !defined(LPC15xx)
#include "uart.h"
#include "ssp.h"
#include "adc.h"
#endif
}})

(main)
