#ifndef COMMON_H
#define COMMON_H

#include "ultra64.h"

f32 mathSinF(s16);
f32 mathCosF(s16);
s32 mathAsinFixed(s32);

// Hand-written asm (asm/global/17A10.s): polynomial sine/cosine of an angle in radians.
f32 sinApprox(f32);
f32 cosApprox(f32);

// A point in world space (mathPickCloserTargetPoint3D, 936B0.c).
typedef struct TargetVec3f {
    f32 x, y, z;
} TargetVec3f;

// A 3D float vector passed and returned by value (vec3f* helpers, 17540.c).
typedef struct Vec3f {
    f32 x, y, z;
} Vec3f;

extern u32 gGlobalPauseFlags;
extern u32 gFrameCounter;
extern u32 gGameFrameCounter; // advances like gFrameCounter except while gGlobalPauseFlags & 2 (450.c)

#endif
