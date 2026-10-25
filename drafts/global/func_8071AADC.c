// func_8071AADC (src/global/11BC10.c): TEXT OK: prototyped definition and reduced locals produce exact code and extern relocation targets
void func_8071AADC(Ub5Actor *arg0, s8 *arg1) {
    f32 var_fv0;
    f32 var_fv1;
    s16 temp_v0;
    s32 temp_v0_2;
    temp_v0 = arg0->unk330->unk16;
    var_fv0 = (f32)(temp_v0 - arg0->unk34E) / (f32)temp_v0;
    if ((f64)var_fv0 > 0.7) var_fv0 = 1.0f;
    temp_v0_2 = arg0->unk35C;
    if (((u32)temp_v0_2 >> 16) != 0) var_fv1 = (f32)(temp_v0_2 & 0xFFFF) * var_fv0; else var_fv1 = (f32)(temp_v0_2 & 0xFFFF);
    lightSetFlags(1);
    lightAdd(arg0->unk340, arg0->unk344, arg0->unk348, 0.0f, 0.0f, 0.0f, var_fv1, 0, 0xFF, 0xFF, 0xFF);
}
