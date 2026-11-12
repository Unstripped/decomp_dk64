#include "common.h"
#include "compiler/ido/memory.h"
#include "actor.h"
#include "render.h"
#include "sched.h"
#include "proto/global/126260.h"
#include "proto/global/2F550.h"
#include "proto/global/55B20.h"
#include "proto/global/5E2F0.h"
#include "proto/global/61AA0.h"
#include "proto/global/69E60.h"

extern u8 gLightNextFlags;
extern s16 gLightNextOwnerId;
extern s16 gLightNextActiveRadius;

void lightSetFlags(u8 flags) {
    gLightNextFlags = flags;
}

void lightSetTargetId(s16 targetId) {
    gLightNextOwnerId = targetId;
}

void lightSetRadius(s16 radius) {
    gLightNextActiveRadius = radius;
}

extern f32 *gChunkLightR;
extern f32 *gChunkLightG;
extern f32 *gChunkLightB;

void lightGetColor(f32 *outR, f32 *outG, f32 *outB, s16 index) {
    *outR = gChunkLightR[index];
    *outG = gChunkLightG[index];
    *outB = gChunkLightB[index];
}

extern s32 gMapChunkCount;

void lightSetColor(f32 r, f32 g, f32 b, s16 index) {
    u8 count;
    s32 i;

    if (gMapChunkCount <= 0) {
        count = 1;
    } else {
        count = gMapChunkCount;
    }
    if (index != -1) {
        if (index < count) {
            gChunkLightR[index] = (r <= 1.0f) ? r : 1.0f;
            gChunkLightG[index] = (g <= 1.0f) ? g : 1.0f;
            gChunkLightB[index] = (b <= 1.0f) ? b : 1.0f;
        }
    } else {
        for (i = 0; i < count; i++) {
            gChunkLightR[i] = (r <= 1.0f) ? r : 1.0f;
            gChunkLightG[i] = (g <= 1.0f) ? g : 1.0f;
            gChunkLightB[i] = (b <= 1.0f) ? b : 1.0f;
        }
    }
}

extern f32 *gChunkLightTargetR;
extern f32 *gChunkLightTargetG;
extern f32 *gChunkLightTargetB;

void lightCopyTargetColors(s16 index) {
    u8 count;
    s32 i;

    if (gMapChunkCount <= 0) {
        count = 1;
    } else {
        count = gMapChunkCount;
    }

    if (index != -1) {
        if (index < count) {
            gChunkLightR[index] = gChunkLightTargetR[index];
            gChunkLightG[index] = gChunkLightTargetG[index];
            gChunkLightB[index] = gChunkLightTargetB[index];
        }
    } else {
        for (i = 0; i < count; i++) {
            gChunkLightR[i] = gChunkLightTargetR[i];
            gChunkLightG[i] = gChunkLightTargetG[i];
            gChunkLightB[i] = gChunkLightTargetB[i];
        }
    }
}

void lightSetTargetColor(f32 r, f32 g, f32 b, s16 index) {
    u8 count;
    u8 i;

    if (gMapChunkCount <= 0) {
        count = 1;
    } else {
        count = gMapChunkCount;
    }

    if (index != -1) {
        if (r <= 1.0f) {
            gChunkLightTargetR[index] = r;
        } else {
            gChunkLightTargetR[index] = 1.0f;
        }
        if (g <= 1.0f) {
            gChunkLightTargetG[index] = g;
        } else {
            gChunkLightTargetG[index] = 1.0f;
        }
        if (b <= 1.0f) {
            gChunkLightTargetB[index] = b;
        } else {
            gChunkLightTargetB[index] = 1.0f;
        }
    } else {
        for (i = 0; i < count; i++) {
            if (r <= 1.0f) {
                gChunkLightTargetR[i] = r;
            } else {
                gChunkLightTargetR[i] = 1.0f;
            }
            if (g <= 1.0f) {
                gChunkLightTargetG[i] = g;
            } else {
                gChunkLightTargetG[i] = 1.0f;
            }
            if (b <= 1.0f) {
                gChunkLightTargetB[i] = b;
            } else {
                gChunkLightTargetB[i] = 1.0f;
            }
        }
    }
}

