#include "common.h"
#include "actor.h"
#include "cutscene.h"
#include "map.h"
#include "collision.h"
#include "water.h"
#include "sched.h"
#define PROTO_SKIP_assetEnsureTableLoaded // PROTO: The number of arguments doesn't agree with the number in the
#include "proto/boot/30E0.h"
#include "proto/global/136820.h"
#include "proto/global/15050.h"
#include "proto/global/166A0.h"
#include "proto/global/2F550.h"
#include "proto/global/36880.h"
#include "proto/global/5E020.h"
#include "proto/global/63EC0.h"
#include "proto/global/6AD90.h"
#include "proto/global/70FD0.h"
#include "proto/global/7CA80.h"
#include "proto/global/CEAE0.h"
#include "proto/global/FE40.h"


typedef struct CollisionStaticTri {
    /* 0x00 */ s16 x[3];
    /* 0x06 */ s16 y[3];
    /* 0x0C */ s16 z[3];
    /* 0x12 */ s16 flags;
    /* 0x14 */ u8 slopeType;
    /* 0x15 */ u8 unk15;
    /* 0x16 */ u8 unk16;
    /* 0x17 */ s8 offsetSlot;
} CollisionStaticTri; // size = 0x18

// Streamed static-mesh cell: triangles [tris, trisEnd) loaded on demand from romAddr.
typedef struct CollisionBufferEntry {
    /* 0x00 */ CollisionStaticTri *tris;
    /* 0x04 */ CollisionStaticTri *trisEnd;
    /* 0x08 */ u32 lastUsedFrame;
    /* 0x0C */ u32 romAddr;
    /* 0x10 */ u32 size;
} CollisionBufferEntry; // size = 0x14

extern CollisionBufferEntry *D_807F9514;
extern s32 D_807F9518;
extern u8 D_807F951C;
extern s32 gCurrentMap;
extern u8 D_807F94B4;

void collisionBuildCellTable(MapFileHeader *header) {
    s32 off;
    void *compressed;
    u8 *dst;
    u8 *src;
    u8 *data;
    u8 *cursor;
    u8 *cellEnd;
    u8 *cellStart;
    s32 base;
    s32 i;
    void *window;

    D_807F9514 = heapAlloc(0x11A8);
    D_807F9518 = header->unk18 * header->unk1A;
    data = assetLoad(3, gCurrentMap, 1, 0);
    D_807F951C = 0;
    if (header->unk9 & 2) {
        compressed = data;
        data = heapAlloc(header->unk4);
        window = heapAlloc(0x2400);
        dst = data;
        src = compressed;
        gunzip(&src, &dst, window);
        heapFree(window);
        assetSetImmediateFree();
        assetFreeBuffer(compressed, 0x9D, 0x3A);
        D_807F951C = 1;
    }
    base = assetGetSize(3, gCurrentMap);
    cursor = data + 4;
    for (i = 0; i < D_807F9518; i++) {
        D_807F9514[i].lastUsedFrame = 0;
        cellStart = cursor + 4;
        off = cursor - data;
        D_807F9514[i].romAddr = base + off + 4;
        off = *(u32 *)cursor;
        cellEnd = data + off;
        cursor = cellEnd;
        if (D_807F951C) {
            D_807F9514[i].tris = (CollisionStaticTri *)cellStart;
            D_807F9514[i].trisEnd = (CollisionStaticTri *)cellEnd;
        } else {
            D_807F9514[i].tris = NULL;
            D_807F9514[i].trisEnd = NULL;
        }
        D_807F9514[i].size = cellEnd - cellStart;
    }
    if (!D_807F951C) {
        assetSetImmediateFree();
        assetFreeBuffer(data, 0xC3, 0x3A);
    }
    D_807F94B4 = 0;
}

extern u8 D_807F94B4;

void collisionSetQueryMode(u8 mode) {
    D_807F94B4 = mode;
}

extern u8 D_807F94B3;
extern u8 D_807F94BC;
extern f32 D_807F948C;


void collisionQueryActorFloor(Actor *actor, u8 *hasFloor, f32 *floorY, u8 *hasWater, f32 *waterY, u8 mode) {
    f32 posX;
    f32 posY;
    f32 posZ;

    D_807F94BC = 0;
    D_807F94B3 = 0;
    if (actor->floorNodeId && actor->attachMode == 0 && (actor->flags & 0x10)) {
        actorGetNodePos(actor, actor->floorNodeId, &posX, &posY, &posZ);
    } else {
        posX = actor->x;
        posY = actor->prevY;
        posZ = actor->z;
    }
    collisionFindFloorAtPoint(actor, posX, posY, posZ, hasFloor, floorY, hasWater, waterY, mode);
}

s32 collisionCheckActorFloor(Actor *actor, f32 x, f32 y, f32 z, f32 *outFloorY) {
    u8 slopeHit;
    u8 normalHit;
    f32 slopeY;
    f32 normalY;
    s32 found;

    if (actor->actorType == 0xBC) {
        D_807F94B3 = 1;
    } else {
        D_807F94B3 = 0;
    }
    D_807F94BC = 1;
    found = collisionFindFloorAtPoint(NULL, x, y, z, &slopeHit, &slopeY, &normalHit, &normalY, 0);
    *outFloorY = D_807F948C;
    return found;
}

extern u8 D_807F94AE;
extern u8 D_807F94AF;
extern u8 D_807F94B0;
extern u8 D_807F94B7;
extern u8 D_807F951D;

void collisionClearFlags(void) {
    D_807F94AE = 0;
    D_807F94AF = 0;
    D_807F94B0 = 0;
    D_807F94B7 = 0;
}

u8 collisionGetStateByte(void) {
    return D_807F951D;
}


extern f32 D_807F9460;
extern u8 D_807F9464;
extern f32 D_807F9468;
extern u8 D_807F946C;
extern u8 D_807F946D;
extern u8 D_807F946E;
extern Actor *D_807F9470;
extern f32 D_807F9474;
extern f32 D_807F9478;
extern f32 D_807F947C;
extern u32 D_807F9480;
extern u8 D_807F9484;
// Per-source floor tables indexed by source (0 mesh, 1 dynamic, 2 box); elements 1 and 2 also
// have their own symbols (D_807F9492/94, D_807F949A/9C, D_807F949F/94A0), which the reloc check requires.
extern s16 D_807F9490[];
extern s16 D_807F9492;
extern s16 D_807F9494;
extern s16 D_807F9498[];
extern s16 D_807F949A;
extern s16 D_807F949C;
extern u8 D_807F949E[];
extern u8 D_807F949F;
extern u8 D_807F94A0;
extern s16 D_807F94A2;
extern s16 D_807F94A4;
extern u8 D_807F94AA;
extern u8 D_807F94AB;
extern u8 D_807F94AC;
extern u8 D_807F94AD;
extern u8 D_807F94B2;
extern u8 D_807F94B6;
extern PlayerState *D_807F94B8;
extern u8 sCamFloorHitCount;

s32 collisionFindFloorAtPoint(Actor *actor, f32 x, f32 y, f32 z, u8 *outHasFloor, f32 *outFloorY, u8 *outHasWater, f32 *outWaterY, u8 mode) {
    u8 meshHit;
    u8 dynHit;
    f32 meshY;
    f32 dynY;
    f32 boxY;
    u8 pad;
    u8 boxHit;
    u8 source;
    u8 pad2;
    f32 threshold;

    D_807F946E = 0;
    if (D_807F94B4 == 1) {
        collisionClearFlags();
        *outHasFloor = 0;
        *outHasWater = 0;
        D_807F94B4 = 0;
        return 0;
    }
    if (actor != NULL) {
        actor->attachMode = 0;
        actor->contactFlags &= 0xFBF1;
        actor->cutsceneId = -1;
        D_807F94B6 = 0;
        D_807F9464 = 0;
        D_807F946C = 0;
        D_807F946D = mode;
        actor->renderFlags &= ~0x40;
        if (actor->collisionFlags & 1) {
            D_807F94B8 = actor->customState;
            D_807F94B8->stateFlags &= ~0x6000;
        }
    }
    D_807F951D = 0;
    D_807F94AB = 0;
    D_807F94AC = 0;
    D_807F94AD = 0;
    collisionClearFlags();
    D_807F94B2 = 0;
    D_807F9484 = 0;
    sCamFloorHitCount = 0;
    meshY = y;
    meshHit = collisionTestSubmeshBoundary(x, z, &meshY, actor);
    if ((meshHit != 0) && (actor != NULL)) {
        actor->unkA8 = meshY;
        actor->floorSurfaceType = D_807F949E[0];
    }
    if (D_807F94B4 != 2) {
        dynY = 99999.0f;
        dynHit = func_8062BCC8(actor, x, z, y, &dynY);
        boxY = 99999.0f;
        boxHit = collisionTestActorBoxFloor(actor, x, z, y, &boxY);
    } else {
        dynHit = 0;
        boxHit = 0;
    }
    threshold = (f32)((f64)y + 4.0);
    dynHit *= 2;
    boxHit *= 4;
    switch ((u8)(meshHit + dynHit + boxHit)) {
    case 0:
        source = 0;
        break;
    case 1:
        source = 1;
        break;
    case 2:
        source = 2;
        break;
    case 3:
        if (mathCheckCloserFloatThreshold(dynY, meshY, threshold, 0) != 0) {
            source = 1;
        } else {
            source = 2;
        }
        break;
    case 4:
        source = 3;
        break;
    case 5:
        if (mathCheckCloserFloatThreshold(boxY, meshY, threshold, 0) != 0) {
            source = 1;
        } else {
            source = 3;
        }
        break;
    case 6:
        if (mathCheckCloserFloatThreshold(boxY, dynY, threshold, 0) != 0) {
            source = 2;
        } else {
            source = 3;
        }
        break;
    case 7:
        if (mathCheckCloserFloatThreshold(dynY, meshY, threshold, 0) != 0) {
            if (mathCheckCloserFloatThreshold(boxY, meshY, threshold, 0) != 0) {
                source = 1;
            } else {
                source = 3;
            }
        } else if (mathCheckCloserFloatThreshold(dynY, boxY, threshold, 0) != 0) {
            source = 3;
        } else {
            source = 2;
        }
    }
    switch (source) {
    default:
        D_807F94AA = 0;
        break;
    case 1:
        if (actor != NULL) {
            actor->floorSlopeType = D_807F949E[0];
            actor->floorTiltPitch = D_807F9498[0];
            actor->floorTiltYaw = D_807F9490[0];
            actor->floorY = meshY;
            if ((D_807F94B6 != 0) && (actor->prevContactFlags & 1)) {
                actor->contactFlags |= 0x400;
            }
        }
        D_807F94A4 = D_807F9498[0];
        D_807F94A2 = D_807F9490[0];
        D_807F948C = meshY;
        D_807F94AA = D_807F94AB;
        D_807F951D = 1;
        break;
    case 2:
        if (actor != NULL) {
            actor->floorSlopeType = D_807F949F;
            actor->floorTiltPitch = D_807F949A;
            actor->floorTiltYaw = D_807F9492;
            actor->floorY = dynY;
            if (actor->prevContactFlags & 1) {
                actor->attachMode = 1;
            }
        }
        D_807F94A4 = D_807F949A;
        D_807F94A2 = D_807F9492;
        D_807F948C = dynY;
        D_807F94AA = D_807F94AC;
        D_807F951D = 2;
        break;
    case 3:
        if (actor != NULL) {
            actor->floorSlopeType = D_807F94A0;
            actor->floorTiltPitch = D_807F949C;
            actor->floorTiltYaw = D_807F9494;
            actor->floorY = boxY;
            if (actor->prevContactFlags & 1) {
                actorAppendCallback10(actor, D_807F9470, D_807F9474, D_807F9478, D_807F947C, D_807F9480, D_807F94B2);
                actor->contactFlags |= 8;
            }
        }
        D_807F94A4 = D_807F949C;
        D_807F94A2 = D_807F9494;
        D_807F948C = boxY;
        D_807F94AA = D_807F94AD;
        D_807F951D = 3;
        break;
    }
    *outHasFloor = D_807F9464;
    *outFloorY = D_807F9460;
    *outHasWater = D_807F946C;
    *outWaterY = D_807F9468;
    D_807F94B4 = 0;
    return (u8)(meshHit | dynHit | boxHit);
}

