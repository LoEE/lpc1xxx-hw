#ifndef SSP_H
#define SSP_H

#if defined(LPC12xx)
#define SSP_Regs LPC_SSP_Type
#define SSP0 ((SSP_Regs *)LPC_SSP)
#elif defined(LPC13xx)
#define SSP_Regs LPC_SSP_TypeDef
#define SSP0 ((SSP_Regs *)LPC_SSP0)
#define SSP1 ((SSP_Regs *)LPC_SSP1)
#else
#error Unknown processor family.
#endif



#define SSP_BITS enum { \
  DSS = 0, CPOL = 6, CPHA = 7, SCR = 8, /* CR0 */ \
  LBM = 0, SSE = 1, MS = 2, SOD = 3, /* CR1 */ \
  TFE = 0, TNF = 1, RNE = 2, RFF = 3, BSY = 4, /* SR */ \
}

enum {
  SSP_SLAVE  = 1 << 2,
  SSP_MASTER = 0 << 2,
};

INLINE
void ssp_setup_raw (SSP_Regs *SSP, int mode, int div1, int div2, int data_size, int cpol, int cpha)
{
  data_size--; div2--;

  SSP_BITS;

  SSP->CR1 = 0;
  SSP->CR0 = (data_size << DSS) | (cpol << CPOL) | (cpha << CPHA) | (div2 << SCR);
  SSP->CPSR = div1;
  SSP->CR1 = mode;
  SSP->CR1 = (1 << SSE) | mode;// | (1<<LBM) ;
}

INLINE
void ssp_setup (SSP_Regs *SSP, int mode, int div1, int div2, int data_size, int cpol, int cpha)
{
  if (mode != SSP_MASTER && mode != SSP_SLAVE) { ERROR ("Mode is not SSP_MASTER or SSP_SLAVE."); }
  if (data_size < 4 || data_size > 16) { ERROR ("Data size is out of range [4-16]."); }
  if (cpol != 0 && cpol != 1) { ERROR ("CPOL is not 1 or 0."); }
  if (cpha != 0 && cpha != 1) { ERROR ("CPHA is not 1 or 0."); }
  if (div1 < 2 || div1 > 254) { ERROR ("Divisor 1 is out of range [2-254]."); }
  if (div1 % 2 != 0) { ERROR ("Divisor 1 is not even."); }
  if (div2 < 1 || div2 > 256) { ERROR ("Divisor 2 is out of range [1-256]."); }

  ssp_setup_raw (SSP, mode, div1, div2, data_size, cpol, cpha);
}

int ssp_tx_empty (SSP_Regs *SSP);
int ssp_tx_full (SSP_Regs *SSP);
int ssp_rx_ready (SSP_Regs *SSP);
int ssp_busy (SSP_Regs *SSP);

int ssp_getc_nowait (SSP_Regs *SSP);
void ssp_putc_nowait (SSP_Regs *SSP, int c);

int ssp_getc (SSP_Regs *SSP);
void ssp_putc (SSP_Regs *SSP, int c);
int ssp_xchgc (SSP_Regs *SSP, int c);

void ssp_put (SSP_Regs *SSP, const void *x, int len);

#endif /* SSP_H */
