// func_80713B40 (src/global/117190.c): from .scratch/MenuB/func_80713B40_best.c
extern u8 D_80755378[];
Gfx *hudDrawScaledText(Gfx *, s16, s16, f32, void *);

Gfx *func_80713B40(Gfx *arg0) {
    s16 temp_t0;
    s16 temp_v0;
    s16 var_v1;
    u32 new_var; // FAKE: extra temp for the alpha byte steers regalloc

    temp_t0 = D_8075531C - 0x8C;
    if (temp_t0 >= 0) {
        if (temp_t0 < 0x96) {
            temp_v0 = temp_t0 - 0x5A;
            var_v1 = temp_v0; // FAKE: copy of temp_v0 steers regalloc
            if (var_v1 < 0) {
                var_v1 = 0xFF;
            } else {
                var_v1 = 0x3C - var_v1;
                var_v1 = var_v1 * 5;
            }
            if (temp_t0 < 0x3C) {
                var_v1 = temp_t0 * 5;
            }
            if (var_v1 >= 0x100) {
                var_v1 = 0xFF;
            }
            arg0 = func_80713AA8(arg0);
            new_var = var_v1 & 0xFF;
            arg0->words.w0 = 0xFA000000;
            arg0->words.w1 = (u32)(new_var | ~0xFF);
            arg0 = hudDrawScaledText(arg0 + 1, 0x280, (s16)(s32)(480.0 - ((f64)(f32)((f64)(0x96 - temp_t0) / 40.0) * 32.0)), (f32)((f64)(0x96 - temp_t0) / 40.0), D_80755378);
        }
    }
    return arg0;
}
