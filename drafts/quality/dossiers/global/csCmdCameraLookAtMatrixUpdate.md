# csCmdCameraLookAtMatrixUpdate (global, src/global/478F0.c)
## Sites
- global:80648000:other:c560e4 (kept): `void *dm = &cs;`. Taking cs's address keeps it in its home 160(sp), reloaded at 0x5450/0x54c0/0x54ec. dm itself takes a slot, which puts &x at sp+64.
- global:80648000:other:be811a (kept): `rz = t / (f64)100;`. The int-converted divisor splits the 100.0 constant. With a 3-use 100.0 web, uopt hoists one register for it.
## Attempts
- 2026-11-09..12, Clean478F0 / ReReview / Rev16K / Rev17L (opus low/xhigh): nohit.
  - Without &cs, cs is coloured to s1. Permuter best=0 only stacks hacks.
  - `t / 100.0` gives one 100.0 candidate hoisted above `sra`.
- 2026-11-15, HackcsCondDepositItem (opus high): nohit.
  - c560e4, each without `dm`: plain removal 94 lines (cs in s1, stack slots +4). `m = cs->data` before the second if: 95. Nested `if (cs->unk9A & 1) { if (cs->data == NULL) ... }`: 97. `cs->data = heapAlloc(0x44); m = cs->data;`: 94.
  - be811a: `rz = t / 100.0` with `rx * 100 + -50.0` (int literal) scores 6. Only the rx product changes, to f32 `mul.s` instead of cvt.d.s + mul.d at 0x5568-0x5570. So any split of the three 100.0 uses gives the target; only the spelling is open.
    - `rz = t * 0.01`: 14. One-line rx: 58.
  - sweep: 0 hits.
## Untried ideas
- uopt_trace of cs's priority without `&cs`: what would make s1 unprofitable (use weights per block) other than taking the address.
- A spelling with a distinct double 100.0 that is not a cast: double literals are canonicalised (Q0473), so this probably needs an int-to-double conversion somewhere natural.
## Evidence
- 0x541c sw a0,160(sp); 0x5450 lw t0,160(sp); 0x54c0 lw t3,160(sp); 0x54ec lw t8,160(sp): no s-register for cs (only s0 = m).
- 0x551c / 0x5540 / 0x5578: three separate `lui at,0x4059` 100.0 materialisations.
