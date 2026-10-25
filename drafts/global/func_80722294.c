// func_80722294 (src/global/126260.c): stage 1 m2c starter generated; requires all supporting views/prototypes and block-by-block reconstruction
? actorGetNodePos(void *, u8, f32 *, ?32 *, f32 *); /* extern */
f32 func_80612790(s16, s16);                        /* extern */
f32 func_80612794(s16);                             /* extern */
s32 func_80721814(s32, s32, f32, ?32, f32, s32);    /* extern */
s32 mathAngleBetweenPoints2D(f32, f32, ? *, s16, s32, s32); /* extern */
extern f32 D_807444CC;
extern f32 D_807444D0;
extern f32 D_807444D4;
extern f32 D_807444D8;
extern f32 D_807444DC;
extern s16 D_80755680;
extern f32 D_80755684;
extern f32 D_80755688;
extern f32 D_8075568C;
extern s32 D_8076A048;
extern s32 D_8076A064;
extern s32 D_8076A0B4;
extern s32 D_8076A0B8;
extern s32 D_8076A0BC;
extern s32 D_807FBB4C;
extern s32 D_807FBB60;
extern s32 D_807FC924;
extern ? D_807FDB60;
extern s32 D_807FDB70;
extern u8 D_807FDB74;
extern u8 D_807FDB75;
extern s16 D_807FDB76;
extern s16 D_807FDB78;
extern s16 D_807FDB7A;
extern u8 D_807FDB7C;
extern u8 D_807FDB7D;
extern u8 D_807FDB7E;
extern u8 D_807FDB7F;
extern u8 D_807FDB80;
extern f32 func_807444E0;

