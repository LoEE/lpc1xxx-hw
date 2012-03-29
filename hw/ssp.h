#ifndef SSP_H
#define SSP_H

#define SSP_BITS enum { \
  DSS = 0, CPOL = 6, CPHA = 7, SCR = 8, /* CR0 */ \
  LBM = 0, SSE = 1, MS = 2, SOD = 3, /* CR1 */ \
  TFE = 0, TNF = 1, RNE = 2, RFF = 3, BSY = 4, /* SR */ \
}

INLINE
void ssp_setup_raw (SSP_TypeDef *SSP, int div1, int div2, int data_size, int cpol, int cpha)
{
  data_size--; div2--;

  SSP_BITS;

  SSP->CR1 = 0;
  SSP->CR0 = (data_size << DSS) | (cpol << CPOL) | (cpha << CPHA) | (div2 << SCR);
  SSP->CPSR = div1;
  SSP->CR1 = (1 << SSE);// | (1<<LBM) ;
}

INLINE
void ssp_setup (SSP_TypeDef *SSP, int div1, int div2, int data_size, int cpol, int cpha)
{
  if (data_size < 4 || data_size > 16) { ERROR ("Data size is out of range [4-16]."); }
  if (cpol != 0 && cpol != 1) { ERROR ("CPOL is not 1 or 0."); }
  if (cpha != 0 && cpha != 1) { ERROR ("CPHA is not 1 or 0."); }
  if (div1 < 2 || div1 > 254) { ERROR ("Divisor 1 is out of range [2-254]."); }
  if (div1 % 2 != 0) { ERROR ("Divisor 1 is not even."); }
  if (div2 < 1 || div2 > 256) { ERROR ("Divisor 2 is out of range [1-256]."); }

  ssp_setup_raw (SSP, div1, div2, data_size, cpol, cpha);
}

int ssp_tx_empty (SSP_TypeDef *SSP);
int ssp_tx_full (SSP_TypeDef *SSP);
int ssp_rx_ready (SSP_TypeDef *SSP);
int ssp_busy (SSP_TypeDef *SSP);

int ssp_getc_nowait (SSP_TypeDef *SSP);
void ssp_putc_nowait (SSP_TypeDef *SSP, int c);

int ssp_getc (SSP_TypeDef *SSP);
void ssp_putc (SSP_TypeDef *SSP, int c);
int ssp_xchgc (SSP_TypeDef *SSP, int c);

void ssp_put (SSP_TypeDef *SSP, const void *x, int len);

#endif /* SSP_H */
