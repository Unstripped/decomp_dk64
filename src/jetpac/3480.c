#include "common.h"

typedef struct {
    void *frame;
    s32 unk4;
    s32 unk8;
    s32 unkC;
    s32 unk10;
    s32 unk14;
} JetpacSprite;

typedef struct {
    JetpacSprite *sprites[2];
    f32 unk8;
    f32 unkC;
    u8 pad10[0x1C - 0x10];
    s32 unk1C;
    u8 pad20[4];
    s32 unk24;
    s32 unk28;
    s32 unk2C;
    s32 unk30;
    u8 pad34[4];
    s32 unk38;
    u8 pad3C[4];
    s32 unk40;
    u8 pad44[4];
    void (*unk48)(void *, s32);
} JetpacItem;

typedef struct {
    u8 pad0[0xC];
    s32 unkC;
    u8 pad10[0x14 - 0x10];
    JetpacItem items[4];
    u8 pad144[4];
    u8 unk148;
    u8 pad149[0x190 - 0x149];
    void (*unk190)(void *, s32);
} JetpacInner;

f32 jetpacRandFloat(void);
s32 func_80027250(f32, f32, f32, f32, f32, f32, f32, f32);
void func_80025700(void *, s32, s32, void *, s32);
extern s32 D_8002DC68[];
s32 jetpacRandSpawnX(void) {
    return (s32)((jetpacRandFloat() * 200.0f) + 90.0f);
}

s32 func_800274C0(void) {
    return D_8002DC68[(s32)(jetpacRandFloat() * 13.0f) % 13];
}

s32 func_80027510(JetpacItem *arg0, f32 arg1, f32 arg2, f32 arg3, f32 arg4, s32 arg5) {
    f32 fa0;
    f32 fa1;

    fa0 = arg0->unk8;
    fa1 = arg0->unkC;
    if (arg0->unk38 == 1) {
        return 0;
    }

    if (arg5 == 0) {
        fa0 += (f32)arg0->unk24;
        fa1 += (f32)arg0->unk28;
    }

    if (arg0->unk1C >= 2) {
        if (func_80027250(fa0, fa1, arg0->unk8 + (f32)arg0->unk2C, arg0->unkC + (f32)arg0->unk30, arg1, arg2, arg3, arg4)) {
            return 1;
        }
    }

    return 0;
}

extern JetpacSprite D_8002D1A0[];
extern JetpacSprite D_8002D230[];
extern JetpacItem D_8002DC9C;
void func_80028B54(s32 *arg0);

#if 0
// Non-matching draft: loop register allocation differences
void func_800275F4(JetpacInner *arg0) {
    s32 pad;
    JetpacItem sp38 = D_8002DC9C;
    JetpacSprite *a2 = D_8002D1A0;
    JetpacItem *a3 = arg0->items;
    JetpacInner *t0 = arg0;

    do {
        JetpacSprite *a0 = a2;
        s32 v0;

        *a3 = sp38;
        for (v0 = 0; v0 < 2; v0++) {
            t0->items[0].sprites[v0] = a0++;
        }
        a2 += 2;
        a3++;
        t0 = (JetpacInner *)((u8 *)t0 + sizeof(JetpacItem));
    } while (a2 != D_8002D230);

    func_80028B54(arg0);
    arg0->unkC = 0;
    arg0->items[2].unk8 = 168.0f;
    arg0->items[2].unkC = 168.0f;
    arg0->items[0].unk8 = 48.0f;
    arg0->items[0].unkC = 56.0f;
    arg0->items[1].unk8 = 128.0f;
    arg0->items[1].unkC = 80.0f;
}
#endif
#pragma GLOBAL_ASM("asm/jetpac/nonmatchings/3480/func_800275F4.s")

#pragma GLOBAL_ASM("asm/jetpac/nonmatchings/3480/func_80027728.s")

#pragma GLOBAL_ASM("asm/jetpac/nonmatchings/3480/func_80027BE8.s")

s32 func_8073110C(s32, s32);
extern u8 D_8002F3C8;
extern JetpacSprite D_8002D968[];
extern JetpacItem D_8002DCEC;

void func_80027D64(void *arg0) {
    JetpacItem sp24 = D_8002DCEC;
    JetpacItem *item;
    s32 count = 5;

    if (D_8002F3C8 != 0 && *(s32 *)((u8 *)arg0 + 4) >= 5000 && func_8073110C(0x17B, 0) == 0 && func_8073110C(0x62, 2) == 0) {
        count = 6;
        sp24.unk40 = count;
    } else {
        sp24.unk40 = (s32)(jetpacRandFloat() * count) + 1;
    }

    item = (JetpacItem *)((u8 *)arg0 + 0x148);
    sp24.sprites[0] = &D_8002D968[sp24.unk40];
    *item = sp24;
    item->unk8 = (f32)func_800274C0();
    *(s32 *)((u8 *)arg0 + 0x144) = jetpacRandSpawnX();
}

