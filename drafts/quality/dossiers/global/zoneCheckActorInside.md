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
## Untried ideas
- A codeless natural use of constant 5 inside the loop. Q0771 suggests a constant-propagated local, but a value-named constant local is still tagged.
- Raise x/y/z/zone instead (Q0766), e.g. a later first assignment. x/y/z must load before the loop guard, so this is unlikely.
## Evidence
- frame -0x68; FP homes f20/f22/f24 = x/y/z, f26 = 1.4
- index loop: multu s1,s6 (s6=10), zone->entries reloaded each pass (lw t7,20(s2))
- count re-read after the call (0x1dd8)
- constants hoisted at 0x1c84-0x1c90
- the hit block stores sb s4,0xfc / sb s4,0xfd, with found = 1 in the jal delay slot (0x1dcc)
- adjsave (uopt_trace -l 5):

  | candidate | target (2 dead tests) | no dead test |
  |---|---|---|
  | const 5 | 3.33 | 2.0 |
  | store-1 | 3.33 | 4.0 |
  | 1.4 | 3.33 | 4.0 |
  | x/y/z/zone | 3.5 | 4.2 |
  | found | 1.71 | 2.0 |
  | 10, 1, &gBehaviourExtraState | 1.67 | 2.0 |
  | flags (ucvt) | 13.3 | 30 |

- The colouring needs const 5 strictly above found/10/1, and at least store-1 (5 wins ties by candidate order).
- The 1.4 constant must sit at or below x/y/z. Only a codeless second use of 5 plus one more nlive unit (Q0163 divisor) gets there.
