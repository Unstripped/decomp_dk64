#include "common.h"
#define PROTO_SKIP_renderModelQuadGfx // FAKE: callee prototype steer
#include "proto/global/119370.h"
#include "proto/global/126260.h"
#include "proto/global/15050.h"
#include "proto/global/17B90.h"
#define PROTO_SKIP_actorBuildModelMatrix
#define PROTO_SKIP_actorBuildModelMatrixFromAngles
#define PROTO_SKIP_actorUpdateModelMatrix
#include "proto/global/35000.h"
#include "proto/global/36880.h"
#include "proto/global/55B20.h"
#include "proto/global/5E2F0.h"
#include "proto/global/61AA0.h"
#include "proto/global/70FD0.h"

typedef struct RenderEntry RenderEntry;
struct RenderEntry {
    /* 0x00 */ s32 unk0;
    /* 0x04 */ f32 unk4;
    /* 0x08 */ f32 unk8;
    /* 0x0C */ f32 unkC;
    /* 0x10 */ f32 unk10;
    /* 0x14 */ RenderEntry *unk14;
    /* 0x18 */ RenderEntry *unk18;
    /* 0x1C */ s16 unk1C;
    /* 0x1E */ s16 unk1E;
    /* 0x20 */ s16 unk20;
    /* 0x22 */ u8 unk22;
    /* 0x23 */ u8 unk23;
    /* 0x24 */ u8 unk24;
    /* 0x25 */ u8 pad25[3];
};

extern RenderEntry *D_807F5FF0;
extern RenderEntry *D_807F5FF4;
extern RenderEntry *D_807F5FF8;
extern RenderEntry *D_807F5FFC;

void renderEntryListsReset(void) {
    D_807F5FF0 = 0;
    D_807F5FF4 = 0;
    D_807F5FF8 = 0;
    D_807F5FFC = 0;
}

s32 renderEntryIsTranslucent(u8 renderType, u8 *entryData) {
    if (renderType == 2) {
        if (entryData[0x4E] & 2) {
            return 0;
        }
        if (entryData[0x4E] & 1) {
            return 1;
        }
        return 0;
    }
    switch (renderType) {
    case 0:
    case 1:
        return 0;
    case 5:
        return 1;
    default:
        return 0;
    }
}


void renderEntryListFreeTranslucent(void) {
    renderEntryListFree(D_807F5FF4);
    D_807F5FF4 = 0;
}


RenderEntry *renderEntryAddOrUpdate(RenderEntry *list, u8 type, s32 targetId, f32 posX, f32 posY, f32 posZ, s16 maxDist, s16 priority, u8 autoPurge, s16 chunkIndex, u8 listIndex) {
    s32 found;
    RenderEntry *prev;
    RenderEntry *node;
    RenderEntry *head;

    found = 0;
    prev = NULL;
    if (listIndex == 1) {
        list = D_807F5FF0;
    }
    if (listIndex == 2) {
        list = D_807F5FF4;
    }
    if (listIndex == 3) {
        list = D_807F5FF8;
    }
    if (listIndex == 4) {
        list = D_807F5FFC;
    }
    head = list;
    if (list != NULL) {
        do {
            if (targetId == list->unk0) {
                found = 1;
            } else {
                prev = list;
                list = list->unk14;
            }
        } while (list != NULL && found == 0);
    }
    if (found != 0) {
        list->unk4 = posX;
        list->unk8 = posY;
        list->unkC = posZ;
        list->unk1C = maxDist;
        if (chunkIndex != -1) {
            list->unk20 = chunkIndex;
        }
        list->unk23 = 1;
    } else {
        node = heapAlloc(0x28);
        node->unk24 = type;
        node->unk0 = targetId;
        node->unk4 = posX;
        node->unk8 = posY;
        node->unkC = posZ;
        node->unk1C = maxDist;
        node->unk1E = priority;
        node->unk22 = autoPurge;
        node->unk23 = 1;
        node->unk20 = 0;
        node->unk14 = NULL;
        node->unk10 = 0.0f;
        if (prev != NULL) {
            prev->unk14 = node;
            node->unk18 = prev;
        } else {
            head = node;
            node->unk18 = NULL;
        }
    }
    if (listIndex == 1) {
        D_807F5FF0 = head;
    }
    if (listIndex == 2) {
        D_807F5FF4 = head;
    }
    if (listIndex == 3) {
        D_807F5FF8 = head;
    }
    if (listIndex == 4) {
        D_807F5FFC = head;
    }
    return head;
}


