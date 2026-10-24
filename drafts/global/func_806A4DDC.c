// func_806A4DDC (src/global/A8400.c): stage 6: instruction stream matches 1:1 except regalloc order and stack frame (built 0x88 vs expected 0x110). Expected has an unexplained 0xAB-byte unused local between the f32 call-spill slot (0x50) and the u8 stop byte (0x103); every natural local ordering tried (u8 pad 0x88/0xAC/0x100 declared first/last) reproduces frame 0x110 but moves the spill/stop slots. state (s1/s2) and node registers swapped; loop-tail 'move v0,a1' artifact not reproduced.
typedef struct A8R2bNode A8R2bNode;

typedef struct A8R2bState {
    /* 0x00 */ u8 pad0[0x4];
    /* 0x04 */ void *unk4;
    /* 0x08 */ u8 pad8[0x4];
    /* 0x0C */ A8R2bNode *unkC;
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
} A8R2bState;

struct A8R2bNode {
    /* 0x00 */ u8 pad0[0x18];
    /* 0x18 */ f32 unk18;
    /* 0x1C */ A8R2bNode *unk1C;
};

typedef struct A8R2bBounds {
    /* 0x000 */ u8 pad0[0x270];
    /* 0x270 */ s16 unk270;
    /* 0x272 */ s16 unk272;
    /* 0x274 */ s16 unk274;
    /* 0x276 */ s16 unk276;
} A8R2bBounds;

extern A8R2bBounds *D_807FC924;

void func_806A4B84(f32, Actor *, A8R2bState *, A8R2bNode *, u8, u8 *);
void func_8070D9AC(A8R2bNode *);
void func_8070E808(Actor *, void *);

void func_806A4DDC(Actor *arg0) {
    A8R2bState *state;
    A8R2bNode *node;
    A8R2bNode *cur;
    f32 acc;
    f32 dt;
    f32 sum;
    f32 lim;
    f64 wide;
    f64 high;
    u8 stop;
    u8 mode;
    s32 i;

    state = arg0->unk174;
    node = state->unkC;
    stop = 0;
    dt = state->unk20;
    lim = (f32) ((f64) (1.0f - dt) * 1.47058823529411775);
    if (lim > 1.0f) {
        lim = 1.0f;
    }
    state->unk40 = lim;
    func_806A3DA0(&arg0->unk7C, &arg0->unk80, dt, lim, (M7Angle *) state);
    wide = (f64) (state->unk20 * 136.8f) * 0.5;
    state->unk44 = arg0->unk7C - wide;
    high = (f64) (state->unk20 * 79.799995f) * 0.5;
    state->unk48 = arg0->unk80 - high;
    state->unk4C = arg0->unk7C + wide;
    state->unk50 = arg0->unk80 + high;
    lim = (f32) D_807FC924->unk270;
    if (lim < state->unk44) {
        state->unk44 = state->unk44;
    } else {
        state->unk44 = lim;
    }
    sum = (f32) D_807FC924->unk272;
    if (sum < state->unk48) {
        state->unk48 = state->unk48;
    } else {
        state->unk48 = sum;
    }
    dt = (f32) D_807FC924->unk274;
    if (state->unk4C < dt) {
        state->unk4C = state->unk4C;
    } else {
        state->unk4C = dt;
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
        dt = cur->unk18;
        sum = acc + dt;
        if (((f64) sum > 73.79999542236328) && (arg0->unk154 == 1)) {
            arg0->unk154 = 2;
            state->unk18 = (f32) ((f64) sum - 73.79999542236328);
            stop = 1;
        } else if ((sum < 0.0f) && (arg0->unk154 == 2)) {
            state->unk14 = state->unk14 + dt;
            state->unk10 = state->unk10 - 1;
            state->unkC = cur->unk1C;
            acc = sum;
            node = cur->unk1C;
            func_8070D9AC(cur);
            i--;
        } else {
            func_806A4B84(acc, arg0, state, cur, (u8) (i == state->unk10), &stop);
            if (stop == 0) {
                node = node->unk1C;
                acc = sum;
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
        }
    }
    if ((mode == 1) && (node == NULL)) {
        func_8070E808(arg0, state->unk4);
    }
}
