#include "common.h"

struct AdpcmNMAcmd;
struct AdpcmNMLoadFilter;
typedef struct {
    u32 w0;
    u32 w1;
} AdpcmAcmd;

typedef struct {
    s32 unk0;
    s32 unk4;
    u8 pad8[8];
    s32 *loop;
} AdpcmWave;

typedef struct {
    u8 pad0[0xC];
    void *unkC;
    void *unk10;
    s32 unk14;
    s32 unk18;
    s32 unk1C;
    AdpcmWave *unk20;
    s32 unk24;
    s32 (*dma)(void *, s32, void *);
    void *unk2C;
    s32 unk30;
    s32 unk34;
    s32 unk38;
    s32 unk3C;
} AdpcmFilter;

struct AdpcmNMAcmd *alLoadParam(struct AdpcmNMAcmd *ptr, struct AdpcmNMLoadFilter *filter, s32 samples, s32 count, s16 out, s16 state, s32 flags);

struct AdpcmNMAcmd *n_alAdpcmPull(AdpcmFilter *filter, s16 *outp, s32 count, struct AdpcmNMAcmd *cmdList) {
    AdpcmAcmd *cmd;
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
    AdpcmFilter *f;
    AdpcmAcmd *initCmd;
    AdpcmAcmd *dmaCmd;
    AdpcmAcmd *clearCmd;

    cmd = (AdpcmAcmd *)cmdList;
    wasLoaded = 0;
    isLooping = 0;
    f = filter;
    if (count == 0) {
        return (struct AdpcmNMAcmd *)cmd;
    }
    state = 0;
    initCmd = cmd++;
    initCmd->w0 = (f->unk24 & 0xFFFFFF) | 0x0B000000;
    initCmd->w1 = ((u32)f->unk20->loop + 8) & 0x1FFFFFFF;
    isLooping = ((u32)(f->unk30 + count) > (u32)f->unk18) && f->unk1C;
    if (isLooping != 0) {
        chunkCount = f->unk18 - f->unk30;
    } else {
        chunkCount = count;
    }
    if (f->unk34 != 0) {
        subSamples = 0x10 - f->unk34;
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
        cmd = (AdpcmAcmd *)alLoadParam((struct AdpcmNMAcmd *)cmd, (struct AdpcmNMLoadFilter *)f, neededSamples, byteCount, *outp, state, f->unk38);
        if (f->unk34 != 0) {
            *outp += f->unk34 * 2;
        } else {
            *outp += 0x20;
        }
        f->unk34 = f->unk14 & 0xF;
        f->unk3C = f->unk20->unk0 + ((u32)f->unk14 >> 4) * 9 + 9;
        f->unk30 = f->unk14;
        outAddr = *outp;
        if (count > chunkCount) {
            do {
                count -= chunkCount;
                dmaOut = (((frameBlocks + 1) << 5) + outAddr + 0x10) & ~0x1F;
                outAddr += chunkCount * 2;
                if ((f->unk1C != -1) && (f->unk1C != 0)) {
                    f->unk1C = f->unk1C - 1;
                }
                chunkCount = ((u32)count < (u32)(f->unk18 - f->unk14)) ? count : f->unk18 - f->unk14;
                neededSamples = (chunkCount - 0x10) + f->unk34;
                if (neededSamples < 0) {
                    neededSamples = 0;
                }
                frameBlocks = (neededSamples + 0xF) >> 4;
                byteCount = frameBlocks * 9;
                cmd = (AdpcmAcmd *)alLoadParam((struct AdpcmNMAcmd *)cmd, (struct AdpcmNMLoadFilter *)f, neededSamples, byteCount, dmaOut, state, f->unk38 | 2);
                dmaCmd = cmd++;
                dmaCmd->w0 = (((f->unk34 * 2) + dmaOut) & 0xFFFFFF) | 0x0A000000;
                dmaCmd->w1 = ((outAddr & 0xFFFF) << 0x10) | ((chunkCount * 2) & 0xFFFF);
            } while (count > chunkCount);
        }
        f->unk34 = (f->unk34 + count) & 0xF;
        f->unk30 = f->unk30 + count;
        f->unk3C = f->unk3C + (frameBlocks * 9);
        return (struct AdpcmNMAcmd *)cmd;
    }
    chunkCount = frameBlocks << 4;
    wasteBytes = (f->unk3C + byteCount) - (f->unk20->unk0 + f->unk20->unk4);
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
        cmd = (AdpcmAcmd *)alLoadParam((struct AdpcmNMAcmd *)cmd, (struct AdpcmNMLoadFilter *)f, chunkCount - clearBytes, byteCount, *outp, state, f->unk38);
        if (f->unk34 != 0) {
            *outp += f->unk34 * 2;
        } else {
            *outp += 0x20;
        }
        f->unk34 = (f->unk34 + count) & 0xF;
        f->unk30 = f->unk30 + count;
        f->unk3C = f->unk3C + (frameBlocks * 9);
    } else {
        f->unk34 = 0;
        f->unk3C = f->unk3C + (frameBlocks * 9);
    }
    if (clearBytes != 0) {
        f->unk34 = 0;
        if (wasLoaded != 0) {
            clearOffset = ((subSamples + chunkCount) - clearBytes) * 2;
        } else {
            clearOffset = 0;
        }
        clearCmd = cmd++;
        clearCmd->w0 = ((*outp + clearOffset) & 0xFFFFFF) | 0x02000000;
        clearCmd->w1 = clearBytes * 2;
    }
    return (struct AdpcmNMAcmd *)cmd;
}

