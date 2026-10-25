// func_806F91B4 (src/global/FCCD0.c): m2c behavioural starter; 142-insn stat update requires local views and stage work.
s32 func_805FEF10(? *);                             /* extern */
s32 func_805FF030(u8, ?);                           /* extern */
? func_80687C48();                                  /* extern */
s32 func_806C8DE0(u8, s32);                         /* extern */
s32 func_806F7FD0(u8);                              /* extern */
? func_806F8278(u8);                                /* extern */
s32 func_806F8EDC(s32, s32, u16 **, s32);           /* extern */
? func_8073129C(s16, ?, ?);                         /* extern */
s16 func_807319D8(?, s32, u8, s32);                 /* extern */
? sfxAllocateChannel(?, ?);                         /* extern */
extern ? D_8074E77C;
extern u8 D_8076A0AB;
extern ? D_807FC950;

void func_806F91B4(s32 arg0, u8 arg1, s16 arg2) {
    void *sp48;
    ? sp3C;
    s32 sp38;
    s32 sp28;
    s32 sp24;
    u16 **sp20;
    s32 temp_a3;
    s32 temp_v0;
    s32 temp_v0_2;
    s32 temp_v0_3;
    s32 var_t2;
    u16 **temp_a2;
    u16 *temp_v1;
    u16 *temp_v1_2;
    u16 *temp_v1_3;
    void *temp_a0;
    void *temp_v1_4;

    sp28 = (s32) arg1;
    sp48 = (arg1 * 0x306) + (func_806C8DE0(arg1, arg0) * 0x5E) + &D_807FC950;
    temp_v0 = func_806F7FD0(arg1);
    var_t2 = arg0 * 0x30;
    temp_a0 = temp_v0 + var_t2;
    if (((temp_a0->unk2D == 0) || (arg2 >= 0)) && (temp_a0->unk2C == 0)) {
        if ((arg0 != 0xA) && (arg0 != 0xC)) {
            temp_v1 = temp_a0->unk0;
            temp_a2 = temp_v0 + var_t2;
            if ((*temp_v1 + arg2) < 0) {
                *temp_v1 = 0;
                sp24 = var_t2;
            } else {
                temp_v1_2 = *temp_a2;
                *temp_v1_2 += arg2;
                sp24 = var_t2;
                sp20 = temp_a2;
                temp_v0_2 = func_806F8EDC(arg0, sp28, temp_a2, arg0);
                temp_v1_3 = *temp_a2;
                if (temp_v0_2 < (s32) *temp_v1_3) {
                    *temp_v1_3 = (u16) temp_v0_2;
                }
                if ((sp24 == 0x180) && (func_805FEF10(&sp3C) != 0)) {
                    func_8073129C(sp3E, 1, 0);
                }
                if ((arg2 > 0) && (sp24 == 0)) {
                    temp_v0_3 = func_805FF030(D_8076A0AB, 1);
                    temp_v1_4 = sp48 + (temp_v0_3 * 2);
                    temp_a3 = temp_v1_4->unk26 + temp_v1_4->unkA;
                    if ((temp_a3 >= 0x4B) && ((temp_a3 - arg2) < 0x4B)) {
                        sp38 = temp_a3;
                        func_8073129C(func_807319D8(0x225, temp_v0_3, *(&D_8074E77C + arg1), temp_a3), 1, 0);
                        func_80687C48();
                    }
                    if ((temp_a3 == 0x64) && ((temp_a3 - arg2) < 0x64)) {
                        sfxAllocateChannel(0xAC, 0x3F800000);
                    }
                }
            }
            var_t2 = sp24;
        }
        if (var_t2 == 0x180) {
            func_806F8278(arg1);
        }
    }
}
