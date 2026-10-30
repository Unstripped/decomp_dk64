// func_806A4DDC (src/global/A8400.c): stage 6, text diff 27 (243 vs 244 insns): frame 0x110 + stop@0x103 reproduced (u8 stop after 3 pointer locals + u8 pad[0x88]); no `sum` local (acc+dt CSE temp in f2, spilled across func_806A4B84 like the original) but its spill slot lands at 0x48 not 0x50; first-half roles lim/sum matched; FAKE: 3 deadsweep dead uses (cur/acc). remaining: expected keeps unk10 in a1 with `move v0,a1` copy (mine v0 directly), `cur` copy (move a0,s1) at loop top, last two FP temps f14 vs f2, delay slot lbu v0,340(s3) fill
#include "common.h"
#include "actor.h"

typedef struct ChainNode ChainNode;

typedef struct ChainState {
    /* 0x00 */ u8 pad0[0x4];
    /* 0x04 */ void *unk4;
    /* 0x08 */ u8 pad8[0x4];
    /* 0x0C */ ChainNode *unkC;
    /* 0x10 */ u8 unk10;
    /* 0x11 */ u8 pad11;
    /* 0x12 */ u8 unk12;
    /* 0x13 */ u8 pad13;
    /* 0x14 */ f32 unk14;
    /* 0x18 */ f32 unk18;
    /* 0x1C */ u8 pad1C[0x4];
    /* 0x20 */ f32 unk20;
    /* 0x24 */ u8 pad24[0x1C];
    /* 0x40 */ f32 unk40;
    /* 0x44 */ f32 unk44;
    /* 0x48 */ f32 unk48;
    /* 0x4C */ f32 unk4C;
    /* 0x50 */ f32 unk50;
} ChainState;

struct ChainNode {
    /* 0x00 */ u8 pad0[0x18];
    /* 0x18 */ f32 unk18;
    /* 0x1C */ ChainNode *unk1C;
};

void func_8070D9AC(ChainNode *);
void func_8070E808(Actor *, void *);

void func_806A4DDC(Actor *arg0) {
    ChainState *state;
    ChainNode *node;
    ChainNode *cur;
    u8 stop;
    u8 pad[0x88];
    f64 wide;
    f64 high;
    f32 acc;
    f32 dt;
    u32 nv;
    f32 lim;
    u8 mode;
    u8 last;
    s32 i;
    f32 sum;

    state = arg0->unk174;
    node = state->unkC;
    stop = 0;
    lim = (f32) ((f64) (1.0f - state->unk20) * 1.47058823529411775);
    if (lim > 1.0f) {
        lim = 1.0f;
    }
    state->unk40 = lim;
    mathAddWaveOffset(&arg0->unk7C, &arg0->unk80, state->unk20, lim, (MotionAngles *) state);
    wide = (f64) (state->unk20 * 136.8f) * 0.5;
    state->unk44 = arg0->unk7C - wide;
    high = (f64) (state->unk20 * 79.799995f) * 0.5;
    state->unk48 = arg0->unk80 - high;
    state->unk4C = arg0->unk7C + wide;
    state->unk50 = arg0->unk80 + high;
    sum = (f32) D_807FC924->unk270;
    if (sum < state->unk44) {
        state->unk44 = state->unk44;
    } else {
        if (dt && dt) {}  // FAKE: deadsweep dead statement (steers uopt; replace with natural C)
        state->unk44 = sum;
    }
    lim = (f32) D_807FC924->unk272;
    if (lim < state->unk48) {
        state->unk48 = state->unk48;
    } else {
        state->unk48 = lim;
    }
    sum = (f32) D_807FC924->unk274;
    if (state->unk4C < sum) {
        state->unk4C = state->unk4C;
    } else {
        state->unk4C = sum;
    }
    sum = (f32) D_807FC924->unk276;
    if (state->unk50 < sum) {
        state->unk50 = state->unk50;
    } else {
        state->unk50 = sum;
    }
    acc = state->unk14;
    i = 0;
    while (((s32) state->unk10 >= i) && (node != NULL) && (stop == 0)) {
        cur = node;
        last = (i == state->unk10);
        dt = cur->unk18;
        if (((f64) (acc + dt) > 73.79999542236328) && (arg0->unk154 == 1)) {
            arg0->unk154 = 2;
            state->unk18 = (f32) ((f64) (acc + dt) - 73.79999542236328);
            stop = 1;
        } else if (((acc + dt) < 0.0f) && (arg0->unk154 == 2)) {
            state->unk14 = state->unk14 + dt;
            nv = state->unk10;
            state->unk10 = nv - 1;
            state->unkC = cur->unk1C;
            acc = acc + dt;
            if (cur && cur) {}  // FAKE: deadsweep dead statement (steers uopt; replace with natural C)
            node = cur->unk1C;
            func_8070D9AC(cur);
            i--;
        } else {
            func_806A4B84(acc, (ActorStateView *) arg0, (SpriteChainState *) state, (SpriteHolder *) cur, last, &stop);
            if (stop == 0) {
                node = node->unk1C;
                acc = acc + dt;
            }
        }
        i++;
    }
    mode = arg0->unk154;
    if (mode == 3) {
        if (state->unk12 != 0) {
            state->unk12 = state->unk12 - 1;
            mode = arg0->unk154;
        } else {
            mode = arg0->unk154 = 1;
            if (acc && acc) {}  // FAKE: deadsweep dead statement (steers uopt; replace with natural C)
        }
    }
    if ((mode == 1) && (node == NULL)) {
        func_8070E808(arg0, state->unk4);
    }
}
