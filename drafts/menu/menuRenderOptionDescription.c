// menuRenderOptionDescription (src/menu/E550.c): StackGroup stage4; Base 7cd507e274df69c7fa35a857595a8de5dfeb8563; full51 text51 reloc0 shape3, n417/417 and frame232 exact. Removed yy/yyo/textDl named homes; expanded two preloop OtherMode packets using consumed arg1 and not-yet-loaded tex, removing two GBI packet homes. First alpha&255 spill4C->60; all observed stack offsets exact. Postloop packet macros retained. Remaining u16 induction andi/compare plus postloop register coloring. Full-width induction variants regressed127. Active fdiff text mismatch same2560 bytes, parked plain OK/non-matching OK. Full map .scratch/StackGroup/menuRenderOptionDescription.md.
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
    u16 x;
    s16 xx;
    char *spCC;
    char *spC8;
    char *spC4;
    s32 spC0;
    s32 yo;

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
    arg1 = dl++; ((Gfx *)arg1)->words.w0 = 0xE3001201; ((Gfx *)arg1)->words.w1 = 0; // FAKE: reuse a consumed parameter's packet home.
    tex = (u32)dl++; ((Gfx *)tex)->words.w0 = 0xE3000C00; ((Gfx *)tex)->words.w1 = 0; // FAKE: reuse the not-yet-loaded texture's home.
    tex = texCacheFindOrLoad(0xB0);
    yo = (s32)(((f32)D_80744494 - 82.0f) * 0.5f);
    y = 0; do {  // FAKE: one source line removes a scheduling barrier before the loop.
        xo = (s32)(((f32)D_80744490 - 204.0f) * 0.5f);
        x = 0;
        if (x && x) {}  // FAKE: deadsweep: steers uopt candidate priority
        do {
            gDPLoadTextureTile_4b(dl++, tex, G_IM_FMT_I, 204, 82, x, y, x + 0x66, (y + 0x29), 0,
                                  G_TX_CLAMP, G_TX_CLAMP, 0, 0, 0, 0);
            gSPTextureRectangle(dl++, xo << 2, yo << 2, (xo + 0x66) << 2, (yo + 0x29) << 2, 0, x << 5, y << 5, 0x400, 0x400);
            x += 0x66;
            xo += 0x66;
        } while (x != 0xCC);
        y += 0x29;
        yo += 0x29;
    } while (y != 0x52);
    gSPSetOtherMode(dl++, G_SETOTHERMODE_H, 12, 2, 0x2000);
    gSPSetOtherMode(dl++, G_SETOTHERMODE_H, 19, 1, 0x80000);
    x = (s32)((f32)(D_80744490 - textGetStringWidth(1, spCC)) * 0.5f);
    yo = (s32)((((f32)D_80744494 - 82.0f) * 0.5f) - (f32)spC0);
    gDPSetPrimColor(dl++, 0, 0, 0xFF, 0xFF, 0xFF, alpha);
    if (D_800339D0 && D_800339D0) {}  // FAKE: duplicate reference steers the post-loop register allocation.
    if (D_800339D0 && D_800339D0) {}  // FAKE: deadsweep/hill-climb: steers uopt candidate priority
    gSPSetOtherMode(dl++, G_SETOTHERMODE_L, 3, 29, 0x504240);
    gDPSetCombine(dl++, 0xFF97FF, 0xFF2CFE7F);
    dl = textDrawStringVtx(dl, 1, (s16)(x * 4), (s16)(yo * 4), spCC, 0);
    xx = (s32)((f32)D_80744490 * 0.5f) * 4;
    arg1 = &off;  // FAKE: address-taken offset retains its stack home across the first text draw.
    off = D_8074450C * 0xC8;
    xx = xx | 0;  // FAKE: deadsweep/hill-climb: steers uopt candidate priority
    dl = hudDrawScaledText(dl, xx, (s16)(*(s32 *)arg1 * 4), .5f, spC8);  // FAKE: .5f spells a separate constant web (argument via lui a3, no mfc1).
    return hudDrawScaledText(dl, xx, (s16)((s32)((f64)off + (f64)spC0 * 0.5) * 4), .5f, spC4);
}
