/*
 * Timers.
 *
 * Copyright (c) 2008-2010 LoEE - Jakub Piotr Cłapa
 * This program is released under the new BSD license.
 */
#ifndef TIME_H
#define TIME_H

extern volatile uint32_t current_time;

typedef struct timer {
  uint32_t start;
  uint32_t interval;
} timer;

INLINE
void timer_start (timer *ti, uint32_t interval)
{
  ti->start = current_time;
  ti->interval = interval;
}

INLINE
int timer_expired (timer *ti)
{
  return current_time - ti->start >= ti->interval;
}

void delay (uint32_t interval);

// Special case because SysTick_Config is static inline
static inline
void time_init (int divider)
{
  if (SysTick_Config (divider)) ERROR("Impossible SysTick reload value.");
}

#endif /* TIME_H */
