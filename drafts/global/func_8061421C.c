// func_8061421C (src/global/17B90.c): stage 3: compilable typed draft reached correct core control flow but has frame/layout and structure-offset differences; remaining diff starts target frame 0x40 versus candidate 0x30, then register allocation and call argument layout.
? func_80613944(f32, f32, void *, s32 *, f32, void *); /* extern */
? func_80614644(void *, void *, f32, f32, f32);     /* extern */
? func_80614D90(void *);                            /* extern */
extern s32 D_80744478;
extern u8 D_80746B60;

void func_8061421C(void *arg0) {
    void *sp3C;
    void *sp38;
    f32 sp2C;
    f32 sp28;
    f32 sp20;
    f32 temp_a2;
    f32 temp_fa0;
    f32 temp_fa0_2;
    f32 temp_fa1;
    f32 temp_fa1_2;
    f32 temp_ft4;
    f32 temp_fv0;
    f32 temp_fv0_2;
    f32 temp_fv0_3;
    f32 temp_fv1;
    f32 temp_fv1_2;
    f32 temp_fv1_3;
    f32 temp_fv1_4;
    f32 var_fa1;
    f32 var_ft1;
    f32 var_fv0;
    f32 var_fv0_2;
    f32 var_fv0_3;
    f64 var_ft2;
    s16 temp_a0;
    s16 temp_v1;
    s16 temp_v1_2;
    s32 *temp_a1;
    void *temp_a3;
    void *temp_s0;
    void *temp_v0;

    temp_v0 = arg0->unk4;
    temp_a3 = temp_v0->unk0;
    temp_s0 = temp_v0->unk4;
    temp_a1 = temp_v0->unk8;
    temp_a2 = temp_v0->unkC;
    sp28 = temp_a3->unk4;
    temp_v1 = temp_v0->unk30;
    if (temp_v1 & 1) {
        var_ft2 = (f64) D_80744478;
        if (D_80744478 < 0) {
            var_ft2 += 4294967296.0;
        }
        var_fa1 = (f32) (var_ft2 * 0.5);
    } else {
        var_fa1 = 1.0f;
    }
    temp_v0->unk30 = (s16) (temp_v1 & 0xFFFE);
    if (D_80746B60 == 0) {
        temp_v0->unk30 = (s16) (temp_v0->unk30 | (temp_v0->unk0->unk1C & 1));
    }
    temp_fv1 = temp_v0->unk58;
    if (temp_fv1 > 0.0f) {
        temp_v0->unk54 = (f32) (temp_v0->unk54 + var_fa1);
        temp_fa0 = temp_v0->unk54;
        if (temp_fa0 < temp_fv1) {
            temp_fv0 = temp_v0->unk4C;
            temp_v0->unk48 = (f32) (temp_fv0 + (((temp_v0->unk50 - temp_fv0) * temp_fa0) / temp_fv1));
        } else {
            temp_v0->unk58 = 0.0f;
            temp_v0->unk48 = (f32) temp_v0->unk50;
        }
    }
    temp_ft4 = temp_a3->unk34;
    temp_fa0_2 = temp_v0->unk48 * var_fa1;
    if (temp_ft4 > 0.0f) {
        if (temp_fa0_2 > 0.0f) {
            var_fv0 = temp_fa0_2;
        } else {
            var_fv0 = -temp_fa0_2;
        }
        temp_a3->unk30 = (f32) (temp_a3->unk30 + var_fv0);
        temp_fv1_2 = temp_a3->unk30;
        if (temp_fv1_2 < temp_ft4) {
            temp_fv0_2 = temp_a3->unk28;
            temp_a3->unk24 = (f32) (temp_fv0_2 + (((temp_a3->unk2C - temp_fv0_2) * temp_fv1_2) / temp_ft4));
        } else {
            temp_a3->unk34 = 0.0f;
            temp_a3->unk24 = (f32) temp_a3->unk2C;
        }
    }
    temp_fa1 = temp_s0->unk34;
    if (temp_fa1 > 0.0f) {
        if (temp_fa0_2 > 0.0f) {
            var_fv0_2 = temp_fa0_2;
        } else {
            var_fv0_2 = -temp_fa0_2;
        }
        temp_s0->unk30 = (f32) (temp_s0->unk30 + var_fv0_2);
        temp_fv1_3 = temp_s0->unk30;
        if (temp_fv1_3 < temp_fa1) {
            temp_fv0_3 = temp_s0->unk28;
            temp_s0->unk24 = (f32) (temp_fv0_3 + (((temp_s0->unk2C - temp_fv0_3) * temp_fv1_3) / temp_fa1));
        } else {
            temp_s0->unk34 = 0.0f;
            temp_s0->unk24 = (f32) temp_s0->unk2C;
        }
    }
    if (*temp_a1 != 0) {
        if (temp_fa0_2 > 0.0f) {
            var_fv0_3 = temp_fa0_2;
        } else {
            var_fv0_3 = -temp_fa0_2;
        }
        temp_fv1_4 = temp_v0->unk44;
        temp_v0->unk40 = (f32) (temp_v0->unk40 + var_fv0_3);
        temp_fa1_2 = temp_v0->unk40;
        if (temp_fa1_2 < temp_fv1_4) {
            temp_v0->unk10 = (f32) ((temp_fv1_4 - temp_fa1_2) / temp_fv1_4);
        } else {
            sp3C = temp_v0;
            sp2C = temp_a2;
            sp38 = temp_a3;
            sp20 = temp_fa0_2;
            func_80613944(temp_fa0_2, temp_fa1_2, arg0, temp_a1, temp_a2, temp_a3);
            func_80613944((bitwise f32) arg0, sp2C);
            temp_v0->unk78 = (s32) (temp_v0->unk78 & ~0x10);
        }
        var_ft1 = sp28 + (((temp_fa0_2 * temp_a3->unk24) / 2.0f) * (1.0f - temp_v0->unk10));
    } else {
        var_ft1 = sp28 + (temp_fa0_2 * temp_a3->unk24);
    }
    sp28 = var_ft1;
    sp3C = temp_v0;
    func_80614644((bitwise void *) temp_fa0_2, arg0, (bitwise f32) temp_a3, sp28, (bitwise f32) temp_a3);
    if (temp_s0->unk0 != 0) {
        temp_v1_2 = temp_v0->unk28;
        temp_a0 = temp_v0->unk2C;
        if (temp_v1_2 < temp_a0) {
            temp_v0->unk28 = (s16) (temp_v1_2 + temp_v0->unk2E);
            if (temp_a0 < temp_v0->unk28) {
                goto block_40;
            }
        } else if (temp_a0 < temp_v1_2) {
            temp_v0->unk28 = (s16) (temp_v1_2 - temp_v0->unk2E);
            if (temp_v0->unk28 < temp_a0) {
block_40:
                temp_v0->unk28 = temp_a0;
            }
        }
        sp3C = temp_v0;
        sp28 = temp_s0->unk4 + temp_s0->unk24;
        func_80614644(arg0, temp_s0, sp28);
        if ((temp_s0->unk24 == 0.0f) && (temp_s0->unk1C & 0x10)) {
            temp_v0->unk2C = 0;
            if (temp_v0->unk28 == 0) {
                func_80613944((bitwise f32) arg0, (bitwise f32) temp_s0);
            }
        }
    }
    func_80614D90(arg0);
}