extern u8 D_807F946E;
extern u8 D_807F94B1;
extern u8 D_807F94AA;
extern s16 D_807F94A2;
extern s16 D_807F94A4;

u8 collisionGetHitStatus(void) {
    return D_807F946E;
}

u8 collisionIsGroundImpact(void) {
    return D_807F94AE;
}

u8 collisionIsHeavyGroundImpact(void) {
    return D_807F94AF;
}

u8 collisionGetFloorType(void) {
    return D_807F94B0;
}

u8 collisionGetMaterialType(void) {
    return D_807F94B7;
}

void collisionGetCoords(s16 *outX, s16 *outZ) {
    *outX = D_807F94A2;
    *outZ = D_807F94A4;
}

u8 collisionGetSurfaceFlags(void) {
    return D_807F94B1;
}

u8 collisionGetHitFlags(void) {
    return D_807F94AA;
}

extern s16 D_807F94A6;
extern s16 D_807F94A8;

void collisionStoreSurfaceNormalAngles(Actor *actor, f32 normalX, f32 normalY, f32 normalZ, u8 slopeType, u8 record, u8 source) {
    f32 horiz;
    f32 absX;
    f32 absY;
    f32 absZ;
    f64 nx;
    s16 yaw;
    s16 pitch;
    u8 type;

    type = slopeType;
    if (slopeType == 0xFF) {
        slopeType = 0;
        type = 0;
    }
    if (type == 0xFE) {
        slopeType = 0;
    }
    D_807F949E[source] = slopeType;
    if (normalZ > 0.0f) {
        absZ = normalZ;
    } else {
        absZ = -normalZ;
    }
    if ((f64) absZ < 0.01) {
        yaw = 0x400;
    } else {
        if (normalX > 0.0f) {
            absX = normalX;
        } else {
            absX = -normalX;
        }
        yaw = (s16)((mathAtan2(absX, absZ) / 3.1415927f) * 2048.0f);
    }
    nx = (f64) normalX;
    if ((nx >= 0.0) && ((f64) normalZ >= 0.0)) {
        yaw -= 0x800;
    } else if ((nx >= 0.0) && ((f64) normalZ < 0.0)) {
        yaw = -yaw;
    } else if ((nx < 0.0) && ((f64) normalZ >= 0.0)) {
        yaw = 0x800 - yaw;
    }
    if (record) {
        D_807F9490[source] = yaw & 0xFFF;
    }
    D_807F94A6 = yaw & 0xFFF;
    horiz = sqrtf((normalX * normalX) + (normalZ * normalZ));
    if ((f64) horiz < 0.01) {
        pitch = 0x400;
    } else {
        if (normalY > 0.0f) {
            absY = normalY;
        } else {
            absY = -normalY;
        }
        pitch = (s16)((mathAtan2(absY, horiz) / 3.1415927f) * 2048.0f);
    }
    if (record) {
        D_807F9498[source] = pitch;
    }
    D_807F94A8 = pitch;
}

extern PlayerStruct *gPlayerSlots;
extern u8 gCurrentPlayerIndex;
extern s16 gCurrentCharacterIndex;
extern f32 D_80752F7C[];
extern f32 D_80752F98[];
extern f32 D_80752FB4[];
extern f32 D_80752FD0[];
extern f32 D_80752FEC[];
extern f32 D_80753008[];
extern f32 D_807F9460;

void collisionCheckSlopeAngle(f32 refY, f32 floorY, u8 scaled, Actor *actor, u8 halveMin) {
    f32 *maxTable;
    f32 *minTable;
    f32 maxStep;
    f32 minStep;
    f32 minHeight;
    f32 maxHeight;
    f32 diff;
    u8 kong;

    if (refY < floorY) {
        if ((actor != NULL) && (actor->collisionFlags & 1)) {
            kong = gPlayerSlots[gCurrentPlayerIndex].unk2C0;
            if (kong != 0) {
                if (kong != 2) {
                    minTable = D_80752F98; maxTable = D_80752F7C; // LAYOUT: same-line join steers as1 scheduling (addiu order)
                } else {
                    minTable = D_80753008;
                    maxTable = D_80752FEC;
                }
            } else {
                minTable = D_80752FD0;
                maxTable = D_80752FB4;
            }
            minHeight = minTable[gCurrentCharacterIndex];
            maxHeight = maxTable[gCurrentCharacterIndex];
        } else {
            minHeight = 10.0f;
            maxHeight = 20.0f;
        }
        if (halveMin != 0) {
            minHeight /= 2;
        }
        if (scaled == 1) {
            minStep = minHeight * 6.0f;
        } else {
            minStep = minHeight;
        }
        diff = floorY - refY;
        if (minStep < diff) {
            if (scaled == 1) {
                maxStep = maxHeight * 6.0f;
            } else {
                maxStep = maxHeight;
            }
            if (diff < maxStep) {
                D_807F9464 = 1;
                D_807F9460 = floorY - maxStep;
                if (scaled) {
                    D_807F9460 /= 6.0f;
                }
            }
        }
    }
}

extern f32 D_807F9468;
extern u8 D_807F946C;

s32 collisionGetFloorTriangleNormal(f32 refY, f32 floorY, u8 scaled, u8 slopeType) {
    f32 limit;
    s32 hit;

    hit = 0;
    if (slopeType == 0xFF && refY < floorY) {
        limit = (scaled == 1) ? 150.0 : 25.0;
        if ((floorY - refY) < limit) {
            D_807F946C = 1;
            hit = 1;
            D_807F9468 = floorY - limit;
            if (scaled) {
                D_807F9468 /= 6.0f;
            }
            D_807F9468 = (f64)D_807F9468 + 6.0;
        }
    }
    return hit;
}

s32 mathCheckCloserFloatThreshold(f32 firstY, f32 secondY, f32 threshold, u8 wide) {
    f32 limit;
    f32 diff0;
    f32 diff1;
    s32 cond0;
    s32 cond1;

    limit = (wide == 1) ? 60.0 : 10.0;

    if (firstY <= threshold) {
        cond0 = 1;
    } else if ((firstY - threshold) < limit) {
        cond0 = 1;
    } else {
        cond0 = 0;
    }

    if (secondY <= threshold) {
        cond1 = 1;
    } else if ((secondY - threshold) < limit) {
        cond1 = 1;
    } else {
        cond1 = 0;
    }

    if (!cond0 && !cond1) {
        return 0;
    }
    if (!cond1) {
        return 0;
    }
    if (!cond0) {
        return 1;
    }

    if (threshold < firstY) {
        diff0 = firstY - threshold;
    } else {
        diff0 = threshold - firstY;
    }

    if (threshold < secondY) {
        diff1 = secondY - threshold;
    } else {
        diff1 = threshold - secondY;
    }

    if (diff0 < diff1) {
        return 0;
    }
    return 1;
}

extern u8 D_807F9484;
extern f32 D_807F9488;
extern u8 D_807F94B5;
extern u8 sCamFloorHitCount;

u8 collisionCheckGroundAtPoint(f32 x, f32 z, f32 *yInOut) {
    u8 ret;

    D_807F9484 = 0;
    sCamFloorHitCount = 0;
    ret = collisionTestSubmeshBoundary(x, z, yInOut, NULL);
    D_807F94A4 = D_807F9498[0];
    D_807F94A2 = D_807F9490[0];
    return ret;
}

u8 collisionGetFloorHeight(f32 *outY) {
    *outY = D_807F9488;
    return D_807F9484;
}

u8 collisionGetSurfaceType(void) {
    return D_807F94B5;
}

extern u8 D_807F94B6;

u8 collisionTestSubmeshBoundary(f32 x, f32 z, f32 *yInOut, Actor *actor) {
    u8 staticHit;
    f32 staticY;
    f32 gridY;
    f32 temp;
    u8 pad;
    u8 val;
    s32 hit;

    staticY = *yInOut;
    staticHit = collisionTestStaticMeshFloor(x, z, &staticY, actor);
    gridY = *yInOut;
    val = collisionTestGridMeshHeight(x, z, &gridY, actor) * 2;
    val += staticHit;
    switch (val) {
    case 0:
        break;
    case 1:
        *yInOut = staticY;
        break;
    case 2:
        *yInOut = gridY;
        D_807F94B6 = 1;
        break;
    case 3:
        temp = (f64)*yInOut + 4.0;
        if (mathCheckCloserFloatThreshold(staticY, gridY, temp, 0) != 0) {
            *yInOut = gridY;
            D_807F94B6 = 1;
        } else {
            *yInOut = staticY;
        }
        break;
    }
    if (val != 0) {
        hit = 1;
    } else {
        hit = 0;
    }
    return hit;
}

extern WaterSurface *gEffectNodeList;

s32 collisionTestGridMeshHeight(f32 posX, f32 posZ, f32 *height, Actor *actor) {
    f32 pz;
    u8 tableFlag;
    f32 pad[2]; // pad: reproduces frame 0xF8 (unused)
    f32 x[4];
    f32 y[4];
    f32 z[4];
    CollisionStaticTri tri; // 0x18 slot puts x/y/z at 0xB8
    u8 hit;
    f32 bestY;
    WaterSurface *node;
    f32 floorY;
    f32 threshold;
    s32 cell_x;
    s32 cell_z;

    hit = 0;
    bestY = 999999.0f;
    node = gEffectNodeList;
    threshold = *height + 4.0;
    if (node != NULL) {
        do {
            if (node->sub->minX <= posX && node->sub->minZ <= posZ && posX <= node->sub->maxX && posZ <= node->sub->maxZ) {
                floorY = posX * 6.0f;
                pz = posZ * 6.0f;
                tableFlag = effectGetTableFlag(node);
                cell_x = (posX - node->sub->minX) / (f32)node->gridStep;
                cell_z = (posZ - node->sub->minZ) / (f32)node->gridStep;

                x[0] = node->gridStep * cell_x + node->sub->minX;
                z[0] = node->gridStep * cell_z + node->sub->minZ;
                y[0] = effectWaterGetHeightAt(node, x[0], z[0], tableFlag);

                x[1] = (cell_x + 1) * node->gridStep + node->sub->minX;
                z[1] = z[0];
                y[1] = effectWaterGetHeightAt(node, x[1], z[1], tableFlag);
                x[2] = x[0];
                z[2] = (cell_z + 1) * node->gridStep + node->sub->minZ;
                y[2] = effectWaterGetHeightAt(node, x[2], z[2], tableFlag);

                x[3] = x[1];
                z[3] = z[2];
                y[3] = effectWaterGetHeightAt(node, x[3], z[3], tableFlag);

                tri.x[0] = x[0] * 6.0f;
                tri.y[0] = y[0] * 6.0f;
                tri.z[0] = z[0] * 6.0f;

                tri.x[1] = x[1] * 6.0f;
                tri.y[1] = y[1] * 6.0f;
                tri.z[1] = z[1] * 6.0f;

                tri.x[2] = x[3] * 6.0f;
                tri.y[2] = y[3] * 6.0f;
                tri.z[2] = z[3] * 6.0f;

                if (collisionPointInTriangleXZS16(&tri, floorY, pz) != 0) {
                    floorY = collisionTriangleHeightAtXZ(&tri, floorY, pz) / 6.0f;
                } else {
                    tri.x[1] = x[2] * 6.0f;
                    tri.y[1] = y[2] * 6.0f;
                    tri.z[1] = z[2] * 6.0f;
                    floorY = collisionTriangleHeightAtXZ(&tri, floorY, pz) / 6.0f;
                }

                switch (node->sub->unk60) {
                case 0:
                case 2:
                case 3:
                    if (node->sub->unk60 == 2 || node->sub->unk60 == 3) {
                        if ((floorY < *height ? *height - floorY : -(*height - floorY)) < 6.0f) {
                            switch (node->sub->unk60) {
                            case 2:
                                D_807F94AF = 2;
                                break;
                            case 3:
                                D_807F94AF = 1;
                                break;
                            }
                        }
                    }
                    hit = 1;
                    if (mathCheckCloserFloatThreshold(bestY, floorY, threshold, 0) != 0) {
                        bestY = floorY;
                    }
                    break;
                case 1:
                    if (actor != NULL) {
                        if (actor->y < floorY) {
                            actor->contactFlags |= 4;
                            actor->unkB0[0] = -1;
                            if (node->unk4A & 1) {
                                D_807F94B0 = 1;
                            }
                        }
                        actor->waterY = floorY;
                        actor->contactFlags |= 2;
                    }
                    D_807F9484 = 1;
                    D_807F9488 = floorY;
                    break;
                }
            }
            node = node->next;
        } while (node != NULL);
    }
    if (hit) {
        *height = bestY;
    }
    return hit;
}

