#include "common.h"
#include "proto/global/137120.h"
#include "proto/global/13E160.h"
#include "audio_config.h"
#include "audio_synth.h"
#include "proto/global/140600.h"
#include "proto/global/1435C0.h"
#include "proto/global/166A0.h"


extern N_ALSynth *n_syn;

void n_alSynSetPitch(ALVoice *voice, f32 pitch) {
    SynCoreParam *param;

    if (voice->pvoice != NULL) {
        param = __n_allocParam();
        if (param == NULL) {
            return;
        }
        param->delta = n_syn->paramSamples + voice->pvoice->delta;
        param->type = 7;
        param->data.f = pitch;
        param->next = NULL;
        n_alEnvmixerParam(voice->pvoice, 3, param);
    }
}

void n_alSynSetPan(ALVoice *voice, f32 pan) {
    SynCoreParam *param;

    if (voice->pvoice != NULL) {
        param = __n_allocParam();
        if (param == NULL) {
            return;
        }
        param->delta = n_syn->paramSamples + voice->pvoice->delta;
        param->type = 0x13;
        param->data.f = pan;
        param->next = NULL;
        n_alEnvmixerParam(voice->pvoice, 3, param);
    }
}

void n_alSynSetFXMix(ALVoice *voice, u8 fxmix) {
    SynCoreParam *param;

    if (voice->pvoice != NULL) {
        param = __n_allocParam();
        if (param == NULL) {
            return;
        }
        param->delta = n_syn->paramSamples + voice->pvoice->delta;
        param->type = 0x12;
        param->data.i = fxmix;
        param->next = NULL;
        n_alEnvmixerParam(voice->pvoice, 3, param);
    }
}





void computeBiquadCoefficients(f32 sampleRate, f32 cutoffFreq, f32 qFactor, f32 *numCoeffs, f32 *denCoeffs) {
    f32 omega;
    f32 omegaSq;
    f32 alpha;
    f32 pad1;
    f32 pad2;
    f32 pad3;
    f32 pad4;
    f32 pad5;
    f32 pad6;

    if (cutoffFreq >= sampleRate - 200.0f) {
        cutoffFreq = sampleRate - 200.0f;
    }
    omega = mathAtan2(cutoffFreq * 3.141592741f, sampleRate);
    omegaSq = omega * omega;
    alpha = (omega * 1.414213657f) / qFactor;
    numCoeffs[0] = omegaSq / (1.0f + omegaSq + alpha);
    numCoeffs[1] = 2.0f * numCoeffs[0];
    numCoeffs[2] = numCoeffs[0];
    denCoeffs[1] = ((omegaSq - 1.0f) * 2.0f) / (1.0f + omegaSq + alpha);
    denCoeffs[2] = ((1.0f + omegaSq) - alpha) / (1.0f + omegaSq + alpha);
}

void _init_lpfilter(SynLPFilter *filter) {
    s32 i;
    s32 scaledCoeff;
    s16 coeff;
    f32 ratio;
    f32 power;
    f32 scale;

    scaledCoeff = filter->unk0 * 16384.0f;
    coeff = scaledCoeff >> 0xF;
    filter->unk2 = 16384.0f - coeff;
    filter->state = 0;
    for (i = 0; i < 8; i++) {
        filter->coeff[i] = 0;
    }
    filter->coeff[i++] = coeff;
    scale = 16384.0f;
    power = ratio = coeff / scale;
    for (; i < 16; i++) {
        power *= ratio;
        filter->coeff[i] = power * scale;
    }
}

f32 n_alSemitonesToPitchRatio(s32 semitones) {
    f32 step;
    f32 ratio;

    ratio = 1.0f;
    if (semitones >= 0) {
        step = 1.0594631f;
    } else {
        step = 0.9438743f;
        semitones = -semitones;
    }
    while (semitones != 0) {
        if (semitones & 1) {
            ratio *= step;
        }
        step *= step;
        semitones >>= 1;
    }
    return ratio;
}


void rebuildLowPassCoefficients(SynLPFilter *filter, f32 sampleRate) {
    s32 i;
    f32 numCoeffs[3];
    f32 denCoeffs[3];

    if (filter->unk2 == 0) {
        return;
    }
    if (filter->unk2 < 10) {
        filter->unk2 = 10;
    }
    computeBiquadCoefficients(sampleRate, filter->unk0 + 10.0f, filter->unk2 / 10.0f, numCoeffs, denCoeffs);
    for (i = 3; i < 8; i++) {
        filter->coeff[i] = 0;
    }
    filter->coeff[0] = numCoeffs[0] * (26768.0f - filter->unk2 * 128.0f);
    filter->coeff[1] = numCoeffs[1] * (26768.0f - filter->unk2 * 128.0f);
    filter->coeff[2] = 0;
    filter->coeff[8] = denCoeffs[1] * -16384.0f;
    filter->coeff[9] = denCoeffs[2] * -16384.0f;
    for (i = 10; i < 16; i++) {
        filter->coeff[i] = 0;
    }
}

typedef struct {
    u8 unk0[0x14];
    void *unk14;
    void *unk18;
    u8 unk1C[8];
    f32 unk24;
    s32 unk28;
} LpfNMDelay;

typedef struct {
    u32 unk0;
    u32 unk4;
    s16 unk8;
    s16 unkA;
    s16 unkC;
    u8 unkE[2];
    f32 unk10;
    f32 unk14;
    s32 unk18;
    f32 unk1C;
    SynLPFilter *unk20;
    LpfNMDelay *unk24;
} LpfNMFx;

