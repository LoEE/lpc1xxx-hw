#lang scribble/text
@(define ports '(0 1 2 3 4))
/* 
 * IO functions for NXP LPC1768. (generated file, check io-pin.ss)
 *
 * See also: http://bitbucket.org/jpc/lpc1768/
 *
 * Copyright (c) 2010 LoEE - Jakub Piotr Cłapa
 * This program is released under the new BSD license.
 */
#ifndef IO_PIN_H
#define IO_PIN_H

#include "LPC17xx.h"

enum pin_port {
@(add-newlines
  (for/list ([i (in-naturals)]
             [port ports])
    @list{P@port = @(* i 32),}))
};

enum pin_dir {
  PIN_IN = 0,
  PIN_OUT = 1,
};

extern void invalid_pin_error () __attribute__((error ("Invalid IO pin number.")));
 
@(define INLINE "extern __inline__ __attribute__((always_inline,gnu_inline))")
@(define-syntax-rule (switch pin_no i port template)
   @list{switch(pin_no) {
           @(add-newlines
             (for/list ([i (in-naturals)]
                        [port (in-list ports)])
               @list{case @(* i 32) ... @(sub1 (* (add1 i) 32)):
                       @template}))
           default:
             invalid_pin_error ();
             break;
         }})
@(define-syntax-rule (switch-pinsel pin_no i register template)
   @list{switch(pin_no) {
           @(add-newlines
             (for/list ([i (in-naturals)]
                        [_ (in-list ports)])
               @list{case @(* i 32) ... @(sub1 (+ (* i 32) 16)):
                       @(let ([register (format "PINSEL~a" (* i 2))])
                          template)
                     case @(+ (* i 32) 16) ... @(sub1 (+ (* i 32) 32)):
                       @(let ([register (format "PINSEL~a" (add1 (* i 2)))])
                          template)}))
           default:
             invalid_pin_error ();
             break;
         }})

@INLINE
int pin_read (int pin_no)
{
  @(switch @{pin_no} i port
           @list{return LPC_GPIO@|port|->FIOPIN & (1 << (pin_no - @(* i 32)));})
  return 0;
}

@INLINE
void pin_write (int pin_no, int value)
{
  @(switch @{pin_no} i port
           @list{if (value) {
                   LPC_GPIO@|port|->FIOSET = (1 << (pin_no - @(* i 32)));
                 } else {
                   LPC_GPIO@|port|->FIOCLR = (1 << (pin_no - @(* i 32)));
                 }
                 break;})
}
           
@INLINE
void pin_dir (int pin_no, enum pin_dir dir)
{
  @(switch @{pin_no} i port
           @list{if (dir == PIN_OUT) {
                   LPC_GPIO@|port|->FIODIR @"|=" (1 << (pin_no - @(* i 32)));
                 } else {
                   LPC_GPIO@|port|->FIODIR @"&=" (1 << (pin_no - @(* i 32)));
                 }
                 break;})
}
           
@INLINE
void pin_setup (int pin_no, int pinsel)
{
  @(switch-pinsel @{pin_no} i register
           @list{LPC_PINCON->@|register| = (LPC_PINCON->@|register| & ~(3 << ((pin_no - @(* i 32)) * 2 % 32))) | (pinsel << ((pin_no - @(* i 32)) * 2 % 32));
                 break;})
}
           
#endif