void lightLerpColors(f32 r, f32 g, f32 b, f32 t, s16 index) {
    u8 count;
    s32 i;

    if (gMapChunkCount <= 0) {
        count = 1;
    } else {
        count = gMapChunkCount;
    }

    if (index != -1) {
        if (index < count) {
            gChunkLightR[index] = ((gChunkLightTargetR[index] - r) * t) + r;
            gChunkLightG[index] = ((gChunkLightTargetG[index] - g) * t) + g;
            gChunkLightB[index] = ((gChunkLightTargetB[index] - b) * t) + b;
        }
    } else {
        for (i = 0; i < count; i++) {
            gChunkLightR[i] = ((gChunkLightTargetR[i] - r) * t) + r;
            gChunkLightG[i] = ((gChunkLightTargetG[i] - g) * t) + g;
            gChunkLightB[i] = ((gChunkLightTargetB[i] - b) * t) + b;
        }
    }
}

extern s16 gLightVolumeCount;
extern f32 D_807F7ECC;
extern f32 D_807F7ED0;
extern f32 D_807F7ED4;
extern f32 D_807F7ED8;
extern f32 D_807F7EDC;
extern f32 D_807F7EE0;
extern f32 D_807F7EE4;
extern f32 D_807F7EE8;
extern s16 gLightNextRange;

void lightInitGlobals(void) {
    D_807F7ECC = cosApprox(0.4363323152f);
    D_807F7ED0 = cosApprox(1.134464025f);
    D_807F7ED4 = 1.0f / (D_807F7ECC - D_807F7ED0);
    D_807F7ED8 = D_807F7ECC;
    D_807F7EDC = D_807F7ED0;
    D_807F7EE0 = D_807F7ED4;
    D_807F7EE4 = 25.0f;
    D_807F7EE8 = 65.0f;
    gLightVolumeCount = 0;
    gLightNextFlags = 0;
    gLightNextOwnerId = -1;
    gLightNextActiveRadius = 700;
    gLightNextRange = 600;
}

void lightClearCount(void) {
    gLightVolumeCount = 0;
}

extern s16 gActiveLightCount;
void lightClearActiveCount(void) {
    gActiveLightCount = 0;
}

void lightSetFovAngles(f32 angleA, f32 angleB) {
    D_807F7EE4 = angleA;
    D_807F7EE8 = angleB;
    D_807F7ED8 = cosApprox(angleA * 0.017453292f);
    D_807F7EDC = cosApprox(angleB * 0.017453292f);
    D_807F7EE0 = 1.0f / (D_807F7ED8 - D_807F7EDC);
}

void lightSetDistanceThreshold(s16 dist) {
    gLightNextRange = dist;
}

typedef struct LightVolume {
    /* 0x00 */ f32 innerAngle;
    /* 0x04 */ f32 cosInner;
    /* 0x08 */ f32 outerAngle;
    /* 0x0C */ f32 cosOuter;
    /* 0x10 */ f32 coneScale;
    /* 0x14 */ f32 radius;
    /* 0x18 */ f32 x;
    /* 0x1C */ f32 y;
    /* 0x20 */ f32 z;
    /* 0x24 */ f32 targetX;
    /* 0x28 */ f32 targetY;
    /* 0x2C */ f32 targetZ;
    /* 0x30 */ s16 ownerId;
    /* 0x32 */ s16 activeRadius;
    /* 0x34 */ s16 range;
    /* 0x36 */ u8 r;
    /* 0x37 */ u8 g;
    /* 0x38 */ u8 b;
    /* 0x39 */ u8 type;
    /* 0x3A */ u8 flags;
    /* 0x3B */ u8 pad3B;
} LightVolume;

