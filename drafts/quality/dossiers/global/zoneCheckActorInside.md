# zoneCheckActorInside (global, src/global/1295B0.c)
## Sites
- global:807264B0:dead-if:7b005b: REMOVED (this unit). Writing the distance test as `if (!(d2 < r2)) continue;` before the hit block gives the same blocks.
- global:807264B0:dead-if:be434b `if (e->flags != 0) {}`: keeps flags in a1 and the entry count in t0 (lh 0x10(a3) at 0x1c50, reloaded at 0x1dd8). Without it they become a0/a1.
- global:807264B0:dead-if:1aaf2a `if (i == 5) {}`: raises the constant-5 web so the callee-saved order is s3=5 s4=1 (stores) s5=found s6=10 s7=1 (sel).
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
## Untried ideas
- be434b: a natural later read of e->flags inside the y block, or a different ordering of the sel/y tests that keeps flags live to 0x1d54.
- 1aaf2a: a second natural use of the constant 5 inside the loop, or something lowering the u8-store 1 web (sb 0xfc/0xfd) below the 5 web.
- A uopt -l 6 priority dump of the 14 form, to read the exact gap between the 5 web and the store-1 web (Q0523 divisor steps).
## Evidence
- frame -0x68; FP homes f20/f22/f24 = x/y/z, f26 = 1.4
- index loop: multu s1,s6 (s6=10), zone->entries reloaded each pass (lw t7,20(s2))
- count re-read after the call (0x1dd8)
- constants hoisted at 0x1c84-0x1c90
- the hit block stores sb s4,0xfc / sb s4,0xfd, with found = 1 in the jal delay slot (0x1dcc)
