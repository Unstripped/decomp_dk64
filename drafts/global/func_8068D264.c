// func_8068D264 (src/global/90D80.c): 409 insns matched exactly, frame 0x88 matched; regalloc diff: D_8075022C and D_80750228 allocated to a2/a3 instead of t1/a2
typedef struct R290B_Player {
    u8 pad[0x270];
    s16 rect[4];
} R290B_Player;

#define R290B_WRITE_GFX(pkt, _w0, _w1) { Gfx *_g = (Gfx *)(pkt); _g->words.w0 = (_w0); _g->words.w1 = (_w1); }

extern R290B_Player *D_807FC924;
extern u32 D_80744478;
extern f32 D_80750228, D_8075022C;
extern u32 D_80750230;
extern s32 D_8076A0A8;
extern Mtx D_2000080;
extern Mtx D_2000180;

Gfx *func_8068D264(Gfx *glist, f32 *arg1) {
    s32 sp84;
    f32 sp80;
    f32 sp7C;

    sp80 = *arg1;
    sp7C = D_80744478 * 0.5;
    sp84 = assetLoad(0x19, 0x173C, 1, 0);
    func_8066B434(sp84, 0x1B2, 0x46);

    gDPPipeSync(glist++);
    gDPSetScissor(glist++, G_SC_NON_INTERLACE, D_807FC924->rect[0], D_807FC924->rect[1], D_807FC924->rect[2], D_807FC924->rect[3]);
    R290B_WRITE_GFX(glist++, 0xE3000A01, 0);
    R290B_WRITE_GFX(glist++, 0xE3000F00, 0x10000);
    R290B_WRITE_GFX(glist++, 0xD9000000, 0);
    R290B_WRITE_GFX(glist++, 0xD9FFFFFF, 0x00200004);
    R290B_WRITE_GFX(glist++, 0xD7000002, -1);
    R290B_WRITE_GFX(glist++, 0xE200001C, 0x00504340);
    R290B_WRITE_GFX(glist++, 0xFC119623, 0xFF2FFFFF);

    if (D_8076A0A8 == 0x26) {
        gDPSetPrimColor(glist++, 0, 0, 0x8A, 0x52, 0x16, 200.0f * sp80);
    } else {
        gDPSetPrimColor(glist++, 0, 0, 0xFF, 0xFF, 0xFF, 35.0f * sp80);
    }

    gDPLoadTextureBlock(glist++, (u8 *)(sp84 + 0x80000000), G_IM_FMT_IA, G_IM_SIZ_8b, 64, 64, 0, G_TX_WRAP, G_TX_WRAP, 6, 6, 0, 0);

    gDPSetTileSize(glist++, 0, (s32)D_8075022C, (s32)D_80750228, 63 << 2, 63 << 2);
    gDPSetTile(glist++, G_IM_FMT_IA, G_IM_SIZ_8b, 8, 0, 1, 0, G_TX_WRAP, 6, 0, G_TX_WRAP, 6, 0);

    R290B_WRITE_GFX(glist++, 0xDA380007, (u32)&D_2000080);
    R290B_WRITE_GFX(glist++, 0xDA380003, (u32)&D_2000180);
    R290B_WRITE_GFX(glist++, 0x01004008, osVirtualToPhysical(&D_80750230));
    R290B_WRITE_GFX(glist++, 0x06000204, 0x00000406);
    gDPPipeSync(glist++);

    if (D_8076A0A8 == 0x26) {
        f64 temp = sp7C;
        D_80750228 -= 2.0 * temp;
        D_8075022C -= 14.0 * temp;
    } else {
        f64 temp = sp7C;
        D_80750228 -= temp;
        D_8075022C -= 0.5 * temp;
    }

    if (D_80750228 < 0.0) {
        D_80750228 = 255.0f;
    }
    if (D_8075022C < 0.0) {
        D_8075022C = 255.0f;
    }

    return glist;
}
