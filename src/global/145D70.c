#include "common.h"

typedef struct SynAllocAcmd {
    u32 w0;
    u32 w1;
} SynAllocAcmd;

typedef struct SynAllocSave {
    u8 pad0[0x40];
    void *out;
    f32 ratio;
    s32 first;
    f32 fraction;
    s32 flags;
} SynAllocSave;

extern SynAllocAcmd *n_alAdpcmPull(void *, s16 *, s32, SynAllocAcmd *);
extern s32 _decodeChunk(void *, s32, void *);

#pragma GLOBAL_ASM("asm/global/nonmatchings/145D70/n_alSavePull.s")

s32 alSaveParam(void *filter, s32 paramID, void *param) {
    void *unused = filter;

    goto decode;

decode:
    _decodeChunk(filter, paramID, param);
    goto done;

done:
    return 0;
}
