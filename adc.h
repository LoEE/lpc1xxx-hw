/*
   ADC functions for NXP LPC1xxx processors.

   For more details see:
       http://bitbucket.org/jpc/lpc1xxx-hw/

   Copyright (c) 2011-2012 Marcin Górski - LoEE
   Copyright (c) 2012 LoEE - Jakub Piotr Cłapa
   This program is released under the new BSD license.
 */
#ifndef ADC_H
#define ADC_H

#if defined(LPC12xx)
#define ADC_Regs LPC_ADC_Type
#define ADC0 ((ADC_Regs *)LPC_ADC0)
#elif defined(LPC13xx)
#define ADC_Regs LPC_ADC_TypeDef
#define ADC0 ((ADC_Regs *)LPC_ADC0)
#elif defined(LPC17xx)
#define ADC_Regs LPC_ADC_TypeDef
#define ADC0 ((ADC_Regs *)LPC_ADC)
#else
#error Unknown processor family.
#endif


#define ADC_BITS enum {                        \
  CH = 0, CHMASK = 0xff, CHMAX = 8,            \
  CLKDIV = 8, BURST = 16, CLKS = 17, START=24, \
  RESULT = 6, RESULTMASK = (0x3ff<<RESULT),    \
  OVERRUN = 1 << 30,                           \
}

INLINE
void adc_setup_raw (ADC_Regs *ADC, int div, int resolution)
{
  ADC_BITS;

#if defined(LPC17xx)
  ADC->CR = (div - 1) << CLKDIV;
#else
  ADC->CR = (div - 1) << CLKDIV | (10 - resolution) << CLKS;
#endif
}

INLINE
void adc_setup (ADC_Regs *ADC, int system_clock, int resolution)
{
#if defined(LPC12xx)
  if (resolution != 10) ERROR("Invalid resolution [resolution is fixed at 10 bits in LPC12xx].");
  int div = (system_clock + 8.99e6) / 9e6;
#elif defined(LPC13xx)
  if (resolution < 3 || resolution > 10) ERROR("Invalid resolution [3 <= resolution <= 10].");
  int div = (system_clock + 4.49e6) / 4.5e6;
#elif defined(LPC17xx)
  if (resolution != 12) ERROR("Invalid resolution [resolution is fixed at 12 bits in LPC17xx].");
  int div = (system_clock + 19.99e6) / 13e6;
#else
  #error "Unknown processor type."
#endif
  if (div < 1 || div > 256) ERROR("Cannot find a valid clock divider [1 <= div <= 256].");

  adc_setup_raw(ADC, div, resolution);
}

void adc_enable_ints (ADC_Regs *ADC, int channels);
void adc_start_burst (ADC_Regs *ADC, int channels);
void adc_start_single (ADC_Regs *ADC, int channel);
void adc_stop (ADC_Regs *ADC);
void adc_flush_all (ADC_Regs *ADC);
int adc_ready (ADC_Regs *ADC, int channel);
int adc_ready_channels (ADC_Regs *ADC);

struct adc_result {
  int value;
  int overrun;
};

struct adc_result adc_read (ADC_Regs *ADC, int channel);

#endif
