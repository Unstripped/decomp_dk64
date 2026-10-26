// func_80613448 (src/global/17B90.c): stage 1: m2c starter; attempted signed entry index but lhu/sign handling and loop form differ
extern ? D_807FB630;
extern u16 D_807FBB30;

u16 func_80613448(s32 *arg0) {
    u16 var_v1;
    void *var_a0;

    var_v1 = D_807FBB30;
    if ((s32) var_v1 >= 0) {
        var_a0 = (var_v1 * 0xC) + &D_807FB630;
loop_2:
        if (*arg0 != var_a0->unk4) {
            var_v1 -= 1;
            var_a0 -= 0xC;
            if ((s32) var_v1 >= 0) {
                goto loop_2;
            }
        }
    }
    if ((s32) var_v1 >= 0) {
        return *(&D_807FB630 + (var_v1 * 0xC));
    }
    return 0U;
}
