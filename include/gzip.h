#ifndef GZIP_H
#define GZIP_H

#include "common.h"

// gzip 1.2.4 decompressor state (upstream gzip.h) shared by boot/30E0 (gunzip, get_method,
// clear_bufs) and boot/1CC0 (inflate). Counts are unsigned as upstream declares them.
struct huft;

extern s32 method;            // compression method of the current member (8 = deflate)
extern s32 exit_code;
extern struct huft *huftPool; // caller-supplied storage for the Huffman tables
extern u8 *inbuf;             // compressed input
extern u8 *slide;             // output buffer (upstream window)
extern s32 header_bytes;      // gzip header and trailer size
extern s32 bytes_in;
extern s32 bytes_out;
extern u32 insize;
extern u32 inptr;             // read offset into inbuf
extern u32 outcnt;            // bytes written to slide

#endif
