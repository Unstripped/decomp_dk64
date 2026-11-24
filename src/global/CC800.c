#include "common.h"
#include "actor.h"
#include "proto/global/10D2D0.h"
#include "proto/global/126260.h"
#include "proto/global/131B0.h"
#include "proto/global/135D30.h"
#include "proto/global/15050.h"
#include "proto/global/17B90.h"
#include "proto/global/19A00.h"
#include "proto/global/201B0.h"
#include "proto/global/5650.h"
#include "proto/global/69E60.h"
#include "proto/global/6AD90.h"
#include "proto/global/70FD0.h"
#include "proto/global/7130.h"
#include "proto/global/7CA80.h"
#include "proto/global/8D3E0.h"
#include "proto/global/936B0.h"
#include "proto/global/CC800.h"
#include "proto/global/CEAE0.h"
#include "proto/global/E4090.h"
#include "proto/global/F56F0.h"
#include "proto/global/F600.h"
#include "proto/global/FCCD0.h"


extern Actor *gCurrentActor;
extern Actor *gSpawnedActor;
extern Actor *gActivePlayerActor;
extern Actor *gPrimaryPlayerActor;
extern u8 gPlayerCount;
extern u8 gCurrentPlayerIndex;
extern PlayerState *gActivePlayerState;
extern s16 gCurrentCharacterIndex;

extern s16 gLevelCollectibleCounts[];

typedef struct ChainOffsets8 {
    /* 0x00 */ f32 offsetX[8];
} ChainOffsets8;

typedef struct ChainOffsets11 {
    /* 0x00 */ f32 offsetX[11];
} ChainOffsets11;

typedef struct ChainOffsets4 {
    /* 0x00 */ f32 offsetX[4];
} ChainOffsets4;

FillRectEntry gSplitScreenDividerRects[22] = {
    { 1, 0, 7, 0, 0, 0, 319, 9 }, { 1, 0, 7, 0, 0, 10, 9, 239 }, { 1, 0, 7, 0, 309, 10, 319, 239 },
    { 1, 0, 7, 0, 10, 229, 309, 239 }, { 2, 0, 7, 0, 0, 0, 319, 11 }, { 2, 0, 7, 0, 0, 12, 11, 239 },
    { 2, 0, 7, 0, 307, 12, 319, 239 }, { 2, 0, 7, 0, 12, 227, 307, 239 }, { 2, 0, 2, 0, 12, 119, 306, 121 },
    { 2, 0, 1, 0, 159, 12, 161, 226 }, { 2, 0, 4, 0, 159, 12, 306, 121 }, { 2, 0, 4, 0, 12, 119, 161, 226 },
    { 3, 0, 4, 0, 0, 119, 320, 121 }, { 3, 0, 4, 0, 159, 12, 161, 121 }, { 3, 0, 4, 0, 159, 119, 306, 226 },
    { 3, 0, 1, 0, 159, 119, 306, 121 }, { 3, 0, 1, 0, 159, 12, 161, 226 }, { 3, 0, 2, 0, 12, 119, 306, 121 },
    { 3, 0, 2, 0, 159, 119, 161, 226 }, { 4, 0, 7, 0, 12, 119, 306, 119 }, { 4, 0, 7, 0, 159, 12, 161, 226 },
    { -1, 0, 0, 0, 0, 0, 0, 0 },
};
G00Entry gViewportLayouts[30] = {
    { 1, 0, 7, 0, 10, 10, 309, 229 }, { 1, 1, 7, 0, 10, 10, 309, 229 }, { 2, 0, 2, 0, 12, 12, 307, 119 },
    { 2, 0, 2, 1, 12, 121, 307, 227 }, { 2, 0, 1, 0, 12, 12, 159, 227 }, { 2, 0, 1, 1, 161, 12, 307, 227 },
    { 2, 0, 4, 0, 12, 12, 159, 119 }, { 2, 0, 4, 1, 161, 121, 307, 227 }, { 2, 1, 7, 0, 12, 12, 307, 227 },
    { 2, 1, 7, 1, 12, 12, 307, 227 }, { 3, 0, 4, 0, 12, 12, 159, 119 }, { 3, 0, 4, 1, 161, 12, 307, 119 },
    { 3, 0, 4, 2, 12, 121, 159, 227 }, { 3, 0, 1, 0, 12, 12, 159, 227 }, { 3, 0, 1, 1, 161, 12, 307, 119 },
    { 3, 0, 1, 2, 161, 121, 307, 227 }, { 3, 0, 2, 0, 12, 12, 307, 119 }, { 3, 0, 2, 1, 12, 121, 159, 227 },
    { 3, 0, 2, 2, 161, 121, 307, 227 }, { 3, 1, 7, 0, 12, 12, 307, 227 }, { 3, 1, 7, 1, 12, 12, 307, 227 },
    { 3, 1, 7, 2, 12, 12, 307, 227 }, { 4, 0, 7, 0, 12, 12, 159, 119 }, { 4, 0, 7, 1, 161, 12, 307, 119 },
    { 4, 0, 7, 2, 12, 121, 159, 227 }, { 4, 0, 7, 3, 161, 121, 307, 227 }, { 4, 1, 7, 0, 12, 12, 307, 227 },
    { 4, 1, 7, 1, 12, 12, 307, 227 }, { 4, 1, 7, 2, 12, 12, 307, 227 }, { 4, 1, 7, 3, 12, 12, 307, 227 },
};
s32 gPlayTimeBaseSeconds = 0;
u8 gViewportCount = 1;
u8 gSplitScreenMode = 0;
u8 gSplitScreenViewMask = 2;
u8 gActivePlayerCount = 1;
u16 gMinigameCoinCount = 0;
u16 gTextNumberArg = 0;
u8 gPlayerStateSaved = 0;
u8 gMultiplayerReducedEffects = 0;
u8 gBossRoundNumber = 1;
ChainOffsets8 sChainOffsets8 = { {
    0.5890486f, -1.3744469f, -0.5890486f, -0.19634955f,
    0.0f, 0.3926991f, 0.7853982f, 0.98174775f,
} };
ChainOffsets11 sChainOffsets11 = { {
    0.36826447f, 0.53232545f, 0.46600294f, 0.17976892f,
    -0.65624374f, -0.40491644f, -0.62133723f, -0.6510078f,
    -0.8255408f, -0.37350044f, -0.31939524f,
} };
ChainOffsets4 sChainOffsets4 = { { 0.0f, 0.0f, 0.0f, 0.0f } };
s32 sRefillSlotIds[5] = { 2, 4, 5, 6, 7 };