extern LightVolume gLightVolumes[];

void lightAdd(f32 x, f32 y, f32 z, f32 targetX, f32 targetY, f32 targetZ, f32 radius, u8 type, u8 r, u8 g, u8 b) {
    if (gLightVolumeCount != 0x10) {
        gLightVolumes[gLightVolumeCount].range = gLightNextRange;
        gLightVolumes[gLightVolumeCount].flags = gLightNextFlags;
        gLightVolumes[gLightVolumeCount].ownerId = gLightNextOwnerId;
        gLightVolumes[gLightVolumeCount].activeRadius = gLightNextActiveRadius;
        gLightVolumes[gLightVolumeCount].outerAngle = D_807F7EE8;
        gLightVolumes[gLightVolumeCount].innerAngle = D_807F7EE4;
        gLightVolumes[gLightVolumeCount].cosOuter = D_807F7EDC;
        gLightVolumes[gLightVolumeCount].cosInner = D_807F7ED8;
        gLightVolumes[gLightVolumeCount].type = type;
        gLightVolumes[gLightVolumeCount].x = x;
        gLightVolumes[gLightVolumeCount].y = y;
        gLightVolumes[gLightVolumeCount].coneScale = D_807F7EE0;
        gLightVolumes[gLightVolumeCount].z = z;
        gLightVolumes[gLightVolumeCount].targetX = targetX;
        gLightVolumes[gLightVolumeCount].targetY = targetY;
        gLightVolumes[gLightVolumeCount].targetZ = targetZ;
        gLightVolumes[gLightVolumeCount].radius = radius;
        gLightVolumes[gLightVolumeCount].r = r;
        gLightVolumes[gLightVolumeCount].g = g;
        gLightVolumes[gLightVolumeCount].b = b;
        gLightVolumeCount++;
        D_807F7ED8 = D_807F7ECC;
        D_807F7EDC = D_807F7ED0;
        D_807F7EE0 = D_807F7ED4;
        D_807F7EE4 = 25.0f;
        D_807F7EE8 = 65.0f;
        gLightNextFlags = 0;
        gLightNextOwnerId = -1;
        gLightNextActiveRadius = 700;
        gLightNextRange = 600;
    }
}

extern s32 D_80748304;
extern s32 D_80748308;
extern u8 gPlayerCount;
extern ActorEntry gActiveActors[];
extern u16 gActiveActorCount;


