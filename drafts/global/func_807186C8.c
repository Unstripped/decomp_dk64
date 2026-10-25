// func_807186C8 (src/global/11BC10.c): Stage 2: compiled behavioral interpolation draft; target uses direct actor reloads and an unrolled three-element interpolation, while draft caches state in s0.
extern f32 D_807FDB50;
extern f32 D_807FDB54;
extern f32 D_807FDB58;

typedef struct {
    f32 progress;
    f32 startX;
    f32 startY;
    f32 startZ;
    f32 endX;
    f32 endY;
    f32 endZ;
    f32 increment;
    f32 angle;
    f32 angleIncrement;
} Ub3Interpolation;

void func_807186C8(Ub2ActorView *arg0, s8 *arg1) {
    f32 result[3];
    f32 start[3];
    f32 end[3];
    Ub2bMtxF spA0;
    Ub2bMtxF sp60;
    Ub3Interpolation *state;
    s32 i;

    state = arg0->unk384;
    if (state == NULL) {
        state = func_80610FE8(0x28);
        arg0->unk384 = state;
        state->progress = 0.0f;
        state->startX = D_807FDB50;
        state->startY = D_807FDB54;
        state->startZ = D_807FDB58;
        state->endX = arg0->unk340;
        state->endY = arg0->unk344;
        state->endZ = arg0->unk348;
        state->increment = 0.01f;
        state->angle = (f32) ((u32) (func_806119A0() % 36000U) / 100U);
        state->angleIncrement = (f32) ((u32) (func_806119A0() % 400U) / 100U);
    }
    end[0] = state->startX;
    end[1] = state->startY;
    end[2] = state->startZ;
    start[0] = state->endX;
    start[1] = state->endY;
    start[2] = state->endZ;
    for (i = 0; i < 3; i++) {
        result[i] = state->progress * (end[i] - start[i]) + start[i];
    }
    arg0->unk340 = result[0];
    arg0->unk344 = result[1];
    arg0->unk348 = result[2];
    state->progress += state->increment;
    state->increment = (f32) ((f64) state->increment + 0.001);
    arg0->unk360 = (f32) ((f64) arg0->unk360 * 0.975);
    arg0->unk364 = (f32) ((f64) arg0->unk364 * 0.975);
    state->angle += state->angleIncrement;
    guScaleF(spA0, arg0->unk360, arg0->unk364, 0.0f);
    guRotateF(sp60, state->angle, 0.0f, 0.0f, 1.0f);
    guMtxCatF(spA0, sp60, spA0);
    guMtxF2L(spA0, (Mtx *) ((u8 *) arg0 + (D_807444FC << 6) + 0x128));
    ((u8 *) arg0)[0x32C] = 2;
}
