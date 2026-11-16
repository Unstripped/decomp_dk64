# schedMain (global, src/global/13980.c)

## Sites
global:8060EE60:dead-if:465d17 (removed, HackschedMain): `if (sSchedState.retraceCount == 0) {}` at the end of the D_807563B4 block. Coupled class (Q0908): its extra block kept lda D_8074682C / D_80746848 uncoloured (`if (1) {}` there gives 13: only the 0x29A part left), and the sSchedState lda reaching it across the loop kept case 0x29A at separate `lui` pairs (else `lui v1; addiu v1` base, `lw v0,0(v1)` / `sw v0,0(v1)`). Replaced by function-local statics (Q0761/Q0922): `static u32 sRetraceCount` (0x807F0560) and `static s8 sFirstAdvanceSkipped = 0` (0x80746848, was D_80746848). Neither has an lda web, so every access keeps its own lui/%lo pair.
global:8060EE60:other:c7f4d5 (tag dropped, HackschedMain): `cnt = x + 1; x = cnt; if (cnt % 480 == 0)`. cnt holds the new count for two uses (the store and the test), so it is ordinary C (Q0601), not a copy temp. Q0980: no other spelling matches (with the static too: `++sRetraceCount % 480` / `sRetraceCount++` 32).
global:8060EE60:other:b97c35 (ORIG, HackschedMain): `if (osSendMesg(...) == -1) {}`. The target runs the compare at 0x4f0 `li at,-1` / 0x4f4 `bnel v0,at,0x250`, and both arms go back to the loop head (0x4fc `b 0x250`). Q0791: an empty test on a call result is original code.

## Attempts
2026-11-16 U HackschedMain anthropic/claude-opus-5-5 465d17 operand classes (variants try; the base scores 2 in the reduced TU, from a bnezl/bnez tail artifact, Q0497): any sSchedState field (retraceCount, taskDone, pad.button) 2; `1`, D_807F04D8, D_807F04C8, D_807F0518[0] 13; cnt 15, sc 21, fbIdx 32, flag 39, i 42, D_8074682C 123, D_807563B4 105; `x && x` on retraceCount 46, `i && i` 32; removal 44.
2026-11-16 U HackschedMain 465d17 positions: loop top / first statement in the D_807563B4 block 25, after osWritebackDCacheAll 33, before the switch 40, case 0x2A0 46.
2026-11-16 U HackschedMain case 0x29A spellings, each with `if (1) {}` in place of the read (ld/++cnt store, cnt++, chained assign, `u32 *rc` pointer, test on the field): 13-29; none colours the case lda differently.
2026-11-16 U HackschedMain struct views: D_807F0540 + sSchedState merged into one {OSTimer; retraceCount; taskDone; pad} at 0x807F0540: 11 with the read, 24 without (fixes D_8074682C, not D_80746848 or the 0x29A lda); separate u32/s32/OSContPad globals 15 / 46.
2026-11-16 U HackschedMain D_807563B4 block shapes without the read: empty-then/else on D_8074682C > 0 36, `if (D_807563B4)` 44 (the behaviour-changing forms were dropped).
2026-11-16 U HackschedMain function-local statics: `static u32 sRetraceCount` alone, no read -> only D_80746848's lda left (text 8); + `static s8 D_80746848 = 0` -> text match (also with D_80746844 static; D_80746830 static matches the text but cannot sit at 0x80746830 in front of schedCreate's D_80746838); D_8074682C static 99 (it needs its lda web). Layout: a 12-byte {taskDone; pad} struct after the static is 8-aligned (.bss 192 vs 176), so taskDone and pad become function-local statics of schedTaskDone / schedDlDebugDump (file-scope OSContPad: schedDlDebugDump 10). D_8074684C / D_80746858 move below schedMain. fdiff TEXT OK, --reloc-ok RELOC-EQUIV OK, masked text and relocation offsets/types equal (fixed).
2026-11-16 U HackschedMain permuter on the read-free copy (struct carve), 900 s -j 2: see ledger.

## Untried ideas
none for schedMain. For schedDlDebugDump (not this function): with `static OSContPad sContPad` its a7e052 `held` copy temp becomes removable (`buttons = sContPad.button;` and `s32 pad;` in held's slot -> RELOC-EQUIV OK, .scratch/HackschedMain/dd_plainpad.c).

## Evidence
0x448 `lui v0,%hi(sSchedState)` / 0x44c `lw v0` / 0x450 `lui at` / 0x45c `sw v0,%lo(..)(at)`: separate pairs, no lda base.
0x3a8 `lui t6,%hi(D_80746848)` / 0x3c4 `lb t6` / 0x3cc `lui at` / 0x3dc `sb t7,%lo(..)(at)`: separate pairs.
0x4f0 `li at,-1` / 0x4f4 `bnel v0,at,0x250` / 0x4fc `b 0x250`: osSendMesg result compare, both arms rejoin.
.bss 0xa0/0xa4/0xa8 (0x807F0560/64/68) are used only by schedMain, schedTaskDone and schedDlDebugDump, in source order. schedDlDebugDump already keeps its state in function-local statics.
