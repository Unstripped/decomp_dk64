// func_806F8BC4 (src/global/FCCD0.c): m2c behavioural starter; 59-insn slot update and recursive case.
s32 func_807142D8();                                /* extern */
extern s32 D_80754280;
extern s32 D_8076A0A8;
extern u8 D_807FC928;

void func_806F8BC4(s32 arg0, u8 arg1, s32 arg2) {
    s32 temp_v1;
    void *temp_v0;
    void *temp_v0_2;

    if (((s32) D_807FC928 < 2) && (func_807142D8() == 0) && ((arg0 != 8) || (func_806F8BC4(9, arg1, arg2 + 0xA), (D_8076A0A8 != 0xF)))) {
        temp_v1 = arg0 * 0x30;
        (D_80754280 + temp_v1)->unk24 = (s32) arg1;
        temp_v0 = D_80754280 + temp_v1;
        if (temp_v0->unk20 == 0) {
            temp_v0->unk7 = (s8) arg2;
        } else {
            temp_v0->unk7 = 0;
        }
        (D_80754280 + temp_v1)->unk20 = 1;
        temp_v0_2 = D_80754280 + temp_v1;
        if (temp_v0_2->unk6 == 0) {
            temp_v0_2->unk6 = (u8) (arg1 != 0);
        }
    }
}
