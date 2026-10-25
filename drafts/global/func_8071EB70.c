// func_8071EB70 (src/global/11BC10.c): stage 3: m2c behavior recovered; frame/type integration remains
f32 *func_80610FE8(?, void *);                      /* extern */
extern void *D_807FC924;

void func_8071EB70(void *arg0, ? arg1) {
    f32 *sp24;
    f32 sp1C;
    f32 *temp_v0;
    f32 *var_v1;
    f32 temp_fa1;
    f32 temp_ft4;
    f32 temp_fv0;
    f32 temp_fv0_2;
    f32 temp_fv1;
    f32 temp_fv1_2;
    f32 var_fa0;
    f32 var_ft2;
    u8 temp_t9;

    var_v1 = arg0->unk384;
    temp_ft4 = (f32) ((s32) (arg0->unk35C * 3) / 4);
    if (var_v1 == NULL) {
        sp1C = temp_ft4;
        temp_v0 = func_80610FE8(4, arg0);
        temp_t9 = arg0->unk36D;
        arg0->unk384 = temp_v0;
        var_ft2 = (f32) temp_t9;
        if ((s32) temp_t9 < 0) {
            var_ft2 += 4294967296.0f;
        }
        *temp_v0 = var_ft2;
        var_v1 = arg0->unk384;
    }
    temp_fv0 = D_807FC924->unk224 - arg0->unk348;
    sp1C = temp_ft4;
    temp_fv1 = D_807FC924->unk21C - arg0->unk340;
    sp24 = var_v1;
    temp_fa1 = D_807FC924->unk220 - arg0->unk344;
    temp_fv0_2 = sqrtf((temp_fv0 * temp_fv0) + ((temp_fv1 * temp_fv1) + (temp_fa1 * temp_fa1)));
    if (temp_fv0_2 < temp_ft4) {
        arg0->unk36D = (u8) (u32) *sp24;
        return;
    }
    temp_fv1_2 = *sp24;
    var_fa0 = (f32) (s32) (temp_fv1_2 * ((temp_fv0_2 - temp_ft4) / ((f32) arg0->unk35C - temp_ft4)));
    if (temp_fv1_2 < var_fa0) {
        var_fa0 = (f32) (s32) temp_fv1_2;
    }
    arg0->unk36D = (u8) (u32) (temp_fv1_2 - var_fa0);
}
