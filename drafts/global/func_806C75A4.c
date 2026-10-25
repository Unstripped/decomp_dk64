// func_806C75A4 (src/global/CBEA0.c): stage 6: size matches (2400B), branches/stack/gfx stores match; only s-reg rotation left: expected tbl=s0,&E8=s1,sel=s2 and yoff=s1,i=s2 (mine sel=s0,tbl=s1,&E8=s2 / i=s1,yoff=s2) + resulting t/f temp order in first block. Fixed this round: x += 8.0 / x -= 8.0 as separate statements (x gets $f0, y spilled), yoff = -unk5 * 0x23 (negu into var reg). uopt: priority=savings/((nlive-2)/4+2); sel 8/5=1.6 > tbl 6/6 > &E8 5/6, i 62/5 > yoff 31/3 - expected needs reverse; tried sel types, copies, loop forms (for/while/++i), decl order, register kw, tbl placement: no change
extern Actor *D_807FBB40;
extern s8 D_80750754;
extern s16 D_80750758;
extern f32 D_807FC8E8;
extern f32 D_807FC8EC;
extern u8 *D_807FC8F0;
typedef struct R1C2CB_Entry {
    s16 unk0;
    s16 unk2;
    s8 unk4;
    s8 unk5;
} R1C2CB_Entry;
extern R1C2CB_Entry D_807506D0[];

#define R1C2CB_GFX(pkt, _w0, _w1) { Gfx *_g = (Gfx *)(pkt); _g->words.w0 = (_w0); _g->words.w1 = (u32)(_w1); }

extern Gfx D_1000118;
extern Mtx D_20000C0;
typedef union R1C2CB_Col {
    s32 w;
    u8 b[4];
} R1C2CB_Col;

extern R1C2CB_Col D_80750814;
extern f32 D_80750818[];
extern f32 D_80750828[];

void func_805FEE84(u8, u8, u8, u8);
void *func_80610FE8(s32);
void heapFreeDeferred(void *);
s32 func_806FBD5C();
Gfx *func_806FC530(Gfx *, s32, s16, s16, void *, s32);
void guScaleF(f32 mf[4][4], f32 x, f32 y, f32 z);
void guTranslateF(f32 mf[4][4], f32 x, f32 y, f32 z);
void guMtxCatF(f32 mf[4][4], f32 nf[4][4], f32 res[4][4]);
void guMtxF2L(f32 mf[4][4], Mtx *m);

Gfx *func_806C75A4(Gfx *gdl, Actor *arg1) {
    f32 sx;
    f32 sy;
    u8 *p;
    f32 *tbl;
    f32 x;
    f32 y;
    R1C2CB_Col col;
    f32 mf[4][4];
    f32 mf2[4][4];
    Mtx *mtx;
    s16 v;
    s8 sel;
    s16 i;
    s16 yoff;

    col = D_80750814;
    if (D_80750754 < 0) {
        return gdl;
    }
    sel = D_807506D0[D_80750754].unk4;
    tbl = &D_80750818[sel];
    v = (f64)(D_80750828[sel] * D_807FC8EC) + ((f64)D_807FC8E8 - 0.5) * (f64)*tbl;
    if (v < 0) {
        v = 0;
    }
    col.b[sel] = v;
    func_805FEE84(col.b[1], col.b[3], col.b[0], col.b[2]);
    if (D_807FC8E8 == 0.0f) {
        return gdl;
    }
    mtx = func_80610FE8(0x40);
    heapFreeDeferred(mtx);
    R1C2CB_GFX(gdl++, 0xE7000000, 0);
    R1C2CB_GFX(gdl++, 0xDE000000, &D_1000118);
    R1C2CB_GFX(gdl++, 0xE3000A01, 0);
    R1C2CB_GFX(gdl++, 0xE200001C, 0x504240);
    R1C2CB_GFX(gdl++, 0xFA000000, 0xFFFFFFFF);
    R1C2CB_GFX(gdl++, 0xFC119623, 0xFF2FFFFF);
    R1C2CB_GFX(gdl++, 0xDA380007, &D_20000C0);
    R1C2CB_GFX(gdl++, 0xDA380003, mtx);
    sy = 1.0;
    sx = 1.0;
    if (sel & 1) {
        sx = D_807FC8EC;
    } else {
        sy = D_807FC8EC;
    }
    guScaleF(mf, sx * 0.55, sy * 0.55, 1.0f);
    switch (sel) {
    case 0:
        x = 160.0f;
        y = *tbl * D_807FC8E8 + -55.0;
        break;
    case 2:
        x = 160.0f;
        y = 265.0 - *tbl * D_807FC8E8;
        break;
    case 1:
        y = 120.0f;
        x = *tbl * D_807FC8E8 + -70.0;
        x += 8.0;
        break;
    case 3:
        y = 120.0f;
        x = 390.0 - *tbl * D_807FC8E8;
        x -= 8.0;
        break;
    }
    guTranslateF(mf2, x * 4.0, y * 4.0, 0.0f);
    guMtxCatF(mf, mf2, mf);
    guMtxF2L(mf, mtx);
    p = D_807FC8F0;
    i = 0;
    if (D_80750758 > 0) {
        do {
            if (*p == 0) {
                i++;
            }
            p++;
        } while (i < D_80750758);
        i = 0;
    }
    yoff = -D_807506D0[D_80750754].unk5 * 0x23;
    if (D_807506D0[D_80750754].unk5 > 0) {
        do {
            gdl = func_806FC530(gdl, 1, -(s16)(func_806FBD5C(1, p) * 2), yoff, p, 0);
            yoff += 0x60;
            if (*p != 0) {
                do {
                    p++;
                } while (*p != 0);
            }
            i++;
            p++;
        } while (i < D_807506D0[D_80750754].unk5);
    }
    R1C2CB_GFX(gdl++, 0xD8380002, 0x40);
    R1C2CB_GFX(gdl++, 0xE7000000, 0);
    return gdl;
}
