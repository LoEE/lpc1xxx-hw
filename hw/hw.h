/*
   Main include file for the LPC1xxx processor support package.

   This is an automatically generated file. For more details see:
       http://bitbucket.org/jpc/lpc1xxx-hw/

   Copyright (c) 2010-2011 LoEE - Jakub Piotr Cłapa
   This program is released under the new BSD license.
*/
#ifndef CPU_H
#define CPU_H


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

#if defined(LPC131x) && defined(LQFP48)
#  include "io/LPC131x-LQFP48.h"
#elif defined(LPC131x) && defined(HVQFN33)
#  include "io/LPC131x-HVQFN33.h"
#elif defined(LPC134x) && defined(LQFP48)
#  include "io/LPC134x-LQFP48.h"
#elif defined(LPC134x) && defined(HVQFN33)
#  include "io/LPC134x-HVQFN33.h"
#else
#  error "The given CPU type and package combination is invalid."
#endif

#include "uart.h"
#include "time.h"

#endif // CPU_H