#include "common.h"


typedef struct {
    u8 pad0[0x40];
    s32 unk40;
    u8 pad44[4];
    u32 unk48;
} ReverbSynth;

extern ReverbSynth *n_syn;

typedef struct {
    s32 unk0;
    s32 unk4;
    s16 unk8;
    s16 unkA;
    s16 unkC;
    u8 padE[2];
    f32 unk10;
    u8 pad14[8];
    f32 unk1C;
    void *unk20;
    void *unk24;
} FxParamEntry;

typedef struct {
    s32 unk0;
    FxParamEntry *unk4;
    u8 unk8;
} FxParamState;

void _init_lpfilter();
typedef struct {
    u8 pad0[0x20];
    void *unk20;
    u8 pad24[0x24];
} AuxBus;

typedef struct {
    u8 pad0[0x34];
    AuxBus *unk34;
} SynthView;

typedef struct {
    s32 unk0;
    FxParamEntry *unk4;
    u8 unk8;
    u8 pad9[0x17];
    u8 *unk20[2];
    u8 *unk28[2];
} FxPullRing;

extern u8 D_807FF0F4[];
extern u8 D_807FF0F6[];
Acmd *n_alAuxBusPull();
Acmd *_n_saveBuffer();
Acmd *_n_loadBuffer();
Acmd *_n_loadOutputBuffer();
Acmd *_n_filterBuffer();

#define SWAP(in, out) { dmemTmp = out; out = in; in = dmemTmp; }

