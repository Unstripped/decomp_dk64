#include "common.h"

#pragma GLOBAL_ASM("asm/global/nonmatchings/141EF0/n_alFxPull.s")

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

s32 n_alFxParamHdl(FxParamState *arg0, s32 arg1, s32 *arg2) {
    FxParamState *sp2C;
    u32 sp28;
    s32 sp24;
    s32 sp20;
    f32 sp1C;

    sp2C = arg0;
    sp28 = arg1 & 7;
    sp24 = arg1 >> 3;
    sp20 = *arg2;
    if (sp24 >= sp2C->unk8) {
        return 0;
    }
    switch (sp28) {
    case 0:
        sp2C->unk4[sp24].unk0 = ((s32)(sp20 * (u32)n_syn->unk40) / 1000) & ~7;
        break;
    case 1:
        sp2C->unk4[sp24].unk4 = ((s32)(sp20 * (u32)n_syn->unk40) / 1000) & ~7;
        break;
    case 2:
        sp2C->unk4[sp24].unkA = sp20;
        break;
    case 3:
        sp2C->unk4[sp24].unk8 = sp20;
        break;
    case 4:
        sp2C->unk4[sp24].unkC = sp20;
        break;
    case 5:
        sp2C->unk4[sp24].unk10 = (((f32)sp20 / 1000.0f) * 2.0f) / (f32)n_syn->unk40;
        break;
    case 6:
        sp1C = (f32)sp20;
        break;
    case 7:
        if (sp2C->unk4[sp24].unk20 != NULL) {
            *(s16 *)sp2C->unk4[sp24].unk20 = sp20;
            _init_lpfilter(sp2C->unk4[sp24].unk20);
        }
        break;
    }
    if ((u32)sp2C->unk4[sp24].unk0 >= (u32)(sp2C->unk0 - 0x10)) {
        sp2C->unk4[sp24].unk0 = sp2C->unk0 - 0x10;
    }
    if ((u32)sp2C->unk4[sp24].unk0 >= (u32)(sp2C->unk0 - 8)) {
        sp2C->unk4[sp24].unk0 = sp2C->unk0 - 8;
    }
    if ((u32)sp2C->unk4[sp24].unk0 >= (u32)sp2C->unk4[sp24].unk4) {
        sp2C->unk4[sp24].unk4 = sp2C->unk4[sp24].unk0 + 8;
    }
    if (sp2C->unk4[sp24].unk24 != NULL) {
        if (sp28 != 6) {
            if (sp2C->unk4[sp24].unk4 - sp2C->unk4[sp24].unk0 != 0) {
                sp1C = (sp2C->unk4[sp24].unk1C / (f32)(u32)(sp2C->unk4[sp24].unk4 - sp2C->unk4[sp24].unk0)) * 173123.4062f;
            } else {
                sp1C = 0.0f;
            }
        }
        sp2C->unk4[sp24].unk1C = (f32)(u32)(sp2C->unk4[sp24].unk4 - sp2C->unk4[sp24].unk0) * (sp1C / 173123.4062f);
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

Acmd *_n_loadOutputBuffer(FxNMOutputRing *arg0, FxNMOutputState *arg1, s32 arg2, s32 arg3, Acmd *arg4) {
    Acmd *sp54;
    s32 sp50;
    s32 sp4C;
    s32 sp48;
    u8 *sp44;
    f32 sp40;
    f32 sp3C;
    f32 sp38;
    s32 sp34;
    s32 sp30;
    s32 sp2C;
    s16 sp2A;

    sp54 = arg4;
    sp48 = 0x2E0;
    sp34 = 0;
    sp2C = 0xB8;
    if (arg1->unk24 != NULL) {
        sp30 = arg1->unk4 - arg1->unk0;
        sp38 = _doModFunc(arg1, sp2C);
        sp38 = sp38 / sp30;
        sp38 = (f32)(s32)(sp38 * 32768.0f);
        sp38 = sp38 / 32768.0f;
        sp3C = 1.0f - sp38;
        sp40 = (*(f32 *)((u8 *)arg1->unk24 + 0x24)) + (sp3C * (f32)sp2C);
        sp4C = (s32)sp40;
        *(f32 *)((u8 *)arg1->unk24 + 0x24) = sp40 - sp4C;
        sp44 = arg0->unk28[arg2] + ((-(arg1->unk4 - arg1->unk18)) * 2);
        sp34 = ((s32)sp44 & 7) >> 1;
        sp54 = _n_loadBuffer(arg0, arg2, sp44 - (sp34 * 2), sp48, sp4C + sp34, sp54);
        sp50 = (s32)(sp3C * 32768.0f);
        sp2A = (s16)(arg3 >> 8);
        {
            Acmd *sp24;
            sp24 = sp54++;
            sp24->words.w0 = (osVirtualToPhysical(*(void **)((u8 *)arg1->unk24 + (arg2 * 4) + 0x14)) & 0xFFFFFF) | 0x05000000;
            sp24->words.w1 = ((sp50 & 0xFFFF) << 14) | ((*(u32 *)((u8 *)arg1->unk24 + 0x28) & 3) << 30) | (((sp48 + (sp34 * 2)) & 0xFFF) << 2) | (sp2A & 3);
        }
        *(u32 *)((u8 *)arg1->unk24 + 0x28) = 0;
        arg1->unk18 += sp4C - sp2C;
    } else {
        sp44 = arg0->unk28[arg2] + (-arg1->unk4 * 2);
        sp54 = _n_loadBuffer(arg0, arg2, sp44, arg3, 0xB8, sp54);
    }
    return sp54;
}

Acmd *_n_loadBuffer(void *arg0, s32 arg1, u8 *arg2, s32 arg3, s32 arg4, Acmd *arg5) {
    Acmd *sp34;
    s32 sp30;
    s32 sp2C;
    u8 *sp28;
    u8 *sp24;

    sp34 = arg5;
    sp24 = (*(s32 *)arg0 * 2) + *(u8 **)((u8 *)arg0 + (arg1 * 4) + 0x20);
    if (arg2 < *(u8 **)((u8 *)arg0 + (arg1 * 4) + 0x20)) {
        arg2 += *(s32 *)arg0 * 2;
    }
    sp28 = arg2 + (arg4 * 2);
    if (sp28 > sp24) {
        sp30 = (sp28 - sp24) >> 1;
        sp2C = (sp24 - arg2) >> 1;
        {
            Acmd *sp20;
            sp20 = sp34++;
            sp20->words.w0 = 0x04000000 | (((sp2C * 2) & 0xFFF) << 12) | (arg3 & 0xFFF);
            sp20->words.w1 = osVirtualToPhysical(arg2);
        }
        {
            Acmd *sp1C;
            sp1C = sp34++;
            sp1C->words.w0 = 0x04000000 | (((sp30 * 2) & 0xFFF) << 12) | ((arg3 + (sp2C * 2)) & 0xFFF);
            sp1C->words.w1 = osVirtualToPhysical(*(void **)((u8 *)arg0 + (arg1 * 4) + 0x20));
        }
    } else {
        {
            Acmd *sp18;
            sp18 = sp34++;
            sp18->words.w0 = 0x04000000 | (((arg4 * 2) & 0xFFF) << 12) | (arg3 & 0xFFF);
            sp18->words.w1 = osVirtualToPhysical(arg2);
        }
    }
    return sp34;
}

Acmd *_n_saveBuffer(void *arg0, s32 arg1, u8 *arg2, s32 arg3, Acmd *arg4) {
    Acmd *sp34;
    s32 sp30;
    s32 sp2C;
    u8 *sp28;
    u8 *sp24;

    sp34 = arg4;
    sp24 = (*(s32 *)arg0 * 2) + *(u8 **)((u8 *)arg0 + (arg1 * 4) + 0x20);
    if (arg2 < *(u8 **)((u8 *)arg0 + (arg1 * 4) + 0x20)) {
        arg2 += *(s32 *)arg0 * 2;
    }
    sp28 = arg2 + 0x170;
    if (sp28 > sp24) {
        sp30 = (sp28 - sp24) >> 1;
        sp2C = (sp24 - arg2) >> 1;
        {
            Acmd *sp20;
            sp20 = sp34++;
            sp20->words.w0 = 0x06000000 | (((sp2C * 2) & 0xFFF) << 12) | (arg3 & 0xFFF);
            sp20->words.w1 = osVirtualToPhysical(arg2);
        }
        {
            Acmd *sp1C;
            sp1C = sp34++;
            sp1C->words.w0 = 0x06000000 | (((sp30 * 2) & 0xFFF) << 12) | ((arg3 + (sp2C * 2)) & 0xFFF);
            sp1C->words.w1 = osVirtualToPhysical(*(void **)((u8 *)arg0 + (arg1 * 4) + 0x20));
        }
    } else {
        {
            Acmd *sp18;
            sp18 = sp34++;
            sp18->words.w0 = 0x06170000 | (arg3 & 0xFFF);
            sp18->words.w1 = osVirtualToPhysical(arg2);
        }
    }
    return sp34;
}

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
typedef struct {
    u8 pad0[0x10];
    f32 unk10;
    f32 unk14;
    u8 pad18[4];
    f32 unk1C;
} FxNMModState;

f32 _doModFunc(FxNMModState *arg0, s32 arg1) {
    f32 sp4;

    arg0->unk14 += arg0->unk10 * arg1;
    if (arg0->unk14 > 2.0f) {
        arg0->unk14 -= 4.0f;
    } else {
        arg0->unk14 = arg0->unk14;
    }
    sp4 = arg0->unk14;
    sp4 = (sp4 < 0.0f) ? -sp4 : sp4;
    sp4 -= 1.0f;
    return arg0->unk1C * sp4;
}

extern Acmd *n_alMainBusPull();
Acmd *n_alSynOutputPull(void *arg0, s16 *arg1) {
    Acmd *sp24;
    Acmd *sp20;
    Acmd *sp1C;
    

    sp24 = (Acmd *)arg1;
    sp24 = n_alMainBusPull(arg0, sp24);
    sp20 = sp24++;
    sp20->words.w0 = 0x0D000000;
    sp1C = sp24++;
    sp1C->words.w0 = 0x062E0000;
    sp1C->words.w1 = n_syn->unk48;
    return sp24;
}

