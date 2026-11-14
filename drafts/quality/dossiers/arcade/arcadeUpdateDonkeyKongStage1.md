# arcadeUpdateDonkeyKongStage1 (arcade, src/arcade/0.c)
## Sites
- arcade:8002EEB8:dead-if:f97550 / #2 / #3: REMOVED, each together with the redundant `return;` after it.
## Attempts
- 2026-11-14 U HackarcadeUpdateDonkeyKongStage1 opus:high:
  - guard removed alone: 3 / 4 / 10 (all three: 17)
  - break instead of return: same scores
  - guard plus return removed: 0 for every subset
## Evidence
- The guard is its own uopt block, so uopt's `.alias` reset comes before `b $59`.
- Without it, the reset follows the jump, which stops as1 hoisting into the next case:
  - case 12: `li at,20` / `li t6,9` at 0xaf28
  - case 11 entry: `lui t8` at 0xb33c
  - case 11: `lui at,0x4f80` at 0xb474
- as1probe scan: deleting record 331 (`.alias $4,$sp` after `b $59`) gives 0.
