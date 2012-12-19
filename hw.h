/*
   Main include file for the LPC1xxx processor support package.

   This is an automatically generated file. For more details see:
       http://bitbucket.org/jpc/lpc1xxx-hw/

   Copyright (c) 2010-2011 LoEE - Jakub Piotr Cłapa
   This program is released under the new BSD license.
*/
#ifndef HW_H
#define HW_H


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

#if defined(LPC131x) && defined(LQFP48)
#  include "io/LPC131x-LQFP48.h"
#elif defined(LPC131x) && defined(HVQFN33)
#  include "io/LPC131x-HVQFN33.h"
#elif defined(LPC134x) && defined(LQFP48)
#  include "io/LPC134x-LQFP48.h"
#elif defined(LPC134x) && defined(HVQFN33)
#  include "io/LPC134x-HVQFN33.h"
#elif defined(LPC122x) && defined(LQFP48)
#  include "io/LPC122x-LQFP48.h"
#elif defined(LPC122x) && defined(LQFP64)
#  include "io/LPC122x-LQFP64.h"
#else
#  error "The given CPU type and package combination is invalid."
#endif

#include "uart.h"
#include "time.h"
#include "ssp.h"

#endif // HW_H