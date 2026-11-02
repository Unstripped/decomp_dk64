// arcadeInsertHighScore (src/arcade/0.c): NOT PARKED (orchestrator, revisit 5): `if (S[arg0] && S[arg0]) {}` reads S[1]/S[2] uninitialised and out of the defined element; find a defined variable-indexed access (or another memory-resident form) first. Stage 5 (frame 0x18, sb 0xC(sp)/lbu 0xC(sp) match), text diff 8: u8 S[3] array local + FAKE variable-indexed dead test keeps S in memory (spill-shaped; plain u8 local/promoted array always coloured v0); loop 2 as do{}while. Remaining: loop-2 value should be a coloured a0 piece (ours ring t4 + ptr a2), ring order sll t2/sll t1 swapped, loop-2 sb/addiu delay slot. Real source shape still unknown (struct/union/array promotion, volatile, address-of all tried).
extern u8 D_8004A794;
void arcadeInsertHighScore(s32 arg0) {
    s32 i;
    s32 j;
    u8 S[3];  // FAKE: array local keeps the initial in memory (target spills it to 0xC(sp), frame 0x18)

    S[0] = D_8004A794;
    for (i = 4; i > arg0; i--) {
        D_8004A74C[i] = D_8004A74C[i - 1];
        for (j = 0; j < 3; j++) {
            D_8004A778[i][j] = D_8004A778[i - 1][j];
        }
    }
    D_8004A74C[arg0] = D_8004A748;
    if (D_8004A778[arg0]) {}  // FAKE: steers loop-2 pointer candidate
    i = 0;
    do {
        if (S[arg0] && S[arg0]) {}  // FAKE: variable-indexed S access keeps S in memory
        D_8004A778[arg0][i] = S[0];
        i++;
    } while (i < 3);
}
