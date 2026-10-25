// func_8070033C (src/global/103AB0.c): Stage 1 m2c behavioral draft; compiled attempts recorded where applicable.
? func_80612970(f32 *, s32, s32, s32);              /* extern */
? func_80626F8C(f32, f32, f32, f32 *, f32 *, s32, f32, s32); /* extern */
extern u8 D_807444FC;
extern u8 D_80754BC0;
extern void *D_807FC924;
extern ? D_807FD808;
extern ? D_807FD840;
extern ? D_807FD848;

void func_8070033C(f32 arg0, f32 arg1, f32 arg2, f32 arg3, f32 arg4, f32 arg5, f32 arg6, u8 arg7, u8 arg8, u8 arg9) {
    f32 sp84;
    f32 sp80;
    u8 sp7F;
    f32 sp78;
    f32 sp74;
    f32 sp70;
    f32 sp64;
    f32 sp58;
    f32 temp_fa1;
    f32 temp_fa1_2;
    f32 temp_fv0;
    f32 temp_fv0_2;
    f32 temp_fv1;
    f32 temp_fv1_2;
    f32 var_fv1;
    u8 var_v1;
    void *temp_a0;
    void *temp_v0;

    if ((s32) D_80754BC0 < 2) {
        var_v1 = 1;
        if (arg6 != 0.0f) {
            sp70 = arg3 - arg0;
            sp74 = arg4 - arg1;
            sp78 = arg5 - arg2;
            sp7F = 1;
            func_80612970(&sp58, subroutine_arg1, sp70.unk4, sp70.unk8);
            sp70 = D_807FC924->unk210 - arg0;
            sp74 = D_807FC924->unk214 - arg1;
            sp78 = D_807FC924->unk218 - arg2;
            func_80612970(&sp64, subroutine_arg1, sp70.unk4, sp70.unk8);
            var_v1 = sp7F;
            var_fv1 = (sp64 * sp58) + (sp68 * sp5C) + (sp6C * sp60);
            if ((f64) var_fv1 < 0.0) {
                var_fv1 = 0.0f;
            }
            if (var_fv1 < arg6) {
                var_v1 = 0;
            }
        }
        if (var_v1 != 0) {
            temp_fv1 = D_807FC924->unk21C - arg0;
            temp_fa1 = D_807FC924->unk220 - arg1;
            temp_fv0 = D_807FC924->unk224 - arg2;
            if (sqrtf((temp_fv0 * temp_fv0) + ((temp_fv1 * temp_fv1) + (temp_fa1 * temp_fa1))) > 995.0f) {
                *(&D_807FD848 + ((D_807444FC * 0x24) + (D_80754BC0 * 0xC))) = 995.0f;
            } else {
                temp_fv1_2 = D_807FC924->unk21C - arg0;
                temp_fa1_2 = D_807FC924->unk220 - arg1;
                temp_fv0_2 = D_807FC924->unk224 - arg2;
                *(&D_807FD848 + ((D_807444FC * 0x24) + (D_80754BC0 * 0xC))) = sqrtf((temp_fv0_2 * temp_fv0_2) + ((temp_fv1_2 * temp_fv1_2) + (temp_fa1_2 * temp_fa1_2)));
            }
            func_80626F8C(arg0, arg1, arg2, &sp84, &sp80, 0, 4.0f, 0);
            temp_v0 = (D_80754BC0 * 0x10) + &D_807FD808;
            temp_a0 = (D_807444FC * 0x24) + (D_80754BC0 * 0xC) + &D_807FD840;
            temp_a0->unk0 = (f32) ((f64) sp84 * 0.25);
            temp_a0->unk4 = (f32) ((f64) sp80 * 0.25);
            temp_v0->unk0 = arg0;
            temp_v0->unk4 = arg1;
            temp_v0->unk8 = arg2;
            temp_v0->unkC = arg7;
            temp_v0->unkD = arg8;
            temp_v0->unkE = arg9;
            D_80754BC0 += 1;
        }
    }
}
