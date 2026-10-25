// func_8071A8B0 (src/global/11BC10.c): stage 5: arithmetic and light call match; closest diff is target 0x40 versus candidate 0x48 frame and swapped spills
void func_8071A8B0(Ub5Actor *arg0, s8 *arg1) {
    f32 sp3C; f32 sp38; f32 var_ft4; f32 var_fv0; s16 temp_v0; s32 temp_v0_2;
    temp_v0 = arg0->unk330->unk16;
    var_fv0 = (f32)(temp_v0 - arg0->unk34E) / (f32)temp_v0;
    if ((f64)var_fv0 > 0.7) var_fv0 = 1.0f;
    temp_v0_2 = arg0->unk35C;
    if (((u32)temp_v0_2 >> 16) != 0) var_ft4 = (f32)(temp_v0_2 & 0xFFFF) * var_fv0; else var_ft4 = (f32)(temp_v0_2 & 0xFFFF);
    sp3C = var_fv0; sp38 = var_ft4;
    lightSetFlags(1);
    lightAdd(arg0->unk340, arg0->unk344, arg0->unk348, 0.0f, 0.0f, 0.0f, var_ft4, 0, 0xFF, (u32)((-80.0f * var_fv0) + 255.0f), (u32)((-205.0f * var_fv0) + 255.0f));
}
