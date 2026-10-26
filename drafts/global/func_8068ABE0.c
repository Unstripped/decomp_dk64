// func_8068ABE0 (src/global/8F4B0.c): sparse switch needing explicit case breaks for jtbl_80759D00 in .late_rodata; held back by func_8068AD7C asm rodata alignment
s32 flagGet(s16, s32, s32);
void flagSet(s16, s32, s32, s16);
void func_805FF378(s16, s32);
void func_80712524(s32, s16);
extern s8 D_8074452C;
extern u16 D_80744734[];
extern s32 D_8076A0A8;

s32 func_8068ABE0(s16 arg0) {
    s16 sp36;
    s32 sp24;
    s32 sp20;
    s32 sp1C;
    s16 temp_a0;
    s16 var_a3;
    s32 var_a1;
    s32 var_v0_2;
    s32 var_v1;
    u16 *var_v0;

    var_v1 = 0;
    var_a1 = 0;
    var_v0 = D_80744734;
loop_1:
    if (D_8076A0A8 == *var_v0) {
        var_a1 = 1;
    } else {
        var_v1 += 1;
        var_v0++;
    }
    if ((var_a1 == 0) && (var_v1 < 8)) {
        goto loop_1;
    }
    temp_a0 = var_v1 + 0x1C5;
    if (var_a1 != 0) {
        sp1C = temp_a0;
        sp36 = -1;
        var_a3 = -1;
        if (flagGet(temp_a0, 0, -1) == 0) {
            var_v0_2 = 0;
            switch (arg0) {
            case 0x7:
                sp24 = 0x1C;
                var_a3 = 0xF;
                break;
            case 0x26:
                sp24 = 0x1C;
                var_a3 = 0x10;
                break;
            case 0x1A:
                sp24 = 0x1C;
                var_a3 = 0x11;
                break;
            case 0x1E:
                sp24 = 0x1C;
                var_a3 = 0x12;
                break;
            case 0x30:
                sp24 = 0x1C;
                var_a3 = 0x13;
                break;
            case 0x48:
                sp24 = 0x1C;
                var_a3 = 0x14;
                break;
            case 0x57:
                sp24 = 0x1C;
                var_a3 = 0x15;
                var_v0_2 = 0x15;
                break;
            case 0x11:
                sp24 = 0x1C;
                var_a3 = 0x16;
                break;
            }
            if (var_a3 != -1) {
                sp20 = var_v0_2;
                sp36 = var_a3;
                flagSet(temp_a0, 1, 0, var_a3);
                if (D_8074452C != 0) {
                    func_805FF378(arg0, sp20);
                    return 1;
                }
                func_80712524(sp24, var_a3);
                return 1;
            }
        }
    }
    return 0;
}