void collectibleCountsClear(void) {
    s16 i;

    for (i = 0; i < 0xE; i++) {
        gLevelCollectibleCounts[i] = 0;
    }
}


s32 playerGetModelAssetId(void) {
    return gKongCharacterTable[gPlayerCharacterId[0]].actorType;
}

typedef struct LinkedActorState {
    /* 0x0 */ Actor *rider;
    /* 0x4 */ Actor *target;
    /* 0x8 */ u8 riderPlayer;
} LinkedActorState;


void playerSpawnMinecart(s32 actorType, u8 param, Actor *parent) {
    LinkedActorState *linked;

    actorSpawn(actorType, 0x82);
    actorCopyPoseAndScale(gSpawnedActor, parent, 0.15f);
    linked = gSpawnedActor->customState;
    linked->target = parent;
    linked->riderPlayer = param;
}

void playerMountBarrel(Actor *rider, Actor *target) {
    LinkedActorState *linked;

    actorSpawn(0x25, 0x8C);
    actorCopyPoseAndScale(gSpawnedActor, gActivePlayerActor, 0.15f);
    linked = gSpawnedActor->customState;
    linked->rider = rider;
    linked->target = target;
}

extern PlayerStruct *gPlayerSlots;

void playerSetupViewports(void) {
    gPlayerCount = gActivePlayerCount;
    gPlayerSlots = NULL;
    if (gPlayerCount >= 2) {
        switch (gSplitScreenMode) {
        case 0:
            gViewportCount = gPlayerCount;
            break;
        case 1:
            gViewportCount = 1;
            break;
        }
    } else {
        gViewportCount = 1;
        gSplitScreenMode = 0;
    }
}

G00Entry *cameraFindViewportEntry(u8 playerIndex) {
    u8 i;
    s32 found;

    i = 0;
    found = 0;
    do {
        if (gPlayerCount == gViewportLayouts[i].playerCount && gSplitScreenMode == gViewportLayouts[i].splitScreenMode && playerIndex == gViewportLayouts[i].playerIndex &&
            (gViewportLayouts[i].viewMask & gSplitScreenViewMask)) {
            found = 1;
        } else {
            i++;
        }
    } while (found == 0);
    return &gViewportLayouts[i];
}

extern OSContPad gControllerPads[];
extern u32 gViModeIndexByTvType[];
extern f32 gGfxFarClip;
extern u32 gGlobalCutsceneFlags;
extern u16 gSavedHeldActorType;

