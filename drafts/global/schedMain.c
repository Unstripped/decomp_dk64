// schedMain (src/global/131B0.c): UNPARKED 2026-11-02: park was 224 insns vs target 220 (count-inexact parks stay drafts); W3SchedB R5: unchanged stage 6 (text 11 = 9 reloc-noise + bnezl). New as1 fact (.scratch/W3SchedB/sm_probe.py): setting the s0 bit (0x8000 of the first mask word) in ANY '.livereg' record after cond2 gives exactly the expected bnezl (text only the IO-name reloc noise left, 21/9), i.e. as1 decides the 'move s0,zero' delay-slot fill by liveness of s0 at the branch target taken from '.livereg' masks (masks hold the call's argument regs; s0 never occurs naturally). Extra-branch-ref route: inserting a copy of the 2nd cond2 branch retargeted to the inner loop head right before/after the cond2 branches gives only 22/10. Dead 'if (i)' tests at every statement boundary: unchanged 23/11 (uopt drops the use). || PREVIOUS: schedMain (src/global/131B0.c): stage 6: ONLY real diff: cond2 'bnez at; move s0,zero' vs expected 'bnezl at; slti at,v0,-299; move s0,zero' (12 DPC_*/SP_* reloc lines are the expected object's undefined_syms IO names: reloc-only noise). W2Layout: one extra branch REF to the inner loop-head label in ugen.out gives exactly the expected bnezl (retargeting any earlier branch to it works; inserting a jump-to-next right before the head does not: W3Label sm_exp2). W3Label 2026-11-01 tried without effect: loop bound variable (n2=2), while/guard forms, continue/break tails, do-while, wrappers (do{}while(0), {}, if(1), for(;;)) around the loop and around the whole cond block, ugen-record injection of every record kind. cfe emits the for as 'lab head; body; lab cont; tjp head' (no entry ujp), so no C spelling found that leaves a 2nd ref. as1 delay-slot result is reproducible from ugen.out only. || PREVIOUS NOTES: stage 6: ONLY real diff: cond2 'bnez at; move s0,zero' vs expected 'bnezl at; slti at,v0,-299; move s0,zero' (the 12 DPC_*/SP_* reloc lines are the expected object using undefined_syms names for IO addresses: reloc-only noise). W2Layout 2026-10-31: reproduced the C pipeline by hand (cfe|uopt|ugen|as1 in /opt/ido5.3; ugen.out = 16-byte records) and perturbed ugen's binary: as1 emits EXACTLY the expected bnezl (rest identical modulo DPC relocs) when the inner for-loop head label (the $34 label right after 'move s0,zero') gets ONE MORE branch reference (tested by retargeting the guard 'bgt D_8074682C,0' to it); label renumbering, .loc deletion, sign flips, every other single-record delete/bit-flip do nothing. So the original has an extra pred on the inner loop head that as1 later removes/folds; C-level goto-into-loop, unreachable goto, while(1)/do-while/for(;;)/++i!=2 loop spellings are all normalised by uopt (no change). Unfound: a C construct that leaves a 2nd ref to the loop head in ugen's stream. || PREVIOUS NOTES: stage 6: ONLY diff: cond2 of the range check emits 'bnez at; move s0,zero' (as1 pulls i=0 into the delay slot) vs expected 'bnezl at; slti at,v0,-299; move s0,zero'. Retried 2026-10-31 (Sched): 3800 single dead-stmt insertions (15 syms x 3-4 forms x all points, also with each 1-2 of the 4 existing FAKEs removed): none gives bnezl; cond2 spellings (6), loop forms (for/do-while/pre-inc/nested if), i type (u8/s16/u32/s64), line layout (same-line, split), callee return types (faultFontInit/faultPrintf s32/unproto) all unchanged; bnezl appears only when i is read after the loop (if (i) {}, flag = i), which adds 'lw s0,96(sp)' uninit load + pointerized D_8074682C so is not the target; as1 given the cc -S text reproduces bnezl (a .s round trip) so the C-path decision depends on ugen binary input, not .loc/.livereg || Leftovers5 Sched 2026-11-01 (unchanged park, 11 text diff): untried-before sweeps all NO effect: nested ifs/negated/swapped cond2 spellings, loop '!= 2'/'<= 1'/countdown, goto-head loops + dead 'goto head' before/after, 'i = i;' / 'x = x;' .loc sweep for every local at every point, dead tests of i/flag at every point (4 forms), function-level 'i = 0;' + 'if (i) {}' after loop (gives bnez still), as1-level bit-flips of every 0x30/0x31/0x35 ugen record word (no bnezl). cond1 and cond2 both branch to label 0x22 (the slti -0x12B); bnezl is as1's target-copy of that slti, chosen only when as1 deems 'or s0,zero,zero' unsafe to hoist (needs s0 live at the target or an extra ref on the loop head).
void schedMain(void *arg0) {
    u32 msg;
    s32 i;
    s32 flag;
    s32 pad1;
    int new_var;
    u32 cnt;
    s32 pad3;
    s32 pad4;

    for (;;) {
        osRecvMesg(arg0, (OSMesg *)&msg, OS_MESG_BLOCK);
        if (D_807F0560 == 0) {}  // FAKE: deadsweep dead statement (steers uopt; replace with natural C)
        if (D_807563B4 != 0) {
            if (D_80746830 == 0) {
                D_8074682C--;
            }
            if (D_80744470 && D_80744470) {}  // FAKE: deadsweep dead statement (steers uopt; replace with natural C)
            if (D_807F0518 && D_807F0518) {}  // FAKE: deadsweep dead statement (steers uopt; replace with natural C)
            if (D_8074682C <= 0) {
                D_807F0518[0]++;
                new_var = D_807F0518[0];
                osViSwapBuffer((void *)D_80744470[(new_var >> 5) & 1]);
                if (D_80746848 && D_80746848) {}  // FAKE: deadsweep dead statement (steers uopt; replace with natural C)
                osViBlack(0);
                D_807F0518[0]++;
                if (D_8074682C < -0x9F && D_8074682C >= -0x100) {
                    for (i = 0; i < 2; i++) {
                        faultFontInit(D_80744470[i & 1], 2, 2);
                        faultPrintf("CURRENT=%x\n", IO_READ(DPC_CURRENT_REG));
                        faultPrintf("START=%x\n", IO_READ(DPC_START_REG));
                        faultPrintf("END=%x\n", IO_READ(DPC_END_REG));
                        faultPrintf("DPSTAT=%x\n", IO_READ(DPC_STATUS_REG));
                        faultPrintf("SPSTAT=%x\n", IO_READ(SP_STATUS_REG));
                        faultPrintf("MAIN-PC=%x\n", D_8076154C);
                    }
                }
                if (D_8074682C < -0x12B) {
                    flag = 0;
                    if ((D_807F0518[0] & 0x1F) == 0) {
                        flag = 1;
                    }
                    if (flag) {
                        if (D_80746848 == 0) {
                            flag = 0;
                            D_80746848 = 1;
                        }
                    }
                    schedDlDebugDump(D_80746844, flag);
                    D_80746844 = 0;
                    D_8074682C = -0x12C;
                }
                osWritebackDCacheAll();
            }
        }
        switch (msg) {
        case 0x29A:
            cnt = D_807F0560 + 1;
            D_807F0560 = cnt;
            if (cnt % 0x1E0 == 0) {
                D_807F04C8 = D_807F04D0;
                D_807F04D8 = D_807F04DC;
            }
            schedHandleRetrace(arg0);
            break;
        case 0x29E:
            schedStartAudioOrYield(arg0);
            break;
        case 0x29B:
            schedHandleRSP(arg0);
            break;
        case 0x29C:
            schedHandleRDP(arg0);
            break;
        case 0x29F:
            if (osSendMesg(D_807F0540.mq, D_807F0540.msg, OS_MESG_BLOCK) == -1) {
            }
            break;
        case 0x2A0:
        case 0x3F2:
            break;
        default:
            schedHandleNewTask(arg0, (TaskNode *)msg);
            break;
        }
    }
}
