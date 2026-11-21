#include "common.h"
#include "render.h"
#include "sched.h"
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
extern RenderEntry *gRenderListPending;
extern RenderEntry *D_807F5FF8;
extern RenderEntry *gRenderListSorted;

void renderEntryListsReset(void) {
    D_807F5FF0 = NULL;
    gRenderListPending = NULL;
    D_807F5FF8 = NULL;
    gRenderListSorted = NULL;
}

s32 renderEntryIsTranslucent(u8 renderType, void *object) {
    RenderQuadModelObj *quad;

    if (renderType == 2) {
        quad = object;
        if (quad->flags & 2) {
            return 0;
        }
        if (quad->flags & 1) {
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
    renderEntryListFree(gRenderListPending);
    gRenderListPending = NULL;
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
        list = gRenderListPending;
    }
    if (listIndex == 3) {
        list = D_807F5FF8;
    }
    if (listIndex == 4) {
        list = gRenderListSorted;
    }
    head = list;
    if (list != NULL) {
        do {
            if (targetId == list->object) {
                found = 1;
            } else {
                prev = list;
                list = list->next;
            }
        } while (list != NULL && found == 0);
    }
    if (found != 0) {
        list->x = posX;
        list->y = posY;
        list->z = posZ;
        list->maxDist = maxDist;
        if (chunkIndex != -1) {
            list->chunkIndex = chunkIndex;
        }
        list->touched = 1;
    } else {
        node = heapAlloc(sizeof(RenderEntry));
        node->type = type;
        node->object = targetId;
        node->x = posX;
        node->y = posY;
        node->z = posZ;
        node->maxDist = maxDist;
        node->modelId = priority;
        node->autoPurge = autoPurge;
        node->touched = 1;
        node->chunkIndex = 0;
        node->next = NULL;
        node->camDist = 0.0f;
        if (prev != NULL) {
            prev->next = node;
            node->prev = prev;
        } else {
            head = node;
            node->prev = NULL;
        }
    }
    if (listIndex == 1) {
        D_807F5FF0 = head;
    }
    if (listIndex == 2) {
        gRenderListPending = head;
    }
    if (listIndex == 3) {
        D_807F5FF8 = head;
    }
    if (listIndex == 4) {
        gRenderListSorted = head;
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
        list = gRenderListPending;
    }
    if (listIndex == 3) {
        list = D_807F5FF8;
    }
    if (listIndex == 4) {
        list = gRenderListSorted;
    }
    head = list;
    if (list != NULL) {
        do {
            if (targetId == list->object) {
                found = 1;
            } else {
                prev = list;
                list = list->next;
            }
        } while (list != NULL && found == 0);
    }
    if (found != 0) {
        if (prev != NULL) {
            prev->next = list->next;
        } else {
            head = list->next;
        }
        if (list->next != NULL) {
            list->next->prev = prev;
        }
        heapFree(list);
    }
    *outFound = found;
    if (listIndex == 1) {
        D_807F5FF0 = head;
    }
    if (listIndex == 2) {
        gRenderListPending = head;
    }
    if (listIndex == 3) {
        D_807F5FF8 = head;
    }
    if (listIndex == 4) {
        gRenderListSorted = head;
    }
    return head;
}

void renderEntryListFree(RenderEntry *list) {
    RenderEntry *cur;

    if (list != NULL) {
        do {
            cur = list;
            list = list->next;
            heapFree(cur);
        } while (list != NULL);
    }
}

RenderEntry *renderEntryListPurgeUntouched(RenderEntry *list) {
    RenderEntry *head;

    head = list;
    if (list != NULL) {
        do {
            if (list->autoPurge == 1 && list->touched == 0) {
                if (list->prev != NULL) {
                    list->prev->next = list->next;
                } else {
                    head = list->next;
                }
                if (list->next != NULL) {
                    list->next->prev = list->prev;
                }
                heapFree(list);
            }
            list = list->next;
        } while (list != NULL);
    }
    return head;
}

void renderEntryListClearTouched(RenderEntry *list) {
    if (list != NULL) {
        do {
            list->touched = 0;
            list = list->next;
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
        list = gRenderListPending;
    }
    if (listIndex == 3) {
        list = D_807F5FF8;
    }
    if (listIndex == 4) {
        list = gRenderListSorted;
    }
    if (list != NULL) {
        do {
            if (targetId == list->object) {
                found = 1;
            } else {
                list = list->next;
            }
        } while (list != NULL && found == 0);
    }
    if (found != 0) {
        if (forceInfiniteDist) {
            list->camDist = -1.0f;
        } else {
            list->maxDist = -2;
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
    s32 inserted;
    f32 insKey;
    f32 dist;
    f32 key;
    RenderEntry *next;

    dist = 0.0f;
    node = list;
    head = list;
    *outClosest = NULL;
    while (node != NULL) {
        dx = node->x - camX;
        dy = node->y - camY;
        dz = node->z - camZ;
        if (node->camDist != -1.0) {
            node->camDist = sqrtf(dx * dx + dy * dy + dz * dz);
        }
        node = node->next;
    }
    if (head != NULL) {
        if (head->camDist < head->maxDist || head->maxDist == -2) {
            *outClosest = head;
            if (head->maxDist == -2) {
                dist = 9999.0f;
            } else {
                dist = head->camDist;
            }
        }
        cur = head->next;
        while (cur != NULL) {
            inserted = 0;
            if ((dist < cur->camDist && cur->camDist < cur->maxDist) || cur->maxDist == -2) {
                *outClosest = cur;
                if (cur->maxDist == -2) {
                    dist = 9999.0f;
                } else {
                    dist = cur->camDist;
                }
            }
            key = (cur->maxDist < cur->camDist) ? 9999.0 : cur->camDist;
            ins = cur->prev;
            while (ins != NULL && inserted == 0) {
                insKey = (ins->maxDist < ins->camDist) ? 9999.0 : ins->camDist;
                if (key <= insKey || cur->maxDist == -2) {
                    inserted = 1;
                    if (ins != cur->prev) {
                        cur->prev->next = cur->next;
                        if (cur->next != NULL) {
                            cur->next->prev = cur->prev;
                        }
                        next = ins->next;
                        ins->next = cur;
                        cur->next = next;
                        if (cur->next != NULL) {
                            cur->next->prev = cur;
                        }
                        cur->prev = ins;
                    }
                }
                ins = ins->prev;
            }
            if (inserted == 0) {
                cur->prev->next = cur->next;
                if (cur->next != NULL) {
                    cur->next->prev = cur->prev;
                }
                cur->prev = NULL;
                cur->next = head;
                head->prev = cur;
                head = cur;
            }
            cur = cur->next;
        }
    }
    return head;
}

extern FrameMatrices *gGfxCurrentFrameBuffer;
extern u8 gRenderSetupKind;
extern Mtx D_2000180;


Gfx *renderEntryListBuildDisplayList(Gfx *glist, RenderEntry *list, f32 camX, f32 camY, f32 camZ, s32 renderMask, s16 layer, u8 playerIndex) {
    u8 ok;
    u8 type;
    void *model;

    ok = 1;
    gDPPipeSync(glist++);
    while (list != NULL) {
        type = list->type;
        model = list->object;
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
                gSPMatrix(glist++, &D_2000180, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
                gRenderSetupKind = 0;
                break;
            case 1:
                glist = renderModelAnimatedSlot(model, glist, list->x, list->y, list->z, 1, layer, playerIndex);
                gRenderSetupKind = 1;
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
        list = list->next;
    }
    gDPPipeSync(glist++);
    return glist;
}


extern u8 gGfxBufferIndex;
extern PlayerStruct *gPlayerSlots;
extern u8 gPlayerCount;
extern u8 gCurrentPlayerIndex;



Gfx *renderActorEntryBuildDisplayList(FrameMatrices *frame, Actor *actor, Gfx *glist, u8 playerIndex) {
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
    f32 scale;
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
        dx = gPlayerSlots[gCurrentPlayerIndex].eyeX - actor->x;
        dy = gPlayerSlots[gCurrentPlayerIndex].eyeY - actor->y;
        dz = gPlayerSlots[gCurrentPlayerIndex].eyeZ - actor->z;
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
            lightSampleColorAtPosition(lightX, lightY, lightZ, actor->boundingRadius, &primR, &primG, &primB, actor->chunkIndex);
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
        if ((actor->y - 5.0f < gPlayerSlots[gCurrentPlayerIndex].eyeY && gPlayerSlots[gCurrentPlayerIndex].eyeY < actor->y + 2.0 * actor->eyeHeight) || (actor->contactFlags & 0x2000)) {
            distSq = (actor->x - gPlayerSlots[gCurrentPlayerIndex].eyeX) * (actor->x - gPlayerSlots[gCurrentPlayerIndex].eyeX)
                   + (actor->z - gPlayerSlots[gCurrentPlayerIndex].eyeZ) * (actor->z - gPlayerSlots[gCurrentPlayerIndex].eyeZ);
            scale = actor->sub4->scaleY;
            if (scale < 0.01) {
                scale = 0.01f;
            }
            d = distSq / (scale / 0.15) / 400.0;
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


void actorBuildModelMatrix(Actor *actor, f32 *dst) {
    f32 cosPitch;
    f32 sinPitch;
    f32 cosRoll;
    f32 sinRoll;
    f32 cosYaw;
    f32 sinYaw;
    f32 u;
    f32 us;
    f32 pad[2];

    cosPitch = mathCosF(actor->pitch);
    sinPitch = mathSinF(actor->pitch);
    cosRoll = mathCosF(actor->roll);
    sinRoll = mathSinF(actor->roll);
    cosYaw = mathCosF(actor->yaw);
    sinYaw = mathSinF(actor->yaw);
    u = actor->sub4->scaleX;
    us = u * cosPitch;
    u = u * sinPitch;
    *dst++ = us * cosYaw + u * (sinRoll * sinYaw);
    *dst++ = u * cosRoll;
    *dst++ = -(us * sinYaw) + u * (sinRoll * cosYaw);
    *dst++ = 0.0f;
    u = actor->sub4->scaleY;
    us = u * cosPitch;
    u = u * sinPitch;
    *dst++ = -(u * cosYaw) + us * (sinRoll * sinYaw);
    *dst++ = us * cosRoll;
    *dst++ = u * sinYaw + us * (sinRoll * cosYaw);
    *dst++ = 0.0f;
    u = actor->sub4->scaleZ;
    *dst++ = u * cosRoll * sinYaw;
    *dst++ = -u * sinRoll;
    *dst++ = u * cosRoll * cosYaw;
    *dst++ = 0.0f;
    *dst++ = actor->x;
    *dst++ = actor->y;
    *dst++ = actor->z;
    *dst = 1.0f;
}













void actorBuildModelMatrixFromAngles(Actor *actor, f32 *dst, f32 pitch, f32 roll, f32 yaw) {
    f32 cosPitch;
    f32 sinPitch;
    f32 cosRoll;
    f32 sinRoll;
    f32 cosYaw;
    f32 sinYaw;
    f32 u;
    f32 us;
    f32 pad[2];

    cosPitch = mathCosF(pitch);
    sinPitch = mathSinF(pitch);
    cosRoll = mathCosF(roll);
    sinRoll = mathSinF(roll);
    cosYaw = mathCosF(yaw);
    sinYaw = mathSinF(yaw);
    u = actor->sub4->scaleX;
    us = u * cosPitch;
    u = u * sinPitch;
    *dst++ = us * cosYaw + u * (sinRoll * sinYaw);
    *dst++ = u * cosRoll;
    *dst++ = -(us * sinYaw) + u * (sinRoll * cosYaw);
    *dst++ = 0.0f;
    u = actor->sub4->scaleY;
    us = u * cosPitch;
    u = u * sinPitch;
    *dst++ = -(u * cosYaw) + us * (sinRoll * sinYaw);
    *dst++ = us * cosRoll;
    *dst++ = u * sinYaw + us * (sinRoll * cosYaw);
    *dst++ = 0.0f;
    u = actor->sub4->scaleZ;
    *dst++ = u * cosRoll * sinYaw;
    *dst++ = -u * sinRoll;
    *dst++ = u * cosRoll * cosYaw;
    *dst++ = 0.0f;
    *dst++ = actor->x;
    *dst++ = actor->y;
    *dst++ = actor->z;
    *dst = 1.0f;
}


void actorUpdateModelMatrix(Actor *actor, u8 concat) {
    f32 tempMf[4][4];
    f32 padMf[4][4];
    s16 relYaw;
    s16 tilt;
    s16 roll;
    s16 yaw;
    s16 pitch;
    s16 pad;

    if (actor->flags & 1) {
        relYaw = (actor->yaw - actor->floorSlopeYaw) & 0xFFF;
        if (relYaw >= 0x801) {
            relYaw -= 0x1000;
        }
        tilt = (0x400 - actor->floorSlopePitch) & 0xFFF;
        roll = mathCosF(relYaw) * tilt;
        roll = (roll + actor->roll) & 0xFFF;
        pitch = mathSinF(relYaw) * tilt;
        pitch = (pitch + actor->pitch) & 0xFFF;
        yaw = actor->yaw;
        if (concat != 0) {
            actorBuildModelMatrixFromAngles(actor, (f32 *)tempMf, pitch, roll, yaw);
            guMtxCatF(actor->modelMtx, tempMf, actor->modelMtx);
            return;
        }
        actorBuildModelMatrixFromAngles(actor, (f32 *)actor->modelMtx, pitch, roll, yaw);
        return;
    }
    if (concat != 0) {
        actorBuildModelMatrix(actor, (f32 *)tempMf);
        guMtxCatF(actor->modelMtx, tempMf, actor->modelMtx);
        return;
    }
    actorBuildModelMatrix(actor, (f32 *)actor->modelMtx);
}
