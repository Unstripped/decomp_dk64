// func_80024A50 (src/arcade/0.c): stage 3 (frame 0 vs 0x18). All code/regs match except the spill: target lbu D_8004A794 at entry, sb 0xC(sp) in beqz delay slot, lbu a0,0xC(sp) before fill loop. Also tried (round 2): s32 temp read before the first loop, temp assigned twice, temp assigned in the arg0<4 guarded branch + after, K&R with s32 narrowed to u8, u8 from s32 temp - all colour the temp in a reg (no spill). Final fill loop must use i (v0), not j.
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
