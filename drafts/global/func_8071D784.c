// func_8071D784 (src/global/11BC10.c): Stage 3: compiled velocity/matrix behavior; target frame is 0xD0 and preserves fs0, while draft local/matrix allocation differs.
typedef struct {
    f32 unk0;
    f32 unk4;
    f32 unk8;
} Ub3bVelocityState;

typedef struct {
    u8 pad0[0x7C];
    f32 unk7C;
    f32 unk80;
} Ub3bPlayerHeight;

extern f32 D_80755674;
extern f32 D_80755678;

void func_8071D784(Ub2ActorView *arg0, s8 *arg1) {
    f32 sp90[4][4];
    f32 sp50[4][4];
    f32 sp48;
    f32 sp44;
    f32 sp40;
    Ub3bVelocityState *state;

    state = arg0->unk384;
    if (state == NULL) {
        state = func_80610FE8(0xC);
        arg0->unk384 = state;
        guRotateF(sp90, -(f32) ((u32) (func_806119A0() % 36000U) / 1000U), 1.0f, 0.0f, 0.0f);
        guRotateF(sp50, (f32) ((arg0->unk35C * 0x168) / 4096), 0.0f, 1.0f, 0.0f);
        guMtxCatF(sp90, sp50, sp90);
        guMtxXFMF(sp90, 0.0f, 0.0f, D_80755678, &sp48, &sp44, &sp40);
        state->unk0 = sp48;
        state->unk4 = sp44;
        state->unk8 = sp40;
    }
    arg0->unk340 += state->unk0;
    arg0->unk344 += state->unk4;
    state->unk4 += D_80755674;
    arg0->unk348 += state->unk8;
    if (arg0->unk344 <= ((Ub3bPlayerHeight *) D_807FBB4C)->unk80) {
        *arg1 = 1;
    }
}
