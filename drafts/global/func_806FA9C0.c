// func_806FA9C0 (src/global/FCCD0.c): stage 3: semantic node countdown draft; local types need frame/regalloc tuning
s32 func_806FA504(s32, void *, s32, s32);           /* extern */
extern s32 D_80754280;

s32 func_806FA9C0(s32 arg0, s32 arg1) {
    s32 sp34;
    s16 temp_v0_2;
    s32 temp_t6;
    s32 temp_v0;
    s32 var_a0;
    s32 var_s1;
    s32 var_s4;
    s32 var_v1;
    u8 temp_v1;
    void *var_s0;
    void *var_s0_2;
    void *var_v0;

    temp_t6 = arg0 * 0x30;
    sp34 = temp_t6;
    var_v0 = D_80754280 + temp_t6;
    var_s0 = var_v0->unk28;
    var_s4 = arg1;
    var_s1 = 0;
    if (var_s0 != NULL) {
        do {
            var_s4 = func_806FA504(arg0, var_s0, var_s1, var_s4);
            if (var_s0->unk0 == 1) {
                var_s1 += 1;
            }
            var_s0 = var_s0->unk18;
        } while (var_s0 != NULL);
        var_v0 = D_80754280 + sp34;
    }
    temp_v1 = var_v0->unk7;
    if (temp_v1 != 0) {
        var_v0->unk7 = (u8) (temp_v1 - 1);
    } else {
        var_s0_2 = var_v0->unk28;
        var_v1 = 0;
        var_a0 = 0;
        if (var_s0_2 != NULL) {
            do {
                temp_v0 = var_s0_2->unkC;
                var_a0 += 1;
                if (temp_v0 != 0) {
                    var_s0_2->unkC = (s32) (temp_v0 - 1);
                } else {
                    temp_v0_2 = var_s0_2->unk10;
                    if (temp_v0_2 > 0) {
                        var_s0_2->unk10 = (s16) (s32) ((f32) temp_v0_2 - 102.4f);
                    }
                    if (var_s0_2->unk10 < 0) {
                        var_s0_2->unk10 = 0;
                        var_v1 += 1;
                    }
                }
                var_s0_2 = var_s0_2->unk18;
            } while (var_s0_2 != NULL);
        }
        if (var_a0 == var_v1) {
            (D_80754280 + sp34)->unk20 = 0;
        }
    }
    return var_s4;
}
