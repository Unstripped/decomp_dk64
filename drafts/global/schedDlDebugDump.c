// schedDlDebugDump (src/global/13980.c): stage 4: full=54 text=8 reloc=46 shape=46 n=415 (323 instructions), frame 184 and all callee-saved exact. Matcher6 on base 2b098035bc2bd79a4eb94174687b52ea14a12e4a improved text 17->8/full 63->54. Replaced named pointer p with u32 array index and D_80744470[p], reversed end-address comparison: uopt now forms a pointer induction spilltemp at target sp+0x50 rather than named home sp+0xb4. Inlined e field expressions and moved raw before ret to preserve all other stack offsets. Initialize n then size then mode; terminate buf before size >>= 2, fixing two scheduling differences. Remaining 8 text lines: D_80746A20 load base s5 instead of v0 (2), and six opcode/extent-ring instructions use t7/t9/t0 rather than t8/t0/t1. Tried index/formal/byte-offset variants, local-home removal, real opcode and extent value routing, pointer/static/aggregate types, typed dead lvalues, and wide/narrow opcode extraction: no further reduction. Local static declarations still shadow existing file-scope data, so 46 normalized relocation differences are not resolved; no data cutover attempted in this private park.
s32 schedDlDebugDump(s32 arg0, s32 arg1) {
    static s32 D_80746A14 = 0;
    static u32 D_80746A18 = 0;
    static s16 D_80746A1C = 0;
    static u32 D_80746A20 = 0;
    static s32 D_80746A24 = 0;
    static s32 D_80746A28 = 0;
    static s8 D_80746A2C = 4;
    u32 p;
    s32 size;
    char *q;
    u16 colorIdx;
    u8 op;
    s16 buttons;
    s32 off;
    u32 n;
    s16 found;
    s32 line;
    s32 cur;
    s32 mode;
    u32 done;
    char buf[36];
    s32 i;
    s32 raw;
    u32 ret;

    done = 0;
    ret = 0;
    if (arg0 == 0) {
        osContGetReadData((OSContPad *)((u8 *)&D_807F0564 + 4));  // FAKE: arg spelled off D_807F0564 so uopt does not CSE lda D_807F0568 with the .button read
        raw = D_807F0568.button;
        buttons = raw;
        if (arg1 != 0 && D_80746A2C != 0) {
            buttons |= 0x400;
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
                if (D_807F05A4 == 0) {}  // FAKE: deadsweep dead statement (steers uopt; replace with natural C)
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
    p = 0;
    do {
        faultFontInit(D_80744470[p], 0, 1);
        line = 0;
        mode = D_80746A24;
        cur = D_80746A20;
        while (done == 0 && line < 0xF) {
            off = cur - D_807F05A4;
            if (line < 0xE) {
                D_80746A28 = mode;
                D_80746A18 = cur;
            }
            op = *(u32 *)cur >> 24;
            if (D_807F05A4 + D_807F0984 < cur) {
                if (done == 0) {}  // FAKE: deadsweep dead statement (steers uopt; replace with natural C)
                done = 1;
            }
            if ((op & 0xF0) == 0xC0) {
                n = 0;
                size = 0x20;
                mode = 2;
                if (op & 4) {
                    buf[0] = 'S';
                    size = 0x60;
                    n = 1;
                }
                if (op & 2) {
                    buf[n] = 'T';
                    if (done && done) {}  // FAKE: deadsweep dead statement (steers uopt; replace with natural C)
                    n++;
                    size += 0x40;
                }
                if (D_8074685C && D_8074685C) {}  // FAKE: deadsweep dead statement (steers uopt; replace with natural C)
                if (op & 1) {
                    buf[n] = 'Z';
                    size += 0x10;
                    n++;
                }
                buf[n] = 0;
                size >>= 2;
                faultPrintf("  %05x.:Triangle:.(%s)....\n", off, buf);
                line++;
                if (line == 1) {
                    for (i = 0; i < size; i += 4) {
                        faultPrintf("  %08x.%08x.%08x.%08x\n", ((u32 *)cur)[i], ((u32 *)cur)[i + 1], ((u32 *)cur)[i + 2], ((u32 *)cur)[i + 3]);
                        line++;
                    }
                    D_80746A18 = cur + size * 4;
                } else {
                    D_80746A18 = cur;
                }
                while (line < 0xF) {
                    faultPrintf("  ----------------------------------\n");
                    line++;
                }
                line = 0x1E;
            } else {
                if (D_80746A20) {}  // FAKE: deadsweep dead statement (steers uopt; replace with natural C)
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
                        op = i;
                        found = 1;
                        i = 0x1B;
                    }
                }
                if (D_8074685C[op].warn != 0) {
                    mode = 1;
                }
                if (found) {
                    size = D_8074685C[op].size >> 2;
                    faultPrintf("  %05x.:.%s...%s.\n", off, D_8074685C[op].name, D_80746A0C[colorIdx]);
                    line++;
                    if (size <= 2) {
                        faultPrintf("  %08x..%08x............\n", ((u32 *)cur)[0], ((u32 *)cur)[1]);
                        line++;
                    } else {
                        faultPrintf("  %08x.%08x.%08x.%08x...\n", ((u32 *)cur)[0], ((u32 *)cur)[1], ((u32 *)cur)[2], ((u32 *)cur)[3]);
                        line += 2;
                    }
                } else {
                    size = 2;
                    if (op == 0) {
                        faultPrintf(" %05x  NOOP..........\n", off);
                    } else {
                        faultPrintf("  %05x Undef.............\n", off);
                    }
                    line++;
                }
            }
            faultFontSetColorMode(0);
            cur += size * 4U;
        }
        p += 1;
    } while (&D_80744478 != &D_80744470[p]);
    controllerStartRead();
    return ret;
}
