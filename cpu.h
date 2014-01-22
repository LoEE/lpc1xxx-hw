/*
   CPU type and features.

   This is an automatically generated file. For more details see:
       https://bitbucket.org/LoEE/lpc1xxx-hw/

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
#elif defined(LPC1769) || defined(LPC1768) || defined(LPC1767) || defined(LPC1766) || defined(LPC1765) || defined(LPC1764) \
   || defined(LPC1763)
#  define LPC17xx
#  define LPC176x
#elif defined(LPC1759) || defined(LPC1758) || defined(LPC1756) || defined(LPC1754) || defined(LPC1752) || defined(LPC1751)
#  define LPC17xx
#  define LPC175x
#else
#  error "No supported CPU type defined."
#endif

#endif // CPU_H