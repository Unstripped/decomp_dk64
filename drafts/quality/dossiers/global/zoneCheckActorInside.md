# zoneCheckActorInside (global, src/global/1295B0.c)
## Sites
- global:807264B0:dead-if:7b005b: REMOVED (unit HackzoneCheckActorInside). Writing the distance test as `if (!(d2 < r2)) continue;` before the hit block gives the same blocks.
- global:807264B0:dead-if:1aaf2a `if (i == 5) {}`: REMOVED (HackzoneCheckActorInside2), merged into the compound dead test below.
- global:807264B0:dead-if:342b4e (was be434b `if (e->flags != 0) {}`) `if ((e->flags == 0) || (e->flags == 5)) {}`: one test does both old jobs. The flags read keeps flags live into the y block (count stays t0, flags a1), the `== 5` adds a second loop use of constant 5, and the two tests add two blocks.
## Attempts
- rounds 3/6/17/20/22 (opus:low): removals, uopt traces, permuter 600 s x2 (best splits flags & 0x80), reconstruct with 19 natural rewrites.
- 2026-11-14 U HackzoneCheckActorInside (opus:high), scored with variants.py try (full=):
  - distance test as early continue, 7b005b removed, be434b + 1aaf2a kept: 0 (kept); the `>=` spelling: 2
  - with all three removed:
    - nested grid (72): best 37
    - continue grid (128): best 37
    - width grid (80): `sel` s8/s16 gives 28 but adds sll/sra
  - with one dead if kept (48-body continue grid):
    - only be434b kept: 14 (constant webs only)
    - only 1aaf2a kept: 23 (count/flags temps only)
  - nudges on the 14 form (found placement, chained stores, 5U, s32 i): 14-87
- 2026-11-15 U HackzoneCheckActorInside2 (opus:high), variants.py try plus uopt_trace -l 5:
  - natural bodies with no dead test:
    - switch (sel) with case 5 falling into 0/1: 37 (nested form: 50)
    - a second real `sel == 5` test (`sel != 5 || speed`, ternary, `continue` on 5): 29, but it emits an extra bnel
    - an ok-flag if/else chain: 25 (different shape)
    - speed test after the y test: 66
    - `else if` after an empty `if (flags & 0x80)`: 53
    - a `u8 flags` local: 38
    - no `e` pointer (`zone->entries[i].f` everywhere), with or without `sel`: 37-54
  - one compound dead test in place of both (14 conditions):
    - `(e->flags == 0) || (e->flags == 5)`: 0 (applied)
    - `(e->flags != 0) || (i == 5)`: 0
    - `|| sel == 5`: 8
    - the `&&` forms: 19-27
    - single tests (`e->flags == 5`): 19
- 2026-11-16 U HackspawnNodeActorOutOfRangeScaled2 (opus:high), variants.py try plus uopt_trace -l 5/-l 6 (no dead test in any body):
  - `sel = e->flags & 0x7F;` moved inside `if (!(e->flags & 0x80))`: 18. flags now lives across the bnez, so count gets t0 and flags a1 as in the target; left: the s3..s8 constant order and the t1/t9 ring (the 0x80 and is emitted before the 0x7f and)
  - same with the switch form: 27; the switch alone gives the target's divisor (found 1.71, 10/1/5/gBES 1.67, store-1 3.33) but const 5 keeps one reference
  - sel-inside nudges: `sel = e->flags; if (!(sel & 0x80)) sel &= 0x7F` 38, early `continue` on 0x80 18, `== 0` spelling 18, x/y/z or found placement 18-19, `i = 0;` outside the for 18
  - masked compares inline (`(e->flags & 0x7F) == c` for one of 0/1/5): 35-37; `e->flags == 5` in place of `sel == 5`: 17 (compares flags, bnel s7,v0)
  - chained `hasArcBounds = collisionHit = 1`: 40; found = 1 before the call or after the stores: 37
  - no-sel inline masks: 38
## Untried ideas
- none natural for the constant web: see the adjsave evidence below. The only open question is whether a codeless construct that is ordinary C (not a dead test, a constant local or no-op arithmetic) can add a uopt reference to 5; none is known.
## Evidence
- frame -0x68; FP homes f20/f22/f24 = x/y/z, f26 = 1.4
- index loop: multu s1,s6 (s6=10), zone->entries reloaded each pass (lw t7,20(s2))
- count re-read after the call (0x1dd8)
- constants hoisted at 0x1c84-0x1c90; s3=5, s4=store-1, s5=found, s6=10, s7=compare-1, s8=&gBehaviourExtraState: every callee-saved register is used, so the colouring order must be exactly 5, store-1, found, 10, 1, &gBES
- the hit block stores sb s4,0xfc / sb s4,0xfd, with found = 1 in the jal delay slot (0x1dcc)
- adjsave (uopt_trace -l 5):

  | candidate | target (dead test) | no dead test | sel inside | switch |
  |---|---|---|---|---|
  | const 5 | 3.33 | 2.0 | 2.0 | 1.67 |
  | store-1 (1\|1) | 3.33 | 4.0 | 4.0 | 3.33 |
  | found | 1.71 | 2.0 | 2.0 | 1.71 |
  | 10, compare-1, &gBES | 1.67 | 2.0 | 2.0 | 1.67 |
  | count | 3.67 (t0) | 4.4 (a1) | 4.4 (t0) | 3.67 (a1) |

- Every hoisted constant spans the same loop blocks, so its adjsave is (references x 10) / divisor with one shared divisor. Ties go to the lower candidate number (5 before store-1, found before the constants). The target order needs 5 >= store-1 > found >= 10/1/gBES. store-1 has 2 references and 10/1/gBES one each, so 5 needs 2 references. In the target code 5 has one (bnel s3,t9 at 0x1cc4), so the second reference generates no code.
