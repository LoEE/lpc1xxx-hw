/*
 * Timers.
 *
 * Copyright (c) 2008-2011 LoEE - Jakub Piotr Cłapa
 * This program is released under the new BSD license.
 */
#include "hw.h"

volatile uint32_t _current_time = 0;

void timer_start (timer *ti, uint32_t interval)
{
  ti->start = current_time();
  ti->interval = interval;
}

void timer_restart (timer *ti)
{
  ti->start = current_time();
}

void timer_advance (timer *ti)
{
  ti->start += ti->interval;
}

void timer_stop (timer *ti)
{
  timer_start (ti, 0xffffffff);
}

int timer_expired (timer *ti)
{
  return !timer_stopped (ti) && current_time() - ti->start >= ti->interval;
}

int timer_stopped (timer *ti)
{
  return ti->interval == 0xffffffff;
}

void delay (uint32_t interval)
{
  uint32_t start = current_time();
  while (current_time() - start < interval);
}

uint32_t current_time (void) {
  return _current_time;
}

void SysTick_Handler (void)
{
  _current_time++;
}
