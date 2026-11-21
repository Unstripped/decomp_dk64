#include "common.h"
#include "actor.h"
#include "model.h"
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

// This TU's .data (0x80748E10-0x80748E40): D_80748E10 is unreferenced; sAssetTableCompressed flags the asset
// tables loaded compressed.
s32 D_80748E10 = 0;
void *sInflateWindow = NULL;
u8 sAssetTableCompressed[0x28] = {
    1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 1, 0, 0, 1, 0, 1, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0
};

typedef struct CollisionStaticTri {
    /* 0x00 */ s16 x[3];
    /* 0x06 */ s16 y[3];
    /* 0x0C */ s16 z[3];
    /* 0x12 */ s16 flags;
    /* 0x14 */ u8 slopeType;
    /* 0x15 */ u8 surface; // surface type: collisionGetSurfaceFlags, Actor.unk78[0]
    /* 0x16 */ u8 tintPath; // low nibble: Actor.tintA level; high nibble: water path id (0xF = none)
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

extern CollisionBufferEntry *sCollisionCells;
extern s32 sCollisionCellCount;
extern u8 sCollisionCellsResident;
extern s32 gCurrentMap;
extern u8 gFloorQueryMode;

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
    s32 endOff;

    sCollisionCells = heapAlloc(0x11A8);
    sCollisionCellCount = header->unk18 * header->unk1A;
    data = assetLoad(3, gCurrentMap, 1, 0);
    sCollisionCellsResident = 0;
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
        sCollisionCellsResident = 1;
    }
    base = assetGetSize(3, gCurrentMap);
    cursor = data + 4;
    for (i = 0; i < sCollisionCellCount; i++) {
        sCollisionCells[i].lastUsedFrame = 0;
        cellStart = cursor + 4;
        off = cursor - data;
        sCollisionCells[i].romAddr = base + off + 4;
        endOff = *(u32 *)cursor;
        cellEnd = data + endOff;
        cursor = cellEnd;
        if (sCollisionCellsResident) {
            sCollisionCells[i].tris = (CollisionStaticTri *)cellStart;
            sCollisionCells[i].trisEnd = (CollisionStaticTri *)cellEnd;
        } else {
            sCollisionCells[i].tris = NULL;
            sCollisionCells[i].trisEnd = NULL;
        }
        sCollisionCells[i].size = cellEnd - cellStart;
    }
    if (!sCollisionCellsResident) {
        assetSetImmediateFree();
        assetFreeBuffer(data, 0xC3, 0x3A);
    }
    gFloorQueryMode = 0;
}


void collisionSetQueryMode(u8 mode) {
    gFloorQueryMode = mode;
}

extern u8 sFloorQueryIsCamera;
extern u8 sRecordCamFloorHits;
extern f32 sFloorY;


void collisionQueryActorFloor(Actor *actor, u8 *hasFloor, f32 *floorY, u8 *hasWater, f32 *waterY, u8 mode) {
    f32 posX;
    f32 posY;
    f32 posZ;

    sRecordCamFloorHits = 0;
    sFloorQueryIsCamera = 0;
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
        sFloorQueryIsCamera = 1;
    } else {
        sFloorQueryIsCamera = 0;
    }
    sRecordCamFloorHits = 1;
    found = collisionFindFloorAtPoint(NULL, x, y, z, &slopeHit, &slopeY, &normalHit, &normalY, 0);
    *outFloorY = sFloorY;
    return found;
}

extern u8 sHazardFloorContact;
extern u8 sHazardFloorKind;
extern u8 sBelowHazardSurface;
extern u8 D_807F94B7;
extern u8 sFloorSource;

void collisionClearFlags(void) {
    sHazardFloorContact = 0;
    sHazardFloorKind = 0;
    sBelowHazardSurface = 0;
    D_807F94B7 = 0;
}

u8 collisionGetStateByte(void) {
    return sFloorSource;
}


extern f32 sCeilingClampY;
extern u8 D_807F9464;
extern f32 D_807F9468;
extern u8 D_807F946C;
extern u8 sAllowObjectAttach;
extern u8 D_807F946E;
extern Actor *D_807F9470;
extern f32 D_807F9474;
extern f32 D_807F9478;
extern f32 D_807F947C;
extern u32 D_807F9480;
extern u8 sWaterSurfaceHit;
// Per-source floor tables indexed by source (0 mesh, 1 dynamic, 2 box); elements 1 and 2 also
// have their own symbols (D_807F9492/94, D_807F949A/9C, D_807F949F/94A0), which the reloc check requires.
extern s16 sSourceTiltYaw[];
extern s16 D_807F9492;
extern s16 D_807F9494;
extern s16 sSourceTiltPitch[];
extern s16 D_807F949A;
extern s16 D_807F949C;
extern u8 D_807F949E[];
extern u8 D_807F949F;
extern u8 D_807F94A0;
extern s16 sFloorTiltYaw;
extern s16 sFloorTiltPitch;
extern u8 sFloorGrabbable;
extern u8 sMeshFloorGrabbable;
extern u8 sObjectFloorGrabbable;
extern u8 D_807F94AD;
extern u8 D_807F94B2;
extern u8 sFloorOnWaterMesh;
extern PlayerState *sFloorQueryPlayer;

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
    if (gFloorQueryMode == 1) {
        collisionClearFlags();
        *outHasFloor = 0;
        *outHasWater = 0;
        gFloorQueryMode = 0;
        return 0;
    }
    if (actor != NULL) {
        actor->attachMode = 0;
        actor->contactFlags &= 0xFBF1;
        actor->cutsceneId = -1;
        sFloorOnWaterMesh = 0;
        D_807F9464 = 0;
        D_807F946C = 0;
        sAllowObjectAttach = mode;
        actor->renderFlags &= ~0x40;
        if (actor->collisionFlags & 1) {
            sFloorQueryPlayer = actor->customState;
            sFloorQueryPlayer->stateFlags &= ~0x6000;
        }
    }
    sFloorSource = 0;
    sMeshFloorGrabbable = 0;
    sObjectFloorGrabbable = 0;
    D_807F94AD = 0;
    collisionClearFlags();
    D_807F94B2 = 0;
    sWaterSurfaceHit = 0;
    sCamFloorHitCount = 0;
    meshY = y;
    meshHit = collisionTestSubmeshBoundary(x, z, &meshY, actor);
    if ((meshHit != 0) && (actor != NULL)) {
        actor->unkA8 = meshY;
        actor->floorSurfaceType = D_807F949E[0];
    }
    if (gFloorQueryMode != 2) {
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
        if (collisionPickCloserFloor(dynY, meshY, threshold, 0) != 0) {
            source = 1;
        } else {
            source = 2;
        }
        break;
    case 4:
        source = 3;
        break;
    case 5:
        if (collisionPickCloserFloor(boxY, meshY, threshold, 0) != 0) {
            source = 1;
        } else {
            source = 3;
        }
        break;
    case 6:
        if (collisionPickCloserFloor(boxY, dynY, threshold, 0) != 0) {
            source = 2;
        } else {
            source = 3;
        }
        break;
    case 7:
        if (collisionPickCloserFloor(dynY, meshY, threshold, 0) != 0) {
            if (collisionPickCloserFloor(boxY, meshY, threshold, 0) != 0) {
                source = 1;
            } else {
                source = 3;
            }
        } else if (collisionPickCloserFloor(dynY, boxY, threshold, 0) != 0) {
            source = 3;
        } else {
            source = 2;
        }
    }
    switch (source) {
    default:
        sFloorGrabbable = 0;
        break;
    case 1:
        if (actor != NULL) {
            actor->floorSlopeType = D_807F949E[0];
            actor->floorTiltPitch = sSourceTiltPitch[0];
            actor->floorTiltYaw = sSourceTiltYaw[0];
            actor->floorY = meshY;
            if ((sFloorOnWaterMesh != 0) && (actor->prevContactFlags & 1)) {
                actor->contactFlags |= 0x400;
            }
        }
        sFloorTiltPitch = sSourceTiltPitch[0];
        sFloorTiltYaw = sSourceTiltYaw[0];
        sFloorY = meshY;
        sFloorGrabbable = sMeshFloorGrabbable;
        sFloorSource = 1;
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
        sFloorTiltPitch = D_807F949A;
        sFloorTiltYaw = D_807F9492;
        sFloorY = dynY;
        sFloorGrabbable = sObjectFloorGrabbable;
        sFloorSource = 2;
        break;
    case 3:
        if (actor != NULL) {
            actor->floorSlopeType = D_807F94A0;
            actor->floorTiltPitch = D_807F949C;
            actor->floorTiltYaw = D_807F9494;
            actor->floorY = boxY;
            if (actor->prevContactFlags & 1) {
                actorAppendRiderPoint(actor, D_807F9470, D_807F9474, D_807F9478, D_807F947C, D_807F9480, D_807F94B2);
                actor->contactFlags |= 8;
            }
        }
        sFloorTiltPitch = D_807F949C;
        sFloorTiltYaw = D_807F9494;
        sFloorY = boxY;
        sFloorGrabbable = D_807F94AD;
        sFloorSource = 3;
        break;
    }
    *outHasFloor = D_807F9464;
    *outFloorY = sCeilingClampY;
    *outHasWater = D_807F946C;
    *outWaterY = D_807F9468;
    gFloorQueryMode = 0;
    return (u8)(meshHit | dynHit | boxHit);
}

