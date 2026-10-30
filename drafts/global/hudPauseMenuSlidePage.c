// hudPauseMenuSlidePage (src/global/ACDC0.c): hudPauseMenuSlidePage (src/global/ACDC0.c): stage 6, 1 text diff cluster. First half + clamp/loop identical in structure; remaining only second half (arg1 != 0): target 'lb t0; sll t4,t0,1; addu v0,s0,t4; lh v1,0xc(v0); move t0,t4; negu t2,t0; ...; addu t3,s0,t2 (in bnez delay slot)' vs mine 'negu+addu right after lh, delay slot filled with lui a2' (2 insns shorter total). A local 'off = idx2*2' used for the loads gives the 'move t0,t4' copy but then uopt folds the unk8[1-idx2] store into 'subu s0-off' instead of negu+addu; every spelling of the store tried (index 1-idx2, (&unk8[1])[-idx2], u8* arith, +-off, pointer temp, early q=&unk8[1-idx2]) keeps negu/addu OR the move, never both; decl-order/type perms (s8/s32/u32 idx2,d s16) no change; rs.py 12000 iters x2 seeds no gain (26 diff lines baseline). 2-reloc diff vs D_807FC7F9 ok.
typedef struct ACDC0HudEntry {
    /* 0x00 */ u8 pad0[8];
    /* 0x08 */ s16 unk8[2];
    /* 0x0C */ s16 unkC[2];
    /* 0x10 */ u8 pad10[2];
    /* 0x12 */ s8 unk12;
    /* 0x13 */ u8 pad13;
    /* 0x14 */ s8 unk14;
    /* 0x15 */ s8 unk15;
} ACDC0HudEntry;

extern s8 D_8075052C;
extern s8 D_807505D0;
void hudPauseMenuBuildPage(ACDC0HudEntry *, s32, s32);
void sfxPlayOnFreeSlot(s32, s32, f32, f32, s32, s32);

extern s8 D_807FC7F9;

s32 hudPauseMenuSlidePage(ACDC0HudEntry *arg0, s32 arg1, s32 arg2) {
    s32 dir;
    u32 idx;
    s32 v;
    s32 d;
    u32 idx2;

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
            if (D_8075052C == 0) {}  // FAKE: deadsweep dead statement (steers uopt; replace with natural C)
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
        idx2 = arg0->unk15;
        d = arg0->unkC[idx2];
        if (idx2 && idx2) {}  // FAKE: deadsweep dead statement (steers uopt; replace with natural C)
        if (d >= 0x15) {
            d = 0x14;
        }
        if (d < -0x14) {
            d = -0x14;
        }
        arg0->unkC[0] -= d;
        arg0->unkC[1] -= d;
        if (arg0->unkC[idx2] == 0) {
            arg0->unk8[1 - idx2] = arg0->unk8[idx2];
            d = arg0->unk15;
            arg1 = 0;
            (&D_807FC7F9)[-d] = 0;
            sfxPlayOnFreeSlot(0x97, 0x4650, 63.0f, 1.0f, 0, 0);
            D_8075052C = 3;
        }
    }
    return arg1;
}
