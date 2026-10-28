#include "common.h"
#include "actor.h"

extern Actor *D_807FBB40;
extern Actor *D_807FBB44;
extern Actor *D_807FBB48;
extern Actor *D_807FBB4C;
extern void *D_807FC924;
extern u8 D_807FC928;
extern u8 D_807FC929;
extern u8 D_807FC950[][0x5E];
extern s32 D_8076A0A8;
extern u8 D_8076A0AB;
extern u8 D_8076A0B1;
extern s16 D_80744490;
extern s16 D_80744494;
extern u8 D_807444F8;
extern u8 D_807444FC;

extern u8 D_807444EC;
extern u8 D_807444F4;
extern s32 D_8076D1F8;
extern s32 D_807FBB64;
extern s8 D_807FD9BC;
extern u8 D_807FD9BD;
extern f32 D_807FD9C4;
extern s32 D_807FD9C8;
void timerQueueCancel(void *);
void n_alSndpPlay(s32, s16, s32, s32, f32, s32, s32 *);

void func_807094D0(arg0)
u8 arg0;
{
    D_807444F4 = D_807444EC;
    switch (arg0) {
    case 2:
        D_807FD9C4 = 1.0f;
        D_807FD9BC = 0;
        D_807444F8 = 1;
        D_807444EC = 6;
        break;
    case 3:
        D_807FD9C4 = 0.5f;
        D_807FD9BC = 0;
        D_807444F8 = 2;
        D_807444EC = 6;
        D_807FD9BD = 2;
        if ((D_807444F4 == 1) && (D_807FBB64 & 1)) {
            timerQueueCancel(0);
        }
        break;
    }
    n_alSndpPlay(D_8076D1F8, 0x1BC, 0x7FFF, 0x3F, 1.0f, 0, &D_807FD9C8);
}

typedef struct EaGridCell {
    s32 offset;
    s32 width;
    s32 height;
} EaGridCell;

extern EaGridCell *D_807FD9B4;

void func_807095E4(s32 arg0, s32 arg1) {
    s32 cols;
    s32 rows;
    s32 remW;
    s32 remH;
    s32 y;
    s32 idx;
    s32 row;
    s32 col;
    s32 x;

    cols = D_80744490 / arg0;
    rows = D_80744494 / arg1;
    remW = D_80744490 - arg0 * cols;
    remH = D_80744494 - arg1 * rows;
    if (remW > 0) {
        cols++;
    }
    if (remH > 0) {
        rows++;
    }
    idx = 0;
    if (remH != 0) {
        y = D_80744494 - remH;
    } else {
        y = D_80744494 - arg1;
    }
    for (row = 0; row < rows; row++) {
        x = 0;
        for (col = 0; col < cols; col++) {
            D_807FD9B4[idx].offset = D_80744490 * y + x;
            if (remW != 0 && col == cols - 1) {
                D_807FD9B4[idx].width = remW;
            } else {
                D_807FD9B4[idx].width = arg0;
            }
            if (remH != 0 && row == 0) {
                D_807FD9B4[idx].height = remH;
            } else {
                D_807FD9B4[idx].height = arg1;
            }
            x += arg0;
            idx++;
        }
        y -= arg1;
    }
}

#ifdef NON_MATCHING
typedef struct EaEntry {
    u32 unk0;
    u8 pad[0x18];
} EaEntry;

typedef struct EaBlockB {
    u32 *unk0;
    s32 *unk4;
    u8 *unk8;
} EaBlockB;

typedef struct EaBlockA {
    s32 unk0;
    s32 unk4;
    u8 *unk8;
    u8 *unkC;
    void *unk10;
    void *unk14;
    u32 *unk18;
    s32 *unk1C;
    s32 *unk20;
} EaBlockA;

void *func_80610FE8(s32);

