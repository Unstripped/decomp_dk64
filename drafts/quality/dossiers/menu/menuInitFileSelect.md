# menuInitFileSelect (menu, src/menu/3E10.c)
## Sites
3244b7 (767) assetPtr = (void *)(s32)&D_8072052C: KEPT.
- Only the cvt pair makes the address one CSE value that is spilled and reloaded (Q0704/Q0341).
- Any pointer spelling is an lda that uopt rematerialises per call.
## Attempts
- rounds 1-35 (opus:low, opus:xhigh): plain, array decay, s32 extern, void * local, as1probe, uopt traces, permutes (no natural form).
- 2026-11-14 HackmenuInitMainScreen (opus), full-file objdump diff lines: plain 64; u8 *assetPtr 64; struct-typed extern 64.
- 2026-11-24 2026-11-24b: continue ReMeasureB18H (opus-5-5, base 127a3fd5; after cb17735e retyped gEffectSpriteGoldenBanana to EffectGridAsset), variants.py try full=: `assetPtr = &gEffectSpriteGoldenBanana` 16, `= (void *)&...` 16, `EffectGridAsset *assetPtr` assigned or initialised at the declaration 16, `void *assetPtr = &...` at the declaration 16 (all copy-propagated into per-call lda, Q1618); `assetPtr = (s32)&...` 0 but cfe Warning 712. Target: lui/addiu a1 0x1fbc/0x1fc0 before li t9,2 / li t0,3 0x1fc4/0x1fc8, sw a1,52(sp) 0x1fd4, lw a1,52(sp) 0x2018/0x205c, frame 0x40.
## Untried ideas
none in natural C. There is no integer source for the address (no .data table or field), and a loop is ruled out by the target.
## Evidence
Background: assetPtr spilled sw a1,52(sp) 0x1fd4, lw a1,52(sp) 0x2018; frame 0x40
