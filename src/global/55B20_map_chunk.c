#include "common.h"
#include "compiler/ido/memory.h"
#include "actor.h"
#include "sched.h"
#include "map.h"
#include "render.h"
#include "proto/global/103AB0_view_effects.h"
#include "proto/global/15050_heap.h"
#include "proto/global/201B0_camera.h"
#include "proto/global/2F550_map_render.h"
#include "proto/global/35000_render_entry.h"
#include "proto/global/36880_model_slot.h"
#include "proto/global/55B20_map_chunk.h"
#include "proto/global/5DE10_fog.h"
#include "proto/global/5E2F0_light.h"
#include "proto/global/61AA0_render_caches.h"
#include "proto/global/63EC0_effect_water.h"
#include "proto/global/67890_target_table.h"
#include "proto/global/68960_fog_distance.h"
#include "proto/global/6AD90_collision.h"

#define WRITE_GFX(pkt, _w0, _w1) { Gfx *_g = (Gfx *)(pkt); _g->words.w0 = (_w0); _g->words.w1 = (u32)(_w1); }

// This TU's .data (0x807482F0-0x807482F8 + 8-byte TU pad); D_807482F0 is unreferenced.
s32 D_807482F0 = 2500;
s32 gMapChunkFrustumCaptureIndex = 5;

typedef struct MapPortalSlot {
    /* 0x0 */ s16 unk0;
    /* 0x2 */ s16 chunk;
    /* 0x4 */ s16 target;
    /* 0x6 */ s16 maxDist;
    /* 0x8 */ u8 seen;
    /* 0x9 */ u8 enabled;
} MapPortalSlot;

extern MapPortalSlot *gMapPortalSlots;

s32 gMapPortalSlotCount;
struct MapGridPoint *gMapGridTrianglePlanes;
s32 gMapChunkCount;
u8 *gMapPortalVisible;
s16 sMapPortalChunkStack[20];
s16 sMapVisibleChunks[20];
s32 sMapVisibleChunkCount;
s32 D_807F6C84; // unreferenced word between the chunk count and sMapClipQuad
typedef struct MapVec3 {
    /* 0x0 */ f32 x;
    /* 0x4 */ f32 y;
    /* 0x8 */ f32 z;
} MapVec3;

MapVec3 sMapClipQuad[4];
u8 D_807F6CB8[0xC0]; // unreferenced space before the clipping scratch buffers
MapVec3 sMapClippedPoly[20];
MapVec3 sMapClipScratchA[20];
MapVec3 sMapClipScratchB[20];
u8 sMapActiveZones[16];
u8 sMapActiveZoneCount;
u8 sMapBlockedPortals[16];
u8 sMapBlockedPortalCount;
Mtx *sMapChunkScaleMtx;
u8 gMapChunkEnabled[0x32];
u8 sMapChunkReleaseCursor;
u8 sMapCamChunkFromActor;
s32 gMapCellCount;

extern f32 *gChunkLightR;
extern f32 *gChunkLightG;
extern f32 *gChunkLightB;
extern f32 *gChunkLightTargetR;
extern f32 *gChunkLightTargetG;
extern f32 *gChunkLightTargetB;

void mapChunkAllocLists(MapFileHeader *header) {
    s32 chunkCount;
    s32 count;
    s32 size;

    chunkCount = gMapChunkCount = *(s32 *)(header->collOff + (u8 *)header);
    if (chunkCount >= 2) {
        count = chunkCount & 0xFF;
    } else {
        count = 1;
    }
    size = count * 4;
    gChunkLightR = heapAlloc(size);
    gChunkLightG = heapAlloc(size);
    gChunkLightB = heapAlloc(size);
    gChunkLightTargetR = heapAlloc(size);
    gChunkLightTargetG = heapAlloc(size);
    gChunkLightTargetB = heapAlloc(size);
}

typedef struct MapPortal {
    /* 0x0 */ s16 target;
    /* 0x2 */ s16 portal;
    /* 0x4 */ s16 maxDist;
    /* 0x6 */ u8 pad6[2];
    /* 0x8 */ s32 dl0;
    /* 0xC */ s32 dl1;
} MapPortal;

extern s32 gMapVtxBase;
extern s16 gMapFogDist;
extern u8 gMapHasCellLitChunks;
extern MapPortal *gMapPortals;
extern s32 gMapPortalCount;
typedef struct MapGridPoint {
    /* 0x00 */ s64 nx;
    /* 0x08 */ s64 ny;
    /* 0x10 */ s64 nz;
    /* 0x18 */ s64 d;
    /* 0x20 */ f32 len;
    /* 0x24 */ f32 lenSq;
    /* 0x28 */ u8 axis;
    /* 0x29 */ u8 pad29[0x7];
} MapGridPoint; /* 0x30 */

typedef struct {
    /* 0x00 */ f32 x[4];
    /* 0x10 */ f32 y[4];
    /* 0x20 */ f32 z[4];
} MapGridVectors;

extern MapGridVectors *gMapGridTriangleVerts;
extern struct MapCell *gMapCells;
extern struct MapBox *gMapCellBoxes;

typedef struct { s32 offset; s16 minX; s16 minZ; s16 maxX; s16 maxZ; } MapChunkCollEntry;

void mapChunksInitFromMapData(MapFileHeader *data) {
    s32 i;
    s32 collOff;
    s32 dlBase;
    u8 *p;
    u8 *file;
    u32 total;
    s32 n;
    s32 chunksOff;
    s32 cellsOff;
    s32 boxesOff;
    s32 vecsOff;
    s32 portalsOff;
    s32 relocsOff;
    s32 entryOff;
    u8 buf[0xE28];
    s32 count;
    s32 k;
    s32 size;

    gMapCellCount = 0;
    gMapHasCellLitChunks = 0;
    sMapCamChunkFromActor = 0;
    if (gMapChunkCount != 0) {
        file = (u8 *)data;
        gMapFogDist = data->fogDist;
        sMapChunkScaleMtx = heapAlloc(0x40);
        guScale(sMapChunkScaleMtx, 1.0f / 3.0f, 1.0f / 3.0f, 1.0f / 3.0f);
        cellsOff = data->cellsOff;
        gMapCellCount = *(s32 *)(file + cellsOff);
        gMapCells = (struct MapCell *)(file + cellsOff + 4);
        boxesOff = data->boxesOff;
        gMapCellBoxes = (struct MapBox *)(file + boxesOff + 4);
        vecsOff = data->vecsOff;
        gMapGridTriangleVerts = (MapGridVectors *)(file + vecsOff);
        if (data) {}  // FAKE: uopt block boundary (boxes holder gets a0, no call in its block)
        collOff = data->collOff;
        chunksOff = data->chunksOff;
        dlBase = data->dlBase;
        portalsOff = data->portalsOff;
        gMapPortalSlotCount = *(s32 *)(file + portalsOff);
        gMapPortalSlots = (MapPortalSlot *)(file + portalsOff + 4);
        gMapPortalVisible = heapAlloc(gMapPortalSlotCount);
        relocsOff = data->relocsOff;
        gMapPortalCount = *(s32 *)(file + relocsOff);
        gMapPortals = (MapPortal *)(file + relocsOff + 4);
        for (i = 0; i < gMapPortalCount; i++) {
            if (gMapPortals[i].dl0 != -1) {
                gMapPortals[i].dl0 += (s32)(file + dlBase);
            }
            if (gMapPortals[i].dl1 != -1) {
                gMapPortals[i].dl1 += (s32)(file + dlBase);
            }
        }
        gMapChunks = heapAlloc(gMapChunkCount * sizeof(MapChunk));
        p = file + chunksOff;
        for (n = 0; n < gMapChunkCount; n++) {
            count = 0;
            gMapChunks[n].state = 0;
            gMapChunks[n].playerMask = 0;
            gMapChunks[n].opaqueList = NULL;
            gMapChunks[n].translucentList = NULL;
            gMapChunks[n].sprites = NULL;
            gMapChunks[n].streamFlags = 4;
            gMapChunks[n].baseVtx = (u8 *)(*(s32 *)(p + 0x2C) + gMapVtxBase);
            gMapChunks[n].curVtx = gMapChunks[n].baseVtx;
            lightSetTargetColor(p[0] / 255.0, p[1] / 255.0, p[2] / 255.0, n);
            lightCopyTargetColors(n);
            gMapChunks[n].noSprites = p[3];
            p += 0xC;
            gMapChunks[n].kind = p[-8];
            gMapChunks[n].lightMode = *(s32 *)(p - 4);
            if (*(s32 *)p != -1) {
                *(s32 *)p += (s32)(file + dlBase);
            }
            gMapChunks[n].layerDl0 = *(s32 *)p;
            p += 8;
            gMapChunks[n].layerSize0 = *(s32 *)(p - 4);
            total = gMapChunks[n].layerSize0;
            if (gMapChunks[n].kind == 2) {
                gMapHasCellLitChunks = 1;
                mapChunkBuildCellTable(gMapChunks[n].layerDl0, gMapChunks[n].layerSize0, buf, &count, 0, n);
            }
            if (*(s32 *)p != -1) {
                *(s32 *)p += (s32)(file + dlBase);
            }
            gMapChunks[n].layerDl1 = *(s32 *)p;
            p += 8;
            gMapChunks[n].layerSize1 = *(s32 *)(p - 4);
            size = gMapChunks[n].layerSize1;
            total += size;
            if (gMapChunks[n].kind == 2) {
                mapChunkBuildCellTable(gMapChunks[n].layerDl1, size, buf, &count, 1, n);
            }
            if (*(s32 *)p != -1) {
                *(s32 *)p += (s32)(file + dlBase);
            }
            gMapChunks[n].layerDl2 = *(s32 *)p;
            p += 8;
            gMapChunks[n].layerSize2 = *(s32 *)(p - 4);
            size = gMapChunks[n].layerSize2;
            total += size;
            if (gMapChunks[n].kind == 2) {
                mapChunkBuildCellTable(gMapChunks[n].layerDl2, size, buf, &count, 2, n);
            }
            if (*(s32 *)p != -1) {
                *(s32 *)p += (s32)(file + dlBase);
            }
            gMapChunks[n].layerDl3 = *(s32 *)p;
            p += 8;
            gMapChunks[n].layerSize3 = *(s32 *)(p - 4);
            total += gMapChunks[n].layerSize3;
            gMapChunks[n].loadCursor = (u8 *)gMapChunks[n].layerDl0 + ((total >> 3) << 3);
            gMapChunks[n].loadStart = (u8 *)gMapChunks[n].layerDl0;
            gMapChunks[n].loadEnd = gMapChunks[n].loadCursor;
            if (gMapChunks[n].kind == 2) {
                mapChunkBuildCellTable(gMapChunks[n].layerDl3, gMapChunks[n].layerSize3, buf, &count, 3, n);
            }
            gMapChunks[n].vtxSize = *(s32 *)(p + 4);
            p += 8;
            gMapChunks[n].litVtx[0] = NULL;
            gMapChunks[n].litVtx[1] = NULL;
            entryOff = n * sizeof(MapChunkCollEntry);
            gMapChunks[n].collStart = (struct MapCollisionNode *)(((MapChunkCollEntry *)((u8 *)((s32)file + collOff + 4) + entryOff))->offset + ((s32)file + collOff));
            gMapChunks[n].collEnd = (struct MapCollisionNode *)(((MapChunkCollEntry *)((u8 *)((s32)file + collOff + 4) + entryOff))[1].offset + ((s32)file + collOff));
            gMapChunks[n].minX = ((MapChunkCollEntry *)((u8 *)((s32)file + collOff + 4) + entryOff))->minX;
            gMapChunks[n].minZ = ((MapChunkCollEntry *)((u8 *)((s32)file + collOff + 4) + entryOff))->minZ;
            gMapChunks[n].maxX = ((MapChunkCollEntry *)((u8 *)((s32)file + collOff + 4) + entryOff))->maxX;
            gMapChunks[n].maxZ = ((MapChunkCollEntry *)((u8 *)((s32)file + collOff + 4) + entryOff))->maxZ;
            gMapChunks[n].lastSeenFrame = -1;
            if (count != 0) {
                gMapChunks[n].cells = heapAlloc(count * sizeof(MapChunkCell));
                memcpy(gMapChunks[n].cells, buf, count * sizeof(MapChunkCell));
                for (i = 0; i < count; i++) {
                    gMapChunks[n].cells[i].layerMask = 0xFF;
                }
            }
            gMapChunks[n].cellCount = count;
        }
        gMapGridTrianglePlanes = heapAlloc(gMapPortalSlotCount / 2 * sizeof(MapGridPoint));
        for (k = 0; k < gMapPortalSlotCount / 2; k++) {
            mapGridTriangleBuildPlane(k, &gMapGridTrianglePlanes[k]);
        }
        if (gMapChunks) {}  // FAKE: stretches the lda gMapChunks web over the plane loop so the chunk record pointer p takes s2 before it
        k = 0;
        do {
            gMapChunkEnabled[k] = 1;
            k++;
        } while (k < 0x32);
        sMapChunkReleaseCursor = 0;
    } else {
        gMapChunks = NULL;
    }
}

