# actorCollisionRunInteractionTable (global, src/global/7A510.c)
## Sites
- None left. All three FAKEs are removed (see Attempts).
- 6c7f1e (removed 2026-11-15): the `if (1) { found = 0; }` block swapped actorB and the gActorGlobalState base (s0/s1). It is replaced by the target's real chain test, a 2-case `switch (entry->chain) { case 0: case 2: done = 1; break; }`.
- 29a3dd (removed 2026-11-15): the `((s8 *)entry)[5]` read set the bnel operand order. It was respelled as an array field `s8 filter[2]` read as `entry->filter[1]` (lead retag -> 4015de).
- 4015de (removed 2026-11-16): the `s8 filter[2]` array field (only for `bnel t2,t0` at 0x3bc). Replaced by named `s8 phase; s8 event;` fields and an indexed outer loop `for (i = 0; !done; i++)` reading `D_8074ABCC[i].field`.
## Attempts
- 2026-11-14 opus:high (full=):
  - found = 0 placements: 14
  - one-case switch on event: 9/10
  - default-first switch: 22-23
  - break without a flag: 29
  - only the pun removed: 1
- 2026-11-15 HackactorCollisionRunInteractionTable2 anthropic/claude-opus-5-5:high (variants.py try full=):
  - `found = 1;` before `if (event != -1) { found = 0; loop }`, with no else: 3. This fixes s0/s1, but the target's `b`/`nop` after the loop (0x3e4) is missing, and so is bnel.
  - The same form with a switch on event, or with found set in the for-init or in a while loop: 3.
  - Nested `if (j < unk201)` around the loop with the else kept: 2. It fixes s0/s1 but emits a duplicate `blez`.
  - Explicit `if (n) do {} while` loops: 17-20.
  - `s8 args[2]` array field with the hack shape: 0. With the plain shape: 13, the s0/s1 swap only.
  - Plain else shape with `switch (entry->chain) { case 0: case 2: }`: 0 with both the array field and the pun. With `entry->event`: 1, bnel only.
  - With the switch shape, an event local of s8/s32/u8 (CSEd) scored 2-27. A variants scan of the switch shape (25 one-edit variants) stays at 1 or worse.
  - Splitting the outer if (A && B, then phase): 13. A while form of the outer loop: 16. A break on chain == 0: 11.
- 2026-11-16 HackactorCollisionRunInteractionTable3 anthropic/claude-opus-5-5:high (variants.py try full=):
  - Named `s8 phase; s8 event;` fields with the entry pointer: 1 (bnel t0,t2 only).
  - Named fields with an indexed loop `D_8074ABCC[i].f` everywhere (switch on chain kept): 0, fdiff 0 (kept).
  - The indexed loop with `chain == 0 || chain == 2` instead of the switch: 14.
  - variants scan of the indexed body (30 variants): all 0 except `D_8074ABCC[i].event == unk244[j]` (1) and narrower i/j widths (2-44).
## Untried ideas
- None for this function.
## Evidence
- Target: actorB is in `$s0` (`lh a0,90(s0)` at 0x34c, `move a1,s0` at 0x3fc). The gActorGlobalState base is in `$s1` (`lbu t6,512(s1)` at 0x370).
- The table walk is one pointer `$s2` (`lh a2,0(s2)` at 0x340, `addiu s2,s2,16` at 0x434); an index loop over `D_8074ABCC[i]` strength-reduces to the same.
- The loop compare is `bnel t2,t0` at 0x3bc: t2 is `lbu 580(t9)` (unk244[j]), and t0 is the CSE'd `lb t0,5(s2)` (event, also the `andi a3` handler argument at 0x404). cfe emits the subscripted side first; with both sides subscripted (`unk244[j]`, `D_8074ABCC[i].event`) source order decides (Q0860).
- The chain test at 0x408-0x41c is `beqzl v0` / `bnel v0,s6(=2)`. The switch on chain produces this same asm. Its added blocks lower the adjsave of the base constant below actorB, as `if (1)` did (Q0523, Q0895, Q1017).
