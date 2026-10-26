// func_80614EBC (src/global/19A00.c): stage 4: typed script-state initialization candidate compiled; exact stores recovered, remaining argument/global register allocation
// Stage 2: m2c behavioral starter; remaining diff: state/table types and global pointer materialization.
extern u8 *D_807F5AF0;
extern s32 D_807F5AF4;
extern s32 D_807FBB50;

void func_80614EBC(void *arg0, s16 arg1) {
    s32 temp_t9;
    void *temp_v0;

    temp_v0 = arg0->unk4;
    temp_v0->unk70 = 0;
    temp_v0->unk78 = 0;
    temp_v0->unk7C = 0;
    temp_v0->unk88 = 0;
    temp_v0->unk80 = 0.0f;
    if (arg1 == 0) {
        temp_v0->unk68 = 0;
        D_807F5AF0 = 0;
        D_807F5AF4 = 0;
        return;
    }
    temp_v0->unk64 = arg1;
    temp_t9 = *(D_807FBB50 + (arg1 * 4)) + D_807FBB50;
    temp_v0->unk68 = temp_t9;
    temp_v0->unk6C = temp_t9;
    D_807F5AF0 = temp_t9;
}
