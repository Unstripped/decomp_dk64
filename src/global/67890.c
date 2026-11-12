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

extern ActorTargetQuad *D_807F93F0;
extern ActorTargetDistanceEntry *D_807F93F4;
extern s32 D_807F93F8;
extern Vtx *D_807F93FC;
extern void *D_807F9400;
extern u8 *gMapPortalVisible;

#define TARGET_VTX(offset) ((Vtx *)((u8 *)D_807F93FC + (offset)))

void actorTargetTableLoad(MapFileHeader *header) {
    s32 j;
    s32 start[3];
    s32 i;
    s32 vtxOffset;
    u8 *base;

    base = (u8 *)header;
    start[0] = 0;
    D_807F93F8 = *(s32 *)(base + header->unk50);
    if (D_807F93F8 != 0) {
        D_807F93F0 = (ActorTargetQuad *)(base + header->unk50 + 4);
        D_807F93F4 = heapAlloc(D_807F93F8 * sizeof(ActorTargetDistanceEntry));
        D_807F93FC = heapAlloc(D_807F93F8 << 6);
        i = 0;
        if (D_807F93F8 > 0) {
            vtxOffset = start[0] * sizeof(Vtx); // FAKE: zero stored to a stack array and reloaded (sw/lw 0x18(sp)) seeds the vertex offset
            do {
                for (j = 0; j < 4; j++) {
                    TARGET_VTX(vtxOffset)->v.ob[0] = D_807F93F0[i].x[j];
                    TARGET_VTX(vtxOffset)->v.ob[1] = D_807F93F0[i].y[j];
                    TARGET_VTX(vtxOffset)->v.ob[2] = D_807F93F0[i].z[j];
                    TARGET_VTX(vtxOffset)->v.tc[0] = (s32)(D_807F93F0[i].texCoords[j][0] * 50.0f) << 5;
                    TARGET_VTX(vtxOffset)->v.tc[1] = (s32)(D_807F93F0[i].texCoords[j][1] * 50.0f) << 5;
                    vtxOffset += sizeof(Vtx);
                }

                D_807F93F4[i].centerX = (D_807F93F0[i].x[0] + D_807F93F0[i].x[1] + D_807F93F0[i].x[2] + D_807F93F0[i].x[3]) * 0.25;
                D_807F93F4[i].centerY = (D_807F93F0[i].y[0] + D_807F93F0[i].y[1] + D_807F93F0[i].y[2] + D_807F93F0[i].y[3]) * 0.25;
                D_807F93F4[i].centerZ = (D_807F93F0[i].z[0] + D_807F93F0[i].z[1] + D_807F93F0[i].z[2] + D_807F93F0[i].z[3]) * 0.25;
                i++;
            } while (i < D_807F93F8);
        }
        D_807F9400 = assetLoad(7, 0x3C7, 1, 0);
    }
}

s32 actorTargetTableContainsId(s32 portalSlot) {
    s32 i;

    for (i = 0; i < D_807F93F8; i++) {
        if (portalSlot == D_807F93F0[i].portalSlot) {
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

    for (i = 0; i < D_807F93F8; i++) {
        D_807F93F4[i].visible = 0;
        if (gMapPortalVisible[D_807F93F0[i].portalSlot] != 0) {
            D_807F93F4[i].distance = sqrtf((((camX - D_807F93F4[i].centerX) * (camX - D_807F93F4[i].centerX)) + ((camY - D_807F93F4[i].centerY) * (camY - D_807F93F4[i].centerY))) + ((camZ - D_807F93F4[i].centerZ) * (camZ - D_807F93F4[i].centerZ)));
            ratio = (D_807F93F4[i].distance - D_807F93F0[i].fadeStart) / (D_807F93F0[i].fadeEnd - D_807F93F0[i].fadeStart);
            if (ratio > 1.0) {
                D_807F93F4[i].alpha = D_807F93F0[i].alphaFar;
            } else if (ratio < 0.0) {
                D_807F93F4[i].alpha = D_807F93F0[i].alphaNear;
            } else {
                D_807F93F4[i].alpha = D_807F93F0[i].alphaNear + (D_807F93F0[i].alphaFar - D_807F93F0[i].alphaNear) * ratio;
            }
            D_807F93F4[i].scrollS = (s32)(mathAngleBetweenPoints2D(camX, camZ, D_807F93F4[i].centerX, D_807F93F4[i].centerZ) * 0.5) % 255;
            dz = camZ - D_807F93F4[i].centerZ;
            dx = camX - D_807F93F4[i].centerX;
            dist2d = sqrtf((dz * dz) + (dx * dx));
            angle = (mathAtan2(D_807F93F4[i].centerY - camY, dist2d) * 2048.0) / 3.1415927410125732;
            D_807F93F4[i].scrollT = (s32)(angle * 0.5) % 255;
            D_807F93F4[i].visible = 1;
        } else {
            D_807F93F4[i].visible = 0;
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
        for (i = 0; i < D_807F93F8; i++) {
            if (D_807F93F4[i].visible != 0) {
                dist = D_807F93F4[i].distance;
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
    gDPSetPrimColor(glist++, 0, 0, 100, 100, 100, D_807F93F4[targetIdx].alpha);
    gSPTexture(glist++, 0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON);
    gDPLoadTextureBlock(glist++, D_807F9400, G_IM_FMT_IA, G_IM_SIZ_8b, 64, 64, 0, G_TX_WRAP, G_TX_WRAP, 6, 6, 0, 0);
    gDPSetTileSize(glist++, 0, D_807F93F4[targetIdx].scrollS, D_807F93F4[targetIdx].scrollT, 63 << 2, 63 << 2);
    gSPVertex(glist++, osVirtualToPhysical(&D_807F93FC[targetIdx * 4]), 4, 0);
    gSP2Triangles(glist++, 0, 1, 2, 0, 0, 2, 3, 0);
    gDPPipeSync(glist++);
    return glist;
}