f32 collisionTriangleHeightAtXZ(CollisionStaticTri *tri, f32 x, f32 z) {
    f64 dx01 = tri->x[0] - tri->x[1];
    f64 dy01 = tri->y[0] - tri->y[1];
    f64 dz01 = tri->z[0] - tri->z[1];
    f64 dx02 = tri->x[0] - tri->x[2];
    f64 dy02 = tri->y[0] - tri->y[2];
    f64 dz02 = tri->z[0] - tri->z[2];
    f64 nx = (dy01 * dz02) - (dz01 * dy02);
    f64 ny = (dz01 * dx02) - (dx01 * dz02);
    f64 nz = (dx01 * dy02) - (dy01 * dx02);
    f64 d = -((nx * tri->x[1]) + (ny * tri->y[1]) + (nz * tri->z[1]));
    f64 val = ((nx * x) + (ny * -1000.0) + (nz * z) + d) / (ny * 2000.0);
    val = 0.0 - val;
    return (2000.0 * val) - 1000.0;
}

extern s32 D_807F9518;
extern s32 gCurrentMap;
extern u16 D_807F9450;
extern u16 D_807F9452;
extern u16 D_807F9454;
extern u16 D_807F9456;
extern u8 D_807F5FC0;
extern u8 D_807F94AB;

u8 collisionTestStaticMeshFloor(f32 x, f32 z, f32 *yInOut, Actor *actor) {
    f32 offset;
    CollisionStaticTri *triEnd;
    CollisionStaticTri *hitTri;
    s32 cell;
    CollisionStaticTri *tri;
    s32 padH[2];
    f64 h2;
    f64 nx;
    f64 ny;
    f64 nz;
    f64 d;
    f64 dx01, dy01, dz01, dx02, dy02, dz02;
    f64 val;
    f32 diff;
    f32 t;
    struct { u8 pad[3]; u8 cb; f32 cc; } spS; // FAKE: address-taken aggregate makes the final read of cb reload after the call (lbu t5)
    f32 threshold;
    s32 padB[1];
    u8 closer;
    s32 padC[3];
    f32 cur;
    s32 iz;
    s32 ix;

    spS.cb = 0;
    spS.cc = 999999.0f;
    cell = ((s32)z / D_807F9452) * D_807F9454 + (s32)x / D_807F9450;
    cur = *yInOut;
    threshold = (f32)((f64)*yInOut + 4.0);
    threshold = threshold * 6.0f;
    if (cell >= D_807F9518) {
        return 0;
    }
    if (D_807F9454 <= x / D_807F9450 || x < 0.0) {
        if (gCurrentMap == 0x57 && actor != NULL) {
            return collisionTestHardcodedFloorPlane(&spS.cc, threshold, cur, yInOut);
        }
        return 0;
    }
    if (D_807F9456 <= z / D_807F9452 || z < 0.0) {
        if (gCurrentMap == 0x57 && actor != NULL) {
            return collisionTestHardcodedFloorPlane(&spS.cc, threshold, cur, yInOut);
        }
        return 0;
    }
    dynamicBufferAllocateEntry(cell);
    x = x * 6.0f;
    z = z * 6.0f;
    if (actor != NULL && actor->floorTriangle != NULL && collisionCheckTriangleXZBoundsS16(actor->floorTriangle, (s32)x, (s32)z) != 0 &&
        collisionPointInTriangleXZS16(actor->floorTriangle, x, z) != 0 && D_807F5FC0 == 0) {
        tri = actor->floorTriangle;
        triEnd = tri + 1;
    } else {
        tri = D_807F9514[cell].tris;
        triEnd = D_807F9514[cell].trisEnd;
    }
    if (tri != triEnd) {
        iz = (s32)z;
        ix = (s32)x;
        do {
            if (collisionCheckTriangleXZBoundsS16(tri, ix, iz) != 0 && collisionPointInTriangleXZS16(tri, x, z) != 0) {
                dx01 = (f64)(tri->x[0] - tri->x[1]);
                dy01 = (f64)(tri->y[0] - tri->y[1]);
                dz01 = (f64)(tri->z[0] - tri->z[1]);
                dx02 = (f64)(tri->x[0] - tri->x[2]);
                dy02 = (f64)(tri->y[0] - tri->y[2]);
                dz02 = (f64)(tri->z[0] - tri->z[2]);
                nx = (dy01 * dz02) - (dz01 * dy02);
                ny = (dz01 * dx02) - (dx01 * dz02);
                d = -((nx * tri->x[1]) + (ny * tri->y[1]) + (((dx01 * dy02) - (dy01 * dx02)) * tri->z[1]));
                if (ny * 2000.0 > 0.01 || ny * 2000.0 < -0.01) {
                    val = 0.0 - ((((x * nx) + (ny * -1000.0)) + (((dx01 * dy02) - (dy01 * dx02)) * z) + d) / (ny * 2000.0));
                    h2 = (2000.0 * val) - 1000.0;
                    if (tri->flags & 4) {
                        offset = mapOffsetSlotGetValue(tri->offsetSlot) * 6.0f;
                        h2 = ((2000.0 * (0.0 - ((((x * nx) + (ny * -1000.0)) + (((dx01 * dy02) - (dy01 * dx02)) * z) + d) / (ny * 2000.0)))) - 1000.0) + offset; // FAKE: recomputes the height formula instead of reusing val, keeping it a separate f64 web (f20) for add.d f24,f20,f6
                    }
                    if ((tri->flags & 0x4000) && actor != NULL && (actor->collisionFlags & 1)) {
                        D_807F94B7 = 1;
                    }
                    if ((tri->flags & 0x80) && (f64)(*yInOut * 6.0f) < h2) {
                        D_807F94B0 = 1;
                    }
                    if ((tri->flags & 0x100) && actor != NULL && (actor->collisionFlags & 1)) {
                        if ((f64)(*yInOut * 6.0f) < h2 && ((diff = h2 - (f64)(*yInOut * 6.0f)) < 600.0f)) {
                            D_807F94B8->stateFlags |= 0x2000;
                        }
                    }
                    if ((tri->flags & 0xA00) && actor != NULL && (actor->collisionFlags & 1)) {
                        if ((f64)(*yInOut * 6.0f) < h2 && ((diff = h2 - (f64)(*yInOut * 6.0f)) < 800.0f)) {
                            D_807F94B8->stateFlags |= 0x4000;
                        }
                    }
                    if (tri->flags & 0x4850) {
                        if (actor != NULL) {
                            if (h2 < (f64)(*yInOut * 6.0f)) {
                                diff = (f64)(*yInOut * 6.0f) - h2;
                            } else {
                                diff = -((f64)(*yInOut * 6.0f) - h2);
                            }
                            if ((tri->flags & 0x10) && diff < 40.0f) {
                                D_807F94AE = 1;
                            }
                            if ((tri->flags & 0x40) && diff < 40.0f) {
                                D_807F94AF = 1;
                            }
                        }
                    } else {
                        if (D_807F94BC != 0) {
                            collisionRecordTriangleS(tri, (f32)h2);
                        }
                        if (!(tri->flags & 1)) {
                            collisionCheckSlopeAngle(*yInOut * 6.0f, (f32)h2, 1, actor, 0);
                            collisionGetFloorTriangleNormal(*yInOut * 6.0f, (f32)h2, 1, tri->slopeType);
                            closer = mathCheckCloserFloatThreshold(spS.cc, (f32)h2, threshold, 1);
                            if (collisionCheckTriangleWindingS16(tri) != 0 && closer != 0) {
                                spS.cb = 1;
                                spS.cc = (f32)h2;
                                hitTri = tri;
                                D_807F94B5 = tri->unk16 & 0xF;
                                if (h2 < (f64)(*yInOut * 6.0f)) {
                                    diff = (f64)(*yInOut * 6.0f) - h2;
                                } else {
                                    diff = -((f64)(*yInOut * 6.0f) - h2);
                                }
                                if (diff > 30.0f) {
                                    t = (diff - 30.0f) / 120.0f;
                                    if ((f64)t > 1.0) {
                                        D_807F94B5 = 0xF;
                                    } else {
                                        D_807F94B5 = (u32)((f32)D_807F94B5 + (f32)(0xF - D_807F94B5) * t);
                                    }
                                }
                                collisionStoreTriangleNormalAnglesS16(actor, tri, 1);
                                if (actor != NULL) {
                                    actor->unk78[0] = tri->unk15;
                                    actor->tintA = D_807F94B5;
                                }
                                D_807F94B1 = tri->unk15;
                                if (tri->flags & 2) {
                                    *yInOut = spS.cc / 6.0f;
                                    if (!(tri->flags & 8)) {
                                        D_807F94AB = 1;
                                    }
                                    if (tri->flags & 0x2000) {
                                        D_807F946E = 1;
                                    }
                                    if (actor != NULL && (tri->flags & 0x1000)) {
                                        actor->renderFlags |= 0x40;
                                    }
                                    if (actor != NULL) {
                                        actor->floorTriangle = tri;
                                    }
                                    return 1;
                                }
                            }
                        } else {
                            if (actor != NULL) {
                                if ((f64)(actor->y * 6.0f) < h2) {
                                    actor->contactFlags |= 4;
                                    actor->unkB0[0] = tri->unk16 >> 4;
                                    if (actor->unkB0[0] == 0xF) {
                                        actor->unkB0[0] = -1;
                                    }
                                }
                                actor->contactFlags |= 2;
                                actor->waterY = h2 / 6.0;
                            }
                            if (tri->flags & 0x20) {
                                collisionCheckSlopeAngle(*yInOut * 6.0f, (f32)h2, 1, actor, 1);
                            }
                            D_807F9484 = 1;
                            D_807F9488 = (f32)(h2 / 6.0);
                        }
                    }
                }
            }
            tri++;
        } while (tri != triEnd);
    }
    if (spS.cb != 0) {
        *yInOut = spS.cc / 6.0f;
        if (!(hitTri->flags & 8)) {
            D_807F94AB = 1;
        }
        if (hitTri->flags & 0x2000) {
            D_807F946E = 1;
        }
        if (actor != NULL && (hitTri->flags & 0x1000)) {
            actor->renderFlags |= 0x40;
        }
    }
    if (gCurrentMap == 0x57 && actor != NULL) {
        spS.cb |= collisionTestHardcodedFloorPlane(&spS.cc, threshold, cur, yInOut);
    }
    if (actor != NULL) {
        actor->floorTriangle = NULL;
    }
    return spS.cb;
}


