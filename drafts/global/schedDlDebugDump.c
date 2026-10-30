// schedDlDebugDump (src/global/131B0.c): stage 4-5 (parked): frame 0xB8 + callee set match; 3 deadsweep FAKEs (full 224->142). Remaining: uopt pointerizes extern/bss scalars in the first block (D_807F0568 -> s1 with 'move a0,s1; lhu 0(s1)', D_80746A2C/A1C pointers in a1/v1, D_80746A14 chain-store pointer) where the target re-emits lui per access; no single dead stmt removes the D_807F0568 pointer (predicate sweep over all points/syms); op/i swap s0/s1 in the loop; beam sweep plateaus ~140
typedef struct {
    u8 op;
    char name[13];
    u8 size;
    u8 warn;
} Sched1DlOp;

extern Sched1DlOp D_8074685C[];
extern s8 D_80746A2C;
extern s16 D_80746A1C;
extern u32 D_80746A18;
extern u32 D_80746A20;
extern s32 D_80746A24;
extern s32 D_80746A28;
extern s32 D_80746A14;
extern char *D_80746A0C[];
extern u32 D_807F05A4;
extern u32 D_807F0984;
extern u32 D_80744478;
extern void faultFontSetColorMode(s32);
extern void controllerStartRead(void);

s32 schedDlDebugDump(s32 arg0, s32 arg1) {
    u8 op;
    s32 size;
    u32 *w;
    s32 line;
    s32 i;
    s32 off;
    s32 colorIdx;
    s32 found;
    Sched1DlOp *e;
    s32 n;
    s32 mode;
    s32 done;
    char buf[36];
    u32 cur;
    s16 buttons;
    u16 raw;
    s32 ret;
    char *q;
    u32 *p;

    done = 0;
    ret = 0;
    if (arg0 == 0) {
        osContGetReadData((OSContPad *)&D_807F0568);
        raw = D_807F0568.button;
        buttons = raw;
        if (arg1 != 0 && D_80746A2C != 0) {
            buttons = raw | 0x400;
        }
        if (buttons & 0x1000) {
            if (!(D_80746A1C & 0x1000)) {
                if (D_80746A2C > 0) {
                    D_80746A2C--;
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
        if (D_80746A1C && D_80746A1C) {}  // FAKE: deadsweep dead statement (steers uopt; replace with natural C)
        if (buttons & 0x800) {
            if (!(D_80746A1C & 0x800)) {
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
                done = 1;
            }
            if ((op & 0xF0) == 0xC0) {
                mode = 2;
                size = 0x20;
                n = 0;
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
                    *q = 'Z';
                    size += 0x10;
                    q++;
                }
                *q = 0;
                size >>= 2;
                faultPrintf("  %05x.:Triangle:.(%s)....\n", off, buf);
                line++;
                if (line == 1) {
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
                if (D_80744470 == 0) {}  // FAKE: deadsweep dead statement (steers uopt; replace with natural C)
                colorIdx = 0;
                found = 0;
                if (op == 0xE7) {
                    mode = 0;
                }
                if (op == 0xF6) {
                    mode = 0;
                }
                if (mode != 0) {
                    mode = 0;
                    faultFontSetColorMode(1);
                    colorIdx = 1;
                }
                for (i = 0; i < 0x1B; i++) {
                    if (op == D_8074685C[i].op) {
                        op = i;
                        found = 1;
                        i = 0x1B;
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
                    if (size < 3) {
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
                    if (D_80744470) {}  // FAKE: deadsweep dead statement (steers uopt; replace with natural C)
                }
            }
            faultFontSetColorMode(0);
            cur += size * 4;
        }
        p++;
    } while (p != &D_80744478);
    controllerStartRead();
    return ret;
}
