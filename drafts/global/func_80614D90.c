// func_80614D90 (src/global/19A00.c): stage 4; permuter best score 360; remaining diff: saved-register allocation and loop scheduling. Attempts: m2c baseline, direct typed state/callback rewrite, result/state declaration order, guard scheduling, permuter run.
typedef s32 (*Perm4gD90Command)(Actor *);
typedef struct Perm4gD90State {
    u8 pad0[0x68];
    u8 *unk68;
    u8 *unk6C;
    void (*unk70)(Actor *);
    u8 *unk74;
    s32 unk78;
} Perm4gD90State;

extern Perm4gD90Command D_80746BEC[];

void func_80614D90(Actor *arg0) {
    int zero;
    s32 result;
    Perm4gD90State *state;

    state = (Perm4gD90State *)arg0->unk4;
    zero = 0;
    if (state->unk68) {
        D_807F5AF4 = 1;
        D_807F5AF0 = state->unk6C;
        if (state->unk78 == (0 & 0xFFFFFFFFFFFFFFFF)) {
            do {
                result = D_80746BEC[*D_807F5AF0](arg0);
                D_807F5AF4 = result;
            } while ((state->unk78 == zero) && (result != 0));
perm4g_d90_schedule:
            ;
        }
        state->unk6C = D_807F5AF0;
        if (state->unk70 != 0) {
            D_807F5AF0 = state->unk74;
            state->unk70(arg0);
        }
    }
}
