# arcadeUpdateBouncingBarrel (arcade, src/arcade/0.c)
## Sites
- arcade:8002D6FC:dead-if:571f64 / #2 (kept, was fcde69): BLOCK SPLIT + AVAILABILITY coupled. The guards hold the entity pointer candidate 7 `{1282|0}` at adjsave 4.600, so it colours v1 with home 28(sp) instead of s0 (4.842 without them); the same-value read makes the unk1A load a candidate that colours into a0 (`lbu a0,26(v1)` at 0x9aa8 / 0x9e10).
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
## Untried ideas
- a real statement that both adds a block inside the entity pointer's range and re-reads unk1A before each flip; nothing in the target's surrounding control flow (0x9a98-0x9ac4, 0x9df4-0x9e1c) shows one.
## Evidence
- 0x9e04 is as1's bc1fl delay-slot copy of 0x9e10; one load is executed per path.
- bias also colours a0 (move a0,zero 0x99c4; addu a0,a0,t7 0x9a00), the register the facing candidate takes at 0x9aa8.
- uopt -l5: entity pointer candidate 7 `{1282|0}` adjsave 4.600 -> reg 2 (v1) with both guards, with `if (1) {}` / `if (floorY) {}` / `if (facing) {}` at both; 4.842 -> reg 14 (s0) without guards (s0 saved at 24(sp)); the block-scoped s32 `dir` temp also gives s0 and frame 0x38.
