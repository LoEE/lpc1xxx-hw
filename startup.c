/*
   ARM Cortex-M3 startup file for the NXP LPC1xxx processors.

   For more details see:
       https://bitbucket.org/LoEE/lpc1xxx-hw/

   Copyright (c) 2010-2011 LoEE - Jakub Piotr Cłapa
   This program is released under the new BSD license.
 */
#include "hw.h"

#define CM3_VECTORS \
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

#define CM0_VECTORS \
  HANDLER(Reset) \
  WEAK_HANDLER(NMI) \
  WEAK_HANDLER(HardFault) \
  RESERVED \
  RESERVED \
  RESERVED \
  RESERVED \
  RESERVED \
  RESERVED \
  RESERVED \
  WEAK_HANDLER(SVC) \
  WEAK_HANDLER(DebugMon) \
  RESERVED \
  WEAK_HANDLER(PendSV) \
  WEAK_HANDLER(SysTick) \

#define LPC17xx_VECTORS \
  /* Vendor specific interrupts for the LPC17xx: */ \
  WEAK_HANDLER(WDT)    \
  WEAK_HANDLER(TIMER0) \
  WEAK_HANDLER(TIMER1) \
  WEAK_HANDLER(TIMER2) \
  WEAK_HANDLER(TIMER3) \
  WEAK_HANDLER(UART0)  \
  WEAK_HANDLER(UART1)  \
  WEAK_HANDLER(UART2)  \
  WEAK_HANDLER(UART3)  \
  WEAK_HANDLER(PWM1)   \
  WEAK_HANDLER(I2C0)   \
  WEAK_HANDLER(I2C1)   \
  WEAK_HANDLER(I2C2)   \
  WEAK_HANDLER(SPI)    \
  WEAK_HANDLER(SSP0)   \
  WEAK_HANDLER(SSP1)   \
  WEAK_HANDLER(PLL0)   \
  WEAK_HANDLER(RTC)    \
  WEAK_HANDLER(EINT0)  \
  WEAK_HANDLER(EINT1)  \
  WEAK_HANDLER(EINT2)  \
  WEAK_HANDLER(EINT3GPIO) \
  WEAK_HANDLER(ADC)    \
  WEAK_HANDLER(BOD)    \
  WEAK_HANDLER(USB)    \
  WEAK_HANDLER(CAN)    \
  WEAK_HANDLER(GPDMA)  \
  WEAK_HANDLER(I2S)    \
  WEAK_HANDLER(ETHERNET) \
  WEAK_HANDLER(RIT)    \
  WEAK_HANDLER(MCPWM)  \
  WEAK_HANDLER(QENC)   \
  WEAK_HANDLER(PLL1)   \
  WEAK_HANDLER(USB_ACT) \
  WEAK_HANDLER(CAN_ACT)

#define LPC13xx_VECTORS \
  /* Vendor specific interrupts for the LPC13xx: */ \
  /* Wake-up pin interrupts (40 interrupts): */ \
  WEAK_HANDLER(WakeUpP0_0) WEAK_HANDLER(WakeUpP0_1) WEAK_HANDLER(WakeUpP0_2) WEAK_HANDLER(WakeUpP0_3) \
  WEAK_HANDLER(WakeUpP0_4) WEAK_HANDLER(WakeUpP0_5) WEAK_HANDLER(WakeUpP0_6) WEAK_HANDLER(WakeUpP0_7) \
  WEAK_HANDLER(WakeUpP0_8) WEAK_HANDLER(WakeUpP0_9) WEAK_HANDLER(WakeUpP0_10) WEAK_HANDLER(WakeUpP0_11) \
  \
  WEAK_HANDLER(WakeUpP1_0) WEAK_HANDLER(WakeUpP1_1) WEAK_HANDLER(WakeUpP1_2) WEAK_HANDLER(WakeUpP1_3) \
  WEAK_HANDLER(WakeUpP1_4) WEAK_HANDLER(WakeUpP1_5) WEAK_HANDLER(WakeUpP1_6) WEAK_HANDLER(WakeUpP1_7) \
  WEAK_HANDLER(WakeUpP1_8) WEAK_HANDLER(WakeUpP1_9) WEAK_HANDLER(WakeUpP1_10) WEAK_HANDLER(WakeUpP1_11) \
  \
  WEAK_HANDLER(WakeUpP2_0) WEAK_HANDLER(WakeUpP2_1) WEAK_HANDLER(WakeUpP2_2) WEAK_HANDLER(WakeUpP2_3) \
  WEAK_HANDLER(WakeUpP2_4) WEAK_HANDLER(WakeUpP2_5) WEAK_HANDLER(WakeUpP2_6) WEAK_HANDLER(WakeUpP2_7) \
  WEAK_HANDLER(WakeUpP2_8) WEAK_HANDLER(WakeUpP2_9) WEAK_HANDLER(WakeUpP2_10) WEAK_HANDLER(WakeUpP2_11) \
  \
  WEAK_HANDLER(WakeUpP3_0) WEAK_HANDLER(WakeUpP3_1) WEAK_HANDLER(WakeUpP3_2) WEAK_HANDLER(WakeUpP3_3) \
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

