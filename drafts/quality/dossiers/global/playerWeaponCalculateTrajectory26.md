# playerWeaponCalculateTrajectory26 (global, src/global/F56F0.c)

## Sites
global:806F1B58:other:c2b7df  other: no final `return`; the fall-through exits leave `ret` in $v0
(0x1170 `sltu v0,zero,t6` -> `beqz v0`; 0x1188 `move v0,t8` in the `beqz t8` delay slot; 0x1198 `jr ra`).
Retagged `// ORIG:` (the target returns `ret` in $v0 with no return-value move; every explicit return form differs).

## Attempts
2026-11-15 HackplayerStateWaypointAimUpdate2 anthropic/claude-opus-5-5:high: variants.py try on the copy
(`t26/*.c`): `return ret;` full=10, `return 0;` 7, `ret = mode == kind; return ret;` 10,
`return (flags & 0x100) && !holdTimer && mode == kind;` 10, `!= 0 && == 0 &&` spelling 10,
`u8 ret` 12, `return ret` in both arms 11, assignment-in-condition `(ret = ...) && (ret = ...)` 10,
`!state->holdTimer` 10; return widths (PROTO_SKIP copy `t26/w_*.c.copy`): u8 ret/expr 12/10,
s16 14/13, u16 12/10. None 0 -> diagnose fixed as ORIG with the offsets above.

## Untried ideas
none (Q0230/Q0457/Q0580 all document this IDO fall-through idiom).

## Evidence
target .text (expected/build/src/global/F56F0.o) 0x1168-0x119c: `lw v0,96(a0); andi t6,v0,0x100;
sltu v0,zero,t6; beqz v0,0x1198; nop; lbu v0,20(a1); sltiu t8,v0,1; beqz t8,0x1198; move v0,t8;
lw t9,24(a1); xor v0,a2,t9; sltiu v0,v0,1; jr ra`.
