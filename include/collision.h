#ifndef COLLISION_H
#define COLLISION_H

#include "common.h"

// Axis-aligned bounds (collisionCheckBoundingBoxXZ/Y); 0x18 bytes.
typedef struct CollisionBoundingBox {
    /* 0x00 */ f32 minX;
    /* 0x04 */ f32 minY;
    /* 0x08 */ f32 minZ;
    /* 0x0C */ f32 maxX;
    /* 0x10 */ f32 maxY;
    /* 0x14 */ f32 maxZ;
} CollisionBoundingBox; // size = 0x18

// Transformed collision box (ActorSub140.unkA4 array, built by actorSub140BuildBoxes); 0x58 bytes.
typedef struct CollisionBox {
    /* 0x00 */ u8 pad0[0x24];
    /* 0x24 */ s32 unk24;
    /* 0x28 */ s32 unk28;
    /* 0x2C */ s32 unk2C;
    /* 0x30 */ s32 unk30;
    /* 0x34 */ s32 unk34;
    /* 0x38 */ s32 unk38;
    /* 0x3C */ s32 unk3C;
    /* 0x40 */ s32 unk40;
    /* 0x44 */ s32 unk44;
    /* 0x48 */ s16 unk48;
    /* 0x4A */ u8 pad4A;
    /* 0x4B */ u8 unk4B;
    /* 0x4C */ u8 unk4C;
    /* 0x4D */ u8 unk4D;
    /* 0x4E */ s8 unk4E;
    /* 0x4F */ u8 unk4F;
    /* 0x50 */ u8 unk50;
    /* 0x51 */ u8 unk51;
    /* 0x52 */ u8 pad52[0x58 - 0x52];
} CollisionBox; // size = 0x58

#endif
