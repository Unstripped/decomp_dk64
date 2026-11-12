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
extern u16 D_807FD63C;

extern s16 gLevelCollectibleCounts[];

void collectibleCountsClear(void) {
    s16 i;

    for (i = 0; i < 0xE; i++) {
        gLevelCollectibleCounts[i] = 0;
    }
}

extern u8 gPlayerCharacterId[];

typedef struct G00Row {
    /* 0x0 */ s32 unk0;
    /* 0x4 */ union {
        s32 unk4;
        struct {
            u8 pad[3];
            u8 characterId;
        } b;
    };
    /* 0x8 */ union {
        s32 unk8;
        struct {
            u8 pad[2];
            u16 modelId;
        } m;
    };
    /* 0xC */ s32 unkC;
} G00Row;
extern G00Row D_8075C410[];

s32 playerGetModelAssetId(void) {
    return D_8075C410[gPlayerCharacterId[0]].unk0;
}

typedef struct G00SpawnSub {
    /* 0x0 */ Actor *unk0;
    /* 0x4 */ Actor *unk4;
    /* 0x8 */ u8 unk8;
} G00SpawnSub;


void func_806C7B50(s32 actorType, u8 param, Actor *parent) {
    G00SpawnSub *sub;

    actorSpawn(actorType, 0x82);
    actorCopyPoseAndScale(gSpawnedActor, parent, 0.15f);
    sub = gSpawnedActor->customState;
    sub->unk4 = parent;
    sub->unk8 = param;
}

void playerMountBarrel(Actor *rider, Actor *target) {
    G00SpawnSub *sub;

    actorSpawn(0x25, 0x8C);
    actorCopyPoseAndScale(gSpawnedActor, gActivePlayerActor, 0.15f);
    sub = gSpawnedActor->customState;
    sub->unk0 = rider;
    sub->unk4 = target;
}

extern u8 gViewportCount;
extern u8 gSplitScreenMode;
extern u8 gActivePlayerCount;

extern PlayerStruct *gPlayerSlots;

