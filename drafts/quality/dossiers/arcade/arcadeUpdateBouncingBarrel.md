# arcadeUpdateBouncingBarrel (arcade, src/arcade/0.c)
## Sites
- arcade:8002D6FC:dead-if:fcde69 / #2 (kept): the dead test makes the unk1A load a uopt candidate that colours into a0 (`lbu a0,26(v1)` at 0x9aa8 / 0x9e10).
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
## Untried ideas
- none left: every candidate-shaping spelling found so far is a reused or value-named local.
## Evidence
- 0x9e04 is as1's bc1fl delay-slot copy of 0x9e10; one load is executed per path.
- bias also colours a0 (move a0,zero 0x99c4; addu a0,a0,t7 0x9a00), the register the facing candidate takes at 0x9aa8.
