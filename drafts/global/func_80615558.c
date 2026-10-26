// func_80615558 (src/global/19A00.c): stage 4: behavioural m2c draft; stack frame and state view remain different
typedef struct P19bDraftState { u8 pad0[0x10]; f32 unk10; u8 pad14[0x2C]; f32 unk40; f32 unk44; u8 pad48[0x30]; s32 unk78; } P19bDraftState;
s32 func_80615558(Actor *arg0) {
    f32 sp1C;
    P19bDraftState *state = (P19bDraftState *)arg0->unk4;
    D_807F5AF0++;
    func_80614FD8((u8 *)&sp1C);
    if (*(s32 *)((u8 *)state + 8) != 0) {
        if (sp1C < state->unk44) {
            state->unk44 = sp1C;
            state->unk40 = state->unk44 - (state->unk10 * state->unk44);
        }
        state->unk78 |= 0x10;
    }
    return 0;
}