void playerSetupViewports(void) {
    gPlayerCount = gActivePlayerCount;
    gPlayerSlots = 0;
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

extern G00Entry D_80750948[];
extern u8 D_80750ABC;

G00Entry *cameraFindViewportEntry(u8 playerIndex) {
    u8 i;
    s32 found;

    i = 0;
    found = 0;
    do {
        if (gPlayerCount == D_80750948[i].unk0 && gSplitScreenMode == D_80750948[i].unk1 && playerIndex == D_80750948[i].unk3 &&
            (D_80750948[i].unk2 & D_80750ABC)) {
            found = 1;
        } else {
            i++;
        }
    } while (found == 0);
    return &D_80750948[i];
}

extern PlayerInventory gPlayerInventoryTable[];
extern OSContPad D_807ECD10[];
extern u16 D_807ECD48[];
extern u32 D_8074458C[];
extern f32 gGfxFarClip;
extern u8 D_80750AD0;
extern s32 gGlobalOverlayFlags;
extern u32 gGlobalCutsceneFlags;
extern u16 D_807FD570;

void playerAllocSlots(s32 spawnIndex) {
    PlayerStruct *blk;
    s32 i;
    u8 sel;
    G00Entry *e;

    gPlayerSlots = heapAlloc(gPlayerCount * sizeof(PlayerStruct));
    heapClearBlock(gPlayerSlots);
    for (i = 0; i < gPlayerCount; i++) {
        blk = &gPlayerSlots[i];
        blk->unk0 = 1;
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
        blk->unk224 = 100.0f;
        blk->unk220 = 100.0f;
        blk->unk21C = 100.0f;
        blk->focusZ = 0.0f;
        blk->focusY = 0.0f;
        blk->focusX = 0.0f;
        blk->upZ = 0.0f;
        blk->upX = 0.0f;
        blk->upY = 1.0f;
        e = cameraFindViewportEntry(sel);
        blk->rect[0] = e->unk4;
        blk->rect[1] = e->unk6;
        blk->rect[2] = e->unk8;
        blk->rect[3] = e->unkA;
        if (osViGetCurrentMode() == D_8074458C[osTvType + osTvType]) {
            blk->rect[0] *= 2;
            blk->rect[1] *= 2;
            blk->rect[2] += 1;
            blk->rect[2] *= 2;
            blk->rect[2] -= 1;
            blk->rect[3] += 1;
            blk->rect[3] *= 2;
            blk->rect[3] -= 1;
        }
        blk->unk278 = blk->rect[2] - blk->rect[0];
        blk->unk27A = blk->rect[3] - blk->rect[1];
        blk->fov = 45.0f;
        blk->unk284 = 10.0f;
        blk->unk280 = (f32)blk->unk278 / (f32)blk->unk27A;
        blk->farClip = gGfxFarClip;
        blk->unk290 = 0;
        blk->contPad = &D_807ECD10[i];
        blk->heldButtonsPtr = &D_807ECD48[i];
        blk->queuedState = -1;
        blk->unk2C0 = 1;
        blk->sizeModeDirty = 1;
        blk->unk2EA = 0;
        blk->unk2EB = 0;
        hudDrawItemWithAlpha(&blk->healthHud);
        if (((gGlobalOverlayFlags & 1) && !(gGlobalCutsceneFlags & 2)) ||
            (gPlayerInventoryTable[i].health + gPlayerInventoryTable[i].healthDelta <= 0)) {
            healthRefill(sel);
        }
    }
    if (D_807FD570 != 0) {
        func_806C80E4();
        D_807FD570 = 0;
    }
    if (gPlayerCount >= 2) {
        actorSpawn(0x13E, 0);
    }
    D_80750AD0 = (gSplitScreenMode == 0) && (gPlayerCount >= 2);
}



void func_806C80E4(void) {
    f32 pad0;
    f32 offsetX;
    f32 pad1;
    f32 distance;
    f32 offsetZ;

    if (D_807FD570 == 0x55) {
        distance = 20.0f;
    } else {
        distance = 0.0f;
    }
    offsetX = mathSinF(gPrimaryPlayerActor->yaw) * distance;
    offsetZ = mathCosF(gPrimaryPlayerActor->yaw) * distance;
    actorListSpawnNodeEntryDefault(D_807FD570, gPrimaryPlayerActor->x + offsetX, gPrimaryPlayerActor->y + 7.0,
                                   gPrimaryPlayerActor->z + offsetZ, 0, 1.0f, gPrimaryPlayerActor);
    ((PlayerState *)gPrimaryPlayerActor->customState)->stateFlags |= 0x01000000;
}

void cameraSetViewportYRange(s16 top, s16 bottom) {
    PlayerStruct *p;

    p = gPlayerSlots;
    p->unk27A = bottom - top;
    p->rect[1] = top;
    p->rect[3] = bottom;
    p->unk280 = (f32)p->unk278 / (f32)p->unk27A;
}

typedef struct G00Tbl8 {
    /* 0x00 */ f32 f[8];
} G00Tbl8;

typedef struct G00Tbl11 {
    /* 0x00 */ f32 f[11];
} G00Tbl11;

typedef struct G00Tbl4 {
    /* 0x00 */ f32 f[4];
} G00Tbl4;

typedef struct G00Vtx {
    /* 0x00 */ f32 unk0;
    /* 0x04 */ f32 unk4;
    /* 0x08 */ f32 unk8;
    /* 0x0C */ f32 unkC;
    /* 0x10 */ f32 unk10;
    /* 0x14 */ f32 unk14;
} G00Vtx;

typedef struct G00Out {
    /* 0x000 */ f32 unk0;
    /* 0x004 */ f32 unk4;
    /* 0x008 */ f32 unk8;
    /* 0x00C */ f32 unkC;
    /* 0x010 */ f32 unk10;
    /* 0x014 */ u8 unk14;
    /* 0x015 */ u8 pad15[3];
    /* 0x018 */ s32 unk18;
    /* 0x01C */ G00Vtx unk1C[12];
} G00Out; // size = 0x13C

extern G00Tbl8 D_80750AD8;
extern G00Tbl11 D_80750AF8;
extern G00Tbl4 D_80750B24;

void func_806C8220(s32 mode, void *buffer, u32 kind) {
    f32 pad;
    G00Tbl8 tbl8;
    G00Tbl11 tbl11;
    G00Tbl4 tbl4;
    f32 *tbl;
    f32 sign;
    s32 count;
    s32 n;
    s32 i;
    s32 j;
    G00Vtx *v;
    s32 pad2[2];
    G00Out *out;

    tbl8 = D_80750AD8;
    count = 1; // FAKE: dead store (every case sets count/n), keeps the frame/stack order
    n = 4; // FAKE: dead store (every case sets n), keeps n in v1 and the buffer copy in a0 (pre-existing, now tagged)
    tbl11 = D_80750AF8;
    out = buffer;
    tbl4 = D_80750B24;
    sign = 1.0f;
    switch (kind) {
    case 3:
        count = 1;
        n = 11;
        tbl = tbl11.f;
        break;
    case 5:
        count = 2;
        n = 8;
        tbl = tbl8.f;
        break;
    case 2:
        count = 1;
        n = 4;
        tbl = tbl4.f;
        break;
    default:
        return;
    }
    for (i = 0; i < count; i++) {
        v = out->unk1C;
        out->unk14 = 2;
        out->unk18 = kind;
        out->unkC = 0.0f;
        out->unk8 = 0.0f;
        out->unk4 = 0.0f;
        out->unk0 = 0.0f;
        out->unk10 = -128.0f;
        for (j = 0; j < n; j++, v++) {
            v->unk4 = 0.0;
            v->unk0 = tbl[j] * sign;
            v->unk8 = 0.0;
            // LAYOUT: one source line; splitting it reorders the three stores
            v->unk14 = 0.0f; v->unkC = 0.0f; v->unk10 = 0.0f;
        }
        out++;
        sign = -sign;
    }
}


// Kong actor: second component pointer (0x178) is the G00Out block func_806C8220 fills.
typedef struct KongActorView {
    /* 0x000 */ Actor base;
    /* 0x178 */ G00Out *unk178;
} KongActorView;

typedef struct G00Slot34 {
    /* 0x00 */ u8 pad0[4];
    /* 0x04 */ f32 unk4;
    /* 0x08 */ u8 pad8[8];
    /* 0x10 */ f32 unk10[4];
    /* 0x20 */ s16 unk20[4];
    /* 0x28 */ s16 unk28;
    /* 0x2A */ u8 pad2A[0xA];
} G00Slot34;

#define KONG_ACTOR ((KongActorView *)gActivePlayerActor)

extern s32 gCurrentMap;
extern Actor *gCamActor;
extern f32 D_80753578[];
extern f32 D_807535E8[];
extern G00Slot34 gPlayerPadState[];

void playerSetupCharacterForSlot(s32 spawnIndex, u8 playerIndex) {
    G00Row *row;
    u32 sel;
    s32 i;

    sel = playerIndex;
    if (gPlayerCount >= 2) {
        gPlayerCharacterId[sel] = gPlayerCharacterId[controllerGetPort(sel)];
    }
    if (sel == 0 && gCurrentMap == 0x50) {
        gPlayerCharacterId[0] = 0;
    }
    row = &D_8075C410[gPlayerCharacterId[sel]];
    actorSpawn(row->unk0, row->unk8);
    gSpawnedActor->flags &= ~0x1000;
    gSpawnedActor->flags |= row->unkC;
    gSpawnedActor->unk16E[0] = 0x42;
    gSpawnedActor->unk16E[1] = 0x42;
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
    gActivePlayerState->playerIndex = sel;
    gActivePlayerState->unk11E = -1;
    gActivePlayerState->idleTimeoutFlag = 0;
    gActivePlayerState->lastFrame = -0x64;
    gCurrentCharacterIndex = row->unk4;
    gActivePlayerState->savedActorType = gSpawnedActor->actorType;
    playerInputToggleActiveState(gActivePlayerActor);
    actorSpawn(0xBC, 0);
    gActivePlayerState->camActor = gSpawnedActor;
    if (sel == 0) {
        gCamActor = gSpawnedActor;
    }
    gSpawnedActor->flags |= 0x100000;
    actorSetInteractionTimer(gActivePlayerActor);
    gActivePlayerState->unk26 = 0x64;
    gActivePlayerActor->accelY = D_80753578[gCurrentCharacterIndex];
    gActivePlayerActor->terminalSpeedY = D_807535E8[gCurrentCharacterIndex];
    gActivePlayerState->effectTimer = 0x78;
    gActivePlayerState->surfaceTimer = 0;
    gActivePlayerState->prevHasArcBounds = 0;
    gActivePlayerState->invulnTimer = 0;
    gActivePlayerState->respawnTimer = 0;
    gActivePlayerState->homingStrength = 0;
    gActivePlayerState->unk10C = 0;
    gActivePlayerState->unk1A0 = 0;
    gActivePlayerState->targetScale[0] = 0.15f;
    gActivePlayerState->targetScale[1] = 0.15f;
    gActivePlayerState->targetScale[2] = 0.15f;
    gActivePlayerState->currentScale[0] = 0.15f;
    gActivePlayerState->currentScale[1] = 0.15f;
    gActivePlayerState->currentScale[2] = 0.15f;
    gActivePlayerState->damageCooldown = 0;
    gActivePlayerState->unk21E = 0x1E;
    gActivePlayerState->unkC8 = -1;
    gActivePlayerState->unkCA = 0;
    gActivePlayerState->unkC8 = -1;
    gActivePlayerState->unk264 = -1;
    gActivePlayerState->unk258 = 1.0f;
    gActivePlayerState->unk25C = 1.0f;
    if (flagGet(0xCE, 0) != 0) {
        gActivePlayerState->stateFlags |= 0x100000;
    }
    func_806C8220(1, KONG_ACTOR->unk178, gActivePlayerActor->actorType);
    gActivePlayerActor->unk146 = 0;
    playerKongStopAudioChannels(gActivePlayerActor, gActivePlayerActor->actorType);
    gActivePlayerActor->floorSlopePitch = 0x400;
    gActivePlayerState->queuedHeldActor = 0;
    gActivePlayerState->heldActor = 0;
    for (i = 0; i < 4; i++) {
        gPlayerPadState[sel].unk20[i] = gPlayerPadState[sel].unk28;
        gPlayerPadState[sel].unk10[i] = gPlayerPadState[sel].unk4;
    }
    playerResumeLocomotion(gActivePlayerActor);
    playerWarpToSpawnPoint(spawnIndex);
    playerSpawnMapHelpers();
}

extern s32 gCurrentMap;
extern s16 D_80753354[];
void func_80028840(void);

void playerSpawnMapHelpers(void) {
    f32 scale;

    scale = -1.0f;
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
    case 0x5:
        if (scale < 0.0f) {
            scale = 1.8f;
        }
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
        gActivePlayerActor->unk155 = 0;
        gActivePlayerActor->flags &= 0xFFFF7FFF;
        gActivePlayerActor->alpha = 0;
        actorSpawn(0x11A, 0x21);
        actorScriptStart(gSpawnedActor, 0x232);
        gSpawnedActor->parentActor = gActivePlayerActor;
        gActivePlayerState->actor = gSpawnedActor;
        return;
    case 0x6:
        func_806C7B50(0x1D, 0, gActivePlayerActor);
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
    case 0x28:
    case 0x51:
        gActivePlayerActor->state = 0x77;
        gActivePlayerActor->unk155 = 0;
        return;
    case 0x4E:
    case 0x4F:
    case 0x83:
        playerKongPlaySoundByState(gActivePlayerActor);
        gActivePlayerState->turnRate = D_80753354[gCurrentCharacterIndex];
        gActivePlayerActor->state = 0x62;
        gActivePlayerActor->unk155 = 0;
        actorScriptStartByIndex(gActivePlayerActor, 0x52);
        return;
    case 0xD3:
        gActivePlayerActor->state = 0x5F;
        gActivePlayerActor->unk155 = 0;
        actorScriptStartByIndex(gActivePlayerActor, 0x4B);
        return;
    case 0x53:
    case 0x99:
    case 0xC5:
    case 0xD0:
    case 0xD5:
        gActivePlayerActor->state = 0x77;
        gActivePlayerActor->unk155 = 0;
        return;
    case 0x6F:
        actorSpawnChildActor(gActivePlayerActor);
        return;
    }
}

