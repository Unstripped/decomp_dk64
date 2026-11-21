# eepromClearSlotData (global, src/global/104F0.c)
## Sites
global:8060C758:do-while0:e9a088 do-while0: made dst a coloured candidate (addiu t0 %lo(D_807ECEA8) at 0xfc4 before lui at %hi(D_807467C8)) (FIXED: u8 *dst = D_807ECEA8; dst += sector * size)
global:8060C758:noop-arith:afefd3 noop-arith: slotId ^ 0 kept the two u8 argument conversions separate (andi a3,s0 at 0xffc and 0x100c) (FIXED 2026-11-17: u32 slotId = slot for the int uses, the u8 parameter slot for both u8 arguments)
## Attempts
2026-11-10..12 Clean104F0 / CleanGlobal104F0 / Rev16H (low, unlevelled): plain block (4 lines), as1probe scan (534 edits), permutes (goto label, redundant reassignments)
2026-11-14 HackeepromClearSlotData opus-5-5:high: 7 statement orders (4-49), dst base initialiser (0, applied); afefd3: 64 slot/slotId mixes (best 8), 80 param-width x mix variants on the new form (best 4: slot memory-resident), u8 slotId (10), global read-back (29)
2026-11-17 CleaneepromClearSlotData anthropic/claude-opus-5-5 (afefd3):
- uopt trace -l 5/-l 6 of the plain body (s32 slotId in both calls, full=20): the u8 narrowing of both calls is ONE candidate, bit 34 `ucvtl{501}` (501 = `ucvt{P 3vreg}` = slotId after copy propagation), locdef bb2 / loclive bb3 (each eepromSetField call ends a block), so CODE MOTION (PRE) makes it a cross-call temp; global coloring assigns it reg 6 (a3, constrained) and ugen saves it around the call (sw a3,40(sp) / lw a3,40(sp)), frame 0x28 -> 0x40. With `^ 0` the second narrowing is the separate tree bits 37-39 `ucvtl{ucvt{uxor{501,0}}}`; ugen folds the xor into `andi a3,s0,0xff`.
- u8 slotId: a fresh `andi a3,s0,0xff` at every call, but the int uses become one CSE'd `ucvt(slotId)` temp in memory (sw s0,44(sp) / lw t2,44(sp), frame 0x40): 10; + sector from `slot` 10; + 5th arg `slot` 24
- per-role u8 copy next to s32 slotId (`id = slot`, `id = slotId` at entry / after bzero / `gEepromCurrentSlot = id = slotId` / `id = gEepromCurrentSlot = slotId`): 20-25
- K&R `int slot` with `slotId = (u8)slot` / `slot & 0xFF`, u8 args from the int param or a u8 local: 11-50
- permuter from the plain body (900 s, -j 2, hack-free weights, base 532): best 0 = `unsigned int slotId` with `slot` as both u8 arguments -> rewritten as `u32 slotId;` + `eepromSetField(0xC, 0, 0, slot, 1); eepromSetField(0xF, 0, 0, slot, slotId);`: fdiff 0, APPLIED. Neighbours: slot also for eepromGetSectorForSlot and/or the global store 0; slot only in the second call 0; s32 slotId with the same arguments 24; u16 slotId 10; u32 slotId in both calls 20.
- 2026-11-21 continue unit 1 Hack104F0 anthropic/claude-opus-5-5: review; K&R definition re-measured as ANSI: `(u8 slot, s32 save)` fdiff 1 (caller eepromSetCurrentSlot: target `andi t6,a0,0xff` at 0x1044 becomes `move a2,a0` + home store), `(s32 slot, s32 save)` fdiff 1 (callee home store `sw a0,0x28(sp)` at 0xf78 lost). K&R stays.
## Untried ideas
none (no hack site left)
## Evidence
0xf70 andi s0,a0,0xff; 0xf84 move a0,s0 (eepromGetSectorForSlot s32 param); 0xfc0-0xfd0 multu / addiu t0 / lui at / sb s0; 0xffc andi a3,s0 (first call); 0x100c andi a3,s0 (second call, value sw s0,16(sp)). Frame 0x28.
uopt (fixed form): `slotId = slot` with u32 slotId is `ustr{429}{10}` (no cvt for u8 -> u32), so every slotId use copy-propagates to the param byte P 3vreg (bit 5, coloured reg 14 = s0); the u8 arguments are P3 itself (no ucvtl candidate), re-narrowed by ugen at each u8 parameter; the 5th argument store is `ustr{1498|1}{10}` (P3, sw s0,16(sp)). With s32 slotId the int view is `ucvt{P3}` (501) and the narrowings `ucvtl{501}`, one CSE web.
Sibling idiom: eepromSetCurrentSlot (matched, next function) declares `u32 slot = slotId;` beside its u8 parameter. Sibling pattern in eepromValidateSaveSlots: cvtl(j) CSE'd into s0 (andi s0,s1,0xff at 0x15d0) with `andi a3,s0,0xff` per eepromGetField call (0x15d8, 0x15ec, 0x1624).
