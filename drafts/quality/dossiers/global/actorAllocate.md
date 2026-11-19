# actorAllocate (global, src/global/7CA80.c)

## Sites
global:80678050:dead-if:ea1524 dead-if: `if (headerSize) {}` inside the first (size) loop adds one loop-weighted read of
headerSize in its own block, so headerSize (cand 8) out-prioritises totalDataSize (cand 11): headerSize a1, totalDataSize a2
(target `li a1,372` / `move a2,zero` at 0x2fc/0x300, loop 0x310-0x33c). Without it the pair swaps (11 lines, 0x2fc-0x34c).

## Attempts
2026-11-09..2026-11-12 (rounds 2/8/13/16/17/20, opus low/xhigh): uopt_trace (priority swap), statement swap, while/for/++
loop forms (scores only), sweeps (class 2), permuter (old weights: only re-added guard; best 10 reused totalDataSize).
2026-11-17 cleanup CleanactorAllocate anthropic/claude-opus-5-5: exact compute_save per block for both candidates (base vs
removal), loop forms with uopt counts, tie test, post-loop respellings, guard operand/position classification, redundant
`(void **)` cast removed (fdiff 0), (u16) casts measured, K&R vs ANSI definition, hack-free-weights permuter 900 s from the
removal body (base 70, zeros only re-insert steers) and 900 s from the refine-in-place near miss (base 10, best 10),
as1probe scan of the near miss -> see Evidence; site kept (2 diagnose nohit, 2 permute nohit).
2026-11-18c cleanup CleanactorAllocateb anthropic/claude-opus-5-5: fresh uopt -l5/-l6 on the current body (counts unchanged);
definition-order swap (M25) on the tie body -> 12 and on the removal -> 11; u16 `allocSize` local as the heapAlloc argument
-> 10; `heapAlloc(totalDataSize += ...)` -> 14 (tds still a1); `(headerSize += 7)` inside the add -> 79; near-miss mask
casts none / first only / second only / `& ~7` / `(u16)(... & ~7)` -> 69 / 3 / 69 / 72 / 6; variants scan of the removal
(best 11) and near-miss (best 2) copies; as1probe 3-round scan of the near miss (records 2670-2695): only deleting the
sp+36 PRE spill moves (full 1) -> site kept (diagnose nohit).

## Untried ideas
- None left that is natural C: the near-miss fix needs cand 38's PRE unit rooted at `headerSize + 7` (base ugen chain
  `addu $2,$5,7; and $13,$2,65528`) while headerSize keeps a bb4 store, and a bb4 store to headerSize always emits its u16
  narrowing before the mask (see Evidence). A reshape giving totalDataSize one more block (n 5 -> 6) needs a block
  boundary between 0x340 and the `jal heapAlloc` at 0x354, which is straight-line code.
- Optional: a third hack-free permuter run from a new seed (two 900 s runs exist; zeros only re-insert steers).

## Evidence
Block/ref counts (uopt -l5, `- live bb - <bb> <loads> <stores> <argreg>`; compute_save = sum refs x 10^depth / (((n-2)>>2)+2)):
- removal: headerSize bb0 st, bb2 (loop) ld+st, bb4 ld = 1+20+1 = 22, n = 5 (0,2,4 + 1,3) -> /2 = 11.0;
  totalDataSize bb0 st, bb2 ld+st, bb4 ld+st+ld(arg a0) = 1+20+3 = 24 -> 12.0. Colour order 0,14,48,52,11(a1),41,8(a2).
- base (guard): headerSize adds bb2 guard ld (10), n = 7 -> /3: 32/3 = 10.667; totalDataSize 24/3 = 8.0 -> 8 a1, 11 a2.
- So headerSize needs exactly ONE more loop-weighted read (same block: 32/2 = 16 > 12; own block: 32/3 > 24/3) or two
  more freq-1 refs (24/2 tie, lower bit 8 wins). Tie proven by `heapAlloc((u16)(totalDataSize + (u16)(...)))`: both
  11.0, headerSize a1; loop matches, but totalDataSize's post-loop store is gone (CSE temp v0, sum in a0, full=5).
