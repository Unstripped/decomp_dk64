// eepromCopySlot (src/global/104F0.c): W4IntA: stage 5, 12 diff lines (unchanged). Diff = chain colour (ours a2 via root-dest targeting of coloured n cand 28; target v0) + dest-first vs src-first multu order. s32 in-place chain (size = lh; size += ..; size &= ..) puts the chain in v0 exactly but then n (cand 28) is coloured a2 directly (sra a2,v0,3, no t8 + move a2,t8, mults on a2): 25. Source order of dst/src (locals, dead uses), n var vs inline x3, mul operand order, memcpy prototype variants (7), casts: all identical output. 10k-eval hill-climb with no-code defs/dead tests on original/replacement/size/n/unk0: no gain.
extern s32 func_8071432C(void);
extern s32 func_80714394(void);
extern u8 D_807ECEA8[];
extern s16 D_807ECEA0[];
extern u8 D_807467C8;
extern u8 D_807EDEA8[];
u8 eepromGetSectorForSlot(s32);
void *memcpy(void *, const void *, size_t);

void eepromCopySlot(void) {
    u8 original;
    u8 replacement;
    s16 unk0;
    s32 size;

    original = eepromGetSectorForSlot(D_807467C8);
    replacement = eepromGetSectorForSlot(3);
    if (((func_8071432C() != 0) || (func_80714394() != 0)) && (original != replacement)) {
        unk0 = D_807ECEA0[0];
        size = ((((unk0 + 0x6B7) & ~0x3F) + 0x27) & ~7) / 8;

        memcpy(D_807ECEA8 + (size * replacement), D_807ECEA8 + (size * original), size);

        D_807EDEA8[replacement] ^= D_807EDEA8[original];
        D_807EDEA8[original] ^= D_807EDEA8[replacement];
        D_807EDEA8[replacement] ^= D_807EDEA8[original];
    }
}