void playerAllocSlots(s32 spawnIndex) {
    PlayerStruct *blk;
    s32 i;
    u8 sel;
    G00Entry *e;

    gPlayerSlots = heapAlloc(gPlayerCount * sizeof(PlayerStruct));
    heapClearBlock(gPlayerSlots);
    for (i = 0; i < gPlayerCount; i++) {
        blk = &gPlayerSlots[i];
        blk->active = 1;
        sel = i;
        gCurrentPlayerIndex = i;
        playerSetupCharacterForSlot(spawnIndex++, sel);
        blk->actor = gActivePlayerActor;
        if (i == 0) {
            gPrimaryPlayerActor = gActivePlayerActor;
        }
        blk->camZ = 100.0f;
        blk->camY = 100.0f;
        blk->camX = 100.0f;
        blk->eyeZ = 100.0f;
        blk->eyeY = 100.0f;
        blk->eyeX = 100.0f;
        blk->focusZ = 0.0f;
        blk->focusY = 0.0f;
        blk->focusX = 0.0f;
        blk->upZ = 0.0f;
        blk->upX = 0.0f;
        blk->upY = 1.0f;
        e = cameraFindViewportEntry(sel);
        blk->rect[0] = e->left;
        blk->rect[1] = e->top;
        blk->rect[2] = e->right;
        blk->rect[3] = e->bottom;
        if (osViGetCurrentMode() == gViModeIndexByTvType[osTvType + osTvType + 1]) {
            blk->rect[0] *= 2;
            blk->rect[1] *= 2;
            blk->rect[2] += 1;
            blk->rect[2] *= 2;
            blk->rect[2] -= 1;
            blk->rect[3] += 1;
            blk->rect[3] *= 2;
            blk->rect[3] -= 1;
        }
        blk->rectWidth = blk->rect[2] - blk->rect[0];
        blk->rectHeight = blk->rect[3] - blk->rect[1];
        blk->fov = 45.0f;
        blk->nearClip = 10.0f;
        blk->aspect = (f32)blk->rectWidth / (f32)blk->rectHeight;
        blk->farClip = gGfxFarClip;
        blk->camChunk = 0;
        blk->contPad = &gControllerPads[i];
        blk->heldButtonsPtr = &gPadPressedButtons[i];
        blk->queuedState = -1;
        blk->sizeMode = 1;
        blk->sizeModeDirty = 1;
        blk->viewFadingOut = 0;
        blk->rumbleDisabled = 0;
        healthHudReset(&blk->healthHud);
        if (((gGlobalOverlayFlags & 1) && !(gGlobalCutsceneFlags & 2)) ||
            (gPlayerInventoryTable[i].health + gPlayerInventoryTable[i].healthDelta <= 0)) {
            healthRefill(sel);
        }
    }
    if (gSavedHeldActorType != 0) {
        playerRestoreHeldActor();
        gSavedHeldActorType = 0;
    }
    if (gPlayerCount >= 2) {
        actorSpawn(0x13E, 0);
    }
    gMultiplayerReducedEffects = (gSplitScreenMode == 0) && (gPlayerCount >= 2);
}



void playerRestoreHeldActor(void) {
    f32 pad0;
    f32 offsetX;
    f32 pad1;
    f32 distance;
    f32 offsetZ;

    if (gSavedHeldActorType == 0x55) {
        distance = 20.0f;
    } else {
        distance = 0.0f;
    }
    offsetX = mathSinF(gPrimaryPlayerActor->yaw) * distance;
    offsetZ = mathCosF(gPrimaryPlayerActor->yaw) * distance;
    actorListSpawnNodeEntryDefault(gSavedHeldActorType, gPrimaryPlayerActor->x + offsetX, gPrimaryPlayerActor->y + 7.0,
                                   gPrimaryPlayerActor->z + offsetZ, 0, 1.0f, gPrimaryPlayerActor);
    ((PlayerState *)gPrimaryPlayerActor->customState)->stateFlags |= 0x01000000;
}

void cameraSetViewportYRange(s16 top, s16 bottom) {
    PlayerStruct *p;

    p = gPlayerSlots;
    p->rectHeight = bottom - top;
    p->rect[1] = top;
    p->rect[3] = bottom;
    p->aspect = (f32)p->rectWidth / (f32)p->rectHeight;
}

void kongChainInit(s32 mode, KongChain *chains, u32 kind) {
    f32 pad;
    ChainOffsets8 tbl8 = sChainOffsets8;
    ChainOffsets11 tbl11 = sChainOffsets11;
    ChainOffsets4 tbl4 = sChainOffsets4;
    s32 count = 1; s32 n = 4; // FAKE: dead defaults (every case overwrites count/n, default returns) steer the pre-switch li v1,4 and frame order (Q0784)
    KongChain *chain = chains;
    f32 sign = 1.0f;
    f32 *offsets;
    s32 i;
    s32 j;
    KongChainNode *node;

    switch (kind) {
    case 3:
        count = 1;
        n = 11;
        offsets = tbl11.offsetX;
        break;
    case 5:
        count = 2;
        n = 8;
        offsets = tbl8.offsetX;
        break;
    case 2:
        count = 1;
        n = 4;
        offsets = tbl4.offsetX;
        break;
    default:
        return;
    }
    for (i = 0; i < count; i++) {
        node = chain->nodes;
        chain->holdTimer = 2;
        chain->kind = kind;
        chain->sway = 0.0f;
        chain->prevVelY = 0.0f;
        chain->prevY = 0.0f;
        chain->prevAngle = 0.0f;
        chain->weight = -128.0f;
        for (j = 0; j < n; j++, node++) {
            node->springX.angle = 0.0;
            node->springX.offset = offsets[j] * sign;
            node->springX.velocity = 0.0;
            node->springY.angle = node->springY.offset = node->springY.velocity = 0.0f;
        }
        chain++;
        sign = -sign;
    }
}


