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

#define ADC_BITS enum {                        \
  CH = 0, CHMASK = 0xff, CHMAX = 8,            \
  CLKDIV = 8, BURST = 16, CLKS = 17, START=24, \
  RESULT = 6, RESULTMASK = (0x3ff<<RESULT),    \
  OVERRUN = 1 << 30,                           \
}

INLINE
void adc_setup_raw (ADC_TypeDef *ADC, int div, int resolution)
{
  ADC_BITS;

  ADC->CR = (div - 1) << CLKDIV | (10 - resolution) << CLKS;
}

INLINE
void adc_setup (ADC_TypeDef *ADC, int system_clock, int resolution)
{
  if (resolution < 3 || resolution > 10) ERROR("Invalid resolution [3 <= resolution <= 10].");
  int div = (system_clock + 4.49e6) / 4.5e6;
  if (div < 1 || div > 256) ERROR("Cannot find a valid clock divider [1 <= div <= 256].");

  adc_setup_raw(ADC, div, resolution);
}

void adc_enable_ints (ADC_TypeDef *ADC, int channels);
void adc_start_burst (ADC_TypeDef *ADC, int channels);
void adc_start_single (ADC_TypeDef *ADC, int channel);
void adc_stop (ADC_TypeDef *ADC);
void adc_flush_all (ADC_TypeDef *ADC);
int adc_ready (ADC_TypeDef *ADC, int channel);
int adc_ready_channels (ADC_TypeDef *ADC);

struct adc_result {
  int value;
  int overrun;
};

struct adc_result adc_read (ADC_TypeDef *ADC, int channel);

#endif
