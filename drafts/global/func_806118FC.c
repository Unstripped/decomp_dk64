// func_806118FC (src/global/16550.c): stage 4: code is score 0 / text-identical. With preceding func_80611850 kept GLOBAL_ASM, fdiff reports only relocations for own floats (.rodata base versus target D_807572DC/E0/E4); compiling the preceding helper C establishes the target 0xC rodata offset and gives TEXT OK. Kept GLOBAL_ASM pending its predecessor's match.
s16 func_80611DF4(s16);

f32 func_806118FC(f32 arg0) {
    s16 var_a0;

    if (arg0 >= 1.0f) {
        var_a0 = 0x7FFF;
    } else if (arg0 <= -1.0f) {
        var_a0 = -0x7FFF;
    } else {
        var_a0 = (s16)(s32)(arg0 * 32767.0f);
    }
    return ((f32)func_80611DF4(var_a0) * 3.1415927f) / 65535.0f;
}
