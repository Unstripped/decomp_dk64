#include "common.h"
#include "actor.h"
#include "map.h"
#include "proto/global/15050.h"
#include "proto/global/166A0.h"
#include "proto/global/67890.h"
#include "proto/global/69E60.h"
#include "proto/global/6AD90.h"


typedef struct ActorTargetQuad {
    /* 0x00 */ f32 texCoords[4][2];
    /* 0x20 */ s16 x[4];
    /* 0x28 */ s16 y[4];
    /* 0x30 */ s16 z[4];
    /* 0x38 */ s16 portalSlot;
    /* 0x3A */ s16 fadeStart;
    /* 0x3C */ s16 fadeEnd;
    /* 0x3E */ u8 alphaNear;
    /* 0x3F */ u8 alphaFar;
} ActorTargetQuad; // size = 0x40

typedef struct ActorTargetDistanceEntry {
    /* 0x00 */ f32 distance;
    /* 0x04 */ f32 centerX;
    /* 0x08 */ f32 centerY;
    /* 0x0C */ f32 centerZ;
    /* 0x10 */ u8 alpha;
    /* 0x11 */ u8 visible;
    /* 0x12 */ u8 scrollS;
    /* 0x13 */ u8 scrollT;
} ActorTargetDistanceEntry; // size = 0x14

extern ActorTargetQuad *gActorTargetQuads;
extern ActorTargetDistanceEntry *gActorTargetStates;
extern s32 gActorTargetCount;
extern Vtx *gActorTargetVerts;
extern void *gActorTargetTexture;
extern u8 *gMapPortalVisible;

#define TARGET_VTX(offset) ((Vtx *)((u8 *)gActorTargetVerts + (offset)))

void actorTargetTableLoad(MapFileHeader *header) {
    s32 j;
    s32 start[3];
    s32 i;
    s32 vtxOffset;
    u8 *base;

    base = (u8 *)header;
    start[0] = 0;
    gActorTargetCount = *(s32 *)(base + header->unk50);
    if (gActorTargetCount != 0) {
        gActorTargetQuads = (ActorTargetQuad *)(base + header->unk50 + 4);
        gActorTargetStates = heapAlloc(gActorTargetCount * sizeof(ActorTargetDistanceEntry));
        gActorTargetVerts = heapAlloc(gActorTargetCount << 6);
        i = 0;
        if (gActorTargetCount > 0) {
            vtxOffset = start[0] * sizeof(Vtx); // FAKE: zero stored to a stack array and reloaded (sw/lw 0x18(sp)) seeds the vertex offset
            do {
                for (j = 0; j < 4; j++) {
                    TARGET_VTX(vtxOffset)->v.ob[0] = gActorTargetQuads[i].x[j];
                    TARGET_VTX(vtxOffset)->v.ob[1] = gActorTargetQuads[i].y[j];
                    TARGET_VTX(vtxOffset)->v.ob[2] = gActorTargetQuads[i].z[j];
                    TARGET_VTX(vtxOffset)->v.tc[0] = (s32)(gActorTargetQuads[i].texCoords[j][0] * 50.0f) << 5;
                    TARGET_VTX(vtxOffset)->v.tc[1] = (s32)(gActorTargetQuads[i].texCoords[j][1] * 50.0f) << 5;
                    vtxOffset += sizeof(Vtx);
                }

                gActorTargetStates[i].centerX = (gActorTargetQuads[i].x[0] + gActorTargetQuads[i].x[1] + gActorTargetQuads[i].x[2] + gActorTargetQuads[i].x[3]) * 0.25;
                gActorTargetStates[i].centerY = (gActorTargetQuads[i].y[0] + gActorTargetQuads[i].y[1] + gActorTargetQuads[i].y[2] + gActorTargetQuads[i].y[3]) * 0.25;
                gActorTargetStates[i].centerZ = (gActorTargetQuads[i].z[0] + gActorTargetQuads[i].z[1] + gActorTargetQuads[i].z[2] + gActorTargetQuads[i].z[3]) * 0.25;
                i++;
            } while (i < gActorTargetCount);
        }
        gActorTargetTexture = assetLoad(7, 0x3C7, 1, 0);
    }
}

s32 actorTargetTableHasPortalSlot(s32 portalSlot) {
    s32 i;

    for (i = 0; i < gActorTargetCount; i++) {
        if (portalSlot == gActorTargetQuads[i].portalSlot) {
            return 1;
        }
    }
    return 0;
}

