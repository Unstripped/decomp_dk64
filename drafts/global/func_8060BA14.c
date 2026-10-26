// func_8060BA14 (src/global/104F0.c): stage 3: full bank-copy and XOR-swap flow compiled; remaining diff is branch-live register allocation, memcpy argument register order, and swap pointer register allocation.
extern s32 func_8060B9D0(u8);
extern s32 func_8071432C(void);
extern s32 func_80714394(void);
extern u8 D_807ECEA8[];
extern u8 D_807EDEA8[];

void func_8060BA14(void) {
    u8 original;
    u8 replacement;
    s32 size;
    u8 temp;

    original = func_8060B9D0(D_807467C8);
    replacement = func_8060B9D0(3);
    if (((func_8071432C() != 0) || (func_80714394() != 0)) && (replacement != original)) {
        size = ((((D_807ECEA0[0] + 0x6B7) & ~0x3F) + 0x27) & ~7) / 8;
        memcpy(D_807ECEA8 + (size * replacement), D_807ECEA8 + (size * original), size);
        temp = D_807EDEA8[replacement] ^ D_807EDEA8[original];
        D_807EDEA8[replacement] = temp;
        D_807EDEA8[original] ^= temp;
        D_807EDEA8[replacement] ^= D_807EDEA8[original];
    }
}
