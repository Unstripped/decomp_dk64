// func_806ABC94 (src/global/ACDC0.c): stage 5-6: regalloc only: dir/v/d/ptr use v0/v1/a3 swapped vs expected (expected dir=v1, v=v0, d=v1, ptr=v0); (arg0->unk8+(-idx))[1] gives subu where expected has move/negu/addu. Permuter 2x300s best 375->305 not clean. Parked NON_MATCHING
typedef struct M1HudEntry {
    /* 0x00 */ u8 pad0[8];
    /* 0x08 */ s16 unk8[2];
    /* 0x0C */ s16 unkC[2];
    /* 0x10 */ u8 pad10[2];
    /* 0x12 */ s8 unk12;
    /* 0x13 */ u8 pad13;
    /* 0x14 */ s8 unk14;
    /* 0x15 */ s8 unk15;
} M1HudEntry;

extern s8 D_807FC7F8[2];

extern s8 D_8075052C;
extern s8 D_807505D0;
void func_806AA304(M1HudEntry *, s32, s32);
void func_80609140(s32, s32, f32, f32, s32, s32);

s32 func_806ABC94(M1HudEntry *arg0, s32 arg1, s32 arg2) {
    s32 dir;
    s32 idx;
    s32 v;
    s32 cur;
    s32 d;
    s32 idx2;

    if (arg1 == 0) {
        dir = 0;
        if (arg2 & 8) {
            dir = 1;
        } else if (arg2 & 4) {
            dir = -1;
        }
        if (dir != 0) {
            idx = arg0->unk15;
            cur = arg0->unk8[idx];
            v = cur + dir;
            if (v < 0) {
                v = D_807505D0;
            }
            if (D_807505D0 < v) {
                v = 0;
            }
            if (v != cur) {
                arg0->unk15 = 1 - idx;
                arg0->unk8[arg0->unk15] = v;
                arg0->unkC[arg0->unk15] = dir * 0xFA;
                func_806AA304(arg0, 0, idx);
                func_80609140(0x2C9, 0x7FFF, 63.0f, 1.0f, 0, 0);
            }
        }
    }
    if (arg1 != 0) {
        idx2 = arg0->unk15;
        d = arg0->unkC[idx2];
        if (d >= 0x15) {
            d = 0x14;
        }
        if (d < -0x14) {
            d = -0x14;
        }
        arg0->unkC[0] -= d;
        arg0->unkC[1] -= d;
        if (arg0->unkC[idx2] == 0) {
            (arg0->unk8 + (-idx2))[1] = arg0->unk8[idx2];
            d = arg0->unk15;
            arg1 = 0;
            D_807FC7F8[1 - d] = 0;
            func_80609140(0x97, 0x4650, 63.0f, 1.0f, 0, 0);
            D_8075052C = 3;
        }
    }
    return arg1;
}
