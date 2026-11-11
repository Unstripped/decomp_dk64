#include "common.h"
#include "render.h"
#include "sched.h"
#define PROTO_SKIP_renderModelQuadGfx // FAKE: callee prototype steer
#include "proto/global/119370.h"
#include "proto/global/126260.h"
#include "proto/global/15050.h"
#include "proto/global/17B90.h"
#include "proto/global/35000.h"
#include "proto/global/36880.h"
#include "proto/global/55B20.h"
#include "proto/global/5E2F0.h"
#include "proto/global/61AA0.h"
#include "proto/global/70FD0.h"


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


RenderEntry *renderEntryAddOrUpdate(RenderEntry *list, u8 type, void *targetId, f32 posX, f32 posY, f32 posZ, s16 maxDist, s16 priority, u8 autoPurge, s16 chunkIndex, u8 listIndex) {
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
        node = heapAlloc(sizeof(RenderEntry));
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


RenderEntry *renderEntryRemove(RenderEntry *list, void *targetId, u8 listIndex, u8 *outFound) {
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

void renderEntrySetDistanceOverride(RenderEntry *list, void *targetId, u8 listIndex, u8 forceInfiniteDist, u8 *outFound) {
    u8 found;

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
    f32 key;

    dist = 0.0f;
    node = list;
    head = list;
    *outClosest = NULL;
    base = list; // FAKE: third copy of list; reading list/head instead changes allocation
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
                key = (f32)((cur->unk1C < cur->unk10) ? 9999.0 : cur->unk10);
                ins = cur->unk18;
                if (ins != NULL) {
                    do {
                        cmpB = (f32)((ins->unk1C < ins->unk10) ? 9999.0 : ins->unk10);
                        if (key <= cmpB || cur->unk1C == -2) {
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

extern s32 gGfxCurrentFrameBuffer;
extern u8 D_807F6009;
extern s32 gGlobalPauseFlags;
extern u8 D_2000180[];

void *renderModelQuadGfx(void *, void *, f32, f32, f32, s32, s32, s32);

Gfx *renderEntryListBuildDisplayList(Gfx *glist, RenderEntry *list, f32 camX, f32 camY, f32 camZ, s32 renderMask, s16 layer, u8 playerIndex) {
    u8 ok;
    u8 type;
    void *model;

    ok = 1;
    gDPPipeSync(glist++);
    if (list != NULL) {
        do {
            type = list->unk24;
            model = list->unk0;
            if ((renderMask & 0x20) == 0 && type != 0 && type != 5) {
                ok = 0;
            }
            if ((renderMask & 0x20000) == 0 && type == 5) {
                ok = 0;
            }
            if ((renderMask & 0x10000) == 0 && type == 0 && (!(((Actor *)model)->flags & 0x40000000) || (gGlobalPauseFlags & 2))) {
                ok = 0;
            }
            if (ok != 0) {
                switch (type) {
                case 0:
                    glist = renderActorEntryBuildDisplayList(gGfxCurrentFrameBuffer, model, glist, playerIndex);
                    gSPMatrix(glist++, D_2000180, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
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
    gDPPipeSync(glist++);
    return glist;
}


extern u8 gGfxBufferIndex;
extern PlayerStruct *gPlayerSlots;
extern u8 gPlayerCount;
extern u8 gCurrentPlayerIndex;



Gfx *renderActorEntryBuildDisplayList(s32 context, Actor *actor, Gfx *glist, u8 playerIndex) {
    PlayerState *ctl;
    f32 dz;
    f32 dy;
    s32 flag;
    f32 dx;
    u8 primR;
    u8 primG;
    u8 primB;
    s32 distSq;
    s32 pad;
    f32 dxb;
    f32 alphaMult;
    f64 d;

    alphaMult = 1.0f;
    if (!(actor->flags & 4)) {
        flag = 0;
        if (gPlayerCount >= 2 && (actor->collisionFlags & 1)) {
            ctl = actor->customState;
            if (gCurrentPlayerIndex != ctl->playerIndex) {
                flag = 1;
            }
        }
        if (flag == 0) {
            return glist;
        }
    }
    if (actor->actorType != 0x1F && actor->actorType != 0x27 && actor->actorType != 0xAE && !(actor->flags & 0x400)) {
        dx = gPlayerSlots[gCurrentPlayerIndex].unk21C - actor->x;
        dy = gPlayerSlots[gCurrentPlayerIndex].unk220 - actor->y;
        dz = gPlayerSlots[gCurrentPlayerIndex].unk224 - actor->z;
        dx = dx * dx;
        dy = dy * dy;
        dz = dz * dz;
        if (sqrtf(dx + dy + dz) > renderScaleDistanceByFov(actor->drawDistance)) {
            return glist;
        }
        if (mapPointOutsideClipBounds(actor->x, actor->y, actor->z, actor->cullMarginX, actor->cullMarginY)) {
            return glist;
        }
    }
    actor->flags |= 0x100;
    if (!(actor->flags & 0x200)) {
        actorCheckWorldBounds(actor);
    }
    gDPPipeSync(glist++);
    gSPSetGeometryMode(glist++, G_ZBUFFER | G_SHADING_SMOOTH);
    gSPClearGeometryMode(glist++, G_FOG | G_CULL_BOTH);
    if (actor->actorType == 0x135) {
        gSPClearGeometryMode(glist++, G_ZBUFFER);
    }
    gSPSegment(glist++, 15, osVirtualToPhysical(actor->unk148[gGfxBufferIndex]));
    if (actor->flags & 0x1000) {
        glist = actorBuildLightDisplayList(glist, actor, gCurrentPlayerIndex);
        gSPSetGeometryMode(glist++, G_LIGHTING);
        gDPSetPrimColor(glist++, 0, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF);
    } else {
        u8 node;
        s32 padE[1];
        f32 lightX;
        f32 lightY;
        f32 lightZ;
        f32 tint;
        gSPClearGeometryMode(glist++, G_LIGHTING);
        if (actor->flags & 0x800000) {
            primR = actor->tintR;
            primG = actor->tintG;
            primB = actor->tintB;
        } else {
            node = actor->unkCD;
            if (node) {
                actorGetNodePos(actor, node, &lightX, &lightY, &lightZ);
            } else {
                lightX = actor->x;
                lightY = actor->y;
                lightZ = actor->z;
            }
            lightSampleColorAtPosition(lightX, lightY, lightZ, actor->unkCE, &primR, &primG, &primB, actor->chunkIndex);
            if (!(actor->renderFlags & 1)) {
                tint = actor->tintA / 15.0f;
                primR = primR * tint;
                primG = primG * tint;
                primB = primB * tint;
            }
        }
        gDPSetPrimColor(glist++, 0, 0xFF, primR, primG, primB, 0xFF);
    }
    if (actor->flags & 0x8000) {
        renderCalcPlayerDistanceAlpha(actor->x, actor->y, actor->z, actor->drawDistance, -1, &actor->alpha);
    }
    if (actor->collisionFlags != 0x80 && actor->collisionFlags != 0x40 && actor->collisionFlags != 8) {
        if ((actor->y - 5.0f < gPlayerSlots[gCurrentPlayerIndex].unk220 && gPlayerSlots[gCurrentPlayerIndex].unk220 < actor->y + 2.0 * actor->eyeHeight) || (actor->contactFlags & 0x2000)) {
            dy = actor->z - gPlayerSlots[gCurrentPlayerIndex].unk224;
            if (dy) {} // FAKE: extra use lifts dy's adjsave to dz's 4.5; dy, coloured first, takes $f2 and dz $f14
            dxb = actor->x - gPlayerSlots[gCurrentPlayerIndex].unk21C;
            distSq = (s32)(dy * dy + dxb * dxb);
            dz = actor->sub4->scaleY;
            if (dz < 0.01) {
                dz = 0.01f;
            }
            if (dxb > 0.5f) { // FAKE: dead block (with dead dy store) lowers dxb's adjsave so it takes $f12 and holds dy's at 4.5
                dy = dy * dy;
            }
            d = (f64)distSq / (dz / 0.15) / 400.0;
            alphaMult = MIN((d > 0.3) ? d - 0.3 : 0.0, 1.0);
        }
    }
    if (actor->alpha * alphaMult != 0.0f) {
        glist = renderActorDisplayList(renderSetSegment6AndFog(glist, actor->alpha * alphaMult, 1), actor);
    }
    gDPPipeSync(glist++);
    gDPSetTextureLUT(glist++, G_TT_NONE);
    gDPPipeSync(glist++);
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