u8 collisionTestHardcodedFloorPlane(f32 *bestY, f32 threshold, f32 refY, f32 *yInOut) {
    f32 diff;
    f64 val;

    val = (f64)(refY * 6.0f);
    if (val > 1614.0) {
        diff = val - 1614.0;
    } else {
        diff = -(val - 1614.0);
    }
    if (diff < 40.0f) {
        D_807F94AE = 1;
    }
    if (mathCheckCloserFloatThreshold(*bestY, 684.0f, threshold, 1)) {
        *yInOut = 114.0f;
        return 1;
    }
    return 0;
}

typedef struct CamFloorHit {
    /* 0x0 */ f32 height;
    /* 0x4 */ s16 angle;
    /* 0x6 */ u8 flags;
    /* 0x7 */ u8 unk7;
} CamFloorHit; // size = 0x8

extern CamFloorHit sCamFloorHits[];

void collisionRecordTriangleS(CollisionStaticTri *tri, f32 height) {
    if (sCamFloorHitCount != 10) {
        sCamFloorHits[sCamFloorHitCount].height = height / 6.0f;
        if (collisionCheckTriangleWindingS16(tri)) {
            sCamFloorHits[sCamFloorHitCount].flags = 1;
        } else {
            sCamFloorHits[sCamFloorHitCount].flags = 2;
        }
        if (tri->flags & 1) {
            sCamFloorHits[sCamFloorHitCount].flags |= 4;
        }
        if (tri->flags & 0x400) {
            sCamFloorHits[sCamFloorHitCount].flags |= 8;
        }
        collisionStoreTriangleNormalAnglesS16(NULL, tri, 0);
        sCamFloorHits[sCamFloorHitCount].angle = D_807F94A8;
        sCamFloorHitCount++;
    }
}
extern u8 D_807F951C;

void dynamicBufferAllocateEntry(s32 index) {
    s32 size;

    if (D_807F9514[index].tris == NULL) {
        size = D_807F9514[index].size;
        if (size != 0) {
            D_807F9514[index].tris = heapAlloc(size);
            D_807F9514[index].trisEnd = D_807F9514[index].tris + size / sizeof(CollisionStaticTri);
            dmaReadAssetDecompress(D_807F9514[index].romAddr, D_807F9514[index].tris, &size, 0, 0, 0, 0);
        }
    }
    D_807F9514[index].lastUsedFrame = gFrameCounter;
}

void dynamicBufferPurgeExpired(void) {
    s32 i;

    if (!D_807F951C) {
        for (i = 0; i < D_807F9518; i++) {
            if (D_807F9514[i].tris != NULL && (gFrameCounter - D_807F9514[i].lastUsedFrame) >= 21) {
                actorClearBufferReferences(i);
                heapFree(D_807F9514[i].tris);
                D_807F9514[i].tris = NULL;
                D_807F9514[i].trisEnd = NULL;
            }
        }
    }
}

void actorClearBufferReferences(s32 cell) {
    s32 i;
    CollisionStaticTri *min = D_807F9514[cell].tris;
    CollisionStaticTri *max = D_807F9514[cell].trisEnd;

    for (i = 0; i < gActiveActorCount; i++) {
        Actor *actor = gActiveActors[i].actor;
        CollisionStaticTri *tri = actor->floorTriangle;

        if (!(actor->flags & 0x2000) && tri >= min && max >= tri) {
            actor->floorTriangle = NULL;
        }
    }
}

typedef struct CrossProductStack {
    f32 cross;
    f32 v0[3];
    f32 v1[3];
} CrossProductStack;

s32 collisionCheckTriangleWindingS16(CollisionStaticTri *tri) {
    CrossProductStack sp;

    sp.v1[0] = tri->x[2] - tri->x[0];
    sp.v1[2] = tri->z[2] - tri->z[0];
    sp.v0[0] = tri->x[1] - tri->x[0];
    sp.v0[2] = tri->z[1] - tri->z[0];
    sp.cross = (sp.v1[2] * sp.v0[0]) - (sp.v1[0] * sp.v0[2]);
    if (sp.cross <= 0.0) {
        return 1;
    }
    return 0;
}

typedef struct CrossProductStack3D {
    f32 cross[3];
    f32 v0[3];
    f32 v1[3];
} CrossProductStack3D;

void collisionStoreTriangleNormalAnglesS16(Actor *actor, CollisionStaticTri *tri, u8 record) {
    CrossProductStack3D sp;

    sp.v1[0] = tri->x[2] - tri->x[0];
    sp.v1[1] = tri->y[2] - tri->y[0];
    sp.v1[2] = tri->z[2] - tri->z[0];
    sp.v0[0] = tri->x[1] - tri->x[0];
    sp.v0[1] = tri->y[1] - tri->y[0];
    sp.v0[2] = tri->z[1] - tri->z[0];
    sp.cross[0] = (sp.v1[1] * sp.v0[2]) - (sp.v1[2] * sp.v0[1]);
    sp.cross[1] = (sp.v1[2] * sp.v0[0]) - (sp.v1[0] * sp.v0[2]);
    sp.cross[2] = (sp.v1[0] * sp.v0[1]) - (sp.v1[1] * sp.v0[0]);
    collisionStoreSurfaceNormalAngles(actor, sp.cross[0], sp.cross[1], sp.cross[2], tri->slopeType, record, 0);
}

s32 collisionCheckTriangleXZBoundsS16(CollisionStaticTri *tri, s32 x, s32 z) {
    s32 p0, p1, p2;
    s32 val;

    p0 = tri->x[0];
    p1 = tri->x[1];
    p2 = tri->x[2];

    val = (p0 < p1) ? p0 : p1;
    if (val >= p2) {
        val = p2;
    }
    if (x < val) {
        return 0;
    }

    val = (p1 < p0) ? p0 : p1;
    if (val <= p2) {
        val = p2;
    }
    if (val < x) {
        return 0;
    }

    p0 = tri->z[0];
    p1 = tri->z[1];
    p2 = tri->z[2];

    val = (p0 < p1) ? p0 : p1;
    if (val >= p2) {
        val = p2;
    }
    if (z < val) {
        return 0;
    }

    val = (p1 < p0) ? p0 : p1;
    if (val <= p2) {
        val = p2;
    }
    if (val < z) {
        return 0;
    }

    return 1;
}

s32 collisionPointInTriangleXZS16(CollisionStaticTri *tri, f32 x, f32 z) {
    f64 pad; // pad: reproduces slot layout (unused)
    f64 hx;
    f64 pad0[1]; // pad: reproduces slot layout (unused)
    f64 sidePt;
    f64 ex, ez, ox, oz;
    f64 mid_x;
    f64 pad1[1]; // pad: reproduces slot layout (unused)
    f64 hz;
    f64 mid_z;
    f64 pad3; // pad: reproduces slot layout (unused)
    f64 pad4; // pad: reproduces slot layout (unused)
    f64 sideRef;
    f64 pad2[1]; // pad: reproduces slot layout (unused)
    f64 sideMid;
    f64 z0;
    s32 i;
    u32 mismatch = 0;

    hx = (f64)(tri->x[1] + tri->x[2]) * 0.5;
    hz = (f64)(tri->z[1] + tri->z[2]) * 0.5;
    mid_x = ((f64)tri->x[0] + hx) * 0.5;
    z0 = tri->z[0];
    mid_z = (z0 + hz) * 0.5;

    for (i = 0; i < 3; i++) {
        switch (i) {
        case 0:
            ex = (f64)(tri->x[1] - tri->x[0]);
            ez = (f64)(tri->z[1] - tri->z[0]);
            ox = (f64)tri->x[0];
            oz = z0;
            break;
        case 1:
            ex = (f64)(tri->x[2] - tri->x[0]);
            ez = (f64)(tri->z[2] - tri->z[0]);
            ox = (f64)tri->x[0];
            oz = z0;
            break;
        case 2:
            ex = (f64)(tri->x[2] - tri->x[1]);
            ez = (f64)(tri->z[2] - tri->z[1]);
            ox = (f64)tri->x[1];
            oz = (f64)tri->z[1];
            break;
        }

        sidePt = ((f64)x - ox) * ez;
        sideRef = ((f64)z - oz) * ex;
        sideMid = ((mid_x - ox) * ez) - ((mid_z - oz) * ex);

        if ((sideRef <= sidePt ? 1 : -1) != (sideMid >= 0.0 ? 1 : -1)) {
            mismatch = 1;
        }
    }

    return (mismatch == 0) & 0xFF;
}


extern ModelSlot *gModelSlots;
extern u8 D_807F946D;
extern u8 D_807F94AC;

