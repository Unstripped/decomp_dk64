// func_80616BA4 (src/global/19A00.c): stage 6: one lbu/store temporary allocation remains after matching control flow
? func_80614F28(u8 *);                              /* extern */
extern s32 D_807F5AF0;

s32 func_80616BA4(void *arg0) {
    u8 sp1F;

    D_807F5AF0 += 1;
    func_80614F28(&sp1F);
    arg0->unk155 = 0;
    arg0->unk154 = sp1F;
    return 1;
}
