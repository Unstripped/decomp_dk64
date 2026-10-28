// func_80024A50 (src/arcade/0.c): stage 3 (frame 0 vs 0x18). Target: CSE'd D_8004A794 lbu hoisted to ENTRY, sb 0xC(sp) in beqz delay slot, lbu a0,0xC(sp) before the fill loop (web split, entry..loop2 uncoloured). Swept (ArcNM1b/d): ~500 variants of local type/position/read form/dead uses/address-taken/struct locals, exhaustive dead-statement insertion, and dummy webs live across loops 1-2 (2..10 extra locals): all colour the web in a register or move things to s-regs; never the spill. Not pressure-induced. Untried: restructure so D_8004A794 is read in a branch-likely position / K&R with u8 param shape.
extern u8 D_8004A794;
void func_80024A50(s32 arg0) {
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
