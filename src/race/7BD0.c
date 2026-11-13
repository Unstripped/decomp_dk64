#include "common.h"
#include "race.h"
#include "sched.h"
#include "proto/boot/3630.h"
#include "proto/boot/3D20.h"
#include "proto/global/100180.h"
#include "proto/global/1025E0.h"
#include "proto/global/112080.h"
#include "proto/global/117190.h"
#include "proto/global/1295B0.h"
#include "proto/global/15050.h"
#include "proto/global/166A0.h"
#include "proto/global/35000.h"
#include "proto/global/450.h"
#include "proto/global/69E60.h"
#include "proto/global/7130.h"
#include "proto/global/7CA80.h"
#include "proto/global/8CA50.h"
#include "proto/global/90D80.h"
#include "proto/global/CC800.h"
#include "proto/global/CEAE0.h"
#include "proto/global/EFDC0.h"
#include "proto/global/FCCD0.h"
#include "proto/race/1770.h"
#include "proto/race/52B0.h"
#include "proto/race/6650.h"
#include "proto/race/7BD0.h"
#include "proto/race/A960.h"

extern PlayerStruct *gPlayerSlots;

typedef struct Struct_807FD63A {
    u16 unk0;
    char pad2[0x32];
} Struct_807FD63A;
extern Struct_807FD63A D_807FD63A[];