// Kong actor: second component pointer (0x178) is the KongChain array kongChainInit fills.
typedef struct KongActorView {
    /* 0x000 */ Actor base;
    /* 0x178 */ KongChain *chains;
} KongActorView;

#define KONG_ACTOR ((KongActorView *)gActivePlayerActor)

extern s32 gCurrentMap;
extern f32 gKongAccelY[];
extern f32 gKongTerminalSpeedY[];

void playerSetupCharacterForSlot(s32 spawnIndex, u8 playerIndex) {
    const KongCharacterEntry *row;
    u32 slot = playerIndex;
    s32 i;

    if (gPlayerCount >= 2) {
        gPlayerCharacterId[slot] = gPlayerCharacterId[controllerGetPort(slot)];
    }
    if (slot == 0 && gCurrentMap == 0x50) {
        gPlayerCharacterId[0] = 0;
    }
    row = &gKongCharacterTable[gPlayerCharacterId[slot]];
    actorSpawn(row->actorType, row->model);
    gSpawnedActor->flags &= ~0x1000;
    gSpawnedActor->flags |= row->actorFlags;
    gSpawnedActor->shadowScale[0] = 0x42;
    gSpawnedActor->shadowScale[1] = 0x42;
    gSpawnedActor->flags |= 0x01000000;
    if (gPlayerCount >= 2) {
        gSpawnedActor->renderFlags |= 0x200;
    }
    gSpawnedActor->flags2 |= 0xC0;
    gSpawnedActor->sub4->boneRotations = heapAlloc(0x100);
    gSpawnedActor->sub4->boneRotations->weight = 0;
    gSpawnedActor->sub4->boneScales = heapAlloc(0x200);
    gSpawnedActor->sub4->boneScales->bone = 0xFF;
    gSpawnedActor->sub4->boneOffsets = heapAlloc(0x200);
    gSpawnedActor->sub4->boneOffsets->bone = 0xFF;
    gActivePlayerActor = gSpawnedActor;
    gActivePlayerState = gActivePlayerActor->customState;
    gActivePlayerState->hitSourcePlayerIndex = -1;
    gActivePlayerState->playerIndex = slot;
    gActivePlayerState->animThresholdIndex = -1;
    gActivePlayerState->idleTimeoutFlag = 0;
    gActivePlayerState->lastFrame = -0x64;
    gCurrentCharacterIndex = row->characterIndex;
    gActivePlayerState->savedActorType = gSpawnedActor->actorType;
    playerInputToggleActiveState(gActivePlayerActor);
    actorSpawn(0xBC, 0);
    gActivePlayerState->camActor = gSpawnedActor;
    if (slot == 0) {
        gCamActor = gSpawnedActor;
    }
    gSpawnedActor->flags |= 0x100000;
    actorSetInteractionTimer(gActivePlayerActor);
    gActivePlayerState->traction = 0x64;
    gActivePlayerActor->accelY = gKongAccelY[gCurrentCharacterIndex];
    gActivePlayerActor->terminalSpeedY = gKongTerminalSpeedY[gCurrentCharacterIndex];
    gActivePlayerState->effectTimer = 0x78;
    gActivePlayerState->surfaceTimer = 0;
    gActivePlayerState->prevHasArcBounds = 0;
    gActivePlayerState->invulnTimer = 0;
    gActivePlayerState->respawnTimer = 0;
    gActivePlayerState->homingStrength = 0;
    gActivePlayerState->ledgeHangOffset = 0;
    gActivePlayerState->aimPitch = 0;
    gActivePlayerState->targetScale[0] = 0.15f;
    gActivePlayerState->targetScale[1] = 0.15f;
    gActivePlayerState->targetScale[2] = 0.15f;
    gActivePlayerState->currentScale[0] = 0.15f;
    gActivePlayerState->currentScale[1] = 0.15f;
    gActivePlayerState->currentScale[2] = 0.15f;
    gActivePlayerState->damageCooldown = 0;
    gActivePlayerState->fadeLevel = 0x1E;
    gActivePlayerState->chargeTimer = -1;
    gActivePlayerState->barrelCooldown = 0;
    gActivePlayerState->chargeTimer = -1; // ORIG: target stores -1 twice (sh at 0xd5c and 0xd6c)
    gActivePlayerState->pendingPickupEffect = -1;
    gActivePlayerState->squashScaleXZ = 1.0f;
    gActivePlayerState->squashScaleY = 1.0f;
    if (flagGet(0xCE, 0) != 0) {
        gActivePlayerState->stateFlags |= 0x100000;
    }
    kongChainInit(1, KONG_ACTOR->chains, gActivePlayerActor->actorType);
    gActivePlayerActor->segmentFlags = 0;
    playerKongStopAudioChannels(gActivePlayerActor, gActivePlayerActor->actorType);
    gActivePlayerActor->floorSlopePitch = 0x400;
    gActivePlayerState->queuedHeldActor = NULL;
    gActivePlayerState->heldActor = NULL;
    for (i = 0; i < 4; i++) {
        gPlayerPadState[slot].stickAngleHistory[i] = gPlayerPadState[slot].stickAngle;
        gPlayerPadState[slot].stickMagHistory[i] = gPlayerPadState[slot].stickMag;
    }
    playerResumeLocomotion(gActivePlayerActor);
    playerWarpToSpawnPoint(spawnIndex);
    playerSpawnMapHelpers();
}

