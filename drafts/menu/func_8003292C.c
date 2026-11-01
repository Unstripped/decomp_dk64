// func_8003292C (src/menu/E550.c): func_8003292C (src/menu/E550.c): stage 4 park; R5 Menu: full diff 161 -> 137 (shape 111; 416 target insns vs 417) via declaration reorder + 2 guarded dead tests (if (x && x) after x = 0 in the inner-loop head, if (spC0) after the loop). Untouched root cause: uopt colours yo (adjsave 15.5: 2 uses in bb9 + def in bb8) before yy/yyo (adjsave 10) so ours yo=a1,yy=a2,yyo=a3 vs target yy=a1,yyo=a2,yo=t0,xo=t4; ours 0.5f (adjsave 3.75 over bb8-18) beats 204.0f (3.33) for f0 (target 204.0=f0, 0.5=f2); u16 x emits andi v1,t0,0xffff (target plain move; s32 x moves x to t0 and y to v1: worse); ours 0.5f args are mfc1 a3 (shared web), target lui a3,0x3f00 (literal spelled .5f for the two args gives the lui). Tried: 2^10 literal-spelling grid (0.5f/82.0f/204.0f sites), yy/yyo inline/s32/explicit y=yy copy, nx temp for the loop compare, 4x 9-minute hill-climbs (decl order, types, dead tests, spellings; best 122-133 only with 8+ fakes or unsafe type narrowing), permuter 560s (garbage).
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

Gfx *func_8003292C(Gfx *dl, void *arg1) {
    u32 tex;
    s32 alpha;
    s32 off;
    s32 y;
    s32 xo;
    u16 x;
    char *spCC;
    char *spC8;
    char *spC4;
    s32 spC0;
    s32 yo;
    s16 yyo;
    s16 yy;

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
    y = 0;
    do {
        xo = (s32)(((f32)D_80744490 - 204.0f) * 0.5f);
        yy = y + 0x29;
        yyo = yo + 0x29;
        x = 0;
        if (x && x) {}  // FAKE: deadsweep: steers uopt candidate priority
        do {
            gDPLoadTextureTile_4b(dl++, tex, G_IM_FMT_I, 204, 82, x, y, x + 0x66, yy, 0,
                                  G_TX_CLAMP, G_TX_CLAMP, 0, 0, 0, 0);
            gSPTextureRectangle(dl++, xo << 2, yo << 2, (xo + 0x66) << 2, yyo << 2, 0, x << 5, y << 5, 0x400, 0x400);
            x += 0x66;
            xo += 0x66;
        } while (x != 0xCC);
        y += 0x29;
        yo += 0x29;
    } while (y != 0x52);
    if (spC0) {}  // FAKE: deadsweep: steers uopt candidate priority
    gSPSetOtherMode(dl++, G_SETOTHERMODE_H, 12, 2, 0x2000);
    gSPSetOtherMode(dl++, G_SETOTHERMODE_H, 19, 1, 0x80000);
    x = (s32)((f32)(D_80744490 - textGetStringWidth(1, spCC)) * 0.5f);
    gDPSetPrimColor(dl++, 0, 0, 0xFF, 0xFF, 0xFF, alpha);
    gSPSetOtherMode(dl++, G_SETOTHERMODE_L, 3, 29, 0x504240);
    gDPSetCombine(dl++, 0xFF97FF, 0xFF2CFE7F);
    dl = textDrawStringVtx(dl, 1, (s16)(x * 4), (s16)((s32)((((f32)D_80744494 - 82.0f) * 0.5f) - (f32)spC0) * 4), spCC, 0);
    x = (s32)((f32)D_80744490 * 0.5f) * 4;
    off = D_8074450C * 0xC8;
    return hudDrawScaledText(hudDrawScaledText(dl, (s16)x, (s16)(off * 4), 0.5f, spC8), (s16)x, (s16)((s32)((f64)off + (f64)spC0 * 0.5) * 4), 0.5f, spC4);
}
