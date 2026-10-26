// func_80613CA8 (src/global/17B90.c): stage 1: m2c starter recovered from local asm; requires complete controller/state views and C compile
? func_80613944(void **, void **, s32 *);           /* extern */
void *func_80614130(s16);                           /* extern */
? func_80614644(?, void **, void **, s32, void **); /* extern */

void func_80613CA8(void **arg0, s16 arg1, s32 arg2, f32 arg3) {
    void *sp30;
    s32 *sp2C;
    void **sp24;
    f32 temp_fv0;
    f32 temp_fv0_2;
    f32 temp_fv1;
    s16 temp_t6;
    void **temp_s0;
    void **temp_s1;
    void **var_a3;
    void *temp_v0;
    void *var_v1;

    var_v1 = arg0->unk4;
    sp2C = var_v1->unk0;
    var_a3 = var_v1->unk8;
    temp_s0 = var_v1->unk4;
    temp_s1 = var_v1->unkC;
    if (*var_a3 != NULL) {
        sp30 = var_v1;
        sp24 = var_a3;
        func_80613944(var_a3, var_a3);
    }
    if (temp_s1->unk0 != NULL) {
        sp30 = var_v1;
        sp24 = var_a3;
        func_80613944(arg0, temp_s1);
    }
    if ((arg1 & 0x4000) == 0x4000) {
        arg1 -= 0x4000;
        if (temp_s0->unk0 != NULL) {
            sp24 = var_a3;
            sp30 = var_v1;
            temp_s1->unk0 = func_80614130(temp_s0->unk10);
            temp_s1->unk4 = (f32) temp_s0->unk4;
            temp_s1->unk8 = (f32) temp_s0->unk8;
            temp_s1->unkC = (s16) temp_s0->unkC;
            temp_s1->unkE = (s16) temp_s0->unkE;
            temp_s1->unk10 = (s16) temp_s0->unk10;
            temp_s1->unk1C = (s16) temp_s0->unk1C;
            temp_s1->unk14 = (f32) temp_s0->unk14;
            temp_s1->unk18 = (f32) temp_s0->unk18;
            temp_s1->unk34 = (f32) temp_s0->unk34;
            temp_s1->unk24 = (f32) temp_s0->unk24;
            temp_s1->unk2C = (f32) temp_s0->unk2C;
            temp_s1->unk28 = (f32) temp_s0->unk28;
            temp_s1->unk30 = (f32) temp_s0->unk30;
            var_v1->unk2A = (s16) var_v1->unk28;
        } else {
            var_v1->unk2A = 0;
        }
    }
    if (arg3 > 0.0f) {
        temp_fv0 = var_v1->unk48;
        if (temp_fv0 > 0.0f) {
            var_v1->unk40 = temp_fv0;
        } else {
            var_v1->unk40 = (f32) -temp_fv0;
        }
        temp_fv1 = var_v1->unk40;
        if (temp_fv1 < arg3) {
            var_v1->unk44 = arg3;
        } else {
            var_v1->unk44 = temp_fv1;
        }
        temp_fv0_2 = var_v1->unk44;
        var_v1->unk10 = (f32) ((temp_fv0_2 - var_v1->unk40) / temp_fv0_2);
    } else {
        if (*sp2C != 0) {
            sp30 = var_v1;
            sp24 = var_a3;
            func_80613944(NULL, arg0, sp2C);
        }
        if (temp_s0->unk0 != NULL) {
            sp30 = var_v1;
            sp24 = var_a3;
            func_80613944(arg0, temp_s0);
        }
    }
    sp30 = var_v1;
    sp24 = var_a3;
    temp_v0 = func_80614130(arg1);
    if (temp_v0 != NULL) {
        var_a3->unk0 = temp_v0;
        var_a3->unk10 = arg1;
        var_a3->unk14 = 0.0f;
        var_a3->unk1C = (u16) temp_v0->unk4;
        var_a3->unk34 = 0.0f;
        var_a3->unk18 = (f32) (temp_v0->unk12 - 1);
        var_a3->unk24 = (f32) temp_v0->unk0;
        var_a3->unk2C = (f32) temp_v0->unk0;
        var_a3->unk30 = 0.0f;
        var_a3->unk28 = (f32) temp_v0->unk0;
    } else {
        var_a3->unk0 = NULL;
        var_a3->unk10 = -1;
        var_a3->unk1C = 0U;
        var_a3->unk14 = 0.0f;
        var_a3->unk18 = 0.0f;
        var_a3->unk34 = 0.0f;
        var_a3->unk24 = 0.0f;
        var_a3->unk2C = 0.0f;
        var_a3->unk28 = 0.0f;
        var_a3->unk30 = 0.0f;
    }
    var_v1->unk78 = 0;
    var_v1->unk7C = 0;
    var_v1->unk80 = 0.0f;
    temp_t6 = var_v1->unk2A;
    var_v1->unkC = temp_s0;
    var_v1->unk0 = var_a3;
    var_v1->unk4 = temp_s1;
    var_v1->unk8 = sp2C;
    var_v1->unk2A = (s16) var_v1->unk29;
    var_v1->unk28 = temp_t6;
    func_80614644(0, arg0, var_a3, arg2, var_a3);
}
