// func_80712FC8 (src/global/117190.c): Menu dispatch behavior recovered; signed comparison/compiler shape remains off
void func_80712FC8(void) {
    s32 arg0;
    s32 arg1;

    if ((D_80755334 >= 0x5A) && (D_807ECD48 & 0x1000)) {
        func_80712EDC();
    } else if (D_8075531C == 0) {
        if (D_8075532C >= 3) {
            func_807124B8(0x28, 0, 1);
        } else {
            func_8060B750(D_8075E5C0[D_80755328 * 4]);
            func_8060B7D0(&arg0, &arg1);
            func_805FF158(1);
            func_805FF378(arg0, arg1);
        }
    }
}
