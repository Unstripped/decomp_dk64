// hudPauseMenuSlidePage (src/global/ACDC0.c): stage 6 (parked NON_MATCHING): 10 text-diff lines, regalloc only: target base ptr (s0+idx*2) v0 / d v1, mine base v1 / d v0 (uopt colours d first: adjsave 3.5 vs base 1.33; base has v0 forbidden). Breakthrough: no idx2 local at all, read arg0->unk15 directly (d = arg0->unkC[arg0->unk15]; arg0->unk8[1 - arg0->unk15] = arg0->unk8[arg0->unk15]) gives the move t0,t4 + negu/addu structure; tail '(&D_807FC7F9)[-arg0->unk15] = 0; arg1 = 0;' (no re-read local d). Tried: d types/decl order perms, clamp spellings, deadsweep w/ globals+field exprs, pointer locals, permuter 420s: no gain.
extern s8 D_807FC7F9;

s32 hudPauseMenuSlidePage(HudEntry *arg0, s32 arg1, s32 arg2) {
    s32 dir;
    s32 idx;
    s32 v;
    s32 d;

    if (arg1 == 0) {
        dir = 0;
        if (arg2 & 8) {
            dir = 1;
        } else if (arg2 & 4) {
            dir = -1;
        }
        if (dir != 0) {
            idx = arg0->unk15;
            v = arg0->unk8[idx] + dir;
            if (dir) {
            }
            if (v < 0) {
                v = D_807505D0;
            }
            if (D_807505D0 < v) {
                v = 0;
            }
            if (v != arg0->unk8[idx]) {
                arg0->unk15 = 1 - idx;
                arg0->unk8[arg0->unk15] = v;
                arg0->unkC[arg0->unk15] = dir * 0xFA;
                hudPauseMenuBuildPage(arg0, 0, idx);
                sfxPlayOnFreeSlot(0x2C9, 0x7FFF, 63.0f, 1.0f, 0, 0);
            }
        }
    }
    if (arg1 != 0) {
        d = arg0->unkC[arg0->unk15];
        if (d >= 0x15) {
            d = 0x14;
        }
        if (d < -0x14) {
            d = -0x14;
        }
        arg0->unkC[0] -= d;
        arg0->unkC[1] -= d;
        if (arg0->unkC[arg0->unk15] == 0) {
            arg0->unk8[1 - arg0->unk15] = arg0->unk8[arg0->unk15];
            (&D_807FC7F9)[-arg0->unk15] = 0;
            arg1 = 0;
            sfxPlayOnFreeSlot(0x97, 0x4650, 63.0f, 1.0f, 0, 0);
            D_8075052C = 3;
        }
    }
    return arg1;
}
