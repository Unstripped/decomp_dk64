// func_806F5A48 (src/global/F9450.c): stage 4: recovered full dispatch and five-pass scheduling flow with target frame; IDO register allocation and boolean materialization remain different
typedef struct { u8 pad[0x58]; s32 unk58; } F9BAt58;
extern s16 func_80632630(s16, s32, s32, s32, f32, s32);
extern void func_806357F8(s16, s32 *, s32 *, s32 *, s32 *, s32 *, s32 *, s32 *, s32 *, s32);
extern void func_806F50C8(s16, s16, s16, s32, s32, s32);
extern void func_806F54E0(u8, s16, u8);

void func_806F5A48(u8 arg0, s16 arg1, F9BAt58 *arg2, u16 arg3) {
    s32 sp90, sp8C, sp88, sp84, sp80, sp7C, sp78, sp74;
    s16 temp_a0, var_s0, var_s2;
    s32 temp_s3, temp_t4, var_s1, var_v0;
    temp_s3 = arg3 & 0xFFFF;
    if (D_807FC928 == 1) func_806357F8(arg1, &sp90, &sp8C, &sp88, &sp84, &sp80, &sp7C, &sp78, &sp74, 1);
    temp_t4 = arg2->unk58;
    var_s2 = 0x91;
    switch (temp_t4) {
    case 3: var_s2 = 0x91; break;
    case 5: var_s2 = 0x15D; break;
    case 4: var_s2 = 0x15E; break;
    case 6: case 7: var_s2 = 0x15F; break;
    case 2: var_s2 = 0x160; break;
    }
    var_s0 = 0;
    var_s1 = 0;
    do {
        if (D_807FC928 == 1) {
            temp_a0 = func_80632630(var_s2, sp90, sp8C, sp88, 0.0f, 0);
            var_v0 = temp_s3 == 0x11;
            func_806F50C8(temp_a0, var_s2, var_s0, var_v0, 0, 1);
        } else {
            var_v0 = temp_s3 == 0x11;
            func_806F54E0(arg0, var_s2, (u8)var_v0);
        }
        var_s1++;
        var_s0 += 3;
    } while (var_s1 != 5);
}
