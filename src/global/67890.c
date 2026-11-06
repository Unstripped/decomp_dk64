#include "common.h"
#include "actor.h"

struct ActorTargetEntry;
struct ActorTargetDistanceEntry;

typedef struct ActorTargetQuadRaw {
    f32 unk0[8];
    s16 unk20[12];
    s16 pad38[4];
} ActorTargetQuadRaw;

typedef struct ActorTargetDistRaw {
    f32 unk0;
    f32 unk4;
    f32 unk8;
    f32 unkC;
    u8 pad10[4];
} ActorTargetDistRaw;

typedef struct ActorTargetVtx {
    s16 ob[3];
    s16 flag;
    s16 tc[2];
    u8 cn[4];
} ActorTargetVtx;

extern struct ActorTargetEntry *D_807F93F0;
extern struct ActorTargetDistanceEntry *D_807F93F4;
extern s32 D_807F93F8;
extern ActorTargetVtx *D_807F93FC;
extern u32 D_807F9400;

void *heapAlloc(s32);
s32 assetLoad(s32, s32, s32, s32);

#define TARGET_QUAD(i) (&((ActorTargetQuadRaw *)D_807F93F0)[i])
#define TARGET_VTX(off) ((ActorTargetVtx *)((u8 *)D_807F93FC + (off)))

void actorTargetTableLoad(void *assetData) {
    s32 j;
    s32 sp[3];
    s32 i;
    s32 vtx_off;
    u8 *p;

    p = assetData;
    sp[0] = 0;
    D_807F93F8 = *(s32 *)(p + *(s32 *)(p + 0x50));
    if (D_807F93F8 != 0) {
        D_807F93F0 = (struct ActorTargetEntry *)(p + *(s32 *)(p + 0x50) + 4);
        D_807F93F4 = heapAlloc(D_807F93F8 * 0x14);
        D_807F93FC = heapAlloc(D_807F93F8 << 6);
        i = 0;
        if (D_807F93F8 > 0) {
            vtx_off = sp[0] * 0x10;
            do {
                for (j = 0; j < 4; j++) {
                    TARGET_VTX(vtx_off)->ob[0] = TARGET_QUAD(i)->unk20[j];
                    TARGET_VTX(vtx_off)->ob[1] = TARGET_QUAD(i)->unk20[j + 4];
                    TARGET_VTX(vtx_off)->ob[2] = TARGET_QUAD(i)->unk20[j + 8];
                    TARGET_VTX(vtx_off)->tc[0] = (s32)(TARGET_QUAD(i)->unk0[j * 2] * 50.0f) << 5;
                    TARGET_VTX(vtx_off)->tc[1] = (s32)(TARGET_QUAD(i)->unk0[j * 2 + 1] * 50.0f) << 5;
                    vtx_off += 0x10;
                }

                ((ActorTargetDistRaw *)D_807F93F4)[i].unk4 = (f32)((f64)(TARGET_QUAD(i)->unk20[0] + TARGET_QUAD(i)->unk20[1] + TARGET_QUAD(i)->unk20[2] + TARGET_QUAD(i)->unk20[3]) * 0.25);
                ((ActorTargetDistRaw *)D_807F93F4)[i].unk8 = (f32)((f64)(TARGET_QUAD(i)->unk20[4] + TARGET_QUAD(i)->unk20[5] + TARGET_QUAD(i)->unk20[6] + TARGET_QUAD(i)->unk20[7]) * 0.25);
                ((ActorTargetDistRaw *)D_807F93F4)[i].unkC = (f32)((f64)(TARGET_QUAD(i)->unk20[8] + TARGET_QUAD(i)->unk20[9] + TARGET_QUAD(i)->unk20[10] + TARGET_QUAD(i)->unk20[11]) * 0.25);
                i++;
            } while (i < D_807F93F8);
        }
        D_807F9400 = assetLoad(7, 0x3C7, 1, 0);
    }
}

typedef struct ActorTargetEntry {
    u8 pad0[0x38];
    s16 unk38;
    u8 pad3A[6];
} ActorTargetEntry;

extern ActorTargetEntry *D_807F93F0;

s32 actorTargetTableContainsId(s32 targetId) {
    s32 i;

    for (i = 0; i < D_807F93F8; i++) {
        if (targetId == D_807F93F0[i].unk38) {
            return 1;
        }
    }
    return 0;
}

typedef struct ActorTargetQuadEntry {
    f32 unk0[8];
    s16 unk20[12];
    s16 unk38;
    s16 unk3A;
    s16 unk3C;
    u8 unk3E;
    u8 unk3F;
} ActorTargetQuadEntry;

typedef struct ActorTargetDistanceEntry {
    f32 unk0;
    f32 unk4;
    f32 unk8;
    f32 unkC;
    u8 unk10;
    u8 unk11;
    s8 unk12;
    s8 unk13;
} ActorTargetDistanceEntry;

extern u8 *D_807F6C2C;
extern ActorTargetDistanceEntry *D_807F93F4;
f32 func_80611BB4(f32, f32);
s32 mathAngleBetweenPoints2D(f32, f32, f32, f32);

