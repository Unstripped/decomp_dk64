# arcadeUpdateBouncingBarrel (arcade, src/arcade/0.c)
## Sites
- arcade:8002D6FC:dead-if:571f64 / #2: FIXED 2026-11-17 (no hack left). Both were one coupled class-2 knot (Q0908): a block-count lever on the entity pointer candidate 7 (`&D_8004BCD0[entIndex]`, s0 vs v1 with home 28(sp)) plus a same-value read that made the flip's facing value a coloured candidate (a0 at 0x9aa8 / 0x9e10). The real source: an early `if (gArcadeFrozen != 0) { return; }` (the block) and `facing = !facing` at both flips (the candidate: cfe's `!` temp).
## Attempts
- 2026-11-14 opus:high (full=):
  - removal: 301 both; 130 first only; 66 second only
  - `!unk1A`: 142
  - xor or swapped comparison: 301
  - ternary or if/else: 195
  - named dir temp: 151+
  - entity pointer local: 345 / 550
- 2026-11-15 U HackarcadeUpdateDonkeyKongStage3 opus:high (full=):
  - facing read into the existing `bias` local (`bias = facing; facing = bias == 0`): 142 both, 194 first only, 254 second only; `floorY` reused at the first: 259
  - new u8 or s32 `dir` local (declared first or last): 151 both, 200 first only, 258 second only; u8 `dir` at the second with the first guard kept: 36
  - permuter from the second-only removal (900 s, -j 2, base 460): best 10, only through variable reuse (`(bias = facing) == 0`, bias in place of floorY in case 3)
- 2026-11-16 U HackarcadeUpdateBouncingBarrel opus:high (full=):
  - Q0908 class test: `if (facing) {}` at both 0; `if (1)` / `if (entIndex)` / `if (floorY)` at both 187; first alone (second kept): unrelated guards 130, `if (facing) {}` 2 (lbu v0 vs a0 at 0x9aa8); second alone (first kept): `if (1)` / `if (entIndex)` 66, `if (floorY)` 14 (registers only, 0x9dc4 / 0x9e04 / 0x9e10)
  - flip spellings: `facing < 1`, `(u8)(facing == 0)`, `0 == facing`, `(s32)facing == 0`, `== 0U`, `!(facing & 0xFF)` 301; `!(facing != 0)` 144; `facing ? 0 : 1` 195; `(facing == 0) & 1` 363
  - block-scoped u8 / s32 `dir` temp 151 / 149; computed `turn` temp s32 151, u8 306; `u8 *` field pointer and block-scoped `ArcadeEntity *` 304; case-2-scoped entity pointer 548
  - collision test inverted / `<=` with arms swapped 137; floor test inverted with arms swapped 304 / 305
  - early `break` after the floor / state-5 / state-6 / flip arms (each and all) 66; empty statement `;` before/after either flip or at the end of the first else arm: 130 / 66 (Q0698)
- 2026-11-16 U HackarcadeUpdateBouncingBarrel2 opus:high (full=):
  - re-measured at the d4b7b65d base (after Polisharcade0's compound-assignment respellings): both removed 301, first only removed 130 (unchanged)
  - permuter from the both-removed body (900 s, -j 2, hack-free weights, base 6269): best 450, only via a dead `if (!gArcadePlayerIndex) {}` after the animTimer wrap, bias reuse at the first flip and `(*(&D_8004BCD0[entIndex])).x`
- 2026-11-17 2026-11-17: cleanup HackarcadeUpdateBouncingBarrel3 HackarcadeUpdateBouncingBarrel3 anthropic/claude-opus-5-5:high: split the knot into its two levers -> fdiff exit 0 (FIXED)
  - diagnostic: `bias = facing; facing = bias == 0` at both + `if (1) {}` at both 0; with bias reuse ONE `if (1) {}` at either flip, after both, or at almost any statement from the frozen test to the switch end gives 0 (pure block lever once the flip value is a coloured local); u8/s32 `dir` local + `if (1) {}` both 22
  - natural block sources with bias reuse: early return `if (gArcadeFrozen != 0) { return; }` 0, `if (gArcadeFrozen) return;` 0, `default: break;` 0; kill test as one 4-term `&&` or as nested ifs 142; case-3 `&&` as nested ifs 142
  - early return alone (flip `== 0`) 187; early return + dir local 22; early return + `!facing` both 0 (fdiff whole object OK); `!` only at site 1 64, only at site 2 130; `default: break;` + `!facing` 0
  - kept: early return + `!facing` at both; four reversed comparisons written entity-first (`y > floorY`, `y > D_8004C6E4`, `y > D_8004C6E8 - 1`, `x > 270.0f`) 0
## Untried ideas
- none for the hack sites (fixed).
## Evidence
- 0x9e04 is as1's bc1fl delay-slot copy of 0x9e10; one load is executed per path.
- the target uses no s-register (frame 0x30): the entity pointer is v1 with home 28(sp) and is stored/reloaded around every jal (0x9930, 0x99e0, 0x9a4c, 0x9ae8, 0x9be0, 0x9c58, 0x9ce8, 0x9d5c).
- uopt -l5/-l6 on the fixed copy: `!facing` makes cfe emit `uequ{0}{uilod facing}` stored into a hidden temp (isvar M -12vreg, cand 45; locals floorY -4, bias -8), then `uistr` of the temp; `== 0` emits `uequ{0}{ucvt(uilod)}` + `ucvt` with no temp. Cand 45 is shared by both flips and colours reg 3 (a0): lbu a0,26(v1) 0x9aa8 / 0x9e10.
- entity pointer cand 7 `{1282|0}`: reg 2 (v1) with the early return; reg 14 (s0) with the `if (gArcadeFrozen == 0) { body }` wrapper (`!facing` alone, 142), where the `!` temp takes reg 2.
