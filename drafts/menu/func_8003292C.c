// func_8003292C (src/menu/E550.c): OvlB 2026-11-03 (revisit 8): stage 4, count-exact 416, frame 232. deadsweep score full 131->115 (shape 95->86) via hill-climb dead tests (5 new FAKEs: spC4==0 in outer loop head, spC0!=41 at outer latch, D_800339D0&&D_800339D0 after alpha prim colour, D_80744494&&D_80744494 + spC8 before textDrawStringVtx, xx=xx|0; old 'if (spC0) {}' before the width call removed: it made spC0's s2 piece start BEFORE the textGetStringWidth call, the target reloads 'lw s2,192(sp)' after it). Remaining: (a) target off = caller-saved t0 + sw/lw 212(sp) around hud call #1 (home = 5th declared vreg word, -20vreg) while ours colours it s1; (b) target &D_80744490 ptr s1 / spC0 s2 / spCC s3 (colour order pieces) vs ours spCC s1; (c) target spill temps alpha/yy/yyo at 96/80/72 = 4 FEWER vreg words than ours (lowest vreg -132 vs -148): inlining yy/yyo makes it WORSE (frame 248/252); (d) x u16 gives andi v1,t0,0xffff where target has move v1,t0 (s32 x -> frame +8; combined with inlining yy/yyo frame 252); (e) yo/yy/yyo colours a1/a2/a3 vs t0/a1/a2 (target colours yy,yyo before yo). Tried: all positions of off/xx/alpha/spC0/tex defs (grid), x type x xx type x inline yy/yyo grid, i/j counted loop (count 428), 57k+49k hill-climb evals.
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
    s16 xx;
    char *spCC;
    char *spC8;
    char *spC4;
    s32 spC0;
    s32 yo;
    s32 yyo;
    s32 yy;

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
        if (spC4 == 0) {}  // FAKE: deadsweep/hill-climb: steers uopt candidate priority
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
        if (spC0 != 41) {}  // FAKE: deadsweep/hill-climb: steers uopt candidate priority
    } while (y != 0x52);
    gSPSetOtherMode(dl++, G_SETOTHERMODE_H, 12, 2, 0x2000);
    gSPSetOtherMode(dl++, G_SETOTHERMODE_H, 19, 1, 0x80000);
    x = (s32)((f32)(D_80744490 - textGetStringWidth(1, spCC)) * 0.5f);
    gDPSetPrimColor(dl++, 0, 0, 0xFF, 0xFF, 0xFF, alpha);
    if (D_800339D0 && D_800339D0) {}  // FAKE: deadsweep/hill-climb: steers uopt candidate priority
    gSPSetOtherMode(dl++, G_SETOTHERMODE_L, 3, 29, 0x504240);
    gDPSetCombine(dl++, 0xFF97FF, 0xFF2CFE7F);
    if (D_80744494 && D_80744494) {}  // FAKE: deadsweep/hill-climb: steers uopt candidate priority
    if (spC8) {}  // FAKE: deadsweep/hill-climb: steers uopt candidate priority
    dl = textDrawStringVtx(dl, 1, (s16)(x * 4), (s16)((s32)((((f32)D_80744494 - 82.0f) * 0.5f) - (f32)spC0) * 4), spCC, 0);
    xx = (s32)((f32)D_80744490 * 0.5f) * 4;
    off = D_8074450C * 0xC8;
    xx = xx | 0;  // FAKE: deadsweep/hill-climb: steers uopt candidate priority
    return hudDrawScaledText(hudDrawScaledText(dl, xx, (s16)(off * 4), .5f, spC8), xx, (s16)((s32)((f64)off + (f64)spC0 * 0.5) * 4), .5f, spC4);  // FAKE: .5f spells a constant web separate from the 0.5f multiplies (args via lui a3, no mfc1)
}
