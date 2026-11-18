# collisionTransformPointByActorMtx (global, src/global/6AD90.c)
## Sites
- global:8066A75C:other:cce365 (REMOVED 2026-11-17f) `idx = gGfxBufferIndex ^ 1; idx = idx & 0xFF;`.
  - Steered colour order: the split mask raised idx (s32, M -4vreg) to adjsave 5/2 = 2.5 above sub
    (actor->collision, M -20vreg, bit 12) at 4/2 = 2.0, so idx coloured first into $v0 and sub took $v1.
  - Every one-statement spelling under the if/else tail leaves idx at 3/2 = 1.5: sub colours first into
    $v0, idx into $v1 (11 lines).
  - Fixed by the tail written as `switch (mtxOffset) { case -1: memcpy; break; default: guMtxL2F; break; }`
    with `u8 idx` in one statement (see Attempts 2026-11-17f).
## Attempts
- CleanD5E10, Rev16G, Rev17L, Rev22B (opus:low).
- 2026-11-14 U, scored with variants.py try (full=):
  - u8 snapshot: 11-22
  - compare swap: 11
  - declaration orders: 16
  - placement of sub/xIn/zIn/mtx: 14-48
  - mask spellings: 11-22
  - snapshot-then-xor: 14-37
  - one-case switch: 21
- 2026-11-17 "2026-11-17: cleanup CleancollisionTransformPointByActorMtx" CleancollisionTransformPointByActorMtx anthropic/claude-opus-5-5:
  - sibling census (uopt -l5): collisionTransformPointToActorLocal also has idx at 1.5, but its sub is
    4/3 = 1.333 (the tri-offset compare blocks make 6+ units, divisor 3) and tri->mtxOffset0 (4.0)
    takes $v0, so idx gets $v1 and sub $a3 there; the one-statement form works in the sibling only
    because its sub range is longer.
  - second reads of actor->collision (compare / nodeMtx / modelMtxF arm, u8 and s32): 18-40;
    no sub local at all: 14 (actor->collision CSE candidate 2.0 takes $v0, frame 4 smaller).
  - tail as `switch (mtxOffset) { case -1: ... default: ... }` (actorUpdateCollisionSpheres idiom,
    70FD0.c:2245): full 0 with u8 idx if/else, u8 idx ?:, s32 `(x ^ 1) & 0xFF`, s32 split mask;
    14 with s32 idx and no mask (no andi). default-first case order: 11. Kept: u8 idx if/else
    (the six other nodeMtx[bufIdx] selectors in 70FD0/7BBD0 use `u8 bufIdx`). fdiff 0, uninit 0.
  - permuter (hack-free weights, -j 2, 900 s) from the one-statement u8 if/else body: base 65, best 0,
    194 zeros, all steers: a dead `if (x) {}` on a live name between the join and the memcpy call
    (the same extra block in the sub range that the switch supplies) or `idx = gGfxBufferIndex;
    idx = idx ^ 1;` (statement split, idx 5/2 like the mask split). permute nohit.
## Untried ideas
- none for this function (no hack sites left).
## Evidence
- 0x4700 `lw v1,0x140(a0)` sub; 0x4708/0x4720 `lui v0,%hi(gGfxBufferIndex)`; 0x4728/0x472c `lbu v0`;
  0x4730 `xori t0,v0,1`; 0x4734 `andi v0,t0,0xff` (u8 truncation of the xor); 0x4738 `sll t2,v0,2`;
  0x4744 `lw a2,116(t3)` mtx.
- 0x4710 `li at,-1`, 0x4740 `bne a3,at,0x4760`: the case -1 compare of the switch; memcpy arm
  0x4748-0x475c, default arm 0x4760-0x4768; no extra instructions for the switch dispatch.
- uopt -l5 with the switch: sub live units bb0..bb5 (the switch compare adds bb4 between the join
  and the case -1 block) = 6, divisor 3, adjsave 4/3 = 1.333; idx 3/2 = 1.5 coloured first
  (forbidden [] -> 1 = $v0), sub second (forbidden [1 3 4 5] -> 2 = $v1).
