// func_8071D28C (src/global/11BC10.c): Stage 3: compiled behavioral orbit draft; saved-register/frame set matches but state pointer allocation and late floating operation ordering differ.
typedef struct {
    u8 pad0[0x7C];
    f32 unk7C;
    u8 pad80[4];
    f32 unk84;
    u8 pad88[0x5E];
    s16 unkE6;
} Ub3bPositionSource;

typedef struct {
    f32 unk0;
    f32 unk4;
    f32 unk8;
    f32 unkC;
    f32 unk10;
    f32 unk14;
    f32 unk18;
    f32 unk1C;
} Ub3bOrbitState;

void func_80714950(s32);
void func_807149FC(s32);
void func_80714A28(s32);
void func_8071D260(void);

void func_8071D28C(Ub2ActorView *arg0, s8 *arg1) {
    Ub3bOrbitState *state;
    Ub3bPositionSource *source;
    f32 x;
    f32 z;

    state = arg0->unk384;
    source = arg0->unk338;
    if (state == NULL) {
        state = func_80610FE8(0x20);
        arg0->unk384 = state;
        x = source->unk7C - arg0->unk340;
        z = source->unk84 - arg0->unk348;
        state->unk0 = sqrtf((x * x) + (z * z));
        state->unk4 = (func_806119FC() * 20.0f) + 10.0f;
        state->unk8 = func_806119FC() * 4095.0f;
        state->unkC = (func_806119FC() * 90.0f) + 10.0f;
        state->unk10 = (f32) source->unkE6;
        state->unk14 = func_806119FC() * 30.0f;
        state->unk18 = 0.0f;
        state->unk1C = (f32) (((func_80611A44() >> 0xF) % 255) % 2) * 2.0f - 1.0f;
    }
    state->unk0 = (f32) ((f64) state->unk0 + ((f64) (state->unk4 - state->unk0) * 0.15));
    state->unk14 = (f32) ((f64) state->unk14 + ((f64) (120.0f - state->unk14) * 0.01));
    state->unk8 += state->unkC;
    state->unk10 += state->unk1C * state->unk14;
    arg0->unk340 = func_80612794((s16) state->unk10) * state->unk0 + source->unk7C;
    arg0->unk348 = func_80612790((s16) state->unk10) * state->unk0 + source->unk84;
    arg0->unk344 = (f32) ((f64) arg0->unk344 + ((f64) func_80612794((s16) state->unk8) * 0.6));
    state->unk18 += 1.0f;
    if (state->unk18 > 45.0f) *arg1 = 1;
    if ((D_8076A064 % (u32) arg0->unk35C) == 0) {
        func_807149B8(1);
        func_807149FC(-1);
        func_80714950(0x2A);
        func_8071498C(func_8071D260);
        func_80714A28(0x20);
        func_80714CC0(*(s32 *) arg0->unk330, arg0->unk360, arg0->unk340, arg0->unk344, arg0->unk348);
    }
}
