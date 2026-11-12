#include "common.h"
#include "audio_synth.h"
#include "proto/global/144E00.h"

Acmd *n_alSavePull(N_PVoice *filter, s16 *outp, Acmd *p) {
    Acmd *result = p;
    s16 samples = 0x170;
    s32 whole;
    s32 value;
    f32 temp;

    if (filter->rs_upitch != 0) {
        Acmd *cmd;

        result = n_alAdpcmPull(filter, &samples, 0xB8, p);
        cmd = result++;
        cmd->words.w0 = 0x0A000000 | (samples & 0xFFFFFF);
        cmd->words.w1 = ((*outp & 0xFFFF) << 16) | 0x170;
    } else {
        Acmd *cmd;

        if (filter->rs_ratio > 1.99995999999999996) {
            filter->rs_ratio = 1.999959946f;
        }
        filter->rs_ratio = (s32)(filter->rs_ratio * 32768.0f);
        filter->rs_ratio = filter->rs_ratio / 32768.0f;
        temp = filter->rs_delta + filter->rs_ratio * 184.0f;
        whole = (s32)temp;
        filter->rs_delta = temp - (f32)whole;
        result = n_alAdpcmPull(filter, &samples, whole, p);
        value = (s32)(filter->rs_ratio * 32768.0f);
        cmd = result++;
        cmd->words.w0 = 0x05000000 | (osVirtualToPhysical(filter->rs_state) & 0xFFFFFF);
        cmd->words.w1 = ((filter->rs_first & 3) << 30) | ((value & 0xFFFF) << 14) | ((samples & 0xFFF) << 2);
        filter->rs_first = 0;
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