extern s16 D_80753354[];
void func_80028840(void);

void playerSpawnMapHelpers(void) {
    f32 scale = -1.0f; // unset: the first case reached picks the factor, then falls through to apply it

    switch (gCurrentMap) {
    case 0x50:
        actorSpawn(0x146, 0);
        return;
    case 0xF:
        actorSpawn(0x14F, 0);
        return;
    case 0xB1:
    case 0xB4:
    case 0xB5:
    case 0xB6:
        actorSpawn(0x150, 0);
        return;
    case 0xB8:
    case 0xBF:
        actorSpawn(0x153, 0);
        return;
    case 0x27:
        if (scale < 0.0f) {
            scale = 0.8f;
        }
        /* fallthrough */
    case 0x5:
        if (scale < 0.0f) {
            scale = 1.8f;
        }
        /* fallthrough */
    case 0x1:
        if (scale < 0.0f) {
            scale = 1.6f;
        }
        gActivePlayerActor->sub4->scaleX = gActivePlayerActor->sub4->scaleX * scale;
        gActivePlayerActor->sub4->scaleY = gActivePlayerActor->sub4->scaleY * scale;
        gActivePlayerActor->sub4->scaleZ = gActivePlayerActor->sub4->scaleZ * scale;
        return;
    case 0x68:
    case 0x88:
    case 0x89:
        playerSetBaseGravity();
        actorScriptStart(gActivePlayerActor, 0);
        controllerAnimSetStateIfChanged(gActivePlayerActor, 0, 0.0f, 0.0f);
        gActivePlayerActor->state = 0x7D;
        gActivePlayerActor->subState = 0;
        gActivePlayerActor->flags &= ~0x8000;
        gActivePlayerActor->alpha = 0;
        actorSpawn(0x11A, 0x21);
        actorScriptStart(gSpawnedActor, 0x232);
        gSpawnedActor->parentActor = gActivePlayerActor;
        gActivePlayerState->actor = gSpawnedActor;
        return;
    case 0x6:
        playerSpawnMinecart(0x1D, 0, gActivePlayerActor);
        return;
    case 0x20:
    case 0x79:
    case 0x7A:
    case 0x7B:
        actorSpawn(0xDA, 0x94);
        gActivePlayerState->actor = gSpawnedActor;
        return;
    case 0x4C:
        commandSetFlags(0, 0);
        commandSetColor(0x6B, 0x30, 0x50);
        commandSetParameters(0x320, 0x82, 0, 0xFF, 0xFF, 0xFF);
        func_80028840();
        /* fallthrough */
    case 0x28:
    case 0x51:
        gActivePlayerActor->state = 0x77;
        gActivePlayerActor->subState = 0;
        return;
    case 0x4E:
    case 0x4F:
    case 0x83:
        playerKongDrawGun(gActivePlayerActor);
        gActivePlayerState->turnRate = D_80753354[gCurrentCharacterIndex];
        gActivePlayerActor->state = 0x62;
        gActivePlayerActor->subState = 0;
        actorScriptStartByIndex(gActivePlayerActor, 0x52);
        return;
    case 0xD3:
        gActivePlayerActor->state = 0x5F;
        gActivePlayerActor->subState = 0;
        actorScriptStartByIndex(gActivePlayerActor, 0x4B);
        return;
    case 0x53:
    case 0x99:
    case 0xC5:
    case 0xD0:
    case 0xD5:
        gActivePlayerActor->state = 0x77;
        gActivePlayerActor->subState = 0;
        return;
    case 0x6F:
        actorSpawnChildActor(gActivePlayerActor);
        return;
    }
}

void actorSetInteractionTimer(Actor *actor) {
    actor->collisionMode = 0x3C;
}


u8 playerLookupKongByActorType(s16 actorType) {
    s32 i;

    for (i = 0; i < 10; i++) {
        if (actorType == gKongCharacterTable[i].actorType) {
            return gKongCharacterTable[i].characterIndex;
        }
    }
    return 0;
}