typedef struct MapZone {
    /* 0x00 */ u8 *verts;
    /* 0x04 */ s16 vertCount;
    /* 0x06 */ u8 pad6[0x2];
    /* 0x08 */ u8 *tris;
    /* 0x0C */ s16 triCount;
    /* 0x0E */ s16 height;
    /* 0x10 */ s16 minY;
    /* 0x12 */ s16 maxY;
    /* 0x14 */ s16 exitCells[16];
    /* 0x34 */ u8 exitCount;
    /* 0x36 */ s16 enterCells[16];
    /* 0x56 */ u8 enterCount;
    /* 0x58 */ s16 links[8];
    /* 0x68 */ u8 linkCount;
} MapZone; /* 0x6C */

extern MapZone *gMapZones[];


void mapFaceBuildTriangleFan(s32 faceId) {
    MapZone *face;
    s32 triCount;
    s32 next;
    s32 cur;
    s32 out;
    s32 curOff;
    u8 *vtx;
    s32 nextOff;

    face = gMapZones[faceId];
    if (face->tris != NULL) {
        heapFree(face->tris);
    }
    triCount = face->vertCount - 2;
    if (triCount < 0) {
        triCount = 0;
    }
    if (triCount != 0) {
        face->tris = heapAlloc(triCount * 0x12);
        face->triCount = triCount;
        if (face->vertCount >= 3) {
            cur = 1;
            next = 2;
            out = 0x24;
            nextOff = 0xC;
            do {
                curOff = cur * 6;
                cur = next;
                *(s16 *)(face->tris + out - 0x24) = *(s16 *)(face->verts);
                *(s16 *)(face->tris + out - 0x1E) = *(s16 *)(face->verts + 2);
                *(s16 *)(face->tris + out - 0x18) = *(s16 *)(face->verts + 4);
                *(s16 *)(face->tris + out - 0x22) = *(s16 *)(face->verts + curOff);
                *(s16 *)(face->tris + out - 0x1C) = *(s16 *)(face->verts + curOff + 2);
                *(s16 *)(face->tris + out - 0x16) = *(s16 *)(face->verts + curOff + 4);
                *(s16 *)(face->tris + out - 0x20) = *(s16 *)(face->verts + nextOff);
                *(s16 *)(face->tris + out - 0x1A) = *(s16 *)(face->verts + nextOff + 2);
                *(s16 *)(face->tris + out - 0x14) = *(s16 *)(face->verts + nextOff + 4);
                out += 0x12;
                nextOff += 6;
                next++;
            } while (next < face->vertCount);
        }
    }
    face->minY = 0x7FFF; face->maxY = -0x8000;  // LAYOUT: same-line stores flip the store scheduling order
    next = 0;
    if (face->vertCount > 0) {
        vtx = face->verts;
        do {
            if (face->maxY < *(s16 *)(vtx + 2)) {
                face->maxY = *(s16 *)(vtx + 2);
            }
            if (*(s16 *)(vtx + 2) < face->minY) {
                face->minY = *(s16 *)(vtx + 2);
            }
            next++;
            vtx += 6;
        } while (next < face->vertCount);
    }
}


typedef struct MapDlCommand {
    /* 0x0 */ u32 w0;
    /* 0x4 */ s32 w1;
} MapDlCommand;

typedef struct MapCell {
    /* 0x00 */ s16 chunk;
    /* 0x02 */ s16 id;
    /* 0x04 */ s16 parent;
    /* 0x06 */ s16 unk6;
    /* 0x08 */ s16 vtxOffset[4];
    /* 0x10 */ s16 vtxCount[4];
    /* 0x18 */ u8 visible;
    /* 0x19 */ u8 seen;
    /* 0x1A */ u8 pad1A[0x2];
} MapCell; /* 0x1C */

void mapChunkBuildCellTable(list, size, buf, count, kind, chunk)
s32 list;
s32 size;
MapChunkCell *buf;
s32 *count;
u8 kind;
s32 chunk;
{
    s32 n;
    s32 key;
    s32 found;
    s32 idx;
    s32 cfound;
    s32 cidx;
    s32 k;

    while (size != 0) {
        key = ((MapDlCommand *)list)->w0;
        idx = 0;
        found = 0;
        size -= 8;
        if (((u32)key >> 24) == 0) {
            n = *count;
            key = ((MapDlCommand *)list)->w1; // FAKE: key (the w0 command word) reused for the w1 cell id; a separate w0 local is a bb2 uopt candidate that also makes idx constrained (idx v1, key s1)
            while (idx < n && found == 0) {
                if (key == buf[idx].id) {
                    found = 1;
                } else {
                    idx += 1;
                }
            }
            cidx = 0;
            cfound = 0;
            do {
                if (key == gMapCells[cidx].id) {
                    cfound = 1;
                } else {
                    cidx += 1;
                }
            } while (cfound == 0);
            if (found == 0) {
                buf[n].id = key;
                for (k = 0; k < 4; k++) {
                    buf[*count].dl[k] = -1;
                }
                buf[*count].dl[kind] = list + 8;
                buf[*count].vtx[kind] = gMapChunks[chunk].curVtx + (gMapCells[cidx].vtxOffset[kind] << 4);
                *count += 1;
            } else {
                buf[idx].dl[kind] = list + 8;
                buf[idx].vtx[kind] = gMapChunks[chunk].curVtx + (gMapCells[cidx].vtxOffset[kind] << 4);
            }
        }
        list += 8;
        if ((size & list) && (size & list)) {} // FAKE: constrains loop invariants after both search indices are dead
    }
}

u8 mapChunkIsInUse(s16 chunk) {
    s32 active;
    s32 result;

    result = chunk != -1;
    if (result != 0) {
        if (gMapChunks[chunk].lightMode != 0) {
            active = 1;
        } else {
            active = 0;
        }
        result = active != 0;
    }
    return result;
}

void mapChunkSetEnabled(s16 chunk, u8 enabled) {
    gMapChunkEnabled[chunk] = enabled;
}

void mapPortalSlotSetEnabled(s16 pair, u8 side, u8 enabled) {
    gMapPortalSlots[pair * 2 + side].enabled = enabled;
}


void mapGridTriangleBuildPlane(s32 tri, MapGridPoint *plane) {
    s64 e1z;
    s64 e1y;
    s64 e1x;
    s64 e2z;
    s64 e2y;
    s64 e2x;
    s64 absX;
    s64 absY;
    s64 absZ;

    e1x = gMapGridTriangleVerts[tri].x[0] - gMapGridTriangleVerts[tri].x[1];
    e1y = gMapGridTriangleVerts[tri].y[0] - gMapGridTriangleVerts[tri].y[1];
    e1z = gMapGridTriangleVerts[tri].z[0] - gMapGridTriangleVerts[tri].z[1];
    e2x = gMapGridTriangleVerts[tri].x[0] - gMapGridTriangleVerts[tri].x[2];
    e2y = gMapGridTriangleVerts[tri].y[0] - gMapGridTriangleVerts[tri].y[2];
    e2z = gMapGridTriangleVerts[tri].z[0] - gMapGridTriangleVerts[tri].z[2];
    plane->nx = e1y * e2z - e1z * e2y;
    plane->ny = e1z * e2x - e1x * e2z;
    plane->nz = e1x * e2y - e1y * e2x;
    plane->d = -((plane->nx * gMapGridTriangleVerts[tri].x[1] + plane->ny * gMapGridTriangleVerts[tri].y[1]) + plane->nz * gMapGridTriangleVerts[tri].z[1]);
    plane->lenSq = plane->nx * plane->nx + plane->ny * plane->ny + plane->nz * plane->nz;
    plane->len = sqrtf(plane->lenSq);
    absX = plane->nx >= 0 ? plane->nx : 0 - plane->nx;
    absY = plane->ny >= 0 ? plane->ny : 0 - plane->ny;
    absZ = plane->nz >= 0 ? plane->nz : 0 - plane->nz;
    if ((absZ >= absX) && (absZ >= absY)) {
        plane->axis = 0;
    }
    if ((absY >= absX) && (absY >= absZ)) {
        plane->axis = 1;
    }
    if ((absX >= absY) && (absX >= absZ)) {
        plane->axis = 2;
    }
}


void mapChunkResetFlags(void) {
    s32 i;
    s32 j;

    for (i = 0; i < gMapChunkCount; i++) {
        gMapChunks[i].playerMask = 0;
        gMapChunks[i].texAnimPending = 1;
        gMapChunks[i].lightsDone = 0;
    }
    for (j = 0; j < gMapCellCount; j++) {
        gMapCells[j].seen = 0;
    }
}

void mapChunkClearBounds(void) {
    s32 i;

    for (i = 0; i < gMapChunkCount; i++) {
        gMapChunks[i].state = 0;
        gMapChunks[i].clipLeft = 0;
        gMapChunks[i].clipTop = 0;
        gMapChunks[i].clipRight = 0;
        gMapChunks[i].clipBottom = 0;
    }
    for (i = 0; i < gMapPortalSlotCount; i++) {
        gMapPortalSlots[i].seen = 0;
        gMapPortalVisible[i] = 0;
    }
}

s32 mapChunkContainsPoint(s16 x, s16 y, s16 chunk) {
    if (gMapChunks[chunk].playerMask == 0) {
        return 0;
    }
    if ((x >= gMapChunks[chunk].clipLeft) && (y >= gMapChunks[chunk].clipTop) && (gMapChunks[chunk].clipRight >= x) && (gMapChunks[chunk].clipBottom >= y)) {
        return 1;
    }
    return 0;
}

void mapChunkUpdateEntryNode(RenderEntry *entry) {
    u8 layer;
    RenderEntry **list;

    entry->chunkIndex = mapChunkFindByPosition(entry->x, entry->y, entry->z, entry->chunkIndex);
    layer = renderEntryIsTranslucent(entry->type, entry->object);
    if (entry->type == 0) {
        ((Actor *)entry->object)->chunkIndex = entry->chunkIndex;
    }
    switch (layer) {
    case 0:
        list = &gMapChunks[entry->chunkIndex].opaqueList;
        break;
    case 1:
        list = &gMapChunks[entry->chunkIndex].translucentList;
        break;
    }
    *list = renderEntryAddOrUpdate(*list, entry->type, entry->object, entry->x, entry->y, entry->z, entry->maxDist, entry->modelId, entry->autoPurge, entry->chunkIndex, 0);
}


void mapChunkMarkRenderEntry(void *targetId, u8 forceInfiniteDist) {
    u8 flag;
    s32 i;

    flag = 0;
    for (i = 0; i < gMapChunkCount && !flag; i++) {
        renderEntrySetDistanceOverride(gMapChunks[i].opaqueList, targetId, 0, forceInfiniteDist, &flag);
        if (!flag) {
            renderEntrySetDistanceOverride(gMapChunks[i].translucentList, targetId, 0, forceInfiniteDist, &flag);
        }
    }
}


u8 mapChunkPurgeNodeList(void *targetId, s16 *outChunk, u8 all) {
    u8 removed;
    s32 i;

    removed = 0;
    for (i = 0; i < gMapChunkCount && (!removed || all); i++) {
        gMapChunks[i].opaqueList = renderEntryRemove(gMapChunks[i].opaqueList, targetId, 0, &removed);
        if (removed) {
            *outChunk = i;
        }
        if (!removed || all) {
            gMapChunks[i].translucentList = renderEntryRemove(gMapChunks[i].translucentList, targetId, 0, &removed);
            if (removed) {
                *outChunk = i;
            }
        }
    }
    return removed;
}

extern u8 gCsModelUpdateCount;


void mapChunkClearNodeFlags(u8 all) {
    s32 i;

    for (i = 0; i < gMapChunkCount; i++) {
        if ((gMapChunks[i].state == 1) || all) {
            renderEntryListClearTouched(gMapChunks[i].opaqueList);
            renderEntryListClearTouched(gMapChunks[i].translucentList);
        }
    }
}

void mapChunkFreeNodeLists(u8 all) {
    s32 i;

    for (i = 0; i < gMapChunkCount; i++) {
        if ((gMapChunks[i].state == 1) || all) {
            gMapChunks[i].opaqueList = renderEntryListPurgeUntouched(gMapChunks[i].opaqueList);
            gMapChunks[i].translucentList = renderEntryListPurgeUntouched(gMapChunks[i].translucentList);
        }
    }
}

