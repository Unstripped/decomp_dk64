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

// Low-pass filter core (libultra's ALLowPass, n_ flavour): what _init_lpfilter and
// rebuildLowPassCoefficients operate on, and what the 0x0B (load coefficients) and 0x0E
// (filter) commands address. Embedded in every N_PVoice and at the head of SynLPFilter.
typedef struct SynLowPass {
    /* 0x00 */ s16 fc; // cutoff
    /* 0x02 */ s16 fgain; // gain; rebuildLowPassCoefficients reads it as the resonance (Q * 10); 0 = off
    /* 0x04 */ u32 unk4;
    /* 0x08 */ s16 coeff[16];
    /* 0x28 */ s32 first; // filter-command flags; 2 = coefficients need a rebuild
} SynLowPass; // size = 0x2C; each owner keeps its 8-byte filter state(s) right after it

// Stereo low-pass of an aux bus and of an n_alFxNew delay section (both allocated 0x38 bytes):
// one 8-byte filter state per channel, indexed by the channel in _n_filterBuffer (141EF0.c).
typedef struct SynLPFilter {
    /* 0x00 */ SynLowPass lp;
    /* 0x2C */ void *fstate[2];
    /* 0x34 */ u8 pad34[4];
} SynLPFilter; // size = 0x38

// Chorus/flange resampler of a delay section (n_ ALResampler, stereo; allocated 0x38 bytes).
typedef struct SynFxResampler {
    /* 0x00 */ u8 pad0[0x14];
    /* 0x14 */ void *state[2]; // per-channel 0x20-byte RESAMPLE_STATE
    /* 0x1C */ u8 pad1C[8];
    /* 0x24 */ f32 delta; // fractional sample carried between frames
    /* 0x28 */ u32 first; // resample-command flags
    /* 0x2C */ u8 pad2C[0xC];
} SynFxResampler; // size = 0x38

// One delay section of an aux-bus effect (libultra's ALDelay; field names from
// synthInternals.h). n_alFxNew (140600.c) fills it from the effect's parameter table and
// n_alFxParamHdl (141EF0.c) updates it.
typedef struct SynFxDelay {
    /* 0x00 */ u32 input; // tap offsets into the delay line, in samples
    /* 0x04 */ u32 output;
    /* 0x08 */ s16 ffcoef;
    /* 0x0A */ s16 fbcoef;
    /* 0x0C */ s16 gain;
    /* 0x10 */ f32 rsinc; // chorus rate
    /* 0x14 */ f32 rsval;
    /* 0x18 */ s32 rsdelta;
    /* 0x1C */ f32 rsgain; // chorus depth
    /* 0x20 */ SynLPFilter *lp;
    /* 0x24 */ SynFxResampler *rs;
} SynFxDelay; // size = 0x28

// Aux-bus effect (libultra's ALFx, Rare's stereo variant): one delay line per channel.
// n_alFxNew builds it, n_alFxPull (141EF0.c) runs it.
typedef struct SynFx {
    /* 0x00 */ u32 length; // delay-line length in samples
    /* 0x04 */ SynFxDelay *delay;
    /* 0x08 */ u8 section_count;
    /* 0x09 */ u8 pad9[0x17];
    /* 0x20 */ s16 *base[2];
    /* 0x28 */ s16 *input[2]; // write position, advanced one frame per pull
} SynFx; // size = 0x30

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
    /* 0x90 */ SynLowPass lowpass; // fc: start fxVolume / param 0x13; fgain: start fxPitch / param 0x12
    /* 0xBC */ void *lowpassState;
} N_PVoice; // size = 0xC0

// Main bus: its `handler` is n_alFxPull while the aux-bus effects are live.
typedef struct N_ALMainBus {
    /* 0x00 */ u8 pad0[4];
    /* 0x04 */ Acmd *(*handler)(s32, Acmd *, s32);
    /* 0x08 */ u8 pad8[0xC];
} N_ALMainBus; // size = 0x14

typedef struct N_ALAuxBus {
    /* 0x00 */ u8 pad0[0x14];
    /* 0x14 */ u32 sourceCount;
    /* 0x18 */ s32 maxSources;
    /* 0x1C */ N_PVoice **sources;
    /* 0x20 */ SynFx *fx;
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
