// func_806A3E9C (src/global/A8400.c): stage 6: body matches 1:1 (u32 casts reproduce the cfc1/ctc1 cvt.w.d sequences). Frame 0x130 vs expected 0x128 and locals +8..+0x10: named f64 locals each cost stack (3 f64 vars -> 0x148, 1 -> 0x138, fully inlined double expressions -> 0x130); expected keeps all doubles in f20-f30 temporaries. i/idx (counter vs index) land in s3/s5 swapped; cnt u8 conversion materialises via v1 then move s8,v1 in expected.
typedef struct A8R2bAnim {
    /* 0x00 */ u8 pad0[0x20];
    /* 0x20 */ f32 unk20;
    /* 0x24 */ f32 unk24;
    /* 0x28 */ f32 unk28;
    /* 0x2C */ f32 unk2C;
    /* 0x30 */ f32 unk30;
    /* 0x34 */ u8 *unk34;
} A8R2bAnim;

s32 func_806A3C6C(s32, u8 *, s32, s32);

s32 func_806A3E9C(s32 arg0, A8R2bAnim *arg1, s32 arg2) {
    f32 spE8[4][4];
    f32 spA8[4][4];
    f32 spA4;
    f32 spA0;
    f32 scale;
    s32 cnt;
    s32 i;
    s32 idx;
    s32 ret;
    s32 off;

    ret = arg0;
    cnt = (u8) (u32) ((((f64) arg1->unk20 < 0.320000000000000007) ? (f64) arg1->unk20 : 0.320000000000000007) * 12.5);
    i = 1;
    idx = 1;
    if (cnt > 0) {
        do {
            spA4 = (f32) ((f64) (arg1->unk2C - arg1->unk24) * ((f64) i * 0.0800000000000000017) + (f64) arg1->unk24);
            spA0 = (f32) ((f64) (arg1->unk30 - arg1->unk28) * ((f64) i * 0.0800000000000000017) + (f64) arg1->unk28);
            guTranslateF(spE8, -48.0f, -32.0f, 0.0f);
            scale = (f32) (((f64) i * 0.0800000000000000017) * 1.9f * 4.0 * 0.5);
            guScaleF(spA8, scale, scale, 1.0f);
            guMtxCatF(spE8, spA8, spE8);
            func_806A3DA0(&spA4, &spA0, (f32) ((f64) i * 0.0800000000000000017), 1.0f, (M7Angle *) arg1);
            guTranslateF(spA8, spA4 * 4.0f, spA0 * 4.0f, 0.0f);
            guMtxCatF(spE8, spA8, spE8);
            off = idx * 2;
            guMtxF2L(spE8, (Mtx *) (arg1->unk34 + ((off + D_807444FC) << 6)));
            ret = func_806A3C6C(ret, arg1->unk34 + ((off + D_807444FC) << 6), (u32) ((((f64) (idx * 300) * 0.0800000000000000017) > 150.0) ? 150.0 : ((f64) (idx * 300) * 0.0800000000000000017)) & 0xFF, arg2);
            i = (i + 1) & 0xFF;
            idx = i;
        } while (cnt >= idx);
    }
    return ret;
}
