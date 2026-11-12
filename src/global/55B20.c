#include "common.h"
#include "actor.h"
#include "map.h"
#include "render.h"
#define PROTO_SKIP_renderEntryListBuildDisplayList // FAKE: callee prototype steer
#include "proto/global/103AB0.h"
#include "proto/global/15050.h"
#include "proto/global/201B0.h"
#include "proto/global/2F550.h"
#include "proto/global/35000.h"
#include "proto/global/36880.h"
#include "proto/global/55B20.h"
#include "proto/global/5DE10.h"
#include "proto/global/5E2F0.h"
#include "proto/global/61AA0.h"
#include "proto/global/63EC0.h"
#include "proto/global/67890.h"
#include "proto/global/68960.h"
#include "proto/global/6AD90.h"

#define WRITE_GFX(pkt, _w0, _w1) { Gfx *_g = (Gfx *)(pkt); _g->words.w0 = (_w0); _g->words.w1 = (u32)(_w1); }

typedef struct MapChunkCell {
    /* 0x00 */ s16 id;
    /* 0x02 */ u8 layerMask;
    /* 0x03 */ u8 pad3;
    /* 0x04 */ s32 dl[4];
    /* 0x14 */ void *vtx[4];
} MapChunkCell; /* 0x24 */

typedef struct MapChunk {
    /* 0x000 */ u8 state;
    /* 0x001 */ u8 playerMask;
    /* 0x002 */ u8 texAnimPending;
    /* 0x003 */ u8 lightMode;
    /* 0x004 */ u8 lightsDone;
    /* 0x005 */ u8 kind;
    /* 0x006 */ u8 noSprites;
    /* 0x007 */ u8 streamFlags;
    /* 0x008 */ u8 *loadCursor;
    /* 0x00C */ u8 *loadStart;
    /* 0x010 */ u8 *loadEnd;
    /* 0x014 */ struct RenderEntry *opaqueList;
    /* 0x018 */ struct RenderEntry *opaqueTail;
    /* 0x01C */ struct RenderEntry *translucentList;
    /* 0x020 */ struct RenderEntry *translucentTail;
    /* 0x024 */ struct SpriteDisplayNode *sprites;
    /* 0x028 */ s32 lastSeenFrame;
    /* 0x02C */ s32 layerDl0;
    /* 0x030 */ s32 layerDl1;
    /* 0x034 */ s32 layerDl2;
    /* 0x038 */ s32 layerDl3;
    /* 0x03C */ s32 layerSize0;
    /* 0x040 */ s32 layerSize1;
    /* 0x044 */ s32 layerSize2;
    /* 0x048 */ s32 layerSize3;
    /* 0x04C */ MapChunkCell *cells;
    /* 0x050 */ s32 cellCount;
    /* 0x054 */ u8 *baseVtx;
    /* 0x058 */ u8 *curVtx;
    /* 0x05C */ s32 vtxSize;
    /* 0x060 */ void *litVtx[2];
    /* 0x068 */ s32 clipLeft;
    /* 0x06C */ s32 clipTop;
    /* 0x070 */ s32 clipRight;
    /* 0x074 */ s32 clipBottom;
    /* 0x078 */ struct MapCollisionNode *collStart;
    /* 0x07C */ struct MapCollisionNode *collEnd;
    /* 0x080 */ s16 minX;
    /* 0x082 */ s16 minZ;
    /* 0x084 */ s16 maxX;
    /* 0x086 */ s16 maxZ;
    /* 0x088 */ PlanePoly frustum[5];
} MapChunk;

extern MapChunk *gMapChunks;
typedef struct MapATpSlot {
    /* 0x0 */ s16 unk0;
    /* 0x2 */ s16 chunk;
    /* 0x4 */ s16 target;
    /* 0x6 */ s16 maxDist;
    /* 0x8 */ u8 seen;
    /* 0x9 */ u8 enabled;
} MapATpSlot;

extern MapATpSlot *gMapPortalSlots;

s32 gMapPortalSlotCount;
struct MapGridPoint *gMapGridTrianglePlanes;
s32 gMapChunkCount;
u8 *gMapPortalVisible;
s16 D_807F6C30[20];
s16 D_807F6C58[20];
s32 D_807F6C80;
s32 D_807F6C84; // unreferenced word between the chunk count and D_807F6C88
typedef struct MapVec3 {
    /* 0x0 */ f32 x;
    /* 0x4 */ f32 y;
    /* 0x8 */ f32 z;
} MapVec3;

MapVec3 D_807F6C88[4];
u8 D_807F6CB8[0xC0]; // unreferenced space before the clipping scratch buffers
MapVec3 D_807F6D78[20];
MapVec3 D_807F6E68[20];
MapVec3 D_807F6F58[20];
u8 D_807F7048[16];
u8 D_807F7058;
u8 D_807F7060[16];
u8 D_807F7070;
Mtx *D_807F7074;
u8 gMapChunkEnabled[0x32];
u8 D_807F70AA;
u8 D_807F70AB;
s32 gMapCellCount;

extern f32 *D_8076A0B4;
extern f32 *D_8076A0B8;
extern f32 *D_8076A0BC;
extern f32 *D_8076A0C0;
extern f32 *D_8076A0C4;
extern f32 *D_8076A0C8;

void mapChunkAllocLists(MapFileHeader *header) {
    s32 temp;
    s32 count;
    s32 size;

    temp = gMapChunkCount = *(s32 *)(header->collOff + (u8 *)header);
    if (temp >= 2) {
        count = temp & 0xFF;
    } else {
        count = 1;
    }
    size = count * 4;
    D_8076A0B4 = heapAlloc(size);
    D_8076A0B8 = heapAlloc(size);
    D_8076A0BC = heapAlloc(size);
    D_8076A0C0 = heapAlloc(size);
    D_8076A0C4 = heapAlloc(size);
    D_8076A0C8 = heapAlloc(size);
}

typedef struct MapPortal {
    /* 0x0 */ s16 target;
    /* 0x2 */ s16 portal;
    /* 0x4 */ s16 maxDist;
    /* 0x6 */ u8 pad6[2];
    /* 0x8 */ s32 dl0;
    /* 0xC */ s32 dl1;
} MapPortal;

extern s32 D_807F5DE8;
extern s32 gMapCellCount;
extern u8 D_807F70AB;
extern s16 D_807F7138;
extern u8 D_807F713A;
extern u8 D_807F70AA;
extern Mtx *D_807F7074;
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

extern MapGridVectors *D_807F6C14;
extern MapGridPoint *gMapGridTrianglePlanes;
extern struct MapCell *gMapCells;
extern struct MapBox *gMapCellBoxes;

extern s16 D_807F6C30[20];
extern s16 D_807F6C58[20];
extern u8 D_807F6CB8[0xC0];
extern u8 D_807F7048[16];
extern u8 D_807F7058;
extern u8 D_807F7060[16];
extern u8 D_807F7070;


typedef struct { s32 offset; s16 minX; s16 minZ; s16 maxX; s16 maxZ; } R13o6ColEntry;

