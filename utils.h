#define writel(val, addr) *(volatile unsigned int *)(addr) = (val)
#define readl(addr) *(volatile unsigned int *)(addr)
#define mdelay(s) udelay((s) * 1000)
void udelay(unsigned int usec);
void _Noreturn panic(void);