void actorCalculateTargetDistancesAndAngles(f32 camX, f32 camY, f32 camZ) {
    s32 i;
    f32 ratio;
    f32 dist2d;
    s16 angle;
    f32 dz, dx;

    for (i = 0; i < gActorTargetCount; i++) {
        gActorTargetStates[i].visible = 0;
        if (gMapPortalVisible[gActorTargetQuads[i].portalSlot] != 0) {
            gActorTargetStates[i].distance = sqrtf((((camX - gActorTargetStates[i].centerX) * (camX - gActorTargetStates[i].centerX)) + ((camY - gActorTargetStates[i].centerY) * (camY - gActorTargetStates[i].centerY))) + ((camZ - gActorTargetStates[i].centerZ) * (camZ - gActorTargetStates[i].centerZ)));
            ratio = (gActorTargetStates[i].distance - gActorTargetQuads[i].fadeStart) / (gActorTargetQuads[i].fadeEnd - gActorTargetQuads[i].fadeStart);
            if (ratio > 1.0) {
                gActorTargetStates[i].alpha = gActorTargetQuads[i].alphaFar;
            } else if (ratio < 0.0) {
                gActorTargetStates[i].alpha = gActorTargetQuads[i].alphaNear;
            } else {
                gActorTargetStates[i].alpha = gActorTargetQuads[i].alphaNear + (gActorTargetQuads[i].alphaFar - gActorTargetQuads[i].alphaNear) * ratio;
            }
            gActorTargetStates[i].scrollS = (s32)(mathAngleBetweenPoints2D(camX, camZ, gActorTargetStates[i].centerX, gActorTargetStates[i].centerZ) * 0.5) % 255;
            dz = camZ - gActorTargetStates[i].centerZ;
            dx = camX - gActorTargetStates[i].centerX;
            dist2d = sqrtf((dz * dz) + (dx * dx));
            angle = (mathAtan2(gActorTargetStates[i].centerY - camY, dist2d) * 2048.0) / 3.1415927410125732;
            gActorTargetStates[i].scrollT = (s32)(angle * 0.5) % 255;
            gActorTargetStates[i].visible = 1;
        } else {
            gActorTargetStates[i].visible = 0;
        }
    }
}

Gfx *renderDepthSortedTargets(Gfx *glist) {
    s32 pad;
    s32 furthestIdx;
    f32 dist;
    f32 maxDist;
    f32 bestDist;
    s32 found;
    s32 i;

    maxDist = 100000000.0f;
    do {
        found = 0;
        bestDist = 0.0f;
        for (i = 0; i < gActorTargetCount; i++) {
            if (gActorTargetStates[i].visible != 0) {
                dist = gActorTargetStates[i].distance;
                if ((dist < maxDist) && (bestDist < dist)) {
                    furthestIdx = i;
                    bestDist = dist;
                    found = 1;
                }
            }
        }
        maxDist = bestDist;
        if (found) {
            glist = renderTargetQuad(glist, furthestIdx);
        }
    } while (found);
    return glist;
}

Gfx *renderTargetQuad(Gfx *glist, s32 targetIdx) {
    gDPPipeSync(glist++);
    gDPSetRenderMode(glist++, G_RM_ZB_XLU_SURF, G_RM_ZB_XLU_SURF2);
    gDPSetCombineMode(glist++, G_CC_MODULATEI_PRIM, G_CC_MODULATEI_PRIM);
    gDPSetCycleType(glist++, G_CYC_1CYCLE);
    gSPClearGeometryMode(glist++, 0xFFFFFFFF);
    gSPSetGeometryMode(glist++, G_ZBUFFER | G_SHADE | G_SHADING_SMOOTH);
    gDPSetPrimColor(glist++, 0, 0, 100, 100, 100, gActorTargetStates[targetIdx].alpha);
    gSPTexture(glist++, 0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON);
    gDPLoadTextureBlock(glist++, gActorTargetTexture, G_IM_FMT_IA, G_IM_SIZ_8b, 64, 64, 0, G_TX_WRAP, G_TX_WRAP, 6, 6, 0, 0);
    gDPSetTileSize(glist++, 0, gActorTargetStates[targetIdx].scrollS, gActorTargetStates[targetIdx].scrollT, 63 << 2, 63 << 2);
    gSPVertex(glist++, osVirtualToPhysical(&gActorTargetVerts[targetIdx * 4]), 4, 0);
    gSP2Triangles(glist++, 0, 1, 2, 0, 0, 2, 3, 0);
    gDPPipeSync(glist++);
    return glist;
}
