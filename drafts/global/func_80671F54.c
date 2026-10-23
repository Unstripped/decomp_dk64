// func_80671F54 (src/global/70FD0.c): Unattempted starter draft from m2c (angle/distance vector calculation)
s32 func_80673708(s32, s32, s32, s32, s32, s32, s32, s32); /* extern */
s32 func_80674ADC(s32, s32, s32, s32, s32, s32, s32, s32); /* extern */
extern s32 D_80747D70;
extern s32 D_807F6000;
extern s32 D_807FB53C;
extern s8 D_807FB5FD;

s32 func_80671F54(f32 arg0, f32 arg1, f32 arg2, f32 arg3, s32 arg4, s32 arg5) {
    s32 temp_ft0;
    s32 temp_ft1;
    s32 temp_ft2;
    s32 temp_ft3;
    s32 var_fp;
    s32 var_s1;
    s32 var_s6;
    void *temp_s0;
    void *temp_s0_2;
    void *temp_v0;

    var_fp = 0;
    D_807FB5FD = 0;
    var_s6 = 0;
    if (D_80747D70 > 0) {
        var_s1 = 0;
        do {
            temp_s0 = var_s1 + D_807F6000;
            temp_s0_2 = temp_s0 + 0x28;
            if ((temp_s0->unk40 != 0) && ((D_807FB53C != 0xBC) || ((D_807F6000 + var_s1)->unk6C & 2))) {
                temp_ft0 = (s32) arg0;
                temp_ft1 = (s32) arg1;
                temp_ft2 = (s32) arg2;
                temp_ft3 = (s32) arg3;
                if ((func_80674ADC(temp_ft0, temp_ft1, temp_ft2, temp_ft3, temp_s0->unk28, temp_s0_2->unk4, temp_s0_2->unk8, temp_s0_2->unkC) != 0) && (temp_s0_2->unk15 & 1) && ((temp_v0 = (D_807F6000 + var_s1)->unk7C, (temp_v0 == NULL)) || (temp_v0->unk70 != 0))) {
                    var_fp = (var_fp | func_80673708(temp_ft0, temp_ft1, temp_ft2, temp_ft3, temp_s0_2->unk18, temp_s0_2->unk1C, arg4, arg5)) & 0xFF;
                }
            }
            var_s6 += 1;
            var_s1 += 0x90;
        } while (var_s6 < D_80747D70);
    }
    return var_fp;
}