void mapChunkRebuildNodeLists(f32 x, f32 y, f32 z, u8 all) {
    s32 i;

    for (i = 0; i < gMapChunkCount; i++) {
        if (gMapChunks[i].state == 1 || all) {
            gMapChunks[i].opaqueList = renderEntryListSortByDistance(gMapChunks[i].opaqueList, x, y, z, &gMapChunks[i].opaqueTail);
            gMapChunks[i].translucentList = renderEntryListSortByDistance(gMapChunks[i].translucentList, x, y, z, &gMapChunks[i].translucentTail);
        }
    }
}

void mapChunkResolveNodeAssets(void) {
    s32 i;

    for (i = 0; i < gMapChunkCount; i++) {
        modelNodeListSyncFlags(gMapChunks[i].opaqueList);
        modelNodeListSyncFlags(gMapChunks[i].translucentList);
    }
}

void mapChunkBuildSpriteChains(f32 x, f32 y, f32 z, u8 all) {
    s32 i;

    for (i = 0; i < gMapChunkCount; i++) {
        if (gMapChunks[i].state == 1 || all) {
            if (gMapChunks[i].noSprites != 0) {
                gMapChunks[i].sprites = NULL;
            } else {
                gMapChunks[i].sprites = spriteListBuildDisplayChain(gMapChunks[i].opaqueList, gMapChunks[i].translucentList, x, y, z);
            }
        }
    }
}



void mapChunkUpdateModelNodes(void) {
    u8 flag;
    s32 i;
    RenderEntry *node;
    RenderEntry *next;

    gCsModelUpdateCount = 0;
    for (i = 0; i < gMapChunkCount; i++) {
        if (gMapChunks[i].playerMask != 0) {
            flag = 1;
        } else {
            flag = 0;
        }
        node = gMapChunks[i].opaqueList;
        while (node != NULL) {
            next = node->next;
            modelPendingQueueInsert(node, flag);
            node = next;
        }
    }
}



u8 mapChunkCheckActorCollision(Actor *actor, f32 x, f32 z, f32 y, f32 *outFloorY) {
    RenderEntry *node;
    s32 i;
    u8 pad;
    u8 mode;
    u8 result;
    s16 gx;
    s16 gz;

    result = 0;
    mode = renderEntryIsTranslucent(1, 0);
    i = 0;
    if (gMapChunkCount > 0) {
        gx = x * 6.0f;
        do {
            if ((gx >= gMapChunks[i].minX - 0x32) &&
                ((gz = z * 6.0f) >= gMapChunks[i].minZ - 0x32) &&
                (gMapChunks[i].maxX + 0x32 >= gx) &&
                (gMapChunks[i].maxZ + 0x32 >= gz)) {
                switch (mode) {
                case 0:
                    node = gMapChunks[i].opaqueList;
                    break;
                case 1:
                    node = gMapChunks[i].translucentList;
                    break;
                }
                if (node != NULL) {
                    do {
                        if (node->type == 1) {
                            result |= collisionTestDynamicActorFloor(actor, node->modelId, x, z, y, outFloorY);
                        }
                        node = node->next;
                    } while (node != NULL);
                }
            }
            i++;
        } while (i < gMapChunkCount);
    }
    return result;
}

s32 mapPointIsInRenderedChunk(f32 x, f32 y, f32 z) {
    s16 *pad;
    s32 i = 0;
    s16 chunk;

    if (gMapChunkCount == 0) {
        return 0xFF;
    }
    chunk = mapChunkFindByPosition(x, y, z, 0);
    while (i < sMapVisibleChunkCount) {
        if (chunk == sMapVisibleChunks[i]) {
            return 1;
        } else {
            i++;
        }
    }
    return 0;
}

u8 mapChunkIsVisible(s16 chunk) {
    s32 result;

    if (gMapChunkCount == 0) {
        return 0xFF;
    }
    if (gMapChunks[chunk].playerMask != 0) {
        result = 1;
    } else {
        result = 0;
    }
    return result;
}

u8 mapChunkIsActive(s16 chunk) {
    s32 result;

    if (gMapChunkCount == 0) {
        return 0xFF;
    }
    if (gMapChunks[chunk].state == 1) {
        result = 1;
    } else {
        result = 0;
    }
    return result;
}

u8 mapChunkIsVisibleForPlayer(s16 player, s16 chunk) {
    s32 result;

    if (gMapChunkCount == 0) {
        return 1;
    }
    if (gMapChunks[chunk].playerMask & (1 << player)) {
        result = 1;
    } else {
        result = 0;
    }
    return result;
}

s16 mapChunkFindAtPoint(f32 x, f32 y, f32 z, s16 hint) {
    s16 cell;

    mapCellFindAtPoint(x, y, z, hint, -1, &cell);
    return cell;
}

typedef struct MapBox {
    /* 0x00 */ s16 minX;
    /* 0x02 */ s16 minY;
    /* 0x04 */ s16 minZ;
    /* 0x06 */ s16 maxX;
    /* 0x08 */ s16 maxY;
    /* 0x0A */ s16 maxZ;
} MapBox;

void mapCellFindAtPoint(f32 x, f32 y, f32 z, s16 chunk, s16 parent, s16 *outCell) {
    s32 i;
    s16 id;
    MapBox *box;

    i = 0;
    if (gMapCellCount > 0) {
        do {
            if (chunk != gMapCells[i].chunk) {
                continue;
            } else if (parent != gMapCells[i].parent) {
                continue;
            } else {
                id = gMapCells[i].id;
            }
            box = gMapCellBoxes;
            box += id;
            if (!((box->minX <= x) && (x <= box->maxX))) {
                continue;
            }
            if ((box->minY <= y) && (y <= box->maxY) && (box->minZ <= z) && (z <= box->maxZ)) {
                *outCell = id;
                mapCellFindAtPoint(x, y, z, chunk, id, outCell);
            }
        } while (++i < gMapCellCount);
    }
}

typedef struct {
    /* 0x0 */ s16 id;
    /* 0x2 */ u8 pad2[2];
    /* 0x4 */ f32 dist;
} MapChunkCandidate;

s16 mapChunkFindByPosition(f32 x, f32 y, f32 z, s16 hint) {
    s32 best;
    s32 count;
    u8 flag;
    f32 dist;
    MapChunkCandidate cand[50];
    f32 bestDist;
    s32 i;
    s32 pad2;
    s32 found;

    count = 0;
    if (gMapChunkCount == 0) {
        return -1;
    }
    x *= 6.0f;
    y *= 6.0f;
    z *= 6.0f;
    if (mapChunkFindNodeAtPoint(x, y, z, hint, &flag, &dist) != 0) {
        if (flag == 0) {
            return hint;
        }
        cand[0].id = hint;
        count = 1;
        cand[0].dist = dist;
    }
    found = 0;
    i = 0;
    if (gMapChunkCount > 0) {
        do {
            if (hint != i) {
                if (mapChunkFindNodeAtPoint(x, y, z, i, &flag, &dist) != 0) {
                    if (flag == 0) {
                        found = 1;
                    } else {
                        cand[count].id = i;
                        cand[count].dist = dist;
                        count++;
                        i++;
                    }
                } else {
                    i++;
                }
            } else {
                i++;
            }
        } while (found == 0 && i < gMapChunkCount);
    }
    if (found != 0) {
        return i;
    }
    bestDist = cand[0].dist;
    if (count == 0) {
        return hint;
    }
    best = cand[0].id;
    for (i = 0; i < count; i++) {
        if (mapFloorHeightIsBetter(bestDist, cand[i].dist, y) != 0) {
            bestDist = cand[i].dist;
            best = cand[i].id;
        }
    }
    return best;
}

s32 mapFloorHeightIsBetter(f32 curY, f32 candY, f32 refY) {
    s32 curOk;
    s32 candOk;
    f32 curDiff;
    f32 candDiff;

    if (curY <= refY) {
        curOk = 1;
    } else if ((curY - refY) < 60.0f) {
        curOk = 1;
    } else {
        curOk = 0;
    }
    if (candY <= refY) {
        candOk = 1;
    } else if ((candY - refY) < 60.0f) {
        candOk = 1;
    } else {
        candOk = 0;
    }
    if (curOk == 0 && candOk == 0) {
        return 0;
    }
    if (candOk == 0) {
        return 0;
    }
    if (curOk == 0) {
        return 1;
    }
    if (refY < curY) {
        curDiff = curY - refY;
    } else {
        curDiff = refY - curY;
    }
    if (refY < candY) {
        candDiff = candY - refY;
    } else {
        candDiff = refY - candY;
    }
    if (curDiff < candDiff) {
        return 0;
    }
    return 1;
}

typedef struct MapCollisionNode {
    /* 0x00 */ s16 x0;
    /* 0x02 */ s16 x1;
    /* 0x04 */ s16 x2;
    /* 0x06 */ s16 y0;
    /* 0x08 */ s16 y1;
    /* 0x0A */ s16 y2;
    /* 0x0C */ s16 z0;
    /* 0x0E */ s16 z1;
    /* 0x10 */ s16 z2;
    /* 0x12 */ u8 flags;
    /* 0x13 */ u8 pad13[1];
} MapCollisionNode; /* 0x14 */

s32 mapChunkFindNodeAtPoint(f32 x, f32 y, f32 z, s16 chunk, u8 *outBlocked, f32 *outHeight) {
    MapCollisionNode *node;
    MapCollisionNode *end;

    if (x < gMapChunks[chunk].minX) {
        return 0;
    }
    if (z < gMapChunks[chunk].minZ) {
        return 0;
    }
    if (gMapChunks[chunk].maxX < x) {
        return 0;
    }
    if (gMapChunks[chunk].maxZ < z) {
        return 0;
    }
    node = gMapChunks[chunk].collStart;
    end = gMapChunks[chunk].collEnd;
    if (node != end) {
        do {
            if ((mapNodeBoxContainsPoint(node, x, z) != 0) && (mapNodeTriangleContainsPoint(node, x, z) != 0)) {
                if (node->flags & 1) {
                    *outBlocked = 0;
                } else {
                    *outBlocked = 1;
                    *outHeight = node->y0;
                }
                return 1;
            }
            node++;
        } while (node != end);
    }
    return 0;
}

s32 mapNodeBoxContainsPoint(MapCollisionNode *box, f32 x, f32 z) {
    f32 z2;
    f32 x2;
    f32 minX;
    f32 minZ;
    f32 maxX;
    f32 maxZ;
    s16 z0;
    s16 z1;
    s16 x1;
    s16 x0;

    x0 = box->x0; x1 = box->x1; // LAYOUT: same line lets as1 issue the x1 load first
    if (x0 < x1) {
        minX = x0;
    } else {
        minX = x1;
    }
    x2 = box->x2;
    if (!(minX < x2)) {
        minX = x2;
    }
    if (x < minX) {
        return 0;
    }
    z0 = box->z0;
    z1 = box->z1;
    if (z0 < z1) {
        minZ = z0;
    } else {
        minZ = z1;
    }
    z2 = box->z2;
    if (!(minZ < z2)) {
        minZ = z2;
    }
    if (z < minZ) {
        return 0;
    }
    if (x1 < x0) {
        maxX = x0;
    } else {
        maxX = x1;
    }
    if (!(x2 < maxX)) {
        maxX = x2;
    }
    if (maxX < x) {
        return 0;
    }
    if (z1 < z0) {
        maxZ = z0;
    } else {
        maxZ = z1;
    }
    if (!(z2 < maxZ)) {
        maxZ = z2;
    }
    if (maxZ < z) {
        return 0;
    }
    return 1;
}

u8 mapNodeTriangleContainsPoint(MapCollisionNode *tri, f32 x, f32 z) {
    f64 cz;
    f64 mx;
    f64 cx;
    f64 tz; // z term: midpoint z of edge 1-2, then the side product (z - oz) * dx
    f64 dx;
    f64 dz;
    f64 ox;
    f64 oz;
    f64 c;
    f64 crossX;
    u16 flag;
    s32 i;

    flag = 0;
    mx = (tri->x2 + tri->x1) * 0.5;
    tz = (tri->z2 + tri->z1) * 0.5;
    cx = (tri->x0 + mx) * 0.5;
    cz = (tri->z0 + tz) * 0.5;
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
        crossX = (x - ox) * dz;
        tz = (z - oz) * dx;
        c = (cx - ox) * dz - (cz - oz) * dx;
        if ((tz <= crossX ? 1 : -1) != (c >= 0.0 ? 1 : -1)) {
            flag = 1;
        }
    }
    return flag == 0;
}