RenderEntry *renderEntryRemove(RenderEntry *list, s32 targetId, u8 listIndex, u8 *outFound) {
    u8 found;
    RenderEntry *prev;
    RenderEntry *head;

    found = 0;
    prev = NULL;
    if (listIndex == 1) {
        list = D_807F5FF0;
    }
    if (listIndex == 2) {
        list = D_807F5FF4;
    }
    if (listIndex == 3) {
        list = D_807F5FF8;
    }
    if (listIndex == 4) {
        list = D_807F5FFC;
    }
    head = list;
    if (list != NULL) {
        do {
            if (targetId == list->unk0) {
                found = 1;
            } else {
                prev = list;
                list = list->unk14;
            }
        } while (list != NULL && found == 0);
    }
    if (found != 0) {
        if (prev != NULL) {
            prev->unk14 = list->unk14;
        } else {
            head = list->unk14;
        }
        if (list->unk14 != NULL) {
            list->unk14->unk18 = prev;
        }
        heapFree(list);
    }
    *outFound = found;
    if (listIndex == 1) {
        D_807F5FF0 = head;
    }
    if (listIndex == 2) {
        D_807F5FF4 = head;
    }
    if (listIndex == 3) {
        D_807F5FF8 = head;
    }
    if (listIndex == 4) {
        D_807F5FFC = head;
    }
    return head;
}

void renderEntryListFree(RenderEntry *list) {
    RenderEntry *cur;

    if (list != NULL) {
        do {
            cur = list;
            list = list->unk14;
            heapFree(cur);
        } while (list != NULL);
    }
}

RenderEntry *renderEntryListPurgeUntouched(RenderEntry *list) {
    RenderEntry *head;

    head = list;
    if (list != NULL) {
        do {
            if (list->unk22 == 1 && list->unk23 == 0) {
                if (list->unk18 != NULL) {
                    list->unk18->unk14 = list->unk14;
                } else {
                    head = list->unk14;
                }
                if (list->unk14 != NULL) {
                    list->unk14->unk18 = list->unk18;
                }
                heapFree(list);
            }
            list = list->unk14;
        } while (list != NULL);
    }
    return head;
}

void renderEntryListClearTouched(RenderEntry *list) {
    if (list != NULL) {
        do {
            list->unk23 = 0;
            list = list->unk14;
        } while (list != NULL);
    }
}

void renderEntrySetDistanceOverride(RenderEntry *list, s32 targetId, u8 listIndex, u8 forceInfiniteDist, s8 *outFound) {
    s8 found;

    found = 0;
    if (listIndex == 1) {
        list = D_807F5FF0;
    }
    if (listIndex == 2) {
        list = D_807F5FF4;
    }
    if (listIndex == 3) {
        list = D_807F5FF8;
    }
    if (listIndex == 4) {
        list = D_807F5FFC;
    }
    if (list != NULL) {
        do {
            if (targetId == list->unk0) {
                found = 1;
            } else {
                list = list->unk14;
            }
        } while (list != NULL && found == 0);
    }
    if (found != 0) {
        if (forceInfiniteDist) {
            list->unk10 = -1.0f;
        } else {
            list->unk1C = -2;
        }
    }
    *outFound = found;
}


