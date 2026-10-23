// func_80663594 (src/global/67890.c): down to 15 diffs using gDPSetPrimColor, gDPLoadTextureBlock (IA 8b 64x64) and gDPSetTileSize; middle Gfx block 100% matched, remaining is address math for D_807F93FC
#include "common.h"
#include "actor.h"

typedef struct R6A_Entry14 {
    f32 unk0;
    u8 pad4[0xC];
    u8 unk10;
    u8 unk11;
    u8 unk12;
    u8 unk13;
} R6A_Entry14;

extern R6A_Entry14 *D_807F93F4;
extern Mtx *D_807F93FC;
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
    gDPSetPrimColor(glist++, 0, 0, 100, 100, 100, D_807F93F4[arg1].unk10);
    W(glist++, 0xD7000002, 0xFFFFFFFF);
    gDPLoadTextureBlock(glist++, D_807F9400, G_IM_FMT_IA, G_IM_SIZ_8b, 64, 64, 0, G_TX_WRAP, G_TX_WRAP, 6, 6, 0, 0);
    gDPSetTileSize(glist++, 0, D_807F93F4[arg1].unk12, D_807F93F4[arg1].unk13, 63 << 2, 63 << 2);
    W(glist++, 0x01004008, osVirtualToPhysical((void *)((arg1 << 6) + D_807F93FC)));
    W(glist++, 0x06000204, 0x00000406);
    W(glist++, 0xE7000000, 0);
    return glist;
}