typedef struct DecodeBook {
    s32 unk0;
    s32 unk4;
    s32 unk8;
} DecodeBook;

typedef struct DecodeWave {
    s32 unk0;
    s32 unk4;
    u8 pad8[4];
    DecodeBook *book;
    s32 *loop;
} DecodeWave;

typedef struct DecodeFilter {
    u8 pad0[0x10];
    void *out;
    s32 unk14;
    s32 unk18;
    s32 unk1C;
    DecodeWave *wave;
    s32 unk24;
    u8 pad28[8];
    s32 unk30;
    s32 unk34;
    s32 unk38;
    s32 unk3C;
} DecodeFilter;

void _decodeChunk(DecodeFilter *filter, s32 paramID, DecodeWave *wave) {
    DecodeFilter *temp;

    temp = filter;
    switch (paramID) {
    case 5:
        temp->wave = wave;
        temp->unk3C = temp->wave->unk0;
        temp->unk30 = 0;
        switch (temp->wave->pad8[0]) {
        case 0:
            temp->wave->unk4 = (temp->wave->unk4 / 9) * 9;
            temp->unk24 = (temp->wave->loop[1] * (temp->wave->loop[0] << 1)) * 8;
            if (temp->wave->book != NULL) {
                temp->unk14 = temp->wave->book->unk0;
                temp->unk18 = temp->wave->book->unk4;
                temp->unk1C = temp->wave->book->unk8;
                bcopy((u8 *)temp->wave->book + 0xC, temp->out, 0x20);
            } else {
                temp->unk14 = temp->unk18 = temp->unk1C = 0;
            }
            break;
        case 1:
            if (temp->wave->book != NULL) {
                temp->unk14 = temp->wave->book->unk0;
                temp->unk18 = temp->wave->book->unk4;
                temp->unk1C = temp->wave->book->unk8;
            } else {
                temp->unk14 = temp->unk18 = temp->unk1C = 0;
            }
            break;
        default:
            break;
        }
        break;
    case 4:
        temp->unk34 = 0;
        temp->unk38 = 1;
        temp->unk30 = 0;
        if (temp->wave != NULL) {
            temp->unk3C = temp->wave->unk0;
            if (temp->wave->pad8[0] == 0) {
                if (temp->wave->book != NULL) {
                    temp->unk1C = temp->wave->book->unk8;
                }
            } else if (temp->wave->pad8[0] == 1) {
                if (temp->wave->book != NULL) {
                    temp->unk1C = temp->wave->book->unk8;
                }
            }
        }
        break;
    default:
        break;
    }
}

typedef struct AdpcmNMAcmd {
    u32 w0;
    u32 w1;
} AdpcmNMAcmd;

typedef struct AdpcmNMLoadFilter {
    u8 pad0[0xC];
    void *unkC;
    void *unk10;
    u8 pad14[0x14];
    s32 (*dma)(void *, s32, void *);
    void *unk2C;
    u8 pad30[8];
    s32 unk38;
    void *unk3C;
} AdpcmNMLoadFilter;

AdpcmNMAcmd *alLoadParam(AdpcmNMAcmd *ptr, AdpcmNMLoadFilter *filter, s32 samples, s32 count, s16 out, s16 state, s32 flags) {
    s32 offset;
    s32 dmaAddr;

    if (count > 0) {
        AdpcmNMAcmd *cmd;

        dmaAddr = filter->dma(filter->unk3C, count, filter->unk2C);
        offset = dmaAddr & 7;
        count += offset;
        cmd = ptr++;
        cmd->w0 = 0x04000000 | ((((count - (count & 7)) + 8) & 0xFFF) << 12) | (state & 0xFFF);
        cmd->w1 = (s32)(dmaAddr - offset);
    } else {
        offset = 0;
    }
    if (flags & 2) {
        AdpcmNMAcmd *cmd;

        cmd = ptr++;
        cmd->w0 = 0x0F000000;
        cmd->w1 = (u32)filter->unk10 & 0x1FFFFFFF;
    }
    {
        AdpcmNMAcmd *cmd;

        cmd = ptr++;
        cmd->w0 = ((u32)filter->unkC & 0x1FFFFFFF & 0xFFFFFF) | 0x01000000;
        cmd->w1 = ((flags & 0xF) << 28) | (((samples * 2) & 0xFFF) << 16) | ((offset & 0xF) << 12) | (out & 0xFFF);
    }
    filter->unk38 = 0;
    return ptr;
}