Acmd *n_alFxPull(s32 time, Acmd *cmdList, s32 busIndex) {
    Acmd *ptr;
    FxPullRing *ring;
    s16 sectionIdx;
    s16 dmemIn;
    s16 dmemOut;
    s16 inDmem;
    s16 outDmem;
    u8 *inPtr;
    u8 *outPtr;
    s32 pad68;
    u8 *lastInPtr;
    FxParamEntry *section;
    s32 pad5C;
    s32 auxCount;
    u32 busChan;
    Acmd *cmd1;
    Acmd *cmd2;
    Acmd *clearCmd;
    s16 dmemTmp;
    Acmd *mixCmd1;
    Acmd *mixCmd2;
    Acmd *scaleCmd1;
    u32 scaledGain;
    Acmd *scaleCmd2;
    Acmd *panCmd1;
    Acmd *panCmd2;
    Acmd *dmaCmd;

    ptr = cmdList;
    ring = ((SynthView *)n_syn)->unk34[busIndex].unk20;
    lastInPtr = NULL;
    auxCount = 1;
    ptr = n_alAuxBusPull(time, cmdList, busIndex, &auxCount);
    inDmem = 0x7C0;
    outDmem = 0x930;
    dmemIn = 0;
    dmemOut = 0x170;
    if (D_807FF0F4[busIndex] == 0) {
        cmd1 = ptr++;
        cmd1->words.w0 = 0x0C00C000;
        cmd1->words.w1 = (inDmem & 0xFFFF) | 0x07C00000;
        cmd2 = ptr++;
        cmd2->words.w0 = 0x0C004000;
        cmd2->words.w1 = (inDmem & 0xFFFF) | 0x09300000;
    }
    ptr = _n_saveBuffer(ring, 0, ring->unk28[0], inDmem, ptr);
    if (D_807FF0F4[busIndex] != 0) {
        ptr = _n_saveBuffer(ring, 1, ring->unk28[1], 0x930, ptr);
    }
    for (busChan = 0; busChan <= D_807FF0F4[busIndex]; busChan++) {
        clearCmd = ptr++;
        clearCmd->words.w0 = (outDmem & 0xFFFFFF) | 0x02000000;
        clearCmd->words.w1 = 0x170;
        if ((s32)ring->unk8 > (sectionIdx = 0)) {
            do {
                section = ring->unk4 + sectionIdx;
                inPtr = ring->unk28[busChan] + ((-section->unk0) * 2);
                outPtr = ring->unk28[busChan] + ((-section->unk4) * 2);
                if ((D_807FF0F6[busIndex] != 0) && (D_807FF0F4[busIndex] != 0)) {
                    section->unk8 = -section->unk8;
                    section->unkA = -section->unkA;
                }
                if (inPtr == lastInPtr) {
                    SWAP(dmemIn, dmemOut);
                } else {
                    ptr = _n_loadBuffer(ring, busChan, inPtr, dmemIn, 0xB8, ptr);
                }
                ptr = _n_loadOutputBuffer(ring, section, busChan, dmemOut, ptr);
                if (section->unk8 != 0) {
                    mixCmd1 = ptr++;
                    mixCmd1->words.w0 = ((u16)section->unk8 & 0xFFFF) | 0x0C000000;
                    mixCmd1->words.w1 = ((dmemIn & 0xFFFF) << 16) | (dmemOut & 0xFFFF);
                    if ((section->unk24 == 0) && (section->unk20 == 0)) {
                        ptr = _n_saveBuffer(ring, busChan, outPtr, dmemOut, ptr);
                    }
                }
                if (section->unkA != 0) {
                    mixCmd2 = ptr++;
                    mixCmd2->words.w0 = ((u16)section->unkA & 0xFFFF) | 0x0C000000;
                    mixCmd2->words.w1 = ((dmemOut & 0xFFFF) << 16) | (dmemIn & 0xFFFF);
                    ptr = _n_saveBuffer(ring, busChan, inPtr, dmemIn, ptr);
                }
                if (section->unk20 != 0) {
                    ptr = _n_filterBuffer(section->unk20, busChan, dmemOut, ptr);
                }
                if (section->unk24 == 0) {
                    ptr = _n_saveBuffer(ring, busChan, outPtr, dmemOut, ptr);
                }
                if (section->unkC != 0) {
                    if (D_807FF0F4[busIndex] != 0) {
                        scaleCmd1 = ptr++;
                        scaleCmd1->words.w0 = ((u16)section->unkC & 0xFFFF) | 0x0C000000;
                        scaleCmd1->words.w1 = ((dmemOut & 0xFFFF) << 16) | (outDmem & 0xFFFF);
                        ;
                    } else {
                        scaledGain = (u32)((f32)section->unkC * 1.4142f);
                        if (scaledGain >= 0x8000) {
                            scaledGain = 0x7FFF;
                        }
                        scaleCmd2 = ptr++;
                        scaleCmd2->words.w0 = ((u16)scaledGain & 0xFFFF) | 0x0C000000;
                        scaleCmd2->words.w1 = ((dmemOut & 0xFFFF) << 16) | (outDmem & 0xFFFF);
                    }
                }
                lastInPtr = ring->unk28[busChan] + (section->unk4 * 2);
            } while (++sectionIdx < (s32)ring->unk8);
        }
        if ((D_807FF0F4[busIndex] != 0) && (busChan == 0)) {
            ptr = _n_loadBuffer(ring, 1, ring->unk28[1], inDmem, 0xB8, ptr);
            if (D_807FF0F6[busIndex] != 0) {
                panCmd1 = ptr++;
                panCmd1->words.w0 = 0x0C005A82;
                panCmd1->words.w1 = ((outDmem & 0xFFFF) << 16) | 0x650;
                ;
            } else {
                panCmd2 = ptr++;
                panCmd2->words.w0 = 0x0C005A82;
                panCmd2->words.w1 = ((outDmem & 0xFFFF) << 16) | 0x4E0;
            }
        } else {}
        dmaCmd = ptr++;
        dmaCmd->words.w0 = (outDmem & 0xFFFFFF) | 0x0A000000;
        dmaCmd->words.w1 = 0x07C00170;
        ring->unk28[busChan] += 0x170;
        if (ring->unk28[busChan] > (ring->unk20[busChan] + (ring->unk0 * 2))) {
            ring->unk28[busChan] -= ring->unk0 * 2;
        }
    }
    return ptr;
}


