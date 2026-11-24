# menuInitMainScreen (menu, src/menu/3E10.c)
## Sites
8083be/35013b/3e828b/37e38b/26a14c (lines 470-474) `(void *)(s32)&D_80721444` arguments: KEPT (director RQ1 2026-11-20: D1 TERMINAL, re-measured nohit -> EXHAUSTED).
- The cast pair makes the address one ucvt CSE value: lui/addiu a1 once at 0xacc/0xad0, spilled `sw a1,48(sp)` at 0xae4 (frame 0x38), reloaded `lw a1,48(sp)` at 0xb18/0xb48/0xb78/0xba8 (Q0704/Q0341).
- Any pointer spelling is an lda constant that uopt rematerialises per call (frame 0x30, text +16).
- The conversion is the original implicit pointer-to-int argument conversion: with an `s32` asset parameter the whole file matches with no cast (see Evidence), but every one of the file's other calls then draws cfe Warning 712.
## Attempts
- rounds 1-35 (opus:low, opus:xhigh): plain, array decay, s32 extern, void * local, as1probe, uopt traces, permutes (no natural form).
- 2026-11-14 HackmenuInitMainScreen (opus), full-file objdump diff lines: plain 198 diff lines; struct-typed extern 198; initialised void * local 198.
- 2026-11-17 CleanmenuInitMainScreen (opus-5-5): menuSpawnUiElementEffect asset parameter retyped `s32` (stand-in `#define PROTO_SKIP_menuSpawnUiElementEffect` + `void menuSpawnUiElementEffect(struct MenuScreenState *, s32, s32, s32, f32, s32, s32);`, definition `s32 assetPtr` passing `(void *)assetPtr` to effectCreateAtPosition, all nine `(void *)(s32)` casts of the file dropped, menuInitFileSelect local `s32 assetPtr`) -> whole-file fdiff exit 0, but 68 cfe Warning 712 (illegal combination of pointer and integer) at the other calls. menuInitFileSelect with a `void *assetPtr` local instead: function 4 bytes longer; without the local: frame 0x38 vs target 0x40 (only diffs). Rejected by the cfe-warning ratchet.
- 2026-11-17 CleanmenuInitMainScreen: menuInitCharacterSelect with `(void *)(s32)` on its repeated &D_807211D0/&D_80720CF0 arguments still full=0 (the cvt is behaviour-neutral there), consistent with an integer parameter in the original TU.
- 2026-11-17 CleanmenuInitMainScreen: permuter (hack-free weights, -j 2, 900 s) from the all-plain body: base 1390, best 1206 (takes the address of a u8 * local, `*(q = &ptr)`, to force a memory home: a steer).
- 2026-11-20 CleanmenuInitMainScreenb (opus-5-5, re-measurement under RQ1 on base 65783e54; body: gMenuScreenSelection[1] split-label fold, sMenuCameraScript* renames; file: 3E10 .data to C 313d28b0, D_80721444 C-defined `EFFECT_GRID_ASSET(1)` in global/124780.c 734ba008), variants.py try full=:
  - one cast dropped: site 470 10 (first call rematerialises lui/addiu 0xacc/0xae0, the CSE web starts at the second call: lui/addiu 0xb00/0xb04, `sw a1,0x30(sp)` 0xb18); sites 471-474 5 each (lui/addiu replaces `lw a1,0x30(sp)` at 0xb18/0xb48/0xb78/0xba8).
  - all five dropped 28 (frame 0x30, text +16); `register void *asset = &D_80721444;` local 28 (copy-propagated lda); variants scan of the all-plain body: 18 swap/float variants, all 28.
  - uopt_trace -l 6: with the casts, candidates 16 `ucvt{1287}` and 17 `ucvt{137}` are the address value; bit 17 splits 79/80/82/84 and is never coloured (memory temp 0x30(sp)). Plain: no candidate (lda leaf).
- 2026-11-24 2026-11-24b: continue ReMeasureB18H (opus-5-5, base 127a3fd5; re-measure after cb17735e retyped gEffectSpriteBarrelEnd and the other sprite externs to EffectGridAsset, as 124780 defines them), variants.py try full=:
  - extern-type lever: five plain `&gEffectSpriteBarrelEnd` 28, five `(void *)&gEffectSpriteBarrelEnd` 28 (frame 0x30, lui/addiu a1 per call: still an lda constant); `EffectGridAsset *barrelEnd` initialised at the declaration or assigned before the first call 28 (copy-propagated, Q1618); `(s32)&gEffectSpriteBarrelEnd` without `(void *)` 0 but 5 cfe Warning 712 (illegal combination of pointer and integer); `(void *)(u32)` 0 (the same steer).
  - one cast dropped: 469 -> 10, 470-473 -> 5 each (unchanged).
  - uopt_trace -l 6: candidate 17 `ucvt{137}` (of 16 `ucvt{1287}`) is the address value; its first piece uopt 4 ($a1), split pieces 79/80/82/84 never coloured (memory temp 0x30(sp)), unchanged by the extern type.
## Untried ideas
none in natural C without the integer parameter; the parameter retype needs 68 caller casts or warnings (both worse). The EffectGridAsset extern type (cb17735e) changes nothing: the pointer spellings stay lda constants (2026-11-24b). A field read of the sprite would pointerize the lda (Q0470), but the target reads no field here.
## Evidence
Background: five unrolled calls (separate .rodata 1.2f literals 312-328(at) at 0xac8-0xb90); &D_80721444 lui/addiu once at 0xacc, sw a1,48(sp) 0xae4, lw a1,48(sp) 0xb18/0xb48/0xb78/0xba8; frame 0x38.
Integer-parameter test copies: `.scratch/CleanmenuInitMainScreen/t/proto_s32c.c` (fdiff 0, 68 warnings), `t/proto_s32b.c` (menuInitFileSelect frame only).
