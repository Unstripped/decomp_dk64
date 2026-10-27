#include "common.h"
#include "actor.h"

extern s32 D_8076A0A8;

typedef struct {
    void (*unk0)();
    void (*unk4)();
    void (*unk8)();
    u8 unkC;
} R41090aEntry;

extern R41090aEntry D_80747D80[8];
extern f32 D_807F6170;
extern f32 D_807F6174;
extern f32 D_807F6178;
extern void *D_807F617C;

void *func_8066B0F8(s32, s32, s32, s32);
u8 fogGetEnabled(void);

#pragma GLOBAL_ASM("asm/global/nonmatchings/41090/func_8063C390.s")

void func_8063C3C0(s16 arg0) {
    if (D_80747D80[arg0].unkC == 0) {
        D_80747D80[arg0].unk0();
        D_80747D80[arg0].unkC = 1;
    }
}

#pragma GLOBAL_ASM("asm/global/nonmatchings/41090/func_8063C418.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/41090/func_8063C450.s")

void func_8063C4A8(void) {
    D_807F6170 = 255.0f;
    D_807F6174 = 255.0f;
}

Gfx *func_8063C4C4(Gfx *g) {
    gDPPipeSync(g++);
    gSPSetOtherMode(g++, G_SETOTHERMODE_H, 20, 2, 0x100000);
    gSPClearGeometryMode(g++, -1);
    gSPSetGeometryMode(g++, 0x200404);
    gSPSetOtherMode(g++, G_SETOTHERMODE_H, 16, 1, 0);
    gSPTexture(g++, 0xFFFF, 0xFFFF, 3, 1, 1);
    gSPSetOtherMode(g++, G_SETOTHERMODE_L, 3, 29, 0x0C192008);
    gDPSetCombine(g++, 0x1114C0, 0xFFFFFEFC);
    gDPSetEnvColor(g++, 0, 0x40, 0x7F, 0xFF);
    gDPSetPrimColor(g++, 0, 0, 0x50, 0x50, 0xB4, 0x46);
    gDPSetTileSize(g++, 1, (s32)D_807F6170, 0, 0x7C, 0x7C);
    gDPSetTile(g++, 4, 1, 0, 0, 7, 0, 1, 5, 0, 1, 5, 0);
    gDPLoadSync(g++);
    gDPLoadBlock(g++, 7, 0, 0, 0x3FF, 0x200);
    gDPTileSync(g++);
    gDPSetTile(g++, 4, 1, 4, 0, 1, 0, 0, 5, 0, 0, 5, 15);
    gDPSetTileSize(g++, 2, (s32)D_807F6174, 0, 0x7C, 0x7C);
    gDPSetTile(g++, 3, 1, 0, 0x100, 7, 0, 1, 5, 0, 1, 5, 0);
    gDPLoadSync(g++);
    gDPLoadBlock(g++, 7, 0, 0, 0x3FF, 0x200);
    gDPTileSync(g++);
    gDPSetTile(g++, 3, 1, 4, 0x100, 2, 0, 0, 5, 0, 0, 5, 15);
    return g;
}

#pragma GLOBAL_ASM("asm/global/nonmatchings/41090/func_8063C6D8.s")

void func_8063C784(void) {
    D_807F6178 = 255.0f;
    D_807F617C = func_8066B0F8(0x19, 0x565, 1, 0);
}

Gfx *func_8063C7C4(Gfx *g) {
    s32 i;
    s32 w;
    s32 h;
    s32 tmem;
    s32 j;
    s32 line;

    tmem = 0;
    w = 0x20;
    h = 0x20;
    j = 5;
    gDPPipeSync(g++);
    gSPSetOtherMode(g++, G_SETOTHERMODE_H, 20, 2, 0x100000);
    gSPClearGeometryMode(g++, -1);
    gSPSetGeometryMode(g++, 0x200405);
    gDPSetTextureImage(g++, G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, D_807F617C);
    gDPSetTile(g++, G_IM_FMT_RGBA, G_IM_SIZ_16b, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0);
    gDPLoadSync(g++);
    gDPLoadBlock(g++, 7, 0, 0, 0x7FF, 0);
    tmem = 0;
    for (i = 0; i < 4; i++) {
        line = (w + 3) / 4;
        gDPSetTile(g++, G_IM_FMT_RGBA, G_IM_SIZ_16b, line, tmem, i, 0, 0, j, i, 0, j, i);
        gDPSetTileSize(g++, i, 2, (s32)D_807F6178, ((w - 1) << 2) + 2, ((h - 1) << 2) + 2);
        tmem += line * h;
        w >>= 1; h >>= 1;
        j--;
    }
    gSPSetOtherMode(g++, G_SETOTHERMODE_H, 16, 1, 0x10000);
    if (fogGetEnabled()) {
        gSPSetGeometryMode(g++, 0x10000);
        gSPSetOtherMode(g++, G_SETOTHERMODE_L, 3, 29, 0xC8112230);
    } else {
        gSPSetOtherMode(g++, G_SETOTHERMODE_L, 3, 29, 0x0C192230);
    }
    gDPSetCombine(g++, 0x26A004, 0x1F1093FF);
    gSPTexture(g++, 0xFFFF, 0xFFFF, 3, 0, 1);
    return g;
}

void func_8063CA7C(void) {
    D_807F6178 -= 1.0;
    if (D_807F6178 < 0.0) {
        D_807F6178 = 255.0f;
    }
}

#pragma GLOBAL_ASM("asm/global/nonmatchings/41090/func_8063CADC.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/41090/func_8063CB40.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/41090/func_8063CE64.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/41090/func_8063CF0C.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/41090/func_8063CF3C.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/41090/func_8063D1D8.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/41090/func_8063D288.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/41090/func_8063D2E4.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/41090/func_8063D468.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/41090/func_8063D494.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/41090/func_8063D4A4.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/41090/func_8063D5AC.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/41090/func_8063D608.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/41090/func_8063D638.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/41090/func_8063D854.s")
