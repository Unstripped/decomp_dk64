#include "common.h"
#include "actor.h"
#include "sched.h"
#include "proto/global/119370.h"
#include "proto/global/126260.h"
#include "proto/global/1295B0.h"
#include "proto/global/12E800.h"
#include "proto/global/15050.h"
#include "proto/global/166A0.h"
#include "proto/global/17B90.h"
#include "proto/global/19A00.h"
#include "proto/global/201B0.h"
#include "proto/global/35000.h"
#include "proto/global/69E60.h"
#include "proto/global/70FD0.h"
#include "proto/global/7130.h"
#include "proto/global/7CA80.h"
#include "proto/global/80150.h"
#include "proto/global/8CA50.h"
#include "proto/global/936B0.h"
#include "proto/global/CEAE0.h"
#include "proto/global/EFDC0.h"
#include "proto/minecart/0.h"
#include "proto/minecart/25F0.h"

struct MinecartElem;

// Track cursor of a minecart (the player's cart is the player actor's customState, an obstacle's
// cart its second component); minecart/0.c holds the full layout.
typedef struct MinecartCart {
    /* 0x00 */ s16 jumpHeight;
    /* 0x02 */ u8 pad2[0x10 - 0x2];
    /* 0x10 */ s16 pointIndex;
    /* 0x12 */ u8 pad12[0x30 - 0x12];
    /* 0x30 */ u8 *route;
    /* 0x34 */ u8 *routeCursor;
    /* 0x38 */ u8 pad38[0x3A - 0x38];
    /* 0x3A */ u8 passBySfxTimer;
    /* 0x3B */ u8 pad3B;
    /* 0x3C */ s16 prevTargetDist;
    /* 0x3E */ u8 pad3E[0x42 - 0x3E];
    /* 0x42 */ u8 branchSide;
} MinecartCart;

// Minecart obstacle actors (minecartUpdateObstacleType1-3): the second component pointer is the cart.
typedef struct MinecartObstacleActor {
    /* 0x000 */ Actor base;
    /* 0x178 */ MinecartCart *cart;
} MinecartObstacleActor;

typedef struct MinecartTrackPoint {
    f32 x;
    f32 y;
    f32 z;
} MinecartTrackPoint;

extern Actor *gCurrentActor;
extern Actor *gSpawnedActor;
extern Actor *gPrimaryPlayerActor;
extern PlayerState *gActivePlayerState;
extern MinecartTrackPoint **gMinecartTrackPoints;
extern PlayerStruct *gPlayerSlots;
extern u32 gFrameCounter;
extern s32 gCurrentMap;
extern s32 D_80717D4C;
extern void *D_8074E880[];
extern u8 D_80720120[];
extern s32 D_8072030C;
extern Actor *gCamActor;
extern struct MinecartElem *gMinecartJunctionTable[];
extern u8 D_80028C34[];
extern u8 D_80028C40[];
extern u8 D_80028C48[];