u8 collisionTestDynamicActorFloor(Actor *actor, s32 slotId, f32 x, f32 z, f32 refY, f32 *floorYOut) {
    s32 pad;
    CollisionTriF *triEnd;
    CollisionTriF *hitTri;
    CollisionTriF *tri;
    f64 nx, ny, nzPart;
    f64 d;
    f64 val;
    f64 dx01, dy01, dz01, dx02, dy02, dz02;
    f32 y;
    CsStateFull *sub7C;
    f32 padB[6];
    f32 hitY;
    u8 hit;
    s32 pad9C;
    s16 slotIdx;
    s32 pad94;
    ModelTriBuffer *buf;

    hit = 0;
    hitY = 999999.0f;

    slotIdx = hashTableLookup(slotId);
    if (slotIdx == -1) {
        return 0;
    }

    buf = &gModelSlots[slotIdx].unk48;
    if (actor != NULL && gModelSlots[slotIdx].unk70 != NULL && D_807F946D != 0) {
        actorCheckNearbyNodeInteractions(actor, slotIdx, gModelSlots[slotIdx].unk70);
    }

    if (!(buf->flags & 4)) {
        return 0;
    }

    if (collisionCheckBoundingBoxXZ(&buf->bbox, x, z) == 0) {
        return 0;
    }

    if (D_807F94B3 != 0 && !(buf->flags & 2)) {
        return 0;
    }

    if (actor != NULL && (actor->collisionFlags & 1)) {
        if (playerSlotMatchesSizeMask(gModelSlots[slotIdx].unk24->unk0, ((PlayerState *)actor->customState)->playerIndex) != 0) {
            return 0;
        }
    }

    sub7C = gModelSlots[slotIdx].unk7C;
    if (sub7C != NULL && sub7C->unk71 == 0) {
        return 0;
    }

    if (!(buf->flags & 1)) {
        modelSlotBuildTriangleBufferThunk(slotIdx, gModelSlots[slotIdx].unk24,
            gModelSlots[slotIdx].x, gModelSlots[slotIdx].y, gModelSlots[slotIdx].z,
            gModelSlots[slotIdx].rotY, gModelSlots[slotIdx].unk14, gModelSlots[slotIdx].unk18,
            gModelSlots[slotIdx].scale);
    } else {
        buf->timestamp = gFrameCounter;
    }

    tri = buf->tri_start;
    triEnd = buf->tri_end;
    if (tri != triEnd) {
        do {
            if (collisionCheckTriangleBoundingBoxXZ(tri, x, z) != 0 &&
                collisionCheckTriangleContainsPointXZ(tri, x, z) != 0 &&
                collisionCheckSurfaceFilter(tri->unk27, buf->unk25) != 0) {
                dx01 = tri->x[0] - tri->x[1];
                dy01 = tri->y[0] - tri->y[1];
                dz01 = tri->z[0] - tri->z[1];
                dx02 = tri->x[0] - tri->x[2];
                dy02 = tri->y[0] - tri->y[2];
                dz02 = tri->z[0] - tri->z[2];
                nx = (dy01 * dz02) - (dz01 * dy02);
                ny = (dz01 * dx02) - (dx01 * dz02);
                nzPart = dx01 * dy02;
                d = -((nx * tri->x[1]) + (ny * tri->y[1]) + ((nzPart - (dy01 * dx02)) * tri->z[1]));
                if (0.01 < ny * 2000.0 || ny * 2000.0 < -0.01) {
                    if (actor != NULL) {
                        val = 0.0 - (((x * nx) + (ny * -1000.0) + ((nzPart - (dy01 * dx02)) * z) + d) / (ny * 2000.0));
                        y = (2000.0 * val) - 1000.0;
                        collisionCheckSlopeAngle(refY, y, 0, actor, 0);
                        if (collisionGetFloorTriangleNormal(refY, y, 0, tri->unk24) != 0 && D_807F946D != 0) {
                            collisionAttachActorToObjectNode(actor, slotIdx, -1, 0, x, y, z);
                            actor->attachMode = 2;
                        }
                    }
                    if (D_807F94BC != 0) {
                        val = 0.0 - (((x * nx) + (ny * -1000.0) + ((nzPart - (dy01 * dx02)) * z) + d) / (ny * 2000.0));
                        collisionRecordTriangleF(tri, (2000.0 * val) - 1000.0);
                    }
                    if (collisionCheckTriangleWindingF32(tri) != 0) {
                        val = 0.0 - (((x * nx) + (ny * -1000.0) + ((nzPart - (dy01 * dx02)) * z) + d) / (ny * 2000.0));
                        y = (2000.0 * val) - 1000.0;
                        if (mathCheckCloserFloatThreshold(hitY, y, refY + 4.0, 0) != 0) {
                            hitTri = tri;
                            hit = 1;
                            hitY = y;
                        }
                    }
                }
            }
            tri++;
        } while (tri != triEnd);
    }

    if (hit != 0 && mathCheckCloserFloatThreshold(*floorYOut, hitY, refY + 4.0, 0) != 0) {
        *floorYOut = hitY;
        collisionStoreTriangleNormalAnglesF32(actor, hitTri, 1);
        sub7C = gModelSlots[slotIdx].unk7C;
        if (sub7C != NULL && sub7C->unk4F != 0) {
            D_807F94AC = 1;
        }
        if (actor != NULL) {
            if (actor->attachMode != 2 && actor->attachMode != 3) {
                collisionAttachActorToObjectNode(actor, slotIdx, hitTri->unk26, hitTri->unk27, x, hitY, z);
            }
            actor->unk78[0] = hitTri->unk25;
        }
        D_807F94B1 = hitTri->unk25;
    }
    return hit;
}


void collisionRecordTriangleF(CollisionTriF *tri, f32 height) {
    if (sCamFloorHitCount != 10) {
        sCamFloorHits[sCamFloorHitCount].height = height;
        if (collisionCheckTriangleWindingF32(tri)) {
            sCamFloorHits[sCamFloorHitCount].flags = 1;
        } else {
            sCamFloorHits[sCamFloorHitCount].flags = 2;
        }
        collisionStoreTriangleNormalAnglesF32(NULL, tri, 0);
        sCamFloorHits[sCamFloorHitCount].angle = D_807F94A8;
        sCamFloorHitCount++;
    }
}

s32 collisionCheckSurfaceFilter(u8 surface, u8 *excluded) {
    u8 i = 0;

    do {
        if (excluded[i] != 0xFF && excluded[i] == surface) {
            return 0;
        }
        i++;
    } while (i < 2);
    return 1;
}


void actorCheckNearbyNodeInteractions(Actor *actor, s16 slot, ModelPosNode *node) {
    u8 count = 0;

    if (node != NULL) {
        do {
            f32 dx = node->x - actor->x;
            f32 dz = node->z - actor->z;
            f32 dist;
            f32 dy;

            dx = dx * dx;
            dz = dz * dz;
            dist = sqrtf(dx + dz);
            dy = node->y - actor->y;
            if (dist < 5.0) {
                if (dy > 0.0f) {
                    if (dy < 25.0) {
                        collisionAttachActorToObjectNode(actor, slot, -1, 0, node->x, node->y, node->z);
                        actor->attachMode = 3;
                        actor->unk12F = count;
                        D_807F946C = 1;
                        D_807F9468 = node->y - 10.0f;
                    }
                }
            }
            node = node->next;
            count++;
        } while (node != NULL);
    }
}

void collisionStoreTriangleNormalAnglesF32(Actor *actor, CollisionTriF *tri, u8 record) {
    CrossProductStack3D sp;

    sp.v1[0] = tri->x[2] - tri->x[0];
    sp.v1[1] = tri->y[2] - tri->y[0];
    sp.v1[2] = tri->z[2] - tri->z[0];
    sp.v0[0] = tri->x[1] - tri->x[0];
    sp.v0[1] = tri->y[1] - tri->y[0];
    sp.v0[2] = tri->z[1] - tri->z[0];
    sp.cross[0] = (sp.v1[1] * sp.v0[2]) - (sp.v1[2] * sp.v0[1]);
    sp.cross[1] = (sp.v1[2] * sp.v0[0]) - (sp.v1[0] * sp.v0[2]);
    sp.cross[2] = (sp.v1[0] * sp.v0[1]) - (sp.v1[1] * sp.v0[0]);
    collisionStoreSurfaceNormalAngles(actor, sp.cross[0], sp.cross[1], sp.cross[2], tri->unk24, record, 1);
}

s32 collisionCheckTriangleWindingF32(CollisionTriF *tri) {
    CrossProductStack sp;

    sp.v1[0] = tri->x[2] - tri->x[0];
    sp.v1[2] = tri->z[2] - tri->z[0];
    sp.v0[0] = tri->x[1] - tri->x[0];
    sp.v0[2] = tri->z[1] - tri->z[0];
    sp.cross = (sp.v1[2] * sp.v0[0]) - (sp.v1[0] * sp.v0[2]);
    if (sp.cross <= 0.0) {
        return 1;
    }
    return 0;
}


void collisionAttachActorToObjectNode(Actor *actor, s16 slot, s8 bone, u8 surface, f32 x, f32 y, f32 z) {
    f32 pad2[10];
    float mtx[4][4];
    float pad[4][4];
    float invMtx[4][4];

    actor->cutsceneId = gModelSlots[slot].id;
    actor->unk10E = surface;
    actor->unk10F = bone;
    modelSlotBuildTransformMatrix(slot, bone, mtx);
    matrix4Invert(invMtx, mtx);
    guMtxXFMF(invMtx, x, y, z, &actor->unk100, &actor->unk104, &actor->unk108);
}

void actorUpdateSubnodeRotationAndMtx(Actor *actor) {
    f32 pad[10];
    float mtx[4][4];
    float padMtx[4][4];
    f32 x;
    f32 y;
    f32 z;
    s16 slot;
    s16 pad40;

    slot = hashTableLookup(actor->cutsceneId);
    if (slot != -1) {
        modelSlotBuildTransformMatrix(slot, actor->unk10F, mtx);
        if (gModelSlots[slot].unk7C != NULL) {
            if (actor->hasArcBounds == 0) {
                actor->yaw += (gModelSlots[slot].unk7C->unk34 * 4095.0f) / 360.0f;
                if (actor->yaw >= 0x1000) {
                    actor->yaw -= 0x1000;
                }
                if (actor->yaw < 0) {
                    actor->yaw += 0xFFF;
                }
            }
            actor->unk100 += gModelSlots[slot].unk7C->unk8;
            actor->unk108 += gModelSlots[slot].unk7C->unkC;
        }
        guMtxXFMF(mtx, actor->unk100, actor->unk104, actor->unk108, &x, &y, &z);
        actor->unk94 = x;
        actor->unk98 = z;
        if (actor->hasArcBounds == 0) {
            actor->x = x;
            actor->z = z;
        }
    }
}

s32 collisionCheckBoundingBoxXZ(CollisionBoundingBox *box, f32 x, f32 z) {
    if (x < box->minX) {
        return 0;
    }
    if (z < box->minZ) {
        return 0;
    }
    if (box->maxX < x) {
        return 0;
    }
    if (box->maxZ < z) {
        return 0;
    }
    return 1;
}

s32 collisionCheckBoundingBoxY(CollisionBoundingBox *box, f32 y) {
    if (y < box->minY) {
        return 0;
    }
    if (box->maxY < y) {
        return 0;
    }
    return 1;
}

s32 collisionCheckTriangleBoundingBoxXZ(CollisionTriF *tri, f32 x, f32 z) {
    f32 x0, x1, x2;
    f32 z0, z1, z2;
    f32 min;
    f32 max;

    x0 = tri->x[0];
    x1 = tri->x[1];
    x2 = tri->x[2];

    min = (x0 < x1) ? x0 : x1;
    if (!(min < x2)) {
        min = x2;
    }
    if (x < min) {
        return 0;
    }
    max = (x1 < x0) ? x0 : x1;
    if (!(x2 < max)) {
        max = x2;
    }
    if (max < x) {
        return 0;
    }

    z0 = tri->z[0];
    z1 = tri->z[1];
    z2 = tri->z[2];

    min = (z0 < z1) ? z0 : z1;
    if (!(min < z2)) {
        min = z2;
    }
    if (z < min) {
        return 0;
    }
    max = (z1 < z0) ? z0 : z1;
    if (!(z2 < max)) {
        max = z2;
    }
    if (max < z) {
        return 0;
    }
    return 1;
}

u8 collisionCheckTriangleContainsPointXZ(CollisionTriF *tri, f32 x, f32 z) {
    f64 cx;
    f64 cz;
    f64 a;
    f64 b;
    f64 dx;
    f64 dz;
    f64 ox;
    f64 oz;
    f64 c;
    s32 sideP;
    u32 outside;
    s32 sideC;
    s32 i;
    s32 pad; // frame size (D = 96)

    outside = 0;
    a = (f64)(tri->x[1] + tri->x[2]) * 0.5;
    b = (f64)(tri->z[1] + tri->z[2]) * 0.5;
    cx = (tri->x[0] + a) * 0.5;
    cz = (tri->z[0] + b) * 0.5;
    i = 0; sideC = 0; do { // LAYOUT: i = 0 joined to the loop head (move v0,zero lands after the hoisted ldc1s); FAKE: dead init sideC = 0 gives sideC an earlier first appearance than sideP (uopt colours ties in first-appearance order: sideC a0, sideP a1)
        switch (i) {
        case 0:
            dx = tri->x[1] - tri->x[0];
            dz = tri->z[1] - tri->z[0];
            ox = tri->x[0];
            oz = tri->z[0];
            break;
        case 1:
            dx = tri->x[2] - tri->x[0];
            dz = tri->z[2] - tri->z[0];
            ox = tri->x[0];
            oz = tri->z[0];
            break;
        case 2:
            dx = tri->x[2] - tri->x[1];
            dz = tri->z[2] - tri->z[1];
            ox = tri->x[1];
            oz = tri->z[1];
            break;
        }
        a = (x - ox) * dz;
        b = (z - oz) * dx;
        c = (cx - ox) * dz - (cz - oz) * dx;
        i++;
        if (b <= a) {
            sideP = 1;
        } else {
            sideP = -1;
        }
        if (c >= 0.0) {
            sideC = 1;
        } else {
            sideC = -1;
        }
        if (sideC != sideP) {
            outside = 1;
        }
    } while (i != 3);
    return outside == 0;
}