void raceInitParticipantArray(Actor *actor, s32 count) {
    RaceParticipant *managerData;
    void *allocated;

    managerData = actor->customState;
    allocated = heapAlloc(count * sizeof(RacePair));
    managerData->pairs = allocated;
    heapClearBlock(allocated);
    managerData->unk1E = count;
    managerData->unk1C = 0xFFFF;
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
    participantData->unk45 = 0;
    participantData->unk3A = 0;
    participantData->lap = 1;
    if (participantData->unk27 == 0) {
        route = raceGetRoute(managerData->route);
        if (route != NULL) {
            participantData->unk3C = route->count - 1;
            raceActivateNextGate(participantData, route);
        }
        participantData->unk48 = cameraFindViewportEntry(participantData->playerIdx);
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

typedef struct RaceEBounds {
    f32 *start;
    char pad4[8];
    f32 *end;
} RaceEBounds;
extern RaceEBounds *gMinecartTrackPoints;

void raceCalculatePathBoundingBox(Actor *actor) {
    RaceParticipant *managerData;
    f32 *p;
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
    for (p = gMinecartTrackPoints->start; p < gMinecartTrackPoints->end; p += 3) {
        x = p[0];
        if (x < minX) {
            minX = x;
        }
        z = p[2];
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
    managerData->unkC = ((maxX - minX) * 0.5f + minX) - 10.0f;
    managerData->unk10 = ((maxZ - minZ) * 0.5f + minZ) - 20.0f;
    managerData->unk4 = 116.48f / (maxX - minX);
    managerData->unk8 = 121.6f / (maxZ - minZ);
}


Gfx *raceRenderMinimapIcon(Gfx *dl, Actor *actor, f32 posX, f32 posZ, u8 red, u8 green, u8 blue) {
    RaceParticipant *managerData;

    managerData = actor->customState;
    posX = managerData->unkC - posX;
    posZ = managerData->unk10 - posZ;
    posX *= managerData->unk4;
    posZ *= managerData->unk8;
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
        if (managerData->unk1C < 0x78) {
            if (managerData->unk1C < 0x5A) {
                countdownVal = (0x78 - managerData->unk1C) / 30;
                if (countdownVal >= 3) {
                    countdownVal = 3;
                }
                textStr = heapAlloc(4);
                heapFreeDeferred(textStr);
                _sprintf(textStr, "%d", countdownVal);
            } else {
                fadeFactor = (f32)(0x78 - managerData->unk1C) * 0.033333335f;
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

    hudPos = tracker->unk48;
    screenX = (s32)((f64)(hudPos->left + 8) + 4.0);
    screenY = hudPos->bottom - 0x22;
    WRITE_GFX(dl++, 0xFA000000, 0xFFC800B4);
    i = 0;
    if (tracker->unk2A > 0) {
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
        } while (i < tracker->unk2A);
    }
    if (tracker->unk2A != 0) {
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

    hudPos = tracker->unk48;
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
    if ((5 - tracker->unk44) > 0) {
        xOffset = 0;
        do {
            xOffsetF = xOffset;
            next = renderRotatedSprite(dl, 0x45, 3, 1, 0x40, 0x40, (s32)((doublePosX + xOffsetF) * 4.0f), scaledSpriteY, 1.5f, 1.5f, 0, 0.0f);
            count += 1;
            xOffset += 0x18;
            dl = next; // FAKE: delayed dl update steers the loop schedule
        } while (count < (5 - tracker->unk44));
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

extern s32 D_8002FCC0[];

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
    s32 hudFlags;
    Gfx *g0;

    hudPos = tracker->unk48;
    lap = tracker->unk37;
    managerData = tracker->actor->customState;
    textX = hudPos->left + 8;
    textY = hudPos->bottom - 0x10;
    g0 = dl++;
    g0->words.w0 = 0xE7000000; g0->words.w1 = 0; // LAYOUT: same-line stores keep the w1 store first
    WRITE_GFX(dl++, 0xFA000000, 0xFFFFFFFF);
    hudFlags = managerData->hudFlags;
    if (hudFlags & 4) {
        lap = (lap < managerData->unk24) ? lap : managerData->unk24;
        lap = (lap >= 2) ? lap : 1;
        lapStr = textTableGetString(0x26, 0xB, 1);
        ofStr = textTableGetString(0x26, 0xC, 1);
        len = strlen(lapStr);
        len += strlen(ofStr);
        textBuf = heapAlloc(len + 8);
        heapFreeDeferred(textBuf);
        _sprintf(textBuf, "%s %d %s %d", lapStr, lap, ofStr, managerData->unk24);
        dl = textDrawStringVtx(dl, 1, (s16)(s32)(2.0f * (f32)(textX * 4)), (s16)(s32)(2.0f * (f32)(textY * 4)), textBuf, 4);
        g0 = dl++;
        g0->words.w0 = 0xDA380007; g0->words.w1 = (u32)&D_20000C0; // LAYOUT: same-line stores steer the ori/addiu schedule
        g0 = dl++;
        g0->words.w0 = 0xDA380005;
        g0->words.w1 = (u32)tracker->hudScale[gGfxBufferIndex];
        fontHeight = textGetFontHeight(1);
        textY = (s32)((f32)textY - (0.5f * (f32)fontHeight));
        hudFlags = managerData->hudFlags;
    }
    if (hudFlags & 2) {
        placeIdx = tracker->unk36;
        if ((placeIdx + 1) == managerData->unk1E) {
            placeIdx = 3;
        }
        if (tracker->unk45 != 0) {
            placeIdx = 4;
        }
        dl = textDrawStringVtx(dl, 1, (s16)(s32)((f32)(textX * 4) + (f32)(textX * 4)), (s16)(s32)(2.0f * (f32)(textY * 4)), textTableGetString(0x26, D_8002FCC0[placeIdx], 1), 4);
    }
    if (tracker->unk34 >= 3 && tracker->unk34 < 5) {
        dl = textDrawAnimated(dl, tracker->unk46, 2, 160.0f, 100.0f, 0.0f, 1.5f);
    }
    return dl;
}



Gfx *raceRenderHud(Gfx *dl, Actor *actor, RaceParticipant *tracker) {
    RaceParticipant *managerData;
    Actor *playerActor;
    PlayerState *playerState;

    managerData = tracker->actor->customState;
    if (tracker == NULL || func_807142D8() != 0) {
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
        WRITE_GFX(dl++, 0xE7000000, 0);
        WRITE_GFX(dl++, 0xD7000000, 0xFFFFFFFF);
        WRITE_GFX(dl++, 0xE200001C, 0x00504240);
        dl = gfxInit2DDisplayList(dl);
        WRITE_GFX(dl++, 0xFA000000, 0x3CA0);
        WRITE_GFX(dl++, 0xE3000A01, 0);
        WRITE_GFX(dl++, 0xFCFFFFFF, 0xFFFDF6FB);
        WRITE_GFX(dl++, 0xF6148170, 0x00048070);
        WRITE_GFX(dl++, 0xE7000000, 0);
        WRITE_GFX(dl++, 0xFA000000, 0x8000FF64);
        WRITE_GFX(dl++, 0xF6150070, 0x00040068);
        WRITE_GFX(dl++, 0xF6150178, 0x00040170);
        WRITE_GFX(dl++, 0xF6048170, 0x00040070);
        WRITE_GFX(dl++, 0xF6150170, 0x00148070);
        WRITE_GFX(dl++, 0xE7000000, 0);
        WRITE_GFX(dl++, 0xFA000000, 0xFFFFFFB4);
        WRITE_GFX(dl++, 0xFC119623, 0xFF2FFFFF);
        WRITE_GFX(dl++, 0xDA380003, (u32)&D_2000180);
        WRITE_GFX(dl++, 0xDA380007, (u32)&D_20000C0);
        WRITE_GFX(dl++, 0xD7000002, 0x80008000);
        dl = renderRotatedSprite(dl, managerData->minimapSprites[0], 3, 1, 0x40, 0x40, 0x88, 0x130, 2.0f, 2.0f, 0, 0.0f);
        dl = renderRotatedSprite(dl, managerData->minimapSprites[1], 3, 1, 0x40, 0x40, 0x108, 0x130, 2.0f, 2.0f, 0, 0.0f);
        dl = renderRotatedSprite(dl, managerData->minimapSprites[2], 3, 1, 0x40, 0x40, 0x88, 0xB0, 2.0f, 2.0f, 0, 0.0f);
        dl = renderRotatedSprite(dl, managerData->minimapSprites[3], 3, 1, 0x40, 0x40, 0x108, 0xB0, 2.0f, 2.0f, 0, 0.0f);
        for (i = 0; i < managerData->unk1E; i++) {
            participantActor = pairs[i].actor;
            if (participantActor == NULL) {
                continue;
            }
            participantData = pairs[i].data;
            if (participantData->unk27 == 0) {
                red = 0x80;
                blue = 0x80;
            } else if (participantData->unk27 == 1) {
                red = 0xFF;
                blue = 0;
            } else {
                continue;
            }
            dl = raceRenderMinimapIcon(dl, actor, participantActor->x, participantActor->z, red, 0, blue);
            targetActor = participantData->unk2C;
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
    managerData->unk24 = 2;
}


void raceInitGenericRaceManager(void) {
    RaceParticipant *managerData;

    actorSpawn(0x132, 0);
    managerData = gSpawnedActor->customState;
    raceInitParticipants(gSpawnedActor);
    managerData->hudFlags = 0xE;
    managerData->unk24 = 2;
}

void raceInitCompetitorRaceManager(void) {
    RaceParticipant *managerData;

    actorSpawn(0x132, 0);
    managerData = gSpawnedActor->customState;
    raceSpawnCompetitors(gSpawnedActor);
    managerData->hudFlags = 0xE;
    managerData->unk24 = 2;
}

void raceInitBeetleRaceManager(void) {
    RaceParticipant *managerData;

    actorSpawn(0x132, 0);
    managerData = gSpawnedActor->customState;
    raceInitBeetleRaceParticipants(gSpawnedActor);
    managerData->hudFlags = 2;
    managerData->unk24 = 1;
}

extern Actor *gCurrentActor;
extern s32 D_8002FCD4[];

void raceSetParticipantRaceStatus(RacePair *pair, u8 newStatus) {
    RaceParticipant *managerData;
    u32 slot;

    if (pair->data->unk34 != newStatus) {
        pair->data->unk34 = newStatus;
        pair->data->unk35 = 0;
        if (newStatus == 3) {
            managerData = gCurrentActor->customState;
            slot = pair->data->unk36;
            if (slot + 1 == managerData->unk1E || pair->data->unk45 != 0) {
                slot = 3;
            }
            if (pair->data->unk27 == 0) {
                pair->data->unk46 = gfxResourceCreate(1, textTableGetString(0x26, D_8002FCD4[slot], 1), 2, 160.0f, 100.0f, 0.0f);
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
    for (i = 0; i < managerData->unk1E; i++) {
        if (pairs[i].actor != NULL) {
            raceSetParticipantRaceStatus(&pairs[i], newStatus);
        }
    }
}

f32 raceGetHandicapSpeedBonus(RaceParticipant *participant) {
    f32 temp;

    if (participant->route >= 11 && participant->route < 15 && (D_807FD63A[participant->playerIdx].unk0 & 0x2000)) {
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
    ownerData->unk2C = NULL;
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
    for (i = 0; i < managerData->unk1E; i++) {
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
    i = managerData->unk1E - 1;
    if (i >= 0) {
        do {
            participantData = pairs[i].data;
            if (participantData->unk27 == 1) {
                if (participantData->unk36 != 0) {
                    sfxId = 0x56;
                } else {
                    sfxId = 0x57;
                }
            }
            i--;
        } while (sfxId == 0 && i >= 0);
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
    RacePair *base;
    RacePair *p;
    RacePair *q;
    s32 i;
    s32 j;
    RacePair tmp;
    u8 cnt;
    u8 swap;

    managerData = gCurrentActor->customState;
    cnt = 0;
    base = managerData->pairs;
    for (i = managerData->unk1E - 1; i >= 0; i--) {
        for (j = 1; j <= i; j++) {
            p = &base[j - 1];
            q = &base[j];
            swap = 0;
            if (p->data->unk45 != 0 && q->data->unk45 == 0) {
                swap = 1;
            } else {
                if (p->data->lap < q->data->lap) {
                    swap = 1;
                } else if (p->data->lap == q->data->lap) {
                    if (p->data->unk3A < q->data->unk3A) {
                        swap = 1;
                    } else if (p->data->unk3A == q->data->unk3A && q->data->unk40 < p->data->unk40) {
                        swap = 1;
                    }
                }
            }
            if (swap != 0) {
                tmp = *p;
                *p = *q;
                *q = tmp;
            }
        }
    }
    q = base;
    for (i = 0; i < managerData->unk1E; i++, q++) {
        q->data->unk36 = i;
        if (q->data->unk45 != 0 || (q->data->unk34 == 2 && managerData->unk24 < q->data->lap)) {
            raceSetParticipantRaceStatus(q, 3);
            cnt++;
        }
    }
    if (cnt >= managerData->unk1E - 1) {
        raceSetAllParticipantsStatus(3);
        racePlayResultSfx();
        managerData->unk1C = 0;
    }
}

void raceSetIntroCutscenePhase(Actor *actor) {
    RaceParticipant *managerData;

    if (actor != NULL && actor->state == 0) {
        managerData = actor->customState;
        managerData->unk1C = 2;
    }
}

void raceClearIntroCutscenePhase(Actor *actor) {
    RaceParticipant *managerData;

    if (actor != NULL && actor->state == 0) {
        managerData = actor->customState;
        managerData->unk1C = 0;
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
        managerData->unk1C = 0x1E;
    }
    switch (gCurrentActor->state) {
    case 0:
        if (managerData->unk1C) {
            managerData->unk1C--;
        } else {
            raceSetAllParticipantsStatus(1);
        }
        break;
    case 1:
        if (managerData->unk1C < 0x5B) {
            if (managerData->unk1C % 30 == 0) {
                sound = 0x75;
                if (managerData->unk1C == 0x5A) {
                    raceSetAllParticipantsStatus(2);
                    sound = 0x74;
                    racePlayStartRaceMusic();
                }
                sfxPlayOnFreeSlot(sound, 0x7FFF, 64.0f, 1.0, 0, 0x80);
            }
            managerData->unk1C++;
        }
        break;
    case 2:
        if (managerData->unk1C < 0x78) {
            managerData->unk1C++;
        }
        raceUpdateStandings();
        break;
    case 3:
        if (gCurrentMap == 0xE || gCurrentMap == 0x52) {
            raceSetAllParticipantsStatus(4);
            managerData->unk1C = 0x32;
        } else {
            managerData->unk1C++;
            if (managerData->unk1C >= 0x78) {
                if (managerData->unk25 == 1) {
                    raceSetAllParticipantsStatus(4);
                    managerData->unk1C = 0x32;
                } else {
                    raceSetAllParticipantsStatus(6);
                }
            }
        }
        break;
    case 4:
        if (managerData->unk1C) {
            managerData->unk1C--;
        } else {
            pairs = managerData->pairs;
            for (i = 0; i < managerData->unk1E; i++) {
                participantData = pairs[i].data;
                if (participantData->unk27 == 0) {
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
    if (func_807142D8() == 0) {
        if (gCurrentActor->state > 0 && gCurrentActor->state < 5) {
            renderCallbacksRegister((void *)raceRenderMinimapAndCountdown, gCurrentActor, 3);
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
    gCurrentActor->unk155 = 0;
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
        if (target->unk10 != 0) {
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
        if (target->curveMode == 3 || target->curveMode == 4 || target->unk10 != 0) {
            chased = target->participant;
            lim = chased->unk4;
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
        if (target->unk10 != 0) {
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
        participantData->unk27 = 1;
        raceRegisterParticipant(raceManager, 0, participantActor, participantData);
        slotIndex = 1;
        raceGetParticipantPair(raceManager, 0, &((RaceComponentActor *)participantActor)->target->actor, &((RaceComponentActor *)participantActor)->target->participant);
        managerData->unk25 = 1;
    } else {
        managerData->unk25 = 0;
    }
    for (playerIdx = 0; playerIdx < gPlayerCount; playerIdx++) {
        actorSpawn(0x13B, 0);
        participantActor = gSpawnedActor;
        participantData = participantActor->customState;
        participantData->unk27 = 0;
        raceRegisterParticipant(raceManager, slotIndex, participantActor, participantData);
        slotIndex++;
        participantData->playerIdx = playerIdx;
    }
    playerIdx = 0;
    if (participantCount > 0) {
        do {
            raceGetParticipantPair(raceManager, playerIdx, &participantActor, &participantData);
            participantData->unk36 = playerIdx;
            playerIdx++;
            participantData->actor = raceManager;
        } while (playerIdx != participantCount);
    }
    managerData->route = 0;
}


void racePlayerHudRenderCallback(Gfx *gfx, Actor *actor) {
    raceRenderHud(gfx, actor, actor->customState);
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
        gCurrentActor->unk155 = 0;
    }
    if ((raceData->unk34 == 2) && (gCurrentActor->state == 0)) {
        playerStateQueueCallback(0x57, NULL, raceData->playerIdx);
        gCurrentActor->state++;
    }
    gCurrentActor->x = playerActor->x;
    gCurrentActor->y = playerActor->y;
    gCurrentActor->z = playerActor->z;
    if (raceData->unk34 == 2) {
        raceUpdateLapAndWaypointTracker(raceData);
    }
    if ((raceData->unk34 > 0) && (raceData->unk34 < 5)) {
        renderCallbacksRegister((void *)racePlayerHudRenderCallback, gCurrentActor, 3);
    }
    raceData->unk1Cf = (raceData->unk40 < raceData->unk1Cf) ? raceData->unk1Cf : raceData->unk40;
    curMax = raceData->unk18;
    diff = (f32)(raceData->unk3A * 3000) - raceData->unk40;
    raceData->unk14 = diff;
    raceData->unk18 = (diff < curMax) ? curMax : raceData->unk14;
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

    if (other->unk45 != 0) {
        ret = 0;
    } else if (participant->unk36 != 0) {
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