void minecartFollowerBehaviour(void) {
    u8 followDist = 0x96;

    behaviourFrameBegin();
    if (!(gCurrentActor->flags & 0x10)) {
        actorScriptStart(gCurrentActor, 0x310);
        actorSpawn(0x11C, 0x4C);
        actorCopyPoseAndScale(gSpawnedActor, gCurrentActor, 1.5 * gCurrentActor->sub4->scaleY);
        gSpawnedActor->parentActor = gCurrentActor;
        gSpawnedActor->yawSpeed = -1;
        gSpawnedActor->sub4->scaleX *= -1.0f;
        gSpawnedActor->unkEC = 0x2BC;
        controllerAnimLoadStateAsset1(gSpawnedActor, controllerLookupStateByHash(gSpawnedActor));
        actorSpawn(0x11C, 0x4C);
        actorCopyPoseAndScale(gSpawnedActor, gCurrentActor, 1.5 * gCurrentActor->sub4->scaleY);
        gSpawnedActor->parentActor = gCurrentActor;
        gSpawnedActor->yawSpeed = 1;
        gSpawnedActor->unkEC = 0x2BC;
        sfxPlayAtPositionPooled(gCurrentActor->x, gCurrentActor->y, gCurrentActor->z, 0x301, 0xFF, 0x7F, 0, 0, 0.0f, 0);
        gCurrentActor->state = 1;
        gCurrentActor->roll = 0x12C;
        gCurrentActor->flags &= ~0x8000;
        gCurrentActor->alpha = 0x96;
    }
    if (func_80724A20()) {
        if (gActivePlayerState->actor->state == 5) {
            if (gCurrentActor->state == 6) {
                gCurrentActor->state = 5;
            } else if (gCurrentActor->state == 5) {
                gCurrentActor->state = 6;
            }
        }
    }
    switch (gCurrentActor->state) {
    case 0:
        gCurrentActor->y += 5.0f;
        if (gCurrentActor->unk155++ >= 0x10) {
            gCurrentActor->state = 0x3B;
        }
        break;
    case 6:
        followDist = 0xFA;
        if ((gFrameCounter % gBehaviourExtraState->unkA) == 0) {
            sfxPlayAtPositionPooled(gCurrentActor->x, gCurrentActor->y, gCurrentActor->z, 0x182, 0xFF, 0x7F, 0, 0, 0.3f, 0);
            actorSpawn(0x11F, 0x50);
            gSpawnedActor->parentActor = gCurrentActor;
            actorCopyPoseAndScale(gSpawnedActor, gCurrentActor, 0.06f);
            gCurrentActor->unk15F++;
        }
        /* fallthrough */
    case 2:
    case 3:
    case 4:
    case 5:
        if (gCurrentActor->unk155 == 0xFF) {
            actorScriptStart(gCurrentActor, 0x311);
            gCurrentActor->state = 1;
        }
        /* fallthrough */
    case 1:
        gCurrentActor->yaw = mathAngleEaseToward(gCurrentActor->yaw, (gPrimaryPlayerActor->yaw + 0x800) & 0xFFF, 8.0f);
        gCurrentActor->x = (mathSinF(gPrimaryPlayerActor->yaw) * followDist + gPrimaryPlayerActor->x - gCurrentActor->x) * 0.3 + gCurrentActor->x;
        gCurrentActor->z = (mathCosF(gPrimaryPlayerActor->yaw) * followDist + gPrimaryPlayerActor->z - gCurrentActor->z) * 0.3 + gCurrentActor->z;
        gCurrentActor->x += 4.0f * mathSinF(gFrameCounter * 0x35);
        gCurrentActor->z += 4.0f * mathCosF(gFrameCounter * 0x3E);
        gCurrentActor->y = (mathSinF(gFrameCounter * 0x32) * 10.0f) + (gActivePlayerState->actor->floorY + 30.0f);
        break;
    }
    actorUpdateModelMatrix(gCurrentActor, 0);
}

s32 minecartSetTargetAheadOfPlayer(BehaviourWorkState *targetState, f32 distanceFactor) {
    targetState->targetX = ((mathSinF(gPrimaryPlayerActor->yaw) * (gActivePlayerState->actor->speedXZ * distanceFactor)) + gPrimaryPlayerActor->x);
    targetState->targetY = gActivePlayerState->actor->floorY;
    targetState->targetZ = ((mathCosF(gPrimaryPlayerActor->yaw) * (gActivePlayerState->actor->speedXZ * distanceFactor)) + gPrimaryPlayerActor->z);
}

void minecartSpawnRandomParticle(void) {
    effectSetSpeed(((randomNonNegative() >> 15) % 100) + 300);
    effectSetCallback(&D_80717D4C);
    effectSetDepth(1);
    effectSetFlags(4);
    effectCreateAtPosition(
        D_8074E880[((randomNonNegative() >> 15) % 1000) % 3],
        0.5f,
        ((randomNonNegative() >> 15) % 20) + (gCurrentActor->x - 10.0f),
        gCurrentActor->y,
        ((randomNonNegative() >> 15) % 20) + (gCurrentActor->z - 10.0f)
    );
}

