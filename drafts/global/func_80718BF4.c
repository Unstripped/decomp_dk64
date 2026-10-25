// func_80718BF4 (src/global/11BC10.c): stage 4: frame 0x48 retained; ground-check scratch currently sp+0x38 versus target sp+0x30. Reordering locals moved it to sp+0x44, so original order retained.
typedef struct {
    s32 unk0;
    f32 unk4;
    f32 unk8;
    f32 unkC;
    f32 unk10;
    f32 unk14;
    f32 unk18;
    f32 unk1C;
} NM2MotionState;

s32 collisionCheckGroundAtPoint(f32, f32, f32 *);
s32 collisionGetFloorHeight(s32 *);

void func_80718BF4(TimedEffectActorView *arg0, s8 *arg1) {
    f64 temp_fv1;
    f32 sp3C;
    f32 sp30;
    f32 temp_fv0;
    f32 var_fv1;

    if (arg0->unk384 == NULL) {
        arg0->unk384 = func_80610FE8(0x20);
        ((NM2MotionState *)arg0->unk384)->unk0 = 0;
        ((NM2MotionState *)arg0->unk384)->unk4 = 0.0f;
        ((NM2MotionState *)arg0->unk384)->unk8 = arg0->unk340;
        ((NM2MotionState *)arg0->unk384)->unkC = arg0->unk348;
        ((NM2MotionState *)arg0->unk384)->unk10 = ((f64)(func_806119A0() % 10000U) / 10000.0) * 0.19;
        ((NM2MotionState *)arg0->unk384)->unk14 = ((f64)(func_806119A0() % 10000U) / 10000.0) * 0.077;
        if ((func_806119A0() / 10000U) & 1) {
            ((NM2MotionState *)arg0->unk384)->unk10 = (f32)(0.0 - (f64)((NM2MotionState *)arg0->unk384)->unk10);
            ((NM2MotionState *)arg0->unk384)->unk14 = (f32)(0.0 - (f64)((NM2MotionState *)arg0->unk384)->unk14);
        }
        sp30 = arg0->unk344;
        collisionCheckGroundAtPoint(arg0->unk340, arg0->unk348, &sp30);
        if (collisionGetFloorHeight((s32 *)((u8 *)arg0->unk384 + 0x18)) == 0) {
            ((NM2MotionState *)arg0->unk384)->unk18 = 0.0f;
        }
        ((NM2MotionState *)arg0->unk384)->unk1C = (f32)D_8076A064;
    }
    sp3C = func_80612D1C(((NM2MotionState *)arg0->unk384)->unk10 * (f32)((NM2MotionState *)arg0->unk384)->unk0);
    temp_fv0 = func_80612D1C(((NM2MotionState *)arg0->unk384)->unk14 * (f32)((NM2MotionState *)arg0->unk384)->unk0) * 6.0f;
    arg0->unk340 = ((NM2MotionState *)arg0->unk384)->unk8 + (sp3C * 6.0f);
    arg0->unk348 = ((NM2MotionState *)arg0->unk384)->unkC + temp_fv0;
    ((NM2MotionState *)arg0->unk384)->unk0 += 1;
    ((NM2MotionState *)arg0->unk384)->unk4 = (f32)((f64)((NM2MotionState *)arg0->unk384)->unk4 + 0.02);
    var_fv1 = ((NM2MotionState *)arg0->unk384)->unk4;
    if ((f64)var_fv1 > 1.0) {
        ((NM2MotionState *)arg0->unk384)->unk4 = 1.0f;
        var_fv1 = ((NM2MotionState *)arg0->unk384)->unk4;
    }
    arg0->unk344 += var_fv1;
    switch (arg0->unk35C) {
    case 0:
        arg0->unk360 = (f32)(((f64)((NM2MotionState *)arg0->unk384)->unk0 * 0.01) + 0.01);
        if ((f64)arg0->unk360 > 0.12) arg0->unk360 = 0.12f;
        break;
    case 1:
        arg0->unk360 = (f32)(((f64)((NM2MotionState *)arg0->unk384)->unk0 * 0.005) + 0.05);
        if ((f64)arg0->unk360 > 0.07) arg0->unk360 = 0.07f;
        break;
    case 2:
        arg0->unk360 = (f32)(((f64)((NM2MotionState *)arg0->unk384)->unk0 * 0.02) + 0.02);
        if ((f64)arg0->unk360 > 0.24) arg0->unk360 = 0.24f;
        break;
    }
    arg0->unk364 = arg0->unk360;
    sp3C = func_80612D1C((f32)((f64)((NM2MotionState *)arg0->unk384)->unk0 * 0.17));
    temp_fv1 = (f64)func_80612D1C((f32)((f64)((NM2MotionState *)arg0->unk384)->unk0 * 0.2267)) * 0.03;
    arg0->unk360 = (f32)((f64)arg0->unk360 + ((f64)sp3C * 0.03));
    arg0->unk364 = (f32)((f64)arg0->unk364 + temp_fv1);
    if ((((NM2MotionState *)arg0->unk384)->unk1C + 100.0f) < (f32)D_8076A064) *arg1 = 1;
    if (((NM2MotionState *)arg0->unk384)->unk18 <= arg0->unk344) {
        *arg1 = 1;
        func_80718124(0.3f, arg0->unk340, arg0->unk344, arg0->unk348);
    }
}
