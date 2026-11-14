# eepromClearSlotData (global, src/global/104F0.c)
## Sites
global:8060C758:do-while0:e9a088 do-while0: made dst a coloured candidate (addiu t0 %lo(D_807ECEA8) at 0xfc4 before lui at %hi(D_807467C8)) (FIXED: u8 *dst = D_807ECEA8; dst += sector * size)
global:8060C758:noop-arith:afefd3 noop-arith: slotId ^ 0 keeps the two u8 argument conversions separate (andi a3,s0 at 0xffc and 0x100c) (KEPT)
## Attempts
2026-11-10..12 Clean104F0 / CleanGlobal104F0 / Rev16H (low, unlevelled): plain block (4 lines), as1probe scan (534 edits), permutes (goto label, redundant reassignments)
2026-11-14 HackeepromClearSlotData opus-5-5:high: 7 statement orders (4-49), dst base initialiser (0, applied); afefd3: 64 slot/slotId mixes (best 8), 80 param-width x mix variants on the new form (best 4: slot memory-resident), u8 slotId (10), global read-back (29)
## Untried ideas
afefd3: none natural found
## Evidence
0xf70 andi s0,a0,0xff; 0xf84 move a0,s0 (eepromGetSectorForSlot s32 param); 0xfc0-0xfd0 multu / addiu t0 / lui at / sb s0; 0xffc andi a3,s0 (first call); 0x100c andi a3,s0 (second call, value sw s0,16(sp)). Frame 0x28.
