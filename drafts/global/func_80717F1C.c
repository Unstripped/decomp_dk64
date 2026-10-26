// func_80717F1C (src/global/11BC10.c): stage 3: target frame 0x28/$s0 save vs draft 0x30/$s0 save, 89/89 insns; blocks match but frame and constant ownership still differ.
typedef struct {
    u8 pad0[0x330];
    void *unk330;
    u8 pad334[4];
    void *unk338;
    u8 pad33C[4];
    f32 unk340;
    f32 unk344;
    f32 unk348;
    u8 pad34C[0x10];
    s32 unk35C;
    f32 unk360;
    u8 pad364[0x20];
    void *unk384;
} TimedEffectActorView;

typedef struct {
    f32 unk0;
    f32 unk4;
    f32 unk8;
    f32 unkC;
} VelocityMotionState;

typedef struct {
    u8 pad0[0xB8];
    f32 unkB8;
    u8 padBC[0x32];
    s16 unkEE;
} Ub2SourceView;

void func_80717F1C(arg0, arg1)
TimedEffectActorView *arg0;
s8 *arg1;
{
    VelocityMotionState *sp24;
    Ub2SourceView *temp_s0;
    VelocityMotionState *temp_v0;
    VelocityMotionState *var_v0;

    var_v0 = arg0->unk384;
    if (var_v0 == NULL) {
        temp_s0 = arg0->unk338;
        temp_v0 = func_80610FE8(0x10);
        arg0->unk384 = temp_v0;
        if (temp_s0 != NULL) {
            sp24 = temp_v0;
            temp_v0->unk0 = func_80612794(temp_s0->unkEE) * (temp_s0->unkB8 * 0.025f);
            temp_v0->unk4 = func_80612790(temp_s0->unkEE) * (temp_s0->unkB8 * 0.025f);
        } else {
            temp_v0->unk0 = 0.0f;
            temp_v0->unk4 = 0.0f;
        }
        temp_v0->unk8 = arg0->unk360;
        temp_v0->unkC = 0.2f;
        var_v0 = arg0->unk384;
    }
    arg0->unk344 = (f32) ((f64) arg0->unk344 - ((f64) arg0->unk35C / 100.0));
    arg0->unk340 = arg0->unk340 + var_v0->unk0;
    arg0->unk348 = arg0->unk348 + var_v0->unk4;
    var_v0->unk0 = (f32) ((f64) var_v0->unk0 * 0.93);
    var_v0->unk4 = (f32) ((f64) var_v0->unk4 * 0.93);
}
