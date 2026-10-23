// func_80659320 (src/global/5E020.c): stage 5, score 70: unrolled pointer loop zeroing 100 entries, v0/v1 swap and store order
#include "common.h"

extern void *D_807F7370[100];
extern void *D_807F7500;

void func_80659320(void) {
    void **p = D_807F7370;

    do {
        *p++ = NULL;
        *p++ = NULL;
        *p++ = NULL;
        *p++ = NULL;
    } while (p != (void **)&D_807F7500);
}
