// func_80723020 (src/global/127B00.c): stage 1 m2c recovery; needs local Uc1 array view and codegen refinement
void *func_80610FE8(s32);                           /* extern */
? memcpy(void *, ? *, ?);                           /* extern */
extern ? D_807FDB90;
extern ? D_807FDBF8;

s32 func_80723020(s32 arg0, s32 arg1, s32 arg2, f32 arg3, f32 arg4, f32 arg5, u8 arg6) {
    u8 sp5C;
    s16 sp5A;
    s16 sp58;
    s16 sp56;
    ? sp54;
    s32 sp50;
    s32 **temp_s7;
    s32 *temp_s4;
    s32 *var_s3;
    s32 temp_s0;
    s32 var_s0;
    s32 var_s1;
    s32 var_s2;
    s32 var_s6;
    s32 var_v0;
    s32 var_v1;
    void **temp_s3;
    void *temp_s5;
    void *temp_v0;

    temp_s7 = (arg1 * 4) + &D_807FDB90;
    temp_s4 = *temp_s7;
    temp_s0 = arg2 & 0xFF;
    var_s6 = 0;
    var_v0 = 0;
    if (temp_s4 == NULL) {
        return -1;
    }
    var_s3 = (0 * 4) + &D_807FDBF8;
loop_3:
    if (*var_s3 == 0) {
        var_v0 = 1;
    } else {
        var_s6 += 1;
        var_s3 += 4;
    }
    if ((var_s6 < 0x20) && (var_v0 == 0)) {
        goto loop_3;
    }
    if (var_v0 == 0) {
        return -1;
    }
    if ((temp_s4->unk4 == 1) && (temp_s0 == 0)) {
        return -1;
    }
    temp_s3 = (var_s6 * 4) + &D_807FDBF8;
    sp50 = 0;
    temp_v0 = func_80610FE8(0x2C);
    *temp_s3 = temp_v0;
    temp_s5 = temp_v0 + 4;
    temp_v0->unk8 = (s16) (*temp_s7)->unk4;
    var_v1 = 0;
    temp_v0->unk4 = func_80610FE8((temp_v0->unk8 * 0xA) + 0xA);
    if (temp_s0 != 0) {
        temp_s5->unk4 = (s16) (temp_s5->unk4 + 1);
        sp5C = arg6;
        sp56 = (s16) (s32) arg3;
        sp58 = (s16) (s32) arg4;
        sp5A = (s16) (s32) arg5;
        memcpy(temp_v0->unk4, &sp54, 0xA);
        var_v1 = 1;
    }
    var_s1 = var_v1 * 0xA;
    var_s0 = 0;
    var_s2 = 0;
    if ((*temp_s7)->unk4 > 0) {
        do {
            memcpy(temp_v0->unk4 + var_s1, (*temp_s7)->unk0 + var_s2, 0xA);
            var_s0 += 1;
            var_s2 += 0xA;
            var_s1 += 0xA;
        } while (var_s0 < (*temp_s7)->unk4);
    }
    (*temp_s3)->unk0 = arg0;
    (*temp_s3)->unkC = 0.0f;
    (*temp_s3)->unk1C = 0;
    (*temp_s3)->unk10 = 0;
    (*temp_s3)->unk16 = 0;
    (*temp_s3)->unk15 = 0;
    (*temp_s3)->unk14 = 0;
    (*temp_s3)->unk18 = 1;
    (*temp_s3)->unk21 = 0;
    (*temp_s3)->unk20 = 1;
    return var_s6;
}
