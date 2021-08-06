#define uchar unsigned char
#define uint unsigned int
#define ulong unsigned long

#define CPU (10000000)
#define delay_us(x) (__delay_cycles((double)x*CPU/1000000.0))
#define delay_ms(x) (__delay_cycles((double)x*CPU/1000000.0))
#define delay_s(x)  (__delay_cycles((double)x*CPU/1000000.0))
#define u32 unsigned int
#define u16 unsigned short
#define u8  unsigned char
