// func_8071E3EC (src/global/11BC10.c): stage 3: closest candidate reconstructs state and light cases; target frame 0x58 versus candidate 0x68, with remaining helper ABI/float-promotion scheduling
typedef struct { f32 unk0; f32 unk4; f32 unk8; } Ub7E3ECState;
extern s32 func_806531B8(f32, f32, s32, s32);
extern void lightAdd(f32, f32, s32, s32, f32, f32, f32, s32, u32, u32, u32);
extern void lightSetFlags(s32);
extern void lightSetRadius(s32);
extern void lightSetTargetId(s16);

void func_8071E3EC(TimedEffectActorView *arg0, s8 *arg1) {
    f32 sp4C;
    f32 sp48;
    f32 sp44;
    f32 sp40;
    f32 temp_fv0;
    f64 var_fv0;
    s32 temp_v0_2;
    Ub7E3ECState *temp_v0;
    Ub7E3ECState *var_v1;

    var_v1 = arg0->unk384;
    if (var_v1 == NULL) {
        temp_v0 = func_80610FE8(0xC);
        arg0->unk384 = temp_v0;
        temp_v0->unk0 = 0.0f;
        temp_v0->unk4 = 0.0f;
        temp_v0->unk8 = (f32)func_806531B8(arg0->unk340, arg0->unk344, arg0->unk348, 0);
        var_v1 = arg0->unk384;
    }
    if ((f64)var_v1->unk4 == 0.0) {
        var_v1->unk0 = (f32)((f64)var_v1->unk0 + 30.0);
        var_fv0 = (f64)var_v1->unk0;
        if (var_fv0 > 300.0) { var_v1->unk4 = 1.0f; var_v1->unk0 = 300.0f; var_fv0 = (f64)var_v1->unk0; }
    } else {
        var_v1->unk0 = (f32)((f64)var_v1->unk0 - 30.0);
        var_fv0 = (f64)var_v1->unk0;
        if (var_fv0 < 30.0) { *arg1 = 1; var_v1->unk0 = 30.0f; var_fv0 = (f64)var_v1->unk0; }
    }
    if (var_fv0 < 300.0) { sp4C = (f32)(var_fv0 / 300.0); } else { sp4C = 1.0f; }
    lightSetRadius(1000);
    lightSetTargetId((s16)(s32)var_v1->unk8);
    temp_v0_2 = arg0->unk35C;
    switch (temp_v0_2) {
    case 0:
        sp48 = 1.0f; sp44 = 1.0f; sp40 = 1.0f; lightSetFlags(2); lightSetRadius(1000); break;
    case 1:
        sp48 = 1.0f; sp44 = 0.5f; sp40 = 0.3f; lightSetFlags(3); lightSetRadius(1000); break;
    case 2:
        sp48 = 1.0f; sp44 = 0.5f; sp40 = 0.3f; lightSetFlags(2); lightSetRadius(2000); break;
    case 3:
        sp48 = 1.0f; sp44 = 1.0f; sp40 = 1.0f; lightSetFlags(2); lightSetRadius(2000); break;
    }
    temp_fv0 = 255.0f * sp4C;
    lightAdd(arg0->unk340, arg0->unk344, arg0->unk348, 0, 0.0f, 0.0f, var_v1->unk0, 0, (u32)(temp_fv0 * sp48), (u32)(temp_fv0 * sp44), (u32)(temp_fv0 * sp40));
}
