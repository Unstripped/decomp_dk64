#include "common.h"
#include "actor.h"
#include "proto/global/119370.h"
#include "proto/global/11BC10.h"
#include "proto/global/127B00.h"
#include "proto/global/1295B0.h"
#include "proto/global/135D30.h"
#include "proto/global/15050.h"
#include "proto/global/166A0.h"
#include "proto/global/201B0.h"
#include "proto/global/35000.h"
#include "proto/global/61AA0.h"
#include "proto/global/69E60.h"
#include "proto/global/70FD0.h"
#include "proto/global/7130.h"
#include "proto/global/7CA80.h"
#include "proto/global/89250.h"
#include "proto/global/8D3E0.h"
#include "proto/global/AA960.h"
#include "proto/global/CC800.h"
#include "proto/global/F9450.h"
#include "proto/global/FCCD0.h"

typedef struct SfxTableEntry {
    /* 0x0 */ u16 actorType;
    /* 0x2 */ s16 spawnType;
    /* 0x4 */ u8 sfxId;
    /* 0x5 */ u8 spawnCount;
} SfxTableEntry; /* size = 6 */

extern Actor *gCurrentActor;
extern Actor *gPrimaryPlayerActor;
extern u32 gGlobalCutsceneFlags;
extern u8 gPlayerCount;
extern SfxTableEntry gActorSpawnSfxTable[];

extern u8 D_807204BC[];
extern u8 D_80720508[];
extern u8 D_807205C4[];
extern u8 D_807205E8[];
extern u8 D_80720710[];
extern u8 D_80720768[];
extern u8 D_807207BC[];
extern u8 D_807207E0[];
extern u8 D_807209EC[];
extern u8 D_80720A10[];
extern u8 D_80720A34[];
extern u8 D_80720A58[];
extern u8 D_807211D0[];
extern u8 D_80721378[];


void sfxSpawnTableNodes(Actor *actor) {
    s32 i;
    s32 found;
    s32 j;
    s16 yawStep;
    s16 yaw;

    i = 0;
    found = 0;
    yaw = 0;
    if (gPlayerCount >= 2) {
        return;
    }
    if (gGlobalOverlayFlags & 0x4000) {
        return;
    }
    while (found == 0 && gActorSpawnSfxTable[i].actorType != 0) {
        if (gActorSpawnSfxTable[i].actorType == actor->actorType) {
            found = 1;
        } else {
            i++;
        }
    }
    if (found == 0) {
        return;
    }
    if (gActorSpawnSfxTable[i].sfxId != 0) {
        sfxAllocateChannel(gActorSpawnSfxTable[i].sfxId, 1.0f);
    }
    yawStep = 0xFFF / gActorSpawnSfxTable[i].spawnCount;
    for (j = 0; j < gActorSpawnSfxTable[i].spawnCount; j++) {
        actorSpawnNodeEntryScaled(gActorSpawnSfxTable[i].spawnType, actor->x, actor->y, actor->z, yaw, 1, -1, 0);
        yaw += yawStep;
    }
}

// spawnData of the bouncing pickups (actorDropBounceExpireUpdate, actorBounceFadeInSpinUpdate):
// the 8-float customData record actorSpawnNodeEntryScaled fills and actorListSpawnNodeInternal copies.
typedef struct BounceSpawnConfig {
    /* 0x00 */ f32 initialState;
    /* 0x04 */ f32 yaw;
    /* 0x08 */ f32 flagId;
    /* 0x0C */ f32 padC[5];
} BounceSpawnConfig; /* size = 0x20 */

void actorSpawnNodeEntryScaled(s16 actorType, f32 x, f32 y, f32 z, s32 yaw, s32 initialState, s32 flagId, Actor *extraParam) {
    s32 pad;
    BounceSpawnConfig config;
    f32 scale;

    scale = 0.15f;
    if (gGlobalCutsceneFlags & 0x10) {
        scale *= 2.0f;
    }
    config.initialState = (u8)initialState;
    config.yaw = (s16)yaw;
    config.flagId = (s16)flagId;
    actorListSpawnNodeEntry(actorType, x, y, z, 0, scale, extraParam, &config);
}