void mapChunksInitFromMapData(MapFileHeader *data) {
    s32 i;
    s32 off;
    s32 base;
    u8 *p;
    u32 total;
    s32 n;
    s32 chunkOff;
    s32 cellsOff;
    s32 boxesOff;
    s32 vecsOff;
    u8 buf[0xE38];
    s32 count;
    s32 k;
    s32 size;

    gMapCellCount = 0;
    D_807F713A = 0;
    D_807F70AB = 0;
    if (gMapChunkCount != 0) {
        p = (u8 *)data;
        D_807F7138 = data->fogDist;
        D_807F7074 = heapAlloc(0x40);
        guScale(D_807F7074, 1.0f / 3.0f, 1.0f / 3.0f, 1.0f / 3.0f);
        cellsOff = data->cellsOff;
        gMapCellCount = *(s32 *)(p + cellsOff);
        gMapCells = (struct MapCell *)(p + cellsOff + 4);
        boxesOff = data->boxesOff;
        gMapCellBoxes = (struct MapBox *)(p + boxesOff + 4);
        vecsOff = data->vecsOff;
        D_807F6C14 = (MapGridVectors *)(p + vecsOff);
        if (data) {}  // FAKE: uopt block boundary (boxes holder gets a0, no call in its block)
        off = data->collOff;
        chunkOff = data->chunksOff;
        base = data->dlBase;
        cellsOff = data->portalsOff;
        gMapPortalSlotCount = *(s32 *)(p + cellsOff);
        gMapPortalSlots = (MapATpSlot *)(p + cellsOff + 4);
        gMapPortalVisible = heapAlloc(gMapPortalSlotCount);
        boxesOff = data->relocsOff;
        gMapPortalCount = *(s32 *)(p + boxesOff);
        gMapPortals = (MapPortal *)(p + boxesOff + 4);
        for (i = 0; i < gMapPortalCount; i++) {
            if (gMapPortals[i].dl0 != -1) {
                gMapPortals[i].dl0 += (s32)(p + base);
                if ((u32)data == (u32)gMapPortals[i].dl1) {} // FAKE: keep the pointer reload on the store path and data above the -1 constant in uopt priority
            }
            if (gMapPortals[i].dl1 != -1) {
                gMapPortals[i].dl1 += (s32)(p + base);
            }
        }
        gMapChunks = heapAlloc(gMapChunkCount * 0x1C8);
        p = (u8 *)data + chunkOff;
        for (n = 0; n < gMapChunkCount; n++) {
            count = 0;
            gMapChunks[n].state = 0;
            gMapChunks[n].playerMask = 0;
            gMapChunks[n].opaqueList = 0;
            gMapChunks[n].translucentList = 0;
            gMapChunks[n].sprites = 0;
            gMapChunks[n].streamFlags = 4;
            gMapChunks[n].baseVtx = (u8 *)(*(s32 *)(p + 0x2C) + D_807F5DE8);
            gMapChunks[n].curVtx = gMapChunks[n].baseVtx;
            lightSetTargetColor(p[0] / 255.0, p[1] / 255.0, p[2] / 255.0, (s16)n);
            lightCopyTargetColors((s16)n);
            gMapChunks[n].noSprites = p[3];
            p += 0xC;
            gMapChunks[n].kind = p[-8];
            gMapChunks[n].lightMode = *(s32 *)(p - 4);
            if (*(s32 *)p != -1) {
                *(s32 *)p += (s32)((u8 *)data + base);
            }
            gMapChunks[n].layerDl0 = *(s32 *)p;
            p += 8;
            gMapChunks[n].layerSize0 = *(s32 *)(p - 4);
            total = gMapChunks[n].layerSize0;
            if (gMapChunks[n].kind == 2) {
                D_807F713A = 1;
                mapChunkBuildCellTable(gMapChunks[n].layerDl0, gMapChunks[n].layerSize0, buf, &count, 0, n);
            }
            if (*(s32 *)p != -1) {
                *(s32 *)p += (s32)((u8 *)data + base);
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
                *(s32 *)p += (s32)((u8 *)data + base);
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
                *(s32 *)p += (s32)((u8 *)data + base);
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
            size = n * 12;
            gMapChunks[n].collStart = (struct MapCollisionNode *)(((R13o6ColEntry *)((u8 *)((s32)data + off + 4) + size))->offset + ((s32)data + off));
            gMapChunks[n].collEnd = (struct MapCollisionNode *)(((R13o6ColEntry *)((u8 *)((s32)data + off + 4) + size))[1].offset + ((s32)data + off));
            gMapChunks[n].minX = ((R13o6ColEntry *)((u8 *)((s32)data + off + 4) + size))->minX;
            gMapChunks[n].minZ = ((R13o6ColEntry *)((u8 *)((s32)data + off + 4) + size))->minZ;
            gMapChunks[n].maxX = ((R13o6ColEntry *)((u8 *)((s32)data + off + 4) + size))->maxX;
            gMapChunks[n].maxZ = ((R13o6ColEntry *)((u8 *)((s32)data + off + 4) + size))->maxZ;
            gMapChunks[n].lastSeenFrame = -1;
            if (count != 0) {
                gMapChunks[n].cells = heapAlloc(count * 0x24);
                memcpy(gMapChunks[n].cells, buf, count * 0x24);
                for (i = 0; i < count; i++) {
                    gMapChunks[n].cells[i].layerMask = 0xFF;
                }
            }
            gMapChunks[n].cellCount = count;
        }
        gMapGridTrianglePlanes = heapAlloc(gMapPortalSlotCount / 2 * 0x30);
        for (k = 0; k < gMapPortalSlotCount / 2; k++) {
            mapGridTriangleBuildPlane(k, &gMapGridTrianglePlanes[k]);
        }
        if (gMapChunks) {}  // FAKE: deadsweep dead statement (steers uopt; replace with natural C)
        k = 0;
        do {
            gMapChunkEnabled[k] = 1;
            k++;
        } while (k < 0x32);
        D_807F70AA = 0;
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
    s32 k;
    s32 next;
    s32 cur;
    s32 out;
    s32 curOff;
    u8 *vtx;

    face = gMapZones[faceId];
    if (face->tris != 0) {
        heapFree(face->tris);
    }
    k = face->vertCount - 2;
    if (k < 0) {
        k = 0;
    }
    if (k != 0) {
        face->tris = heapAlloc(k * 0x12);
        face->triCount = k;
        if (face->vertCount >= 3) {
            cur = 1;
            next = 2;
            out = 0x24;
            k = 0xC;
            do {
                curOff = cur * 6;
                if (k && k) {}  // FAKE: deadsweep: steers uopt coloring (keeps unk4 temp in a0)
                cur = next;
                *(s16 *)(face->tris + out - 0x24) = *(s16 *)(face->verts);
                next += 1;
                *(s16 *)(face->tris + out - 0x1E) = *(s16 *)(face->verts + 2);
                *(s16 *)(face->tris + out - 0x18) = *(s16 *)(face->verts + 4);
                *(s16 *)(face->tris + out - 0x22) = *(s16 *)(face->verts + curOff);
                *(s16 *)(face->tris + out - 0x1C) = *(s16 *)(face->verts + curOff + 2);
                *(s16 *)(face->tris + out - 0x16) = *(s16 *)(face->verts + curOff + 4);
                *(s16 *)(face->tris + out - 0x20) = *(s16 *)(face->verts + k);
                *(s16 *)(face->tris + out - 0x1A) = *(s16 *)(face->verts + k + 2);
                *(s16 *)(face->tris + out - 0x14) = *(s16 *)(face->verts + k + 4);
                out += 0x12;
                k += 6;
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
            next += 1;
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

    if (size != 0) {
        do {
            key = ((MapDlCommand *)list)->w0;
            idx = 0;
            found = 0;
            size -= 8;
            if (((u32)key >> 24) == 0) {
                n = *count;
                key = ((MapDlCommand *)list)->w1;
                if (n > 0) {
                    do {
                        if (key == buf[idx].id) {
                            found = 1;
                        } else {
                            idx += 1;
                        }
                    } while (idx < n && found == 0);
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
        } while (size != 0);
    }
}

s32 mapChunkIsInUse(s16 chunk) {
    s32 active;
    s32 result;

    result = (chunk + 1) != 0;
    if (result != 0) {
        if (gMapChunks[chunk].lightMode != 0) {
            active = 1;
        } else {
            active = 0;
        }
        result = active != 0;
    }
    return result & 0xFF;
}

void mapByteArraySet(s16 index, u8 val) {
    gMapChunkEnabled[index] = val;
}

void mapObjectSetByte(s16 objIndex, u8 byteOffset, u8 val) {
    gMapPortalSlots[objIndex * 2 + byteOffset].enabled = val;
}

f32 sqrtf(f32);

void mapGridTriangleBuildPlane(s32 tri, MapGridPoint *plane) {
    s64 a2v;
    s64 a1v;
    s64 a0v;
    s64 b2v;
    s64 b1v;
    s64 b0v;
    s64 x;
    s64 y;
    s64 z;

    a0v = (s64)(D_807F6C14[tri].x[0] - D_807F6C14[tri].x[1]);
    a1v = (s64)(D_807F6C14[tri].y[0] - D_807F6C14[tri].y[1]);
    a2v = (s64)(D_807F6C14[tri].z[0] - D_807F6C14[tri].z[1]);
    b0v = (s64)(D_807F6C14[tri].x[0] - D_807F6C14[tri].x[2]);
    b1v = (s64)(D_807F6C14[tri].y[0] - D_807F6C14[tri].y[2]);
    b2v = (s64)(D_807F6C14[tri].z[0] - D_807F6C14[tri].z[2]);
    plane->nx = a1v * b2v - a2v * b1v;
    plane->ny = a2v * b0v - a0v * b2v;
    plane->nz = a0v * b1v - a1v * b0v;
    plane->d = (s64)-(((f32)plane->nx * D_807F6C14[tri].x[1] + (f32)plane->ny * D_807F6C14[tri].y[1]) + (f32)plane->nz * D_807F6C14[tri].z[1]);
    plane->lenSq = (f32)(plane->nx * plane->nx + plane->ny * plane->ny + plane->nz * plane->nz);
    plane->len = sqrtf(plane->lenSq);
    x = plane->nx >= 0 ? plane->nx : 0 - plane->nx;
    y = plane->ny >= 0 ? plane->ny : 0 - plane->ny;
    z = plane->nz >= 0 ? plane->nz : 0 - plane->nz;
    if ((z >= x) && (z >= y)) {
        plane->axis = 0;
    }
    if ((y >= x) && (y >= z)) {
        plane->axis = 1;
    }
    if ((x >= y) && (x >= z)) {
        plane->axis = 2;
    }
}

struct MapCell;

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

    entry->unk20 = mapChunkFindByPosition(entry->unk4, entry->unk8, entry->unkC, entry->unk20);
    layer = renderEntryIsTranslucent(entry->unk24, entry->unk0);
    if (entry->unk24 == 0) {
        ((Actor *)entry->unk0)->chunkIndex = entry->unk20;
    }
    switch (layer) {
    case 0:
        list = &gMapChunks[entry->unk20].opaqueList;
        break;
    case 1:
        list = &gMapChunks[entry->unk20].translucentList;
        break;
    }
    *list = renderEntryAddOrUpdate(*list, entry->unk24, entry->unk0, entry->unk4, entry->unk8, entry->unkC, entry->unk1C, entry->unk1E, entry->unk22, entry->unk20, 0);
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
    u8 flag;
    s32 i;

    flag = 0;
    for (i = 0; i < gMapChunkCount && (!flag || all); i++) {
        gMapChunks[i].opaqueList = renderEntryRemove(gMapChunks[i].opaqueList, targetId, 0, &flag);
        if (flag) {
            *outChunk = i;
        }
        if (!flag || all) {
            gMapChunks[i].translucentList = renderEntryRemove(gMapChunks[i].translucentList, targetId, 0, &flag);
            if (flag) {
                *outChunk = i;
            }
        }
    }
    return flag;
}

struct MapCell;
struct MapBox;
extern u8 D_807F7140;


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

    i = 0;
    if (gMapChunkCount > 0) {
        do {
            modelNodeListSyncFlags(gMapChunks[i].opaqueList);
            modelNodeListSyncFlags(gMapChunks[i].translucentList);
            i += 1;
        } while (i < gMapChunkCount);
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
    void *node;
    void *next;

    D_807F7140 = 0;
    for (i = 0; i < gMapChunkCount; i++) {
        if (gMapChunks[i].playerMask != 0) {
            flag = 1;
        } else {
            flag = 0;
        }
        node = gMapChunks[i].opaqueList;
        while (node != NULL) {
            next = ((RenderEntry *)node)->unk14;
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
                        if (node->unk24 == 1) {
                            result |= collisionTestDynamicActorFloor(actor, node->unk1E, x, z, y, outFloorY);
                        }
                        node = node->unk14;
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
    s32 i;
    s16 chunk;

    i = 0;
    if (gMapChunkCount == 0) {
        return 0xFF;
    }
    chunk = mapChunkFindByPosition(x, y, z, 0);
    while (i < D_807F6C80) {
        if (chunk == D_807F6C58[i]) {
            return 1;
        }
        i++;
        continue; // FAKE: trailing continue reorders uopt coloring (chunk before the loop bound)
    }
    return 0;
}

s32 mapChunkIsVisible(s16 chunk) {
    s32 result;

    if (gMapChunkCount == 0) {
        return 0xFF;
    }
    if (gMapChunks[chunk].playerMask != 0) {
        result = 1;
    } else {
        result = 0;
    }
    return result & 0xFF;
}

s32 mapChunkIsActive(s16 chunk) {
    s32 result;

    if (gMapChunkCount == 0) {
        return 0xFF;
    }
    if (gMapChunks[chunk].state == 1) {
        result = 1;
    } else {
        result = 0;
    }
    return result & 0xFF;
}

s32 mapChunkIsVisibleForPlayer(s16 player, s16 chunk) {
    s32 result;

    if (gMapChunkCount == 0) {
        return 1;
    }
    if (gMapChunks[chunk].playerMask & (1 << player)) {
        result = 1;
    } else {
        result = 0;
    }
    return result & 0xFF;
}

s16 mapChunkFindAtPoint(f32 x, f32 y, f32 z, s16 hint) {
    s16 temp;

    mapCellFindAtPoint(x, y, z, hint, -1, &temp);
    return temp;
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
            if ((chunk == gMapCells[i].chunk) && (parent == gMapCells[i].parent)) {
                id = gMapCells[i].id;
                if (id) {} // FAKE: raises id's adjsave so the table address is not hoisted into a saved register
                box = (MapBox *)((u8 *)gMapCellBoxes + id * 12); // FAKE: byte-offset box address steers codegen (&gMapCellBoxes[id] fdiff=1)
                if (box && box) {} // FAKE: keeps box's live range apart from the hoisted cell table address
                if (((f32)box->minX <= x) && (x <= (f32)box->maxX) && ((f32)box->minY <= y) && (y <= (f32)box->maxY) && ((f32)box->minZ <= z) && (z <= (f32)box->maxZ)) {
                    *outCell = id;
                    mapCellFindAtPoint(x, y, z, chunk, id, outCell);
                }
            }
            i++;
        } while (i < gMapCellCount);
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

    if (x < (f32)gMapChunks[chunk].minX) {
        return 0;
    }
    if (z < (f32)gMapChunks[chunk].minZ) {
        return 0;
    }
    if ((f32)gMapChunks[chunk].maxX < x) {
        return 0;
    }
    if ((f32)gMapChunks[chunk].maxZ < z) {
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
                    *outHeight = (f32)node->y0;
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
        minX = (f32) x0;
    } else {
        minX = (f32) x1;
    }
    x2 = (f32) box->x2;
    if (!(minX < x2)) {
        minX = x2;
    }
    if (x < minX) {
        return 0;
    }
    z0 = box->z0;
    z1 = box->z1;
    if (z0 < z1) {
        minZ = (f32) z0;
    } else {
        minZ = (f32) z1;
    }
    z2 = (f32) box->z2;
    if (!(minZ < z2)) {
        minZ = z2;
    }
    if (z < minZ) {
        return 0;
    }
    if (x1 < x0) {
        maxX = (f32) x0;
    } else {
        maxX = (f32) x1;
    }
    if (!(x2 < maxX)) {
        maxX = x2;
    }
    if (maxX < x) {
        return 0;
    }
    if (z1 < z0) {
        maxZ = (f32) z0;
    } else {
        maxZ = (f32) z1;
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
    f64 mz;
    f64 dx;
    f64 dz;
    f64 ox;
    f64 oz;
    f64 c;
    f64 pad;
    u16 flag;
    s32 i;

    flag = 0;
    mx = (tri->x2 + tri->x1) * 0.5;
    mz = (tri->z2 + tri->z1) * 0.5;
    cx = (tri->x0 + mx) * 0.5;
    cz = (tri->z0 + mz) * 0.5;
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
        mx = (x - ox) * dz; // mx/mz reused as the two cross products
        mz = (z - oz) * dx;
        c = (cx - ox) * dz - (cz - oz) * dx;
        if ((mz <= mx ? 1 : -1) != (c >= 0.0 ? 1 : -1)) {
            flag = 1;
        }
    }
    return flag == 0;
}


typedef struct {
    /* 0x000 */ u8 pad0[4];
    /* 0x004 */ Actor *actor;
    /* 0x008 */ Mtx viewMtx[2];
    /* 0x088 */ u8 pad88[0x21C - 0x88];
    /* 0x21C */ f32 posX;
    /* 0x220 */ f32 posY;
    /* 0x224 */ f32 posZ;
    /* 0x228 */ u8 pad228[0x270 - 0x228];
    /* 0x270 */ s16 viewLeft;
    /* 0x272 */ s16 viewTop;
    /* 0x274 */ s16 viewRight;
    /* 0x276 */ s16 viewBottom;
    /* 0x278 */ s16 viewWidth;
    /* 0x27A */ s16 viewHeight;
    /* 0x27C */ f32 fov;
    /* 0x280 */ u8 pad280[0x288 - 0x280];
    /* 0x288 */ f32 fogDist;
    /* 0x28C */ u8 pad28C[4];
    /* 0x290 */ s16 chunk;
    /* 0x292 */ u8 pad292[0x2F0 - 0x292];
} MapPlayer;

extern MapPlayer *gPlayerSlots;
extern u8 gCurrentPlayerIndex;

void mapChunkActivate(s16 chunkIndex) {
    gMapChunks[chunkIndex].state = 1;
    gMapChunks[chunkIndex].playerMask |= 1 << gCurrentPlayerIndex;
    gMapChunks[chunkIndex].clipLeft = gPlayerSlots[gCurrentPlayerIndex].viewLeft;
    gMapChunks[chunkIndex].clipTop = gPlayerSlots[gCurrentPlayerIndex].viewTop;
    gMapChunks[chunkIndex].clipRight = gPlayerSlots[gCurrentPlayerIndex].viewRight;
    gMapChunks[chunkIndex].clipBottom = gPlayerSlots[gCurrentPlayerIndex].viewBottom;
}


void mapChunkSetIndexOverride(s8 index) {
    D_807F70AB = index;
}

extern f32 D_807F5E20[];

extern PlanePoly gFrustumPlanes[];
extern u8 gGfxBufferIndex;
extern f32 D_807F5FB4;
extern f32 D_807F5FB0;
extern u8 D_807F6C08;

void mapChunkFrameUpdate(f32 x, f32 y, f32 z) {
    gPlayerSlots[gCurrentPlayerIndex].chunk = mapChunkFindByPosition(x, y, z, gPlayerSlots[gCurrentPlayerIndex].chunk);
    if (D_807F70AB != 0) {
        gPlayerSlots[gCurrentPlayerIndex].chunk = gPlayerSlots[gCurrentPlayerIndex].actor->chunkIndex;
    }
    mapUpdateFogDistance(&gPlayerSlots[gCurrentPlayerIndex].fogDist, gPlayerSlots[gCurrentPlayerIndex].chunk);
    D_807F7138 = (s16)(s32)gPlayerSlots[gCurrentPlayerIndex].fogDist;
    frustumCalculateCornerRays(D_807F5FB4, D_807F5FB0, (f32)D_807F7138);
    frustumCornersTransformByInverse(&gPlayerSlots[gCurrentPlayerIndex].viewMtx[gGfxBufferIndex]);
    frustumOrientPolyNormals(x, y, z, gFrustumPlanes, D_807F5E20);
    mapChunkClearBounds();
    mapChunkActivate(gPlayerSlots[gCurrentPlayerIndex].chunk);
    mapTriggerCollectZonesAtPoint(x, y, z);
    D_807F6C80 = 0;
    D_807F6C08 = 0;
    mapChunkTraversePortals(gPlayerSlots[gCurrentPlayerIndex].chunk, 0, gPlayerSlots[gCurrentPlayerIndex].viewLeft, gPlayerSlots[gCurrentPlayerIndex].viewTop, gPlayerSlots[gCurrentPlayerIndex].viewRight, gPlayerSlots[gCurrentPlayerIndex].viewBottom, x, y, z);
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
            if (kind == 0xFD) {
                if (((u32)(*(s32 *)(cmd + 4) * 0x10) >> 0x1C) == 0) {
                    addr = *(s32 *)(cmd + 4);
                    *(void **)(cmd + 4) = assetLoad(0x19, addr, 0, 0);
                    count++;
                }
                if (cmd && cmd) {}  // FAKE: deadsweep dead statement (steers uopt; replace with natural C)
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
            if ((op = (*(u32 *)cmd >> 0x18)) == 0xFD) {
                if (orig) {} // FAKE: dead read of the lookup result keeps the BST out-params' web out of $a0
                addr = *(u32 *)(cmd + 4);
                if ((addr >= 0x80000000U) && (addr < 0xA0000000U)) {
                    collisionBstLookupByHash(addr, &node, &orig);
                    assetFreeBuffer((void *)*(u32 *)(cmd + 4), 0x542, 0x22);
                    *(u32 *)(cmd + 4) = orig;
                }
            }
            cmd += 8;
        } while (cmd != end);
    }
}

void mapChunkSetFlagBit3(s16 chunk) {
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
                    gMapChunks[i].streamFlags &= 0xFFFC;
                }
                n = mapObjectCollectIdsByType((s8)i, buf, 0x10);
                for (j = 0; j < n; j++) {
                    idx = buf[j];
                    if (flags[idx] == 0) {
                        if (gMapChunks[idx].playerMask == 0) {
                            if (!(gMapChunks[idx].streamFlags & 4)) {
                                gMapChunks[idx].loadCursor = mapChunkLoadAssetRefs(gMapChunks[idx].loadCursor, gMapChunks[idx].loadEnd, 5);
                                if (gMapChunks[idx].loadCursor == gMapChunks[idx].loadEnd) {
                                    gMapChunks[idx].streamFlags &= 0xFFFD;
                                    gMapChunks[idx].streamFlags |= 4;
                                } else {
                                    gMapChunks[idx].streamFlags |= 2;
                                }
                                gMapChunks[idx].streamFlags &= 0xFFFE;
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
                            gMapChunks[i].streamFlags &= 0xFFFD;
                            gMapChunks[i].streamFlags |= 4;
                        } else {
                            gMapChunks[i].streamFlags |= 2;
                        }
                        gMapChunks[i].streamFlags &= 0xFFFE;
                    }
                } else if (!(gMapChunks[i].streamFlags & 1) && (u32)(gFrameCounter - gMapChunks[i].lastSeenFrame) >= 3U) {
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

extern f32 D_807F5FAC;
extern s32 D_807482F4;
extern PlanePoly D_807F7148[];

void mapChunkBuildClipFrusta(f32 x, f32 y, f32 z) {
    f32 viewMtx[4][4];
    f32 invMtx[4][4];
    s32 i;
    f32 corners[4][3];

    frustumCalculateCornerRays(D_807F5FB4, D_807F5FB0, D_807F5FAC);
    guMtxL2F(viewMtx, &gPlayerSlots[gCurrentPlayerIndex].viewMtx[gGfxBufferIndex]);
    matrix4Invert(invMtx, viewMtx);
    for (i = 0; i < gMapChunkCount; i++) {
        if (gMapChunks[i].state == 1) {
            mapScreenRectBuildFrustum(gMapChunks[i].clipLeft, gMapChunks[i].clipTop, gMapChunks[i].clipRight, gMapChunks[i].clipBottom,
                          x, y, z, gCurrentPlayerIndex, invMtx, &gMapChunks[i].frustum[0], corners);
            if (i == D_807482F4) {
                memcpy(D_807F7148, &gMapChunks[i].frustum[0], sizeof(gMapChunks[i].frustum));
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

extern FrustumCorners D_807F5DF0;
void mapScreenRectBuildFrustum(s32 left, s32 top, s32 right, s32 bottom, f32 x, f32 y, f32 z, u8 player, f32 (*mtx)[4], void *planes, f32 (*out)[3]) {
    s32 i;
    f32 q;
    f32 x0;
    f32 x1;
    f32 y0;
    f32 y1;
    f32 m[4][3];

    q = ((f32)(left - gPlayerSlots[player].viewLeft)) / (f32)gPlayerSlots[player].viewWidth;
    x0 = (q * (D_807F5DF0.c1x - D_807F5DF0.c0x)) + D_807F5DF0.c0x;
    q = ((f32)(right - gPlayerSlots[player].viewLeft)) / (f32)gPlayerSlots[player].viewWidth;
    x1 = (q * (D_807F5DF0.c1x - D_807F5DF0.c0x)) + D_807F5DF0.c0x;
    q = ((f32)(top - gPlayerSlots[player].viewTop)) / (f32)gPlayerSlots[player].viewHeight;
    y0 = ((D_807F5DF0.c2y - D_807F5DF0.c0y) * q) + D_807F5DF0.c0y;
    q = ((f32)(bottom - gPlayerSlots[player].viewTop)) / (f32)gPlayerSlots[player].viewHeight;
    y1 = ((D_807F5DF0.c2y - D_807F5DF0.c0y) * q) + D_807F5DF0.c0y;
    m[0][0] = x1; m[0][1] = y1; m[0][2] = D_807F5DF0.c0z;
    m[1][0] = x0; m[1][1] = y1; m[1][2] = D_807F5DF0.c1z;
    m[2][0] = x1; m[2][1] = y0; m[2][2] = D_807F5DF0.c2z;
    m[3][0] = x0; m[3][1] = y0; m[3][2] = D_807F5DF0.c3z;
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


extern u8 D_807F7048[];
extern u8 D_807F7060[];


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

    D_807F7058 = 0;
    D_807F7070 = 0;
    for (p = gMapZones, i = 0; i != 0x20; i++) {
        if (*p != NULL) {
            zone = *p;
            if ((f32)zone->minY <= y && y <= (f32)(zone->maxY + zone->height)) {
                tri = (MapTriangle *)zone->tris;
                for (j = 0; j < zone->triCount; j++, tri++) {
                    if (mapTriangleBoundsContainPoint(tri, x, z) != 0 && mapTriangleContainsPoint(tri, x, z) != 0) {
                        h = mapTriangleHeightAtPoint(tri, x, z);
                        if (h <= y && y <= (f32)zone->height + h) {
                            k = 0;
                            if (D_807F7058 != 0x10) {
                                D_807F7048[D_807F7058] = i;
                                D_807F7058++;
                            }
                            for (; k < zone->linkCount; k++) {
                                found = 0;
                                n = 0;
                                while (!found && n < D_807F7070) {
                                    if (D_807F7060[n] == zone->links[k]) {
                                        found = 1;
                                    } else {
                                        n++;
                                    }
                                }
                                if (!found && n != 0x10) {
                                    D_807F7060[D_807F7070] = zone->links[k];
                                    D_807F7070++;
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
    i = 0;
    while (i < D_807F7058) {
        idx = D_807F7048[i];
        if (gMapZones[idx] != 0) {
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
                    if (!zone->enterCount) {} // FAKE: re-test of the count reorders the loop's register candidates
                    for (j = 0; j < zone->exitCount; j++) {
                        mapCellSetFlag(*val, 0);
                        val++;
                    }
                }
            }
        }
        i++;
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
    f64 d68;
    f64 d02;
    f64 q;
    f64 d04;
    f64 d6A;
    f64 t;
    f64 dCE;
    f64 N1;
    f64 N2;
    f64 dC10;
    d02 = (f64)(tri->x0 - tri->x1);
    d68 = (f64)(tri->y0 - tri->y1);
    dCE = (f64)(tri->z0 - tri->z1);
    d04 = (f64)(tri->x0 - tri->x2);
    d6A = (f64)(tri->y0 - tri->y2);
    dC10 = (f64)(tri->z0 - tri->z2);
    N1 = d68 * dC10 - dCE * d6A;
    N2 = dCE * d04 - d02 * dC10;
    q = -((f64)tri->z1 * (d02 * d6A - d68 * d04) + (N1 * (f64)tri->x1 + N2 * (f64)tri->y1));
    if (N2 * 2000.0 > 0.01 || N2 * 2000.0 < -0.01) {
        t = N1 * x + N2 * -1000.0 + (d02 * d6A - d68 * d04) * z + q;
        t = t / (N2 * 2000.0);
        if (t < 0.0) {
            t = 0.0 - t;
        }
        ret = (f32)(2000.0 * t - 1000.0);
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

s32 mapTriangleContainsPoint(MapTriangle *tri, f32 x, f32 z) {
    f64 cz;
    f64 mx;
    f64 cx;
    f64 mz;
    f64 dx;
    f64 dz;
    f64 ox;
    f64 oz;
    f64 c;
    f64 pad;
    u16 flag;
    s32 i;

    flag = 0;
    mx = (tri->x2 + tri->x1) * 0.5;
    mz = (tri->z2 + tri->z1) * 0.5;
    cx = (tri->x0 + mx) * 0.5;
    cz = (tri->z0 + mz) * 0.5;
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
        mx = (x - ox) * dz; // mx/mz reused as the two cross products
        mz = (z - oz) * dx;
        c = (cx - ox) * dz - (cz - oz) * dx;
        if ((mz <= mx ? 1 : -1) != (c >= 0.0 ? 1 : -1)) {
            flag = 1;
        }
    }
    return (flag == 0) & 0xFF;
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
                                  x, y, z, D_807F5FAC,
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


void func_8065C990(void *, void *, s32, void *, s32, s32);
extern f32 D_807F7EEC;
extern f32 D_807F7EF0;
extern f32 D_807F7EF4;
extern u8 D_807F78C0;

void mapChunksApplyLights(f32 x, f32 y, f32 z) {
    s32 i;
    s32 obj;
    void *matrix;
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
                                obj = lightCollectVolumesInBounds(x, y, z, gMapCellBoxes[boxIdx].minX, gMapCellBoxes[boxIdx].minY, gMapCellBoxes[boxIdx].minZ, gMapCellBoxes[boxIdx].maxX, gMapCellBoxes[boxIdx].maxY, gMapCellBoxes[boxIdx].maxZ, i, &hit);
                                nodeIdx = 0;
                                found = 0;
                                key = gMapCells[k].id; node = gMapChunks[i].cells;  // LAYOUT: same-line statements steer scheduling
                                do {
                                    if (key == node->id) {
                                        found = 1;
                                    } else {
                                        nodeIdx += 1;
                                        node += 1;
                                    }
                                } while (found == 0);
                                if (gGlobalPauseFlags & 0x10) {
                                    gMapChunks[i].cells[nodeIdx].vtx[j] = matrixCacheLookup(obj, i, boxIdx, j);
                                    if (gMapChunks[i].cells[nodeIdx].vtx[j] == NULL) {
                                        gMapChunks[i].cells[nodeIdx].vtx[j] = matrixCacheInsert(obj, i, boxIdx, j, gMapCells[k].vtxCount[j], hit);
                                        src = gMapChunks[i].baseVtx + gMapCells[k].vtxOffset[j] * 0x10;
                                        memcpy(gMapChunks[i].cells[nodeIdx].vtx[j], src, gMapCells[k].vtxCount[j] * 0x10);
                                        matrix = gMapChunks[i].cells[nodeIdx].vtx[j];
                                        D_807F7EEC = D_8076A0B4[i];
                                        D_807F7EF0 = D_8076A0B8[i];
                                        D_807F7EF4 = D_8076A0BC[i];
                                        func_8065C990(matrix, (u8 *)matrix + gMapCells[k].vtxCount[j] * 0x10, 1, &D_807F78C0, obj, gMapChunks[i].lightMode == 1);
                                    }
                                }
                            }
                        }
                    }
                }
            } else {
                if (flag == 0) {
                    obj = lightCollectVolumesInBounds(x, y, z, -0x8000, -0x8000, -0x8000, -0x8000, -0x8000, -0x8000, -1, &hit);
                    flag = 1;
                }
                if (gMapChunks[i].litVtx[gGfxBufferIndex] == NULL) {
                    gMapChunks[i].litVtx[gGfxBufferIndex] = heapAlloc(gMapChunks[i].vtxSize);
                }
                memcpy(gMapChunks[i].litVtx[gGfxBufferIndex], gMapChunks[i].baseVtx, gMapChunks[i].vtxSize);
                D_807F7EEC = D_8076A0B4[i];
                D_807F7EF0 = D_8076A0B8[i];
                D_807F7EF4 = D_8076A0BC[i];
                if (gGlobalPauseFlags & 0x10) {
                    func_8065C990((s32)gMapChunks[i].litVtx[gGfxBufferIndex], (s32)gMapChunks[i].litVtx[gGfxBufferIndex] + gMapChunks[i].vtxSize, 1, &D_807F78C0, obj, gMapChunks[i].lightMode == 1);  // FAKE: s32 args steer the a0 register (callee takes void * here)
                }
            }
            gMapChunks[i].curVtx = gMapChunks[i].litVtx[gGfxBufferIndex];
        }
    }
    effectWaterApplyLights(x, y, z);
}




void mapChunkFreeIdleBuffers(void) {
    s32 i;

    if (D_807F713A != 0) {
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

    if (!mapChunkIsVisible(D_807F70AA)) {
        for (node = gMapChunks[D_807F70AA].opaqueList; node != NULL; node = node->unk14) {
            modelSlotFreeTexAnimBuffers(node->unk0, node->unk24);
            modelSlotFreeAssetTextures(node->unk0, node->unk24);
        }
        for (node = gMapChunks[D_807F70AA].translucentList; node != NULL; node = node->unk14) {
            modelSlotFreeTexAnimBuffers(node->unk0, node->unk24);
            modelSlotFreeAssetTextures(node->unk0, node->unk24);
        }
    }
    D_807F70AA++;
    if (gMapChunkCount == D_807F70AA) {
        D_807F70AA = 0;
    }
}

extern s16 D_807F6C30[];

s32 mapNodeIdListContains(s16 id, s32 count) {
    s32 i;

    for (i = 0; i < count; i++) {
        if (id == D_807F6C30[i]) {
            return 1;
        }
        continue; // FAKE: trailing continue gives id an unconstrained register
    }
    return 0;
}

extern s16 D_807F6BF0[];


typedef struct {
    /* 0x000 */ u8 pad0[0x8];
    /* 0x008 */ s32 dl;
} MapChunkArg;


extern u8 D_807F5FEC;
extern void *D_807F5DEC;
extern s32 gGlobalOverlayFlags;
extern u8 D_807F6009;
extern s32 D_807F600C;
extern struct RenderEntry *D_807F5FFC;
extern Gfx D_2000180;

u32 osVirtualToPhysical(void *);
Gfx *renderEntryListBuildDisplayList(Gfx *, struct RenderEntry *, f32, f32, f32, s32, s16, s32); // FAKE: callee prototype steer
Gfx *func_80027034(Gfx *);

Gfx *mapChunksRender(Gfx *gfx, void *view, f32 x, f32 y, f32 z, s32 flags) {
    s32 i;
    s32 idx;
    struct RenderEntry *list;
    u8 flag;

    idx = 0;
    flag = (D_807F5FEC != 0) && (gPlayerSlots[gCurrentPlayerIndex].fov == 45.0);
    gDPPipeSync(gfx++);
    if (flags & 0x10) {
        gSPMatrix(gfx++, osVirtualToPhysical(D_807F7074), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
        gSPSegment(gfx++, 6, osVirtualToPhysical((void *)D_807F5DE8));
        gSPSegment(gfx++, 7, osVirtualToPhysical(D_807F5DEC));
        gfx = mapViewDrawPass(gfx, view, 1);
        if (((MapChunkArg *)view)->dl != -1) {
            gDPPipeSync(gfx++);
            gSPDisplayList(gfx++, osVirtualToPhysical((void *)((MapChunkArg *)view)->dl));
        }
        gfx = effectWaterRenderSurfaces(gfx, 0, 0);
        for (i = 0; i < D_807F6C08; i++) {
            if (gMapPortals[D_807F6BF0[i]].dl0 != -1) {
                gDPPipeSync(gfx++);
                gSPDisplayList(gfx++, osVirtualToPhysical((void *)gMapPortals[D_807F6BF0[i]].dl0));
            }
            if (gMapPortals[D_807F6BF0[i]].dl1 != -1) {
                gDPPipeSync(gfx++);
                gSPDisplayList(gfx++, osVirtualToPhysical((void *)gMapPortals[D_807F6BF0[i]].dl1));
            }
        }
        gSPMatrix(gfx++, &D_2000180, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    }
    for (i = D_807F6C80 - 1; i >= 0; i--) {
        idx = D_807F6C58[i];
        if (gMapChunks[idx].state == 1) {
            if (gMapChunks[idx].texAnimPending != 0) {
                mapChunkAnimateTextures(idx);
                gMapChunks[idx].texAnimPending = 0;
            }
            gDPPipeSync(gfx++);
            gDPSetScissor(gfx++, G_SC_NON_INTERLACE, gMapChunks[idx].clipLeft, gMapChunks[idx].clipTop, gMapChunks[idx].clipRight, gMapChunks[idx].clipBottom);
            mapSetClipBounds((s16)gMapChunks[idx].clipLeft, (s16)gMapChunks[idx].clipTop, (s16)gMapChunks[idx].clipRight, (s16)gMapChunks[idx].clipBottom);
            gfx = fogRender(gfx);
            if (flags & 0x10) {
                gfx = mapChunkEmitSegmentCommands(gfx, idx);
                if (gMapChunks[idx].layerDl0 != -1) {
                    gSPMatrix(gfx++, osVirtualToPhysical(D_807F7074), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
                    gSPSegment(gfx++, 6, osVirtualToPhysical(gMapChunks[idx].curVtx));
                    gSPSegment(gfx++, 7, osVirtualToPhysical(D_807F5DEC));
                    gfx = mapChunkEmitLayerDisplayLists(gfx, idx, 0);
                    gDPPipeSync(gfx++);
                    gSPMatrix(gfx++, &D_2000180, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
                }
                if (gMapChunks[idx].layerDl2 != -1) {
                    gSPMatrix(gfx++, osVirtualToPhysical(D_807F7074), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
                    gSPSegment(gfx++, 6, osVirtualToPhysical(gMapChunks[idx].curVtx));
                    gSPSegment(gfx++, 7, osVirtualToPhysical(D_807F5DEC));
                    gfx = mapChunkEmitLayerDisplayLists(gfx, idx, 2);
                    gSPMatrix(gfx++, &D_2000180, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
                }
            }
            gDPPipeSync(gfx++);
            if (!(gGlobalOverlayFlags & 0x01000000)) {
                gfx = billboardRenderQueued(gfx, idx);
            }
            gfx = spriteListRender(gfx, gMapChunks[idx].sprites);
            D_807F6009 = 0xFF;
            if (flag != 0) {
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
                    gSPMatrix(gfx++, osVirtualToPhysical(D_807F7074), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
                    gSPSegment(gfx++, 6, osVirtualToPhysical(gMapChunks[idx].curVtx));
                    gSPSegment(gfx++, 7, osVirtualToPhysical(D_807F5DEC));
                    gfx = mapChunkEmitLayerDisplayLists(gfx, idx, 1);
                    gSPMatrix(gfx++, &D_2000180, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
                    gDPPipeSync(gfx++);
                }
                if (gMapChunks[idx].layerDl3 != -1) {
                    gSPMatrix(gfx++, osVirtualToPhysical(D_807F7074), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
                    gSPSegment(gfx++, 6, osVirtualToPhysical(gMapChunks[idx].curVtx));
                    gSPSegment(gfx++, 7, osVirtualToPhysical(D_807F5DEC));
                    gfx = mapChunkEmitLayerDisplayLists(gfx, idx, 3);
                    gDPPipeSync(gfx++);
                    gSPMatrix(gfx++, &D_2000180, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
                }
            }
        }
    }
    if (flags & 0x10) {
        gSPMatrix(gfx++, osVirtualToPhysical(D_807F7074), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
        gSPSegment(gfx++, 6, osVirtualToPhysical((void *)D_807F5DE8));
        gSPSegment(gfx++, 7, osVirtualToPhysical(D_807F5DEC));
        gfx = mapViewDrawPass(gfx, view, 2);
        if (gGlobalOverlayFlags & 0x1000) {
            gDPPipeSync(gfx++);
            gfx = func_80027034(gfx);
            gSPMatrix(gfx++, osVirtualToPhysical(D_807F7074), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
        }
        gfx = effectWaterRenderSurfaces(gfx, idx, 1);
        gSPMatrix(gfx++, &D_2000180, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
        gDPPipeSync(gfx++);
        gfx = renderDepthSortedTargets(gfx);
    }
    for (i = D_807F6C80 - 1; i >= 0; i--) {
        idx = D_807F6C58[i];
        if (gMapChunks[idx].state == 1) {
            gDPPipeSync(gfx++);
            gDPSetScissor(gfx++, G_SC_NON_INTERLACE, gMapChunks[idx].clipLeft, gMapChunks[idx].clipTop, gMapChunks[idx].clipRight, gMapChunks[idx].clipBottom);
            mapSetClipBounds((s16)gMapChunks[idx].clipLeft, (s16)gMapChunks[idx].clipTop, (s16)gMapChunks[idx].clipRight, (s16)gMapChunks[idx].clipBottom);
            D_807F6009 = 0xFF;
            if (flag != 0) {
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
        gSPMatrix(gfx++, osVirtualToPhysical(D_807F7074), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
        gSPSegment(gfx++, 6, osVirtualToPhysical((void *)D_807F5DE8));
        gSPSegment(gfx++, 7, osVirtualToPhysical(D_807F5DEC));
        gfx = mapViewDrawPass(gfx, view, 3);
        gSPMatrix(gfx++, &D_2000180, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
        gDPPipeSync(gfx++);
    }
    gDPPipeSync(gfx++);
    gDPSetScissor(gfx++, G_SC_NON_INTERLACE, gPlayerSlots[gCurrentPlayerIndex].viewLeft, gPlayerSlots[gCurrentPlayerIndex].viewTop, gPlayerSlots[gCurrentPlayerIndex].viewRight, gPlayerSlots[gCurrentPlayerIndex].viewBottom);
    mapSetClipBounds(gPlayerSlots[gCurrentPlayerIndex].viewLeft, gPlayerSlots[gCurrentPlayerIndex].viewTop, gPlayerSlots[gCurrentPlayerIndex].viewRight, gPlayerSlots[gCurrentPlayerIndex].viewBottom);
    D_807F600C = 0;
    gfx = renderEntryListBuildDisplayList(gfx, D_807F5FFC, x, y, z, flags, -1, 0);
    return billboardRenderQueued(gfx, -1);
}




Gfx *mapChunkEmitLayerDisplayLists(Gfx *p, s32 chunk, u8 layer) {
    MapCell *node;
    Gfx *gfx;
    s32 i;
    s32 found;

    gfx = p;
    if (p == 0) {} // FAKE: rs
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
            gfx = (Gfx *)((u32)gfx | 0); // FAKE: extra gfx reference (raises its colouring priority above the packet pointers)
            if (gMapChunks[chunk].cells[i].dl[layer] == -1) {
                continue;
            }
            found = 0;
            node = gMapCells; p = (Gfx *)&gMapChunks[chunk].cells[i]; do { // LAYOUT: keeps lh a0 before lw v0 // FAKE: reusing the gfx parameter p as the cell pointer preserves its parameter precolor
                if (((MapChunkCell *)p)->id == node->id) {
                    found = 1;
                } else {
                    node++;
                }
            } while (found == 0);
            if (*(u32 *)&gMapCells == 0) {} // FAKE: integer-typed ghost keeps the bound in t1 without coloring the node pointer load
            if (node->visible == 0) {
                continue;
            }
            if ((((MapChunkCell *)p)->layerMask & (1 << layer)) == 0) {
                continue;
            }
            gSPSegment(gfx++, 6, osVirtualToPhysical((void *)gMapChunks[chunk].cells[i].vtx[layer]));
            gDPPipeSync(gfx++);
            gSPDisplayList(gfx++, osVirtualToPhysical((void *)gMapChunks[chunk].cells[i].dl[layer]));
            gDPPipeSync(gfx++);
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
    s32 poly0;
    s32 found;
    s32 k;

    mapChunkIdListAddUnique(chunk);
    i = 0;
    if (gMapPortalSlotCount > 0) {
        do {
            if ((chunk == gMapPortalSlots[i].chunk) && (mapNodeIdListContains(gMapPortalSlots[i].target, depth) == 0)) {
                if (gMapPortalSlots[i].enabled != 0) {
                    gMapPortalSlots[i].seen = 1;
                    id = i / 2;
                    if (mapChunkHitListExcludes(id) != 0) {
                        emitted = mapGridPointEmit(id, x, y, z);
                        if (emitted != 0) {
                            clipRight = right;
                            clipLeft = left;
                            clipTop = top;
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
                                        mapChunkIdListAddUniqueLimited(k);
                                    }
                                }
                            }
                            if (actorTargetTableContainsId(i) != 0) {
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
                            id = gMapPortalSlots[i].target;
                            if (gMapChunkEnabled[id] != 0) {
                                gMapChunks[id].state = 1;
                                gMapChunks[id].playerMask |= 1 << gCurrentPlayerIndex;
                                mapRectIntersect(clipLeft, clipTop, clipRight, clipBottom, gMapChunks[id].clipLeft, gMapChunks[id].clipTop, gMapChunks[id].clipRight, gMapChunks[id].clipBottom, &outLeft, &outTop, &outRight, &outBottom);
                                gMapChunks[id].clipLeft = outLeft;
                                gMapChunks[id].clipTop = outTop;
                                gMapChunks[id].clipRight = outRight;
                                gMapChunks[id].clipBottom = outBottom;
                                D_807F6C30[depth] = chunk;
                                mapChunkTraversePortals(id, depth + 1, clipLeft, clipTop, clipRight, clipBottom, x, y, z);
                            }
                        }
                    }
                }
            }
            i++;
        } while (i < gMapPortalSlotCount);
    }
}


s32 mapChunkHitListExcludes(s32 id) {
    u8 *p = D_807F7060;

    if (D_807F7070 > 0) {
        do {
            if (id == *p) {
                return 0;
            } else {
                p++;
            }
        } while (p < D_807F7060 + D_807F7070);
    }
    return 1;
}


void mapChunkIdListAddUniqueLimited(s32 id) {
    s32 i = 0;

    while (i < D_807F6C08) {
        if (id == D_807F6BF0[i]) {
            return;
        }
        i++;
    }
    if (i == 0xC) {
        return;
    }
    D_807F6BF0[D_807F6C08] = id;
    D_807F6C08++;
}


void mapChunkIdListAddUnique(s16 id) {
    s32 i = 0;

    while (i < D_807F6C80) {
        if (id == D_807F6C58[i]) {
            return;
        }
        i++;
    }
    D_807F6C58[D_807F6C80] = id;
    D_807F6C80++;
}


typedef struct MapGridQuad {
    /* 0x00 */ f32 x[4];
    /* 0x10 */ f32 y[4];
    /* 0x20 */ f32 px;
    /* 0x24 */ f32 py;
} MapGridQuad;




u8 mapGridPointEmit(s32 tri, f32 x, f32 y, f32 z) {
    f32 h;
    f32 dist;
    f32 px;
    f32 py;
    f32 pz;
    MapGridQuad quad;
    f32 nx;
    f32 ny;
    f32 nz;

    nz = (f32)gMapGridTrianglePlanes[tri].nz;
    ny = (f32)gMapGridTrianglePlanes[tri].ny;
    nx = (f32)gMapGridTrianglePlanes[tri].nx;
    h = (f32)gMapGridTrianglePlanes[tri].d;
    dist = (h + (nx * x + ny * y + nz * z)) / gMapGridTrianglePlanes[tri].len;
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
            quad->x[k] = D_807F6C14[tri].x[k];
            quad->y[k] = D_807F6C14[tri].y[k];
        }
        break;
    case 1:
        quad->px = x;
        quad->py = z;
        for (k = 0; k < 4; k++) {
            quad->x[k] = D_807F6C14[tri].x[k];
            quad->y[k] = D_807F6C14[tri].z[k];
        }
        break;
    case 2:
        quad->px = y;
        quad->py = z;
        for (k = 0; k < 4; k++) {
            quad->x[k] = D_807F6C14[tri].y[k];
            quad->y[k] = D_807F6C14[tri].z[k];
        }
        break;
    }
}

void mapGridPlaneProjectPoint(s32 tri, f32 x, f32 y, f32 z, f32 *outX, f32 *outY, f32 *outZ) {
    f32 n10;
    f32 t;
    f32 n0;
    f32 n8;
    f32 a;
    a = (f32)(-gMapGridTrianglePlanes[tri].d);
    n8 = (f32)gMapGridTrianglePlanes[tri].ny;
    n0 = (f32)gMapGridTrianglePlanes[tri].nx;
    n10 = (f32)gMapGridTrianglePlanes[tri].nz;
    t = (a - (n10 * z + (n0 * x + n8 * y))) / gMapGridTrianglePlanes[tri].lenSq;
    *outX = (f32)gMapGridTrianglePlanes[tri].nx * t + x;
    *outY = (f32)gMapGridTrianglePlanes[tri].ny * t + y;
    *outZ = (f32)gMapGridTrianglePlanes[tri].nz * t + z;
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

s32 mapGridPointPlaneDistanceWithin(s32 tri, f32 x, f32 y, f32 z, s16 maxDist) {
    f32 v;

    v = ((f32)gMapGridTrianglePlanes[tri].d + ((f32)gMapGridTrianglePlanes[tri].nx * x + (f32)gMapGridTrianglePlanes[tri].ny * y + (f32)gMapGridTrianglePlanes[tri].nz * z)) / gMapGridTrianglePlanes[tri].len;
    if (v < 0.0) {
        v = 0.0 - v;
    }
    return (v <= (f32)maxDist) & 0xFF;
}



s32 mapGridQuadClipToFrustum(s32 tri, f32 x, f32 y, f32 z)
{
    s32 k;
    s32 n2;
    s32 n1;

    n1 = 0;
    n2 = 0;
    for (k = 0; k < 4; k++) {
        D_807F6C88[k].x = D_807F6C14[tri].x[k];
        D_807F6C88[k].y = D_807F6C14[tri].y[k];
        D_807F6C88[k].z = D_807F6C14[tri].z[k];
    }
    mapPolyClipToFrustumPlane(D_807F6C88, D_807F6E68, 4, &n2, 0);
    if (n2 == 0) {
        return 0;
    }
    mapPolyClipToFrustumPlane(D_807F6E68, D_807F6F58, n2, &n1, 1);
    if (n1 == 0) {
        return 0;
    }
    mapPolyClipToFrustumPlane(D_807F6F58, D_807F6E68, n1, &n2, 2);
    if (n2 == 0) {
        return 0;
    }
    mapPolyClipToFrustumPlane(D_807F6E68, D_807F6F58, n2, &n1, 3);
    if (n1 == 0) {
        return 0;
    }
    mapPolyClipToFrustumPlane(D_807F6F58, D_807F6D78, n1, &n2, 4);
    if (n2 < 3) {
        n2 = 0;
    }
    return n2;
}


void mapPolyClipToFrustumPlane(MapVec3 *in, MapVec3 *out, s32 count, s32 *outCount, s32 planeIdx) {
    f32 hit[3];
    PlanePoly *plane;
    MapVec3 *prev;
    MapVec3 *cur;
    s32 n;
    s32 i;
    f64 curDist;
    f64 prevDist;

    cur = in;
    n = 0;
    prev = cur + (count - 1);
    plane = &gFrustumPlanes[planeIdx];
    for (i = 0; i < count; i++, prev = cur) {
        cur = &in[i];
        curDist = plane->d + (((plane->a * cur->x) + (plane->b * cur->y)) + (plane->c * cur->z));
        prevDist = plane->d + (((plane->a * prev->x) + (plane->b * prev->y)) + (plane->c * prev->z));
        if (curDist >= 0.0) {
            if (prevDist >= 0.0) {
                memcpy(&out[n], cur, 0xC);
                n++;
            } else {
                mapFrustumPlaneIntersectEdge(&prev->x, &cur->x, planeIdx, hit);
                memcpy(&out[n++], hit, 0xC);
                memcpy(&out[n++], cur, 0xC);
            }
        } else if (prevDist >= 0.0) {
            mapFrustumPlaneIntersectEdge(&prev->x, &cur->x, planeIdx, hit);
            memcpy(&out[n++], hit, 0xC);
        }
    }
    *outCount = n;
}

void mapFrustumPlaneIntersectEdge(f32 *a, f32 *b, s32 planeIdx, f32 *out) {
    f32 pad[4];
    f32 bx;
    f64 s;
    f64 dist;

    dist = (((gFrustumPlanes[planeIdx].a * a[0]) + (gFrustumPlanes[planeIdx].b * a[1])) + (gFrustumPlanes[planeIdx].c * a[2])) + gFrustumPlanes[planeIdx].d;
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

    *outLeft = gPlayerSlots[gCurrentPlayerIndex].viewRight;
    *outTop = gPlayerSlots[gCurrentPlayerIndex].viewBottom;
    *outRight = gPlayerSlots[gCurrentPlayerIndex].viewLeft;
    *outBottom = gPlayerSlots[gCurrentPlayerIndex].viewTop;
    flag = 0;
    for (i = 0; i < count; i++) {
        flag |= camProjectToScreen(D_807F6D78[i].x, D_807F6D78[i].y, D_807F6D78[i].z, &sx, &sy, 0, 1.0f, gCurrentPlayerIndex); x = (s16)sx; y = (s16)sy; // LAYOUT: same-line statements steer sra scheduling
        if (x < gPlayerSlots[gCurrentPlayerIndex].viewLeft) {
            x = gPlayerSlots[gCurrentPlayerIndex].viewLeft;
        }
        if (y < gPlayerSlots[gCurrentPlayerIndex].viewTop) {
            y = gPlayerSlots[gCurrentPlayerIndex].viewTop;
        }
        if (gPlayerSlots[gCurrentPlayerIndex].viewRight < x) {
            x = gPlayerSlots[gCurrentPlayerIndex].viewRight;
        }
        if (gPlayerSlots[gCurrentPlayerIndex].viewBottom < y) {
            y = gPlayerSlots[gCurrentPlayerIndex].viewBottom;
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

    p = (u8 *)assetLoad(0x14, id, 1, 1);
    mapNodeAssetParse(p);
    if (p != NULL) {
        assetFreeBuffer(p, 0xBED, 0x22);
    }
}


#define MAP_ZONE_SLOT (*(MapZone **)slot)
void mapNodeAssetParse(u8 *data) {
    s32 *word;
    s32 *end;
    s16 n;
    s32 i;
    s16 idx;
    u8 *p;
    s32 slot; // FAKE: integer-typed slot address (a MapZone ** local recolours the parse loop)
    void *zone;

    word = (s32 *)(&gMapCellBoxes + 1); end = (s32 *)&D_807F7138; // FAKE: same-line statements steer lui/addiu scheduling; the neighbour-symbol spelling keeps this address a separate web from the loop's table base
    do {
        *word++ = 0;
    } while (word < end);
    if (data == NULL) {
        return;
    }
    n = *(s16 *)data;
    p = data + 2;
    for (i = 0; i < n; i++) {
        idx = *(s16 *)p;
        p += 2;
        zone = heapAlloc(0x6C);
        slot = (s32)&gMapZones[idx];
        MAP_ZONE_SLOT = zone;
        MAP_ZONE_SLOT->minY = 0x7FFF;
        MAP_ZONE_SLOT->maxY = -0x8000;
        MAP_ZONE_SLOT->tris = NULL;
        MAP_ZONE_SLOT->vertCount = *(s16 *)p;
        p += 2;
        MAP_ZONE_SLOT->verts = heapAlloc((u32)MAP_ZONE_SLOT->vertCount * 6);
        memcpy(MAP_ZONE_SLOT->verts, p, (u32)MAP_ZONE_SLOT->vertCount * 6);
        p += ((u32)MAP_ZONE_SLOT->vertCount * 6 / 2) * 2;
        MAP_ZONE_SLOT->height = *(s16 *)p;
        MAP_ZONE_SLOT->exitCount = *(s16 *)(p + 2);
        p += 4;
        memcpy(MAP_ZONE_SLOT->exitCells, p, 0x20);
        MAP_ZONE_SLOT->enterCount = *(s16 *)(p + 0x20);
        p += 0x22;
        memcpy(MAP_ZONE_SLOT->enterCells, p, 0x20);
        MAP_ZONE_SLOT->linkCount = *(s16 *)(p + 0x20);
        p += 0x22;
        memcpy(MAP_ZONE_SLOT->links, p, 0x10);
        p += 0x10;
        mapFaceBuildTriangleFan(idx);
    }
}
#undef MAP_ZONE_SLOT

extern s16 D_807F7358;
extern s16 D_807F735A;
extern s16 D_807F735C;
extern s16 D_807F735E;


s16 mapObjectCollectIdsByType(s8 type, s8 *out, s16 max) {
    s16 i;
    s16 n;

    n = 0;
    if (type == -1) {
        return 0;
    }
    for (i = 0; i < gMapPortalSlotCount && n < max; ) {
        if (gMapPortalSlots[i].chunk == type) {
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
    /* 0x00C */ s32 frame;
    /* 0x010 */ u8 active;
    /* 0x011 */ u8 visible;
    /* 0x012 */ u8 pad12[0x2];
} MapSearchEntry;

extern u8 D_807F72A0;
extern u8 D_807F72B4;
extern MapSearchEntry D_807F72B8[];

void mapSearchTableReset(void) {
    s32 i;

    D_807F72A0 = 0;
    D_807F72B4 = 0; for (i = 0; i < 8; i++) { // LAYOUT: one line keeps as1 from moving the sb D_807F72B4 ahead of the loop setup
        D_807F72B8[i].active = 0;
    }
}

extern MapSearchEntry gMapSearchTable[];


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

    for (i = 0; i < 10; i++) {
        if (gMapSearchTable[i].active != 0) {
            if (gFrameCounter == gMapSearchTable[i].frame) {
                if ((f32)zbufferDepthToDistance((s16)zbufferReadDepth(gMapSearchTable[i].x, gMapSearchTable[i].y)) <= (f32)gMapSearchTable[i].maxDepth) {
                    gMapSearchTable[i].visible = 1;
                } else {
                    gMapSearchTable[i].visible = 0;
                }
            }
        }
        if ((u32)(gFrameCounter - gMapSearchTable[i].frame) >= 3) {
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


void mapSetClipBounds(left, top, right, bottom)
s16 left;
s16 top;
s16 right;
s16 bottom;
{
    D_807F7358 = left;
    D_807F735A = top;
    D_807F735C = right;
    D_807F735E = bottom;
}


s32 mapPointOutsideClipBounds(f32 x, f32 y, f32 z, u8 marginX, u8 marginY) {
    f32 sx;
    f32 sy;
    s16 px;
    s16 py;
    s16 x0;
    s16 x1;
    s16 z0;
    s16 z1;
    f32 dist;
    f32 t;

    camProjectToScreen(x, y, z, &sx, &sy, 0, 1.0f, gCurrentPlayerIndex);
    px = (s16)sx;
    py = (s16)sy;
    dist = sqrtf((x - gPlayerSlots[gCurrentPlayerIndex].posX) * (x - gPlayerSlots[gCurrentPlayerIndex].posX)
                 + (y - gPlayerSlots[gCurrentPlayerIndex].posY) * (y - gPlayerSlots[gCurrentPlayerIndex].posY)
                 + (z - gPlayerSlots[gCurrentPlayerIndex].posZ) * (z - gPlayerSlots[gCurrentPlayerIndex].posZ));
    if (dist < 90.0f) {
        return 0;
    }
    x0 = 20;
    x1 = 20;
    z0 = 0;
    t = (dist - 60.0f) / 120.0f;
    if (dist >= 180.0f) {
        z1 = 50;
    } else if (t > 0.0) {
        x0 = -60.0f * t + 80.0f;
        x1 = -60.0f * t + 80.0f;
        z0 = -130.0f * t + 130.0f;
        z1 = -80.0f * t + 130.0f;
    } else {
        x0 = 80;
        x1 = 80;
        z0 = 130;
        z1 = 130;
    }
    if ((px < D_807F7358 - x0 - marginX) || (D_807F735C + x1 + marginX < px)
        || (py < D_807F735A - z0 - marginY) || (D_807F735E + z1 + marginY < py)) {
        return 1;
    }
    return 0;
}

