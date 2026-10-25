// func_80703CF8 (src/global/103AB0.c): Compiled display-list and matrix draft; frame, rodata placement, and call ordering remain unmatched.
? assetFreeBuffer(s32, ?, ?);                       /* extern */
Mtx *func_80610FE8(?);                              /* extern */
? func_80612CA0(f32 (*)[4], f32);                   /* extern */
f32 func_80612D1C(f32, f64, void *, void *, void *); /* extern */
s32 func_8066B0F8(?, ?, ?, ?);                      /* extern */
? heapFreeDeferred(Mtx *);                          /* extern */
extern ? D_1000118;
extern ? D_2000080;
extern s16 D_80744490;
extern s16 D_80744494;
extern u8 D_8074450C;
extern ? D_80754C08;

void *func_80703CF8(void *arg0, u8 arg1) {
    Mtx *spFC;
    f64 sp20;
    Mtx *temp_v0_2;
    f32 temp_ft5;
    f32 temp_fv1;
    f32 var_ft2;
    f64 temp_fa1;
    f64 var_ft1;
    s32 temp_v0;
    void *temp_s0;
    void *temp_s0_10;
    void *temp_s0_11;
    void *temp_s0_12;
    void *temp_s0_13;
    void *temp_s0_14;
    void *temp_s0_15;
    void *temp_s0_16;
    void *temp_s0_17;
    void *temp_s0_2;
    void *temp_s0_3;
    void *temp_s0_4;
    void *temp_s0_5;
    void *temp_s0_6;
    void *temp_s0_7;
    void *temp_s0_8;
    void *temp_s0_9;
    void *var_s0;

    var_s0 = arg0;
    if (arg1 != 0) {
        temp_v0 = func_8066B0F8(0xE, 0x5F, 0, 0);
        assetFreeBuffer(temp_v0, 0x540, 0x2F);
        temp_v0_2 = func_80610FE8(0x40);
        spFC = temp_v0_2;
        heapFreeDeferred(temp_v0_2);
        temp_s0 = var_s0 + 8;
        var_s0->unk0 = 0xDE000000;
        var_s0->unk4 = &D_1000118;
        temp_s0_2 = temp_s0 + 8;
        var_s0->unk8 = 0xE200001C;
        temp_s0->unk4 = 0x504340;
        temp_s0_3 = temp_s0_2 + 8;
        temp_s0_2->unk4 = 0xFF2FFFFF;
        temp_s0->unk8 = 0xFC121624;
        temp_s0_4 = temp_s0_3 + 8;
        temp_s0_3->unk4 = 0xFF;
        temp_s0_2->unk8 = 0xFA000000;
        temp_s0_5 = temp_s0_4 + 8;
        temp_s0_4->unk4 = -1;
        temp_s0_3->unk8 = 0xD7000002;
        temp_s0_6 = temp_s0_5 + 8;
        temp_s0_5->unk4 = 0x2000;
        temp_s0_4->unk8 = 0xE3001201;
        temp_s0_7 = temp_s0_6 + 8;
        temp_s0_5->unk8 = 0xFD900000;
        temp_s0_8 = temp_s0_7 + 8;
        temp_s0_6->unk4 = (s32) (temp_v0 + 0x80000000);
        temp_s0_6->unk8 = 0xF5900000;
        temp_s0_7->unk4 = 0x07080200;
        temp_s0_9 = temp_s0_8 + 8;
        temp_s0_7->unk8 = 0xE6000000;
        temp_s0_8->unk4 = 0;
        temp_s0_10 = temp_s0_9 + 8;
        temp_s0_8->unk8 = 0xF3000000;
        temp_s0_11 = temp_s0_10 + 8;
        temp_s0_9->unk4 = 0x073FF200;
        temp_s0_9->unk8 = 0xE7000000;
        temp_s0_12 = temp_s0_11 + 8;
        temp_s0_10->unk4 = 0;
        temp_s0_10->unk8 = 0xF5800800;
        temp_s0_11->unk4 = 0x80200;
        temp_s0_13 = temp_s0_12 + 8;
        temp_s0_11->unk8 = 0xF2000000;
        temp_s0_12->unk4 = 0xFC0FC;
        temp_s0_13->unk4 = &D_2000080;
        temp_s0_12->unk8 = 0xDA380007;
        temp_s0_14 = temp_s0_13 + 8;
        var_ft1 = (f64) arg1;
        if ((s32) arg1 < 0) {
            var_ft1 += 4294967296.0;
        }
        temp_fa1 = var_ft1 / 255.0;
        sp20 = temp_fa1;
        var_ft2 = (f32) D_8074450C;
        temp_ft5 = (f32) ((f64) ((f32) ((f64) func_80612D1C((f32) ((temp_fa1 * 1.5707963705062866) + 3.1415927410125732), temp_fa1, temp_s0_12, temp_s0_13, temp_s0_9) + 1.0) * 40.0f) + 1.4);
        if ((s32) D_8074450C < 0) {
            var_ft2 += 4294967296.0f;
        }
        temp_fv1 = temp_ft5 * var_ft2;
        guScaleF((f32 (*)[4]) &spBC[0], temp_fv1, temp_fv1, temp_fv1);
        func_80612CA0((f32 (*)[4]) &sp7C[0], (f32) (sp20 * 360.0 * 1.5));
        guMtxCatF((f32 (*)[4]) &spBC[0], (f32 (*)[4]) &sp7C[0], (f32 (*)[4]) &spBC[0]);
        guTranslateF((f32 (*)[4]) &sp7C[0], (f32) ((s16) D_80744490 >> 1), (f32) ((s16) D_80744494 >> 1), 0.0f);
        guMtxCatF((f32 (*)[4]) &spBC[0], (f32 (*)[4]) &sp7C[0], (f32 (*)[4]) &spBC[0]);
        guMtxF2L((f32 (*)[4]) &spBC[0], spFC);
        temp_s0_13->unk8 = 0xDA380003;
        temp_s0_15 = temp_s0_14 + 8;
        temp_s0_14->unk4 = spFC;
        temp_s0_14->unk8 = 0x01004008;
        temp_s0_16 = temp_s0_15 + 8;
        temp_s0_15->unk4 = osVirtualToPhysical(&D_80754C08);
        temp_s0_17 = temp_s0_16 + 8;
        temp_s0_16->unk4 = 0x406;
        temp_s0_15->unk8 = 0x06000204;
        temp_s0_16->unk8 = 0xE7000000;
        temp_s0_17->unk4 = 0;
        var_s0 = temp_s0_17 + 8;
    }
    return var_s0;
}