void minecartFollowerChildBehaviour(void) {
    s32 padA;
    BehaviourWorkState *targetState;
    s16 angleOffset;
    s32 padB;
    s32 padC;
    f32 interpT;
    f32 sinT;
    f32 lateralOffset;
    f32 vertOffset;
    Actor *parent;
    MinecartCart *playerCart;
    f64 frameProgress;
    f32 clampedProgress;
    f32 blend;
    s16 timer;

    parent = gCurrentActor->parentActor;
    targetState = parent->customState;
    angleOffset = gCurrentActor->yawSpeed * gCurrentActor->unkEC;
    if (!(gCurrentActor->flags & 0x10)) {
        controllerAnimSetStateIfChanged(gCurrentActor, 0x59C, 0.0f, 0.0f);
        gCurrentActor->flags |= 0x800000;
        gCurrentActor->tintR = 0xFF;
        gCurrentActor->tintG = 0xFF;
        gCurrentActor->tintB = 0xFF;
        gCurrentActor->flags &= ~0x8000;
        gCurrentActor->alpha = 0x96;
    }
    gCurrentActor->yaw = parent->yaw;
    gCurrentActor->x = (mathSinF(parent->yaw + angleOffset) * 47.0f + parent->x - gCurrentActor->x) * 0.3 + gCurrentActor->x;
    gCurrentActor->z = (mathCosF(parent->yaw + angleOffset) * 47.0f + parent->z - gCurrentActor->z) * 0.3 + gCurrentActor->z;
    gCurrentActor->y += (parent->y - 10.0f - gCurrentActor->y) * 0.3;
    switch (parent->state) {
    case 2:
    case 3:
        if ((gCurrentActor->yawSpeed == 1 && parent->state == 2) || (gCurrentActor->yawSpeed == -1 && parent->state == 3)) {
            playerCart = gActivePlayerState->actor->customState;
            minecartSpawnRandomParticle();
            switch (parent->unk155) {
            case 0:
                if (playerCart->jumpHeight == 0) {
                    gCurrentActor->unk155 = 0;
                    actorScriptStart(gCurrentActor, 0x312);
                    parent->unk155 = 1;
                    minecartSetTargetAheadOfPlayer(targetState, 2.2f);
                }
                break;
            case 1:
                frameProgress = gCurrentActor->sub4->model->frame / 17.0;
                clampedProgress = MIN(1.0, frameProgress);
                blend = mathCosF(clampedProgress * 2048.0f + 2048.0f) * 0.5 + 0.5;
                gCurrentActor->x = (targetState->targetX - gCurrentActor->x) * blend + gCurrentActor->x;
                gCurrentActor->y = (gCurrentActor->y + 10.0f) + ((gActivePlayerState->actor->floorY - (gCurrentActor->y + 10.0f)) * blend);
                gCurrentActor->z = (targetState->targetZ - gCurrentActor->z) * blend + gCurrentActor->z;
                if (gPrimaryPlayerActor->sub4->animId == 0x294 || (gCurrentActor->sub4->model->frame > 16.0f && gCurrentActor->sub4->model->frame < 18.0f)) {
                    gCurrentActor->interactionType = 1;
                } else {
                    gCurrentActor->interactionType = 0;
                }
                if (gCurrentActor->unk155 != 0) {
                    parent->unk155 = 0xFF;
                }
                break;
            }
        }
        break;
    case 4:
    case 5:
        if ((gCurrentActor->yawSpeed == 1 && parent->state == 4) || (gCurrentActor->yawSpeed == -1 && parent->state == 5)) {
            minecartSpawnRandomParticle();
            switch (parent->unk155) {
            case 0:
                targetState->timer = 0x46;
                parent->unk155 = 1;
                gCurrentActor->interactionType = 1;
                sfxPlayAtPositionPooled(gCurrentActor->x, gCurrentActor->y, gCurrentActor->z, 0x301, 0xFF, 0x7F, 0, 0, 0.0f, 0);
            case 1:
                minecartSetTargetAheadOfPlayer(targetState, 0.3f);
                timer = targetState->timer;
                targetState->timer = timer - 1;
                if (timer != 0) {
                    interpT = mathCosF(targetState->timer / 70.0 * 2048.0 + 2048.0) * 0.5 + 0.5;
                    sinT = mathSinF(2048.0f * interpT);
                    lateralOffset = mathSinF(interpT * 1536.0f + 1024.0f) * (gCurrentActor->yawSpeed * -110);
                    vertOffset = (mathCosF(interpT * 4096.0f) * 0.5 + 0.5) * 50.0 + -30.0;
                    gCurrentActor->x = ((mathSinF(gPrimaryPlayerActor->yaw - 0x400) * lateralOffset + targetState->targetX) - gCurrentActor->x) * sinT + gCurrentActor->x;
                    gCurrentActor->y += (gActivePlayerState->actor->floorY + vertOffset - gCurrentActor->y) * sinT;
                    gCurrentActor->z = ((mathCosF(gPrimaryPlayerActor->yaw - 0x400) * lateralOffset + targetState->targetZ) - gCurrentActor->z) * sinT + gCurrentActor->z;
                    if (targetState->timer < 0x10) {
                        gCurrentActor->interactionType = 0;
                    }
                } else {
                    parent->unk155 = 0xFF;
                }
                break;
            }
            if (gCurrentActor->yawSpeed == 1) {
                gCurrentActor->pitch = mathAngleEaseToward(gCurrentActor->pitch, 0xC00, 7.0f);
            } else {
                gCurrentActor->pitch = mathAngleEaseToward(gCurrentActor->pitch, 0x400, 7.0f);
            }
        }
        break;
    case 6:
        if (parent->unk155 == 0) {
            targetState->timer = gBehaviourExtraState->unkB;
            parent->unk155 = 1;
        }
        if (gCurrentActor->yawSpeed == 1) {
            gCurrentActor->pitch = mathAngleEaseToward(gCurrentActor->pitch, 0xC00, 16.0f);
        } else {
            gCurrentActor->pitch = mathAngleEaseToward(gCurrentActor->pitch, 0x400, 16.0f);
        }
        timer = targetState->timer;
        if (timer != 0) {
            targetState->timer = timer - 1;
        } else {
            parent->unk155 = 0xFF;
        }
        if (gCurrentActor->unk155 == 0 && parent->unk15F == 4) {
            gActivePlayerState->stateFlags |= 0x10000000;
            gCurrentActor->unk15F = 0xB4;
            gCurrentActor->unk155++;
        }
        gCurrentActor->unkEC = mathAngleEaseToward(gCurrentActor->unkEC, 0x64, 10.0f);
        break;
    case 0x3B:
        actorDespawn(gCurrentActor);
        break;
    case 1:
        break;
    }
    if (parent->state == 6) {
        if (gCurrentActor->unk15F != 0) {
            gCurrentActor->unk15F -= 0xC;
            camSetTarget(gActivePlayerState->camActor, gActivePlayerState->actor, 4, (gCurrentActor->unk15F << 12) / 360, 0x64, 0, 5, 0x23, 0x14, 0, 0.2f);
        }
    }
    if (parent->state != 6) {
        if (gCurrentActor->pitch != 0) {
            gCurrentActor->pitch = mathAngleEaseToward(gCurrentActor->pitch, 0, 8.0f);
            gCurrentActor->unkEC = mathAngleEaseToward(gCurrentActor->unkEC, 0x2BC, 10.0f);
        }
    }
    actorUpdateModelMatrix(gCurrentActor, 0);
}

