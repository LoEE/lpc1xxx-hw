/*
 * This is the NXP LPC1342 linker file for code running from flash.
 *
 * TODO: 
 * - add boot ROM memory regions
 *
 * See also: http://bb.loee.pl/lpc1xxx-hw
 *
 * Copyright (c) 2010 LoEE - Jakub Piotr Cłapa
 * This program is released under the new BSD license.
 */
MEMORY {
  flash (rx)  : ORIGIN = 0x00000000, LENGTH = 16K
  ram   (rwx) : ORIGIN = 0x10000200, LENGTH =  2K
}

INCLUDE flash.ldh
