#include "common.h"
#include "proto/global/1435C0.h"
#include "proto/global/1445A0.h"

typedef struct AuxResample {
    u8 pad0[0x8C];
    u8 pitch;
} AuxResample;

typedef struct AuxPVoiceEnv {
    u8 pad0[8];
    AuxResample *resample;
    u8 padC[0xC];
    s16 time;
} AuxPVoiceEnv;

typedef struct AuxPVoice {
    u8 pad0[8];
    AuxPVoiceEnv *env;
} AuxPVoice;

typedef struct AuxBus {
    u8 pad0[0x14];
    u32 count;
    s32 capacity;
    AuxPVoice **pvoices;
    u8 pad20[0x24];
    void *filter;
} AuxBus;

typedef struct AuxSynth {
    u8 pad0[0x34];
    AuxBus *buses;
} AuxSynth;

extern AuxSynth *n_syn;

Acmd *n_alAuxBusPull(s32 time, Acmd *cmdList, s32 busIndex, s32 *outCount) {
    Acmd *ptr;
    AuxBus *bus;
    AuxPVoice **pvoices;
    s32 i;
    s32 count;
    u32 max;
    u32 ratio;

    ptr = cmdList;
    bus = n_syn->buses + busIndex;
    pvoices = bus->pvoices;
    count = 0;
    max = 1;
    {
        Acmd *cmd;

        cmd = ptr++;
        cmd->words.w0 = 0x020007C0;
        cmd->words.w1 = 0x2E0;
    }
    *outCount = 0;
    for (i = 0; i < bus->count; i++) {
        if ((pvoices[i]->env != NULL) && (pvoices[i]->env->time == busIndex) && (pvoices[i]->env->resample != NULL) && (pvoices[i]->env->resample->pitch >= 0x40)) {
            ptr = n_alEnvmixerPull(pvoices[i], time, ptr);
            (*outCount)++;
            count++;
            if (pvoices[i]->env->resample->pitch > max) {
                max = pvoices[i]->env->resample->pitch;
            }
        }
    }
    if (count != 0) {
        max -= 0x3E;
        if (max >= 7) {
            ratio = (u32)(26755.0f / sqrtf((f32)max));
        } else {
            ratio = (u32)(65536.0f / (f32)max);
        }
        {
            Acmd *cmd;

            cmd = ptr++;
            cmd->words.w0 = 0x4E0;
            cmd->words.w1 = ((ratio & 0xFFFF) << 16) | (max & 0xFFFF);
        }
        {
            Acmd *cmd;

            cmd = ptr++;
            cmd->words.w0 = 0x650;
            cmd->words.w1 = ((ratio & 0xFFFF) << 16) | (max & 0xFFFF);
        }
    }
    for (i = 0; i < bus->count; i++) {
        if (((pvoices[i]->env != NULL) && (pvoices[i]->env->time == busIndex) &&
             ((pvoices[i]->env->resample == NULL) || (pvoices[i]->env->resample->pitch < 0x40))) ||
            ((pvoices[i]->env == NULL) && (busIndex == 0))) {
            Acmd *oldPtr;

            oldPtr = ptr;
            ptr = n_alEnvmixerPull(pvoices[i], time, ptr);
            if (ptr != oldPtr) {
                (*outCount)++;
            }
        }
    }
    return ptr;
}
