// func_806832F4 (src/global/80150.c): Stage 5 (LgFB6b): frame 0x30 ok; 3-insn diff at the return (target: sltu t3/beqz t3/move v0,t3/lw v0,24/sltiu t4/move v0,t4 = && temp coloured v0 with the compare in the ring; ours: compare expr is its own uopt candidate (cand 27 'sp28 != 0') coloured v1 + beqzl + move v0,v1). uopt_trace: temp 564 forbidden v0 because it interferes with that candidate. Tried (all unchanged 325 or worse): ternary, !!, (u8)/(u32) forms, ret locals u8/u16/s16/s32/u32 with 4 shapes, if-returns, break/return outside switch, if((sp28=f())) assign forms, u32/s32 local types, 0 != x operand order, (u32)x>0 compares, deadsweep (--extra sp28 sp24 arg1 D_8076A0A8 D_807FBB40: only a dead if (sp24==0) {} that changes shape, not the target).
s32 func_805FEF10(void *);

s32 func_806832F4(s32 arg0, s32 arg1) {
    s32 pad;
    s32 sp28;
    s32 sp24 = 0;
    struct {
        char unk0[2];
        s16 unk2;
    } sp20;

    switch (D_8076A0A8) {
    default:
        return 0;
    case 7:
    case 26:
    case 30:
    case 38:
    case 42:
    case 48:
        sp28 = func_805FEF10(&sp20);
        if (sp28 != 0) {
            sp24 = flagGet(sp20.unk2, 0);
            if (arg1 != 0 && sp24 == 0) {
                flagSet(sp20.unk2, 1, 0);
                camStartPath(D_807FBB4C, 0x19, 4);
                D_807FBB40->unk144 = 1;
                D_807FBB40->unk155[0] = 0xB;
            }
        }
        return (sp28 != 0) && (sp24 == 0);
    }
}