void lightApplyToActors(void) {
    s32 i;
    s32 j;
    s32 lightCount;
    Actor *actor;
    f32 dot;
    f32 dist;
    f32 d[3];
    f32 dist2d;
    f32 a[3];
    f32 dirX;
    f32 dirY;
    f32 dirZ;
    f32 maxDist;
    f32 edgeDist;
    f32 scale;
    s16 angle;
    u8 litActors[64];
    f32 shadowScale[2];
    f32 innerDist;
    f32 range;
    s32 pad;
    f32 factor;
    f32 alpha;

    lightCount = 0;
    for (i = 0; i < gActiveActorCount; i++) {
        litActors[i] = 0;
    }
    for (i = 0; i < gLightVolumeCount && gPlayerCount < 3; i++) {
        if ((lightCheckPlayerDistance(&gLightVolumes[i]) != 0) && (lightCount < 12)) {
            lightCount++;
            for (j = 0; j < gActiveActorCount; j++) {
                actor = gActiveActors[j].actor;
                if (actor->flags & 0x2000) {
                    continue;
                }
                switch (gLightVolumes[i].type) {
                case 1:
                    d[0] = gLightVolumes[i].targetX - gLightVolumes[i].x;
                    d[1] = gLightVolumes[i].targetY - gLightVolumes[i].y;
                    d[2] = gLightVolumes[i].targetZ - gLightVolumes[i].z;
                    dist = sqrtf((d[0] * d[0]) + (d[1] * d[1]) + (d[2] * d[2]));
                    if (dist == 0.0f) {
                        dist = 0.1f;
                    }
                    dirX = d[0] / dist;
                    dirY = d[1] / dist;
                    dirZ = d[2] / dist;
                    d[0] = actor->x - gLightVolumes[i].x;
                    d[1] = actor->y - gLightVolumes[i].y;
                    d[2] = actor->z - gLightVolumes[i].z;
                    dist = sqrtf((d[0] * d[0]) + (d[1] * d[1]) + (d[2] * d[2]));
                    if (dist == 0.0f) {
                        dist = 0.1f;
                    }
                    a[0] = d[0] / dist;
                    a[1] = d[1] / dist;
                    a[2] = d[2] / dist;
                    dot = (a[0] * dirX) + (a[1] * dirY) + (a[2] * dirZ);
                    if (dot < 0.0f) {
                        dot = 0.0f;
                    }
                    if (gLightVolumes[i].cosOuter <= dot) {
                        if (gLightVolumes[i].cosInner <= dot) {
                            dot = 1.0f;
                        } else {
                            dot -= gLightVolumes[i].cosOuter;
                            dot *= gLightVolumes[i].coneScale;
                        }
                        commandQueuePush(actor, gLightVolumes[i].x, gLightVolumes[i].y,
                                         gLightVolumes[i].z, 0xFF, gLightVolumes[i].r * dot,
                                         gLightVolumes[i].g * dot, gLightVolumes[i].b * dot,
                                         0);
                        if ((actor->flags & 0x01000000) && (actor->flags & 4)) {
                            dist = sqrtf(((gLightVolumes[i].x - actor->x) * (gLightVolumes[i].x - actor->x)) +
                                         ((gLightVolumes[i].z - actor->z) * (gLightVolumes[i].z - actor->z)));
                            dist2d = (dist != 0) ? dist : 0.001f;
                            scale = (gLightVolumes[i].y - actor->y) / dist2d;
                            if (!(scale > 0)) {
                                scale = -scale;
                            }
                            if (scale == 0.0f) {
                                scale = 0.1f;
                            }
                            scale = (actor->eyeHeight * 0.4f) / scale;
                            angle = mathAngleBetweenPoints2D(gLightVolumes[i].x, gLightVolumes[i].z, actor->x,
                                                             actor->z);
                            if (actor->sub4 != NULL) {
                                shadowScale[0] = actor->sub4->scaleX;
                                shadowScale[1] = actor->sub4->scaleZ;
                            } else {
                                shadowScale[0] = 0.15f;
                                shadowScale[1] = 0.15f;
                            }
                            alpha = actor->alpha / 255.0;
                            billboardSubmit(actor, 0x3C9, 0x40, 0x40, actor->unk16E[0] * shadowScale[0],
                                            actor->unk16E[1] * shadowScale[1], 1, 0x64,
                                            D_80748304 * dot * alpha, angle + 0xC00, scale * dot);
                            litActors[j] = 1;
                        }
                    }
                    break;
                case 0:
                    edgeDist = sqrtf(((gLightVolumes[i].x - actor->x) * (gLightVolumes[i].x - actor->x)) +
                                     ((gLightVolumes[i].y - actor->y) * (gLightVolumes[i].y - actor->y)) +
                                     ((gLightVolumes[i].z - actor->z) * (gLightVolumes[i].z - actor->z))) -
                               actor->boundingRadius;
                    if (edgeDist < 0.0) {
                        edgeDist = 0.1f;
                    }
                    maxDist = gLightVolumes[i].radius * 1.3f;
                    if ((actor->flags & 0x01000000) && (edgeDist < maxDist) && (actor->flags & 4)) {
                        dist2d = sqrtf(((gLightVolumes[i].x - actor->x) * (gLightVolumes[i].x - actor->x)) +
                                       ((gLightVolumes[i].z - actor->z) * (gLightVolumes[i].z - actor->z)));
                        if (dist2d == 0.0f) {
                            dist2d = 1.0f;
                        }
                        scale = (gLightVolumes[i].y - actor->y) / dist2d;
                        if (!(scale > 0)) {
                            scale = -scale;
                        }
                        if (scale == 0.0f) {
                            scale = 0.1f;
                        }
                        scale = (actor->eyeHeight * 0.4f) / scale;
                        angle = mathAngleBetweenPoints2D(gLightVolumes[i].x, gLightVolumes[i].z, actor->x,
                                                         actor->z);
                        if (scale > 10.0f) {
                            scale = 10.0f;
                        }
                        if (actor->sub4 != NULL) {
                            shadowScale[0] = actor->sub4->scaleX;
                            shadowScale[1] = actor->sub4->scaleZ;
                        } else {
                            shadowScale[0] = 0.15f;
                            shadowScale[1] = 0.15f;
                        }
                        litActors[j] = 1;
                    }
                    innerDist = maxDist / 3.0f;
                    if (edgeDist < innerDist) {
                        commandQueuePush(actor, gLightVolumes[i].x, gLightVolumes[i].y,
                                         gLightVolumes[i].z, 0xFF, gLightVolumes[i].r, gLightVolumes[i].g,
                                         gLightVolumes[i].b, 0);
                        if ((actor->flags & 0x01000000) && (actor->flags & 4)) {
                            alpha = actor->alpha / 255.0;
                            billboardSubmit(actor, 0x3C9, 0x40, 0x40, actor->unk16E[0] * shadowScale[0],
                                            actor->unk16E[1] * shadowScale[1], 1, 0x64,
                                            D_80748304 * alpha, angle + 0xC00, scale);
                        }
                    } else {
                        edgeDist -= innerDist;
                        range = maxDist - innerDist;
                        if (edgeDist < range) {
                            factor = 1.0f - (edgeDist / range);
                            commandQueuePush(actor, gLightVolumes[i].x, gLightVolumes[i].y,
                                             gLightVolumes[i].z, 0xFF, gLightVolumes[i].r * factor,
                                             gLightVolumes[i].g * factor,
                                             gLightVolumes[i].b * factor, 0);
                            if ((actor->flags & 0x01000000) && (actor->flags & 4)) {
                                alpha = actor->alpha / 255.0;
                                billboardSubmit(actor, 0x3C9, 0x40, 0x40,
                                                actor->unk16E[0] * shadowScale[0],
                                                actor->unk16E[1] * shadowScale[1], 1, 0x64,
                                                D_80748304 * factor * alpha, angle + 0xC00,
                                                scale * factor);
                            }
                        }
                    }
                    break;
                }
            }
        }
    }
    for (i = 0; i < gActiveActorCount; i++) {
        if (litActors[i] == 0) {
            actor = gActiveActors[i].actor;
            if ((actor->flags & 0x01000000) && (actor->flags & 4)) {
                if (actor->sub4 != NULL) {
                    shadowScale[0] = actor->sub4->scaleX;
                    shadowScale[1] = actor->sub4->scaleZ;
                } else {
                    shadowScale[0] = 0.15f;
                    shadowScale[1] = 0.15f;
                }
                alpha = actor->alpha / 255.0;
                billboardSubmit(actor, 0x3C9, 0x40, 0x40, actor->unk16E[0] * shadowScale[0],
                                actor->unk16E[1] * shadowScale[1], 1, 0x64,
                                D_80748308 * alpha, 0, 1);
            }
        }
    }
}

