#ifndef HEAP_H
#define HEAP_H

#include "common.h"

// Header in front of every heap block; the payload starts at (HeapBlock *)block + 1.
// Free blocks sit on their pool's address-sorted free list (next/prev). While a block is
// allocated, byte 0xB (payload[-5]) holds its tag: 0 normal, 1 locked (never freed),
// 2 survives an overlay load.
typedef struct HeapBlock {
    /* 0x00 */ struct HeapBlock *physPrev; // physically preceding block in the arena
    /* 0x04 */ s32 size;                   // payload bytes
    /* 0x08 */ struct HeapBlock *next;     // next free block
    /* 0x0C */ struct HeapBlock *prev;     // previous free block
} HeapBlock; // size = 0x10

// One arena: pool 0 is the general best-fit heap, the others fixed-size block pools.
typedef struct HeapPool {
    /* 0x00 */ void *owner;      // handle variable that refers to this pool
    /* 0x04 */ u8 *start;
    /* 0x08 */ HeapBlock *freeList;
    /* 0x0C */ s32 size;
    /* 0x10 */ u16 blockSize;    // 0 for the general heap
} HeapPool; // size = 0x14

// Block waiting to be freed once its frame delay runs out.
typedef struct DeferredFree {
    /* 0x00 */ void *ptr;
    /* 0x04 */ u8 delay;
} DeferredFree; // size = 0x8

#endif
