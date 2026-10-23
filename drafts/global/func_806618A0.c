// func_806618A0 (src/global/63EC0.c): Variant of func_806616A0 with extra 0xFA000000 command, exact packet structure
#include "common.h"

typedef struct R1D63EC0_Sub2 {
    u8 pad0[0x14];
    s32 unk14;
    s32 unk18;
    u8 pad1C[0x2C - 0x1C];
    s32 unk2C;
    s32 unk30;
    f32 unk34;
    f32 unk38;
    f32 unk3C;
    f32 unk40;
    u8 pad44[0x64 - 0x44];
    u8 val;
} R1D63EC0_Sub2;

typedef struct R1D63EC0_Obj2 {
    R1D63EC0_Sub2 *sub;
    u8 pad4[0x30 - 4];
    s32 unk30;
    s32 unk34;
    s32 unk38;
    s32 unk3C;
} R1D63EC0_Obj2;

typedef struct R1D63EC0_Struct1 {
    void *unk0;
    u8 pad4[0x18 - 4];
} R1D63EC0_Struct1;
extern R1D63EC0_Struct1 D_80748A9C[];

#define R1D63EC0_WRITE_GFX(pkt, _w0, _w1) { Gfx *_g = (Gfx *)(pkt); _g->words.w0 = (_w0); _g->words.w1 = (_w1); }

Gfx *func_806618A0(Gfx *dlist, R1D63EC0_Obj2 *arg1, u8 arg2) {
    s32 temp;
    R1D63EC0_WRITE_GFX(dlist++, 0xE7000000, 0);
    R1D63EC0_WRITE_GFX(dlist++, 0xFD180000, (u32)D_80748A9C[arg2].unk0);
    R1D63EC0_WRITE_GFX(dlist++, 0xF5180000, 0x0701785E);
    R1D63EC0_WRITE_GFX(dlist++, 0xE6000000, 0);
    R1D63EC0_WRITE_GFX(dlist++, 0xF3000000, 0x073FF080);
    R1D63EC0_WRITE_GFX(dlist++, 0xE7000000, 0);
    R1D63EC0_WRITE_GFX(dlist++, 0xF5181000, 0x0001785E);
    R1D63EC0_WRITE_GFX(dlist++, 0xF2000000, 0x0007C07C);
    R1D63EC0_WRITE_GFX(dlist++, 0xFC20FE04, 0xFF0FF3FF);
    R1D63EC0_WRITE_GFX(dlist++, 0xFA000000, (u32)arg1->sub->val);
    R1D63EC0_WRITE_GFX(dlist++, 0xE3000A01, 0x00100000);
    R1D63EC0_WRITE_GFX(dlist++, 0xD9000000, 0);
    R1D63EC0_WRITE_GFX(dlist++, 0xD9FFFFFF, 0x00210005);
    R1D63EC0_WRITE_GFX(dlist++, 0xE3000F00, 0);
    R1D63EC0_WRITE_GFX(dlist++, 0xD7000902, 0xFFFFFFFF);
    R1D63EC0_WRITE_GFX(dlist++, 0xE200001C, 0xC8104A50);
    R1D63EC0_WRITE_GFX(dlist++, 0xF2000000 | ((s32)arg1->sub->unk3C & 0xFFF), 0x0107C07C);
    R1D63EC0_WRITE_GFX(dlist++, 0xF5181000, 0x0101785E);
    temp = (s32)arg1->sub->unk40 & 0xFFF;
    R1D63EC0_WRITE_GFX(dlist++, (0xF2000000 | temp) | (temp << 12), 0x0207C07C);
    R1D63EC0_WRITE_GFX(dlist++, 0xF5181000, 0x0201745D);
    return dlist;
}
