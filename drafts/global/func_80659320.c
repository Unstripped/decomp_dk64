// func_80659320 (src/global/5E020.c): matched: for (i = 0; i < 100; i++) on 100-entry pointer array triggers IDO unrolling
#include "common.h"

typedef struct Cam1_Node {
    s32 key;
    s32 value;
    struct Cam1_Node *next;
} Cam1_Node;

extern Cam1_Node *D_807F7370[];

void func_80659320(void) {
    s32 i;

    for (i = 0; i < 100; i++) {
        D_807F7370[i] = NULL;
    }
}
