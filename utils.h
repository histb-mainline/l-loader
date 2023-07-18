#define writel(val, addr) *(volatile unsigned int *)(y) = (x)
#define readl(addr) *(volatile unsigned int *)(x)
#define mdelay(s) udelay((s) * 1000)
void udelay(unsigned int usec);
void _Noreturn panic(void);
