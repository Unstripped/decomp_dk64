# eepromValidateSaveSlots (global, src/global/104F0.c)
## Sites
global:8060CBBC:other:b73cc4 other -> ORIG: (u8)i & 0xFF at the first K&R eepromClearSlotData call: andi s3,s4 at 0x14ec + andi a0,s3 at 0x14f4
global:8060CBBC:other:b73cc4#2 other -> ORIG: second call, andi a0,s3 at 0x1630 (s3 = andi s3,s4 at 0x156c)
global:8060CBBC:dead-store:37b7c4 dead-store: ok = 0 between loops keeps ok/stored/index colouring (s0/s1/s2) (KEPT)
global:8060CBBC:dead-if:8fa679 dead-if: if (ok = D_80744530) {} in the third loop keeps ok in s0, stored in s1 (KEPT)
## Attempts
2026-11-10..12 Clean104F0 / Rev16B / Rev16D / Rev16H / CleanGlobal104F0 / Rev25B: traces, reconstructs, permutes (noted in history)
2026-11-14 HackeepromValidateSaveSlots opus-5-5:high: masks classified per spelling (plain 9/31, (u8)i 1 each, & 0xFF 9/30, (u8)(i & 0xFF) 83/89) -> ORIG; dead defs: single removals 46/118, both 151, initialisers, while-loop exit test, early continue, block slot2 (151-152), recipe scans (best 44)
## Untried ideas
dead defs: none natural found
## Evidence
0x14ec andi s3,s4,0xff; 0x14f4 andi a0,s3,0xff; 0x1518 andi a3,s3,0xff (eepromSetField u8 arg reuses s3); 0x156c andi s3,s4; 0x1630 andi a0,s3. ok: li s0,1 at 0x1480, move s0,zero at 0x14f0.
