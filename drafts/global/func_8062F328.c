// func_8062F328 (src/global/2F550.c): stage 5: same shape; target copies arg0 to a2, uses a0 as the byte offset (strength-reduced), v1 counter, a3/t0 for the D_807F5FD0/FD4 address regs; ours picks a2/a3 for the globals and v0 for the offset. for and do-while forms give the same regs.
extern s32 D_807F5FD0;
extern s32 *D_807F5FD4;

void func_8062F328(s32 arg0) {
    s32 i;

    if (D_807F5FD0 != 0) {
        i = 0;
        if (D_807F5FD0 >= 0) {
            do {
                D_807F5FD4[i] += arg0;
                i++;
            } while (D_807F5FD0 >= i);
        }
    }
}
