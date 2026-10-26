// func_80613044 (src/global/17B90.c): stage 1: m2c starter; entry is continuation immediately after func_80612E90's tail
? animListInit(s32, void *);                        /* extern */
? func_806130A4(s32, s32 *);                        /* extern */
? func_806133C8(s32, s32 *);                        /* extern */
? renderReplaceSegment6Commands(s32, s32 *);        /* extern */

void *func_80613044(s32 *arg1, s32 arg6, s32 arg7, s32 arg8, s32 arg9, s32 arg12, s32 arg16) {
    s32 *temp_a1;
    s32 *temp_a1_2;
    s32 *temp_a1_3;

    temp_a1 = saved_reg_s2->unk4;
    renderReplaceSegment6Commands(*temp_a1, temp_a1);
    temp_a1_2 = saved_reg_s2->unk4;
    func_806133C8(*temp_a1_2, temp_a1_2);
    animListInit(arg16, saved_reg_s2);
    if (arg12 & 1) {
        temp_a1_3 = saved_reg_s2->unk4;
        func_806130A4(*temp_a1_3, temp_a1_3);
    }
    return saved_reg_s2;
}
