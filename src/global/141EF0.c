#include "common.h"
#include "audio_synth.h"
#include "proto/global/140600.h"
#include "proto/global/141EF0.h"
#include "proto/global/1445A0.h"
#include "proto/global/144A90.h"


extern N_ALSynth *n_syn;

extern u8 D_807FF0F4[];
extern u8 D_807FF0F6[];

#define SWAP(in, out) { dmemTmp = out; out = in; in = dmemTmp; }

Acmd *n_alFxPull(s32 time, Acmd *cmdList, s32 busIndex) {
    Acmd *ptr;
    SynFx *ring;
    s16 sectionIdx;
    s16 dmemIn;
    s16 dmemOut;
    s16 inDmem;
    s16 outDmem;
    s16 *inPtr;
    s16 *outPtr;
    s32 pad68;
    s16 *lastInPtr;
    SynFxDelay *section;
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
    ring = n_syn->auxBus[busIndex].fx;
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
    ptr = _n_saveBuffer(ring, 0, ring->input[0], inDmem, ptr);
    if (D_807FF0F4[busIndex] != 0) {
        ptr = _n_saveBuffer(ring, 1, ring->input[1], 0x930, ptr);
    }
    for (busChan = 0; busChan <= D_807FF0F4[busIndex]; busChan++) {
        clearCmd = ptr++;
        clearCmd->words.w0 = (outDmem & 0xFFFFFF) | 0x02000000;
        clearCmd->words.w1 = 0x170;
        for (sectionIdx = 0; sectionIdx < ring->section_count; sectionIdx++) {
            section = ring->delay + sectionIdx;
            inPtr = &ring->input[busChan][-section->input];
            outPtr = &ring->input[busChan][-section->output];
            if ((D_807FF0F6[busIndex] != 0) && (D_807FF0F4[busIndex] != 0)) {
                section->ffcoef = -section->ffcoef;
                section->fbcoef = -section->fbcoef;
            }
            if (inPtr == lastInPtr) {
                SWAP(dmemIn, dmemOut);
            } else {
                ptr = _n_loadBuffer(ring, busChan, inPtr, dmemIn, 0xB8, ptr);
            }
            ptr = _n_loadOutputBuffer(ring, section, busChan, dmemOut, ptr);
            if (section->ffcoef != 0) {
                mixCmd1 = ptr++;
                mixCmd1->words.w0 = ((u16)section->ffcoef & 0xFFFF) | 0x0C000000;
                mixCmd1->words.w1 = ((dmemIn & 0xFFFF) << 16) | (dmemOut & 0xFFFF);
                if ((section->rs == NULL) && (section->lp == NULL)) {
                    ptr = _n_saveBuffer(ring, busChan, outPtr, dmemOut, ptr);
                }
            }
            if (section->fbcoef != 0) {
                mixCmd2 = ptr++;
                mixCmd2->words.w0 = ((u16)section->fbcoef & 0xFFFF) | 0x0C000000;
                mixCmd2->words.w1 = ((dmemOut & 0xFFFF) << 16) | (dmemIn & 0xFFFF);
                ptr = _n_saveBuffer(ring, busChan, inPtr, dmemIn, ptr);
            }
            if (section->lp != NULL) {
                ptr = _n_filterBuffer(section->lp, busChan, dmemOut, ptr);
            }
            if (section->rs == NULL) {
                ptr = _n_saveBuffer(ring, busChan, outPtr, dmemOut, ptr);
            }
            if (section->gain != 0) {
                if (D_807FF0F4[busIndex] != 0) {
                    scaleCmd1 = ptr++;
                    scaleCmd1->words.w0 = ((u16)section->gain & 0xFFFF) | 0x0C000000;
                    scaleCmd1->words.w1 = ((dmemOut & 0xFFFF) << 16) | (outDmem & 0xFFFF);
                    ; // FAKE: own .loc line keeps the w1 sw out of the arm-closing b delay slot (Q0430, Q0183; removing it: 44 lines differ)
                } else {
                    scaledGain = (u32)((f32)section->gain * 1.4142f);
                    if (scaledGain >= 0x8000) {
                        scaledGain = 0x7FFF;
                    }
                    scaleCmd2 = ptr++;
                    scaleCmd2->words.w0 = ((u16)scaledGain & 0xFFFF) | 0x0C000000;
                    scaleCmd2->words.w1 = ((dmemOut & 0xFFFF) << 16) | (outDmem & 0xFFFF);
                }
            }
            lastInPtr = &ring->input[busChan][section->output];
        }
        if ((D_807FF0F4[busIndex] != 0) && (busChan == 0)) {
            ptr = _n_loadBuffer(ring, 1, ring->input[1], inDmem, 0xB8, ptr);
            if (D_807FF0F6[busIndex] != 0) {
                panCmd1 = ptr++;
                panCmd1->words.w0 = 0x0C005A82;
                panCmd1->words.w1 = ((outDmem & 0xFFFF) << 16) | 0x650;
                ; // FAKE: own .loc line keeps the w1 sw out of the arm-closing b delay slot (Q0430, Q0183; removing it: 34 lines differ)
            } else {
                panCmd2 = ptr++;
                panCmd2->words.w0 = 0x0C005A82;
                panCmd2->words.w1 = ((outDmem & 0xFFFF) << 16) | 0x4E0;
            }
        } else {} // FAKE: empty else arm emits the target b join; nop under IDO 7.1 -g (Q0671; removing it: 31 lines differ)
        dmaCmd = ptr++;
        dmaCmd->words.w0 = (outDmem & 0xFFFFFF) | 0x0A000000;
        dmaCmd->words.w1 = 0x07C00170;
        ring->input[busChan] += 0xB8;
        if (ring->input[busChan] > &ring->base[busChan][ring->length]) {
            ring->input[busChan] -= ring->length;
        }
    }
    return ptr;
}