s32 playerGetResolvedKongId(s32 playerIndex) {
    s32 kong;
    Actor *actor;
    PlayerState *ps;

    kong = gPlayerCharacterId[playerIndex];
    if (kong == 6 || kong == 7) {
        actor = gPlayerSlots[playerIndex].actor;
        ps = (&actor->customState)[playerIndex]; // ORIG: the target reads component pointer playerIndex of the slot actor (lw v1,372(t0) at 0x1334, t0 = actor + playerIndex * 4), not always the first
        kong = playerLookupKongByActorType(ps->savedActorType);
    }
    return kong;
}


void playerSetKongByActorType(s16 actorType) {
    s32 found;
    u8 i;

    found = 0;
    i = gPlayerCharacterId[gCurrentPlayerIndex] = 0;
    do {
        if (actorType == gKongCharacterTable[i].actorType) {
            found = 1;
        } else {
            gPlayerCharacterId[gCurrentPlayerIndex] = i + 1; i = gPlayerCharacterId[gCurrentPlayerIndex]; // LAYOUT: one source line; split, the sb of i + 1 schedules one slot earlier (Q0202)
        }
    } while (found == 0);
    playerApplyCharacterModel(&gKongCharacterTable[i]);
}


void playerCycleKongDebug(void) {
    gPlayerCharacterId[gCurrentPlayerIndex]++;
    gPlayerCharacterId[gCurrentPlayerIndex] %= 8;
    gActivePlayerState->gunDrawn = 0;
    playerApplyCharacterModel(&gKongCharacterTable[gPlayerCharacterId[gCurrentPlayerIndex]]);
    timerQueueAdd(playerDebugMaxKongAbilities, 0x14, gCurrentPlayerIndex, 0, 0);
}


void playerApplyCharacterModel(const KongCharacterEntry *row) {
    gActivePlayerActor->actorType = row->actorType;
    gCurrentCharacterIndex = row->characterIndex;
    controllerAnimFree(gActivePlayerActor);
    actorSub140Free(gActivePlayerActor->collision);
    controllerAnimInit(gActivePlayerActor, row->model);
    gActivePlayerActor->collision = actorSub140CreateFromModel(gActivePlayerActor);
    gActivePlayerActor->flags &= ~0x1000;
    gActivePlayerActor->flags |= row->actorFlags;
    gActivePlayerActor->sub4->boneRotations = heapAlloc(0x100);
    gActivePlayerActor->sub4->boneRotations->weight = 0;
    gActivePlayerActor->sub4->boneScales = heapAlloc(0x100);
    gActivePlayerActor->sub4->boneScales->bone = 0xFF;
    gActivePlayerActor->sub4->boneOffsets = heapAlloc(0x100);
    gActivePlayerActor->sub4->boneOffsets->bone = 0xFF;
    kongChainInit(1, KONG_ACTOR->chains, gActivePlayerActor->actorType);
    slotQueueInit(0);
}

extern s16 gSavedSlotSpawnFlags;
extern u8 gAmbientIndoors;

void playerWarpToSpawnPoint(s32 spawnIndex) {
    PlayerState *ps = gActivePlayerActor->customState;
    G01Pos *spawn = raceGridSpawnPoint(spawnIndex);

    gSavedSlotSpawnFlags = 0;
    gGlobalPauseFlags &= ~0x400;
    switch (spawn->spawnKind) {
    case 2:
        gActivePlayerActor->state = 0x4F;
        gActivePlayerActor->subState = 3;
        scriptSetActorRampTarget(gActivePlayerActor, 0.5f, 0.0f);
        ps->idleDelay = 1;
        gActivePlayerActor->contactFlags |= 4;
        actorUpdatePrevContactFlags(gActivePlayerActor);
        actorScriptStartByIndex(gActivePlayerActor, 0x34);
        /* fallthrough */
    case 0:
        gActivePlayerActor->waterY = -10000.0f;
        gActivePlayerActor->x = spawn->x;
        gActivePlayerActor->y = gActivePlayerActor->prevPeakY = spawn->y;
        gActivePlayerActor->z = spawn->z;
        gActivePlayerActor->yaw = (spawn->yaw / 255.0) * 4095.0;
        gActivePlayerActor->moveYaw = gActivePlayerActor->yaw;
        break;
    case 1:
        playerWaypointPathStartLineFromPoint(gActivePlayerActor, spawn, 0x32);
        break;
    }
    gActivePlayerActor->contactFlags &= ~0x200;
    ps->camActor->savedYaw = (spawn->camMode <= 0) ? 1 : spawn->camMode;
    if (spawn->flags & 1) {
        gAmbientIndoors = 1;
    }
}


void playerRespawnResetPhysics(s32 spawnIndex) {
    actorClearMovementFlags(gActivePlayerActor);
    playerSyncInventoryOnSpawn(spawnIndex);
    gActivePlayerActor->peakY = gActivePlayerActor->y;
}


void playerRevertAnimalTransformation(Actor *actor, PlayerState *ps) {
    s32 i;

    if (gPlayerSlots[ps->playerIndex].sizeMode != 1) {
        playerSetSizeMode(gActivePlayerActor, 1);
    }
    if (actor->sub4->scale[0] != ps->targetScale[0]) {
        for (i = 0; i < 3; i++) {
            ps->currentScale[i] = ps->targetScale[i];
            actor->sub4->scale[i] = ps->targetScale[i];
        }
    }
}


