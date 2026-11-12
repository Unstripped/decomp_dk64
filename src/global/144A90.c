#include "common.h"
#include "audio_synth.h"
#include "proto/global/140600.h"

extern N_ALSynth *n_syn;
extern u8 D_807FF0F4[];
extern u8 D_807FF0F6[];

Acmd *n_alMainBusPull(s32 sampleCount, Acmd *ptr) {
    Acmd *result;
    s32 i;
    s32 unused;
    result = ptr;
    {
        Acmd *cmd;

        cmd = result++;
        cmd->words.w0 = 0x020004E0;
        cmd->words.w1 = 0x2E0;
    }
    if (n_syn->maxAuxBusses > (i = 0)) {
        do {
            result = n_syn->mainBus->handler(sampleCount, result, i);
            if (D_807FF0F4[i] != 0) {
                if (D_807FF0F6[i] != 0) {
                    Acmd *cmd;

                    cmd = result++;
                    cmd->words.w0 = 0x0C008000;
                    cmd->words.w1 = 0x07C004E0;
                } else {
                    Acmd *cmd;

                    cmd = result++;
                    cmd->words.w0 = 0x0C007FFF;
                    cmd->words.w1 = 0x07C00650;
                }
            } else {
                if (D_807FF0F6[i] != 0) {
                    Acmd *cmd;

                    cmd = result++;
                    cmd->words.w0 = 0x0C008000;
                    cmd->words.w1 = 0x07C00650;
                } else {
                    Acmd *cmd;

                    cmd = result++;
                    cmd->words.w0 = 0x0C007FFF;
                    cmd->words.w1 = 0x07C00650;
                }
                {
                    Acmd *cmd;

                    cmd = result++;
                    cmd->words.w0 = 0x0C007FFF;
                    cmd->words.w1 = 0x07C004E0;
                }
            }
            if (n_syn->auxBus[i].filter->lp.fgain > 0) {
                SynLPFilter *fx;

                fx = n_syn->auxBus[i].filter;
                if (fx->lp.first != 0) {
                    rebuildLowPassCoefficients(&fx->lp, (f32)n_syn->outputRate);
                }
                {
                    Acmd *cmd;

                    cmd = result++;
                    cmd->words.w0 = 0x0B000020;
                    cmd->words.w1 = osVirtualToPhysical(fx->lp.coeff);
                }
                {
                    Acmd *cmd;

                    cmd = result++;
                    cmd->words.w0 = 0x0E0004E0;
                    cmd->words.w1 = (u32)osVirtualToPhysical(fx->fstate[0]) & 0xFFFFFF & 0xFFFFFF;
                }
                {
                    Acmd *cmd;

                    cmd = result++;
                    cmd->words.w0 = 0x0E000650;
                    cmd->words.w1 = (u32)osVirtualToPhysical(fx->fstate[1]) & 0xFFFFFF & 0xFFFFFF;
                }
                fx->lp.first = 0;
            }
        } while (++i < n_syn->maxAuxBusses);
    }
    return result;
}
