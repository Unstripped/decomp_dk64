#include "common.h"
#include "proto/global/137120.h"

void alHeapInit(ALHeap *hp, u8 *base, s32 len) {
    hp->base = base;
    hp->len = len;
    hp->cur = hp->base;
    hp->count = 0;
}

void *alHeapDBAlloc(u8 *file, s32 line, ALHeap *hp, s32 num, s32 size) {
    s32 bytes;
    u8 *ptr = NULL;

    bytes = (num * size + 15) & ~15;
    if ((hp->cur + bytes) <= (hp->base + hp->len)) {
        ptr = hp->cur;
        hp->cur += bytes;
    } else {
    }
    return ptr;
}
