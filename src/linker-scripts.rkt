#lang at-exp racket
(require scribble/text
         "common.rkt"
         "devices.rkt")

(define output-dir "../linker-scripts")

(define (main)
  (make-directory/remove output-dir)
  
  (parameterize ([current-directory output-dir])
    (for ([d (in-list devices)])
      (define fname (format "~a.ld" (device-model d)))
      (unless (file-exists? fname)
        (with-output-to-file fname
          (λ () (output (device-linker-script d))))))
    
    (with-output-to-file "flash.ld" (λ () (output (flash-linker-script))))
    (with-output-to-file "bootloader.ld" (λ () (output (bootloader-linker-script))))))

(define (TODO)
  @list{TODO: 
        - handle the exotic input sections (e.g. glue and veneer, C++ sections)
        - add boot ROM memory regions})

;;
;; Formatting
;;
(define (flash-linker-script)
  @list{
@header[url]{
        This is the linker file fragment for code running from flash 
        on NXP LPC17xx family of microprocessors. It lacks MEMORY declarations
        so it must be included from an apropriate model-specific file.
        
        @(TODO)}

OUTPUT_FORMAT("elf32-littlearm")
OUTPUT_ARCH(arm)

ENTRY(Reset_Handler)

SECTIONS {
  . = 0;

  .text : {
    _stext = .;
    KEEP(*(.cs3.interrupt_vector))
    *(SORT_BY_ALIGNMENT(SORT_BY_NAME(.text*)))
    *(SORT_BY_ALIGNMENT(SORT_BY_NAME(.rodata*)))
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
}})

(define (bootloader-linker-script)
  @list{
@header[url]{
        This is the linker file fragment for code running from flash 
        on NXP LPC17xx family of microprocessors. It lacks MEMORY declarations
        so it must be included from an apropriate model-specific file.
        
        @(TODO)}

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
}})

(define (device-linker-script d)
  @list{
@header[url]{
        This is the NXP @(device-model d) linker file for code running from flash.

        @(TODO)}

MEMORY {
  FLASH (rx)  : ORIGIN = 0x00000000, LENGTH = @format-size[(device-total-flash d)]
  @(add-newlines
    (for/list ([b (device-ram-map d)])
      @list{@(memory-block-name b) (rwx) : ORIGIN = 0x@(number->string (memory-block-addr b) 16), @;
            LENGTH = @(format-size (memory-block-size b))}))
}

INCLUDE flash.ld
})

(define (format-size n)
  (cond
    [(zero? (remainder n 1024)) @list{@[/ n 1024]K}]
    [else n]))

(main)
