// func_8060C758 (src/global/104F0.c): stage 3: size/bank expression matches; remaining frame, argument-home, and temporary register allocation.
extern u8 D_807ECEA8[];

void func_8060C758(s32 arg0, s32 arg1) {
    s32 temp_s0;

    temp_s0 = arg0 & 0xFF;
    D_807467C8 = temp_s0;
    bzero(D_807ECEA8 + func_8060B9D0(temp_s0) * ((s32)((((D_807ECEA0[0] + 0x6B7) & ~0x3F) + 0x27) & ~7) / 8),
          (s32)((((D_807ECEA0[0] + 0x6B7) & ~0x3F) + 0x27) & ~7) / 8);
    func_8060C648(0xC, 0, 0, temp_s0 & 0xFF, 1);
    func_8060C648(0xF, 0, 0, temp_s0 & 0xFF, temp_s0);
    if (arg1 != 0) {
        func_8060B8F8(1);
    }
}
