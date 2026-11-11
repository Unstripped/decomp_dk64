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

// One world-space collision triangle (ModelTriBuffer.tri_start[], built by modelTriangleTransform); 0x28 bytes.
typedef struct CollisionTriF {
    /* 0x00 */ f32 x[3];
    /* 0x0C */ f32 y[3];
    /* 0x18 */ f32 z[3];
    /* 0x24 */ u8 unk24;
    /* 0x25 */ u8 unk25;
    /* 0x26 */ s8 unk26;
    /* 0x27 */ u8 unk27;
} CollisionTriF; // size = 0x28

// Transformed collision box (ActorSub140.unkA4 array, built by actorSub140BuildBoxes); 0x58 bytes.
typedef struct CollisionBox {
    /* 0x00 */ s64 nx; // plane normal (collisionBuildPlane: cross product of the two edges)
    /* 0x08 */ s64 ny;
    /* 0x10 */ s64 nz;
    /* 0x18 */ s64 d; // plane offset: -(n . vertex 1)
    /* 0x20 */ f32 len; // |n|; 0 = degenerate triangle
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
    /* 0x4A */ u8 axis; // dominant normal axis: 0 = z, 1 = y, 2 = x (collisionBuildPlane)
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
