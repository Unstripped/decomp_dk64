// func_8060E25C (src/global/104F0.c): stage 4: frame/control flow match; remaining register allocation (selector starts in v0 rather than t6, temporary register shifts) and missing arg0 home spill; tried exact m2c expression and direct local rewrite
extern s32 func_8060B9D0(u8);
extern s32 func_807142D8(void);
extern void func_80731030(void);
extern u8 D_807ECEA8[];
extern u8 D_807EDEB0[];
extern u8 D_807FC928;

u8 *func_8060E25C(s32 arg0) {
    u8 *result;
    s32 selector;

    selector = arg0 & 0xFF;
    result = NULL;
    switch (selector) {
    case 0:
        if ((func_807142D8() != 0) || (D_807FC928 >= 2)) {
            func_80731030();
            bzero(D_807EDEB0, ((((D_807ECEA0[0] + 0x6B7) & ~0x3F) + 0x27) & ~7) / 8);
            result = D_807EDEB0;
        } else {
            result = D_807ECEA8 + (func_8060B9D0(D_807467C8) * (((((D_807ECEA0[0] + 0x6B7) & ~0x3F) + 0x27) & ~7) / 8));
        }
        break;
    case 1:
        result = ((s32) (((((((D_807ECEA0[0] + 0x6B7) & ~0x3F) + 0x27) & ~7) * 4) + 0x3F) & ~0x3F) / 8) + D_807ECEA8;
        break;
    }
    return result;
}
