// func_806F70A8 (src/global/F9450.c): Stage 3 close table-search draft; target loop, loads, comparison, and returns match. Current mismatch is argument/pointer register allocation and duplicated zero return.
extern u8 D_807FD798;
extern s16 D_807FD790;

s32 func_806F70A8(s16 arg0) {
    u8 *var_a1;
    s32 var_v0;

    var_v0 = 0;
    if ((s32) D_807FD798 > 0) {
        var_a1 = (u8 *) &D_807FD790;
loop_2:
        var_v0 += 1;
        if (arg0 == *(s16 *) var_a1) {
            return 1;
        }
        var_a1 += 2;
        if (var_v0 >= (s32) D_807FD798) {
            return 0;
        }
        goto loop_2;
    }
    return 0;
}
