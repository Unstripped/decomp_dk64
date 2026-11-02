// arcadeInsertHighScore (src/arcade/0.c): Leftovers6 Arcade: stage 4 PARKED NON_MATCHING (count exact 45 insns / frame 0x18 / same blocks, nm sizes equal 0xb4). deadsweep score full=7 (text 7). Lever: u8 S[4] memory-resident via variable-indexed dead test 'if (S[i % 1]) {}' in loop 2 with the real read S[0] (no lda copy). Remaining: target loop 2 hoists 'lbu a0,0xC(sp)' before the loop as a plain spilled-scalar piece (v1=A778 ptr), ours 'lbu t4,12(sp)' in the loop + sb/addiu order + sll t2/t1/subu ring order. Analysis: target c is a plain u8 local whose WHOLE live range is uncoloured (adjsave<=0: compute_save penalties) with a reload piece in a0; plain c always gets colour 1 (unconstrained, adjsave 3.67). Tried: plain c with 13.5k random structural spellings (type/decl order/redefs/loop forms/dead tests), copy local d=c (copy-propagated), no-code defs, 24-48 dead consts (c constrained but still coloured), grid S index forms.
extern u8 D_8004A794;
void arcadeInsertHighScore(s32 arg0) {
    s32 i;
    s32 j;
    u8 S[4];  // FAKE: array local with a variable-indexed access keeps the initial byte in memory (target spills it to 0xC(sp), frame 0x18)

    S[0] = D_8004A794;
    for (i = 4; i > arg0; i--) {
        D_8004A74C[i] = D_8004A74C[i - 1];
        for (j = 0; j < 3; j++) {
            D_8004A778[i][j] = D_8004A778[i - 1][j];
        }
    }
    D_8004A74C[arg0] = D_8004A748;
    for (i = 0; i < 3; i++) {
        if (S[i % 1]) {}  // FAKE: variable-indexed S access (always element 0) keeps S in memory
        D_8004A778[arg0][i] = S[0];
    }
}