extern void *D_80748E14;
void assetEnsureTableLoaded();
extern s32 D_807F9678;
extern u8 D_807F967C;
extern u8 D_807F967D;
extern s32 *D_807F95A8[];
extern u8 D_80748E18[];
extern s32 *D_807FB1A0[];
typedef struct {
    void *dmaDst;
    void *buffer;
    u8 compressed;
} DmaQueueEntry;

// Actor collision box triangle (ActorSub140.triangles, stride 0x58). 70FD0 views the same record as
// CollisionBox with s32/s16 fields; here the world-space triangle is read as f32.
typedef struct CollisionBoxTri {
    /* 0x00 */ u8 pad0[0x24];
    /* 0x24 */ f32 x0;
    /* 0x28 */ f32 x1;
    /* 0x2C */ f32 x2;
    /* 0x30 */ f32 y0;
    /* 0x34 */ f32 y1;
    /* 0x38 */ f32 y2;
    /* 0x3C */ f32 z0;
    /* 0x40 */ f32 z1;
    /* 0x44 */ f32 z2;
    /* 0x48 */ u32 mtxOffset0; // per-vertex matrix byte offsets (0x40 per Mtx), -1 = box bounds
    /* 0x4C */ u32 mtxOffset1;
    /* 0x50 */ u32 mtxOffset2;
    /* 0x54 */ u8 pad54[2];
    /* 0x56 */ u8 unk56;
    /* 0x57 */ u8 pad57;
} CollisionBoxTri; // size = 0x58




s32 collisionTestActorBoxFloor(Actor *self, f32 x, f32 z, f32 refY, f32 *outFloorY) {
    f32 pad;
    CollisionBoxTri *hit_tri;
    f64 nx, ny, nz;
    f64 d;
    f64 val;
    f64 dx01, dy01, dz01, dx02, dy02, dz02;
    f32 y;
    s32 hit;
    s32 i;
    s32 j;
    Actor *actor;
    CollisionBoxTri *tri;
    u16 actor_count;
    f32 pad108[1];
    f32 hit_y;
    f32 padAC[4];
    Actor *hit_actor;
    f32 pad98[2];

    hit = 0;
    hit_y = 999999.0f;
    actor_count = gActiveActorCount;
    i = 0;
    if ((s32)actor_count > 0) {
        do {
            actor = gActiveActors[i].actor;
            if (!(actor->flags & 0x2000)) {
                if (actor->collision != NULL && self != actor && (actor->flags & 0x10)) {
                    tri = actor->collision->triangles;
                    j = 0;
                    if (actor->collision->triangleCount > 0) {
                        do {
                            if ((collisionCheckBoxTriangleBoundsXZ(tri, x, z) != 0) &&
                                (collisionCheckBoxTriangleContainsPointXZ(tri, x, z) != 0) &&
                                (tri->unk56 != 0)) {
                                dx01 = (f64)(tri->x0 - tri->x1);
                                dy01 = (f64)(tri->y0 - tri->y1);
                                dz01 = tri->z0 - tri->z1;
                                dx02 = tri->x0 - tri->x2;
                                dy02 = tri->y0 - tri->y2;
                                dz02 = tri->z0 - tri->z2;
                                nx = (dy01 * dz02) - (dz01 * dy02);
                                ny = (dz01 * dx02) - (dx01 * dz02);
                                nz = (dx01 * dy02) - (dy01 * dx02);
                                dy02 = 0.0;  // FAKE: kills nz store forwarding into d
                                d = -(nz * (f64)tri->z1 + (nx * (f64)tri->x1 + ny * (f64)tri->y1));
                                if (0.01 < ny * 2000.0 || ny * 2000.0 < -0.01) {
                                    if (self != NULL) {
                                        val = (0.0 - ((((f64)x * nx) + (ny * -1000.0) + (nz * (f64)z) + d) / (ny * 2000.0)));
                                        collisionCheckSlopeAngle(refY, (f32)((2000.0 * val) - 1000.0), 0, self, 0);
                                    }
                                    if (D_807F94BC != 0) {
                                        val = (0.0 - ((((f64)x * nx) + (ny * -1000.0) + (nz * (f64)z) + d) / (ny * 2000.0)));
                                        collisionRecordBoxTriangle(tri, (f32)((2000.0 * val) - 1000.0));
                                    }
                                    if (collisionCheckBoxTriangleWinding(tri) != 0) {
                                        val = (0.0 - ((((f64)x * nx) + (ny * -1000.0) + (nz * (f64)z) + d) / (ny * 2000.0)));
                                        y = (f32)((2000.0 * val) - 1000.0);
                                        if (mathCheckCloserFloatThreshold(hit_y, y, (f32)((f64)refY + 4.0), 0) != 0) {
                                            hit_tri = tri;
                                            hit_actor = actor;
                                            hit = 1;
                                            hit_y = y;
                                        }
                                    }
                                }
                            }
                            j++;
                            tri++;
                        } while (j < actor->collision->triangleCount);
                    }
                }
            }
            i++;
        } while (i < (s32)gActiveActorCount);
    }

    if (hit != 0 && mathCheckCloserFloatThreshold(*outFloorY, hit_y, (f32)((f64)refY + 4.0), 0) != 0) {
        *outFloorY = hit_y;
        collisionStoreBoxTriangleNormalAngles(self, hit_tri, 1);
        if (hit_actor->flags2 & 8) {
            D_807F94AD = 1;
        }
        if (self != NULL) {
            collisionTransformPointToActorLocal(self, hit_actor, hit_tri, x, hit_y, z);
        }
    }
    return hit;
}

void collisionRecordBoxTriangle(CollisionBoxTri *tri, f32 height) {
    if (sCamFloorHitCount != 0xA) {
        sCamFloorHits[sCamFloorHitCount].height = height;
        if (collisionCheckBoxTriangleWinding(tri) != 0) {
            sCamFloorHits[sCamFloorHitCount].flags = 1;
        } else {
            sCamFloorHits[sCamFloorHitCount].flags = 2;
        }
        collisionStoreBoxTriangleNormalAngles(NULL, tri, 0);
        sCamFloorHits[sCamFloorHitCount].angle = D_807F94A8;
        sCamFloorHitCount++;
    }
}

extern u8 gGfxBufferIndex;
extern Actor *D_807F9470;
extern f32 D_807F9474;
extern f32 D_807F9478;
extern f32 D_807F947C;
extern u32 D_807F9480;


void collisionTransformPointToActorLocal(Actor *actor, Actor *target, CollisionBoxTri *tri, f32 x, f32 y, f32 z) {
    float xfMtx[4][4];
    float invMtx[4][4];
    ActorSub140 *sub;
    s32 idx;
    Mtx *mtx;

    D_807F9470 = target;
    sub = target->collision;
    if (gFrameCounter == sub->unk88) {
        idx = gGfxBufferIndex;
    } else {
        idx = (gGfxBufferIndex ^ 1) & 0xFF;
    }
    mtx = sub->nodeMtx[idx];
    if ((tri->mtxOffset1 != tri->mtxOffset0) || (tri->mtxOffset2 != tri->mtxOffset0)) {
        D_807F94B2 = 1;
    }
    D_807F9480 = tri->mtxOffset0;
    if (tri->mtxOffset0 == -1) {
        memcpy(xfMtx, sub->modelMtxF, 0x40);
    } else {
        guMtxL2F(xfMtx, &mtx[tri->mtxOffset0 >> 6]);
    }
    matrix4Invert(invMtx, xfMtx);
    guMtxXFMF(invMtx, x, y, z, &D_807F9474, &D_807F9478, &D_807F947C);
}

void collisionTransformPointByActorMtx(Actor *actor, u32 mtxOffset, f32 *xInOut, f32 yIn, f32 *zInOut) {
    s32 idx;
    f32 xIn;
    f32 zIn;
    f32 yOut;
    ActorSub140 *sub;
    Mtx *mtx;
    float xfMtx[4][4];

    xIn = *xInOut;
    zIn = *zInOut;
    sub = actor->collision;
    if (gFrameCounter == sub->unk88) {
        idx = gGfxBufferIndex;
    } else {
        idx = gGfxBufferIndex ^ 1;
        idx = idx & 0xFF; // FAKE: split mask steers sub/idx v0/v1 allocation
    }
    mtx = sub->nodeMtx[idx];
    if (mtxOffset == -1) {
        memcpy(xfMtx, sub->modelMtxF, 0x40);
    } else {
        guMtxL2F(xfMtx, &mtx[mtxOffset >> 6]);
    }
    guMtxXFMF(xfMtx, xIn, yIn, zIn, xInOut, &yOut, zInOut);
}

s32 collisionCheckBoxTriangleBoundsXZ(CollisionBoxTri *tri, f32 x, f32 z) {
    s32 pad;
    f32 min_z;
    f32 max_x;
    f32 x0;
    f32 x1;
    f32 min_x;
    f32 x2;
    f32 z0;
    f32 z1;
    f32 z2;
    f32 max_z;

    min_x = ((x0 = tri->x0) < (x1 = tri->x1)) ? x0 : x1;
    x2 = tri->x2;
    min_x = (min_x < x2) ? min_x : x2;

    z0 = tri->z0;
    z1 = tri->z1;
    min_z = (z0 < z1) ? z0 : z1;
    z2 = tri->z2;
    min_z = (min_z < z2) ? min_z : z2;

    max_x = (x1 < x0) ? x0 : x1;
    max_x = (x2 < max_x) ? max_x : x2;

    max_z = (z1 < z0) ? z0 : z1;
    max_z = (z2 < max_z) ? max_z : z2;

    if ((x < min_x) || (max_x < x) || (z < min_z) || (max_z < z)) {
        return 0;
    }
    return 1;
}

u8 collisionCheckBoxTriangleContainsPointXZ(CollisionBoxTri *tri, f32 x, f32 z) {
    f64 cx;
    f64 cz;
    f64 a;
    f64 b;
    f64 dx;
    f64 dz;
    f64 ox;
    f64 oz;
    f64 c;
    s32 sideP;
    u32 outside;
    s32 sideC;
    s32 i;
    s32 pad; // frame size (D = 96)

    outside = 0;
    a = (f64)(tri->x2 + tri->x1) * 0.5;
    b = (f64)(tri->z2 + tri->z1) * 0.5;
    cx = (tri->x0 + a) * 0.5;
    cz = (tri->z0 + b) * 0.5;
    i = 0; sideC = 0; do { // LAYOUT: i = 0 joined to the loop head (move v0,zero lands after the hoisted ldc1s); FAKE: dead init sideC = 0 gives sideC an earlier first appearance than sideP (uopt colours ties in first-appearance order: sideC a0, sideP a1)
        switch (i) {
        case 0:
            dx = tri->x1 - tri->x0;
            dz = tri->z1 - tri->z0;
            ox = tri->x0;
            oz = tri->z0;
            break;
        case 1:
            dx = tri->x2 - tri->x0;
            dz = tri->z2 - tri->z0;
            ox = tri->x0;
            oz = tri->z0;
            break;
        case 2:
            dx = tri->x2 - tri->x1;
            dz = tri->z2 - tri->z1;
            ox = tri->x1;
            oz = tri->z1;
            break;
        }
        a = (x - ox) * dz;
        b = (z - oz) * dx;
        c = (cx - ox) * dz - (cz - oz) * dx;
        i++;
        if (b <= a) {
            sideP = 1;
        } else {
            sideP = -1;
        }
        if (c >= 0.0) {
            sideC = 1;
        } else {
            sideC = -1;
        }
        if (sideC != sideP) {
            outside = 1;
        }
    } while (i != 3);
    return outside == 0;
}