void minecartUpdateFollower(void) {
    f32 delta;
    f32 dist;
    MinecartCart *playerCart;
    s32 pointIndex;
    s16 pointX;
    s16 pointZ;

    playerCart = gActivePlayerState->actor->customState;
    pointX = gMinecartTrackPoints[gCurrentActor->unk15F][gCurrentActor->yawSpeed].x;
    pointZ = gMinecartTrackPoints[gCurrentActor->unk15F][gCurrentActor->yawSpeed].z;
    if (!(gCurrentActor->flags & 0x10)) {
        controllerAnimSetStateIfChanged(gCurrentActor, 0x5FF, 0.0f, 0.0f);
        animSetSpeed(gCurrentActor, 0, 1.0f);
        animSetLoopMode(gCurrentActor, 0, 0);
        animSetLoopLimit(gCurrentActor, 0, -1);
        gCurrentActor->unk144 = 0x24;
        if (gCurrentActor->parentActor->unk15F == 1) {
            gCurrentActor->unk15F = *playerCart->routeCursor & ~0xC0;
        } else {
            switch (*playerCart->routeCursor & ~0xC0) {
            case 1:
            case 2:
                gCurrentActor->unk15F = (gCurrentActor->parentActor->unk15F ^ 1) + 1;
                break;
            case 3:
            case 4:
            case 5:
            case 6:
                gCurrentActor->unk15F = (gCurrentActor->parentActor->unk15F % 4) + 3;
                break;
            case 7:
            case 8:
                gCurrentActor->unk15F = (gCurrentActor->parentActor->unk15F ^ 1) + 7;
                break;
            }
        }
        pointIndex = playerCart->pointIndex - 2;
        gCurrentActor->yawSpeed = MAX(0, pointIndex);
        gCurrentActor->speedXZ = 1100.0f;
        gCurrentActor->speedY = 400.0f;
        gCurrentActor->flags |= 0x800000;
        gCurrentActor->tintR = 0xFF;
        gCurrentActor->tintG = 0xFF;
        gCurrentActor->tintB = 0xFF;
        gCurrentActor->accelY = -10.0f;
        gCurrentActor->terminalSpeedY = -200.0f;
        gCurrentActor->movePitch = 0xB4;
        gCurrentActor->unkEC = 0;
    }
    if (gFrameCounter % 3 == 0) {
        effectSetDepth(1);
        effectCreateAtPosition(D_80720120, 1.0f, gCurrentActor->x, gCurrentActor->y + 10.0f, gCurrentActor->z);
    }
    gCurrentActor->yaw = mathAngleEaseToward(gCurrentActor->yaw, mathAngleBetweenPoints2D(pointX, pointZ, gCurrentActor->x, gCurrentActor->z), 6.0f);
    gCurrentActor->moveYaw = gCurrentActor->yaw;
    actorApplyGravity();
    actorApplyVelocity(gCurrentActor);
    actorUpdateFloorContactAndTilt(gCurrentActor, 2.0 * mathSinF(gFrameCounter * 0x64) + 10.0);
    if ((pointX - gCurrentActor->x) * (pointX - gCurrentActor->x) + (pointZ - gCurrentActor->z) * (pointZ - gCurrentActor->z) < 1600.0f) {
        gCurrentActor->yawSpeed++;
    }
    if (gActorGlobalState.unk15 != 0 || --gCurrentActor->movePitch == 0) {
        if (gCurrentActor->parentActor != NULL) {
            gCurrentActor->parentActor->unk15F--;
        }
        if (gCurrentActor->parentActor == NULL || gCurrentActor->parentActor->unk15F == 0) {
            if (gActivePlayerState->stateFlags & 0x10000000) {
                gActivePlayerState->stateFlags &= ~0x10000000;
                camSetTargetScaled(gActivePlayerState->camActor, gActivePlayerState->actor, 4, 0x800, 0x28, 0, 5, 0x19, 0x14, 0, 0.15f);
            }
        }
        tagBarrelSpawnActorSmokePuffs(0, 1);
        actorDespawn(gCurrentActor);
    }
    dist = gCurrentActor->x - gPlayerSlots->camX;
    dist = dist * dist;
    delta = gCurrentActor->y - gPlayerSlots->camY;
    dist = delta * delta + dist;
    delta = gCurrentActor->z - gPlayerSlots->camZ;
    dist = delta * delta + dist;
    switch (gCurrentActor->unkEC) {
    case 0:
    case 2:
        if (dist < 6400.0f) {
            sfxPlayFromActorWithAltitudeCheck(gCurrentActor, 0x128, 0xFF, 0x7F, 0);
            gCurrentActor->unkEC++;
        }
        break;
    case 1:
        if (dist > 10000.0f) {
            gCurrentActor->unkEC++;
        }
        break;
    }
    actorUpdateModelMatrix(gCurrentActor, 0);
}

