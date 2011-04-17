#lang at-exp racket
(require scribble/text
         "common.rkt"
         "devices.rkt")

(define output-dir "hw")

(define (main)
  (make-directory/ignore output-dir)
  (parameterize ([current-directory output-dir])
    (with-output-to-file "hw.h" #:exists 'replace
      (λ () (output (generate-hw))))))

(define (generate-hw)
  @list{
@header[url]{Main include file for the LPC1xxx processor support package.}
@cpp-wrap['CPU]{

#include "stdint.h"
#include "common.h"
                
#if defined(LPC1311) || defined(LPC1313)
#  define LPC13xx
#  define LPC131x
#  include "CMSIS/LPC13xx.h"
#elif defined(LPC1342) || defined(LPC1343)
#  define LPC13xx
#  define LPC134x
#  define CPU_HAS_USB
#  include "CMSIS/LPC13xx.h"
#else
#  error "No supported CPU type defined."
#endif

#ifdef LPC13xx
#  if !defined(LQFP48) && !defined(HVQFN33)
#    error "No supported CPU package types defined."
#  endif
#  include "system/LPC13xx.h"
#endif

#if@;
@(disable-prefix (add-newlines #:sep "\n#elif"
   (for*/list ([family '(LPC131x LPC134x)]
               [package '(LQFP48 HVQFN33)])
     @list{
 defined(@family) && defined(@package)
#  include "io/@|family|-@|package|.h"})))
#else
#  error "The given CPU type and package combination is invalid."
#endif

#include "uart.h"
#include "time.h"
}})

(main)