void playerRestoreKongState(Actor *actor, PlayerState *ps) {
    playerTransformAnimalEndSfx(actor);
    ps->stateFlags &= ~0x30;
    actor->flags |= 0x8000;
    actor->alpha = 0xFF;
}

void func_800268DC(Actor *, PlayerState *, PlayerInventory *); /* mpResetPlayerOnRespawn (multiplayer) */

void playerSyncInventoryOnSpawn(s32 spawnIndex) {
    PlayerState *ps = gActivePlayerActor->customState;
    s32 pad[1];
    KongChain *chains = KONG_ACTOR->chains;
    s32 pad2[1];
    PlayerInventory *inventory;
    u8 i;

    playerGetResolvedKongId(ps->playerIndex);
    inventory = &gPlayerInventoryTable[ps->playerIndex];
    ps->effectTimer = 0x78;
    for (i = 0; i < 2; i++) {
        sfxStopSlotSound(gActivePlayerActor, i);
    }
    playerWarpToSpawnPoint(spawnIndex);
    kongChainInit(0, chains, gActivePlayerActor->actorType);
    healthRefill(ps->playerIndex);
    gActivePlayerActor->speedXZ = 0.0f;
    ps->stateFlags &= ~0x080000A0;
    ps->statusEffectTimer = 0;
    ps->maxSpeed = 0.0f;
    if (gPlayerCount >= 2) {
        func_800268DC(gActivePlayerActor, ps, inventory); /* mpResetPlayerOnRespawn */
    }
    playerRevertAnimalTransformation(gActivePlayerActor, ps);
    if (camIsCutsceneActive() == 0) {
        if (gPlayerCount >= 2 && gSplitScreenMode == 1) {
            camResetAllPlayers();
        } else {
            camResetPlayer(gActivePlayerActor, ps->playerIndex);
        }
    }
    actorSetInteractionTimer(gActivePlayerActor);
    playerResumeLocomotion(gActivePlayerActor);
    gActivePlayerActor->roll = 0;
    gActivePlayerActor->pitch = 0;
}

extern G01Pos *gMapSpawnPoints;
extern u8 gMapSpawnPointCount;
extern G01Pos gMapDefaultSpawnPoint;
extern G01Pos gMapHeaderSpawnPos;

void playerLoadSpawnerAsset(s32 mapId) {
    gMapSpawnPoints = assetLoad(0x17, mapId, 1, 1);
    gMapSpawnPointCount = assetGetCachedSizeOrResolve(0x17, mapId) / 10U;
    playerCheckSpawnerFlagFixup(mapId);
    gMapDefaultSpawnPoint.yaw = 0;
    gMapDefaultSpawnPoint.x = gMapHeaderSpawnPos.x;
    gMapDefaultSpawnPoint.y = gMapHeaderSpawnPos.y;
    gMapDefaultSpawnPoint.z = gMapHeaderSpawnPos.z;
}


void playerCheckSpawnerFlagFixup(s32 mapId) {
    if (mapId == 0x1E) {
        if (flagGet(0xA0, 0) != 0) {
            gMapSpawnPoints[18].y = 0x65D;
            gMapSpawnPoints[23].y = 0x65D;
        } else {
            gMapSpawnPoints[18].y = 0x626;
            gMapSpawnPoints[23].y = 0x626;
        }
    }
}

extern f32 gSavedSlotSpawnX;
extern f32 gSavedSlotSpawnY;
extern f32 gSavedSlotSpawnZ;
extern s16 gSavedSlotSpawnYaw;
extern G01Pos gSavedSlotSpawnPoint;

G01Pos *raceGridSpawnPoint(s32 spawnIndex) {
    if (gSavedSlotSpawnFlags & 1) {
        gSavedSlotSpawnPoint.x = gSavedSlotSpawnX;
        gSavedSlotSpawnPoint.y = gSavedSlotSpawnY;
        gSavedSlotSpawnPoint.z = gSavedSlotSpawnZ;
        gSavedSlotSpawnPoint.yaw = (gSavedSlotSpawnYaw / 4095.0) * 360.0;
        return &gSavedSlotSpawnPoint;
    }
    if (gMapSpawnPointCount == 0) {
        return &gMapDefaultSpawnPoint;
    }
    if (spawnIndex >= gMapSpawnPointCount) {
        return gMapSpawnPoints;
    }
    return &gMapSpawnPoints[spawnIndex];
}

void func_800268C0(u8 flags); // multiplayer overlay mpSetFlags, called only while it is loaded

/* Reading `q->collisionFlags` at each test (no flags local) and keeping `q = pl->queuedActor` as a separate copy
 * variable leaves the `move v0,a0`. */
