// func_80724308 (src/global/127B00.c): stage 1: m2c starter regenerated in second pass; not yet integrated after priority small-function matches
f32 splineEvalCubic(f64, f32, u8, void *, f32, f32, f32); /* extern */
extern ? D_807FDB90;

void func_80724308(s32 arg0, f32 arg1, f32 arg2, f32 arg3, s32 arg4, f32 arg5) {
    s8 sp47;
    s8 sp46;
    u8 sp45;
    s8 sp44;
    void *sp40;
    f32 sp3C;
    f32 sp38;
    f64 sp20;
    f32 temp_fa1;
    f32 temp_ft4;
    f32 temp_fv1;
    f64 temp_fa0;
    s16 temp_v0;
    s16 temp_v0_3;
    s16 temp_v0_4;
    s32 temp_v0_5;
    s32 temp_v0_6;
    s32 temp_v0_7;
    s32 var_a1;
    s8 temp_v0_2;
    s8 temp_v1;
    s8 temp_v1_2;
    void *temp_a2;

    temp_a2 = *(&D_807FDB90 + (arg0 * 4));
    var_a1 = arg4;
    temp_v0 = temp_a2->unk4;
    if (var_a1 >= temp_v0) {
        var_a1 = temp_v0 - 1;
    }
    temp_v0_2 = var_a1 - 1;
    if (temp_v0_2 < 0) {
        sp44 = 0;
    } else {
        sp44 = temp_v0_2;
    }
    sp45 = (u8) var_a1;
    temp_v0_3 = temp_a2->unk4;
    temp_v1 = var_a1 + 1;
    if (temp_v1 >= temp_v0_3) {
        sp46 = temp_v0_3 - 1;
    } else {
        sp46 = temp_v1;
    }
    temp_v0_4 = temp_a2->unk4;
    temp_v1_2 = var_a1 + 2;
    if (temp_v1_2 >= temp_v0_4) {
        sp47 = temp_v0_4 - 1;
    } else {
        sp47 = temp_v1_2;
    }
    temp_v0_5 = temp_a2->unk0;
    temp_fa0 = (f64) arg5;
    sp20 = temp_fa0;
    sp40 = temp_a2;
    sp3C = splineEvalCubic(temp_fa0, (f32) (temp_v0_5 + ((u8) sp44 * 0xA))->unk2, (u8) var_a1, temp_a2, (f32) (temp_v0_5 + ((var_a1 & 0xFF) * 0xA))->unk2, (f32) (temp_v0_5 + ((u8) sp46 * 0xA))->unk2, (f32) (temp_v0_5 + ((u8) sp47 * 0xA))->unk2);
    temp_v0_6 = temp_a2->unk0;
    sp38 = splineEvalCubic(temp_fa0, (f32) *(temp_v0_6 + ((u8) sp44 * 0xA)), (u8) temp_a2, (bitwise void *) (f32) *(temp_v0_6 + (sp45 * 0xA)), (f32) *(temp_v0_6 + ((u8) sp46 * 0xA)), (f32) *(temp_v0_6 + ((u8) sp47 * 0xA)));
    temp_v0_7 = temp_a2->unk0;
    temp_fv1 = arg1 - sp3C;
    temp_fa1 = arg2 - sp38;
    temp_ft4 = arg3 - splineEvalCubic(temp_fa0, (f32) (temp_v0_7 + ((u8) sp44 * 0xA))->unk6, (u8) temp_a2, (bitwise void *) (f32) (temp_v0_7 + (sp45 * 0xA))->unk6, (f32) (temp_v0_7 + ((u8) sp46 * 0xA))->unk6, (f32) (temp_v0_7 + ((u8) sp47 * 0xA))->unk6);
    sqrtf((temp_fv1 * temp_fv1) + (temp_fa1 * temp_fa1) + (temp_ft4 * temp_ft4));
}
