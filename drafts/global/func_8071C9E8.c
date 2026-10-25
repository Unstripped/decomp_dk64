// func_8071C9E8 (src/global/11BC10.c): stage 4 behavioral draft compiled; target frame/saved registers match in the initial version, but state-pointer lifetime and local stack offsets differ; matrix tail matches structurally
typedef struct {
    s16 angle;
    s16 y;
    s16 speed;
    s16 x;
    s16 z;
    s16 target_y;
    s16 rotation;
} M3C9State;
typedef struct { u8 pad0[0x84]; f32 y; } M3C9Actor;
extern s16 D_80755650[];
extern s32 D_8071FB08;
s16 func_806CC190(s16, s16, f32);
s16 mathAngleBetweenPoints2D(f32, f32, f32, f32);
void func_8071C9E8(Ub2ActorView *arg0, s8 *arg1) {
    f32 spA0[4][4]; f32 sp60[4][4]; M3C9State *state; s32 random; u8 choice;
    state = arg0->unk384;
    if (state == NULL) { choice = (func_80611A44() >> 0xF) % 1000 % 6; arg0->unk384 = func_80610FE8(0xE); state = arg0->unk384; state->speed = (func_80611A44() >> 0xF) % 5 + 10; state->x = D_80755650[choice * 3]; state->z = D_80755650[choice * 3 + 1]; state->target_y = D_80755650[choice * 3 + 2]; state->rotation = 0; state->y = (s16)arg0->unk344; }
    if (((M3C9Actor *)D_807FBB4C)->y < 340.0f) { state->x = 300; state->z = 150; state->target_y = 100; }
    state->angle = func_806CC190(state->angle, mathAngleBetweenPoints2D((f32)state->x, (f32)state->target_y, arg0->unk340, arg0->unk348), (f32)((func_80611A44() >> 0xF) % 10 + 5));
    state->y = (s16)((f64)(state->z - state->y) * 0.1 + state->y); arg0->unk340 += state->speed * func_80612794(state->angle); arg0->unk348 += state->speed * func_80612790(state->angle); arg0->unk344 = (f32)((f64)func_80612794((state->speed + 0x32) * D_8076A064) * 40.0 + (state->y + 0x28));
    random = (func_80611A44() >> 0xF) % 1000; if (random >= 991) { choice = (func_80611A44() >> 0xF) % 1000 % 6; state->x = D_80755650[choice * 3]; state->z = D_80755650[choice * 3 + 1]; state->target_y = D_80755650[choice * 3 + 2]; }
    lightSetFlags(1); lightAdd(arg0->unk340, arg0->unk344, arg0->unk348, 0.0f, 0.0f, 0.0f, 150.0f, 0, 0x96, 0x96, 0xFF); if (!(D_8076A064 & 3)) { func_807149B8(1); func_8071498C(func_8071C818); func_80714CC0((s32)&D_8071FB08, 1.6f, arg0->unk340, arg0->unk344, arg0->unk348); }
    state->rotation += state->speed; guScaleF(spA0, arg0->unk360, arg0->unk364, 0.0f); guRotateF(sp60, (f32)state->rotation, 0.0f, 0.0f, 1.0f); guMtxCatF(spA0, sp60, spA0); guMtxF2L(spA0, (Mtx *)((u8 *)arg0 + (D_807444FC << 6) + 0x128)); arg0->pad0[0x32C] = 2;
}
