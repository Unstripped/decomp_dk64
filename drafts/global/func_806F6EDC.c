// func_806F6EDC (src/global/F9450.c): Stage 4 close structural draft; target prologue, loop, call, and sign-extension match. Current mismatch is delay-slot scheduling and return register.
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
