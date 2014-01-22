/*
   This is the NXP LPC1765 linker file for code running from flash.

   TODO:
   - handle the exotic input sections (e.g. glue and veneer, C++ sections)
   - add boot ROM memory regions

   This is an automatically generated file. For more details see:
       https://bitbucket.org/LoEE/lpc1xxx-hw/

   Copyright (c) 2010-2011 LoEE - Jakub Piotr Cłapa
   This program is released under the new BSD license.
*/

MEMORY {
  FLASH (rx)  : ORIGIN = 0x00000000, LENGTH = 256K
  SRAM (rwx) : ORIGIN = 0x10000000, LENGTH = 32K
  SRAM0 (rwx) : ORIGIN = 0x2007c000, LENGTH = 16K
  SRAM1 (rwx) : ORIGIN = 0x20080000, LENGTH = 16K
}

INCLUDE flash.ld