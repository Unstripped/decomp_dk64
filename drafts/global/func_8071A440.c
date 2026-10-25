// func_8071A440 (src/global/11BC10.c): stage 5: behavior and arithmetic match; closest diff is target 0x48 versus candidate 0x68 frame/local placement
void func_8071A440(Ub5Actor *arg0, s8 *arg1) {
    f32 sp44;
    f64 sp38;
    f32 var_fv0;
    f64 temp_fv1;
    s16 temp_v0;

    temp_v0 = arg0->unk330->unk16;
    var_fv0 = (f32)(temp_v0 - arg0->unk34E) / (f32)temp_v0;
    if ((f64)var_fv0 > 0.7) var_fv0 = 1.0f;
    if ((arg0->unk35C == D_807FD580->unk88) && ((void *)arg0 == D_80028C30)) {
        temp_fv1 = (f64)var_fv0;
        sp38 = temp_fv1;
        sp44 = var_fv0;
        lightSetFlags(1);
        lightAdd(arg0->unk340, arg0->unk344, arg0->unk348, 0.0f, 0.0f, 0.0f, (f32)(temp_fv1 * 50.0), 0, 0xFF, (u32)((-80.0f * var_fv0) + 255.0f), (u32)((-205.0f * var_fv0) + 255.0f));
    }
}