extern PlayerStruct *gPlayerSlots;
extern u8 gCurrentPlayerIndex;

void mapChunkActivate(s16 chunkIndex) {
    gMapChunks[chunkIndex].state = 1;
    gMapChunks[chunkIndex].playerMask |= 1 << gCurrentPlayerIndex;
    gMapChunks[chunkIndex].clipLeft = gPlayerSlots[gCurrentPlayerIndex].rect[0];
    gMapChunks[chunkIndex].clipTop = gPlayerSlots[gCurrentPlayerIndex].rect[1];
    gMapChunks[chunkIndex].clipRight = gPlayerSlots[gCurrentPlayerIndex].rect[2];
    gMapChunks[chunkIndex].clipBottom = gPlayerSlots[gCurrentPlayerIndex].rect[3];
}


void mapChunkSetIndexOverride(s8 fromActor) {
    sMapCamChunkFromActor = fromActor;
}

extern PlanePoly gFrustumPlanes[];
extern u8 gGfxBufferIndex;
extern f32 gViewFov;
extern f32 gViewAspect;
extern u8 sMapVisiblePortalCount;

void mapChunkFrameUpdate(f32 x, f32 y, f32 z) {
    gPlayerSlots[gCurrentPlayerIndex].camChunk = mapChunkFindByPosition(x, y, z, gPlayerSlots[gCurrentPlayerIndex].camChunk);
    if (sMapCamChunkFromActor != 0) {
        gPlayerSlots[gCurrentPlayerIndex].camChunk = gPlayerSlots[gCurrentPlayerIndex].actor->chunkIndex;
    }
    mapUpdateFogDistance(&gPlayerSlots[gCurrentPlayerIndex].farClip, gPlayerSlots[gCurrentPlayerIndex].camChunk);
    gMapFogDist = gPlayerSlots[gCurrentPlayerIndex].farClip;
    frustumCalculateCornerRays(gViewFov, gViewAspect, gMapFogDist);
    frustumCornersTransformByInverse(&gPlayerSlots[gCurrentPlayerIndex].viewMtx[gGfxBufferIndex]);
    frustumOrientPolyNormals(x, y, z, gFrustumPlanes, gFrustumCorners[0]);
    mapChunkClearBounds();
    mapChunkActivate(gPlayerSlots[gCurrentPlayerIndex].camChunk);
    mapTriggerCollectZonesAtPoint(x, y, z);
    sMapVisibleChunkCount = 0;
    sMapVisiblePortalCount = 0;
    mapChunkTraversePortals(gPlayerSlots[gCurrentPlayerIndex].camChunk, 0, gPlayerSlots[gCurrentPlayerIndex].rect[0], gPlayerSlots[gCurrentPlayerIndex].rect[1], gPlayerSlots[gCurrentPlayerIndex].rect[2], gPlayerSlots[gCurrentPlayerIndex].rect[3], x, y, z);
    mapChunkRenderNodes(x, y, z);
    effectWaterUpdateMeshes(x, y, z, gCurrentPlayerIndex);
    actorCalculateTargetDistancesAndAngles(x, y, z);
    mapChunksApplyLights(x, y, z);
}


u8 *mapChunkLoadAssetRefs(u8 *cmd, u8 *end, s16 limit) {
    s32 count;
    s32 kind;
    s32 addr;

    count = 0;
    if ((cmd != end) && (limit > 0)) {
        do {
            kind = *(u32 *)cmd >> 0x18;
            switch (kind) {
            case 0xFD:
                if (((u32)(*(s32 *)(cmd + 4) * 0x10) >> 0x1C) == 0) {
                    addr = *(s32 *)(cmd + 4);
                    *(void **)(cmd + 4) = assetLoad(0x19, addr, 0, 0);
                    count++;
                }
                break;
            }
            cmd += 8;
        } while ((cmd != end) && (count < limit));
    }
    return cmd;
}



void mapChunkReleaseAssets(u8 *cmd, u8 *end) {
    s32 pad[2];
    s32 node;
    s32 orig;
    u32 addr;
    u32 op;

    if (cmd != end) {
        do {
            op = *(u32 *)cmd >> 0x18;
            switch (op) {
            case 0xFD:
                addr = *(u32 *)(cmd + 4);
                if ((addr >= 0x80000000U) && (addr < 0xA0000000U)) {
                    assetRefBstLookupByHash(addr, &node, &orig);
                    assetFreeBuffer((void *)*(u32 *)(cmd + 4), 0x542, 0x22);
                    *(u32 *)(cmd + 4) = orig;
                }
                break;
            }
            cmd += 8;
        } while (cmd != end);
    }
}

void mapChunkRequestStreaming(s16 chunk) {
    gMapChunks[chunk].streamFlags |= 8;
}

extern u32 gGlobalCutsceneFlags;

void mapChunkUpdateAssetStreaming(void) {
    s32 i;
    s32 j;
    s8 buf[0x10];
    u8 flags[0x34];
    s8 idx;
    s16 n;

    if (!(gGlobalCutsceneFlags & 0x100)) {
        for (i = 0; i < gMapChunkCount; i++) {
            flags[i] = 0;
        }
        for (i = 0; i < gMapChunkCount; i++) {
            if (gMapChunks[i].playerMask != 0) {
                flags[i] = 1;
                gMapChunks[i].lastSeenFrame = gFrameCounter;
                if (!(gMapChunks[i].streamFlags & 4)) {
                    gMapChunks[i].loadCursor = mapChunkLoadAssetRefs(gMapChunks[i].loadCursor, gMapChunks[i].loadEnd, 0x270F);
                    gMapChunks[i].streamFlags |= 4;
                    gMapChunks[i].streamFlags &= ~3;
                }
                n = mapPortalCollectTargets(i, buf, 0x10);
                for (j = 0; j < n; j++) {
                    idx = buf[j];
                    if (flags[idx] == 0) {
                        if (gMapChunks[idx].playerMask == 0) {
                            if (!(gMapChunks[idx].streamFlags & 4)) {
                                gMapChunks[idx].loadCursor = mapChunkLoadAssetRefs(gMapChunks[idx].loadCursor, gMapChunks[idx].loadEnd, 5);
                                if (gMapChunks[idx].loadCursor == gMapChunks[idx].loadEnd) {
                                    gMapChunks[idx].streamFlags &= ~2;
                                    gMapChunks[idx].streamFlags |= 4;
                                } else {
                                    gMapChunks[idx].streamFlags |= 2;
                                }
                                gMapChunks[idx].streamFlags &= ~1;
                            }
                            flags[idx] = 1;
                        }
                    }
                }
            }
        }
        for (i = 0; i < gMapChunkCount; i++) {
            if (flags[i] == 0) {
                if (gMapChunks[i].streamFlags & 8) {
                    if (!(gMapChunks[i].streamFlags & 4)) {
                        gMapChunks[i].loadCursor = mapChunkLoadAssetRefs(gMapChunks[i].loadCursor, gMapChunks[i].loadEnd, 5);
                        if (gMapChunks[i].loadCursor == gMapChunks[i].loadEnd) {
                            gMapChunks[i].streamFlags &= ~2;
                            gMapChunks[i].streamFlags |= 4;
                        } else {
                            gMapChunks[i].streamFlags |= 2;
                        }
                        gMapChunks[i].streamFlags &= ~1;
                    }
                } else if (!(gMapChunks[i].streamFlags & 1) && (gFrameCounter - gMapChunks[i].lastSeenFrame) >= 3U) {
                    mapChunkReleaseAssets(gMapChunks[i].loadStart, gMapChunks[i].loadCursor);
                    gMapChunks[i].loadCursor = gMapChunks[i].loadStart;
                    gMapChunks[i].streamFlags |= 1;
                    gMapChunks[i].streamFlags &= ~6;
                }
            }
            gMapChunks[i].streamFlags &= ~8;
        }
    }
}


void mapChunkRenderNodes(f32 x, f32 y, f32 z) {
    s32 i;

    mapChunkBuildClipFrusta(x, y, z);
    for (i = 0; i < gMapCellCount; i++) {
        gMapCells[i].visible = 0;
    }
    mapCellUpdateVisibility(x, y, z, -1);
    mapTriggerApplyZones(x, y, z);
}

extern f32 gViewFarClip;
extern PlanePoly sMapSelectedChunkFrustum[];

void mapChunkBuildClipFrusta(f32 x, f32 y, f32 z) {
    f32 viewMtx[4][4];
    f32 invMtx[4][4];
    s32 i;
    f32 corners[4][3];

    frustumCalculateCornerRays(gViewFov, gViewAspect, gViewFarClip);
    guMtxL2F(viewMtx, &gPlayerSlots[gCurrentPlayerIndex].viewMtx[gGfxBufferIndex]);
    matrix4Invert(invMtx, viewMtx);
    for (i = 0; i < gMapChunkCount; i++) {
        if (gMapChunks[i].state == 1) {
            mapScreenRectBuildFrustum(gMapChunks[i].clipLeft, gMapChunks[i].clipTop, gMapChunks[i].clipRight, gMapChunks[i].clipBottom,
                          x, y, z, gCurrentPlayerIndex, invMtx, &gMapChunks[i].frustum[0], corners);
            if (i == gMapChunkFrustumCaptureIndex) {
                memcpy(sMapSelectedChunkFrustum, &gMapChunks[i].frustum[0], sizeof(gMapChunks[i].frustum));
            }
        }
    }
}

typedef struct FrustumCorners {
    /* 0x00 */ f32 c0x;
    /* 0x04 */ f32 c0y;
    /* 0x08 */ f32 c0z;
    /* 0x0C */ f32 c1x;
    /* 0x10 */ f32 c1y;
    /* 0x14 */ f32 c1z;
    /* 0x18 */ f32 c2x;
    /* 0x1C */ f32 c2y;
    /* 0x20 */ f32 c2z;
    /* 0x24 */ f32 c3x;
    /* 0x28 */ f32 c3y;
    /* 0x2C */ f32 c3z;
} FrustumCorners;

extern FrustumCorners sFrustumCornerRays;
void mapScreenRectBuildFrustum(s32 left, s32 top, s32 right, s32 bottom, f32 x, f32 y, f32 z, u8 player, f32 (*mtx)[4], PlanePoly *planes, f32 (*out)[3]) {
    s32 i;
    f32 q;
    f32 x0;
    f32 x1;
    f32 y0;
    f32 y1;
    f32 m[4][3];

    q = ((f32)(left - gPlayerSlots[player].rect[0])) / (f32)gPlayerSlots[player].rectWidth;
    x0 = (q * (sFrustumCornerRays.c1x - sFrustumCornerRays.c0x)) + sFrustumCornerRays.c0x;
    q = ((f32)(right - gPlayerSlots[player].rect[0])) / (f32)gPlayerSlots[player].rectWidth;
    x1 = (q * (sFrustumCornerRays.c1x - sFrustumCornerRays.c0x)) + sFrustumCornerRays.c0x;
    q = ((f32)(top - gPlayerSlots[player].rect[1])) / (f32)gPlayerSlots[player].rectHeight;
    y0 = ((sFrustumCornerRays.c2y - sFrustumCornerRays.c0y) * q) + sFrustumCornerRays.c0y;
    q = ((f32)(bottom - gPlayerSlots[player].rect[1])) / (f32)gPlayerSlots[player].rectHeight;
    y1 = ((sFrustumCornerRays.c2y - sFrustumCornerRays.c0y) * q) + sFrustumCornerRays.c0y;
    m[0][0] = x1; m[0][1] = y1; m[0][2] = sFrustumCornerRays.c0z;
    m[1][0] = x0; m[1][1] = y1; m[1][2] = sFrustumCornerRays.c1z;
    m[2][0] = x1; m[2][1] = y0; m[2][2] = sFrustumCornerRays.c2z;
    m[3][0] = x0; m[3][1] = y0; m[3][2] = sFrustumCornerRays.c3z;
    for (i = 0; i < 4; i++) {
        guMtxXFMF(mtx, m[i][0], m[i][1], m[i][2], &out[i][0], &out[i][1], &out[i][2]);
    }
    frustumOrientPolyNormals(x, y, z, planes, out[0]);
}

typedef struct MapTriangle {
    /* 0x00 */ s16 x0;
    /* 0x02 */ s16 x1;
    /* 0x04 */ s16 x2;
    /* 0x06 */ s16 y0;
    /* 0x08 */ s16 y1;
    /* 0x0A */ s16 y2;
    /* 0x0C */ s16 z0;
    /* 0x0E */ s16 z1;
    /* 0x10 */ s16 z2;
} MapTriangle;




