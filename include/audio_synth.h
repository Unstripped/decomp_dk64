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
    } data;
    /* 0x10 */ union {
        f32 f;
        s32 i;
    } moredata;
    /* 0x14 */ u8 pad14[0x10];
} SynCoreParam; // size = 0x24

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

// Physical voice (libultra's N_PVoice), the target of ALVoice.pvoice. Lives on one of
// n_syn's free/alloc/lame lists through `node`; alN_PVoiceNew (140600.c) fills the rest.
typedef struct PVoice_s {
    /* 0x00 */ ALLink node;
    /* 0x08 */ ALVoice *vvoice;
    /* 0x0C */ void *unkC;
    /* 0x10 */ void *unk10;
    /* 0x14 */ u8 unk14[0x14];
    /* 0x28 */ ALDMAproc dma;
    /* 0x2C */ u8 dmaState[8];
    /* 0x34 */ s32 unk34;
    /* 0x38 */ s32 unk38;
    /* 0x3C */ s32 unk3C;
    /* 0x40 */ void *unk40;
    /* 0x44 */ f32 unk44;
    /* 0x48 */ s32 unk48;
    /* 0x4C */ f32 unk4C;
    /* 0x50 */ s32 unk50;
    /* 0x54 */ void *unk54;
    /* 0x58 */ s16 unk58;
    /* 0x5A */ s16 unk5A;
    /* 0x5C */ s16 unk5C;
    /* 0x5E */ s16 unk5E;
    /* 0x60 */ s16 unk60;
    /* 0x62 */ s16 unk62;
    /* 0x64 */ s16 unk64;
    /* 0x66 */ s16 unk66;
    /* 0x68 */ s16 unk68;
    /* 0x6A */ u8 unk6A[4];
    /* 0x6E */ s16 unk6E;
    /* 0x70 */ s32 unk70;
    /* 0x74 */ s32 unk74;
    /* 0x78 */ s32 unk78;
    /* 0x7C */ s32 unk7C;
    /* 0x80 */ s32 unk80;
    /* 0x84 */ s32 unk84;
    /* 0x88 */ s32 delta; // samples until the envelope's release ends; 0 = free to steal
    /* 0x8C */ u8 unk8C;
    /* 0x8D */ u8 unk8D[3];
    /* 0x90 */ s16 unk90;
    /* 0x92 */ s16 unk92;
    /* 0x94 */ u8 unk94[0x24];
    /* 0xB8 */ s32 unkB8;
    /* 0xBC */ void *unkBC;
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
