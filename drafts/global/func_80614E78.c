// func_80614E78 (src/global/19A00.c): stage 4: typed table-dispatch candidate compiled; frame/control flow recovered, remaining argument/global materialization
// Stage 2: m2c behavioral starter; remaining diff: script-table type and pointer expression.
void func_80614EBC(void *arg0, s16 arg1);
extern s32 D_807FBB54;

void func_80614E78(void *arg0, s32 arg1) {
    func_80614EBC(*(D_807FBB54 + ((((arg1 * 7) + arg0->unk58) - 2) * 2)));
}
