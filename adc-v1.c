/*
   ADC functions for NXP LPC1xxx processors.

   For more details see:
       https://bitbucket.org/LoEE/lpc1xxx-hw/

   Copyright (c) 2011-2012 Marcin Górski - LoEE
   Copyright (c) 2012-2014 LoEE - Jakub Piotr Cłapa
   This program is released under the new BSD license.
 */
void adc_enable_ints (ADC_Regs *ADC, int channels)
{
  ADC->INTEN = channels & 0xff;
}

void adc_start_burst (ADC_Regs *ADC, int channels)
{
  ADC->CR = (ADC->CR & ~CHMASK) | (channels) << CH | 1 << BURST;
}

void adc_start_single (ADC_Regs *ADC, int channel)
{
  ADC->CR = (ADC->CR & ~CHMASK) | 1 << (channel + CH) | 1 << START;
}

void adc_stop (ADC_Regs *ADC)
{
  ADC->CR = ADC->CR & ~(1 << BURST) & ~(1 << START);
}

void adc_flush_all (ADC_Regs *ADC)
{
  for(int i = 0; i < CHMAX; i++)
    adc_read(ADC, i);
}

int adc_ready (ADC_Regs *ADC, int channel)
{
  return ADC->STAT & (1 << channel);
}

int adc_ready_channels (ADC_Regs *ADC)
{
  return ADC->STAT & CHMASK;
}

struct adc_result adc_read (ADC_Regs *ADC, int channel)
{
  volatile const uint32_t *REG = &ADC->DR[0] + channel;
  uint32_t stat = *REG;
  return (struct adc_result){
    .value = (stat & RESULTMASK) >> RESULT,
    .overrun = stat & OVERRUN,
  };
}
