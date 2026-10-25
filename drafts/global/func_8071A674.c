// func_8071A674 (src/global/11BC10.c): stage 3: compiled C with target light body; direct post-increment loop and one-argument lightSetFlags retain target call sequence. Closest candidate frame is 0x58 versus target 0x48; end-pointer allocation and one remaining stack local differ.
extern s32 D_8002FBB0[];
extern s32 D_8002FBC0;
void func_8071A674(Ub5Actor *arg0, s8 *arg1) {
    f64 temp_fv1;
    f32 var_fv0;
    s32 *var_v0;

    var_v0 = &D_8002FBB0[0];
    var_fv0 = (f32)(arg0->unk330->unk16 - arg0->unk34E) / (f32)arg0->unk330->unk16;
    if ((f64)var_fv0 > 0.7) {
        var_fv0 = 1.0f;
    }
    do {
        if ((s32)arg0 == *var_v0++) {
            temp_fv1 = (f64)var_fv0;
            lightSetFlags(1);
            lightAdd(arg0->unk340, arg0->unk344, arg0->unk348, 0.0f, 0.0f, 0.0f,
                     (f32)(temp_fv1 * 50.0), 0, 0xFF,
                     (u32)((-80.0f * var_fv0) + 255.0f),
                     (u32)((-205.0f * var_fv0) + 255.0f));
            return;
        }
    } while (var_v0 != &D_8002FBC0);
}
