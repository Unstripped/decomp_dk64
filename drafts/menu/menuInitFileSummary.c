// menuInitFileSummary (src/menu/3E10.c): W2Int 2026-11-03: unchanged full=7 shape=2 (loop 1: target s0=p s1=end(&D_80033809) s2=q; ours s1=q s2=end). Confirmed with -l5/-l6: cand 18 p adjsave 20.5 (3 uses+def in bb6), 15 q 15.5 (bb5 lh + bb6 inc), 2 end (arg0 isvar) 6.0; colouring order p,q,end; end needs >= 15.5 (ties go to lower candidate number, end is #2 so 3 in-loop events suffice). Tried new: no-code defs `arg0 = (void *)((u32)arg0 | 0/+0/&0xFFFFFFFF/*1/^0)` at 4 loop positions x 0-2 repeats (150): cfe folds them, no effect; `+ ((s32)arg0 * 0)` terms on k/store/cond (27 combos): adds +3 insns; dead `if (end/arg0 == 0/&&) {}` at loop top/mid/end: end becomes a late s3 candidate (full 18-23, shape 7-12); separate `s8 *end` local at 3 declaration positions: 12; direct `p < &D_80033809` / neighbour-symbol spellings: 7-8; index loops (for i=0..4, do/while, p[i], q[i-1]): not unrolled but keep `i` (move s1,zero; slti s1,4; addu t1,s2,s1), 73; 420 s annealer over p/q/k/arg0 dead tests in the loop region: none < 7. Untried: a real third in-loop reference to end that costs no code.
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
