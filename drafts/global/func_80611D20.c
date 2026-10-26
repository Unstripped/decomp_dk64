// func_80611D20 (src/global/16A20.c): stage 3: table interpolation recovered; remaining pointer/value register allocation after indexed table access.
extern ? D_80746A50;
extern ? D_80746ACC;
extern ? D_80746B4C;

s32 func_80611D20(s32 arg0) {
    ? *var_a2;
    s32 var_a0;
    s32 var_a1;
    s32 var_v1;
    u16 temp_a3;
    void *temp_t0;

    var_a0 = arg0;
    var_v1 = 7;
    if (var_a0 >= 0x7FE0) {
        var_a1 = 3;
        var_a2 = &D_80746B4C;
        var_a0 -= 0x7FE0;
    } else {
        var_v1 = 0x1FF;
        if (var_a0 >= 0x7800) {
            var_v1 = 0x1F;
            var_a1 = 5;
            var_a2 = &D_80746ACC;
            var_a0 -= 0x7800;
        } else {
            var_a1 = 9;
            var_a2 = &D_80746A50;
        }
    }
    temp_t0 = var_a2 + ((var_a0 >> var_a1) * 2);
    temp_a3 = temp_t0->unk0;
    return temp_a3 - ((s32) ((temp_a3 - temp_t0->unk2) * (var_a0 & var_v1)) >> var_a1);
}