typedef struct LightTrigger {
    /* 0x00 */ f32 cosOuter;
    /* 0x04 */ f32 cosInner;
    /* 0x08 */ f32 coneScale;
    /* 0x0C */ f32 dirX;
    /* 0x10 */ f32 dirY;
    /* 0x14 */ f32 dirZ;
    /* 0x18 */ s32 rangeSq;
    /* 0x1C */ f32 invFalloffLength;
    /* 0x20 */ f32 falloffStart;
    /* 0x24 */ f32 invFadeLength;
    /* 0x28 */ f32 fadeStart;
    /* 0x2C */ f32 r;
    /* 0x30 */ f32 g;
    /* 0x34 */ f32 b;
    /* 0x38 */ s16 x;
    /* 0x3A */ s16 y;
    /* 0x3C */ s16 z;
    /* 0x3E */ u8 type;
    /* 0x3F */ u8 volumeIndex;
} LightTrigger;

extern LightTrigger gLightCandidates[];
extern LightTrigger gActiveLights[];
extern s16 gLightCandidateCount;
s16 lightCollectVolumesInBounds(f32 x, f32 y, f32 z, s16 minX, s16 minY, s16 minZ, s16 maxX, s16 maxY, s16 maxZ, s32 targetId, s8 *outFlag) {
    f32 pad[3];
    f32 diff[3];
    f32 dist;
    f32 innerRadius;
    s32 i;

    *outFlag = 0;
    gLightCandidateCount = 0;
    for (i = 0; i < gLightVolumeCount; i++) {
        if (lightCheckVolumeBounds(&gLightVolumes[i], x, y, z, minX, minY, minZ, maxX, maxY, maxZ, targetId)) {
            if (gLightCandidateCount < 12) {
                if (gLightVolumes[i].flags & 1) {
                    *outFlag = 1;
                }
                gLightCandidates[gLightCandidateCount].volumeIndex = i;
                gLightCandidates[gLightCandidateCount].x = gLightVolumes[i].x * 3.0f;
                gLightCandidates[gLightCandidateCount].y = gLightVolumes[i].y * 3.0f;
                gLightCandidates[gLightCandidateCount].z = gLightVolumes[i].z * 3.0f;
                gLightCandidates[gLightCandidateCount].r = gLightVolumes[i].r / 255.0;
                gLightCandidates[gLightCandidateCount].g = gLightVolumes[i].g / 255.0;
                gLightCandidates[gLightCandidateCount].b = gLightVolumes[i].b / 255.0;
                gLightCandidates[gLightCandidateCount].type = gLightVolumes[i].type;
                switch ((u32)gLightVolumes[i].type) {  // FAKE: u32 switch operand on the u8 type keeps the original jump-table compare
                case 1:
                    diff[0] = gLightVolumes[i].targetX - gLightVolumes[i].x;
                    diff[1] = gLightVolumes[i].targetY - gLightVolumes[i].y;
                    diff[2] = gLightVolumes[i].targetZ - gLightVolumes[i].z;
                    dist = sqrtf((diff[0] * diff[0] + diff[1] * diff[1]) + diff[2] * diff[2]);
                    if (dist == 0.0f) {
                        dist = 0.1f;
                    }
                    gLightCandidates[gLightCandidateCount].dirX = diff[0] / dist;
                    gLightCandidates[gLightCandidateCount].dirY = diff[1] / dist;
                    gLightCandidates[gLightCandidateCount].dirZ = diff[2] / dist;
                    gLightCandidates[gLightCandidateCount].cosInner = gLightVolumes[i].cosInner;
                    gLightCandidates[gLightCandidateCount].rangeSq = 0x127690;
                    gLightCandidates[gLightCandidateCount].cosOuter = gLightVolumes[i].cosOuter;
                    gLightCandidates[gLightCandidateCount].coneScale = gLightVolumes[i].coneScale;
                    break;
                case 0:
                    if (gLightVolumes[i].radius == 0.0f) {
                        gLightVolumes[i].radius = 0.1f;
                    }
                    dist = gLightVolumes[i].radius * 3.0f;
                    gLightCandidates[gLightCandidateCount].rangeSq = dist * dist;
                    innerRadius = (gLightVolumes[i].radius / 3) * 3.0f;
                    gLightCandidates[gLightCandidateCount].invFalloffLength = 1.0f / (gLightVolumes[i].radius * 3.0f - innerRadius);
                    gLightCandidates[gLightCandidateCount].falloffStart = innerRadius;
                    gLightCandidates[gLightCandidateCount].fadeStart = ((gLightVolumes[i].radius * 1.3f) / 3) * 3.0f;
                    gLightCandidates[gLightCandidateCount].invFadeLength = 1.0f / ((gLightVolumes[i].radius * 1.3f) * 3.0f - gLightCandidates[gLightCandidateCount].fadeStart);
                    break;
                }
                lightAddDedupEntry(gLightCandidateCount);
                gLightCandidateCount++;
            }
        }
    }
    return gLightCandidateCount;
}

