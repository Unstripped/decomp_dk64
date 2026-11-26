# arcadeSpawnStage4Enemies (arcade, src/arcade/0_game.c)
## Sites
arcade:800311E0:other:80f369 other (kept FAKE, R-oildrum part 1 fails): `u8 i` is the conveyor-clear counter (v1:
  `move v1,zero` 0xd1f8, loop 0xd240-0xd25c with `andi t1,v1,0xff` 0xd248, never stored) and the cement-pan slot
  (arcadeFindFreeEntityAfterPlayer's v0, `andi t3,v0,0xff` 0xd2a0 for the template copy, stored to i's home
  `sb v0,31(sp)` 0xd2f0 in the arcadeRand delay slot, reloaded `lbu v1,31(sp)` 0xd304).
## Attempts
2026-11-24 Polisharcade0e anthropic/claude-opus-5-5:xhigh: pre-existing reuse, tagged (R5); separate slot local after i
  moves the home to sp+0x1e; declared first it keeps home and frame but swaps v0/v1 in the loop and v1/a0 at +0x124.
2026-11-25c continue-lead-2 CleanarcadeUpdateOilDrumEntity anthropic/claude-opus-5-5 (base 9fb6f661): R-oildrum
  three-part census (director 2026-11-25c + refinements), bodies in census_s4/, scores `variants.py try`, stack slots from
  `as1probe keep` t.s, cfe offsets from `ucode --cfe` (census_s4/census_raw.txt). ORIG test (rulings.md:98-101) first:
  the slot role IS stored to i's own home (0x1f), but no separate local at the real (u8) width grows the frame (0x20 at
  every u8 position) and the counter is register-only (no second value spills to 0x1f): not ORIG.
## R-oildrum census (target R0: frame 0x20, slot home sb/lbu @0x1f, pointer spill sw/lw @0x18 (a0), counter v1)
Part 1, frame proof (`u8 i` counter + separate `slot`); "stack" = frame, slot home, pointer spill:
| body | position | score | frame | slot home | ptr spill | stack vs target |
|---|---|---|---|---|---|---|
| F_u8_u8_is | function scope, i then slot (u8) | 28 | 0x20 | 0x1e | 0x18 | slot home moves |
| F_u8_u8_si | function scope, slot then i (u8) | 27 | 0x20 | 0x1f | 0x18 | IDENTICAL (regs only: slot a0, ptr v1) |
| F_reg_is | i, `register u8 slot` | 28 | 0x20 | 0x1e | 0x18 | slot home moves |
| F_reg_si | `register u8 slot`, i | 27 | 0x20 | 0x1f | 0x18 | IDENTICAL (regs only) |
| F_reg2_si | slot, `register u8 i` | 27 | 0x20 | 0x1f | 0x18 | IDENTICAL (regs only) |
| B_slotblk_u8 / _reg | i function, slot in the `% 120` if block | 28 / 28 | 0x20 | 0x1e | 0x18 | slot home moves |
| B_ctrblk_u8 / _reg | slot function, counter in the else block | 27 / 27 | 0x20 | 0x1f | 0x18 | IDENTICAL (regs only) |
| B_both_u8 | counter in else block, slot in if block | 28 | 0x20 | 0x1e | 0x18 | slot home moves |
| F_u8_s8 is/si | slot s8 | 62 / 61 | 0x20 | 0x1e / 0x1f | 0x18 | lb for lbu; si stack identical |
| F_u8_u16 / s16 is/si | slot halfword | 29-62 | 0x20 | 0x1c / 0x1e | 0x18 | home moves |
| F_u8_s32 is/si, B_*_s32 | slot word | 63 | 0x28 | 0x20 / 0x24 | 0x1c | frame grows |
| F_s32_* (10 bodies) | counter s32 | 72-73 | 0x28 | various | 0x1c | frame grows |
Result: FAILS. At the slot-first and counter-block-scoped u8 positions (the values' real width: lbu/sb, andi 0xff) the
split keeps frame 0x20, the slot's home 0x1f and the pointer spill 0x18; the only effect is the colouring (slot a0,
pointer v1 instead of v1/a0). Register-only evidence (R5 / 12E800 near ruling).
Part 2, no-local (measured for the record): slot inline `gArcadeEntities[(u8)arcadeFindFreeEntityAfterPlayer()]` at
each use 125 (frame 0x18, several calls); `ArcadeEntity *pan` pointer local after/before i 48/49 (pointer homed 0x18/0x1c,
no slot byte); `static u8 slot` 89; counter loop unrolled into four stores 67. All fail.
Part 3 (not needed after part 1 fails): both roles u8 (andi 0xff 0xd248 / 0xd2a0), live in disjoint regions (counter in the
else arm of `(gArcadeScreenTimer & 1) == 0`, slot in the later `% 120` block).
Hidden-reuse check (director item 2026-11-25c): no other local takes a second value (i is the tagged site). None.
## Untried ideas
- none: every hack-free split is register-only at the slot-first position (FAKE stays under R5).
## Evidence
0xd1e8 addiu sp,sp,-32; ra 0x14; counter v1 0xd1f8-0xd25c; slot `sb v0,31(sp)` 0xd2f0 / `lbu v1,31(sp)` 0xd304; entity
pointer a0 spilled `sw a0,24(sp)` 0xd364 / `lw a0,24(sp)` 0xd378 across the second arcadeRand.
