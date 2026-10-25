// func_80708DA4 (src/global/10D2D0.c): Stage 1 m2c behavioral starter; 360-instruction state handler needs local views and compiler cleanup.
s32 func_805FCA64();                                /* extern */
f32 func_80612D1C(f32, ?, void *);                  /* extern */
s32 func_806C8DE0(s16);                             /* extern */
s32 func_807085D0(s32, void *, void *, void *);     /* extern */
? func_80708C24(s16, void *, void *, void *);       /* extern */
extern u8 D_807FC928;
extern ? D_807FC950;

s32 func_80708DA4(s32 arg0, s16 arg1, void *arg2) {
    void *sp38;
    u8 sp37;
    void *sp28;
    s32 sp24;
    f64 var_ft0;
    f64 var_ft1;
    f64 var_ft3;
    f64 var_ft5;
    s32 temp_a0;
    u16 temp_t3_3;
    u8 temp_t3;
    u8 temp_t3_2;
    u8 temp_t4;
    u8 temp_t5;
    u8 temp_v0;
    u8 temp_v0_2;
    u8 var_t0;
    void *temp_t9;

    temp_t9 = (arg1 * 0x306) + &D_807FC950;
    sp38 = temp_t9 + (func_806C8DE0(arg1) * 0x5E);
    sp28 = temp_t9;
    temp_a0 = D_807FC928 == 1;
    var_t0 = arg2->unk2E4;
    if (temp_a0 == 0) {
        var_t0 = 0;
    }
    if (temp_a0 == 0) {
        sp37 = var_t0;
        func_80708C24(arg1, arg2, sp28, sp38);
        arg2->unk2E2 = (u16) (arg2->unk2E2 & 0xFFEA);
    }
    if ((s32) arg2->unk2E3 & 0x10) {
        switch (var_t0) {                           /* switch 1; irregular */
        case 2:                                     /* switch 1 */
            arg2->unk2E5 = 0x32U;
            break;
        case 3:                                     /* switch 1 */
            temp_t3 = arg2->unk2E5;
            var_ft1 = (f64) temp_t3;
            if ((s32) temp_t3 < 0) {
                var_ft1 += 4294967296.0;
            }
            arg2->unk2E5 = (u8) (u32) (18.0 - var_ft1);
            arg2->unk2E4 = 1U;
            break;
        }
    }
    if ((s32) arg2->unk2E3 & 1) {
        arg2->unk2E2 = (u16) (arg2->unk2E2 ^ 1);
        switch (var_t0) {                           /* switch 2; irregular */
        case 1:                                     /* switch 2 */
            break;
        case 0:                                     /* switch 2 */
            arg2->unk2E5 = 0x12U;
            arg2->unk2E4 = 1U;
            break;
        case 3:                                     /* switch 2 */
            temp_t3_2 = arg2->unk2E5;
            var_ft0 = (f64) temp_t3_2;
            if ((s32) temp_t3_2 < 0) {
                var_ft0 += 4294967296.0;
            }
            arg2->unk2E5 = (u8) (u32) (18.0 - var_ft0);
            arg2->unk2E4 = 1U;
            break;
        }
    } else if ((s32) arg2->unk2E3 & 4) {
        arg2->unk2E5 = 1U;
        arg2->unk2E4 = 2U;
        temp_t3_3 = arg2->unk2E2 ^ 4;
        arg2->unk2E2 = temp_t3_3;
        arg2->unk2E2 = (u16) (temp_t3_3 & 8);
    } else {
        switch (var_t0) {                           /* switch 3; irregular */
        case 1:                                     /* switch 3 */
            temp_t5 = arg2->unk2E5;
            var_ft5 = (f64) temp_t5;
            if ((s32) temp_t5 < 0) {
                var_ft5 += 4294967296.0;
            }
            sp24 = (s32) arg2->unk2E3;
            temp_v0 = arg2->unk2E5;
            arg2->unk2E0 = (s16) (u32) ((f64) func_80612D1C((f32) (((var_ft5 / 18.0) * 1.5707963705062866) + 1.5707963705062866), 3) * 65535.0);
            arg2->unk2E5 = (u8) (temp_v0 - 1);
            if (temp_v0 == 0) {
                arg2->unk2E4 = 2U;
                arg2->unk2E5 = 0x32U;
            }
            break;
        case 2:                                     /* switch 3 */
            sp24 = (s32) arg2->unk2E3;
            func_80708C24(arg1, arg2, sp28, sp38);
            break;
        case 3:                                     /* switch 3 */
            temp_t4 = arg2->unk2E5;
            var_ft3 = (f64) temp_t4;
            if ((s32) temp_t4 < 0) {
                var_ft3 += 4294967296.0;
            }
            sp24 = (s32) arg2->unk2E3;
            temp_v0_2 = arg2->unk2E5;
            arg2->unk2E0 = (s16) (u32) ((f64) func_80612D1C((f32) ((1.5707963705062866 - ((var_ft3 / 18.0) * 1.5707963705062866)) + 1.5707963705062866), 3, arg2) * 65535.0);
            arg2->unk2E5 = (u8) (temp_v0_2 - 1);
            if (temp_v0_2 == 0) {
                arg2->unk2E4 = 0U;
            }
            break;
        }
    }
    sp24 = (s32) arg2->unk2E3;
    if (((func_805FCA64() != 0) || ((s32) arg2->unk2E3 & 0x80)) && ((arg2->unk2E4 != 0) || (arg2->unk2E2 != 0))) {
        arg0 = func_807085D0(arg0, sp28, sp38, arg2);
    }
    return arg0;
}
