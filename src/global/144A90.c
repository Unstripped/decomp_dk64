#include "common.h"
#include "proto/global/140600.h"

typedef struct AdpcmNMAcmd {
    u32 w0;
    u32 w1;
} AdpcmNMAcmd;

typedef struct AdpcmNMFX {
    u8 pad0[2];
    s16 count;
    u8 pad4[0x24];
    void *unk28;
    void *unk2C;
    void *unk30;
} AdpcmNMFX;

typedef struct AdpcmNMAuxBus {
    u8 pad0[0x44];
    AdpcmNMFX *fx;
} AdpcmNMAuxBus;

typedef struct AdpcmNMMainBus {
    u8 pad0[4];
    AdpcmNMAcmd *(*pull)(s32, AdpcmNMAcmd *, s32);
} AdpcmNMMainBus;

typedef struct AdpcmNMSynth {
    u8 pad0[0x30];
    AdpcmNMMainBus *mainBus;
    AdpcmNMAuxBus *auxBuses;
    u8 pad38[4];
    s32 maxAuxBusses;
    s32 outputRate;
} AdpcmNMSynth;

extern AdpcmNMSynth *n_syn;
extern u8 D_807FF0F4[];
extern u8 D_807FF0F6[];

AdpcmNMAcmd *n_alMainBusPull(s32 sampleCount, AdpcmNMAcmd *ptr) {
    AdpcmNMAcmd *result;
    s32 i;
    s32 unused;
    result = ptr;
    {
        AdpcmNMAcmd *cmd;

        cmd = result++;
        cmd->w0 = 0x020004E0;
        cmd->w1 = 0x2E0;
    }
    if (n_syn->maxAuxBusses > (i = 0)) {
        do {
            result = n_syn->mainBus->pull(sampleCount, result, i);
            if (D_807FF0F4[i] != 0) {
                if (D_807FF0F6[i] != 0) {
                    AdpcmNMAcmd *cmd;

                    cmd = result++;
                    cmd->w0 = 0x0C008000;
                    cmd->w1 = 0x07C004E0;
                } else {
                    AdpcmNMAcmd *cmd;

                    cmd = result++;
                    cmd->w0 = 0x0C007FFF;
                    cmd->w1 = 0x07C00650;
                }
            } else {
                if (D_807FF0F6[i] != 0) {
                    AdpcmNMAcmd *cmd;

                    cmd = result++;
                    cmd->w0 = 0x0C008000;
                    cmd->w1 = 0x07C00650;
                } else {
                    AdpcmNMAcmd *cmd;

                    cmd = result++;
                    cmd->w0 = 0x0C007FFF;
                    cmd->w1 = 0x07C00650;
                }
                {
                    AdpcmNMAcmd *cmd;

                    cmd = result++;
                    cmd->w0 = 0x0C007FFF;
                    cmd->w1 = 0x07C004E0;
                }
            }
            if (n_syn->auxBuses[i].fx->count > 0) {
                AdpcmNMFX *fx;

                fx = n_syn->auxBuses[i].fx;
                if (fx->unk28 != 0) {
                    rebuildLowPassCoefficients(fx, (f32)n_syn->outputRate);
                }
                {
                    AdpcmNMAcmd *cmd;

                    cmd = result++;
                    cmd->w0 = 0x0B000020;
                    cmd->w1 = osVirtualToPhysical((u8 *)fx + 8);
                }
                {
                    AdpcmNMAcmd *cmd;

                    cmd = result++;
                    cmd->w0 = 0x0E0004E0;
                    cmd->w1 = (u32)osVirtualToPhysical(fx->unk2C) & 0xFFFFFF & 0xFFFFFF;
                }
                {
                    AdpcmNMAcmd *cmd;

                    cmd = result++;
                    cmd->w0 = 0x0E000650;
                    cmd->w1 = (u32)osVirtualToPhysical(fx->unk30) & 0xFFFFFF & 0xFFFFFF;
                }
                fx->unk28 = 0;
            }
        } while (++i < n_syn->maxAuxBusses);
    }
    return result;
}
