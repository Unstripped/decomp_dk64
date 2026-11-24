# Names queue (continue-unit names stream)

Accepted proposals waiting for the next names window (`.omp/skills/continue-unit/names.md`). The lead appends after
the "Check"; the window that applies a line deletes it. Format:
`- [field|global|func] <seg or include/h.h> <Record|-> <old> -> <new> | <evidence, file:line> | <worker>`;
`held:` lines keep an item out until new evidence arrives.

## Queue
- [field] include/actor.h PlayerState unk78 -> pickupStepX, unk7C -> pickupStepZ, unk80 -> pickupYaw | CEAE0 playerStartPickupApproach (1916-1920) stores the per-frame x/z step and facing yaw; D5E10 playerStateHoldPickup adds the steps / sets yaw each frame | PolishglobalD5E10c (2026-11-24)
- [field] include/render.h EffectNode param -> frame, boneIndex -> modelSlot, subIndex -> nodeIndex, frameCount -> cellCount | 119370: param is the animation frame index compared with grid frames; boneIndex/subIndex from effectCreate's modelSlot/nodeIndex (modelSlotGetNodePos(modelSlot, 1, nodeIndex)); frameCount is width*height cells per frame | Polishglobal119370c (2026-11-24)
- [type] global/450_main_loop.c Struct80744464 -> ViModeByTvType (gLowResViModeByTvType, renamed eb53794b) | values {0xF, 2, 0x1E} are the low-res VI modes for PAL/NTSC/MPAL, same as gViModeIndexByTvType[osTvType * 2] | Polishglobal450c (2026-11-24)
- [type] include/actor.h G00Entry -> ViewportLayout, G01Pos -> SpawnPoint | G00Entry is the row type of gViewportLayouts[] (playerCount, splitScreenMode, viewMask, playerIndex, left/top/right/bottom); G01Pos the 10-byte map spawner rows (gMapSpawnPoints, gMapDefaultSpawnPoint, gSavedSlotSpawnPoint) | PolishglobalCC800e (2026-11-24)
- [local] race/1770_path_follow.c raceStartPathBoost (renamed eb53794b) param volume -> amount | stores the f32 to pathState->boostAmount, not a volume (1770:469 caller passes `bonus`) | TypesOwner15 (2026-11-24)

## Held
- held: [global] global D_80753C84 -> gKongPathRespawnTimers, D_80753CA4 -> gKongPathCheckRespawnTimers (worker: tentative) | per-kong s16 tables stored to respawnTimer every frame of playerStateAttachedCallbackFall/CheckFall while proxPathFollowerStep runs | PolishglobalD5E10c (2026-11-24)
