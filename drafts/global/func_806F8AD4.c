// func_806F8AD4 (src/global/FCCD0.c): m2c behavioural starter; 60-insn selector switch.
s32 func_805FF030(u8, ?);                           /* extern */
s32 func_806C8DE0(u8);                              /* extern */
s32 func_806F7FD0(u8);                              /* extern */
s32 func_80731A04(?, s32, s32, s32);                /* extern */
extern u8 D_8076A0AB;

u16 func_806F8AD4(u8 arg0, u8 arg1) {
    u16 sp26;
    s32 sp1C;
    s32 temp_a1;
    s32 temp_v0;
    u16 *temp_v1_2;
    u16 var_a2;
    u8 temp_v1;
    void *temp_a0;

    sp26 = 0;
    var_a2 = sp26;
    temp_a0 = func_806F7FD0(arg1) + (arg0 * 0x30);
    temp_v1 = temp_a0->unk2C;
    switch (temp_v1) {                              /* irregular */
    case 2:
        break;
    case 0:
        temp_v1_2 = temp_a0->unk0;
        if (temp_v1_2 != NULL) {
            var_a2 = *temp_v1_2;
        } else {
            sp1C = func_806C8DE0(arg1);
            temp_v0 = func_805FF030(D_8076A0AB, 1);
            temp_a1 = temp_v0;
            if (arg0 != 0xA) {
                if (arg0 == 0xC) {
                    var_a2 = func_80731A04(0x1D5, temp_a1, temp_v0, sp1C) & 0xFFFF;
                }
            } else {
                var_a2 = func_80731A04(0x225, temp_a1, temp_a1, sp1C) & 0xFFFF;
            }
        }
        break;
    case 1:
        var_a2 = 0x14;
        break;
    }
    return var_a2;
}
