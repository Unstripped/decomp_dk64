// func_80615C34 (src/global/19A00.c): stage 4: five fdiff attempts (typed pointer baseline; void* selection; leading s16; trailing s16; leading s32). Best reproduces every instruction except selected pointer spill at sp+0x18 instead of target sp+0x20; frame, actor save, byte handling, and float conversion are exact.
void func_80614644(Actor *, P19bValue *, f32);

s32 func_80615C34(Actor *arg0) {
    u8 sp27;
    P19bValue *sp20;
    P19bState *temp_v0;
    P19bValue *var_a1;

    temp_v0 = (P19bState *)arg0->unk4;
    if (temp_v0->unk84 != 0) {
        var_a1 = temp_v0->unk4;
    } else {
        var_a1 = temp_v0->unk0;
    }
    sp20 = var_a1;
    D_807F5AF0++;
    func_80614F28(&sp27);
    if (sp27 == 0xFF) {
        sp27 = ((P19bState *)arg0->unk4)->unk88;
    }
    func_80614644(arg0, sp20, (f32)sp27);
    return 1;
}
