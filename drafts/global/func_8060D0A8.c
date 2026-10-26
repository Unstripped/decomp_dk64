// func_8060D0A8 (src/global/104F0.c): stage 4: exact text/frame/callee-save set; only sp28 stack slot is 0x2C instead of target 0x28
extern void func_8060C758(s32, s32);
extern u8 D_807467C8;
extern u8 D_807ECEA8;
extern s8 D_807EDEA8;
extern void func_8060CB74(void);

void func_8060D0A8(void) {
    s32 sp28;
    s8 *var_v0;
    s32 var_s0;

    var_v0 = &D_807EDEA8;
    var_s0 = 0;
    sp28 = (s32) D_807467C8;
    do {
        *var_v0 = var_s0;
        var_s0 += 1;
        var_v0 += 1;
    } while (var_s0 < 4);
    bzero(&D_807ECEA8, 0x800);
    func_8060CB74();
    var_s0 = 0;
    do {
        func_8060C758(var_s0 & 0xFF, var_s0 == 3);
        var_s0 += 1;
    } while (var_s0 != 4);
    D_807467C8 = (u8) sp28;
}
