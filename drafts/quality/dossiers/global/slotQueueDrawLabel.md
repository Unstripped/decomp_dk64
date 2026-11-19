# slotQueueDrawLabel (global, src/global/FCCD0.c)

## Sites
- f22aa7: dead `displayMode == 0` read in case 2. OPEN (FAKE kept). The fdiff-0 fix from 2026-11-18c (CleanslotQueueDrawLabelb: an s32
  selector local at its use, declared after `label`, with `u8 text[8]` -> `text[4]`) was REJECTED at merge (Lead20261118c, director
  condition: the text size must hold every reachable output).
  - Why it fits the bytes: `mode`'s home word takes text's old upper half (0x70-0x73), which the target never touches. Text is only addressed as sp+108, and nothing reads or writes 112..115(sp). So the frame (0x78), text 108, alpha 107, width 92 and the slot*48 spill at 48(sp) stay where they were. The int-width selector gets no shared cfe switch temp (Q0944) and takes v0, and the pointer takes v1.
  - Why it was rejected: text[4] holds `o`, `NA` and a `%d` only up to 999. Two reachable values are not capped at 999 by code: slot 1 coins (F9450.c:621, item 0xB7 adds 5 to every kong's `coins` directly, bypassing slotQueueAddValue's 0x3E7 clamp) and slot 9 (slotQueueUpdateGoldenBananaTotal sums 5 kongs x 14 u16 goldenBananas, each clamped only to 100; slotQueueGetMaxValue's 0xC8 is never applied to it). Game content keeps both at 3 digits, but no cap proves it; text[8] holds any u16 (5 digits + NUL).
  - Analysis of the dead read:
  - Without it the selector is a2 and the slot pointer v0; the target has v0 and v1.
  - Q0908 class: same-value. Only a displayMode read works (1, slot, .x, .shown, gfx, text[0]: 7 = removal). It works anywhere between guTranslate and the first call of an arm (before the switch, start of case 1/2/default); after an arm's _sprintf or after the switch it does not.
  - Mechanism (uopt -l5/-l6, 2026-11-17f): the 2-case switch lowers to a compare chain on cfe's temp -68vreg (cand 40), which is also the `%d` ternary result, so it is adjsave 3.0 and takes a2. The dead read is a second use of ucvt{uilod displayMode} (cand 48) in case 2's block, which makes that expression its own web: adjsave 1.5, v0. The slot pointer uixa (cand 46, 1.33) then gets v1. On removal cand 48 is not a candidate (one use, folded into the temp store), so the temp a2 gets the lbu and the pointer gets v0.
  - There is no uadd(sel,0) copy: the switch is not an xjp. The B5EC0 lever (Q0875) does not apply.

## Attempts
- 2026-11-14 U HackslotQueueInit: 7-106 lines (see the ledger).
- 2026-11-16 U HackslotQueueStateFadeIn2 (anthropic/claude-opus-5-5:high): classification above; real two-read selections (if/else-if chain, nested switch in default, if (mode == 1) else switch, switch with if/else in default) all 31: IDO lowers them to an if-chain `bne` layout.
- 2026-11-17f U CleanslotQueueDrawLabel (anthropic/claude-opus-5-5):
  - sweep re-run: plain and recipe nohit.
  - Selector local at its use (`mode = gSlotQueue[slot].displayMode; switch (mode)`), every width at 5 declaration positions plus block scope (30 bodies):
    - s32/u32/s16 declared last or in a block: 3. Registers match; only the slot*48 spill moves from 0x30(sp) to 0x2c(sp).
    - s32/u32 after alpha, viewport or scale: 6. After text: 10. First: 15.
    - s16 after alpha: 0. This is the 2026-11-12 variant, which the lead rejected (ce024b7a) as a width steer. s8 after alpha: 1 (lb instead of lbu).
    - u8/u16 (the field's width) after alpha: 18. Mode takes v0 (2.0), the temp a2 (1.5), and the no-code u8->int ucvt{mode} (cand 51, 1.5) takes v1, so the pointer drops to a0. Elsewhere: 28-50.
  - Frame: label -4 (0x74), text -12 (0x6c), alpha -13 (0x6b, homed), then a 3-byte alignment gap at -16..-14, viewport -20, scale -24, width -28 (0x5c, homed), 9 GBI `_g` block locals -32..-64, the switch/ternary temp -68, and the spill at 0x30. An int-width selector needs a 4-aligned word that is not free, so it adds one. Only a 1-2 byte local fits the gap.
  - variants scan of the s32 mode body: nothing below 3. `mode` s16 gives 3 there, because the gap is only reached when it is declared after alpha.
  - Named s32 `count` for the `%d` value (`count = ternary;` or an if/else) and no dead read: 3. The switch gets its own cfe temp -72 (1.5), which takes v0; the pointer takes v1 and count a2. That is one frame word more (spill 0x2c). This explains the 2026-11-15 permuter hint ("%d ternary into an s32 temp"): the selector lands in a2 only because cfe reuses the switch temp for the ternary result. u8/u16/s16 count: 84-125.
  - permuter, 900 s, -j 2, hack-free weights, base 12 (the s32 selector-local body, fdiff 3; the first base with v0/v1 already right): 17006 iterations, nothing below 12.
- 2026-11-18c U CleanslotQueueDrawLabelb (anthropic/claude-opus-5-5): sweep plain/recipe nohit, removal re-measured 7. Fix: s32 or u32 `mode` after `label` with text[4], [3] or [2], and also `switch (mode = ...)`: all 0. Proposed s32 with text[4]; rejected at merge (overflow, above). Also tried: `register s32`/`register u32` mode declared last 3, `register s32 count` 3 (the register class still allocates a home, Q1002), and a `displayMode & 0xFF` selector 94.

## Untried ideas
- A text-size change is closed unless every printed value is provably capped at 3 digits. Within text[8], an int-width selector still costs a frame word (3).

## Evidence
- 0x1f0c `addu v1,t6,t5`, 0x1f10 `lbu v0,44(v1)`.
- 0x1f5c: `slot == 5` is compiled as `slot*48 == 240` using the spilled offset at 48(sp).
- Frame 0x78: alpha `sb t8,107(sp)` 0x1e9c, width `sw zero,92(sp)` 0x1ea0, label `sw t6,116(sp)` 0x1dd4, text `addiu a0,sp,108` 0x1f18.
- Every stack access in the function (expected objdump): ra 36, s0 32, a0 home 120, a1 home 124, label 116, alpha 107, width 92, the spill 48, outgoing args 16/20, and text only as sp+108 (0x1f18, 0x1f2c, 0x1fbc, 0x215c, 0x216c). Nothing touches 112..115.
