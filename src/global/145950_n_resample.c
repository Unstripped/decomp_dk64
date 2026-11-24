#include "common.h"
#include "audio_synth.h"
#include "proto/global/140600_syn_filter.h"
#include "proto/global/144E00_n_load.h"
#include "proto/global/145D70_n_save.h"

Acmd *n_alResamplePull(N_PVoice *filter, s16 *outp, s32 outCount, Acmd *p) {
    Acmd *result = p;
    s32 unused;
    f32 ratio;

    result = n_alSavePull(filter, outp, p);
    if ((filter->rspFxLevel != 0) && (filter->rspFxLevel < 0x40)) {
        Acmd *cmd;

        if (filter->rspFxLevel >= 6) {
            ratio = 26755.0f / sqrtf((f32)filter->rspFxLevel + 1.0f);
        } else {
            ratio = 65536.0f / ((f32)filter->rspFxLevel + 1.0f);
        }
        if (ratio < 7723.0f) {
            ratio = 7723.0f;
        }
        cmd = result++;
        cmd->words.w0 = *outp & 0xFFFF;
        cmd->words.w1 = (((u32)ratio & 0xFFFF) << 16) | (u16)(filter->rspFxLevel + 1);
    }
    if (filter->lowpass.fgain > 0) {
        if (filter->lowpass.first != 0) {
            rebuildLowPassCoefficients(&filter->lowpass, 22050.0f);
        }
        {
            Acmd *cmd;

            cmd = result++;
            cmd->words.w0 = 0x0B000020;
            cmd->words.w1 = osVirtualToPhysical(filter->lowpass.coeff);
        }
        if (filter->lowpass.first == 2) {
            filter->lowpass.first = 0;
        }
        {
            Acmd *cmd;

            cmd = result++;
            cmd->words.w0 = 0x0E000000 | ((filter->lowpass.first & 0xFF) << 16) | (*outp & 0xFFFF);
            cmd->words.w1 = (osVirtualToPhysical(filter->lowpassState) & 0xFFFFFF) & 0xFFFFFF;
        }
        filter->lowpass.first = 0;
    }
    return result;
}

s32 alResampleParam(N_PVoice *filter, s32 paramID, void *param) {
    void **arg = (void **)&param;

    switch (paramID) {
        case 4:
            filter->lowpass.fgain = 0;
            _decodeChunk(filter, 4, param);
            break;
        case 0x12:
            filter->lowpass.fgain = (s32)param;
            filter->lowpass.first |= 2;
            break;
        case 0x13:
            filter->lowpass.fc = (s16)*(f32 *)arg;
            filter->lowpass.first |= 2;
            break;
        case 0x11:
            filter->rspFxLevel = (s32)param;
            break;
        default:
            _decodeChunk(filter, paramID, param);
            break;
    }
    return 0;
}
