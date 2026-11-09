#include "common.h"
#include "proto/global/137120.h"
#include "proto/global/13E160.h"
#include "proto/global/140600.h"
#include "proto/global/1435C0.h"
#include "proto/global/166A0.h"

typedef struct SynVoiceParam {
    struct SynVoiceParam *next;
    s32 delta;
    s16 type;
    union {
        f32 f;
        s32 i;
    } data;
} SynVoiceParam;

typedef struct {
    u8 unk0[0x88];
    s32 delta;
} SynPVoice;

extern ALSynth *n_syn;

void n_alSynSetPitch(ALVoice *voice, f32 pitch) {
    SynVoiceParam *param;

    if (voice->pvoice != NULL) {
        param = __n_allocParam();
        if (param == NULL) {
            return;
        }
        param->delta = n_syn->paramSamples + ((SynPVoice *)voice->pvoice)->delta;
        param->type = 7;
        param->data.f = pitch;
        param->next = NULL;
        n_alEnvmixerParam(voice->pvoice, 3, param);
    }
}

void n_alSynSetPan(ALVoice *voice, f32 pan) {
    SynVoiceParam *param;

    if (voice->pvoice != NULL) {
        param = __n_allocParam();
        if (param == NULL) {
            return;
        }
        param->delta = n_syn->paramSamples + ((SynPVoice *)voice->pvoice)->delta;
        param->type = 0x13;
        param->data.f = pan;
        param->next = NULL;
        n_alEnvmixerParam(voice->pvoice, 3, param);
    }
}

void n_alSynSetFXMix(ALVoice *voice, u8 fxmix) {
    SynVoiceParam *param;

    if (voice->pvoice != NULL) {
        param = __n_allocParam();
        if (param == NULL) {
            return;
        }
        param->delta = n_syn->paramSamples + ((SynPVoice *)voice->pvoice)->delta;
        param->type = 0x12;
        param->data.i = fxmix;
        param->next = NULL;
        n_alEnvmixerParam(voice->pvoice, 3, param);
    }
}


typedef struct LpfNMBiquad {
    f32 unk0;
    f32 unk4;
    f32 unk8;
} LpfNMBiquad;



void computeBiquadCoefficients(f32 sampleRate, f32 cutoffFreq, f32 qFactor, LpfNMBiquad *numCoeffs, LpfNMBiquad *denCoeffs) {
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
    numCoeffs->unk0 = omegaSq / (1.0f + omegaSq + alpha);
    numCoeffs->unk4 = 2.0f * numCoeffs->unk0;
    numCoeffs->unk8 = numCoeffs->unk0;
    denCoeffs->unk4 = ((omegaSq - 1.0f) * 2.0f) / (1.0f + omegaSq + alpha);
    denCoeffs->unk8 = ((1.0f + omegaSq) - alpha) / (1.0f + omegaSq + alpha);
}

typedef struct SynLPFilter {
    s16 unk0;
    s16 unk2;
    u32 unk4;
    s16 coeff[16];
    s32 state;
} SynLPFilter;

void _init_lpfilter(SynLPFilter *filter) {
    s32 i;
    s32 scaledCoeff;
    s16 spE;
    f32 sp8;
    f32 sp4;
    f32 sp0;

    scaledCoeff = (s32)((f32)filter->unk0 * 16384.0f);
    spE = (s16)(scaledCoeff >> 0xF);
    filter->unk2 = (s16)(s32)(16384.0f - (f32)spE);
    filter->state = 0;
    i = 0;
    do {
        filter->coeff[i] = 0;
    } while (++i < 8);
    filter->coeff[i++] = spE;
    sp0 = 16384.0f;
    sp4 = sp8 = (f32)spE / sp0;
    if (i < 0x10) {
        do {
            sp4 *= sp8;
            filter->coeff[i] = (s16)(s32)(sp4 * sp0);
        } while (++i < 0x10);
    }
}

