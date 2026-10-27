// func_80033AF0 (src/boss/F0D0.c): from .scratch/Boss3F/func_80033AF0_best.c
? func_80027BA8(s32, ?, ?, void **);                /* extern */
? func_80028478(?, s16, s16, s16, s32, s32);        /* extern */
u8 func_800330D0(void *, void *);                   /* extern */
? func_8003340C(void *);                            /* extern */
? func_800334A4(void *, f32);                       /* extern */
? func_800336C0();                                  /* extern */
? func_80033784(void *, ?, ?, void **);             /* extern */
? func_8003392C(void *);                            /* extern */
s32 func_800339D8(void *, s32);                     /* extern */
? func_80033A80(s8);                                /* extern */
? func_80604CBC(void *, ?, ?, ?, s32, s32, f32, s32); /* extern */
? func_80605314(void *, ?);                         /* extern */
? func_80608528(void *, ?, ?, ?, s32);              /* extern */
? func_806086CC(f32, f32, f32, ?, s32, s32, s32, s32, f32, s32); /* extern */
s32 func_80611A44();                                /* extern */
f32 func_80612794(s16);                             /* extern */
? func_80614D00(void *, s32, ?);                    /* extern */
? func_80614D90(void *);                            /* extern */
? func_80614EBC(void *, ?, ?, void **);             /* extern */
s32 func_8061CB50();                                /* extern */
? func_8061CC40(void *, ?, ?, void **);             /* extern */
? func_80626110(s32, s16, s16);                     /* extern */
s32 currentActorTestClearFlag();                                /* extern */
? currentActorClearFlag();                                  /* extern */
? actorUpdateModelMatrix(void *, ?);                         /* extern */
? func_8063DA40(u8, ?);                             /* extern */
? func_80659610(?, u8 *, void **);                  /* extern */
? func_8065A708(f32, f32, f32, f32, f32, u32, u32, s32, s32, s32, s32); /* extern */
? func_806653C0(void *, ?, s32);                    /* extern */
? func_80665564(void *, ?);                         /* extern */
? func_80671C0C(void *, ?, f32 *, f32 *, f32 *);    /* extern */
? func_8067ACB4(void *);                            /* extern */
? func_806845B8(?, ?, ?, void **);                  /* extern */
? func_80684A00(?, ?, ?, void **);                  /* extern */
? func_80684BB0(?, s16, ?);                         /* extern */
? func_80685B44(? *, ?, ?, ?, s32, s32, s32, s32, s32); /* extern */
? func_80687474(void *, ?);                         /* extern */
? func_8068780C(?, ?, ?, ?);                        /* extern */
? func_80690814(void *, ?);                         /* extern */
? func_80690A28(?, ?, ?, s32, f32, f32, f32, void *); /* extern */
? func_80697184();                                  /* extern */
? func_80714950(void *);                            /* extern */
? func_8071498C(? *);                               /* extern */
? func_807149B8(?);                                 /* extern */
? func_80714C08(? *, ?, void *, ?, s32);            /* extern */
? func_80714CC0(? *, ?, f32, f32, f32);             /* extern */
? actorSetUniformScale(void *, f32);                       /* extern */
s32 func_80724A20();                                /* extern */
? behaviourFrameBegin();                                  /* extern */
? actorApplyGravity();                                  /* extern */
? func_8072A450();                                  /* extern */
? func_8072E1A4(?, void *, ?, void **);             /* extern */
? volumeTriggerSetEnabled(s16, ?);                            /* extern */
s32 flagGet(?, ?);                            /* extern */
extern ? D_80035B84;
extern ? D_80035B98;
extern ? D_80035BD8;
extern ? D_80035BEC;
extern ? D_80036C40;
extern ? D_80036DD0;
extern ? D_8071EDEC;
extern ? D_8071FC58;
extern ? D_80720054;
extern ? D_80720BE8;
extern s16 D_807502DC;
extern f32 D_807502F0;
extern s32 D_8076A064;
extern s32 D_807F5D10;
extern void *D_807FBB40;
extern void *D_807FBB4C;
extern u8 D_807FBB85;
extern u8 D_807FBDC4;
extern void *D_807FDC90;
extern void *D_807FDCA0;