void actorSetInteractionTimer(Actor *actor) {
    actor->unk144 = 0x3C;
}


u8 playerLookupKongByActorType(s16 actorType) {
    s32 i;

    for (i = 0; i < 10; i++) {
        if (actorType == D_8075C410[i].unk0) {
            return D_8075C410[i].b.characterId;
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
        ps = (&actor->customState)[playerIndex]; // component pointer arg0 (0x174 + arg0 * 4), as the original indexes it
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
        if (actorType == D_8075C410[i].unk0) {
            found = 1;
        } else {
            gPlayerCharacterId[gCurrentPlayerIndex] = i + 1; i = gPlayerCharacterId[gCurrentPlayerIndex];
        }
    } while (found == 0);
    playerApplyCharacterModel(&D_8075C410[i]);
}


void playerCycleKongDebug(void) {
    gPlayerCharacterId[gCurrentPlayerIndex]++;
    gPlayerCharacterId[gCurrentPlayerIndex] %= 8;
    gActivePlayerState->gunDrawn = 0;
    playerApplyCharacterModel(&D_8075C410[gPlayerCharacterId[gCurrentPlayerIndex]]);
    timerQueueAdd(playerInitKongActor, 0x14, gCurrentPlayerIndex, 0, 0);
}


void playerApplyCharacterModel(void *arg) {
    G00Row *row = arg;

    gActivePlayerActor->actorType = row->unk0;
    gCurrentCharacterIndex = row->unk4;
    controllerAnimFree(gActivePlayerActor);
    actorSub140Free(gActivePlayerActor->collision);
    controllerAnimInit(gActivePlayerActor, row->m.modelId);
    gActivePlayerActor->collision = actorSub140CreateFromModel(gActivePlayerActor);
    gActivePlayerActor->flags &= ~0x1000;
    gActivePlayerActor->flags |= row->unkC;
    gActivePlayerActor->sub4->boneRotations = heapAlloc(0x100);
    gActivePlayerActor->sub4->boneRotations->weight = 0;
    gActivePlayerActor->sub4->boneScales = heapAlloc(0x100);
    gActivePlayerActor->sub4->boneScales->bone = 0xFF;
    gActivePlayerActor->sub4->boneOffsets = heapAlloc(0x100);
    gActivePlayerActor->sub4->boneOffsets->bone = 0xFF;
    func_806C8220(1, KONG_ACTOR->unk178, gActivePlayerActor->actorType);
    slotQueueInit(0);
}

extern s16 D_8076AEE2;
extern s8 D_80770DC9;

void playerWarpToSpawnPoint(s32 spawnIndex) {
    PlayerState *ps = gActivePlayerActor->customState;
    G01Pos *spawn = func_806C96C4(spawnIndex);

    D_8076AEE2 = 0;
    gGlobalPauseFlags &= ~0x400;
    switch (spawn->unk8) {
    case 2:
        gActivePlayerActor->state = 0x4F;
        gActivePlayerActor->unk155 = 3;
        scriptSetActorRampTarget(gActivePlayerActor, 0.5f, 0.0f);
        ps->unk50 = 1;
        gActivePlayerActor->contactFlags |= 4;
        actorUpdatePrevContactFlags(gActivePlayerActor);
        actorScriptStartByIndex(gActivePlayerActor, 0x34);
        /* fallthrough */
    case 0:
        gActivePlayerActor->waterY = -10000.0f;
        gActivePlayerActor->x = spawn->unk0;
        gActivePlayerActor->y = gActivePlayerActor->prevPeakY = spawn->unk2;
        gActivePlayerActor->z = spawn->unk4;
        gActivePlayerActor->yaw = (spawn->unk6 / 255.0) * 4095.0;
        gActivePlayerActor->moveYaw = gActivePlayerActor->yaw;
        break;
    case 1:
        playerWaypointPathStartLineFromPoint(gActivePlayerActor, spawn, 0x32);
        break;
    }
    gActivePlayerActor->contactFlags &= ~0x200;
    ps->camActor->unk15F = (spawn->unk7 <= 0) ? 1 : spawn->unk7;
    if (spawn->unk9 & 1) {
        D_80770DC9 = 1;
    }
}


void playerRespawnResetPhysics(s32 spawnIndex) {
    actorClearMovementFlags(gActivePlayerActor);
    playerSyncInventoryOnSpawn(spawnIndex);
    gActivePlayerActor->peakY = gActivePlayerActor->y;
}

typedef struct G01Sub4f {
    /* 0x00 */ u8 pad0[0x34];
    /* 0x34 */ f32 unk34[3];
} G01Sub4f;


void playerRevertAnimalTransformation(Actor *actor, PlayerState *ps) {
    s32 i;

    if (gPlayerSlots[ps->playerIndex].unk2C0 != 1) {
        playerSetSizeMode(gActivePlayerActor, 1);
    }
    if (((G01Sub4f *)actor->sub4)->unk34[0] != ps->targetScale[0]) {
        for (i = 0; i < 3; i++) {
            ps->currentScale[i] = ps->targetScale[i];
            ((G01Sub4f *)actor->sub4)->unk34[i] = ps->targetScale[i];
        }
    }
}


void playerRestoreKongState(Actor *actor, PlayerState *ps) {
    playerTransformAnimalEndSfx(actor);
    ps->stateFlags &= ~0x30;
    actor->flags |= 0x8000;
    actor->alpha = 0xFF;
}

void func_800268DC(Actor *, void *, void *); /* mpResetPlayerOnRespawn (multiplayer) */

void playerSyncInventoryOnSpawn(s32 spawnIndex) {
    PlayerState *ps = gActivePlayerActor->customState;
    s32 pad[1];
    void *vtxBuffer = KONG_ACTOR->unk178;
    s32 pad2[1];
    PlayerInventory *inventory;
    u8 i;

    playerGetResolvedKongId(ps->playerIndex);
    inventory = &gPlayerInventoryTable[ps->playerIndex];
    ps->effectTimer = 0x78;
    i = 0;
    do {
        sfxStopSlotSound(gActivePlayerActor, i);
        i++;
    } while (i < 2);
    playerWarpToSpawnPoint(spawnIndex);
    func_806C8220(0, vtxBuffer, gActivePlayerActor->actorType);
    healthRefill(ps->playerIndex);
    gActivePlayerActor->speedXZ = 0.0f;
    ps->stateFlags &= 0xF7FFFF5F;
    ps->unk200 = 0;
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

extern G01Pos *D_807FC900;
extern u8 D_807FC904;
extern G01Pos D_807FC908;
extern G01Pos D_807FD574;

void playerLoadSpawnerAsset(s32 mapId) {
    D_807FC900 = assetLoad(0x17, mapId, 1, 1);
    D_807FC904 = assetGetCachedSizeOrResolve(0x17, mapId) / 10U;
    playerCheckSpawnerFlagFixup(mapId);
    D_807FC908.unk6 = 0;
    D_807FC908.unk0 = D_807FD574.unk0;
    D_807FC908.unk2 = D_807FD574.unk2;
    D_807FC908.unk4 = D_807FD574.unk4;
}


void playerCheckSpawnerFlagFixup(s32 mapId) {
    if (mapId == 0x1E) {
        if (flagGet(0xA0, 0) != 0) {
            D_807FC900[18].unk2 = 0x65D;
            D_807FC900[23].unk2 = 0x65D;
        } else {
            D_807FC900[18].unk2 = 0x626;
            D_807FC900[23].unk2 = 0x626;
        }
    }
}

extern f32 D_8076AEE4;
extern f32 D_8076AEE8;
extern f32 D_8076AEEC;
extern s16 D_8076AEF0;
extern G01Pos D_807FC918;

G01Pos *func_806C96C4(s32 spawnIndex) {
    if (D_8076AEE2 & 1) {
        D_807FC918.unk0 = D_8076AEE4;
        D_807FC918.unk2 = D_8076AEE8;
        D_807FC918.unk4 = D_8076AEEC;
        D_807FC918.unk6 = (D_8076AEF0 / 4095.0) * 360.0;
        return &D_807FC918;
    }
    if (D_807FC904 == 0) {
        return &D_807FC908;
    }
    if (spawnIndex >= D_807FC904) {
        return D_807FC900;
    }
    return &D_807FC900[spawnIndex];
}

void func_800268C0();

/* Reading `q->collisionFlags` at each test (no flags local) and keeping `q = pl->queuedActor` as a separate copy
 * variable leaves the `move v0,a0`. */
s8 func_806C9830(s8 delta, Actor *actor) {
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
                    func_800268C0(1, actor);
                }
            } else if (q->collisionFlags & 4) {
                if (q->actorType == 0x29 || q->actorType == 0xAB) {
                    result = -3;
                    if (gGlobalOverlayFlags & 0x04000000) {
                        func_800268C0(2, actor);
                    }
                } else {
                    result = -2;
                    if (gGlobalOverlayFlags & 0x04000000) {
                        func_800268C0(1, actor);
                    }
                }
            } else if (gGlobalOverlayFlags & 0x04000000) {
                func_800268C0(1, actor);
            }
        }
    }
    return result;
}


