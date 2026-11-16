# actorBoneChainSwingUpdate (global, src/global/9CE20.c)

## Sites

global:80698120:dead-if:5f92e4 dead-if (fixed 2026-11-15, became b0cf60): an early (init-block, bb 4) use of the constant 0x50 stretched the 0x50 constant web over bb 4..29 (split 363/414, adjsave -0.33), so uopt left it uncoloured and ugen emits `li t4,80` inside the queue loop (0x334). Without it the web is the loop only (adjsave 5.0): `li a1,80` is hoisted to the preheader, the `gActorGlobalState` base moves a1 -> a2, and on the early-continue base `data` moves to callee-saved s0.

global:80698120:dead-if:04e08b dead-if (fixed 2026-11-15): the dead `volumeTriggerQueueCount == 0` test only added a block to the `(int)volumeTriggerQueueCount` web (ucvt{776}), lowering its adjsave from 11.0 to 7.67 so `i` (9.8) is coloured first (v1; count in a0; t2..t4 ring). An early continue in the loop body gives the same (Q0773, 7.33).

global:80698120:other:b0cf60 other (OPEN, tagged FAKE by the lead at merge 6ea097ac): `switch (*p) { case 0: data->sinkTimer = 0x50; break; default: break; }`. It supplies two separate CFG conditions (2026-11-15, HackactorBoneChainSwingUpdate3): (a) the non-store edge from the loop head (bb 24) passes through a block (the default arm). That adds a block to the count web ucvt{290} (default blocks [23..24] -> [23..24,27], adjsave 11.0 -> 7.33), so `i` colours to v1 before the count (a0). (b) An empty block sits between the head test and the store block (the jump to the case label). Then uopt makes no `{80|0}` candidate, and ugen emits `li t4,80` in the loop at 0x334 instead of hoisting a coloured `li a1,80` to the preheader. Without default: (a) fails (261). Early continue only: (b) fails (369). Plain `if`: both fail (378).

global:80698120:other:ad82de other (copy-only, pre-existing untagged, tagged 2026-11-15): `data->phase = 0.f;`. The f32 literal spelling is its own zero constant (Q0473), giving `mtc1 zero,$f16` at 0x5c.

global:80698120:other:3303bc other (copy-only, pre-existing untagged, tagged 2026-11-15): `data->bobPhase = 0.000f;`. This is the fourth distinct zero constant, giving `mtc1 zero,$f4` at 0x78.

Removed 2026-11-15 (untagged, no key): `data->nodeAngle = 0.00f;` -> `0.0` (the folded double literal is the natural second zero class).

## Attempts

2026-11-14 Rev20A HackactorBoneChainSwingUpdate openai-codex/gpt-5.6-sol: removed 5f92e4 alone; uopt trace plus the stock 119-body variants scan found no match (best baseline full mismatch 149).

2026-11-14 Rev20A HackactorBoneChainSwingUpdate openai-codex/gpt-5.6-sol: removed 04e08b alone; stock variants found no match; 7,583 as1 schedule edits improved 44 candidates but none matched (baseline full 274, best 266).

2026-11-14 Rev20A HackactorBoneChainSwingUpdate openai-codex/gpt-5.6-sol: tried a named `ActorGlobalState *` in both available pad declaration slots. It restores code before the queue but loads the count into `t9` at 0x30c and adds `move a0,a1` at 0x310.

2026-11-14 Rev20A HackactorBoneChainSwingUpdate openai-codex/gpt-5.6-sol: removed both sites together, tried a named repeated `Actor *`, and tried initializing `dir` through a default switch case. Coupled removal changes text from 3920 to 3824 bytes; the actor pointer grows it to 3984; the default keeps 3920 but increases mismatches. Restored both original tagged sites.

2026-11-15 HackactorBoneChainSwingUpdate2 anthropic/claude-opus-5-5:high: 04e08b loop forms (variants try): while 274; `i = 0; if (n > 0) do..while` 274; guarded do-while with `i = 0` inside the guard 42/44 (registers right, no post-loop `move v1,zero`); `if (n) for (...)` 6 and `i = 0; if (n > 0) for (; ...)` 2 (registers identical, one extra guard branch); separate s16 index for the queue loop 50 (loses the hoisted node-loop `i = 0`); compound dead tests (`n == 0x50` before the loop) fix 04e08b's role but not 5f92e4's (149). Early continue in the loop body: full 0 -> 04e08b fixed.

2026-11-15 HackactorBoneChainSwingUpdate2 anthropic/claude-opus-5-5:high: 5f92e4 on the early-continue base: removal full 369 (data -> s0); stock 118-body variants scan no improvement; store-constant spellings (0x50U, (u8)0x50, 80.0f, 0x50L) 369; continue with an inline queue read 361. 900 s permuter (-j 2, base 7361) found best=0 by inserting `if (data) {}` before the store (a steer); translated into ordinary C as a one-case switch with an explicit empty default (0); other shapes: if/else 149, switch without default 261, switch on the inline element read 152. Both sites fixed.

