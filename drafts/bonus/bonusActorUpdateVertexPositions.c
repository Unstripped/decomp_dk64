// func_8002881C (src/bonus/2690.c): stage 5 (W2Bonus revisit): frame 0x58 + all 392 insns match except 'sh t1,6(v0); slti at,v1,7' order in vertex-loop join block; deadsweep with --extra across all 8 locals 0 gain, line joins across all lines no change, as1 hoists slti from loop-latch blt to join block after sh
#include "common.h"

typedef struct {
    s8 unk0;
    u8 unk1;
    u16 unk2;
    s16 unk4;
    s16 unk6;
} W2B_D2Ent;

typedef struct {
    char pad0[0x1C];
    W2B_D2Ent *unk1C;
} W2B_D2Model;

typedef struct {
    char pad0[0x20];
    f32 unk20;
} W2B_D2Info;

typedef struct {
    char pad0[4];
    u8 unk4;
    u8 unk5;
} W2B_D2Sub;

typedef struct W2B_D2Actor W2B_D2Actor;
struct W2B_D2Actor {
    char pad0[4];
    W2B_D2Model *unk4;
    char pad8[0x58];
    s32 unk60;
    char pad64[0x82];
    s16 unkE6;
    char padE8[0x5C];
    u8 unk144;
    char pad145[0xF];
    u8 unk154;
    u8 unk155;
    char pad156[0x1E];
    void *unk174;
    W2B_D2Info *unk178;
};

typedef struct {
    W2B_D2Actor *unk0;
    W2B_D2Actor *unk4;
    f32 unk8;
    f32 unkC;
    s8 unk10;
    u8 unk11;
    char pad12[2];
    f32 unk14;
    f32 unk18;
    u8 unk1C;
} W2B_D2Link;
#define W2B_BD2 ((W2B_D2Actor *)D_807FBB40)

extern u8 D_807FBD70;
void *heapAlloc(s32);
void heapClearBlock(void *);

void func_8002881C(void) {
    W2B_D2Link *link = W2B_BD2->unk174;
    s16 *sp50 = link->unk0->unk174;
    W2B_D2Info *sp4C = link->unk0->unk178;
    W2B_D2Sub *sub;
    W2B_D2Ent *chk;
    s32 vb[2];
    f32 sp38;
    W2B_D2Ent *p;
    f32 fx;
    f32 fy;
    f32 sp28;
    s32 i;

    if (!(W2B_BD2->unk60 & 0x10)) {
        W2B_BD2->unk144 = 0x24;
        link->unkC = 275.0f;
        link->unk8 = 275.0f;
        link->unk10 = link->unk11;
        W2B_BD2->unk4->unk1C = heapAlloc(0x38);
        heapClearBlock(W2B_BD2->unk4->unk1C);
    }
    sub = link->unk4->unk174;
    if (D_807FBD70 == 4 && sub->unk4 == 0 && link->unk10 == -1) {
        link->unk8 = 275.0f;
        link->unk10 = link->unk11;
        sub->unk5 = 0;
    }
    if (*sp50 > 0 && link->unk0->unk154 == 0) {
        if (sub->unk4 == 0) {
            if (link->unk10 >= 0) {
                link->unk10--;
            }
            if (link->unk10 < 0) {
                link->unk8 -= sp4C->unk20;
            }
        } else {
            link->unk8 += 40.0f;
            link->unk0->unk154 = 2;
        }
    }
    link->unkC = link->unkC + (link->unk8 - link->unkC) * 0.3;
    if (sub->unk4 != 0) {
        if (link->unk14 < 1.0f) {
            link->unk14 += 0.1f;
        } else if (link->unk14 > 1.0f) {
            link->unk14 = 1.0f;
        }
    } else if (link->unk1C != 0) {
        link->unk1C--;
        if (link->unk1C == 0) {
            actorScriptStart(D_807FBB40, 0x1F6);
        }
    }
    chk = W2B_BD2->unk4->unk1C;
    if (chk != 0) {
        vb[1] = 0;
        vb[0] = (s32)chk;
        sp38 = 1.0f - ((link->unkC - 40.0f) / 235.0f);
        fx = func_80612794(link->unk4->unkE6) * (5000.0f * sp38 + 150.0f);
        fy = func_80612790(link->unk4->unkE6) * (5000.0f * sp38 + 150.0f);
        sp28 = link->unk14 * 128.0f + -128.0f;
        i = 4;
        if (fx < 0.0f) {
            fx = 65535.0f + fx;
        }
        if (fy < 0.0f) {
            fy = 65535.0f + fy;
        }
        p = (W2B_D2Ent *)(vb[1] * 8 + vb[0]);
        do {
            p->unk1 = i;
            i++;
            p->unk0 = (s32)sp28;
            p->unk2 = (u32)fx;
            p->unk4 = 0;
            p->unk6 = (u32)fy;
            if (fx > 32767.0f) {
                fx = fx + (65535.0f - fx) * 0.5;
            } else {
                fx = fx * 0.5;
            }
            if (fy > 32767.0f) {
                fy = fy + (65535.0f - fy) * 0.5;
            } else {
                fy = fy * 0.5;
            }
            p++;
        } while (i < 7);
        switch (W2B_BD2->unk155) {
        case 0:
            link->unk18 = link->unk18 + (sp38 - link->unk18) * 0.1;
            break;
        case 1:
        case 2:
            link->unk18 = link->unk18 + (0.0 - link->unk18) * 0.1;
            break;
        }
        p->unk0 = (s32)(link->unk18 * -128.0f);
        p->unk1 = 0xE;
        p->unk2 = 0x61A8;
        p->unk4 = 0;
        p->unk6 = 0;
        p++;
        i = 0xC;
        do {
            p->unk0 = (s32)(link->unk18 * -128.0f);
            p->unk1 = i;
            i++;
            p += 2;
            p[-2].unk2 = 0xD8F0;
            p[-2].unk4 = 0;
            p[-2].unk6 = 0;
        } while (i < 0xD);
        p->unk0 = 0;
    }
    actorUpdateModelMatrix(D_807FBB40, 0);
}
