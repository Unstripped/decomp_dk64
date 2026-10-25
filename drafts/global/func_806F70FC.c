// func_806F70FC (src/global/F9450.c): Stage 1 m2c starter; reviewed 160-instruction randomized-vector target.
u32 func_806119A0();                                /* extern */
? func_80714950(?);                                 /* extern */
? func_8071496C(s16);                               /* extern */
? func_8071498C(? *);                               /* extern */
? func_807149B8(?);                                 /* extern */
? func_80714CC0(? *, ?, f32, f32, f32);             /* extern */
extern ? D_8071FC58;
extern ? func_8071C48C;
extern ? func_8071C620;

void func_806F70FC(f32 arg0, f32 arg1, f32 arg2, ? arg3, f32 arg4, s32 arg5) {
    f32 var_ft0;
    f32 var_ft0_2;
    f32 var_ft1;
    f64 temp_fs0;
    s16 temp_s0;
    s16 var_s1;
    u32 temp_hi;
    u32 temp_hi_2;
    u32 temp_hi_3;

    func_80714950(0x1006E);
    func_8071498C(&func_8071C48C);
    func_807149B8(1);
    func_80714CC0(&D_8071FC58, arg3, arg0, arg1, arg2);
    var_s1 = 0;
    if (arg5 > 0) {
        temp_fs0 = 1000.0 / ((f64) arg4 + (f64) arg4);
        do {
            temp_hi = (u32) (func_806119A0() / 10000U) % 1000U;
            var_ft0 = (f32) temp_hi;
            if ((s32) temp_hi < 0) {
                var_ft0 += 4294967296.0f;
            }
            temp_hi_2 = (u32) (func_806119A0() / 10000U) % 1000U;
            var_ft1 = (f32) temp_hi_2;
            if ((s32) temp_hi_2 < 0) {
                var_ft1 += 4294967296.0f;
            }
            temp_hi_3 = (u32) (func_806119A0() / 10000U) % 1000U;
            var_ft0_2 = (f32) temp_hi_3;
            if ((s32) temp_hi_3 < 0) {
                var_ft0_2 += 4294967296.0f;
            }
            func_8071498C(&func_8071C620);
            temp_s0 = var_s1 + 1;
            func_8071496C(temp_s0);
            func_807149B8(1);
            func_80714CC0(&D_8071FC58, arg3, arg0 + (f32) ((f64) (var_ft0 / arg4) - temp_fs0), arg1 + (f32) ((f64) (var_ft1 / arg4) - temp_fs0), arg2 + (f32) ((f64) (var_ft0_2 / arg4) - temp_fs0));
            var_s1 = temp_s0;
        } while (temp_s0 != arg5);
    }
}