f32 n_alSemitonesToPitchRatio(s32 semitones) {
    f32 sp4;
    f32 sp0;

    sp0 = 1.0f;
    if (semitones >= 0) {
        sp4 = 1.0594631f;
    } else {
        sp4 = 0.9438743f;
        semitones = -semitones;
    }
    if (semitones != 0) {
        do {
            if (semitones & 1) {
                sp0 *= sp4;
            }
            sp4 *= sp4;
            semitones = semitones >> 1;
        } while (semitones != 0);
    }
    return sp0;
}


void rebuildLowPassCoefficients(SynLPFilter *filter, f32 sampleRate) {
    s32 i;
    LpfNMBiquad numCoeffs;
    LpfNMBiquad denCoeffs;

    if (filter->unk2 == 0) {
        return;
    }
    if (filter->unk2 < 10) {
        filter->unk2 = 10;
    }
    computeBiquadCoefficients(sampleRate, (f32)filter->unk0 + 10.0f, (f32)filter->unk2 / 10.0f, &numCoeffs, &denCoeffs);
    i = 3;
    do {
        filter->coeff[i] = 0;
    } while (++i < 8);
    filter->coeff[0] = (s16)(s32)(((f32 *)&numCoeffs)[0] * (26768.0f - ((f32)filter->unk2 * 128.0f)));
    filter->coeff[1] = (s16)(s32)(((f32 *)&numCoeffs)[1] * (26768.0f - ((f32)filter->unk2 * 128.0f)));
    filter->coeff[2] = 0;
    filter->coeff[8] = (s16)(s32)(((f32 *)&denCoeffs)[1] * -16384.0f);
    filter->coeff[9] = (s16)(s32)(((f32 *)&denCoeffs)[2] * -16384.0f);
    i = 10;
    do {
        filter->coeff[i] = 0;
    } while (++i < 16);
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
    SynLPFilter base;
    void *unk2C;
    void *unk30;
} LpfNMFilter;

typedef struct {
    s32 unk0;
    s32 unk4;
    s16 unk8;
    s16 unkA;
    s16 unkC;
    u8 unkE[2];
    f32 unk10;
    f32 unk14;
    s32 unk18;
    f32 unk1C;
    LpfNMFilter *unk20;
    LpfNMDelay *unk24;
} LpfNMFx;

typedef struct {
    s32 unk0;
    LpfNMFx *unk4;
    u8 unk8;
    u8 unk9[0x17];
    s16 *unk20;
    s16 *unk24;
    s16 *unk28;
    s16 *unk2C;
} LpfNMFxState;


extern s32 D_80756458[];

void n_alFxNew(void **outFx, void *config, s16 busIndex, ALHeap *heap) {
    u16 sectionIdx;
    u16 tableOffset;
    u16 bufIdx;
    s32 *paramTable;
    LpfNMFx *section;
    LpfNMFxState *fxState;

    paramTable = NULL;
    fxState = alHeapDBAlloc(NULL, 0, heap, 1, 0x30);
    *outFx = fxState;
    switch (((u8 *)config + busIndex)[0x1C]) {
        case 6:
            paramTable = *(s32 **)((u8 *)config + (busIndex * 4) + 0x20);
            break;
        default:
            paramTable = D_80756458;
            break;
    }

    tableOffset = 0;
    fxState->unk8 = (u8)paramTable[tableOffset];
    tableOffset += 1;
    fxState->unk0 = paramTable[tableOffset];
    tableOffset += 1;
    fxState->unk4 = alHeapDBAlloc(NULL, 0, heap, fxState->unk8, 0x28);
    fxState->unk20 = alHeapDBAlloc(NULL, 0, heap, fxState->unk0, 2);
    fxState->unk28 = fxState->unk20;
    fxState->unk24 = alHeapDBAlloc(NULL, 0, heap, fxState->unk0, 2);
    fxState->unk2C = fxState->unk24;
    for (bufIdx = 0; bufIdx < (u32)fxState->unk0; bufIdx++) {
        fxState->unk24[bufIdx] = 0;
        fxState->unk20[bufIdx] = fxState->unk24[bufIdx];
    }
    for (sectionIdx = 0; (s32)sectionIdx < (s32)fxState->unk8; sectionIdx++) {
        section = &fxState->unk4[sectionIdx];
        section->unk0 = paramTable[tableOffset];
        tableOffset += 1;
        section->unk4 = paramTable[tableOffset];
        tableOffset += 1;
        section->unkA = (s16)paramTable[tableOffset];
        tableOffset += 1;
        section->unk8 = (s16)paramTable[tableOffset];
        tableOffset += 1;
        section->unkC = (s16)paramTable[tableOffset];
        tableOffset += 1;
        if (paramTable[tableOffset] != 0) {
            section->unk10 = ((f32)paramTable[tableOffset] / 1000.0f * 2.0f) / (f32)*(s32 *)((u8 *)config + 0x18);
            tableOffset += 1;
            section->unk1C = ((f32)paramTable[tableOffset] / 173123.4062f) * (f32)(u32)(section->unk4 - section->unk0);
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
            section->unk20->base.unk0 = (s16)paramTable[tableOffset];
            tableOffset += 1;
            _init_lpfilter((SynLPFilter *)section->unk20);
        } else {
            section->unk20 = NULL;
            tableOffset += 1;
        }
    }
}