RenderEntry *renderEntryListSortByDistance(RenderEntry *list, f32 camX, f32 camY, f32 camZ, RenderEntry **outClosest) {
    RenderEntry *node;
    f32 dx;
    f32 dy;
    f32 dz;
    RenderEntry *head;
    RenderEntry *cur;
    RenderEntry *ins;
    RenderEntry *base;
    s32 inserted;
    f32 dist;
    f32 cmpB;

    dist = 0.0f;
    node = list;
    head = list;
    *outClosest = NULL;
    base = list;
    if (base != NULL) {
        do {
            dx = node->unk4 - camX;
            dy = node->unk8 - camY;
            dz = node->unkC - camZ;
            if (node->unk10 != -1.0) {
                node->unk10 = sqrtf(dx * dx + dy * dy + dz * dz);
            }
            node = node->unk14;
        } while (node != NULL);
    }
    if (base != NULL) {
        if (base->unk10 < base->unk1C || base->unk1C == -2) {
            *outClosest = base;
            if (base->unk1C == -2) {
                dist = 9999.0f;
            } else {
                dist = base->unk10;
            }
        }
        cur = base->unk14;
        if (cur != NULL) {
            do {
                inserted = 0;
                if ((dist < cur->unk10 && cur->unk10 < cur->unk1C) || cur->unk1C == -2) {
                    *outClosest = cur;
                    if (cur->unk1C == -2) {
                        dist = 9999.0f;
                    } else {
                        dist = cur->unk10;
                    }
                }
                dz = (f32)((cur->unk1C < cur->unk10) ? 9999.0 : cur->unk10);
                ins = cur->unk18;
                if (ins != NULL) {
                    do {
                        cmpB = (f32)((ins->unk1C < ins->unk10) ? 9999.0 : ins->unk10);
                        if (dz <= cmpB || cur->unk1C == -2) {
                            inserted = 1;
                            if (ins != cur->unk18) {
                                cur->unk18->unk14 = cur->unk14;
                                node = cur->unk14;
                                if (node != NULL) {
                                    node->unk18 = cur->unk18;
                                }
                                node = ins->unk14;
                                ins->unk14 = cur;
                                cur->unk14 = node;
                                if (cur->unk14 != NULL) {
                                    cur->unk14->unk18 = cur;
                                }
                                cur->unk18 = ins;
                            }
                        }
                        ins = ins->unk18;
                    } while (ins != NULL && inserted == 0);
                }
                if (inserted == 0) {
                    cur->unk18->unk14 = cur->unk14;
                    if (cur->unk14 != NULL) {
                        cur->unk14->unk18 = cur->unk18;
                    }
                    cur->unk18 = NULL;
                    cur->unk14 = head;
                    head->unk18 = cur;
                    head = cur;
                }
                cur = cur->unk14;
            } while (cur != NULL);
        }
    }
    return head;
}

typedef struct GfxWords {
    u32 w0;
    u32 w1;
} GfxWords;

typedef struct EntryModel {
    /* 0x00 */ u8 pad0[0x60];
    /* 0x60 */ u32 unk60;
} EntryModel;

extern s32 gGfxCurrentFrameBuffer;
extern u8 D_807F6009;
extern s32 gGlobalPauseFlags;
extern u8 D_2000180[];

void *renderModelQuadGfx(void *, void *, f32, f32, f32, s32, s32, s32);

#define WRITE_GFX_WORDS(pkt, _w0, _w1) { GfxWords *_g = (GfxWords *)(pkt); _g->w0 = (_w0); _g->w1 = (u32)(_w1); }

