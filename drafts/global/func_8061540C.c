// func_8061540C (src/global/19A00.c): stage 2: m2c behavioural draft; state view/register allocation not yet matched
typedef struct P19bValue { void *unk0; f32 unk4; u8 pad8[0x1C]; f32 unk24; } P19bValue;
typedef struct P19bState { P19bValue *unk0; P19bValue *unk4; s32 *unk8; u8 padC[4]; f32 unk10; u8 pad14[0x10]; f32 unk24; s16 unk28; s16 unk2A; s16 unk2C; u8 pad2E[0x4A]; f32 unk78; f32 unk80; s32 unk84; s32 unk88; } P19bState;
s32 func_8061540C(Actor *arg0) {
    f32 sp24;
    P19bValue *sp20;
    P19bState *state;
    state = (P19bState *)arg0->unk4;
    if (state->unk84 != 0) { sp20 = state->unk4; } else { sp20 = state->unk0; }
    D_807F5AF0++;
    func_80614FD8((u8 *)&sp24);
    if (sp24 < 0.0f) { sp24 = (f32) state->unk88; }
    if ((state->unk48 * sp20->unk24) > 0.0f) { if (sp24 <= sp20->unk4) { return 1; } } else if (sp20->unk4 <= sp24) { return 1; }
    state->unk80 = sp24;
    state->unk78 |= 8;
    return 0;
}
