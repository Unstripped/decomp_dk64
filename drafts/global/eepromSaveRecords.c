// eepromSaveRecords (src/global/104F0.c): stage 4: full=26 text=27 reloc=0 shape=7; R12_sonnet_xhigh_4 (base 564cfef3) Q0548 XBB-window survey: as1probe keep on the park, patched as1 variants limit 0/1/2/3/5/10/100 (L100 built privately from as1patch by patching `li t4,10` at 0x42ace4 to 100, built with /usr/bin/make in .scratch/R12_sonnet_xhigh_4/as1L) and jr-live, plus as1probe scan. RESULT: pure uopt colouring plus a missing uopt copy, no as1 lever. Limit 0 is worse (28); limits 1/2/3/5/10/100 and jrlive all give full=26 text=27 shape=7 (n=342); scan (3134 edits) hits are only deletes/swaps at records 554-704 (the poll-ghost narrowing). The target's memcpy delay slot `move s4,s1` (and `addu a1` before the jal) is a uopt copy we do not emit, not an as1 fill; the li-at mask and s0/s2 tail clusters are candidate colouring. No guard route. | Prior: R11_eepromSaveRecords (base 9d6acd9dc66f1deacad36794631e27332c87412b): stage 4 park full=26 text=27 reloc=0 shape=7, 296 insns/frame 0x1078. Dissected ugen/as1 and uopt candidate webs behind all 3 remaining diff clusters. 1) Lines 105-115 offset alignment: target expands literal immediate masks via $at (li at,-64/and at 105, li at,-8/and at 110, li at,-64/and at 114). In isolation, (x & ~0x3FU) + 39; (x & ~7U) * 4 + 63; return x & ~0x3F; reproduces the exact three li-at sequence, but in eepromSaveRecords signed ~0x3F is globally colored to $s3 (cand 183, adjsave 12.0) across the entire function, so any signed mask in the arm joins $s3 (and v0,v0,s3, full=109), whereas two unsigned ~0x3FU masks common into a $v1 web (li v1,-64, full=125). 2) Tail b regalloc (lines 152-170): loop b (cand 38) and tail b (cand 90) were unified in $s2 in target; in decompiled C, b range is split, and because $s0 (holding loop i) dies at the join, uopt ascending register scan assigns 16 ($s0) to cand 38/90 instead of 18 ($s2). Extending i or arg0 across the join recolors the function and grows the frame. 3) Memcpy delay copy (lines 201-232): target places or s4,s1,zero (s4=sector) in the memcpy delay slot and branches on raw slti at,s4,0x100, narrowing andi s2,s1,0xffff in the branch delay slot. Pre-assigning idx=sector before memcpy crosses sleepMilliseconds and spills. Final private copy in exact stage-4 park fdiff OK. | Prior: EepromSave (base 0475d51ccaea07dca3cb6b50e2c427b68afcd771): retained stage-4 full=26 text=27 reloc=0 shape=7, 296 insns/frame 0x1078. No improved C. Rechecked the typed-mask mechanism: signed -64 joins the s3 web; unsigned first/last -64 becomes a two-use v1 web; explicit initialized signed/unsigned mask locals do not prevent this. New algebra probes: De Morgan full27 (one extra instruction), OR/XOR full117, inverted subtraction full119; bitfield lowering spills offset (full67), dead block between unsigned uses changes global allocation/frame (full239). Tail b identity defs, repeated ownership, and s16/u8 ghost consumers leave full26; replacing its ghost by an explicit mask regresses full139. Raw guard height identity still coalesces the memcpy copy (full55, one row short); early flag-address interference regresses full67. Baseline l5/l6 confirms tail candidate90=ucvtl, assigned s0 before sector58=s1; candidate90 adjsave1.5 forbids regs1-4,17-22 but not14-16. Candidate38 first-loop b is s2, but neutral defs do not merge its range with90. Exact residual remains first andi/subu vs li-at/and; tail b s0/s2; missing memcpy-delay move s4,s1; poll address v1/t2 and shifted guard scratch regs. Evidence .scratch/EepromSave/*-score.txt and baseline-l6.txt. | Prior paragraphs: eepromSaveRecords (src/global/104F0.c): EepromSave (base 0475d51ccaea07dca3cb6b50e2c427b68afcd771): retained stage-4 full=26 text=27 reloc=0 shape=7, 296 insns/frame 0x1078. No improved C. Rechecked the typed-mask mechanism: signed -64 joins the s3 web; unsigned first/last -64 becomes a two-use v1 web; explicit initialized signed/unsigned mask locals do not prevent this. New algebra probes: De Morgan full27 (one extra instruction), OR/XOR full117, inverted subtraction full119; bitfield lowering spills offset (full67), dead block between unsigned uses changes global allocation/frame (full239). Tail b identity defs, repeated ownership, and s16/u8 ghost consumers leave full26; replacing its ghost by an explicit mask regresses full139. Raw guard height identity still coalesces the memcpy copy (full55, one row short); early flag-address interference regresses full67. Baseline l5/l6 confirms tail candidate90=ucvtl, assigned s0 before sector58=s1; candidate90 adjsave1.5 forbids regs1-4,17-22 but not14-16. Candidate38 first-loop b is s2, but neutral defs do not merge its range with90. Exact residual remains first andi/subu vs li-at/and; tail b s0/s2; missing memcpy-delay move s4,s1; poll address v1/t2 and shifted guard scratch regs. Evidence .scratch/EepromSave/*-score.txt and baseline-l6.txt. | stage 4 park full=26 text=27 reloc=0 shape=7; 296 instructions and 0x1078 frame. Corrected old lossy (u16)offset alignment to offset-(offset&0x3F), matching target 32-bit behavior without changing full/text score. Remaining: B_post uses andi/subu instead of per-use li at,-64/and; tail b s0 vs s2; missing memcpy-delay move s4,s1 and poll/guard register differences. Tried signed/unsigned int/long/64-bit masks, compound chains, alignment shifts/divisions, parameter/local value routing, narrow sector variants, raw vs narrowed loop guard partitions, early index initialization, copy-retention and typed integer ghost reads. Removing poll ghost gets full=25 text=26 but 295 instructions (not parkable); all typed/lifetime combinations regress. Prior dead ends: candidate 90 ucvtl, u16 vs s32 idx, cross-loop b lifetime. | Finisher2b (base 82b768fd2cde4792d240c55bf4f4cd4bc3e0be85): retained full26 stage-4 park. Corrected candidate identities: bit23=M-23 raw u8 i is s1, bit33=ucvt(i) is s0, height is bit26=M-16/v0; the prior ledger's height/s1 label is wrong. Tail reuse of idx, with or without |0, leaves full26 unchanged. Defining i on the else path then extending it after CRC recolors and shrinks the frame (full262); not a two-edge-only fix. Backend scan exposes duplicate initial guard narrowing at record703. Routing raw guard through height removes it but coalesces the desired s4 copy (full55/one row short); retaining the guard and replacing the poll ghost by equality spills sector (full52). No improved C retained. Evidence: .scratch/Finisher2b-eepromSaveRecords/{base-l5.txt,*-score.txt,baseline-scan.txt}; final private park fdiff OK.
void eepromSaveRecords(s32 arg0) {
    s32 j;
    s32 sector;
    s32 offset;
    s32 height;
    u16 idx;
    u16 a;
    u16 b;
    u8 i;
    u8 workingData[0x800];
    u8 savedData[0x800];
    u8 *p;
    p = D_807ECD08;
    if (D_807EDEAC == 2) {
        _sprintf((char *)D_807ECEA8 + ((((((((((D_807ECEA0[0] + 0x6B7) & ~0x3F) + 0x27) & ~7) * 4) + 0x3F) & ~0x3F) + 0x207) & ~7) / 8), D_807467C0);
        memcpy(workingData, D_807ECEA8, 0x800);
        memcpy(savedData, D_807ED6A8, 0x800);
        if (arg0 == 0) {
            eepromCopySlot();
            for (i = 0; i < 4; i++) {
                height = ((((D_807ECEA0[0] + 0x6B7) & ~0x3F) + 0x27) & ~7);
                height /= 8;

                a = i * height;
                if (a) {}  // FAKE: live range / colouring of the narrowed index temp
                b = (((i + 1) * height) / 4) - 1;
                ((u32 *)workingData)[b] = eepromCalculateCrc32(a + workingData, height - 4);
            }
            sector = 0;
            offset = D_807ECEA0[0];
            offset += 0x6B7;
            offset = (offset - (offset & 0x3F)) + 0x27;
            offset = ((s32)(offset & ~7U) * 4) + 0x3F;
            offset = (s32)(offset & ~0x3FU);
            offset /= 8;
        } else {
            offset = (((((((D_807ECEA0[0] + 0x6B7) & ~0x3F) + 0x27) & ~7) * 4) + 0x3F) & ~0x3F);
            offset /= 8;
            sector = (offset / 8) & 0xFFFF;
        }
        a = offset;
        if (a) {}  // FAKE: live range / colouring of the narrowed index temp
        b = ((offset + 0x40) / 4) - 1;
        if (b) {}  // FAKE: live range / colouring of the narrowed index temp
        ((u32 *)workingData)[b] = eepromCalculateCrc32(a + workingData, 0x3C);
        bzero(strlen(D_807467C0) - (0x800 - ((((((((D_807ECEA0[0] + 0x6B7) & ~0x3F) + 0x27) & ~7) * 4) + 0x3F) & ~0x3F) / 8)) + workingData + 0x840, (0x800 - ((((((((D_807ECEA0[0] + 0x6B7) & ~0x3F) + 0x27) & ~7) * 4) + 0x3F) & ~0x3F) / 8)) - strlen(D_807467C0) - 0x40);
        if (D_807ECEA0) {}  // FAKE: deadsweep dead statement (steers uopt)
        osWritebackDCacheAll();
        memcpy(D_807ED6A8 + sector * 8, workingData + sector * 8, 0x800 - (sector << 3));
        if (D_807ECD08[0] != 0) do sleepMilliseconds(1.0f); while (*p != 0);
        if (D_807ECD08 && D_807ECD08) {}  // FAKE: colours the polled D_807ECD08 address candidate
        if (D_80744460 != 0) {
            D_807467C4 = 0;
        } else {
            D_807467C4 = 1;
            for (idx = sector; idx < 0x100; idx += 2) {
                D_807467E4 = 0x1E;
                D_807467E8 = (f32)(u32)idx * 0.00390625f;
                if (((u64 *)savedData)[idx] != ((u64 *)workingData)[idx] ||
                    ((u64 *)savedData)[idx + 1] != ((u64 *)workingData)[idx + 1]) {
                    for (j = 0; j < 2; j++) {
                        if (D_80744460 != 0) {
                            D_807467C4 = 0;
                            return;
                        }
                        osEepromWrite(&D_807ECCF0, idx + j, workingData + idx * 8 + j * 8);
                        sleepMilliseconds(15.0f);
                    }
                }
            }
            D_807467C4 = 0;
        }
    }
}
