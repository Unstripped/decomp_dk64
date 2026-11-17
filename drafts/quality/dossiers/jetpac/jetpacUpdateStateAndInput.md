# jetpacUpdateStateAndInput (jetpac, src/jetpac/0.c)

## Sites
jetpac:80025168:other:9d8530 other (removed 2026-11-17): the value-named `zero` local only mattered in the `D_8002BA70 = zero` store; it kept the `&D_8002BA70` lda web at one use so the target's independent `lui $t6` load at 0x1168 and `lui $at` store at 0x11a8 stayed. Replaced by the `u8 *initPending = &D_8002BA70` pointer local.

## Attempts
2026-11-10 cleanup round 7 CleanJetpac0 anthropic/claude-opus-5-5:low: permutation only moved the `D_8002BA70` store into a branch -> nohit.
2026-11-11 cleanup round 17 Rev17M anthropic/claude-opus-5-5:low: literal zero held `&D_8002BA70` in `$v0`; a `flag = 0` substitute was only another value-named local -> nohit.
2026-11-14 HackjetpacUpdateStateAndInput openai-codex/gpt-5.6-sol: checked the ANSI `s32 eepromGetField(s32, u8, u8, u8)` prototype; tested truthy byte tests, control-type load/chained-store forms, a typed byte snapshot, meaningful EEPROM index/sub-index/slot locals, a later first-assignment state local, and one-case selector switches; `variants.py scan` found no improving ordinary-C rewrite -> fdiff mismatch, original retained.
2026-11-17 HackjetpacUpdateStateAndInput2 anthropic/claude-opus-5-5: zero local only in the store still matches (eeprom args and `flag` test take literal 0); `D_8002BA70 = jetpacGame.controlType`, chained store, `= jetpacGame.gameState` score full=43; pointer local `u8 *initPending = &D_8002BA70` for the test and the clear (or only the clear) scores 0 -> fdiff OK, uninit 0, applied (test and clear through the pointer).

## Untried ideas
The owner redesign in `pending.md` can change `flagGet` from `u8` to `s32` across its definition and all callers (the file-scope `s32 flagGet(s32, s32)` ORIG declaration cites 0x11d4).

## Evidence
The target loads `D_8002BA70` independently with `lui $t6` / `lbu $t6` at 0x1168-0x116c and stores with `lui $at` / `sb $zero` at 0x11a8-0x11ac.
uopt_trace (-l 5): with the zero local, copy propagation rewrites `uistr{lda D_8002BA70}{zero}` into a direct `ustr{D_8002BA70 S 148}{0}`, leaving the lda web one use (bb0 load, not coloured). With literal 0 the store stays `uistr(lda)` in bb1, a 2-use web with adjsave +0.5 coloured into `$v0`. Accessing the flag through a `u8 *` local (Q0783) gives the same independent accesses.
The file's `eepromGetField` declaration and definition are ANSI and return `s32`.
