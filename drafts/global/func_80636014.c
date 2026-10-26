// func_80636014 (src/global/36880.c): stage 6: only diff is idx register: target keeps idx copy in a3 (move a3,a0 before lookup), mine uses v1; tried extra unused 4th param, local idx decl first. Signature (s32,u8,u8).
void func_8062D094(void *, u8);

void func_80636014(s32 arg0, u8 arg1, u8 arg2) {
    s32 idx;

    idx = arg0;
    if (arg1 == 1) {
        idx = hashTableLookup(arg0);
    }
    func_8062D094(D_807F6000[idx].unk20, arg2);
}
