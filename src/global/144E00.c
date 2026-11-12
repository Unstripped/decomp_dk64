#include "common.h"
#include "audio_synth.h"
#include "proto/global/144E00.h"

Acmd *n_alAdpcmPull(N_PVoice *filter, s16 *outp, s32 count, Acmd *cmdList) {
    Acmd *cmd;
    s16 state;
    s32 neededSamples;
    s32 frameBlocks;
    s32 byteCount;
    s32 wasteBytes;
    s32 clearOffset;
    s32 clearBytes;
    s32 chunkCount;
    s32 dmaOut;
    s32 subSamples;
    s32 outAddr;
    s32 wasLoaded;
    s32 isLooping;
    N_PVoice *f;
    Acmd *initCmd;
    Acmd *dmaCmd;
    Acmd *clearCmd;

    cmd = cmdList;
    wasLoaded = 0;
    isLooping = 0;
    f = filter;
    if (count == 0) {
        return cmd;
    }
    state = 0;
    initCmd = cmd++;
    initCmd->words.w0 = (f->dc_bookSize & 0xFFFFFF) | 0x0B000000;
    initCmd->words.w1 = (u32)f->dc_table->waveInfo.adpcmWave.book->book & 0x1FFFFFFF;
    isLooping = (f->dc_sample + count > f->dc_loop.end) && f->dc_loop.count;
    if (isLooping != 0) {
        chunkCount = f->dc_loop.end - f->dc_sample;
    } else {
        chunkCount = count;
    }
    if (f->dc_lastsam != 0) {
        subSamples = 0x10 - f->dc_lastsam;
    } else {
        subSamples = 0;
    }
    neededSamples = chunkCount - subSamples;
    if (neededSamples < 0) {
        neededSamples = 0;
    }
    frameBlocks = (neededSamples + 0xF) >> 4;
    byteCount = frameBlocks * 9;
    if (isLooping != 0) {
        cmd = alLoadParam(cmd, f, neededSamples, byteCount, *outp, state, f->dc_first);
        if (f->dc_lastsam != 0) {
            *outp += f->dc_lastsam * 2;
        } else {
            *outp += 0x20;
        }
        f->dc_lastsam = f->dc_loop.start & 0xF;
        f->dc_memin = (s32)f->dc_table->base + (f->dc_loop.start >> 4) * 9 + 9;
        f->dc_sample = f->dc_loop.start;
        outAddr = *outp;
        if (count > chunkCount) {
            do {
                count -= chunkCount;
                dmaOut = (((frameBlocks + 1) << 5) + outAddr + 0x10) & ~0x1F;
                outAddr += chunkCount * 2;
                if ((f->dc_loop.count != -1) && (f->dc_loop.count != 0)) {
                    f->dc_loop.count = f->dc_loop.count - 1;
                }
                chunkCount = (count < f->dc_loop.end - f->dc_loop.start) ? count : f->dc_loop.end - f->dc_loop.start;
                neededSamples = (chunkCount - 0x10) + f->dc_lastsam;
                if (neededSamples < 0) {
                    neededSamples = 0;
                }
                frameBlocks = (neededSamples + 0xF) >> 4;
                byteCount = frameBlocks * 9;
                cmd = alLoadParam(cmd, f, neededSamples, byteCount, dmaOut, state, f->dc_first | 2);
                dmaCmd = cmd++;
                dmaCmd->words.w0 = (((f->dc_lastsam * 2) + dmaOut) & 0xFFFFFF) | 0x0A000000;
                dmaCmd->words.w1 = ((outAddr & 0xFFFF) << 0x10) | ((chunkCount * 2) & 0xFFFF);
            } while (count > chunkCount);
        }
        f->dc_lastsam = (f->dc_lastsam + count) & 0xF;
        f->dc_sample = f->dc_sample + count;
        f->dc_memin = f->dc_memin + (frameBlocks * 9);
        return cmd;
    }
    chunkCount = frameBlocks << 4;
    wasteBytes = (f->dc_memin + byteCount) - ((s32)f->dc_table->base + f->dc_table->len);
    if (wasteBytes < 0) {
        wasteBytes = 0;
    }
    clearBytes = (wasteBytes / 9) * 0x10;
    if (clearBytes > (chunkCount + subSamples)) {
        clearBytes = chunkCount + subSamples;
    }
    byteCount -= wasteBytes;
    if ((clearBytes - (clearBytes & 0xF)) < count) {
        wasLoaded = 1;
        cmd = alLoadParam(cmd, f, chunkCount - clearBytes, byteCount, *outp, state, f->dc_first);
        if (f->dc_lastsam != 0) {
            *outp += f->dc_lastsam * 2;
        } else {
            *outp += 0x20;
        }
        f->dc_lastsam = (f->dc_lastsam + count) & 0xF;
        f->dc_sample = f->dc_sample + count;
        f->dc_memin = f->dc_memin + (frameBlocks * 9);
    } else {
        f->dc_lastsam = 0;
        f->dc_memin = f->dc_memin + (frameBlocks * 9);
    }
    if (clearBytes != 0) {
        f->dc_lastsam = 0;
        if (wasLoaded != 0) {
            clearOffset = ((subSamples + chunkCount) - clearBytes) * 2;
        } else {
            clearOffset = 0;
        }
        clearCmd = cmd++;
        clearCmd->words.w0 = ((*outp + clearOffset) & 0xFFFFFF) | 0x02000000;
        clearCmd->words.w1 = clearBytes * 2;
    }
    return cmd;
}

