# arcadeUpdatePlayerEntity (arcade, src/arcade/0.c)
## Sites
- arcade:8002B89C:dead-if:5f684d (kept): the dead read of D_8004BC84 stretches the &D_8004BC84 address web, so uopt does not colour it. The target rematerialises `lui` for the load at 0x8924 and the store at 0x8944.
- arcade:8002B89C:dead-if:e534b2 (kept): the same for &D_8004BC80 (0x83d8-0x83f0).
## Attempts
- 2026-11-14 opus:high (full=):
  - removal: 14 / 27 / 37
  - phase spellings: 19-121
  - early phase read: 335
  - coll call moved before the counter block: 27
## Untried ideas
- A natural use of the counters elsewhere in the function that keeps their address webs long. None found in the current body.
