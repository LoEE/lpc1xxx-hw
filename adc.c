/*
   ADC functions for NXP LPC1xxx processors.

   For more details see:
       https://bitbucket.org/LoEE/lpc1xxx-hw/

   Copyright (c) 2011-2012 Marcin Górski - LoEE
   Copyright (c) 2012-2014 LoEE - Jakub Piotr Cłapa
   This program is released under the new BSD license.
 */
#include "hw.h"

ADC_BITS;

#if defined(LPC15xx)
#include "adc-lpc15xx.c"
#else
#include "adc-v1.c"
#endif
