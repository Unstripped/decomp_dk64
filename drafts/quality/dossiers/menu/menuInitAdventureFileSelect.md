# menuInitAdventureFileSelect (menu, src/menu/3E10.c)
## Sites
826fa7/32876d/f3492f (504/508/512) (void *)(s32)&D_8072052C arguments: KEPT.
- Only the cvt pair makes the address one CSE value that is spilled and reloaded (Q0704/Q0341).
- Any pointer spelling is an lda that uopt rematerialises per call.
## Attempts
- rounds 1-35 (opus:low, opus:xhigh): plain, array decay, s32 extern, void * local, as1probe, uopt traces, permutes (no natural form).
- 2026-11-14 HackmenuInitMainScreen (opus), full-file objdump diff lines: plain 76; struct-typed extern 76.
## Untried ideas
none in natural C. There is no integer source for the address (no .data table or field), and a loop is ruled out by the target.
## Evidence
Background: calls between menuCheckSaveFile(0/1/2), indices 0/1/3; the only .data reference to D_8072052C is the sprite pointer table word at 0x8075547C