void minecartStartScriptNearPlayer(void) {
    if (gCurrentActor->unk155 != 0) {
        return;
    }
    if (behaviourIsTargetWithinAngle(10000) != 0 ||
        (gBehaviourTargetActor->x - gCurrentActor->x) * (gBehaviourTargetActor->x - gCurrentActor->x) +
        (gBehaviourTargetActor->y - gCurrentActor->y) * (gBehaviourTargetActor->y - gCurrentActor->y) +
        (gBehaviourTargetActor->z - gCurrentActor->z) * (gBehaviourTargetActor->z - gCurrentActor->z) < 2500.0f) {
        actorScriptStart(gCurrentActor, 0x280);
    }
}

void minecartChooseBranchSide(MinecartCart *cart) {
    PlayerState *targetPlayerState = gBehaviourTargetActor->customState;
    MinecartCart *targetCart = targetPlayerState->actor->customState;
    u8 targetTrack = *targetCart->routeCursor - 0x10;

    if (targetTrack < *cart->routeCursor) {
        cart->branchSide = 1;
    } else if (targetTrack > *cart->routeCursor) {
        cart->branchSide = 2;
    } else {
        cart->branchSide = 0;
    }
}

void minecartAdjustTargetSpeed(void) {
    u16 targetAngle;
    PlayerState *targetPlayerState = gBehaviourTargetActor->customState;

    targetAngle = gCurrentActor->sub4->boneRotations->rotY;
    if (targetAngle >= 0x47D1 && targetAngle < 0xB830) {
        gBehaviourWorkState->unk26 = MAX(9, gBehaviourWorkState->unk26 - 5);
    } else if (targetAngle < 0x3830 || targetAngle >= 0xC7D1) {
        gBehaviourWorkState->unk26 = MIN(gBehaviourExtraState->unkD, gBehaviourWorkState->unk26 + 5);
    } else {
        gBehaviourWorkState->unk26 = targetPlayerState->actor->speedXZ;
    }
}

