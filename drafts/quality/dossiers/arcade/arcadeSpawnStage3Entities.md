# arcadeSpawnStage3Entities (arcade, src/arcade/0.c)

## Sites
- 6ec87d: early `i = 0` plus `i = i + 0x24`. REMOVED.
  - D_8004C170 is D_8004BCD0[0x25], so the six stores are one descending walk from 0x25.
  - `i = 0x25` at the function top keeps the counter live from the start, as the early `i = 0` did.

## Attempts
- 2026-11-14 U HackarcadeSpawnStage3Entities: `i = 0x25` at the top matches (RELOC-EQUIV). Late placement: 418 lines. Literal [0x25] with `i = 0x24`: 418.

## Untried ideas
- Retire D_8004C170 in the other three functions (lines 1245, 1309, 1478). Not in this item.

## Evidence
- Raw words equal except `addiu t4,t4,0x4a0` vs `0` at 0x4c7c; both resolve to 0x8004C170.
