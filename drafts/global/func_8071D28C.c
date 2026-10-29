// func_8071D28C (src/global/11BC10.c): Fx11BG copy C (agent stopped: subagent credits ran out), deadsweep score full=118 vs expected; earlier note: Stage 3: compiled behavioral orbit draft; saved-register/frame set matches but state pointer allocation and late floating operation ordering differ.
void func_807149FC(s32);
void func_80714A28(s16);
void playerStateQueueCallback();
u8 collisionGetFloorHeight(f32 *);
extern f32 D_80755674;
extern f32 D_80755678;

typedef struct {
    u8 pad0[0x7C];
    f32 unk7C;
    f32 unk80;
    f32 unk84;
    u8 pad88[0x24];
    f32 unkAC;
    u8 padB0[0x8];
    f32 unkB8;
    u8 padBC[0x2A];
    s16 unkE6;
} Fx11BGSource;

typedef struct {
    f32 unk0;
    f32 unk4;
    f32 unk8;
    f32 unkC;
    f32 unk10;
    f32 unk14;
    f32 unk18;
    f32 unk1C;
} Fx11BGOrbitState;

typedef struct {
    f32 unk0;
    f32 unk4;
    f32 unk8;
} Fx11BGVelocityState;

typedef struct {
    f32 unk0;
    f32 unk4;
    f32 unk8;
    f32 unkC;
} Fx11BGFallState;

u8 func_8071D94C(Fx11BGSource *, TimedEffectActorView *, s8 *);

void func_8071D28C(TimedEffectActorView *arg0, s8 *arg1) {
    Fx11BGOrbitState *var_v1;
    Fx11BGOrbitState *temp_v0;
    Fx11BGSource *source;

    var_v1 = arg0->unk384;
    source = arg0->unk338;
    if (var_v1 == NULL) {
        temp_v0 = func_80610FE8(0x20);
        arg0->unk384 = temp_v0;
        temp_v0->unk0 = sqrtf(((source->unk7C - arg0->unk340) * (source->unk7C - arg0->unk340)) + ((source->unk84 - arg0->unk348) * (source->unk84 - arg0->unk348)));
        temp_v0->unk4 = (func_806119FC() * 20.0f) + 10.0f;
        temp_v0->unk8 = func_806119FC() * 4095.0f;
        temp_v0->unkC = (func_806119FC() * 90.0f) + 10.0f;
        temp_v0->unk10 = (f32) source->unkE6;
        temp_v0->unk14 = func_806119FC() * 30.0f;
        temp_v0->unk18 = 0.0f;
        temp_v0->unk1C = (f32) ((((randomNonNegative() >> 0xF) % 0xFF) % 2) * 2.0f) - 1.0f;
        var_v1 = arg0->unk384;
    }
    var_v1->unk0 = (f32) ((f64) var_v1->unk0 + ((f64) (var_v1->unk4 - var_v1->unk0) * 0.15));
    var_v1->unk14 = (f32) ((f64) var_v1->unk14 + ((f64) (120.0f - var_v1->unk14) * 0.01));
    var_v1->unk8 = var_v1->unk8 + var_v1->unkC;
    var_v1->unk10 = var_v1->unk10 + (var_v1->unk1C * var_v1->unk14);
    arg0->unk340 = (func_80612794((s16) var_v1->unk10) * var_v1->unk0) + source->unk7C;
    arg0->unk348 = (func_80612790((s16) var_v1->unk10) * var_v1->unk0) + source->unk84;
    arg0->unk344 = (f32) ((f64) arg0->unk344 + ((f64) func_80612794((s16) var_v1->unk8) * 0.6));
    var_v1->unk18 = var_v1->unk18 + 1.0f;
    if (44.0f < var_v1->unk18) {
        *arg1 = 1;
    }
    if ((D_8076A064 % arg0->unk35C) == 0) {
        func_807149B8(1);
        func_807149FC(-1);
        func_80714950(0x2A);
        func_8071498C(&func_8071D260);
        func_80714A28(0x20);
        func_80714CC0(*(s32 *) arg0->unk330, arg0->unk360, arg0->unk340, arg0->unk344, arg0->unk348);
    }
}
