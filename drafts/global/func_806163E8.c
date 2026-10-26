// func_806163E8 (src/global/19A00.c): stage 4: five fdiff attempts (typed pointer baseline; added s32 local; added s16 local; swapped pointer/float declaration order; void* selection). Best preserves all operations and target frame but selected pointer spills at sp+0x18 rather than target sp+0x20.
s32 func_806163E8(Actor *arg0) {
    f32 sp24;
    void *sp20;
    P19bState *temp_v0;
    P19bValue *var_v1;

    temp_v0 = (P19bState *)arg0->unk4;
    if (temp_v0->unk84 != 0) {
        var_v1 = temp_v0->unk4;
    } else {
        var_v1 = temp_v0->unk0;
    }
    sp20 = var_v1;
    D_807F5AF0++;
    func_80614FD8((u8 *)&sp24);
    ((P19bState *)arg0->unk4)->unk88 = ((P19bValue *)sp20)->unk4 - sp24;
    return 1;
}
