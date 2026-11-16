# bonusTurtleTroubleSnakeUpdate (bonus, src/bonus/2690.c)
## Sites
bonus:8002881C:other:d2868d other: `s32 vb[2]` stack pair (index 0 at 0x40, base chk at 0x3c) read back as `vb[1] * 8 + vb[0]`; FIXED
## Attempts
2026-11-10..14 (history, 59 events): `p = chk` (frame 0x50, chk in a1); `s32 pad[2]` + `p = chk` (frame ok, no reloads); rot[n] with an s32 n home (n right, rot coloured a1); permuter runs; none matched.
2026-11-16 HackbonusTargetGameUpdate HackbonusTargetGameUpdate anthropic/claude-opus-5-5:high (variants try, function scores):
- `s32 n; BoneRotation *rot; n = 0; rot = chk; p = &rot[n]` -> 72 (n=0 propagated, rot copy-propagated into chk, a1).
- rot[n] index loops, chk tested, rot = chk copy -> 110 (chk coloured t0, spilled to 0x44 = chk's home).
- `s32 pad; s32 n; BoneRotation *chk;` + `s32 pad2` for p, chk tested, chk[n] loops -> 61 (chk coloured a1, spilled to 0x3c at the jal).
- same, `if (chk)` -> 61; separate tested chk + rot re-read from the field -> 3.
- null test on the field, `n = 0; rot = gCurrentActor->sub4->boneRotations;` inside the if -> 0 (rot before n=0 -> 2); p kept for the tail after the first loop -> 116.
Applied: zero variant, whole-file fdiff 0.
## Untried ideas
naming the two pad slots (0x44, 0x34) as real locals if their use is ever found.
## Evidence
Frame 0x58, no $s registers: snake 0x54, shooter 0x50, game 0x4c homes; 0x23a0 `lw v0,0x1c(t1)` boneRotations; 0x23a4 `beqzl v0`; 0x23ac `sw zero,0x40(sp)` (n), 0x23b0 `sw v0,0x3c(sp)` (rot); after mathSinF/mathCosF 0x2440 `lw t5,0x40(sp)`, 0x245c `lw t4,0x3c(sp)`, 0x2468 `sll t6,t5,3`, 0x24b4 `addu v0,t4,t6` (strength-reduced rot + n*8); loops step v0 by 8 / 16.
