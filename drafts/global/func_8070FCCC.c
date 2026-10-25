// func_8070FCCC (src/global/114270.c): stage 1: verified player/bound selection, angle update, and threshold body; the effect-spawn tail from 0x8070FE98 remains to reconstruct
typedef struct R114c4FcccActorView {
    u8 unk0[0x90];
    f32 unk90;
    u8 unk94[0x66];
    u8 unkFA;
} R114c4FcccActorView;
typedef struct R114c4FcccContextView {
    u8 unk0[0x174];
    R114c4FcccActorView *unk174;
} R114c4FcccContextView;
typedef struct R114c4FcccBoundView {
    u8 unk0[0xA8];
    f32 unkA8;
    f32 unkAC;
} R114c4FcccBoundView;
typedef struct R114c4FcccPlayerView {
    u8 unk0[0x214];
    f32 unk214;
} R114c4FcccPlayerView;
extern R114c4FcccContextView *D_807F5D10;
extern R114c4FcccBoundView *D_807FBB4C;

void func_8070FA58(M114aAngle *);

s32 func_8070FCCC(M114aAngle *arg0) {
    R114c4FcccPlayerView *player = (R114c4FcccPlayerView *)D_807FC924;
    f32 bound;
    s32 result;
    f32 delta;
    f32 increment;

    if ((D_807F5D10->unk174->unkFA != 0) && (player->unk214 < (D_807F5D10->unk174->unk90 + 3.0f))) {
        bound = D_807FBB4C->unkAC;
    } else {
        delta = D_807FBB4C->unkA8 - player->unk214;
        if (delta < 0.0f) {
            delta = -delta;
        }
        increment = D_807FBB4C->unkAC - player->unk214;
        if (increment < 0.0f) {
            increment = -increment;
        }
        bound = (delta < increment) ? D_807FBB4C->unkA8 : D_807FBB4C->unkAC;
    }
    func_8070FA58(arg0);
    func_8070FC40(arg0);
    result = arg0->unkB0 < 0x10;
    arg0->unkB0++;
    arg0->unk8 = arg0->unk4;
    if (!result && (arg0->unkB1 >= 0x50)) {
        arg0->unkB1 -= 0x50;
    }
    increment = (f32)((1.0 / ((f64)arg0->unk10 * 4.0)) * 60.0);
    arg0->unkC += (f32)((f64)((30.0f - (increment - 30.0f)) + 30.0f) * 0.25);
    return ((arg0->unkB1 >= 0x50) && (bound != 0.0f));
}
