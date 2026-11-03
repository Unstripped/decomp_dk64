// func_8003292C (src/menu/E550.c): MenuB 2026-11-03: stage 4, count-exact 416, frame 232, full 131 (was 135), shape 95 (was 109), parked in copy. NEW levers: (1) '.5f' (distinct literal spelling) for the two hudDrawScaledText f32 args splits the 0.5f web from the f2 multiplies: args become 'lui a3,0x3f00' (target) instead of 'mfc1 a3,$f2' -> removes 2 mfc1+1 mtc1, count 416 -> 414 until the s32 yy/yyo (not s16) restore count 416 with better shape (109 -> 95). (2) callee protos (textGetFontHeight u8(s16), texCacheFindOrLoad(u16), textDrawStringVtx s16/u8) do not change codegen. Remaining: (a) target 'off' is UNCOLOURED (move t0,a2; sw t0,212(sp); lw t0,212(sp) after hud call #1) while ours colours it s1; memory-resident 'off' (s32 off[1] or volatile) adds the sw/lw but then count 418 with u16 x (andi vs target move v1,t0) and s32 x needs frame 240 (x,xx stop packing); (b) post-loop s-reg roles: target s1=&D_80744490 ptr, s2=spC0, s3=spCC vs ours s3/s2/s1, and spC0 reload 'lw s2,192(sp)' placed late in target; (c) uopt colours yo=a1 (ours) vs target yy=a1,yyo=a2,yo=t0,xo=t4; hoisted invariant order y<<2,yy<<2,xo,yyo<<2,yo<<2,y<<5 in target vs ours ...,yo<<2,y<<5,yyo<<2 (ours yyo<<2 coloured last); spill slots alpha/yy/yyo 80/76/72 vs target 96/80/72 (4 hole candidates). Tried: 8.3k-eval random hill-climb over x/xx/yy/yyo/off/y/yo/xo/tex/alpha types x inline-vs-named x 5 literal spellings x decl order x update form x dead tests: no gain over this state; callee-proto toggles; mem-resident off grid.
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
    xx = (s32)((f32)D_80744490 * 0.5f) * 4;
    off = D_8074450C * 0xC8;
    return hudDrawScaledText(hudDrawScaledText(dl, xx, (s16)(off * 4), .5f, spC8), xx, (s16)((s32)((f64)off + (f64)spC0 * 0.5) * 4), .5f, spC4);  // FAKE: .5f spells a constant web separate from the 0.5f multiplies (args via lui a3, no mfc1)
}
