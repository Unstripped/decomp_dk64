// func_8070FCCC (src/global/114270.c): stage 1: actor/player bound selection and angle update compiled; effect-spawn tail remains
typedef struct R114bFcccActorView {
    u8 unk0[0x90];
    f32 unk90;
    u8 unk94[0x65];
    u8 unkFA;
} R114bFcccActorView;
typedef struct R114bFcccContextView {
    u8 unk0[0x174];
    R114bFcccActorView *unk174;
} R114bFcccContextView;
typedef struct R114bFcccBoundView {
    u8 unk0[0xA8];
    f32 unkA8;
    f32 unkAC;
} R114bFcccBoundView;
typedef struct R114bFcccPlayerView {
    u8 unk0[0x214];
    f32 unk214;
} R114bFcccPlayerView;
extern R114bFcccContextView *D_807F5D10;
extern R114bFcccBoundView *D_807FBB4C;

s32 func_8070FCCC(M114aAngle *arg0) {
    R114bFcccPlayerView *player = (R114bFcccPlayerView *)D_807FC924;
    f32 bound;
    s32 result;
    f32 delta;
    f32 increment;

    if ((D_807F5D10->unk174->unkFA != 0) && (player->unk214 < (D_807F5D10->unk174->unk90 + 3.0f))) {
        bound = D_807FBB4C->unkAC;
    } else {
        delta = D_807FBB4C->unkA8 - player->unk214;
        if (delta < 0.0f) delta = -delta;
        increment = D_807FBB4C->unkAC - player->unk214;
        if (increment < 0.0f) increment = -increment;
        bound = (delta < increment) ? D_807FBB4C->unkA8 : D_807FBB4C->unkAC;
    }
    func_8070FA58(arg0);
    func_8070FC40(arg0);
    result = arg0->unkB0 < 0x10;
    arg0->unkB0++;
    arg0->unk8 = arg0->unk4;
    if (!result && (arg0->unkB1 >= 0x50)) arg0->unkB1 -= 0x50;
    increment = (f32)((1.0 / ((f64)arg0->unk10 * 4.0)) * 60.0);
    arg0->unkC += (f32)((f64)((30.0f - (increment - 30.0f)) + 30.0f) * 0.25);
    return ((arg0->unkB1 >= 0x50) && (bound != 0.0f));
}
