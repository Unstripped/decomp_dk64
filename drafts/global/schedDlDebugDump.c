// schedDlDebugDump (src/global/13980.c): Sched 2026-11-02: STAGE 4-5, restored the best known body (81 dead-test FAKEs from the leftovers5 hill-climb: deadsweep full/text 81/77 vs 133/123 of the previous 5-FAKE draft). Whole-file harness in the true TU (starting at schedCreate): 323 insns, frame 0xB8 + callee set match; remaining diff: 2 extra real insns ('sw a0,184(sp)' arg0 home store from the arg dead tests + one a3/v1 copy in the Triangle block), hi(D_80746A2C)/hi(D_80746A1C)/D_80746A18 are coloured a1/a0/a2 in the target (ours ring temps t8/t2), buttons v1 ok. Natural C (no FAKEs) is 335 insns/text 215 (pointerized lui+addiu of the 4+-ref globals D_80746A2C/A1C). Greedy dead-test sweep over 14 globals x 4 forms from the natural body (5 rounds, 40k compiles) only reached n=323/text 122: the old climb stays best. TU end note: the 3 trailing nops are .text end padding to 16 of the sched TU (ends 0x8060FFF0), so insn count compares as code+pad; a count-exact body gets the 3 pad nops automatically.
s32 schedDlDebugDump(s32 arg0, s32 arg1) {
    s32 cur;
    u32 n;
    u32 *w;
    s16 found;
    s32 i;
    s32 off;
    s32 line;
    u8 op;
    DlOpInfo *e;
    s32 raw;
    s32 mode;
    u32 done;
    char buf[36];
    s16 buttons;
    u16 colorIdx;
    s32 size;
    u32 ret;
    char *q;
    u32 *p;

if (D_80746A0C && D_80746A0C) {}  // FAKE: deadsweep dead statement (steers uopt; replace with natural C)
    done = 0;
    if (D_80744478) {}  // FAKE: deadsweep dead statement (steers uopt; replace with natural C)
    ret = 0;
    if (arg0 == 0) {
        if (arg0 == 0) {}  // FAKE: deadsweep dead statement (steers uopt; replace with natural C)
        osContGetReadData((OSContPad *)((u8 *)&D_807F0564 + 4));  // FAKE: arg spelled off D_807F0564 so uopt does not CSE lda D_807F0568 with the .button read
        if (done && done) {}  // FAKE: deadsweep dead statement (steers uopt; replace with natural C)
        if (D_80746A0C && D_80746A0C) {}  // FAKE: deadsweep dead statement (steers uopt; replace with natural C)
        raw = D_807F0568.button;
        buttons = raw;
        if (arg1 != 0 && D_80746A2C != 0) {
            buttons = raw | 0x400;
        }
        if (D_80746A2C && D_80746A2C) {}  // FAKE: deadsweep dead statement (steers uopt; replace with natural C)
        if (buttons & 0x1000) {
            if (!(D_80746A1C & 0x1000)) {
                if (D_80746A2C > 0) {
                    D_80746A2C -= 1;
                }
            }
            if (arg0) {}  // FAKE: deadsweep dead statement (steers uopt; replace with natural C)
        }
        if (!done) {}  // FAKE: deadsweep dead statement (steers uopt; replace with natural C)
        if (buttons & 0x400) {
            if (D_807F05A4 != 0) {}  // FAKE: deadsweep dead statement (steers uopt; replace with natural C)
            if (!(D_80746A1C & 0x400)) {
                if (done == 0) {}  // FAKE: deadsweep dead statement (steers uopt; replace with natural C)
                if (D_80746A18 != 0) {
                    D_80746A24 = D_80746A28;
                    if (!D_80746A18) {}  // FAKE: deadsweep dead statement (steers uopt; replace with natural C)
                    if (done != 0) {}  // FAKE: deadsweep dead statement (steers uopt; replace with natural C)
                    if (D_80746A24 != 0) {}  // FAKE: deadsweep dead statement (steers uopt; replace with natural C)
                    D_80746A20 = D_80746A18;
                    if (!D_80744478) {}  // FAKE: deadsweep dead statement (steers uopt; replace with natural C)
                }
                if (!D_80746A24) {}  // FAKE: deadsweep dead statement (steers uopt; replace with natural C)
            }
            if (arg0 && arg0) {}  // FAKE: deadsweep dead statement (steers uopt; replace with natural C)
        }
        if (buttons & 0x800) {
            if (D_80746A0C && D_80746A0C) {}  // FAKE: deadsweep dead statement (steers uopt; replace with natural C)
            if (!(D_80746A1C & 0x800)) {
                if (D_80746A18 == 0) {}  // FAKE: deadsweep dead statement (steers uopt; replace with natural C)
                D_80746A24 = 0;
                D_80746A20 = D_807F05A4;
            }
        }
        if (buttons & 0x10) {
            if (!(D_80746A1C & 0x10)) {
                if (D_80746A24 != 0) {}  // FAKE: deadsweep dead statement (steers uopt; replace with natural C)
                ret = 1;
                if (done && done) {}  // FAKE: deadsweep dead statement (steers uopt; replace with natural C)
            }
        }
        if (D_80746A1C) {}  // FAKE: deadsweep dead statement (steers uopt; replace with natural C)
        D_80746A1C = buttons;
    } else {
        D_80746A24 = 0;
        D_80746A20 = D_80746A14 = D_807F05A4;
        if (!D_80744470) {}  // FAKE: deadsweep dead statement (steers uopt; replace with natural C)
        D_80746A1C = 0;
        if (!D_80746A20) {}  // FAKE: deadsweep dead statement (steers uopt; replace with natural C)
        D_80746A18 = 0;
    }
    p = D_80744470;
    if (!arg0) {}  // FAKE: deadsweep dead statement (steers uopt; replace with natural C)
    do {
        faultFontInit(*p, 0, 1);
        line = 0;
        cur = D_80746A20;
        mode = D_80746A24;
        while (done == 0 && line < 0xF) {
            off = cur - D_807F05A4;
            if (D_807F05A4 && D_807F05A4) {}  // FAKE: deadsweep dead statement (steers uopt; replace with natural C)
            if (!D_80746A18) {}  // FAKE: deadsweep dead statement (steers uopt; replace with natural C)
            if (line < 0xE) {
                D_80746A28 = mode;
                D_80746A18 = cur;
            }
            if (D_80746A24 == 0) {}  // FAKE: deadsweep dead statement (steers uopt; replace with natural C)
            op = *(u32 *)cur >> 24;
            if (D_807F05A4 + D_807F0984 < cur) {
                if (D_80744478) {}  // FAKE: deadsweep dead statement (steers uopt; replace with natural C)
                if (D_80744470 == 0) {}  // FAKE: deadsweep dead statement (steers uopt; replace with natural C)
                if (!done) {}  // FAKE: deadsweep dead statement (steers uopt; replace with natural C)
                done = 1;
            }
            if (!D_80746A14) {}  // FAKE: deadsweep dead statement (steers uopt; replace with natural C)
            if ((op & 0xF0) == 0xC0) {
                n = 0;
                size = 0x20;
                mode = 2;
                if (op & 4) {
                    if (!D_80746A2C) {}  // FAKE: deadsweep dead statement (steers uopt; replace with natural C)
                    if (op) {}  // FAKE: deadsweep dead statement (steers uopt; replace with natural C)
                    buf[0] = 'S';
                    if (!cur) {}  // FAKE: deadsweep dead statement (steers uopt; replace with natural C)
                    size = 0x60;
                    if (D_80746A0C && D_80746A0C) {}  // FAKE: deadsweep dead statement (steers uopt; replace with natural C)
                    if (D_80746A28 != 0) {}  // FAKE: deadsweep dead statement (steers uopt; replace with natural C)
                    n = 1;
                    if (arg0) {}  // FAKE: deadsweep dead statement (steers uopt; replace with natural C)
                }
                if (op & 2) {
                    if (!D_80746A1C) {}  // FAKE: deadsweep dead statement (steers uopt; replace with natural C)
                    buf[n] = 'T';
                    n++;
                    size += 0x40;
                }
                if (!done) {}  // FAKE: deadsweep dead statement (steers uopt; replace with natural C)
                q = buf + n;
                if (op & 1) {
                    if (D_80746A28 == 0) {}  // FAKE: deadsweep dead statement (steers uopt; replace with natural C)
                    size += 0x10;
                    *q = 'Z';
                    if (!D_80746A28) {}  // FAKE: deadsweep dead statement (steers uopt; replace with natural C)
                    q++;
                    if (!D_80746A20) {}  // FAKE: deadsweep dead statement (steers uopt; replace with natural C)
                }
                if (size == 0) {}  // FAKE: deadsweep dead statement (steers uopt; replace with natural C)
                if (arg0 == 0) {}  // FAKE: deadsweep dead statement (steers uopt; replace with natural C)
                *q = 0;
                faultPrintf("  %05x.:Triangle:.(%s)....\n", off, buf);
                if (D_80746A20 == 0) {}  // FAKE: deadsweep dead statement (steers uopt; replace with natural C)
                size >>= 2;
                line++;
                if (line == 1) {
                    if (!D_80744478) {}  // FAKE: deadsweep dead statement (steers uopt; replace with natural C)
                    w = (u32 *)cur;
                    if (D_80746A14) {}  // FAKE: deadsweep dead statement (steers uopt; replace with natural C)
                    for (i = 0; i < size * 4; i += 16) {
                        faultPrintf("  %08x.%08x.%08x.%08x\n", w[0], w[1], w[2], w[3]);
                        w += 4;
                        if (!D_80744478) {}  // FAKE: deadsweep dead statement (steers uopt; replace with natural C)
                        line++;
                    }
                    D_80746A18 = size * 4 + cur;
                } else {
                    if (!cur) {}  // FAKE: deadsweep dead statement (steers uopt; replace with natural C)
                    D_80746A18 = cur;
                    if (!done) {}  // FAKE: deadsweep dead statement (steers uopt; replace with natural C)
                }
                while (line < 0xF) {
                    faultPrintf("  ----------------------------------\n");
                    line++;
                }
                if (!D_80746A28) {}  // FAKE: deadsweep dead statement (steers uopt; replace with natural C)
                if (D_80746A0C == 0) {}  // FAKE: deadsweep dead statement (steers uopt; replace with natural C)
                if (D_80744470 && D_80744470) {}  // FAKE: deadsweep dead statement (steers uopt; replace with natural C)
                line = 0x1E;
            } else {
                if (D_80746A14) {}  // FAKE: deadsweep dead statement (steers uopt; replace with natural C)
                if (done == 0) {}  // FAKE: deadsweep dead statement (steers uopt; replace with natural C)
                if (!D_80746A0C) {}  // FAKE: deadsweep dead statement (steers uopt; replace with natural C)
                colorIdx = 0;
                if (line == 0) {}  // FAKE: deadsweep dead statement (steers uopt; replace with natural C)
                found = 0;
                if (op == 0xE7) {
                    if (!cur) {}  // FAKE: deadsweep dead statement (steers uopt; replace with natural C)
                    mode = 0;
                }
                if (op == 0xF6) {
                    mode = 0;
                }
                if (mode != 0) {
                    faultFontSetColorMode(1);
                    if (arg0 && arg0) {}  // FAKE: deadsweep dead statement (steers uopt; replace with natural C)
                    colorIdx = 1;
                    mode = 0;
                }
                if (D_80746A0C && D_80746A0C) {}  // FAKE: deadsweep dead statement (steers uopt; replace with natural C)
                if (!arg0) {}  // FAKE: deadsweep dead statement (steers uopt; replace with natural C)
                for (i = 0; i < 0x1B; i++) {
                    if (op == D_8074685C[i].op) {
                        i = 0x1B;
                        found = 1;
                        op = i;
                    }
                }
                e = &D_8074685C[op];
                if (e->warn != 0) {
                    mode = 1;
                }
                if (D_80744470 == 0) {}  // FAKE: deadsweep dead statement (steers uopt; replace with natural C)
                if (found) {
                    size = e->size >> 2;
                    faultPrintf("  %05x.:.%s...%s.\n", off, e->name, D_80746A0C[colorIdx]);
                    line++;
                    if (done) {}  // FAKE: deadsweep dead statement (steers uopt; replace with natural C)
                    if (size <= 2) {
                        if (D_80746A2C != 0) {}  // FAKE: deadsweep dead statement (steers uopt; replace with natural C)
                        line++;
                        if (done) {}  // FAKE: deadsweep dead statement (steers uopt; replace with natural C)
                        faultPrintf("  %08x..%08x............\n", ((u32 *)cur)[0], ((u32 *)cur)[1]);
                    } else {
                        faultPrintf("  %08x.%08x.%08x.%08x...\n", ((u32 *)cur)[0], ((u32 *)cur)[1], ((u32 *)cur)[2], ((u32 *)cur)[3]);
                        line += 2;
                    }
                } else {
                    if (!D_80746A2C) {}  // FAKE: deadsweep dead statement (steers uopt; replace with natural C)
                    if (D_80746A14 && D_80746A14) {}  // FAKE: deadsweep dead statement (steers uopt; replace with natural C)
                    size = 2;
                    if (op == 0) {
                        if (op == 0) {}  // FAKE: deadsweep dead statement (steers uopt; replace with natural C)
                        if (D_80746A28 != 0) {}  // FAKE: deadsweep dead statement (steers uopt; replace with natural C)
                        faultPrintf(" %05x  NOOP..........\n", off);
                    } else {
                        faultPrintf("  %05x Undef.............\n", off);
                    }
                    line++;
                    if (D_80746A14) {}  // FAKE: deadsweep dead statement (steers uopt; replace with natural C)
                    if (D_80744470 && D_80744470) {}  // FAKE: deadsweep dead statement (steers uopt; replace with natural C)
                    if (!D_80744470) {}  // FAKE: deadsweep dead statement (steers uopt; replace with natural C)
                }
                if (!D_807F05A4) {}  // FAKE: deadsweep dead statement (steers uopt; replace with natural C)
            }
            faultFontSetColorMode(0);
            if (done != 0) {}  // FAKE: deadsweep dead statement (steers uopt; replace with natural C)
            cur += size * 4;
            if (!line) {}  // FAKE: deadsweep dead statement (steers uopt; replace with natural C)
            if (D_80746A20) {}  // FAKE: deadsweep dead statement (steers uopt; replace with natural C)
        }
        if (!D_807F05A4) {}  // FAKE: deadsweep dead statement (steers uopt; replace with natural C)
        if (D_80746A20 == 0) {}  // FAKE: deadsweep dead statement (steers uopt; replace with natural C)
        p++;
    } while (p != &D_80744478);
    if (!D_807F0984) {}  // FAKE: deadsweep dead statement (steers uopt; replace with natural C)
    controllerStartRead();
    if (D_80746A14) {}  // FAKE: deadsweep dead statement (steers uopt; replace with natural C)
    return ret;
}
