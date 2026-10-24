// func_806AA09C (src/global/ACDC0.c): stage 6: only the two float spill slots differ (fx/fy at 0x44/0x40 vs expected 0x48/0x44); everything else identical, parked NON_MATCHING in ACDC0.c. Tried extra pads/unused f32 locals (frame grows), sc local, expression reorders; permuter 240s best 10 vs 16 not clean
#define M1_WRITE_GFX(pkt, _w0, _w1) { Gfx *_g = (Gfx *)(pkt); _g->words.w0 = (_w0); _g->words.w1 = (_w1); }

void heapFreeDeferred(void *);
void *func_80610FE8(s32);
Gfx *func_806FC530(Gfx *, s32, s16, s32, void *, s32);
void _sprintf(char *, const char *, ...);
Gfx *func_8068C5A8(Gfx *, s32, s32, s32, s32, s32, s32, s32, f32, f32, s32, f32);

Gfx *func_806AA09C(s16 x, s16 y, s16 n1, s16 n2, Gfx *dl, s8 flag, f32 scale) {
    Mtx *mtx;
    s32 w;
    f32 m1[4][4];
    f32 m2[4][4];
    char buf1[8];
    char buf2[8];

    mtx = func_80610FE8(0x40);
    heapFreeDeferred(mtx);
    if (n1 >= 0x64) {
        w = 0x7C;
    } else if (n1 >= 10) {
        w = 0x5C;
    } else {
        w = 0x3C;
    }
    if (flag != 0) {
        x = (f32)x - (f32)w * scale;
    }
    guScaleF(m1, scale, scale, 1.0f);
    guTranslateF(m2, x, y, 0.0f);
    guMtxCatF(m1, m2, m1);
    guMtxF2L(m1, mtx);
    M1_WRITE_GFX(dl++, 0xDA380002, (u32)mtx);
    _sprintf(buf1, "%d", n1);
    _sprintf(buf2, "%d", n2);
    dl = func_806FC530(func_806FC530(dl, 1, 0, -0x28, buf1, 0x80), 1, w, 0x28, buf2, 0);
    M1_WRITE_GFX(dl++, 0xD8380002, 0x40);
    M1_WRITE_GFX(dl++, 0xE7000000, 0);
    return func_8068C5A8(dl, 0x9F, 0, 2, 0x20, 0x20, (s32)((f32)x + (f32)(w - 0x10) * scale), (s32)((f32)y + 45.0f * scale), scale * 3.125, scale * 3.125, 0, 0.0f);
}
