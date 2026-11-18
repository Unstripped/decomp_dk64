# playerWeaponCalculateTrajectory4 (global, src/global/F56F0.c)
## Sites
- global:806F1858:other:3ee789 other (kept): `angle = 4U`; same candidate-order steer as Trajectory7.
  - Target: `lbu v1,0x8e`, `sltiu at,v1,4` at 0xe80, table value `lhu v0` at 0xe9c.
  - uopt -l5/-l6 (2026-11-18), literal bound: index {669} is cand 0, angle {637} cand 11, a1 {202} cand 17, a2 {266} cand 19.
    - All four are "assigned (unconstrained)", so first-fit in candidate order: index reg 1 ($v0), angle reg 2 ($v1).
    - index and angle both have adjsave 2.0, but the tie is irrelevant: unconstrained candidates never sort by adjsave.
    - They interfere through bb2: uopt live ranges are whole blocks, and index's last use (sll at 0xe88) and angle's def share the then-block.
  - With `angle = 4U`, angle is cand 0 and takes $v0; index is cand 3 and takes $v1. The 4 is propagated into the sltiu and the store emits no code.
## Attempts
- rounds 3-24: see history.
- 2026-11-14 U HackBoundLocalSizeofB opus:high (variants.py try full=):
  - `angle = sizeof(D_80752F30) / sizeof(D_80752F30[0])` with the extern sized [4]: 0 (not applied: the reuse of angle remains)
  - count local (u16/u32, before/after index): 9
  - literal: 9; inline sizeof: 9; declaration swap: 9
  - table pointer: 9; early return with a block-scoped angle: 9
  - s16 index: 51; no `index >= 0` test: 14
  - variants scan on the literal: 9
- 2026-11-18 "2026-11-18: cleanup CleanplayerWeaponCalculateTrajectory22" CleanplayerWeaponCalculateTrajectory22 (variants.py try full=):
  - `u32 index` with a `(s32)index >= 0` sign test: 9.
  - Nested ifs: 9.
  - `(*count)++`: 9.
  - Q0601 `PlayerState *player = gActivePlayerState;` local: 41 (text 48).
    - player is cand 0 and takes $v0, so index gets $v1 and angle $v0 as in the target.
    - The pointer load becomes `lui v0; lw v0` instead of `lui t6; lw t6` (0xe68/0xe6c), and the $t ring shifts by one for the rest of the body.
  - No angle local (table read inside the rotY store): 45 (shape 19).
  - variants scan on the literal: 9, no zero.
## Untried ideas
- None natural (see the playerWeaponCalculateTrajectory22 dossier: the $v0 holder must be referenced before index and emit no code in bb0/bb1).
- Lead decision (open since 2026-11-14): accept `angle = ARRAY_COUNT(D_80752F30)` (one temp, two roles, Q0214) as natural, or keep the tag. The 2026-11-18 rulings (Q0814 constant-local exception, reuse = steer) point to keep.
## Evidence
- D_80752F30: exactly 4 shorts, 0x80752F30-0x80752F37 (last 0xFA24); next label D_80752F38.
- 0xe68/0xe6c: `lui t6; lw t6` (gActivePlayerState in a ugen temp).
- 0xe74/0xe78: `lbu v1,142(t6); addiu v1,v1,-20`.
- 0xe90-0xe9c: `lui v0; addu v0,v0,t7; lhu v0`.
- $v0 is first written at 0xe90.
