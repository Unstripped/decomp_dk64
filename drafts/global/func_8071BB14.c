// func_8071BB14 (src/global/11BC10.c): stage 3 behavior starter compiled; matrix tail correct, but frame and unsigned conversion lowering differ
typedef struct { f32 angle; f32 speed; } Ua2dBb14State;
void func_8071BB14(Ub2ActorView *arg0, s8 *arg1) {
    f32 sp70[4][4]; f32 sp30[4][4]; f32 angle; f64 speed; u32 random; Ua2dBb14State *state;
    state = arg0->unk384;
    if (state == NULL) { arg0->unk384 = func_80610FE8(8); random = (func_806119A0() % 36000U) / 100U; angle = (f32)random; if ((s32)random < 0) { angle += 4294967296.0f; } ((Ua2dBb14State *)arg0->unk384)->angle = angle; random = func_806119A0() % 10000U; speed = (f64)random; if ((s32)random < 0) { speed += 4294967296.0; } ((Ua2dBb14State *)arg0->unk384)->speed = (f32)(speed / 7000.0); state = arg0->unk384; }
    arg0->unk344 = (f32)((f64)arg0->unk344 + ((f64)state->speed + 1.0)); guScaleF(sp70, arg0->unk360, arg0->unk364, 0.0f); guRotateF(sp30, state->angle, 0.0f, 0.0f, 1.0f); guMtxCatF(sp70, sp30, sp70); guMtxF2L(sp70, (Mtx *)((u8 *)arg0 + (D_807444FC << 6) + 0x128)); arg0->pad0[0x32C] = 2;
}
