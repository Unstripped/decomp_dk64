// func_8061600C (src/global/19A00.c): stage 4: five fdiff attempts (typed pointer baseline; leading s16; void* selection; leading s32; 2-byte padding). Best preserves every instruction except selected pointer spill at sp+0x18 instead of target sp+0x20; frame and scalar read are exact.
typedef struct P19c2Motion {
    u8 pad0[0x1C];
    s16 unk1C;
} P19c2Motion;

typedef struct P19c2State {
    P19c2Motion *unk0;
    P19c2Motion *unk4;
    u8 pad8[0x7C];
    s32 unk84;
} P19c2State;

s32 func_8061600C(Actor *arg0) {
    s16 sp26;
    void *sp20;
    P19c2State *temp_v0;
    P19c2Motion *var_v1;

    temp_v0 = (P19c2State *)arg0->unk4;
    if (temp_v0->unk84 != 0) {
        var_v1 = temp_v0->unk4;
    } else {
        var_v1 = temp_v0->unk0;
    }
    sp20 = var_v1;
    D_807F5AF0++;
    func_80614F4C((u8 *)&sp26);
    ((P19c2Motion *)sp20)->unk1C &= ~sp26;
    return 1;
}
