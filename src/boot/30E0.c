#include "common.h"

extern s32 method;
extern s32 exit_code;
extern s32 huftPool;
extern u8 *inbuf;
extern u8 *slide;
extern s32 header_bytes;
extern s32 bytes_in;
extern s32 bytes_out;
extern s32 insize;
extern s32 inptr;
extern s32 outcnt;

s32 inflate(void);
s32 get_method(void);
void clear_bufs(void);

void gunzip(u8 **inBufPtr, u8 **outBufPtr, s32 huftStorage) {
    inbuf = *inBufPtr;
    slide = *outBufPtr;
    huftPool = huftStorage;
    clear_bufs();
    if (inbuf[inptr] != 0x1F) {
        inptr += 1;
    }
    method = get_method();
    if (method >= 0) {
        inflate();
        *inBufPtr += inptr;
        *outBufPtr += outcnt;
    }
}

s32 get_method(void) {
    s32 c;
    u8 flags;
    u32 len;

    inptr += 2;
    method = -1;
    header_bytes = 0;
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
    header_bytes = inptr + 8;
    return c;
}

u32 bi_reverse(u32 code, s32 bitCount) {
    u32 res = 0;

    do {
        res |= code & 1;
        code >>= 1, res <<= 1;
    } while (--bitCount > 0);
    return res >> 1;
}

void clear_bufs(void) {
    outcnt = 0;
    insize = inptr = 0;
    bytes_in = bytes_out = 0;
}
