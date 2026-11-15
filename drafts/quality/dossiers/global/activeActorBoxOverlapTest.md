# activeActorBoxOverlapTest (global, src/global/36880.c)
## Sites
global:80635EF0:dead-store:c23f42 dead-store (removed): dead s16 copies rx/ry/rz renumber the int webs: count a1, i a0, gActiveActors cursor t0, mask t1 (0x4370-0x43c4); without them v1/v0/a1/a2.
global:80635EF0:other:30e5e7 other (removed): alias `b = a` read by the low-bound compares keeps the coordinate loads in f18/f22/f24 and the radius cvt.s.w in f0/f2/f16 (0x43d4-0x4414).
## Attempts
2026-11-14 Polish36880BoxOverlapTag claude-opus-5-5:high: plain removal of copies (58 diff lines); one pointer for all compares; gActiveActors[i].actor at every use; assignment in the flag test -> nohit
2026-11-14 HacktexAnimUpdateNodes claude-opus-5-5:high: copies READ by all six compares (s16 or s32, assignment or declaration initialiser; nested if, single &&-chain, `!= 0`, operand-order matrix of the low/high compares) -> int webs match, full=18 with or without the alias: only the FP pairs swap (loads f0/f2/f16, cvts f24/f22/f18). Per-group spelling matrix: radiusX low + rx high + alias = full=0 (a second spelling of one value: steer, nohit), rx low + radiusX high + alias full=12, without alias 18/47. ActorEntry pointer walk full=64-67, `continue` form 80. Permuter 905 s (perm_box, base 90) from the rx-read/no-alias body: output-0-1 best=0 hoists `rx + x` into an f32 temp before the loop (plus an alias).
2026-11-14 HacktexAnimUpdateNodes claude-opus-5-5:high: hint translated into six f32 bound locals (minX = x - radiusX; maxX = x + radiusX; ... before the loop; compares minX <= a->x ... a->x <= maxZ), copies and alias deleted -> full=0 in every ordering (grouped, interleaved, max-first, max-only, min-only, radius + x or x + radius); fdiff 0. Both sites removed.
## Untried ideas
none (function clean)
## Evidence
0x4384 sw a3,44(sp) and 0x4388-0x438c sll/sra a3: ANSI s16 radiusX narrowed at entry; radiusY/Z lh 50(sp)/54(sp), mask lhu 58(sp) hoisted before the loop (0x43a8-0x43b0).
One cvt.s.w per radius reused by both bounds (f0 at 0x43d8 -> add.s 0x4430); one lwc1 per coordinate reused (f18 0x43d4 -> c.le.s 0x4434).
uopt trace: with the alias the radius cvts get the early expression bits (40/48/56, regs 24/25/28) and the second-group a->x loads the late ones (62/67/72, regs 29/31/32); with read copies and no alias the loads get the early bits (34/42/50) and the cvts of the copy-propagated params the late ones (79/83/87) -> swapped FP registers.
Bound locals: uopt forward-propagates each f32 bound into the loop (the subtraction/add stays inside, after the lwc1) but the cvt.s.w expressions get the early bits, so the radius cvts colour f0/f2/f16 and the loads f18/f22/f24 as in the target.
