# pathPlaybackAdvance (global, src/global/127B00.c)
## Sites
global:80723484:dead-if:6354a6 dead-if: REMOVED. Its folded `pb == -4` test (const web 203) was the 22nd neighbour of pb web 13 and the -1 web 201 (both then constrained -> v0/v1), and it split the pb copy (`move v0,a1`, +0x24) from the isLooping load (`lbu a1,22(a1)`, +0x34).
global:80723484:dead-if:0106d1 dead-if (block split): `if (1) {}`, `if (pb) {}`, `if (quot) {}`, `if (overshoot) {}` at the site all match. It puts the pointIndex reread after the case-0 store in a join block, so the remainder stays a t8 ring temp (`mfhi t8`, +0x3EC; `sw t8`, +0x3F0) and is copied into the dir-1 pointIndex ilod web a3 (`move a3,t8`, +0x418). Without it the urem becomes a v1 candidate (`mfhi v1; sw v1`), score 5.
global:80723484:dead-if:f5ff39 dead-if (availability): only `if (tq) {}` at the site matches; `if (1)`/`if (pb)`/`if (quot)` score 2. The extra use makes `quot + 1` a CSE candidate coloured v1 (`addiu v1,a2,1`, +0x3DC; `beqz v1`, +0x430). Without it: `addiu t5,a2,1; beqz t5`, score 2.
## Attempts
2026-11-10 round 9 CleanGlobal127B00 anthropic/claude-opus-5-5:low: removal/cond/classify/permute; permute dropped the e96ad4/5bbfeb pair with repeated casts (Q0608).
2026-11-14 HackpathPlaybackAdvance openai-codex/gpt-5.6-sol: removals r1=299 r2=5 r3=93 r123=301; 511 path->count rewrites, 32 rereads, named pointIndex pointer -> nohit.
2026-11-16 HackpathPlaybackAdvance2 anthropic/claude-opus-5-5:high: dir-1 `limit` (reused for -pb->pointIndex) renamed `overshoot` -> g1 removal 299 -> 9 (new candidate interferes with pb and -1); plus `(pb = gPathPlaybacks[slot])->active != 0` (pb copy in the active-test block) -> g1 removal fdiff 0 (FIXED). Other head spellings: `(pb = gPathPlaybacks[slot]) != NULL && pb->active` 199, `(pb = ...) != NULL && gPathPlaybacks[slot]->active` 2, nested `if (slot != -1) { pb = ...` not better.
2026-11-16 HackpathPlaybackAdvance2: dir-0 `limit` reassigned as the divisor renamed `span` -> fdiff 0 with all steers; g3 removal 93 -> 2 (span keeps pb constrained without the tq web).
2026-11-16 HackpathPlaybackAdvance2: g2 natural joins (break/return on zero, assignment in the test, empty else, ternary/self-store, if-chain, swapped cases, named index temp before/after the store, index local from the <0 test) -> 5..30; index temp after the store (Z1) reaches shape 0 but `move a2,v1` vs `move a3,t8`.
2026-11-16 HackpathPlaybackAdvance2: g3 spellings (quot + 1 / 1 + quot / ++quot / quot += 1 / != -1 / > 0, tq u32/s32, tq before the switch / before or used in loopCount) -> 2 (folded to `li at,-1; beq a2,at` or t5). One merged guard (tq hoisted, `if (tq) {}` in case 0) fixes the split but folds case 1 -> 2.
2026-11-16 HackpathPlaybackAdvance2: permuter 900 s on the g2+g3 removal (pre-span copy): base 531, best 10 (aliases pb through new_var2 + pointIndex local): not applied.
## Untried ideas
A real second use of quot + 1 on the case-1 path that emits no code (none found in the asm: v1 is read once at +0x430).
A real join before the case-0 reread that emits no instruction (the target has none besides ugen div traps).
## Evidence
+0x00 `li v1,-1` (web 201) and +0x24 `move v0,a1` (pb web 13): both constrained (degree 22).
+0x34 `lbu a1,22(a1)`: isLooping reuses a1 once the gPathPlaybacks[slot] web 6 is dead (separate block).
+0x3CC `addiu t7,a1,-1` before the loopMode dispatch; +0x3DC `addiu v1,a2,1` in the `beq t0,t1` delay slot; +0x3EC `mfhi t8`; +0x3F0 `sw t8,16(v0)`; +0x418 `move a3,t8`; +0x41C `beqz t8`; +0x430 `beqz v1`.
Related knowledge: Q0397, Q0492, Q0520, Q0601, Q0608, Q0908.