void effectSpawnAttachedSprite(DropBounceState *state, void *spriteAsset, f32 scale) {
    if (gGlobalCutsceneFlags & 0x10) {
        scale *= 2.0f;
    }
    effectSetDuration(-1);
    effectSetDepth(1);
    effectSetMode(2);
    state->sprite = effectCreateAtActorBone(spriteAsset, scale * 0.35, gCurrentActor, 1, 2);
}

void actorHealthDropUpdate(void) {
    DropBounceState *state = gCurrentActor->customState;

    actorDropBounceExpireUpdate(4.5f);
    if (!(gCurrentActor->flags & 0x10)) {
        effectSpawnAttachedSprite(state, D_80720710, 1.0f);
    }
}

void func_806A5FA4(void) {
    DropBounceState *state = gCurrentActor->customState;

    actorDropBounceExpireUpdate(4.5f);
    if (!(gCurrentActor->flags & 0x10)) {
        effectSpawnAttachedSprite(state, D_80720508, 1.0f);
    }
}

void effectSpawnAttachedSpriteColored(void *spriteAsset, s32 characterId) {
    DropBounceState *state = gCurrentActor->customState;

    actorDropBounceExpireUpdate(4.5f);
    if (!(gCurrentActor->flags & 0x10)) {
        if (characterId != gPrimaryPlayerActor->actorType) {
            effectSetColor(0xFF, 0xFF, 0xFF, 0x64);
        }
        effectSpawnAttachedSprite(state, spriteAsset, 1.0f);
    }
}

void effectSpawnAttachedSpriteColoredType3(void) {
    effectSpawnAttachedSpriteColored(D_807209EC, 3);
}

void effectSpawnAttachedSpriteColoredType6(void) {
    effectSpawnAttachedSpriteColored(D_80720A10, 6);
}

void effectSpawnAttachedSpriteColoredType4(void) {
    effectSpawnAttachedSpriteColored(D_807207E0, 4);
}

void effectSpawnAttachedSpriteColoredType2(void) {
    effectSpawnAttachedSpriteColored(D_80720A34, 2);
}

void effectSpawnAttachedSpriteColoredType5(void) {
    effectSpawnAttachedSpriteColored(D_80720A58, 5);
}

void func_806A615C(void) {
    DropBounceState *state = gCurrentActor->customState;

    actorDropBounceExpireUpdate(4.5f);
    if (!(gCurrentActor->flags & 0x10)) {
        effectSetScale(-0.35f, 0.35f);
        effectSpawnAttachedSprite(state, D_80720768, 1.0f);
    }
}

void func_806A61D0(void) {
    DropBounceState *state = gCurrentActor->customState;

    actorDropBounceExpireUpdate(4.5f);
    if (!(gCurrentActor->flags & 0x10)) {
        effectSpawnAttachedSprite(state, D_807204BC, 1.0f);
    }
}

void func_806A6230(void) {
    DropBounceState *state = gCurrentActor->customState;

    actorDropBounceExpireUpdate(4.5f);
    if (!(gCurrentActor->flags & 0x10)) {
        if ((gGlobalOverlayFlags & 0x80000) || (gGlobalOverlayFlags & 0x2000)) {
            gCurrentActor->unk15F = 1;
        }
        effectSpawnAttachedSprite(state, D_807207BC, 1.0f);
    }
}

void effectSpawnA6230Wrapper(void) {
    func_806A6230();
}

void func_806A62D4(void) {
    DropBounceState *state = gCurrentActor->customState;

    actorDropBounceExpireUpdate(4.5f);
    if (!(gCurrentActor->flags & 0x10)) {
        effectSetColor(0xFF, 0xFF, 0, 0xFF);
        effectSpawnAttachedSprite(state, D_807211D0, 1.5f);
    }
}

void func_806A6348(void) {
    DropBounceState *state = gCurrentActor->customState;

    actorDropBounceExpireUpdate(4.5f);
    if (!(gCurrentActor->flags & 0x10)) {
        effectSpawnAttachedSprite(state, D_807205C4, 1.0f);
    }
}

void func_806A63A8(void) {
    DropBounceState *state = gCurrentActor->customState;

    actorDropBounceExpireUpdate(4.5f);
    if (!(gCurrentActor->flags & 0x10)) {
        effectSpawnAttachedSprite(state, D_807205E8, 1.0f);
    }
}

