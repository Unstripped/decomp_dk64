#include "common.h"
#include "race.h"
#include "sched.h"
#include "proto/boot/3630_string.h"
#include "proto/boot/3D20_sprintf.h"
#include "proto/global/100180_text_font.h"
#include "proto/global/1025E0_gfx_resource.h"
#include "proto/global/112080_resource_parse.h"
#include "proto/global/117190_menu_transition.h"
#include "proto/global/1295B0_spawn_nodes.h"
#include "proto/global/15050_heap.h"
#include "proto/global/166A0_random.h"
#include "proto/global/35000_render_entry.h"
#include "proto/global/450_main_loop.h"
#include "proto/global/69E60_actor_physics.h"
#include "proto/global/7130_sfx.h"
#include "proto/global/7CA80_actor_manager.h"
#include "proto/global/8CA50_anim_list.h"
#include "proto/global/90D80_render_callbacks.h"
#include "proto/global/CC800_player_setup.h"
#include "proto/global/CEAE0_player_update.h"
#include "proto/global/EFDC0_player_state_enter.h"
#include "proto/global/FCCD0_slot_queue.h"
#include "proto/race/1770.h"
#include "proto/race/52B0.h"
#include "proto/race/6650.h"
#include "proto/race/7BD0.h"
#include "proto/race/A960.h"

extern PlayerStruct *gPlayerSlots;




void raceInitParticipantArray(Actor *actor, s32 count) {
    RaceParticipant *managerData;
    void *allocated;

    managerData = actor->customState;
    allocated = heapAlloc(count * sizeof(RacePair));
    managerData->pairs = allocated;
    heapClearBlock(allocated);
    managerData->participantCount = count;
    managerData->phaseTimer = 0xFFFF;
    actor->state = 0;
}

void raceRegisterParticipant(Actor *manager, s32 slot, Actor *participant, RaceParticipant *participantData) {
    RaceParticipant *managerData;
    RacePair *pairs;
    RaceRoute *route;

    managerData = manager->customState;
    pairs = managerData->pairs;
    pairs[slot].actor = participant;
    pairs[slot].data = participantData;
    participantData->eliminated = 0;
    participantData->routePos = 0;
    participantData->lap = 1;
    if (participantData->isCpu == 0) {
        route = raceGetRoute(managerData->route);
        if (route != NULL) {
            participantData->activeGatePos = route->count - 1;
            raceActivateNextGate(participantData, route);
        }
        participantData->viewport = cameraFindViewportEntry(participantData->playerIdx);
    }
}

void raceGetParticipantPair(Actor *manager, s32 slot, Actor **outActor, RaceParticipant **outData) {
    RaceParticipant *managerData;
    RacePair *pairs;

    managerData = manager->customState;
    pairs = managerData->pairs;
    *outActor = pairs[slot].actor;
    *outData = pairs[slot].data;
}


void raceCalculatePathBoundingBox(Actor *actor) {
    RaceParticipant *managerData;
    TargetVec3f *p;
    f32 minX;
    f32 minZ;
    f32 maxX;
    f32 maxZ;
    f32 x;
    f32 z;

    minX = 9999.0f;
    minZ = 9999.0f;
    maxX = -1.0f;
    maxZ = -1.0f;
    managerData = actor->customState;
    for (p = gMinecartTrackPoints[0]; p < gMinecartTrackPoints[3]; p++) {
        x = p->x;
        if (x < minX) {
            minX = x;
        }
        z = p->z;
        if (z < minZ) {
            minZ = z;
        }
        if (maxX < x) {
            maxX = x;
        }
        if (maxZ < z) {
            maxZ = z;
        }
    }
    managerData->minimapCenterX = ((maxX - minX) * 0.5f + minX) - 10.0f;
    managerData->minimapCenterZ = ((maxZ - minZ) * 0.5f + minZ) - 20.0f;
    managerData->minimapScaleX = 116.48f / (maxX - minX);
    managerData->minimapScaleZ = 121.6f / (maxZ - minZ);
}


Gfx *raceRenderMinimapIcon(Gfx *dl, Actor *actor, f32 posX, f32 posZ, u8 red, u8 green, u8 blue) {
    RaceParticipant *managerData;

    managerData = actor->customState;
    posX = managerData->minimapCenterX - posX;
    posZ = managerData->minimapCenterZ - posZ;
    posX *= managerData->minimapScaleX;
    posZ *= managerData->minimapScaleZ;
    gDPSetPrimColor(dl++, 0, 0, red, green, blue, 0xC8);
    return renderRotatedSprite(dl, 0x4A, 3, 1, 0x10, 0x10,
        (s32)(((0.5f * posX) + 50.0f) * 4.0f),
        (s32)(((0.5f * posZ) + 60.0f) * 4.0f),
        1.0f, 1.0f, 0, 0.0f);
}

#define WRITE_GFX(pkt, _w0, _w1) { Gfx *_g = (Gfx *)(pkt); _g->words.w0 = (_w0); _g->words.w1 = (_w1); }
extern Gfx D_1000118;
extern Mtx D_20000C0;
extern Mtx D_2000180;
extern u8 gGfxBufferIndex;
extern s16 gScreenWidth;

