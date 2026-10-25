// func_8071D94C (src/global/11BC10.c): Stage 3: compiled initializer behavior; target has exact allocation and randomization flow but stack-local scheduling differs.
typedef struct {
    f32 unk0;
    f32 unk4;
    f32 unk8;
    f32 unkC;
} Ub3bFallingState;

typedef struct {
    u8 pad0[0x7C];
    f32 unk7C;
    u8 pad80[4];
    f32 unk84;
    u8 pad88[0x5E];
    s16 unkE6;
} Ub3bPositionSource;

void collisionGetFloorHeight(void *);

void func_8071D94C(void *arg0, TimedEffectActorView *arg1, s8 *arg2) {
    Ub3bFallingState *state;
    Ub3bPositionSource *source;
    s16 sp34;
    f32 sp30;
    f32 sp2C;
    f32 sp28;

    state = func_80610FE8(0x10);
    arg1->unk384 = state;
    arg1->unk340 += 2.0f * (func_806119FC() - 0.5f);
    arg1->unk344 += 2.0f * (func_806119FC() - 0.5f);
    arg1->unk348 += 2.0f * (func_806119FC() - 0.5f);
    if (arg0 != NULL) {
        source = arg0;
        sp34 = (source->unkE6 + (func_806119A0() & 0x1FF) + 0x700) & 0xFFF;
        sp2C = source->unk84 * 0.016666668f;
        if (sp2C > 1.0f) sp2C = 1.0f;
        if ((f64) sp2C < 0.3) *arg2 = 1;
        sp28 = sp2C * 1.5f * 1.8f;
        arg1->unk338 = arg0;
    } else {
        sp2C = 0.8f;
        sp34 = (s16) (func_806119A0() % 4095U);
        sp28 = (func_806119FC() + 1.0f) * 3.0f;
    }
    sp30 = func_806119FC() * sp2C;
    arg1->unk36D = 0x82;
    arg1->unk360 = (f32) ((f64) arg1->unk360 * (0.5 * (f64) (1.0f + func_806119FC())));
    arg1->unk364 = arg1->unk360;
    state->unk0 = func_80612794(sp34) * sp30;
    state->unk4 = func_80612790(sp34) * sp30;
    state->unk8 = sp28;
    collisionGetFloorHeight(&state->unkC);
}