typedef struct SynPVoiceInit {
    u8 unk0[0xC];
    void *unkC;
    void *unk10;
    u8 unk14[0x14];
    s32 unk28;
    u8 unk2C[8];
    s32 unk34;
    s32 unk38;
    s32 unk3C;
    void *unk40;
    f32 unk44;
    s32 unk48;
    f32 unk4C;
    s32 unk50;
    void *unk54;
    s16 unk58;
    s16 unk5A;
    s16 unk5C;
    s16 unk5E;
    s16 unk60;
    s16 unk62;
    s16 unk64;
    s16 unk66;
    s16 unk68;
    u8 unk6A[4];
    s16 unk6E;
    s32 unk70;
    s32 unk74;
    s32 unk78;
    s32 unk7C;
    s32 unk80;
    s32 unk84;
    u8 unk88[4];
    u8 unk8C;
    u8 unk8D[3];
    s16 unk90;
    s16 unk92;
    u8 unk94[0x24];
    s32 unkB8;
    void *unkBC;
} SynPVoiceInit;

void alN_PVoiceNew(SynPVoiceInit *pvoice, s32 (*initCallback)(void *), ALHeap *heap) {
    pvoice->unkC = alHeapDBAlloc(NULL, 0, heap, 1, 0x20);
    pvoice->unk10 = alHeapDBAlloc(NULL, 0, heap, 1, 0x20);
    pvoice->unk28 = initCallback(pvoice->unk2C);
    pvoice->unk34 = 0;
    pvoice->unk38 = 1;
    pvoice->unk3C = 0;
    pvoice->unk40 = alHeapDBAlloc(NULL, 0, heap, 1, 0x20);
    pvoice->unk4C = 0.0f;
    pvoice->unk50 = 1;
    pvoice->unk44 = 1.0f;
    pvoice->unk48 = 0;
    pvoice->unk54 = alHeapDBAlloc(NULL, 0, heap, 1, 0x50);
    pvoice->unk78 = 1;
    pvoice->unk84 = 0;
    pvoice->unk5A = 1;
    pvoice->unk68 = 1;
    pvoice->unk6E = 1;
    pvoice->unk5C = 1;
    pvoice->unk5E = 1;
    pvoice->unk60 = 0;
    pvoice->unk62 = 0;
    pvoice->unk66 = 1;
    pvoice->unk64 = 0;
    pvoice->unk66 = 1;
    pvoice->unk64 = 0;
    pvoice->unk70 = 0;
    pvoice->unk74 = 0;
    pvoice->unk58 = 0;
    pvoice->unk7C = 0;
    pvoice->unk80 = 0;
    pvoice->unk8C = 0;
    pvoice->unk92 = 0;
    pvoice->unk90 = 0;
    pvoice->unkBC = alHeapDBAlloc(NULL, 0, heap, 1, 8);
    pvoice->unkB8 = 0;
}

