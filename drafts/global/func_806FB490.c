// func_806FB490 (src/global/100180.c): Stage 1 m2c draft saved; substantial renderer function remains.
s32 func_806FB490(s32 arg0, s32 arg1, u8 *arg2, s16 arg3, u8 arg4, u8 *arg5, u8 arg6) {
    u8 *sp1C;
    s16 var_a2_2;
    s16 var_s3;
    s32 temp_t3;
    s32 temp_t6;
    s32 temp_t7_2;
    s32 temp_v0;
    s32 temp_v1;
    s32 var_a2;
    u32 temp_t3_2;
    u8 *var_s0;
    u8 *var_s2;
    u8 *var_t0;
    u8 *var_t1;
    u8 temp_t5;
    u8 temp_t6_2;
    u8 temp_t7;
    u8 temp_t8;
    u8 temp_t8_2;
    u8 temp_t8_3;
    u8 temp_t8_4;
    u8 temp_t9;
    u8 temp_t9_2;
    u8 var_t8;

    temp_t5 = *arg5;
    temp_t3_2 = arg0 & 0xFF;
    var_t1 = arg2 + (arg3 >> 1);
    var_s2 = (arg6 * 0x10) + arg1 + (arg6 * arg4);
    sp1C = (u8 *) arg6;
    sp1C = var_s2;
    temp_t3 = (temp_t3_2 >> 1) & 0xFF;
    var_t0 = arg2;
    var_s0 = var_s2;
    temp_v0 = (temp_t5 & 1) != 0;
    temp_v1 = (temp_t3_2 & 1) != 0;
    var_s3 = 0;
    *arg5 = temp_t5 + temp_t3_2;
    do {
        var_a2_2 = 0;
        if (temp_t3 > 0) {
            temp_t6 = arg3 & 1;
            do {
                if ((temp_t6 != 0) && (temp_v0 == 0)) {
                    temp_t8 = *var_t0;
                    var_t0 += 1;
                    temp_t8_2 = var_s2->unk0 | (temp_t8 * 0x10);
                    var_s2->unk0 = temp_t8_2;
                    var_s2 += 1;
                    var_s2->unk-1 = (s8) (temp_t8_2 | ((s32) (*var_t0 & 0xF0) >> 4));
                } else if ((temp_t6 != 0) && (temp_v0 != 0)) {
                    temp_t8_3 = *var_t0;
                    var_t0 += 1;
                    var_s2->unk0 |= temp_t8_3 & 0xF;
                    temp_t8_4 = var_s2->unk1;
                    var_s2 += 1;
                    *var_s2 = temp_t8_4 | (*var_t0 & 0xF0);
                } else if ((temp_t6 == 0) && (temp_v0 != 0)) {
                    temp_t6_2 = var_s2->unk0;
                    var_s2 += 1;
                    var_s2->unk-1 = (s8) (temp_t6_2 | ((s32) (*var_t0 & 0xF0) >> 4));
                    temp_t9 = *var_t0;
                    var_t0 += 1;
                    var_s2->unk0 |= temp_t9 * 0x10;
                } else {
                    temp_t9_2 = var_s2->unk0;
                    temp_t7 = *var_t0;
                    var_t0 += 1;
                    var_s2 += 1;
                    var_s2->unk-1 = (s8) (temp_t9_2 | temp_t7);
                }
                var_a2_2 += 1;
            } while (var_a2_2 < temp_t3);
        }
        var_t1 += 0x100;
        if (temp_v1 != 0) {
            temp_t7_2 = arg3 & 1;
            if ((temp_t7_2 != 0) && (temp_v0 == 0)) {
                *var_s2 |= *var_t0 * 0x10;
            } else {
                if ((temp_t7_2 != 0) && (temp_v0 != 0)) {
                    var_t8 = *var_s2 | (*var_t0 * 0x10);
                    goto block_25;
                }
                if ((temp_t7_2 == 0) && (temp_v0 != 0)) {
                    *var_s2 |= (s32) (*var_t0 & 0xF0) >> 4;
                } else {
                    var_t8 = *var_s2 | *var_t0;
block_25:
                    *var_s2 = var_t8;
                }
            }
        }
        var_s3 += 1;
        var_s0 -= arg6;
        var_t0 = var_t1;
        var_s2 = var_s0;
    } while (var_s3 < 0x10);
    var_a2 = temp_v0;
    if (temp_v0 != 0) {
        var_a2 = temp_v1;
    }
    return var_a2 + arg1 + temp_t3;
}