void func_806A6408(void) {
    DropBounceState *state = gCurrentActor->customState;

    actorDropBounceExpireUpdate(12.0f);
    if (!(gCurrentActor->flags & 0x10)) {
        effectSpawnAttachedSprite(state, D_80721378, 2.0f);
    }
}

extern u8 D_807203B0;
extern u8 D_807203D4;
extern u8 D_807203F8;
extern u8 D_8072041C;
extern u8 D_80720440;

void func_806A6468(void) {
    DropBounceState *state;
    void *anim;

    state = gCurrentActor->customState;
    actorDropBounceExpireUpdate(4.5f);
    if (!(gCurrentActor->flags & 0x10)) {
        switch (gPrimaryPlayerActor->actorType) {
        case 3:
            anim = &D_807203B0;
            break;
        case 2:
            anim = &D_8072041C;
            break;
        case 4:
            anim = &D_807203F8;
            break;
        case 6:
            anim = &D_807203D4;
            break;
        case 5:
            anim = &D_80720440;
            break;
        }
        effectSpawnAttachedSprite(state, anim, 1.0f);
        if (gCurrentActor->state == 0x63) {
            gCurrentActor->state = 1;
            gCurrentActor->unk15F = 2;
        }
    }
}

extern u8 D_80720EBC;
extern u8 D_80720EE8;
extern u8 D_80720F14;
extern u8 D_80720F40;
extern u8 D_80720F6C;

void func_806A6574(void) {
    DropBounceState *state;
    void *anim;

    state = gCurrentActor->customState;
    actorDropBounceExpireUpdate(4.5f);
    if (!(gCurrentActor->flags & 0x10)) {
        switch (gPrimaryPlayerActor->actorType) {
        case 3:
            anim = &D_80720EE8;
            break;
        case 2:
            anim = &D_80720F40;
            break;
        case 4:
            anim = &D_80720F14;
            break;
        case 6:
            anim = &D_80720EBC;
            break;
        case 5:
            anim = &D_80720F6C;
            break;
        }
        effectSpawnAttachedSprite(state, anim, 1.0f);
    }
}

extern s16 D_8075038C;

