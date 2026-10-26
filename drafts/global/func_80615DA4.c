// func_80615DA4 (src/global/19A00.c): stage 3: 5+ fdiff attempts: typed m2c, eliminated selected-pointer local, direct selection, declaration reorders, and unprototyped-call probe; best 600-second permuter score 565. Frame remains 0x38 versus target 0x28; call-state/float scheduling differs.
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

s32 func_80615DA4(Actor *arg0) {
    u8 sp27;
    Perm4cMotion *sp20;
    Perm4cState *temp_a1;
    Perm4cMotion *new_var;
    s16 temp_v0;
    f32 temp_fv1;
    f32 temp_fv0;

    temp_a1 = (Perm4cState *)arg0->unk4;
    if (temp_a1->unk84 != 0) {
        sp20 = temp_a1->unk4;
    } else {
        sp20 = temp_a1->unk0;
    }
    D_807F5AF0++;
    func_80614F28(&sp27);
    temp_v0 = sp20->unkC;
    temp_fv1 = sp20->unk4;
    sp20->unk1E = temp_v0;
    temp_fv0 = (f32)temp_v0;
    new_var = sp20;
    new_var->unk1C |= 8;
    sp20->unk20 = sp27;
    if (temp_fv0 < temp_fv1) {
        new_var->unk8 = temp_fv1 - temp_fv0;
    } else {
        sp20->unk8 = -(temp_fv1 - temp_fv0);
    }
    sp20->unkE = sp27;
    temp_a1 = (Perm4cState *)arg0->unk4;
    temp_a1->unk78 |= 0x20;
    return 1;
}
