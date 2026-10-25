// func_806F6EDC (src/global/F9450.c): Stage 4: target prologue/call/sign extension and return register are close; branch target and delay-slot scheduling remain.
extern s32 func_806F6E58();

s32 func_806F6EDC(void) {
    s32 var_s0;
    s32 temp_v0;
    s32 temp_v1;

    var_s0 = 0;
loop_1:
    temp_v0 = func_806F6E58((s16) var_s0);
    var_s0 += 1;
    temp_v1 = temp_v0 & 0xFF;
    if (var_s0 < 5) {
        if (temp_v1 == 0) {
            goto loop_1;
        }
    }
    return temp_v1;
}
