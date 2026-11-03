// schedDlDebugDump (src/global/13980.c): MiscC leftovers7: STAGE 4-5, NEW BASE with function-local statics. D_80746A14/18/1C/20/24/28/2C are referenced ONLY by this function (asm + src grep), so they are `static` locals here (static u32 D_80746A14; ... static s8 D_80746A2C = 4;): the natural body (0 FAKEs) goes text 177 -> 140 and shows the target's lui a1/a0 hoists; 6 dead tests -> deadsweep text 81, then two LAYOUT joins in the Triangle block (size += 0x10; *q = 'Z'; and *q = 0; faultPrintf(...)) -> text 75 / full 121 (full includes ~46 reloc lines because the statics are .bss/.data-relative, not D_ names; count 415/415 exact, frame 0xB8). Old 81-FAKE non-static body (text 77) is in git history of this file. Needs when merged: drop the file-scope externs of those 7 symbols + carve .data/.bss (A2C=4 is .data, rest .bss) from 131B0.data.s; D_80746A0C/D_8074685C tables are also used only here (not yet tried as statics). Remaining diff: s-reg naming (op/idx s0<->s1, cur s5 lui), buttons narrowing: target is ori t8,v0,0x400; sll t9,t8,16 hoisted above beqz then sra v1,t9,16 (ring temps), ours ori v1 (20 spellings of the narrowing, local decl order/type climbs 50k evals, 1-2 statement line-joins 30k combos did not change it).
s32 schedDlDebugDump(s32 arg0, s32 arg1) {
    static u32 D_80746A14;
    static u32 D_80746A18;
    static s16 D_80746A1C;
    static u32 D_80746A20;
    static s32 D_80746A24;
    static s32 D_80746A28;
    static s8 D_80746A2C = 4;
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

    done = 0;
    ret = 0;
    if (arg0 == 0) {
        osContGetReadData((OSContPad *)((u8 *)&D_807F0564 + 4));  // FAKE: arg spelled off D_807F0564 so uopt does not CSE lda D_807F0568 with the .button read
        raw = D_807F0568.button;
        buttons = raw;
        if (arg1 != 0 && D_80746A2C != 0) {
            buttons = raw | 0x400;
        }
        if (buttons & 0x1000) {
            if (!(D_80746A1C & 0x1000)) {
                if (D_80746A2C > 0) {
                    D_80746A2C -= 1;
                }
            }
        }
        if (buttons & 0x400) {
            if (!(D_80746A1C & 0x400)) {
                if (D_80746A18 != 0) {
                    D_80746A24 = D_80746A28;
                    D_80746A20 = D_80746A18;
                }
            }
        }
        if (buttons & 0x800) {
            if (!(D_80746A1C & 0x800)) {
                if (D_807F05A4 && D_807F05A4) {}  // FAKE: deadsweep dead statement (steers uopt; replace with natural C)
                D_80746A24 = 0;
                D_80746A20 = D_807F05A4;
            }
        }
        if (buttons & 0x10) {
            if (!(D_80746A1C & 0x10)) {
                ret = 1;
            }
        }
        D_80746A1C = buttons;
    } else {
        D_80746A24 = 0;
        D_80746A20 = D_80746A14 = D_807F05A4;
        D_80746A1C = 0;
        D_80746A18 = 0;
    }
    p = D_80744470;
    do {
        faultFontInit(*p, 0, 1);
        line = 0;
        cur = D_80746A20;
        mode = D_80746A24;
        while (done == 0 && line < 0xF) {
            off = cur - D_807F05A4;
            if (line < 0xE) {
                D_80746A28 = mode;
                D_80746A18 = cur;
            }
            op = *(u32 *)cur >> 24;
            if (D_807F05A4 + D_807F0984 < cur) {
                done = 1;
            }
            if ((op & 0xF0) == 0xC0) {
                n = 0;
                size = 0x20;
                if (done && done) {}  // FAKE: deadsweep dead statement (steers uopt; replace with natural C)
                mode = 2;
                if (op & 4) {
                    buf[0] = 'S';
                    size = 0x60;
                    n = 1;
                }
                if (op & 2) {
                    buf[n] = 'T';
                    n++;
                    size += 0x40;
                }
                q = buf + n;
                if (op & 1) {
                    size += 0x10; *q = 'Z';  // LAYOUT: joined statements change as1 scheduling (text 81 -> 75 with the next one)
                    q++;
                }
                *q = 0; faultPrintf("  %05x.:Triangle:.(%s)....\n", off, buf);  // LAYOUT: joined statements change as1 scheduling
                size >>= 2;
                line++;
                if (line == 1) {
                    if (D_80744470) {}  // FAKE: deadsweep dead statement (steers uopt; replace with natural C)
                    w = (u32 *)cur;
                    for (i = 0; i < size * 4; i += 16) {
                        faultPrintf("  %08x.%08x.%08x.%08x\n", w[0], w[1], w[2], w[3]);
                        w += 4;
                        line++;
                    }
                    D_80746A18 = size * 4 + cur;
                } else {
                    D_80746A18 = cur;
                }
                while (line < 0xF) {
                    faultPrintf("  ----------------------------------\n");
                    line++;
                }
                line = 0x1E;
            } else {
                if (D_80744470) {}  // FAKE: deadsweep dead statement (steers uopt; replace with natural C)
                colorIdx = 0;
                found = 0;
                if (op == 0xE7) {
                    mode = 0;
                }
                if (op == 0xF6) {
                    mode = 0;
                }
                if (mode != 0) {
                    faultFontSetColorMode(1);
                    colorIdx = 1;
                    mode = 0;
                }
                for (i = 0; i < 0x1B; i++) {
                    if (op == D_8074685C[i].op) {
                        if (i && i) {}  // FAKE: hc
                        i = 0x1B;
                        found = 1;
                        op = i;
                    }
                }
                e = &D_8074685C[op];
                if (e->warn != 0) {
                    mode = 1;
                }
                if (found) {
                    size = e->size >> 2;
                    faultPrintf("  %05x.:.%s...%s.\n", off, e->name, D_80746A0C[colorIdx]);
                    line++;
                    if (size <= 2) {
                        line++;
                        faultPrintf("  %08x..%08x............\n", ((u32 *)cur)[0], ((u32 *)cur)[1]);
                    } else {
                        faultPrintf("  %08x.%08x.%08x.%08x...\n", ((u32 *)cur)[0], ((u32 *)cur)[1], ((u32 *)cur)[2], ((u32 *)cur)[3]);
                        line += 2;
                        if (i) {}  // FAKE: hc
                    }
                } else {
                    size = 2;
                    if (op == 0) {
                        faultPrintf(" %05x  NOOP..........\n", off);
                    } else {
                        faultPrintf("  %05x Undef.............\n", off);
                    }
                    line++;
                    if (D_80744470) {}  // FAKE: deadsweep dead statement (steers uopt; replace with natural C)
                }
            }
            faultFontSetColorMode(0);
            if (size == 0) {}  // FAKE: hc
            cur += size * 4;
        }
        p++;
    } while (p != &D_80744478);
    controllerStartRead();
    return ret;
}