#pragma GLOBAL_ASM("asm/jetpac/nonmatchings/3480/func_80027EC0.s")


typedef struct {
    u8 pad0[0x10];
    s32 unk10;
    u8 pad14[0xF8 - 0x14];
    JetpacItem item;
} UnkStruct_80028340;

extern JetpacItem D_8002DD38;

void func_80028340(UnkStruct_80028340 *arg0) {
    JetpacItem sp1C = D_8002DD38;
    sp1C.unk8 = (f32)func_800274C0();
    arg0->item = sp1C;
    arg0->unk10 = 3;
}

typedef struct {
    u8 pad0[0x344];
    s32 unk344;
} JetpacGlobal;

extern JetpacGlobal D_8002EC30;

s32 func_800283EC(f32 arg0, f32 arg1, f32 arg2, f32 arg3) {
    JetpacInner *inner = (JetpacInner *)((u8 *)&D_8002EC30 + D_8002EC30.unk344 * 0x194);
    s32 unk28 = *(s32 *)((u8 *)inner + 0x28);
    s32 i;
    JetpacItem *item;

    inner = (JetpacInner *)((u8 *)inner + 0x1C);
    if (unk28 < 2) {
        item = inner->items;
        i = 0;
        if (2 - unk28 > 0) {
            do {
                if (func_80027510(item, arg0, arg1, arg2, arg3, 1)) {
                    return 1;
                }
                i++;
                item++;
            } while (i < 2 - inner->unkC);
        }
    }

    if (func_80027510((JetpacItem *)((u8 *)inner + 0xF8), arg0, arg1, arg2, arg3, 0)) {
        return 1;
    }
    if (func_80027510((JetpacItem *)((u8 *)inner + 0x148), arg0, arg1, arg2, arg3, 0)) {
        return 1;
    }

    return 0;
}
void jetpacItemsUpdate(void) {
    u8 *player = (u8 *)&D_8002EC30 + D_8002EC30.unk344 * 0x194;
    JetpacItem *item = (JetpacItem *)(player + 0x30);
    s32 i = 0;
    s32 count = 4;

    do {
        if (item->unk1C >= 2 && item->unk48 != NULL) {
            item->unk48(item, i);
        }
        i++;
        item++;
    } while (i != count);
}
void func_800285DC(void) {
    JetpacInner *inner = (JetpacInner *)((u8 *)&D_8002EC30 + D_8002EC30.unk344 * 0x194 + 0x1C);
    inner->unk190(&inner->unk148, 5);
}

void func_80028634(void) {
    JetpacInner *inner = (JetpacInner *)((u8 *)&D_8002EC30 + D_8002EC30.unk344 * 0x194 + 0x1C);
    JetpacItem *item = inner->items;
    s32 i;

    inner->unkC = 8;
    for (i = 0; i < 3; i++, item++) {
        item->unk8 = 168.0f;
        item->unkC = (f32)(i * 16) + 136.0f;
    }
}

#pragma GLOBAL_ASM("asm/jetpac/nonmatchings/3480/func_800286D0.s")

void func_80028950(void) {
    JetpacInner *inner = (JetpacInner *)((u8 *)&D_8002EC30 + D_8002EC30.unk344 * 0x194 + 0x1C);
    JetpacItem *item = inner->items;
    s32 i;

    inner->unkC = 2;
    for (i = 0; i < 3; i++, item++) {
        item->unk8 = 168.0f;
        item->unkC = (f32)(i * 16) + -8.0f;
    }
}

extern s32 D_8002DD88;
extern JetpacSprite D_8002DC38[];
#if 0
// Non-matching draft: stack frame 0x58 instead of 0x50; sp44 offset difference
void func_800289EC(void) {
    s32 sp44 = D_8002DD88;
    u8 *player = (u8 *)&D_8002EC30 + D_8002EC30.unk344 * 0x194;
    f32 unkC = *(f32 *)(player + 0x3C);
    JetpacItem *item = (JetpacItem *)(player + 0x30);
    s32 i;

    if (unkC < 116.0f) {
        s32 v = (s32)unkC / 3;
        s32 mod = v % 2;
        s32 idx = (mod > 0) ? mod : -mod;

        func_80025700(&D_8002DC38[idx], (s32)item->unk8, (s32)((unkC + 48.0f) + 4.0f), &sp44, 0);
    }

    i = 0;
    do {
        item->unk48(item, i);
        i++;
        item++;
    } while (i != 3);
}
#endif
#pragma GLOBAL_ASM("asm/jetpac/nonmatchings/3480/func_800289EC.s")

