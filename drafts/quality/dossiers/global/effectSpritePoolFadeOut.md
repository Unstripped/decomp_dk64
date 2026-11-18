# effectSpritePoolFadeOut (global, src/global/114270.c)
## Sites
global:807122B4:other:da39a3 other: comment-only tag on the missing final return. On the pool->count == 0 && D_807FDA1C == 6 path the target writes no $v0 after lw v0,%lo(D_807550E0)(v0) at 0x2d4c, so it returns pool. FIXED 2026-11-17 as `// ORIG:` (offsets below); no hack site left.
## Attempts
2026-11-11 round 14 CleanGlobal114270 opus-5-5:low: return 1 (uopt identical, ugen +li v0,1 +b, +8 bytes); permute from return 1 -> best 0 only by deleting it -> nohit
2026-11-11 round 16 Rev16K opus-5-5:low: return 0 (+b 0x2f08 +move v0,zero, score 205); permute best 0 moved return 1 after the if (branch-target false zero) -> nohit
2026-11-12 round 20 Rev20C opus-5-5:low: final return 0 permute: best 0 only made it unreachable -> nohit
2026-11-13 round 38 CleanGlobal114270 opus-5-5:xhigh: trace6 of return 1 (pool M-8vreg cand 0 -> uopt 1 $v0, i M-2vreg cand 23 -> uopt 14 $s0, colouring identical); permute from return 1 -> nohit
2026-11-17 2026-11-17: cleanup CleaneffectSpritePoolFadeOut CleaneffectSpritePoolFadeOut opus-5-5: variants try return (s32)pool 13 (pool cand 0 coloured uopt 2 $v1, +move v0,v1 at 0x2f04, +b 0x2f08), return pool != NULL 13, return 2 2, guard clause if (D_807FDA1C == 6) return (s32)pool 14 / pool != NULL 14 / 1 3 / 0 3; return 1 hoisted after the if: variants full=0 but fdiff 1 (beq t0,at at 0x2e64 -> 0x2efc instead of 0x2f00); variants scan of the return (s32)pool body: 9 variants, no zero -> FAKE retagged `// ORIG:` with offsets, fdiff 0, uninit 0, cwarn 0 -> 0
## Untried ideas
none for the site (resolved as ORIG). Permuter from the return (s32)pool base not run: every earlier permuter zero only deleted or displaced the added return (rounds 14/16/20/38).
## Evidence
0x2d48/0x2d4c lui/lw v0 = D_807550E0 (pool in $v0); 0x2d68 lhu t6,0(v0); 0x2d74 beqz t6,0x2e58.
0x2e58 lbu t0,0(s4) (D_807FDA1C); 0x2e5c li at,6; 0x2e64 beq t0,at,0x2f00 (delay slot addiu v1 = &D_8077058C): no $v0 write, no call on this path.
0x2efc li v0,1 (return 1 of the != 6 arm) falls into the epilogue at 0x2f00 (lw ra,0x2c(sp)); 0x2f18 jr ra; frame 0x30, s0-s4 saved.
0x2e50 b 0x2f00 / 0x2e54 move v0,zero: the return 0 arm.
Caller 8F4B0.c:452 tests `effectSpritePoolFadeOut() != 0`, so the leftover non-null pool reads as true on the fall-through path.
cfe warnings for 114270.c: 0 (cwarn list), before and after.
