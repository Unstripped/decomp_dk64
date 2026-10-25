// func_80700BF4 (src/global/103AB0.c): Stage 1 m2c behavioral draft; compiled attempts recorded where applicable.
s16 func_807009F4(s16);                             /* extern */
s16 func_80700AE4(s16, s16, s16);                   /* extern */
extern u8 D_807444FC;
extern u8 D_80754BC0;
extern s32 D_807FBB60;
extern void *D_807FC924;
extern u8 D_807FC928;
extern ? D_807FD610;
extern s16 D_807FD800;
extern s16 D_807FD802;
extern s16 D_807FD804;
extern s16 D_807FD806;
extern ? D_807FD838;
extern ? D_807FD840;

void func_80700BF4(void) {
    f32 temp_fv0;
    f32 temp_fv1;
    f64 var_ft5;
    s16 temp_s1;
    s16 temp_s3;
    s16 var_a2;
    s32 temp_t4;
    s32 temp_t8;
    s32 var_s4;
    u8 temp_t2;
    u8 temp_t9;
    u8 var_v1;
    void *temp_a0;
    void *temp_s0;
    void *temp_v0;
    void *temp_v1;
    void *var_a1;

    var_v1 = D_80754BC0;
    if (var_v1 != 0) {
        var_a1 = (D_807444FC * 0x24) + &D_807FD840;
        do {
            temp_t9 = var_v1 - 1;
            D_80754BC0 = temp_t9;
            var_v1 = temp_t9 & 0xFF;
            temp_a0 = var_a1 + (var_v1 * 0xC);
            temp_fv1 = temp_a0->unk0;
            if (((f32) D_807FC924->unk270 < temp_fv1) && (temp_fv1 < (f32) D_807FC924->unk274)) {
                temp_fv0 = temp_a0->unk4;
                if (((f32) D_807FC924->unk272 < temp_fv0) && (temp_fv0 < (f32) D_807FC924->unk276) && !(D_807FBB60 & 2)) {
                    var_v1 = D_80754BC0;
                    var_a1 = &D_807FD840 + (D_807444FC * 0x24);
                    if ((var_a1 + (var_v1 * 0xC))->unk8 < (f32) func_807009F4(func_80700AE4((s16) (s32) temp_fv1, (s16) (s32) temp_fv0))) {
                        *(&D_807FD838 + (D_807444FC * 3) + var_v1) = 5;
                    }
                }
            }
        } while (var_v1 != 0);
    }
    var_a2 = func_80700AE4(0xA0, 0xDC) == 0x7FFF;
    if (var_a2 == 0) {
        var_a2 = func_80700AE4(0xC, 0x78, var_a2) == 0x7FFF;
        if (var_a2 == 0) {
            var_a2 = func_80700AE4(0x134, 0x78, var_a2) == 0x7FFF;
        }
    }
    D_807FD800 = var_a2;
    D_807FD802 = func_807009F4(func_80700AE4(D_807FD804, D_807FD806, var_a2));
    var_s4 = 0;
    if ((s32) D_807FC928 > 0) {
        do {
            temp_v1 = D_807FC924 + (var_s4 * 0x2F0);
            if (temp_v1->unk0 != 0) {
                temp_s0 = temp_v1->unk4->unk174;
                temp_v0 = &D_807FD610 + (var_s4 * 0x34);
                temp_t2 = temp_v0->unk30;
                temp_s3 = temp_s0->unk110 - 0x14;
                temp_s1 = temp_s0->unk10E + temp_v0->unk2E;
                var_ft5 = (f64) temp_t2;
                if ((s32) temp_t2 < 0) {
                    var_ft5 += 4294967296.0;
                }
                temp_t4 = (u32) ((f64) 0x28 + (var_ft5 / 1.5)) & 0xFFFF;
                temp_s0->unk114 = func_807009F4(func_80700AE4(temp_s1, temp_s3));
                temp_s0->unk116 = func_807009F4(func_80700AE4(temp_s1, temp_s0->unk112));
                temp_s0->unk118 = func_807009F4(func_80700AE4((s16) (temp_s1 - temp_t4), temp_s3));
                temp_s0->unk11A = func_807009F4(func_80700AE4((s16) (temp_s1 + temp_t4), temp_s3));
            }
            temp_t8 = (var_s4 + 1) & 0xFF;
            var_s4 = temp_t8;
        } while (temp_t8 < (s32) D_807FC928);
    }
}