void actorDropBounceExpireUpdate(f32 floorOffset) {
    DropBounceState *state;

    state = gCurrentActor->customState;
    if (gGlobalCutsceneFlags & 0x10) {
        floorOffset *= 2.0f;
    }
    if (!(gCurrentActor->flags & 0x10)) {
        gCurrentActor->state = (s32)((BounceSpawnConfig *)gCurrentActor->spawnData)->initialState;
        gCurrentActor->moveYaw = ((BounceSpawnConfig *)gCurrentActor->spawnData)->yaw;
        gCurrentActor->yaw = gCurrentActor->moveYaw;
        actorAppendModelSubNode(gCurrentActor, 0.0f, 0.0f, 0.0f, -1);
        state->bounceCount = 0;
        state->collectable = 0;
        state->flagId = ((BounceSpawnConfig *)gCurrentActor->spawnData)->flagId;
        gCurrentActor->unkFA = 0x270F;
    }
    if (gActorGlobalState.notifyReceived != 0) {
        gCurrentActor->state = gActorGlobalState.notifyValue[0];
    }
    actorUpdatePrevContactFlags(gCurrentActor);
    if (gCurrentActor->hasArcBounds != 0) {
        if (actorAngleInArc(gCurrentActor, gCurrentActor->moveYaw) == 0) {
            s16 midYaw;
            s16 backYaw;
            s16 delta;

            midYaw = mathAngleArcMidpoint(gCurrentActor->arcYawMin, gCurrentActor->arcYawMax);
            backYaw = (gCurrentActor->moveYaw + 0x800) & 0xFFF;
            delta = midYaw - backYaw;
            gCurrentActor->moveYaw = midYaw + delta;
        }
    }
    switch (gCurrentActor->state) {
    case 0:
        break;
    case 1:
        gCurrentActor->unk144 = 0x1C;
        actorSetCollisionRadius(gCurrentActor, 60.0f);
        actorAppendModelNode(gCurrentActor, 0.0f, 0.0f, 0.0f, 50.0f, -1);
        actorAppendModelSubNode(gCurrentActor, 0.0f, 0.0f, 0.0f, -1);
        gCurrentActor->speedY = ((randomLcgNext() / 10000) % 200) * 0.5 + 220.0 - 50.0;
        if (!(gGlobalOverlayFlags & 0x4000) && ((gCurrentActor->actorType < 0x4B) || (gCurrentActor->actorType >= 0x50))) {
            gCurrentActor->speedXZ = 30.0f;
        }
        gCurrentActor->state++;
    case 2:
        actorApplyVelocity(gCurrentActor);
        actorUpdateFloorContactAndTilt(gCurrentActor, floorOffset);
        gCurrentActor->speedY -= 20.0f;
        if (gCurrentActor->speedY < D_8075038C) {
            gCurrentActor->speedY = D_8075038C;
        }
        if ((gCurrentActor->contactFlags & 1) && !(gCurrentActor->prevContactFlags & 1)) {
            switch (state->bounceCount) {
            case 0:
                if (gCurrentActor->unk15F != 1) {
                    state->collectable = 1;
                }
                gCurrentActor->speedY = 150.0f;
                break;
            case 1:
                gCurrentActor->speedY = 100.0f;
                break;
            case 2:
                gCurrentActor->speedY = 50.0f;
                break;
            case 3:
                gCurrentActor->speedXZ = 0.0f;
                gCurrentActor->speedY = 0.0f;
                if (gCurrentActor->actorType == 0x8C) {
                    state->collectable = 1;
                }
                if (gCurrentActor->actorType != 0x6E && gCurrentActor->actorType != 0x8C && !(gGlobalOverlayFlags & 0x4000) && gCurrentActor->unk15F != 2) {
                    state->expireTimer = 0x64;
                    gCurrentActor->state = 3;
                } else {
                    gCurrentActor->state = 0x64;
                }
                break;
            }
            switch (gCurrentActor->actorType) {
            case 0x34:
                sfxPlayFromActorWithAltitudeCheck(gCurrentActor, 0xF5, gCurrentActor->speedY + 105.0f, 0x7F, 0x1E);
                break;
            case 0x36:
                if (state->bounceCount == 0) {
                    sfxPlayFromActorWithAltitudeCheck(gCurrentActor, 0x1D1, 0xFF, 0x7F, 0xA);
                }
                break;
            default:
                sfxPlayFromActorWithAltitudeCheck(gCurrentActor, 1, gCurrentActor->speedY + 105.0f, 0x7F, 0x14);
                break;
            }
            state->bounceCount++;
        }
        break;
    case 3:
        if (camIsCutsceneActive() == 0) {
            state->expireTimer--;
        }
        if (state->expireTimer == 0) {
            gCurrentActor->state = 4;
        }
        break;
    case 4:
        state->sprite->alpha -= 5;
        if (state->sprite->alpha < 0xA) {
            if ((gGlobalOverlayFlags & 0x10000) && actorTypeIsRespawnPickup(gCurrentActor->actorType) != 0) {
                delayedSpawnQueueAddActor(gCurrentActor->actorType, 0x258, gCurrentActor->x, gCurrentActor->y, gCurrentActor->z);
            }
            actorDespawn(gCurrentActor);
        }
        break;
    case 25:
        state->expireTimer = 0x64;
        gCurrentActor->state = 3;
        state->collectable = 1;
        break;
    }
}

// customState of the fade-in spinning bouncers (actorBounceFadeInSpinUpdate, actorUpdateSfxAndGround).
typedef struct BounceFadeState {
    /* 0x0 */ u8 bounceCount;
    /* 0x1 */ u8 collectable;
    /* 0x2 */ u8 pad2[6];
    /* 0x8 */ u16 fadeInFrames;
    /* 0xA */ s16 flagId;
} BounceFadeState;

// customState of the path-following collectibles (actorPathCollectibleUpdate).
typedef struct PathCollectibleState {
    /* 0x0 */ u8 pathId;
    /* 0x1 */ u8 pathSpeed;
    /* 0x2 */ s8 pathHandle;
    /* 0x3 */ u8 pad3[1];
    /* 0x4 */ u16 bobAngle;
    /* 0x6 */ s16 collectedFlag;
} PathCollectibleState;

extern s16 D_80750384;
extern f32 D_80750388;


