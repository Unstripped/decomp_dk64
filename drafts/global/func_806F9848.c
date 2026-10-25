// func_806F9848 (src/global/FCCD0.c): Stage 1 m2c reconstruction; needs typed slot records and register allocation.
? func_806F9608(void **, s32);                      /* extern */
? func_806F966C(void *);                            /* extern */
? func_806F96CC(void *, s32);                       /* extern */
? func_806F9744(void *, s32, f32, f32, s32);        /* extern */
extern s16 D_80744490;
extern u8 D_8074E77C;
extern s32 D_80754280;
extern s32 D_8076A0A8;

void func_806F9848(s32 arg0) {
    s8 *sp44;
    s32 sp3C;
    s32 sp30;
    s32 temp_v1;
    s32 var_a1;
    s32 var_s1;
    void **var_s0;
    void *temp_a0;
    void *temp_a0_2;
    void *temp_s0;
    void *temp_s0_2;
    void *temp_s0_3;
    void *temp_v0;
    void *temp_v0_2;
    void *temp_v0_3;

    temp_v1 = arg0 * 0x30;
    temp_s0 = temp_v1 + D_80754280;
    var_s0 = temp_s0 + 0x28;
    var_a1 = 1;
    var_s1 = -1;
    if (((f64) D_80744490 * 0.5) < (f64) (D_80754280 + temp_v1)->unk8) {
        var_a1 = -1;
    }
    sp30 = temp_v1;
    sp3C = var_a1;
    func_806F9608(var_s0, var_a1);
    temp_a0 = temp_s0->unk28;
    sp44 = temp_a0->unk14;
    func_806F96CC(temp_a0, arg0);
    temp_v0 = D_80754280 + sp30;
    func_806F9744(temp_s0->unk28, arg0, (f32) temp_v0->unk8, (f32) temp_v0->unkC, 0);
    *sp44 = 0xFF;
    temp_s0->unk28->unk10 = 0;
    if (D_8076A0A8 != 1) {
        if (D_8076A0A8 != 5) {
            if (D_8076A0A8 != 0x19) {
                if ((D_8076A0A8 == 0x2A) && (arg0 == 0xD)) {
                    var_s1 = 0x10;
                }
            } else {
                goto block_13;
            }
        } else {
            goto block_10;
        }
    } else {
        if (arg0 == 0xE) {
            var_s1 = 0x11;
        }
block_10:
        if ((var_s1 == -1) && (arg0 == 0xE)) {
            var_s1 = 0x13;
        }
block_13:
        if ((var_s1 == -1) && (arg0 == 0xE)) {
            var_s1 = 0x12;
        } else if (arg0 == 1) {
            var_s1 = D_8074E77C + 0x14;
        }
    }
    if (var_s1 >= 0) {
        temp_s0_2 = temp_s0->unk28;
        var_s0 = temp_s0_2 + 0x18;
        func_806F9608(var_s0);
        temp_a0_2 = temp_s0_2->unk18;
        sp44 = temp_a0_2->unk14;
        func_806F96CC(temp_a0_2, arg0);
        temp_v0_2 = D_80754280 + sp30;
        func_806F9744(temp_s0_2->unk18, var_s1, (f32) temp_v0_2->unk8, (f32) (temp_v0_2->unkC + 0x20), 0);
        *sp44 = 0xFF;
        temp_s0_2->unk18->unk10 = 0;
    }
    temp_s0_3 = *var_s0;
    func_806F966C(temp_s0_3 + 0x18);
    func_806F96CC(temp_s0_3->unk18, arg0);
    temp_s0_3->unk18->unk10 = 0;
    temp_v0_3 = temp_s0_3->unk18->unk14;
    temp_v0_3->unk0 = (s32) ((D_80754280 + sp30)->unk8 + (sp3C * 0x14));
    temp_v0_3->unk4 = (s32) ((D_80754280 + sp30)->unkC - 0xA);
}
