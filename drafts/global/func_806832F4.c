// func_806832F4 (src/global/80150.c): Stage 5: frame 0x30 ok; diff 7 lines at return: expected sltu t3/beqz t3/move v0,t3/lw v0/sltiu t4/move v0,t4, ours v1+beqzl and extra move; tried ret var, && forms, ternary, break/return, decl order perms (120), default ret var, if(sp28)
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
