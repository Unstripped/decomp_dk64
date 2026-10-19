#ifndef ULTRA64_H
#define ULTRA64_H

/* Subset of libultra 2.0L declarations, added as code needs them. */

typedef signed char s8;
typedef unsigned char u8;
typedef signed short s16;
typedef unsigned short u16;
typedef signed long s32;
typedef unsigned long u32;
typedef signed long long s64;
typedef unsigned long long u64;
typedef float f32;
typedef double f64;

#define NULL 0

#define OS_READ 0
#define OS_WRITE 1

#define PI_STATUS_DMA_BUSY (1 << 0)

void osInvalDCache(void *vaddr, s32 nbytes);
s32 osPiRawStartDma(s32 direction, u32 devAddr, void *dramAddr, u32 size);
u32 osPiGetStatus(void);

#endif
