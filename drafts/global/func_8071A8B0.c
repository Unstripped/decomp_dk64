// func_8071A8B0 (src/global/11BC10.c): TEXT OK: reduced locals produce exact code and extern relocation targets
void func_8071A8B0(Ub5Actor *arg0, s8 *arg1) {
    f32 var_fv0;
    f32 var_ft4;
    s16 temp_v0;
    s32 temp_v0_2;
    temp_v0 = arg0->unk330->unk16;
    var_fv0 = (f32)(temp_v0 - arg0->unk34E) / (f32)temp_v0;
    if ((f64)var_fv0 > 0.7) var_fv0 = 1.0f;
    temp_v0_2 = arg0->unk35C;
    if (((u32)temp_v0_2 >> 16) != 0) var_ft4 = (f32)(temp_v0_2 & 0xFFFF) * var_fv0; else var_ft4 = (f32)(temp_v0_2 & 0xFFFF);
    lightSetFlags(1);
    lightAdd(arg0->unk340, arg0->unk344, arg0->unk348, 0.0f, 0.0f, 0.0f, var_ft4, 0, 0xFF, (u32)((-80.0f * var_fv0) + 255.0f), (u32)((-205.0f * var_fv0) + 255.0f));
}