void mapTriggerCollectZonesAtPoint(f32 x, f32 y, f32 z) {
    s32 pad[10];
    MapZone **p;
    MapZone *zone;
    MapTriangle *tri;
    s32 i;
    s32 j;
    s32 k;
    s32 n;
    s32 found;
    f32 h;

    sMapActiveZoneCount = 0;
    sMapBlockedPortalCount = 0;
    for (p = gMapZones, i = 0; i != 0x20; i++) {
        if (*p != NULL) {
            zone = *p;
            if (zone->minY <= y && y <= zone->maxY + zone->height) {
                tri = (MapTriangle *)zone->tris;
                for (j = 0; j < zone->triCount; j++, tri++) {
                    if (mapTriangleBoundsContainPoint(tri, x, z) != 0 && mapTriangleContainsPoint(tri, x, z) != 0) {
                        h = mapTriangleHeightAtPoint(tri, x, z);
                        if (h <= y && y <= zone->height + h) {
                            if (sMapActiveZoneCount != 0x10) {
                                sMapActiveZones[sMapActiveZoneCount] = i;
                                sMapActiveZoneCount++;
                            }
                            for (k = 0; k < zone->linkCount; k++) {
                                found = 0;
                                n = 0;
                                while (!found && n < sMapBlockedPortalCount) {
                                    if (sMapBlockedPortals[n] == zone->links[k]) {
                                        found = 1;
                                    } else {
                                        n++;
                                    }
                                }
                                if (!found && n != 0x10) {
                                    sMapBlockedPortals[sMapBlockedPortalCount] = zone->links[k];
                                    sMapBlockedPortalCount++;
                                }
                            }
                        }
                    }
                }
            }
        }
        p++;
    }
}




void mapTriggerApplyZones(f32 x, f32 y, f32 z) {
    s32 i;
    s32 j;
    s32 done;
    s16 *val;
    MapZone *zone;
    u8 idx;

    done = 0;
    for (i = 0; i < sMapActiveZoneCount; i++) {
        idx = sMapActiveZones[i];
        if (gMapZones[idx] != NULL) {
            zone = gMapZones[idx];
            if (!done) {
                if (zone->enterCount != 0) {
                    done = 1;
                    val = zone->enterCells;
                    for (j = 0; j < gMapCellCount; j++) {
                        gMapCells[j].visible = 0;
                    }
                    for (j = 0; j < zone->enterCount; j++) {
                        mapCellSetFlag(*val, 1);
                        val++;
                    }
                } else {
                    val = zone->exitCells;
                    if (!zone->enterCount) {} // FAKE: dead re-test of the u8 count makes uopt colour its load to $v1 (never emitted), ending ugen's v1 == zone copy so val is built from s2 at 0x3cb0
                    for (j = 0; j < zone->exitCount; j++) {
                        mapCellSetFlag(*val, 0);
                        val++;
                    }
                }
            }
        }
    }
}

void mapCellSetFlag(s32 id, u8 visible) {
    s32 i;
    s32 found;

    i = 0;
    found = 0;
    while (!found && i < gMapCellCount) {
        if (id == gMapCells[i].id) {
            gMapCells[i].visible = visible;
            if (visible != 0) {
                gMapCells[i].seen = 1;
            }
            found = 1;
        }
        i++;
    }
    for (i = 0; i < gMapCellCount; i++) {
        if (id == gMapCells[i].parent) {
            mapCellSetFlag(gMapCells[i].id, visible);
        }
    }
}

f32 mapTriangleHeightAtPoint(MapTriangle *tri, f32 x, f32 z) {
    f32 ret;
    f64 e1y;
    f64 e1x;
    f64 d;
    f64 e2x;
    f64 e2y;
    f64 t;
    f64 e1z;
    f64 nx;
    f64 ny;
    f64 e2z;

    e1x = tri->x0 - tri->x1;
    e1y = tri->y0 - tri->y1;
    e1z = tri->z0 - tri->z1;
    e2x = tri->x0 - tri->x2;
    e2y = tri->y0 - tri->y2;
    e2z = tri->z0 - tri->z2;
    nx = e1y * e2z - e1z * e2y;
    ny = e1z * e2x - e1x * e2z;
    d = -(tri->z1 * (e1x * e2y - e1y * e2x) + (nx * tri->x1 + ny * tri->y1));
    if (ny * 2000.0 > 0.01 || ny * 2000.0 < -0.01) {
        t = nx * x + ny * -1000.0 + (e1x * e2y - e1y * e2x) * z + d;
        t = t / (ny * 2000.0);
        if (t < 0.0) {
            t = 0.0 - t;
        }
        ret = 2000.0 * t - 1000.0;
    } else {
        ret = -32768.0f;
    }
    return ret;
}

s32 mapTriangleBoundsContainPoint(MapTriangle *tri, f32 x, f32 z) {
    f32 minX;
    f32 maxX;
    f32 minZ;
    f32 maxZ;

    minX = (tri->x0 < tri->x1) ? (f32)tri->x0 : (f32)tri->x1;
    minX = (minX < (f32)tri->x2) ? minX : (f32)tri->x2;
    minZ = (tri->z0 < tri->z1) ? (f32)tri->z0 : (f32)tri->z1;
    minZ = (minZ < (f32)tri->z2) ? minZ : (f32)tri->z2;
    maxX = (tri->x0 > tri->x1) ? (f32)tri->x0 : (f32)tri->x1;
    maxX = (maxX > (f32)tri->x2) ? maxX : (f32)tri->x2;
    maxZ = (tri->z0 > tri->z1) ? (f32)tri->z0 : (f32)tri->z1;
    maxZ = (maxZ > (f32)tri->z2) ? maxZ : (f32)tri->z2;
    if (x < minX || x > maxX || z < minZ || z > maxZ) {
        return 0;
    }
    return 1;
}

u8 mapTriangleContainsPoint(MapTriangle *tri, f32 x, f32 z) {
    f64 cz;
    f64 mx;
    f64 cx;
    f64 tz; // z term: midpoint z of edge 1-2, then the side product (z - oz) * dx
    f64 dx;
    f64 dz;
    f64 ox;
    f64 oz;
    f64 c;
    f64 crossX;
    u16 flag;
    s32 i;

    flag = 0;
    mx = (tri->x2 + tri->x1) * 0.5;
    tz = (tri->z2 + tri->z1) * 0.5;
    cx = (tri->x0 + mx) * 0.5;
    cz = (tri->z0 + tz) * 0.5;
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
        crossX = (x - ox) * dz;
        tz = (z - oz) * dx;
        c = (cx - ox) * dz - (cz - oz) * dx;
        if ((tz <= crossX ? 1 : -1) != (c >= 0.0 ? 1 : -1)) {
            flag = 1;
        }
    }
    return flag == 0;
}


void mapCellUpdateVisibility(f32 x, f32 y, f32 z, s32 parent) {
    s32 idx;
    s32 i;

    for (i = 0; i < gMapCellCount; i++) {
        if (parent == gMapCells[i].parent) {
            if (gMapChunks[gMapCells[i].chunk].state == 1) {
                idx = gMapCells[i].id;
                if (mapBspBoxInFrustum(gMapCellBoxes[idx].minX, gMapCellBoxes[idx].minY, gMapCellBoxes[idx].minZ,
                                  gMapCellBoxes[idx].maxX, gMapCellBoxes[idx].maxY, gMapCellBoxes[idx].maxZ,
                                  x, y, z, gViewFarClip,
                                  &gMapChunks[gMapCells[i].chunk].frustum[0]) != 0) {
                    gMapCells[i].visible = 1;
                    gMapCells[i].seen = 1;
                }
                if (gMapCells[i].visible != 0) {
                    mapCellUpdateVisibility(x, y, z, gMapCells[i].id);
                }
            }
        }
    }
}


extern f32 gLightBaseR;
extern f32 gLightBaseG;
extern f32 gLightBaseB;

void mapChunksApplyLights(f32 x, f32 y, f32 z) {
    s32 i;
    s32 lightCount;
    Vtx *cellVtx;
    u8 *src;
    s16 key;
    s32 pad0;
    MapChunkCell *node;
    s16 boxIdx;
    s32 j;
    s32 k;
    s32 nodeIdx;
    s32 found;
    u8 hit;
    s32 pad1;
    u8 pad2;
    u8 flag;
    flag = 0;
    matrixCacheResetStats();
    lightClearActiveCount();
    for (i = 0; i < gMapChunkCount; i++) {
        if ((gMapChunks[i].lightMode != 0) && (gMapChunks[i].state == 1) && (gMapChunks[i].lightsDone == 0)) {
            gMapChunks[i].lightsDone = 1;
            if (gMapChunks[i].kind == 2) {
                flag = 0;
                for (k = 0; k < gMapCellCount; k++) {
                    if ((i == gMapCells[k].chunk) && (gMapCells[k].seen != 0)) {
                        for (j = 0; j < 2; j++) {
                            if (gMapCells[k].vtxCount[j] != 0) {
                                boxIdx = gMapCells[k].id;
                                lightCount = lightCollectVolumesInBounds(x, y, z, gMapCellBoxes[boxIdx].minX, gMapCellBoxes[boxIdx].minY, gMapCellBoxes[boxIdx].minZ, gMapCellBoxes[boxIdx].maxX, gMapCellBoxes[boxIdx].maxY, gMapCellBoxes[boxIdx].maxZ, i, &hit);
                                nodeIdx = 0;
                                found = 0;
                                key = gMapCells[k].id; node = gMapChunks[i].cells;  // LAYOUT: same-line statements steer scheduling
                                do {
                                    if (key == node->id) {
                                        found = 1;
                                    } else {
                                        nodeIdx++;
                                        node++;
                                    }
                                } while (found == 0);
                                if (gGlobalPauseFlags & 0x10) {
                                    gMapChunks[i].cells[nodeIdx].vtx[j] = matrixCacheLookup(lightCount, i, boxIdx, j);
                                    if (gMapChunks[i].cells[nodeIdx].vtx[j] == NULL) {
                                        gMapChunks[i].cells[nodeIdx].vtx[j] = matrixCacheInsert(lightCount, i, boxIdx, j, gMapCells[k].vtxCount[j], hit);
                                        src = gMapChunks[i].baseVtx + gMapCells[k].vtxOffset[j] * 0x10;
                                        memcpy(gMapChunks[i].cells[nodeIdx].vtx[j], src, gMapCells[k].vtxCount[j] * 0x10);
                                        cellVtx = gMapChunks[i].cells[nodeIdx].vtx[j];
                                        gLightBaseR = gChunkLightR[i];
                                        gLightBaseG = gChunkLightG[i];
                                        gLightBaseB = gChunkLightB[i];
                                        lightApplyToVertices((s32)cellVtx, (s32)(cellVtx + gMapCells[k].vtxCount[j]), 1, gLightCandidates, lightCount, gMapChunks[i].lightMode == 1);
                                    }
                                }
                            }
                        }
                    }
                }
            } else {
                if (flag == 0) {
                    lightCount = lightCollectVolumesInBounds(x, y, z, -0x8000, -0x8000, -0x8000, -0x8000, -0x8000, -0x8000, -1, &hit);
                    flag = 1;
                }
                if (gMapChunks[i].litVtx[gGfxBufferIndex] == NULL) {
                    gMapChunks[i].litVtx[gGfxBufferIndex] = heapAlloc(gMapChunks[i].vtxSize);
                }
                memcpy(gMapChunks[i].litVtx[gGfxBufferIndex], gMapChunks[i].baseVtx, gMapChunks[i].vtxSize);
                gLightBaseR = gChunkLightR[i];
                gLightBaseG = gChunkLightG[i];
                gLightBaseB = gChunkLightB[i];
                if (gGlobalPauseFlags & 0x10) {
                    lightApplyToVertices((s32)gMapChunks[i].litVtx[gGfxBufferIndex], (s32)((u8 *)gMapChunks[i].litVtx[gGfxBufferIndex] + gMapChunks[i].vtxSize), 1, gLightCandidates, lightCount, gMapChunks[i].lightMode == 1);
                }
            }
            gMapChunks[i].curVtx = gMapChunks[i].litVtx[gGfxBufferIndex];
        }
    }
    effectWaterApplyLights(x, y, z);
}




void mapChunkFreeIdleBuffers(void) {
    s32 i;

    if (gMapHasCellLitChunks != 0) {
        matrixCacheEvict(0, 0x190);
    }
    for (i = 0; i < gMapChunkCount; i++) {
        if (gMapChunks[i].lightMode != 0 && gMapChunks[i].kind != 2 && gMapChunks[i].lightsDone == 0) {
            if (gMapChunks[i].litVtx[gGfxBufferIndex] != NULL) {
                heapFree(gMapChunks[i].litVtx[gGfxBufferIndex]);
                gMapChunks[i].litVtx[gGfxBufferIndex] = NULL;
            }
        }
    }
}