2026-11-15 HackactorBoneChainSwingUpdate3 anthropic/claude-opus-5-5:high: b0cf60 (variants try, fdiff on the private copy): plain `if` 378; early continue then store 369; store then `continue` 369; braced store 369; `while` with `i++` in the index 369; `p` assigned in the continue test 369; if/else-continue and continue/else-store 149. Empty-block position test on the early-continue base: `if (1) {}`, `if (i) {}` or `if (data) {}` between the continue test and the store give 0; at the body top or after the store 144; before or after the loop 149. Q0908 unrelated-local guards in that position: nodeCount 19, player 141, p 274 (each extends a range into the loop). On the plain body: `if (nodeCount) {}` before or after the if 167; `if (data|player|nodeCount) {}` inside the if 274/285/290. Switch spellings: default first 0; `case 0: break; default: continue;` with the store after the switch 0; `default: continue; case 0: break;` 0; `case 0: store; break; default: continue;` 0; `default: continue; case 0: store;` 0; `case 0: store;` falling into `default: break;` 0; `case 0: store; continue;` without default 0. variants scan (118 bodies) on the plain (378) and early-continue (369) bodies: no improvement. uopt -zdbug:5 flow graphs and active-range dumps for plain, early-continue, early-continue + `if (1) {}`, switch, and switch without default.

2026-11-15 HackactorBoneChainSwingUpdate3 anthropic/claude-opus-5-5:high: init zero literals (review). Respelling all three of `0.00f`/`0.f`/`0.000f` as `0.0f` changes text from 3920 to 3904 bytes (each alone 263). All 27 {0.0f,0.0,0} assignments of nodeAngle/phase/bobPhase are >= 249 (`0.0` and `0` behave the same). All 32 {0.0f,0.0} assignments of the five init zeros are >= 249. Any one of the three as `0.0` or `0` gives 0, so nodeAngle -> `0.0` was kept (fdiff 0). On that base phase/bobPhase as 0.0f 263, as 0.0 or 0 257/258, and bobPhase as `0.0F` 263. `.0f` gives 0 but is another spelling.

## Untried ideas

A ruling on `switch (*p) { case 0: break; default: continue; } data->sinkTimer = 0x50;` (0; no empty or no-op arm: every arm changes control flow). It is still a one-case switch, so it was not swapped in for the tagged form (HackactorBoneChainSwingUpdate3).

A non-switch C construct that puts a block between the head test and the store with no dead code: none found. Candidates would be a real semantic second test that the target folds, but the target has a single `bnezl t3` at 0x338.

Zero literals: a natural fourth zero class (for example a zero produced by an expression rather than a literal). Only the `0.0f` and folded `0.0`/`0` classes are known (Q0438, Q0473).

## Evidence

Target queue loop: `lbu a0,596(a1)` at 0x30c, `move v1,zero` 0x310, `blez a0` 0x314, element through `t2`/`v0` at 0x31c/0x320, `li t4,80` at 0x334 (before `bnezl t3`), `sb t4,22(t1)` 0x340, count reload `lbu a0,596(a1)` 0x344, post-loop `move v1,zero` at 0x354 (the node loop's `i = 0`, then spilled to 118(sp) around calls, so the queue and node loops share `i`).

uopt -zdbug:5 (private copy, 2026-11-15 HackactorBoneChainSwingUpdate3; flow-graph bb numbers): loop head bb 24 (loopfirstbb, depth 2), latch 26..29 by variant. Store-path/non-store-path blocks: plain 25 / direct edge; early continue 26 / 25; switch 25,26 / 27; switch without default 25,26 / direct edge; early continue + `if (1) {}` 26,27,28 / 25. Count web ucvt{290}: adjsave 11.0 (plain, no default) vs 7.33 (continue, switch). `i` {912}: 9.8 (plain, continue) vs 9.1875 (switch, continue + block). `{80|0}` candidate: present in plain (active 373, bb 24 needreglod + bb 25, adjsave 5.0) and early continue (412, bb 24 + bb 26); absent in switch, switch without default and continue + block.

Init zeros: target `mtc1 zero,$f4` 0x40 (swingAmplitude, `swc1 $f4,0(t1)` 0x4c), `mtc1 zero,$f10` 0x48 (nodeAngle 16(t1)), `mtc1 zero,$f16` 0x5c (phase 12(t1)), `mtc1 zero,$f4` 0x78 (bobPhase 32(t1)), `mtc1 zero,$f8` 0xc4 (spinAngle 24(t1), after randomNonNegative).

uopt -zdbug:5 (private copy, 2026-11-15 HackactorBoneChainSwingUpdate2): `{1250|0} ucvt{776}` (the int-converted count) adjsave 7.67 with the dead test, 7.33 with the early continue, 11.0 with neither; `i` ({912|0}, -10vreg) 9.8. Constant `{80|0}`: with 5f92e4 ranges 363 [bb 4..8,11] and 414 [bb 9..29] at -0.33 (uncoloured); without it one range [bb 24..27] at 5.0 coloured to uopt reg 4 (a1).
