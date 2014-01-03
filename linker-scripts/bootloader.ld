/*
   This is the linker file fragment for code running from flash
   on NXP LPC17xx family of microprocessors. It lacks MEMORY declarations
   so it must be included from an apropriate model-specific file.

   TODO:
   - handle the exotic input sections (e.g. glue and veneer, C++ sections)
   - add boot ROM memory regions

   This is an automatically generated file. For more details see:
       http://bitbucket.org/jpc/lpc1xxx-hw/

   Copyright (c) 2010-2011 LoEE - Jakub Piotr Cłapa
   This program is released under the new BSD license.
*/

OUTPUT_FORMAT("elf32-littlearm")
OUTPUT_ARCH(arm)

ENTRY(Reset_Handler)

SECTIONS {
  . = 0;

  .text 0x1000 : {
    _stext = .;
    KEEP(*(.cs3.interrupt_vector))
    KEEP(*(SORT_BY_NAME(.before*)))
    *(SORT_BY_ALIGNMENT(SORT_BY_NAME(.text*)))
    *(SORT_BY_ALIGNMENT(SORT_BY_NAME(.rodata*)))
    KEEP(*(SORT_BY_NAME(.after*)))
    . = ALIGN(4);
    _etext = .;
  } > FLASH

  .data : {
    _sdata = .;
    *(SORT_BY_ALIGNMENT(SORT_BY_NAME(.data*)))
    . = ALIGN(4);
    _edata = .;
  } > SRAM AT > FLASH

  .bss : {
    *(SORT_BY_ALIGNMENT(SORT_BY_NAME(.bss*)))
    *(SORT_BY_ALIGNMENT(SORT_BY_NAME(COMMON)))
    . = ALIGN(4);
    _ebss = .;
  } > SRAM

  _sstack = ORIGIN(SRAM) + LENGTH(SRAM) - 32; /* 32 bytes for IAP */
}