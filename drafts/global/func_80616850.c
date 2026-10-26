// func_80616850 (src/global/19A00.c): stage 4; permuter best score 21; remaining diff: one cursor/state register allocation. Attempts: m2c baseline, reordered cursor increment, state-first scheduling, typed local state, permuter run.
s32 func_80616850(Actor *arg0) {
    s32 sp24;
    P19dState *state;
    u16 sp22;
    P19dState *initialState;

    initialState = (P19dState *)arg0->unk4;
    sp24 = initialState->unk88;
    D_807F5AF0++;
    state = initialState;
    func_80614F4C((u8 *)&sp22);
    initialState = (P19dState *)arg0->unk4;
    state->unk5C = state->unk64;
    state->unk60 = D_807F5AF0 - state->unk68;
    func_80614EBC(arg0, sp22);
    D_807F5AF0 = state->unk6C;
    state->unk88 = sp24;
    return D_807F5AF4;
}
