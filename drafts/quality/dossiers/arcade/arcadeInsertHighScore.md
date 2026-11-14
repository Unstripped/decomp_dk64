# arcadeInsertHighScore (arcade, src/arcade/0.c)

## Sites
- e03dfc: `u16 initial[2]` memory home. KEPT.
- 2190b9, 718d93, 286c69, 2190b9#2: dead guards. KEPT.
  - They exist to place the memory-homed byte's reload.

## Attempts
- 2026-11-14 U HackarcadeInsertHighScore: aggregate and row-pointer forms 38-45. Invariant variable index 13 (still a steer).

## Untried ideas
- An original reason for the byte's memory home (an address-taken use compiled out?). Not provable from the target.

## Evidence
- 0xa54/0xa68 `lbu t6; sb t6,12(sp)` at entry; a single reload `lbu a0,12(sp)` at 0xae0 before the fill loop.
