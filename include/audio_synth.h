#ifndef AUDIO_SYNTH_H
#define AUDIO_SYNTH_H

#include "common.h"

// Rare's libaudio synthesizer core (n_syn): parameter updates, physical voices, low-pass
// filters, buses and the synth itself, as built by n_alSynNew (13E160.c).

// One pending synthesizer parameter update (libultra's N_ALParam), queued on a physical voice
// and applied by the envmixer when the sample clock reaches `delta`. n_alSynNew carves the
// free pool in 0x24-byte elements so n_alSynStartVoiceParams's larger start record
// (SynAllocStartParam, 141AD0.c) fits in one; `pad14` reserves that tail.
typedef struct SynCoreParam {
    /* 0x00 */ struct SynCoreParam *next;
    /* 0x04 */ s32 delta;
    /* 0x08 */ s16 type;
    /* 0x0A */ s16 unity;
    /* 0x0C */ union {
        f32 f;
        s32 i;
        void *ptr;
        struct {
            s16 s0;
            s16 s1;
        } s;
    } data;
    /* 0x10 */ union {
        f32 f;
        s32 i;
    } moredata;
    /* 0x14 */ u8 pad14[0x10];
} SynCoreParam; // size = 0x24

// Voice start record (type 13): n_alSynStartVoiceParams (141AD0.c) fills it in a
// SynCoreParam slot and n_alEnvmixerPull (1435C0.c) consumes it. Same header as SynCoreParam.
typedef struct SynStartParam {
    /* 0x00 */ SynCoreParam *next;
    /* 0x04 */ s32 delta;
    /* 0x08 */ s16 type;
    /* 0x0A */ s16 unity;
    /* 0x0C */ f32 pitch;
    /* 0x10 */ s16 volume;
    /* 0x12 */ u8 pan;
    /* 0x13 */ u8 fxmix;
    /* 0x14 */ u8 fxDelay;
    /* 0x15 */ u8 fxPitch;
    /* 0x18 */ f32 fxVolume;
    /* 0x1C */ s32 samples;
    /* 0x20 */ ALWaveTable *wave;
} SynStartParam; // size = 0x24

// Low-pass filter of an aux bus and of an n_alFxNew section (both allocated 0x38 bytes with
// two 8-byte state buffers). _init_lpfilter derives `coeff` from the cutoff `unk0`;
// rebuildLowPassCoefficients reads `unk2` as the resonance (Q * 10).
typedef struct SynLPFilter {
    /* 0x00 */ s16 unk0;
    /* 0x02 */ s16 unk2;
    /* 0x04 */ u32 unk4;
    /* 0x08 */ s16 coeff[16];
    /* 0x28 */ s32 state;
    /* 0x2C */ void *unk2C;
    /* 0x30 */ void *unk30;
    /* 0x34 */ u8 pad34[4];
} SynLPFilter; // size = 0x38

