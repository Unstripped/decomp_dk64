// func_80663594 (src/global/67890.c): 100% logic and control-flow match, minor register allocation (t5-t9) in middle Gfx block
#include "common.h"
#include "actor.h"

typedef struct R2F684C0_Entry14 {
    f32 unk0;
    u8 pad4[0xC];
    u8 unk10;
    u8 unk11;
    u8 unk12;
    u8 unk13;
} R2F684C0_Entry14;

extern R2F684C0_Entry14 *D_807F93F4;
extern u32 D_807F93FC;
extern u32 D_807F9400;
u32 osVirtualToPhysical(void *);

#define R2F684C0_WRITE_GFX(pkt, _w0, _w1) { Gfx *_g = (Gfx *)(pkt); _g->words.w0 = (_w0); _g->words.w1 = (u32)(_w1); }
#define R2F684C0_WRITE_GFX_REV(pkt, _w0, _w1) { Gfx *_g = (Gfx *)(pkt); _g->words.w1 = (u32)(_w1); _g->words.w0 = (_w0); }

Gfx *func_80663594(Gfx *glist, s32 arg1) {
    R2F684C0_WRITE_GFX(glist++, 0xE7000000, 0);
    R2F684C0_WRITE_GFX(glist++, 0xE200001C, 0x00504A50);
    R2F684C0_WRITE_GFX(glist++, 0xFC11FE23, 0xFFFFF7FB);
    R2F684C0_WRITE_GFX(glist++, 0xE3000A01, 0);
    R2F684C0_WRITE_GFX(glist++, 0xD9000000, 0);
    R2F684C0_WRITE_GFX(glist++, 0xD9FFFFFF, 0x00200005);
    R2F684C0_WRITE_GFX(glist++, 0xFA000000, D_807F93F4[arg1].unk10 | 0x64646400);
    R2F684C0_WRITE_GFX(glist++, 0xD7000002, 0xFFFFFFFF);
    R2F684C0_WRITE_GFX(glist++, 0xFD700000, D_807F9400);
    R2F684C0_WRITE_GFX(glist++, 0xF5700000, 0x07018060);
    R2F684C0_WRITE_GFX(glist++, 0xE6000000, 0);
    R2F684C0_WRITE_GFX(glist++, 0xF3000000, 0x077FF100);
    R2F684C0_WRITE_GFX(glist++, 0xE7000000, 0);
    R2F684C0_WRITE_GFX(glist++, 0xF5681000, 0x00018060);
    R2F684C0_WRITE_GFX_REV(glist++, 0xF2000000, 0x000FC0FC);
    R2F684C0_WRITE_GFX_REV(glist++, (D_807F93F4[arg1].unk13 | 0xF2000000) | (D_807F93F4[arg1].unk12 << 12), 0x000FC0FC);
    R2F684C0_WRITE_GFX(glist++, 0x01004008, osVirtualToPhysical((void *)((arg1 << 6) + D_807F93FC)));
    R2F684C0_WRITE_GFX(glist++, 0x06000204, 0x00000406);
    R2F684C0_WRITE_GFX(glist++, 0xE7000000, 0);
    return glist;
}
