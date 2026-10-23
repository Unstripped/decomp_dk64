// func_8066A834 (src/global/699B0.c): starter m2c draft (unattempted)
s32 func_8066A834(void *arg0, f32 arg1, f32 arg2) {
    f32 sp20;
    f32 sp1C;
    f32 sp0;
    f32 temp_fa1;
    f32 temp_ft4;
    f32 temp_ft5;
    f32 temp_fv0;
    f32 temp_fv1;
    f32 var_fa0;
    f32 var_fv0;
    s32 var_v0;

    temp_fv1 = arg0->unk28;
    temp_fv0 = arg0->unk24;
    if (temp_fv0 < temp_fv1) {
        var_fa0 = temp_fv0;
    } else {
        var_fa0 = temp_fv1;
    }
    temp_fa1 = arg0->unk2C;
    if (!(var_fa0 < temp_fa1)) {
        var_fa0 = temp_fa1;
    }
    temp_ft4 = arg0->unk3C;
    temp_ft5 = arg0->unk40;
    if (temp_ft4 < temp_ft5) {
        sp20 = temp_ft4;
    } else {
        sp20 = temp_ft5;
    }
    sp0 = arg0->unk44;
    if (!(sp20 < sp0)) {
        sp20 = sp0;
    }
    if (temp_fv1 < temp_fv0) {
        sp1C = temp_fv0;
    } else {
        sp1C = temp_fv1;
    }
    if (!(temp_fa1 < sp1C)) {
        sp1C = temp_fa1;
    }
    if (temp_ft5 < temp_ft4) {
        var_fv0 = temp_ft4;
    } else {
        var_fv0 = temp_ft5;
    }
    if (!(sp0 < var_fv0)) {
        var_fv0 = sp0;
    }
    if ((arg1 < var_fa0) || (sp1C < arg1) || (arg2 < sp20) || (var_v0 = 1, (var_fv0 < arg2))) {
        var_v0 = 0;
    }
    return var_v0;
}
