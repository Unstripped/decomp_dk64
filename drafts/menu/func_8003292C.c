// func_8003292C (src/menu/E550.c): stage 3 (frame 232 now matches): added named yy=y+0x29, yyo=yo+0x29 (set at outer-loop top, before x=0) and off=D_8074450C*0xC8 (CSE'd across the first hudDrawScaledText call; target spills it at 212(sp)). Spill slots now 72/76/80 vs target 72/80/96 and strings 196..208 vs target 192..204 (4 bytes). Remaining: loop var colouring x=t0,y=v1,xo=t1,yo=a0 vs target x=v1,y=a0,xo=t4,yo=t0; alpha v0 vs a2; uopt temp slot sizes (target 8-byte temps at 72/80). Declaration order of locals does NOT change layout/colouring (60 shuffles all 481). Dropping yo/xo as expressions hoists base offsets into the outer loop (frame 224).
extern Gfx D_1000118[];
extern Mtx D_20000C0;
extern u8 D_800339D0;
extern s16 D_80744490;
extern s16 D_80744494;
extern u8 D_8074450C;
char *func_8070E750(s32, s32, s32);
s32 func_806FD894(s32);
s32 texCacheFindOrLoad(s32);
s32 func_806FBD5C(s32, char *);
Gfx *func_806FC530(Gfx *, s32, s16, s16, char *, s32);
Gfx *hudDrawScaledText(Gfx *, s16, s16, f32, char *);

Gfx *func_8003292C(Gfx *dl, void *arg1) {
    s32 x;
    s32 y;
    s32 xo;
    s32 yo;
    s32 tex;
    char *spCC;
    char *spC8;
    char *spC4;
    s32 spC0;
    s32 alpha;
    s32 yy;
    s32 yyo;
    s32 off;

    spCC = func_8070E750(0xD, 0, 1);
    spC8 = func_8070E750(0xD, 1, 1);
    spC4 = func_8070E750(0xD, 2, 1);
    spC0 = func_806FD894(1);
    gDPPipeSync(dl++);
    gSPDisplayList(dl++, D_1000118);
    gSPSetOtherMode(dl++, G_SETOTHERMODE_L, 3, 29, 0x0F0A4000);
    gDPSetCombine(dl++, 0x119623, 0xFF2FFFFF);
    gSPMatrix(dl++, &D_20000C0, G_MTX_PROJECTION | G_MTX_LOAD | G_MTX_NOPUSH);
    alpha = D_800339D0 * 15;
    if (alpha > 0xFF) {
        alpha = 0xFF;
    }
    alpha &= 0xFF;
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
    gSPSetOtherMode(dl++, G_SETOTHERMODE_H, 12, 2, 0x2000);
    gSPSetOtherMode(dl++, G_SETOTHERMODE_H, 19, 1, 0x80000);
    x = (s32)((f32)(D_80744490 - func_806FBD5C(1, spCC)) * 0.5f);
    gDPSetPrimColor(dl++, 0, 0, 0xFF, 0xFF, 0xFF, alpha);
    gSPSetOtherMode(dl++, G_SETOTHERMODE_L, 3, 29, 0x504240);
    gDPSetCombine(dl++, 0xFF97FF, 0xFF2CFE7F);
    dl = func_806FC530(dl, 1, (s16)(x * 4), (s16)((s32)((((f32)D_80744494 - 82.0f) * 0.5f) - (f32)spC0) * 4), spCC, 0);
    x = (s32)((f32)D_80744490 * 0.5f) * 4;
    off = D_8074450C * 0xC8;
    return hudDrawScaledText(hudDrawScaledText(dl, (s16)x, (s16)(off * 4), 0.5f, spC8), (s16)x, (s16)((s32)((f64)off + (f64)spC0 * 0.5) * 4), 0.5f, spC4);
}
