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
## Untried ideas
- A permuter run from the 66-score single removal.
## Evidence
- 0x9e04 is as1's bc1fl delay-slot copy of 0x9e10; one load is executed per path.
