// func_8069A750 (src/global/9DD70.c): stage 2: 22/30 insns; skeleton+fused epilogue identical. Missing: li v1,2 / li a2,3 hoisted to the preheader and the two no-op tests beq v0,2/beq v0,3 -> loop condition (both with nop delay slots). Empirically the tests survive ONLY when the continue target block is separated from the if by another block: a redundant 'if (i>=count) break;' before the while test keeps them (p18), and an inner for(;;){if(c) break;} gives the exact target skeleton incl. sltu-before-load + beq/nop (h3) but with the second test inverted (bne back to the first test). Every form without such a block (empty if, if/else, continue, goto label, switch with empty/default cases, do-while-with-increment-at-top) drops both branches. Target also keeps the array base at &D_807FBB70 with a 0x7C displacement (lw t8,0x7C(a0)) whereas a local Actor **list = base+0x7C gives lw 0(a0).
extern Actor *D_807FBB40;
extern ActorGlobalState D_807FBB70;
extern u8 D_807FBBA9;

s32 func_8069A750(void) {
    Actor **list = (Actor **)((u8 *)&D_807FBB70 + 0x7C);
    s32 i;

    for (i = 0; i < D_807FBBA9; i++) {
        if (list[i]->unk58 != 2 && list[i]->unk58 != 3) {
            continue;
        }
    }
    if (D_807FBB40->unk58 == 0x1F) {
        return 0;
    }
    return 0;
}
