// func_8071AADC (src/global/11BC10.c): stage 5: all instructions match apart from target 0x40 versus candidate 0x48 frame; dummy pad gets target local offset
void func_8071AADC(arg0, arg1)
Ub5Actor *arg0;
s8 *arg1;
{
    s32 pad; f32 sp38; f32 var_fv1; s16 temp_v0; s32 temp_v0_2;
    temp_v0 = arg0->unk330->unk16;
    var_fv1 = (f32)(temp_v0 - arg0->unk34E) / (f32)temp_v0;
    if ((f64)var_fv1 > 0.7) var_fv1 = 1.0f;
    temp_v0_2 = arg0->unk35C;
    if (((u32)temp_v0_2 >> 16) != 0) sp38 = (f32)(temp_v0_2 & 0xFFFF) * var_fv1; else sp38 = (f32)(temp_v0_2 & 0xFFFF);
    lightSetFlags(1);
    lightAdd(arg0->unk340, arg0->unk344, arg0->unk348, 0.0f, 0.0f, 0.0f, sp38, 0, 0xFF, 0xFF, 0xFF);
}
