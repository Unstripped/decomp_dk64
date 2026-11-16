# slotQueueDrawLabel (global, src/global/FCCD0.c)

## Sites
- f22aa7: dead `displayMode == 0` read in case 2. KEPT.
  - Without it the selector is a2 and the slot pointer v0; the target has v0 and v1.
  - Q0908 class: same-value. Only a displayMode read works (1, slot, .x, .shown, gfx, text[0]: 7 = removal). It works anywhere between guTranslate and the first call of an arm (before the switch, start of case 1/2/default); after an arm's _sprintf or after the switch it does not.

## Attempts
- 2026-11-14 U HackslotQueueInit: 7-106 lines (see the ledger).
- 2026-11-16 U HackslotQueueStateFadeIn2 (anthropic/claude-opus-5-5:high): classification above; real two-read selections (if/else-if chain, nested switch in default, if (mode == 1) else switch, switch with if/else in default) all 31: IDO lowers them to an if-chain `bne` layout.

## Evidence
- 0x1f0c `addu v1,t6,t5`, 0x1f10 `lbu v0,44(v1)`.
- 0x1f5c: `slot == 5` is compiled as `slot*48 == 240` using the spilled offset at 48(sp).