extern s32 D_807552EC;
void func_80026E20(u8, s8);

s32 func_806C9974(u8 playerIndex, s8 delta) {
    PlayerStruct *pl;

    pl = &gPlayerSlots[playerIndex];
    pl->unk2E2 |= 0x11;
    if (gPlayerCount >= 2 && delta < 0 && D_807552EC == 1) {
        func_80026E20(playerIndex, delta);
    }
    if (delta < 0) {
        rumbleRequest(playerIndex, 0xFF, 5);
    }
    if (!(gGlobalOverlayFlags & 0x800)) {
        gPlayerInventoryTable[playerIndex].healthDelta += delta;
    }
    if (gPlayerInventoryTable[playerIndex].healthDelta + gPlayerInventoryTable[playerIndex].health <= 0) {
        pl->unk2E2 |= 0xC0;
        return 1;
    }
    return 0;
}

extern s32 D_807552E4;
extern s8 D_80750ACC;
extern s32 D_807FD56C;

void playerResetSpawnGlobals(void) {
    PlayerInventory *p = gPlayerInventoryTable;
    s32 i;
    s32 j;

    for (i = 0; i < 4; i++) {
        bzero(p, sizeof(PlayerInventory));
        if (gActivePlayerCount >= 2) {
            if (D_807552E4 == 1) {
                for (j = 0; j < 6; j++) {
                    p->kong[j].unk0[2] = 7;
                }
            }
            for (j = 0; j < 6; j++) {
                p->kong[j].unk0[1] = 1;
            }
            p->melons = 1;
        } else {
            p->melons = 1;
        }
        healthRefill(i);
        p++;
    }
    collectibleCountsClear();
    D_80750ACC = 0;
    D_807FD56C = 0;
}


