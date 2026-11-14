# collisionTransformPointByActorMtx (global, src/global/6AD90.c)
## Sites
- global:8066A75C:other:cce365 `idx = gGfxBufferIndex ^ 1; idx = idx & 0xFF;`.
  - The target does mask: xori/andi at 0x4730/0x4734, with sub in v1.
  - Every one-statement spelling gives v0/v1 swapped (11).
  - Only xor-then-mask as two statements matches.
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
## Untried ideas
- why the sibling collisionTransformPointToActorLocal matches with the one-statement mask (different surrounding webs)
