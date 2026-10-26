// func_80615ADC (src/global/19A00.c): stage 5: exact text, own-data relocation mismatch; retained GLOBAL_ASM.
void func_80614014(s32, u16, f32, u8);

s32 func_80615ADC(s32 arg0) {
    u16 sp1E;
    u8 sp1D;

    D_807F5AF0++;
    func_80614F4C((u8 *)&sp1E);
    func_80614F28(&sp1D);
    func_80614014(arg0, sp1E, 0.0f, sp1D);
    return 1;
}
