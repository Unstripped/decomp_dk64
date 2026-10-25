// func_80704484 (src/global/103AB0.c): Compiled transition-state draft; exact float conversion and dispatch call shapes remain unmatched.
? func_805FF000(f32, u8, ?);                        /* extern */
s32 func_80600454(s16, u8 *);                       /* extern */
s32 func_80703374(f32, f32, s32, ?, ?, ?, s32);     /* extern */
? func_80703850(f32, f32, s32, ?, ?);               /* extern */
s32 func_80703AB0(f32, f32, s32, s32, ?);           /* extern */
s32 func_80703CF8(f32, f32, s32, s32, ?);           /* extern */
? func_8070B308(?);                                 /* extern */
s32 func_8070B318();                                /* extern */
? func_8070B324(f32, ?, ? *);                       /* extern */
s32 func_8070E750(?, u8, ?);                        /* extern */
? sfxStopChannel(f32, ?, ?, ?);                     /* extern */
? textSpawnMarkerChecked(?, ?, ?, s32, s32, s32, s32, s32); /* extern */
extern u8 D_80750AC0;
extern ? D_80754CC8;
extern s16 D_8076A0AA;
extern u8 D_8076A0AB;
extern u8 D_8076A0B1;
extern f32 D_807FD888;
extern f32 D_807FD88C;

s32 func_80704484(f32 arg0, s32 arg1) {
    u8 sp5B;
    f32 sp54;
    ? sp44;
    ? var_a1;
    f32 temp_fv0;
    f32 var_fa0;
    s32 temp_ft0;
    s32 temp_t6;
    s32 var_v0;
    s32 var_v0_2;
    s32 var_v1;

    var_fa0 = arg0;
    temp_t6 = arg1 & 0xFF;
    if (D_807FD88C != 0.0f) {
        if (temp_t6 == 2) {
            var_v0 = 2;
        } else {
            var_v0 = 1;
        }
        D_807FD888 += D_807FD88C * (f32) var_v0;
        if (D_807FD888 < 0.0f) {
            func_805FF000(D_807FD88C, D_8076A0AB, 2);
            if (!(D_8076A0B1 & 0x20) && (func_80600454(D_8076A0AA, &sp5B) != 0)) {
                textSpawnMarkerChecked(1, 0, 0x64, func_8070E750(0x23, sp5B, 1), 0, 0x28, 6, 8);
                D_8076A0B1 |= 0x20;
            }
            sfxStopChannel(6e-44f, 0);
            if (func_8070B318() == 2) {
                func_8070B308(0);
            }
            D_807FD88C = 0.0f;
            D_807FD888 = 0.0f;
            D_8076A0B1 &= 0xFFBF;
        } else if (D_807FD888 > 31.0f) {
            if (D_8076A0B1 & 1) {
                sfxStopChannel(D_807FD88C, 0x2C, 0, 2);
            }
            D_807FD88C = 0.0f;
            D_807FD888 = 31.0f;
            osViBlack(1U);
            D_8076A0B1 |= 0xC;
        } else {
            sp54 = D_807FD888 * 0.032258064f;
            temp_fv0 = (D_807FD888 * 255.0f) / 28.0f;
            if (temp_fv0 < 0.0f) {
                temp_ft0 = (s32) 0.0f;
                if (M2C_ERROR(/* cfc1 */) & 0x78) {
                    if (!(M2C_ERROR(/* cfc1 */) & 0x78)) {
                        var_v1 = ((s32) (0.0f - 2.1474836e9f) | 0x80000000) & 0xFFFF;
                    } else {
                        goto block_19;
                    }
                } else if (temp_ft0 >= 0) {
                    var_v1 = temp_ft0 & 0xFFFF;
                } else {
block_19:
                    var_v1 = -1 & 0xFFFF;
                }
            } else {
                if (temp_fv0 > 255.0f) {
                    var_fa0 = 255.0f;
                } else {
                    var_fa0 = temp_fv0;
                }
                var_v1 = (u32) var_fa0 & 0xFFFF;
            }
            if ((D_807FD888 < ((D_807FD88C * 2.0f) + 31.0f)) && (D_8076A0B1 & 4)) {
                D_8076A0B1 ^= 6;
            }
            if ((D_807FD888 > 28.0f) && (temp_t6 != 3)) {
                var_v0_2 = func_80703374(var_fa0, D_807FD88C, (bitwise s32) arg0, 0, 0, 0, 0xFF);
                goto block_40;
            }
            if (temp_t6 != 1) {
                if (temp_t6 != 2) {
                    if (temp_t6 == 3) {
                        if (D_80750AC0 == 1) {
                            func_80703850(var_fa0, D_807FD88C, var_v1 & 0xFF, 0, 2);
                        } else {
                            goto block_37;
                        }
                    } else {
                        var_v0_2 = func_80703374(var_fa0, D_807FD88C, (bitwise s32) arg0, 0, 0, 0, var_v1);
                        goto block_40;
                    }
                } else {
block_37:
                    var_v0_2 = func_80703AB0(var_fa0, D_807FD88C, (bitwise s32) arg0, var_v1 & 0xFF, 2);
                    goto block_40;
                }
            } else {
                var_v0_2 = func_80703CF8(var_fa0, D_807FD88C, (bitwise s32) arg0, var_v1 & 0xFF, 2);
block_40:
                arg0 = (bitwise f32) var_v0_2;
            }
            if ((D_8076A0B1 & 0x41) || !(D_8076A0B1 & 0x20)) {
                sp44.unk0 = (s32) D_80754CC8.unk0;
                var_a1 = 0;
                sp44.unk4 = (s32) D_80754CC8.unk4;
                sp44.unk8 = (s32) D_80754CC8.unk8;
                if (D_807FD88C >= 0.0f) {
                    var_a1 = 1;
                }
                func_8070B324(1.0f - sp54, var_a1, &sp44);
            }
        }
    }
    return (bitwise s32) arg0;
}
