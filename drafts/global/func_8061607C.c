// func_8061607C (src/global/19A00.c): stage 4: 5+ fdiff attempts: state-local selection, inline ternary, pointer/value declaration reorders, duplicated value expression, and selected-pointer spill local; best permuter score 16. Only selected-motion pointer spill is sp+0x24 versus target sp+0x1C (frame and all instructions otherwise match).
typedef struct Perm4cMotion {
    void *unk0;
    f32 unk4;
    f32 unk8;
    s16 unkC;
    s16 unkE;
    u8 pad10[0xC];
    s16 unk1C;
    s16 unk1E;
    s16 unk20;
    u8 pad22[2];
    f32 unk24;
    f32 unk28;
    f32 unk2C;
    f32 unk30;
    f32 unk34;
} Perm4cMotion;

typedef struct Perm4cState {
    Perm4cMotion *unk0;
    Perm4cMotion *unk4;
    u8 pad8[0x70];
    s32 unk78;
    u8 pad7C[8];
    s32 unk84;
} Perm4cState;

s32 func_8061607C(Actor *arg0) {
    f32 sp20;
    Perm4cMotion *sp1C;
    f32 var_fv0;

    sp1C = ((Perm4cState *)arg0->unk4)->unk84 != 0
        ? ((Perm4cState *)arg0->unk4)->unk4
        : ((Perm4cState *)arg0->unk4)->unk0;
    D_807F5AF0++;
    func_80614FD8((u8 *)&sp20);
    if (sp1C->unk0 != NULL) {
        var_fv0 = *(f32 *)sp1C->unk0;
    } else {
        var_fv0 = .0f;
    }
    if (sp20 > 0.0f) {
        sp1C->unk34 = sp20;
        sp1C->unk2C = var_fv0;
        sp1C->unk30 = 0.0f;
        sp1C->unk28 = sp1C->unk24;
    } else {
        sp1C->unk24 = var_fv0;
        sp1C->unk34 = 0.0f;
    }
    return 1;
}