// Physical voice (libultra's N_PVoice: the n_ ADPCM decoder, resampler and envelope mixer
// flattened into one object, field prefixes dc_/rs_/em_ as in n_synthInternals.h), the target
// of ALVoice.pvoice. Lives on one of n_syn's free/alloc/lame lists through `node`;
// alN_PVoiceNew (140600.c) fills the rest. 0x88.. are Rare's additions.
typedef struct PVoice_s {
    /* 0x00 */ ALLink node;
    /* 0x08 */ ALVoice *vvoice;
    /* 0x0C */ void *dc_state;
    /* 0x10 */ void *dc_lstate;
    /* 0x14 */ ALRawLoop dc_loop;
    /* 0x20 */ ALWaveTable *dc_table;
    /* 0x24 */ s32 dc_bookSize;
    /* 0x28 */ ALDMAproc dc_dma;
    /* 0x2C */ void *dc_dmaState;
    /* 0x30 */ s32 dc_sample;
    /* 0x34 */ s32 dc_lastsam;
    /* 0x38 */ s32 dc_first;
    /* 0x3C */ s32 dc_memin;
    /* 0x40 */ void *rs_state;
    /* 0x44 */ f32 rs_ratio;
    /* 0x48 */ s32 rs_upitch;
    /* 0x4C */ f32 rs_delta;
    /* 0x50 */ s32 rs_first;
    /* 0x54 */ void *em_state;
    /* 0x58 */ s16 em_pan;
    /* 0x5A */ s16 em_volume;
    /* 0x5C */ s16 em_cvolL;
    /* 0x5E */ s16 em_cvolR;
    /* 0x60 */ s16 em_dryamt;
    /* 0x62 */ s16 em_wetamt;
    /* 0x64 */ u16 em_lratl;
    /* 0x66 */ s16 em_lratm;
    /* 0x68 */ s16 em_ltgt;
    /* 0x6A */ u16 em_rratl;
    /* 0x6C */ s16 em_rratm;
    /* 0x6E */ s16 em_rtgt;
    /* 0x70 */ s32 em_delta;
    /* 0x74 */ s32 em_segEnd;
    /* 0x78 */ s32 em_first;
    /* 0x7C */ SynCoreParam *em_ctrlList;
    /* 0x80 */ SynCoreParam *em_ctrlTail;
    /* 0x84 */ s32 em_motion;
    /* 0x88 */ s32 delta; // samples until the envelope's release ends; 0 = free to steal
    /* 0x8C */ u8 unk8C; // start fxDelay / param 0x11; n_alResamplePull pitch-shifts when 1..0x3F
    /* 0x8D */ u8 unk8D[3];
    // 0x90..0xBF: per-voice low-pass, laid out like SynLPFilter's first 0x30 bytes
    // (n_alResamplePull hands &unk90 to rebuildLowPassCoefficients).
    /* 0x90 */ s16 unk90; // start fxVolume / param 0x13: cutoff
    /* 0x92 */ s16 unk92; // start fxPitch / param 0x12: > 0 enables the filter
    /* 0x94 */ u8 unk94[4];
    /* 0x98 */ s16 unk98[16]; // coefficients (loaded by the 0x0B command)
    /* 0xB8 */ s32 unkB8; // filter flags (2 = rebuild)
    /* 0xBC */ void *unkBC; // filter state
} N_PVoice; // size = 0xC0

// Main bus: its `handler` is n_alFxPull while the aux-bus effects are live.
typedef struct N_ALMainBus {
    /* 0x00 */ u8 pad0[4];
    /* 0x04 */ Acmd *(*handler)(s32, Acmd *, s32);
    /* 0x08 */ u8 pad8[0xC];
} N_ALMainBus; // size = 0x14

typedef struct N_ALAuxBus {
    /* 0x00 */ u8 pad0[0x14];
    /* 0x14 */ s32 sourceCount;
    /* 0x18 */ s32 maxSources;
    /* 0x1C */ N_PVoice **sources;
    /* 0x20 */ void *fx;
    /* 0x24 */ u8 pad24[0x20];
    /* 0x44 */ SynLPFilter *filter;
} N_ALAuxBus; // size = 0x48

typedef struct N_ALSynth {
    /* 0x00 */ ALPlayer *head;
    /* 0x04 */ ALLink pFreeList;
    /* 0x0C */ ALLink pAllocList;
    /* 0x14 */ ALLink pLameList;
    /* 0x1C */ s32 paramSamples;
    /* 0x20 */ s32 curSamples;
    /* 0x24 */ ALDMANew dma;
    /* 0x28 */ ALHeap *heap;
    /* 0x2C */ SynCoreParam *paramList;
    /* 0x30 */ N_ALMainBus *mainBus;
    /* 0x34 */ N_ALAuxBus *auxBus;
    /* 0x38 */ s32 numPVoices;
    /* 0x3C */ s32 maxAuxBusses;
    /* 0x40 */ s32 outputRate;
    /* 0x44 */ s32 maxOutSamples;
    /* 0x48 */ s16 *outBuffer;
    /* 0x4C */ s32 unk4C;
} N_ALSynth; // size = 0x50

#endif