void lightAddDedupEntry(s16 index) {
    s32 i;
    u8 val;

    if (gActiveLightCount != 12) {
        val = gLightCandidates[index].volumeIndex;
        for (i = 0; i < gActiveLightCount; i++) {
            if (val == gActiveLights[i].volumeIndex) {
                return;
            }
        }
        memcpy(&gActiveLights[gActiveLightCount++], &gLightCandidates[index], sizeof(LightTrigger));
    }
}

extern f32 D_807F5E20[];
extern PlanePoly gFrustumPlanes[];

s32 lightCheckVolumeBounds(LightVolume *light, f32 x, f32 y, f32 z, s16 minX, s16 minY, s16 minZ, s16 maxX, s16 maxY, s16 maxZ, s32 targetId) {
    Mtx viewMtx;
    f32 dx, dy;

    if ((light->flags & 2) && (targetId != light->ownerId) && (minX != -0x8000)) {
        return 0;
    }

    dx = light->x - x;
    dy = light->y - y;
    if (sqrtf((dx * dx) + (dy * dy) + ((light->z - z) * (light->z - z))) < light->activeRadius) {
        if (minX == -0x8000) {
            return 1;
        }
        switch (light->type) {
        case 0:
            if ((light->x < minX - light->radius) ||
                (light->y < minY - light->radius) ||
                (light->z < minZ - light->radius) ||
                (maxX + light->radius < light->x) ||
                (maxY + light->radius < light->y) ||
                (maxZ + light->radius < light->z)) {
                return 0;
            }
            return 1;
        case 1:
            guLookAt(&viewMtx, light->x, light->y, light->z, (light->x == light->targetX) ? (light->targetX + 0.2f) : light->targetX, light->targetY, light->targetZ, 0.0f, 1.0f, 0.0f);
            frustumCalculateCornerRays(light->outerAngle * 2, 1.0f, light->range);
            frustumCornersTransformByInverse(&viewMtx);
            frustumOrientPolyNormals(light->x, light->y, light->z, gFrustumPlanes, D_807F5E20);
            planeFromTwoPoints(light->x, light->y, light->z, light->targetX, light->targetY, light->targetZ);
            return mapBspBoxInFrustum(minX, minY, minZ, maxX, maxY, maxZ, light->x, light->y, light->z, light->range, gFrustumPlanes);
        }
        return 0;
    }
    return 0;
}



