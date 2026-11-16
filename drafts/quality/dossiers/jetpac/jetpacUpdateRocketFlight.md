# jetpacUpdateRocketFlight (jetpac, src/jetpac/3480.c)
## Sites
- jetpac:800286D0:other:fb4a33 (fixed 2026-11-16): the empty `if (!t) {}` in the final 3-item loop lifted t (cand 11, var 29) from adjsave 9.0 to 11.0, so it coloured reg 24 ($f0) before the 168.0/16.0 consts (adjsave 10.0). Replaced by a dedicated `f32 pos` for the final running value.
## Attempts
- 2026-11-14 opus:high (full=):
  - removal: 38
  - header ++ / do-while: 39; index: 42; per-item expression: 31
  - running value in y: 20 (best); y + header: 21; y indexed: 24
  - t from y: 33; mirror loop: 47
- 2026-11-16 HackjetpacUpdateRocketFlight anthropic/claude-opus-5-5:high:
  - dedicated `pos` local, `item++` in the body: 0 (fdiff exit 0, adopted)
  - dedicated `pos`, `item++` in the for header: 4
  - `item++` before `t += 16.0f`: 39; `(item++)->unkC = t`: 39; `t = item->unkC + 16.0f`: 38
  - `item->unkC = y + spd; y += 16.0f`: 30
  - LAYOUT clamp split re-measured after the fix: 2 (kept)
  - `(f32)(i * 16)` cast dropped: 0 (codegen-neutral; kept to mirror the sibling placement functions)
## Untried ideas
- none for the guard (fixed).
## Evidence
- 0x1494 `lwc1 $f18,0x24(sp)`: spd lives in its stack home (never coloured; stored at 0x13ec / 0x1490).
- 0x14a8-0x14b4: running value `add.s $f0,$f12,$f18`, `swc1 $f0,0xc(a2)`, `add.s $f0,$f0,$f2` with 16.0 in $f2 (0x149c).
- 0x129c-0x12f4: clamp result in $f0, zero in $f2, 1.0 in $f14 (rematerialised after each jal at 0x1324/0x1418).
- uopt -l5 (removal form): t adjsave 9.0, 168.0 const (cand 84) 10.0, 16.0 const (cand 87) 10.0, colouring order 84, 87, 11.