s32 func_80709890(EaBlockA *arg0, EaBlockA **arg1, EaBlockB **arg2, s32 **arg3) {
    s32 count;
    s32 k;
    s32 sum;
    EaBlockB *b;
    u32 *p;
    EaEntry *q;

    if (arg0 == NULL) {
        return 0;
    }
    if (arg1 == NULL) {
        return 0;
    }
    D_807FD9B4 = func_80610FE8(0x708);
    arg0->unk10 = func_80610FE8(arg0->unk0 * 0x10);
    if (D_807FD9B4 && D_807FD9B4) {}
    arg0->unk14 = func_80610FE8(arg0->unk0 * 0x10);
    arg0->unk8 = (u8 *)arg0 + 0x2C;
    arg0->unkC = arg0->unk8 + arg0->unk0 * 0xC;
    arg0->unk18 = (u32 *)(arg0->unkC + arg0->unk4 * 0x1C);
    count = 1;
    p = arg0->unk18;
    while (*p++ != 0) {
        count++;
    }
    arg0->unk20 = (s32 *)arg0->unk18 + count;
    arg0->unk1C = arg0->unk20 + count;
    *arg1 = arg0;
    if (arg2 != NULL) {
        b = (EaBlockB *)(arg0->unk1C + count);
        b->unk8 = (u8 *)(b + 1);
        q = (EaEntry *)b->unk8;
        if (D_807FD9B4 && D_807FD9B4) {}
        count = 1;
        while ((q++)->unk0 != 0) {
            count++;
        }
        b->unk0 = (u32 *)(b->unk8 + count * 0x1C);
        k = 1;
        p = b->unk0;
        while (*p++ != -1) {
            if (D_807FD9B4 && D_807FD9B4) {}
            k++;
        }
        b->unk4 = (s32 *)((u8 *)b->unk0 + k * 4);
        if (q && q) {}
        count = 0;
        sum = 0;
        if (b->unk0[0] != -1) {
            do {
                b->unk4[count] = (s32)b->unk4 + k * 4 + sum * 2;
                sum += b->unk0[count];
                count++;
            } while (b->unk0[count] != -1);
        }
        *arg2 = b;
    }
    if (arg3 != NULL) {
        if (arg2 == NULL) {
            *arg3 = arg0->unk1C + count;
        } else {
            *arg3 = b->unk4 + count;
        }
    }
    return 1;
}
#else

#pragma GLOBAL_ASM("asm/global/nonmatchings/10E1D0/func_80709890.s")
#endif

#ifdef NON_MATCHING
typedef struct EaSortView { s32 unk0, unk4, unk8; u8 *unkC; s32 unk10, unk14; s32 *unk18, *unk1C, *unk20; } EaSortView;
typedef struct EaSortEntry { s32 unk0, unk4, unk8; u8 padC[0x10]; } EaSortEntry;
s32 func_80709ACC(EaSortView *arg0) {
    EaSortEntry *e; s32 min, max, i, out = 0, off = 0;
    while (*(s32 *)((u8 *)arg0->unk18 + out)) {
        e = (EaSortEntry *)(arg0->unkC + off);
        min = max = e->unk0;
        for (i = 0; i < *(s32 *)((u8 *)arg0->unk18 + out); i++, off += 0x1C, e++) {
            if (e->unk0 > max) max = e->unk0; else if (e->unk0 < min) min = e->unk0;
            if (e->unk4 > max) max = e->unk4; else if (e->unk4 < min) min = e->unk4;
            if (e->unk8 > max) max = e->unk8; else if (e->unk8 < min) min = e->unk8;
        }
        *(s32 *)((u8 *)arg0->unk20 + out) = min;
        *(s32 *)((u8 *)arg0->unk1C + out) = max;
        out += 4;
    }
    return 1;
}
#else

#pragma GLOBAL_ASM("asm/global/nonmatchings/10E1D0/func_80709ACC.s")
#endif

#pragma GLOBAL_ASM("asm/global/nonmatchings/10E1D0/func_80709BC4.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/10E1D0/func_8070A220.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/10E1D0/func_8070A848.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/10E1D0/func_8070A934.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/10E1D0/func_8070AC74.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/10E1D0/func_8070AF24.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/10E1D0/func_8070B05C.s")

extern u8 D_80755070;

void func_8070B308(u8 arg0) {
    D_80755070 = arg0;
}

u8 func_8070B318(void) {
    return D_80755070;
}

#pragma GLOBAL_ASM("asm/global/nonmatchings/10E1D0/func_8070B324.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/10E1D0/func_8070B7EC.s")
