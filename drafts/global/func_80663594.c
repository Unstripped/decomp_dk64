// func_80663594 (src/global/67890.c): 100% logic and control-flow match, 53 diffs (down from 136) by matching W store orders, residual t5-t9 temp regalloc in middle Gfx block
#include "common.h"
#include "actor.h"

typedef struct R4B_Entry14 {
    f32 unk0;
    u8 pad4[0xC];
    u8 unk10;
    u8 unk11;
    u8 unk12;
    u8 unk13;
} R4B_Entry14;

extern R4B_Entry14 *D_807F93F4;
extern u32 D_807F93FC;
extern u32 D_807F9400;
u32 osVirtualToPhysical(void *);

#define W(pkt, _w0, _w1) { Gfx *_g = (Gfx *)(pkt); _g->words.w0 = (_w0); _g->words.w1 = (u32)(_w1); }

Gfx *func_80663594(Gfx *glist, s32 arg1) {
    W(glist++, 0xE7000000, 0);
    W(glist++, 0xE200001C, 0x00504A50);
    W(glist++, 0xFC11FE23, 0xFFFFF7FB);
    W(glist++, 0xE3000A01, 0);
    W(glist++, 0xD9000000, 0);
    W(glist++, 0xD9FFFFFF, 0x00200005);
    W(glist++, 0xFA000000, D_807F93F4[arg1].unk10 | 0x64646400);
    W(glist++, 0xD7000002, 0xFFFFFFFF);
    W(glist++, 0xFD700000, D_807F9400);
    W(glist++, 0xF5700000, 0x07018060);
    W(glist++, 0xE6000000, 0);
    W(glist++, 0xF3000000, 0x077FF100);
    W(glist++, 0xE7000000, 0);
    W(glist++, 0xF5681000, 0x00018060);
    W(glist++, 0xF2000000, 0x000FC0FC);
    W(glist++, (D_807F93F4[arg1].unk13 | 0xF2000000) | (D_807F93F4[arg1].unk12 << 12), 0x000FC0FC);
    W(glist++, 0x01004008, osVirtualToPhysical((void *)((arg1 << 6) + D_807F93FC)));
    W(glist++, 0x06000204, 0x00000406);
    W(glist++, 0xE7000000, 0);
    return glist;
}
