// func_80718BF4 (src/global/11BC10.c): stage 4: matches target 0x48 frame and initialization through first movement; closest trial uses direct state loads, but collision scratch is at sp+0x38 rather than target sp+0x30 and later switch register flow differs
typedef struct {
    s32 unk0;
    f32 unk4;
    f32 unk8;
    f32 unkC;
    f32 unk10;
    f32 unk14;
    f32 unk18;
    f32 unk1C;
} Ub8MotionState;

s32 collisionCheckGroundAtPoint(f32, f32, f32 *);
s32 collisionGetFloorHeight(s32 *);

void func_80718BF4(Ub2ActorView *arg0, s8 *arg1) {
    f64 temp_fv1;
    f32 sp3C;
    f32 sp30;
    f32 temp_fv0;
    f32 var_fv1;

    if (arg0->unk384 == NULL) {
        arg0->unk384 = func_80610FE8(0x20);
        ((Ub8MotionState *)arg0->unk384)->unk0 = 0;
        ((Ub8MotionState *)arg0->unk384)->unk4 = 0.0f;
        ((Ub8MotionState *)arg0->unk384)->unk8 = arg0->unk340;
        ((Ub8MotionState *)arg0->unk384)->unkC = arg0->unk348;
        ((Ub8MotionState *)arg0->unk384)->unk10 = ((f64)(func_806119A0() % 10000U) / 10000.0) * 0.19;
        ((Ub8MotionState *)arg0->unk384)->unk14 = ((f64)(func_806119A0() % 10000U) / 10000.0) * 0.077;
        if ((func_806119A0() / 10000U) & 1) {
            ((Ub8MotionState *)arg0->unk384)->unk10 = (f32)(0.0 - (f64)((Ub8MotionState *)arg0->unk384)->unk10);
            ((Ub8MotionState *)arg0->unk384)->unk14 = (f32)(0.0 - (f64)((Ub8MotionState *)arg0->unk384)->unk14);
        }
        sp30 = arg0->unk344;
        collisionCheckGroundAtPoint(arg0->unk340, arg0->unk348, &sp30);
        if (collisionGetFloorHeight((s32 *)((u8 *)arg0->unk384 + 0x18)) == 0) {
            ((Ub8MotionState *)arg0->unk384)->unk18 = 0.0f;
        }
        ((Ub8MotionState *)arg0->unk384)->unk1C = (f32)D_8076A064;
    }
    sp3C = func_80612D1C(((Ub8MotionState *)arg0->unk384)->unk10 * (f32)((Ub8MotionState *)arg0->unk384)->unk0);
    temp_fv0 = func_80612D1C(((Ub8MotionState *)arg0->unk384)->unk14 * (f32)((Ub8MotionState *)arg0->unk384)->unk0) * 6.0f;
    arg0->unk340 = ((Ub8MotionState *)arg0->unk384)->unk8 + (sp3C * 6.0f);
    arg0->unk348 = ((Ub8MotionState *)arg0->unk384)->unkC + temp_fv0;
    ((Ub8MotionState *)arg0->unk384)->unk0 += 1;
    ((Ub8MotionState *)arg0->unk384)->unk4 = (f32)((f64)((Ub8MotionState *)arg0->unk384)->unk4 + 0.02);
    var_fv1 = ((Ub8MotionState *)arg0->unk384)->unk4;
    if ((f64)var_fv1 > 1.0) {
        ((Ub8MotionState *)arg0->unk384)->unk4 = 1.0f;
        var_fv1 = ((Ub8MotionState *)arg0->unk384)->unk4;
    }
    arg0->unk344 += var_fv1;
    switch (arg0->unk35C) {
    case 0:
        arg0->unk360 = (f32)(((f64)((Ub8MotionState *)arg0->unk384)->unk0 * 0.01) + 0.01);
        if ((f64)arg0->unk360 > 0.12) arg0->unk360 = 0.12f;
        break;
    case 1:
        arg0->unk360 = (f32)(((f64)((Ub8MotionState *)arg0->unk384)->unk0 * 0.005) + 0.05);
        if ((f64)arg0->unk360 > 0.07) arg0->unk360 = 0.07f;
        break;
    case 2:
        arg0->unk360 = (f32)(((f64)((Ub8MotionState *)arg0->unk384)->unk0 * 0.02) + 0.02);
        if ((f64)arg0->unk360 > 0.24) arg0->unk360 = 0.24f;
        break;
    }
    arg0->unk364 = arg0->unk360;
    sp3C = func_80612D1C((f32)((f64)((Ub8MotionState *)arg0->unk384)->unk0 * 0.17));
    temp_fv1 = (f64)func_80612D1C((f32)((f64)((Ub8MotionState *)arg0->unk384)->unk0 * 0.2267)) * 0.03;
    arg0->unk360 = (f32)((f64)arg0->unk360 + ((f64)sp3C * 0.03));
    arg0->unk364 = (f32)((f64)arg0->unk364 + temp_fv1);
    if ((((Ub8MotionState *)arg0->unk384)->unk1C + 100.0f) < (f32)D_8076A064) *arg1 = 1;
    if (((Ub8MotionState *)arg0->unk384)->unk18 <= arg0->unk344) {
        *arg1 = 1;
        func_80718124(0.3f, arg0->unk340, arg0->unk344, arg0->unk348);
    }
}