void minecartPlayPassBySfx(MinecartCart *cart) {
    f32 delta;
    f32 dist = gCurrentActor->x - gBehaviourTargetActor->x;
    dist = dist * dist;
    delta = gCurrentActor->y - gBehaviourTargetActor->y;
    dist = delta * delta + dist;
    delta = gCurrentActor->z - gBehaviourTargetActor->z;
    dist = sqrtf(dist + delta * delta);
    if (dist < 200.0f) {
        if (++cart->passBySfxTimer >= 9) {
            sfxPlayFromActorWithAltitudeCheck(gCurrentActor, 0x1F, 0xFF, (127.0f - (dist - cart->prevTargetDist)), 0);
            cart->passBySfxTimer = randomLcgNext() / 4294967295.0 * 3.0;
        }
    }
    cart->prevTargetDist = dist;
}

void minecartUpdateObstacleType1(void) {
    MinecartCart *cart;
    s16 *routeInfo;
    f32 nodePosZ;
    f32 nodePosY;
    f32 nodePosX;
    u8 *alloc;

    cart = ((MinecartObstacleActor *)gCurrentActor)->cart;
    behaviourFrameBegin();
    if (!(gCurrentActor->flags & 0x10)) {
        func_80724CA4(2, 1);
        gBehaviourWorkState->unk35 = 6;
    }
    if (gActorGlobalState.unk15 != 0) {
        sfxPlayFromActorWithAltitudeCheck(gCurrentActor, 0xF6, 0xFF, 0x7F, 0x1E);
        camStartShake(gCamActor, 0xA, 0x14);
        gCurrentActor->state = 0x40;
        tagBarrelSpawnActorSmokePuffs(0, 1);
    }
    switch (gCurrentActor->state) {
    case 0:
        if (gActorGlobalState.unk254 != 0) {
            routeInfo = gActorGlobalState.unk278[0];
            alloc = heapAlloc(2);
            alloc[0] = routeInfo[1];
            alloc[1] = 0xFF;
            cart->routeCursor = alloc;
            cart->pointIndex = routeInfo[2];
            gBehaviourWorkState->unk26 = 0x46;
            gCurrentActor->speedXZ = 0.0f;
            gCurrentActor->state++;
        } else {
            func_80724E48(1);
            minecartStartScriptNearPlayer();
            actorUpdateModelMatrix(gCurrentActor, 0);
            return;
        }
    case 1:
        func_80724E48(1);
        minecartStartScriptNearPlayer();
        minecartAdjustTargetSpeed();
        actorSpawnNodeEffectFacingCamera(6, 0xFF);
        actorApproachTargetSpeed(0x200);
        minecartFollowTrack(cart, 0x7FFF, 0x23);
        actorGetNodePos(gCurrentActor, 5, &nodePosX, &nodePosY, &nodePosZ);
        commandQueuePush(gCurrentActor, nodePosX, nodePosY, nodePosZ, 0xFF, 0xFF, 0xFF, 0xFF, 0);
        minecartPlayPassBySfx(cart);
        return;
    case 2:
        gCurrentActor->state = 0x40;
        actorUpdateModelMatrix(gCurrentActor, 0);
        return;
    default:
        actorUpdateModelMatrix(gCurrentActor, 0);
        return;
    }
}

