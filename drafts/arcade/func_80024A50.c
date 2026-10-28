// func_80024A50 (src/arcade/0.c): stage 3 (frame 0 vs 0x18). Shift loops, final fill loop (counter is i, reuses the outer counter reg v0) and all register assignments match. Only missing: target loads D_8004A794 at entry, stores it to 0xC(sp) in the beqz delay slot and reloads it (lbu a0,0xC(sp)) before the final fill loop (uncoloured uopt candidate). Named u8 local, volatile, arrays, struct, address-taken, K&R, decl-order variants all colour the byte in a reg or reload per iteration.
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
