// func_80616BA4 (src/global/19A00.c): stage 6: correct instructions and order; actor/value allocation is a0/v1 rather than target v1/t8
s32 func_80616BA4(Actor *arg0) {
    u8 sp1F;
    u8 temp;

    D_807F5AF0++;
    func_80614F28(&sp1F);
    temp = sp1F;
    arg0->unk155[0] = 0;
    arg0->unk154 = temp;
    return 1;
}
