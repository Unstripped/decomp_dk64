// func_806F8DC4 (src/global/FCCD0.c): stage 4: exact branch/call sequence and stores; index multiplication expansion differs
extern u8 D_8076A0AB;
extern u16 D_807FC992[][0x2D];
extern s32 func_805FF030();
s32 func_806C8DE0(s32);
s32 func_80731A04(s32, s32, s32, s32);

void func_806F8DC4(s8 *arg0, s32 arg1, s32 arg2) {
    s32 sp1C;
    s32 temp_a3;
    s32 temp_v0;

    sp1C = func_805FF030(D_8076A0AB, 1);
    temp_v0 = func_806C8DE0(0);
    temp_a3 = temp_v0;
    *arg0 = 0x7F;
    if (arg2 != 8) {
        if (arg2 != 0xA) {
            if ((arg2 == 0xC) && (func_80731A04(0x1D5, sp1C, sp1C, temp_a3) != 0)) {
                *(u8 *)arg0 = 0xFF;
            }
        } else if (func_80731A04(0x225, sp1C, sp1C, temp_a3) != 0) {
            *(u8 *)arg0 = 0xFF;
        }
    } else if (arg1 < D_807FC992[temp_v0][sp1C]) {
        *(u8 *)arg0 = 0xFF;
    }
}