extern PlayerStruct *gPlayerSlots;
extern u8 gViewportCount;
#define SQ(x) ((x) * (x))

s32 lightCheckPlayerDistance(LightVolume *light) {
    s32 i;

    for (i = 0; i < gViewportCount; i++) {
        if (gPlayerSlots[i].active != 0) {
            if (sqrtf(SQ(light->x - gPlayerSlots[i].camX) + SQ(light->y - gPlayerSlots[i].camY) + SQ(light->z - gPlayerSlots[i].camZ)) < light->activeRadius) {
                return 1;
            }
        }
    }
    return 0;
}




void lightSampleColorAtPosition(f32 x, f32 y, f32 z, s16 radius, u8 *outR, u8 *outG, u8 *outB, s16 chunk) {
    s32 i;
    f32 r;
    f32 g;
    f32 b;
    f32 dist;
    f32 dot;
    f32 factor;
    if (mapChunkIsInUse(chunk) == 0) {
        *outR = *outG = *outB = 0xFF;
        return;
    }
    if (gActiveLightCount == 0) {
        *outR = (s32)(gChunkLightR[chunk] * 255.0f);
        *outG = (s32)(gChunkLightG[chunk] * 255.0f);
        *outB = (s32)(gChunkLightB[chunk] * 255.0f);
        return;
    }
    r = gChunkLightR[chunk]; g = gChunkLightG[chunk]; b = gChunkLightB[chunk];  // LAYOUT: one line changes as1 scheduling of the three loads

    for (i = 0; i < gActiveLightCount; i++) {
        switch (gActiveLights[i].type) {
        case 1: {
            f32 d[3];
            f32 n[3];
            d[0] = x - gActiveLights[i].x / 3;
            d[1] = y - gActiveLights[i].y / 3;
            d[2] = z - gActiveLights[i].z / 3;
            dist = sqrtf((d[0] * d[0]) + (d[1] * d[1]) + (d[2] * d[2]));
            if (dist == 0.0f) {
                dist = 0.1f;
            }
            n[0] = d[0] / dist;
            n[1] = d[1] / dist;
            n[2] = d[2] / dist;
            dot = (n[0] * gActiveLights[i].dirX) + (n[1] * gActiveLights[i].dirY) + (n[2] * gActiveLights[i].dirZ);
            if (dot < 0.0f) {
                dot = 0.0f;
            }
            if (gActiveLights[i].cosOuter <= dot) {
                if (gActiveLights[i].cosInner <= dot) {
                    dot = 1.0f;
                } else {
                    dot -= gActiveLights[i].cosOuter;
                    dot *= gActiveLights[i].coneScale;
                }
                if (dist > 300.0) {
                    if (dist > 1100.0) {
                        dot = 0.0f;
                    } else {
                        dot = dot * (1.0 - ((dist - 300.0) / 800.0));
                    }
                }
                r += gActiveLights[i].r * dot;
                g += gActiveLights[i].g * dot;
                b += gActiveLights[i].b * dot;
            }
            break;
        }
        case 0: {
            f32 dx;
            f32 dy;
            f32 dz;
            f32 edgeDist;
            f32 range;
            f32 fadeLength;
            dz = (gActiveLights[i].z / 3) - z;
            dx = (gActiveLights[i].x / 3) - x;
            dy = (gActiveLights[i].y / 3) - y;
            dist = sqrtf((dz * dz) + ((dx * dx) + (dy * dy)));
            edgeDist = dist - radius;
            if (dist <= radius) {
                edgeDist = 0.1f;
            }
            range = gActiveLights[i].fadeStart / 3.0f;
            if (edgeDist < range) {
                r += gActiveLights[i].r;
                g += gActiveLights[i].g;
                b += gActiveLights[i].b;
            } else {
                edgeDist -= range;
                fadeLength = (1.0f / gActiveLights[i].invFadeLength) / 3.0f;
                fadeLength -= range;
                if (edgeDist < fadeLength) {
                    factor = 1.0f - (edgeDist / fadeLength);
                    r += gActiveLights[i].r * factor;
                    g += gActiveLights[i].g * factor;
                    b += gActiveLights[i].b * factor;
                }
            }
            break;
        }
        }
    }
    if (r > 1.0f) {
        r = 1.0f;
    }
    if (g > 1.0f) {
        g = 1.0f;
    }
    if (b > 1.0f) {
        b = 1.0f;
    }
    *outR = (s32)(r * 255.0f);
    *outG = (s32)(g * 255.0f);
    *outB = (s32)(b * 255.0f);
}
