// func_80672328 (src/global/70FD0.c): Identified quad angle calculation with func_80611E60 (like 79890.c); blocked on callee func_806725A0 defined as void but return value checked
typedef struct M70I_Actor {
    u8 pad0[0x88];
    f32 unk88;
    u8 pad8C[4];
    f32 unk90;
} M70I_Actor;

s32 func_80611E60(s32);
void func_806725A0();

s32 func_80672328(M70I_Actor *arg0, f32 arg1, f32 arg2) {
    s32 sp44;
    s32 sp40;
    f32 sp34;
    s32 sp28;
    s32 sp24;
    s32 sp20;
    s32 sp1C;
    f32 temp_fv0;
    s16 var_a2;
    s32 temp_a1;
    s32 temp_ft1;
    s32 temp_ft2;
    s32 temp_ft4;
    s32 temp_ft5;
    s32 temp_v1;

    temp_ft2 = (s32)(arg0->unk88 * 8.0f);
    temp_ft5 = (s32)(arg0->unk90 * 8.0f);
    temp_ft1 = (s32)(arg1 * 8.0f);
    temp_ft4 = (s32)(arg2 * 8.0f);
    sp44 = temp_ft2;
    temp_v1 = temp_ft1 - temp_ft2;
    sp20 = temp_v1;
    sp28 = temp_ft1;
    sp40 = temp_ft5;
    temp_a1 = temp_ft4 - temp_ft5;
    sp1C = temp_a1;
    sp24 = temp_ft4;
    temp_fv0 = sqrtf((f32)((temp_v1 * temp_v1) + (temp_a1 * temp_a1)));
    sp34 = temp_fv0;
    if ((f64)temp_fv0 == 0.0) {
        return 1;
    }
    if (temp_v1 >= 0 && temp_a1 >= 0) {
        sp20 = temp_v1;
        sp1C = temp_a1;
        var_a2 = (s16)(func_80611E60((s32)(((f64)temp_v1 * 65535.9) / (f64)sp34)) >> 4);
    }
    if (temp_v1 >= 0 && temp_a1 < 0) {
        sp20 = temp_v1;
        sp1C = temp_a1;
        var_a2 = (func_80611E60((s32)(((f64)(sp40 - sp24) * 65535.9) / (f64)sp34)) >> 4) + 0x400;
    }
    if (temp_v1 < 0 && temp_a1 < 0) {
        sp20 = temp_v1;
        sp1C = temp_a1;
        var_a2 = (func_80611E60((s32)(((f64)(sp44 - sp28) * 65535.9) / (f64)sp34)) >> 4) + 0x800;
    }
    if (temp_v1 < 0 && temp_a1 >= 0) {
        var_a2 = (func_80611E60((s32)(((f64)temp_a1 * 65535.9) / (f64)sp34)) >> 4) + 0xC00;
    }
    func_806725A0(arg0, var_a2, var_a2);
    // returns v0 from func_806725A0 (which was defined as void)
    return 1;
}
