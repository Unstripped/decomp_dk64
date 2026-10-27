// func_80027BA8 (src/boss/3840.c): from .scratch/Boss3C/func_80027BA8_best.c
? func_80027950(void *, s32, u8, void *);           /* extern */
? func_80027A30(void *, s32, u8, void *);           /* extern */
? func_80614EBC(void *, s32, u8, void *);           /* extern */
? func_8061CC40(void *, u8, ?, void *);             /* extern */
? func_8061D4E4(s32, u8, void *);                   /* extern */
s32 currentActorTestClearFlag(u8, void *);                      /* extern */
? currentActorClearFlag(u8, void *);                        /* extern */
? func_8070D8C0(void *, u8, u8, void *);            /* extern */
? actorMoveWithinZone(?, f32, f32, u16, f32);             /* extern */
? actorSetTargetSpeed(void *, u8, u8, void *);            /* extern */
s32 func_8072D13C(u8, ?);                           /* extern */
extern u8 D_807444EC;
extern u8 D_8076A0B1;
extern s8 D_8076A0B3;
extern void *D_807FBB40;
extern void *D_807FBB4C;
extern void *D_807FDC90;
extern void *D_807FDC9C;

u8 func_80027BA8(s32 arg0, u16 arg1, f32 arg2) {
    void *sp34;
    u8 sp2F;
    u8 sp2E;
    s16 temp_a0;
    u8 temp_a2;
    u8 temp_v0;
    u8 temp_v0_10;
    u8 temp_v0_11;
    u8 temp_v0_12;
    u8 temp_v0_13;
    u8 temp_v0_2;
    u8 temp_v0_3;
    u8 temp_v0_4;
    u8 temp_v0_5;
    u8 temp_v0_6;
    u8 temp_v0_7;
    u8 temp_v0_9;
    u8 var_t1;
    void *temp_a3;
    void *temp_s0;
    void *temp_v0_8;
    void *temp_v1;
    void *temp_v1_2;

    temp_a3 = D_807FBB40;
    temp_v1 = D_807FBB4C->unk174;
    temp_s0 = temp_a3->unk178;
    sp2E = 0;
    temp_a2 = temp_a3->unk154;
    var_t1 = 1;
    switch ((s32) temp_a2) {                        /* switch 1; irregular */
    case 0x54:                                      /* switch 1 */
        if (temp_a3->unk155 != 0) {
            sp2F = 0;
            var_t1 = sp2F;
            if (currentActorTestClearFlag(temp_a2, temp_a3) != 0) {
                var_t1 = 1;
            }
        } else {
            sp2F = 0;
            currentActorClearFlag(temp_a2, temp_a3);
            var_t1 = 0;
            D_807FBB40->unk155 = 1U;
        }
        break;
    case 0x5F:                                      /* switch 1 */
        temp_v0 = temp_s0->unk15;
        temp_s0->unk15 = (u8) (temp_v0 + 1);
        sp2F = 1;
        func_8061CC40(temp_a3, *(temp_v0 + arg0), 1, temp_a3);
        var_t1 = 1;
        break;
    case 0x5E:                                      /* switch 1 */
        if (D_807444EC == 1) {
            sp2F = 1;
            func_8061D4E4(temp_v1->unk104, temp_a2, temp_a3);
            var_t1 = 1;
        }
        D_8076A0B3 = 0;
        temp_a3->unk60 = (s32) (temp_a3->unk60 & ~4);
        D_8076A0B1 |= 0x10;
        temp_v0_2 = temp_s0->unk15;
        temp_s0->unk15 = (u8) (temp_v0_2 + 1);
        temp_s0->unk4 = (s16) (*(temp_v0_2 + arg0) * 0x1E);
        break;
    case 0x5D:                                      /* switch 1 */
        temp_v0_3 = temp_s0->unk15;
        temp_s0->unk15 = (u8) (temp_v0_3 + 1);
        sp2F = 1;
        actorSetTargetSpeed(temp_a3, *(temp_v0_3 + arg0), temp_a2, temp_a3);
        var_t1 = 1;
        break;
    case 0x5C:                                      /* switch 1 */
        *temp_a3->unk17C = *(temp_s0->unk15 + arg0);
        temp_s0->unk15 = (u8) (temp_s0->unk15 + 1);
        break;
    case 0x5A:                                      /* switch 1 */
        temp_v0_4 = temp_s0->unk15;
        sp2F = 1;
        func_8070D8C0(temp_a3, *(temp_v0_4 + arg0), (temp_v0_4 + arg0)->unk1, temp_a3);
        var_t1 = 1;
        temp_s0->unk15 = (u8) (temp_s0->unk15 + 2);
        break;
    case 0x42:                                      /* switch 1 */
block_16:
        sp2F = var_t1;
        actorMoveWithinZone(0x42, (f32) D_807FDC90->unkA, (f32) D_807FDC90->unkE, arg1, arg2);
        if (func_8072D13C(D_807FBB40->unk154, 0) == 0) {
        default:                                    /* switch 1 */
block_64:
            var_t1 = 0;
        }
        break;
    case 0x69:                                      /* switch 1 */
        D_807FDC90->unk1A = (u16) (D_807FDC90->unk1A | 0x20);
        break;
    case 0x58:                                      /* switch 1 */
        temp_a3->unk60 = (s32) (temp_a3->unk60 | 4);
        break;
    case 0x59:                                      /* switch 1 */
        temp_a3->unk60 = (s32) (temp_a3->unk60 & ~4);
        break;
    case 0x51:                                      /* switch 1 */
        temp_v0_5 = temp_s0->unk15;
        sp2F = 1;
        func_80614EBC(temp_a3, (temp_v0_5 + arg0)->unk1 + (*(arg0 + temp_v0_5) << 8), temp_a2, temp_a3);
        var_t1 = 1;
        temp_s0->unk15 = (u8) (temp_s0->unk15 + 2);
        break;
    case 0x55:                                      /* switch 1 */
        var_t1 = 0;
        if (temp_a3->unk155 == 0) {
            temp_v0_6 = temp_s0->unk15;
            temp_s0->unk8 = (s16) ((temp_v0_6 + arg0)->unk1 + (*(arg0 + temp_v0_6) << 8));
            temp_s0->unk15 = (u8) (temp_v0_6 + 2);
            D_807FBB40->unk155 = 1U;
        } else {
            temp_s0->unk8 = (s16) (temp_s0->unk8 - 1);
            if (temp_s0->unk8 == 0) {
                var_t1 = 1;
            }
        }
        break;
    case 0x23:                                      /* switch 1 */
        if (temp_a3->unk155 == 0) {
            temp_v0_7 = temp_s0->unk15;
            temp_s0->unk15 = (u8) (temp_v0_7 + 1);
            temp_s0->unk8 = (s16) *(temp_v0_7 + arg0);
            D_807FBB40->unk155 = 1U;
            sp2F = 0;
            actorSetTargetSpeed(D_807FBB40, D_807FDC9C->unkD, temp_a2, temp_a3);
            var_t1 = sp2F;
        } else {
            temp_v0_8 = D_807FDC90->unk4;
            sp2F = 0;
            sp34 = temp_v1;
            actorMoveWithinZone(0x23, temp_v0_8->unk7C, temp_v0_8->unk84, arg1, arg2);
            var_t1 = 0;
            temp_s0->unk8 = (s16) (temp_s0->unk8 - 1);
            if ((temp_s0->unk8 == 0) || (temp_v1->unk1F0 & 0x80000)) {
                temp_v1->unk1F0 = (s32) (temp_v1->unk1F0 & 0xFFF7FFFF);
                sp2F = 1;
                actorSetTargetSpeed(D_807FBB40, D_807FDC9C->unkC);
                var_t1 = 1;
            }
        }
        break;
    case 0x52:                                      /* switch 1 */
        if (!(temp_a3->unk6A & 1)) {
            goto block_64;
        }
        break;
    case 0x53:                                      /* switch 1 */
        if (temp_a3->unk155 == 0) {
            goto block_64;
        }
        break;
    case 0x4F:                                      /* switch 1 */
        temp_s0->unk16 = (u8) temp_s0->unk15;
        break;
    case 0x50:                                      /* switch 1 */
        temp_s0->unk15 = (u8) temp_s0->unk16;
        break;
    case 0x66:                                      /* switch 1 */
        if (D_807FDC90->unk1A & 8) {
            temp_s0->unk15 = (u8) temp_s0->unk16;
        }
        break;
    case 0x63:                                      /* switch 1 */
        temp_v0_9 = temp_s0->unk15;
        temp_v1_2 = temp_s0 + (*(temp_v0_9 + arg0) * 2);
        temp_a0 = temp_v1_2->unk8;
        if (temp_a0 != 0) {
            temp_v1_2->unk8 = (s16) (temp_a0 - 1);
            goto block_64;
        }
        temp_s0->unk15 = (u8) (temp_v0_9 + 1);
        break;
    case 0x62:                                      /* switch 1 */
        temp_v0_10 = temp_s0->unk15;
        (temp_s0 + (*(arg0 + temp_v0_10) * 2))->unk8 = (s16) (temp_v0_10 + arg0)->unk1;
        temp_s0->unk15 = (u8) (temp_s0->unk15 + 2);
        sp2E = 1;
        break;
    case 0x64:                                      /* switch 1 */
        temp_v0_11 = temp_s0->unk15;
        (temp_s0 + *(arg0 + temp_v0_11))->unk18 = (u8) (temp_v0_11 + arg0)->unk1;
        temp_s0->unk15 = (u8) (temp_s0->unk15 + 2);
        sp2E = 1;
        break;
    case 0x68:                                      /* switch 1 */
        D_807FDC90->unk1A = (u16) (D_807FDC90->unk1A & 0xFFEF);
        sp2E = 1;
        break;
    case 0x65:                                      /* switch 1 */
        D_807FDC90->unk2C = (s16) *(temp_s0->unk15 + arg0);
        temp_s0->unk15 = (u8) (temp_s0->unk15 + 1);
        sp2E = 1;
        break;
    case 0x67:                                      /* switch 1 */
        func_80027950(temp_s0, arg0, temp_a2, temp_a3);
        var_t1 = 0;
        D_807FBB40->unk154 = 0x42U;
        D_807FBB40->unk155 = 0U;
        goto block_16;
    case 0x4C:                                      /* switch 1 */
        func_80027A30(temp_s0, arg0, temp_a2, temp_a3);
        var_t1 = 0;
        D_807FBB40->unk154 = 0x42U;
        D_807FBB40->unk155 = 0U;
        goto block_16;
    case 0x4B:                                      /* switch 1 */
        D_807FDC90->unk25 = (u8) (D_807FDC90->unk25 + 1);
        temp_v0_12 = temp_s0->unk15;
        if ((s32) (temp_v0_12 + arg0)->unk1 < (s32) D_807FDC90->unk25) {
            D_807FDC90->unk25 = (u8) *(temp_v0_12 + arg0);
        }
        temp_s0->unk15 = (u8) (temp_s0->unk15 + 2);
        var_t1 = 0;
        D_807FBB40->unk154 = 0x42U;
        D_807FBB40->unk155 = 0U;
        goto block_16;
    case 0x41:                                      /* switch 1 */
        var_t1 = 0;
        D_807FDC90->unk25 = (u8) *(temp_s0->unk15 + arg0);
        temp_s0->unk15 = (u8) (temp_s0->unk15 + 1);
        D_807FBB40->unk154 = 0x42U;
        D_807FBB40->unk155 = 0U;
        goto block_16;
    case 0x49:                                      /* switch 1 */
    case 0x4A:                                      /* switch 1 */
        temp_v0_13 = temp_a3->unk155;
        var_t1 = 0;
        switch (temp_v0_13) {                       /* switch 2; irregular */
        case 0:                                     /* switch 2 */
            temp_a3->unk128 = (s16) (temp_a3->unk128 - 0xA);
            if (D_807FBB40->unk128 < 0) {
                D_807FBB40->unk128 = 0;
                D_807FBB40->unk155 = (u8) (D_807FBB40->unk155 + 1);
            }
            break;
        case 1:                                     /* switch 2 */
            if (temp_a2 == 0x49) {
                D_807FDC90->unk25 = (u8) *(temp_s0->unk15 + arg0);
                temp_s0->unk15 = (u8) (temp_s0->unk15 + 1);
            } else {
                sp2F = 0;
                func_80027950(temp_s0, arg0, temp_a2, temp_a3);
            }
            sp2F = 0;
            func_8072D13C(0x49U, 0);
            var_t1 = 0;
            D_807FBB40->unk7C = (f32) D_807FDC90->unkA;
            D_807FBB40->unk84 = (f32) D_807FDC90->unkE;
            D_807FBB40->unk155 = (u8) (D_807FBB40->unk155 + 1);
            break;
        case 2:                                     /* switch 2 */
            temp_a3->unk128 = (s16) (temp_a3->unk128 + 0xA);
            if (D_807FBB40->unk128 >= 0x100) {
                D_807FBB40->unk128 = 0xFF;
                var_t1 = 1;
            }
            break;
        }
        break;
    }
    if (var_t1 != 0) {
        D_807FBB40->unk154 = (u8) *(temp_s0->unk15 + arg0);
        temp_s0->unk15 = (u8) (temp_s0->unk15 + 1);
        D_807FBB40->unk155 = 0U;
    }
    return sp2E;
}
