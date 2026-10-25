// func_806FA1A4 (src/global/FCCD0.c): Stage 1 m2c reconstruction; batched display-list layout requires typed per-player buffer.
s32 func_805FF030(u8, ?);                           /* extern */
f32 func_80612794(f32, s16);                        /* extern */
s32 func_806C8DE0(?);                               /* extern */
void *func_806F9D8C(f32, s32, void *, void *);      /* extern */
s8 func_8073110C(f32, s16, ?);                      /* extern */
extern ? D_2000180;
extern ? D_807505AE;
extern s32 D_80754280;
extern u8 D_8076A0AB;
extern ? D_807FC992;
extern ? D_807FD7A0;
extern ? D_807FD7B8;
extern ? D_807FD7D0;
extern u8 D_807FD7E4;

void *func_806FA1A4(s32 arg0, void *arg1, void *arg2) {
    s32 sp88;
    s32 sp84;
    f32 sp80;
    f32 sp7C;
    s32 sp70;
    f32 temp_fa0;
    f32 temp_ft3;
    f32 var_fa0;
    f32 var_fs1;
    f64 temp_fv0;
    f64 temp_fv1;
    s32 temp_s5;
    s32 temp_v0;
    s32 temp_v0_2;
    s32 temp_v1;
    s32 var_s0;
    s8 var_v1;
    void *temp_fp;
    void *temp_v0_3;
    void *var_s4;

    temp_fp = arg1->unk14;
    var_s4 = arg2;
    sp70 = func_805FF030(D_8076A0AB, 1);
    temp_v0 = func_806C8DE0(0);
    temp_s5 = arg0 * 0x30;
    sp88 = (s32) (D_80754280 + temp_s5)->unk4;
    temp_v1 = temp_fp->unk4;
    sp84 = temp_v1;
    temp_ft3 = (f32) ((f64) temp_fp->unk0 * 4.0);
    sp80 = temp_ft3;
    temp_fa0 = (f32) ((f64) temp_v1 * 4.0);
    sp7C = temp_fa0;
    var_s0 = 0;
    var_fa0 = (f32) ((f64) temp_fa0 + 92.0);
    sp80 = (f32) ((f64) temp_ft3 - (4.0 * (6.0 - ((1.0 - (f64) func_80612794(temp_fa0, arg1->unk10)) * (f64) arg1->unk4))));
    do {
        var_v1 = 1;
        if (var_s0 > 0) {
            sp7C = var_fa0;
            var_v1 = func_8073110C(var_fa0, *(&D_807505AE + (var_s0 * 2)), 0);
        }
        if (var_v1 != 0) {
            temp_v0_2 = var_s0 * 4;
            if (var_s0 == temp_v0) {
                var_fs1 = 2.0f;
                (D_80754280 + temp_s5)->unk4 = (s16) sp88;
            } else {
                var_fs1 = 1.5f;
                (D_80754280 + temp_s5)->unk4 = (u16) *(&D_807FC992 + ((var_s0 * 0x5E) + (sp70 * 2)));
            }
            sp7C = var_fa0;
            temp_v0_3 = func_806F9D8C(var_fa0, arg0, arg1, var_s4);
            var_s4 = temp_v0_3;
            if (var_s0 != temp_v0) {
                temp_v0_3->unk0 = 0xFA000000;
                var_s4 = temp_v0_3 + 8;
                temp_v0_3->unk4 = (s32) (((s32) D_807FD7E4 >> 1) & 0xFF);
            }
            temp_fv0 = (f64) var_fs1;
            temp_fv1 = (f64) var_fa0;
            *(temp_v0_2 + &D_807FD7A0) = (f32) ((f64) sp80 - (10.0 * temp_fv0));
            *(temp_v0_2 + &D_807FD7B8) = (f32) (temp_fv1 - (30.0 * temp_fv0));
            var_fa0 = (f32) (temp_fv1 + 136.0);
            *(temp_v0_2 + &D_807FD7D0) = (f32) (temp_fv0 * 1.15);
            temp_fp->unk4 = (s32) (temp_fp->unk4 + 0x22);
        }
        var_s0 += 1;
    } while (var_s0 != 5);
    (D_80754280 + temp_s5)->unk4 = (s16) sp88;
    temp_fp->unk4 = sp84;
    var_s4->unk0 = 0xDA380003;
    var_s4->unk4 = &D_2000180;
    return var_s4 + 8;
}
