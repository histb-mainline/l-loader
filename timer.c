// SPDX-License-Identifier: GPL-2.0-or-later
/*
 * Copyright 2023 (r) Yang Xiwen <forbidden405@foxmail.com>
 *
 * Written based on Hi3798CV200 Datasheet 3 - System Chap.10 Timer
 * Tested on a Hi3798MV200 based SoC
 */
#include "utils.h"

#define TIMER23_BASE 0xF8A29000

#define TIMER_LOAD	0x0
#define TIMER_VALUE	0x4

#define TIMER_CONTROL	0x8
#define TIMER_ONESHOT		(1 << 0)

#define TIMER_TIMERSIZE_16BIT	(0 << 1)
#define TIMER_TIMERSIZE_32BIT	(1 << 1)

#define TIMER_TIMERPRE_MASK	(3 << 2)
#define TIMER_TIMERPRE_NODIV	(0 << 2)
#define TIMER_TIMERPRE_DIV16	(1 << 2)
#define TIMER_TIMERPRE_DIV256	(2 << 2)

#define TIMER_INTEN		(1 << 5)
#define TIMER_TIMERMODE_FREE	(0 << 6)
#define TIMER_TIMERMODE_CYCLE	(1 << 6)

#define TIMER_TIMEREN		(1 << 7)

#define TIMER_INTCLR	0xC
#define TIMER_RIS	0x10
#define TIMER_MIS	0x14
#define TIMER_BGLOAD	0x18
void udelay(unsigned int usecs)
{
	// error is less than 1 clock if executed in a raw program(1/24 usec)
	unsigned int clocks = usecs + usecs / 2; // freq is 1.5MHz, so to sleep x usecs, we need to wait 1.5x clocks.
	unsigned long base = TIMER23_BASE;
	int val;

	if(clocks < usecs) panic(); // multiply overflow
	// Step 1: set counting mode(one shot, divide by 16, 32 bit)
	val = TIMER_ONESHOT \
	      | TIMER_TIMERSIZE_32BIT \
	      | TIMER_TIMERPRE_DIV16 \
	      | TIMER_TIMERMODE_FREE;
	writel(val, base + TIMER_CONTROL); // freq(24MHz) / 16 = 1.5MHz, 32bit

	// Step 2: set init value, and wait until TIMERx_VALUE updates since PCLK is significantly slower than CPU( 24 MHz vs. 1600 MHz)
	writel(clocks, base + TIMER_LOAD);
	while(readl(base + TIMER_VALUE) != clocks);

	// Step 3: start timer, and wait until 0
	val |= TIMER_TIMEREN;
	writel(val, base + TIMER_CONTROL);
	while(readl(base + TIMER_VALUE) != 0);

	// End: clear interrupt
	writel(0, base + TIMER_INTCLR);

	return;
}