extern u8 D_807F946E;
extern u8 D_807F94B1;

u8 collisionGetHitStatus(void) {
    return D_807F946E;
}

u8 collisionIsGroundImpact(void) {
    return sHazardFloorContact;
}

u8 collisionIsHeavyGroundImpact(void) {
    return sHazardFloorKind;
}

u8 collisionGetFloorType(void) {
    return sBelowHazardSurface;
}

u8 collisionGetMaterialType(void) {
    return D_807F94B7;
}

void collisionGetCoords(s16 *outX, s16 *outZ) {
    *outX = sFloorTiltYaw;
    *outZ = sFloorTiltPitch;
}

u8 collisionGetSurfaceFlags(void) {
    return D_807F94B1;
}

u8 collisionGetHitFlags(void) {
    return sFloorGrabbable;
}

extern s16 D_807F94A6;
extern s16 sLastNormalPitch;

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
        sSourceTiltYaw[source] = yaw & 0xFFF;
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
        sSourceTiltPitch[source] = pitch;
    }
    sLastNormalPitch = pitch;
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
            kong = gPlayerSlots[gCurrentPlayerIndex].sizeMode;
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
                sCeilingClampY = floorY - maxStep;
                if (scaled) {
                    sCeilingClampY /= 6.0f;
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

s32 collisionPickCloserFloor(f32 firstY, f32 secondY, f32 threshold, u8 wide) {
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

extern f32 D_807F9488;
extern u8 sFloorLightLevel;

u8 collisionCheckGroundAtPoint(f32 x, f32 z, f32 *yInOut) {
    u8 ret;

    sWaterSurfaceHit = 0;
    sCamFloorHitCount = 0;
    ret = collisionTestSubmeshBoundary(x, z, yInOut, NULL);
    sFloorTiltPitch = sSourceTiltPitch[0];
    sFloorTiltYaw = sSourceTiltYaw[0];
    return ret;
}

u8 collisionGetFloorHeight(f32 *outY) {
    *outY = D_807F9488;
    return sWaterSurfaceHit;
}

u8 collisionGetSurfaceType(void) {
    return sFloorLightLevel;
}


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
        sFloorOnWaterMesh = 1;
        break;
    case 3:
        temp = (f64)*yInOut + 4.0;
        if (collisionPickCloserFloor(staticY, gridY, temp, 0) != 0) {
            *yInOut = gridY;
            sFloorOnWaterMesh = 1;
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
    s32 cellX;
    s32 cellZ;
    f32 px;

    hit = 0;
    bestY = 999999.0f;
    node = gEffectNodeList;
    threshold = *height + 4.0;
    while (node != NULL) {
        if (node->sub->minX <= posX && node->sub->minZ <= posZ && posX <= node->sub->maxX && posZ <= node->sub->maxZ) {
            px = posX * 6.0f;
            pz = posZ * 6.0f;
            tableFlag = effectGetTableFlag(node);
            cellX = (posX - node->sub->minX) / (f32)node->gridStep;
            cellZ = (posZ - node->sub->minZ) / (f32)node->gridStep;

            x[0] = node->gridStep * cellX + node->sub->minX;
            z[0] = node->gridStep * cellZ + node->sub->minZ;
            y[0] = effectWaterGetHeightAt(node, x[0], z[0], tableFlag);

            x[1] = (cellX + 1) * node->gridStep + node->sub->minX;
            z[1] = z[0];
            y[1] = effectWaterGetHeightAt(node, x[1], z[1], tableFlag);
            x[2] = x[0];
            z[2] = (cellZ + 1) * node->gridStep + node->sub->minZ;
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

            if (collisionPointInTriangleXZS16(&tri, px, pz) != 0) {
                floorY = collisionTriangleHeightAtXZ(&tri, px, pz) / 6.0f;
            } else {
                tri.x[1] = x[2] * 6.0f;
                tri.y[1] = y[2] * 6.0f;
                tri.z[1] = z[2] * 6.0f;
                floorY = collisionTriangleHeightAtXZ(&tri, px, pz) / 6.0f;
            }

            switch (node->sub->unk60) {
            case 0:
            case 2:
            case 3:
                if ((node->sub->unk60 == 2 || node->sub->unk60 == 3) && (floorY < *height ? *height - floorY : -(*height - floorY)) < 6.0f) {
                    switch (node->sub->unk60) {
                    case 2:
                        sHazardFloorKind = 2;
                        break;
                    case 3:
                        sHazardFloorKind = 1;
                        break;
                    }
                }
                hit = 1;
                if (collisionPickCloserFloor(bestY, floorY, threshold, 0) != 0) {
                    bestY = floorY;
                }
                break;
            case 1:
                if (actor != NULL) {
                    if (actor->y < floorY) {
                        actor->contactFlags |= 4;
                        actor->waterPathId[0] = -1;
                        if (node->unk4A & 1) {
                            sBelowHazardSurface = 1;
                        }
                    }
                    actor->waterY = floorY;
                    actor->contactFlags |= 2;
                }
                sWaterSurfaceHit = 1;
                D_807F9488 = floorY;
                break;
            }
        }
        node = node->next;
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

extern s32 sCollisionCellCount;
extern s32 gCurrentMap;
extern u16 D_807F9450;
extern u16 D_807F9452;
extern u16 D_807F9454;
extern u16 D_807F9456;
extern u8 sMapOffsetSlotsMoving;

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
    f64 padD;
    f64 d;
    f64 dx01, dy01, dz01, dx02, dy02, dz02;
    f64 val;
    f32 diff;
    f32 t;
    f32 floorY;
    u8 hit;
    f32 threshold;
    s32 padB[1];
    u8 closer;
    s32 padC[3];
    f32 cur;
    s32 iz;
    s32 ix;

    hit = 0;
    floorY = 999999.0f;
    cell = ((s32)z / D_807F9452) * D_807F9454 + (s32)x / D_807F9450;
    cur = *yInOut;
    threshold = (f32)((f64)*yInOut + 4.0);
    threshold = threshold * 6.0f;
    if (cell >= sCollisionCellCount) {
        return 0;
    }
    if (D_807F9454 <= x / D_807F9450 || x < 0.0) {
        if (gCurrentMap == 0x57 && actor != NULL) {
            return collisionTestHardcodedFloorPlane(&floorY, threshold, cur, yInOut);
        }
        return 0;
    }
    if (D_807F9456 <= z / D_807F9452 || z < 0.0) {
        if (gCurrentMap == 0x57 && actor != NULL) {
            return collisionTestHardcodedFloorPlane(&floorY, threshold, cur, yInOut);
        }
        return 0;
    }
    dynamicBufferAllocateEntry(cell);
    x = x * 6.0f;
    z = z * 6.0f;
    if (actor != NULL && actor->floorTriangle != NULL && collisionCheckTriangleXZBoundsS16(actor->floorTriangle, (s32)x, (s32)z) != 0 &&
        collisionPointInTriangleXZS16(actor->floorTriangle, x, z) != 0 && sMapOffsetSlotsMoving == 0) {
        tri = actor->floorTriangle;
        triEnd = tri + 1;
    } else {
        tri = sCollisionCells[cell].tris;
        triEnd = sCollisionCells[cell].trisEnd;
    }
    iz = (s32)z;
    ix = (s32)x;
    while (tri != triEnd) {
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
                    sBelowHazardSurface = 1;
                }
                if ((tri->flags & 0x100) && actor != NULL && (actor->collisionFlags & 1)) {
                    if ((f64)(*yInOut * 6.0f) < h2 && ((diff = h2 - (f64)(*yInOut * 6.0f)) < 600.0f)) {
                        sFloorQueryPlayer->stateFlags |= 0x2000;
                    }
                }
                if ((tri->flags & 0xA00) && actor != NULL && (actor->collisionFlags & 1)) {
                    if ((f64)(*yInOut * 6.0f) < h2 && ((diff = h2 - (f64)(*yInOut * 6.0f)) < 800.0f)) {
                        sFloorQueryPlayer->stateFlags |= 0x4000;
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
                            sHazardFloorContact = 1;
                        }
                        if ((tri->flags & 0x40) && diff < 40.0f) {
                            sHazardFloorKind = 1;
                        }
                    }
                } else {
                    if (sRecordCamFloorHits != 0) {
                        collisionRecordTriangleS(tri, (f32)h2);
                    }
                    if (!(tri->flags & 1)) {
                        collisionCheckSlopeAngle(*yInOut * 6.0f, (f32)h2, 1, actor, 0);
                        collisionGetFloorTriangleNormal(*yInOut * 6.0f, (f32)h2, 1, tri->slopeType);
                        closer = collisionPickCloserFloor(floorY, (f32)h2, threshold, 1);
                        if (collisionCheckTriangleWindingS16(tri) != 0 && closer != 0) {
                            hit = 1;
                            floorY = (f32)h2;
                            hitTri = tri;
                            sFloorLightLevel = tri->tintPath & 0xF;
                            if (h2 < (f64)(*yInOut * 6.0f)) {
                                diff = (f64)(*yInOut * 6.0f) - h2;
                            } else {
                                diff = -((f64)(*yInOut * 6.0f) - h2);
                            }
                            if (diff > 30.0f) {
                                t = (diff - 30.0f) / 120.0f;
                                if ((f64)t > 1.0) {
                                    sFloorLightLevel = 0xF;
                                } else {
                                    sFloorLightLevel = (u32)((f32)sFloorLightLevel + (f32)(0xF - sFloorLightLevel) * t);
                                }
                            }
                            collisionStoreTriangleNormalAnglesS16(actor, tri, 1);
                            if (actor != NULL) {
                                actor->floorTriSurface[0] = tri->surface;
                                actor->tintA = sFloorLightLevel;
                            }
                            D_807F94B1 = tri->surface;
                            if (tri->flags & 2) {
                                *yInOut = floorY / 6.0f;
                                if (!(tri->flags & 8)) {
                                    sMeshFloorGrabbable = 1;
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
                                actor->waterPathId[0] = tri->tintPath >> 4;
                                if (actor->waterPathId[0] == 0xF) {
                                    actor->waterPathId[0] = -1;
                                }
                            }
                            actor->contactFlags |= 2;
                            actor->waterY = h2 / 6.0;
                        }
                        if (tri->flags & 0x20) {
                            collisionCheckSlopeAngle(*yInOut * 6.0f, (f32)h2, 1, actor, 1);
                        }
                        sWaterSurfaceHit = 1;
                        D_807F9488 = (f32)(h2 / 6.0);
                    }
                }
            }
        }
        tri++;
    }
    if (hit) {
        *yInOut = floorY / 6.0f;
        if (!(hitTri->flags & 8)) {
            sMeshFloorGrabbable = 1;
        }
        if (hitTri->flags & 0x2000) {
            D_807F946E = 1;
        }
        if (actor != NULL && (hitTri->flags & 0x1000)) {
            actor->renderFlags |= 0x40;
        }
    }
    if (gCurrentMap == 0x57 && actor != NULL) {
        hit |= collisionTestHardcodedFloorPlane(&floorY, threshold, cur, yInOut);
    }
    if (actor != NULL) {
        actor->floorTriangle = NULL;
    }
    return hit;
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
        sHazardFloorContact = 1;
    }
    if (collisionPickCloserFloor(*bestY, 684.0f, threshold, 1)) {
        *yInOut = 114.0f;
        return 1;
    }
    return 0;
}

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
        sCamFloorHits[sCamFloorHitCount].angle = sLastNormalPitch;
        sCamFloorHitCount++;
    }
}

