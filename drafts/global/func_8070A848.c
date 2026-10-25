// func_8070A848 (src/global/10E1D0.c): stage 6: output/input pointers match target with var_v1 declared before var_v0, but mask stays a1 rather than a0 and loop temporary coloring remains shifted; tried declaration order, pointer update order, explicit mask local, and direct argument walking
void func_8070A848(s32 *arg0, s32 *arg1) {
    s32 temp_t3;
    s32 var_a2;
    s32 *var_v1 = arg1;
    s32 *var_v0 = arg0;

    var_a2 = 0;
    if (((D_80744490 * D_80744494) / 16) > 0) do {
        var_a2++;
        var_v0 += 8;
        var_v0[-8] = var_v1[0] | 0x10001;
        temp_t3 = var_v1[1];
        var_v1 += 8;
        var_v0[-7] = temp_t3 | 0x10001;
        var_v0[-6] = var_v1[-6] | 0x10001;
        var_v0[-5] = var_v1[-5] | 0x10001;
        var_v0[-4] = var_v1[-4] | 0x10001;
        var_v0[-3] = var_v1[-3] | 0x10001;
        var_v0[-2] = var_v1[-2] | 0x10001;
        var_v0[-1] = var_v1[-1] | 0x10001;
    } while (var_a2 < ((D_80744490 * D_80744494) / 16));
}
