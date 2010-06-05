/*
 * This is the NXP LPC1752 linker file for code running from flash.
 *
 * TODO: 
 * - handle the exotic input sections (e.g. glue and veneer, C++ sections)
 * - add boot ROM memory regions
 *
 * See also: http://bitbucket.org/jpc/lpc17xx/
 *
 * Copyright (c) 2010 LoEE - Jakub Piotr Cłapa
 * This program is released under the new BSD license.
 */
MEMORY {
  flash (rx)  : ORIGIN = 0x00000000, LENGTH = 64K
  ram   (rwx) : ORIGIN = 0x10000000, LENGTH = 16K
}

INCLUDE flash.ldh
