#include "common.h"
#include "audio_synth.h"
#include "proto/global/1435C0.h"
#include "proto/global/1445A0.h"

extern N_ALSynth *n_syn;

Acmd *n_alAuxBusPull(s32 time, Acmd *cmdList, s32 busIndex, s32 *outCount) {
    Acmd *ptr;
    N_ALAuxBus *bus;
    N_PVoice **pvoices;
    s32 i;
    s32 count;
    u32 max;
    u32 ratio;

    ptr = cmdList;
    bus = n_syn->auxBus + busIndex;
    pvoices = bus->sources;
    count = 0;
    max = 1;
    {
        Acmd *cmd;

        cmd = ptr++;
        cmd->words.w0 = 0x020007C0;
        cmd->words.w1 = 0x2E0;
    }
    *outCount = 0;
    for (i = 0; i < bus->sourceCount; i++) {
        if ((pvoices[i]->vvoice != NULL) && (pvoices[i]->vvoice->fxBus == busIndex) && (pvoices[i]->vvoice->pvoice != NULL) && (pvoices[i]->vvoice->pvoice->unk8C >= 0x40)) {
            ptr = n_alEnvmixerPull(pvoices[i], time, ptr);
            (*outCount)++;
            count++;
            if (pvoices[i]->vvoice->pvoice->unk8C > max) {
                max = pvoices[i]->vvoice->pvoice->unk8C;
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
    for (i = 0; i < bus->sourceCount; i++) {
        if (((pvoices[i]->vvoice != NULL) && (pvoices[i]->vvoice->fxBus == busIndex) &&
             ((pvoices[i]->vvoice->pvoice == NULL) || (pvoices[i]->vvoice->pvoice->unk8C < 0x40))) ||
            ((pvoices[i]->vvoice == NULL) && (busIndex == 0))) {
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