void dynamicBufferAllocateEntry(s32 index) {
    u32 size;

    if (sCollisionCells[index].tris == NULL) {
        size = sCollisionCells[index].size;
        if (size != 0) {
            sCollisionCells[index].tris = heapAlloc(size);
            sCollisionCells[index].trisEnd = sCollisionCells[index].tris + size / sizeof(CollisionStaticTri);
            dmaReadAssetDecompress(sCollisionCells[index].romAddr, sCollisionCells[index].tris, &size, 0, 0, 0, 0);
        }
    }
    sCollisionCells[index].lastUsedFrame = gFrameCounter;
}

void dynamicBufferPurgeExpired(void) {
    s32 i;

    if (!sCollisionCellsResident) {
        for (i = 0; i < sCollisionCellCount; i++) {
            if (sCollisionCells[i].tris != NULL && (gFrameCounter - sCollisionCells[i].lastUsedFrame) >= 21) {
                actorClearBufferReferences(i);
                heapFree(sCollisionCells[i].tris);
                sCollisionCells[i].tris = NULL;
                sCollisionCells[i].trisEnd = NULL;
            }
        }
    }
}

void actorClearBufferReferences(s32 cell) {
    s32 i;
    CollisionStaticTri *min = sCollisionCells[cell].tris;
    CollisionStaticTri *max = sCollisionCells[cell].trisEnd;

    for (i = 0; i < gActiveActorCount; i++) {
        Actor *actor = gActiveActors[i].actor;
        CollisionStaticTri *tri = actor->floorTriangle;

        if (!(actor->flags & 0x2000) && tri >= min && tri <= max) {
            actor->floorTriangle = NULL;
        }
    }
}

