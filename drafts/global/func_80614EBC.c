// func_80614EBC (src/global/19A00.c): stage 4; best permuter score 20; remaining five GPR allocations (global base a0 vs v1, result v1 vs t9)
typedef struct Perm2ScriptState {
    u8 pad0[0x64];
    s16 unk64;
    u8 pad66[2];
    u8 *unk68;
    u8 *unk6C;
    s32 unk70;
    u8 pad74[4];
    s32 unk78;
    s32 unk7C;
    f32 unk80;
    u8 pad84[4];
    s32 unk88;
} Perm2ScriptState;

extern u8 *D_807F5AF0;
extern u8 *D_807FBB50;
extern s32 D_807F5AF4;

void func_80614EBC(Actor *arg0, s32 arg1) {
    Perm2ScriptState *new_var;
    Perm2ScriptState *temp_v0;
    u8 *temp_t9;

    temp_v0 = (Perm2ScriptState *)arg0->unk4;
    temp_v0->unk70 = 0;
    new_var = temp_v0;
    new_var->unk78 = 0;
    temp_v0->unk7C = 0;
    new_var->unk88 = 0;
    temp_v0->unk80 = 0.0f;
    if (arg1 == 0) {
        new_var->unk68 = NULL;
        D_807F5AF0 = NULL;
        D_807F5AF4 = 0;
        return;
    }
    new_var->unk64 = arg1;
    temp_t9 = D_807FBB50 + ((s32 *)D_807FBB50)[arg1];
    new_var->unk68 = temp_t9;
    temp_v0->unk6C = temp_t9;
    D_807F5AF0 = temp_t9;
}