Gfx *raceRenderCountdownText(Gfx *dl, Actor *actor) {
    u8 alpha;
    s32 textX;
    s32 pad;
    RaceParticipant *managerData;
    s32 countdownVal;
    u8 *textStr;
    f32 fadeFactor;

    alpha = 0xFF;
    textX = gScreenWidth / 2;
    managerData = actor->customState;
    if (actor->state == 2 || actor->state == 1) {
        if (managerData->phaseTimer < 0x78) {
            if (managerData->phaseTimer < 0x5A) {
                countdownVal = (0x78 - managerData->phaseTimer) / 30;
                if (countdownVal >= 3) {
                    countdownVal = 3;
                }
                textStr = heapAlloc(4);
                heapFreeDeferred(textStr);
                _sprintf(textStr, "%d", countdownVal);
            } else {
                fadeFactor = (f32)(0x78 - managerData->phaseTimer) * 0.033333335f;
                alpha = (u8)(u32)((f32)alpha * fadeFactor);
                textStr = textTableGetString(0x26, 9, 1);
            }
            WRITE_GFX(dl++, 0xDE000000, (u32)&D_1000118);
            WRITE_GFX(dl++, 0xE7000000, 0);
            WRITE_GFX(dl++, 0xE200001C, 0x00504240);
            WRITE_GFX(dl++, 0xFA000000, alpha & 0xFF);
            WRITE_GFX(dl++, 0xFCFF97FF, 0xFF2CFE7F);
            textX -= textGetStringWidth(1, textStr) >> 1;
            dl = textDrawStringVtx(dl, 1, (s16)(textX * 4), 0x3C, textStr, 1);
        }
    }
    return dl;
}

Gfx *raceRenderSpeedBoostHud(Gfx *dl, RaceParticipant *tracker) {
    G00Entry *hudPos;
    s32 screenX;
    s32 screenY;
    s32 i;
    s32 offset;
    f32 doubleX;
    s16 scaledY;
    f32 f_offset;

    hudPos = tracker->viewport;
    screenX = (s32)((f64)(hudPos->left + 8) + 4.0);
    screenY = hudPos->bottom - 0x22;
    WRITE_GFX(dl++, 0xFA000000, 0xFFC800B4);
    i = 0;
    if (tracker->projectileAmmo > 0) {
        offset = 0;
        doubleX = (f32)screenX + (f32)screenX;
        scaledY = (s16)(s32)(((f32)screenY + (f32)screenY) * 4.0f);
        do {
            Gfx *next;
            f_offset = offset;
            next = renderRotatedSprite(dl, 0x4A, 3, 1, 0x10, 0x10,
                (s32)((doubleX + f_offset) * 4.0f),
                scaledY, 4.0f, 4.0f, 0, 0.0f);
            i++;
            offset += 0x10;
            dl = next; // FAKE: delayed dl update steers the loop schedule
        } while (i < tracker->projectileAmmo);
    }
    if (tracker->projectileAmmo != 0) {
        WRITE_GFX(dl++, 0xDA380003, (u32)&D_2000180);
    }
    return dl;
}


Gfx *raceRenderCoinHud(Gfx *dl, RaceParticipant *tracker) {
    s32 pad[2];
    f32 posX;
    f32 doublePosX;
    f32 posY;
    f32 halfFontHeight;
    G00Entry *hudPos;
    f32 xOffsetF;
    s16 scaledSpriteY;
    s32 xOffset;
    s32 count;
    u8 *labelStr;
    Gfx *next;

    hudPos = tracker->viewport;
    halfFontHeight = (f32)textGetFontHeight(1) * 0.5f;
    posX = (f32)(hudPos->left + 8);
    posY = (f32)(hudPos->bottom - 0x10);
    posY -= 2 * halfFontHeight;
    labelStr = textTableGetString(0x26, 0xA, 1);
    WRITE_GFX(dl++, 0xFA000000, 0xFFFFFFFF);
    dl = textDrawStringVtx(dl, 1, (s16)(s32)(2.0f * (posX * 4.0f)), (s16)(s32)(2.0f * (posY * 4.0f)), labelStr, 4);
    WRITE_GFX(dl++, 0xDA380007, (u32)&D_20000C0);
    WRITE_GFX(dl++, 0xDA380005, (u32)tracker->hudScale[gGfxBufferIndex]);
    posX += 0.5f * (f32)textGetStringWidth(1, labelStr);
    posX = (f32)((f64)posX + 8.0);
    doublePosX = posX + posX;
    posY = (f32)((f64)posY + (0.4 * (f64)halfFontHeight));
    WRITE_GFX(dl++, 0xFA000000, 0xFFFF00FF);
    scaledSpriteY = (s16)(s32)((posY + posY) * 4.0f);
    for (xOffset = 0; xOffset < 0x78; xOffset += 0x18) {
        xOffsetF = xOffset;
        dl = renderRotatedSprite(dl, 0x4B, 3, 1, 0x40, 0x40, (s32)((doublePosX + xOffsetF) * 4.0f), scaledSpriteY, 1.5f, 1.5f, 0, 0.0f);
    }
    WRITE_GFX(dl++, 0xFA000000, 0xFF0000FF);
    count = 0;
    if ((5 - tracker->gateMissesLeft) > 0) {
        xOffset = 0;
        do {
            xOffsetF = xOffset;
            next = renderRotatedSprite(dl, 0x45, 3, 1, 0x40, 0x40, (s32)((doublePosX + xOffsetF) * 4.0f), scaledSpriteY, 1.5f, 1.5f, 0, 0.0f);
            count += 1;
            xOffset += 0x18;
            dl = next; // FAKE: delayed dl update steers the loop schedule
        } while (count < (5 - tracker->gateMissesLeft));
    }
    WRITE_GFX(dl++, 0xDA380003, (u32)&D_2000180);
    return dl;
}