void minecartUpdateObstacleType2(void) {
    MinecartCart *cart;
    s16 *routeInfo;
    f32 node2Z;
    f32 node2Y;
    f32 node2X;
    f32 node1Z;
    f32 node1Y;
    f32 node1X;
    u8 *alloc;
    s32 pad0, pad1, pad2;

    cart = ((MinecartObstacleActor *)gCurrentActor)->cart;
    behaviourFrameBegin();
    if (!(gCurrentActor->flags & 0x10)) {
        if ((gCurrentMap == 0x4D) || (gCurrentMap == 0x81) || (gCurrentMap == 0x82)) {
            actorGetOrSetNodeScale(gCurrentActor, 1, 50.0f);
        }
        effectSetDepth(1);
        effectSetDuration(-1);
        effectCreateAtActorBone(&D_8072030C, 0.14f, gCurrentActor, 0xB, 2);
        gCurrentActor->state = 0;
    }
    if ((gActorGlobalState.bossFightPhase == 9) || (gActorGlobalState.unk15 != 0)) {
        tagBarrelSpawnActorSmokePuffs(0, 1);
        gCurrentActor->state = 0x40;
        camStartShake(gCamActor, 0xA, 0x14);
    }
    switch (gCurrentActor->state) {
    case 0:
        if (gActorGlobalState.unk254 != 0) {
            routeInfo = gActorGlobalState.unk278[0];
            alloc = heapAlloc(4);
            alloc[0] = routeInfo[1];
            alloc[1] = 0xFF;
            cart->route = alloc;
            cart->routeCursor = alloc;
            cart->pointIndex = 1;
            gBehaviourWorkState->unk26 = routeInfo[2];
            gCurrentActor->speedXZ = 0.0f;
            gCurrentActor->state++;
        } else {
            actorUpdateModelMatrix(gCurrentActor, 0);
            return;
        }
    case 1:
        if ((gCurrentMap == 0x4D) || (gCurrentMap == 0x81) || (gCurrentMap == 0x82)) {
            minecartChooseBranchSide(cart);
            minecartApplyJunction(cart, gMinecartJunctionTable, 0, 3);
            actorGetNodePos(gCurrentActor, 1, &node1X, &node1Y, &node1Z);
            actorGetNodePos(gCurrentActor, 2, &node2X, &node2Y, &node2Z);
        }
        actorApproachTargetSpeed(0x200);
        minecartFollowTrack(cart, 0x7FFF, 0x23);
        if ((gCurrentActor->state == 2) && ((gCurrentMap == 0x4D) || (gCurrentMap == 0x81) || (gCurrentMap == 0x82))) {
            gCurrentActor->state = 1;
            cart->routeCursor--;
        }
        actorGetNodePos(gCurrentActor, 5, &node1X, &node1Y, &node1Z);
        commandQueuePush(gCurrentActor, node1X, node1Y, node1Z, 0xFF, 0xFF, 0xFF, 0xFF, 0);
        minecartPlayPassBySfx(cart);
        return;
    case 2:
        gCurrentActor->state = 0x40;
        actorUpdateModelMatrix(gCurrentActor, 0);
        return;
    default:
        actorUpdateModelMatrix(gCurrentActor, 0);
        return;
    }
}

