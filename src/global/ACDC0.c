#include "common.h"
#include "actor.h"

#pragma GLOBAL_ASM("asm/global/nonmatchings/ACDC0/func_806A80C0.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/ACDC0/func_806A8158.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/ACDC0/func_806A9124.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/ACDC0/func_806A921C.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/ACDC0/D_8075AA80.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/ACDC0/D_8075AA88.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/ACDC0/D_8075AA90.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/ACDC0/D_8075AA94.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/ACDC0/D_8075AA9C.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/ACDC0/D_8075AAA4.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/ACDC0/D_8075AAAC.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/ACDC0/D_8075AAB4.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/ACDC0/D_8075AABC.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/ACDC0/D_8075AAC4.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/ACDC0/D_8075AACC.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/ACDC0/D_8075AAD4.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/ACDC0/D_8075AADC.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/ACDC0/D_8075AAE4.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/ACDC0/func_806A92B4.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/ACDC0/func_806AA09C.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/ACDC0/func_806AA304.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/ACDC0/func_806AB4EC.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/ACDC0/func_806AB808.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/ACDC0/func_806ABA6C.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/ACDC0/func_806ABB98.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/ACDC0/func_806ABC94.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/ACDC0/func_806ABE3C.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/ACDC0/func_806AC048.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/ACDC0/func_806AC07C.s")

Gfx *func_806A921C(Gfx *);
Gfx *func_806ABB98(Gfx *, s32, s32, f32, char *);
Gfx *func_80703374(Gfx *, s32, s32, s32, s32);
Gfx *func_806FC530(Gfx *, s32, s32, s32, char *, s32);
s32 _sprintf(char *, const char *, ...);
extern char **D_807FC7E0;

Gfx *func_806ACA88(Gfx *dl, Actor *actor) {
    char buf[0x28];
    s32 remaining;
    s32 val;

    remaining = 0xFF - actor->unk128;
    if (remaining >= 9) {
        val = 8;
    } else {
        val = remaining;
    }
    actor->unk128 += val;
    if (actor->unk128 >= 0x80) {
        val = 0x7F;
    } else {
        val = actor->unk128;
    }
    dl = func_806A921C(func_80703374(dl, 0, 0, 0, val));
    gDPSetCombineLERP(dl++, 0, 0, 0, TEXEL0, TEXEL0, 0, PRIMITIVE, 0, 0, 0, 0, TEXEL0, TEXEL0, 0, PRIMITIVE, 0);
    dl->words.w0 = 0xFA000000;
    dl->words.w1 = (actor->unk128 & 0xFF) | 0xFFFFFF00;
    dl++;
    dl = func_806FC530(dl, 1, 0x168, 0x104, D_807FC7E0[0], 1);
    _sprintf(buf, "q %s", D_807FC7E0[1]);
    dl = func_806FC530(dl, 1, 0x208, 0x190, buf, 1);
    _sprintf(buf, "b %s", D_807FC7E0[2]);
    return func_806FC530(dl, 1, 0x208, 0x21C, buf, 1);
}

extern Actor *D_807FBB44;
extern s32 D_807FBB60;
void actorSpawn(s32, s32);

void func_806ACC00(u8 arg0) {
    actorSpawn(0x156, 0);
    D_807FBB44->unk15F = arg0;
    D_807FBB44->unk64 |= 2;
    D_807FBB60 |= 0x40001;
}

extern Actor *D_807FBB40;
void actorDespawn(Actor *);
void heapFreeDeferred(void *);

void func_806ACC64(void) {
    s16 i;

    D_807FBB60 |= 0x40;
    for (i = 0; i < 3; i++) {
        heapFreeDeferred(D_807FC7E0[i]);
    }
    heapFreeDeferred(D_807FC7E0);
    actorDespawn(D_807FBB40);
}

extern u16 D_807ECD58;
extern s32 D_8076A0A8;
void *func_80610FE8(s32);
char *func_8070E750(s32, s32, s32);
void func_8061CC40(s32, s32, s32);
void func_80724994(s32, s32, s32, s32, s32);
void func_805FF378(s32, s32);
void func_805FF544(void);
void func_805FF898(void);
void func_806ACC64(void);
void renderCallbacksRegister(void *, void *, s32);

