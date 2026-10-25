// func_80708C24 (src/global/10D2D0.c): Stage 1 m2c behavioral starter; needs local views/prototypes and IDO matching.
? func_80026B0C(s32, ?, ?);                         /* extern */
s32 func_805FCA64();                                /* extern */
? func_80609140(?, ?, ?, ?, s32, s32);              /* extern */
s32 func_8070943C();                                /* extern */
s32 func_8071432C();                                /* extern */
s32 func_8071441C();                                /* extern */
extern s32 D_807FBB60;
extern u8 D_807FC928;

void func_80708C24(s32 arg0, void *arg1, void *arg2, ? arg3) {
    s32 sp28;
    s32 temp_v0;
    s8 temp_lo;
    s8 temp_v0_2;
    s8 temp_v1_2;
    u16 temp_v1;
    u8 temp_t3;

    temp_v1 = arg1->unk2E2;
    temp_v0 = temp_v1 & 0xFF;
    sp28 = temp_v0;
    if (temp_v0 & 0x10) {
        arg1->unk2E2 = (u16) (temp_v1 ^ 0x10);
        temp_v0_2 = arg2->unk2FD;
        if (temp_v0_2 > 0) {
            temp_lo = arg2->unk2FC * func_8070943C();
            temp_v1_2 = arg2->unk2FB + arg2->unk2FD;
            if (temp_v1_2 < temp_lo) {
                arg2->unk2FB = temp_v1_2;
            } else {
                arg2->unk2FB = temp_lo;
            }
        } else if (temp_v0_2 < 0) {
            if ((func_8071432C() != 0) || (func_8071441C() != 0)) {
                arg2->unk2FB = (s8) (arg2->unk2FB + arg2->unk2FD);
            }
            if (arg2->unk2FB <= 0) {
                arg2->unk2FB = 0;
                arg1->unk2E6 = 0xC;
                if ((s32) D_807FC928 >= 2) {
                    func_80026B0C(arg0, 0x7FFF, 0x427C0000);
                }
            } else {
                func_80609140(0x24B, 0x7FFF, 0x427C0000, 0x3F800000, 0, 0);
            }
        }
        arg2->unk2FD = 0;
    }
    if ((!(D_807FBB60 & 2) && (func_805FCA64() != 0)) || (sp28 & 0x80)) {
        temp_t3 = arg1->unk2E5 - 1;
        arg1->unk2E5 = temp_t3;
        if (!(temp_t3 & 0xFF)) {
            arg1->unk2E5 = 0x11U;
            arg1->unk2E4 = 3;
        }
    }
}
