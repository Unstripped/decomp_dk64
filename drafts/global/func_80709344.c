// func_80709344 (src/global/10D2D0.c): Stage 4 behavioral draft; target needs pointer/argument register allocation and one instruction.
typedef struct R1F10D2D0_PlayerState {
    u8 unk0;
    u8 pad1[0x2E1];
    u16 unk2E2;
    u8 unk2E4;
    u8 unk2E5;
    u8 unk2E6;
    u8 pad2E7[9];
} R1F10D2D0_PlayerState;

extern s8 D_80744504;
s32 func_80708DA4(s32, s16, s32, s32);

s32 func_80709344(s32 arg0) {
    s16 var_s0;
    s32 temp_lo;
    s32 var_s1;
    u16 temp_v1;
    s32 temp_v0;

    var_s1 = arg0;
    var_s0 = 0;
    if ((s32) D_807FC928 > 0) {
        do {
            temp_lo = var_s0 * 0x2F0;
            temp_v0 = (s32) D_807FC924 + temp_lo;
            if (((R1F10D2D0_PlayerState *) temp_v0)->unk0 != 0) {
                temp_v1 = ((R1F10D2D0_PlayerState *) temp_v0)->unk2E2;
                if (!(temp_v1 & 0x20) && (((((R1F10D2D0_PlayerState *) temp_v0)->unk2E4 != 0 || temp_v1 != 0) && D_80744504 == 0) || temp_v1 & 0x10)) {
                    var_s1 = func_80708DA4(var_s1, var_s0, temp_lo + (s32) D_807FC924, (s32) D_807FC924);
                }
            }
            var_s0 += 1;
        } while (var_s0 < (s32) D_807FC928);
    }
    return var_s1;
}
