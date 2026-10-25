// func_80713B40 (src/global/117190.c): Stage 2 m2c fade/display-list/text draft: recovers color clamps and scaled text, but stack frame remains 0x30 versus target 0x28 and signed fade arithmetic/register allocation differs.
extern u8 D_80755378[];
Gfx *hudDrawScaledText(Gfx *, s16, s16, f32, void *);

s32 func_80713B40(s32 arg0) {
    s16 sp26;
    s16 sp22;
    f32 temp_fv0;
    s16 temp_t0;
    s16 temp_v0;
    s16 var_v1;
    s32 var_a1;
    Gfx *temp_v0_2;

    temp_t0 = D_8075531C - 0x8C;
    var_a1 = arg0;
    if (temp_t0 >= 0) {
        temp_v0 = temp_t0 - 0x5A;
        if (temp_t0 < 0x96) {
            if (temp_v0 < 0) {
                var_v1 = 0xFF;
            } else {
                var_v1 = (0x3C - temp_v0) * 5;
            }
            if (temp_t0 < 0x3C) {
                var_v1 = temp_t0 * 5;
            }
            if (var_v1 >= 0x100) {
                var_v1 = 0xFF;
            }
            sp22 = var_v1;
            sp26 = temp_t0;
            temp_v0_2 = func_80713AA8((Gfx *)var_a1);
            temp_v0_2->words.w0 = 0xFA000000;
            temp_v0_2->words.w1 = (u32)((var_v1 & 0xFF) | ~0xFF);
            temp_fv0 = (f32)((f64)(0x96 - temp_t0) / 40.0);
            var_a1 = (s32)hudDrawScaledText(temp_v0_2 + 1, 0x280, (s16)(s32)(480.0 - ((f64)temp_fv0 * 32.0)), temp_fv0, D_80755378);
        }
    }
    return var_a1;
}
