// func_80652BC8 (src/global/55B20.c): not attempted in C; m2c starter only (needs struct field/register work, stage 0)
u8 func_80630324(?, ?);                             /* extern */
s32 func_80668E9C(s32, s16, f32, f32, f32, s32);    /* extern */
extern s32 D_807F6C18;
extern s32 D_807F6C28;

s32 func_80652BC8(s32 arg0, f32 arg1, f32 arg2, f32 arg3, s32 arg4) {
    void *sp74;
    u8 sp6E;
    s32 temp_ft2;
    s32 temp_ft4;
    s32 var_s1;
    s32 var_s5;
    s32 var_s6;
    void *temp_v0;
    void *var_s0;

    var_s1 = 0;
    sp6E = func_80630324(1, 0);
    var_s5 = 0;
    if (D_807F6C28 > 0) {
        var_s6 = 0;
        var_s0 = sp74;
        temp_ft2 = (s32) (arg1 * 6.0f);
        do {
            temp_v0 = D_807F6C18 + var_s6;
            if ((s16) temp_ft2 >= (temp_v0->unk80 - 0x32)) {
                temp_ft4 = (s32) (arg2 * 6.0f);
                if (((s16) temp_ft4 >= (temp_v0->unk82 - 0x32)) && ((temp_v0->unk84 + 0x32) >= (s16) temp_ft2) && ((temp_v0->unk86 + 0x32) >= (s16) temp_ft4)) {
                    switch (sp6E) {                 /* irregular */
                    case 0:
                        var_s0 = temp_v0->unk14;
                        break;
                    case 1:
                        var_s0 = temp_v0->unk1C;
                        break;
                    }
                    if (var_s0 != NULL) {
                        do {
                            if (var_s0->unk24 == 1) {
                                var_s1 = (var_s1 | func_80668E9C(arg0, var_s0->unk1E, arg1, arg2, arg3, arg4)) & 0xFF;
                            }
                            var_s0 = var_s0->unk14;
                        } while (var_s0 != NULL);
                    }
                }
            }
            var_s5 += 1;
            var_s6 += 0x1C8;
        } while (var_s5 < D_807F6C28);
        sp74 = var_s0;
    }
    return var_s1;
}