void actorBounceFadeInSpinUpdate(u8 fadeAlpha) {
    BounceFadeState *state;
    s16 volume;

    state = gCurrentActor->customState;
    if (!(gCurrentActor->flags & 0x10)) {
        gCurrentActor->flags |= 0x801000;
        gCurrentActor->tintR = 0xFF;
        gCurrentActor->tintG = 0xFF;
        gCurrentActor->tintB = 0xFF;
        gCurrentActor->flags &= ~0x8000;
        gCurrentActor->state = (s32)((BounceSpawnConfig *)gCurrentActor->spawnData)->initialState;
        gCurrentActor->moveYaw = ((BounceSpawnConfig *)gCurrentActor->spawnData)->yaw;
        gCurrentActor->yaw = gCurrentActor->moveYaw;
        state->bounceCount = 0;
        state->collectable = 1;
        state->flagId = ((BounceSpawnConfig *)gCurrentActor->spawnData)->flagId;
        gCurrentActor->unkFA = 0x270F;
        playerAddHealthDelta(0, 0x40);
    }
    if (state->fadeInFrames < 30.0f) {
        state->fadeInFrames++;
    }
    gCurrentActor->alpha = state->fadeInFrames * 0.033333335f * 255.0f;
    if (gActorGlobalState.notifyReceived != 0) {
        gCurrentActor->state = gActorGlobalState.notifyValue[0];
    }
    actorUpdatePrevContactFlags(gCurrentActor);
    if (gCurrentActor->hasArcBounds != 0 && actorAngleInArc(gCurrentActor, gCurrentActor->moveYaw) == 0) {
        s16 midYaw = mathAngleArcMidpoint(gCurrentActor->arcYawMin, gCurrentActor->arcYawMax);
        s16 backYaw = (gCurrentActor->moveYaw + 0x800) & 0xFFF;
        s16 delta = midYaw - backYaw;

        gCurrentActor->moveYaw = midYaw + delta;
    }
    if (gCurrentActor->state == 1 || gCurrentActor->state == 2 || gCurrentActor->state == 4
        || gCurrentActor->state == 5 || gCurrentActor->state == 6) {
        gCurrentActor->unk144 = 0x1C;
        actorSetCollisionRadius(gCurrentActor, 60.0f);
        actorAppendModelNode(gCurrentActor, 0.0f, 0.0f, 0.0f, 50.0f, -1);
        actorAppendModelSubNode(gCurrentActor, 0.0f, 0.0f, 0.0f, -1);
        switch (gCurrentActor->state) {
        case 1:
            gCurrentActor->speedXZ = D_80750384;
            gCurrentActor->speedY = 0.0f;
            break;
        case 2:
            gCurrentActor->speedY = 2000.0f;
            break;
        case 4:
            gCurrentActor->speedXZ = 1500.0f;
            gCurrentActor->speedY = 4000.0f;
            break;
        case 5:
            gCurrentActor->speedXZ = 200.0f;
            gCurrentActor->speedY = 2000.0f;
            break;
        case 6:
            gCurrentActor->speedXZ = 1000.0f;
            gCurrentActor->speedY = 2000.0f;
            break;
        }
        gCurrentActor->state = 3;
    }
    switch (gCurrentActor->state) {
    case 0:
        break;
    case 3:
        actorApplyVelocity(gCurrentActor);
        actorUpdateFloorContactAndTilt(gCurrentActor, 0.0f);
        gCurrentActor->speedY += D_80750388;
        if (gCurrentActor->speedY < D_8075038C) {
            gCurrentActor->speedY = D_8075038C;
        }
        if ((gCurrentActor->contactFlags & 1) && !(gCurrentActor->prevContactFlags & 1)) {
            volume = 0xC8;
            switch (state->bounceCount) {
            case 0:
                gCurrentActor->speedY = 1600.0f;
                gCurrentActor->speedXZ /= 2;
                break;
            case 1:
                gCurrentActor->speedY = 1200.0f;
                gCurrentActor->speedXZ /= 2;
                volume = 0x64;
                break;
            case 2:
                gCurrentActor->speedY = 800.0f;
                gCurrentActor->speedXZ /= 2;
                volume = 0x46;
                break;
            case 3:
                gCurrentActor->speedXZ = 0.0f;
                gCurrentActor->speedY = 0.0f;
                volume = 0x1E;
                if (fadeAlpha != 0) {
                    gCurrentActor->state = 0x64;
                }
                break;
            }
            if (gCurrentActor->actorType == 0x48) {
                sfxPlayAtPositionPooled(gCurrentActor->x, gCurrentActor->y, gCurrentActor->z, 0x2A1, volume, 0x7F, 0, 0, 0.0f, 0);
            }
            state->bounceCount++;
        }
        break;
    case 0x64:
        break;
    }
    gCurrentActor->yaw += 0x72;
    actorUpdateModelMatrix(gCurrentActor, 0);
}