s32 n_alFxParamHdl(FxParamState *filter, s32 paramID, s32 *paramVal) {
    FxParamState *state;
    u32 cmdType;
    s32 sectionIdx;
    s32 val;
    f32 sweepCoeff;

    state = filter;
    cmdType = paramID & 7;
    sectionIdx = paramID >> 3;
    val = *paramVal;
    if (sectionIdx >= state->unk8) {
        return 0;
    }
    switch (cmdType) {
    case 0:
        state->unk4[sectionIdx].unk0 = ((s32)(val * (u32)n_syn->unk40) / 1000) & ~7;
        break;
    case 1:
        state->unk4[sectionIdx].unk4 = ((s32)(val * (u32)n_syn->unk40) / 1000) & ~7;
        break;
    case 2:
        state->unk4[sectionIdx].unkA = val;
        break;
    case 3:
        state->unk4[sectionIdx].unk8 = val;
        break;
    case 4:
        state->unk4[sectionIdx].unkC = val;
        break;
    case 5:
        state->unk4[sectionIdx].unk10 = (((f32)val / 1000.0f) * 2.0f) / (f32)n_syn->unk40;
        break;
    case 6:
        sweepCoeff = (f32)val;
        break;
    case 7:
        if (state->unk4[sectionIdx].unk20 != NULL) {
            *(s16 *)state->unk4[sectionIdx].unk20 = val;
            _init_lpfilter(state->unk4[sectionIdx].unk20);
        }
        break;
    }
    if ((u32)state->unk4[sectionIdx].unk0 >= (u32)(state->unk0 - 0x10)) {
        state->unk4[sectionIdx].unk0 = state->unk0 - 0x10;
    }
    if ((u32)state->unk4[sectionIdx].unk0 >= (u32)(state->unk0 - 8)) {
        state->unk4[sectionIdx].unk0 = state->unk0 - 8;
    }
    if ((u32)state->unk4[sectionIdx].unk0 >= (u32)state->unk4[sectionIdx].unk4) {
        state->unk4[sectionIdx].unk4 = state->unk4[sectionIdx].unk0 + 8;
    }
    if (state->unk4[sectionIdx].unk24 != NULL) {
        if (cmdType != 6) {
            if (state->unk4[sectionIdx].unk4 - state->unk4[sectionIdx].unk0 != 0) {
                sweepCoeff = (state->unk4[sectionIdx].unk1C / (f32)(u32)(state->unk4[sectionIdx].unk4 - state->unk4[sectionIdx].unk0)) * 173123.4062f;
            } else {
                sweepCoeff = 0.0f;
            }
        }
        state->unk4[sectionIdx].unk1C = (f32)(u32)(state->unk4[sectionIdx].unk4 - state->unk4[sectionIdx].unk0) * (sweepCoeff / 173123.4062f);
    }
    return 0;
}

typedef struct {
    s32 unk0;
    u8 pad4[0x1C];
    u8 *unk20[2];
    u8 *unk28[2];
} FxNMOutputRing;

typedef struct {
    s32 unk0;
    s32 unk4;
    u8 pad8[0x10];
    s32 unk18;
    u8 pad1C[8];
    void *unk24;
} FxNMOutputState;

f32 _doModFunc();
Acmd *_n_loadBuffer(void *, s32, u8 *, s32, s32, Acmd *);

