#include "common.h"
#include "proto/global/140600.h"
#include "proto/global/145D70.h"

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

SynAllocAcmd *n_alResamplePull(SynAllocResample *filter, s16 *outp, s32 outCount, SynAllocAcmd *p) {
    SynAllocAcmd *result = p;
    s32 unused;
    f32 ratio;

    result = n_alSavePull(filter, outp, p);
    if ((filter->pitch != 0) && (filter->pitch < 0x40)) {
        SynAllocAcmd *cmd;

        if (filter->pitch >= 6) {
            ratio = 26755.0f / sqrtf((f32)filter->pitch + 1.0f);
        } else {
            ratio = 65536.0f / ((f32)filter->pitch + 1.0f);
        }
        if (ratio < 7723.0f) {
            ratio = 7723.0f;
        }
        cmd = result++;
        cmd->w0 = *outp & 0xFFFF;
        cmd->w1 = (((u32)ratio & 0xFFFF) << 16) | (u16)(filter->pitch + 1);
    }
    if (filter->count > 0) {
        if (filter->flags != 0) {
            rebuildLowPassCoefficients(&filter->samples, 22050.0f);
        }
        {
            SynAllocAcmd *cmd;

            cmd = result++;
            cmd->w0 = 0x0B000020;
            cmd->w1 = osVirtualToPhysical(&filter->state);
        }
        if (filter->flags == 2) {
            filter->flags = 0;
        }
        {
            SynAllocAcmd *cmd;

            cmd = result++;
            cmd->w0 = 0x0E000000 | ((filter->flags & 0xFF) << 16) | (*outp & 0xFFFF);
            cmd->w1 = (osVirtualToPhysical(filter->input) & 0xFFFFFF) & 0xFFFFFF;
        }
        filter->flags = 0;
    }
    return result;
}

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
