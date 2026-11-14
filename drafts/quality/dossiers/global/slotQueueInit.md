# slotQueueInit (global, src/global/FCCD0.c)

## Sites
- da5663 / 06d21a: the mapGetHubWorldIndex PROTO_SKIP define plus the K&R extern. KEPT, not ORIG.
  - The shared u8 prototype matches if the bitfield helpers pass `map` rather than `map & 0xFF`. Only slotQueueAddValue then differs (addu v1/a0 at 0x1368).
- ab9e8a: dead `player && player`. FIXED: `s32 player = (u8)i` (word home of a byte value).
- 0930b5: kongInv two-step. KEPT (addu operand order at 0x494).

## Evidence
- 0x48c `lbu a0,155(sp)`; 0x4a0 `sw a0,120(sp)`.
- 0x494 `addu t9,s8,t8`.
- 0x1428/0x1468/0x14ac `andi a0,a1,0xff` before the jal.
