// func_806EC4AC (src/global/EFDC0.c): stage 1 m2c starter; large state transition requires block-order work
? func_80614E78(f32, f32, void *, ?, void **, s16 *); /* extern */
? func_806CF398(void *, void **);                   /* extern */
extern ? D_80753250;
extern ? D_8075388C;
extern ? D_807538D8;
extern ? D_807538E8;
extern ? D_807538F8;
extern ? D_80753988;
extern ? D_807539FC;
extern ? D_80753A5C;
extern void *D_807FBB40;
extern void *D_807FBB48;
extern void *D_807FD580;
extern s16 D_807FD584;

void func_806EC4AC(void) {
    f32 temp_fa0;
    f32 temp_ft4;
    f32 temp_fv0;
    f32 temp_fv0_2;
    f32 temp_fv0_3;
    f32 temp_fv1;
    f32 var_fa1;
    f32 var_fs0;
    f32 var_ft5;
    f32 var_fv1;
    s16 temp_v0;
    s32 temp_v1;

    func_806CF398(D_807FBB48, &D_807FBB48);
    temp_fv0 = *(&D_80753A5C + (D_807FD584 * 4));
    temp_v1 = D_807FD584 * 2;
    if (temp_fv0 > 0.0f) {
        var_fs0 = temp_fv0;
    } else {
        var_fs0 = -temp_fv0;
    }
    temp_ft4 = D_807FBB48->unkAC;
    temp_fv0_2 = (f32) *(&D_807538D8 + temp_v1);
    var_fv1 = D_807FBB48->unkA0 - temp_ft4;
    if (temp_fv0_2 < var_fv1) {
        var_fv1 = temp_fv0_2;
    }
    temp_v0 = *(&D_807538E8 + temp_v1);
    temp_fa0 = ((((f32) (*(&D_807538F8 + temp_v1) - temp_v0) * (var_fv1 / temp_fv0_2)) + (f32) temp_v0) - ((temp_ft4 - (f32) *(&D_8075388C + temp_v1)) - D_807FBB48->unk80)) * 40.0f;
    if (temp_fa0 > 0.0f) {
        var_fa1 = (f32) ((f64) D_807FBB48->unkC0 * (0.5 + (f64) ((var_fv1 * 40.0f) / (2.0f * (temp_fv0_2 * 40.0f)))));
        var_ft5 = (var_fa1 * var_fa1) / (2.0f * temp_fa0);
        if (var_ft5 < var_fs0) {
            goto block_9;
        }
    } else {
        var_fa1 = 0.0f;
block_9:
        var_ft5 = var_fs0;
    }
    D_807FBB48->unkC0 = var_fa1;
    D_807FD580->unk1C = var_ft5;
    D_807FD580->unk10 = 0;
    D_807FD580->unk30 = (f32) *(&D_80753250 + (D_807FD584 * 4));
    temp_fv1 = *(&D_80753988 + (D_807FD584 * 4));
    temp_fv0_3 = D_807FBB40->unkB8;
    if (temp_fv0_3 < temp_fv1) {
        D_807FBB40->unkB8 = temp_fv0_3;
    } else {
        D_807FBB40->unkB8 = temp_fv1;
    }
    D_807FBB48->unk154 = 0x4E;
    D_807FBB48->unk155 = 0;
    func_80614E78(temp_fa0, var_fa1, D_807FBB40, 0x35, &D_807FBB48, &D_807FD584);
    D_807FD580->unk48 = (s16) *(&D_807539FC + (D_807FD584 * 2));
}
