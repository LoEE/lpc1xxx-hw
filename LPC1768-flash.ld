/*
 * This is the NXP LPC1768 linker file for code running from flash.
 *
 * TODO: 
 * - handle the exotic input sections (e.g. glue and veneer, C++ sections)
 * - add additional Ethernet and USB RAM memory regions (2x16k)
 * - add boot ROM memory regions
 *
 * See also: http://bitbucket.org/jpc/lpc17xx/
 *
 * Copyright (c) 2010 LoEE - Jakub Piotr Cłapa
 * This program is released under the new BSD license.
 */
MEMORY {
  flash (rx)  : ORIGIN = 0x00000000, LENGTH = 512K
  ram   (rwx) : ORIGIN = 0x10000000, LENGTH =  32K
}

INCLUDE flash.ldh
