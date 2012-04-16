/*
 * Common macros and definitions.
 *
 * Copyright (c) 2008-2010 LoEE - Jakub Piotr Cłapa
 * This program is released under the new BSD license.
 */
#ifndef COMMON_H
#define COMMON_H

#define NOINLINE __attribute__((__noinline__))
#define INLINE extern __inline__ __attribute__((__always_inline__,__gnu_inline__))

#define _CONCAT(a,b) a##b
#define CONCAT(a,b) _CONCAT(a,b)
#define _ERROR(msg,cnt) ({ extern void CONCAT(e,cnt)(void) __attribute__((__noreturn__,__error__("\n\t"msg)));\
    CONCAT(e,cnt)(); })
#define ERROR(msg) _ERROR(msg,__COUNTER__)

#define VOLATILE(x) (*(volatile typeof(x) *)(&x))

#endif