extern s32 D_80750B34[];

void playerSpawnMapActors(s32 mapId) {
    s32 i;

    for (i = 0; i < 5; i++) {
        slotQueueAddValue(D_80750B34[i], mapId, 0x270F);
    }
    slotQueueInit(0);
}


void playerInitKongActor(s32 playerIndex, s32 unused1, s32 unused2) {
    s32 kong = playerGetResolvedKongId(playerIndex);
    KongInventory *p = &gPlayerInventoryTable[playerIndex].kong[kong];

    p->unk0[2] = 7;
    p->unk0[4] = 0xF;
    p->unk0[1] = 3;
    p->unk0[0] = 3;
    flagSet(0x179, 1, 0);
    playerSpawnMapActors(playerIndex);
}

void playerGetCharacterIndex(u8 playerIndex) {
    PlayerStruct *p = &gPlayerSlots[playerIndex];

    p->unk21C = p->camX;
    p->unk220 = p->camY;
    p->unk224 = p->camZ;
    p->unk234 = p->focusX;
    p->unk238 = p->focusY;
    p->unk23C = p->focusZ;
}

s32 playerSpawnAllPlayers(void) {
    KongInventory *row = &gPlayerInventoryTable[0].kong[gPlayerCharacterId[0]];
    s32 i;
    s32 v;

    v = 0;
    for (i = 0; i < 8 && !v; i++) {
        v = row->unk42[i] > 0;
    }
    return v;
}

#pragma GLOBAL_ASM("asm/global/nonmatchings/CC800/D_8075C410.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/CC800/D_8075C414.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/CC800/D_8075C420.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/CC800/D_8075C430.s")
