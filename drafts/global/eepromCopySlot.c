// eepromCopySlot (src/global/104F0.c): stage 5: frame 0x20 exact, callee-saved exact; regalloc diff (v1/a3 swap in memcpy args multu)
extern s32 func_8071432C(void);
extern s32 func_80714394(void);
extern u8 D_807ECEA8[];

void eepromCopySlot(void) {
    u8 original;
    u8 replacement;
    s32 size;
    s16 unk0;

    original = func_8060B9D0(D_807467C8);
    replacement = func_8060B9D0(3);
    if (((func_8071432C() != 0) || (func_80714394() != 0)) && (replacement != original)) {
        unk0 = D_807ECEA0[0];
        size = ((((unk0 + 0x6B7) & ~0x3F) + 0x27) & ~7) / 8;
        memcpy(D_807ECEA8 + (size * replacement), D_807ECEA8 + (size * original), size);
        D_807EDEA8[replacement] ^= D_807EDEA8[original];
        D_807EDEA8[original] ^= D_807EDEA8[replacement];
        D_807EDEA8[replacement] ^= D_807EDEA8[original];
    }
}