s32 collisionCheckTriangleWindingS16(CollisionStaticTri *tri) {
    f32 v1[3];
    f32 v0[3];
    f32 cross[1]; // ORIG: the target stores the cross product to its own stack word below v0 (swc1 $f10,4(sp) at 0x293c, never reloaded: cvt.d.s at 0x2938 converts the register copy); a coloured scalar drops the store

    v1[0] = tri->x[2] - tri->x[0];
    v1[2] = tri->z[2] - tri->z[0];
    v0[0] = tri->x[1] - tri->x[0];
    v0[2] = tri->z[1] - tri->z[0];
    cross[0] = (v1[2] * v0[0]) - (v1[0] * v0[2]);
    if (cross[0] <= 0.0) {
        return 1;
    }
    return 0;
}

void collisionStoreTriangleNormalAnglesS16(Actor *actor, CollisionStaticTri *tri, u8 record) {
    f32 v1[3];
    f32 v0[3];
    f32 cross[3];

    v1[0] = tri->x[2] - tri->x[0];
    v1[1] = tri->y[2] - tri->y[0];
    v1[2] = tri->z[2] - tri->z[0];
    v0[0] = tri->x[1] - tri->x[0];
    v0[1] = tri->y[1] - tri->y[0];
    v0[2] = tri->z[1] - tri->z[0];
    cross[0] = (v1[1] * v0[2]) - (v1[2] * v0[1]);
    cross[1] = (v1[2] * v0[0]) - (v1[0] * v0[2]);
    cross[2] = (v1[0] * v0[1]) - (v1[1] * v0[0]);
    collisionStoreSurfaceNormalAngles(actor, cross[0], cross[1], cross[2], tri->slopeType, record, 0);
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

    val = (p0 > p1) ? p0 : p1;
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

    val = (p0 > p1) ? p0 : p1;
    if (val <= p2) {
        val = p2;
    }
    if (val < z) {
        return 0;
    }

    return 1;
}

u8 collisionPointInTriangleXZS16(CollisionStaticTri *tri, f32 x, f32 z) {
    f64 pad; // pad: reproduces slot layout (unused)
    f64 hx;
    f64 pad0[1]; // pad: reproduces slot layout (unused)
    f64 sidePt;
    f64 ex, ez, ox, oz;
    f64 midX;
    f64 pad1[1]; // pad: reproduces slot layout (unused)
    f64 hz;
    f64 midZ;
    f64 pad3; // pad: reproduces slot layout (unused)
    f64 pad4; // pad: reproduces slot layout (unused)
    f64 sideRef;
    f64 pad2[1]; // pad: reproduces slot layout (unused)
    f64 sideMid;
    f64 z0;
    s32 i;
    u32 mismatch = 0;

    hx = (tri->x[1] + tri->x[2]) * 0.5;
    hz = (tri->z[1] + tri->z[2]) * 0.5;
    midX = (tri->x[0] + hx) * 0.5;
    z0 = tri->z[0];
    midZ = (z0 + hz) * 0.5;

    for (i = 0; i < 3; i++) {
        switch (i) {
        case 0:
            ex = tri->x[1] - tri->x[0];
            ez = tri->z[1] - tri->z[0];
            ox = tri->x[0];
            oz = z0;
            break;
        case 1:
            ex = tri->x[2] - tri->x[0];
            ez = tri->z[2] - tri->z[0];
            ox = tri->x[0];
            oz = z0;
            break;
        case 2:
            ex = tri->x[2] - tri->x[1];
            ez = tri->z[2] - tri->z[1];
            ox = tri->x[1];
            oz = tri->z[1];
            break;
        }

        sidePt = (x - ox) * ez;
        sideRef = (z - oz) * ex;
        sideMid = ((midX - ox) * ez) - ((midZ - oz) * ex);

        if ((sideRef <= sidePt ? 1 : -1) != (sideMid >= 0.0 ? 1 : -1)) {
            mismatch = 1;
        }
    }

    return mismatch == 0;
}