void actorCalculateTargetDistancesAndAngles(f32 camX, f32 camY, f32 camZ) {
    s32 i;
    f32 ratio;
    f32 dist2d;
    s16 angle;
    f32 dz, dx;

    for (i = 0; i < D_807F93F8; i++) {
        D_807F93F4[i].unk11 = 0;
        if (D_807F6C2C[((ActorTargetQuadEntry *)D_807F93F0)[i].unk38] != 0) {
            D_807F93F4[i].unk0 = sqrtf((((camX - D_807F93F4[i].unk4) * (camX - D_807F93F4[i].unk4)) + ((camY - D_807F93F4[i].unk8) * (camY - D_807F93F4[i].unk8))) + ((camZ - D_807F93F4[i].unkC) * (camZ - D_807F93F4[i].unkC)));
            ratio = (D_807F93F4[i].unk0 - (f32)((ActorTargetQuadEntry *)D_807F93F0)[i].unk3A) / (f32)(((ActorTargetQuadEntry *)D_807F93F0)[i].unk3C - ((ActorTargetQuadEntry *)D_807F93F0)[i].unk3A);
            if ((f64)ratio > 1.0) {
                D_807F93F4[i].unk10 = ((ActorTargetQuadEntry *)D_807F93F0)[i].unk3F;
            } else if ((f64)ratio < 0.0) {
                D_807F93F4[i].unk10 = ((ActorTargetQuadEntry *)D_807F93F0)[i].unk3E;
            } else {
                u8 e3E = ((ActorTargetQuadEntry *)D_807F93F0)[i].unk3E;
                f32 fa = (u32)e3E;
                D_807F93F4[i].unk10 = (u8)(u32)(((f32)(((ActorTargetQuadEntry *)D_807F93F0)[i].unk3F - e3E) * ratio) + fa);
            }
            D_807F93F4[i].unk12 = (s32)((f64)mathAngleBetweenPoints2D(camX, camZ, D_807F93F4[i].unk4, D_807F93F4[i].unkC) * 0.5) % 255;
            dz = camZ - D_807F93F4[i].unkC;
            dx = camX - D_807F93F4[i].unk4;
            dist2d = sqrtf((dz * dz) + (dx * dx));
            angle = ((f64)func_80611BB4(D_807F93F4[i].unk8 - camY, dist2d) * 2048.0) / 3.1415927410125732;
            D_807F93F4[i].unk13 = (s32)((f64)angle * 0.5) % 255;
            D_807F93F4[i].unk11 = 1;
        } else {
            D_807F93F4[i].unk11 = 0;
        }
    }
}

Gfx *renderTargetQuad(Gfx *, s32);

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
        i = 0;
        if (D_807F93F8 > 0) {
            do {
                if (D_807F93F4[i].unk11 != 0) {
                    dist = D_807F93F4[i].unk0;
                    if ((dist < maxDist) && (bestDist < dist)) {
                        furthestIdx = i;
                        bestDist = dist;
                        found = 1;
                    }
                }
                i += 1;
            } while (i < D_807F93F8);
        }
        maxDist = bestDist;
        if (found != 0) {
            glist = renderTargetQuad(glist, furthestIdx);
        }
    } while (found != 0);
    return glist;
}

typedef struct ActorTargetDistanceView {
    u8 pad0[0x10];
    u8 unk10;
    u8 unk11;
    u8 unk12;
    u8 unk13;
} ActorTargetDistanceView;

#define TARGET_VIEW ((ActorTargetDistanceView *)D_807F93F4)

#define W(pkt, _w0, _w1) { Gfx *_g = (Gfx *)(pkt); _g->words.w0 = (_w0); _g->words.w1 = (u32)(_w1); }

Gfx *renderTargetQuad(Gfx *glist, s32 targetIdx) {
    W(glist++, 0xE7000000, 0);
    W(glist++, 0xE200001C, 0x00504A50);
    W(glist++, 0xFC11FE23, 0xFFFFF7FB);
    W(glist++, 0xE3000A01, 0);
    W(glist++, 0xD9000000, 0);
    W(glist++, 0xD9FFFFFF, 0x00200005);
    gDPSetPrimColor(glist++, 0, 0, 100, 100, 100, TARGET_VIEW[targetIdx].unk10);
    W(glist++, 0xD7000002, 0xFFFFFFFF);
    gDPLoadTextureBlock(glist++, D_807F9400, G_IM_FMT_IA, G_IM_SIZ_8b, 64, 64, 0, G_TX_WRAP, G_TX_WRAP, 6, 6, 0, 0);
    gDPSetTileSize(glist++, 0, TARGET_VIEW[targetIdx].unk12, TARGET_VIEW[targetIdx].unk13, 63 << 2, 63 << 2);
    gSPVertex(glist++, osVirtualToPhysical(&D_807F93FC[targetIdx * 4]), 4, 0);
    W(glist++, 0x06000204, 0x00000406);
    W(glist++, 0xE7000000, 0);
    return glist;
}
