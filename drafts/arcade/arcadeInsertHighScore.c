// arcadeInsertHighScore (src/arcade/0.c): Leftovers7 Arcade: stage 4 PARKED NON_MATCHING, deadsweep score full=6 (was 7), count exact 57 lines / frame 0x18 / sb 12(sp). NEW LEVER (Leftovers7): size-MISMATCHED access keeps the byte in memory AND makes the loop-2 read an ilod (not a var occurrence): 'u16 S[2]; *(u8 *)S = D_8004A794; ... = *(u8 *)S' plus dead 'if (S[0]) {}' (uopt then forwards neither, loop-2 lbu is hoisted into the preheader like the target; the old u8 S[4]+S[i%1]-in-loop kept the lbu in the loop). do-while with 'i++' last (i = 0; do { joined, LAYOUT) fixed the sb/addiu loop-2 delay-slot order (target: addiu v0; sb 0(v1); bne; addiu v1). Dead S[0]/S[i % 1] outside the loop give the 3 never-coded spill slots (frame 0x18, S at 12). Remaining 6 lines: (1) hoisted lbu gets a1 not a0 (the ilod candidate's def is in the preheader block where arg0/a0 is still live (block-level interference); the target's a0 means its piece has NO unit in the preheader: a variable piece with needreglod in the loop block, split() cannot run in a leaf unless constrained: unsolved), (2) lbu/move v0,zero order in the preheader, (3) as1 emits sll t1 before sll t2/subu (target sll t2; sll t1; lui at; subu). Tried: 20k hill-climb steps over dead tests/joins/decl order/S type (u16[2]/u32[1]/s32[1]), p=D_8004A778[arg0] pointer var, block-split dead ifs, static local, volatile, S[arg0 % 1] (hoists but materialises addiu a0,sp,12).
extern u8 D_8004A794;
void arcadeInsertHighScore(s32 arg0) {
    s32 i;
    s32 j;
    u16 S[2];  // FAKE: u16 array read/written through (u8 *) casts: mismatched access sizes keep the byte in memory (sb 12(sp) at entry) and make the loop-2 read a hoistable ilod (lbu in the preheader)

    *(u8 *)S = D_8004A794;
    for (i = 4; i > arg0; i--) {
        D_8004A74C[i] = D_8004A74C[i - 1];
        for (j = 0; j < 3; j++) {
            D_8004A778[i][j] = D_8004A778[i - 1][j];
        }
    }
    D_8004A74C[arg0] = D_8004A748;
    if (S[0]) {}  // FAKE: dead S access (spill-slot candidates for the target frame 0x18)
    if (S[i % 1] == 0) {}  // FAKE: dead variable-indexed S access (spill-slot candidates for the target frame 0x18)
    i = 0; do {  // LAYOUT: init joined on the do line
        D_8004A778[arg0][i] = *(u8 *)S;
        i++;
    } while (i < 3);
}
