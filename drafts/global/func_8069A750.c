// func_8069A750 (src/global/9DD70.c): stage 2: nested for(;;) skeleton matches all but second test inversion (bne vs beq to latch); empty/continue/switch forms delete both tests
// for(;;){ if (x==2||x==3) break; } inside a for loop: reproduces sltu-before-load,
// preheader li 2/3, hoisted actor load and the fused epilogue; only the second
// test is inverted (bne back to the first test) and operands are const-first.
// Empty if / continue / switch / while forms make IDO delete both tests entirely.
extern Actor *D_807FBB40;
extern ActorGlobalState D_807FBB70;
extern u8 D_807FBBA9;

s32 func_8069A750(void) {
    Actor **list = (Actor **)((u8 *)&D_807FBB70 + 0x7C);
    s32 i;

    for (i = 0; i < D_807FBBA9; i++) {
        for (;;) {
            if (list[i]->unk58 == 2 || list[i]->unk58 == 3) {
                break;
            }
        }
    }
    if (D_807FBB40->unk58 == 0x1F) {
        return 0;
    }
    return 0;
}