GfxWords *renderEntryListBuildDisplayList(GfxWords *glist, RenderEntry *list, f32 camX, f32 camY, f32 camZ, s32 renderMask, s16 layer, u8 playerIndex) {
    s32 ok;
    u8 type;
    EntryModel *model;
    GfxWords *tmp;

    ok = 1;
    glist->w0 = 0xE7000000;
    glist->w1 = 0;
    glist++;
    if (list != NULL) {
        do {
            type = list->unk24;
            model = (EntryModel *)list->unk0;
            if ((renderMask & 0x20) == 0 && type != 0 && type != 5) {
                ok = 0;
            }
            if ((renderMask & 0x20000) == 0 && type == 5) {
                ok = 0;
            }
            if ((renderMask & 0x10000) == 0 && type == 0 && (!(model->unk60 & 0x40000000) || (gGlobalPauseFlags & 2))) {
                ok = 0;
            }
            if (ok != 0) {
                switch (type) {
                case 0:
                    tmp = renderActorEntryBuildDisplayList(gGfxCurrentFrameBuffer, model, glist, playerIndex);
                    tmp->w0 = 0xDA380003;
                    tmp->w1 = (u32)D_2000180;
                    glist = tmp + 1;
                    D_807F6009 = 0;
                    break;
                case 1:
                    glist = renderModelAnimatedSlot(model, glist, list->unk4, list->unk8, list->unkC, 1, layer, playerIndex);
                    D_807F6009 = 1;
                    break;
                case 2:
                    glist = renderModelQuadGfx(model, glist, camX, camY, camZ, 1, layer, playerIndex);
                    break;
                case 5:
                    glist = effectGridBuildDisplayList(model, glist, layer);
                    break;
                }
            } else {
                ok = 1;
            }
            list = list->unk14;
        } while (list != NULL);
    }
    WRITE_GFX_WORDS(glist++, 0xE7000000, 0);
    return glist;
}

typedef struct ModelInfo {
    /* 0x00 */ u8 pad0[0x38];
    /* 0x38 */ f32 unk38;
} ModelInfo;

typedef struct ActorCtl {
    /* 0x000 */ u8 pad0[0x1A4];
    /* 0x1A4 */ u8 unk1A4;
} ActorCtl;

typedef struct RenderActor {
    /* 0x000 */ u8 pad0[4];
    /* 0x004 */ ModelInfo *unk4;
    /* 0x008 */ u8 pad8[0x50];
    /* 0x058 */ s32 unk58;
    /* 0x05C */ u16 unk5C;
    /* 0x05E */ u8 pad5E[2];
    /* 0x060 */ u32 unk60;
    /* 0x064 */ u32 unk64;
    /* 0x068 */ u8 pad68[2];
    /* 0x06A */ u16 unk6A;
    /* 0x06C */ u8 pad6C[0x10];
    /* 0x07C */ f32 unk7C;
    /* 0x080 */ f32 unk80;
    /* 0x084 */ f32 unk84;
    /* 0x088 */ u8 pad88[0x45];
    /* 0x0CD */ u8 unkCD;
    /* 0x0CE */ s16 unkCE;
    /* 0x0D0 */ u8 padD0[0x58];
    /* 0x128 */ s16 unk128;
    /* 0x12A */ s16 unk12A;
    /* 0x12C */ s16 unk12C;
    /* 0x12E */ u8 pad12E[2];
    /* 0x130 */ u8 unk130;
    /* 0x131 */ u8 unk131;
    /* 0x132 */ u8 pad132[0x16];
    /* 0x148 */ void *unk148[2];
    /* 0x150 */ u8 pad150[0xE];
    /* 0x15E */ u8 unk15E;
    /* 0x15F */ u8 pad15F[0xB];
    /* 0x16A */ u8 unk16A;
    /* 0x16B */ u8 unk16B;
    /* 0x16C */ u8 unk16C;
    /* 0x16D */ u8 unk16D;
    /* 0x16E */ u8 pad16E[6];
    /* 0x174 */ ActorCtl *unk174;
} RenderActor;

typedef struct PlayerView {
    /* 0x000 */ u8 pad0[0x21C];
    /* 0x21C */ f32 unk21C;
    /* 0x220 */ f32 unk220;
    /* 0x224 */ f32 unk224;
    /* 0x228 */ u8 pad228[0x2F0 - 0x228];
} PlayerView;