void _decodeChunk(N_PVoice *filter, s32 paramID, ALWaveTable *wave) {
    N_PVoice *temp;

    temp = filter;
    switch (paramID) {
    case 5:
        temp->dc_table = wave;
        temp->dc_memin = (s32)temp->dc_table->base;
        temp->dc_sample = 0;
        switch (temp->dc_table->type) {
        case 0:
            temp->dc_table->len = (temp->dc_table->len / 9) * 9;
            temp->dc_bookSize = 2 * temp->dc_table->waveInfo.adpcmWave.book->order * temp->dc_table->waveInfo.adpcmWave.book->npredictors * 8;
            if (temp->dc_table->waveInfo.adpcmWave.loop != NULL) {
                temp->dc_loop.start = temp->dc_table->waveInfo.adpcmWave.loop->start;
                temp->dc_loop.end = temp->dc_table->waveInfo.adpcmWave.loop->end;
                temp->dc_loop.count = temp->dc_table->waveInfo.adpcmWave.loop->count;
                bcopy(temp->dc_table->waveInfo.adpcmWave.loop->state, temp->dc_lstate, 0x20);
            } else {
                temp->dc_loop.start = temp->dc_loop.end = temp->dc_loop.count = 0;
            }
            break;
        case 1:
            if (temp->dc_table->waveInfo.rawWave.loop != NULL) {
                temp->dc_loop.start = temp->dc_table->waveInfo.rawWave.loop->start;
                temp->dc_loop.end = temp->dc_table->waveInfo.rawWave.loop->end;
                temp->dc_loop.count = temp->dc_table->waveInfo.rawWave.loop->count;
            } else {
                temp->dc_loop.start = temp->dc_loop.end = temp->dc_loop.count = 0;
            }
            break;
        default:
            break;
        }
        break;
    case 4:
        temp->dc_lastsam = 0;
        temp->dc_first = 1;
        temp->dc_sample = 0;
        if (temp->dc_table != NULL) {
            temp->dc_memin = (s32)temp->dc_table->base;
            if (temp->dc_table->type == 0) {
                if (temp->dc_table->waveInfo.adpcmWave.loop != NULL) {
                    temp->dc_loop.count = temp->dc_table->waveInfo.adpcmWave.loop->count;
                }
            } else if (temp->dc_table->type == 1) {
                if (temp->dc_table->waveInfo.rawWave.loop != NULL) {
                    temp->dc_loop.count = temp->dc_table->waveInfo.rawWave.loop->count;
                }
            }
        }
        break;
    default:
        break;
    }
}

Acmd *alLoadParam(Acmd *ptr, N_PVoice *filter, s32 samples, s32 count, s16 out, s16 state, s32 flags) {
    s32 offset;
    s32 dmaAddr;

    if (count > 0) {
        Acmd *cmd;

        dmaAddr = filter->dc_dma(filter->dc_memin, count, filter->dc_dmaState);
        offset = dmaAddr & 7;
        count += offset;
        cmd = ptr++;
        cmd->words.w0 = 0x04000000 | ((((count - (count & 7)) + 8) & 0xFFF) << 12) | (state & 0xFFF);
        cmd->words.w1 = (s32)(dmaAddr - offset);
    } else {
        offset = 0;
    }
    if (flags & 2) {
        Acmd *cmd;

        cmd = ptr++;
        cmd->words.w0 = 0x0F000000;
        cmd->words.w1 = (u32)filter->dc_lstate & 0x1FFFFFFF;
    }
    {
        Acmd *cmd;

        cmd = ptr++;
        cmd->words.w0 = ((u32)filter->dc_state & 0x1FFFFFFF & 0xFFFFFF) | 0x01000000;
        cmd->words.w1 = ((flags & 0xF) << 28) | (((samples * 2) & 0xFFF) << 16) | ((offset & 0xF) << 12) | (out & 0xFFF);
    }
    filter->dc_first = 0;
    return ptr;
}
