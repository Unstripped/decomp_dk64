# csScriptLoad (global, src/global/42630.c)

## Sites
- none (no FAKE/goto/proto-steer/cfe-warning site).

## Attempts
- 2026-11-09..13 (history): views fixed (CsLoadSpawn -> CsSpawnReq D_807F61F0; file-local CsLoad* views retired for ModelSlot + CsState), names fixed (CsSpawnReq timerActor/hostActor/active), reviews fake=0/0.
- 2026-11-17e 2026-11-17: cleanup HackcsCmdExec11 HackcsCmdExec11 anthropic/claude-opus-5-5 (variants.py try full=, base ff2f08b4 = after 23d2164d u8 gCsCondFlag and 11134d9a merged 0xA4 CsState): re-review. The hand-rotated outer loop `if (n != 0) { do { ... n--; } while (n != 0); }` scores 0 as `while (n != 0) { ... n--; }` (also `for (; n != 0; n--)` 0) and fdiffs 0: applied as `while`, like the two inner `while (m != 0)` loops. `heapAlloc(0xA4)` / `heapAlloc(0x50)` -> `heapAlloc(sizeof(CsState))` / `heapAlloc(sizeof(CsNode))` (both structs are exactly those sizes after 11134d9a): fdiff 0.

## Untried ideas
- none needed (no hack site). Optional readability: a `CsState *` local for the four `gModelSlots[slot].unk7C` accesses (not measured; Q0601-style pointer local could change the s-register colouring).

## Evidence
- heapAlloc arguments are literal 0xA4 and 0x50 in the target; CsState (include/cutscene.h) is 0xA4 and CsNode 0x50.
