// func_806F46B0 (src/global/F93B0.c): stage 3: matched loop blocks and instruction count; register allocation remains divergent
extern ? D_80753EA0;
extern s32 D_8076A0A8;

f32 func_806F46B0(s16 arg0) {
    s16 var_v1;
    s8 temp_a3;
    void *temp_a0;

    var_v1 = 0;
loop_1:
    temp_a0 = &D_80753EA0 + (var_v1 * 6);
    if ((D_8076A0A8 == temp_a0->unk0) && ((temp_a3 = temp_a0->unk2, (arg0 == temp_a3)) || (temp_a3 == -1))) {
        return (f32) temp_a0->unk4;
    }
    var_v1 += 1;
    if (var_v1 >= 0xD) {
        return 20000.0f;
    }
    goto loop_1;
}
