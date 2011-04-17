/*
 * Timers.
 *
 * Copyright (c) 2008-2010 LoEE - Jakub Piotr Cłapa
 * This program is released under the new BSD license.
 */
#include "hw.h"

volatile uint32_t current_time = 0;

void SysTick_Handler (void)
{
  current_time++;
}

void delay (uint32_t interval)
{
  uint32_t start = current_time;
  while (current_time - start < interval);
}
