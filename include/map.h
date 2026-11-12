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
    /* 0x00 */ s32 unk0;      // uncompressed size of the static collision asset (collisionInitStaticCache)
    /* 0x04 */ u32 unk4;      // uncompressed size of the collision mesh asset (collisionBuildCellTable)
    /* 0x08 */ u8 unk8;
    /* 0x09 */ u8 unk9;       // bit 0: static collision gzipped, bit 1: collision mesh gzipped
    /* 0x0A */ s16 unkA;
    /* 0x0C */ s16 fogDist;
    /* 0x0E */ s16 unkE;
    /* 0x10 */ s16 unk10;
    /* 0x12 */ s16 unk12;
    /* 0x14 */ s16 unk14;
    /* 0x16 */ s16 unk16;
    /* 0x18 */ s16 unk18;
    /* 0x1A */ s16 unk1A;
    /* 0x1C */ s16 unk1C;
    /* 0x1E */ s16 unk1E;
    /* 0x20 */ s16 unk20;
    /* 0x22 */ s16 unk22;
    /* 0x24 */ s16 unk24;
    /* 0x26 */ s16 unk26;
    /* 0x28 */ s16 unk28;
    /* 0x2A */ s16 unk2A;
    /* 0x2C */ s16 unk2C;
    /* 0x2E */ u8 pad2E[2];
    /* 0x30 */ s32 unk30;
    /* 0x34 */ s32 dlBase;
    /* 0x38 */ s32 unk38;
    /* 0x3C */ u8 pad3C[4];
    /* 0x40 */ s32 unk40;
    /* 0x44 */ s32 unk44;
    /* 0x48 */ s32 unk48;
    /* 0x4C */ s32 unk4C;     // water surfaces (effectWaterInitNodes)
    /* 0x50 */ s32 unk50;     // actor target quads (actorTargetTableLoad)
    /* 0x54 */ s32 unk54;     // trigger zones (triggerZoneInit)
    /* 0x58 */ s32 cellsOff;
    /* 0x5C */ s32 boxesOff;
    /* 0x60 */ s32 vecsOff;
    /* 0x64 */ s32 collOff;   // chunk collision table; its first word is the chunk count
    /* 0x68 */ s32 chunksOff;
    /* 0x6C */ s32 portalsOff;
    /* 0x70 */ s32 relocsOff;
} MapFileHeader; // size = 0x74

// One saved-map slot (D_8076A160[18], owned by src/global/3C10.c): the model slots and actor
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

#endif
