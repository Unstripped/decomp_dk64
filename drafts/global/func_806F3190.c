// func_806F3190 (src/global/F56F0.c): stage 1 m2c reconstruction; requires local views and exact switch/call signatures
? func_806F1768(s32 *, s32, s32 *);                 /* extern */
? func_806F1858(s32 *, s32, s32 *);                 /* extern */
? func_806F18F4(s32 *, s32, s32 *);                 /* extern */
? func_806F1990(s32 *, s32, s32 *);                 /* extern */
? func_806F1C04(s32 *, s32, s32 *);                 /* extern */
? func_806F1EB0(s32 *, s32, s32 *);                 /* extern */
? func_806F22A8(s32 *, s32, s32 *);                 /* extern */
? func_806F2754(s32 *, s32, s32 *);                 /* extern */
? func_806F2A40(s32 *, s32 *, s32 *);               /* extern */
? func_806F2C48(s32 *, s32, s32 *);                 /* extern */
? func_806F2EDC(s32 *, s32 *, s32 *, s32 *, s32 *, f32, f32, f32, f32); /* extern */
? func_806F2FC0(s32 *, void *, u16);                /* extern */
s32 func_80714608(?);                               /* extern */
extern s32 D_8076A0A8;

void func_806F3190(s32 *arg0, u16 arg1) {
    void *sp74;
    s32 sp70;
    s32 sp6C;
    s32 sp64;
    s32 *sp60;
    s8 *sp5C;
    f32 sp58;
    f32 temp_fv0;
    f32 temp_fv0_3;
    f32 temp_fv0_5;
    f32 temp_fv0_7;
    f32 var_fv1;
    f32 var_fv1_2;
    f32 var_fv1_3;
    f32 var_fv1_4;
    f32 var_fv1_5;
    f32 var_fv1_6;
    f32 var_fv1_7;
    f32 var_fv1_8;
    f64 temp_fv0_2;
    f64 temp_fv0_4;
    f64 temp_fv0_6;
    f64 temp_fv0_8;
    f64 var_fv0;
    f64 var_fv0_2;
    u8 temp_t9;
    u8 temp_v0_2;
    u8 temp_v0_3;
    void **temp_v0;

    sp74 = arg0->unk174;
    if ((arg0->unk154 != 0x77) && (arg0->unk60 & 4)) {
        temp_v0 = arg0->unk4;
        sp64 = temp_v0->unk1C;
        sp60 = temp_v0->unk20;
        sp70 = 0;
        sp6C = 0;
        sp5C = temp_v0->unk24;
        if ((func_80714608(0) != 0) && ((sp74->unk21E != 0x1E) || (arg0->unk154 == 0x34))) {
            func_806F2A40(arg0, sp60, &sp6C);
        }
        switch (arg1) {                             /* switch 1 */
        case 0:                                     /* switch 1 */
            func_806F2C48(arg0, sp64, &sp70);
            func_806F1C04(arg0, sp64, &sp70);
            if (sp74->unk8E != 0) {
                func_806F1858(arg0, sp64, &sp70);
            }
            break;
        case 1:                                     /* switch 1 */
            temp_t9 = arg0->unk154;
            switch (temp_t9) {                      /* switch 2 */
            case 7:                                 /* switch 2 */
            case 8:                                 /* switch 2 */
            case 9:                                 /* switch 2 */
            case 10:                                /* switch 2 */
            case 11:                                /* switch 2 */
                break;
            case 2:                                 /* switch 2 */
                func_806F2754(arg0, sp64, &sp70);
                break;
            default:                                /* switch 2 */
            case 3:                                 /* switch 2 */
            case 4:                                 /* switch 2 */
            case 5:                                 /* switch 2 */
            case 6:                                 /* switch 2 */
                func_806F2C48(arg0, sp64, &sp70);
                break;
            }
            func_806F22A8(arg0, sp64, &sp70);
            if (sp74->unk8E != 0) {
                func_806F1768(arg0, sp64, &sp70);
            }
            break;
        case 2:                                     /* switch 1 */
            temp_v0_2 = arg0->unk154;
            switch (temp_v0_2) {                    /* switch 3; irregular */
            case 38:                                /* switch 3 */
                if (arg0->unk155 != 0) {
                    temp_fv0 = (*arg0->unk4)->unk4;
                    if (temp_fv0 < 6.0f) {
                        var_fv1 = 0.0f;
                    } else {
                        var_fv1 = temp_fv0 - 6.0f;
                    }
                    temp_fv0_2 = (f64) var_fv1 / 17.0;
                    if (temp_fv0_2 > 1.0) {
                        var_fv1_2 = (f32) 1.0;
                    } else {
                        var_fv1_2 = (f32) temp_fv0_2;
                    }
                    if (D_8076A0A8 == 0xCD) {
                        var_fv0 = 17.0;
                    } else {
                        var_fv0 = 0.0;
                    }
                    func_806F2EDC(NULL, NULL, arg0, sp60, &sp6C, 1.4e-44f, 1.5e-44f, var_fv1_2, (f32) var_fv0);
                }
                break;
            case 39:                                /* switch 3 */
                temp_fv0_3 = (*arg0->unk4)->unk4;
                if (temp_fv0_3 < 6.0f) {
                    var_fv1_3 = 0.0f;
                } else {
                    var_fv1_3 = temp_fv0_3 - 6.0f;
                }
                temp_fv0_4 = (f64) var_fv1_3 / 17.0;
                if (temp_fv0_4 > 1.0) {
                    var_fv1_4 = (f32) 1.0;
                } else {
                    var_fv1_4 = (f32) temp_fv0_4;
                }
                if (D_8076A0A8 == 0xCD) {
                    var_fv0_2 = 17.0;
                } else {
                    var_fv0_2 = 0.0;
                }
                func_806F2EDC(NULL, NULL, arg0, sp60, &sp6C, 7e-45f, 8e-45f, var_fv1_4, (f32) var_fv0_2);
                break;
            case 40:                                /* switch 3 */
                temp_fv0_5 = (*arg0->unk4)->unk4;
                if (temp_fv0_5 < 7.0f) {
                    var_fv1_5 = 0.0f;
                } else {
                    var_fv1_5 = temp_fv0_5 - 7.0f;
                }
                temp_fv0_6 = (f64) var_fv1_5 / 14.0;
                if (temp_fv0_6 > 1.0) {
                    var_fv1_6 = (f32) 1.0;
                } else {
                    var_fv1_6 = (f32) temp_fv0_6;
                }
                sp58 = var_fv1_6;
                func_806F2EDC(NULL, arg0, sp60, &sp6C, (s32 *)9, 1.5e-44f, var_fv1_6, 1.8f);
                func_806F2EDC(arg0, sp60, &sp6C, (s32 *)4, (s32 *)6, sp58, 1.8f);
                break;
            case 41:                                /* switch 3 */
                temp_fv0_7 = (*arg0->unk4)->unk4;
                if (temp_fv0_7 < 4.0f) {
                    var_fv1_7 = 0.0f;
                } else {
                    var_fv1_7 = temp_fv0_7 - 4.0f;
                }
                temp_fv0_8 = (f64) var_fv1_7 / 6.0;
                if (temp_fv0_8 > 1.0) {
                    var_fv1_8 = (f32) 1.0;
                } else {
                    var_fv1_8 = (f32) temp_fv0_8;
                }
                sp58 = var_fv1_8;
                func_806F2EDC(NULL, arg0, sp60, &sp6C, (s32 *)9, 1.5e-44f, var_fv1_8, 1.3f);
                func_806F2EDC(arg0, sp60, &sp6C, (s32 *)4, (s32 *)6, sp58, 1.3f);
                break;
            }
            break;
        case 3:                                     /* switch 1 */
            func_806F1EB0(arg0, sp64, &sp70);
            if (sp74->unk8E != 0) {
                func_806F1990(arg0, sp64, &sp70);
            }
            break;
        case 4:                                     /* switch 1 */
        case 5:                                     /* switch 1 */
            if (sp74->unk8E != 0) {
                func_806F18F4(arg0, sp64, &sp70);
            }
            break;
        }
        *(sp64 + (sp70 * 8)) = 0;
        *(sp60 + (sp6C * 0x10)) = 0xFF;
        *sp5C = 0xFF;
        temp_v0_3 = sp74->unk8E;
        if (temp_v0_3 != 0) {
            sp74->unk8E = (u8) (temp_v0_3 - 1);
            if (sp74->unk8C != 0) {
                func_806F2FC0(arg0, sp74, arg1);
            }
        }
        if (sp74->unk8E == 0) {
            sp74->unk8F = 0;
        }
    }
}