- Loop forms: `while (*types != 0)`, `for (; *types != 0; types++)`, `*types++` in the add: identical counts
  (11.0/12.0), full 11/12. Index loop full 82. `headerSize = (u16)(headerSize + 4)`, `sizeof(void *)`: 11.
- Guard classification: `if (1)`, `if (totalDataSize)`, `if (*types)`, `if (types)` all 11 (= removal): class 2, only a
  headerSize read works; it works anywhere in the loop body (before the add, after `headerSize += 4`, after `types++`: 0).
- Post-loop: `heapAlloc(totalDataSize += ...)`, `heapAlloc(totalDataSize = totalDataSize + (u16)...)`: 14; refine in place
  `headerSize = (headerSize + 7) & 0xFFF8` (live across calls): 90; a u16 aligned-size local: 17 (temps shift 36->32).
- Casts: both `(u16)((headerSize + 7) & 0xFFF8)` make the whole narrowed value the PRE unit (t6, sw 36(sp) at 0x350,
  lw t8 at 0x378); dropping the second CSEs only `headerSize + 7` (v0, full=2); dropping both 70. `(void **)` on
  `&actor->customState` (already void **) is redundant: removed, fdiff 0.
- variants.py scan on the removal copy: 21 variants, best 11 (no width/declswap/swap helps).
- Near miss (hack-free permuter run 1, output-10-1, rewritten): `headerSize += 7; totalDataSize += (u16)(headerSize &
  0xFFF8); ... dataPtr = (u8 *)actor + ((u16)(headerSize & 0xFFF8));` gives headerSize bb4 ld+st+ld = 24/2 = 12.0 =
  totalDataSize 12.0, lower bit 8 wins -> a1/a2 and the whole loop match; full=2: `addiu v0,a1,7` vs target
  `addiu t5,a1,7` at 0x340 (as1 rename, ringfifo: ugen `addu $5,$5,7; and $13,$5,65535; move $5,$13; and $2,$5,65528`).
  Same 2 for `= (u16)(headerSize + 7)`, `& ~7`, `& -8`, `8 - 1`, decl swaps; scan on that copy: best 2; as1probe scan:
  no single record edit reaches 0.
- Permuter outputs that score 0 only re-insert a steer: `if (!headerSize) {}` / `if (headerSize) {}` in the loop, or
  `if (!totalDataSize && !totalDataSize) {}` before the inits (uninitialised two-term dead read lengthening tds's range).
- 2026-11-18c, current body: base guard gives headerSize bb0 st, bb2 (guard block) ld, bb4 ld+st, bb6 ld = 32, n = 7 -> 10.667
  vs totalDataSize 24/3 = 8.0; forbidden [v0 v1 a0] (a0 probably the K&R param `type`'s entry range, cand 2) -> headerSize a1, tds a2.
  Removal unchanged (tds 12.0 first -> a1; headerSize 11.0 -> a2; full 11).
- Near-miss tie measured: headerSize bb4 ld 2 + st 1 = 24/2 = 12.0 = tds 12.0, bit 8 wins (a1). Swapping the inits
  (`totalDataSize = 0;` first) hands the tie to tds (full 12): the tie goes to the first-defined candidate (M25).
- Near-miss ugen chain (as1probe keep): `addu $5,$5,7; and $13,$5,65535; move $5,$13; and $2,$5,65528; and $14,$2,65535;
  move $2,$14` -> as1 drops the 0xffff ands and the add lands in v0 (cand 38's register), mask in t6. Base chain
  `addu $2,$5,7; and $13,$2,65528; move $2,$13; and $14,$2,65535; move $2,$14` -> add t5, mask t6 (Q0374/Q1512 shift).
