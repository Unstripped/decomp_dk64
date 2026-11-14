# heapInitGeneralPool (global, src/global/15050.c)
## Sites
- 28b74f/73dee9/fbcccd/ff18d9: u64 zero stores. Retagged ORIG.
  - li pairs at 0x8c0-0x8f4.
  - The t4/t5 zero pair is reused for end->next (0x8f8/0x904).
## Attempts
- earlier rounds: low, unlevelled, xhigh round 36 (see the history file)
- 2026-11-14 U: ORIG classification
## Evidence
- target_heapInitGeneralPool.s
- copy.diff
