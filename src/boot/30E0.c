#include "common.h"

extern s32 method;
extern s32 exit_code;
extern s32 huftPool;
extern u8 *inbuf;
extern u8 *slide;
extern s32 D_80013ACC;
extern s32 D_80013AD8;
extern s32 D_80013ADC;
extern s32 insize;
extern s32 inptr;
extern s32 outcnt;

s32 inflate(void);
s32 get_method(void);
void clear_bufs(void);

void gunzip(u8 **arg0, u8 **arg1, s32 arg2) {
    inbuf = *arg0;
    slide = *arg1;
    huftPool = arg2;
    clear_bufs();
    if (inbuf[inptr] != 0x1F) {
        inptr += 1;
    }
    method = get_method();
    if (method >= 0) {
        inflate();
        *arg0 += inptr;
        *arg1 += outcnt;
    }
}

s32 get_method(void) {
    s32 c;
    u8 flags;
    u32 len;

    inptr += 2;
    method = -1;
    D_80013ACC = 0;
    c = method = inbuf[inptr++];
    if (c != 8) {
        exit_code = 1;
        return -1;
    }
    flags = inbuf[inptr++];
    inptr += 6;
    if (flags & 2) {
        inptr += 2;
    }
    if (flags & 4) {
        len = inbuf[inptr++];
        len |= inbuf[inptr++] << 8;
        inptr += len;
    }
    if (flags & 8) {
        while (inbuf[inptr++] != 0) {
        }
    }
    if (flags & 0x10) {
        while (inbuf[inptr++] != 0) {
        }
    }
    D_80013ACC = inptr + 8;
    return c;
}

u32 bi_reverse(u32 arg0, s32 arg1) {
    u32 res = 0;

    do {
        res |= arg0 & 1;
        arg0 >>= 1, res <<= 1;
    } while (--arg1 > 0);
    return res >> 1;
}

void clear_bufs(void) {
    outcnt = 0;
    insize = inptr = 0;
    D_80013AD8 = D_80013ADC = 0;
}
