// func_807069A4 (src/global/109660.c): Stage 2 compiled behavior reconstruction; m2c starter records matrix, clip, and draw-loop structure.
s32 func_8066B0F8(?, ?, ?, ?);                      /* extern */
? func_80702464(void **, s32, ?, u32, u32, s32, s32, f32, f32, f32, f32, f32, f32, s32, s32); /* extern */
? func_807063B8(f32, f32, f32 *, u8 *, ?, f32);     /* extern */
? func_807065F8(s16, u8 *, u8 *, u8 *);             /* extern */
extern u8 D_807444FC;
extern f32 D_80754CE4;
extern void *D_807FC924;
extern s32 D_807FD8A0;
extern ? D_807FD8A8;
extern ? D_807FD928;

void *func_807069A4(void *arg0, f32 arg1, f32 arg2, ? arg3, f32 arg4, f32 arg5) {
    f32 sp140;
    f32 sp13C;
    f32 sp138;
    f32 sp134;
    f32 sp130;
    f32 sp12C;
    u8 sp12B;
    u8 sp9B;
    u8 sp9A;
    u8 sp99;
    f32 sp94;
    f32 sp68;
    f32 *var_s0;
    f32 temp_fa0;
    f32 temp_fa1;
    f32 temp_ft2;
    f32 temp_ft4;
    f32 temp_ft5;
    f32 temp_fv0;
    f32 temp_fv1;
    f32 var_fa0;
    f32 var_fv1;
    s32 var_s1;
    void *temp_s2;
    void *temp_s3;
    void *temp_t0;
    void *temp_t1;
    void *temp_t2;
    void *temp_t5;
    void *temp_t5_2;
    void *temp_t6;
    void *temp_t9;
    void *temp_t9_2;
    void *temp_v0;

    temp_fv0 = 5.6f / D_80754CE4;
    temp_s3 = D_807FC924->unk4;
    temp_s2 = temp_s3->unk174;
    sp94 = temp_fv0;
    guScaleF((f32 (*)[4]) &spDC[0], temp_fv0, temp_fv0, temp_fv0);
    guTranslateF((f32 (*)[4]) &sp9C[0], -2560.0f, -1920.0f, 0.0f);
    guMtxCatF((f32 (*)[4]) &spDC[0], (f32 (*)[4]) &sp9C[0], (f32 (*)[4]) &spDC[0]);
    guRotateF((f32 (*)[4]) &sp9C[0], (f32) ((0x1000 - temp_s2->unk104->unkE4) & 0xFFF) * 0.087890625f, 0.0f, 0.0f, 1.0f);
    guMtxCatF((f32 (*)[4]) &spDC[0], (f32 (*)[4]) &sp9C[0], (f32 (*)[4]) &spDC[0]);
    guTranslateF((f32 (*)[4]) &sp9C[0], 2560.0f, 1920.0f, 0.0f);
    guMtxCatF((f32 (*)[4]) &spDC[0], (f32 (*)[4]) &sp9C[0], (f32 (*)[4]) &spDC[0]);
    guMtxF2L((f32 (*)[4]) &spDC[0], &D_807FD8A8 + (D_807444FC << 6));
    arg1 = 6.2831855f - arg1;
    arg2 = (arg4 / arg5) * (6.2831855f - arg2);
    if (D_807FD8A0 == 0) {
        D_807FD8A0 = func_8066B0F8(0xE, arg3, 0, 0);
    }
    temp_t5 = arg0;
    arg0 = temp_t5 + 8;
    temp_t5->unk0 = 0xDA380003;
    temp_t5->unk4 = (void *) (&D_807FD8A8 + (D_807444FC << 6));
    temp_t1 = arg0;
    arg0 = temp_t1 + 8;
    temp_t1->unk4 = &D_807FD928;
    temp_t1->unk0 = 0xDA380007;
    temp_t5_2 = arg0;
    arg0 = temp_t5_2 + 8;
    temp_t5_2->unk4 = 0;
    temp_t5_2->unk0 = 0xE7000000;
    temp_t9 = arg0;
    arg0 = temp_t9 + 8;
    temp_t9->unk4 = 0x404240;
    temp_t9->unk0 = 0xE200001C;
    temp_t2 = arg0;
    arg0 = temp_t2 + 8;
    temp_t2->unk4 = -0x805;
    temp_t2->unk0 = 0xFC11FE23;
    temp_t6 = arg0;
    arg0 = temp_t6 + 8;
    temp_t6->unk4 = 0;
    temp_t6->unk0 = 0xE3000A01;
    func_807065F8((s16) (s32) temp_s3->unk80, &sp9B, &sp9A, &sp99);
    temp_v0 = arg0;
    arg0 = temp_v0 + 8;
    temp_v0->unk0 = 0xFA000000;
    temp_v0->unk4 = (s32) ((sp9B << 0x18) | (sp9A << 0x10) | (sp99 << 8) | 0xFF);
    temp_t9_2 = arg0;
    arg0 = temp_t9_2 + 8;
    temp_t9_2->unk4 = 0;
    temp_t9_2->unk0 = 0xD9000000;
    temp_t0 = arg0;
    arg0 = temp_t0 + 8;
    temp_t0->unk4 = 0x200004;
    temp_t0->unk0 = 0xD9FFFFFF;
    var_fv1 = arg1 * 0.15915494f * D_80754CE4;
    var_fa0 = arg2 * 0.15915494f * D_80754CE4;
    temp_fa1 = 1.0f / sp94;
    if (var_fv1 > 1.0f) {
        do {
            var_fv1 -= 1.0f;
        } while (var_fv1 > 1.0f);
    }
    if (var_fa0 > 1.0f) {
        do {
            var_fa0 -= 1.0f;
        } while (var_fa0 > 1.0f);
    }
    temp_fv1 = var_fv1 * arg4;
    temp_fa0 = var_fa0 * arg5;
    sp12B = 1;
    temp_ft4 = 460.0f * temp_fa1 * 0.5f;
    sp12C = temp_fv1 - temp_ft4;
    temp_ft5 = 380.0f * temp_fa1 * 0.5f;
    sp134 = temp_ft4 + temp_fv1;
    sp130 = temp_fa0 - temp_ft5;
    sp138 = temp_ft5 + temp_fa0;
    temp_ft2 = -70.0f * temp_fa1;
    sp68 = temp_ft2;
    sp13C = temp_ft2;
    sp140 = temp_ft2;
    func_807063B8(temp_fa0, temp_fa1, &sp12C, &sp12B, 0, arg4);
    func_807063B8((bitwise f32) &sp12C, (bitwise f32) &sp12B, (f32 *)1, (bitwise u8 *) arg5);
    var_s1 = 0;
    if ((s32) sp12B > 0) {
        var_s0 = &sp12C;
        do {
            func_80702464(&arg0, D_807FD8A0, 0, (u32) arg4, (u32) arg5, 0x20, 0x20, var_s0->unk0, var_s0->unk4, var_s0->unk8, var_s0->unkC, var_s0->unk10, var_s0->unk14, 0x10, 0x10);
            var_s1 += 1;
            var_s0 += 0x18;
        } while (var_s1 < (s32) sp12B);
    }
    return arg0;
}