#if 0
// Non-matching draft: IDO unrolls 6-iteration loop but emits D_8002D1A0+0x18 instead of D_8002D1B8
extern void *D_8002D190[];
void func_80028B54(s32 *arg0) {
    s32 i;
    void *val = D_8002D190[(*arg0 / 4) % 4];

    for (i = 0; i < 6; i++) {
        D_8002D1A0[i].frame = val;
    }
}
#endif
#pragma GLOBAL_ASM("asm/jetpac/nonmatchings/3480/func_80028B54.s")

typedef struct {
    f32 unk0;
    f32 unk4;
    f32 unk8;
    f32 unkC;
    u8 color[4];
    u8 pad14[8];
    s32 unk1C;
    s32 unk20;
    s32 unk24;
    s32 unk28;
    u8 pad2C[4];
    s32 unk30;
} JetpacLedge;

void func_80028BD0(JetpacLedge *arg0, s32 arg1, s32 arg2, s32 arg3, u8 arg4, u8 arg5, u8 arg6) {
    arg0->unk30 = arg3;
    arg0->unk8 = 0.0f;
    arg0->unkC = 0.0f;
    arg0->unk0 = (f32)arg1;
    arg0->unk4 = (f32)arg2;
    arg0->color[0] = arg4;
    arg0->color[1] = arg5;
    arg0->color[2] = arg6;
    arg0->color[3] = 0xFF;
    arg0->unk20 = arg2;
    arg0->unk1C = arg1;
    arg0->unk28 = (arg0->unk24 = (arg3 * 8) + arg1 + 16, arg2 + 12);
}
extern JetpacLedge D_8002EF80[];
extern JetpacLedge D_8002EFB4[];
extern JetpacLedge D_8002EFE8[];
extern JetpacLedge D_8002F01C[];

void jetpacInitLedges(void) {
    func_80028BD0(D_8002EF80, 0xC0, 0x30, 4, 0, 0xBE, 0);
    func_80028BD0(D_8002EFB4, 0x20, 0x48, 4, 0, 0xBE, 0);
    func_80028BD0(D_8002EFE8, 0x78, 0x60, 2, 0, 0xBE, 0);
    func_80028BD0(D_8002F01C, 0, 0xB8, 0x1E, 0xBE, 0xBE, 0);
}
s32 jetpacCheckLedgeCollision(f32 arg0, f32 arg1, f32 arg2, f32 arg3, s32 arg4) {
    JetpacLedge *ledge = D_8002EF80;
    s32 i;

    for (i = 0; i < 4; i++, ledge++) {
        f32 fv0 = ledge->unk28;
        if (arg4 == 0) {
            fv0 -= 4.0f;
        }
        if (func_80027250(arg0, arg1, arg2, arg3, ledge->unk1C, ledge->unk20, ledge->unk24, fv0)) {
            return i;
        }
    }
    return -1;
}

#if 0
// Non-matching draft: IDO CSEs 0x36C load where target reloads into $t9 and emits beql
s32 func_80028E04(s32 arg0, s32 arg1, s32 arg2) {
    u8 *base = (u8 *)&D_8002EC30 + arg0 * 0x34;

    if (arg1 < *(s32 *)(base + 0x36C)) {
        if (arg2 < *(s32 *)(base + 0x36C)) {
            return -2;
        }
        return -1;
    }
    if (*(s32 *)(base + 0x374) < arg2) {
        if (*(s32 *)(base + 0x374) < arg1) {
            return 2;
        }
        return 1;
    }
    return 0;
}
#endif
#pragma GLOBAL_ASM("asm/jetpac/nonmatchings/3480/func_80028E04.s")

void func_80025700(void *, s32, s32, void *, s32);
extern void *D_8002DE68;
extern void *D_8002DE80;
extern void *D_8002DE98;
extern u8 D_8002EF90[];
extern u8 D_8002F060[];

#if 0
// Non-matching draft: register allocation swap between $s3 and $s8 ($fp) in prologue
void func_80028E88(void) {
    u8 *color = D_8002EF90;
    void *de80 = &D_8002DE80;
    u8 *base = (u8 *)&D_8002EC30;
    JetpacLedge *ledge = D_8002EF80;
    u8 *color_fp;

    color_fp = color;
    do {
        s32 x = (s32)*(f32 *)(base + 0x350);
        s32 y = (s32)*(f32 *)(base + 0x354);
        JetpacLedge *cur = ledge;
        s32 j = 0;

        func_80025700(&D_8002DE68, x, y, color_fp, 0);
        x += 8;
        if (cur->unk30 > 0) {
            do {
                func_80025700(de80, x, y, color, 0);
                j++;
                x += 8;
            } while (j < cur->unk30);
        }
        func_80025700(&D_8002DE98, x, y, color, 0);
        color += 0x34;
        base += 0x34;
        ledge++;
        color_fp += 0x34;
    } while (color != D_8002F060);
}
#endif
#pragma GLOBAL_ASM("asm/jetpac/nonmatchings/3480/func_80028E88.s")
