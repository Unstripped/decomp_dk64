// func_80612C30 (src/global/17540.c): stage 2: m2c starter; remaining diff not yet reduced
f32 func_80612D10(f32);                             /* extern */
f32 func_80612D1C(f32);                             /* extern */

void func_80612C30(f32 (*arg0)[4], f32 arg1) {
    f32 sp24;
    f32 sp20;
    f32 temp_fa0;
    f32 temp_fv0;

    temp_fa0 = arg1 * 0.017453292f;
    arg1 = temp_fa0;
    temp_fv0 = func_80612D1C(temp_fa0);
    sp24 = temp_fv0;
    sp20 = func_80612D10(arg1);
    guMtxIdentF(arg0);
    arg0[2][0] = temp_fv0;
    arg0[0][2] = -temp_fv0;
    arg0[0][0] = sp20;
    arg0[2][2] = sp20;
}
