// func_806F58A0 (src/global/F9450.c): stage 4: recovered full stack frame, dispatch table, five-iteration schedule loop, and callees; stack local placement and argument coercions remain off
typedef struct { u8 pad[0x58]; s32 unk58; } F9BAt58;
extern s16 func_80632630(s16, s32, s32, s32, f32, s32);
extern void func_806357F8(s16, s32 *, s32 *, s32 *, s32 *, s32 *, s32 *, s32 *, s32 *, s32);
extern void func_806F50C8(s16, s16, s16, s32, s32, s32);
extern void func_806F54E0(u8, s16, u8);

void func_806F58A0(u8 arg0, s16 arg1, F9BAt58 *arg2) {
    s32 sp7C, sp78, sp74, sp70, sp6C, sp68, sp64, sp60;
    s16 var_s0, var_s2;
    s32 temp_t4, var_s1;
    if (D_807FC928 == 1) {
        func_806357F8(arg1, &sp7C, &sp78, &sp74, &sp70, &sp6C, &sp68, &sp64, &sp60, 1);
    }
    temp_t4 = arg2->unk58;
    var_s2 = 0xD;
    switch (temp_t4) {
    case 3: var_s2 = 0xA; break;
    case 5: var_s2 = 0x16; break;
    case 4: case 9: var_s2 = 0x1E; break;
    case 6: case 7: var_s2 = 0x1F; break;
    case 2: case 8: var_s2 = 0xD; break;
    }
    var_s0 = 0;
    var_s1 = 0;
    do {
        if (D_807FC928 == 1) {
            func_806F50C8(func_80632630(var_s2, sp7C, sp78, sp74, 0.0f, 0), var_s2, var_s0, 1, 0, 1);
        } else {
            func_806F54E0(arg0, var_s2, 0);
        }
        var_s1++;
        var_s0 += 3;
    } while (var_s1 != 5);
}
