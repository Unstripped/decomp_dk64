// func_8071C9E8 (src/global/11BC10.c): stage 6 text-complete modulo upstream sizes/rodata: two-level state reads (field test, post-if read, post-height-block read giving a1/s0 web split with move), u8 sp5B choice home sharing the sp16 slot at +3 (decl order state,sp5B,sp58,sp4C), s16* sp4C table-pointer local, store order (field-store before rand; x,z,target_y,rotation), func_805FF030-style 2-arg calls correct; works with the same char randomNonNegative decl as CDE0
typedef struct {
    s16 angle;
    s16 y;
    s16 speed;
    s16 x;
    s16 z;
    s16 target_y;
    s16 rotation;
} Fx11BFC9State;

extern s16 D_80755650[];
s16 func_806CC190(s16, s16, f32);
s16 mathAngleBetweenPoints2D(f32, f32, f32, f32);
extern s32 D_8071FB08;

void func_8071C9E8(TimedEffectActorView *arg0, s8 *arg1) {
    f32 spA0[4][4];
    f32 sp60[4][4];
    Fx11BFC9State *state;
    u8 sp5B;
    s16 sp58;
    s16 *sp4C;

    if (arg0->unk384 == NULL) {
        sp5B = (randomNonNegative() >> 0xF) % 1000 % 6;
        arg0->unk384 = func_80610FE8(0xE);
        state = arg0->unk384;
        state->speed = ((randomNonNegative() >> 0xF) % 5) + 10;
        sp4C = &D_80755650[sp5B * 3];
        state->x = sp4C[0];
        state->z = sp4C[1];
        state->target_y = sp4C[2];
        state->rotation = 0;
        state->y = (s16)arg0->unk344;
    }
    state = arg0->unk384;
    if (*(f32 *)((u8 *)D_807FBB4C + 0x84) < 340.0f) {
        state->x = 0x12C;
        state->z = 0x96;
        state->target_y = 0x64;
    }
    sp58 = mathAngleBetweenPoints2D((f32)state->x, (f32)state->target_y, arg0->unk340, arg0->unk348);
    state->angle = func_806CC190(state->angle, sp58, (f32)(((randomNonNegative() >> 0xF) % 10) + 5));
    state->y = (s16)((f64)(state->z - state->y) * 0.1 + (f64)state->y);
    arg0->unk340 += state->speed * func_80612794(state->angle);
    arg0->unk348 += state->speed * func_80612790(state->angle);
    arg0->unk344 = (f32)((((f64)func_80612794((state->speed + 0x32) * D_8076A064)) * 40.0) + (state->y + 0x28));
    if (((randomNonNegative() >> 0xF) % 1000) >= 991) {
        sp5B = ((randomNonNegative() >> 0xF) % 1000) % 6;
        state->x = D_80755650[sp5B * 3];
        state->z = D_80755650[(sp5B * 3) + 1];
        state->target_y = D_80755650[(sp5B * 3) + 2];
    }
    lightSetFlags(1);
    lightAdd(arg0->unk340, arg0->unk344, arg0->unk348, 0.0f, 0.0f, 0.0f, 150.0f, 0, 0x96, 0x96, 0xFF);
    if (!(D_8076A064 & 3)) {
        func_807149B8(1);
        func_8071498C(func_8071C818);
        func_80714CC0((s32)&D_8071FB08, 1.6f, arg0->unk340, arg0->unk344, arg0->unk348);
    }
    state->rotation += state->speed;
    guScaleF(spA0, arg0->unk360, arg0->unk364, 0.0f);
    guRotateF(sp60, (f32)state->rotation, 0.0f, 0.0f, 1.0f);
    guMtxCatF(spA0, sp60, spA0);
    guMtxF2L(spA0, (Mtx *)((u8 *)arg0 + (D_807444FC << 6) + 0x128));
    arg0->pad0[0x32C] = 2;
}
