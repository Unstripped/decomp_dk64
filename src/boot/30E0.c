#include "common.h"
#include "proto/boot/1CC0.h"
#include "proto/boot/30E0.h"
#include "gzip.h"

// gzip 1.2.4 (gzip.h, gzip.c) header constants
#define DEFLATED 8
#define ERROR 1

#define CONTINUATION 0x02 // part number present
#define EXTRA_FIELD 0x04  // extra field present
#define ORIG_NAME 0x08    // original file name present
#define COMMENT 0x10      // file comment present

void gunzip(u8 **inBufPtr, u8 **outBufPtr, void *huftStorage) {
    inbuf = *inBufPtr;
    slide = *outBufPtr;
    huftPool = huftStorage;
    clear_bufs();
    // optional one-byte prefix before the 1F 8B gzip magic
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
    u8 flags;
    u32 len;

    inptr += 2; // magic
    method = -1;
    header_bytes = 0;
    method = inbuf[inptr++];
    if (method != DEFLATED) {
        exit_code = ERROR;
        return -1;
    }
    flags = inbuf[inptr++];
    inptr += 6; // time stamp, extra flags, OS type
    if (flags & CONTINUATION) {
        inptr += 2;
    }
    if (flags & EXTRA_FIELD) {
        len = inbuf[inptr++];
        len |= inbuf[inptr++] << 8;
        inptr += len;
    }
    if (flags & ORIG_NAME) {
        while (inbuf[inptr++] != 0) {
        }
    }
    if (flags & COMMENT) {
        while (inbuf[inptr++] != 0) {
        }
    }
    header_bytes = inptr + 2 * sizeof(s32); // include crc and size
    return method;
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