void func_80033AF0(void) {
    void *sp88;
    s32 sp84;
    u8 sp83;
    u8 sp7F;
    u8 sp7D;
    u8 sp7C;
    u8 sp7B;
    f32 sp74;
    f32 sp70;
    f32 sp68;
    f32 sp64;
    f32 sp60;
    u8 *sp50;
    f32 temp_fv0;
    f32 var_ft4;
    f32 var_fv0;
    f32 var_fv0_2;
    f32 var_fv1;
    s16 temp_v0_15;
    s16 temp_v0_19;
    s16 var_s0_2;
    s16 var_s0_3;
    s16 var_s0_4;
    s32 temp_s0;
    s32 temp_t5;
    s32 temp_v0_13;
    s32 var_v0_2;
    u8 *temp_a1;
    u8 temp_t0;
    u8 temp_t1;
    u8 temp_t1_2;
    u8 temp_t4;
    u8 temp_t5_2;
    u8 temp_t5_3;
    u8 temp_t8;
    u8 temp_t8_2;
    u8 temp_t8_3;
    u8 temp_t8_4;
    u8 temp_v0;
    u8 temp_v0_10;
    u8 temp_v0_11;
    u8 temp_v0_12;
    u8 temp_v0_14;
    u8 temp_v0_16;
    u8 temp_v0_17;
    u8 temp_v0_18;
    u8 temp_v0_4;
    u8 temp_v0_7;
    u8 temp_v0_9;
    u8 temp_v1;
    u8 temp_v1_2;
    u8 var_v0;
    u8 var_v0_3;
    u8 var_v1;
    void **temp_v1_3;
    void *temp_s0_2;
    void *temp_s1;
    void *temp_v0_2;
    void *temp_v0_3;
    void *temp_v0_5;
    void *temp_v0_6;
    void *temp_v0_8;
    void *temp_v1_4;
    void *var_s0;

    temp_s1 = D_807FBB40->unk178;
    sp88 = D_807FBB40->unk17C;
    sp84 = *(&D_80035B84 + (temp_s1->unk14 * 4));
    if (D_807FBB4C->unk80 < (D_807FBB40->unk80 - 10.0f)) {
        sp83 = 1;
    } else {
        sp83 = 0;
    }
    sp7F = 0;
    behaviourFrameBegin();
    func_8067ACB4(D_807FBB40);
    if (!(D_807FBB40->unk60 & 0x10)) {
        D_807FBB40->unkCC = 1;
        D_807FBB40->unk144 = 0x24;
        if (flagGet(0x6A, 2) != 0) {
            func_80614EBC(D_807FBB40, 0x226);
            func_8061CC40(D_807FBB40, 0x14, 1);
            sp88->unk0 = 9U;
            sp88->unk2 = 5U;
            D_807FBB40->unk154 = 0x20U;
            D_807FBB40->unk155 = 0U;
            D_807FBB40->unk155 = 0xBU;
            D_807FBB40->unk110 = 0U;
        } else {
            D_807FBB40->unk146 = 0;
            D_807FDC90->unk30 = (f32) D_807FBB40->unk4->unk38;
            actorSetUniformScale(D_807FBB40, (f32) ((f64) D_807FDC90->unk30 * 0.333));
            D_807FBB40->unk154 = 0x1EU;
            D_807FBB40->unk155 = 0U;
            D_807FBB40->unk80 = (f32) (D_807FBB40->unk80 + 650.0f);
            D_807FBB40->unk60 = (s32) (D_807FBB40->unk60 & 0xFFFF7FFF);
            sp88->unk0 = 0xFU;
        }
        D_807FBB40->unk6A = (u16) (D_807FBB40->unk6A & 0xFFFE);
        D_807FBB40->unkC4 = (f32) D_807502F0;
        D_807FBB40->unkC8 = (f32) D_807502DC;
    }
    if ((s32) temp_s1->unk14 < 2) {
        temp_v0 = sp88->unk4;
        if (temp_v0 != 0) {
            temp_t5 = (temp_v0 - 0x10) & 0xFF;
            temp_v1 = *(&D_80035BEC + temp_t5);
            sp7D = sp88->unk5 - 0x10;
            if (temp_v1 != 0) {
                sp7C = 0x46;
            } else {
                sp7C = 0xFF;
            }
            if (temp_v1 != 0) {
                sp7B = 0xA0;
            } else {
                sp7B = 0xFF;
            }
            var_v0 = sp88->unk3;
            if (var_v0 != temp_t5) {
                func_80659610(0x1388);
                temp_v0_2 = D_807FDCA0->unk14 + (temp_t5 * 0xA);
                func_8065A708((f32) temp_v0_2->unk0, (f32) (temp_v0_2->unk2 - 0x32), (f32) temp_v0_2->unk4, 0.0f, 0.0f, 0U, 0x43700000U, 0, (s32) sp7C, (s32) sp7B, 0xFF);
                var_v0 = sp88->unk3;
            }
            if (var_v0 != sp7D) {
                func_80659610(0x1388);
                temp_v0_3 = D_807FDCA0->unk14 + (sp7D * 0xA);
                func_8065A708((f32) temp_v0_3->unk0, (f32) (temp_v0_3->unk2 - 0x32), (f32) temp_v0_3->unk4, 0.0f, 0.0f, 0U, 0x43700000U, 0, (s32) sp7C, (s32) sp7B, 0xFF);
            }
        }
    }
    var_s0 = D_807FBB40;
    var_v1 = var_s0->unk154;
    if (((var_v1 == 0x27) && (temp_s1->unk14 == 4)) || ((D_807FBB85 != 0) && (var_v1 != 0x37))) {
        if (D_807FBB4C->unk154 == 0x36) {
            var_s0->unk154 = 0x2BU;
            D_807FBB40->unk155 = 0U;
            var_s0 = D_807FBB40;
        } else {
            func_80614EBC(var_s0, 0x226);
            D_807FBB40->unk154 = 0x37U;
            D_807FBB40->unk155 = 0U;
            var_s0 = D_807FBB40;
        }
        var_v1 = var_s0->unk154;
    }
    if ((var_v1 == 0x23) && (var_s0->unk155 == 1) && (sp83 == 0) && (sp88->unk6 != 0)) {
        var_s0->unk154 = 0x2BU;
        D_807FBB40->unk155 = 0U;
        var_s0 = D_807FBB40;
        var_v1 = var_s0->unk154;
    }
    switch ((s32) var_v1) {                         /* switch 1; irregular */
    case 0x1E:                                      /* switch 1 */
        var_s0_2 = 0;
        do {
            temp_a1 = &D_80036DD0 + var_s0_2;
            if (*(&D_80035B98 + ((D_807FDC90->unk2C & 0x1F) * 2)) & (1 << var_s0_2)) {
                *(&D_80036DD0 + var_s0_2) = 0xFA;
            }
            if (*temp_a1 != 0) {
                temp_v0_4 = *(&D_80035BEC + var_s0_2);
                if (temp_v0_4 != 0) {
                    var_ft4 = (f32) 0.27;
                } else {
                    var_ft4 = (f32) GLUE_F64(0x3FF00000U, 0U);
                }
                if (temp_v0_4 != 0) {
                    var_fv1 = (f32) 0.62;
                } else {
                    var_fv1 = (f32) GLUE_F64(0x3FF00000U, 0U);
                }
                sp50 = temp_a1;
                sp70 = var_fv1;
                sp74 = var_ft4;
                func_80659610(0x1388, temp_a1, &D_807FDC90);
                temp_v0_5 = D_807FDCA0->unk14 + (var_s0_2 * 0xA);
                temp_v1_2 = *temp_a1;
                var_fv0 = (f32) temp_v1_2;
                if ((s32) temp_v1_2 < 0) {
                    var_fv0 += 4294967296.0f;
                }
                func_8065A708((f32) temp_v0_5->unk0, (f32) (temp_v0_5->unk2 - 0x28A), (bitwise f32) temp_a1, (f32) temp_v0_5->unk4, 0.0f, (u32) (var_fv0 * var_ft4), (u32) (var_fv0 * var_fv1), (s32) temp_v1_2);
                *sp50 -= 0x19;
            }
            var_s0_2 += 1;
        } while (var_s0_2 < 0x10);
        if (!(D_8076A064 & 7)) {
            D_807FDC90->unk2C = (s16) (D_807FDC90->unk2C + 1);
        }
        var_s0 = D_807FBB40;
        if (D_807FBDC4 != 0) {
            var_s0->unk154 = 0x1FU;
            D_807FBB40->unk155 = 0U;
            var_s0 = D_807FBB40;
        }
        break;
    case 0x1F:                                      /* switch 1 */
        temp_s0 = (u32) ((func_80612794((s16) (D_8076A064 * 0x7D)) * 100.0f) + 155.0f) & 0xFF;
        func_80659610(0x1388);
        temp_v0_6 = D_807FDCA0->unk14;
        func_8065A708((f32) temp_v0_6->unk32, (f32) (temp_v0_6->unk34 - 0x28A), (f32) temp_v0_6->unk36, 0.0f, 0.0f, 0U, 0x43700000U, 0, temp_s0, temp_s0, temp_s0);
        if (currentActorTestClearFlag() != 0) {
            func_806086CC(D_807FBB40->unk7C, D_807FBB40->unk80, D_807FBB40->unk84, 0x19C, 0x64, 0x7F, 0, 0, 0.0f, 0);
            D_807FBB40->unk154 = 0x20U;
            D_807FBB40->unk155 = 0U;
        }
block_200:
        var_s0 = D_807FBB40;
        break;
    case 0x20:                                      /* switch 1 */
        func_8072A450();
        var_s0 = D_807FBB40;
        temp_t0 = var_s0->unk155;
        switch (temp_t0) {                          /* switch 2 */
        case 0:                                     /* switch 2 */
            func_80684A00(4, 1);
            sp7F = 1;
            actorApplyGravity();
            func_806653C0(D_807FBB40, 0, D_807FBB40->unkC0);
            func_80665564(D_807FBB40, 0);
            var_s0 = D_807FBB40;
            if (var_s0->unk110 == 1) {
                var_s0->unk155 = (u8) (var_s0->unk155 + 1);
                goto block_200;
            }
            break;
        case 1:                                     /* switch 2 */
            if (currentActorTestClearFlag() != 0) {
                D_807FBB40->unk155 = (u8) (D_807FBB40->unk155 + 1);
            }
            goto block_200;
        case 2:                                     /* switch 2 */
            func_80614EBC(var_s0, 0x225);
            func_80614D90(D_807FBB40);
            temp_s1->unk18 = 2U;
            sp88->unk2 = 0xFFU;
            sp88->unk1 = (u8) *(&D_80035BD8 + (2 & 0xFF));
            D_807FBB40->unk155 = (u8) (D_807FBB40->unk155 + 1);
            D_807FBB40->unk6A = (u16) (D_807FBB40->unk6A | 1);
            /* fallthrough */
        case 3:                                     /* switch 2 */
            func_80614D00(var_s0, 0x3F800000, 0);
            D_807FBB40->unk155 = (u8) (D_807FBB40->unk155 + 1);
            /* fallthrough */
        case 4:                                     /* switch 2 */
            func_8067ACB4(var_s0);
            func_80665564(D_807FBB40, 0);
            func_800334A4(sp88, 0.025f);
            if ((*D_807FBB40->unk4)->unk4 >= 40.0f) {
                D_807FBB40->unk6A = (u16) (D_807FBB40->unk6A | 1);
            } else {
                D_807FBB40->unk6A = 0U;
                func_80684A00(4, 1);
                sp7F = 1;
            }
            goto block_200;
        case 5:                                     /* switch 2 */
            sp88->unk0 = (u8) sp88->unk1;
            temp_v0_7 = temp_s1->unk18;
            if (temp_v0_7 != 0) {
                temp_t4 = (temp_v0_7 - 1) & 0xFF;
                temp_s1->unk18 = temp_t4;
                sp88->unk1 = (u8) *(&D_80035BD8 + temp_t4);
                D_807FBB40->unk155 = 3U;
            } else {
                func_80614EBC(D_807FBB40, 0x224);
                D_807FBB40->unk155 = (u8) (D_807FBB40->unk155 + 1);
            }
            goto block_200;
        case 6:                                     /* switch 2 */
            func_8072E1A4(0xA, D_807FBB4C);
            goto block_200;
        case 7:                                     /* switch 2 */
            func_80614EBC(var_s0, 0x222);
            D_807FBB40->unk155 = (u8) (D_807FBB40->unk155 + 1);
            /* fallthrough */
        case 8:                                     /* switch 2 */
            if (currentActorTestClearFlag() != 0) {
                D_807FBB40->unk155 = (u8) (D_807FBB40->unk155 + 1);
                func_80608528(D_807FBB40, 0x128, 0xFF, 0x19, 0);
            }
            goto block_200;
        case 9:                                     /* switch 2 */
            temp_fv0 = var_s0->unk4->unk38;
            if (temp_fv0 < D_807FDC90->unk30) {
                actorSetUniformScale(var_s0, (f32) ((f64) temp_fv0 * 1.01));
                func_800336C0();
                sp7F = 1;
            } else {
                func_80614EBC(var_s0, 0x227);
                D_807FBB40->unk155 = (u8) (D_807FBB40->unk155 + 1);
            }
            goto block_200;
        case 11:                                    /* switch 2 */
            var_s0->unk6A = (u16) (var_s0->unk6A & 0xFFFE);
            if (currentActorTestClearFlag() != 0) {
                func_80614EBC(D_807FBB40, 0x22C);
                D_807FBB40->unk155 = (u8) (D_807FBB40->unk155 + 1);
            }
            goto block_200;
        case 13:                                    /* switch 2 */
            temp_v0_8 = D_807FDCA0->unk14;
            func_80626110(D_807F5D10, temp_v0_8->unkAA, temp_v0_8->unkAE);
            temp_s1->unk14 = 0U;
            temp_s1->unk15 = 0U;
            D_807FBB40->unk154 = (u8) *((0 & 0xFF) + sp84);
            temp_s1->unk15 = (u8) (temp_s1->unk15 + 1);
            D_807FBB40->unk155 = 0U;
            sp88->unk2 = 5U;
            var_s0 = D_807FBB40;
            break;
        }
        break;
    case 0x0:                                       /* switch 1 */
        temp_v0_9 = var_s0->unk155;
        switch (temp_v0_9) {                        /* switch 3; irregular */
        case 0:                                     /* switch 3 */
        case 1:                                     /* switch 3 */
        case 2:                                     /* switch 3 */
            func_80033784(sp88, 0, 1, &D_807FBB4C);
            func_80614EBC(D_807FBB40, 0x226);
            D_807FBB40->unk155 = 3U;
            var_s0 = D_807FBB40;
            break;
        case 3:                                     /* switch 3 */
            if (D_807FBB4C->unk154 != 0x33) {
                temp_t1 = temp_s1->unk16;
                temp_s1->unk15 = temp_t1;
                D_807FBB40->unk154 = (u8) *((temp_t1 & 0xFF) + sp84);
                temp_s1->unk15 = (u8) (temp_s1->unk15 + 1);
                D_807FBB40->unk155 = 0U;
                var_s0 = D_807FBB40;
            }
            break;
        }
        break;
    case 0x23:                                      /* switch 1 */
        func_8072A450();
        var_s0 = D_807FBB40;
        temp_v0_10 = var_s0->unk155;
        switch (temp_v0_10) {                       /* switch 4; irregular */
        case 0:                                     /* switch 4 */
            temp_v0_11 = temp_s1->unk15;
            temp_t5_2 = *(temp_v0_11 + sp84);
            temp_s1->unk15 = (u8) (temp_v0_11 + 1);
            temp_s1->unk18 = temp_t5_2;
            temp_s1->unk19 = temp_t5_2;
            func_8003340C(sp88);
            sp88->unk1 = func_800330D0(temp_s1, sp88);
            D_807FBB40->unk155 = 1U;
            D_807FBB40->unk6A = (u16) (D_807FBB40->unk6A | 1);
            /* fallthrough */
        case 1:                                     /* switch 4 */
            var_s0->unk155 = 2U;
            func_80614D00(D_807FBB40, *(&D_80036C40 + (temp_s1->unk14 * 4)), 0);
            sp88->unk6 = sp83;
            /* fallthrough */
        case 2:                                     /* switch 4 */
            func_8067ACB4(var_s0);
            func_80665564(D_807FBB40, 0);
            if (D_807FBB40->unk4->unk64 == 0x223) {
                var_fv0_2 = 0.02173913f;
            } else {
                var_fv0_2 = 0.041666664f;
            }
            func_800334A4(sp88, var_fv0_2);
            var_v0_2 = 0x17;
            temp_v1_3 = D_807FBB40->unk4;
            if (temp_v1_3->unk64 == 0x223) {
                var_v0_2 = 0x35;
            }
            if ((f32) var_v0_2 <= temp_v1_3->unk0->unk4) {
                D_807FBB40->unk6A = (u16) (D_807FBB40->unk6A | 1);
            } else {
                D_807FBB40->unk6A = 0U;
                func_80684A00(4, 1);
                sp7F = 1;
            }
            goto block_200;
        case 3:                                     /* switch 4 */
            sp88->unk2 = (u8) sp88->unk0;
            sp88->unk0 = (u8) sp88->unk1;
            if (sp83 != 0) {
                temp_s1->unk18 = (u8) temp_s1->unk19;
            }
            if (temp_s1->unk18 != 0) {
                sp88->unk1 = func_800330D0(temp_s1, sp88);
                temp_s1->unk18 = (u8) (temp_s1->unk18 - 1);
                func_8003340C(sp88);
                D_807FBB40->unk155 = 1U;
            } else {
                D_807FBB40->unk154 = (u8) *(temp_s1->unk15 + sp84);
                temp_s1->unk15 = (u8) (temp_s1->unk15 + 1);
                D_807FBB40->unk155 = 0U;
            }
            goto block_200;
        }
        break;
    case 0x25:                                      /* switch 1 */
    case 0x28:                                      /* switch 1 */
        func_8072E1A4(0xA, D_807FBB4C, 1, &D_807FBB4C);
        if (func_800339D8(temp_s1, sp84) != 0) {
            func_80033784(sp88, 0);
        } else if (func_80724A20() == 0) {
            temp_s0_2 = D_807FBB40;
            temp_t8 = temp_s0_2->unk155;
            switch (temp_t8) {                      /* switch 5 */
            case 0:                                 /* switch 5 */
                func_80033784(sp88, 0xA);
                temp_v0_12 = temp_s1->unk15;
                temp_t5_3 = temp_v0_12 + 1;
                temp_v0_13 = temp_t5_3 & 0xFF;
                temp_s1->unk18 = (u8) (*(temp_v0_12 + sp84) - 1);
                temp_s1->unk15 = temp_t5_3;
                temp_s1->unk15 = (u8) (temp_v0_13 + 1);
                temp_s1->unk19 = (u8) *(temp_v0_13 + sp84);
                func_80614EBC(D_807FBB40, 0x229);
                D_807FBB40->unk155 = 1U;
                break;
            case 2:                                 /* switch 5 */
                if (temp_s0_2->unk154 == 0x25) {
                    func_80614EBC(temp_s0_2, 0x228);
                    goto block_131;
                }
                if (!(D_807FDC90->unk1A & 0x8000)) {
                    if (D_807FBB4C->unk110 == 1) {
                        func_8061CC40(temp_s0_2, 0xF, 1);
                        D_807FDC90->unk1A = (u16) (D_807FDC90->unk1A | 0x8000);
                        goto block_130;
                    }
                } else {
block_130:
                    func_80614EBC(temp_s0_2, 0x22F);
block_131:
                    D_807FBB40->unk155 = 3U;
                }
                break;
            case 3:                                 /* switch 5 */
                if (temp_s0_2->unk154 == 0x25) {
                    func_80684A00(3, 1);
                    sp7F = 1;
                } else {
                    func_80671C0C(temp_s0_2, 1, &sp68, &sp64, &sp60);
                    sp68 += (f32) (((s32) (func_80611A44() >> 0xF) % 100) - 0x32);
                    sp64 += (f32) (((s32) (func_80611A44() >> 0xF) % 100) + 0x32);
                    sp60 += (f32) (((s32) (func_80611A44() >> 0xF) % 100) - 0x32);
                    func_807149B8(1);
                    func_8071498C(&D_8071EDEC);
                    func_80714950(D_807FBB40);
                    func_80714CC0(&D_8071FC58, 0x3FC00000, sp68, sp64, sp60);
                    func_80714C08(&D_80720054, 0x40400000, D_807FBB40, 1, 2);
                }
                break;
            case 4:                                 /* switch 5 */
                if (temp_s0_2->unk154 == 0x25) {
                    func_80690814(temp_s0_2, 3);
                    func_80690A28(0x3B, 1, 0x3F99999A, D_807FBB4C->unk7C, D_807FBB4C->unk80 + 5.0f, D_807FBB4C->unk84, 900.0f, D_807FBB40);
                } else {
                    sp88->unk1 = func_800330D0(temp_s1, sp88);
                    func_8003392C(sp88);
                }
                D_807FBB40->unk155 = 5U;
                break;
            case 6:                                 /* switch 5 */
                temp_v0_14 = temp_s1->unk18;
                if (temp_v0_14 != 0) {
                    temp_s1->unk18 = (u8) (temp_v0_14 - 1);
                    D_807FDC90->unk2C = (s16) temp_s1->unk19;
                    D_807FBB40->unk155 = 7U;
                } else {
                    func_80614EBC(temp_s0_2, 0x22D);
                    D_807FBB40->unk155 = 8U;
                }
                break;
            case 7:                                 /* switch 5 */
                temp_v0_15 = D_807FDC90->unk2C;
                if (temp_v0_15 != 0) {
                    if (D_807FBB4C->unk154 == 0x33) {
                        D_807FDC90->unk2C = (s16) temp_s1->unk19;
                    } else {
                        D_807FDC90->unk2C = (s16) (temp_v0_15 - 1);
                    }
                } else {
                    temp_s0_2->unk155 = 2;
                }
                break;
            case 9:                                 /* switch 5 */
                func_80033784(sp88, 0);
                func_80614EBC(D_807FBB40, 0x22C);
                D_807FBB40->unk155 = 0xAU;
                break;
            case 11:                                /* switch 5 */
                temp_s0_2->unk154 = (u8) *(temp_s1->unk15 + sp84);
                temp_s1->unk15 = (u8) (temp_s1->unk15 + 1);
                D_807FBB40->unk155 = 0U;
                break;
            }
        }
        goto block_200;
    case 0x27:                                      /* switch 1 */
        temp_v0_16 = var_s0->unk155;
        switch (temp_v0_16) {                       /* switch 6 */
        case 0:                                     /* switch 6 */
        case 1:                                     /* switch 6 */
        case 2:                                     /* switch 6 */
            func_80697184();
            func_80033784(sp88, 0);
            func_80614EBC(D_807FBB40, 0x22E);
            func_8061CC40(D_807FBB40, 2, 1);
            func_80687474(D_807FBB40, 0x3F99999A);
            func_806086CC(D_807FBB40->unk7C, D_807FBB40->unk80, D_807FBB40->unk84, 0x305, 0xFF, 0x7F, 0, 0, 0.0f, 0);
            D_807FBB40->unk155 = 3U;
            var_s0 = D_807FBB40;
            break;
        case 4:                                     /* switch 6 */
            func_8068780C(7, 0xB, 0x11, 0x20);
            func_8068780C(0xC, 0x10, 0x11, 0x20);
            goto block_200;
        case 5:                                     /* switch 6 */
            func_806845B8(7, 0x20, 1, &D_807FBB4C);
            if ((currentActorTestClearFlag() != 0) || (func_8061CB50() == 0)) {
                D_807FBB40->unk155 = (u8) (D_807FBB40->unk155 + 1);
            }
            goto block_200;
        case 6:                                     /* switch 6 */
            if ((s32) temp_s1->unk14 < 3) {
                func_80614EBC(var_s0, 0x22C, 1, &D_807FBB4C);
            } else {
                var_s0->unk155 = (u8) (temp_v0_16 + 1);
            }
            D_807FBB40->unk155 = (u8) (D_807FBB40->unk155 + 1);
            var_s0 = D_807FBB40;
            break;
        case 8:                                     /* switch 6 */
            currentActorClearFlag();
            temp_s1->unk15 = 0U;
            temp_t8_2 = temp_s1->unk14 + 1;
            temp_s1->unk14 = temp_t8_2;
            D_807FBB40->unk154 = (u8) *((0 & 0xFF) + *(&D_80035B84 + ((temp_t8_2 & 0xFF) * 4)));
            temp_s1->unk15 = (u8) (temp_s1->unk15 + 1);
            D_807FBB40->unk155 = 0U;
            var_s0 = D_807FBB40;
            break;
        }
        break;
    case 0x29:                                      /* switch 1 */
        temp_t8_3 = var_s0->unk155;
        switch (temp_t8_3) {                        /* switch 7 */
        case 0:                                     /* switch 7 */
            var_s0->unk60 = (s32) (var_s0->unk60 & 0xFFFF7FFF);
            func_80614EBC(D_807FBB40, 0x231, 1, &D_807FBB4C);
            temp_v0_17 = temp_s1->unk15;
            temp_s1->unk15 = (u8) (temp_v0_17 + 1);
            temp_s1->unk8 = (s16) *(temp_v0_17 + sp84);
            D_807FBB40->unk155 = (u8) (D_807FBB40->unk155 + 1);
            var_s0 = D_807FBB40;
            break;
        case 2:                                     /* switch 7 */
            func_80684A00(2, 1, 1, &D_807FBB4C);
            func_80684A00(3, 1);
            sp7F = 1;
            goto block_200;
        case 3:                                     /* switch 7 */
            func_80684BB0(2, (s16) (((s32) ((s32) (func_80611A44() >> 0xF) % 32767) % 6) + 5), 0x28);
            func_80684BB0(3, (s16) (((s32) ((s32) (func_80611A44() >> 0xF) % 32767) % 6) + 5), 0x28);
            sp7F = 1;
            goto block_200;
        case 4:                                     /* switch 7 */
            func_80033A80(temp_s1->unk9);
            goto block_200;
        case 5:                                     /* switch 7 */
            var_s0->unk154 = (u8) *(temp_s1->unk15 + sp84);
            temp_s1->unk15 = (u8) (temp_s1->unk15 + 1);
            D_807FBB40->unk155 = 0U;
            var_s0 = D_807FBB40;
            break;
        }
        break;
    case 0x2B:                                      /* switch 1 */
        temp_v0_18 = var_s0->unk155;
        switch (temp_v0_18) {                       /* switch 8; irregular */
        case 0:                                     /* switch 8 */
            func_80614EBC(var_s0, 0x222, 1, &D_807FBB4C);
            D_807FDC90->unk2C = 0x5A;
            D_807FBB40->unk155 = (u8) (D_807FBB40->unk155 + 1);
            var_s0 = D_807FBB40;
            break;
        case 1:                                     /* switch 8 */
            temp_v0_19 = D_807FDC90->unk2C;
            if (temp_v0_19 != 0) {
                D_807FDC90->unk2C = (s16) (temp_v0_19 - 1);
            } else {
                temp_t1_2 = temp_s1->unk16;
                temp_s1->unk15 = temp_t1_2;
                D_807FBB40->unk154 = (u8) *((temp_t1_2 & 0xFF) + sp84);
                temp_s1->unk15 = (u8) (temp_s1->unk15 + 1);
                D_807FBB40->unk155 = 0U;
            }
            goto block_200;
        }
        break;
    case 0x37:                                      /* switch 1 */
        temp_t8_4 = var_s0->unk155;
        switch (temp_t8_4) {                        /* switch 9 */
        case 0:                                     /* switch 9 */
            func_8061CC40(var_s0, 6, 0x81, &D_807FBB4C);
            D_807FBB40->unk155 = (u8) (D_807FBB40->unk155 + 1);
            var_s0 = D_807FBB40;
            break;
        case 1:                                     /* switch 9 */
            if (currentActorTestClearFlag() != 0) {
                D_807FBB40->unk155 = (u8) (D_807FBB40->unk155 + 1);
            }
            goto block_200;
        case 2:                                     /* switch 9 */
            func_80033A80(5);
            goto block_200;
        case 3:                                     /* switch 9 */
            if (currentActorTestClearFlag() != 0) {
                func_8063DA40(sp88->unk0, 0x1E);
                D_807FBB40->unk155 = (u8) (D_807FBB40->unk155 + 1);
            }
            goto block_200;
        case 4:                                     /* switch 9 */
            if (currentActorTestClearFlag() != 0) {
                func_80685B44(&D_80720BE8, 0, 0x40C00000, 6, 0x50, 0x64, (s32) D_807FBB40->unk7C, (s32) (D_807FBB4C->unk80 + 100.0f), (s32) D_807FBB40->unk84);
                func_80685B44(&D_80720BE8, 0x14, 0x40C00000, 8, 0x96, 0x46, (s32) D_807FBB40->unk7C, (s32) (D_807FBB4C->unk80 + 100.0f), (s32) D_807FBB40->unk84);
                D_807FBB40->unk155 = (u8) (D_807FBB40->unk155 + 1);
            }
            goto block_200;
        case 5:                                     /* switch 9 */
            if (func_8061CB50() == 0) {
                func_80033784(sp88, 0);
                var_s0_3 = 0;
                var_v0_3 = sp88->unk0;
                do {
                    if (var_s0_3 != var_v0_3) {
                        func_8063DA40((u8) var_s0_3, 0x28);
                        var_v0_3 = sp88->unk0;
                    }
                    var_s0_3 += 1;
                } while (var_s0_3 < 0x10);
                temp_v1_4 = D_807FDCA0->unk14 + (var_v0_3 * 0xA);
                func_80028478(0x8A, temp_v1_4->unk0, temp_v1_4->unk2, temp_v1_4->unk4, 0x5DC, 1);
                var_s0_4 = 0;
                D_807FBB40->unk154 = 0x40U;
                do {
                    volumeTriggerSetEnabled(var_s0_4, 0);
                    var_s0_4 += 1;
                } while (var_s0_4 < 7);
            }
            goto block_200;
        }
        break;
    default:                                        /* switch 1 */
        func_80027BA8(sp84, 0, 0, &D_807FBB4C);
        goto block_200;
    }
    if (sp7F != 0) {
        if (var_s0->unk6E == -1) {
            func_80604CBC(var_s0, 0x135, 0x4B, 1, 0, 0xB4, 1.0f, 0);
            goto block_205;
        }
    } else {
        func_80605314(var_s0, 0);
block_205:
        var_s0 = D_807FBB40;
    }
    actorUpdateModelMatrix(var_s0, 0);
}
