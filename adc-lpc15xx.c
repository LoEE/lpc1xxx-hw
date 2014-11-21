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
  ADC->INTEN = SEQAINTEN;
}

void adc_start_burst (ADC_Regs *ADC, int channels)
{
  ADC->SEQA_CTRL = channels | BURST | FULLSEQ | SEQEN;
}

void adc_start_single (ADC_Regs *ADC, int channel)
{
  ADC->SEQA_CTRL = (1 << channel) | START | FULLSEQ | SEQEN;
}

void adc_stop (ADC_Regs *ADC)
{
  ADC->SEQA_CTRL = 0;
}

void adc_flush_all (ADC_Regs *ADC)
{
  for(int i = 0; i < CHMAX; i++)
    adc_read(ADC, i);
}

int adc_ready (ADC_Regs *ADC, int channel)
{
  return ADC->FLAGS & SEQAINT;
}

struct adc_result adc_read (ADC_Regs *ADC, int channel)
{
  uint32_t stat = ADC->DAT[channel];
  return (struct adc_result){
    .value = (stat & RESULTMASK) >> RESULTs,
    .overrun = stat & OVERRUN,
  };
}
