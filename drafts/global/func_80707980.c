// func_80707980 (src/global/109660.c): m2c reconstruction; stage 4 reached in private compile (0x40 frame, s0/ra saves), but shared return tail and block ordering still differ.
s32 func_8061CB50();                                /* extern */
? func_8068B830(f64, ?, s16, s16, s16);             /* extern */
? func_8068B8A4(f32, ?);                            /* extern */
? func_8068B8FC();                                  /* extern */
void *func_80704B20(void *, s32, s32, s32, s32, s32, s32, s32, f32); /* extern */
? func_80705C00(?, ?, ?);                           /* extern */
void *func_80705F5C(void *, ?, ?, ?);               /* extern */
void *func_807069A4(void *, s32, s32, ?, f32, f32); /* extern */
void *func_8070770C(void *, ?);                     /* extern */
extern f32 D_80754CE8;
extern s32 D_8076A0A8;
extern u8 D_8076AEE0;
extern void *D_807FBB4C;
extern void *D_807FC924;
extern s16 D_807FD800;
extern f32 D_807FD88C;

void *func_80707980(void *arg0, s32 arg1, s32 arg2, s32 arg3, s16 arg4) {
    f32 sp38;
    f32 temp_fv0;
    f32 temp_fv0_2;
    f32 temp_fv1;
    f32 var_fa1;
    f32 var_ft4;
    f32 var_fv1;
    f64 temp_fa0;
    s16 temp_t3_2;
    s16 temp_v0;
    s16 temp_v0_2;
    s16 temp_v0_3;
    s32 temp_a2;
    s32 var_v0;
    u16 temp_t3;
    void *temp_s0;
    void *temp_s0_2;
    void *temp_s0_3;
    void *temp_s0_4;
    void *temp_s0_5;
    void *temp_v0_4;
    void *temp_v0_5;
    void *var_s0;

    arg0->unk0 = 0xE7000000;
    arg0->unk4 = 0;
    var_s0 = arg0 + 8;
    if ((D_807FD88C != 0.0f) && (D_8076AEE0 == 3)) {
        var_s0 = func_8070770C(var_s0);
    }
    switch (D_8076A0A8) {                           /* switch 1 */
    case 0x53:                                      /* switch 1 */
    case 0x9A:                                      /* switch 1 */
    case 0xC5:                                      /* switch 1 */
    case 0xC6:                                      /* switch 1 */
        return var_s0;
    case 0xE:                                       /* switch 1 */
        var_s0 = func_807069A4(var_s0, arg1, arg2, 0x2D, 320.0f, 240.0f);
block_56:
        D_80754CE8 = 0.0f;
        var_s0->unk0 = 0xE7000000;
        var_s0->unk4 = 0;
        return var_s0 + 8;
    case 0x3:                                       /* switch 1 */
    case 0xB:                                       /* switch 1 */
    case 0x41:                                      /* switch 1 */
    case 0x42:                                      /* switch 1 */
    case 0x43:                                      /* switch 1 */
    case 0x44:                                      /* switch 1 */
    case 0x45:                                      /* switch 1 */
    case 0x4A:                                      /* switch 1 */
    case 0x4B:                                      /* switch 1 */
    case 0x7C:                                      /* switch 1 */
    case 0x7D:                                      /* switch 1 */
    case 0x7E:                                      /* switch 1 */
    case 0x7F:                                      /* switch 1 */
    case 0x80:                                      /* switch 1 */
        var_s0 = func_807069A4(var_s0, arg1, arg2, 0x2E, 320.0f, 240.0f);
        goto block_56;
    case 0x26:                                      /* switch 1 */
        temp_t3 = D_807FC924->unk290;
        switch (temp_t3) {                          /* switch 2 */
        case 0:                                     /* switch 2 */
        case 1:                                     /* switch 2 */
        case 3:                                     /* switch 2 */
        case 6:                                     /* switch 2 */
        case 8:                                     /* switch 2 */
        case 10:                                    /* switch 2 */
            var_s0 = func_8070770C(var_s0);
            break;
        default:                                    /* switch 2 */
            func_80705C00(0x3E8, 0x4E20, 0);
            var_s0 = func_80704B20(var_s0, arg1, arg2, arg3, 0, 0, 0, -1, 0.0f);
            break;
        }
        goto block_56;
    case 0x1E:                                      /* switch 1 */
        temp_v0 = (s16) D_807FC924->unk290;
        if (((temp_v0 != 7) && (temp_v0 != 6) && (temp_v0 != 8) && (temp_v0 != 0)) || (D_807FD800 != 0)) {
            temp_v0_2 = D_807FBB4C->unk12C;
            if ((temp_v0_2 == 9) || (temp_v0_2 == 0xB) || (temp_v0_2 == 3)) {
                var_v0 = 1;
            } else {
                var_v0 = 0;
            }
            var_s0 = func_80704B20(var_s0, arg1, arg2, arg3, 0, 0, var_v0, 9, 0.0f);
        }
        goto block_56;
    case 0x27:                                      /* switch 1 */
        func_80705C00(0xBB8, 0x2328, 0);
        var_s0 = func_80704B20(var_s0, arg1, arg2, arg3, 0, 0, 0, -1, 0.0f);
        goto block_56;
    case 0x4:                                       /* switch 1 */
        var_s0 = func_8070770C(var_s0);
        goto block_56;
    case 0xB0:                                      /* switch 1 */
        var_s0 = func_8070770C(var_s0);
        goto block_56;
    case 0x7:                                       /* switch 1 */
        temp_t3_2 = (s16) D_807FC924->unk290;
        switch (temp_t3_2) {                        /* switch 3 */
        case 8:                                     /* switch 3 */
        case 9:                                     /* switch 3 */
        case 12:                                    /* switch 3 */
        case 16:                                    /* switch 3 */
            var_s0 = func_8070770C(var_s0);
            break;
        case 11:                                    /* switch 3 */
        case 14:                                    /* switch 3 */
            func_80705C00(0, 0x7530, 1);
            var_s0 = func_80704B20(var_s0, arg1, arg2, arg3, 4, 4, 1, -1, 0.0f);
            break;
        default:                                    /* switch 3 */
            func_80705C00(0, 0x7530, 0);
            var_s0 = func_80704B20(var_s0, arg1, arg2, arg3, 4, 4, 0, -1, 0.0f);
            break;
        }
        goto block_56;
    case 0x8:                                       /* switch 1 */
        var_s0 = func_80705F5C(func_80704B20(var_s0, arg1, arg2, arg3, 3, 3, 1, -1, 0.0f), 0, 0x7D00, 0);
        goto block_56;
    case 0x30:                                      /* switch 1 */
        temp_v0_3 = (s16) D_807FC924->unk290;
        if ((temp_v0_3 >= 0xC) && (temp_v0_3 < 0x12)) {
            var_s0 = func_8070770C(var_s0, 0x5DC0);
        } else {
            func_80705C00(0, 0x5DC0, 1);
            var_s0 = func_80705F5C(func_80704B20(var_s0, arg1, arg2, arg3, 2, 2, 1, -1, 0.0f), 0, 0x5DC0, 1);
        }
        goto block_56;
    case 0x37:                                      /* switch 1 */
        var_s0 = func_80704B20(var_s0, arg1, arg2, arg3, 1, 1, 1, -1, 0.0f);
        goto block_56;
    case 0x22:                                      /* switch 1 */
        if (func_8061CB50() != 0) {
            var_fa1 = D_807FC924->unk210;
            var_ft4 = D_807FC924->unk218;
        } else {
            var_fa1 = D_807FBB4C->unk7C;
            var_ft4 = D_807FBB4C->unk84;
        }
        temp_fv0 = var_fa1 - 3000.0f;
        temp_fv1 = var_ft4 - 5000.0f;
        temp_fv0_2 = sqrtf((temp_fv0 * temp_fv0) + (temp_fv1 * temp_fv1));
        if (temp_fv0_2 < 2500.0f) {
            temp_fa0 = (f64) ((2500.0f - temp_fv0_2) / 1000.0f);
            if (temp_fa0 > 1.0) {
                var_fv1 = (f32) 1.0;
            } else {
                var_fv1 = (f32) temp_fa0;
            }
            sp38 = var_fv1;
            func_8068B830(temp_fa0, 0, (s16) (s32) (2.0f + var_fv1), (s16) (s32) (var_fv1 * 400.0f), (s16) (s32) (var_fv1 * 30.0f));
            func_8068B8A4((f32) (((f64) var_fv1 * -0.6) + 1.0), 0);
        } else {
            func_8068B8FC();
            func_8068B8A4(1.0f);
        }
        func_80705C00(0xBB8, 0x4E20, 0);
        var_s0 = func_80704B20(var_s0, arg1, arg2, arg3, 5, 6, 1, -1, 0.0f);
        goto block_56;
    case 0x99:                                      /* switch 1 */
    case 0xAC:                                      /* switch 1 */
        func_80705C00(0xBB8, 0x4E20, 0);
        var_s0 = func_80704B20(var_s0, arg1, arg2, arg3, 5, 5, 1, -1, 0.0f);
        goto block_56;
    case 0x6F:                                      /* switch 1 */
        var_s0 = func_80705F5C(func_80704B20(var_s0, arg1, arg2, arg3, 6, 6, 1, -1, 0.0f), 0xC8, 0x4268, 0);
        goto block_56;
    case 0x57:                                      /* switch 1 */
        var_s0 = func_80705F5C(func_80704B20(var_s0, arg1, arg2, arg3, 6, 6, 1, -1, 0.0f), 0x3E8, 0x2EE0, 0);
        goto block_56;
    case 0xD5:                                      /* switch 1 */
        func_80705C00(0x8FC, 0x1388, 0);
        var_s0 = func_80704B20(var_s0, arg1, arg2, arg3, 7, 7, 0, -1, 0.0f);
        goto block_56;
    case 0xD0:                                      /* switch 1 */
        var_s0->unk4 = -1;
        var_s0->unk0 = 0xF7000000;
block_55:
        temp_s0 = var_s0 + 8;
        temp_s0_2 = temp_s0 + 8;
        var_s0->unk8 = 0xE200001C;
        temp_s0->unk4 = 0;
        temp_s0_2->unk4 = 0x300000;
        temp_s0->unk8 = 0xE3000A01;
        temp_a2 = arg4 * 0x2F0;
        temp_v0_4 = D_807FC924 + temp_a2;
        temp_s0_3 = temp_s0_2 + 8;
        temp_s0_2->unk8 = (s32) ((((temp_v0_4->unk276 - 1) & 0x3FF) * 4) | 0xF6000000 | (((temp_v0_4->unk274 - 1) & 0x3FF) << 0xE));
        temp_s0_4 = temp_s0_3 + 8;
        temp_v0_5 = D_807FC924 + temp_a2;
        temp_s0_5 = temp_s0_4 + 8;
        temp_s0_3->unk4 = (s32) (((temp_v0_5->unk272 & 0x3FF) * 4) | ((temp_v0_5->unk270 & 0x3FF) << 0xE));
        temp_s0_3->unk8 = 0xE7000000;
        temp_s0_4->unk4 = 0;
        temp_s0_5->unk4 = 0;
        temp_s0_4->unk8 = 0xE3000A01;
        var_s0 = temp_s0_5 + 8;
        goto block_56;
    case 0x36:                                      /* switch 1 */
        var_s0->unk0 = 0xF7000000;
        var_s0->unk4 = 0xFFC1FFC1;
        goto block_55;
    case 0x50:                                      /* switch 1 */
        func_80705C00(0x8FC, 0x1388, 1);
        var_s0 = func_80705F5C(func_80704B20(var_s0, arg1, arg2, arg3, 7, 6, 0, -1, D_80754CE8), 0xC8, 0x2EE0, 2);
        goto block_56;
    default:                                        /* switch 1 */
        var_s0->unk0 = 0xF7000000;
        var_s0->unk4 = 0x10001;
        goto block_55;
    }
}
