#include "common.h"

#pragma GLOBAL_ASM("asm/global/nonmatchings/141EF0/n_alFxPull.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/141EF0/n_alFxParamHdl.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/141EF0/_n_loadOutputBuffer.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/141EF0/_n_loadBuffer.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/141EF0/_n_saveBuffer.s")

typedef struct {
    u8 pad0[2];
    s16 unk2;
    u8 pad4[0x24];
    u32 unk28;
} ReverbFilterBuffer;

Acmd *_n_filterBuffer(ReverbFilterBuffer *arg0, s32 arg1, s32 arg2, Acmd *arg3) {
    Acmd *sp24;
    s16 sp22;
    Acmd *sp1C;
    Acmd *sp18;

    sp24 = arg3;
    sp22 = (s16)(arg2 >> 8);
    sp1C = sp24++;
    sp1C->words.w0 = 0x0B000020;
    sp1C->words.w1 = osVirtualToPhysical((u8 *)arg0 + 8);
    sp18 = sp24++;
    sp18->words.w0 = 0x0E000000 | ((arg0->unk28 & 0xFF) << 16) | (arg0->unk2 & 0xFFFF);
    sp18->words.w1 = (osVirtualToPhysical(*(void **)((u8 *)arg0 + (arg1 * 4) + 0x2C)) & 0xFFFFFF) | ((sp22 & 0xFF) << 24);
    arg0->unk28 = 0;
    return sp24;
}

#pragma GLOBAL_ASM("asm/global/nonmatchings/141EF0/_doModFunc.s")


typedef struct {
    u8 pad0[0x40];
    s32 unk40;
    u8 pad44[4];
    u32 unk48;
} ReverbSynth;

extern ReverbSynth *D_807563E4;
extern Acmd *n_alMainBusPull();
Acmd *func_8073E800(void *arg0, s16 *arg1) {
    Acmd *sp24;
    Acmd *sp20;
    Acmd *sp1C;
    

    sp24 = (Acmd *)arg1;
    sp24 = n_alMainBusPull(arg0, sp24);
    sp20 = sp24++;
    sp20->words.w0 = 0x0D000000;
    sp1C = sp24++;
    sp1C->words.w0 = 0x062E0000;
    sp1C->words.w1 = D_807563E4->unk48;
    return sp24;
}