void *func_80722294(void *arg0, void *arg1, s16 arg2) {
    u8 spB7;
    s32 spB0;
    void *spA8;
    s16 sp9E;
    s16 sp9C;
    f32 sp94;
    f32 sp90;
    f32 sp8C;
    f32 sp74;
    ?32 sp70;
    f32 sp6C;
    f32 sp68;
    f32 sp64;
    f32 sp60;
    f32 temp_fa1;
    f32 temp_fv1;
    f32 var_fa0;
    f32 var_fa1;
    f32 var_ft1_2;
    f32 var_ft2;
    f32 var_ft2_3;
    f32 var_ft2_4;
    f32 var_ft4;
    f32 var_ft5;
    f64 var_ft1;
    f64 var_ft2_2;
    f64 var_ft3;
    f64 var_ft3_2;
    f64 var_ft3_3;
    f64 var_ft3_4;
    f64 var_fv0;
    f64 var_fv0_2;
    f64 var_fv0_3;
    f64 var_fv0_4;
    f64 var_fv0_5;
    f64 var_fv0_6;
    s16 temp_a0;
    s16 var_a1;
    s16 var_s0;
    s16 var_v1;
    s32 temp_ft3;
    s32 temp_lo;
    s32 temp_s0;
    s32 temp_t1;
    s32 temp_t9;
    s32 temp_v0_2;
    s32 var_s2;
    u32 temp_v0_3;
    u32 temp_v0_4;
    u32 temp_v0_5;
    u8 temp_t4;
    u8 temp_t5;
    u8 temp_t6;
    u8 temp_t8;
    u8 temp_t9_2;
    u8 temp_v1;
    void *temp_s1;
    void *temp_s1_2;
    void *temp_s4;
    void *temp_v0;
    void *temp_v0_6;
    void *temp_v0_7;
    void *var_s1;
    void *var_t0;

    var_s1 = arg0;
    if (arg1 == D_807FBB4C) {
        spB7 = 1;
    } else {
        spB7 = 0;
    }
    var_s2 = 1;
    spB0 = D_8076A048;
    temp_v1 = arg1->unkCD;
    temp_v0 = D_8076A048 + (D_807FDB75 * 0x78);
    var_t0 = temp_v0 + 0x270;
    temp_s4 = temp_v0 + 0x278;
    if (temp_v1 != 0) {
        spA8 = var_t0;
        actorGetNodePos(arg1, temp_v1, &sp74, &sp70, &sp6C);
        var_t0 = spA8;
    } else {
        sp74 = arg1->unk7C;
        sp70 = arg1->unk80;
        sp6C = arg1->unk84;
    }
    if (spB7 != 0) {
        var_fa1 = D_80755684;
        var_ft4 = D_8075568C;
        var_ft5 = D_80755688;
        var_a1 = D_80755680;
    } else {
        var_a1 = 0;
        var_fa1 = (f32) D_807FDB7E;
        var_ft4 = (f32) D_807FDB7F;
        if ((s32) D_807FDB7F < 0) {
            var_ft4 += 4294967296.0f;
        }
        var_ft5 = (f32) D_807FDB80;
        if ((s32) D_807FDB80 < 0) {
            var_ft5 += 4294967296.0f;
        }
    }
    var_v1 = arg1->unk12C;
    if (var_v1 == -1) {
        var_v1 = 0;
    }
    if (arg1->unk64 & 1) {
        var_fa0 = 1.0f;
    } else {
        temp_t6 = arg1->unk16D;
        var_ft2 = (f32) temp_t6;
        if ((s32) temp_t6 < 0) {
            var_ft2 += 4294967296.0f;
        }
        var_fa0 = var_ft2 / 15.0f;
    }
    if (arg1->unk60 & 0x800000) {
        temp_t8 = arg1->unk16A;
        var_ft3 = (f64) temp_t8;
        if ((s32) temp_t8 < 0) {
            var_ft3 += 4294967296.0;
        }
        sp60 = (f32) (var_ft3 / 255.0);
        temp_t4 = arg1->unk16B;
        var_ft3_2 = (f64) temp_t4;
        if ((s32) temp_t4 < 0) {
            var_ft3_2 += 4294967296.0;
        }
        sp64 = (f32) (var_ft3_2 / 255.0);
        temp_t5 = arg1->unk16C;
        var_ft3_3 = (f64) temp_t5;
        if ((s32) temp_t5 < 0) {
            var_ft3_3 += 4294967296.0;
        }
        sp68 = (f32) (var_ft3_3 / 255.0);
    } else {
        temp_v0_2 = var_v1 * 4;
        sp60 = *(D_8076A0B4 + temp_v0_2);
        sp64 = *(D_8076A0B8 + temp_v0_2);
        sp68 = *(D_8076A0BC + temp_v0_2);
    }
    if (D_807FDB7C != 0) {
        var_fv0 = (f64) (sp60 * var_fa0);
    } else {
        var_fv0 = 1.0;
    }
    var_ft2_2 = (f64) D_807FDB60.unkB;
    if ((s32) D_807FDB60.unkB < 0) {
        var_ft2_2 += 4294967296.0;
    }
    temp_v0_3 = (u32) (var_fv0 * var_ft2_2);
    var_t0->unk4 = (s8) temp_v0_3;
    var_t0->unk0 = (s8) temp_v0_3;
    if (D_807FDB7C != 0) {
        var_fv0_2 = (f64) (sp64 * var_fa0);
    } else {
        var_fv0_2 = GLUE_F64(0x3FF00000U, 0U);
    }
    var_ft3_4 = (f64) D_807FDB60.unkC;
    if ((s32) D_807FDB60.unkC < 0) {
        var_ft3_4 += 4294967296.0;
    }
    temp_v0_4 = (u32) (var_fv0_2 * var_ft3_4);
    var_t0->unk5 = (s8) temp_v0_4;
    var_t0->unk1 = (s8) temp_v0_4;
    if (D_807FDB7C != 0) {
        var_fv0_3 = (f64) (sp68 * var_fa0);
    } else {
        var_fv0_3 = GLUE_F64(0x3FF00000U, 0U);
    }
    var_ft1 = (f64) D_807FDB60.unkD;
    if ((s32) D_807FDB60.unkD < 0) {
        var_ft1 += 4294967296.0;
    }
    temp_v0_5 = (u32) (var_fv0_3 * var_ft1);
    var_t0->unk6 = (s8) temp_v0_5;
    var_t0->unk2 = (s8) temp_v0_5;
    if (D_807FDB7D != 0) {
        var_fv0_4 = (f64) (sp60 * var_fa0);
    } else {
        var_fv0_4 = GLUE_F64(0x3FF00000U, 0U);
    }
    temp_v0->unk278 = (u8) (s32) (var_fv0_4 * (f64) var_fa1);
    if (D_807FDB7D != 0) {
        var_fv0_5 = (f64) (sp64 * var_fa0);
    } else {
        var_fv0_5 = GLUE_F64(0x3FF00000U, 0U);
    }
    temp_s4->unk1 = (u8) (s32) (var_fv0_5 * (f64) var_ft4);
    if (D_807FDB7D != 0) {
        spA8 = var_t0;
        var_fv0_6 = (f64) (sp68 * var_fa0);
    } else {
        var_fv0_6 = GLUE_F64(0x3FF00000U, 0U);
        spA8 = var_t0;
    }
    temp_s4->unk4 = (u8) temp_v0->unk278;
    temp_s4->unk5 = (u8) temp_s4->unk1;
    temp_ft3 = (s32) (var_fv0_6 * (f64) var_ft5);
    temp_s4->unk2 = (s8) temp_ft3;
    temp_s4->unk6 = (s8) temp_ft3;
    temp_s0 = arg2 * 0x2F0;
    temp_v0_6 = D_807FC924 + temp_s0;
    sp9E = var_a1;
    temp_a0 = mathAngleBetweenPoints2D(sp74, sp6C, &D_807FDB60, var_a1, temp_v0_6->unk21C, temp_v0_6->unk224) + D_807FDB76;
    sp9C = temp_a0;
    sp94 = ((D_807FC924 + temp_s0)->unk21C - (func_80612794(temp_a0) * (f32) D_807FDB78)) - sp74;
    sp90 = (f32) (var_a1 + D_807FDB7A);
    temp_fa1 = ((D_807FC924 + temp_s0)->unk224 - (func_80612790(temp_a0, var_a1) * (f32) D_807FDB78)) - sp6C;
    sp8C = temp_fa1;
    temp_fv1 = 127.0f / sqrtf((sp94 * sp94) + (sp90 * sp90) + (temp_fa1 * temp_fa1));
    temp_s4->unk8 = (s8) (s32) (sp94 * temp_fv1);
    temp_s4->unk9 = (s8) (s32) (sp90 * temp_fv1);
    temp_s4->unkA = (s8) (s32) (temp_fa1 * temp_fv1);
    if (spB7 != 0) {
        D_807444CC = (f32) temp_s4->unk8;
        D_807444D0 = (f32) temp_s4->unk9;
        D_807444D4 = (f32) temp_s4->unkA;
        D_807444D8 = 10.0f;
        D_807444DC = -10.0f;
        func_807444E0 = 10.0f;
        D_80755680 = (s16) (s32) ((f64) D_80755680 + ((f64) -D_80755680 * 0.05));
        var_ft2_3 = (f32) D_807FDB7E;
        if ((s32) D_807FDB7E < 0) {
            var_ft2_3 += 4294967296.0f;
        }
        D_80755684 = (f32) ((f64) D_80755684 + ((f64) (var_ft2_3 - D_80755684) * 0.05));
        var_ft1_2 = (f32) D_807FDB7F;
        if ((s32) D_807FDB7F < 0) {
            var_ft1_2 += 4294967296.0f;
        }
        D_80755688 = (f32) ((f64) D_80755688 + ((f64) (var_ft1_2 - D_80755688) * 0.05));
        var_ft2_4 = (f32) D_807FDB80;
        if ((s32) D_807FDB80 < 0) {
            var_ft2_4 += 4294967296.0f;
        }
        D_8075568C = (f32) ((f64) D_8075568C + ((f64) (var_ft2_4 - D_8075568C) * 0.05));
    }
    var_s0 = 0;
    if ((s32) D_807FDB74 > 0) {
        do {
            if ((arg1 == *(D_807FDB70 + (var_s0 * 0x10))) && (func_80721814(var_s2 & 0xFF, (var_s0 * 0x10) + D_807FDB70, sp74, sp70, sp6C, (s32) arg2) != 0)) {
                var_s2 = (var_s2 + 1) & 0xFF;
            }
            var_s0 += 1;
        } while (var_s0 < (s32) D_807FDB74);
        var_s0 = 0;
    }
    if (!(D_807FBB60 & 2) && (arg1->unk5C & 1) && (arg1->unk174->unkD4 != 0) && (D_8076A064 & 2)) {
        temp_v0->unk278 = 0U;
        temp_s4->unk1 = 0U;
        temp_s4->unk2 = 0;
        temp_s4->unk4 = 0U;
        temp_s4->unk5 = 0U;
        temp_s4->unk6 = 0;
        spA8->unk2 = 0;
        spA8->unk1 = 0;
        spA8->unk0 = 0;
        spA8->unk6 = 0;
        spA8->unk5 = 0;
        spA8->unk4 = 0;
    }
    if (var_s2 > 0) {
        do {
            temp_v0_7 = var_s1;
            var_s1 += 8;
            temp_v0_7->unk0 = (s32) (((((s32) ((var_s0 * 0x18) + 0x30) / 8) & 0xFF) << 8) | 0xDC080000 | 0xA);
            temp_t9 = var_s0 * 0x10;
            var_s0 += 1;
            temp_v0_7->unk4 = (s32) (spB0 + (D_807FDB75 * 0x78) + temp_t9 + 0x278);
        } while (var_s0 < var_s2);
    }
    temp_lo = var_s2 * 0x18;
    temp_s1_2 = var_s1 + 8;
    temp_s1 = temp_s1_2 + 8;
    var_s1->unk0 = (s32) (((((s32) (temp_lo + 0x30) / 8) & 0xFF) << 8) | 0xDC080000 | 0xA);
    var_s1->unk4 = (s32) (spB0 + (D_807FDB75 * 0x78) + 0x270);
    temp_s1_2->unk4 = temp_lo;
    var_s1->unk8 = 0xDB020000;
    temp_s1->unk4 = 0;
    temp_s1_2->unk8 = 0xE7000000;
    temp_t9_2 = D_807FDB75 + 1;
    temp_t1 = temp_t9_2 & 0xFF;
    D_807FDB75 = temp_t9_2;
    if (temp_t1 >= 0x18) {
        D_807FDB75 = temp_t1 - 1;
    }
    return temp_s1 + 8;
}
