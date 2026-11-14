# textBoxUpdateRows (global, src/global/A8400.c)

## Sites
- a22210: dead `if (acc && acc) {}`. REMOVED.
  - The `mode == 3` test is now a one-case `switch (mode)` with `s16 mode`.
  - The switch dispatch block restores the state s2 / node s1 colouring.
  - s16 avoids the selector copy that u8 mode gets.

## Attempts
- 2026-11-14 U HacktextBoxUpdateRows: fixed. See the ledger for line counts.

## Evidence
- Target 0x1a00 `lbu v0,340(s3)` compares v0 directly at 0x1a08 and 0x1a38. With u8 mode the selector is v1, plus `move v1,v0`.
