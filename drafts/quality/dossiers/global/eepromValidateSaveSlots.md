# eepromValidateSaveSlots (global, src/global/104F0.c)
## Sites
global:8060CBBC:other:b73cc4 other -> ORIG: (u8)i & 0xFF at the first K&R eepromClearSlotData call: andi s3,s4 at 0x14ec + andi a0,s3 at 0x14f4
global:8060CBBC:other:b73cc4#2 other -> ORIG: second call, andi a0,s3 at 0x1630 (s3 = andi s3,s4 at 0x156c)
global:8060CBBC:dead-store:37b7c4 dead-store: ok = 0 between loops kept ok s0 / stored s1 -> FIXED 2026-11-15 (the global-CRC block uses its own u32 globalOk in the old pad word)
global:8060CBBC:dead-if:6c4c65 (base key 8fa679) dead-if: if (version) {} after found = version = ... in the third loop: two empty blocks in the version/i/j live ranges (version adjsave 42 -> 35, i 41 -> 38.27, j 131.25 -> 116.67, found 36.67) so i s4, found s5, version s6 (KEPT, class 1: any int local works; the old ok = D_80744530 reuse is no longer needed once globalOk exists)
global:8060CBBC:dead-store:2e4194 dead-store (copy-only, pre-existing, now tagged): (j = i + 1) embedded in the loop-1 idx product; j is dead but the assignment puts i + 1 left in multu s2,t9 at 0x14b4 (Q0519) (KEPT)
## Attempts
2026-11-10..12 Clean104F0 / Rev16B / Rev16D / Rev16H / CleanGlobal104F0 / Rev25B: traces, reconstructs, permutes (noted in history)
2026-11-14 HackeepromValidateSaveSlots opus-5-5:high: masks classified per spelling -> ORIG; dead defs: single removals 46/118, both 151, initialisers, while-loop exit test, early continue, block slot2 (151-152), recipe scans (best 44)
2026-11-15 HackeepromCopySlot anthropic/claude-opus-5-5:high:
- pad/pad2 -> u32 latest holding eepromGetField(0x10, i) (inline assign 151, nested if 154; with ok = 0 kept 46/55): no effect
- ok as a real def in the third loop (ok = eepromGetField(0xD, i) in the test: 60 with both defs gone, 46 with ok = 0; ok = valid[i]: 100): reuse rejected anyway (steer)
- third-loop structure on the old base: merged valid && field-D test (151/46), outer continue (152/47), inner nested if (151/46), field-D continue (160/113)
- globalOk (u32 in pad, or pad2) for the second ok role in the global-CRC block: both defs gone 32, dead-if kept + ok = 0 gone -> 0 (APPLIED, fdiff 0); globalStored for stored: 36 (worse)
- on top of globalOk without the dead-if: found = X; version = found (29), version = found = X (29), version = X; found = version (32); compare with found (39); while form (29); nested ifs (29)
- inner `if (j == i || valid[j] == 0) continue;` (Q0523): 4 (f1 order), 8 (found = version = X), 4 (version = found = X); plus loop test `version == found`: 3 (only found/version colour s5/s6 swapped)
- from that 3-line base: split continues (3), field-D continue (3), field-D || field-F continue (5), slot2 before continue (3), outer continue (4), merged outer test (3), found = 0xFF after the calls (4), for-init found = version (7)
- permuter on the f1 base (globalOk, no dead defs, found = X; version = found), 900 s hack-free weights: base 170, best 10 = an added if (!version) {} in the sector-fill loop (another dead test)
- dead test respelled: if (found) / if (i) / if (version) / if (D_80744530) {} all 0, if (globalOk) 37, if (off) 25; applied if (version) {}
- j = i + 1 embedded store: SIZE * (i + 1) and (i + 1) * SIZE 1 (multu t9,s2), j = i + 1 statement before idx / at loop top 1, j * SIZE 1, for (...; i = j) 106; variants scan on the plain form best 1
## Untried ideas
raise found above version (found adjsave 31.4 over 22 blocks vs version 35.0 over 20 in the continue form; the dead-if base has found 36.67 over 18): a natural construct that starts found's live range after a block that version spans (uopt counts found from its def in bb16)
## Evidence
0x14ec andi s3,s4,0xff; 0x14f4 andi a0,s3,0xff; 0x1518 andi a3,s3,0xff (eepromSetField u8 arg reuses s3); 0x156c andi s3,s4; 0x1630 andi a0,s3. ok: li s0,1 at 0x1480, move s0,zero at 0x14f0; global CRC block li s0,1 at 0x17a4, move s0,zero at 0x1800 (globalOk), stored lw s1 at 0x17e4. Third loop: andi v1/s6/s5 of v0 at 0x15a4-0x15b0 (entry test temp, version, found), bne v1,v1 entry test, move s2,s6 at 0x15f4 (cvt of version for the field-F compare), li s5,255 at 0x1634, beq s6,s5 at 0x1674, sb s5 at 0x1680.
uopt (level 5, base): ok adjsave 15.75 with the dead def vs 10.75 without (stored 11.0); version 35.0 vs 42.0, i 38.27 vs 41.0, j 116.67 vs 131.25 (one extra block unit each), found 36.67 both.