void minecartUpdateObstacleType3(void) {
    MinecartCart *cart;
    s32 pad;
    f32 nodePosZ;
    f32 nodePosY;
    f32 nodePosX;
    PlayerState *playerState;
    f64 reboundSpeed;
    f64 targetSpeed;

    cart = ((MinecartObstacleActor *)gCurrentActor)->cart;
    behaviourFrameBegin();
    playerState = gBehaviourTargetActor->customState;
    if (!(gCurrentActor->flags & 0x10)) {
        gCurrentActor->unk144 = 0x3C;
        gBehaviourWorkState->unk35 = 2;
        effectSetDepth(1);
        effectSetDuration(-1);
        effectCreateAtActorBone(&D_8072030C, 0.14f, gCurrentActor, 0xB, 2);
    }
    if (gActorGlobalState.bossFightPhase == 4) {
        sfxPlayFromActorWithAltitudeCheck(gCurrentActor, 0xF6, 0xFF, 0x7F, 0x1E);
        camStartShake(gCamActor, 0xA, 0x14);
        reboundSpeed = gCurrentActor->speedXZ * 1.2;
        gCurrentActor->speedXZ = -(reboundSpeed > 0.0 ? reboundSpeed : -reboundSpeed);
        playerStateQueueCallback(0x34, gCurrentActor, 0);
    }
    func_80724A20();
    switch (gCurrentActor->state) {
    case 0:
        if (gActorGlobalState.unk254 != 0) {
            switch (gCurrentMap) {
            case 0x37:
                cart->routeCursor = D_80028C40;
                break;
            case 0x6A:
                cart->routeCursor = D_80028C48;
                break;
            default:
                cart->routeCursor = D_80028C34;
            }
            cart->pointIndex = 1;
            gCurrentActor->speedXZ = 0.0f;
            gCurrentActor->state++;
            goto case_1;
        } else {
            actorUpdateModelMatrix(gCurrentActor, 0);
            return;
        }
case_1:
    case 1:
        if (mathAngleDistance(mathAngleBetweenPoints2D(gPrimaryPlayerActor->x, gPrimaryPlayerActor->z, gCurrentActor->x, gCurrentActor->z), gCurrentActor->yaw) >= 0x201 &&
            (gCurrentActor->x - gPrimaryPlayerActor->x) * (gCurrentActor->x - gPrimaryPlayerActor->x) + (gCurrentActor->z - gPrimaryPlayerActor->z) * (gCurrentActor->z - gPrimaryPlayerActor->z) < 22500.0f) {
            gBehaviourWorkState->unk26 = 0;
        } else {
            targetSpeed = playerState->actor->speedXZ * 1.4;
            gBehaviourWorkState->unk26 = MIN(MAX(targetSpeed, 45.0), 90.0);
        }
        actorApproachTargetSpeed(0x200);
        actorSpawnNodeEffectFacingCamera(6, 0xFF);
        minecartFollowTrack(cart, 0x7FFF, 0x23);
        actorGetNodePos(gCurrentActor, 5, &nodePosX, &nodePosY, &nodePosZ);
        commandQueuePush(gCurrentActor, nodePosX, nodePosY, nodePosZ, 0xFF, 0xFF, 0xFF, 0xFF, 0);
        if (gPrimaryPlayerActor->state == 0x70 || cart->pointIndex == 0x90) {
            gCurrentActor->state++;
        }
        return;
    case 2:
        tagBarrelSpawnActorSmokePuffs(0, 1);
        gCurrentActor->state = 0x40;
        actorUpdateModelMatrix(gCurrentActor, 0);
        return;
    default:
        actorUpdateModelMatrix(gCurrentActor, 0);
        return;
    }
}