Acmd *_n_loadOutputBuffer(FxNMOutputRing *ring, FxNMOutputState *state, s32 bufIdx, s32 dmem, Acmd *cmdList) {
    Acmd *ptr;
    s32 fixedRatio;
    s32 sampleCount;
    s32 tempDmem;
    u8 *srcPtr;
    f32 accum;
    f32 ratio;
    f32 modVal;
    s32 align;
    s32 span;
    s32 count;
    s16 dmemHi;

    ptr = cmdList;
    tempDmem = 0x2E0;
    align = 0;
    count = 0xB8;
    if (state->unk24 != NULL) {
        span = state->unk4 - state->unk0;
        modVal = _doModFunc(state, count);
        modVal = modVal / span;
        modVal = (f32)(s32)(modVal * 32768.0f);
        modVal = modVal / 32768.0f;
        ratio = 1.0f - modVal;
        accum = (*(f32 *)((u8 *)state->unk24 + 0x24)) + (ratio * (f32)count);
        sampleCount = (s32)accum;
        *(f32 *)((u8 *)state->unk24 + 0x24) = accum - sampleCount;
        srcPtr = ring->unk28[bufIdx] + ((-(state->unk4 - state->unk18)) * 2);
        align = ((s32)srcPtr & 7) >> 1;
        ptr = _n_loadBuffer(ring, bufIdx, srcPtr - (align * 2), tempDmem, sampleCount + align, ptr);
        fixedRatio = (s32)(ratio * 32768.0f);
        dmemHi = (s16)(dmem >> 8);
        {
            Acmd *resampleCmd;
            resampleCmd = ptr++;
            resampleCmd->words.w0 = (osVirtualToPhysical(*(void **)((u8 *)state->unk24 + (bufIdx * 4) + 0x14)) & 0xFFFFFF) | 0x05000000;
            resampleCmd->words.w1 = ((fixedRatio & 0xFFFF) << 14) | ((*(u32 *)((u8 *)state->unk24 + 0x28) & 3) << 30) | (((tempDmem + (align * 2)) & 0xFFF) << 2) | (dmemHi & 3);
        }
        *(u32 *)((u8 *)state->unk24 + 0x28) = 0;
        state->unk18 += sampleCount - count;
    } else {
        srcPtr = ring->unk28[bufIdx] + (-state->unk4 * 2);
        ptr = _n_loadBuffer(ring, bufIdx, srcPtr, dmem, 0xB8, ptr);
    }
    return ptr;
}

Acmd *_n_loadBuffer(void *fx, s32 bufIdx, u8 *src, s32 dmem, s32 count, Acmd *cmdList) {
    Acmd *ptr;
    s32 wrappedCount;
    s32 directCount;
    u8 *endPtr;
    u8 *bufEnd;

    ptr = cmdList;
    bufEnd = (*(s32 *)fx * 2) + *(u8 **)((u8 *)fx + (bufIdx * 4) + 0x20);
    if (src < *(u8 **)((u8 *)fx + (bufIdx * 4) + 0x20)) {
        src += *(s32 *)fx * 2;
    }
    endPtr = src + (count * 2);
    if (endPtr > bufEnd) {
        wrappedCount = (endPtr - bufEnd) >> 1;
        directCount = (bufEnd - src) >> 1;
        {
            Acmd *cmd1;
            cmd1 = ptr++;
            cmd1->words.w0 = 0x04000000 | (((directCount * 2) & 0xFFF) << 12) | (dmem & 0xFFF);
            cmd1->words.w1 = osVirtualToPhysical(src);
        }
        {
            Acmd *cmd2;
            cmd2 = ptr++;
            cmd2->words.w0 = 0x04000000 | (((wrappedCount * 2) & 0xFFF) << 12) | ((dmem + (directCount * 2)) & 0xFFF);
            cmd2->words.w1 = osVirtualToPhysical(*(void **)((u8 *)fx + (bufIdx * 4) + 0x20));
        }
    } else {
        {
            Acmd *singleCmd;
            singleCmd = ptr++;
            singleCmd->words.w0 = 0x04000000 | (((count * 2) & 0xFFF) << 12) | (dmem & 0xFFF);
            singleCmd->words.w1 = osVirtualToPhysical(src);
        }
    }
    return ptr;
}