extern u8 gGfxBufferIndex;
extern PlayerView *gPlayerSlots;
extern u8 gPlayerCount;
extern u8 gCurrentPlayerIndex;


#define RENDER_ACT ((RenderActor *)actor)
#define CUR_PLAYER_VIEW ((PlayerView *)((u8 *)gPlayerSlots + gCurrentPlayerIndex * 0x2F0))

void *renderActorEntryBuildDisplayList(s32 context, void *actor, GfxWords *glist, u8 playerIndex) {
    ActorCtl *ctl;
    f32 dz;
    f32 dy;
    s32 flag;
    f32 dx;
    u8 primR;
    u8 primG;
    u8 primB;
    f64 x;
    f32 dxb;
    f32 alphaMult;
    f64 d;

    alphaMult = 1.0f;
    if (!(RENDER_ACT->unk60 & 4)) {
        flag = 0;
        if (gPlayerCount >= 2 && (RENDER_ACT->unk5C & 1) && (ctl = RENDER_ACT->unk174, gCurrentPlayerIndex != ctl->unk1A4)) {
            flag = 1;
        }
        if (flag == 0) {
            return glist;
        }
    }
    if (RENDER_ACT->unk58 != 0x1F && RENDER_ACT->unk58 != 0x27 && RENDER_ACT->unk58 != 0xAE && !(RENDER_ACT->unk60 & 0x400)) {
        dx = CUR_PLAYER_VIEW->unk21C - RENDER_ACT->unk7C;
        dy = CUR_PLAYER_VIEW->unk220 - RENDER_ACT->unk80;
        dz = CUR_PLAYER_VIEW->unk224 - RENDER_ACT->unk84;
        dx = dx * dx;
        dy = dy * dy;
        dz = dz * dz;
        if (sqrtf(dx + dy + dz) > renderScaleDistanceByFov(RENDER_ACT->unk12A)) {
            return glist;
        }
        if (mapPointOutsideClipBounds(RENDER_ACT->unk7C, RENDER_ACT->unk80, RENDER_ACT->unk84, RENDER_ACT->unk130, RENDER_ACT->unk131)) {
            return glist;
        }
    }
    RENDER_ACT->unk60 |= 0x100;
    if (!(RENDER_ACT->unk60 & 0x200)) {
        actorCheckWorldBounds(actor);
    }
    gDPPipeSync((Gfx *)glist++);
    gSPSetGeometryMode((Gfx *)glist++, G_ZBUFFER | G_SHADING_SMOOTH);
    gSPClearGeometryMode((Gfx *)glist++, G_FOG | G_CULL_BOTH);
    if (RENDER_ACT->unk58 == 0x135) {
        gSPClearGeometryMode((Gfx *)glist++, G_ZBUFFER);
    }
    gSPSegment((Gfx *)glist++, 15, osVirtualToPhysical(RENDER_ACT->unk148[gGfxBufferIndex]));
    if (RENDER_ACT->unk60 & 0x1000) {
        glist = actorBuildLightDisplayList(glist, actor, gCurrentPlayerIndex);
        gSPSetGeometryMode((Gfx *)glist++, G_LIGHTING);
        gDPSetPrimColor((Gfx *)glist++, 0, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF);
    } else {
        u8 node;
        s32 padE[1];
        f32 lightX;
        f32 lightY;
        f32 lightZ;
        s32 padF[1];
        gSPClearGeometryMode((Gfx *)glist++, G_LIGHTING);
        if (RENDER_ACT->unk60 & 0x800000) {
            primR = RENDER_ACT->unk16A;
            primG = RENDER_ACT->unk16B;
            primB = RENDER_ACT->unk16C;
        } else {
            node = RENDER_ACT->unkCD;
            if (node) {
                actorGetNodePos(actor, node, &lightX, &lightY, &lightZ);
            } else {
                lightX = RENDER_ACT->unk7C;
                lightY = RENDER_ACT->unk80;
                lightZ = RENDER_ACT->unk84;
            }
            lightSampleColorAtPosition(lightX, lightY, lightZ, RENDER_ACT->unkCE, &primR, &primG, &primB, RENDER_ACT->unk12C);
            if (!(RENDER_ACT->unk64 & 1)) {
                dx = RENDER_ACT->unk16D / 15.0f;
                primR = primR * dx;
                primG = primG * dx;
                primB = primB * dx;
            }
        }
        gDPSetPrimColor((Gfx *)glist++, 0, 0xFF, primR, primG, primB, 0xFF);
    }
    if (RENDER_ACT->unk60 & 0x8000) {
        renderCalcPlayerDistanceAlpha(RENDER_ACT->unk7C, RENDER_ACT->unk80, RENDER_ACT->unk84, RENDER_ACT->unk12A, -1, &RENDER_ACT->unk128);
    }
    if (RENDER_ACT->unk5C != 0x80 && RENDER_ACT->unk5C != 0x40 && RENDER_ACT->unk5C != 8) {
        if ((RENDER_ACT->unk80 - 5.0f < CUR_PLAYER_VIEW->unk220 && CUR_PLAYER_VIEW->unk220 < RENDER_ACT->unk80 + 2.0 * RENDER_ACT->unk15E) || (RENDER_ACT->unk6A & 0x2000)) {
            dy = RENDER_ACT->unk84 - CUR_PLAYER_VIEW->unk224;
            if (dy) {} // FAKE: second use keeps dy a coloured web (FP colour order)
            dxb = RENDER_ACT->unk7C - CUR_PLAYER_VIEW->unk21C;
            flag = (s32)(dy * dy + dxb * dxb);
            if (flag && flag) {} // FAKE: keep flag a candidate
            dz = RENDER_ACT->unk4->unk38;
            if (dz < 0.01) {
                dz = 0.01f;
            }
            if (dxb > 0.5f) {} // FAKE: dead FP compare extends dxb's range (f12 colour)
            alphaMult = ((((f64)flag / (dz / 0.15) / 400.0) > 0.3 ? ((f64)flag / (dz / 0.15) / 400.0) - 0.3 : 0.0) < 1.0) ? (((f64)flag / (dz / 0.15) / 400.0) > 0.3 ? ((f64)flag / (dz / 0.15) / 400.0) - 0.3 : 0.0) : 1.0;
        }
    }
    if (RENDER_ACT->unk128 * alphaMult != 0.0f) {
        glist = renderActorDisplayList(renderSetSegment6AndFog(glist, RENDER_ACT->unk128 * alphaMult, 1), actor);
    }
    gDPPipeSync((Gfx *)glist++);
    gDPSetTextureLUT((Gfx *)glist++, G_TT_NONE);
    gDPPipeSync((Gfx *)glist++);
    return glist;
}

