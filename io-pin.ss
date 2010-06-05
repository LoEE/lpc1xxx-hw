#lang scribble/text
@(define ports '(P0 P1 P2 P3 P4))
@(define registers '(LPC_GPIO0 LPC_GPIO1 LPC_GPIO2 LPC_GPIO3 LPC_GPIO4))
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

enum pin_port {
@(add-newlines
  (for/list ([i (in-naturals)]
             [port ports])
    @list{@port = @(* i 32),}))
};

enum pin_dir {
  PIN_IN = 0,
  PIN_OUT = 1,
};

extern void invalid_pin_error () __attribute__((error ("Invalid IO pin number.")));
 
@(define INLINE "extern __inline__ __attribute__((always_inline))")
@(define-syntax-rule (switch pin_no i register template)
   @list{switch(pin_no) {
           @(add-newlines
             (for/list ([i (in-naturals)]
                        [register registers])
               @list{case @(* i 32) ... @(sub1 (* (add1 i) 32)):
                       @template}))
           default:
             invalid_pin_error ();
             break;
         }})

@INLINE
int pin_read (int pin_no)
{
  @(switch @{pin_no} i register
           @list{return @|register|->FIOPIN & (1 << (pin_no - @(* i 32)));})
  return 0;
}

@INLINE
void pin_write (int pin_no, int value)
{
  @(switch @{pin_no} i register
           @list{if (value) {
                   @|register|->FIOSET = (1 << (pin_no - @(* i 32)));
                 } else {
                   @|register|->FIOCLR = (1 << (pin_no - @(* i 32)));
                 }
                 break;})
}
           
@INLINE
void pin_dir (int pin_no, enum pin_dir dir)
{
  @(switch @{pin_no} i register
           @list{if (dir == PIN_OUT) {
                   @|register|->FIODIR @"|=" (1 << (pin_no - @(* i 32)));
                 } else {
                   @|register|->FIODIR @"&=" (1 << (pin_no - @(* i 32)));
                 }
                 break;})
}
           
#endif
