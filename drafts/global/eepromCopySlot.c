// eepromCopySlot (src/global/104F0.c): W3IntB 2026-11-02: stage 5, score 6 (was 9), count 78 exact, LEGAL (no uninitialised read). Found by a random pair search over legal dead statements: 'if (replacement == 0) {}' in place of 'if (src) {}' + no-code 'unk0 = unk0 | 0;' after dst (alt: keep 'if (src) {}' + 'size = size | 0;' + 'if (replacement == 0) {}', also 6). Left 6 lines: original a1 (target a3) and unk0 a0 (target v0); replacement v1 now exact. Third-level pairs on both 6-states (25k each, ~30%) none < 6. Targets: unk0 must colour v0 (share with the div chain) and original a3 (a0-a2 taken by src/dst/size).
extern s32 func_8071432C(void);
extern s32 func_80714394(void);

void eepromCopySlot(void) {
    u8 original;
    u8 replacement;
    s16 unk0;
    s32 size;
    u8 *src;
    u8 *dst;

    original = eepromGetSectorForSlot(D_807467C8);
    replacement = eepromGetSectorForSlot(3);
    if (((func_8071432C() != 0) || (func_80714394() != 0)) && (original != replacement)) {
        unk0 = D_807ECEA0[0];
        size = ((((unk0 + 0x6B7) & ~0x3F) + 0x27) & ~7) / 8;
        src = D_807ECEA8 + (size * original);
        if (replacement == 0) {} // FAKE: pins the src/dst order and colours replacement v1
        dst = D_807ECEA8 + (size * replacement);
        unk0 = unk0 | 0; // FAKE: no-code def extends unk0's live range past dst
        memcpy(dst, src, size);
        D_807EDEA8[replacement] ^= D_807EDEA8[original];
        D_807EDEA8[original] ^= D_807EDEA8[replacement];
        D_807EDEA8[replacement] ^= D_807EDEA8[original];
    }
}