void func_806ACCE8(void) {
    s32 i;

    if (!(D_807FBB40->unk60 & 0x10)) {
        D_807FBB40->unk168 = 0x1E;
        D_807FBB40->unk128 = 0;
        D_807FBB40->unk60 &= ~0x8000;
        D_807FC7E0 = func_80610FE8(0xC);
        for (i = 0; i < 3; i++) {
            D_807FC7E0[i] = func_8070E750(0x24, i + 0xF, 0);
        }
    }
    if (D_807FBB40->unk168 != 0) {
        D_807FBB40->unk168--;
    } else if (D_807FBB40->unk154 == 0) {
        if (D_807ECD58 & 0x8000) {
            switch (D_807FBB40->unk15F) {
                case 2:
                    func_8061CC40(0, 0x20, 1);
                    func_806ACC64();
                    break;
                case 3:
                case 4:
                    func_80724994(3, 7, 0x30, 0, 0);
                    func_806ACC64();
                    break;
                default:
                    func_805FF378(D_8076A0A8, 0);
                    break;
            }
            D_807FBB40->unk154 = 1;
        } else if (D_807ECD58 & 0x4000) {
            switch (D_807FBB40->unk15F) {
                case 3:
                case 4:
                    func_80724994(3, 7, 0x3C, 0, 0);
                case 2:
                    func_806ACC64();
                    break;
                case 1:
                    func_805FF544();
                    break;
                default:
                    func_805FF898();
                    break;
            }
            D_807FBB40->unk154 = 1;
        }
    }
    renderCallbacksRegister(func_806ACA88, D_807FBB40, 5);
}

extern u8 D_807505F8[];
extern u8 D_807505F9[];
Gfx *func_806ACF10(Gfx *dl, Actor *actor) {
    u8 sel;
    u8 c;

    dl = func_806A921C(dl);
    sel = actor->unk155[0] == 0;
    c = D_807505F8[sel];
    gDPSetPrimColor(dl++, 0, 0, c, c, c, 255);
    dl = func_806ABB98(dl, 0x280, 0x1B8, 0.7f, D_807FC7E0[0]);
    c = D_807505F9[-sel];
    gDPSetPrimColor(dl++, 0, 0, c, c, c, 255);
    return func_806ABB98(dl, 0x280, 0x208, 0.7f, D_807FC7E0[3]);
}

typedef struct {
    u8 pad0[3];
    s8 unk3;
} M2_ACDC0_Axis;

typedef struct {
    u8 pad0[0x294];
    M2_ACDC0_Axis *unk294;
    u16 *unk298;
    u8 pad29C[0x2F0 - 0x29C];
} M2_ACDC0_Player;

extern s8 D_807FC80E;
extern s8 D_807FC8B9;
extern M2_ACDC0_Player *D_807FC924;
extern s8 D_8076A105;
void func_80609140(s32, s32, f32, f32, s32, s32);
void func_806291B4(s32);
void func_80714638(void);
Gfx *func_806AC048(Gfx *, Actor *);

void func_806ACFFC(void) {
    s32 i;
    s32 off;
    u16 btn;

    if (!(D_807FBB40->unk60 & 0x10)) {
        D_807FC7E0 = func_80610FE8(0x10);
        i = 0;
        do {
            D_807FC7E0[i] = func_8070E750(0x24, i, 0);
            i++;
        } while (i != 4);
        D_807FBB60 &= ~0x10030;
        func_806291B4(7);
        D_807FC80E = 0;
        D_807FBB40->unk155[0] = 0;
    }
    i = D_807FC8B9;
    off = i * 0x2F0;
    if (((M2_ACDC0_Player *)((u8 *)D_807FC924 + off))->unk294->unk3 >= 0x33 || ((M2_ACDC0_Player *)((u8 *)D_807FC924 + off))->unk294->unk3 < -0x32) {
        if (!(D_807FC80E & 1)) {
            D_807FBB40->unk155[0] = 1 - D_807FBB40->unk155[0];
            D_807FC80E |= 1;
            func_80609140(0x2A0, 0x7FFF, 63.0f, 1.0f, 0, 0);
        }
    } else {
        D_807FC80E &= 0xFFFE;
    }
    btn = *((M2_ACDC0_Player *)((u8 *)D_807FC924 + off))->unk298;
    if (btn & 0x8000) {
        if (D_807FBB40->unk155[0] == 0) {
            D_807FBB60 |= 0x10070;
            for (i = 0; i < 4; i++) {
                heapFreeDeferred(D_807FC7E0[i]);
            }
            heapFreeDeferred(D_807FC7E0);
        } else if (D_807FBB40->unk155[0] == 1) {
            D_8076A105 = -1;
            func_80714638();
            D_807FBB40->unk155[0] = 2;
        }
    }
    renderCallbacksRegister(func_806AC048, D_807FBB40, 1);
    renderCallbacksRegister(func_806ACF10, D_807FBB40, 5);
}
