# tagBarrelActorUpdate (global, src/global/80150.c)
## Sites
global:806809F0:other:71b822 other: `default: break;` (empty) in the trigger-queue loop's `switch (*triggerId) { case 2: sub->riseTimer = 0x8C; break; ... }`. It gives the not-2 edge its own block with its own source line, which is what lets uopt drop the loop counter (LFTR with a reloaded bound, Q0452) and what puts a `.loc` barrier between the bound recompute and the pointer increment at the 0x5928 latch. Kept (diagnose nohit): no measured natural form builds that block.
## Attempts
2026-11-18 2026-11-18: cleanup CleantagBarrelActorUpdate CleantagBarrelActorUpdate anthropic/claude-opus-5-5 (scored with variants.py try):
- no default (switch for loop, while + i++, do-while under a count test, for header split over two lines, case without break): 294 each (counter kept: move a2,zero / addiu a2,a2,1 / slt at,a2,a0; no v1 bound, reloc 4)
- plain `if (*triggerId == 2)` (for or while): 301
- one-case switch whose case ends in `continue` (the 9CE20 actorBoneChainSwingUpdate form): 4; also 4 with braces around the case, all on one line, or with the for header split. as1 order only: `addu v1,t5,t9` before the bne and `addiu v0,v0,4` in its delay slot (target: addiu at 0x58f8, addu in the slot 0x5900). In ugen's listing the switch-end block takes the `for` line (416), so no `.loc` barrier separates the bound recompute from the increment; the default's own `break` line (423) is that barrier. as1probe scan over records 280-320: only noop/delete/swap edits that C cannot emit lower it (2).
- the base written on one line: 4 (same `.loc` cause)
- `if (== 2) { store; continue; }` 250, `if (!= 2) continue;` guard 254, `else continue` 254, empty `else` 247, `default:` first 247, `default: continue;` 33
- switch on `*gActorGlobalState.volumeTriggerQueueId[i]` without the triggerId local: 250 with the default, 314 without
- variants scan (swap/float/width/declswap) of the no-default copy and of the case-continue copy: nothing below 294 / 4
- permuter (hack-free weights, -j 2, 900 s) from the no-default body: base 3443 (permuter base 3360), best 2205 = a dead triple guard `if ((!sub) && (!sub) && (!sub)) {}` inside the loop body after the switch (Q0548 block split: the same extra not-2 block the empty default gives), no zero
- review: `scaleFactor` was reused in case 10 for the remaining-growth fraction `(0.15 - scaleX) / 0.13`; a block-scoped `f32 growthLeft` matches (fdiff 0) and 71b822 re-measures the same on the new body (294/301/4)
2026-11-19 2026-11-18c: cleanup CleanthrowableBarrelUpdateb CleanthrowableBarrelUpdateb anthropic/claude-opus-5-5 (variants.py try on the base a3d0ef71 body; diagnose re-run after the stale rung):
- ORIG check (director ruling 2026-11-18b, empty default): the not-2 edge is `bne t1,t7,0x5928` at 0x58fc, straight to the latch 0x5928 (the join); no bound check, no gap entries, no block of its own (the `sll t5,a0,2` 0x58f4 / `addu v1,t5,t9` 0x5900 bound recompute sits before and in the bne slot, executed on both edges). Default at the join -> stays FAKE (diagnose nohit).
- s16 value local `trigger = *gActorGlobalState.volumeTriggerQueueId[i]` (selector local at its use) with the one-case switch and no default: 309; with `if (trigger == 2)`: 313
- case 2 without its own break, falling into `default: break;`: 249
2026-11-24 2026-11-24b: continue ReMeasureB18H anthropic/claude-opus-5-5 (variants.py try at 127a3fd5, after the cb17735e EffectGridAsset extern retype; the loop reads no sprite):
- re-run: no default 294, plain if 301, case-ends-in-continue 4, case 2 falling into `default: break;` 249 (unchanged)
- Q1616/Q1620 pointer-walk loop `s16 **ids` from `volumeTriggerQueueId` to `&volumeTriggerQueueId[count]` (replacing the triggerId local): with if 289, with the one-case switch 347; the entry test becomes sltu/beqz on the pointers instead of `blez a0` (0x58d4), `li a0,140` is hoisted, and the bound is recomputed only after the case-2 store, never on the not-2 edge
## Untried ideas
none that give the not-2 edge a block with its own line without an empty arm: the target performs no work there except the bound recompute.
## Evidence
0x58c8-0x58e0: lbu a0,596 (count), li t0,1, blez a0,0x5934, la v0 gActorGlobalState, li t1,2.
0x58e8-0x5900 (loop head): la t9 gActorGlobalState; lh t7,0(v1) (*triggerId); sll t5,a0,2 and addu v1,t5,t9 (default arm's bound from the old count, hoisted by as1 above and into the slot of bne t1,t7,0x5928 at 0x58fc); addiu v0,v0,4 at 0x58f8.
0x5904-0x5924 (case 2): li t2,140; sb t2,14(s2) (riseTimer); lbu a0,596 reload (the u8 store may alias the count); la t4; sll t3,a0,2; b 0x5928 at 0x5920 with addu v1,t3,t4 in the slot.
0x5928-0x5930 (latch): sltu at,v0,v1; bnezl at,0x58e8; lw v1,632(v0) (next triggerId reuses v1).
