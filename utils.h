#define writel(x, y) *(volatile unsigned int *)(y) = (x)
#define readl(x) *(volatile unsigned int *)(x)
#define mdelay(s) udelay((s) * 1000)
void udelay(unsigned int usec);
