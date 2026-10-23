// func_80658E8C (src/global/55B20.c): stage 1/2: behaviour reconstructed from asm (func_80626F8C call, player pos via D_807FC924[D_807FC929], sqrtf distance, 90/180/60/120 ramp, rect test vs D_807F7358..5E); frame 0x50 vs 0x48 and local slot order still off; prototyped f32 args required (K&R promotes to double)
typedef struct M55P7Pos {
    /* 0x000 */ u8 pad0[0x21C];
    /* 0x21C */ f32 unk21C;
    /* 0x220 */ f32 unk220;
    /* 0x224 */ f32 unk224;
} M55P7Pos;

void func_80626F8C(f32, f32, f32, f32 *, f32 *, s32, f32, s32);
f32 sqrtf(f32);

s32 func_80658E8C(f32 arg0, f32 arg1, f32 arg2, u8 arg3) {
    s32 x0;
    s32 x1;
    s32 z0;
    s32 z1;
    f32 sp44;
    f32 sp40;
    s16 x;
    s16 z;
    f32 t;
    f32 d;
    M55P7Pos *player;

    func_80626F8C(arg0, arg1, arg2, &sp44, &sp40, 0, 1.0f, D_807FC929);
    x = (s16)sp44;
    z = (s16)sp40;
    player = (M55P7Pos *)&D_807FC924[D_807FC929];
    d = sqrtf((player->unk21C - arg0) * (player->unk21C - arg0) + (player->unk220 - arg1) * (player->unk220 - arg1) + (player->unk224 - arg2) * (player->unk224 - arg2));
    if (d < 90.0f) {
        return 0;
    }
    x0 = 20;
    x1 = 20;
    z0 = 0;
    z1 = 50;
    if (d < 180.0f) {
        t = (d - 60.0f) / 120.0f;
        x0 = 80;
        x1 = 80;
        z0 = 130;
        z1 = 130;
        if (t > 0.0f) {
            x0 = (s16)(-60.0f * t + 80.0f);
            x1 = (s16)(-60.0f * t + 80.0f);
            z0 = (s16)(-130.0f * t + 130.0f);
            z1 = (s16)(-80.0f * t + 130.0f);
        }
    }
    if (x < D_807F7358 - x0 - arg3) {
        return 1;
    }
    if (D_807F735C + x1 + arg3 < x) {
        return 1;
    }
    if (z < D_807F735A - z0 - arg3) {
        return 1;
    }
    if (D_807F735E + z1 + arg3 < z) {
        return 1;
    }
    return 0;
}