void mapChunkReleaseAndAdvance(void) {
    RenderEntry *node;

    if (!mapChunkIsVisible(sMapChunkReleaseCursor)) {
        for (node = gMapChunks[sMapChunkReleaseCursor].opaqueList; node != NULL; node = node->next) {
            modelSlotFreeTexAnimBuffers(node->object, node->type);
            modelSlotFreeAssetTextures(node->object, node->type);
        }
        for (node = gMapChunks[sMapChunkReleaseCursor].translucentList; node != NULL; node = node->next) {
            modelSlotFreeTexAnimBuffers(node->object, node->type);
            modelSlotFreeAssetTextures(node->object, node->type);
        }
    }
    sMapChunkReleaseCursor++;
    if (gMapChunkCount == sMapChunkReleaseCursor) {
        sMapChunkReleaseCursor = 0;
    }
}


s32 mapPortalChunkStackContains(s16 id, s32 count) {
    s32 i;

    i = 0;
    while (i < count) {
        if (id == sMapPortalChunkStack[i]) {
            return 1;
        } else {
            i++;
        }
    }
    return 0;
}

extern s16 sMapVisiblePortals[];




extern u8 gMapFirstViewPending;
extern void *gMapDisplayListBase;
extern u8 gRenderSetupKind;
extern void *gRenderLoadedTexture;
extern struct RenderEntry *gRenderListSorted;
extern Gfx D_2000180;

Gfx *func_80027034(Gfx *);

