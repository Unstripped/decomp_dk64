// func_80024A50 (src/arcade/0.c): stage 3 (frame 0 vs 0x18). Target = CSE'd D_8004A794 lbu hoisted to ENTRY, sb 0xC(sp) in beqz delay, lbu a0,0xC(sp) before fill loop: i.e. web split, region A (entry..loop2) uncoloured, region B coloured a0. ArcNM1b harness (480 variants: local type u8/s8/s16/u16/u32/s32/char x assign position x read form x dead use, exhaustive dead-statement insertion over globals+locals, address-taken local, struct/array local, 'if(D_8004A794 && D_8004A794){}' which hoists the load to entry but keeps it in v0) all colour the web in a register (no frame) or give an 8-byte frame when v is read uninitialised. uopt -l 5: web has adjsave 3.7 and only conflicts with 11 webs; needs a reason for the colourer to fail (>=12 interfering webs) -- not found. Untried: extra dummy webs live across loop 1/2.
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