Acmd *_n_saveBuffer(void *fx, s32 bufIdx, u8 *dest, s32 dmem, Acmd *cmdList) {
    Acmd *ptr;
    s32 wrappedCount;
    s32 directCount;
    u8 *endPtr;
    u8 *bufEnd;

    ptr = cmdList;
    bufEnd = (*(s32 *)fx * 2) + *(u8 **)((u8 *)fx + (bufIdx * 4) + 0x20);
    if (dest < *(u8 **)((u8 *)fx + (bufIdx * 4) + 0x20)) {
        dest += *(s32 *)fx * 2;
    }
    endPtr = dest + 0x170;
    if (endPtr > bufEnd) {
        wrappedCount = (endPtr - bufEnd) >> 1;
        directCount = (bufEnd - dest) >> 1;
        {
            Acmd *cmd1;
            cmd1 = ptr++;
            cmd1->words.w0 = 0x06000000 | (((directCount * 2) & 0xFFF) << 12) | (dmem & 0xFFF);
            cmd1->words.w1 = osVirtualToPhysical(dest);
        }
        {
            Acmd *cmd2;
            cmd2 = ptr++;
            cmd2->words.w0 = 0x06000000 | (((wrappedCount * 2) & 0xFFF) << 12) | ((dmem + (directCount * 2)) & 0xFFF);
            cmd2->words.w1 = osVirtualToPhysical(*(void **)((u8 *)fx + (bufIdx * 4) + 0x20));
        }
    } else {
        {
            Acmd *singleCmd;
            singleCmd = ptr++;
            singleCmd->words.w0 = 0x06170000 | (dmem & 0xFFF);
            singleCmd->words.w1 = osVirtualToPhysical(dest);
        }
    }
    return ptr;
}

typedef struct {
    u8 pad0[2];
    s16 unk2;
    u8 pad4[0x24];
    u32 unk28;
} ReverbFilterBuffer;

Acmd *_n_filterBuffer(ReverbFilterBuffer *buf, s32 bufIdx, s32 gain, Acmd *cmdList) {
    Acmd *ptr;
    s16 gainHi;
    Acmd *loadCmd;
    Acmd *filterCmd;

    ptr = cmdList;
    gainHi = (s16)(gain >> 8);
    loadCmd = ptr++;
    loadCmd->words.w0 = 0x0B000020;
    loadCmd->words.w1 = osVirtualToPhysical((u8 *)buf + 8);
    filterCmd = ptr++;
    filterCmd->words.w0 = 0x0E000000 | ((buf->unk28 & 0xFF) << 16) | (buf->unk2 & 0xFFFF);
    filterCmd->words.w1 = (osVirtualToPhysical(*(void **)((u8 *)buf + (bufIdx * 4) + 0x2C)) & 0xFFFFFF) | ((gainHi & 0xFF) << 24);
    buf->unk28 = 0;
    return ptr;
}
typedef struct {
    u8 pad0[0x10];
    f32 unk10;
    f32 unk14;
    u8 pad18[4];
    f32 unk1C;
} FxNMModState;

f32 _doModFunc(FxNMModState *mod, s32 count) {
    f32 val;

    mod->unk14 += mod->unk10 * count;
    if (mod->unk14 > 2.0f) {
        mod->unk14 -= 4.0f;
    } else {
        mod->unk14 = mod->unk14;
    }
    val = mod->unk14;
    val = (val < 0.0f) ? -val : val;
    val -= 1.0f;
    return mod->unk1C * val;
}

extern Acmd *n_alMainBusPull();
Acmd *n_alSynOutputPull(void *synth, s16 *cmdList) {
    Acmd *cmd;
    Acmd *syncCmd;
    Acmd *outCmd;
    

    cmd = (Acmd *)cmdList;
    cmd = n_alMainBusPull(synth, cmd);
    syncCmd = cmd++;
    syncCmd->words.w0 = 0x0D000000;
    outCmd = cmd++;
    outCmd->words.w0 = 0x062E0000;
    outCmd->words.w1 = n_syn->unk48;
    return cmd;
}

