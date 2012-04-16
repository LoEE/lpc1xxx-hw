#include "hw.h"

SSP_BITS;

int ssp_tx_empty (SSP_TypeDef *SSP)
{
  return SSP->SR & (1 << TFE);
}

int ssp_tx_full (SSP_TypeDef *SSP)
{
  return !(SSP->SR & (1 << TNF));
}

int ssp_rx_ready (SSP_TypeDef *SSP)
{
  return SSP->SR & (1<<RNE);
}

int ssp_busy (SSP_TypeDef *SSP)
{
  return SSP->SR & (1<<BSY);
}

int ssp_getc_nowait (SSP_TypeDef *SSP)
{
  return SSP->DR;
}

void ssp_putc_nowait (SSP_TypeDef *SSP, int c)
{
  SSP->DR = c;
}

NOINLINE
int ssp_getc (SSP_TypeDef *SSP)
{
  while (!ssp_rx_ready (SSP));
  return ssp_getc_nowait (SSP);
}

NOINLINE
void ssp_putc (SSP_TypeDef *SSP, int c)
{
  while (ssp_tx_full (SSP));
  ssp_putc_nowait (SSP, c);
}

int ssp_xchgc (SSP_TypeDef *SSP, int c)
{
  ssp_putc (SSP, c);
  return ssp_getc (SSP);
}

void ssp_put (SSP_TypeDef *SSP, const void *x, int len)
{
  const char *s = x;
  while (len--)
    ssp_putc (SSP, *s++);
}
