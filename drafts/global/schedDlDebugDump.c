// schedDlDebugDump (src/global/13980.c): CtrlSched revisit8: STAGE 4 (count exact 415, frame 184, callee-saved set same), deadsweep score full 119->69 (text 73->23, reloc 46 = uncarved statics), shape 63->60. KEY structure changes vs the old park: (1) Triangle word dump loop is the LFTR source form 'for (i = 0; i < size; i += 4) faultPrintf(..., ((u32 *)cur)[i], [i+1], [i+2], [i+3]); line++;' (no w pointer, no size*4 bound, no w += 4): uopt then derives the byte IV + size*4 bound after the 'blez s4' guard exactly like the target (target's guard tests size, bound sll s2 computed after it); (2) 'buttons |= 0x400;' (compound on the s16 local) reproduces the target's ori t8,v0 / sll t9 / beqz / sra v1 chain hoisted over the lb stall (buttons = raw | 0x400 gave ori v1 dest-reuse and no hoist); (3) declaration order + all old dead tests re-tuned by a count/frame-guarded SA (5 FAKEs left: all needed, deleting any costs 3-6). Remaining diff (23 text lines): p loop pointer spills to 180(sp) vs target 80(sp) (5 lines; target p looks like a uopt temp slot at the bottom = original probably indexed D_80744470[k] with an LFTR'd pointer IV, but a k-index loop gave frame 192), q pointer split (move a3,v1 ... addiu a3,v1,1 vs target in-place addiu v1,v1,1; 4 lines), addiu s3,s3,1 slot after jal (2), b/sll s0,s4,2 delay slot (target copies post-loop sll s0,s4,2 into the bne delay slot and the b delay slot; 4).
s32 schedDlDebugDump(s32 arg0, s32 arg1) {
    static s32 D_80746A14 = 0;
    static u32 D_80746A18 = 0;
    static s16 D_80746A1C = 0;
    static u32 D_80746A20 = 0;
    static s32 D_80746A24 = 0;
    static s32 D_80746A28 = 0;
    static s8 D_80746A2C = 4;
    u32 *p;
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
    DlOpInfo *e;
    s32 i;
    u32 ret;
    s32 raw;

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
                q = buf + n;
                if (op & 1) {
                    size += 0x10; *q = 'Z';  // LAYOUT: joined statements change as1 scheduling (text 81 -> 75 with the next one)
                    q++;
                }
                size = size >> 2;
                q[0] = 0;
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
                done = done;  // FAKE: deadsweep dead statement (steers uopt; replace with natural C)
            }
            faultFontSetColorMode(0);
            cur += size * 4U;
        }
        p++;
    } while (p != &D_80744478);
    controllerStartRead();
    return ret;
}
