#include "common.h"

typedef struct SynAllocFx {
    u8 pad0[0x24];
    void *result;
    u8 pad28[0x20];
} SynAllocFx;

typedef struct SynAllocSynthFx {
    u8 pad0[0x34];
    SynAllocFx *fx;
} SynAllocSynthFx;

extern SynAllocSynthFx *D_807563E4;
extern void n_alFxNew(void *, void *, s16, void *);

void *func_8073D160(s16 arg0, void *arg1, void *arg2) {
    n_alFxNew(&D_807563E4->fx[arg0].result, arg1, arg0, arg2);
    return D_807563E4->fx[arg0].result;
}
