# audioThreadInit (global, src/global/6710.c)
## Sites
global:80601A10:noop-arith:442abf noop-arith: `(i ^ 0) < 39` kept the DMA loop counter i in $s2 (move s2,zero 0xf4; sltiu at,s2,0x27 0x124) instead of uopt LFTR to bne s0,s3 against D_8076FE68+0x320. FIXED 2026-11-17 (removed).
global:80601A10:dead-if:67a7aa dead-if: `if (taskConfig != 0) {}` in the DMA loop put &D_8076FE68[i] in $s1 and i in $s2 (without it, with ^ 0 kept: i=s1, &D[i]=s2). FIXED 2026-11-17 (removed).
## Attempts
2026-11-10 round 10 Rev10F opus:xhigh: diagnose both sites (LFTR without ^ 0; dead test adds uneq/ucg1 cands and 2 blocks), permuter both removed -> best (i + 1) <= 39 + if (1) {} (nohit)
2026-11-12 round 19 Rev19B/Perm19 opus:low: uopt_trace diagnose (live ranges 68/70); permuter zeros only re-add ^ 0 or a do {} while (0) wrapper (nohit)
2026-11-12 round 33 CleanGlobal6710 opus:low: uopt_trace uxor{879,0} node feeds ules{7,39} (nohit)
2026-11-17 2026-11-17: cleanup CleanaudioThreadInit CleanaudioThreadInit opus: SDK amCreateAudioMgr shape, ACMD loop as `for (i = 0; i < 2; i++) D_8076D4D0.cmdBuffers[i] = ...` on the shared u32 i (replacing the cmdBuf pointer walk), `u32 i;` declared before synConfig, plain `i < 39`, no dead test -> fdiff 0, both sites fixed
2026-11-17 same unit, measured on the way (variants.py try, full score): plain i < 39 = 62; s32 i with (u32)i, 39U or sizeof(D_8076FE68)/sizeof(D_8076FE68[0]) - 1 = 62; while / do-while forms = 64; i <= 38, 39 > i, i != 39 = 62; i + 1 < 40 = 22 (8 with the dead test); pointer IV node++ = 101; ^0 kept without dead test = 16; ACMD loop on i but synConfig first = 2 (sp+0x48); ACMD loop on separate j = 64; ACMD loop on i with post-loop D_8076FE68[39] = 114
2026-11-17 same unit: permuter 900 s -j 2, hack-free weights, from the all-removed body (cmdBuf walk kept) -> base 1668, best 241 ((i + 1) <= 39 + dead if (!i) {} + alias local); all 594 outputs keep the cmdBuf walk (nohit)
2026-11-17 same unit: SDK alHeapAlloc(hp, n, size) macro for the five alHeapDBAlloc(NULL, 0, ...) calls and cmdCount * sizeof(Acmd) -> fdiff 0 (readability, kept)
## Untried ideas
none left for these sites (both fixed).
AudioDmaNode as { ALLink node; ... } would drop the two (ALLink *) casts in alLink, but audioDma* functions use ->next/->prev (file-wide polish item, not a hack)
## Evidence
target 0xf4 move s2,zero; 0x120 addiu s2,s2,1; 0x124 sltiu at,s2,0x27; 0x128/0x12c addiu s1/s0 += 0x14; 0x134 sw v0,-4(s1); 0x154 sw v0,0x10(s1) (post-loop D_8076FE68[i].ptr via the &D[i] temp)
target ACMD loop 0x158-0x194: s0 walks D_8076D4D0, s1 = D_8076D4D0+8, sltu at,s0,s1 (LFTR with < kept: Q1224, next loop on the same i); tasks loop 0x1a0-0x210: bne s0,s2 (last loop on i, EQ_INEQ applies)
uopt trace (zdbug 6): plain body prints EQ_INEQ at BB 4 and BB 14; fixed body only BB 14; fixed body has one counter {1392} M -4vreg in ules{i,39}, ules{i,2}, ules{i,3}
frame: synConfig at sp+0x44 (0x50 addiu v0,sp,0x44; 0x9c addiu t4,sp,0x150) needs i as the first declared local
uopt keeps ^0, <<0, >>0 on the IV (no code, LFTR blocked); folds |0, +0, &0xFFFFFFFF and same-width casts (LFTR proceeds)
