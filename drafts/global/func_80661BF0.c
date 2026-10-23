// func_80661BF0 (src/global/63EC0.c): 24-packet Gfx writer with D_80748A90 entry->res0 and res1 references
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

typedef struct R1D63EC0_Entry {
    void (*fn0)();
    void (*fn1)();
    void (*fn2)();
    void *res0;
    void *res1;
    u32 flags;
} R1D63EC0_Entry;

extern R1D63EC0_Entry D_80748A90[];

#define R1D63EC0_WRITE_GFX(pkt, _w0, _w1) { Gfx *_g = (Gfx *)(pkt); _g->words.w0 = (_w0); _g->words.w1 = (_w1); }

Gfx *func_80661BF0(Gfx *dlist, R1D63EC0_Obj2 *arg1, u8 arg2) {
    R1D63EC0_Entry *entry = &D_80748A90[arg2];
    R1D63EC0_WRITE_GFX(dlist++, 0xE7000000, 0);
    R1D63EC0_WRITE_GFX(dlist++, 0xFD500000, (u32)entry->res0);
    R1D63EC0_WRITE_GFX(dlist++, 0xF5500000, 0x07018060);
    R1D63EC0_WRITE_GFX(dlist++, 0xE6000000, 0);
    R1D63EC0_WRITE_GFX(dlist++, 0xF3000000, 0x073FF200);
    R1D63EC0_WRITE_GFX(dlist++, 0xE7000000, 0);
    R1D63EC0_WRITE_GFX(dlist++, 0xF5400800, 0x00018060);
    R1D63EC0_WRITE_GFX(dlist++, 0xF2000000, 0x000FC0FC);
    R1D63EC0_WRITE_GFX(dlist++, 0xFC121824, 0xFF33FFFF);
    R1D63EC0_WRITE_GFX(dlist++, 0xE3000A01, 0);
    R1D63EC0_WRITE_GFX(dlist++, 0xD9000000, 0);
    R1D63EC0_WRITE_GFX(dlist++, 0xD9FFFFFF, 0x00200005);
    R1D63EC0_WRITE_GFX(dlist++, 0xE3000F00, 0x00010000);
    R1D63EC0_WRITE_GFX(dlist++, 0xD7000002, 0xFFFFFFFF);
    R1D63EC0_WRITE_GFX(dlist++, 0xE200001C, 0x00552230);
    R1D63EC0_WRITE_GFX(dlist++, 0xF2000000 | ((s32)arg1->sub->unk3C & 0xFFF), 0x000FC0FC);
    R1D63EC0_WRITE_GFX(dlist++, 0xF5181000, 0x0101785E);
    R1D63EC0_WRITE_GFX(dlist++, 0xFD100000, (u32)entry->res1);
    R1D63EC0_WRITE_GFX(dlist++, 0xE8000000, 0);
    R1D63EC0_WRITE_GFX(dlist++, 0xF5000100, 0x07000000);
    R1D63EC0_WRITE_GFX(dlist++, 0xE6000000, 0);
    R1D63EC0_WRITE_GFX(dlist++, 0xF0000000, 0x0703C000);
    R1D63EC0_WRITE_GFX(dlist++, 0xE7000000, 0);
    R1D63EC0_WRITE_GFX(dlist++, 0xE3001001, 0x00008000);
    return dlist;
}
