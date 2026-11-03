// arcadeInsertHighScore (src/arcade/0.c): W3Near revisit7 re-derive (no improvement, still full=6): remaining diff = (a) lbu a1,12(sp)/sb a1 vs target a0 (uopt candidate 46 = ilod S[0] interferes with arg0 candidate 7 in the loop-2 preheader bb 11; target gave it a0), (b) as1 order sll t2,a0,2 / sll t1,a0,2 / subu t2 (target: mul-by-3 chain first). as1probe record-permutation of the preheader (4480 topological orders of lw/mul9/sw/move/mul10/la/addu/lbu) bottoms at full=5, so the schedule hunk alone is not reachable by reordering and the C cannot change ring order (t1=arg0*4, t2=arg0*3 are allocated in ucode order). Tried this unit: natural u8 c / s32 c / char c locals (c coloured v0, 43-44), natural D_8004A794 read in loop 2 as extern or function-local static (no entry hoist, no frame: 22-30), early dead reads of D_8004A794 (E hoists to entry and is coloured v0), row-pointer local p = D_8004A778[arg0] before/after the store (+1 move, 11), S decl width/order grid (u16[2], u8[4], u32[1], order i/j/S), dead-test form/position grid x 4 loop-2 forms x 3 statement orders (all plateau at 6), exhaustive LAYOUT join of the 7 tail lines (2^6, all 6), deadsweep sweep --extra over the 4 globals (no improving statement). D_8004A794 is a lone .data byte 0x20 (' ') whose only user is this function (candidate function-local static, needs a .data carve): static + extern forms both reload in the loop-2 preheader instead of the entry hoist the target has, so the S-trick park stays the best. | previous note: // arcadeInsertHighScore (src/arcade/0.c): Leftovers7 Arcade: stage 4 PARKED NON_MATCHING, deadsweep score full=6 (was 7), count exact 57 lines / frame 0x18 / sb 12(sp). NEW LEVER (Leftovers7): size-MISMATCHED access keeps the byte in memory AND makes the loop-2 read an ilod (not a var occurrence): 'u16 S[2]; *(u8 *)S = D_8004A794; ... = *(u8 *)S' plus dead 'if (S[0]) {}' (uopt then forwards neither, loop-2 lbu is hoisted into the preheader like the target; the old u8 S[4]+S[i%1]-in-loop kept the lbu in the loop). do-while with 'i++' last (i = 0; do { joined, LAYOUT) fixed the sb/addiu loop-2 delay-slot order (target: addiu v0; sb 0(v1); bne; addiu v1). Dead S[0]/S[i % 1] outside the loop give the 3 never-coded spill slots (frame 0x18, S at 12). Remaining 6 lines: (1) hoisted lbu gets a1 not a0 (the ilod candidate's def is in the preheader block where arg0/a0 is still live (block-level interference); the target's a0 means its piece has NO unit in the preheader: a variable piece with needreglod in the loop block, split() cannot run in a leaf unless constrained: unsolved), (2) lbu/move v0,zero order in the preheader, (3) as1 emits sll t1 before sll t2/subu (target sll t2; sll t1; lui at; subu). Tried: 20k hill-climb steps over dead tests/joins/decl order/S type (u16[2]/u32[1]/s32[1]), p=D_8004A778[arg0] pointer var, block-split dead ifs, static local, volatile, S[arg0 % 1] (hoists but materialises addiu a0,sp,12).
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
