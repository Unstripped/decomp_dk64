// func_80723F88 (src/global/127B00.c): stage 1 m2c recovery; needs local Uc1 array view and codegen refinement
? func_80627B58(?);                                 /* extern */
f32 func_80724308(s32, ?, s32, s32, s32, f32);      /* extern */
extern ? D_807FDB90;

void func_80723F88(s32 arg0, ? arg1, s32 arg2, s32 arg3, s32 *arg4, f32 *arg5) {
    s32 sp68;
    f32 temp_fv0;
    f32 temp_fv0_2;
    f32 var_fs2;
    f32 var_fs3;
    f64 temp_fs0;
    s32 temp_s1_2;
    s32 temp_v0;
    s32 var_s0;
    s32 var_s0_2;
    void **temp_s1;

    var_fs3 = 999999.0f;
    var_fs2 = 0.0f;
    func_80627B58(0x3F000000);
    temp_s1 = (arg0 * 4) + &D_807FDB90;
    var_s0 = 0;
    if ((*temp_s1)->unk4 > 0) {
        do {
            temp_fv0 = func_80724308(arg0, arg1, arg2, arg3, var_s0, 0.0f);
            if (temp_fv0 < var_fs3) {
                sp68 = var_s0;
                *arg4 = var_s0;
                *arg5 = 0.0f;
                var_fs3 = temp_fv0;
            }
            var_s0 += 1;
        } while (var_s0 < (*temp_s1)->unk4);
    }
    temp_v0 = sp68 - 1;
    if (temp_v0 < 0) {
        var_s0_2 = 0;
    } else {
        var_s0_2 = temp_v0;
    }
    temp_s1_2 = sp68 + 1;
    if (temp_s1_2 >= var_s0_2) {
        do {
            temp_fv0_2 = func_80724308(arg0, arg1, arg2, arg3, var_s0_2, var_fs2);
            if (temp_fv0_2 < var_fs3) {
                *arg4 = var_s0_2;
                *arg5 = var_fs2;
                var_fs3 = temp_fv0_2;
            }
            var_fs2 = (f32) ((f64) var_fs2 + 0.005);
            temp_fs0 = (f64) var_fs2;
            if (temp_fs0 >= 1.0) {
                var_s0_2 += 1;
                var_fs2 = (f32) (temp_fs0 - 1.0);
            }
        } while (temp_s1_2 >= var_s0_2);
    }
}
