// func_80709344 (src/global/10D2D0.c): Matched: self-assignment arg0 = arg0 before initialization schedules move s1,a0 before the remaining callee-save stores.
typedef struct NmF10D2D0b_PlayerState {
    u8 unk0;
    u8 pad1[0x2E1];
    u16 unk2E2;
    u8 unk2E4;
} NmF10D2D0b_PlayerState;

extern s8 D_80744504;
s32 func_80708DA4(s32, s16, s32, s32);

s32 func_80709344(s32 arg0) {
    s16 var_s0;
    s32 temp_lo;
    u16 temp_v1;
    s32 temp_v0;

    arg0 = arg0;
    var_s0 = 0;
    if ((s32)D_807FC928 > 0) {
        do {
            temp_lo = var_s0 * 0x2F0;
            temp_v0 = (s32)D_807FC924 + temp_lo;
            if (((NmF10D2D0b_PlayerState *)temp_v0)->unk0 != 0) {
                temp_v1 = ((NmF10D2D0b_PlayerState *)temp_v0)->unk2E2;
                if (!(temp_v1 & 0x20) && (((((NmF10D2D0b_PlayerState *)temp_v0)->unk2E4 != 0 || temp_v1 != 0) &&
                                           D_80744504 == 0) ||
                                          temp_v1 & 0x10)) {
                    arg0 = func_80708DA4(arg0, var_s0, (temp_lo ^ 0) + (s32)D_807FC924,
                                          (s32)D_807FC924);
                }
            }
            var_s0 += 1;
        } while (var_s0 < (s32)D_807FC928);
    }
    return arg0;
}