#define LPC122x_VECTORS \
  /* Vendor specific interrupts for the LPC122x: */ \
  /* Wake-up pin interrupts (12 interrupts): */ \
  WEAK_HANDLER(WakeUpP0_0) WEAK_HANDLER(WakeUpP0_1) WEAK_HANDLER(WakeUpP0_2) WEAK_HANDLER(WakeUpP0_3) \
  WEAK_HANDLER(WakeUpP0_4) WEAK_HANDLER(WakeUpP0_5) WEAK_HANDLER(WakeUpP0_6) WEAK_HANDLER(WakeUpP0_7) \
  WEAK_HANDLER(WakeUpP0_8) WEAK_HANDLER(WakeUpP0_9) WEAK_HANDLER(WakeUpP0_10) WEAK_HANDLER(WakeUpP0_11) \
  \
  /* Other peripherals: */ \
  WEAK_HANDLER(I2C0) \
  WEAK_HANDLER(CT16B0) \
  WEAK_HANDLER(CT16B1) \
  WEAK_HANDLER(CT32B0) \
  WEAK_HANDLER(CT32B1) \
  WEAK_HANDLER(SSP) \
  WEAK_HANDLER(UART0) \
  WEAK_HANDLER(UART1) \
  WEAK_HANDLER(CMP) \
  WEAK_HANDLER(ADC) \
  WEAK_HANDLER(WDT) \
  WEAK_HANDLER(BOD) \
  RESERVED \
  WEAK_HANDLER(PIO0) \
  WEAK_HANDLER(PIO1) \
  WEAK_HANDLER(PIO2) \
  RESERVED \
  WEAK_HANDLER(DMA) \
  WEAK_HANDLER(RTC) \
  RESERVED

#define LPC15xx_VECTORS \
  /* Vendor specific interrupts for the LPC15xx: */                                                \
  WEAK_HANDLER(WDT) WEAK_HANDLER(BOD) WEAK_HANDLER(FLASH) WEAK_HANDLER(EE) WEAK_HANDLER(DMA)       \
  WEAK_HANDLER(GINT0) WEAK_HANDLER(GINT1) WEAK_HANDLER(PIN_INT0) WEAK_HANDLER(PIN_INT1)            \
  WEAK_HANDLER(PIN_INT2) WEAK_HANDLER(PIN_INT3) WEAK_HANDLER(PIN_INT4) WEAK_HANDLER(PIN_INT5)      \
  WEAK_HANDLER(PIN_INT6) WEAK_HANDLER(PIN_INT7) WEAK_HANDLER(RIT) WEAK_HANDLER(SCT0)               \
  WEAK_HANDLER(SCT1) WEAK_HANDLER(SCT2) WEAK_HANDLER(SCT3) WEAK_HANDLER(MRT) WEAK_HANDLER(UART0)   \
  WEAK_HANDLER(UART1) WEAK_HANDLER(UART2) WEAK_HANDLER(I2C0) WEAK_HANDLER(SPI0) WEAK_HANDLER(SPI1) \
  WEAK_HANDLER(C_CAN0) WEAK_HANDLER(USB) WEAK_HANDLER(USB_FIQ) WEAK_HANDLER(USB_WAKEUP)            \
  WEAK_HANDLER(ADC0_SEQA) WEAK_HANDLER(ADC0_SEQB) WEAK_HANDLER(ADC0_THCMP) WEAK_HANDLER(ADC0_OVR)  \
  WEAK_HANDLER(ADC1_SEQA) WEAK_HANDLER(ADC1_SEQB) WEAK_HANDLER(ADC1_THCMP) WEAK_HANDLER(ADC1_OVR)  \
  WEAK_HANDLER(DAC) WEAK_HANDLER(CMP0) WEAK_HANDLER(CMP1) WEAK_HANDLER(CMP2) WEAK_HANDLER(CMP3)    \
  WEAK_HANDLER(QEI) WEAK_HANDLER(RTC_ALARM) WEAK_HANDLER(RTC_WAKE)                                 \

#if defined (LPC17xx)
#define VECTORS CM3_VECTORS LPC17xx_VECTORS
#elif defined (LPC13xx)
#define VECTORS CM3_VECTORS LPC13xx_VECTORS
#elif defined (LPC15xx)
#define VECTORS CM3_VECTORS LPC15xx_VECTORS
#elif defined (LPC122x)
#define VECTORS CM0_VECTORS LPC122x_VECTORS
#else
#error "Unknown processor type."
#endif

// Dummy handler.
void Default_Handler (void) { while (1); }

// Weakly bind most interrupt vectors to the dummy handler.
#define HANDLER(name) \
  void __attribute__((weak,externally_visible)) name##_Handler(void);
#ifndef WEAK_HANDLER_DEBUG
#define WEAK_HANDLER(name) \
  void __attribute__((weak,alias("Default_Handler"),externally_visible)) name##_Handler(void);
#else
#define WEAK_HANDLER(name) \
  void __attribute__((weak,externally_visible)) name##_Handler(void) { WEAK_HANDLER_DEBUG(#name); while(1); };
#endif
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

extern uint32_t _etext, _sdata, _edata, _sbss, _ebss;

void
Reset_Handler(void)
{
  uint32_t *s, *d;
  // Copy initialization data to RAM (.data section)
  s = &_etext;
  d = &_sdata;
  do *d++ = *s++; while (d < &_edata);
  // Zero the remaining allocated RAM (.bss section)
  d = &_edata;
  do *d++ = 0; while (d < &_ebss);

  // Everything is ready. Run the user program.
  main();
  while (1);
}
