/*
 * Timers.
 *
 * Copyright (c) 2008-2011 LoEE - Jakub Piotr Cłapa
 * This program is released under the new BSD license.
 */
#ifndef TIME_H
#define TIME_H

typedef struct timer {
  uint32_t start;
  uint32_t interval;
} timer;

#define STOPPED_TIMER {0,-1}

void timer_start (timer *ti, uint32_t interval);
void timer_stop (timer *ti);
int timer_expired (timer *ti);
int timer_stopped (timer *ti);
void delay (uint32_t interval);
uint32_t current_time (void);

// Special case because SysTick_Config is static inline
static inline
void time_init (int divider)
{
  if (SysTick_Config (divider)) ERROR("Impossible SysTick reload value.");
}

#endif /* TIME_H */
