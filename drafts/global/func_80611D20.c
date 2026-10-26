// func_80611D20 (src/global/16A20.c): stage 4: 5+ fdiff iterations; frame/control flow/size fixed. Permuter -j2 --seconds 600 improved 740 to 190 (no zero); current remaining diff is three address-construction schedules plus pointer/value register allocation (a3/t0/t8). uopt trace run.
extern u16 D_80746A50[];
extern u16 D_80746ACC[];
extern u16 D_80746B4C[];

s32 func_80611D20(s32 arg0) {
    u16 *var_a2;
    s32 var_a1;
    s32 var_v1;
    long temp_a3;
    u16 next_value;
    s32 difference;
    u16 *temp_t0;

    var_v1 = 7;
    if (arg0 >= 0x7FE0) {
        var_a1 = 3;
        arg0 -= 0x7FE0;
        var_a2 = D_80746B4C;
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
    next_value = temp_t0[1];
    difference = temp_a3 - next_value;
    return temp_a3 - ((s32)((u32)difference * (arg0 & var_v1)) >> var_a1);
}
