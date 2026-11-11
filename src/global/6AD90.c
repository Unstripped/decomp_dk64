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
    /* 0x12 */ s16 unk12;
    /* 0x14 */ u8 unk14;
    /* 0x15 */ u8 unk15;
    /* 0x16 */ u8 unk16;
    /* 0x17 */ s8 unk17;
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

void collisionSetQueryMode(u8 arg0) {
    D_807F94B4 = arg0;
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

void collisionCheckActorFloor(Actor *arg0, f32 arg1, f32 arg2, f32 arg3, f32 *arg4) {
    u8 slopeHit;
    u8 normalHit;
    f32 slopeY;
    f32 normalY;

    if (arg0->actorType == 0xBC) {
        D_807F94B3 = 1;
    } else {
        D_807F94B3 = 0;
    }
    D_807F94BC = 1;
    collisionFindFloorAtPoint(NULL, arg1, arg2, arg3, &slopeHit, &slopeY, &normalHit, &normalY, 0);
    *arg4 = D_807F948C;
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

s32 collisionFindFloorAtPoint(Actor *arg0, f32 arg1, f32 arg2, f32 arg3, u8 *arg4, f32 *arg5, u8 *arg6, f32 *arg7, u8 arg8) {
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
        *arg4 = 0;
        *arg6 = 0;
        D_807F94B4 = 0;
        return 0;
    }
    if (arg0 != NULL) {
        arg0->attachMode = 0;
        arg0->contactFlags &= 0xFBF1;
        arg0->cutsceneId = -1;
        D_807F94B6 = 0;
        D_807F9464 = 0;
        D_807F946C = 0;
        D_807F946D = arg8;
        arg0->renderFlags &= ~0x40;
        if (arg0->collisionFlags & 1) {
            D_807F94B8 = arg0->customState;
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
    meshY = arg2;
    meshHit = collisionTestSubmeshBoundary(arg1, arg3, &meshY, arg0);
    if ((meshHit != 0) && (arg0 != NULL)) {
        arg0->unkA8 = meshY;
        arg0->floorSurfaceType = D_807F949E[0];
    }
    if (D_807F94B4 != 2) {
        dynY = 99999.0f;
        dynHit = func_8062BCC8(arg0, arg1, arg3, arg2, (s32)&dynY);
        boxY = 99999.0f;
        boxHit = collisionTestActorBoxFloor(arg0, arg1, arg3, arg2, &boxY);
    } else {
        dynHit = 0;
        boxHit = 0;
    }
    threshold = (f32)((f64)arg2 + 4.0);
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
        if (arg0 != NULL) {
            arg0->floorSlopeType = D_807F949E[0];
            arg0->floorTiltPitch = D_807F9498[0];
            arg0->floorTiltYaw = D_807F9490[0];
            arg0->floorY = meshY;
            if ((D_807F94B6 != 0) && (arg0->prevContactFlags & 1)) {
                arg0->contactFlags |= 0x400;
            }
        }
        D_807F94A4 = D_807F9498[0];
        D_807F94A2 = D_807F9490[0];
        D_807F948C = meshY;
        D_807F94AA = D_807F94AB;
        D_807F951D = 1;
        break;
    case 2:
        if (arg0 != NULL) {
            arg0->floorSlopeType = D_807F949F;
            arg0->floorTiltPitch = D_807F949A;
            arg0->floorTiltYaw = D_807F9492;
            arg0->floorY = dynY;
            if (arg0->prevContactFlags & 1) {
                arg0->attachMode = 1;
            }
        }
        D_807F94A4 = D_807F949A;
        D_807F94A2 = D_807F9492;
        D_807F948C = dynY;
        D_807F94AA = D_807F94AC;
        D_807F951D = 2;
        break;
    case 3:
        if (arg0 != NULL) {
            arg0->floorSlopeType = D_807F94A0;
            arg0->floorTiltPitch = D_807F949C;
            arg0->floorTiltYaw = D_807F9494;
            arg0->floorY = boxY;
            if (arg0->prevContactFlags & 1) {
                actorAppendCallback10(arg0, D_807F9470, D_807F9474, D_807F9478, D_807F947C, D_807F9480, D_807F94B2);
                arg0->contactFlags |= 8;
            }
        }
        D_807F94A4 = D_807F949C;
        D_807F94A2 = D_807F9494;
        D_807F948C = boxY;
        D_807F94AA = D_807F94AD;
        D_807F951D = 3;
        break;
    }
    *arg4 = D_807F9464;
    *arg5 = D_807F9460;
    *arg6 = D_807F946C;
    *arg7 = D_807F9468;
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

void collisionStoreSurfaceNormalAngles(Actor *arg0, f32 arg1, f32 arg2, f32 arg3, u8 arg4, u8 arg5, u8 arg6) {
    f32 horiz;
    f32 absX;
    f32 absY;
    f32 absZ;
    f64 nx;
    s16 yaw;
    s16 pitch;
    u8 type;

    type = arg4;
    if (arg4 == 0xFF) {
        arg4 = 0;
        type = 0;
    }
    if (type == 0xFE) {
        arg4 = 0;
    }
    D_807F949E[arg6] = arg4;
    if (arg3 > 0.0f) {
        absZ = arg3;
    } else {
        absZ = -arg3;
    }
    if ((f64) absZ < 0.01) {
        yaw = 0x400;
    } else {
        if (arg1 > 0.0f) {
            absX = arg1;
        } else {
            absX = -arg1;
        }
        yaw = (s16)((mathAtan2(absX, absZ) / 3.1415927f) * 2048.0f);
    }
    nx = (f64) arg1;
    if ((nx >= 0.0) && ((f64) arg3 >= 0.0)) {
        yaw -= 0x800;
    } else if ((nx >= 0.0) && ((f64) arg3 < 0.0)) {
        yaw = -yaw;
    } else if ((nx < 0.0) && ((f64) arg3 >= 0.0)) {
        yaw = 0x800 - yaw;
    }
    if (arg5) {
        D_807F9490[arg6] = yaw & 0xFFF;
    }
    D_807F94A6 = yaw & 0xFFF;
    horiz = sqrtf((arg1 * arg1) + (arg3 * arg3));
    if ((f64) horiz < 0.01) {
        pitch = 0x400;
    } else {
        if (arg2 > 0.0f) {
            absY = arg2;
        } else {
            absY = -arg2;
        }
        pitch = (s16)((mathAtan2(absY, horiz) / 3.1415927f) * 2048.0f);
    }
    if (arg5) {
        D_807F9498[arg6] = pitch;
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

void collisionCheckSlopeAngle(f32 arg0, f32 arg1, u8 arg2, Actor *arg3, u8 arg4) {
    f32 *maxTable;
    f32 *minTable;
    f32 maxStep;
    f32 minStep;
    f32 minHeight;
    f32 maxHeight;
    f32 diff;
    u8 kong;

    if (arg0 < arg1) {
        if ((arg3 != NULL) && (arg3->collisionFlags & 1)) {
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
        if (arg4 != 0) {
            minHeight /= 2;
        }
        if (arg2 == 1) {
            minStep = minHeight * 6.0f;
        } else {
            minStep = minHeight;
        }
        diff = arg1 - arg0;
        if (minStep < diff) {
            if (arg2 == 1) {
                maxStep = maxHeight * 6.0f;
            } else {
                maxStep = maxHeight;
            }
            if (diff < maxStep) {
                D_807F9464 = 1;
                D_807F9460 = arg1 - maxStep;
                if (arg2) {
                    D_807F9460 /= 6.0f;
                }
            }
        }
    }
}

extern f32 D_807F9468;
extern u8 D_807F946C;

s32 collisionGetFloorTriangleNormal(f32 arg0, f32 arg1, u8 arg2, u8 arg3) {
    f32 limit;
    s32 hit;

    hit = 0;
    if (arg3 == 0xFF && arg0 < arg1) {
        limit = (arg2 == 1) ? 150.0 : 25.0;
        if ((arg1 - arg0) < limit) {
            D_807F946C = 1;
            hit = 1;
            D_807F9468 = arg1 - limit;
            if (arg2) {
                D_807F9468 /= 6.0f;
            }
            D_807F9468 = (f64)D_807F9468 + 6.0;
        }
    }
    return hit;
}

s32 mathCheckCloserFloatThreshold(f32 arg0, f32 arg1, f32 arg2, u8 arg3) {
    f32 limit;
    f32 diff0;
    f32 diff1;
    s32 cond0;
    s32 cond1;

    limit = (arg3 == 1) ? 60.0 : 10.0;

    if (arg0 <= arg2) {
        cond0 = 1;
    } else if ((arg0 - arg2) < limit) {
        cond0 = 1;
    } else {
        cond0 = 0;
    }

    if (arg1 <= arg2) {
        cond1 = 1;
    } else if ((arg1 - arg2) < limit) {
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

    if (arg2 < arg0) {
        diff0 = arg0 - arg2;
    } else {
        diff0 = arg2 - arg0;
    }

    if (arg2 < arg1) {
        diff1 = arg1 - arg2;
    } else {
        diff1 = arg2 - arg1;
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

u8 collisionCheckGroundAtPoint(f32 arg0, f32 arg1, f32 *arg2) {
    u8 ret;

    D_807F9484 = 0;
    sCamFloorHitCount = 0;
    ret = collisionTestSubmeshBoundary(arg0, arg1, arg2, NULL);
    D_807F94A4 = D_807F9498[0];
    D_807F94A2 = D_807F9490[0];
    return ret;
}

u8 collisionGetFloorHeight(f32 *arg0) {
    *arg0 = D_807F9488;
    return D_807F9484;
}

u8 collisionGetSurfaceType(void) {
    return D_807F94B5;
}

extern u8 D_807F94B6;

u8 collisionTestSubmeshBoundary(f32 arg0, f32 arg1, f32 *arg2, Actor *arg3) {
    u8 staticHit;
    f32 staticY;
    f32 gridY;
    f32 temp;
    u8 pad;
    u8 val;
    s32 hit;

    staticY = *arg2;
    staticHit = collisionTestStaticMeshFloor(arg0, arg1, &staticY, arg3);
    gridY = *arg2;
    val = collisionTestGridMeshHeight(arg0, arg1, &gridY, arg3) * 2;
    val += staticHit;
    switch (val) {
    case 0:
        break;
    case 1:
        *arg2 = staticY;
        break;
    case 2:
        *arg2 = gridY;
        D_807F94B6 = 1;
        break;
    case 3:
        temp = (f64)*arg2 + 4.0;
        if (mathCheckCloserFloatThreshold(staticY, gridY, temp, 0) != 0) {
            *arg2 = gridY;
            D_807F94B6 = 1;
        } else {
            *arg2 = staticY;
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

s32 collisionTestGridMeshHeight(f32 arg0, f32 arg1, f32 *arg2, Actor *arg3) {
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
    threshold = (f32)((f64)*arg2 + 4.0);
    if (node != NULL) {
        do {
            if (node->sub->minX <= arg0 && node->sub->minZ <= arg1 && arg0 <= node->sub->maxX && arg1 <= node->sub->maxZ) {
                floorY = arg0 * 6.0f;
                pz = arg1 * 6.0f;
                tableFlag = effectGetTableFlag(node);
                cell_x = (arg0 - node->sub->minX) / (f32)node->gridStep;
                cell_z = (arg1 - node->sub->minZ) / (f32)node->gridStep;

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
                    if (floorY && floorY) {}  // FAKE: deadsweep dead statement (keeps hit out of a register)
                    hit = 1;
                    if (node->sub->unk60 == 2 || node->sub->unk60 == 3) {
                        if ((floorY < *arg2 ? *arg2 - floorY : -(*arg2 - floorY)) < 6.0f) {
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
                    if (mathCheckCloserFloatThreshold(bestY, floorY, threshold, 0) != 0) {
                        bestY = floorY;
                    }
                    break;
                case 1:
                    if (arg3 != 0) {
                        if (arg3->y < floorY) {
                            arg3->contactFlags |= 4;
                            arg3->unkB0[0] = -1;
                            if (node->unk4A & 1) {
                                D_807F94B0 = 1;
                            }
                        }
                        arg3->waterY = floorY;
                        arg3->contactFlags |= 2;
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
        *arg2 = bestY;
    }
    return hit;
}

f32 collisionTriangleHeightAtXZ(CollisionStaticTri *arg0, f32 arg1, f32 arg2) {
    f64 dx01 = arg0->x[0] - arg0->x[1];
    f64 dy01 = arg0->y[0] - arg0->y[1];
    f64 dz01 = arg0->z[0] - arg0->z[1];
    f64 dx02 = arg0->x[0] - arg0->x[2];
    f64 dy02 = arg0->y[0] - arg0->y[2];
    f64 dz02 = arg0->z[0] - arg0->z[2];
    f64 nx = (dy01 * dz02) - (dz01 * dy02);
    f64 ny = (dz01 * dx02) - (dx01 * dz02);
    f64 nz = (dx01 * dy02) - (dy01 * dx02);
    f64 d = -((nx * arg0->x[1]) + (ny * arg0->y[1]) + (nz * arg0->z[1]));
    f64 val = ((nx * arg1) + (ny * -1000.0) + (nz * arg2) + d) / (ny * 2000.0);
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

u8 collisionTestStaticMeshFloor(f32 arg0, f32 arg1, f32 *arg2, Actor *arg3) {
    s32 padTop;
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
    cell = ((s32)arg1 / D_807F9452) * D_807F9454 + (s32)arg0 / D_807F9450;
    cur = *arg2;
    threshold = (f32)((f64)*arg2 + 4.0);
    threshold = threshold * 6.0f;
    if (cell >= D_807F9518) {
        return 0;
    }
    if (D_807F9454 <= arg0 / D_807F9450 || arg0 < 0.0) {
        if (gCurrentMap == 0x57 && arg3 != NULL) {
            return collisionTestHardcodedFloorPlane(&spS.cc, threshold, cur, arg2);
        }
        return 0;
    }
    if (D_807F9456 <= arg1 / D_807F9452 || arg1 < 0.0) {
        if (gCurrentMap == 0x57 && arg3 != NULL) {
            return collisionTestHardcodedFloorPlane(&spS.cc, threshold, cur, arg2);
        }
        return 0;
    }
    dynamicBufferAllocateEntry(cell);
    arg0 = arg0 * 6.0f;
    arg1 = arg1 * 6.0f;
    if (arg3 != NULL && arg3->floorTriangle != NULL && collisionCheckTriangleXZBoundsS16(arg3->floorTriangle, (s32)arg0, (s32)arg1) != 0 &&
        collisionPointInTriangleXZS16(arg3->floorTriangle, arg0, arg1) != 0 && D_807F5FC0 == 0) {
        tri = arg3->floorTriangle;
        triEnd = tri + 1;
    } else {
        tri = D_807F9514[cell].tris;
        triEnd = D_807F9514[cell].trisEnd;
    }
    if (tri != triEnd) {
        iz = (s32)arg1;
        ix = (s32)arg0;
        do {
            if (collisionCheckTriangleXZBoundsS16(tri, ix, iz) != 0 && collisionPointInTriangleXZS16(tri, arg0, arg1) != 0) {
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
                    val = 0.0 - ((((arg0 * nx) + (ny * -1000.0)) + (((dx01 * dy02) - (dy01 * dx02)) * arg1) + d) / (ny * 2000.0));
                    h2 = (2000.0 * val) - 1000.0;
                    if (tri->unk12 & 4) {
                        h2 = (f64)(mapOffsetSlotGetValue(tri->unk17) * 6.0f); // FAKE: assigning M first fixes add.d operand order
                        h2 = ((2000.0 * (0.0 - ((((arg0 * nx) + (ny * -1000.0)) + (((dx01 * dy02) - (dy01 * dx02)) * arg1) + d) / (ny * 2000.0)))) - 1000.0) + h2;
                    }
                    if ((tri->unk12 & 0x4000) && arg3 != NULL && (arg3->collisionFlags & 1)) {
                        D_807F94B7 = 1;
                    }
                    if ((tri->unk12 & 0x80) && (f64)(*arg2 * 6.0f) < h2) {
                        D_807F94B0 = 1;
                    }
                    if ((tri->unk12 & 0x100) && arg3 != NULL && (arg3->collisionFlags & 1)) {
                        if ((f64)(*arg2 * 6.0f) < h2 && ((diff = h2 - (f64)(*arg2 * 6.0f)) < 600.0f)) {
                            D_807F94B8->stateFlags |= 0x2000;
                        }
                    }
                    if ((tri->unk12 & 0xA00) && arg3 != NULL && (arg3->collisionFlags & 1)) {
                        if ((f64)(*arg2 * 6.0f) < h2 && ((diff = h2 - (f64)(*arg2 * 6.0f)) < 800.0f)) {
                            D_807F94B8->stateFlags |= 0x4000;
                        }
                    }
                    if (tri->unk12 & 0x4850) {
                        if (arg3 != NULL) {
                            if (h2 < (f64)(*arg2 * 6.0f)) {
                                diff = (f64)(*arg2 * 6.0f) - h2;
                            } else {
                                diff = -((f64)(*arg2 * 6.0f) - h2);
                            }
                            if ((tri->unk12 & 0x10) && diff < 40.0f) {
                                D_807F94AE = 1;
                            }
                            if ((tri->unk12 & 0x40) && diff < 40.0f) {
                                D_807F94AF = 1;
                            }
                        }
                    } else {
                        if (D_807F94BC != 0) {
                            collisionRecordTriangleS(tri, (f32)h2);
                        }
                        if (!(tri->unk12 & 1)) {
                            collisionCheckSlopeAngle(*arg2 * 6.0f, (f32)h2, 1, arg3, 0);
                            collisionGetFloorTriangleNormal(*arg2 * 6.0f, (f32)h2, 1, tri->unk14);
                            closer = mathCheckCloserFloatThreshold(spS.cc, (f32)h2, threshold, 1);
                            if (collisionCheckTriangleWindingS16(tri) != 0 && closer != 0) {
                                spS.cb = 1;
                                spS.cc = (f32)h2;
                                hitTri = tri;
                                D_807F94B5 = tri->unk16 & 0xF;
                                if (h2 < (f64)(*arg2 * 6.0f)) {
                                    diff = (f64)(*arg2 * 6.0f) - h2;
                                } else {
                                    diff = -((f64)(*arg2 * 6.0f) - h2);
                                }
                                if (diff > 30.0f) {
                                    t = (diff - 30.0f) / 120.0f;
                                    if ((f64)t > 1.0) {
                                        D_807F94B5 = 0xF;
                                    } else {
                                        D_807F94B5 = (u32)((f32)D_807F94B5 + (f32)(0xF - D_807F94B5) * t);
                                    }
                                }
                                collisionStoreTriangleNormalAnglesS16(arg3, tri, 1);
                                if (arg3 != NULL) {
                                    arg3->unk78[0] = tri->unk15;
                                    arg3->tintA = D_807F94B5;
                                }
                                D_807F94B1 = tri->unk15;
                                if (tri->unk12 & 2) {
                                    *arg2 = spS.cc / 6.0f;
                                    if (!(tri->unk12 & 8)) {
                                        D_807F94AB = 1;
                                    }
                                    if (tri->unk12 & 0x2000) {
                                        D_807F946E = 1;
                                    }
                                    if (arg3 != NULL && (tri->unk12 & 0x1000)) {
                                        arg3->renderFlags |= 0x40;
                                    }
                                    if (arg3 != NULL) {
                                        arg3->floorTriangle = tri;
                                    }
                                    return 1;
                                }
                            }
                        } else {
                            if (arg3 != NULL) {
                                if ((f64)(arg3->y * 6.0f) < h2) {
                                    arg3->contactFlags |= 4;
                                    arg3->unkB0[0] = tri->unk16 >> 4;
                                    if (arg3->unkB0[0] == 0xF) {
                                        arg3->unkB0[0] = -1;
                                    }
                                }
                                arg3->contactFlags |= 2;
                                arg3->waterY = h2 / 6.0;
                            }
                            if (tri->unk12 & 0x20) {
                                collisionCheckSlopeAngle(*arg2 * 6.0f, (f32)h2, 1, arg3, 1);
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
        *arg2 = spS.cc / 6.0f;
        if (!(hitTri->unk12 & 8)) {
            D_807F94AB = 1;
        }
        if (hitTri->unk12 & 0x2000) {
            D_807F946E = 1;
        }
        if (arg3 != NULL && (hitTri->unk12 & 0x1000)) {
            arg3->renderFlags |= 0x40;
        }
    }
    if (gCurrentMap == 0x57 && arg3 != NULL) {
        spS.cb |= collisionTestHardcodedFloorPlane(&spS.cc, threshold, cur, arg2);
    }
    if (arg3 != NULL) {
        arg3->floorTriangle = NULL;
    }
    return spS.cb;
}


u8 collisionTestHardcodedFloorPlane(f32 *arg0, f32 arg1, f32 arg2, f32 *arg3) {
    f32 diff;
    f64 val;

    val = (f64)(arg2 * 6.0f);
    if (val > 1614.0) {
        diff = val - 1614.0;
    } else {
        diff = -(val - 1614.0);
    }
    if (diff < 40.0f) {
        D_807F94AE = 1;
    }
    if (mathCheckCloserFloatThreshold(*arg0, 684.0f, arg1, 1)) {
        *arg3 = 114.0f;
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

void collisionRecordTriangleS(CollisionStaticTri *arg0, f32 arg1) {
    if (sCamFloorHitCount != 10) {
        sCamFloorHits[sCamFloorHitCount].height = arg1 / 6.0f;
        if (collisionCheckTriangleWindingS16(arg0)) {
            sCamFloorHits[sCamFloorHitCount].flags = 1;
        } else {
            sCamFloorHits[sCamFloorHitCount].flags = 2;
        }
        if (arg0->unk12 & 1) {
            sCamFloorHits[sCamFloorHitCount].flags |= 4;
        }
        if (arg0->unk12 & 0x400) {
            sCamFloorHits[sCamFloorHitCount].flags |= 8;
        }
        collisionStoreTriangleNormalAnglesS16(NULL, arg0, 0);
        sCamFloorHits[sCamFloorHitCount].angle = D_807F94A8;
        sCamFloorHitCount++;
    }
}
extern s32 gFrameCounter;
extern u8 D_807F951C;

void dynamicBufferAllocateEntry(s32 arg0) {
    u32 size;

    if (D_807F9514[arg0].tris == NULL) {
        size = D_807F9514[arg0].size;
        if (size != 0) {
            D_807F9514[arg0].tris = heapAlloc(size);
            D_807F9514[arg0].trisEnd = D_807F9514[arg0].tris + size / sizeof(CollisionStaticTri);
            dmaReadAssetDecompress(D_807F9514[arg0].romAddr, D_807F9514[arg0].tris, &size, 0, 0, 0, 0);
        }
    }
    D_807F9514[arg0].lastUsedFrame = gFrameCounter;
}

void dynamicBufferPurgeExpired(void) {
    s32 i;

    if (!D_807F951C) {
        for (i = 0; i < D_807F9518; i++) {
            if (D_807F9514[i].tris != NULL && (u32)(gFrameCounter - D_807F9514[i].lastUsedFrame) >= 21) {
                actorClearBufferReferences(i);
                heapFree(D_807F9514[i].tris);
                D_807F9514[i].tris = NULL;
                D_807F9514[i].trisEnd = NULL;
            }
        }
    }
}
extern ActorEntry gActiveActors[];
extern u16 gActiveActorCount;

void actorClearBufferReferences(s32 arg0) {
    s32 i;
    CollisionStaticTri *min = D_807F9514[arg0].tris;
    CollisionStaticTri *max = D_807F9514[arg0].trisEnd;

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

s32 collisionCheckTriangleWindingS16(CollisionStaticTri *arg0) {
    CrossProductStack sp;

    sp.v1[0] = arg0->x[2] - arg0->x[0];
    sp.v1[2] = arg0->z[2] - arg0->z[0];
    sp.v0[0] = arg0->x[1] - arg0->x[0];
    sp.v0[2] = arg0->z[1] - arg0->z[0];
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

void collisionStoreTriangleNormalAnglesS16(Actor *arg0, CollisionStaticTri *arg1, u8 arg2) {
    CrossProductStack3D sp;

    sp.v1[0] = arg1->x[2] - arg1->x[0];
    sp.v1[1] = arg1->y[2] - arg1->y[0];
    sp.v1[2] = arg1->z[2] - arg1->z[0];
    sp.v0[0] = arg1->x[1] - arg1->x[0];
    sp.v0[1] = arg1->y[1] - arg1->y[0];
    sp.v0[2] = arg1->z[1] - arg1->z[0];
    sp.cross[0] = (sp.v1[1] * sp.v0[2]) - (sp.v1[2] * sp.v0[1]);
    sp.cross[1] = (sp.v1[2] * sp.v0[0]) - (sp.v1[0] * sp.v0[2]);
    sp.cross[2] = (sp.v1[0] * sp.v0[1]) - (sp.v1[1] * sp.v0[0]);
    collisionStoreSurfaceNormalAngles(arg0, sp.cross[0], sp.cross[1], sp.cross[2], arg1->unk14, arg2, 0);
}

s32 collisionCheckTriangleXZBoundsS16(CollisionStaticTri *arg0, s32 arg1, s32 arg2) {
    s32 p0, p1, p2;
    s32 val;

    p0 = arg0->x[0];
    p1 = arg0->x[1];
    p2 = arg0->x[2];

    val = (p0 < p1) ? p0 : p1;
    if (val >= p2) {
        val = p2;
    }
    if (arg1 < val) {
        return 0;
    }

    val = (p1 < p0) ? p0 : p1;
    if (val <= p2) {
        val = p2;
    }
    if (val < arg1) {
        return 0;
    }

    p0 = arg0->z[0];
    p1 = arg0->z[1];
    p2 = arg0->z[2];

    val = (p0 < p1) ? p0 : p1;
    if (val >= p2) {
        val = p2;
    }
    if (arg2 < val) {
        return 0;
    }

    val = (p1 < p0) ? p0 : p1;
    if (val <= p2) {
        val = p2;
    }
    if (val < arg2) {
        return 0;
    }

    return 1;
}

s32 collisionPointInTriangleXZS16(CollisionStaticTri *arg0, f32 arg1, f32 arg2) {
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

    hx = (f64)(arg0->x[1] + arg0->x[2]) * 0.5;
    hz = (f64)(arg0->z[1] + arg0->z[2]) * 0.5;
    mid_x = ((f64)arg0->x[0] + hx) * 0.5;
    z0 = arg0->z[0];
    mid_z = (z0 + hz) * 0.5;

    for (i = 0; i < 3; i++) {
        switch (i) {
        case 0:
            ex = (f64)(arg0->x[1] - arg0->x[0]);
            ez = (f64)(arg0->z[1] - arg0->z[0]);
            ox = (f64)arg0->x[0];
            oz = z0;
            break;
        case 1:
            ex = (f64)(arg0->x[2] - arg0->x[0]);
            ez = (f64)(arg0->z[2] - arg0->z[0]);
            ox = (f64)arg0->x[0];
            oz = z0;
            break;
        case 2:
            ex = (f64)(arg0->x[2] - arg0->x[1]);
            ez = (f64)(arg0->z[2] - arg0->z[1]);
            ox = (f64)arg0->x[1];
            oz = (f64)arg0->z[1];
            break;
        }

        sidePt = ((f64)arg1 - ox) * ez;
        sideRef = ((f64)arg2 - oz) * ex;
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

u8 collisionTestDynamicActorFloor(Actor *arg0, s32 arg1, f32 arg2, f32 arg3, f32 arg4, f32 *arg5) {
    s32 pad;
    CollisionTriF *tri_end;
    CollisionTriF *hit_tri;
    CollisionTriF *tri;
    f64 nx, ny, nz_product;
    f64 d;
    f64 val;
    f64 dx01, dy01, dz01, dx02, dy02, dz02;
    f32 y;
    CsStateFull *sub7C;
    f32 padB[6];
    f32 hit_y;
    u8 hit;
    s32 pad9C;
    s16 slotIdx;
    s32 pad94;
    ModelTriBuffer *buf;

    hit = 0;
    hit_y = 999999.0f;

    slotIdx = hashTableLookup(arg1);
    if (slotIdx == -1) {
        return 0;
    }

    buf = &gModelSlots[slotIdx].unk48;
    if (arg0 != NULL && gModelSlots[slotIdx].unk70 != NULL && D_807F946D != 0) {
        actorCheckNearbyNodeInteractions(arg0, slotIdx, gModelSlots[slotIdx].unk70);
    }

    if (!(buf->flags & 4)) {
        return 0;
    }

    if (collisionCheckBoundingBoxXZ(&buf->bbox, arg2, arg3) == 0) {
        return 0;
    }

    if (D_807F94B3 != 0 && !(buf->flags & 2)) {
        return 0;
    }

    if (arg0 != NULL && (arg0->collisionFlags & 1)) {
        if (playerSlotMatchesSizeMask(gModelSlots[slotIdx].unk24->unk0, ((PlayerState *)arg0->customState)->playerIndex) != 0) {
            return 0;
        }
    }

    sub7C = gModelSlots[slotIdx].unk7C;
    if (sub7C != NULL && sub7C->unk71 == 0) {
        return 0;
    }

    if (!(buf->flags & 1)) {
        modelSlotBuildTriangleBufferThunk(slotIdx, gModelSlots[slotIdx].unk24,
            gModelSlots[slotIdx].unk0, gModelSlots[slotIdx].unk4, gModelSlots[slotIdx].unk8,
            gModelSlots[slotIdx].unk10, gModelSlots[slotIdx].unk14, gModelSlots[slotIdx].unk18,
            gModelSlots[slotIdx].unkC);
    } else {
        buf->timestamp = gFrameCounter;
    }

    tri = buf->tri_start;
    tri_end = buf->tri_end;
    if (tri != tri_end) {
        do {
            if (collisionCheckTriangleBoundingBoxXZ(tri, arg2, arg3) != 0 &&
                collisionCheckTriangleContainsPointXZ(tri, arg2, arg3) != 0 &&
                collisionCheckSurfaceFilter(tri->unk27, buf->unk25) != 0) {
                dx01 = tri->x[0] - tri->x[1];
                dy01 = tri->y[0] - tri->y[1];
                dz01 = tri->z[0] - tri->z[1];
                dx02 = tri->x[0] - tri->x[2];
                dy02 = tri->y[0] - tri->y[2];
                dz02 = tri->z[0] - tri->z[2];
                nx = (dy01 * dz02) - (dz01 * dy02);
                ny = (dz01 * dx02) - (dx01 * dz02);
                nz_product = dx01 * dy02;
                d = -((nx * tri->x[1]) + (ny * tri->y[1]) + ((nz_product - (dy01 * dx02)) * tri->z[1]));
                if (0.01 < ny * 2000.0 || ny * 2000.0 < -0.01) {
                    if (arg0 != NULL) {
                        val = 0.0 - (((arg2 * nx) + (ny * -1000.0) + ((nz_product - (dy01 * dx02)) * arg3) + d) / (ny * 2000.0));
                        y = (2000.0 * val) - 1000.0;
                        collisionCheckSlopeAngle(arg4, y, 0, arg0, 0);
                        if (collisionGetFloorTriangleNormal(arg4, y, 0, tri->unk24) != 0 && D_807F946D != 0) {
                            collisionAttachActorToObjectNode(arg0, slotIdx, -1, 0, arg2, y, arg3);
                            arg0->attachMode = 2;
                        }
                    }
                    if (D_807F94BC != 0) {
                        val = 0.0 - (((arg2 * nx) + (ny * -1000.0) + ((nz_product - (dy01 * dx02)) * arg3) + d) / (ny * 2000.0));
                        collisionRecordTriangleF(tri, (2000.0 * val) - 1000.0);
                    }
                    if (collisionCheckTriangleWindingF32(tri) != 0) {
                        val = 0.0 - (((arg2 * nx) + (ny * -1000.0) + ((nz_product - (dy01 * dx02)) * arg3) + d) / (ny * 2000.0));
                        y = (2000.0 * val) - 1000.0;
                        if (mathCheckCloserFloatThreshold(hit_y, y, arg4 + 4.0, 0) != 0) {
                            hit_tri = tri;
                            hit = 1;
                            hit_y = y;
                        }
                    }
                }
            }
            tri++;
        } while (tri != tri_end);
    }

    if (hit != 0 && mathCheckCloserFloatThreshold(*arg5, hit_y, (f32)((f64)arg4 + 4.0), 0) != 0) {
        *arg5 = hit_y;
        collisionStoreTriangleNormalAnglesF32(arg0, hit_tri, 1);
        sub7C = gModelSlots[slotIdx].unk7C;
        if (sub7C != NULL && sub7C->unk4F != 0) {
            D_807F94AC = 1;
        }
        if (arg0 != NULL) {
            if (arg0->attachMode != 2 && arg0->attachMode != 3) {
                collisionAttachActorToObjectNode(arg0, slotIdx, hit_tri->unk26, hit_tri->unk27, arg2, hit_y, arg3);
            }
            arg0->unk78[0] = hit_tri->unk25;
        }
        D_807F94B1 = hit_tri->unk25;
    }
    return hit;
}


void collisionRecordTriangleF(CollisionTriF *arg0, f32 arg1) {
    if (sCamFloorHitCount != 10) {
        sCamFloorHits[sCamFloorHitCount].height = arg1;
        if (collisionCheckTriangleWindingF32(arg0)) {
            sCamFloorHits[sCamFloorHitCount].flags = 1;
        } else {
            sCamFloorHits[sCamFloorHitCount].flags = 2;
        }
        collisionStoreTriangleNormalAnglesF32(NULL, arg0, 0);
        sCamFloorHits[sCamFloorHitCount].angle = D_807F94A8;
        sCamFloorHitCount++;
    }
}

s32 collisionCheckSurfaceFilter(u8 arg0, u8 *arg1) {
    u8 i = 0;

    do {
        if (arg1[i] != 0xFF && arg1[i] == arg0) {
            return 0;
        }
        i++;
    } while (i < 2);
    return 1;
}


void actorCheckNearbyNodeInteractions(Actor *arg0, s16 arg1, ModelPosNode *arg2) {
    u8 count = 0;

    if (arg2 != NULL) {
        do {
            f32 dx = arg2->x - arg0->x;
            f32 dz = arg2->z - arg0->z;
            f32 dist;
            f32 dy;

            dx = dx * dx;
            dz = dz * dz;
            dist = sqrtf(dx + dz);
            dy = arg2->y - arg0->y;
            if (dist < 5.0) {
                if (dy > 0.0f) {
                    if (dy < 25.0) {
                        collisionAttachActorToObjectNode(arg0, arg1, -1, 0, arg2->x, arg2->y, arg2->z);
                        arg0->attachMode = 3;
                        arg0->unk12F = count;
                        D_807F946C = 1;
                        D_807F9468 = arg2->y - 10.0f;
                    }
                }
            }
            arg2 = arg2->next;
            count++;
        } while (arg2 != NULL);
    }
}

void collisionStoreTriangleNormalAnglesF32(Actor *arg0, CollisionTriF *arg1, u8 arg2) {
    CrossProductStack3D sp;

    sp.v1[0] = arg1->x[2] - arg1->x[0];
    sp.v1[1] = arg1->y[2] - arg1->y[0];
    sp.v1[2] = arg1->z[2] - arg1->z[0];
    sp.v0[0] = arg1->x[1] - arg1->x[0];
    sp.v0[1] = arg1->y[1] - arg1->y[0];
    sp.v0[2] = arg1->z[1] - arg1->z[0];
    sp.cross[0] = (sp.v1[1] * sp.v0[2]) - (sp.v1[2] * sp.v0[1]);
    sp.cross[1] = (sp.v1[2] * sp.v0[0]) - (sp.v1[0] * sp.v0[2]);
    sp.cross[2] = (sp.v1[0] * sp.v0[1]) - (sp.v1[1] * sp.v0[0]);
    collisionStoreSurfaceNormalAngles(arg0, sp.cross[0], sp.cross[1], sp.cross[2], arg1->unk24, arg2, 1);
}

s32 collisionCheckTriangleWindingF32(CollisionTriF *arg0) {
    CrossProductStack sp;

    sp.v1[0] = arg0->x[2] - arg0->x[0];
    sp.v1[2] = arg0->z[2] - arg0->z[0];
    sp.v0[0] = arg0->x[1] - arg0->x[0];
    sp.v0[2] = arg0->z[1] - arg0->z[0];
    sp.cross = (sp.v1[2] * sp.v0[0]) - (sp.v1[0] * sp.v0[2]);
    if (sp.cross <= 0.0) {
        return 1;
    }
    return 0;
}


void collisionAttachActorToObjectNode(Actor *arg0, s16 arg1, s8 arg2, u8 arg3, f32 arg4, f32 arg5, f32 arg6) {
    f32 pad2[10];
    float mtx[4][4];
    float pad[4][4];
    float invMtx[4][4];

    arg0->cutsceneId = gModelSlots[arg1].unk88;
    arg0->unk10E = arg3;
    arg0->unk10F = arg2;
    modelSlotBuildTransformMatrix(arg1, arg2, mtx);
    matrix4Invert(invMtx, mtx);
    guMtxXFMF(invMtx, arg4, arg5, arg6, &arg0->unk100, &arg0->unk104, &arg0->unk108);
}

void actorUpdateSubnodeRotationAndMtx(Actor *arg0) {
    f32 pad[10];
    float mtx[4][4];
    float padMtx[4][4];
    f32 x;
    f32 y;
    f32 z;
    s16 slot;
    s16 pad40;

    slot = hashTableLookup(arg0->cutsceneId);
    if (slot != -1) {
        modelSlotBuildTransformMatrix(slot, arg0->unk10F, mtx);
        if (gModelSlots[slot].unk7C != NULL) {
            if (arg0->hasArcBounds == 0) {
                arg0->yaw += (gModelSlots[slot].unk7C->unk34 * 4095.0f) / 360.0f;
                if (arg0->yaw >= 0x1000) {
                    arg0->yaw -= 0x1000;
                }
                if (arg0->yaw < 0) {
                    arg0->yaw += 0xFFF;
                }
            }
            arg0->unk100 += gModelSlots[slot].unk7C->unk8;
            arg0->unk108 += gModelSlots[slot].unk7C->unkC;
        }
        guMtxXFMF(mtx, arg0->unk100, arg0->unk104, arg0->unk108, &x, &y, &z);
        arg0->unk94 = x;
        arg0->unk98 = z;
        if (arg0->hasArcBounds == 0) {
            arg0->x = x;
            arg0->z = z;
        }
    }
}

s32 collisionCheckBoundingBoxXZ(CollisionBoundingBox *arg0, f32 arg1, f32 arg2) {
    if (arg1 < arg0->minX) {
        return 0;
    }
    if (arg2 < arg0->minZ) {
        return 0;
    }
    if (arg0->maxX < arg1) {
        return 0;
    }
    if (arg0->maxZ < arg2) {
        return 0;
    }
    return 1;
}

s32 collisionCheckBoundingBoxY(CollisionBoundingBox *arg0, f32 arg1) {
    if (arg1 < arg0->minY) {
        return 0;
    }
    if (arg0->maxY < arg1) {
        return 0;
    }
    return 1;
}

s32 collisionCheckTriangleBoundingBoxXZ(CollisionTriF *arg0, f32 arg1, f32 arg2) {
    f32 x0, x1, x2;
    f32 z0, z1, z2;
    f32 min;
    f32 max;

    x0 = arg0->x[0];
    x1 = arg0->x[1];
    x2 = arg0->x[2];

    min = (x0 < x1) ? x0 : x1;
    if (!(min < x2)) {
        min = x2;
    }
    if (arg1 < min) {
        return 0;
    }
    max = (x1 < x0) ? x0 : x1;
    if (!(x2 < max)) {
        max = x2;
    }
    if (max < arg1) {
        return 0;
    }

    z0 = arg0->z[0];
    z1 = arg0->z[1];
    z2 = arg0->z[2];

    min = (z0 < z1) ? z0 : z1;
    if (!(min < z2)) {
        min = z2;
    }
    if (arg2 < min) {
        return 0;
    }
    max = (z1 < z0) ? z0 : z1;
    if (!(z2 < max)) {
        max = z2;
    }
    if (max < arg2) {
        return 0;
    }
    return 1;
}

u8 collisionCheckTriangleContainsPointXZ(CollisionTriF *arg0, f32 arg1, f32 arg2) {
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
    a = (f64)(arg0->x[1] + arg0->x[2]) * 0.5;
    b = (f64)(arg0->z[1] + arg0->z[2]) * 0.5;
    cx = (arg0->x[0] + a) * 0.5;
    cz = (arg0->z[0] + b) * 0.5;
    i = 0; sideC = 0; do { // LAYOUT: i = 0 joined to the loop head (move v0,zero lands after the hoisted ldc1s); FAKE: dead init sideC = 0 gives sideC an earlier first appearance than sideP (uopt colours ties in first-appearance order: sideC a0, sideP a1)
        switch (i) {
        case 0:
            dx = arg0->x[1] - arg0->x[0];
            dz = arg0->z[1] - arg0->z[0];
            ox = arg0->x[0];
            oz = arg0->z[0];
            break;
        case 1:
            dx = arg0->x[2] - arg0->x[0];
            dz = arg0->z[2] - arg0->z[0];
            ox = arg0->x[0];
            oz = arg0->z[0];
            break;
        case 2:
            dx = arg0->x[2] - arg0->x[1];
            dz = arg0->z[2] - arg0->z[1];
            ox = arg0->x[1];
            oz = arg0->z[1];
            break;
        }
        a = (arg1 - ox) * dz;
        b = (arg2 - oz) * dx;
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
    void *unk0;
    void *unk4;
    u8 unk8;
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
    /* 0x48 */ u32 unk48; // per-vertex matrix byte offsets (0x40 per Mtx), -1 = box bounds
    /* 0x4C */ u32 unk4C;
    /* 0x50 */ u32 unk50;
    /* 0x54 */ u8 pad54[2];
    /* 0x56 */ u8 unk56;
    /* 0x57 */ u8 pad57;
} CollisionBoxTri; // size = 0x58




s32 collisionTestActorBoxFloor(Actor *arg0, f32 arg1, f32 arg2, f32 arg3, f32 *arg4) {
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
                if (actor->collision != NULL && arg0 != actor && (actor->flags & 0x10)) {
                    tri = actor->collision->triangles;
                    j = 0;
                    if (actor->collision->triangleCount > 0) {
                        do {
                            if ((collisionCheckBoxTriangleBoundsXZ(tri, arg1, arg2) != 0) &&
                                (collisionCheckBoxTriangleContainsPointXZ(tri, arg1, arg2) != 0) &&
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
                                    if (arg0 != NULL) {
                                        val = (0.0 - ((((f64)arg1 * nx) + (ny * -1000.0) + (nz * (f64)arg2) + d) / (ny * 2000.0)));
                                        collisionCheckSlopeAngle(arg3, (f32)((2000.0 * val) - 1000.0), 0, arg0, 0);
                                    }
                                    if (D_807F94BC != 0) {
                                        val = (0.0 - ((((f64)arg1 * nx) + (ny * -1000.0) + (nz * (f64)arg2) + d) / (ny * 2000.0)));
                                        collisionRecordBoxTriangle(tri, (f32)((2000.0 * val) - 1000.0));
                                    }
                                    if (collisionCheckBoxTriangleWinding(tri) != 0) {
                                        val = (0.0 - ((((f64)arg1 * nx) + (ny * -1000.0) + (nz * (f64)arg2) + d) / (ny * 2000.0)));
                                        y = (f32)((2000.0 * val) - 1000.0);
                                        if (mathCheckCloserFloatThreshold(hit_y, y, (f32)((f64)arg3 + 4.0), 0) != 0) {
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

    if (hit != 0 && mathCheckCloserFloatThreshold(*arg4, hit_y, (f32)((f64)arg3 + 4.0), 0) != 0) {
        *arg4 = hit_y;
        collisionStoreBoxTriangleNormalAngles(arg0, hit_tri, 1);
        if (hit_actor->flags2 & 8) {
            D_807F94AD = 1;
        }
        if (arg0 != NULL) {
            collisionTransformPointToActorLocal(arg0, hit_actor, hit_tri, arg1, hit_y, arg2);
        }
    }
    return hit;
}

void collisionRecordBoxTriangle(CollisionBoxTri *arg0, f32 arg1) {
    if (sCamFloorHitCount != 0xA) {
        sCamFloorHits[sCamFloorHitCount].height = arg1;
        if (collisionCheckBoxTriangleWinding(arg0) != 0) {
            sCamFloorHits[sCamFloorHitCount].flags = 1;
        } else {
            sCamFloorHits[sCamFloorHitCount].flags = 2;
        }
        collisionStoreBoxTriangleNormalAngles(NULL, arg0, 0);
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


void collisionTransformPointToActorLocal(Actor *arg0, Actor *arg1, CollisionBoxTri *arg2, f32 arg3, f32 arg4, f32 arg5) {
    float xfMtx[4][4];
    float invMtx[4][4];
    ActorSub140 *sub;
    s32 idx;
    Mtx *mtx;

    D_807F9470 = arg1;
    sub = arg1->collision;
    if (gFrameCounter == sub->unk88) {
        idx = gGfxBufferIndex;
    } else {
        idx = (gGfxBufferIndex ^ 1) & 0xFF;
    }
    mtx = sub->unk74[idx];
    if ((arg2->unk4C != arg2->unk48) || (arg2->unk50 != arg2->unk48)) {
        D_807F94B2 = 1;
    }
    D_807F9480 = arg2->unk48;
    if (arg2->unk48 == -1) {
        memcpy(xfMtx, sub->boxBounds, 0x40);
    } else {
        guMtxL2F(xfMtx, &mtx[arg2->unk48 >> 6]);
    }
    matrix4Invert(invMtx, xfMtx);
    guMtxXFMF(invMtx, arg3, arg4, arg5, &D_807F9474, &D_807F9478, &D_807F947C);
}

void collisionTransformPointByActorMtx(Actor *actor, u32 arg1, f32 *arg2, f32 arg3, f32 *arg4) {
    s32 idx;
    f32 x;
    f32 y;
    f32 z;
    ActorSub140 *sub;
    Mtx *mtx;
    float xfMtx[4][4];

    x = *arg2;
    y = *arg4;
    sub = actor->collision;
    if (gFrameCounter == sub->unk88) {
        idx = gGfxBufferIndex;
    } else {
        idx = gGfxBufferIndex ^ 1;
        idx = idx & 0xFF; // FAKE: split mask steers sub/idx v0/v1 allocation
    }
    mtx = sub->unk74[idx];
    if (arg1 == -1) {
        memcpy(xfMtx, sub->boxBounds, 0x40);
    } else {
        guMtxL2F(xfMtx, &mtx[arg1 >> 6]);
    }
    guMtxXFMF(xfMtx, x, arg3, y, arg2, &z, arg4);
}

s32 collisionCheckBoxTriangleBoundsXZ(CollisionBoxTri *arg0, f32 arg1, f32 arg2) {
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

    min_x = ((x0 = arg0->x0) < (x1 = arg0->x1)) ? x0 : x1;
    x2 = arg0->x2;
    min_x = (min_x < x2) ? min_x : x2;

    z0 = arg0->z0;
    z1 = arg0->z1;
    min_z = (z0 < z1) ? z0 : z1;
    z2 = arg0->z2;
    min_z = (min_z < z2) ? min_z : z2;

    max_x = (x1 < x0) ? x0 : x1;
    max_x = (x2 < max_x) ? max_x : x2;

    max_z = (z1 < z0) ? z0 : z1;
    max_z = (z2 < max_z) ? max_z : z2;

    if ((arg1 < min_x) || (max_x < arg1) || (arg2 < min_z) || (max_z < arg2)) {
        return 0;
    }
    return 1;
}

u8 collisionCheckBoxTriangleContainsPointXZ(CollisionBoxTri *arg0, f32 arg1, f32 arg2) {
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
    a = (f64)(arg0->x2 + arg0->x1) * 0.5;
    b = (f64)(arg0->z2 + arg0->z1) * 0.5;
    cx = (arg0->x0 + a) * 0.5;
    cz = (arg0->z0 + b) * 0.5;
    i = 0; sideC = 0; do { // LAYOUT: i = 0 joined to the loop head (move v0,zero lands after the hoisted ldc1s); FAKE: dead init sideC = 0 gives sideC an earlier first appearance than sideP (uopt colours ties in first-appearance order: sideC a0, sideP a1)
        switch (i) {
        case 0:
            dx = arg0->x1 - arg0->x0;
            dz = arg0->z1 - arg0->z0;
            ox = arg0->x0;
            oz = arg0->z0;
            break;
        case 1:
            dx = arg0->x2 - arg0->x0;
            dz = arg0->z2 - arg0->z0;
            ox = arg0->x0;
            oz = arg0->z0;
            break;
        case 2:
            dx = arg0->x2 - arg0->x1;
            dz = arg0->z2 - arg0->z1;
            ox = arg0->x1;
            oz = arg0->z1;
            break;
        }
        a = (arg1 - ox) * dz;
        b = (arg2 - oz) * dx;
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

s32 collisionCheckBoxTriangleWinding(CollisionBoxTri *arg0) {
    CrossProductStack sp;

    sp.v1[0] = arg0->x2 - arg0->x0;
    sp.v1[2] = arg0->z2 - arg0->z0;
    sp.v0[0] = arg0->x1 - arg0->x0;
    sp.v0[2] = arg0->z1 - arg0->z0;
    sp.cross = (sp.v1[2] * sp.v0[0]) - (sp.v1[0] * sp.v0[2]);
    if (sp.cross <= 0.0) {
        return 1;
    }
    return 0;
}

void collisionStoreBoxTriangleNormalAngles(Actor *arg0, CollisionBoxTri *arg1, u8 arg2) {
    CrossProductStack3D sp;

    sp.v1[0] = arg1->x2 - arg1->x0;
    sp.v1[1] = arg1->y2 - arg1->y0;
    sp.v1[2] = arg1->z2 - arg1->z0;
    sp.v0[0] = arg1->x1 - arg1->x0;
    sp.v0[1] = arg1->y1 - arg1->y0;
    sp.v0[2] = arg1->z1 - arg1->z0;
    sp.cross[0] = (sp.v1[1] * sp.v0[2]) - (sp.v1[2] * sp.v0[1]);
    sp.cross[1] = (sp.v1[2] * sp.v0[0]) - (sp.v1[0] * sp.v0[2]);
    sp.cross[2] = (sp.v1[0] * sp.v0[1]) - (sp.v1[1] * sp.v0[0]);
    collisionStoreSurfaceNormalAngles(arg0, sp.cross[0], sp.cross[1], sp.cross[2], 1, arg2, 2);
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

void assetInflateAndFree(void *arg0, void *arg1) {
    u8 *src;
    u8 *dst;

    src = arg0;
    dst = arg1;
    if (D_80748E14 == NULL) {
        D_80748E14 = heapAlloc(0x2400);
    }
    gunzip(&src, &dst, D_80748E14);
    heapFree(arg0);
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
            if (D_807FA8A0[i].unk8 != 0) {
                assetInflateAndFree(D_807FA8A0[i].unk0, D_807FA8A0[i].unk4);
            }
        } while (++i < D_807F9680);
    }
    if (D_80748E14 != NULL) {
        heapFree(D_80748E14);
        D_80748E14 = NULL;
    }
    D_807F9680 = 0;
}

s32 assetGetSize(s32 arg0, s32 arg1) {
    s32 romAddr;
    s32 size;

    assetEnsureTableLoaded();
    assetResolveRomRange(arg0, arg1, &romAddr, &size);
    if (size == 0) {
        return 0;
    }
    return romAddr;
}

s32 assetGetCachedSizeOrResolve(s32 arg0, s32 arg1) {
    s32 romAddr;
    s32 size;

    if (D_80748E18[arg0] != 0) {
        size = D_807FB1A0[arg0][arg1];
    } else {
        assetEnsureTableLoaded();
        assetResolveRomRange(arg0, arg1, &romAddr, &size);
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

void *assetLoad(s32 arg0, u32 arg1, u8 arg2, u8 arg3) {
    s32 pad;
    s32 romAddr;
    s32 size;
    s32 allocSize;
    void *buffer;

    assetEnsureTableLoaded();
    if (arg3 == 0) {
        if ((arg1 >= 0x80000000U) && (arg1 < 0xA0000000U)) {
            collisionBstInsertByHash(arg1, arg0, 0);
            D_807F967C = 0;
            D_807F9678 = 0;
            return (void *)arg1;
        }
        buffer = (void *)assetGetTableEntry(arg0, arg1);
        if (buffer != NULL) {
            collisionBstInsertByHash(buffer, arg0, arg1);
            D_807F967C = 0;
            D_807F9678 = 0;
            return buffer;
        }
    }
    assetResolveRomRange(arg0, arg1, &romAddr, &size);
    if (size == 0) {
        D_807F967C = 0;
        D_807F9678 = 0;
        return NULL;
    }
    if (D_80748E18[arg0] != 0) {
        allocSize = D_807FB1A0[arg0][arg1];
    } else {
        allocSize = size;
    }
    if (D_807F9678 == 0) {
        buffer = heapAlloc(allocSize);
    } else {
        buffer = heapAllocFromPool(D_807F9678, allocSize);
    }
    if (arg2 != 0) {
        if (D_80748E18[arg0] != 0) {
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
        D_807FA8A0[D_807F9680].unk8 = D_80748E18[arg0];
        if (D_80748E18[arg0] != 0) {
            D_807FA8A0[D_807F9680].unk0 = heapAlloc(size);
            D_807FA8A0[D_807F9680].unk4 = buffer;
        } else {
            D_807FA8A0[D_807F9680].unk4 = buffer;
            D_807FA8A0[D_807F9680].unk0 = buffer;
        }
        osInvalDCache(D_807FA8A0[D_807F9680].unk0, size);
        osPiStartDma(&D_807F9688[D_807F9680], 0, 0, romAddr, D_807FA8A0[D_807F9680].unk0, (u32)size, &D_807656D0);
        D_807F9680 += 1;
    }
    assetSetTableEntry(arg0, arg1, (s32)buffer);
    collisionBstInsertByHash(buffer, arg0, arg1);
    D_807F967C = 0;
    D_807F9678 = 0;
    return buffer;
}

void assetSetImmediateFree(void) {
    D_807F967D = 1;
}

void assetFreeBuffer(void *arg0, s32 arg1, s32 arg2) {
    s32 table;
    s32 index;

    if (collisionBstLookupAndDecrementByHash(arg0) == 0) {
        collisionBstDeleteByHash(arg0, &table, &index);
        assetSetTableEntry(table, index, 0);
        if (D_807F967D == 0) {
            heapFreeDeferred(arg0);
        } else {
            heapFree(arg0);
        }
    }
    D_807F967D = 0;
}

void assetSetTableEntry(s32 arg0, s32 arg1, s32 arg2) {
    if (D_807F95A8[arg0] != NULL) {
        D_807F95A8[arg0][arg1] = arg2;
    }
}

s32 assetResolveRomRange(s32 arg0, s32 arg1, s32 *arg2, s32 *arg3) {
    s32 pad[2];
    s32 target;
    s32 end;
    u64 header;
    s32 *table;
    s32 start;
    s32 size;
    s32 index;

    index = arg1;
    table = &D_807F9528[arg0][arg1];
    start = table[0];
    if (start & 0x80000000) {
        size = 8;
        start &= 0x7FFFFFFF;
        dmaReadAssetDecompress(D_8000DDCC + start, &header, &size, 0, 0, 0, 0);
        target = (s16)(header >> 48);
        assetResolveRomRange(arg0, target, arg2, arg3);
        index = target;
    } else {
        end = table[1] & 0x7FFFFFFF;
        *arg2 = D_8000DDCC + start;
        *arg3 = end - start;
    }
    return index;
}

s32 assetGetTableEntry(s32 arg0, s32 arg1) {
    s32 *ptr = D_807F95A8[arg0];
    s32 ret = 0;

    if (ptr != NULL) {
        ret = ptr[arg1];
    }
    return ret;
}

void assetEnsureTableLoaded(s32 arg0) {
    u32 start;
    s32 pad50;
    u64 header;
    s32 pad44;
    u32 size;
    u32 headerSize;

    headerSize = 8;
    if (D_807F9528[arg0] != NULL) {
        return;
    }
    start = D_807F9520[arg0];
    dmaReadAssetDecompress(D_8000DDCC + start, &header, &headerSize, 0, 0, 0, 0);
    size = (u32)(header >> 32) - start;
    D_807F9528[arg0] = heapAlloc(size);
    dmaReadAssetDecompress(D_8000DDCC + start, D_807F9528[arg0], &size, 0, 0, 0, 0);
    switch (arg0) {
        case 4:
        case 7:
        case 14:
        case 25: {
            u32 i;
            D_807F95A8[arg0] = heapAlloc(size);
            for (i = 0; i < (u32)(size / 4); i++) {
                D_807F95A8[arg0][i] = 0;
            }
            break;
        }
        default:
            D_807F95A8[arg0] = NULL;
            break;
    }
}


typedef struct CollisionBstNodeBase {
    /* 0x00 */ s32 unk0;
    /* 0x04 */ u8 pad4[3];
    /* 0x07 */ u8 unk7;
    /* 0x08 */ u16 pad8;
    /* 0x0A */ u16 unkA;
    /* 0x0C */ s32 unkC;
    /* 0x10 */ u8 unk10;
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


void collisionBstLookupByHash(s32 arg0, s32 *arg1, s32 *arg2) {
    collisionBstLookupOrAssert(D_807F9628[collisionGetBucketIndex(arg0)], arg0, arg1, arg2);
}

typedef struct CollisionBstNode {
    /* 0x00 */ s32 unk0;
    /* 0x04 */ s32 unk4;
    /* 0x08 */ s32 unk8;
    /* 0x0C */ s32 unkC;
    /* 0x10 */ u8 unk10;
    /* 0x14 */ struct CollisionBstNode *left;
    /* 0x18 */ struct CollisionBstNode *right;
} CollisionBstNode;

void collisionBstLookupOrAssert(CollisionBstNode *arg0, u32 arg1, s32 *arg2, s32 *arg3) {
    u8 idxA;
    u16 idxB;
    s32 frame;

    if (arg0 == NULL) {
        idxA = 0;
        idxB = 0;
        frame = 0;
        collisionQueueSearch(arg1, &idxA, &idxB, &frame);
        faultSetMessage(7, idxA, idxB, gFrameCounter - frame);
    }
    if (arg1 == arg0->unk0) {
        *arg2 = arg0->unk4;
        *arg3 = arg0->unk8;
    } else if (arg0->unk0 < arg1) {
        collisionBstLookupOrAssert(arg0->right, arg1, arg2, arg3);
    } else {
        collisionBstLookupOrAssert(arg0->left, arg1, arg2, arg3);
    }
}


void collisionBstInsertByHash(s32 arg0, s32 arg1, s32 arg2) {
    u32 index = collisionGetBucketIndex(arg0);

    D_807F9628[index] = collisionBstInsert(D_807F9628[index], arg0, arg1, arg2);
}

CollisionBstNode *collisionBstInsert(CollisionBstNode *node, u32 arg1, s32 arg2, s32 arg3) {
    if (node == NULL) {
        node = (CollisionBstNode *)heapAlloc(sizeof(CollisionBstNode));
        node->unkC = 1;
        node->unk0 = arg1;
        node->unk4 = arg2;
        node->unk8 = arg3;
        node->unk10 = D_807F967C;
        node->right = NULL;
        node->left = NULL;
    } else if (arg1 == node->unk0) {
        node->unkC++;
        if (D_807F967C) {
            node->unk10 = 1;
        }
    } else if (node->unk0 < arg1) {
        node->right = collisionBstInsert(node->right, arg1, arg2, arg3);
    } else {
        node->left = collisionBstInsert(node->left, arg1, arg2, arg3);
    }
    return node;
}


s32 collisionBstLookupAndDecrementByHash(s32 arg0) {
    return collisionBstLookupAndDecrement(D_807F9628[collisionGetBucketIndex(arg0)], arg0);
}

typedef struct CollisionQueueEntry {
    s32 unk0;
    s32 unk4;
    u16 unk8;
    u8 unkA;
} CollisionQueueEntry;

extern CollisionQueueEntry D_807FB228[];

void collisionQueueSearch(s32 arg0, u8 *arg1, u16 *arg2, s32 *arg3) {
    s32 i;

    if ((i = D_807FB221 - 1) < 0) {
        i = 0x3F;
    }
    while (i != D_807FB220) {
        if (arg0 == D_807FB228[i].unk4) {
            *arg1 = D_807FB228[i].unkA;
            *arg2 = D_807FB228[i].unk8;
            *arg3 = D_807FB228[i].unk0;
            break;
        }
        if (--i < 0) {
            i = 0x3F;
        }
    }
}

void collisionQueueAppend(s32 arg0, u8 arg1, u16 arg2) {
    u8 idx = D_807FB221;
    CollisionQueueEntry *item = &D_807FB228[idx];

    item->unk0 = gFrameCounter;
    item->unk4 = arg0;
    item->unkA = arg1;
    item->unk8 = arg2;
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


s32 collisionBstLookupAndDecrement(CollisionBstNodeBase *node, u32 arg1) {
    u8 idxA;
    u16 idxB;
    s32 frame;

    if (node == NULL) {
        idxA = 0;
        idxB = 0;
        frame = 0;
        collisionQueueSearch(arg1, &idxA, &idxB, &frame);
        return 0;
    }
    if (arg1 == node->unk0) {
        if (node->unk10 == 0) {
            node->unkC--;
        }
        collisionQueueAppend(arg1, node->unk7, node->unkA);
        return node->unkC;
    }
    if (node->unk0 < arg1) {
        return collisionBstLookupAndDecrement(node->right, arg1);
    }
    return collisionBstLookupAndDecrement(node->left, arg1);
}


void collisionBstDeleteByHash(s32 arg0, s32 arg1, s32 arg2) {
    u32 index = collisionGetBucketIndex(arg0);

    D_807F9628[index] = collisionBstDelete(D_807F9628[index], arg0, arg1, arg2);
}


CollisionBstNode *collisionBstDelete(CollisionBstNode *node, u32 key, s32 *out_val1, s32 *out_val2) {
    CollisionBstNode *old;

    if (node != NULL) {
        if (key == node->unk0) {
            *out_val1 = node->unk4;
            *out_val2 = node->unk8;
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
                node->right = collisionBstExtractMin(node->right, &node->unk0, &node->unk4, &node->unk8, &node->unkC, &node->unk10);
            }
        } else if (node->unk0 < key) {
            node->right = collisionBstDelete(node->right, key, out_val1, out_val2);
        } else {
            node->left = collisionBstDelete(node->left, key, out_val1, out_val2);
        }
    }
    return node;
}

CollisionBstNode *collisionBstExtractMin(CollisionBstNode *node, s32 *arg1, s32 *arg2, s32 *arg3, s32 *arg4, u8 *arg5) {
    void *pad;
    CollisionBstNode *left = node->left;

    if (left == NULL) {
        CollisionBstNode *old;

        *arg1 = node->unk0;
        *arg2 = node->unk4;
        *arg3 = node->unk8;
        *arg4 = node->unkC;
        *arg5 = node->unk10;
        old = node;
        node = node->right;
        heapFree(old);
    } else {
        node->left = collisionBstExtractMin(left, arg1, arg2, arg3, arg4, arg5);
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
    /* 0x00 */ s32 unk0;
    /* 0x04 */ s32 unk4;
    /* 0x08 */ s32 unk8;
    /* 0x0C */ s32 unkC;
    /* 0x10 */ u8 unk10;
} CollisionBstFlatItem;


void collisionBstRebalanceBucket(s32 arg0) {
    s32 count;
    void *buffer;
    CollisionBstNodeBase *new_root;
    s32 index;

    index = 0;
    count = collisionBstCountNodes(D_807F9628[arg0]);
    if (count != 0) {
        buffer = heapAlloc(count * 20);
        collisionBstFlatten(D_807F9628[arg0], buffer, &index);
        collisionBstSortFlatItems(buffer, 0, count - 1);
        new_root = collisionBstBuildBalanced(buffer, 0, count - 1);
        collisionBstFreeTree(D_807F9628[arg0]);
        D_807F9628[arg0] = new_root;
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

    node->unk0 = buffer[mid].unk0;
    node->unk4 = buffer[mid].unk4;
    node->unk8 = buffer[mid].unk8;
    node->unkC = buffer[mid].unkC;
    node->unk10 = buffer[mid].unk10;

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
    buffer[*index].unk0 = node->unk0;
    buffer[*index].unk4 = node->unk4;
    buffer[*index].unk8 = node->unk8;
    buffer[*index].unkC = node->unkC;
    buffer[*index].unk10 = node->unk10;
    (*index)++;
    collisionBstFlatten(node->left, buffer, index);
    collisionBstFlatten(node->right, buffer, index);
}

void collisionBstSortFlatItems(CollisionBstFlatItem *arr, s32 low, s32 high) {
    s32 i;
    s32 j;
    u32 pivot;
    CollisionBstFlatItem *pivot_ptr;
    s32 size = 20;
    u32 temp0;
    s32 temp1;
    s32 temp2;
    s32 temp3;
    u8 temp4;

    if (low < high) {
        pivot_ptr = (CollisionBstFlatItem *)((u8 *)arr + high * size);
        pivot = pivot_ptr->unk0;
        i = low - 1;
        j = high;

        while (1) {
            while (arr[++i].unk0 < pivot && i < high)
                ;
            while (pivot < arr[--j].unk0 && low < j)
                ;
            if (i >= j) {
                break;
            }
            temp0 = arr[i].unk0;
            temp1 = arr[i].unk4;
            temp2 = arr[i].unk8;
            temp3 = arr[i].unkC;
            temp4 = arr[i].unk10;
            arr[i].unk0 = arr[j].unk0;
            arr[i].unk4 = arr[j].unk4;
            arr[i].unk8 = arr[j].unk8;
            arr[i].unkC = arr[j].unkC;
            arr[i].unk10 = arr[j].unk10;
            arr[j].unk0 = temp0;
            arr[j].unk4 = temp1;
            arr[j].unk8 = temp2;
            arr[j].unkC = temp3;
            arr[j].unk10 = temp4;
        }

        temp0 = arr[i].unk0;
        temp1 = arr[i].unk4;
        temp2 = arr[i].unk8;
        temp3 = arr[i].unkC;
        temp4 = arr[i].unk10;
        arr[i].unk0 = pivot_ptr->unk0;
        arr[i].unk4 = pivot_ptr->unk4;
        arr[i].unk8 = pivot_ptr->unk8;
        arr[i].unkC = pivot_ptr->unkC;
        arr[i].unk10 = pivot_ptr->unk10;
        if (!arr) {} // FAKE: dead check steers uopt coloring of the a0-a3 temps
        pivot_ptr->unk0 = temp0;
        pivot_ptr->unk4 = temp1;
        pivot_ptr->unk8 = temp2;
        pivot_ptr->unkC = temp3;
        pivot_ptr->unk10 = temp4;

        collisionBstSortFlatItems(arr, low, i - 1);
        collisionBstSortFlatItems(arr, i + 1, high);
    }
}

u32 collisionGetBucketIndex(u32 key) {
    return (key >> 12) % 20;
}