s32 n_alFxParamHdl(void *filter, s32 paramID, s32 *paramVal) {
    SynFx *state;
    u32 cmdType;
    s32 sectionIdx;
    s32 val;
    f32 sweepCoeff;

    state = filter;
    cmdType = paramID & 7;
    sectionIdx = paramID >> 3;
    val = *paramVal;
    if (sectionIdx >= state->section_count) {
        return 0;
    }
    switch (cmdType) {
    case 0:
        state->delay[sectionIdx].input = ((s32)(val * (u32)n_syn->outputRate) / 1000) & ~7;
        break;
    case 1:
        state->delay[sectionIdx].output = ((s32)(val * (u32)n_syn->outputRate) / 1000) & ~7;
        break;
    case 2:
        state->delay[sectionIdx].fbcoef = val;
        break;
    case 3:
        state->delay[sectionIdx].ffcoef = val;
        break;
    case 4:
        state->delay[sectionIdx].gain = val;
        break;
    case 5:
        state->delay[sectionIdx].rsinc = (((f32)val / 1000.0f) * 2.0f) / (f32)n_syn->outputRate;
        break;
    case 6:
        sweepCoeff = (f32)val;
        break;
    case 7:
        if (state->delay[sectionIdx].lp != NULL) {
            state->delay[sectionIdx].lp->lp.fc = val;
            _init_lpfilter(&state->delay[sectionIdx].lp->lp);
        }
        break;
    }
    if (state->delay[sectionIdx].input >= state->length - 0x10) {
        state->delay[sectionIdx].input = state->length - 0x10;
    }
    if (state->delay[sectionIdx].input >= state->length - 8) {
        state->delay[sectionIdx].input = state->length - 8;
    }
    if (state->delay[sectionIdx].input >= state->delay[sectionIdx].output) {
        state->delay[sectionIdx].output = state->delay[sectionIdx].input + 8;
    }
    if (state->delay[sectionIdx].rs != NULL) {
        if (cmdType != 6) {
            if (state->delay[sectionIdx].output - state->delay[sectionIdx].input != 0) {
                sweepCoeff = (state->delay[sectionIdx].rsgain / (f32)(state->delay[sectionIdx].output - state->delay[sectionIdx].input)) * 173123.4062f;
            } else {
                sweepCoeff = 0.0f;
            }
        }
        state->delay[sectionIdx].rsgain = (f32)(state->delay[sectionIdx].output - state->delay[sectionIdx].input) * (sweepCoeff / 173123.4062f);
    }
    return 0;
}