typedef struct {
    u32 unk0;
    LpfNMFx *unk4;
    u8 unk8;
    u8 unk9[0x17];
    s16 *unk20;
    s16 *unk24;
    s16 *unk28;
    s16 *unk2C;
} LpfNMFxState;


extern s32 D_80756458[];

void n_alFxNew(void **outFx, AudioInitArgs *config, s16 busIndex, ALHeap *heap) {
    u16 sectionIdx;
    u16 tableOffset;
    u16 bufIdx;
    s32 *paramTable;
    LpfNMFx *section;
    LpfNMFxState *fxState;

    paramTable = NULL;
    fxState = alHeapDBAlloc(NULL, 0, heap, 1, 0x30);
    *outFx = fxState;
    switch (config->fxType[busIndex]) {
        case 6:
            paramTable = config->params[busIndex];
            break;
        default:
            paramTable = D_80756458;
            break;
    }

    tableOffset = 0;
    fxState->unk8 = paramTable[tableOffset];
    tableOffset += 1;
    fxState->unk0 = paramTable[tableOffset];
    tableOffset += 1;
    fxState->unk4 = alHeapDBAlloc(NULL, 0, heap, fxState->unk8, 0x28);
    fxState->unk20 = alHeapDBAlloc(NULL, 0, heap, fxState->unk0, 2);
    fxState->unk28 = fxState->unk20;
    fxState->unk24 = alHeapDBAlloc(NULL, 0, heap, fxState->unk0, 2);
    fxState->unk2C = fxState->unk24;
    for (bufIdx = 0; bufIdx < fxState->unk0; bufIdx++) {
        fxState->unk24[bufIdx] = 0;
        fxState->unk20[bufIdx] = fxState->unk24[bufIdx];
    }
    for (sectionIdx = 0; sectionIdx < fxState->unk8; sectionIdx++) {
        section = &fxState->unk4[sectionIdx];
        section->unk0 = paramTable[tableOffset];
        tableOffset += 1;
        section->unk4 = paramTable[tableOffset];
        tableOffset += 1;
        section->unkA = paramTable[tableOffset];
        tableOffset += 1;
        section->unk8 = paramTable[tableOffset];
        tableOffset += 1;
        section->unkC = paramTable[tableOffset];
        tableOffset += 1;
        if (paramTable[tableOffset] != 0) {
            section->unk10 = paramTable[tableOffset] / 1000.0f * 2.0f / config->outputRate;
            tableOffset += 1;
            section->unk1C = paramTable[tableOffset] / 173123.4062f * (section->unk4 - section->unk0);
            tableOffset += 1;
            section->unk14 = 1.0f;
            section->unk18 = 0;
            section->unk24 = alHeapDBAlloc(NULL, 0, heap, 1, 0x38);
            section->unk24->unk14 = alHeapDBAlloc(NULL, 0, heap, 1, 0x20);
            section->unk24->unk18 = alHeapDBAlloc(NULL, 0, heap, 1, 0x20);
            section->unk24->unk24 = 0.0f;
            section->unk24->unk28 = 1;
        } else {
            section->unk24 = NULL;
            tableOffset += 1;
            tableOffset += 1;
        }
        if (paramTable[tableOffset] != 0) {
            section->unk20 = alHeapDBAlloc(NULL, 0, heap, 1, 0x38);
            section->unk20->unk2C = alHeapDBAlloc(NULL, 0, heap, 1, 8);
            section->unk20->unk30 = alHeapDBAlloc(NULL, 0, heap, 1, 8);
            section->unk20->unk0 = paramTable[tableOffset];
            tableOffset += 1;
            _init_lpfilter(section->unk20);
        } else {
            section->unk20 = NULL;
            tableOffset += 1;
        }
    }
}

void alN_PVoiceNew(N_PVoice *pvoice, ALDMANew dmaNew, ALHeap *heap) {
    pvoice->dc_state = alHeapDBAlloc(NULL, 0, heap, 1, 0x20);
    pvoice->dc_lstate = alHeapDBAlloc(NULL, 0, heap, 1, 0x20);
    pvoice->dc_dma = dmaNew(&pvoice->dc_dmaState);
    pvoice->dc_lastsam = 0;
    pvoice->dc_first = 1;
    pvoice->dc_memin = 0;
    pvoice->rs_state = alHeapDBAlloc(NULL, 0, heap, 1, 0x20);
    pvoice->rs_delta = 0.0f;
    pvoice->rs_first = 1;
    pvoice->rs_ratio = 1.0f;
    pvoice->rs_upitch = 0;
    pvoice->em_state = alHeapDBAlloc(NULL, 0, heap, 1, 0x50);
    pvoice->em_first = 1;
    pvoice->em_motion = 0;
    pvoice->em_volume = 1;
    pvoice->em_ltgt = 1;
    pvoice->em_rtgt = 1;
    pvoice->em_cvolL = 1;
    pvoice->em_cvolR = 1;
    pvoice->em_dryamt = 0;
    pvoice->em_wetamt = 0;
    pvoice->em_lratm = 1;
    pvoice->em_lratl = 0;
    pvoice->em_lratm = 1;
    pvoice->em_lratl = 0;
    pvoice->em_delta = 0;
    pvoice->em_segEnd = 0;
    pvoice->em_pan = 0;
    pvoice->em_ctrlList = 0;
    pvoice->em_ctrlTail = 0;
    pvoice->unk8C = 0;
    pvoice->unk92 = 0;
    pvoice->unk90 = 0;
    pvoice->unkBC = alHeapDBAlloc(NULL, 0, heap, 1, 8);
    pvoice->unkB8 = 0;
}

