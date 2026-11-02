// arcadeInsertHighScore (src/arcade/0.c): arcadeInsertHighScore (src/arcade/0.c): stage 5, PARKED NON_MATCHING in W4Frame copy; text diff 4 (was 8). Frame 0x18, sb t6,0xC(sp) in the beqz delay slot, loop-1 regs, ring order (sll t2/t1, subu) all match. Lever: 'u8 S[1]; S[0] = D_8004A794; ... = S[i % 1];' (defined variable-indexed access, always element 0, no uninitialised read) keeps the byte memory-resident. Remaining 4 lines: loop 2 target hoists 'lbu a0,0xC(sp)' before the loop (coloured a0 piece of a plain spilled scalar: v1 = A778 ptr, move v0,zero after it) while ours takes 'addiu a0,sp,0xC' + 'lbu t4,0(a0)' in the loop (array = address-based). Real shape is a plain u8 local whose first piece loses colouring over loop 1 (needs one more invisible candidate live over loop 1; extra locals k = arg0/gl748/etc. defined before loop 1 tried: no). 4 grids tried: S[n] n=1..16 x index forms (i%1, i&0, i*0, arg0%1, arg0/5 ...) x value/test forms x loop forms (for / do-while) x decl order; local copy v = S[idx] before loop 2: worse (15+).
extern u8 D_8004A794;
void arcadeInsertHighScore(s32 arg0) {
    s32 i;
    s32 j;
    u8 S[1];

    S[0] = D_8004A794;
    for (i = 4; i > arg0; i--) {
        D_8004A74C[i] = D_8004A74C[i - 1];
        for (j = 0; j < 3; j++) {
            D_8004A778[i][j] = D_8004A778[i - 1][j];
        }
    }
    D_8004A74C[arg0] = D_8004A748;
    for (i = 0; i < 3; i++) {
        D_8004A778[arg0][i] = S[i % 1];  // FAKE: variable-indexed access (always element 0) keeps S in memory: target spills the byte to 0xC(sp), frame 0x18
    }
}
