// menuInitFileSummary (src/menu/3E10.c): W4Menu + leftovers6 W2IntC: stage 4+ (frame 0x80, parked NON_MATCHING in menu/3E10.c), deadsweep full=7 text=7 shape=2 (241/241). W4Menu: '(call ^ 0) != sp64' fixed the beq t6,v0 order. Left: loop 1 (p/q/end) regalloc: target s0=p s1=end s2=q, ours s1=q s2=end (-l5: q cand adjsave 15.5 coloured before end/arg0 6.0; target needs end before q). Tried (W4Menu SA + W2IntC): end as arg0/local, dead tests and no-code | 0 / ^ 0 / & -1 / * 1 defs, 12 loop forms; W2IntC: index loops 'for (i..) (&D_80033805)[i] = flagGet((&D_807505B2)[i-1])' (count 239, IV not eliminated), '&A[i] < end' tests (247), pointer-difference q '(p - &D_80033805)' (244, not strength reduced), const end '&D_80033809', declaration/assignment orders of p/q/end (7 or 12), 600s anneal over dead tests + line joins, permuter 34k iterations (no gain).
extern s8 D_80033809;
void menuInitFileSummary(void *arg0, s32 arg1) {
    MenuScreenState *temp_s6 = *(MenuScreenState **)((u8 *)arg0 + 0x174);
    u8 *row = D_807FC950[0];
    s8 *p;
    s16 *q;
    s8 *p2;
    void *a1;
    u32 sp64;
    s32 i;
    s32 k;
    s32 j;

    func_80030894(temp_s6, &D_80720CF0, 0x122, 0xD2, 0.75f, 2, 0);
    func_80030894(temp_s6, &D_80720D14, 0x23, 0xD2, 0.75f, 2, 0);
    func_80030894(temp_s6, &D_8072052C, 0x76, 0x91, 0.6f, 2, 9);
    D_80033F4C = 1600.0f;
    eepromLoadPlayerData((u8)D_80033F48, 0);
    D_80033804 = 1;
    q = &D_807505B2;
    p = &D_80033805;
    arg0 = &D_80033809;
    do {
        k = flagGet(q[-1], 0);
        q++;
        *p++ = k;
    } while (p < (s8 *)arg0);
    for (p2 = &D_80033805 - 1, i = 0; i != 5; i++) {
        if (*p2 != 0) {
            a1 = D_80750518[i];
        } else {
            a1 = &D_807211D0;
        }
        func_80030894(temp_s6, a1, i, i, 0.8f, 2, 0xF);
        p2++;
    }
    osPiReadIo(func_800297A8(0xAFFE1464), &sp64);
    if ((func_800297A8(0x0107183B) ^ 0) != sp64) { // FAKE: ^ 0 flips the commutative bne/beq operand order
        *(u32 *)(s32)&actorUpdateCollisionSpheres = 0x03E00008;
    }
    D_8003380C = 0;
    for (k = 0; k != 5; k++) {
        for (j = 0; j != 8; j++) {
            D_8003380C += *(u16 *)(row + 0x42 + j * 2);
        }
        row += 0x5E;
    }
    D_80033814 = D_80750AB0 / 60;
    D_80033810 = (s32)D_80033814 / 60;
    D_80033814 = D_80033814 - D_80033810 * 60;
    if (i) {} // FAKE: extends i's live range to the end, giving loop 2 the target's s0/s1 (p2/i) colouring
    D_80033F51 = menuCalculateGamePercentage();
}
