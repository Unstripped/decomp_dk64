// func_8002B180 (src/race/6650.c): stage 5 (frame 0x68, s0 only, text size match; 74 normalized diff lines, mostly FP regalloc): (a) D_807FDCA0 address hoisted to a1 for 2nd/3rd access (orig keeps plain lui/lw); (b) temp_ft4/var_ft5 get f14/f16 (orig f16/f18) and the 1.2f product stays in f12 (orig spills it to 0x54(sp), i.e. only f2/f16/f18 available to variables). Tried: decl-order sweeps (no effect), int vs s32, sp54 reuse for var_ft5 result (74 vs 94), pad/tmp ptr temp for arg0->unk30 (needed for v0/v1), array/volatile sp54 (worse), permuter 3x. Needs f32 unk7C/80/84 + 5xf32 mathAngleDiscrete decls.
// NEEDS (existing top-block declarations changed in the draft's compile): Actor_BB40.unk7C/unk80/unk84 are f32 (not s32);
// mathAngleDiscrete is s32 mathAngleDiscrete(f32, f32, f32, f32, f32); func_806CC10C stays s32 (s16, s16).
// Struct_FDCA0_Sub / Struct_DC90 / Struct_DC98 / Struct_DC9C / Struct_FDCA0 / Struct_arg0 / Struct_sp5C / Struct_sp58 /
// Struct_8002B180_Arg1 are the ones already declared above the function in src/race/6650.c.

void func_8002B180(Struct_sp58 *arg0, Struct_8002B180_Arg1 *arg1) {
    f32 var_ft5;
    f32 var_fv1;
    f32 temp_ft4;
    f32 sp58;
    f32 sp54;
    f32 dx;
    f32 dz;
    f32 temp_fv0;
    f32 sp_angle;
    Struct_sp5C *sp40;
    s32 sp3C;
    f32 sp38;
    Struct_FDCA0_Sub *var_v1;
    u8 idx;
    Struct_arg0 *pad;

    pad = arg0->unk30;
    sp40 = pad->unk174;
    sp3C = func_8002E960(sp40->unk26);
    sp38 = func_8002F784(sp3C, arg0, arg1->unk4);
    idx = D_807FDC98->unk20[D_807FDC90->unk25 * 2];
    var_v1 = &D_807FDCA0->unk14[idx];
    dx = (f32)var_v1->unk0 - D_807FBB40->unk7C;
    dz = (f32)var_v1->unk4 - D_807FBB40->unk84;
    sp58 = sqrtf((dx * dx) + (dz * dz));
    var_v1 = &D_807FDCA0->unk14[idx];
    if (sp58 < (f32)var_v1->unk7) {
        D_807FDC90->unk25++;
        D_807FDC90->unk25 = D_807FDC90->unk25 % D_807FDC9C->unk11;
        var_v1 = &D_807FDCA0->unk14[idx];
    }
    sp_angle = mathAngleDiscrete((f32)var_v1->unk0, (f32)var_v1->unk4, D_807FBB40->unk7C, D_807FBB40->unk84, sp58);
    temp_ft4 = func_806CC10C((s16)sp_angle, D_807FBB40->unkE6);

    var_ft5 = temp_ft4;
    var_fv1 = (u32)D_807FDCA0->unk14[idx].unk7;
    sp54 = var_fv1 * 1.2f;
    if (sp58 < sp54) {
        sp54 = temp_ft4 * (1.0 + ((1.0f - ((sp58 - var_fv1) / (sp54 - var_fv1))) * 1.5 * (2.0f * arg0->unk4)));
        var_ft5 = sp54;
    }
    arg0->unkC += ((var_ft5 * 0.0033333334f) - arg0->unkC) * 0.5f;
    if (arg0->unk34 >= 2 && arg0->unk34 < 5) {
        if (arg1->unkF != 0 && raceGetProgressPercent(sp3C, arg0, sp40) > 0.75) {
            func_8002DE78(arg1, 0, &D_8002FC70, &D_8002FCA0);
        }
        temp_fv0 = func_8002E1C8(arg1, sp38, &D_8002FC70, &D_8002FCA0);
        if (D_807FBB40->unkB8 < 650.0f) {
            D_807FBB40->unkB8 = D_807FBB40->unkB8;
        } else {
            D_807FBB40->unkB8 = 650.0f;
        }
        arg0->unk4 = temp_fv0;
    }
}
