/*
   CPU type and features.

   This is an automatically generated file. For more details see:
       http://bitbucket.org/jpc/lpc1xxx-hw/

   Copyright (c) 2010-2011 LoEE - Jakub Piotr Cłapa
   This program is released under the new BSD license.
*/
#ifndef CPU_H
#define CPU_H


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

#endif // CPU_H