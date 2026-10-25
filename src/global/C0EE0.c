#include "common.h"
#include "actor.h"

extern Actor *D_807FBB40;
extern Actor *D_807FBB4C;

#pragma GLOBAL_ASM("asm/global/nonmatchings/C0EE0/func_806BC1E0.s")

extern u8 D_1000118[];
extern u8 D_2000180[];
#define R1C0C1_WRITE_GFX(pkt, _w0, _w1) { Gfx *_g = (Gfx *)(pkt); _g->words.w0 = (_w0); _g->words.w1 = (u32)(_w1); }

Gfx *func_806FC530(Gfx *, s32, s32, s32, char *, s32);

Gfx *func_806BCF98(Gfx *dl, Actor *actor) {
    R1C0C1_WRITE_GFX(dl++, 0xDE000000, D_1000118);
    R1C0C1_WRITE_GFX(dl++, 0xE200001C, 0x504240);
    gDPSetPrimColor(dl++, 0, 0, 255, 255, 255, 255);
    R1C0C1_WRITE_GFX(dl++, 0xFC119623, 0xFF2FFFFF);
    R1C0C1_WRITE_GFX(dl++, 0xDA380003, D_2000180);
    dl = func_806FC530(dl, 1, 0x208, 0xC8, "q YES", 1);
    return func_806FC530(dl, 1, 0x208, 0x12C, "b NO", 1);
}

extern s8 D_807FC8C0[];

void func_806BD094(s16 idx, s8 val) {
    if (idx >= 0 && idx < 0x10) {
        D_807FC8C0[idx] = val;
    }
}

void func_8073129C(s32, s32, s32);
void func_8063DA40(s16, s32);

void func_806BD0CC(void) {
    s32 i;

    func_8073129C(0x30, 0, 2);
    for (i = 0; i < 0x10; i++) {
        D_807FC8C0[i] = -1;
        func_8063DA40(i, 0);
    }
    D_807FC8C0[5] = 0;
    D_807FC8C0[6] = 1;
    D_807FC8C0[9] = 1;
    D_807FC8C0[0xA] = 0;
}
