#define TIMER23_BASE 0xF8A29000
void udelay(unsigned int usecs)
{
	// TODO use macros to replace magic numbers
	// error is less than 1 clock if executed in a raw program(1/24 usec)
	unsigned int clocks = usecs + usecs / 2; // freq is 1.5MHz, so to sleep x usecs, we need to wait 1.5x clocks.
	volatile unsigned int *ptr = (volatile unsigned int *)TIMER23_BASE;

	if(clocks < usecs) return; // multiply overflow
	// Step 1: set counting mode(one shot, divide by 16, 32 bit)
	ptr[2] = 7; // freq(24MHz) / 16 = 1.5MHz, 32bit
	
	// Step 2: set init value, and wait until TIMERx_VALUE updates since PCLK is significantly slower than CPU( 24 MHz vs. 1600 MHz
	ptr[0] = clocks;
	while(ptr[1] != clocks);

	// Step 3: start timer, and wait until 0
	ptr[2] = 0x87;
	while(ptr[1]);

	// End: clear interrupt
	ptr[3] = 0;

	return;
}
