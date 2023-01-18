#define TIMER23_BASE 0xF8A29000
void udelay(unsigned int usecs)
{
	unsigned int clocks = usecs / 2 * 3;
	volatile unsigned int *ptr = (volatile unsigned int *)TIMER23_BASE;
	ptr[2] = 7; // freq / 16 = 1.5MHz, 32bit
	ptr[0] = clocks;
	ptr[2] = 0x87;
	while(ptr[1]);
}
