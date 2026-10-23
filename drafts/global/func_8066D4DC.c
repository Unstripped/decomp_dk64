// func_8066D4DC (src/global/70FD0.c): 409/409 insns, 0x170 text bytes (409/409 opcodes match, 0x54/0x42/0x38/0x34 stack offsets match, 0xA8 frame match); 0 off on size, pure regalloc differences
f32 func_80611BB4(f32, f32);

s16 func_8066D4DC(arg0, arg1)
s16 *arg0;
u8 *arg1;
{
    f32 sp9C[3];
    f32 sp90[3];
    f32 sp84[3];
    f32 sp78[3];
    f32 sp68[4];
    f32 len;
    f32 var_fa0;
    f32 var_fa1;
    f32 angle;
    f32 sp54;
    f32 dist;
    f32 temp_ft5;
    s16 var_v1;
    s16 sp42;
    f32 sp38;
    f32 sp34;

    sp9C[0] = arg0[6] - arg0[0];
    sp9C[1] = arg0[7] - arg0[1];
    sp9C[2] = arg0[8] - arg0[2];

    sp90[0] = arg0[3] - arg0[0];
    sp90[1] = arg0[4] - arg0[1];
    sp90[2] = arg0[5] - arg0[2];

    sp84[0] = sp9C[1] * sp90[2] - sp9C[2] * sp90[1];
    sp84[1] = sp9C[2] * sp90[0] - sp9C[0] * sp90[2];
    sp84[2] = sp9C[0] * sp90[1] - sp9C[1] * sp90[0];

    len = sqrtf(sp84[0] * sp84[0] + sp84[1] * sp84[1] + sp84[2] * sp84[2]);
    if ((f64)len < 0.01) {
        len = 0.01f;
    }
    len = 1.0f / len;

    sp78[0] = sp84[0] * len;
    sp78[1] = sp84[1] * len;
    sp78[2] = sp84[2] * len;

    if (sp84[0] >= 0.0f) {
        var_fa0 = sp84[0];
    } else {
        var_fa0 = 0.0 - sp84[0];
    }

    if (sp84[2] >= 0.0f) {
        var_fa1 = sp84[2];
    } else {
        var_fa1 = 0.0 - sp84[2];
    }

    if ((f64)var_fa1 < 0.01 && (f64)var_fa1 > -0.01) {
        angle = 1.57f;
    } else {
        angle = func_80611BB4(var_fa0, var_fa1);
    }

    if (0.0 <= (f64)sp84[0] && 0.0 <= (f64)sp84[2]) {
        sp42 = (s32)((f64)(f32)((f64)angle * 57.29577791868205) * 11.375);
    }
    var_v1 = sp42;
    if (0.0 <= (f64)sp84[0] && (f64)sp84[2] < 0.0) {
        var_v1 = (s32)((180.0 - (f64)(f32)((f64)angle * 57.29577791868205)) * 11.375);
    }
    if ((f64)sp84[0] < 0.0 && (f64)sp84[2] < 0.0) {
        var_v1 = (s32)(((f64)(f32)((f64)angle * 57.29577791868205) + 180.0) * 11.375);
    }
    if ((f64)sp84[0] < 0.0 && 0.0 <= (f64)sp84[2]) {
        var_v1 = (s32)((360.0 - (f64)(f32)((f64)angle * 57.29577791868205)) * 11.375);
    }

    sp78[0] *= 20.0f;
    sp78[1] *= 20.0f;
    sp78[2] *= 20.0f;

    sp68[0] = sp78[0] + (f32)arg0[0];
    sp68[1] = sp78[1] + (f32)arg0[1];
    sp68[2] = sp78[2] + (f32)arg0[2];

    sp9C[0] = arg0[0] - arg0[3];
    sp9C[1] = arg0[1] - arg0[4];
    sp9C[2] = arg0[2] - arg0[5];

    sp90[0] = arg0[0] - arg0[6];
    sp90[1] = arg0[1] - arg0[7];
    sp90[2] = arg0[2] - arg0[8];

    temp_ft5 = sp9C[1] * sp90[2] - sp90[1] * sp9C[2];
    sp38 = sp9C[2] * sp90[0] - sp90[2] * sp9C[0];
    sp34 = sp9C[0] * sp90[1] - sp90[0] * sp9C[1];

    sp54 = -(((f32)arg0[3] * temp_ft5) + ((f32)arg0[4] * sp38) + ((f32)arg0[5] * sp34));

    dist = (temp_ft5 * sp68[0]) + (sp38 * sp68[1]) + (sp34 * sp68[2]) + sp54;

    if ((!(0.0 < (f64)dist) || !(0.0 < (f64)sp54)) && (!((f64)dist < 0.0) || !((f64)sp54 < 0.0))) {
        var_v1 -= 0x800;
        if (var_v1 < 0) {
            var_v1 += 0xFFF;
        }
        *arg1 = 1;
    } else {
        *arg1 = 0;
    }

    return var_v1;
}
