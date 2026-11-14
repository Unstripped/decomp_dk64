# loadOverlay (global, src/global/15050.c)
## Sites
- 06800c/107109/d792f5/5b9db4: u64 header save/restore. Retagged ORIG: target lw/sw pairs at 0x384-0x3a8 and 0x4a8-0x4cc.
- eb8b38: the dead if (gHeapPools[0].start == 0) {}. Kept.
  - Removal costs 3 (spill order at 0x1ec/0x254/0x25c).
  - The target loop has no test.
## Attempts
- earlier rounds: low, unlevelled, xhigh round 36 (see the history file)
- 2026-11-14 U, scored with variants.py try (full=):
  - ORIG classification
  - eb8b38 while loop: 3
  - eb8b38 for-init: 5
  - eb8b38 previous-pointer walk: 123
## Evidence
- target_loadOverlay.s
- copy.diff
