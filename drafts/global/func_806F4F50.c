// func_806F4F50 (src/global/F9450.c): stage 1: m2c reconstruction retained for later type recovery
s32 func_806F4EBC(f32, f32, s16, s16 **, s32, s32); /* extern */
extern s32 D_80754244;
extern s16 D_807FD720;

void func_806F4F50(s16 arg0, s16 **arg1, f32 arg2, s32 arg3) {
    s16 *sp1C;
    s16 **var_a1;
    s16 *var_v0;
    s16 *var_v1;
    s32 temp_a0;
    s32 temp_v0;
    s32 var_a2;
    s32 var_a3;
    s32 var_t0;

    var_a1 = arg1;
    var_a3 = arg3;
    var_a2 = 0;
    var_t0 = 0;
    if (D_807FD720 > 0) {
        var_a3 = 0 * 4;
loop_2:
        var_v0 = NULL;
        var_a2 += 1;
        var_a1 = D_80754244 + var_a3;
        var_v1 = *var_a1;
        var_a3 += 4;
        if ((var_v1 != NULL) && (arg0 != *var_v1)) {
loop_4:
            var_v0 = var_v1;
            var_v1 = var_v1->unk18;
            if (var_v1 != NULL) {
                if (arg0 != *var_v1) {
                    goto loop_4;
                }
            }
        }
        if ((var_v1 != NULL) && (arg0 == var_v1->unk0)) {
            var_t0 = 1;
            if (var_v0 != NULL) {
                var_v0->unk18 = (s16 *) var_v1->unk18;
            } else {
                *var_a1 = var_v1->unk18;
            }
        }
        sp1C = var_v1;
        if (var_t0 == 0) {
            if (var_a2 >= D_807FD720) {
                sp1C = var_v1;
            } else {
                goto loop_2;
            }
        }
    }
    temp_v0 = func_806F4EBC((bitwise f32) arg1, (bitwise f32) arg3, arg0, var_a1, var_a2, var_a3);
    if ((D_807FD720 >= temp_v0) && (temp_v0 >= 0)) {
        temp_a0 = temp_v0 * 4;
        sp1C->unk18 = (s32) *(D_80754244 + temp_a0);
        *(D_80754244 + temp_a0) = sp1C;
        sp1C->unk8 = (s16) (s32) arg1;
        sp1C->unkA = (s16) (s32) arg2;
        sp1C->unkC = (s16) (s32) arg3;
    }
}