f32 mathCosF(s16);
f32 mathSinF(s16);

void actorBuildModelMatrix(Actor *actor, f32 *dst) {
    f32 sinA;
    f32 cosA;
    f32 sinB;
    f32 cosB;
    f32 sinC;
    f32 cosC;
    f32 u;
    f32 us;
    f32 pad0;
    f32 t20;

    sinA = mathCosF(actor->pitch);
    cosA = mathSinF(actor->pitch);
    sinB = mathCosF(actor->roll);
    cosB = mathSinF(actor->roll);
    sinC = mathCosF(actor->yaw);
    cosC = mathSinF(actor->yaw);
    u = actor->sub4->scaleX;
    us = u * sinA;
    u = u * cosA;
    *dst++ = us * sinC + u * (cosB * cosC);
    *dst++ = u * sinB;
    *dst++ = (f32)u * (cosB * sinC) - us * cosC;
    *dst++ = 0.0f;
    u = actor->sub4->scaleY;
    us = u * sinA;
    u = u * cosA;
    *dst++ = (f32)us * (cosB * cosC) - u * sinC;
    *dst++ = us * sinB;
    *dst++ = u * cosC + us * (cosB * sinC);
    *dst++ = 0.0f;
    u = actor->sub4->scaleZ;
    *dst++ = u * sinB * cosC;
    *dst++ = -u * cosB;
    *dst++ = u * sinB * sinC;
    *dst++ = 0.0f;
    *dst++ = actor->x;
    *dst++ = actor->y;
    *dst++ = actor->z;
    *dst = 1.0f;
}