Gfx *mapChunksRender(Gfx *gfx, MapBspNode *view, f32 x, f32 y, f32 z, s32 flags) {
    s32 i;
    s32 idx;
    struct RenderEntry *list;
    u8 flag;

    idx = 0;
    flag = (gMapFirstViewPending != 0) && (gPlayerSlots[gCurrentPlayerIndex].fov == 45.0);
    gDPPipeSync(gfx++);
    if (flags & 0x10) {
        gSPMatrix(gfx++, osVirtualToPhysical(sMapChunkScaleMtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
        gSPSegment(gfx++, 6, osVirtualToPhysical((void *)gMapVtxBase));
        gSPSegment(gfx++, 7, osVirtualToPhysical(gMapDisplayListBase));
        gfx = mapViewDrawPass(gfx, view, 1);
        if (view->dl != -1) {
            gDPPipeSync(gfx++);
            gSPDisplayList(gfx++, osVirtualToPhysical((void *)view->dl));
        }
        gfx = effectWaterRenderSurfaces(gfx, 0, 0);
        for (i = 0; i < sMapVisiblePortalCount; i++) {
            if (gMapPortals[sMapVisiblePortals[i]].dl0 != -1) {
                gDPPipeSync(gfx++);
                gSPDisplayList(gfx++, osVirtualToPhysical((void *)gMapPortals[sMapVisiblePortals[i]].dl0));
            }
            if (gMapPortals[sMapVisiblePortals[i]].dl1 != -1) {
                gDPPipeSync(gfx++);
                gSPDisplayList(gfx++, osVirtualToPhysical((void *)gMapPortals[sMapVisiblePortals[i]].dl1));
            }
        }
        gSPMatrix(gfx++, &D_2000180, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    }
    for (i = sMapVisibleChunkCount - 1; i >= 0; i--) {
        idx = sMapVisibleChunks[i];
        if (gMapChunks[idx].state == 1) {
            if (gMapChunks[idx].texAnimPending != 0) {
                mapChunkAnimateTextures(idx);
                gMapChunks[idx].texAnimPending = 0;
            }
            gDPPipeSync(gfx++);
            gDPSetScissor(gfx++, G_SC_NON_INTERLACE, gMapChunks[idx].clipLeft, gMapChunks[idx].clipTop, gMapChunks[idx].clipRight, gMapChunks[idx].clipBottom);
            mapSetClipBounds(gMapChunks[idx].clipLeft, gMapChunks[idx].clipTop, gMapChunks[idx].clipRight, gMapChunks[idx].clipBottom);
            gfx = fogRender(gfx);
            if (flags & 0x10) {
                gfx = mapChunkEmitSegmentCommands(gfx, idx);
                if (gMapChunks[idx].layerDl0 != -1) {
                    gSPMatrix(gfx++, osVirtualToPhysical(sMapChunkScaleMtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
                    gSPSegment(gfx++, 6, osVirtualToPhysical(gMapChunks[idx].curVtx));
                    gSPSegment(gfx++, 7, osVirtualToPhysical(gMapDisplayListBase));
                    gfx = mapChunkEmitLayerDisplayLists(gfx, idx, 0);
                    gDPPipeSync(gfx++);
                    gSPMatrix(gfx++, &D_2000180, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
                }
                if (gMapChunks[idx].layerDl2 != -1) {
                    gSPMatrix(gfx++, osVirtualToPhysical(sMapChunkScaleMtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
                    gSPSegment(gfx++, 6, osVirtualToPhysical(gMapChunks[idx].curVtx));
                    gSPSegment(gfx++, 7, osVirtualToPhysical(gMapDisplayListBase));
                    gfx = mapChunkEmitLayerDisplayLists(gfx, idx, 2);
                    gSPMatrix(gfx++, &D_2000180, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
                }
            }
            gDPPipeSync(gfx++);
            if (!(gGlobalOverlayFlags & 0x01000000)) {
                gfx = billboardRenderQueued(gfx, idx);
            }
            gfx = spriteListRender(gfx, gMapChunks[idx].sprites);
            gRenderSetupKind = 0xFF;
            if (flag) {
                list = gMapChunks[idx].opaqueTail;
            } else {
                list = gMapChunks[idx].opaqueList;
            }
            gfx = renderEntryListBuildDisplayList(gfx, list, x, y, z, flags, idx, flag);
            if (flags & 0x10) {
                gSPClearGeometryMode(gfx++, 0xFFFFFFFF);
                gSPSetGeometryMode(gfx++, 0x200004);
                gfx = fogRender(gfx);
                gfx = mapChunkEmitSegmentCommands(gfx, idx);
                if (gMapChunks[idx].layerDl1 != -1) {
                    gSPMatrix(gfx++, osVirtualToPhysical(sMapChunkScaleMtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
                    gSPSegment(gfx++, 6, osVirtualToPhysical(gMapChunks[idx].curVtx));
                    gSPSegment(gfx++, 7, osVirtualToPhysical(gMapDisplayListBase));
                    gfx = mapChunkEmitLayerDisplayLists(gfx, idx, 1);
                    gSPMatrix(gfx++, &D_2000180, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
                    gDPPipeSync(gfx++);
                }
                if (gMapChunks[idx].layerDl3 != -1) {
                    gSPMatrix(gfx++, osVirtualToPhysical(sMapChunkScaleMtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
                    gSPSegment(gfx++, 6, osVirtualToPhysical(gMapChunks[idx].curVtx));
                    gSPSegment(gfx++, 7, osVirtualToPhysical(gMapDisplayListBase));
                    gfx = mapChunkEmitLayerDisplayLists(gfx, idx, 3);
                    gDPPipeSync(gfx++);
                    gSPMatrix(gfx++, &D_2000180, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
                }
            }
        }
    }
    if (flags & 0x10) {
        gSPMatrix(gfx++, osVirtualToPhysical(sMapChunkScaleMtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
        gSPSegment(gfx++, 6, osVirtualToPhysical((void *)gMapVtxBase));
        gSPSegment(gfx++, 7, osVirtualToPhysical(gMapDisplayListBase));
        gfx = mapViewDrawPass(gfx, view, 2);
        if (gGlobalOverlayFlags & 0x1000) {
            gDPPipeSync(gfx++);
            gfx = func_80027034(gfx);
            gSPMatrix(gfx++, osVirtualToPhysical(sMapChunkScaleMtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
        }
        gfx = effectWaterRenderSurfaces(gfx, idx, 1);
        gSPMatrix(gfx++, &D_2000180, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
        gDPPipeSync(gfx++);
        gfx = renderDepthSortedTargets(gfx);
    }
    for (i = sMapVisibleChunkCount - 1; i >= 0; i--) {
        idx = sMapVisibleChunks[i];
        if (gMapChunks[idx].state == 1) {
            gDPPipeSync(gfx++);
            gDPSetScissor(gfx++, G_SC_NON_INTERLACE, gMapChunks[idx].clipLeft, gMapChunks[idx].clipTop, gMapChunks[idx].clipRight, gMapChunks[idx].clipBottom);
            mapSetClipBounds(gMapChunks[idx].clipLeft, gMapChunks[idx].clipTop, gMapChunks[idx].clipRight, gMapChunks[idx].clipBottom);
            gRenderSetupKind = 0xFF;
            if (flag) {
                list = gMapChunks[idx].translucentTail;
            } else {
                list = gMapChunks[idx].translucentList;
            }
            gfx = renderEntryListBuildDisplayList(gfx, list, x, y, z, flags, idx, flag);
            if (gGlobalOverlayFlags & 0x01000000) {
                gfx = billboardRenderQueued(gfx, idx);
            }
        }
    }
    if (flags & 0x10) {
        gSPMatrix(gfx++, osVirtualToPhysical(sMapChunkScaleMtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
        gSPSegment(gfx++, 6, osVirtualToPhysical((void *)gMapVtxBase));
        gSPSegment(gfx++, 7, osVirtualToPhysical(gMapDisplayListBase));
        gfx = mapViewDrawPass(gfx, view, 3);
        gSPMatrix(gfx++, &D_2000180, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
        gDPPipeSync(gfx++);
    }
    gDPPipeSync(gfx++);
    gDPSetScissor(gfx++, G_SC_NON_INTERLACE, gPlayerSlots[gCurrentPlayerIndex].rect[0], gPlayerSlots[gCurrentPlayerIndex].rect[1], gPlayerSlots[gCurrentPlayerIndex].rect[2], gPlayerSlots[gCurrentPlayerIndex].rect[3]);
    mapSetClipBounds(gPlayerSlots[gCurrentPlayerIndex].rect[0], gPlayerSlots[gCurrentPlayerIndex].rect[1], gPlayerSlots[gCurrentPlayerIndex].rect[2], gPlayerSlots[gCurrentPlayerIndex].rect[3]);
    gRenderLoadedTexture = NULL;
    gfx = renderEntryListBuildDisplayList(gfx, gRenderListSorted, x, y, z, flags, -1, 0);
    return billboardRenderQueued(gfx, -1);
}




Gfx *mapChunkEmitLayerDisplayLists(Gfx *gfx, s32 chunk, u8 layer) {
    s32 i;
    s32 found;
    s32 j;

    gDPPipeSync(gfx++);
    if (gMapChunks[chunk].kind != 2) {
        switch (layer) {
        case 0:
            gSPDisplayList(gfx++, osVirtualToPhysical((void *)gMapChunks[chunk].layerDl0));
            break;
        case 1:
            gSPDisplayList(gfx++, osVirtualToPhysical((void *)gMapChunks[chunk].layerDl1));
            break;
        case 2:
            gSPDisplayList(gfx++, osVirtualToPhysical((void *)gMapChunks[chunk].layerDl2));
            break;
        case 3:
            gSPDisplayList(gfx++, osVirtualToPhysical((void *)gMapChunks[chunk].layerDl3));
            break;
        }
    } else {
        for (i = 0; i < gMapChunks[chunk].cellCount; i++) {
            if (gMapChunks[chunk].cells[i].dl[layer] != -1) {
                found = 0;
                j = 0;
                do {
                    if (gMapCells[j].id == gMapChunks[chunk].cells[i].id) {
                        found = 1;
                    } else {
                        j++;
                    }
                } while (found == 0);
                if (gMapCells[j].visible && (gMapChunks[chunk].cells[i].layerMask & (1 << layer))) {
                    gSPSegment(gfx++, 6, osVirtualToPhysical(gMapChunks[chunk].cells[i].vtx[layer]));
                    gDPPipeSync(gfx++);
                    gSPDisplayList(gfx++, osVirtualToPhysical((void *)gMapChunks[chunk].cells[i].dl[layer]));
                    gDPPipeSync(gfx++);
                }
            }
        }
    }
    return gfx;
}

void mapChunkEffectSetFlag(s16 chunk, s16 cellId, u8 layer, u8 set) {
    s32 i;

    for (i = 0; i < gMapChunks[chunk].cellCount; i++) {
        if (cellId == gMapChunks[chunk].cells[i].id) {
            if (set != 0) {
                gMapChunks[chunk].cells[i].layerMask |= 1 << layer;
            } else {
                gMapChunks[chunk].cells[i].layerMask &= ~(1 << layer);
            }
            return;
        }
    }
}


void mapChunkTraversePortals(s16 chunk, s32 depth, s32 left, s32 top, s32 right, s32 bottom, f32 x, f32 y, f32 z) {
    s32 id;
    s32 poly;
    s32 i;
    s32 polyLeft;
    s32 polyTop;
    s32 polyRight;
    s32 polyBottom;
    s32 clipLeft;
    s32 clipTop;
    s32 clipRight;
    s32 clipBottom;
    s32 outLeft;
    s32 outTop;
    s32 outRight;
    s32 outBottom;
    u8 overlap;
    u8 emitted;
    s16 target;
    s32 poly0;
    s32 found;
    s32 k;

    mapVisibleChunkAdd(chunk);
    for (i = 0; i < gMapPortalSlotCount; i++) {
        if ((chunk == gMapPortalSlots[i].chunk) && (mapPortalChunkStackContains(gMapPortalSlots[i].target, depth) == 0)) {
            if (gMapPortalSlots[i].enabled != 0) {
                gMapPortalSlots[i].seen = 1;
                id = i / 2;
                if (mapPortalIsUnblocked(id) != 0) {
                    emitted = mapGridPointEmit(id, x, y, z);
                    if (emitted != 0) {
                        clipLeft = left;
                        clipTop = top;
                        clipRight = right;
                        clipBottom = bottom;
                    } else if (mapGridPointPlaneDistanceWithin(id, x, y, z, gMapPortalSlots[i].maxDist) != 0) {
                        poly0 = mapGridQuadClipToFrustum(id, x, y, z);
                        if (poly0 != 0) {
                            mapPolyProjectToScreenRect(poly0, &polyLeft, &polyTop, &polyRight, &polyBottom);
                            overlap = mapRectOverlapTest(polyLeft, polyTop, polyRight, polyBottom, left, top, right, bottom, &clipLeft, &clipTop, &clipRight, &clipBottom);
                        }
                    } else {
                        poly0 = 0;
                        found = 0;
                        k = 0;
                        while ((found == 0) && (k < gMapPortalCount)) {
                            if ((i == gMapPortals[k].portal) && (gMapPortals[k].target == gMapPortalSlots[i].target)) {
                                found = 1;
                            } else {
                                k++;
                            }
                        }
                        if ((found != 0) && (mapGridPointPlaneDistanceWithin(id, x, y, z, gMapPortals[k].maxDist) != 0)) {
                            poly = mapGridQuadClipToFrustum(id, x, y, z);
                            if (poly != 0) {
                                mapPolyProjectToScreenRect(poly, &polyLeft, &polyTop, &polyRight, &polyBottom);
                                if (mapRectOverlapTest(polyLeft, polyTop, polyRight, polyBottom, left, top, right, bottom, &clipLeft, &clipTop, &clipRight, &clipBottom) != 0) {
                                    mapVisiblePortalAdd(k);
                                }
                            }
                        }
                        if (actorTargetTableHasPortalSlot(i) != 0) {
                            poly = mapGridQuadClipToFrustum(id, x, y, z);
                            if (poly != 0) {
                                mapPolyProjectToScreenRect(poly, &polyLeft, &polyTop, &polyRight, &polyBottom);
                                if (mapRectOverlapTest(polyLeft, polyTop, polyRight, polyBottom, left, top, right, bottom, &clipLeft, &clipTop, &clipRight, &clipBottom) != 0) {
                                    gMapPortalVisible[i] = 1;
                                }
                            }
                        }
                    }
                    if (((poly0 != 0) && (overlap != 0)) || emitted) {
                        gMapPortalVisible[i] = 1;
                        target = gMapPortalSlots[i].target;
                        if (gMapChunkEnabled[target] != 0) {
                            gMapChunks[target].state = 1;
                            gMapChunks[target].playerMask |= 1 << gCurrentPlayerIndex;
                            mapRectIntersect(clipLeft, clipTop, clipRight, clipBottom, gMapChunks[target].clipLeft, gMapChunks[target].clipTop, gMapChunks[target].clipRight, gMapChunks[target].clipBottom, &outLeft, &outTop, &outRight, &outBottom);
                            gMapChunks[target].clipLeft = outLeft;
                            gMapChunks[target].clipTop = outTop;
                            gMapChunks[target].clipRight = outRight;
                            gMapChunks[target].clipBottom = outBottom;
                            sMapPortalChunkStack[depth] = chunk;
                            mapChunkTraversePortals(target, depth + 1, clipLeft, clipTop, clipRight, clipBottom, x, y, z);
                        }
                    }
                }
            }
        }
    }
}


s32 mapPortalIsUnblocked(s32 id) {
    u8 *p = sMapBlockedPortals;

    if (sMapBlockedPortalCount > 0) {
        do {
            if (id == *p) {
                return 0;
            } else {
                p++;
            }
        } while (p < sMapBlockedPortals + sMapBlockedPortalCount);
    }
    return 1;
}


void mapVisiblePortalAdd(s32 id) {
    s32 i = 0;

    while (i < sMapVisiblePortalCount) {
        if (id == sMapVisiblePortals[i]) {
            return;
        }
        i++;
    }
    if (i == 0xC) {
        return;
    }
    sMapVisiblePortals[sMapVisiblePortalCount] = id;
    sMapVisiblePortalCount++;
}


void mapVisibleChunkAdd(s16 id) {
    s32 i = 0;

    while (i < sMapVisibleChunkCount) {
        if (id == sMapVisibleChunks[i]) {
            return;
        }
        i++;
    }
    sMapVisibleChunks[sMapVisibleChunkCount] = id;
    sMapVisibleChunkCount++;
}


typedef struct MapGridQuad {
    /* 0x00 */ f32 x[4];
    /* 0x10 */ f32 y[4];
    /* 0x20 */ f32 px;
    /* 0x24 */ f32 py;
} MapGridQuad;




u8 mapGridPointEmit(s32 tri, f32 x, f32 y, f32 z) {
    f32 d;
    f32 dist;
    f32 px;
    f32 py;
    f32 pz;
    MapGridQuad quad;
    f32 nx;
    f32 ny;
    f32 nz;

    nz = gMapGridTrianglePlanes[tri].nz;
    ny = gMapGridTrianglePlanes[tri].ny;
    nx = gMapGridTrianglePlanes[tri].nx;
    d = gMapGridTrianglePlanes[tri].d;
    dist = (d + (nx * x + ny * y + nz * z)) / gMapGridTrianglePlanes[tri].len;
    if (dist < 0.0) {
        dist = 0.0 - dist;
    }
    if (dist > 80.0) {
        return 0;
    }
    mapGridPlaneProjectPoint(tri, x, y, z, &px, &py, &pz);
    mapGridPointBuildVectors(tri, px, py, pz, &quad);
    if (mapGridQuadContainsPoint(&quad)) {
        return 1;
    }
    return 0;
}

s32 mapGridQuadContainsPoint(MapGridQuad *quad) {
    f32 mx;
    f32 my;
    f32 ex;
    f32 ey;
    f32 vx;
    f32 vy;
    f32 dx;
    f32 dy;
    f32 pad;
    f32 cross2;
    s32 i;

    mx = (quad->x[0] + quad->x[2]) * 0.5;
    my = (quad->y[0] + quad->y[2]) * 0.5;
    for (i = 0; i != 4; i++) {
        switch (i) {
        case 0:
            vx = quad->x[0];
            vy = quad->y[0];
            ex = quad->x[1] - quad->x[0];
            ey = quad->y[1] - quad->y[0];
            break;
        case 1:
            vx = quad->x[1];
            vy = quad->y[1];
            ex = quad->x[2] - quad->x[1];
            ey = quad->y[2] - quad->y[1];
            break;
        case 2:
            vx = quad->x[2];
            vy = quad->y[2];
            ex = quad->x[3] - quad->x[2];
            ey = quad->y[3] - quad->y[2];
            break;
        case 3:
            vx = quad->x[3];
            vy = quad->y[3];
            ex = quad->x[0] - quad->x[3];
            ey = quad->y[0] - quad->y[3];
            break;
        }
        dx = quad->px - vx;
        dy = quad->py - vy;
        if (dx * ey - dy * ex != 0.0) {
            cross2 = (mx - vx) * ey - (my - vy) * ex;
            if (dx * ey - dy * ex > 0.0) {
                if (cross2 <= 0.0) {
                    return 0;
                }
            } else if (cross2 >= 0.0) {
                return 0;
            }
        }
    }
    return 1;
}



void mapGridPointBuildVectors(s32 tri, f32 x, f32 y, f32 z, MapGridQuad *quad) {
    s32 k;

    switch (gMapGridTrianglePlanes[tri].axis) {
    case 0:
        quad->px = x;
        quad->py = y;
        for (k = 0; k < 4; k++) {
            quad->x[k] = gMapGridTriangleVerts[tri].x[k];
            quad->y[k] = gMapGridTriangleVerts[tri].y[k];
        }
        break;
    case 1:
        quad->px = x;
        quad->py = z;
        for (k = 0; k < 4; k++) {
            quad->x[k] = gMapGridTriangleVerts[tri].x[k];
            quad->y[k] = gMapGridTriangleVerts[tri].z[k];
        }
        break;
    case 2:
        quad->px = y;
        quad->py = z;
        for (k = 0; k < 4; k++) {
            quad->x[k] = gMapGridTriangleVerts[tri].y[k];
            quad->y[k] = gMapGridTriangleVerts[tri].z[k];
        }
        break;
    }
}

void mapGridPlaneProjectPoint(s32 tri, f32 x, f32 y, f32 z, f32 *outX, f32 *outY, f32 *outZ) {
    f32 nz;
    f32 t;
    f32 nx;
    f32 ny;
    f32 negD;

    negD = -gMapGridTrianglePlanes[tri].d;
    ny = gMapGridTrianglePlanes[tri].ny;
    nx = gMapGridTrianglePlanes[tri].nx;
    nz = gMapGridTrianglePlanes[tri].nz;
    t = (negD - (nz * z + (nx * x + ny * y))) / gMapGridTrianglePlanes[tri].lenSq;
    *outX = gMapGridTrianglePlanes[tri].nx * t + x;
    *outY = gMapGridTrianglePlanes[tri].ny * t + y;
    *outZ = gMapGridTrianglePlanes[tri].nz * t + z;
}

void mapRectIntersect(s32 left0, s32 top0, s32 right0, s32 bottom0, s32 left1, s32 top1, s32 right1, s32 bottom1, s32 *outLeft, s32 *outTop, s32 *outRight, s32 *outBottom) {
    if ((left0 == right0) || (top0 == bottom0)) {
        *outLeft = left1;
        *outTop = top1;
        *outRight = right1;
        *outBottom = bottom1;
        return;
    }
    if ((left1 == right1) || (top1 == bottom1)) {
        *outLeft = left0;
        *outTop = top0;
        *outRight = right0;
        *outBottom = bottom0;
        return;
    }
    *outLeft = (left0 < left1) ? left0 : left1;
    *outTop = (top0 < top1) ? top0 : top1;
    *outRight = (right1 < right0) ? right0 : right1;
    *outBottom = (bottom1 < bottom0) ? bottom0 : bottom1;
}

s32 mapRectOverlapTest(s32 left0, s32 top0, s32 right0, s32 bottom0, s32 left1, s32 top1, s32 right1, s32 bottom1, s32 *outLeft, s32 *outTop, s32 *outRight, s32 *outBottom) {
    if (left0 == -1) {
        return 0;
    }
    if (left1 == -1) {
        return 0;
    }
    *outLeft = (left1 < left0) ? left0 : left1;
    *outTop = (top1 < top0) ? top0 : top1;
    *outRight = (right0 < right1) ? right0 : right1;
    *outBottom = (bottom0 < bottom1) ? bottom0 : bottom1;
    if (!(*outLeft < *outRight)) {
        return 0;
    }
    if (!(*outTop < *outBottom)) {
        return 0;
    }
    return 1;
}

u8 mapGridPointPlaneDistanceWithin(s32 tri, f32 x, f32 y, f32 z, s16 maxDist) {
    f32 dist;

    dist = (gMapGridTrianglePlanes[tri].d + (gMapGridTrianglePlanes[tri].nx * x + gMapGridTrianglePlanes[tri].ny * y + gMapGridTrianglePlanes[tri].nz * z)) / gMapGridTrianglePlanes[tri].len;
    if (dist < 0.0) {
        dist = 0.0 - dist;
    }
    return dist <= maxDist;
}



s32 mapGridQuadClipToFrustum(s32 tri, f32 x, f32 y, f32 z)
{
    s32 k;
    s32 countA;
    s32 countB;

    countB = 0;
    countA = 0;
    for (k = 0; k < 4; k++) {
        sMapClipQuad[k].x = gMapGridTriangleVerts[tri].x[k];
        sMapClipQuad[k].y = gMapGridTriangleVerts[tri].y[k];
        sMapClipQuad[k].z = gMapGridTriangleVerts[tri].z[k];
    }
    mapPolyClipToFrustumPlane(sMapClipQuad, sMapClipScratchA, 4, &countA, 0);
    if (countA == 0) {
        return 0;
    }
    mapPolyClipToFrustumPlane(sMapClipScratchA, sMapClipScratchB, countA, &countB, 1);
    if (countB == 0) {
        return 0;
    }
    mapPolyClipToFrustumPlane(sMapClipScratchB, sMapClipScratchA, countB, &countA, 2);
    if (countA == 0) {
        return 0;
    }
    mapPolyClipToFrustumPlane(sMapClipScratchA, sMapClipScratchB, countA, &countB, 3);
    if (countB == 0) {
        return 0;
    }
    mapPolyClipToFrustumPlane(sMapClipScratchB, sMapClippedPoly, countB, &countA, 4);
    if (countA < 3) {
        countA = 0;
    }
    return countA;
}


void mapPolyClipToFrustumPlane(MapVec3 *in, MapVec3 *out, s32 count, s32 *outCount, s32 planeIdx) {
    f32 hit[3];
    MapVec3 *prev;
    MapVec3 *cur;
    s32 n;
    s32 i;
    f64 curDist;
    f64 prevDist;

    n = 0;
    prev = &in[count - 1];
    for (i = 0; i < count; i++, prev = cur) {
        cur = &in[i];
        curDist = PLANE_DIST(gFrustumPlanes[planeIdx], cur->x, cur->y, cur->z);
        prevDist = PLANE_DIST(gFrustumPlanes[planeIdx], prev->x, prev->y, prev->z);
        if (curDist >= 0.0) {
            if (prevDist >= 0.0) {
                memcpy(&out[n], cur, sizeof(MapVec3));
                n++;
            } else {
                mapFrustumPlaneIntersectEdge(&prev->x, &cur->x, planeIdx, hit);
                memcpy(&out[n++], hit, sizeof(MapVec3));
                memcpy(&out[n++], cur, sizeof(MapVec3));
            }
        } else if (prevDist >= 0.0) {
            mapFrustumPlaneIntersectEdge(&prev->x, &cur->x, planeIdx, hit);
            memcpy(&out[n++], hit, sizeof(MapVec3));
        }
    }
    *outCount = n;
}

void mapFrustumPlaneIntersectEdge(f32 *a, f32 *b, s32 planeIdx, f32 *out) {
    f32 pad[4];
    f32 bx;
    f64 s;
    f64 dist;

    dist = PLANE_DIST(gFrustumPlanes[planeIdx], a[0], a[1], a[2]);
    bx = b[0];
    s = dist / (((gFrustumPlanes[planeIdx].a * (a[0] - bx)) + (gFrustumPlanes[planeIdx].b * (a[1] - b[1]))) + (gFrustumPlanes[planeIdx].c * (a[2] - b[2])));
    out[0] = a[0] + ((bx - a[0]) * s);
    out[1] = a[1] + ((b[1] - a[1]) * s);
    out[2] = a[2] + ((b[2] - a[2]) * s);
}



void mapPolyProjectToScreenRect(s32 count, s32 *outLeft, s32 *outTop, s32 *outRight, s32 *outBottom) {
    f32 sx;
    f32 sy;
    s16 x;
    s16 y;
    s32 i;
    u8 flag;

    *outLeft = gPlayerSlots[gCurrentPlayerIndex].rect[2];
    *outTop = gPlayerSlots[gCurrentPlayerIndex].rect[3];
    *outRight = gPlayerSlots[gCurrentPlayerIndex].rect[0];
    *outBottom = gPlayerSlots[gCurrentPlayerIndex].rect[1];
    flag = 0;
    for (i = 0; i < count; i++) {
        flag |= camProjectToScreen(sMapClippedPoly[i].x, sMapClippedPoly[i].y, sMapClippedPoly[i].z, &sx, &sy, 0, 1.0f, gCurrentPlayerIndex); x = (s16)sx; y = (s16)sy; // LAYOUT: same-line statements steer sra scheduling
        if (x < gPlayerSlots[gCurrentPlayerIndex].rect[0]) {
            x = gPlayerSlots[gCurrentPlayerIndex].rect[0];
        }
        if (y < gPlayerSlots[gCurrentPlayerIndex].rect[1]) {
            y = gPlayerSlots[gCurrentPlayerIndex].rect[1];
        }
        if (gPlayerSlots[gCurrentPlayerIndex].rect[2] < x) {
            x = gPlayerSlots[gCurrentPlayerIndex].rect[2];
        }
        if (gPlayerSlots[gCurrentPlayerIndex].rect[3] < y) {
            y = gPlayerSlots[gCurrentPlayerIndex].rect[3];
        }
        if (x < *outLeft) {
            *outLeft = x;
        }
        if (y < *outTop) {
            *outTop = y;
        }
        if (*outRight < x) {
            *outRight = x;
        }
        if (*outBottom < y) {
            *outBottom = y;
        }
    }
    if ((*outLeft == *outRight) || (*outTop == *outBottom) || (flag != 0)) {
        *outLeft = -1;
        *outTop = -1;
        *outRight = -1;
        *outBottom = -1;
    }
}


void mapLoadNodeAsset(s32 id) {
    u8 *p;

    p = assetLoad(0x14, id, 1, 1);
    mapNodeAssetParse(p);
    if (p != NULL) {
        assetFreeBuffer(p, 0xBED, 0x22);
    }
}


void mapNodeAssetParse(u8 *data) {
    s32 pad[2];
    s16 n;
    s32 i;
    s16 idx;
    s16 *p;

    for (i = 0; i < 32; i++) {
        gMapZones[i] = NULL;
    }
    if (data == NULL) {
        return;
    }
    p = (s16 *)data;
    n = *p++;
    for (i = 0; i < n; i++) {
        idx = *p++;
        gMapZones[idx] = heapAlloc(sizeof(MapZone));
        gMapZones[idx]->minY = 0x7FFF;
        gMapZones[idx]->maxY = -0x8000;
        gMapZones[idx]->tris = NULL;
        gMapZones[idx]->vertCount = *p++;
        gMapZones[idx]->verts = heapAlloc(gMapZones[idx]->vertCount * 6);
        memcpy(gMapZones[idx]->verts, p, gMapZones[idx]->vertCount * 6);
        p += gMapZones[idx]->vertCount * 6 / sizeof(s16);
        gMapZones[idx]->height = *p++;
        gMapZones[idx]->exitCount = *p++;
        memcpy(gMapZones[idx]->exitCells, p, sizeof(gMapZones[idx]->exitCells));
        p += sizeof(gMapZones[idx]->exitCells) / sizeof(s16);
        gMapZones[idx]->enterCount = *p++;
        memcpy(gMapZones[idx]->enterCells, p, sizeof(gMapZones[idx]->enterCells));
        p += sizeof(gMapZones[idx]->enterCells) / sizeof(s16);
        gMapZones[idx]->linkCount = *p++;
        memcpy(gMapZones[idx]->links, p, sizeof(gMapZones[idx]->links));
        p += sizeof(gMapZones[idx]->links) / sizeof(s16);
        mapFaceBuildTriangleFan(idx);
    }
}

extern s16 sMapClipLeft;
extern s16 sMapClipTop;
extern s16 sMapClipRight;
extern s16 sMapClipBottom;


s16 mapPortalCollectTargets(s8 chunk, s8 *out, s16 max) {
    s16 i;
    s16 n;

    n = 0;
    if (chunk == -1) {
        return 0;
    }
    i = 0;
    while (i < gMapPortalSlotCount && n < max) {
        if (gMapPortalSlots[i].chunk == chunk) {
            out[n++] = gMapPortalSlots[i].target;
        }
        i++;
    }
    return n;
}

typedef struct MapSearchEntry {
    /* 0x000 */ void *key;
    /* 0x004 */ s16 x;
    /* 0x006 */ s16 y;
    /* 0x008 */ s16 maxDepth;
    /* 0x00A */ u8 padA[0x2];
    /* 0x00C */ u32 frame;
    /* 0x010 */ u8 active;
    /* 0x011 */ u8 visible;
    /* 0x012 */ u8 pad12[0x2];
} MapSearchEntry;

extern MapSearchEntry D_807F72B8[];
extern MapSearchEntry gMapSearchTable[];

void mapSearchTableReset(void) {
    s32 i;

    for (i = 0; i < 10; i++) {
        gMapSearchTable[i].active = 0;
    }
}



void mapSearchTableAddProbe(void *key, s16 x, s16 y, s16 maxDepth) {
    s32 i;
    s32 found;
    MapSearchEntry *entry;

    found = 0;
    i = 0;
    while ((i < 10) && !found) {
        entry = &gMapSearchTable[i];
        if (entry->active != 0) {
            i++;
        } else {
            found = 1;
        }
    }
    if (found) {
        entry = &gMapSearchTable[i];
        entry->active = 1;
        entry->frame = gFrameCounter;
        entry->key = key;
        entry->x = x;
        entry->y = y;
        entry->maxDepth = maxDepth;
    }
}


void mapSearchTableUpdateVisibility(void) {
    s32 i;
    f32 depth;

    for (i = 0; i < 10; i++) {
        if (gMapSearchTable[i].active != 0) {
            if (gFrameCounter == gMapSearchTable[i].frame) {
                depth = zbufferDepthToDistance(zbufferReadDepth(gMapSearchTable[i].x, gMapSearchTable[i].y));
                if (depth <= gMapSearchTable[i].maxDepth) {
                    gMapSearchTable[i].visible = 1;
                } else {
                    gMapSearchTable[i].visible = 0;
                }
            }
        }
        if ((gFrameCounter - gMapSearchTable[i].frame) >= 3) {
            gMapSearchTable[i].active = 0;
        }
    }
}

extern u8 D_807F72A1;
extern void *D_807F72A4;
extern u8 D_807F72B5;

u8 mapSearchTableGetValue(void *key) {
    s32 i;

    if (key == gMapSearchTable[0].key) { return D_807F72A1; } if (key == D_807F72A4) { return D_807F72B5; } // LAYOUT: same-line tests steer as1 scheduling
    for (i = 0; i < 8; i++) {
        if (key == D_807F72B8[i].key) {
            return D_807F72B8[i].visible;
        }
    }
    return 0;
}


void mapSetClipBounds(s16 left, s16 top, s16 right, s16 bottom) {
    sMapClipLeft = left;
    sMapClipTop = top;
    sMapClipRight = right;
    sMapClipBottom = bottom;
}


s32 mapPointOutsideClipBounds(f32 x, f32 y, f32 z, u8 marginX, u8 marginY) {
    f32 sx;
    f32 sy;
    s16 px;
    s16 py;
    s16 extraLeft;
    s16 extraRight;
    s16 extraTop;
    s16 extraBottom;
    f32 dist;
    f32 t;

    camProjectToScreen(x, y, z, &sx, &sy, 0, 1.0f, gCurrentPlayerIndex);
    px = (s16)sx;
    py = (s16)sy;
    dist = sqrtf((x - gPlayerSlots[gCurrentPlayerIndex].eyeX) * (x - gPlayerSlots[gCurrentPlayerIndex].eyeX)
                 + (y - gPlayerSlots[gCurrentPlayerIndex].eyeY) * (y - gPlayerSlots[gCurrentPlayerIndex].eyeY)
                 + (z - gPlayerSlots[gCurrentPlayerIndex].eyeZ) * (z - gPlayerSlots[gCurrentPlayerIndex].eyeZ));
    if (dist < 90.0f) {
        return 0;
    }
    extraLeft = 20;
    extraRight = 20;
    extraTop = 0;
    t = (dist - 60.0f) / 120.0f;
    if (dist >= 180.0f) {
        extraBottom = 50;
    } else if (t > 0.0) {
        extraLeft = -60.0f * t + 80.0f;
        extraRight = -60.0f * t + 80.0f;
        extraTop = -130.0f * t + 130.0f;
        extraBottom = -80.0f * t + 130.0f;
    } else {
        extraLeft = 80;
        extraRight = 80;
        extraTop = 130;
        extraBottom = 130;
    }
    if ((px < sMapClipLeft - extraLeft - marginX) || (sMapClipRight + extraRight + marginX < px)
        || (py < sMapClipTop - extraTop - marginY) || (sMapClipBottom + extraBottom + marginY < py)) {
        return 1;
    }
    return 0;
}

