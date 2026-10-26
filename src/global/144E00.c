#include "common.h"

#pragma GLOBAL_ASM("asm/global/nonmatchings/144E00/n_alAdpcmPull.s")

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
