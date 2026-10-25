// func_8071F444 (src/global/11BC10.c): stage 4: target 0x20 frame and callee-saved set retained; state-init/FP scheduling differs
typedef struct {
    f32 unk0;
    f32 unk4;
    f32 unk8;
    f32 unkC;
} Ud1F444MotionState;

typedef struct {
    u8 unk0[0x340];
    f32 unk340;
    f32 unk344;
    u8 unk348[6];
    s16 unk34E;
    u8 unk350;
    u8 unk351[0x33];
    f32 unk360;
    u8 unk364[0x1C];
    Ud1F444MotionState *unk384;
} Ud1F444ActorView;

void func_8071F444(Ud1F444ActorView *arg0, s8 *arg1) {
    Ud1F444MotionState *var_v1;

    var_v1 = arg0->unk384;
    if (var_v1 == NULL) {
        if (D_8076A064 & 1) {
            arg0->unk360 = arg0->unk360 * -1.0f;
        }
        var_v1 = func_80610FE8(8);
        arg0->unk384 = var_v1;
        var_v1->unk4 = 0.0f;
        var_v1->unk0 = (f32) (((s32) (func_80611A44() >> 0xF) % 20) + 5);
        var_v1->unkC = 0.0f;
        var_v1->unk8 = (f32) (((s32) (func_80611A44() >> 0xF) % 100) + 0xA);
    }
    arg0->unk344 = (f32) ((f64) arg0->unk344 + ((1.0 + (f64) func_80612794((s16) (s32) var_v1->unk4)) * (f64) (f32) (1.0 + ((f64) var_v1->unk0 * 0.4))));
    arg0->unk340 = (f32) (arg0->unk340 + (func_80612794((s16) (s32) var_v1->unkC) * (f32) ((f64) var_v1->unk8 * 0.5)));
    if (arg0->unk350 == 0) {
        arg0->unk34E = (s16) (s32) (((f64) func_80612794((s16) (s32) var_v1->unkC) * 2.5) + 2.5);
    }
    var_v1->unk4 = var_v1->unk4 + 100.0f;
    var_v1->unkC = var_v1->unkC + 50.0f;
    if (arg0->unk344 > 960.0f) {
        *arg1 = 1;
    }
}
