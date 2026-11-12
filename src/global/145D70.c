#include "common.h"
#include "proto/global/144E00.h"

typedef struct SynAllocSave {
    u8 pad0[0x40];
    void *out;
    f32 ratio;
    s32 first;
    f32 fraction;
    s32 flags;
} SynAllocSave;


Acmd *n_alSavePull(SynAllocSave *filter, s16 *outp, Acmd *p) {
    Acmd *result = p;
    s16 samples = 0x170;
    s32 whole;
    s32 value;
    f32 temp;

    if (filter->first != 0) {
        Acmd *cmd;

        result = n_alAdpcmPull(filter, &samples, 0xB8, p);
        cmd = result++;
        cmd->words.w0 = 0x0A000000 | (samples & 0xFFFFFF);
        cmd->words.w1 = ((*outp & 0xFFFF) << 16) | 0x170;
    } else {
        Acmd *cmd;

        if (filter->ratio > 1.99995999999999996) {
            filter->ratio = 1.999959946f;
        }
        filter->ratio = (s32)(filter->ratio * 32768.0f);
        filter->ratio = filter->ratio / 32768.0f;
        temp = filter->fraction + filter->ratio * 184.0f;
        whole = (s32)temp;
        filter->fraction = temp - (f32)whole;
        result = n_alAdpcmPull(filter, &samples, whole, p);
        value = (s32)(filter->ratio * 32768.0f);
        cmd = result++;
        cmd->words.w0 = 0x05000000 | (osVirtualToPhysical(filter->out) & 0xFFFFFF);
        cmd->words.w1 = ((filter->flags & 3) << 30) | ((value & 0xFFFF) << 14) | ((samples & 0xFFF) << 2);
        filter->flags = 0;
    }
    return result;
}

s32 alSaveParam(void *filter, s32 paramID, void *param) {
    void *unused = filter;

    switch (paramID) {
    default:
        _decodeChunk(filter, paramID, param);
        break;
    }
    return 0;
}
