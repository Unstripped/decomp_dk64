// arcadeInsertHighScore (src/arcade/0.c): arcadeInsertHighScore (src/arcade/0.c): stage 3 (frame 0 vs 0x18). Target spills D_8004A794 to 0xC(sp) across loop 1 (lbu hoisted to entry, sb in beqz slot, lbu before fill loop). Tried K&R u8/narrow parameter shapes, stack layout/local arrays, branch-likely loops, and initial web splitting; uopt allocates all 7 caller-saved regs in loop 1 but colours web into register or s0 rather than spilling.
extern u8 D_8004A794;
void arcadeInsertHighScore(s32 arg0) {
    u8 initial;
    s32 i;
    s32 j;

    for (i = 4; i > arg0; i--) {
        D_8004A74C[i] = D_8004A74C[i - 1];
        for (j = 0; j < 3; j++) {
            D_8004A778[i][j] = D_8004A778[i - 1][j];
        }
    }
    D_8004A74C[arg0] = D_8004A748;
    for (i = 0; i < 3; i++) {
        D_8004A778[arg0][i] = D_8004A794;
    }
}