void actorBounceFadeInSpinUpdateType1(void) {
    actorBounceFadeInSpinUpdate(1);
}


void actorUpdateSfxAndGround(void) {
    BounceFadeState *state;

    state = gCurrentActor->customState;
    if (!(gCurrentActor->flags & 0x10)) {
        gCurrentActor->renderFlags |= 4;
        gCurrentActor->flags |= 0x400;
        effectSpawnBurstParticleCluster(gCurrentActor);
    }
    if (state->fadeInFrames == 1) {
        sfxPlayAtPositionPooled(gCurrentActor->x, gCurrentActor->y, gCurrentActor->z, 0x73, 0xFF, 0x7F, 1, 0, 0.0f, 0);
        sfxAllocateChannel(0x3B, 0.7f);
    } else if (state->fadeInFrames == 0xA) {
        sfxPlayAtPositionPooled(gCurrentActor->x, gCurrentActor->y, gCurrentActor->z, 0x19C, 0xB4, 0x7F, 1, 0, 0.0f, 0);
    }
    actorBounceFadeInSpinUpdate(0);
    if (gCurrentActor->y < gCurrentActor->waterY) {
        gCurrentActor->speedXZ = 0.0f;
        gCurrentActor->y = gCurrentActor->waterY;
        gCurrentActor->speedY = gCurrentActor->accelY;
    }
    billboardSubmit(gCurrentActor, 0x3C8, 0x40, 0x40, 0x1E, 0x1E, 1, 0x96, 0x78, 0, 1.0f);
}


void actorSpawnRingBurstAndUpdate(void) {
    if (!(gCurrentActor->flags & 0x10)) {
        gCurrentActor->flags |= 0x400;
        effectSpawnRingBursts(gCurrentActor, 20.0f, 40.0f, 0x1E);
        gCurrentActor->floorY = 99999.0f;
        actorUpdateFloorContactAndTilt(gCurrentActor, 0);
    }
    actorBounceFadeInSpinUpdate(0);
    if (gCurrentActor->floorY != 99999.0f) {
        billboardSubmit(gCurrentActor, 0x3C8, 0x40, 0x40, 0x19, 0x19, 1, 0x96, 0x78, 0, 1.0f);
    }
}



// spawnData of the path-following collectibles.
typedef struct PathCollectibleConfig {
    s32 pathId;
    s32 pathSpeed;
} PathCollectibleConfig;

