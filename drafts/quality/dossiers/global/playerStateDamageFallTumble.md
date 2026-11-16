# playerStateDamageFallTumble (global, src/global/D5E10.c)

## Sites
- global:806D9320:dead-if:4a0a6c (dead-if): `if (z) {} // FAKE: dead guard is a real uopt use (Q0561)`.
  Steered the (b == 0) uequ candidate {1261|0} (bit 21): the guard added a use after the decel
  ternary (adjsave 1.5), so it was coloured v0 (`sltiu v0,a0,1` at 0x8300) and decel kept a1.
  REMOVED (2026-11-16, HackplayerStateDamageFallTumble): see Attempts.
- global:806D9320:noop-arith:u23f28 / d23f28 (`^ 0`): fixed in round 15 (twin of 806D91A4).

## Attempts
2026-11-09..14 (rounds CleanD5E10, 3, 6, 15, 16, 17, 36, RereviewGlobalMid1; see
`uv run tools/quality.py history playerStateDamageFallTumble`): removal (fdiff 1 / 50 lines),
cond flips (`z != 0`, `!z`, `if (n)`), b width, 8 re-read forms (Q0589), permuter runs (best 10..45,
all new_var / if (1) / no-op multiply hacks), uopt_trace l5 (guard = extra use of {1261|0}).

2026-11-16 HackplayerStateDamageFallTumble anthropic/claude-opus-5-5:high -> fdiff 0, site removed.
Scores (variants.py try, full=):
- guard removed, z kept as `z & C & 1` (all widths, both & orders): 50; z placed after decel: 50.
- `z = (b == 0) & C; if (z & 1)`: 3 (`and v0,t5,v1` / `sltiu t5`).
- b dropped, `z = (prev == 0)` before decel, `z & C & 1`: 8 (a0/v0 swap of contactFlags/sltiu).
- same with `z = (prev == 0)` after the decel ternary: 1 (only `and t5,v1,v0` vs `and t5,v0,v1`).
  `C & z & 1`, `z !` spelling, declswap, `u32 z`: still 1; `z & (C & 1)`: 58.
- contactFlags in a named local (s32/u32/u16, three placements): 5..12.
- `(z = (prev == 0)) & C & 1` after decel: 0, but z is a dead store (not taken).
- no locals, `(prev == 0) & C & 1`: 53; `C & (prev == 0) & 1`: 53; `!b & C & 1` with u16 b: 53.
- no locals, `!prev & C & 1` after decel: 0 -> TAKEN.
- `f32 pad` still needed (removal: 2).

## Untried ideas
none for this site (removed).

## Evidence
Target 0x82f4..0x8318: `and t3,v1,a0; andi t4,t3,1; beqz t4; sltiu v0,a0,1; li a1,2/1;
and t5,v0,v1; andi t6,t5,1`. a0 = prevContactFlags, v1 = contactFlags.
uopt (tr_X1 vs tr_X3): cfe lowers `!E` used as an arithmetic `&` operand to a compiler temp
(isvar 1041, -36vreg, `ustr{1041}{uequ{0|1}{959|4}}`), which uand keeps on the left
(`uand{1041}{1300}`); `(E == 0)` stays an isop expression `uand{1261}{1300}` and without an
extra use does not get v0.