s8 playerResolveHitDamage(s8 delta, Actor *actor) {
    s8 result;
    PlayerState *ps;
    PlayerStruct *pl;
    Actor *q;

    result = delta;

    if (gPlayerCount >= 2) {
        ps = actor->customState;
        pl = &gPlayerSlots[ps->playerIndex];
        if (pl->queuedActor != NULL) {
            q = pl->queuedActor;
            if (q->collisionFlags & 1) {
                result = -1;
                if (gGlobalOverlayFlags & 0x04000000) {
                    func_800268C0(1);
                }
            } else if (q->collisionFlags & 4) {
                if (q->actorType == 0x29 || q->actorType == 0xAB) {
                    result = -3;
                    if (gGlobalOverlayFlags & 0x04000000) {
                        func_800268C0(2);
                    }
                } else {
                    result = -2;
                    if (gGlobalOverlayFlags & 0x04000000) {
                        func_800268C0(1);
                    }
                }
            } else if (gGlobalOverlayFlags & 0x04000000) {
                func_800268C0(1);
            }
        }
    }
    return result;
}


void func_80026E20(u8, s8);

s32 playerAddHealthDelta(u8 playerIndex, s8 delta) {
    PlayerStruct *pl;

    pl = &gPlayerSlots[playerIndex];
    pl->healthHudFlags |= 0x11;
    if (gPlayerCount >= 2 && delta < 0 && gMpSettings.matchPhase == 1) {
        func_80026E20(playerIndex, delta);
    }
    if (delta < 0) {
        rumbleRequest(playerIndex, 0xFF, 5);
    }
    if (!(gGlobalOverlayFlags & 0x800)) {
        gPlayerInventoryTable[playerIndex].healthDelta += delta;
    }
    if (gPlayerInventoryTable[playerIndex].healthDelta + gPlayerInventoryTable[playerIndex].health <= 0) {
        pl->healthHudFlags |= 0xC0;
        return 1;
    }
    return 0;
}

extern s32 gSavedPlayerStateFlags;

void playerResetSpawnGlobals(void) {
    PlayerInventory *p = gPlayerInventoryTable;
    s32 i;
    s32 j;

    for (i = 0; i < 4; i++) {
        bzero(p, sizeof(PlayerInventory));
        if (gActivePlayerCount >= 2) {
            if (gMpSettings.matchType == 1) {
                for (j = 0; j < 6; j++) {
                    p->kong[j].weaponFlags = 7;
                }
            }
            for (j = 0; j < 6; j++) {
                p->kong[j].slamLevel = 1;
            }
            p->melons = 1;
        } else {
            p->melons = 1;
        }
        healthRefill(i);
        p++;
    }
    collectibleCountsClear();
    gPlayerStateSaved = 0;
    gSavedPlayerStateFlags = 0;
}


void playerRefillConsumables(s32 playerIndex) {
    s32 i;

    for (i = 0; i < 5; i++) {
        slotQueueAddValue(sRefillSlotIds[i], playerIndex, 9999);
    }
    slotQueueInit(0);
}


void playerDebugMaxKongAbilities(s32 playerIndex, s32 unused1, s32 unused2) {
    s32 kong = playerGetResolvedKongId(playerIndex);
    KongInventory *kongInv = &gPlayerInventoryTable[playerIndex].kong[kong];

    kongInv->weaponFlags = 7;
    kongInv->instrumentFlags = 0xF;
    kongInv->slamLevel = 3;
    kongInv->moveLevel = 3;
    flagSet(0x179, 1, 0);
    playerRefillConsumables(playerIndex);
}

void playerCopyCameraToEye(u8 playerIndex) {
    PlayerStruct *p = &gPlayerSlots[playerIndex];

    p->eyeX = p->camX;
    p->eyeY = p->camY;
    p->eyeZ = p->camZ;
    p->eyeFocusX = p->focusX;
    p->eyeFocusY = p->focusY;
    p->eyeFocusZ = p->focusZ;
}

s32 playerKongHasWorldGoldenBanana(void) {
    KongInventory *row = &gPlayerInventoryTable[0].kong[gPlayerCharacterId[0]];
    s32 i;
    s32 v;

    v = 0;
    for (i = 0; i < 8 && !v; i++) {
        v = row->goldenBananas[i] > 0;
    }
    return v;
}

// Indexed by gPlayerCharacterId: { actorType, characterIndex, model, actorFlags }.
const KongCharacterEntry gKongCharacterTable[10] = {
    { 2, 0, 0x4, 0x1000 },
    { 3, 1, 0x1, 0x1000 },
    { 4, 2, 0x6, 0x1000 },
    { 5, 3, 0x9, 0x1000 },
    { 6, 4, 0xC, 0x1000 },
    { 7, 5, 0xDB, 0x1000 },
    { 8, 6, 0x14, 0x1000 },
    { 9, 0, 0x18, 0x1000 },
    { 2, 0, 0x1D, 0x0 },
    { 2, 0, 0x1D, 0x0 },
};
