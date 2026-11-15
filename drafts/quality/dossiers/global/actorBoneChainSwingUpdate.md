# actorBoneChainSwingUpdate (global, src/global/9CE20.c)

## Sites

global:80698120:dead-if:5f92e4 dead-if (fixed 2026-11-15): an early (init-block, bb 4) use of the constant 0x50 stretched the 0x50 constant web over bb 4..29 (split 363/414, adjsave -0.33), so uopt left it uncoloured and ugen emits `li t4,80` inside the queue loop (0x334). Without it the web is the loop only (adjsave 5.0): `li a1,80` is hoisted to the preheader, the `gActorGlobalState` base moves a1 -> a2, and on the early-continue base `data` moves to callee-saved s0. Fixed by the switch-shaped queue body below.

global:80698120:dead-if:04e08b dead-if (fixed 2026-11-15): the dead `volumeTriggerQueueCount == 0` test only added a block to the `(int)volumeTriggerQueueCount` web (ucvt{776}), lowering its adjsave from 11.0 to 7.67 so `i` (9.8) is coloured first (v1; count in a0; t2..t4 ring). An early continue in the loop body gives the same (Q0773, 7.33).

Final queue loop body (both sites gone, fdiff 0): `p = gActorGlobalState.volumeTriggerQueueId[i]; switch (*p) { case 0: data->sinkTimer = 0x50; break; default: break; }`. The explicit empty `default: break;` is required (without it full 261).

## Attempts

2026-11-14 Rev20A HackactorBoneChainSwingUpdate openai-codex/gpt-5.6-sol: removed 5f92e4 alone; uopt trace plus the stock 119-body variants scan found no match (best baseline full mismatch 149).

2026-11-14 Rev20A HackactorBoneChainSwingUpdate openai-codex/gpt-5.6-sol: removed 04e08b alone; stock variants found no match; 7,583 as1 schedule edits improved 44 candidates but none matched (baseline full 274, best 266).

2026-11-14 Rev20A HackactorBoneChainSwingUpdate openai-codex/gpt-5.6-sol: tried a named `ActorGlobalState *` in both available pad declaration slots. It restores code before the queue but loads the count into `t9` at 0x30c and adds `move a0,a1` at 0x310.

2026-11-14 Rev20A HackactorBoneChainSwingUpdate openai-codex/gpt-5.6-sol: removed both sites together, tried a named repeated `Actor *`, and tried initializing `dir` through a default switch case. Coupled removal changes text from 3920 to 3824 bytes; the actor pointer grows it to 3984; the default keeps 3920 but increases mismatches. Restored both original tagged sites.

2026-11-15 HackactorBoneChainSwingUpdate2 anthropic/claude-opus-5-5:high: 04e08b loop forms (variants try): while 274; `i = 0; if (n > 0) do..while` 274; guarded do-while with `i = 0` inside the guard 42/44 (registers right, no post-loop `move v1,zero`); `if (n) for (...)` 6 and `i = 0; if (n > 0) for (; ...)` 2 (registers identical, one extra guard branch); separate s16 index for the queue loop 50 (loses the hoisted node-loop `i = 0`); compound dead tests (`n == 0x50` before the loop) fix 04e08b's role but not 5f92e4's (149). Early continue in the loop body: full 0 -> 04e08b fixed.

2026-11-15 HackactorBoneChainSwingUpdate2 anthropic/claude-opus-5-5:high: 5f92e4 on the early-continue base: removal full 369 (data -> s0); stock 118-body variants scan no improvement; store-constant spellings (0x50U, (u8)0x50, 80.0f, 0x50L) 369; continue with an inline queue read 361. 900 s permuter (-j 2, base 7361) found best=0 by inserting `if (data) {}` before the store (a steer); translated into ordinary C as a one-case switch with an explicit empty default (0); other shapes: if/else 149, switch without default 261, switch on the inline element read 152. Both sites fixed.

## Untried ideas

None (no sites left).

## Evidence

Target queue loop: `lbu a0,596(a1)` at 0x30c, `move v1,zero` 0x310, `blez a0` 0x314, element through `t2`/`v0` at 0x31c/0x320, `li t4,80` at 0x334 (before `bnezl t3`), `sb t4,22(t1)` 0x340, count reload `lbu a0,596(a1)` 0x344, post-loop `move v1,zero` at 0x354 (the node loop's `i = 0`, then spilled to 118(sp) around calls, so the queue and node loops share `i`).

uopt -zdbug:5 (private copy): `{1250|0} ucvt{776}` (the int-converted count) adjsave 7.67 with the dead test, 7.33 with the early continue, 11.0 with neither; `i` ({912|0}, -10vreg) 9.8. Constant `{80|0}`: with 5f92e4 ranges 363 [bb 4..8,11] and 414 [bb 9..29] at -0.33 (uncoloured); without it one range [bb 24..27] at 5.0 coloured to uopt reg 4 (a1).