void actorBuildModelMatrixFromAngles(Actor *actor, f32 *dst, f32 angleA, f32 angleB, f32 angleC) {
    f32 sinA;
    f32 cosA;
    f32 sinB;
    f32 cosB;
    f32 sinC;
    f32 cosC;
    f32 u;
    f32 us;
    f32 pad0;
    f32 t20;

    sinA = mathCosF((s16)(s32)angleA);
    cosA = mathSinF((s16)(s32)angleA);
    sinB = mathCosF((s16)(s32)angleB);
    cosB = mathSinF((s16)(s32)angleB);
    sinC = mathCosF((s16)(s32)angleC);
    cosC = mathSinF((s16)(s32)angleC);
    u = actor->sub4->scaleX;
    us = u * sinA;
    u = u * cosA;
    *dst++ = us * sinC + u * (cosB * cosC);
    *dst++ = u * sinB;
    *dst++ = (f32)u * (cosB * sinC) - us * cosC;
    *dst++ = 0.0f;
    u = actor->sub4->scaleY;
    us = u * sinA;
    u = u * cosA;
    *dst++ = (f32)us * (cosB * cosC) - u * sinC;
    *dst++ = us * sinB;
    *dst++ = u * cosC + us * (cosB * sinC);
    *dst++ = 0.0f;
    u = actor->sub4->scaleZ;
    *dst++ = u * sinB * cosC;
    *dst++ = -u * cosB;
    *dst++ = u * sinB * sinC;
    *dst++ = 0.0f;
    *dst++ = actor->x;
    *dst++ = actor->y;
    *dst++ = actor->z;
    *dst = 1.0f;
}


void actorUpdateModelMatrix(Actor *actor, u8 concat) {
    f32 tempMf[4][4];
    f32 padMf[4][4];
    s16 angle;
    s16 angDelta;
    s16 calcAngleB;
    s16 calcAngleC;
    s16 x;
    s16 y;

    if (actor->flags & 1) {
        angle = (actor->yaw - actor->floorSlopeYaw) & 0xFFF;
        if (angle >= 0x801) {
            angle -= 0x1000;
        }
        angDelta = (0x400 - actor->floorSlopePitch) & 0xFFF;
        calcAngleB = (s32)(mathCosF(angle) * (f32)angDelta);
        calcAngleB = (calcAngleB + actor->roll) & 0xFFF;
        x = (s32)(mathSinF(angle) * (f32)angDelta);
        x = (x + actor->pitch) & 0xFFF;
        calcAngleC = actor->yaw;
        if (concat != 0) {
            actorBuildModelMatrixFromAngles(actor, (f32 *)tempMf, x, calcAngleB, calcAngleC);
            guMtxCatF(actor->modelMtx, tempMf, actor->modelMtx);
            return;
        }
        actorBuildModelMatrixFromAngles(actor, (f32 *)actor->modelMtx, x, calcAngleB, calcAngleC);
        return;
    }
    if (concat != 0) {
        actorBuildModelMatrix(actor, (f32 *)tempMf);
        guMtxCatF(actor->modelMtx, tempMf, actor->modelMtx);
        return;
    }
    actorBuildModelMatrix(actor, (f32 *)actor->modelMtx);
}
