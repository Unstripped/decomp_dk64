# menuInitAdventureFileSelect (menu, src/menu/3E10.c)
## Sites
826fa7/32876d/f3492f (504/508/512) (void *)(s32)&D_8072052C arguments: KEPT.
- Only the cvt pair makes the address one CSE value that is spilled and reloaded (Q0704/Q0341).
- Any pointer spelling is an lda that uopt rematerialises per call.
## Attempts
- rounds 1-35 (opus:low, opus:xhigh): plain, array decay, s32 extern, void * local, as1probe, uopt traces, permutes (no natural form).
- 2026-11-14 HackmenuInitMainScreen (opus), full-file objdump diff lines: plain 76; struct-typed extern 76.
- 2026-11-24 2026-11-24b: continue ReMeasureB18H (opus-5-5, base 127a3fd5; after cb17735e retyped gEffectSpriteGoldenBanana to EffectGridAsset), variants.py try full=: three plain `&gEffectSpriteGoldenBanana` 16, three `(void *)&...` 16, `EffectGridAsset *banana` initialised or assigned before the first call 16 (copy-propagated, Q1618), `(s32)&...` without `(void *)` 0 but 3 cfe Warning 712; one cast dropped: 576 -> 9 (first call rematerialises lui/addiu after the li t0/t1 argument loads), 580 / 584 -> 4 each. Target: lui/addiu a1 0x1110/0x1114 before li t0,2 / li t1,2 0x1118/0x111c, sw a1,48(sp) 0x1128, lw a1,48(sp) 0x116c/0x11b0, frame 0x38.
## Untried ideas
none in natural C. There is no integer source for the address (no .data table or field), and a loop is ruled out by the target.
## Evidence
Background: calls between menuCheckSaveFile(0/1/2), indices 0/1/3; the only .data reference to D_8072052C is the sprite pointer table word at 0x8075547C