void actorPathCollectibleUpdate(void *spriteAsset) {
    PathCollectibleState *state;
    s16 unlockFlag;
    s32 otherKong;
    s32 unlocked;

    state = gCurrentActor->customState;
    if (!(gCurrentActor->flags & 0x10)) {
        if (gCurrentActor->actorType == 0x93) {
            state->collectedFlag = -1;
        } else {
            state->collectedFlag = actorListLookupEntry(actorListFindIdByActor(gCurrentActor));
        }
        if (state->collectedFlag != -1 && flagGet(state->collectedFlag, 0) != 0) {
            actorDespawn(gCurrentActor);
            return;
        }
        actorAppendModelSubNode(gCurrentActor, 0.0f, 0.0f, 0.0f, -1);
        actorSetCollisionRadius(gCurrentActor, 175.0f);
        actorAppendModelNode(gCurrentActor, 0.0f, 12.0f, 0.0f, 80.0f, -1);
        state->pathId = ((PathCollectibleConfig *)gCurrentActor->spawnData)->pathId;
        state->pathSpeed = ((PathCollectibleConfig *)gCurrentActor->spawnData)->pathSpeed;
        state->pathHandle = pathPlaybackStart(gCurrentActor, state->pathId, 0, 0.0f, 0.0f, 0.0f, 0);
        if (state->pathHandle != -1) {
            pathPlaybackSetLooping(state->pathHandle, 1);
            pathPlaybackSetSpeed(state->pathHandle, state->pathSpeed);
            pathPlaybackSetLoopLimit(state->pathHandle, -1);
            pathPlaybackSetActive(state->pathHandle, 1);
        }
        state->bobAngle = 0;
    } else {
        if (state->pathHandle != -1) {
            pathPlaybackAdvance(state->pathHandle);
            pathPlaybackGetPosition(state->pathHandle, &gCurrentActor->x, &gCurrentActor->y, &gCurrentActor->z);
        }
        gCurrentActor->y += 5.0 * mathSinF(state->bobAngle);
        state->bobAngle = (state->bobAngle + 0x50) & 0xFFF;
        if (gGameFrameCounter % 0x18 == 0) {
            switch (gCurrentActor->actorType) {
            case 0x5B:
                unlockFlag = 6;
                break;
            case 0x6F:
                unlockFlag = 0x75;
                break;
            case 0x70:
                unlockFlag = 0x42;
                break;
            case 0x71:
                unlockFlag = 0x46;
                break;
            default:
                unlockFlag = -1;
                break;
            }
            unlocked = (unlockFlag == -1 || flagGet(unlockFlag, 0) != 0) ? 1 : 0;
            if (unlocked != 0) {
                effectSetDepth(1);
                otherKong = 1;
                if (gCurrentActor->actorType == 0x93) {
                    otherKong = 0;
                } else if (gPrimaryPlayerActor->actorType == 3 && gCurrentActor->actorType == 0x5B) {
                    otherKong = 0;
                } else if (gPrimaryPlayerActor->actorType == 6 && gCurrentActor->actorType == 0x6F) {
                    otherKong = 0;
                } else if (gPrimaryPlayerActor->actorType == 5 && gCurrentActor->actorType == 0x70) {
                    otherKong = 0;
                } else if (gPrimaryPlayerActor->actorType == 4 && gCurrentActor->actorType == 0x71) {
                    otherKong = 0;
                } else if (gPrimaryPlayerActor->actorType == 2 && gCurrentActor->actorType == 0x72) {
                    otherKong = 0;
                }
                if (otherKong != 0) {
                    effectSetColor(0xFF, 0xFF, 0xFF, 0x96);
                } else {
                    effectSetCallback(&effectProximityFadeUpdate);
                    effectSetSpeed(0x226);
                }
                effectSetFlags(4);
                effectSetMode(3);
                effectCreateAtActorBone(spriteAsset, 0.8f, gCurrentActor, 1, 2);
                gCurrentActor->unk144 = 2;
            } else {
                gCurrentActor->unk144 = 1;
            }
        }
        if (gActorGlobalState.bossFightPhase == 4) {
            effectSpawnBurstParticleCluster(gCurrentActor);
            sfxPlayAtPositionPooled(gCurrentActor->x, gCurrentActor->y, gCurrentActor->z, 0x2BF, 0xFF, 0x7F, 0x1E, 0, 0.0f, 0);
            actorDespawn(gCurrentActor);
            if (gCurrentActor->actorType == 0x93) {
                func_80724994(3, 1, 0x27, 0, 0);
            } else {
                if (state->collectedFlag != -1) {
                    flagSet(state->collectedFlag, 1, 0);
                }
                slotQueueUpdate(0, 0, 0);
                slotQueueAddValue(0, 0, 0xA);
            }
        }
    }
}

extern u8 D_80720FBC;
void actorPathCollectibleUpdateFBC(void) {
    actorPathCollectibleUpdate(&D_80720FBC);
}

extern u8 D_80720F98;

void actorPathCollectibleUpdateF98(void) {
    actorPathCollectibleUpdate(&D_80720F98);
}

extern u8 D_80721028;

void actorPathCollectibleUpdate1028(void) {
    actorPathCollectibleUpdate(&D_80721028);
}

extern u8 D_80721004;

void actorPathCollectibleUpdate1004A(void) {
    actorPathCollectibleUpdate(&D_80721004);
}

extern u8 D_80720FE0;

void actorPathCollectibleUpdateFE0(void) {
    actorPathCollectibleUpdate(&D_80720FE0);
}

void actorPathCollectibleUpdate1004B(void) {
    actorPathCollectibleUpdate(&D_80721004);
}


