# csCmdCameraLookAtMatrixUpdate (global, src/global/478F0.c)
## Sites
- global:80648000:other:c560e4 (fixed 2026-11-17): `void *dm = &cs;`. Taking cs's address kept it in its home 160(sp), reloaded at 0x5450/0x54c0/0x54ec. dm itself took a slot, which put &x at sp+64. Replaced by `pad[21]` (frame word) plus a guard-clause early return for the second test.
- global:80648000:other:be811a (fixed 2026-11-17): `rz = t / (f64)100;`. The int-converted divisor split the 100.0 constant. With a 3-use 100.0 web, uopt hoists one register for it. Replaced by the file-local macro `RAND_FRACTION(n)` used for rx and rz.
## Attempts
- 2026-11-09..12, Clean478F0 / ReReview / Rev16K / Rev17L (opus low/xhigh): nohit.
  - Without &cs, cs is coloured to s1. Permuter best=0 only stacks hacks.
  - `t / 100.0` gives one 100.0 candidate hoisted above `sra`.
- 2026-11-15, HackcsCondDepositItem (opus high): nohit.
  - c560e4, each without `dm`: plain removal 94 lines (cs in s1, stack slots +4). `m = cs->data` before the second if: 95. Nested `if (cs->unk9A & 1) { if (cs->data == NULL) ... }`: 97. `cs->data = heapAlloc(0x44); m = cs->data;`: 94.
  - be811a: `rz = t / 100.0` with `rx * 100 + -50.0` (int literal) scores 6. Only the rx product changes, to f32 `mul.s` instead of cvt.d.s + mul.d at 0x5568-0x5570. So any split of the three 100.0 uses gives the target; only the spelling is open.
    - `rz = t * 0.01`: 14. One-line rx: 58.
  - sweep: 0 hits.
- 2026-11-17, CleancsCmdCameraLookAtMatrixUpdate (opus): both fixed, fdiff 0.
  - be811a: `#define RAND_FRACTION(n) ((f32)((randomNonNegative() >> 15) % (n)) / (f64)(n))`, `rx = RAND_FRACTION(100); rz = RAND_FRACTION(100);`, `t` dropped: fdiff 0. The conversion constant `1.0000000000000000e+02` has 2 uses and the literal `100.0` 1 use; neither is coloured. A bare `(f64)100` at both divisors or `rx * (f64)100` also match (steers). `100.0L` at rz: 58, same as plain `100.0`.
  - c560e4: plain removal (pad[21]) after the be811a fix: 86. cs (bit 0) adjsave 1.25 over 10 blocks takes s1, and the int 100 constant (bit 77, adjsave 0.5) shares s1. K&R definition: 86. `CsLookAt **slot` for every data access: 86. Scalar pad: 86.
  - c560e4 fix: `if (!(cs->unk9A & 1) || (randomLcgNext() / 10000U) % 20U != 0) { return; }` then the spawn body. The return adds an exit block. cs splits into 0 (adjsave -1.0) and 84 (0.0), both uncoloured, so it stays in 160(sp). Two separate guards, or only `if (!(cs->unk9A & 1)) return;` before the old rand `if`, also match.
  - The plain 3x `100.0` still scores 58 with the early return, so the macro is still needed.
  - Hack-free permuter, 900 s, -j 2, from the all-removed body (old if shape, pad[21], plain 100.0): baseline 7235, best 510 (dead `if (!t && !t) {}` plus `rx * (float)100.0`), no zero.
## Untried ideas
- None open: both sites fixed.
## Evidence
- 0x541c sw a0,160(sp); 0x5450 lw t0,160(sp); 0x54c0 lw t3,160(sp); 0x54ec lw t8,160(sp): no s-register for cs (only s0 = m).
- 0x551c / 0x5540 / 0x5578: three separate `lui at,0x4059` 100.0 materialisations. 0x550c / 0x5550 `li at,100` twice: the int 100 is uncoloured too.
- 0x5524 cvt.s.w + 0x552c cvt.d.s + 0x5530 div.d: the numerator goes through f32 before the double division.
- 0x55a0 add.d with $f10/$f11 = -50.0 (0xc049): `+ -50.0`; `- 50.0` scores 3.
- Frame: pad covers sp+80..159, a word at sp+76 (dm, now pad[21]), rx home sp+72 (spilled across the second randomNonNegative), x sp+64, y sp+60, z sp+56.