s32 collisionCheckBoxTriangleWinding(CollisionBoxTri *tri) {
    CrossProductStack sp;

    sp.v1[0] = tri->x2 - tri->x0;
    sp.v1[2] = tri->z2 - tri->z0;
    sp.v0[0] = tri->x1 - tri->x0;
    sp.v0[2] = tri->z1 - tri->z0;
    sp.cross = (sp.v1[2] * sp.v0[0]) - (sp.v1[0] * sp.v0[2]);
    if (sp.cross <= 0.0) {
        return 1;
    }
    return 0;
}

void collisionStoreBoxTriangleNormalAngles(Actor *actor, CollisionBoxTri *tri, u8 record) {
    CrossProductStack3D sp;

    sp.v1[0] = tri->x2 - tri->x0;
    sp.v1[1] = tri->y2 - tri->y0;
    sp.v1[2] = tri->z2 - tri->z0;
    sp.v0[0] = tri->x1 - tri->x0;
    sp.v0[1] = tri->y1 - tri->y0;
    sp.v0[2] = tri->z1 - tri->z0;
    sp.cross[0] = (sp.v1[1] * sp.v0[2]) - (sp.v1[2] * sp.v0[1]);
    sp.cross[1] = (sp.v1[2] * sp.v0[0]) - (sp.v1[0] * sp.v0[2]);
    sp.cross[2] = (sp.v1[0] * sp.v0[1]) - (sp.v1[1] * sp.v0[0]);
    collisionStoreSurfaceNormalAngles(actor, sp.cross[0], sp.cross[1], sp.cross[2], 1, record, 2);
}

extern s32 D_8000DDCC;
extern u32 *D_807F9520;
extern s32 *D_807F9528[];
extern void *D_807F9628[];
extern s32 D_807F9680;
extern u8 D_807FB220;
extern u8 D_807FB221;

void collisionInitTables(void) {
    s32 i;
    s32 size;

    size = 0x80;
    D_807F9520 = heapAlloc(0x80);
    dmaReadAssetDecompress(D_8000DDCC, D_807F9520, &size, 0, 0, 0, 0);

    for (i = 0; i < 0x20; i++) {
        D_807F9528[i] = 0;
        D_807F95A8[i] = 0;
    }

    for (i = 0; i < 0x14; i++) {
        D_807F9628[i] = 0;
    }

    D_807F9680 = 0;
    D_807F967C = 0;
    D_807F9678 = 0;
    D_807F967D = 0;

    for (i = 0; i < 0x20; i++) {
        if (D_80748E18[i] != 0) {
            D_807FB1A0[i] = assetLoad(0x1A, i, 1, 1);
        } else {
            D_807FB1A0[i] = NULL;
        }
    }

    D_807FB220 = 0;
    D_807FB221 = 0;
}

void assetInflateAndFree(void *compressed, void *out) {
    u8 *src;
    u8 *dst;

    src = compressed;
    dst = out;
    if (D_80748E14 == NULL) {
        D_80748E14 = heapAlloc(0x2400);
    }
    gunzip(&src, &dst, D_80748E14);
    heapFree(compressed);
}

extern DmaQueueEntry D_807FA8A0[];
extern s8 D_80746834;
extern OSMesgQueue D_807656D0;

void dmaDrainQueueAndFreeBuffer(void) {
    s32 i;

    i = 0;
    if (D_807F9680 > 0) {
        do {
            D_80746834 = 7;
            osRecvMesg(&D_807656D0, NULL, 1);
            D_80746834 = 0;
            if (D_807FA8A0[i].compressed != 0) {
                assetInflateAndFree(D_807FA8A0[i].dmaDst, D_807FA8A0[i].buffer);
            }
        } while (++i < D_807F9680);
    }
    if (D_80748E14 != NULL) {
        heapFree(D_80748E14);
        D_80748E14 = NULL;
    }
    D_807F9680 = 0;
}

s32 assetGetSize(s32 table, s32 index) {
    s32 romAddr;
    s32 size;

    assetEnsureTableLoaded();
    assetResolveRomRange(table, index, &romAddr, &size);
    if (size == 0) {
        return 0;
    }
    return romAddr;
}

s32 assetGetCachedSizeOrResolve(s32 table, s32 index) {
    s32 romAddr;
    s32 size;

    if (D_80748E18[table] != 0) {
        size = D_807FB1A0[table][index];
    } else {
        assetEnsureTableLoaded();
        assetResolveRomRange(table, index, &romAddr, &size);
    }
    return size;
}

void collisionResolveWallContact(void) {
    D_807F967C = 1;
}

void assetSetRomTableOffset(s32 offset) {
    D_807F9678 = offset;
}

extern OSIoMesg D_807F9688[];

void *assetLoad(s32 table, s32 index, u8 sync, u8 noCache) { // index: asset index, or a K0 address (0x80000000-0x9FFFFFFF) returned as is
    s32 pad;
    s32 romAddr;
    s32 size;
    s32 allocSize;
    void *buffer;

    assetEnsureTableLoaded();
    if (noCache == 0) {
        if ((index >= 0x80000000U) && (index < 0xA0000000U)) {
            collisionBstInsertByHash((void *)index, table, 0);
            D_807F967C = 0;
            D_807F9678 = 0;
            return (void *)index;
        }
        buffer = (void *)assetGetTableEntry(table, index);
        if (buffer != NULL) {
            collisionBstInsertByHash(buffer, table, index);
            D_807F967C = 0;
            D_807F9678 = 0;
            return buffer;
        }
    }
    assetResolveRomRange(table, index, &romAddr, &size);
    if (size == 0) {
        D_807F967C = 0;
        D_807F9678 = 0;
        return NULL;
    }
    if (D_80748E18[table] != 0) {
        allocSize = D_807FB1A0[table][index];
    } else {
        allocSize = size;
    }
    if (D_807F9678 == 0) {
        buffer = heapAlloc(allocSize);
    } else {
        buffer = heapAllocFromPool(D_807F9678, allocSize);
    }
    if (sync != 0) {
        if (D_80748E18[table] != 0) {
            void *compressed = heapAlloc(size);
            dmaReadAssetDecompress(romAddr, compressed, &size, 0, 0, 0, 0);
            assetInflateAndFree(compressed, buffer);
        } else {
            dmaReadAssetDecompress(romAddr, buffer, &size, 0, 0, 0, 0);
        }
    } else {
        if (D_807F9680 == 0xC0) {
            faultSetMessage(6, 0, 0, 0);
        }
        D_807FA8A0[D_807F9680].compressed = D_80748E18[table];
        if (D_80748E18[table] != 0) {
            D_807FA8A0[D_807F9680].dmaDst = heapAlloc(size);
            D_807FA8A0[D_807F9680].buffer = buffer;
        } else {
            D_807FA8A0[D_807F9680].buffer = buffer;
            D_807FA8A0[D_807F9680].dmaDst = buffer;
        }
        osInvalDCache(D_807FA8A0[D_807F9680].dmaDst, size);
        osPiStartDma(&D_807F9688[D_807F9680], 0, 0, romAddr, D_807FA8A0[D_807F9680].dmaDst, (u32)size, &D_807656D0);
        D_807F9680 += 1;
    }
    assetSetTableEntry(table, index, (s32)buffer);
    collisionBstInsertByHash(buffer, table, index);
    D_807F967C = 0;
    D_807F9678 = 0;
    return buffer;
}

void assetSetImmediateFree(void) {
    D_807F967D = 1;
}

void assetFreeBuffer(void *buffer, s32 line, s32 fileId) {
    s32 table;
    s32 index;

    if (collisionBstLookupAndDecrementByHash(buffer) == 0) {
        collisionBstDeleteByHash(buffer, &table, &index);
        assetSetTableEntry(table, index, 0);
        if (D_807F967D == 0) {
            heapFreeDeferred(buffer);
        } else {
            heapFree(buffer);
        }
    }
    D_807F967D = 0;
}

void assetSetTableEntry(s32 table, s32 index, s32 value) {
    if (D_807F95A8[table] != NULL) {
        D_807F95A8[table][index] = value;
    }
}

s32 assetResolveRomRange(s32 tableId, s32 assetIndex, s32 *outRomAddr, s32 *outSize) {
    s32 pad[2];
    s32 target;
    s32 end;
    u64 header;
    s32 *table;
    s32 start;
    s32 size;
    s32 index;

    index = assetIndex;
    table = &D_807F9528[tableId][assetIndex];
    start = table[0];
    if (start & 0x80000000) {
        size = 8;
        start &= 0x7FFFFFFF;
        dmaReadAssetDecompress(D_8000DDCC + start, &header, &size, 0, 0, 0, 0);
        target = (s16)(header >> 48);
        assetResolveRomRange(tableId, target, outRomAddr, outSize);
        index = target;
    } else {
        end = table[1] & 0x7FFFFFFF;
        *outRomAddr = D_8000DDCC + start;
        *outSize = end - start;
    }
    return index;
}

s32 assetGetTableEntry(s32 table, s32 index) {
    s32 *ptr = D_807F95A8[table];
    s32 ret = 0;

    if (ptr != NULL) {
        ret = ptr[index];
    }
    return ret;
}

void assetEnsureTableLoaded(s32 tableIndex) {
    u32 start;
    s32 pad50;
    u64 header;
    s32 pad44;
    u32 size;
    s32 headerSize;

    headerSize = 8;
    if (D_807F9528[tableIndex] != NULL) {
        return;
    }
    start = D_807F9520[tableIndex];
    dmaReadAssetDecompress(D_8000DDCC + start, &header, &headerSize, 0, 0, 0, 0);
    size = (u32)(header >> 32) - start;
    D_807F9528[tableIndex] = heapAlloc(size);
    dmaReadAssetDecompress(D_8000DDCC + start, D_807F9528[tableIndex], &size, 0, 0, 0, 0);
    switch (tableIndex) {
        case 4:
        case 7:
        case 14:
        case 25: {
            u32 i;
            D_807F95A8[tableIndex] = heapAlloc(size);
            for (i = 0; i < (u32)(size / 4); i++) {
                D_807F95A8[tableIndex][i] = 0;
            }
            break;
        }
        default:
            D_807F95A8[tableIndex] = NULL;
            break;
    }
}


typedef struct CollisionBstNodeBase {
    /* 0x00 */ s32 key;
    /* 0x04 */ u8 pad4[3];
    /* 0x07 */ u8 table;
    /* 0x08 */ u16 pad8;
    /* 0x0A */ u16 index;
    /* 0x0C */ s32 refCount;
    /* 0x10 */ u8 persistent;
    /* 0x11 */ u8 pad11[3];
    /* 0x14 */ struct CollisionBstNodeBase *left;
    /* 0x18 */ struct CollisionBstNodeBase *right;
} CollisionBstNodeBase;

s32 collisionBstCountNodes(CollisionBstNodeBase *node) {
    s32 count;

    if (node == NULL) {
        return 0;
    }
    count = collisionBstCountNodes(node->left);
    return collisionBstCountNodes(node->right) + count + 1;
}


