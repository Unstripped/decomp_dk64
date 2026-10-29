// func_8071D94C (src/global/11BC10.c): Fx11BG copy C (agent stopped: subagent credits ran out), deadsweep score full=41 vs expected; earlier note: Stage 3: compiled initializer behavior; target has exact allocation and randomization flow but stack-local scheduling differs.
u8 func_8071D94C(Fx11BGSource *arg0, TimedEffectActorView *arg1, s8 *arg2) {
    s16 sp38;
    s16 sp34;
    f32 sp30;
    f32 sp2C;
    f32 sp28;
    Fx11BGFallState *sp24;
    Fx11BGFallState *temp_v0;
    f32 var_fv0;

    temp_v0 = func_80610FE8(0x10);
    arg1->unk384 = temp_v0;
    sp24 = temp_v0;
    var_fv0 = func_806119FC();
    arg1->unk340 = arg1->unk340 + ((var_fv0 - 0.5f) * 2.0f);
    var_fv0 = func_806119FC();
    arg1->unk344 = arg1->unk344 + ((var_fv0 - 0.5f) * 2.0f);
    var_fv0 = func_806119FC();
    arg1->unk348 = arg1->unk348 + ((var_fv0 - 0.5f) * 2.0f);
    if (arg0 != NULL) {
        sp34 = (arg0->unkE6 + (func_806119A0() & 0x1FF) + 0x700) & 0xFFF;
        sp2C = arg0->unkB8 * 0.016666668f;
        if (!(sp2C < 1.0f)) {
            sp2C = 1.0f;
        }
        if (sp2C < 0.3) {
            *arg2 = 1;
        }
        sp28 = sp2C * 1.5f * 1.8f;
        arg1->unk338 = arg0;
    } else {
        sp2C = 0.8f;
        sp34 = (s16) (func_806119A0() % 4095U);
        sp28 = (func_806119FC() + 1.0f) * 3.0f;
    }
    arg1->unk360 = (f32) ((f64) arg1->unk360 * (0.5 * (f64) (1.0f + func_806119FC())));
    arg1->unk36D = 0x82;
    arg1->unk364 = arg1->unk360;
    sp30 = func_806119FC() * sp2C;
    sp24->unk0 = func_80612794(sp34) * sp30;
    sp24->unk4 = func_80612790(sp34) * sp30;
    sp24->unk8 = sp28;
    return collisionGetFloorHeight(&sp24->unkC);
}
