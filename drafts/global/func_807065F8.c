// func_807065F8 (src/global/109660.c): stage 1 m2c candidate; needs switch-table and D_80754F58 record typing
extern ? D_80754F58;
extern s32 D_8076A0A8;

void func_807065F8(s16 arg0, s8 *arg1, s8 *arg2, s8 *arg3) {
    f32 temp_fv0;
    f32 var_ft1;
    f32 var_ft2;
    f32 var_ft4;
    s16 temp_a1;
    s32 temp_lo;
    s32 temp_t5;
    s32 var_v0;
    u8 temp_a3;
    u8 temp_t0;
    u8 temp_t1;
    void *temp_a2;
    void *temp_v1;

    if (D_8076A0A8 >= 0x4C) {
        switch (D_8076A0A8);                        /* switch 1; jump table: jtbl_8075DFF0 */
    } else if (D_8076A0A8 >= 0xF) {
        switch (D_8076A0A8) {                       /* switch 2 */
        case 0x41:                                  /* switch 2 */
        case 0x42:                                  /* switch 2 */
        case 0x43:                                  /* switch 2 */
        case 0x44:                                  /* switch 2 */
        case 0x45:                                  /* switch 2 */
        case 0x4A:                                  /* switch 2 */
        case 0x4B:                                  /* switch 2 */
        case 0x7C:                                  /* switch 1 */
        case 0x7D:                                  /* switch 1 */
        case 0x7E:                                  /* switch 1 */
        case 0x7F:                                  /* switch 1 */
        case 0x80:                                  /* switch 1 */
            *arg1 = 0x3F;
            *arg2 = 0x3F;
            *arg3 = 0x3F;
            return;
        }
    } else {
        if (D_8076A0A8 == 0xE) {
            var_v0 = 0;
            if (arg0 < D_80754F58.unk6) {
                do {
                    temp_t5 = (var_v0 + 1) & 0xFF;
                    temp_lo = temp_t5 * 6;
                    var_v0 = temp_t5;
                } while (arg0 < (&D_80754F58 + temp_lo)->unk6);
            }
            temp_a2 = &D_80754F58 + (var_v0 * 6);
            temp_v1 = &D_80754F58 + (var_v0 * 6);
            temp_a1 = temp_v1->unk6;
            temp_a3 = temp_v1->unk8;
            temp_fv0 = (f32) (arg0 - temp_a1) / (f32) (temp_a2->unk0 - temp_a1);
            var_ft1 = (f32) temp_a3;
            if ((s32) temp_a3 < 0) {
                var_ft1 += 4294967296.0f;
            }
            *arg1 = (s8) (u32) (((f32) (temp_a2->unk2 - temp_a3) * temp_fv0) + var_ft1);
            temp_t0 = temp_v1->unk9;
            var_ft4 = (f32) temp_t0;
            if ((s32) temp_t0 < 0) {
                var_ft4 += 4294967296.0f;
            }
            *arg2 = (s8) (u32) (((f32) (temp_a2->unk3 - temp_t0) * temp_fv0) + var_ft4);
            temp_t1 = temp_v1->unkA;
            var_ft2 = (f32) temp_t1;
            if ((s32) temp_t1 < 0) {
                var_ft2 += 4294967296.0f;
            }
            *arg3 = (s8) (u32) (((f32) (temp_a2->unk4 - temp_t1) * temp_fv0) + var_ft2);
            return;
        }
    default:                                        /* switch 2 */
    default:                                        /* switch 1 */
        *arg1 = 0xFF;
        *arg2 = 0xFF;
        *arg3 = 0xFF;
    }
}
