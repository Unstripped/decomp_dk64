// func_8071A674 (src/global/11BC10.c): stage 3: core loop/light body is close; target 0x48 versus candidate 0x60 frame and register allocation remain
void func_8071A674(Ub5Actor *arg0, s8 *arg1) {
    f32 var_fv0; f64 temp_fv1; s16 temp_v0; s32 *var_v0; s32 temp_t9;
    temp_v0 = arg0->unk330->unk16; var_v0 = &D_8002FBB0;
    var_fv0 = (f32)(temp_v0 - arg0->unk34E) / (f32)temp_v0;
    if ((f64)var_fv0 > 0.7) var_fv0 = 1.0f;
    do {
        temp_t9 = *var_v0++;
        if ((s32)arg0 == temp_t9) {
            temp_fv1 = (f64)var_fv0;
            lightSetFlags(1);
            lightAdd(arg0->unk340, arg0->unk344, arg0->unk348, 0.0f, 0.0f, 0.0f, (f32)(temp_fv1 * 50.0), 0, 0xFF, (u32)((-80.0f * var_fv0) + 255.0f), (u32)((-205.0f * var_fv0) + 255.0f));
            return;
        }
    } while (var_v0 != &D_8002FBC0);
}
