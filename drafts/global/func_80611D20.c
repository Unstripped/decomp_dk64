// func_80611D20 (src/global/16A20.c): stage 4: exact control flow and size; remaining table/shift register swap (a1/a2) and dependent temporaries
extern u16 D_80746A50[];
extern u16 D_80746ACC[];
extern u16 D_80746B4C[];

s32 func_80611D20(s32 arg0) {
    u16 *var_a2;
    s32 var_a1;
    s32 var_v1;
    u16 temp_a3;
    u16 *temp_t0;

    var_v1 = 7;
    if (arg0 >= 0x7FE0) {
        var_a2 = D_80746B4C;
        var_a1 = 3;
        arg0 -= 0x7FE0;
    } else {
        var_v1 = 0x1FF;
        if (arg0 >= 0x7800) {
            var_a2 = D_80746ACC;
            var_v1 = 0x1F;
            var_a1 = 5;
            arg0 -= 0x7800;
        } else {
            var_a2 = D_80746A50;
            var_a1 = 9;
        }
    }
    temp_t0 = var_a2 + (arg0 >> var_a1);
    temp_a3 = *temp_t0;
    return temp_a3 - ((s32)((u32)(temp_a3 - temp_t0[1]) * (arg0 & var_v1)) >> var_a1);
}
