// func_806C8220 (src/global/CC800.c): G00: frame matches with f32 pad0 first and f64 pad1 last; remaining: li t5,2 should be hoisted to entry and used by case-2 compare; out/tbl/i regs (target a0/a1/a3), mine a3/a0/a1. struct-copy locals from D_80750AD8/AF8/B24 match.
typedef struct G00Tbl8 {
    /* 0x00 */ f32 f[8];
} G00Tbl8;

typedef struct G00Tbl11 {
    /* 0x00 */ f32 f[11];
} G00Tbl11;

typedef struct G00Tbl4 {
    /* 0x00 */ f32 f[4];
} G00Tbl4;

typedef struct G00Vtx {
    /* 0x00 */ f32 unk0;
    /* 0x04 */ f32 unk4;
    /* 0x08 */ f32 unk8;
    /* 0x0C */ f32 unkC;
    /* 0x10 */ f32 unk10;
    /* 0x14 */ f32 unk14;
} G00Vtx;

typedef struct G00Out {
    /* 0x000 */ f32 unk0;
    /* 0x004 */ f32 unk4;
    /* 0x008 */ f32 unk8;
    /* 0x00C */ f32 unkC;
    /* 0x010 */ f32 unk10;
    /* 0x014 */ u8 unk14;
    /* 0x015 */ u8 pad15[3];
    /* 0x018 */ s32 unk18;
    /* 0x01C */ G00Vtx unk1C[12];
} G00Out; // size = 0x13C

extern G00Tbl8 D_80750AD8;
extern G00Tbl11 D_80750AF8;
extern G00Tbl4 D_80750B24;

void func_806C8220(s32 arg0, G00Out *arg1, s32 arg2) {
    f32 pad0;
    G00Tbl8 sp74;
    G00Tbl11 sp48;
    G00Tbl4 sp38;
    f64 pad1;
    f32 *tbl;
    f32 sign;
    s32 count;
    s32 n;
    s32 i;
    s32 j;
    G00Vtx *v;
    G00Out *out;

    sp74 = D_80750AD8;
    count = 1;
    n = 4;
    sp48 = D_80750AF8;
    tbl = sp38.f;
    sp38 = D_80750B24;
    out = arg1;
    sign = 1.0f;
    if (arg2 == 2) {
        goto start;
    }
    if (arg2 == 3) {
        goto case3;
    }
    if (arg2 == 5) {
        goto case5;
    }
    return;
case3:
    count = 1;
    n = 11;
    tbl = sp48.f;
    goto start;
case5:
    count = 2;
    n = 8;
    tbl = sp74.f;
start:
    for (i = 0; i < count; i++) {
        v = out->unk1C;
        out->unk14 = 2;
        out->unk18 = arg2;
        out->unkC = 0.0f;
        out->unk8 = 0.0f;
        out->unk4 = 0.0f;
        out->unk0 = 0.0f;
        out->unk10 = -128.0f;
        for (j = 0; j < n; j++) {
            v->unk4 = 0.0f;
            v->unk10 = 0.0f;
            v->unk0 = tbl[j] * sign;
            v->unkC = 0.0f;
            v->unk14 = 0.0f;
            v->unk8 = 0.0f;
            v++;
        }
        out++;
        sign = -sign;
    }
