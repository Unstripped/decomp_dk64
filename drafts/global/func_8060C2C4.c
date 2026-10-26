// func_8060C2C4 (src/global/104F0.c): stage 4: control flow/frame/saved-register set match; target homes a2 at sp+0x30 and register allocation differs thereafter
extern s32 func_80631C20(s32);

void func_8060C2C4(s32 arg0, s32 arg1, s32 arg2, u16 *arg3, s8 *arg4) {
    s32 temp_s2;
    s32 temp_v0;
    s32 var_s0;

    temp_s2 = arg2 & 0xFF;
    *arg3 += 0x320;
    var_s0 = 0;
    if (temp_s2 > 0) {
        do {
            temp_v0 = func_80631C20(var_s0 & 0xFF);
            var_s0 += 1;
            *arg3 += temp_v0;
        } while (var_s0 != temp_s2);
    }
    *arg4 = 1;
}
