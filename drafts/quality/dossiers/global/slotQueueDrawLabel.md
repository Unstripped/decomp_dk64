# slotQueueDrawLabel (global, src/global/FCCD0.c)

## Sites
- f22aa7: dead `displayMode == 0` read in case 2. KEPT.
  - Without it the selector is a2 and the slot pointer v0; the target has v0 and v1.

## Attempts
- 2026-11-14 U HackslotQueueInit: 7-106 lines (see the ledger).

## Evidence
- 0x1f0c `addu v1,t6,t5`, 0x1f10 `lbu v0,44(v1)`.
- 0x1f5c: `slot == 5` is compiled as `slot*48 == 240` using the spilled offset at 48(sp).
