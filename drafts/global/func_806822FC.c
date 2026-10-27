// func_806822FC (src/global/80150.c): from .scratch/R2H/func_806822FC_best.c
void func_806822FC(void) {
    s32 sp58;
    f32 sp54;
    u8 sp4B;
    u8 sp4A;
    f32 sp38;
    f32 sp34;
    void *var_v1;
    f32 temp_fa1;
    f32 temp_ft5;
    f32 temp_fv0;
    f32 temp_fv0_2;
    f32 temp_fv0_3;
    f32 temp_fv1;
    f32 temp_fv1_2;
    f64 var_fv1;
    s32 var_v0;
    u8 temp_t4;
    u8 temp_t8;
    u8 temp_v0;
    u8 temp_v0_2;
    u8 temp_v0_3;
    u8 temp_v0_4;
    u8 var_t0;
    void *temp_a0;
    void *temp_a0_2;
    void *temp_s1;
    void *temp_v0_5;
    void *var_s0;

    temp_s1 = D_807FBB40->unk174;
    sp4B = 0;
    if (!(D_807FBB40->unk60 & 0x10)) {
        D_807FBB40->unk132 = 1;
        temp_s1->unk2 = 0U;
        temp_s1->unk8 = 0;
        temp_s1->unk1 = 0U;
        temp_s1->unk3 = 0U;
    }
    temp_v0 = D_807FBB40->unk154;
    if ((temp_v0 == 2) || (temp_v0 == 3)) {
        sp58 = temp_s1->unk4->unk174->unk104;
        temp_s1->unk8 = (s16) (s32) ((f64) temp_s1->unk8 - (((f64) D_807FD63E * 0.08 * (f64) D_8074E7F8 * 4096.0) / 360.0));
        temp_s1->unk8 = (s16) (temp_s1->unk8 & 0xFFF);
        sp4A = 0;
        sp54 = func_80612794(temp_s1->unk8) * D_8074E7F4;
        temp_ft5 = func_80612790(temp_s1->unk8) * D_8074E7F4;
        D_8074E804 = (f32) ((f64) D_8074E804 - ((f64) D_807FD63F * 0.04 * (f64) D_8074E800));
        var_fv1 = (f64) D_8074E804;
        if (var_fv1 > 50.0) {
            D_8074E804 = 50.0f;
            var_fv1 = (f64) D_8074E804;
        }
        if (var_fv1 < -50.0) {
            D_8074E804 = -50.0f;
        }
        temp_fv0 = D_807FBB40->unk7C;
        temp_fv1 = D_807FBB40->unk80 + D_8074E7FC;
        temp_fa1 = D_807FBB40->unk84;
        sp4A = 0;
        func_8061C2F0(D_8074E804, temp_fa1, sp58, temp_fv0, temp_fv1, temp_fa1, temp_fv0 + sp54, temp_fv1 + D_8074E804, temp_fa1 + temp_ft5, 0);
        if (func_8061CB50() == 0) {
            sp4A = 0;
            func_8068C350(&func_806FF01C, D_807FBB4C, 3);
            func_8068C350(&func_806FEF7C, D_807FBB4C, 3);
        }
        sp4A = 0;
        func_8066E6C8(D_807FBB40, 0, 0);
    } else {
        sp4A = 0;
        func_8066E6C8(D_807FBB40, 0, 1);
    }
    var_t0 = sp4A;
    if (temp_s1->unk2 != 0) {
        func_8068C350(&func_8068DAF4, temp_s1, 3);
    }
    temp_a0 = D_807FBB40->unk11C;
    var_v1 = &D_807FBB70;
    if ((temp_a0 != NULL) && (temp_s1->unk2 != 0) && (temp_a0->unk154 == 5) && (temp_s1->unk1 == 0)) {
        temp_s1->unk1 = 0x1EU;
    }
    temp_v0_2 = temp_s1->unk1;
    temp_t4 = temp_v0_2 - 1;
    if (temp_v0_2 != 0) {
        temp_s1->unk1 = temp_t4;
        if (!(temp_t4 & 0xFF)) {
            sp4B = 1;
        }
    }
    var_v0 = 0;
    if ((s32) D_807FBB70.unk254 > 0) {
        do {
            var_v0 += 1;
            if (var_v1->unk258 == 1) {
                temp_s1->unk3 = 1U;
                var_t0 = 1 & 0xFF;
            }
            var_v1 += 4;
        } while (var_v0 < (s32) D_807FBB70.unk254);
    }
    if ((sp4B != 0) || (var_t0 != 0)) {
        temp_s1->unk2 = 0U;
        temp_v0_3 = D_807FBB40->unk154;
        if ((temp_v0_3 == 2) || (temp_v0_3 == 3)) {
            D_807FBB40->unk154 = 3U;
        } else {
            D_807FBB40->unk154 = 0U;
            D_807FBB40->unk144 = 2;
        }
        temp_a0_2 = D_807FBB40->unk11C;
        if (temp_a0_2 != NULL) {
            func_806782C0(temp_a0_2);
            D_807FBB40->unk11C = NULL;
        }
        if (sp4B != 0) {
            func_8063DA40(0x30, 0, 1, 1U);
            func_8063DA40(0x2F, 0);
            func_8063DA40(0x31, 0);
        }
    }
    var_s0 = D_807FBB40;
    temp_v0_4 = var_s0->unk154;
    switch (temp_v0_4) {
    case 0:
        var_s0->unk132 = 1;
        if ((D_807FBB70.unk200 == 5) && (temp_s1->unk3 == 0)) {
            D_807FBB40->unk154 = 1U;
            D_807FBB40->unk132 = 2;
        }
block_58:
        var_s0 = D_807FBB40;
        break;
    case 1:
        if (D_807FBB70.unk200 == 4) {
            var_s0->unk154 = 2U;
            temp_s1->unk0 = 6U;
            temp_s1->unk4 = (void *) D_807FBB70.unk1FC;
            if (temp_s1->unk2 == 0) {
                func_8063DA40(0x30, 0xA, 1, 1U);
                temp_s1->unk2 = 1U;
                func_806A2A10(0xC8, 0x20, D_8074E810, 1);
                func_806A2B08(D_807FBB44);
                D_807FBB40->unk60 = (s32) (D_807FBB40->unk60 | 0x200000);
            }
            D_807FBB40->unk60 = (s32) (D_807FBB40->unk60 & ~4);
            D_807FBB40->unk144 = 1;
            var_s0 = D_807FBB40;
        }
        break;
    case 2:
        if ((D_807FD63C & 0x2000) && (func_8067ACDC(var_s0, 4, 0, 1U) == 0) && (temp_s1->unk0 != 0)) {
            func_806907F0(D_807FBB40->unk7C, D_807FBB40->unk80 + D_8074E7FC, D_807FBB40->unk84);
            temp_fv0_2 = D_807FC924->unk230 - D_807FC924->unk218;
            temp_fv1_2 = D_807FC924->unk228 - D_807FC924->unk210;
            temp_fv0_3 = func_80611BB4(D_807FC924->unk22C - D_807FC924->unk214, sqrtf((temp_fv0_2 * temp_fv0_2) + (temp_fv1_2 * temp_fv1_2)));
            sp38 = temp_fv0_3;
            sp34 = func_80612D1C(temp_fv0_3) * D_8074E808;
            func_8069084C(0x4A, 0, 0x3F19999A, temp_s1->unk8, func_80612D10(sp38) * D_8074E808, sp34, D_807FBB40);
            func_80608528(D_807FBB40, 0x17, 0xFF, 0x7F, 0x19);
            temp_t8 = temp_s1->unk0 - 1;
            temp_s1->unk0 = temp_t8;
            if (!(temp_t8 & 0xFF)) {
                D_807FBB40->unk154 = 3U;
            }
        }
        goto block_58;
    case 3:
        if (func_8067ACDC(var_s0, 4, 0, 1U) == 0) {
            func_80679200(temp_s1->unk4, D_807FBB40, 0x40, 1, 0, 0);
            func_8067A70C(D_807FBB40, temp_s1->unk4, D_807FBB40->unk7C, D_807FBB40->unk80, D_807FBB40->unk84 - 42.0f, 2, 1);
            temp_v0_5 = temp_s1->unk4;
            temp_v0_5->unk60 = (s32) (temp_v0_5->unk60 & ~8);
            func_806CFF9C(temp_s1->unk4);
            D_807FBB40->unk60 = (s32) (D_807FBB40->unk60 | 4);
            D_807FBB40->unk154 = 0U;
            D_807FBB40->unk144 = 2;
        }
        goto block_58;
    }
    actorUpdateModelMatrix(var_s0, 0);
}
