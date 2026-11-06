// menuRenderOptionDescription (src/menu/E550.c): Menu4: full14->10 text10 reloc0 shape3, 417 lines and frame0xE8; relocated existing xo guards preserve x304 and row-mask priorities, giving Combine t2. Remaining tail as1 scheduling and final ugen/as1 scratch chain; parked fdiff OK, active full-TU mismatch.
Gfx *menuRenderOptionDescription(Gfx *dl, void *arg1) {
    u32 tex;
    s32 alpha;
    s32 y;
    s32 xo;
    s32 off;
    s32 x;
    char *spCC;
    char *spC8;
    char *spC4;
    s32 spC0;
    s16 xx;
    s32 yo;
    Gfx *loadTilePacket;

    spCC = textTableGetString(0xD, 0, 1);
    spC8 = textTableGetString(0xD, 1, 1);
    spC4 = textTableGetString(0xD, 2, 1);
    spC0 = textGetFontHeight(1);
    gDPPipeSync(dl++);
    gSPDisplayList(dl++, D_1000118);
    gSPSetOtherMode(dl++, G_SETOTHERMODE_L, 3, 29, 0x0F0A4000);
    gDPSetCombine(dl++, 0x119623, 0xFF2FFFFF);
    gSPMatrix(dl++, &D_20000C0, G_MTX_PROJECTION | G_MTX_LOAD | G_MTX_NOPUSH);
    alpha = D_800339D0 * 15;
    if (alpha > 0xFF) {
        alpha = 0xFF;
    }
    gDPSetPrimColor(dl++, 0, 0, alpha, alpha, alpha, 0xFF);
    gSPSetOtherMode(dl++, G_SETOTHERMODE_H, 12, 2, 0);
    gSPSetOtherMode(dl++, G_SETOTHERMODE_H, 19, 1, 0);
    tex = texCacheFindOrLoad(0xB0);
    yo = (s32)(((f32)D_80744494 - 82.0f) * 0.5f);
    y = 0; do {  // FAKE: one source line removes a scheduling barrier before the loop.
        xo = (s32)(((f32)D_80744490 - 204.0f) * 0.5f);
        x = 0; do { // FAKE: as1probe proved this boundary reorders induction initialization.
            if (x) {} // FAKE: shorten the full-width induction range and raise its colouring priority.
            { gDPSetTextureImage(dl++, G_IM_FMT_I, G_IM_SIZ_8b, 102, tex); \
              gDPSetTile(dl++, G_IM_FMT_I, G_IM_SIZ_8b, (((((x + 0x66) - x + 1) >> 1) + 7) >> 3), 0, G_TX_LOADTILE, 0, G_TX_CLAMP, 0, 0, G_TX_CLAMP, 0, 0); \
              gDPLoadSync(dl++); \
              loadTilePacket = dl++; \
              loadTilePacket->words.w0 = _SHIFTL(G_LOADTILE, 24, 8) | _SHIFTL(x << 1, 12, 12) | _SHIFTL(y << 2, 0, 12); \
              loadTilePacket->words.w1 = _SHIFTL(G_TX_LOADTILE, 24, 3) | _SHIFTL((x + 0x66) << 1, 12, 12) | _SHIFTL((y + 0x29) << 2, 0, 12); \
              gDPPipeSync(dl++); \
              gDPSetTile(dl++, G_IM_FMT_I, G_IM_SIZ_4b, (((((x + 0x66) - x + 1) >> 1) + 7) >> 3), 0, G_TX_RENDERTILE, 0, G_TX_CLAMP, 0, 0, G_TX_CLAMP, 0, 0); \
              gDPSetTileSize(dl++, G_TX_RENDERTILE, x << 2, y << 2, (x + 0x66) << 2, (y + 0x29) << 2); \
              } // FAKE: expanded GBI packet reuse; continuations retain macro scheduling.
            gSPTextureRectangle(dl++, xo << 2, yo << 2, (xo + 0x66) << 2, (yo + 0x29) << 2, 0, x << 5, y << 5, 0x400, 0x400);
            x += 0x66;
            xo += 0x66;
        } while (x != 0xCC);
        y += 0x29;
        yo += 0x29;
    } while (y != 0x52);
    if ((s8)D_800339D0 && xo) {}  // FAKE: keep xo below the row-mask priority while merging the post-loop packet block.
    if ((s8)D_800339D0 && xo) {}  // FAKE: preserve xo's range length and the Combine packet's v0/v1 interference.
    gSPSetOtherMode(dl++, G_SETOTHERMODE_H, 12, 2, 0x2000);
    gSPSetOtherMode(dl++, G_SETOTHERMODE_H, 19, 1, 0x80000);
    xo = (s32)((f32)(D_80744490 - textGetStringWidth(1, spCC)) * 0.5f);
    yo = (s32)((((f32)D_80744494 - 82.0f) * 0.5f) - (f32)spC0);
    gDPSetPrimColor(dl++, 0, 0, 0xFF, 0xFF, 0xFF, alpha);
    loadTilePacket = dl++; loadTilePacket->words.w0 = 0xE200001C; loadTilePacket->words.w1 = 0x504240; // FAKE: reuse the t1 load-tile range for this packet.
    arg1 = dl++; ((Gfx *)arg1)->words.w0 = 0xFCFF97FF; ((Gfx *)arg1)->words.w1 = 0xFF2CFE7F; // FAKE: reuse the consumed parameter's packet home.
    dl = textDrawStringVtx(dl, 1, (s16)(xo * 4), (s16)(yo * 4), spCC, 0);
    x = (s32)((f32)D_80744490 * 0.5f);
    arg1 = &off;  // FAKE: address-taken offset retains its stack home across the first text draw.
    off = D_8074450C * 0xC8;
    xx = x * 4;
    xx = xx | 0;  // FAKE: deadsweep/hill-climb: steers uopt candidate priority
    dl = hudDrawScaledText(dl, xx, (s16)(*(s32 *)arg1 * 4), .5f, spC8);  // FAKE: .5f spells a separate constant web (argument via lui a3, no mfc1).
    return hudDrawScaledText(dl, xx, (s16)((s32)((f64)off + (f64)spC0 * 0.5) * 4), .5f, spC4);
}
