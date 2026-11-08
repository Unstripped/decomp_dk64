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

extern SynAllocSynthFx *n_syn;
extern void n_alFxNew(void *, void *, s16, void *);

void *n_alSynNewFx(s16 fxId, void *c, void *bus) {
    n_alFxNew(&n_syn->fx[fxId].result, c, fxId, bus);
    return n_syn->fx[fxId].result;
}