void collisionBstLookupByHash(s32 key, s32 *outTable, s32 *outIndex) {
    collisionBstLookupOrAssert(D_807F9628[collisionGetBucketIndex(key)], key, outTable, outIndex);
}

typedef struct CollisionBstNode {
    /* 0x00 */ s32 key;
    /* 0x04 */ s32 table;
    /* 0x08 */ s32 index;
    /* 0x0C */ s32 refCount;
    /* 0x10 */ u8 persistent;
    /* 0x14 */ struct CollisionBstNode *left;
    /* 0x18 */ struct CollisionBstNode *right;
} CollisionBstNode;

void collisionBstLookupOrAssert(CollisionBstNode *node, u32 key, s32 *outTable, s32 *outIndex) {
    u8 idxA;
    u16 idxB;
    s32 frame;

    if (node == NULL) {
        idxA = 0;
        idxB = 0;
        frame = 0;
        collisionQueueSearch(key, &idxA, &idxB, &frame);
        faultSetMessage(7, idxA, idxB, gFrameCounter - frame);
    }
    if (key == node->key) {
        *outTable = node->table;
        *outIndex = node->index;
    } else if (node->key < key) {
        collisionBstLookupOrAssert(node->right, key, outTable, outIndex);
    } else {
        collisionBstLookupOrAssert(node->left, key, outTable, outIndex);
    }
}


void collisionBstInsertByHash(void *buffer, s32 table, s32 index) { // keyed by the loaded asset's address
    u32 bucket = collisionGetBucketIndex((u32)buffer);

    D_807F9628[bucket] = collisionBstInsert(D_807F9628[bucket], (u32)buffer, table, index);
}

CollisionBstNode *collisionBstInsert(CollisionBstNode *node, u32 key, s32 table, s32 index) {
    if (node == NULL) {
        node = (CollisionBstNode *)heapAlloc(sizeof(CollisionBstNode));
        node->refCount = 1;
        node->key = key;
        node->table = table;
        node->index = index;
        node->persistent = D_807F967C;
        node->right = NULL;
        node->left = NULL;
    } else if (key == node->key) {
        node->refCount++;
        if (D_807F967C) {
            node->persistent = 1;
        }
    } else if (node->key < key) {
        node->right = collisionBstInsert(node->right, key, table, index);
    } else {
        node->left = collisionBstInsert(node->left, key, table, index);
    }
    return node;
}


s32 collisionBstLookupAndDecrementByHash(void *buffer) {
    return collisionBstLookupAndDecrement(D_807F9628[collisionGetBucketIndex((u32)buffer)], (u32)buffer);
}

typedef struct CollisionQueueEntry {
    s32 frame;
    s32 key;
    u16 index;
    u8 table;
} CollisionQueueEntry;

extern CollisionQueueEntry D_807FB228[];

void collisionQueueSearch(s32 key, u8 *outTable, u16 *outIndex, s32 *outFrame) {
    s32 i;

    if ((i = D_807FB221 - 1) < 0) {
        i = 0x3F;
    }
    while (i != D_807FB220) {
        if (key == D_807FB228[i].key) {
            *outTable = D_807FB228[i].table;
            *outIndex = D_807FB228[i].index;
            *outFrame = D_807FB228[i].frame;
            break;
        }
        if (--i < 0) {
            i = 0x3F;
        }
    }
}

void collisionQueueAppend(s32 key, u8 table, u16 index) {
    u8 idx = D_807FB221;
    CollisionQueueEntry *item = &D_807FB228[idx];

    item->frame = gFrameCounter;
    item->key = key;
    item->table = table;
    item->index = index;
    D_807FB221 = idx + 1;

    if (D_807FB221 == 0x40) {
        D_807FB221 = 0;
    }

    if (D_807FB220 == D_807FB221) {
        D_807FB220++;
        if (D_807FB220 == 0x40) {
            D_807FB220 = 0;
        }
    }
}


s32 collisionBstLookupAndDecrement(CollisionBstNodeBase *node, u32 key) {
    u8 idxA;
    u16 idxB;
    s32 frame;

    if (node == NULL) {
        idxA = 0;
        idxB = 0;
        frame = 0;
        collisionQueueSearch(key, &idxA, &idxB, &frame);
        return 0;
    }
    if (key == node->key) {
        if (node->persistent == 0) {
            node->refCount--;
        }
        collisionQueueAppend(key, node->table, node->index);
        return node->refCount;
    }
    if (node->key < key) {
        return collisionBstLookupAndDecrement(node->right, key);
    }
    return collisionBstLookupAndDecrement(node->left, key);
}


void collisionBstDeleteByHash(void *buffer, s32 *table, s32 *index) {
    u32 bucket = collisionGetBucketIndex((u32)buffer);

    D_807F9628[bucket] = collisionBstDelete(D_807F9628[bucket], (u32)buffer, table, index);
}


CollisionBstNode *collisionBstDelete(CollisionBstNode *node, u32 key, s32 *out_val1, s32 *out_val2) {
    CollisionBstNode *old;

    if (node != NULL) {
        if (key == node->key) {
            *out_val1 = node->table;
            *out_val2 = node->index;
            if (node->left == NULL && node->right == NULL) {
                heapFree(node);
                node = NULL;
            } else if (node->left == NULL) {
                old = node;
                node = node->right;
                heapFree(old);
            } else if (node->right == NULL) {
                old = node;
                node = node->left;
                heapFree(old);
            } else {
                node->right = collisionBstExtractMin(node->right, &node->key, &node->table, &node->index, &node->refCount, &node->persistent);
            }
        } else if (node->key < key) {
            node->right = collisionBstDelete(node->right, key, out_val1, out_val2);
        } else {
            node->left = collisionBstDelete(node->left, key, out_val1, out_val2);
        }
    }
    return node;
}

CollisionBstNode *collisionBstExtractMin(CollisionBstNode *node, s32 *outKey, s32 *outTable, s32 *outIndex, s32 *outRefCount, u8 *outPersistent) {
    void *pad;
    CollisionBstNode *left = node->left;

    if (left == NULL) {
        CollisionBstNode *old;

        *outKey = node->key;
        *outTable = node->table;
        *outIndex = node->index;
        *outRefCount = node->refCount;
        *outPersistent = node->persistent;
        old = node;
        node = node->right;
        heapFree(old);
    } else {
        node->left = collisionBstExtractMin(left, outKey, outTable, outIndex, outRefCount, outPersistent);
    }
    return node;
}


void collisionBstRebalanceAll(void) {
    s32 i;

    for (i = 0; i < 20; i++) {
        collisionBstRebalanceBucket(i);
    }
}

typedef struct CollisionBstFlatItem {
    /* 0x00 */ s32 key;
    /* 0x04 */ s32 table;
    /* 0x08 */ s32 index;
    /* 0x0C */ s32 refCount;
    /* 0x10 */ u8 persistent;
} CollisionBstFlatItem;


void collisionBstRebalanceBucket(s32 bucket) {
    s32 count;
    void *buffer;
    CollisionBstNodeBase *new_root;
    s32 index;

    index = 0;
    count = collisionBstCountNodes(D_807F9628[bucket]);
    if (count != 0) {
        buffer = heapAlloc(count * 20);
        collisionBstFlatten(D_807F9628[bucket], buffer, &index);
        collisionBstSortFlatItems(buffer, 0, count - 1);
        new_root = collisionBstBuildBalanced(buffer, 0, count - 1);
        collisionBstFreeTree(D_807F9628[bucket]);
        D_807F9628[bucket] = new_root;
        heapFree(buffer);
    }
}


void collisionBstFreeTree(CollisionBstNodeBase *node) {
    if (node != NULL) {
        collisionBstFreeTree(node->left);
        collisionBstFreeTree(node->right);
        heapFree(node);
    }
}

CollisionBstNodeBase *collisionBstBuildBalanced(CollisionBstFlatItem *buffer, s32 start, s32 end) {
    CollisionBstNode *node;
    s32 mid;

    node = (CollisionBstNode *)heapAlloc(sizeof(CollisionBstNode));
    mid = (start + end) / 2;

    node->key = buffer[mid].key;
    node->table = buffer[mid].table;
    node->index = buffer[mid].index;
    node->refCount = buffer[mid].refCount;
    node->persistent = buffer[mid].persistent;

    if (start != mid) {
        node->left = (CollisionBstNode *)collisionBstBuildBalanced(buffer, start, mid - 1);
    } else {
        node->left = NULL;
    }

    if (end != mid) {
        node->right = (CollisionBstNode *)collisionBstBuildBalanced(buffer, mid + 1, end);
    } else {
        node->right = NULL;
    }

    return (CollisionBstNodeBase *)node;
}

void collisionBstFlatten(CollisionBstNode *node, CollisionBstFlatItem *buffer, s32 *index) {
    if (node == NULL) {
        return;
    }
    buffer[*index].key = node->key;
    buffer[*index].table = node->table;
    buffer[*index].index = node->index;
    buffer[*index].refCount = node->refCount;
    buffer[*index].persistent = node->persistent;
    (*index)++;
    collisionBstFlatten(node->left, buffer, index);
    collisionBstFlatten(node->right, buffer, index);
}

void collisionBstSortFlatItems(CollisionBstFlatItem *arr, s32 low, s32 high) {
    s32 i;
    s32 j;
    u32 pivot;
    CollisionBstFlatItem *pivot_ptr;
    u32 temp0;
    s32 temp1;
    s32 temp2;
    s32 temp3;
    u8 temp4;

    if (low < high) {
        pivot_ptr = (CollisionBstFlatItem *)((u8 *)arr + high * sizeof(CollisionBstFlatItem)); // FAKE: byte-offset pivot address keeps arr first in addu t5,s3,t6; &arr[high] swaps the operands
        pivot = pivot_ptr->key;
        i = low - 1;
        j = high;

        while (1) {
            while (arr[++i].key < pivot && i < high)
                ;
            while (pivot < arr[--j].key && low < j)
                ;
            if (i >= j) {
                break;
            }
            temp0 = arr[i].key;
            temp1 = arr[i].table;
            temp2 = arr[i].index;
            temp3 = arr[i].refCount;
            temp4 = arr[i].persistent;
            arr[i].key = arr[j].key;
            arr[i].table = arr[j].table;
            arr[i].index = arr[j].index;
            arr[i].refCount = arr[j].refCount;
            arr[i].persistent = arr[j].persistent;
            arr[j].key = temp0;
            arr[j].table = temp1;
            arr[j].index = temp2;
            arr[j].refCount = temp3;
            arr[j].persistent = temp4;
        }

        temp0 = arr[i].key;
        temp1 = arr[i].table;
        temp2 = arr[i].index;
        temp3 = arr[i].refCount;
        temp4 = arr[i].persistent;
        arr[i].key = pivot_ptr->key;
        arr[i].table = pivot_ptr->table;
        arr[i].index = pivot_ptr->index;
        arr[i].refCount = pivot_ptr->refCount;
        arr[i].persistent = pivot_ptr->persistent;
        if (!arr) {} // FAKE: dead check steers uopt coloring of the a0-a3 temps
        pivot_ptr->key = temp0;
        pivot_ptr->table = temp1;
        pivot_ptr->index = temp2;
        pivot_ptr->refCount = temp3;
        pivot_ptr->persistent = temp4;

        collisionBstSortFlatItems(arr, low, i - 1);
        collisionBstSortFlatItems(arr, i + 1, high);
    }
}

u32 collisionGetBucketIndex(u32 key) {
    return (key >> 12) % 20;
}
