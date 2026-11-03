// arcadeInsertHighScore (src/arcade/0.c): stage 6, text-identical but REJECTED: dead tests read u16 S[0]/S[i%1] whose byte 1 is never written (uninitialised dead read); needs a fully initialised form (Arcade, revisit 8)
extern u8 D_8004A794;
void arcadeInsertHighScore(s32 arg0) {
    s32 i;
    s32 j;
    u16 S[2];  // FAKE: u16 array read/written through (u8 *) casts: mismatched access sizes keep the byte in memory (sb 12(sp) at entry); the variable-indexed dead reads make the loop-2 read a hoistable ilod

    *(u8 *)S = D_8004A794;
    for (i = 4; i > arg0; i--) {
        D_8004A74C[i] = D_8004A74C[i - 1];
        for (j = 0; j < 3; j++) {
            D_8004A778[i][j] = D_8004A778[i - 1][j];
        }
    }
    D_8004A74C[arg0] = D_8004A748;
    if (S[0]) {}  // FAKE: dead S access (residency / spill-slot candidate for frame 0x18); S is address-taken memory, value unused
    if (S[i % 1] == 0) {}  // FAKE: dead variable-indexed S access (memory residency)
    if (D_8004A778[arg0] && D_8004A778[arg0]) {}  // FAKE: row address becomes a CSE candidate computed here, so arg0 no longer appears in the loop-2 preheader bb and the hoisted lbu can take a0
    if (S[i % 1]) {}  // FAKE: second variable-indexed dead S read (candidate order for the colouring)
    i = 0; do {  // LAYOUT: init joined on the do line
        D_8004A778[arg0][i] = *(u8 *)S;
        i++;
    } while (i < 3);
}
