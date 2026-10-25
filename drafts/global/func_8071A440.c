// func_8071A440 (src/global/11BC10.c): stage 3: all instructions and stack locals match, except 0x50 candidate frame versus 0x48 target frame
void func_8071A440(Ub5Actor *arg0, s8 *arg1) {
    f64 temp_fv1;
    f32 var_fv0;
    var_fv0 = (f32)(arg0->unk330->unk16 - arg0->unk34E) / (f32)arg0->unk330->unk16;
    if ((f64)var_fv0 > 0.7) var_fv0 = 1.0f;
    if ((arg0->unk35C == D_807FD580->unk88) && ((void *)arg0 == D_80028C30)) {
        temp_fv1 = (f64)var_fv0;
        lightSetFlags(1);
        lightAdd(arg0->unk340, arg0->unk344, arg0->unk348, 0.0f, 0.0f, 0.0f, (f32)(temp_fv1 * 50.0), 0, 0xFF, (u32)((-80.0f * var_fv0) + 255.0f), (u32)((-205.0f * var_fv0) + 255.0f));
    }
}
