// func_806F70A8 (src/global/F9450.c): Stage 4: do-loop removes duplicate zero return and matches control shape; argument/pointer allocation remains.
extern u8 D_807FD798;
extern s16 D_807FD790;

s32 func_806F70A8(s16 arg0) {
    s16 *var_a1;
    s32 var_v0;

    var_v0 = 0;
    if ((s32) D_807FD798 > 0) {
        var_a1 = &D_807FD790;
        do {
            var_v0 += 1;
            if (arg0 == *var_a1) {
                return 1;
            }
            var_a1 += 1;
        } while (var_v0 < (s32) D_807FD798);
    }
    return 0;
}
