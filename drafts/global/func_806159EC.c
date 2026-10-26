// func_806159EC (src/global/19A00.c): stage 4: typed and K&R calls emit move a2/a3, target requires li; remaining ABI/immediate selection.
void func_80613CA8(s32, s16, s32, s32);

s32 func_806159EC(s32 arg0) {
    s16 sp1E;

    D_807F5AF0++;
    func_80614F4C((u8 *)&sp1E);
    func_80613CA8(arg0, sp1E, 0, 0);
    return 1;
}