Gfx *raceInitHudDisplayList(Gfx *dl, RaceParticipant *tracker) {
    WRITE_GFX(dl++, 0xE7000000, 0);
    WRITE_GFX(dl++, 0xE200001C, 0x00504240);
    WRITE_GFX(dl++, 0xE3000A01, 0);
    WRITE_GFX(dl++, 0xFC119623, 0xFF2FFFFF);
    dl = gfxInit2DDisplayList(dl);
    WRITE_GFX(dl++, 0xDE000000, (u32)&D_1000118);
    WRITE_GFX(dl++, 0xDA380007, (u32)&D_20000C0);
    guScale((Mtx *)tracker->hudScale[gGfxBufferIndex], 0.5f, 0.5f, 1.0f);
    WRITE_GFX(dl++, 0xDA380005, (u32)tracker->hudScale[gGfxBufferIndex]);
    WRITE_GFX(dl++, 0xDA380003, (u32)&D_2000180);
    return dl;
}

s32 sRacePlaceTextIds[5] = { 4, 5, 6, 7, 8 };

Gfx *raceDrawHudText(Gfx *dl, RaceParticipant *tracker) {
    RaceParticipant *managerData;
    G00Entry *hudPos;
    s32 pad;
    u8 *textBuf;
    u8 lap;
    s32 textX;
    s32 textY;
    s32 placeIdx;
    u32 fontHeight;
    u8 *lapStr;
    u8 *ofStr;
    s32 len;
    s32 pad2;
    Gfx *g0;

    hudPos = tracker->viewport;
    lap = tracker->lap;
    managerData = tracker->actor->customState;
    textX = hudPos->left + 8;
    textY = hudPos->bottom - 0x10;
    g0 = dl++;
    g0->words.w0 = 0xE7000000; g0->words.w1 = 0; // LAYOUT: same-line stores keep the w1 store first
    gDPSetPrimColor(dl++, 0, 0, 0xFF, 0xFF, 0xFF, 0xFF);
    if (managerData->hudFlags & 4) {
        lap = (lap < managerData->lapCount) ? lap : managerData->lapCount;
        lap = (lap >= 2) ? lap : 1;
        lapStr = textTableGetString(0x26, 0xB, 1);
        ofStr = textTableGetString(0x26, 0xC, 1);
        len = strlen(lapStr);
        len += strlen(ofStr);
        textBuf = heapAlloc(len + 8);
        heapFreeDeferred(textBuf);
        _sprintf(textBuf, "%s %d %s %d", lapStr, lap, ofStr, managerData->lapCount);
        dl = textDrawStringVtx(dl, 1, (s16)(2.0f * (textX * 4)), (s16)(2.0f * (textY * 4)), textBuf, 4);
        g0 = dl++;
        g0->words.w0 = 0xDA380007; g0->words.w1 = (u32)&D_20000C0; // LAYOUT: same-line stores steer the ori/addiu schedule
        g0 = dl++;
        g0->words.w0 = 0xDA380005;
        g0->words.w1 = (u32)tracker->hudScale[gGfxBufferIndex];
        fontHeight = textGetFontHeight(1);
        textY -= 0.5f * fontHeight;
    }
    if (managerData->hudFlags & 2) {
        placeIdx = tracker->place;
        if ((placeIdx + 1) == managerData->participantCount) {
            placeIdx = 3;
        }
        if (tracker->eliminated != 0) {
            placeIdx = 4;
        }
        dl = textDrawStringVtx(dl, 1, (s16)(2.0f * (textX * 4)), (s16)(2.0f * (textY * 4)), textTableGetString(0x26, sRacePlaceTextIds[placeIdx], 1), 4);
    }
    if (tracker->raceStatus >= 3 && tracker->raceStatus < 5) {
        dl = textDrawAnimated(dl, tracker->resultTextId, 2, 160.0f, 100.0f, 0.0f, 1.5f);
    }
    return dl;
}



Gfx *raceRenderHud(Gfx *dl, Actor *actor, RaceParticipant *tracker) {
    RaceParticipant *managerData;
    Actor *playerActor;
    PlayerState *playerState;

    managerData = tracker->actor->customState;
    if (tracker == NULL || menuIsTransitionType3Or4() != 0) {
        return dl;
    }
    playerActor = gPlayerSlots[tracker->playerIdx].actor;
    if (playerActor == NULL) {
        return dl;
    }
    playerState = playerActor->customState;
    if (actor != playerState->actor) {
        return dl;
    }
    dl = raceInitHudDisplayList(dl, tracker);
    if (managerData->hudFlags & 8) {
        dl = raceRenderCoinHud(dl, tracker);
    } else if (managerData->hudFlags & 0x10) {
        dl = raceRenderSpeedBoostHud(dl, tracker);
    }
    if (managerData->hudFlags & 6) {
        dl = raceDrawHudText(dl, tracker);
    }
    return dl;
}