extern ModelSlot *gModelSlots;

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
    CsState *csState;
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

    buf = &gModelSlots[slotIdx].triBuffer;
    if (actor != NULL && gModelSlots[slotIdx].attachPoints != NULL && sAllowObjectAttach != 0) {
        actorCheckNearbyNodeInteractions(actor, slotIdx, gModelSlots[slotIdx].attachPoints);
    }

    if (!(buf->flags & 4)) {
        return 0;
    }

    if (collisionCheckBoundingBoxXZ(&buf->bbox, x, z) == 0) {
        return 0;
    }

    if (sFloorQueryIsCamera != 0 && !(buf->flags & 2)) {
        return 0;
    }

    if (actor != NULL && (actor->collisionFlags & 1)) {
        if (playerSlotMatchesSizeMask(gModelSlots[slotIdx].asset->unk0, ((PlayerState *)actor->customState)->playerIndex) != 0) {
            return 0;
        }
    }

    csState = gModelSlots[slotIdx].csState;
    if (csState != NULL && csState->unk71 == 0) {
        return 0;
    }

    if (!(buf->flags & 1)) {
        modelSlotBuildTriangleBufferThunk(slotIdx, gModelSlots[slotIdx].asset,
            gModelSlots[slotIdx].x, gModelSlots[slotIdx].y, gModelSlots[slotIdx].z,
            gModelSlots[slotIdx].rotX, gModelSlots[slotIdx].rotY, gModelSlots[slotIdx].rotZ,
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
                        if (collisionGetFloorTriangleNormal(refY, y, 0, tri->unk24) != 0 && sAllowObjectAttach != 0) {
                            collisionAttachActorToObjectNode(actor, slotIdx, -1, 0, x, y, z);
                            actor->attachMode = 2;
                        }
                    }
                    if (sRecordCamFloorHits != 0) {
                        val = 0.0 - (((x * nx) + (ny * -1000.0) + ((nzPart - (dy01 * dx02)) * z) + d) / (ny * 2000.0));
                        collisionRecordTriangleF(tri, (2000.0 * val) - 1000.0);
                    }
                    if (collisionCheckTriangleWindingF32(tri) != 0) {
                        val = 0.0 - (((x * nx) + (ny * -1000.0) + ((nzPart - (dy01 * dx02)) * z) + d) / (ny * 2000.0));
                        y = (2000.0 * val) - 1000.0;
                        if (collisionPickCloserFloor(hitY, y, refY + 4.0, 0) != 0) {
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

    if (hit != 0 && collisionPickCloserFloor(*floorYOut, hitY, refY + 4.0, 0) != 0) {
        *floorYOut = hitY;
        collisionStoreTriangleNormalAnglesF32(actor, hitTri, 1);
        csState = gModelSlots[slotIdx].csState;
        if (csState != NULL && csState->unk4F != 0) {
            sObjectFloorGrabbable = 1;
        }
        if (actor != NULL) {
            if (actor->attachMode != 2 && actor->attachMode != 3) {
                collisionAttachActorToObjectNode(actor, slotIdx, hitTri->unk26, hitTri->unk27, x, hitY, z);
            }
            actor->floorTriSurface[0] = hitTri->unk25;
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
        sCamFloorHits[sCamFloorHitCount].angle = sLastNormalPitch;
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
    f32 v1[3];
    f32 v0[3];
    f32 cross[3];

    v1[0] = tri->x[2] - tri->x[0];
    v1[1] = tri->y[2] - tri->y[0];
    v1[2] = tri->z[2] - tri->z[0];
    v0[0] = tri->x[1] - tri->x[0];
    v0[1] = tri->y[1] - tri->y[0];
    v0[2] = tri->z[1] - tri->z[0];
    cross[0] = (v1[1] * v0[2]) - (v1[2] * v0[1]);
    cross[1] = (v1[2] * v0[0]) - (v1[0] * v0[2]);
    cross[2] = (v1[0] * v0[1]) - (v1[1] * v0[0]);
    collisionStoreSurfaceNormalAngles(actor, cross[0], cross[1], cross[2], tri->unk24, record, 1);
}

s32 collisionCheckTriangleWindingF32(CollisionTriF *tri) {
    f32 v1[3];
    f32 v0[3];
    f32 cross[1]; // ORIG: the target stores the cross product to its own stack word below v0 (swc1 $f4,4(sp) at 0x3910, never reloaded: cvt.d.s at 0x390c converts the register copy); a coloured scalar drops the store

    v1[0] = tri->x[2] - tri->x[0];
    v1[2] = tri->z[2] - tri->z[0];
    v0[0] = tri->x[1] - tri->x[0];
    v0[2] = tri->z[1] - tri->z[0];
    cross[0] = (v1[2] * v0[0]) - (v1[0] * v0[2]);
    if (cross[0] <= 0.0) {
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
    guMtxXFMF(invMtx, x, y, z, &actor->attachLocalX, &actor->attachLocalY, &actor->attachLocalZ);
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
        if (gModelSlots[slot].csState != NULL) {
            if (actor->hasArcBounds == 0) {
                actor->yaw += (gModelSlots[slot].csState->rotYDelta * 4095.0f) / 360.0f;
                if (actor->yaw >= 0x1000) {
                    actor->yaw -= 0x1000;
                }
                if (actor->yaw < 0) {
                    actor->yaw += 0xFFF;
                }
            }
            actor->attachLocalX += gModelSlots[slot].csState->riderDriftX;
            actor->attachLocalZ += gModelSlots[slot].csState->riderDriftZ;
        }
        guMtxXFMF(mtx, actor->attachLocalX, actor->attachLocalY, actor->attachLocalZ, &x, &y, &z);
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
    f64 hx;
    u32 outside;
    s32 i;

    outside = 0;
    hx = (tri->x[1] + tri->x[2]) * 0.5;
    b = (tri->z[1] + tri->z[2]) * 0.5; // FAKE: b reused for the z edge midpoint before its side-product role; a separate hz gives the same code but the frame holds only ten f64 locals (dx/dz/ox/oz homes fixed at sp+0xa0..0x88), so it grows 0xc8 -> 0xd0
    cx = (tri->x[0] + hx) * 0.5;
    cz = (tri->z[0] + b) * 0.5;
    for (i = 0; i < 3; i++) {
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
        if (((b <= a) ? 1 : -1) != ((c >= 0.0) ? 1 : -1)) {
            outside = 1;
        }
    }
    return outside == 0;
}

void assetEnsureTableLoaded();
extern s32 sAssetLoadPool;
extern u8 sAssetLoadPersistent;
extern u8 sAssetFreeImmediate;
extern s32 *sAssetCachedBuffers[];
extern s32 *sAssetInflatedSizes[];
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
    /* 0x56 */ u8 enabled; // 0 = ignored by floor tests (70FD0 ActorSub140Tri.enabled)
    /* 0x57 */ u8 pad57;
} CollisionBoxTri; // size = 0x58




s32 collisionTestActorBoxFloor(Actor *self, f32 x, f32 z, f32 refY, f32 *outFloorY) {
    f32 pad;
    CollisionBoxTri *hitTri;
    f64 nx, ny, nzPart;
    f64 d;
    f64 val;
    f64 dx01, dy01, dz01, dx02, dy02, dz02;
    f32 y;
    s32 hit;
    s32 i;
    s32 j;
    Actor *actor;
    CollisionBoxTri *tri;
    u16 pad2;
    f32 pad3[1];
    f32 hitY;
    f32 pad4[4];
    Actor *hitActor;
    f32 pad5[2];

    hit = 0;
    hitY = 999999.0f;
    for (i = 0; i < gActiveActorCount; i++) {
        actor = gActiveActors[i].actor;
        if (!(actor->flags & 0x2000)) {
            if (actor->collision != NULL && self != actor && (actor->flags & 0x10)) {
                tri = actor->collision->triangles;
                for (j = 0; j < actor->collision->triangleCount; j++, tri++) {
                    if ((collisionCheckBoxTriangleBoundsXZ(tri, x, z) != 0) &&
                        (collisionCheckBoxTriangleContainsPointXZ(tri, x, z) != 0) &&
                        (tri->enabled != 0)) {
                        dx01 = tri->x0 - tri->x1;
                        dy01 = tri->y0 - tri->y1;
                        dz01 = tri->z0 - tri->z1;
                        dx02 = tri->x0 - tri->x2;
                        dy02 = tri->y0 - tri->y2;
                        dz02 = tri->z0 - tri->z2;
                        nx = (dy01 * dz02) - (dz01 * dy02);
                        ny = (dz01 * dx02) - (dx01 * dz02);
                        nzPart = dx01 * dy02;
                        d = -((tri->z1 * (nzPart - (dy01 * dx02))) + (nx * tri->x1 + ny * tri->y1));
                        if (0.01 < ny * 2000.0 || ny * 2000.0 < -0.01) {
                            val = (0.0 - (((x * nx) + (ny * -1000.0) + ((nzPart - (dy01 * dx02)) * z) + d) / (ny * 2000.0)));
                            y = (2000.0 * val) - 1000.0;
                            if (self != NULL) {
                                collisionCheckSlopeAngle(refY, y, 0, self, 0);
                            }
                            if (sRecordCamFloorHits != 0) {
                                collisionRecordBoxTriangle(tri, y);
                            }
                            if (collisionCheckBoxTriangleWinding(tri) != 0) {
                                if (collisionPickCloserFloor(hitY, y, refY + 4.0, 0) != 0) {
                                    hitTri = tri;
                                    hitActor = actor;
                                    hit = 1;
                                    hitY = y;
                                }
                            }
                        }
                    }
                }
            }
        }
    }

    if (hit != 0 && collisionPickCloserFloor(*outFloorY, hitY, refY + 4.0, 0) != 0) {
        *outFloorY = hitY;
        collisionStoreBoxTriangleNormalAngles(self, hitTri, 1);
        if (hitActor->flags2 & 8) {
            D_807F94AD = 1;
        }
        if (self != NULL) {
            collisionTransformPointToActorLocal(self, hitActor, hitTri, x, hitY, z);
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
        sCamFloorHits[sCamFloorHitCount].angle = sLastNormalPitch;
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
    f32 xfMtx[4][4];
    f32 invMtx[4][4];
    ActorSub140 *sub;
    u8 idx;
    Mtx *mtx;

    D_807F9470 = target;
    sub = target->collision;
    if (gFrameCounter == sub->mtxFrame) {
        idx = gGfxBufferIndex;
    } else {
        idx = gGfxBufferIndex ^ 1;
    }
    mtx = sub->nodeMtx[idx];
    if ((tri->mtxOffset1 != tri->mtxOffset0) || (tri->mtxOffset2 != tri->mtxOffset0)) {
        D_807F94B2 = 1;
    }
    D_807F9480 = tri->mtxOffset0;
    if (tri->mtxOffset0 == -1) {
        memcpy(xfMtx, sub->modelMtxF, sizeof(xfMtx));
    } else {
        guMtxL2F(xfMtx, &mtx[tri->mtxOffset0 >> 6]);
    }
    matrix4Invert(invMtx, xfMtx);
    guMtxXFMF(invMtx, x, y, z, &D_807F9474, &D_807F9478, &D_807F947C);
}

void collisionTransformPointByActorMtx(Actor *actor, u32 mtxOffset, f32 *xInOut, f32 yIn, f32 *zInOut) {
    u8 idx;
    f32 xIn;
    f32 zIn;
    f32 yOut;
    ActorSub140 *sub;
    Mtx *mtx;
    f32 xfMtx[4][4];

    xIn = *xInOut;
    zIn = *zInOut;
    sub = actor->collision;
    if (gFrameCounter == sub->mtxFrame) {
        idx = gGfxBufferIndex;
    } else {
        idx = gGfxBufferIndex ^ 1;
    }
    mtx = sub->nodeMtx[idx];
    switch (mtxOffset) {
    case -1:
        memcpy(xfMtx, sub->modelMtxF, 0x40);
        break;
    default:
        guMtxL2F(xfMtx, &mtx[mtxOffset >> 6]);
        break;
    }
    guMtxXFMF(xfMtx, xIn, yIn, zIn, xInOut, &yOut, zInOut);
}

s32 collisionCheckBoxTriangleBoundsXZ(CollisionBoxTri *tri, f32 x, f32 z) {
    s32 pad;
    f32 minZ;
    f32 maxX;
    f32 x0;
    f32 x1;
    f32 minX;
    f32 x2;
    f32 z0;
    f32 z1;
    f32 z2;
    f32 maxZ;

    minX = ((x0 = tri->x0) < (x1 = tri->x1)) ? x0 : x1;
    x2 = tri->x2;
    minX = (minX < x2) ? minX : x2;

    z0 = tri->z0;
    z1 = tri->z1;
    minZ = (z0 < z1) ? z0 : z1;
    z2 = tri->z2;
    minZ = (minZ < z2) ? minZ : z2;

    maxX = (x1 < x0) ? x0 : x1;
    maxX = (x2 < maxX) ? maxX : x2;

    maxZ = (z1 < z0) ? z0 : z1;
    maxZ = (z2 < maxZ) ? maxZ : z2;

    if ((x < minX) || (maxX < x) || (z < minZ) || (maxZ < z)) {
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
    f64 hx;
    u32 outside;
    s32 i;

    outside = 0;
    hx = (tri->x2 + tri->x1) * 0.5;
    b = (tri->z2 + tri->z1) * 0.5; // FAKE: b reused for the z edge midpoint before its side-product role; a separate hz gives the same code but the frame holds only ten f64 locals (dx/dz/ox/oz homes fixed at sp+0xa0..0x88), so it grows 0xc8 -> 0xd0
    cx = (tri->x0 + hx) * 0.5;
    cz = (tri->z0 + b) * 0.5;
    for (i = 0; i < 3; i++) {
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
        if (((b <= a) ? 1 : -1) != ((c >= 0.0) ? 1 : -1)) {
            outside = 1;
        }
    }
    return outside == 0;
}

s32 collisionCheckBoxTriangleWinding(CollisionBoxTri *tri) {
    f32 v1[3];
    f32 v0[3];
    f32 cross[1]; // ORIG: the target stores the cross product to its own stack word below v0 (swc1 $f4,4(sp) at 0x4bf0, never reloaded: cvt.d.s at 0x4bec converts the register copy); a coloured scalar drops the store

    v1[0] = tri->x2 - tri->x0;
    v1[2] = tri->z2 - tri->z0;
    v0[0] = tri->x1 - tri->x0;
    v0[2] = tri->z1 - tri->z0;
    cross[0] = (v1[2] * v0[0]) - (v1[0] * v0[2]);
    if (cross[0] <= 0.0) {
        return 1;
    }
    return 0;
}

void collisionStoreBoxTriangleNormalAngles(Actor *actor, CollisionBoxTri *tri, u8 record) {
    f32 v1[3];
    f32 v0[3];
    f32 cross[3];

    v1[0] = tri->x2 - tri->x0;
    v1[1] = tri->y2 - tri->y0;
    v1[2] = tri->z2 - tri->z0;
    v0[0] = tri->x1 - tri->x0;
    v0[1] = tri->y1 - tri->y0;
    v0[2] = tri->z1 - tri->z0;
    cross[0] = (v1[1] * v0[2]) - (v1[2] * v0[1]);
    cross[1] = (v1[2] * v0[0]) - (v1[0] * v0[2]);
    cross[2] = (v1[0] * v0[1]) - (v1[1] * v0[0]);
    collisionStoreSurfaceNormalAngles(actor, cross[0], cross[1], cross[2], 1, record, 2);
}

extern s32 D_8000DDCC;
extern u32 *D_807F9520;
extern s32 *sAssetTableOffsets[];
extern void *sAssetRefBuckets[];
extern s32 sDmaQueueCount;
extern u8 sAssetFreeHistoryTail;
extern u8 sAssetFreeHistoryHead;

void collisionInitTables(void) {
    s32 i;
    u32 size;

    size = 0x80;
    D_807F9520 = heapAlloc(0x80);
    dmaReadAssetDecompress(D_8000DDCC, D_807F9520, &size, 0, 0, 0, 0);

    for (i = 0; i < 0x20; i++) {
        sAssetTableOffsets[i] = NULL;
        sAssetCachedBuffers[i] = NULL;
    }

    for (i = 0; i < 0x14; i++) {
        sAssetRefBuckets[i] = NULL;
    }

    sDmaQueueCount = 0;
    sAssetLoadPersistent = 0;
    sAssetLoadPool = 0;
    sAssetFreeImmediate = 0;

    for (i = 0; i < 0x20; i++) {
        if (sAssetTableCompressed[i] != 0) {
            sAssetInflatedSizes[i] = assetLoad(0x1A, i, 1, 1);
        } else {
            sAssetInflatedSizes[i] = NULL;
        }
    }

    sAssetFreeHistoryTail = 0;
    sAssetFreeHistoryHead = 0;
}

void assetInflateAndFree(void *compressed, void *out) {
    u8 *src;
    u8 *dst;

    src = compressed;
    dst = out;
    if (sInflateWindow == NULL) {
        sInflateWindow = heapAlloc(0x2400);
    }
    gunzip(&src, &dst, sInflateWindow);
    heapFree(compressed);
}

extern DmaQueueEntry sDmaQueue[];
extern s8 D_80746834;
extern OSMesgQueue D_807656D0;

void dmaDrainQueueAndFreeBuffer(void) {
    s32 i;

    for (i = 0; i < sDmaQueueCount; i++) {
        D_80746834 = 7;
        osRecvMesg(&D_807656D0, NULL, 1);
        D_80746834 = 0;
        if (sDmaQueue[i].compressed != 0) {
            assetInflateAndFree(sDmaQueue[i].dmaDst, sDmaQueue[i].buffer);
        }
    }
    if (sInflateWindow != NULL) {
        heapFree(sInflateWindow);
        sInflateWindow = NULL;
    }
    sDmaQueueCount = 0;
}

s32 assetGetSize(s32 table, s32 index) {
    s32 romAddr;
    u32 size;

    assetEnsureTableLoaded();
    assetResolveRomRange(table, index, &romAddr, &size);
    if (size == 0) {
        return 0;
    }
    return romAddr;
}

s32 assetGetCachedSizeOrResolve(s32 table, s32 index) {
    s32 romAddr;
    u32 size;

    if (sAssetTableCompressed[table] != 0) {
        size = sAssetInflatedSizes[table][index];
    } else {
        assetEnsureTableLoaded();
        assetResolveRomRange(table, index, &romAddr, &size);
    }
    return size;
}

void collisionResolveWallContact(void) {
    sAssetLoadPersistent = 1;
}

void assetSetRomTableOffset(s32 offset) {
    sAssetLoadPool = offset;
}

extern OSIoMesg D_807F9688[];

void *assetLoad(s32 table, s32 index, u8 sync, u8 noCache) { // index: asset index, or a K0 address (0x80000000-0x9FFFFFFF) returned as is
    s32 pad;
    s32 romAddr;
    u32 size;
    s32 allocSize;
    void *buffer;

    assetEnsureTableLoaded();
    if (noCache == 0) {
        if ((index >= 0x80000000U) && (index < 0xA0000000U)) {
            collisionBstInsertByHash((void *)index, table, 0);
            sAssetLoadPersistent = 0;
            sAssetLoadPool = 0;
            return (void *)index;
        }
        buffer = (void *)assetGetTableEntry(table, index);
        if (buffer != NULL) {
            collisionBstInsertByHash(buffer, table, index);
            sAssetLoadPersistent = 0;
            sAssetLoadPool = 0;
            return buffer;
        }
    }
    assetResolveRomRange(table, index, &romAddr, &size);
    if (size == 0) {
        sAssetLoadPersistent = 0;
        sAssetLoadPool = 0;
        return NULL;
    }
    if (sAssetTableCompressed[table] != 0) {
        allocSize = sAssetInflatedSizes[table][index];
    } else {
        allocSize = size;
    }
    if (sAssetLoadPool == 0) {
        buffer = heapAlloc(allocSize);
    } else {
        buffer = heapAllocFromPool(sAssetLoadPool, allocSize);
    }
    if (sync != 0) {
        if (sAssetTableCompressed[table] != 0) {
            void *compressed = heapAlloc(size);
            dmaReadAssetDecompress(romAddr, compressed, &size, 0, 0, 0, 0);
            assetInflateAndFree(compressed, buffer);
        } else {
            dmaReadAssetDecompress(romAddr, buffer, &size, 0, 0, 0, 0);
        }
    } else {
        if (sDmaQueueCount == 0xC0) {
            faultSetMessage(6, 0, 0, 0);
        }
        sDmaQueue[sDmaQueueCount].compressed = sAssetTableCompressed[table];
        if (sAssetTableCompressed[table] != 0) {
            sDmaQueue[sDmaQueueCount].dmaDst = heapAlloc(size);
            sDmaQueue[sDmaQueueCount].buffer = buffer;
        } else {
            sDmaQueue[sDmaQueueCount].buffer = buffer;
            sDmaQueue[sDmaQueueCount].dmaDst = buffer;
        }
        osInvalDCache(sDmaQueue[sDmaQueueCount].dmaDst, size);
        osPiStartDma(&D_807F9688[sDmaQueueCount], 0, 0, romAddr, sDmaQueue[sDmaQueueCount].dmaDst, size, &D_807656D0);
        sDmaQueueCount += 1;
    }
    assetSetTableEntry(table, index, (s32)buffer);
    collisionBstInsertByHash(buffer, table, index);
    sAssetLoadPersistent = 0;
    sAssetLoadPool = 0;
    return buffer;
}

void assetSetImmediateFree(void) {
    sAssetFreeImmediate = 1;
}

void assetFreeBuffer(void *buffer, s32 line, s32 fileId) {
    s32 table;
    s32 index;

    if (collisionBstLookupAndDecrementByHash(buffer) == 0) {
        collisionBstDeleteByHash(buffer, &table, &index);
        assetSetTableEntry(table, index, 0);
        if (sAssetFreeImmediate == 0) {
            heapFreeDeferred(buffer);
        } else {
            heapFree(buffer);
        }
    }
    sAssetFreeImmediate = 0;
}

void assetSetTableEntry(s32 table, s32 index, s32 value) {
    if (sAssetCachedBuffers[table] != NULL) {
        sAssetCachedBuffers[table][index] = value;
    }
}

s32 assetResolveRomRange(s32 tableId, s32 assetIndex, s32 *outRomAddr, u32 *outSize) {
    s32 pad[2];
    s32 target;
    s32 end;
    u64 header;
    s32 *table;
    s32 start;
    u32 size;
    s32 index;

    index = assetIndex;
    table = &sAssetTableOffsets[tableId][assetIndex];
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
    s32 *ptr = sAssetCachedBuffers[table];
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
    u32 headerSize;

    headerSize = 8;
    if (sAssetTableOffsets[tableIndex] != NULL) {
        return;
    }
    start = D_807F9520[tableIndex];
    dmaReadAssetDecompress(D_8000DDCC + start, &header, &headerSize, 0, 0, 0, 0);
    size = (u32)(header >> 32) - start;
    sAssetTableOffsets[tableIndex] = heapAlloc(size);
    dmaReadAssetDecompress(D_8000DDCC + start, sAssetTableOffsets[tableIndex], &size, 0, 0, 0, 0);
    switch (tableIndex) {
        case 4:
        case 7:
        case 14:
        case 25: {
            u32 i;
            sAssetCachedBuffers[tableIndex] = heapAlloc(size);
            for (i = 0; i < size / 4; i++) {
                sAssetCachedBuffers[tableIndex][i] = 0;
            }
            break;
        }
        default:
            sAssetCachedBuffers[tableIndex] = NULL;
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
    collisionBstLookupOrAssert(sAssetRefBuckets[collisionGetBucketIndex(key)], key, outTable, outIndex);
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

    sAssetRefBuckets[bucket] = collisionBstInsert(sAssetRefBuckets[bucket], (u32)buffer, table, index);
}

CollisionBstNode *collisionBstInsert(CollisionBstNode *node, u32 key, s32 table, s32 index) {
    if (node == NULL) {
        node = (CollisionBstNode *)heapAlloc(sizeof(CollisionBstNode));
        node->refCount = 1;
        node->key = key;
        node->table = table;
        node->index = index;
        node->persistent = sAssetLoadPersistent;
        node->right = NULL;
        node->left = NULL;
    } else if (key == node->key) {
        node->refCount++;
        if (sAssetLoadPersistent) {
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
    return collisionBstLookupAndDecrement(sAssetRefBuckets[collisionGetBucketIndex((u32)buffer)], (u32)buffer);
}

typedef struct CollisionQueueEntry {
    s32 frame;
    s32 key;
    u16 index;
    u8 table;
} CollisionQueueEntry;

extern CollisionQueueEntry sAssetFreeHistory[];

void collisionQueueSearch(s32 key, u8 *outTable, u16 *outIndex, s32 *outFrame) {
    s32 i;

    if ((i = sAssetFreeHistoryHead - 1) < 0) {
        i = 0x3F;
    }
    while (i != sAssetFreeHistoryTail) {
        if (key == sAssetFreeHistory[i].key) {
            *outTable = sAssetFreeHistory[i].table;
            *outIndex = sAssetFreeHistory[i].index;
            *outFrame = sAssetFreeHistory[i].frame;
            break;
        }
        if (--i < 0) {
            i = 0x3F;
        }
    }
}

void collisionQueueAppend(s32 key, u8 table, u16 index) {
    u8 idx = sAssetFreeHistoryHead;
    CollisionQueueEntry *item = &sAssetFreeHistory[idx];

    item->frame = gFrameCounter;
    item->key = key;
    item->table = table;
    item->index = index;
    sAssetFreeHistoryHead = idx + 1;

    if (sAssetFreeHistoryHead == 0x40) {
        sAssetFreeHistoryHead = 0;
    }

    if (sAssetFreeHistoryTail == sAssetFreeHistoryHead) {
        sAssetFreeHistoryTail++;
        if (sAssetFreeHistoryTail == 0x40) {
            sAssetFreeHistoryTail = 0;
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

    sAssetRefBuckets[bucket] = collisionBstDelete(sAssetRefBuckets[bucket], (u32)buffer, table, index);
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
    /* 0x00 */ u32 key;
    /* 0x04 */ s32 table;
    /* 0x08 */ s32 index;
    /* 0x0C */ s32 refCount;
    /* 0x10 */ u8 persistent;
} CollisionBstFlatItem;


void collisionBstRebalanceBucket(s32 bucket) {
    s32 count;
    CollisionBstFlatItem *buffer;
    CollisionBstNode *newRoot;
    s32 index;

    index = 0;
    count = collisionBstCountNodes(sAssetRefBuckets[bucket]);
    if (count != 0) {
        buffer = heapAlloc(count * sizeof(CollisionBstFlatItem));
        collisionBstFlatten(sAssetRefBuckets[bucket], buffer, &index);
        collisionBstSortFlatItems(buffer, 0, count - 1);
        newRoot = collisionBstBuildBalanced(buffer, 0, count - 1);
        collisionBstFreeTree(sAssetRefBuckets[bucket]);
        sAssetRefBuckets[bucket] = newRoot;
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

CollisionBstNode *collisionBstBuildBalanced(CollisionBstFlatItem *buffer, s32 start, s32 end) {
    CollisionBstNode *node;
    s32 mid;

    node = heapAlloc(sizeof(CollisionBstNode));
    mid = (start + end) / 2;

    node->key = buffer[mid].key;
    node->table = buffer[mid].table;
    node->index = buffer[mid].index;
    node->refCount = buffer[mid].refCount;
    node->persistent = buffer[mid].persistent;

    if (start != mid) {
        node->left = collisionBstBuildBalanced(buffer, start, mid - 1);
    } else {
        node->left = NULL;
    }

    if (end != mid) {
        node->right = collisionBstBuildBalanced(buffer, mid + 1, end);
    } else {
        node->right = NULL;
    }

    return node;
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
    u32 swapKey;
    s32 swapTable;
    s32 swapIndex;
    s32 swapRefCount;
    u8 swapPersistent;

    if (low < high) {
        pivot = arr[high].key;
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
            swapKey = arr[i].key;
            swapTable = arr[i].table;
            swapIndex = arr[i].index;
            swapRefCount = arr[i].refCount;
            swapPersistent = arr[i].persistent;
            arr[i].key = arr[j].key;
            arr[i].table = arr[j].table;
            arr[i].index = arr[j].index;
            arr[i].refCount = arr[j].refCount;
            arr[i].persistent = arr[j].persistent;
            arr[j].key = swapKey;
            arr[j].table = swapTable;
            arr[j].index = swapIndex;
            arr[j].refCount = swapRefCount;
            arr[j].persistent = swapPersistent;
        }

        swapKey = arr[i].key;
        swapTable = arr[i].table;
        swapIndex = arr[i].index;
        swapRefCount = arr[i].refCount;
        swapPersistent = arr[i].persistent;
        arr[i].key = arr[high].key;
        arr[i].table = arr[high].table;
        arr[i].index = arr[high].index;
        arr[i].refCount = arr[high].refCount;
        arr[i].persistent = arr[high].persistent;
        arr[high].key = swapKey;
        arr[high].table = swapTable;
        arr[high].index = swapIndex;
        arr[high].refCount = swapRefCount;
        arr[high].persistent = swapPersistent;

        collisionBstSortFlatItems(arr, low, i - 1);
        collisionBstSortFlatItems(arr, i + 1, high);
    }
}

u32 collisionGetBucketIndex(u32 key) {
    return (key >> 12) % 20;
}
