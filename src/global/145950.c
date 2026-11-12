#include "common.h"
#include "audio_synth.h"
#include "proto/global/140600.h"
#include "proto/global/144E00.h"
#include "proto/global/145D70.h"

Acmd *n_alResamplePull(N_PVoice *filter, s16 *outp, s32 outCount, Acmd *p) {
    Acmd *result = p;
    s32 unused;
    f32 ratio;

    result = n_alSavePull(filter, outp, p);
    if ((filter->unk8C != 0) && (filter->unk8C < 0x40)) {
        Acmd *cmd;

        if (filter->unk8C >= 6) {
            ratio = 26755.0f / sqrtf((f32)filter->unk8C + 1.0f);
        } else {
            ratio = 65536.0f / ((f32)filter->unk8C + 1.0f);
        }
        if (ratio < 7723.0f) {
            ratio = 7723.0f;
        }
        cmd = result++;
        cmd->words.w0 = *outp & 0xFFFF;
        cmd->words.w1 = (((u32)ratio & 0xFFFF) << 16) | (u16)(filter->unk8C + 1);
    }
    if (filter->unk92 > 0) {
        if (filter->unkB8 != 0) {
            rebuildLowPassCoefficients(&filter->unk90, 22050.0f);
        }
        {
            Acmd *cmd;

            cmd = result++;
            cmd->words.w0 = 0x0B000020;
            cmd->words.w1 = osVirtualToPhysical(filter->unk98);
        }
        if (filter->unkB8 == 2) {
            filter->unkB8 = 0;
        }
        {
            Acmd *cmd;

            cmd = result++;
            cmd->words.w0 = 0x0E000000 | ((filter->unkB8 & 0xFF) << 16) | (*outp & 0xFFFF);
            cmd->words.w1 = (osVirtualToPhysical(filter->unkBC) & 0xFFFFFF) & 0xFFFFFF;
        }
        filter->unkB8 = 0;
    }
    return result;
}

s32 alResampleParam(N_PVoice *filter, s32 paramID, void *param) {
    void **arg = (void **)&param;

    switch (paramID) {
        case 4:
            filter->unk92 = 0;
            _decodeChunk(filter, 4, param);
            break;
        case 0x12:
            filter->unk92 = (s32)param;
            filter->unkB8 |= 2;
            break;
        case 0x13:
            filter->unk90 = (s16)*(f32 *)arg;
            filter->unkB8 |= 2;
            break;
        case 0x11:
            filter->unk8C = (s32)param;
            break;
        default:
            _decodeChunk(filter, paramID, param);
            break;
    }
    return 0;
}
