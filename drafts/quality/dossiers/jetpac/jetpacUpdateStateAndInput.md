# jetpacUpdateStateAndInput (jetpac, src/jetpac/0.c)

## Sites
jetpac:80025168:other:9d8530 other: the value-named `zero` local prevents uopt from retaining `&D_8002BA70` in `$v0`; literal zero changes the target's independent `lui $t6` load at 0x1168 and `lui $at` store at 0x11a8.

## Attempts
2026-11-10 cleanup round 7 CleanJetpac0 anthropic/claude-opus-5-5:low: permutation only moved the `D_8002BA70` store into a branch -> nohit.
2026-11-11 cleanup round 17 Rev17M anthropic/claude-opus-5-5:low: literal zero held `&D_8002BA70` in `$v0`; a `flag = 0` substitute was only another value-named local -> nohit.
2026-11-14 HackjetpacUpdateStateAndInput openai-codex/gpt-5.6-sol: checked the ANSI `s32 eepromGetField(s32, u8, u8, u8)` prototype; tested truthy byte tests, control-type load/chained-store forms, a typed byte snapshot, meaningful EEPROM index/sub-index/slot locals, a later first-assignment state local, and one-case selector switches; `variants.py scan` found no improving ordinary-C rewrite -> fdiff mismatch, original retained.

## Untried ideas
The owner redesign in `pending.md` can change `flagGet` from `u8` to `s32` across its definition and all callers; no local cast or prototype suppression is acceptable. It does not remove the separate `zero` regalloc steer.
No remaining local ordinary-C hypothesis avoids replacing the value-named local with another codegen-only construct.

## Evidence
The target loads `D_8002BA70` independently with `lui $t6` / `lbu $t6` at 0x1168-0x116c and stores with `lui $at` / `sb $zero` at 0x11a8-0x11ac.
With literal zero, uopt retains `&D_8002BA70` in `$v0`, changing those address-materialization instructions; the rest of the target is otherwise aligned, including `andi $t9,$v0,0xff` after `flagGet` at 0x11d4.
The file's `eepromGetField` declaration and definition are ANSI and return `s32`, so there is no K&R or return-width consolidation lever at that call.
