# playerWeaponCalculateTrajectory22 (global, src/global/F56F0.c)
## Sites
global:806F18F4:other:2fa922 other (kept): `angle = 0x16;` then `tableIndex = recoilTimer - angle;`.
- The 0x16 is folded into `addiu v1,v1,-22` at 0xf14, so the store emits no code.
- Its only effect is numbering: angle (M -6vreg) becomes uopt candidate 0 and tableIndex (M -4vreg) candidate 3.
- All four candidates (angle, tableIndex, slots a1, count a2) are "assigned (unconstrained)". They colour first-fit in candidate order, so adjsave ties do not matter.
- Result: angle gets reg 1 ($v0, lhu v0 at 0xf38) and tableIndex gets reg 2 ($v1, lbu v1 at 0xf10).
- Same mechanism as the siblings playerWeaponCalculateTrajectory4 (3ee789) and playerWeaponCalculateTrajectory7 (b7ba3b).
## Attempts
- rounds 3-37 (2026-11-09..13): see history.
  - Permuter best=0 only by restoring `angle = 0x16`, or by moving the steer to `angle = 4U` as the bound.
  - Q0725 fold of the table value into tableIndex: nohit.
- 2026-11-18 "2026-11-18: cleanup CleanplayerWeaponCalculateTrajectory22" CleanplayerWeaponCalculateTrajectory22 (variants.py try, full=):
  - Literal `recoilTimer - 0x16`: 9.
    - uopt -l6: tableIndex is cand 0 -> $v0 and angle cand 11 -> $v1. Swapped against the target.
  - `u32 tableIndex` with a `(s32)tableIndex >= 0` sign test and `tableIndex < 4`: 9.
  - Nested `if (tableIndex >= 0) { if ((u32)tableIndex < 4U) ... }`: 9.
  - Q0601 pointer local `PlayerState *player = gActivePlayerState;` (used once): 41 (text 48).
    - player is cand 0 and takes $v0. That gives tableIndex $v1 and angle $v0, the target colouring.
    - But the pointer load becomes `lui v0; lw v0` where the target has `lui t6; lw t6` (0xf04/0xf08). Every later $t register then shifts by one.
  - variants scan (swap/width/declswap) on the literal body: best 9, no zero.
  - Permuter run perm_t22 from the literal body (hack-free weights, -j 2, 900 s, base 60): best=0, with 21 zero outputs.
    - Every zero re-inserts a steer that numbers the value variable before tableIndex:
      - `angle = 0x16` as the subtrahend (7 outputs, one as `int new_var`).
      - `angle = 4U` as the bound (4 outputs).
      - `angle = 0` as the lower bound in `tableIndex >= angle` (4 outputs).
      - tableIndex reused for the table value, with `recoilTimer - 0x16` re-read in the sign test (5 outputs). The target loads recoilTimer once (lbu at 0xf10).
      - A dead `!count && !count && !count` assigned to angle (1 output).
    - Result: nohit.
## Untried ideas
- None natural. The target needs the table-value variable referenced before tableIndex in the ucode while emitting no code there.
  - Code-free forms are a dead initialiser (`u16 angle = 0;`, measured 0 by CleanplayerWeaponCalculateTrajectory7, Q0592: still a tagged steer) or a reused constant (this site).
  - Any live candidate placed earlier takes $v0 in bb0 and emits code there (timer/player locals).
## Evidence
- 0xf04 `lui t6` / 0xf08 `lw t6,0(t6)` (gActivePlayerState in a ugen temp, not a coloured local).
- 0xf10 `lbu v1,142(t6)` and 0xf14 `addiu v1,v1,-22`: tableIndex in $v1, base folded.
- 0xf18 `bltz v1` / 0xf1c `sltiu at,v1,4` / 0xf20 `beqz at`: signed test, then unsigned range test.
- 0xf2c-0xf38 `lui v0; addu v0,v0,t7; lhu v0`: the table value is in $v0.
- $v0 is written nowhere before 0xf2c. The candidate holding $v0 first must therefore emit no code in bb0/bb1.
- D_80752F38: u16 table, 4 entries (0x80752F38-0x80752F3F); its only user is this function.
