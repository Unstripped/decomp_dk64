# modelSlotsLoadMap (global:80632084, src/global/36880.c)

## 2026-11-17 Polishglobal36880e (review after knowledge commit b8cbd3fa)
- Q0594 re-checked incl. the 2026-11-17 extension (s16 field -> u8 param = lbu low byte): no call in this function passes a wider field to a narrower param through a pun; all args are plain fields/globals.
- `u8 *pad;` is frame-only: removing it fails fdiff (frame shrinks).
- `if (entryCount > 0) do { ... } while (i < entryCount);` with `i = 0` at the top: rewriting as `for (i = 0; i < entryCount; i++)` (with or without the top `i = 0`) fails fdiff.
- `modelFlagsApplyState(gCurrentMap, gModelSlots[outCount].csModelId, ...)`: the target reloads the just-stored slot csModelId (slot+0x8A); passing `entry->mapObjectId` fails fdiff. Original data flow, not a steer.
- Casts kept: map asset blob = s32 count, count x ModelAssetEntry (0x30), s32 count, count x 0x24-byte {s32 modelIndex; u8 vars[0x20]} records (same layout modelAssetGetSubtables walks).
- clint uninit `entry` (line 278): read only inside the loop, which runs only when mapData != NULL, where entry is set; path-insensitive false positive.
- Name proposal (cross-file, include/model.h): ModelSlot.unk8C -> stateFlags.
