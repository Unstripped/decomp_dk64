#include "common.h"

typedef struct SynAllocAcmd {
    u32 w0;
    u32 w1;
} SynAllocAcmd;

typedef struct SynAllocResample {
    u8 pad0[0x8C];
    u8 pitch;
    u8 pad8D[2];
    s16 samples;
    s16 count;
    u8 pad94[4];
    void *state;
    u8 pad9C[0x1C];
    s32 flags;
    void *input;
} SynAllocResample;

extern s32 _decodeChunk(void *, s32, void *);
extern SynAllocAcmd *n_alSavePull(void *, s16 *, SynAllocAcmd *);
extern void func_8073BE54(void *, f32);

#pragma GLOBAL_ASM("asm/global/nonmatchings/145950/n_alResamplePull.s")

s32 alResampleParam(SynAllocResample *filter, s32 paramID, void *param) {
    void **arg = (void **)&param;

    switch (paramID) {
        case 4:
            filter->count = 0;
            _decodeChunk(filter, 4, param);
            break;
        case 0x12:
            filter->count = (s32)param;
            filter->flags |= 2;
            break;
        case 0x13:
            filter->samples = (s16)*(f32 *)arg;
            filter->flags |= 2;
            break;
        case 0x11:
            filter->pitch = (s32)param;
            break;
        default:
            _decodeChunk(filter, paramID, param);
            break;
    }
    return 0;
}
