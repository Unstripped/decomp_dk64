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

void _init_lpfilter(SynLowPass *filter) {
    s32 i;
    s32 scaledCoeff;
    s16 coeff;
    f32 ratio;
    f32 power;
    f32 scale;

    scaledCoeff = filter->fc * 16384.0f;
    coeff = scaledCoeff >> 0xF;
    filter->fgain = 16384.0f - coeff;
    filter->first = 0;
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


void rebuildLowPassCoefficients(SynLowPass *filter, f32 sampleRate) {
    s32 i;
    f32 numCoeffs[3];
    f32 denCoeffs[3];

    if (filter->fgain == 0) {
        return;
    }
    if (filter->fgain < 10) {
        filter->fgain = 10;
    }
    computeBiquadCoefficients(sampleRate, filter->fc + 10.0f, filter->fgain / 10.0f, numCoeffs, denCoeffs);
    for (i = 3; i < 8; i++) {
        filter->coeff[i] = 0;
    }
    filter->coeff[0] = numCoeffs[0] * (26768.0f - filter->fgain * 128.0f);
    filter->coeff[1] = numCoeffs[1] * (26768.0f - filter->fgain * 128.0f);
    filter->coeff[2] = 0;
    filter->coeff[8] = denCoeffs[1] * -16384.0f;
    filter->coeff[9] = denCoeffs[2] * -16384.0f;
    for (i = 10; i < 16; i++) {
        filter->coeff[i] = 0;
    }
}



extern s32 D_80756458[];

void n_alFxNew(void **outFx, AudioInitArgs *config, s16 busIndex, ALHeap *heap) {
    u16 sectionIdx;
    u16 tableOffset;
    u16 bufIdx;
    s32 *paramTable;
    SynFxDelay *section;
    SynFx *fxState;

    paramTable = NULL;
    fxState = alHeapDBAlloc(NULL, 0, heap, 1, sizeof(SynFx));
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
    fxState->section_count = paramTable[tableOffset];
    tableOffset += 1;
    fxState->length = paramTable[tableOffset];
    tableOffset += 1;
    fxState->delay = alHeapDBAlloc(NULL, 0, heap, fxState->section_count, sizeof(SynFxDelay));
    fxState->base[0] = alHeapDBAlloc(NULL, 0, heap, fxState->length, 2);
    fxState->input[0] = fxState->base[0];
    fxState->base[1] = alHeapDBAlloc(NULL, 0, heap, fxState->length, 2);
    fxState->input[1] = fxState->base[1];
    for (bufIdx = 0; bufIdx < fxState->length; bufIdx++) {
        fxState->base[1][bufIdx] = 0;
        fxState->base[0][bufIdx] = fxState->base[1][bufIdx];
    }
    for (sectionIdx = 0; sectionIdx < fxState->section_count; sectionIdx++) {
        section = &fxState->delay[sectionIdx];
        section->input = paramTable[tableOffset];
        tableOffset += 1;
        section->output = paramTable[tableOffset];
        tableOffset += 1;
        section->fbcoef = paramTable[tableOffset];
        tableOffset += 1;
        section->ffcoef = paramTable[tableOffset];
        tableOffset += 1;
        section->gain = paramTable[tableOffset];
        tableOffset += 1;
        if (paramTable[tableOffset] != 0) {
            section->rsinc = paramTable[tableOffset] / 1000.0f * 2.0f / config->outputRate;
            tableOffset += 1;
            section->rsgain = paramTable[tableOffset] / 173123.4062f * (section->output - section->input);
            tableOffset += 1;
            section->rsval = 1.0f;
            section->rsdelta = 0;
            section->rs = alHeapDBAlloc(NULL, 0, heap, 1, sizeof(SynFxResampler));
            section->rs->state[0] = alHeapDBAlloc(NULL, 0, heap, 1, 0x20);
            section->rs->state[1] = alHeapDBAlloc(NULL, 0, heap, 1, 0x20);
            section->rs->delta = 0.0f;
            section->rs->first = 1;
        } else {
            section->rs = NULL;
            tableOffset += 1;
            tableOffset += 1;
        }
        if (paramTable[tableOffset] != 0) {
            section->lp = alHeapDBAlloc(NULL, 0, heap, 1, sizeof(SynLPFilter));
            section->lp->fstate[0] = alHeapDBAlloc(NULL, 0, heap, 1, 8);
            section->lp->fstate[1] = alHeapDBAlloc(NULL, 0, heap, 1, 8);
            section->lp->lp.fc = paramTable[tableOffset];
            tableOffset += 1;
            _init_lpfilter(&section->lp->lp);
        } else {
            section->lp = NULL;
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
    pvoice->lowpass.fgain = 0;
    pvoice->lowpass.fc = 0;
    pvoice->lowpassState = alHeapDBAlloc(NULL, 0, heap, 1, 8);
    pvoice->lowpass.first = 0;
}

