# mapChunkLoadAssetRefs / mapChunkReleaseAssets (global, src/global/55B20.c)

## Sites
- 834154 (mapChunkLoadAssetRefs): `if (cmd && cmd) {}` in the 0xFD branch. REMOVED.
  - It lowered the adjsave of `end` and `limit` (3.67 -> 2.75) below the 0xFD constant (3.33), so the constant took s2 (target 0x3010 `li s2,253`) and end/limit took s3/s4.
- d13434 (mapChunkReleaseAssets): `if (orig) {}`, an uninitialised dead read. REMOVED.
  - Same mechanism: `end` must colour last (s6, target 0x3098).

## Attempts
- 2026-11-14 U HackmapChunkLoadAssetRefs:
  - The switch on the opcode matches in both functions (fdiff 0). mapChunkReleaseAssets needs the `op` local in the switch; switching on the expression directly gives 6 diff lines.
  - Other forms all 13-17 diff lines: kind as u32 or u8, merged condition, Gfx * view, while or for loop, s16 count, declaration swap.

## Untried ideas
- Walk the list as `Gfx *` in both functions. This needs the gMapChunks loadStart/loadCursor/loadEnd field types and the call sites at 1324-1363.

## Evidence
- uopt -l5 for mapChunkLoadAssetRefs:
  - Base: cand 47 (0xFD const) 3.33 -> s2; cand 5 (end) 2.75 -> s3; cand 10 (limit) 2.75 -> s4.
  - Without the dead test: end and limit 3.67 -> s2/s3; the const -> s4.
  - With the switch: matches the base.
