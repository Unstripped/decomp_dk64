// func_8071D5BC (src/global/11BC10.c): Stage 3: compiled matrix/drop behavior; target frame is 0xC0 with s0/s1 while draft matrix/local lifetime differs.
typedef struct {
    u8 pad0[0x7C];
    f32 unk7C;
    f32 unk80;
    f32 unk84;
    u8 pad88[0xD6];
    u8 unk15E;
} Ub3bPlayerView;

void func_8071D5BC(TimedEffectActorView *arg0, s8 *arg1) {
    f32 sp80[4][4];
    f32 sp40[4][4];
    Ub3bPlayerView *player;
    f32 scale;
    f32 x;
    f32 z;
    s32 radius;

    player = (Ub3bPlayerView *) D_807FBB4C;
    scale = arg0->unk360;
    radius = (s32) (scale * 20.0f);
    if ((player->unk80 <= arg0->unk344) && (arg0->unk344 < player->unk80 + (f32) player->unk15E)) {
        x = player->unk7C - arg0->unk340;
        z = player->unk84 - arg0->unk348;
        if ((x * x) + (z * z) < (f32) (radius * radius)) {
            playerStateQueueCallback(0x2E, 0, 0);
            scale = arg0->unk360;
        }
    }
    guScaleF(sp80, scale, arg0->unk364, 0.0f);
    guRotateF(sp40, 90.0f, 1.0f, 0.0f, 0.0f);
    guMtxCatF(sp80, sp40, sp80);
    guTranslateF(sp40, arg0->unk340, arg0->unk344, arg0->unk348);
    guMtxCatF(sp80, sp40, sp80);
    if ((s32) arg0->unk36D >= 9) {
        arg0->unk36D -= 9;
    } else {
        *arg1 = 1;
    }
    arg0->unk360 = (f32) ((f64) arg0->unk360 * 1.08);
    arg0->unk364 = arg0->unk360;
    guMtxF2L(sp80, (Mtx *) ((u8 *) arg0 + (D_807444FC << 6) + 0x128));
    ((u8 *) arg0)[0x32C] = 3;
}
