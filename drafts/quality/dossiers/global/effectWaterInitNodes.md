# effectWaterInitNodes (global, src/global/63EC0.c)

## Sites
global:8065F1C0:dead-if:c329e5 dead-if: the empty `gCurrentMap == 0` block preserves the opening table loop's `$v0` base / `$v1` end coloring; removed by expressing the later real 0x53/0xC5 map selector as a switch.
global:8065F1C0:noop-arith:5ef177 noop-arith: the extra `count * 0` use gives count's pre-loop piece (LR14: bb3 def + 2 uses, bb5 1 use, bb6/bb7) adjsave 1.5, tying base (LR26/28: bb5 def, bb6 two IV inits) and winning on the lower candidate number (Q0900), so count takes `$v0` (0x68/0x70/0x88) and base `$v1` (0x84/0x8c).

## Attempts
2026-11-14 U HackeffectWaterInitNodes openai-codex/gpt-5.6-sol: replaced the dead map block and later OR condition with a two-case selector switch -> whole-function fdiff exit 0.
2026-11-14 U HackeffectWaterInitNodes openai-codex/gpt-5.6-sol: natural zero guards, count switches, positive guarded for/do-while loops, index sentinels, MAX/MIN, u8/s32 and structured loads, declaration/assignment timing, sizeof-derived table counts, constant node size, and targeted variant/as1 scans -> best natural fdiff score 55; noop retained.
2026-11-17 2026-11-17: cleanup CleaneffectWaterInitNodes CleaneffectWaterInitNodes anthropic/claude-opus-5-5: copy-def census (D5E10/Q0739 lever), 36 combinations of an s32 loop-bound copy / u8 field-read local (position, declaration order, guard/bound split) -> best fdiff 3 (`end = count` before the ripple store: registers right, but end's def store `sw v0,0x4c(sp)` sits in bb3 at 0x74 instead of the split store at 0x9c); copy in bb5 triggers LFTR (52); guard-only copy propagates away (10).
2026-11-17 2026-11-17: cleanup CleaneffectWaterInitNodes CleaneffectWaterInitNodes anthropic/claude-opus-5-5: base/count spellings (201B0 has_ilod lever): section-pointer forms incl. 684C0's `(s32 *)section + 1`, `(u8)*(s32 *)section` (narrowed to lbu 3, same 10 lines), masks (51), narrow count types (11-12), per-iteration def pointer (46, merges s6/s2), register/initialised count (10), ripple-store order (56) -> no natural form below 10 variant lines.
2026-11-17 2026-11-17: cleanup CleaneffectWaterInitNodes CleaneffectWaterInitNodes anthropic/claude-opus-5-5: permuter, hack-free weights, natural `count == 0` body, -j 2, 900 s -> best 20 (empty `if (!i) {}` before the loop: count $a1), no zero.
2026-11-17 2026-11-17: cleanup CleaneffectWaterInitNodes CleaneffectWaterInitNodes anthropic/claude-opus-5-5: review removed the two no-op `(s32)` casts on the s16 extent differences -> fdiff 0.

## Untried ideas
A construct that adds one count reference in bb3/bb5 and leaves no surviving variable (a copy that survives stores at its def; a propagated copy adds nothing): none known in ordinary C. A real block between base's def (bb5) and the IV inits (bb6) would lower base to 1.0 and let count win the tie (Q0895), but the target has no branch between 0x78 and 0x9c.

## Evidence
The target loads count into `$v0` at 0x68, tests `$v0` at 0x70 (beqzl, delay `lw ra`) and 0x88 (blez), computes the water-definition base in `$v1` at 0x84/0x8c (second `lw 0x4c(a0)` at 0x78 after the `gWaterRippleActive` store at 0x6c), copies it to the two IVs s6/s2 at 0x94/0x98 and stores count to its home sp+0x4c at 0x9c in the preheader (split-boundary store; loop end reloads it at 0x294). uopt -l5: count piece adjsave 1.5 (hack) vs 1.0 (natural), base 1.5; tie broken by candidate number. `(u8)*(s32 *)section` compiles identically to `*(u8 *)(section + 3)`: the section probably starts with an s32 count word like the 684C0/67890/36880 sections.
