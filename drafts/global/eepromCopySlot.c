// eepromCopySlot (src/global/104F0.c): W2IntA: stage 5, score 9 (was 12), count 78 exact. src/dst locals (src assigned FIRST + dead test 'if (src) {}' pins evaluation) give src-first multu order and the size chain in v0 exactly. Remaining 6 lines = colour rotation: replacement a3 (target v1), original a0 (target a3), unk0 v1 (target v0, shares v0 with chain; ours interferes with cand 28 udiv coloured v0 first). Variants reaching 6: (a) dead read of unk0 BEFORE its def (illegal), (b) K&R phantom formal 'void eepromCopySlot(unk0) s32 unk0;' + 'if (unk0) {}' at entry (needs the two extern decls unprototyped; not adopted). Tried: 4320-variant type/decl-order/dt grid (floor 9), guarded anneals (floor 9), n var/inline/size-chain forms c1-c7 x u1-u9, legal pre-def unk0=0 + dead test (9, no gain).
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
        if (src) {} // FAKE: pins src before dst (evaluation order and colouring of the mask temps)
        dst = D_807ECEA8 + (size * replacement);
        memcpy(dst, src, size);
        D_807EDEA8[replacement] ^= D_807EDEA8[original];
        D_807EDEA8[original] ^= D_807EDEA8[replacement];
        D_807EDEA8[replacement] ^= D_807EDEA8[original];
    }
}
