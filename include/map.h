#ifndef MAP_H
#define MAP_H

#include "common.h"

// One ambient sound emitter of the map geometry file (mapGetSoundEmitters); 8 bytes.
typedef struct LevelSoundEmitter {
    /* 0x0 */ s16 x;
    /* 0x2 */ s16 y;
    /* 0x4 */ s16 z;
    /* 0x6 */ u8 volume;
    /* 0x7 */ u8 group;
} LevelSoundEmitter; // size = 0x8

// Map geometry file header (asset table 1; mapHeaderLoad and the per-subsystem init calls it makes).
// Offsets 0x30.. are byte offsets from the header start to the file's sections.
typedef struct MapFileHeader {
    /* 0x00 */ s32 staticCollisionSize;      // uncompressed size of the static collision asset (collisionInitStaticCache)
    /* 0x04 */ u32 collisionMeshSize;      // uncompressed size of the collision mesh asset (collisionBuildCellTable)
    /* 0x08 */ u8 renderFlags;
    /* 0x09 */ u8 gzipFlags;       // bit 0: static collision gzipped, bit 1: collision mesh gzipped
    /* 0x0A */ s16 farClip;
    /* 0x0C */ s16 fogDist;
    /* 0x0E */ s16 matrixCacheLimitKb;
    /* 0x10 */ s16 staticCellsX;
    /* 0x12 */ s16 staticCellsZ;
    /* 0x14 */ s16 staticCellSizeX;
    /* 0x16 */ s16 staticCellSizeZ;
    /* 0x18 */ s16 meshCellsX;
    /* 0x1A */ s16 meshCellsZ;
    /* 0x1C */ s16 meshCellSizeX;
    /* 0x1E */ s16 meshCellSizeZ;
    /* 0x20 */ s16 defaultSpawnX;
    /* 0x22 */ s16 defaultSpawnY;
    /* 0x24 */ s16 defaultSpawnZ;
    /* 0x26 */ s16 boundMinX;
    /* 0x28 */ s16 boundMinZ;
    /* 0x2A */ s16 boundMaxX;
    /* 0x2C */ s16 boundMaxZ;
    /* 0x2E */ u8 pad2E[2];
    /* 0x30 */ s32 bspOff;
    /* 0x34 */ s32 dlBase;
    /* 0x38 */ s32 vtxBase;
    /* 0x3C */ u8 pad3C[4];
    /* 0x40 */ s32 trackPointsOff;
    /* 0x44 */ s32 soundEmittersOff;
    /* 0x48 */ s32 chunkAnimsOff;
    /* 0x4C */ s32 waterSurfacesOff;     // water surfaces (effectWaterInitNodes)
    /* 0x50 */ s32 targetQuadsOff;     // actor target quads (actorTargetTableLoad)
    /* 0x54 */ s32 triggerZonesOff;     // trigger zones (triggerZoneInit)
    /* 0x58 */ s32 cellsOff;
    /* 0x5C */ s32 boxesOff;
    /* 0x60 */ s32 vecsOff;
    /* 0x64 */ s32 collOff;   // chunk collision table; its first word is the chunk count
    /* 0x68 */ s32 chunksOff;
    /* 0x6C */ s32 portalsOff;
    /* 0x70 */ s32 relocsOff;
} MapFileHeader; // size = 0x74

// One saved-map slot (gSavedMapSlots[18], owned by src/global/3C10.c): the model slots and actor
// records of a map left in the background, restored by actorMapModelsSetup.
typedef struct Struct8076A160 {
    /* 0x00 */ u8 inUse;
    /* 0x01 */ u8 pad1;
    /* 0x02 */ s16 flags;
    /* 0x04 */ f32 x;
    /* 0x08 */ f32 y;
    /* 0x0C */ f32 z;
    /* 0x10 */ s16 yaw;
    /* 0x12 */ s16 map;
    /* 0x14 */ u8 returnExitIndex;
    /* 0x18 */ u8 *modelData;
    /* 0x1C */ s32 recordSize;
    /* 0x20 */ u8 *records;
    /* 0x24 */ u8 rgb[52][3];
} Struct8076A160; // size = 0xC0

// One map BSP tree node (src/global/2F550.c): kind 0 split nodes use child0/child1 and the
// split plane, kind 1 leaves are drawn by mapTreeRender/mapViewDrawPass, kind 2 nodes by
// mapChunksRender (src/global/55B20.c).
typedef struct MapBspNode {
    /* 0x00 */ struct MapBspNode *child0;
    /* 0x04 */ struct MapBspNode *child1;
    /* 0x08 */ s32 dl; // display list address, or -1 when the node has none
    /* 0x0C */ s32 unkC; // leaf display lists, -1 when absent
    /* 0x10 */ s32 unk10;
    /* 0x14 */ s32 unk14;
    /* 0x18 */ s32 unk18;
    /* 0x1C */ void *unk1C[12]; // per-entry display lists drawn by mapViewDrawPass
    /* 0x4C */ f32 planeNx; /* split plane normal x */
    /* 0x50 */ f32 planeNy;
    /* 0x54 */ f32 planeNz;
    /* 0x58 */ f32 planeD; /* split plane d */
    /* 0x5C */ s16 planeVertX[3];
    /* 0x62 */ s16 planeVertY[3];
    /* 0x68 */ s16 planeVertZ[3];
    /* 0x6E */ s16 unk6E; // added to D_807F5E64 when a leaf is drawn
    /* 0x70 */ s16 surfaceEffects[12];
    /* 0x88 */ s16 surfaceChunks[12];
    /* 0xA0 */ s16 minX; /* bounds min x/y/z, max x/y/z */
    /* 0xA2 */ s16 minY;
    /* 0xA4 */ s16 minZ;
    /* 0xA6 */ s16 maxX;
    /* 0xA8 */ s16 maxY;
    /* 0xAA */ s16 maxZ;
    /* 0xAC */ u8 surfaceOffsetSlots[12];
    /* 0xB8 */ u8 kind; /* 0 split node, 1 leaf, 2 map chunks */
    /* 0xB9 */ u8 surfacePasses[12];
    /* 0xC5 */ u8 surfaceCount; // entry count of the per-entry arrays
} MapBspNode;

// Per-map audio entry (gMapAudioTable, indexed by map id): the map's song (450.c), its base volume
// (7130.c) and mapActionLookupEntry's fallback action (F4C0.c).
typedef struct MapAudioEntry {
    /* 0x0 */ u8 songId;
    /* 0x1 */ u8 volume;
    /* 0x2 */ s16 defaultAction;
} MapAudioEntry; // size = 0x4

extern MapAudioEntry gMapAudioTable[];

#endif
