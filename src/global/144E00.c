#include "common.h"

#pragma GLOBAL_ASM("asm/global/nonmatchings/144E00/n_alAdpcmPull.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/144E00/_decodeChunk.s")

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