// Seven sprite assets the sparkle actor picks from at random.
typedef struct SparkleSpriteTable {
    void *sprites[7];
} SparkleSpriteTable;

extern u8 D_80721170;
extern SparkleSpriteTable sSparkleSprites;

void effectActorSparkleTick(void) {
    s32 hasInstrument;
    s32 idx;
    SparkleSpriteTable table;

    hasInstrument = gPlayerInventoryTable[0].kong[gPlayerCharacterId[0]].instrumentFlags & 1;
    if (!(gCurrentActor->flags & 0x10)) {
        actorAppendModelSubNode(gCurrentActor, 0.0f, 10.0f, 0.0f, -1);
        actorSetCollisionRadius(gCurrentActor, 175.0f);
        actorAppendModelNode(gCurrentActor, 0.0f, 10.0f, 0.0f, 80.0f, -1);
        gCurrentActor->floorY = 99999.0f;
        actorUpdateFloorContactAndTilt(gCurrentActor, 0);
    }
    actorUpdatePrevContactFlags(gCurrentActor);
    if (hasInstrument != 0 && gActorGlobalState.bossFightPhase == 4 && gFrameCounter % 5 == 0) {
        idx = (randomNonNegative() >> 15) % 0xFF % 7;
        table = sSparkleSprites;
        effectSetCallback(&effectOrbitSourceUpdate);
        effectSetDuration(-1);
        effectSetDepth(1);
        effectSetSpeed(100);
        effectCreateAtActorBone(table.sprites[idx], 0.2f, gCurrentActor, 1, 0);
        sfxAllocateChannel(0x7F, 1.0f);
        slotQueueUpdate(7, 0, 0);
        slotQueueAddValue(7, 0, slotQueueGetMaxValue(7, 0));
    }
    if (!(gFrameCounter & 0xF)) {
        effectSetDepth(1);
        effectSetCallback(&effectProximityFadeUpdate);
        effectSetSpeed(0x226);
        effectSetMode(2);
        effectSetColor(0xFF, 0xFF, 0xFF, hasInstrument ? 0xFF : 0x7F);
        effectCreateAtActorBone(&D_80721170, 0.4f, gCurrentActor, 1, 2);
    }
    if (gCurrentActor->floorY != 99999.0f) {
        billboardSubmit(gCurrentActor, 0x3C8, 0x40, 0x40, 0xE, 0xE, 1, 0x96, 0x78, 0, 1.0f);
    }
}

// customState of the shrinking actor (effectActorShrinkTick).
typedef struct ShrinkState {
    f32 scale;
    s16 frames;
} ShrinkState;

extern u8 sShrinkBone;
extern u8 sShrinkStartAlpha;
extern u8 sShrinkAlphaStep;
extern f32 sShrinkRate;
extern f32 sShrinkFrames;

void effectActorShrinkTick(void) {
    ShrinkState *state;
    BoneVector *scales;

    state = gCurrentActor->customState;
    if (!(gCurrentActor->flags & 0x10)) {
        gCurrentActor->sub4->boneScales = heapAlloc(0x20);
        heapClearBlock(gCurrentActor->sub4->boneScales);
        state->frames = 0;
        state->scale = 1.0f;
        gCurrentActor->flags &= ~0x8000;
        gCurrentActor->flags |= 0x40000000;
        gCurrentActor->alpha = sShrinkStartAlpha;
    }
    if (sShrinkAlphaStep < gCurrentActor->alpha) {
        gCurrentActor->alpha -= sShrinkAlphaStep;
    }
    state->frames += 1;
    if (sShrinkFrames < state->frames) {
        actorDespawn(gCurrentActor);
    } else {
        state->scale *= sShrinkRate;
        scales = gCurrentActor->sub4->boneScales;
        scales->bone = sShrinkBone;
        scales->lastBone = 0xFF;
        scales->x = state->scale;
        scales->y = state->scale;
        scales->z = state->scale;
        scales[1].bone = 0xFF;
        actorUpdateModelMatrix(gCurrentActor, 0);
    }
}


void func_806A8070(void) {
    if (!(gCurrentActor->flags & 0x10)) {
        gCurrentActor->flags |= 0x40000000;
    }
    actorUpdateModelMatrix(gCurrentActor, 0);
}
