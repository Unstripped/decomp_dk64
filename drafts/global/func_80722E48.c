// func_80722E48 (src/global/127B00.c): stage 1 m2c recovery; needs local Uc1 array view and codegen refinement
? *func_80610FE8(s32);                              /* extern */
extern ? D_807FDB90;
extern ? D_807FDBF8;

void func_80722E48(s16 *arg0) {
    ? **temp_s1;
    ? *temp_v0;
    ? *var_a0;
    ? *var_s2;
    ? temp_at;
    s16 temp_s5;
    s16 temp_s7;
    s16 var_s0;
    s16 var_s4;
    s16 var_s4_2;
    s32 temp_lo;
    s32 temp_t6;
    s32 temp_t7;
    void *temp_t9;

    var_s4 = 0;
    do {
        temp_t6 = var_s4 * 4;
        var_s4 += 1;
        *(&D_807FDB90 + temp_t6) = 0;
    } while (var_s4 < 0x1A);
    temp_s7 = *arg0;
    var_s2 = arg0 + 2;
    var_s4_2 = 0;
    if (temp_s7 > 0) {
        do {
            temp_s5 = var_s2->unk0;
            var_s0 = 0;
            temp_v0 = func_80610FE8(8);
            temp_s1 = &D_807FDB90 + (temp_s5 * 4);
            *temp_s1 = temp_v0;
            temp_v0->unk4 = (s16) var_s2->unk2;
            var_a0 = var_s2 + 2 + 4;
            (*temp_s1)->unk0 = func_80610FE8(((*temp_s1)->unk4 + 1) * 0xA);
            var_s4_2 += 1;
            if ((*temp_s1)->unk4 > 0) {
                do {
                    temp_lo = var_s0 * 0xA;
                    temp_at = (unaligned s32) *var_a0;
                    var_s0 += 1;
                    var_a0 += 0xA;
                    temp_t9 = (*temp_s1)->unk0 + temp_lo;
                    temp_t9->unk0 = (unaligned s32) temp_at;
                    temp_t9->unk4 = (unaligned s32) var_a0->unk-6;
                    temp_t9->unk8 = (u16) var_a0->unk-2;
                } while (var_s0 < (*temp_s1)->unk4);
            }
            var_s2 = var_a0;
        } while (var_s4_2 < temp_s7);
        var_s4_2 = 0;
    }
    do {
        temp_t7 = var_s4_2 * 4;
        var_s4_2 += 1;
        *(&D_807FDBF8 + temp_t7) = 0;
    } while (var_s4_2 < 0x20);
}