Acmd *_n_loadOutputBuffer(SynFx *ring, SynFxDelay *state, s32 bufIdx, s32 dmem, Acmd *cmdList) {
    Acmd *ptr;
    s32 fixedRatio;
    s32 sampleCount;
    s32 tempDmem;
    s16 *srcPtr;
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
    if (state->rs != NULL) {
        span = state->output - state->input;
        modVal = _doModFunc(state, count);
        modVal = modVal / span;
        modVal = (f32)(s32)(modVal * 32768.0f);
        modVal = modVal / 32768.0f;
        ratio = 1.0f - modVal;
        accum = state->rs->delta + (ratio * (f32)count);
        sampleCount = (s32)accum;
        state->rs->delta = accum - sampleCount;
        srcPtr = &ring->input[bufIdx][-(state->output - state->rsdelta)];
        align = ((s32)srcPtr & 7) >> 1;
        ptr = _n_loadBuffer(ring, bufIdx, srcPtr - align, tempDmem, sampleCount + align, ptr);
        fixedRatio = (s32)(ratio * 32768.0f);
        dmemHi = (s16)(dmem >> 8);
        {
            Acmd *resampleCmd;
            resampleCmd = ptr++;
            resampleCmd->words.w0 = (osVirtualToPhysical(state->rs->state[bufIdx]) & 0xFFFFFF) | 0x05000000;
            resampleCmd->words.w1 = ((state->rs->first & 3) << 30) | ((fixedRatio & 0xFFFF) << 14) | (((tempDmem + (align * 2)) & 0xFFF) << 2) | (dmemHi & 3);
        }
        state->rs->first = 0;
        state->rsdelta += sampleCount - count;
    } else {
        srcPtr = &ring->input[bufIdx][-state->output];
        ptr = _n_loadBuffer(ring, bufIdx, srcPtr, dmem, 0xB8, ptr);
    }
    return ptr;
}

Acmd *_n_loadBuffer(SynFx *fx, s32 bufIdx, s16 *src, s32 dmem, s32 count, Acmd *cmdList) {
    Acmd *ptr;
    s32 wrappedCount;
    s32 directCount;
    s16 *endPtr;
    s16 *bufEnd;

    ptr = cmdList;
    bufEnd = &fx->base[bufIdx][fx->length];
    if (src < fx->base[bufIdx]) {
        src += fx->length;
    }
    endPtr = src + count;
    if (endPtr > bufEnd) {
        wrappedCount = endPtr - bufEnd;
        directCount = bufEnd - src;
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
            cmd2->words.w1 = osVirtualToPhysical(fx->base[bufIdx]);
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

Acmd *_n_saveBuffer(SynFx *fx, s32 bufIdx, s16 *dest, s32 dmem, Acmd *cmdList) {
    Acmd *ptr;
    s32 wrappedCount;
    s32 directCount;
    s16 *endPtr;
    s16 *bufEnd;

    ptr = cmdList;
    bufEnd = &fx->base[bufIdx][fx->length];
    if (dest < fx->base[bufIdx]) {
        dest += fx->length;
    }
    endPtr = dest + 0xB8;
    if (endPtr > bufEnd) {
        wrappedCount = endPtr - bufEnd;
        directCount = bufEnd - dest;
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
            cmd2->words.w1 = osVirtualToPhysical(fx->base[bufIdx]);
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

Acmd *_n_filterBuffer(SynLPFilter *buf, s32 bufIdx, s32 gain, Acmd *cmdList) {
    Acmd *ptr;
    s16 gainHi;
    Acmd *loadCmd;
    Acmd *filterCmd;

    ptr = cmdList;
    gainHi = (s16)(gain >> 8);
    loadCmd = ptr++;
    loadCmd->words.w0 = 0x0B000020;
    loadCmd->words.w1 = osVirtualToPhysical(buf->lp.coeff);
    filterCmd = ptr++;
    filterCmd->words.w0 = 0x0E000000 | ((buf->lp.first & 0xFF) << 16) | (buf->lp.fgain & 0xFFFF);
    filterCmd->words.w1 = (osVirtualToPhysical(buf->fstate[bufIdx]) & 0xFFFFFF) | ((gainHi & 0xFF) << 24);
    buf->lp.first = 0;
    return ptr;
}
f32 _doModFunc(SynFxDelay *mod, s32 count) {
    f32 val;

    mod->rsval += mod->rsinc * count;
    mod->rsval = (mod->rsval > 2.0f) ? mod->rsval - 4.0f : mod->rsval;
    val = mod->rsval;
    val = (val < 0.0f) ? -val : val;
    val -= 1.0f;
    return mod->rsgain * val;
}

Acmd *n_alSynOutputPull(s32 sampleCount, Acmd *cmdList) {
    Acmd *cmd;
    Acmd *syncCmd;
    Acmd *outCmd;

    cmd = cmdList;
    cmd = n_alMainBusPull(sampleCount, cmd);
    syncCmd = cmd++;
    syncCmd->words.w0 = 0x0D000000;
    outCmd = cmd++;
    outCmd->words.w0 = 0x062E0000;
    outCmd->words.w1 = (u32)n_syn->outBuffer;
    return cmd;
}

