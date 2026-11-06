// menuRenderOptionDescription (src/menu/E550.c): Stage 6; full=27 text=27 reloc=0 shape=3, normalized 417/417 and frame 0xE8 exact. Menu3 restores two preloop macro homes, reuses arg1 for postloop Combine, and changes both postloop ghosts to signed-byte expressions: alpha at0x60, yy at0x50, yyo at0x48, all observed stack offsets exact without the old exact-stack alternative's six preheader scratch regressions. Combine remains v0 instead of t2; raw offset byte remains v1 instead of t0; loop-tail schedule and later conversion scratch differences remain. Active fdiff FAILED .text 2560/2560; parked fdiff OK; --non-matching compiles.
extern Gfx D_1000118[];
extern Mtx D_20000C0;
extern s16 D_80744490;
extern s16 D_80744494;
extern u8 D_8074450C;
char *textTableGetString(s32, s32, s32);
s32 textGetFontHeight(s32);
s32 texCacheFindOrLoad(s32);
s32 textGetStringWidth(s32, char *);
Gfx *textDrawStringVtx(Gfx *, s32, s16, s16, char *, s32);
Gfx *hudDrawScaledText(Gfx *, s16, s16, f32, char *);

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
    gSPSetOtherMode(dl++, G_SETOTHERMODE_H, 12, 2, 0x2000);
    gSPSetOtherMode(dl++, G_SETOTHERMODE_H, 19, 1, 0x80000);
    xo = (s32)((f32)(D_80744490 - textGetStringWidth(1, spCC)) * 0.5f);
    yo = (s32)((((f32)D_80744494 - 82.0f) * 0.5f) - (f32)spC0);
    gDPSetPrimColor(dl++, 0, 0, 0xFF, 0xFF, 0xFF, alpha);
    if ((s8)D_800339D0 && (s8)D_800339D0) {}  // FAKE: separate the ghost's signed-byte expression from the alpha load's spill region.
    if ((s8)D_800339D0 && (s8)D_800339D0) {}  // FAKE: retain the post-loop allocation constraints.
    loadTilePacket = dl++; loadTilePacket->words.w0 = 0xE200001C; loadTilePacket->words.w1 = 0x504240; // FAKE: reuse the t1 load-tile range for this packet.
    arg1 = dl++; ((Gfx *)arg1)->words.w0 = 0xFCFF97FF; ((Gfx *)arg1)->words.w1 = 0xFF2CFE7F; // FAKE: reuse the consumed parameter's packet home.
    dl = textDrawStringVtx(dl, 1, (s16)(xo * 4), (s16)(yo * 4), spCC, 0);
    xx = (s32)((f32)D_80744490 * 0.5f) * 4;
    arg1 = &off;  // FAKE: address-taken offset retains its stack home across the first text draw.
    x = D_8074450C * 0xC8; off = x; // FAKE: the v1 carrier interferes with off, assigning its spill range to t0.
    xx = xx | 0;  // FAKE: deadsweep/hill-climb: steers uopt candidate priority
    dl = hudDrawScaledText(dl, xx, (s16)(*(s32 *)arg1 * 4), .5f, spC8);  // FAKE: .5f spells a separate constant web (argument via lui a3, no mfc1).
    return hudDrawScaledText(dl, xx, (s16)((s32)((f64)off + (f64)spC0 * 0.5) * 4), .5f, spC4);
}
