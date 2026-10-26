// func_80615A3C (src/global/19A00.c): stage 4: integer ABI candidate; remaining func_80613C48 declaration conflicts with matched func_8061594C float ABI.
void func_80613C48(s32, s16, s32, s32);

s32 func_80615A3C(s32 arg0) {
    s16 sp1E;
    s32 sp18;

    D_807F5AF0++;
    func_80614F4C((u8 *)&sp1E);
    func_80614FD8(&sp18);
    func_80613C48(arg0, sp1E, 0, sp18);
    return 1;
}