Gfx *raceRenderMinimapAndCountdown(Gfx *dl, Actor *actor) {
    RaceParticipant *managerData;
    RaceParticipant *participantData;
    Actor *participantActor;
    Actor *targetActor;
    RacePair *pairs;
    s32 i;
    s32 red;
    s32 blue;

    managerData = actor->customState;
    if (managerData->hudFlags & 1) {
        pairs = managerData->pairs;
        gDPPipeSync(dl++);
        gSPTexture(dl++, 0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_OFF);
        gDPSetRenderMode(dl++, G_RM_XLU_SURF, G_RM_XLU_SURF2);
        dl = gfxInit2DDisplayList(dl);
        gDPSetPrimColor(dl++, 0, 0, 0x00, 0x00, 0x3C, 0xA0);
        gDPSetCycleType(dl++, G_CYC_1CYCLE);
        gDPSetCombineMode(dl++, G_CC_PRIMITIVE, G_CC_PRIMITIVE);
        gDPFillRectangle(dl++, 0x12, 0x1C, 0x52, 0x5C);
        gDPPipeSync(dl++);
        gDPSetPrimColor(dl++, 0, 0, 0x80, 0x00, 0xFF, 0x64);
        gDPFillRectangle(dl++, 0x10, 0x1A, 0x54, 0x1C);
        gDPFillRectangle(dl++, 0x10, 0x5C, 0x54, 0x5E);
        gDPFillRectangle(dl++, 0x10, 0x1C, 0x12, 0x5C);
        gDPFillRectangle(dl++, 0x52, 0x1C, 0x54, 0x5C);
        gDPPipeSync(dl++);
        gDPSetPrimColor(dl++, 0, 0, 0xFF, 0xFF, 0xFF, 0xB4);
        gDPSetCombineMode(dl++, G_CC_MODULATEIA_PRIM, G_CC_MODULATEIA_PRIM);
        gSPMatrix(dl++, &D_2000180, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
        gSPMatrix(dl++, &D_20000C0, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_PROJECTION);
        gSPTexture(dl++, 0x8000, 0x8000, 0, G_TX_RENDERTILE, G_ON);
        dl = renderRotatedSprite(dl, managerData->minimapSprites[0], 3, 1, 0x40, 0x40, 0x88, 0x130, 2.0f, 2.0f, 0, 0.0f);
        dl = renderRotatedSprite(dl, managerData->minimapSprites[1], 3, 1, 0x40, 0x40, 0x108, 0x130, 2.0f, 2.0f, 0, 0.0f);
        dl = renderRotatedSprite(dl, managerData->minimapSprites[2], 3, 1, 0x40, 0x40, 0x88, 0xB0, 2.0f, 2.0f, 0, 0.0f);
        dl = renderRotatedSprite(dl, managerData->minimapSprites[3], 3, 1, 0x40, 0x40, 0x108, 0xB0, 2.0f, 2.0f, 0, 0.0f);
        for (i = 0; i < managerData->participantCount; i++) {
            participantActor = pairs[i].actor;
            if (participantActor == NULL) {
                continue;
            }
            participantData = pairs[i].data;
            if (participantData->isCpu == 0) {
                red = 0x80;
                blue = 0x80;
            } else if (participantData->isCpu == 1) {
                red = 0xFF;
                blue = 0;
            } else {
                continue;
            }
            dl = raceRenderMinimapIcon(dl, actor, participantActor->x, participantActor->z, red, 0, blue);
            targetActor = participantData->projectile;
            if (targetActor != NULL) {
                dl = raceRenderMinimapIcon(dl, actor, targetActor->x, targetActor->z, 0xFF, 0xC8, 0);
            }
        }
    }
    return raceRenderCountdownText(dl, actor);
}


extern Actor *gSpawnedActor;


void raceInitCarRaceManager(void) {
    RaceParticipant *managerData;
    Actor *actor;

    actorSpawn(0x132, 0);
    actor = gSpawnedActor;
    raceInitOpponentEntities(actor);
    raceCalculatePathBoundingBox(actor);
    managerData = actor->customState;
    managerData->hudFlags = 0x17;
    managerData->minimapSprites[0] = 0x46;
    managerData->minimapSprites[1] = 0x47;
    managerData->minimapSprites[2] = 0x48;
    managerData->minimapSprites[3] = 0x49;
    managerData->lapCount = 2;
}


void raceInitGenericRaceManager(void) {
    RaceParticipant *managerData;

    actorSpawn(0x132, 0);
    managerData = gSpawnedActor->customState;
    raceInitParticipants(gSpawnedActor);
    managerData->hudFlags = 0xE;
    managerData->lapCount = 2;
}

void raceInitCompetitorRaceManager(void) {
    RaceParticipant *managerData;

    actorSpawn(0x132, 0);
    managerData = gSpawnedActor->customState;
    raceSpawnCompetitors(gSpawnedActor);
    managerData->hudFlags = 0xE;
    managerData->lapCount = 2;
}

void raceInitBeetleRaceManager(void) {
    RaceParticipant *managerData;

    actorSpawn(0x132, 0);
    managerData = gSpawnedActor->customState;
    raceInitBeetleRaceParticipants(gSpawnedActor);
    managerData->hudFlags = 2;
    managerData->lapCount = 1;
}

extern Actor *gCurrentActor;
s32 sRaceResultTextIds[4] = { 0, 1, 2, 3 };

void raceSetParticipantRaceStatus(RacePair *pair, u8 newStatus) {
    RaceParticipant *managerData;
    u32 slot;

    if (pair->data->raceStatus != newStatus) {
        pair->data->raceStatus = newStatus;
        pair->data->statusStep = 0;
        if (newStatus == 3) {
            managerData = gCurrentActor->customState;
            slot = pair->data->place;
            if (slot + 1 == managerData->participantCount || pair->data->eliminated != 0) {
                slot = 3;
            }
            if (pair->data->isCpu == 0) {
                pair->data->resultTextId = gfxResourceCreate(1, textTableGetString(0x26, sRaceResultTextIds[slot], 1), 2, 160.0f, 100.0f, 0.0f);
            }
        }
    }
}


void raceSetAllParticipantsStatus(u8 newStatus) {
    s32 i;
    RaceParticipant *managerData;
    RacePair *pairs;

    managerData = gCurrentActor->customState;
    pairs = managerData->pairs;
    gCurrentActor->state = newStatus;
    for (i = 0; i < managerData->participantCount; i++) {
        if (pairs[i].actor != NULL) {
            raceSetParticipantRaceStatus(&pairs[i], newStatus);
        }
    }
}

f32 raceGetHandicapSpeedBonus(RaceParticipant *participant) {
    f32 temp;

    if (participant->route >= 11 && participant->route < 15 && (gPlayerPadState[participant->playerIdx].heldButtons & 0x2000)) {
        temp = participant->route - 10;
        return temp * 0.2f;
    }
    return 0.0f;
}

void raceDespawnProjectile(Actor *projectile, RaceAuxState *projectileData) {
    Actor *owner;
    RaceParticipant *ownerData;

    owner = projectileData->owner;
    ownerData = owner->customState;
    ownerData->projectile = NULL;
    actorDespawn(projectile);
}

Actor *raceFindNearestParticipant(Actor *self) {
    Actor *manager;
    f32 best;
    f32 distSq;
    RaceParticipant *selfData;
    Actor *nearest;
    Actor *other;
    RaceParticipant *managerData;
    RacePair *pairs;
    s32 i;

    best = 1e9f;
    selfData = self->customState;
    manager = selfData->actor;
    managerData = manager->customState;
    nearest = NULL;
    pairs = managerData->pairs;
    for (i = 0; i < managerData->participantCount; i++) {
        other = pairs[i].actor;
        if (other != NULL && other != self) {
            distSq = (self->x - other->x) * (self->x - other->x) + (self->y - other->y) * (self->y - other->y) + (self->z - other->z) * (self->z - other->z);
            if (distSq < best) {
                nearest = other;
                best = distSq;
            }
        }
    }
    return nearest;
}


void racePlayResultSfx(void) {
    RaceParticipant *managerData;
    RacePair *pairs;
    RaceParticipant *participantData;
    s32 i;
    s32 sfxId;

    managerData = gCurrentActor->customState;
    sfxId = 0;
    pairs = managerData->pairs;
    for (i = managerData->participantCount - 1; sfxId == 0 && i >= 0; i--) {
        participantData = pairs[i].data;
        if (participantData->isCpu == 1) {
            if (participantData->place != 0) {
                sfxId = 0x56;
            } else {
                sfxId = 0x57;
            }
        }
    }
    if (sfxId == 0) {
        sfxId = 0x56;
    }
    sfxAllocateChannel(sfxId, 1.0f);
}

extern s32 gCurrentMap;

void racePlayStartRaceMusic(void) {
    s32 soundId;
    f32 vol;

    vol = 1.0f;
    switch (gCurrentMap) {
    case 0xE:
        soundId = 0x13;
        vol = 0.6f;
        break;
    case 0x27:
        soundId = 0x3D;
        break;
    case 0x52:
        soundId = 0x66;
        break;
    case 0x1B:
    default:
        soundId = 0x1B;
        break;
    }
    sfxAllocateChannel(soundId, vol);
}

void raceUpdateStandings(void) {
    RaceParticipant *managerData;
    RacePair *pairs;
    RacePair *p;
    RacePair *q;
    s32 i;
    s32 j;
    RacePair tmp;
    u8 finishedCount;
    u8 swap;

    managerData = gCurrentActor->customState;
    finishedCount = 0;
    pairs = managerData->pairs;
    for (i = managerData->participantCount - 1; i >= 0; i--) {
        for (j = 1; j <= i; j++) {
            p = &pairs[j - 1];
            q = &pairs[j];
            swap = 0;
            if (p->data->eliminated != 0 && q->data->eliminated == 0) {
                swap = 1;
            } else if (p->data->lap < q->data->lap) {
                swap = 1;
            } else if (p->data->lap == q->data->lap) {
                if (p->data->routePos < q->data->routePos) {
                    swap = 1;
                } else if (p->data->routePos == q->data->routePos && q->data->nextPointDist < p->data->nextPointDist) {
                    swap = 1;
                }
            }
            if (swap != 0) {
                tmp = *p;
                *p = *q;
                *q = tmp;
            }
        }
    }
    q = pairs;
    for (i = 0; i < managerData->participantCount; i++, q++) {
        q->data->place = i;
        if (q->data->eliminated != 0 || (q->data->raceStatus == 2 && managerData->lapCount < q->data->lap)) {
            raceSetParticipantRaceStatus(q, 3);
            finishedCount++;
        }
    }
    if (finishedCount >= managerData->participantCount - 1) {
        raceSetAllParticipantsStatus(3);
        racePlayResultSfx();
        managerData->phaseTimer = 0;
    }
}

void raceSetIntroCutscenePhase(Actor *actor) {
    RaceParticipant *managerData;

    if (actor != NULL && actor->state == 0) {
        managerData = actor->customState;
        managerData->phaseTimer = 2;
    }
}

void raceClearIntroCutscenePhase(Actor *actor) {
    RaceParticipant *managerData;

    if (actor != NULL && actor->state == 0) {
        managerData = actor->customState;
        managerData->phaseTimer = 0;
    }
}



void raceManagerBehaviorUpdate(void) {
    RaceParticipant *managerData;
    u16 sound;
    u8 i;
    RaceParticipant *participantData;
    f32 scale;
    Actor *playerActor;
    s32 axis;
    RacePair *pairs;

    managerData = gCurrentActor->customState;
    if (!(gCurrentActor->flags & 0x10)) {
        managerData->phaseTimer = 0x1E;
    }
    switch (gCurrentActor->state) {
    case 0:
        if (managerData->phaseTimer) {
            managerData->phaseTimer--;
        } else {
            raceSetAllParticipantsStatus(1);
        }
        break;
    case 1:
        if (managerData->phaseTimer < 0x5B) {
            if (managerData->phaseTimer % 30 == 0) {
                sound = 0x75;
                if (managerData->phaseTimer == 0x5A) {
                    raceSetAllParticipantsStatus(2);
                    sound = 0x74;
                    racePlayStartRaceMusic();
                }
                sfxPlayOnFreeSlot(sound, 0x7FFF, 64.0f, 1.0, 0, 0x80);
            }
            managerData->phaseTimer++;
        }
        break;
    case 2:
        if (managerData->phaseTimer < 0x78) {
            managerData->phaseTimer++;
        }
        raceUpdateStandings();
        break;
    case 3:
        if (gCurrentMap == 0xE || gCurrentMap == 0x52) {
            raceSetAllParticipantsStatus(4);
            managerData->phaseTimer = 0x32;
        } else {
            managerData->phaseTimer++;
            if (managerData->phaseTimer >= 0x78) {
                if (managerData->hasCpuRival == 1) {
                    raceSetAllParticipantsStatus(4);
                    managerData->phaseTimer = 0x32;
                } else {
                    raceSetAllParticipantsStatus(6);
                }
            }
        }
        break;
    case 4:
        if (managerData->phaseTimer) {
            managerData->phaseTimer--;
        } else {
            pairs = managerData->pairs;
            for (i = 0; i < managerData->participantCount; i++) {
                participantData = pairs[i].data;
                if (participantData->isCpu == 0) {
                    playerActor = gPlayerSlots[participantData->playerIdx].actor;
                    scale = 1.0f;
                    playerActor->alpha = 0xFF;
                    playerActor->flags |= 0x8000;
                    if (gCurrentMap == 0xB9) {
                        scale = 0.3f;
                    }
                    for (axis = 0; axis < 3; axis++) {
                        playerActor->sub4->scale[axis] = scale * 0.15;
                    }
                    playerActor->roll = 0;
                    playerActor->pitch = 0;
                }
            }
            raceSetAllParticipantsStatus(5);
        }
        break;
    }
    raceUpdateWaypointActivation(managerData);
    if (menuIsTransitionType3Or4() == 0) {
        if (gCurrentActor->state > 0 && gCurrentActor->state < 5) {
            renderCallbacksRegister(raceRenderMinimapAndCountdown, gCurrentActor, 3);
        }
    }
}


// Finish-line banner/flag component (raceFinishBannerBehaviorUpdate): which banner it is, the flag's
// bob angle and the model scale it bobs around.
typedef struct RaceBannerState {
    /* 0x0 */ u8 kind;
    /* 0x1 */ u8 pad1;
    /* 0x2 */ s16 bobAngle;
    /* 0x4 */ f32 baseScale;
} RaceBannerState;

void raceUpdateFinishLineFlagBobbing(RaceBannerState *banner) {
    s16 angle;
    f32 scale;

    switch (gCurrentActor->state) {
    case 0:
        angle = banner->bobAngle;
        if (((s16)(angle % 2048) >= 0x81) && ((0x800 - (s16)(angle % 2048)) >= 0x81)) {
            banner->bobAngle = angle + 0x80;
            angle = banner->bobAngle;
        }
        break;
    case 1:
        banner->bobAngle += 0x80;
        angle = banner->bobAngle;
        break;
    default:
        angle = banner->bobAngle;
        break;
    }
    banner->bobAngle = angle & 0xFFF;
    scale = (((mathSinF(banner->bobAngle) + 1.0f) * 1.5) + 1.0) * banner->baseScale;
    gCurrentActor->sub4->scaleX = gCurrentActor->sub4->scaleY = gCurrentActor->sub4->scaleZ = scale;
}

void raceUpdateCheckeredFlagAnimation(void) {
    if (gCurrentActor->state != 0) {
        if (gCurrentActor->state == 1) {
            if (animIsPlaying(gCurrentActor, 0) == 0) {
                animSetSpeed(gCurrentActor, 0, 1.0f);
                animSetLoopLimit(gCurrentActor, 0, -1);
            }
        }
    } else {
        if (animIsPlaying(gCurrentActor, 0) != 0) {
            animSetFinished(gCurrentActor, 0, 1);
        }
    }
}


void raceFinishBannerBehaviorUpdate(void) {
    RaceBannerState *banner = gCurrentActor->customState;

    if (!(gCurrentActor->flags & 0x10)) {
        banner->baseScale = gCurrentActor->sub4->scaleY;
    }
    switch (banner->kind) {
    case 2:
        raceUpdateCheckeredFlagAnimation();
        break;
    case 1:
        raceUpdateCheckeredFlagAnimation();
        actorUpdateFloorContactAndTilt(gCurrentActor, 0.0f);
        gCurrentActor->y = gCurrentActor->waterY;
        gCurrentActor->contactFlags |= 4;
        gCurrentActor->prevContactFlags |= 4;
        break;
    default:
        raceUpdateFinishLineFlagBobbing(banner);
        break;
    }
    actorUpdateModelMatrix(gCurrentActor, 0);
}

// Gate post component: how many participants currently have this gate active.
typedef struct RaceGatePostState {
    /* 0x0 */ u8 pad0[8];
    /* 0x8 */ u8 refCount;
} RaceGatePostState;

void raceSetGateVisualState(RaceWaypoint *waypoint, s32 state) {
    u8 i;
    Actor *post;
    RaceGatePostState *postState;

    for (i = 0; i < 2; i++) {
        post = waypoint->actors[i];
        if (post != NULL) {
            postState = post->customState;
            if (state == 1) {
                if (postState->refCount == 0) {
                    post->state = state;
                }
                postState->refCount = postState->refCount + 1;
            } else {
                if (postState->refCount != 0) {
                    postState->refCount = postState->refCount - 1;
                }
                if (postState->refCount == 0) {
                    post->state = state;
                }
            }
        }
    }
}

f32 raceLerp(f32 t, f32 x0, f32 y0, f32 x1, f32 y1) {
    return ((y1 - y0) * ((t - x0) / (x1 - x0))) + y0;
}

f32 raceEvaluatePiecewiseCurve(f32 targetX, RaceCurvePoint *points) {
    u8 i;
    f32 ret;
    s32 found;

    found = 0;
    i = 1;
    if (targetX < points[0].x) {
        ret = points[0].y;
        found = 1;
    }
    if (found == 0) {
        do {
            f32 x = points[i].x;
            if (targetX < x) {
                ret = raceLerp(targetX, points[i - 1].x, points[i - 1].y, x, points[i].y);
                found = 1;
            }
            i++;
        } while (i < 6 && found == 0);
    }
    if (found == 0) {
        ret = points[5].y;
    }
    return ret;
}

void raceSetPiecewiseCurveMode(RaceTarget *target, u8 mode, RaceCurvePoint *points, RaceVec3f *values) {
    switch (mode) {
    case 0:
    case 1:
        points[0].y = values->x;
        points[1].y = values->y;
        points[2].y = values->y;
        points[3].y = values->y;
        points[4].y = values->y;
        points[5].y = values->z;
        break;
    case 2:
    case 3:
        points[3].y = values->z;
        points[4].y = values->z;
        points[5].y = values->z;
        break;
    case 5:
        points[0].y = values->x;
        points[1].y = values->z;
        points[2].y = values->z;
        points[3].y = values->z;
        points[4].y = values->z;
        points[5].y = values->z;
        break;
    }
    gCurrentActor->subState = 0;
    target->curveMode = mode;
}


f32 raceEvaluateCurveWithRubberband(RaceTarget *target, f32 t, RaceCurvePoint *points, RaceVec3f *values) {
    f32 ret;
    f32 lim;
    RaceParticipant *chased;

    switch (target->curveMode) {
    case 0:
        ret = raceEvaluatePiecewiseCurve(t, points);
        break;
    case 1:
        ret = raceEvaluatePiecewiseCurve(t, points);
        if (target->chaseEnabled != 0) {
            if (points[4].x < t) {
                if ((u32)randomLcgNext() % 0xFF < 0xA) {
                    raceSetPiecewiseCurveMode(target, 2, points, values);
                }
            }
        }
        break;
    case 2:
    case 3:
    case 4:
        if (target->curveMode == 3 || target->curveMode == 4 || target->chaseEnabled != 0) {
            chased = target->participant;
            lim = chased->throttle;
            points[0].y = lim < values->x ? lim : values->x;
            points[1].y = lim < values->y ? lim : values->y;
            if (target->curveMode == 4) {
                points[2].y = lim;
            } else {
                points[2].y = values->z;
            }
            ret = raceEvaluatePiecewiseCurve(t, points);
            if (target->curveMode == 2) {
                if (t < points[3].x) {
                    raceSetPiecewiseCurveMode(target, 3, points, values);
                }
            }
            if (target->curveMode == 3) {
                if (t < points[2].x) {
                    raceSetPiecewiseCurveMode(target, 4, points, values);
                }
            }
        } else if (target->curveMode == 2) {
            ret = values->y;
            raceSetPiecewiseCurveMode(target, 1, points, values);
        }
        break;
    case 5:
        ret = raceEvaluatePiecewiseCurve(t, points);
        if (t < points[1].x) {
            raceSetPiecewiseCurveMode(target, 1, points, values);
        }
        break;
    default:
        ret = 0.0f;
        break;
    }
    return ret;
}

f32 raceEvaluateCurveTargetSpeed(RaceTarget *target, f32 t, RaceCurvePoint *points, RaceVec3f *values) {
    f32 ret;

    switch (target->curveMode) {
    case 0:
        ret = raceEvaluatePiecewiseCurve(t, points);
        break;
    case 1:
        ret = raceEvaluatePiecewiseCurve(t, points);
        if (target->chaseEnabled != 0) {
            if (points[4].x < t) {
                raceSetPiecewiseCurveMode(target, 5, points, values);
            }
        }
        break;
    case 5:
        ret = raceEvaluatePiecewiseCurve(t, points);
        if (t < points[1].x) {
            raceSetPiecewiseCurveMode(target, 1, points, values);
        }
        break;
    default:
        ret = 0.0f;
        break;
    }
    return ret;
}

extern u8 gPlayerCount;

void raceInitBeetleRaceParticipants(Actor *raceManager) {
    RaceParticipant *managerData;
    RaceParticipant *participantData;
    Actor *participantActor;
    s32 slotIndex;
    s32 playerIdx;
    s32 participantCount;

    participantCount = gPlayerCount;
    slotIndex = 0;
    managerData = raceManager->customState;
    if (participantCount == 1) {
        participantCount++;
    }
    raceInitParticipantArray(raceManager, participantCount);
    if (gPlayerCount == 1) {
        participantActor = spawnNodeSpawnById(1, 0, 0, 0, 0, 0, 0);
        participantData = ((RaceComponentActor *)participantActor)->participant;
        participantData->isCpu = 1;
        raceRegisterParticipant(raceManager, 0, participantActor, participantData);
        slotIndex = 1;
        raceGetParticipantPair(raceManager, 0, &((RaceComponentActor *)participantActor)->target->actor, &((RaceComponentActor *)participantActor)->target->participant);
        managerData->hasCpuRival = 1;
    } else {
        managerData->hasCpuRival = 0;
    }
    for (playerIdx = 0; playerIdx < gPlayerCount; playerIdx++) {
        actorSpawn(0x13B, 0);
        participantActor = gSpawnedActor;
        participantData = participantActor->customState;
        participantData->isCpu = 0;
        raceRegisterParticipant(raceManager, slotIndex, participantActor, participantData);
        slotIndex++;
        participantData->playerIdx = playerIdx;
    }
    for (playerIdx = 0; playerIdx < participantCount; playerIdx++) {
        raceGetParticipantPair(raceManager, playerIdx, &participantActor, &participantData);
        participantData->place = playerIdx;
        participantData->actor = raceManager;
    }
    managerData->route = 0;
}


Gfx *racePlayerHudRenderCallback(Gfx *gfx, Actor *actor) {
    return raceRenderHud(gfx, actor, actor->customState);
}


void racePlayerTrackerBehaviorUpdate(void) {
    Actor *playerActor;
    RaceParticipant *raceData;
    f32 curMax;
    f32 diff;

    raceData = gCurrentActor->customState;
    playerActor = gPlayerSlots[raceData->playerIdx].actor;
    if (!(gCurrentActor->flags & 0x10)) {
        playerStateQueueCallback(0x4E, gCurrentActor, raceData->playerIdx);
        gCurrentActor->state = 0;
        gCurrentActor->subState = 0;
    }
    if ((raceData->raceStatus == 2) && (gCurrentActor->state == 0)) {
        playerStateQueueCallback(0x57, NULL, raceData->playerIdx);
        gCurrentActor->state++;
    }
    gCurrentActor->x = playerActor->x;
    gCurrentActor->y = playerActor->y;
    gCurrentActor->z = playerActor->z;
    if (raceData->raceStatus == 2) {
        raceUpdateLapAndWaypointTracker(raceData);
    }
    if ((raceData->raceStatus > 0) && (raceData->raceStatus < 5)) {
        renderCallbacksRegister(racePlayerHudRenderCallback, gCurrentActor, 3);
    }
    raceData->maxNextPointDistSq = (raceData->nextPointDist < raceData->maxNextPointDistSq) ? raceData->maxNextPointDistSq : raceData->nextPointDist;
    curMax = raceData->maxProgressScore;
    diff = (f32)(raceData->routePos * 3000) - raceData->nextPointDist;
    raceData->progressScore = diff;
    raceData->maxProgressScore = (diff < curMax) ? curMax : raceData->progressScore;
}


void raceHandleRacerCollision(RaceTarget *target) {
    f32 distSq;
    f32 pad;
    f32 velX;
    f32 velZ;
    f32 playerVel;
    s16 diffAnglePlayer;
    s16 diffAngleActor;
    s16 targetAngle;
    f32 bounceScale;
    s32 sfxId;
    Actor *racer;

    racer = target->actor;
    distSq = (racer->x - gCurrentActor->x) * (racer->x - gCurrentActor->x) + (racer->z - gCurrentActor->z) * (racer->z - gCurrentActor->z);
    if (gActorGlobalState.bossFightPhase == 4 && distSq < target->distSq && (target->curveMode == 1 || target->curveMode == 0 || target->curveMode == 4 || (gCurrentActor->actorType == 0x143 && target->curveMode == 5))) {
        targetAngle = mathAngleBetweenPoints2D(gCurrentActor->x, gCurrentActor->z, racer->x, racer->z);
        bounceScale = 1.0f;
        if (mathAngleDistance(racer->moveYaw, targetAngle) < 0x200) {
            bounceScale = 4.0f;
        }
        diffAngleActor = (s16)(racer->moveYaw - targetAngle) & 0xFFF;
        diffAnglePlayer = (s16)(gCurrentActor->moveYaw - targetAngle);
        diffAnglePlayer = diffAnglePlayer & 0xFFF;
        velX = mathSinF(diffAngleActor) * racer->speedXZ;
        velZ = mathCosF(diffAngleActor) * racer->speedXZ;
        playerVel = mathCosF(diffAnglePlayer) * gCurrentActor->speedXZ;
        velZ = (playerVel - velZ) * bounceScale + playerVel;
        racer->speedXZ = sqrtf(velX * velX + velZ * velZ);
        racer->moveYaw = (s16)(s32)(((f64)mathAtan2(velX, velZ) * 4096.0) / 6.2831854820251465);
        racer->moveYaw = racer->moveYaw + targetAngle;
        racer->moveYaw = racer->moveYaw & 0xFFF;
        if (target->bumpCooldown == 0) {
            switch (gCurrentActor->actorType) {
            case 0x134:
                sfxId = 0x1F9;
                break;
            case 0x143:
                sfxId = 0x18A;
                break;
            }
            sfxPlayAtPositionPooled(gCurrentActor->x, gCurrentActor->y, gCurrentActor->z, (s16)sfxId, 0xFF, 0x7F, 0, 0, 0.0f, 0);
            target->bumpCooldown = 0x14;
        }
    }
    target->distSq = distSq;
    if (target->bumpCooldown > 0) {
        target->bumpCooldown--;
    }
}

s32 raceCheckLapCompletionThreshold(RaceParticipant *participant, RaceParticipant *other, s32 threshold) {
    s32 ret;

    if (other->eliminated != 0) {
        ret = 0;
    } else if (participant->place != 0) {
        if (slotQueueGetValue(11, 0) >= threshold) {
            ret = 1;
        } else {
            ret = 3;
        }
    } else {
        ret = 2;
    }
    return ret;
}
