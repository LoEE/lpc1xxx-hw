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
#else
#  error "The given CPU type and package combination is invalid."
#endif

#include "uart.h"
#include "time.h"
#include "ssp.h"
}})

(main)
