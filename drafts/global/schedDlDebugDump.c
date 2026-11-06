// schedDlDebugDump (src/global/13980.c): stage 6 SchedDump 2026-11-06: improved full54/text8 to full48/text2/reloc46/shape46 n415 (323 instructions), whole-file frame/text extents unchanged. Replace the inner extent-overflow done==0 dead guard with op = (word >> 24) & 0xFFFF: Q0253 burns one ring slot at opcode extraction, and removing the later guard restores all subsequent temporaries. Only remaining text rows are object 0x1018/0x101c: target lui v0,%hi(D_80746A20); lw s5,%lo(D_80746A20)(v0), current uses s5 as the base in both. uopt -l5/-l6 identifies static D20 candidate47 uncoloured (adjsave -24 baseline, -30 improved), cur candidate80 coloured19=s5 (adjsave88.8235321); there is no coloured D20 address candidate. Ugen emits lw $21,D20 directly. DIAGNOSTIC ONLY: replacing that one record by lw $2,D20; move $21,$2 makes as1 full46/text0/reloc46/n415; no C reproducer found. Alias/array/bitfield/pointer views, destination homes, copy barriers, no-op expressions, savings thresholds, guarded regions, 64-bit conversions and typed ghosts did not improve the last pair. Remaining three old steering constructs were retested and are necessary at this best. Backend single-record scans: 553 baseline edits and 368 improved-load-region edits, zero improvements. Permuter from original text8 baseline ran -j2/600s, 42243 iterations, best60 (no improvement; 755 invalid mutations). Evidence .scratch/SchedDump/text2-trace5.list, text2-trace6.list, text2probe/t.s, text2probe/load-v0-copy.G (diagnostic only), text2-objdump.diff. Plain whole-file 13980_text2.c fdiff FAILED .text plus reloc, CURRENT20; final parked 13980.c fdiff OK and --non-matching compile passes. Draft saved with original history retained. stage 6: full=54 text=8 reloc=46 shape=46 n=415 (323 instructions), frame 184 and callee-saved exact. Matcher8 base 9be598a1b53e8f6b46eaf86544764c28fd319eba preserves Matcher6 text8 but fixes data ownership: file-scope D_80746A14..D_80746A2C definitions must be excluded from NON_MATCHING and removed for plain C, leaving sole function-local statics in original address order; .data now byte-identical 528 bytes vs previous 560. Replaced chained D_80746A20=D_80746A14=D_807F05A4 with separate D_80746A14 then D_80746A20 assignments, fixing an actual reversed store relocation hidden by deadsweep normalization. Removed done&&done and D_8074685C&&D_8074685C FAKEs together with unchanged text8. Remaining: D_80746A20 load base s5 instead of v0 (2) and six opcode/extent-ring registers. Tried unique local statics, all file statics/globals and prefixes, local static declaration placement, signedness combinations of five statics, address-pointer types, explicit address integer routes, moved static/cur dead-read lifetime partitions, conversion routing, and targeted static dead sweep (423 variants): no text improvement. Prior Matcher6 dead ends: index/formal/byte-offset, local-home removal, opcode/extent locals, pointer/static/aggregate types, typed dead lvalues, wide/narrow opcode extraction. Pure alias D_807F0564+4 equals D_807F0568; local .data relocations are non-normalized diagnostics, not 46 real address errors. Re-scored after 7e40c10c and expected refresh: still full54/text8/reloc46/shape46. Permuter -j2 --seconds600 observed no score below60, but the tool-fix agent confirmed deleting shared .scratch/permuter during the run (many late compile errors); no best candidate survived to inspect. No rerun: the structural/type/lifetime searches and 423-variant static sweep had already exhausted this attempt without a text improvement. Plain-C fdiff: FAILED: Section .text content mismatch (built: 4976 bytes, expected: 4976 bytes); FAILED: Relocations mismatch; CURRENT (60). Final parked copy fdiff OK; --non-matching compile passes.
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
        D_80746A14 = D_807F05A4;
        D_80746A20 = D_807F05A4;
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
            op = (*(u32 *)cur >> 24) & 0xFFFF;  // FAKE: burns one ugen ring slot before opcode/extent temporaries
            if (D_807F05A4 + D_807F0984 < cur) {
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
                    n++;
                    size += 0x40;
                }
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
