// func_80682AB4 (src/global/80150.c): from .scratch/R3D/func_80682AB4_best.c
void func_80682AB4(BehBStruct82AB4 *arg0) {
    f32 sp70 = D_807FBB40->unk7C;
    f32 sp6C = D_807FBB40->unk80 - 10.0f;
    f32 sp68 = D_807FBB40->unk84;
    f32 temp_fs1;
    f32 var_fv0;
    f32 temp_fv0;
    f32 var_fv0_2;
    s16 temp_s5;
    s16 temp_t0;
    s32 var_s1;
    BehBActor *temp_s2;

    temp_fs1 = (f32)arg0->unk4 / 20.0f;
    temp_s5 = (s16)((s32)(D_807FBB40->unkE6 + (819.2 * arg0->unk6)) & 0xFFF);
    temp_s5 = (s16)((s32)(temp_s5 - (819.2 * temp_fs1) * arg0->unk20) & 0xFFF);
    var_s1 = 0;
    do {
        temp_s2 = arg0->unk8[var_s1];
        temp_t0 = (s16)((s32)(4096.0 - (var_s1 * 819.2)) + temp_s5) & 0xFFF;
        temp_s2->unk7C = (func_80612794(temp_t0) * 45.0f) + sp70;
        temp_s2->unk84 = (func_80612790(temp_t0) * 45.0f) + sp68;
        temp_s2->unk80 = sp6C;
        if (var_s1 == arg0->unk6) {
            var_fv0 = 1.0f - temp_fs1;
        } else if (var_s1 == arg0->unk7) {
            var_fv0 = temp_fs1;
        } else {
            var_fv0 = 0.0f;
        }
        var_s1++;
        temp_fv0 = (f32)((f64)(f32)((f64)var_fv0 - 0.6) * 2.5);
        if (temp_fv0 < 0.0f) {
            var_fv0_2 = 0.0f;
        } else if (temp_fv0 > 1.0f) {
            var_fv0_2 = 1.0f;
        } else {
            var_fv0_2 = temp_fv0;
        }
        temp_s2->unk15F = (u32)((12.0f * var_fv0_2) + 3.0f);
    } while (var_s1 != 5);
}
