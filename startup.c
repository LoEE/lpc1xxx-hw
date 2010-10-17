/*
 * ARM Cortex-M3 startup file for the NXP LPC13xx processors.
 *
 * Copyright (c) 2010 LoEE - Jakub Piotr Cłapa
 * This program is released under the new BSD license.
 */
#include "LPC17xx.h"

#define VECTORS \
  HANDLER(Reset) \
  WEAK_HANDLER(NMI) \
  WEAK_HANDLER(HardFault) \
  WEAK_HANDLER(MemManage) \
  WEAK_HANDLER(BusFault) \
  WEAK_HANDLER(UsageFault) \
  RESERVED \
  RESERVED \
  RESERVED \
  RESERVED \
  WEAK_HANDLER(SVC) \
  WEAK_HANDLER(DebugMon) \
  RESERVED \
  WEAK_HANDLER(PendSV) \
  WEAK_HANDLER(SysTick) \
  /* Vendor specific interrupts for the LPC13xx: */ \
  /* Wake-up pin interrupts (40 interrupts): */ \
  WEAK_HANDLER(WakeUp0_0) WEAK_HANDLER(WakeUp0_1) WEAK_HANDLER(WakeUp0_2) WEAK_HANDLER(WakeUp0_3) \
  WEAK_HANDLER(WakeUp0_4) WEAK_HANDLER(WakeUp0_5) WEAK_HANDLER(WakeUp0_6) WEAK_HANDLER(WakeUp0_7) \
  WEAK_HANDLER(WakeUp0_8) WEAK_HANDLER(WakeUp0_9) WEAK_HANDLER(WakeUp0_10) WEAK_HANDLER(WakeUp0_11) \
  \
  WEAK_HANDLER(WakeUp1_0) WEAK_HANDLER(WakeUp1_1) WEAK_HANDLER(WakeUp1_2) WEAK_HANDLER(WakeUp1_3) \
  WEAK_HANDLER(WakeUp1_4) WEAK_HANDLER(WakeUp1_5) WEAK_HANDLER(WakeUp1_6) WEAK_HANDLER(WakeUp1_7) \
  WEAK_HANDLER(WakeUp1_8) WEAK_HANDLER(WakeUp1_9) WEAK_HANDLER(WakeUp1_10) WEAK_HANDLER(WakeUp1_11) \
  \
  WEAK_HANDLER(WakeUp2_0) WEAK_HANDLER(WakeUp2_1) WEAK_HANDLER(WakeUp2_2) WEAK_HANDLER(WakeUp2_3) \
  WEAK_HANDLER(WakeUp2_4) WEAK_HANDLER(WakeUp2_5) WEAK_HANDLER(WakeUp2_6) WEAK_HANDLER(WakeUp2_7) \
  WEAK_HANDLER(WakeUp2_8) WEAK_HANDLER(WakeUp2_9) WEAK_HANDLER(WakeUp2_10) WEAK_HANDLER(WakeUp2_11) \
  \
  WEAK_HANDLER(WakeUp3_0) WEAK_HANDLER(WakeUp3_1) WEAK_HANDLER(WakeUp3_2) WEAK_HANDLER(WakeUp3_3) \
  \
  /* Other peripherals: */ \
  WEAK_HANDLER(I2C0) \
  WEAK_HANDLER(CT16B0) \
  WEAK_HANDLER(CT16B1) \
  WEAK_HANDLER(CT32B0) \
  WEAK_HANDLER(CT32B1) \
  WEAK_HANDLER(SSP) \
  WEAK_HANDLER(UART) \
  WEAK_HANDLER(USBIRQ) \
  WEAK_HANDLER(USBFIQ) \
  WEAK_HANDLER(ADC) \
  WEAK_HANDLER(WDT) \
  WEAK_HANDLER(BOD) \
  RESERVED \
  WEAK_HANDLER(PIO3) \
  WEAK_HANDLER(PIO2) \
  WEAK_HANDLER(PIO1) \
  WEAK_HANDLER(PIO0)

// Dummy handler.
void Default_Handler (void) { while (1); }

// Weakly bind most interrupt vectors to the dummy handler.
#define HANDLER(name) \
  void __attribute__((weak,externally_visible)) name##_Handler(void);
#define WEAK_HANDLER(name) \
  void __attribute__((weak,alias("Default_Handler"),externally_visible)) name##_Handler(void);
#define RESERVED
VECTORS
#undef HANDLER
#undef WEAK_HANDLER
#undef RESERVED

// Start of the stack (last RAM address; exported in the linker script)
extern char _sstack;

// The signature of Cortex-M3 interrupt handlers.
typedef void (* const Interrupt_Handler_P)(void);

// Interrupt vectors table
__attribute__ ((externally_visible,section(".cs3.interrupt_vector")))
Interrupt_Handler_P interrupt_vectors[] = {
  (void*)&_sstack,              // the first  word contains  the initial
                                // stack pointer  the hardware  loads it
                                // to the  SP register before  the first
                                // instruction
#define HANDLER(name) name##_Handler,
#define WEAK_HANDLER(name) name##_Handler,
#define RESERVED 0,
VECTORS
#undef HANDLER
#undef WEAK_HANDLER
#undef RESERVED
};

extern int main (void);
extern void setup_clocks (void);

extern uint32_t _etext, _sdata, _edata, _sbss, _ebss;

void
Reset_Handler(void)
{
  // Disabled due to PLL0 and PCLK settings interaction.
  // Run manualy when appropriate.
  //setup_clocks (); // Must be provided by the user

  uint32_t *s, *d;
  // Copy initialization data to RAM (.data section)
  s = &_etext;
  d = &_sdata;
  while (d < &_edata) *d++ = *s++;
  // Zero the remaining allocated RAM (.bss section)
  d = &_sbss;
  while (d < &_ebss)  *d++ = 0;
  
  // Everything is ready. Run the user program.
  main();
  while (1);
}
